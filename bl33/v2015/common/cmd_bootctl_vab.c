/* SPDX-License-Identifier: (GPL-2.0+ OR MIT) */
/*
 * common/cmd_bootctl_vab.c
 *
 * Copyright (C) 2020 Amlogic, Inc. All rights reserved.
 *
 */

#include <common.h>
#include <command.h>
#include <environment.h>
#include <malloc.h>
#include <asm/byteorder.h>
#include <config.h>
#include <asm/arch/io.h>
#include <partition_table.h>
#include <libavb.h>
#include <version.h>
#include <fb_mmc.h>
#include <mmc.h>
#include <amlogic/aml_mmc.h>
#include <u-boot/sha1.h>
#include <emmc_partitions.h>

#ifdef CONFIG_BOOTLOADER_CONTROL_BLOCK

// Spaces used by misc partition are as below:
// 0   - 2K     For bootloader_message
// 2K  - 16K    Used by Vendor's bootloader (the 2K - 4K range may be optionally used
//              as bootloader_message_ab struct)
// 16K - 32K    Used by uncrypt and recovery to store wipe_package for A/B devices
// 32K - 64K    System space, used for miscellanious AOSP features. See below.
// Note that these offsets are admitted by bootloader,recovery and uncrypt, so they
// are not configurable without changing all of them.
#define BOOTLOADER_MESSAGE_OFFSET_IN_MISC 0
#define VENDOR_SPACE_OFFSET_IN_MISC 2 * 1024
#define WIPE_PACKAGE_OFFSET_IN_MISC 16 * 1024
#define SYSTEM_SPACE_OFFSET_IN_MISC 32 * 1024
#define SYSTEM_SPACE_SIZE_IN_MISC 32 * 1024
#define BOOTLOADER_OFFSET		512
#define BOOTLOADER_MAX_SIZE		(4 * 1024 * 1024)

#define MERGE_STATE_FILE "/ota/state"

extern int store_read_ops(
    unsigned char *partition_name,
    unsigned char * buf, uint64_t off, uint64_t size);
extern int store_write_ops(
    unsigned char *partition_name,
    unsigned char * buf, uint64_t off, uint64_t size);

#define AB_METADATA_MISC_PARTITION_OFFSET 2048

#define MISCBUF_SIZE  2080

/* Bootloader Message (2-KiB)
 *
 * This structure describes the content of a block in flash
 * that is used for recovery and the bootloader to talk to
 * each other.
 *
 * The command field is updated by linux when it wants to
 * reboot into recovery or to update radio or bootloader firmware.
 * It is also updated by the bootloader when firmware update
 * is complete (to boot into recovery for any final cleanup)
 *
 * The status field was used by the bootloader after the completion
 * of an "update-radio" or "update-hboot" command, which has been
 * deprecated since Froyo.
 *
 * The recovery field is only written by linux and used
 * for the system to send a message to recovery or the
 * other way around.
 *
 * The stage field is written by packages which restart themselves
 * multiple times, so that the UI can reflect which invocation of the
 * package it is.  If the value is of the format "#/#" (eg, "1/3"),
 * the UI will add a simple indicator of that status.
 *
 * We used to have slot_suffix field for A/B boot control metadata in
 * this struct, which gets unintentionally cleared by recovery or
 * uncrypt. Move it into struct bootloader_message_ab to avoid the
 * issue.
 */
struct bootloader_message {
	char command[32];
	char status[32];
	char recovery[768];

	// The 'recovery' field used to be 1024 bytes.  It has only ever
	// been used to store the recovery command line, so 768 bytes
	// should be plenty.  We carve off the last 256 bytes to store the
	// stage string (for multistage packages) and possible future
	// expansion.
	char stage[32];

	// The 'reserved' field used to be 224 bytes when it was initially
	// carved off from the 1024-byte recovery field. Bump it up to
	// 1184-byte so that the entire bootloader_message struct rounds up
	// to 2048-byte.
	char reserved[1184];
};

/**
 * The A/B-specific bootloader message structure (4-KiB).
 *
 * We separate A/B boot control metadata from the regular bootloader
 * message struct and keep it here. Everything that's A/B-specific
 * stays after struct bootloader_message, which should be managed by
 * the A/B-bootloader or boot control HAL.
 *
 * The slot_suffix field is used for A/B implementations where the
 * bootloader does not set the androidboot.ro.boot.slot_suffix kernel
 * commandline parameter. This is used by fs_mgr to mount /system and
 * other partitions with the slotselect flag set in fstab. A/B
 * implementations are free to use all 32 bytes and may store private
 * data past the first NUL-byte in this field. It is encouraged, but
 * not mandatory, to use 'struct bootloader_control' described below.
 *
 * The update_channel field is used to store the Omaha update channel
 * if update_engine is compiled with Omaha support.
 */
struct bootloader_message_ab {
	struct bootloader_message message;
	char slot_suffix[32];
	char update_channel[128];

	// Round up the entire struct to 4096-byte.
	char reserved[1888];
};

#define BOOT_CTRL_MAGIC   0x42414342 /* Bootloader Control AB */
#define BOOT_CTRL_VERSION 1

typedef struct slot_metadata {
	// Slot priority with 15 meaning highest priority, 1 lowest
	// priority and 0 the slot is unbootable.
	uint8_t priority : 4;
	// Number of times left attempting to boot this slot.
	uint8_t tries_remaining : 3;
	// 1 if this slot has booted successfully, 0 otherwise.
	uint8_t successful_boot : 1;
	// 1 if this slot is corrupted from a dm-verity corruption, 0
	// otherwise.
	uint8_t verity_corrupted : 1;
	// Reserved for further use.
	uint8_t reserved : 7;
}slot_metadata;

enum UpdateState {
	None = 0,
	Initiated,
	Unverified,
	Merging,
	MergeNeedsReboot,
	MergeCompleted,
	MergeFailed,
	Cancelled
};

/* Bootloader Control AB
 *
 * This struct can be used to manage A/B metadata. It is designed to
 * be put in the 'slot_suffix' field of the 'bootloader_message'
 * structure described above. It is encouraged to use the
 * 'bootloader_control' structure to store the A/B metadata, but not
 * mandatory.
 */
typedef struct bootloader_control {
	// NUL terminated active slot suffix.
	char slot_suffix[4];
	// Bootloader Control AB magic number (see BOOT_CTRL_MAGIC).
	uint32_t magic;
	// Version of struct being used (see BOOT_CTRL_VERSION).
	uint8_t version;
	// Number of slots being managed.
	uint8_t nb_slot : 3;
	// Number of times left attempting to boot recovery.
	uint8_t recovery_tries_remaining : 3;
	// Status of any pending snapshot merge of dynamic partitions.
	uint8_t merge_status : 3;
	// Ensure 4-bytes alignment for slot_info field.
	u8 roll_flag;
	// Per-slot information.  Up to 4 slots.
	struct slot_metadata slot_info[4];
	// Reserved for further use.
	uint8_t merge_flag;
	uint8_t reserved1[7];
	// CRC32 of all 28 bytes preceding this field (little endian
	// format).
	uint32_t crc32_le;
}bootloader_control;

// Holds Virtual A/B merge status information. Current version is 1. New fields
// must be added to the end.
struct misc_virtual_ab_message {
	uint8_t version;
	uint32_t magic;
	uint8_t merge_status;  // IBootControl 1.1, MergeStatus enum.
	uint8_t source_slot;   // Slot number when merge_status was written.
	uint8_t reserved[57];
};

#define MISC_VIRTUAL_AB_MESSAGE_VERSION 2
#define MISC_VIRTUAL_AB_MAGIC_HEADER 0x56740AB0

unsigned int kDefaultBootAttempts = 4;

/* Magic for the A/B struct when serialized. */
#define AVB_AB_MAGIC "\0AB0"
#define AVB_AB_MAGIC_LEN 4

/* Versioning for the on-disk A/B metadata - keep in sync with avbtool. */
#define AVB_AB_MAJOR_VERSION 1
#define AVB_AB_MINOR_VERSION 0

/* Size of AvbABData struct. */
#define AVB_AB_DATA_SIZE 32

/* Maximum values for slot data */
#define AVB_AB_MAX_PRIORITY 15
#define AVB_AB_MAX_TRIES_REMAINING 4

/* Struct used for recording per-slot metadata.
 *
 * When serialized, data is stored in network byte-order.
 */
typedef struct AvbABSlotData {
  /* Slot priority. Valid values range from 0 to AVB_AB_MAX_PRIORITY,
   * both inclusive with 1 being the lowest and AVB_AB_MAX_PRIORITY
   * being the highest. The special value 0 is used to indicate the
   * slot is unbootable.
   */
	uint8_t priority;

  /* Number of times left attempting to boot this slot ranging from 0
   * to AVB_AB_MAX_TRIES_REMAINING.
   */
	uint8_t tries_remaining;

  /* Non-zero if this slot has booted successfully, 0 otherwise. */
	uint8_t successful_boot;

  /* Reserved for future use. */
	uint8_t reserved[1];
} AvbABSlotData;

/* Struct used for recording A/B metadata.
 *
 * When serialized, data is stored in network byte-order.
 */
typedef struct AvbABData {
	/* Magic number used for identification - see AVB_AB_MAGIC. */
	uint8_t magic[AVB_AB_MAGIC_LEN];

	/* Version of on-disk struct - see AVB_AB_{MAJOR,MINOR}_VERSION. */
	uint8_t version_major;
	uint8_t version_minor;

	/* Padding to ensure |slots| field start eight bytes in. */
	u8 roll_flag;
	u8 reserved1[1];

	/* Per-slot metadata. */
	AvbABSlotData slots[2];

	/* Reserved for future use. */
	uint8_t reserved2[12];

	/* CRC32 of all 28 bytes preceding this field. */
	uint32_t crc32;
}AvbABData;

bool boot_info_validate(bootloader_control* info)
{
	if (info->magic != BOOT_CTRL_MAGIC) {
		printf("Magic 0x%x is incorrect.\n", info->magic);
		return false;
	}
	return true;
}

bool boot_info_validate_normalAB(AvbABData* info)
{
	if (memcmp(info->magic, AVB_AB_MAGIC, AVB_AB_MAGIC_LEN) != 0) {
		printf("Magic %s is incorrect.\n", info->magic);
		return false;
	}
	if (info->version_major > AVB_AB_MAJOR_VERSION) {
		printf("No support for given major version.\n");
		return false;
	}
	return true;
}


void boot_info_reset(bootloader_control* boot_ctrl)
{
	int slot;

	memset(boot_ctrl, '\0', sizeof(bootloader_control));
	memcpy(boot_ctrl->slot_suffix, "_a", 2);
	boot_ctrl->magic = BOOT_CTRL_MAGIC;
	boot_ctrl->version = BOOT_CTRL_VERSION;
	boot_ctrl->nb_slot = 2;
	boot_ctrl->roll_flag = 0;
	boot_ctrl->merge_flag = -1;

	for (slot = 0; slot < 4; ++slot) {
		slot_metadata entry = {};

		if (slot < boot_ctrl->nb_slot) {
			entry.priority = 7;
			entry.tries_remaining = kDefaultBootAttempts;
			entry.successful_boot = 1;
		} else {
			entry.priority = 0;  // Unbootable
			entry.tries_remaining = 0;
			entry.successful_boot = 0;
		}

		boot_ctrl->slot_info[slot] = entry;
	}
	boot_ctrl->recovery_tries_remaining = 0;
}

void dump_boot_info(bootloader_control* boot_ctrl)
{
#if 0
	int slot;

	printf("boot_ctrl->slot_suffix = %s\n", boot_ctrl->slot_suffix);
	printf("boot_ctrl->magic = 0x%x\n", boot_ctrl->magic);
	printf("boot_ctrl->version = %d\n", boot_ctrl->version);
	printf("boot_ctrl->nb_slot = %d\n", boot_ctrl->nb_slot);
	for (slot = 0; slot < 4; ++slot) {
		printf("boot_ctrl->slot_info[%d].priority = %d\n", slot,
			boot_ctrl->slot_info[slot].priority);
		printf("boot_ctrl->slot_info[%d].tries_remaining = %d\n",
			slot, boot_ctrl->slot_info[slot].tries_remaining);
		printf("boot_ctrl->slot_info[%d].successful_boot = %d\n",
			slot, boot_ctrl->slot_info[slot].successful_boot);
	}
	printf("boot_ctrl->recovery_tries_remaining = %d\n",
		boot_ctrl->recovery_tries_remaining);
#endif
}

static bool slot_is_bootable(slot_metadata* slot) {
	return slot->tries_remaining != 0;
}

int get_active_slot(bootloader_control* info) {
	if (info->slot_info[0].priority > info->slot_info[1].priority) {
		return 0;
	} else if (info->slot_info[0].priority == info->slot_info[1].priority) {
		if (info->slot_info[0].successful_boot == 1)
			return 0;
		else
			return 1;
	} else {
		return 1;
	}
}

static bool slot_is_bootable_normalAB(AvbABSlotData* slot) {
	return slot->priority > 0 &&
		(slot->successful_boot || (slot->tries_remaining > 0));
}

int get_active_slot_normalAB(AvbABData* info) {
	if (info->slots[0].priority > info->slots[1].priority)
		return 0;
	else
		return 1;
}

static uint32_t vab_crc32(const u8 *buf, size_t size)
{
	static u32 crc_table[256];
	u32 ret = -1;
	u32 i, j, crc, mask;
	size_t l;

	// Compute the CRC-32 table only once.
	if (!crc_table[1]) {
		for (i = 0; i < 256; ++i) {
			crc = i;

			for (j = 0; j < 8; ++j) {
				mask = -(crc & 1);

				crc = (crc >> 1) ^ (0xEDB88320 & mask);
			}
			crc_table[i] = crc;
		}
	}

	for (l = 0; l < size; ++l)
		ret = (ret >> 8) ^ crc_table[(ret ^ buf[l]) & 0xFF];

	return ~ret;
}

int boot_info_set_active_slot(bootloader_control* bootctrl, int slot)
{
	int i;
	// Set every other slot with a lower priority than the new "active" slot.
	const unsigned int kActivePriority = 15;
	const unsigned int kActiveTries = 6;

	for (i = 0; i < bootctrl->nb_slot; ++i) {
		if (i != slot) {
			bootctrl->slot_info[i].priority -= 1;
			if (bootctrl->slot_info[i].priority >= kActivePriority)
				bootctrl->slot_info[i].priority = kActivePriority - 1;
		}
		printf("bootctrl->slot_info[%d].priority = %d\n", i,
			bootctrl->slot_info[i].priority);
	}

	// Note that setting a slot as active doesn't change the successful bit.
	// The successful bit will only be changed by setSlotAsUnbootable().
	bootctrl->slot_info[slot].priority = kActivePriority;
	bootctrl->slot_info[slot].tries_remaining = kActiveTries;

	printf("bootctrl->slot_info[%d].priority = %d\n", slot,
		bootctrl->slot_info[slot].priority);
	printf("bootctrl->slot_info[%d].tries_remaining = %d\n", slot,
		bootctrl->slot_info[slot].tries_remaining);

	// Setting the current slot as active is a way to revert the operation that
	// set *another* slot as active at the end of an updater. This is commonly
	// used to cancel the pending update. We should only reset the verity_corrpted
	// bit when attempting a new slot, otherwise the verity bit on the current
	// slot would be flip.
	if (slot != get_active_slot(bootctrl))
		bootctrl->slot_info[slot].verity_corrupted = 0;

	dump_boot_info(bootctrl);

	return 0;
}

int boot_info_open_partition(char *miscbuf)
{
	char *partition = "misc";

	printf("Start read %s partition datas!\n", partition);
	if (store_read_ops((unsigned char *)partition,
		(unsigned char *)miscbuf, 0, MISCBUF_SIZE) < 0) {
		printf("failed to store read %s.\n", partition);
		return -1;
	}
	return 0;
}

bool boot_info_load(bootloader_control *out_info, char *miscbuf)
{
	memcpy(out_info, miscbuf + AB_METADATA_MISC_PARTITION_OFFSET, sizeof(bootloader_control));
	dump_boot_info(out_info);
	return true;
}

bool boot_info_load_normalAB(AvbABData *out_info, char *miscbuf)
{
	memcpy(out_info, miscbuf + AB_METADATA_MISC_PARTITION_OFFSET, AVB_AB_DATA_SIZE);
	return true;
}


bool boot_info_save(bootloader_control *info, char *miscbuf)
{
	char *partition = "misc";

	printf("save boot-info\n");
	info->crc32_le = vab_crc32((const uint8_t *)info,
		sizeof(bootloader_control) - sizeof(uint32_t));

	memcpy(miscbuf + AB_METADATA_MISC_PARTITION_OFFSET, info, sizeof(bootloader_control));
	dump_boot_info(info);
	store_write_ops((unsigned char *)partition, (unsigned char *)miscbuf, 0, MISCBUF_SIZE);
	return true;
}

int write_bootloader(int copy, int dstindex)
{
	int ret = -1;
	unsigned char *buffer = NULL;
	char str[128];
	u64 addr;
	u64 size = 0x2000 * 512 - 512;

	buffer = (unsigned char *)malloc(size);
	if (!buffer) {
		printf("ERROR! fail to allocate memory ...\n");
		goto exit;
	}
	memset(buffer, 0, size);
	addr = (unsigned long)buffer;

	if (copy == 0) {
		sprintf(str, "amlmmc switch 1 user");
		ret = run_command(str, 0);
	} else if (copy == 1) {
		sprintf(str, "amlmmc switch 1 boot0");
		ret = run_command(str, 0);
	} else if (copy == 2) {
		sprintf(str, "amlmmc switch 1 boot1");
		ret = run_command(str, 0);
	}
	if (ret != 0) {
		printf("amlmmc cmd %s failed\n", str);
		goto exit;
	}

	sprintf(str, "amlmmc read 1 0x%llx 0x1  0x%llx", addr, size / 512);
	printf("command: %s\n", str);
	ret = run_command(str, 0);
	if (ret != 0) {
		printf("amlmmc cmd %s failed\n", str);
		goto exit;
	}

	switch (dstindex) {
		case 0: {
			sprintf(str, "amlmmc switch 1 user");
			ret = run_command(str, 0);
			if (ret != 0) {
				printf("amlmmc cmd %s failed\n", str);
				goto exit;
			}
			sprintf(str, "amlmmc write 1 0x%llx 0x1 0x%llx", addr, size / 512);
			printf("command: %s\n", str);
			ret = run_command(str, 0);
			if (ret != 0) {
				printf("amlmmc cmd %s failed\n", str);
				goto exit;
			}
			break;
		}
		case 1: {
			sprintf(str, "amlmmc switch 1 boot0");
			ret = run_command(str, 0);
			if (ret != 0) {
				printf("amlmmc cmd %s failed\n", str);
				goto exit;
			}
			sprintf(str, "amlmmc write 1 0x%llx 0x1	0x%llx", addr, size / 512);
			printf("command: %s\n", str);
			ret = run_command(str, 0);
			if (ret != 0) {
				printf("amlmmc cmd %s failed\n", str);
				goto exit;
			}
			break;
		}
		case 2: {
			sprintf(str, "amlmmc switch 1 boot1");
			ret = run_command(str, 0);
			if (ret != 0) {
				printf("amlmmc cmd %s failed\n", str);
				goto exit;
			}
			sprintf(str, "amlmmc write 1 0x%llx 0x1	0x%llx", addr, size /  512);
			printf("command: %s\n", str);
			ret = run_command(str, 0);
			if (ret != 0) {
				printf("amlmmc cmd %s failed\n", str);
				goto exit;
			}
			break;
		}
		default: {
			goto exit;
			break;
		}
	}

	sprintf(str, "amlmmc switch 1 user");
	ret = run_command(str, 0);

exit:
	if (buffer) {
		free(buffer);
		buffer = NULL;
	}
	return ret;
}

static int write_bootloader_up(int i)
{
	unsigned char *buffer = NULL;
	int capacity_boot = 0x2000 * 512;
	int ret = 0;
	char partname[32] = {0};
	char *slot_name = NULL;
	int bootloader_index = 0;
	int size = BOOTLOADER_MAX_SIZE - BOOTLOADER_OFFSET;

#ifdef CONFIG_MMC_MESON_GX
	struct mmc *mmc = NULL;

	if (store_get_type() == BOOT_EMMC)
		mmc = find_mmc_device(1);

	if (mmc)
		capacity_boot = mmc->capacity_boot;
#endif

	printf("capacity_boot: 0x%x\n", capacity_boot);
	buffer = (unsigned char *)malloc(capacity_boot);
	if (!buffer) {
		printf("ERROR! fail to allocate memory ...\n");
		return -1;
	}
	memset(buffer, 0, capacity_boot);

	slot_name = getenv("active_slot");
	if (slot_name && (strcmp(slot_name, "_a") == 0))
		strcpy((char *)partname, "bootloader_a");
	else if (slot_name && (strcmp(slot_name, "_b") == 0))
		strcpy((char *)partname, "bootloader_b");
	else
		strcpy((char *)partname, "bootloader_up");

	ret = store_read_ops((unsigned char *)partname, buffer, 0, size);
	if (ret) {
		printf("Fail to read 0x%xB from part[%s] at offset 0\n",
					size, "bootloader_up");
		free(buffer);
		return -1;
	}

	if (i == 0)
		bootloader_index = AML_BL_BOOT0;
	else
		bootloader_index = AML_BL_BOOT1;

	ret = amlmmc_write_bootloader(1, bootloader_index, size, buffer);
	if (ret) {
		printf("Failed to write boot0\n");
		free(buffer);
		return -1;
	}

	free(buffer);
	return 0;
}

void bootloader_update_check(void)
{
	int ret = 0;
	char *writeboot = getenv("write_boot");

	if (writeboot && !strcmp(writeboot, "1")) {
		if (has_boot_slot == 0) {
			printf("non ab for kernel 5.15 update boot0 & boot1 from bootloader_up\n");
			ret = write_bootloader_up(0);
			ret += write_bootloader_up(1);
		} else {
			printf("ab for kernel 5.15 update boot0 from bootloader_a or _b\n");
			ret = write_bootloader_up(0);
		}
		if (ret != 0)
			run_command("reboot", 0);

		setenv("write_boot", "0");
		setenv("upgrade_step", "1");
		run_command("saveenv", 0);
		run_command("reboot", 0);
	}
}

static int is_f2fs_by_name(char *name)
{
	int ret = -1;
#ifdef CONFIG_AML_SD_EMMC
	struct partitions *partition = NULL;

	partition = find_mmc_partition_by_name(name);
	if (!partition)
		return ret;
	ret = (partition->mask_flags >> 12) & 0x1;
#endif

	return ret;
}

/**
 *get merge status
 */
int check_mergestatus(const char *filename)
{
	if (!filename)
		return -1;

#ifdef CONFIG_AML_SD_EMMC
	int part_no = -1;
	char cmd[256] = {0};

	part_no = get_partition_num_by_name("metadata");
	if (part_no < 0) {
		printf("fail find part index for metadata\n");
		return -1;
	}

	void *loadaddr = (void *)simple_strtoul("0x1080000", NULL, 16);

	sprintf(cmd, "ext4load mmc 1:0x%X 0x1080000 %s",
			part_no,
			filename);

	if (run_command(cmd, 0)) {
		printf("command[%s] failed\n", cmd);
		return -1;
	}

	char *pData = (char *)loadaddr;

	printf("merge_state: %d\n", pData[1]);

	if (pData[1] == Initiated || pData[1] == Unverified)
		return 1;
#endif
	return 0;
}

static void update_after_failed_rollback(void)
{
	run_command("run init_display; run storeargs; run update;", 0);
}

void rollback_failure_handler(void) __attribute__((weak, alias("update_after_failed_rollback")));

static int do_GetValidSlot(
	cmd_tbl_t *cmdtp,
	int flag,
	int argc,
	char * const argv[])
{
	char miscbuf[MISCBUF_SIZE] = {0};
	bootloader_control boot_ctrl;
	AvbABData info;
	int slot;
	int AB_mode = 0;
	bool bootable_a, bootable_b;
	char str_count[16];

	if (argc != 1)
		return cmd_usage(cmdtp);

	//recovery mode, need disable dolby
	run_command("get_rebootmode", 0);
	char *rebootmode = getenv("reboot_mode");

	if ((!strcmp(rebootmode, "factory_reset")) || (!strcmp(rebootmode, "update")))
		setenv("dolby_status", "0");

	boot_info_open_partition(miscbuf);
	boot_info_load(&boot_ctrl, miscbuf);

	if (!boot_info_validate(&boot_ctrl)) {
		printf("boot-info virtual ab is invalid. Try normal ab.\n");
		boot_info_load_normalAB(&info, miscbuf);
		if (!boot_info_validate_normalAB(&info)) {
			printf("boot-info is invalid. Resetting.\n");
			boot_info_reset(&boot_ctrl);
			boot_info_save(&boot_ctrl, miscbuf);
		} else {
			printf("update from normal ab to virtual ab\n");
			AB_mode = 1;
		}
	}

	//if recovery mode, need disable dolby
	if (!memcmp(miscbuf, "boot-recovery", strlen("boot-recovery"))) {
		printf("recovery mode, need disable dolby\n");
		setenv("dolby_status", "0");
	}

	if (AB_mode == 1) {
		slot = get_active_slot_normalAB(&info);
		bootable_a = slot_is_bootable_normalAB(&info.slots[0]);
		bootable_b = slot_is_bootable_normalAB(&info.slots[1]);
		if (has_boot_slot == 1) {
			sprintf(str_count, "%d", info.slots[0].tries_remaining);
			setenv("retry-count_a", str_count);
			sprintf(str_count, "%d", info.slots[1].tries_remaining);
			setenv("retry-count_b", str_count);
		}
		boot_info_reset(&boot_ctrl);
		boot_ctrl.slot_info[0].successful_boot = info.slots[0].successful_boot;
		boot_ctrl.slot_info[1].successful_boot = info.slots[1].successful_boot;
		boot_info_set_active_slot(&boot_ctrl, slot);
		boot_ctrl.roll_flag = info.roll_flag;
		boot_info_save(&boot_ctrl, miscbuf);
		slot = get_active_slot(&boot_ctrl);
	} else {
		slot = get_active_slot(&boot_ctrl);
		bootable_a = slot_is_bootable(&boot_ctrl.slot_info[0]);
		bootable_b = slot_is_bootable(&boot_ctrl.slot_info[1]);
		if (has_boot_slot == 1) {
			sprintf(str_count, "%d", boot_ctrl.slot_info[0].tries_remaining);
			setenv("retry-count_a", str_count);
			sprintf(str_count, "%d", boot_ctrl.slot_info[1].tries_remaining);
			setenv("retry-count_b", str_count);
		}
	}

	if (dynamic_partition)
		setenv("partition_mode", "dynamic");
	else
		setenv("partition_mode", "normal");

	if (vendor_boot_partition) {
		setenv("vendor_boot_mode", "true");
		printf("set vendor_boot_mode true\n");
	} else {
		setenv("vendor_boot_mode", "false");
		printf("set vendor_boot_mode false\n");
	}

	if (slot == 0) {
		if (bootable_a) {
			if (has_boot_slot == 1) {
				setenv("active_slot", "_a");
				setenv("boot_part", "boot_a");
				setenv("recovery_part", "recovery_a");
				setenv("slot-suffixes", "0");
			} else {
				setenv("active_slot", "normal");
				setenv("boot_part", "boot");
				setenv("recovery_part", "recovery");
				setenv("slot-suffixes", "-1");
			}
		} else if (bootable_b) {
#ifdef CONFIG_FASTBOOT
			struct misc_virtual_ab_message message;

			set_mergestatus_cancel(&message);
#endif
			boot_ctrl.roll_flag = 1;
			boot_info_save(&boot_ctrl, miscbuf);
			run_command("set_active_slot b", 0);
			setenv("default_env", "1");
			run_command("saveenv", 0);
#ifdef CONFIG_AML_GPT
			if (write_bootloader(2, 1) == 0)  {
#else
			if (write_bootloader(2, 0) == 0)  {
#endif
				printf("rollback ok\n");
				run_command("reset", 0);
			} else {
				printf("rollback failed\n");
				rollback_failure_handler();
			}
		} else {
			rollback_failure_handler();
		}
	}

	if (slot == 1) {
		if (bootable_b) {
			if (has_boot_slot == 1) {
				setenv("active_slot", "_b");
				setenv("boot_part", "boot_b");
				setenv("recovery_part", "recovery_b");
				setenv("slot-suffixes", "1");
			} else {
				setenv("active_slot", "normal");
				setenv("boot_part", "boot");
				setenv("recovery_part", "recovery");
				setenv("slot-suffixes", "-1");
			}
		} else if (bootable_a) {
#ifdef CONFIG_FASTBOOT
			struct misc_virtual_ab_message message;

			set_mergestatus_cancel(&message);
#endif
			boot_ctrl.roll_flag = 1;
			boot_info_save(&boot_ctrl, miscbuf);
			run_command("set_active_slot a", 0);
			setenv("default_env", "1");
			run_command("saveenv", 0);
#ifdef CONFIG_AML_GPT
			if (write_bootloader(2, 1) == 0)  {
#else
			if (write_bootloader(1, 0) == 0)  {
#endif
				printf("rollback ok\n");
				run_command("reset", 0);
			} else {
				printf("rollback failed\n");
				rollback_failure_handler();
			}
		} else {
			rollback_failure_handler();
		}
	}

	if (rebootmode && (strcmp(rebootmode, "rescueparty") == 0)) {
		printf("rebootmode is rescueparty, need rollback\n");

#ifdef CONFIG_FASTBOOT
		struct misc_virtual_ab_message message;

		set_mergestatus_cancel(&message);
#endif
		if (slot == 0) {
			boot_ctrl.roll_flag = 1;
			boot_info_save(&boot_ctrl, miscbuf);
			run_command("set_active_slot b", 0);
			setenv("default_env", "1");
			run_command("saveenv", 0);
#ifdef CONFIG_AML_GPT
			if (write_bootloader(2, 1) == 0)  {
#else
			if (write_bootloader(2, 0) == 0)  {
#endif
				printf("rollback ok\n");
				run_command("reset", 0);
			} else {
				printf("rollback failed\n");
				rollback_failure_handler();
			}
		} else if (slot == 1) {
			boot_ctrl.roll_flag = 1;
			boot_info_save(&boot_ctrl, miscbuf);
			run_command("set_active_slot a", 0);
			setenv("default_env", "1");
			run_command("saveenv", 0);
#ifdef CONFIG_AML_GPT
			if (write_bootloader(2, 1) == 0)  {
#else
			if (write_bootloader(1, 0) == 0)  {
#endif
				printf("rollback ok\n");
				run_command("reset", 0);
			} else {
				printf("rollback failed\n");
				rollback_failure_handler();
			}
		}
	}

	bootloader_update_check();
	return 0;
}

static int do_SetActiveSlot(
	cmd_tbl_t *cmdtp,
	int flag,
	int argc,
	char * const argv[])
{
	char miscbuf[MISCBUF_SIZE] = {0};
	bootloader_control info;

	if (argc != 2)
		return cmd_usage(cmdtp);

	if (has_boot_slot == 0) {
		printf("device is not ab mode\n");
		return -1;
	}

	boot_info_open_partition(miscbuf);
	boot_info_load(&info, miscbuf);

	if (!boot_info_validate(&info)) {
		printf("boot-info is invalid. Resetting.\n");
		boot_info_reset(&info);
		boot_info_save(&info, miscbuf);
	}

	if (strcmp(argv[1], "a") == 0) {
		setenv("active_slot", "_a");
		setenv("slot-suffixes", "0");
		setenv("boot_part", "boot_a");
		setenv("recovery_part", "recovery_a");
		printf("set active slot a\n");
		boot_info_set_active_slot(&info, 0);
	} else if (strcmp(argv[1], "b") == 0) {
		setenv("active_slot", "_b");
		setenv("slot-suffixes", "1");
		setenv("boot_part", "boot_b");
		setenv("recovery_part", "recovery_b");
		printf("set active slot b\n");
		boot_info_set_active_slot(&info, 1);
	} else {
		printf("error input slot\n");
		return -1;
	}

	boot_info_save(&info, miscbuf);

	printf("info.roll_flag = %d\n", info.roll_flag);

	if (info.roll_flag == 1) {
		printf("if null gpt, write dtb back when rollback\n");
		run_command("imgread dtb ${boot_part} ${dtb_mem_addr}", 0);
		run_command("emmc dtb_write ${dtb_mem_addr} 0", 0);
	}

	return 0;
}

static int do_SetRollFlag
(cmd_tbl_t *cmdtp,
	int flag,
	int argc,
	char * const argv[])
{
	char miscbuf[MISCBUF_SIZE] = {0};
	bootloader_control info;

	if (argc != 2)
		return cmd_usage(cmdtp);

	if (has_boot_slot == 0) {
		printf("device is not ab mode\n");
		return -1;
	}

	boot_info_open_partition(miscbuf);
	boot_info_load(&info, miscbuf);

	if (!boot_info_validate(&info)) {
		printf("boot-info is invalid. Resetting.\n");
		return 0;
	}

	if (strcmp(argv[1], "1") == 0)
		info.roll_flag = 1;
	else
		info.roll_flag = 0;

	boot_info_save(&info, miscbuf);

	printf("set info.roll_flag = %d\n", info.roll_flag);

	return 0;
}

static int do_SetUpdateTries
(cmd_tbl_t *cmdtp,
	int flag,
	int argc,
	char * const argv[])
{
	char miscbuf[MISCBUF_SIZE] = {0};
	bootloader_control boot_ctrl;
	bool bootable_a, bootable_b;
	int slot;
	int update_flag = 0;
	int merge_ret = -1;
	char *rebootmode = getenv("reboot_mode");

	if (has_boot_slot == 0) {
		printf("device is not ab mode\n");
		return -1;
	}

	boot_info_open_partition(miscbuf);
	boot_info_load(&boot_ctrl, miscbuf);

	//unsupport update dt in boothal, update dt in uboot
	run_command("update_dt;", 0);

	if (!boot_info_validate(&boot_ctrl)) {
		printf("boot-info is invalid. Resetting\n");
		boot_info_reset(&boot_ctrl);
		boot_info_save(&boot_ctrl, miscbuf);
	}

	slot = get_active_slot(&boot_ctrl);
	bootable_a = slot_is_bootable(&boot_ctrl.slot_info[0]);
	bootable_b = slot_is_bootable(&boot_ctrl.slot_info[1]);

	if (slot == 0) {
		if (bootable_a) {
			if (boot_ctrl.slot_info[0].successful_boot == 0) {
				boot_ctrl.slot_info[0].tries_remaining -= 1;
				update_flag = 1;
			}
		}
	}

	if (slot == 1) {
		if (bootable_b) {
			if (boot_ctrl.slot_info[1].successful_boot == 0) {
				boot_ctrl.slot_info[1].tries_remaining -= 1;
				update_flag = 1;
			}
		}
	}

	printf("boot_ctrl.merge_flag = %d\n", boot_ctrl.merge_flag);

	if (update_flag == 1)
		boot_info_save(&boot_ctrl, miscbuf);

	if (boot_ctrl.merge_flag < 1) {
		printf("can't get merge_flag from bootctrl\n");
		printf("try to read it from metadata\n");
		if (is_f2fs_by_name("metadata") == 0) {
			printf("metadata is ext4\n");
			merge_ret = check_mergestatus(MERGE_STATE_FILE);
		}
	} else if (boot_ctrl.merge_flag == Initiated ||
		boot_ctrl.merge_flag == Unverified) {
		printf("merge_flag is Initiated or Unverified\n");
		merge_ret = 1;
	}

	if (rebootmode && (!strcmp(rebootmode, "fastboot")) &&
		update_flag == 1 &&
		merge_ret == 1) {
		printf("reboot bootloader during merge, rollback\n");
		if (slot == 0 && bootable_a) {
			if (boot_ctrl.slot_info[0].successful_boot == 0)
				boot_ctrl.slot_info[0].tries_remaining = 0;
		} else if (slot == 1 && bootable_b) {
			if (boot_ctrl.slot_info[1].successful_boot == 0)
				boot_ctrl.slot_info[1].tries_remaining = 0;
		}
		boot_info_save(&boot_ctrl, miscbuf);
		run_command("reboot", 0);
	}

	printf("%s boot_ctrl.roll_flag = %d\n", __func__, boot_ctrl.roll_flag);
	if (boot_ctrl.roll_flag == 1)
		setenv("rollback_flag", "1");

	return 0;
}

static int do_Get_slot_state(
	cmd_tbl_t *cmdtp,
	int flag,
	int argc,
	char * const argv[])
{
	char miscbuf[MISCBUF_SIZE] = {0};
	bootloader_control info;

	if (argc != 3)
		return cmd_usage(cmdtp);

	if (has_boot_slot == 0) {
		printf("device is not ab mode\n");
		return -1;
	}

	boot_info_open_partition(miscbuf);
	boot_info_load(&info, miscbuf);

	if (!boot_info_validate(&info)) {
		printf("boot-info is invalid. Resetting.\n");
		boot_info_reset(&info);
		boot_info_save(&info, miscbuf);
	}

	if (strcmp(argv[2], "suc_stete") == 0) {
		if (strcmp(argv[1], "a") == 0) {
			if (info.slot_info[0].successful_boot == 1)
				return 1;
			else
				return 0;
		}
		if (strcmp(argv[1], "b") == 0) {
			if (info.slot_info[1].successful_boot == 1)
				return 1;
			else
				return 0;
		}
	}

	if (strcmp(argv[2], "boot_state") == 0) {
		if (strcmp(argv[1], "a") == 0) {
			if (slot_is_bootable(&info.slot_info[0]))
				return 1;
			else
				return 0;
		}
		if (strcmp(argv[1], "b") == 0) {
			if (slot_is_bootable(&info.slot_info[1]))
				return 1;
			else
				return 0;
		}
	}

	return -1;
}

int do_GetSystemMode (cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
#ifdef CONFIG_SYSTEM_AS_ROOT
	setenv("system_mode", "1");
#else
	setenv("system_mode", "0");
#endif

	return 0;
}

int do_GetAvbMode (cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
#ifdef CONFIG_AVB2
	setenv("avb2", "1");
#else
	setenv("avb2", "0");
#endif

	return 0;
}

int do_UpdateDt(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	char *update_dt = getenv("update_dt");
	char *part_changed = getenv("part_changed");

	printf("update_dt %s, part_changed: %s\n", update_dt, part_changed);
	if (update_dt && (!strcmp(update_dt, "1"))) {
		printf("write dtb\n");
		run_command("imgread dtb ${boot_part} ${dtb_mem_addr}", 0);
		run_command("emmc dtb_write ${dtb_mem_addr} 0", 0);

		setenv("update_dt", "0");
		run_command("saveenv", 0);

		if (part_changed && (!strcmp(part_changed, "1"))) {
			setenv("part_changed", "0");
			run_command("saveenv", 0);

			run_command("reset", 0);
		}
	}
	return 0;
}

#endif /* CONFIG_BOOTLOADER_CONTROL_BLOCK */

U_BOOT_CMD(
get_valid_slot, 2, 0, do_GetValidSlot,
"get_valid_slot",
"\nThis command will choose valid slot to boot up which saved in misc\n"
"partition by mark to decide whether execute command!\n"
"So you can execute command: get_valid_slot"
);

U_BOOT_CMD(
set_active_slot, 2, 1, do_SetActiveSlot,
"set_active_slot",
"\nThis command will set active slot\n"
"So you can execute command: set_active_slot a"
);

U_BOOT_CMD
(set_roll_flag, 2, 1, do_SetRollFlag,
	"set_roll_flag",
	"\nThis command will set active slot\n"
	"So you can execute command: set_active_slot a"
);

U_BOOT_CMD
(update_tries, 2, 0, do_SetUpdateTries,
	"update_tries",
	"\nThis command will change tries_remaining in misc\n"
	"So you can execute command: update_tries"
);

U_BOOT_CMD(
get_slot_state, 3, 2, do_Get_slot_state,
"get_slot_state a suc_stete",
"\nThis command will get slot state\n"
"you can run: get_slot_state a suc_stete/boot_state"
);


U_BOOT_CMD(
get_system_as_root_mode, 1,	0, do_GetSystemMode,
"get_system_as_root_mode",
"\nThis command will get system_as_root_mode\n"
"So you can execute command: get_system_as_root_mode"
);

U_BOOT_CMD(
get_avb_mode, 1,	0, do_GetAvbMode,
"get_avb_mode",
"\nThis command will get avb mode\n"
"So you can execute command: get_avb_mode"
);

U_BOOT_CMD
(update_dt, 1,	0, do_UpdateDt,
	"update_dt",
	"\nThis command will update dt\n"
	"So you can execute command: update_dt"
);

