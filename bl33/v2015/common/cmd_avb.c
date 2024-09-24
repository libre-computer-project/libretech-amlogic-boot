/*
* Copyright (C) 2017 Amlogic, Inc. All rights reserved.
* *
This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* (at your option) any later version.
* *
This program is distributed in the hope that it will be useful, but WITHOUT
* ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
* FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
* more details.
* *
You should have received a copy of the GNU General Public License along
* with this program; if not, write to the Free Software Foundation, Inc.,
* 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
* *
Description:
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
#include <emmc_partitions.h>
#include <amlogic/storage_if.h>
#include <asm/arch/bl31_apis.h>
#ifdef CONFIG_AML_ANTIROLLBACK
#include <anti-rollback.h>
#endif
#include <amlogic/aml_efuse.h>

#define AVB_USE_TESTKEY
#define MAX_DTB_SIZE (AML_DTB_IMG_MAX_SZ + 512)
#define DTB_PARTITION_SIZE 258048
#define AVB_NUM_SLOT (4)
#define MAX_AVBKEY_LEN (8 + 1024)

// The last slot is reserved for recovery partition
#define RECOVERY_ARB_LOCATION (31)
#define CONFIG_AVB2_KPUB_EMBEDDED

#ifdef CONFIG_AVB2_KPUB_VENDOR
extern const char avb2_kpub_vendor[];
extern const int avb2_kpub_vendor_len;
#endif /* CONFIG_AVB_KPUB_VENDOR */

extern const char avb2_kpub_default[];
extern const int avb2_kpub_default_len;
extern const char avb2_kpub_production[];
extern const int avb2_kpub_production_len;

void *memory_addr;
AvbOps avb_ops_;
int run_in_recovery;

static AvbIOResult read_from_partition(AvbOps* ops, const char* partition, int64_t offset,
		size_t num_bytes, void *buffer, size_t *out_num_read)
{
	uint64_t rc = 0;
	uint64_t part_bytes = 0;

	if (ops->get_size_of_partition(ops, partition, &part_bytes) != AVB_IO_RESULT_OK)
		return AVB_IO_RESULT_ERROR_NO_SUCH_PARTITION;

	if (part_bytes < offset)
		return AVB_IO_RESULT_ERROR_RANGE_OUTSIDE_PARTITION;

	*out_num_read = 0;
	if (!memcmp(partition, "dt", strlen("dt"))) {
		char *dtb_buf = malloc(MAX_DTB_SIZE);

		if (!dtb_buf)
			return AVB_IO_RESULT_ERROR_OOM;

		memset(dtb_buf, 0x00, MAX_DTB_SIZE);
		rc = store_dtb_rw(dtb_buf, MAX_DTB_SIZE, 2);
		if (rc) {
			printf("Failed to read dtb\n");
			free(dtb_buf);
			return AVB_IO_RESULT_ERROR_IO;
		}
		*out_num_read = num_bytes > MAX_DTB_SIZE ? MAX_DTB_SIZE : num_bytes;
		memcpy(buffer, dtb_buf, *out_num_read);
		free(dtb_buf);
		return AVB_IO_RESULT_OK;
	} else if (!strcmp(partition, "recovery-memory")) {
		char *filesize_str = getenv("filesize");
		uint32_t filesize = 0;

		if (filesize_str) {
			/* There is no risk in using the value to index _ctype through isxdigit
			 * because _ctype is an array of 256 elements
			 * and every value would fall into a posisition of _ctype.
			 */
			/* coverity[tainted_data] */
			filesize = simple_strtoul(filesize_str, NULL, 16);
		} else {
			return AVB_IO_RESULT_ERROR_IO;
		}

		if (memory_addr) {
			num_bytes = (filesize - offset >= num_bytes) ? num_bytes :
				(filesize - offset);
			memcpy(buffer, (uint8_t *)(memory_addr + offset), num_bytes);
			*out_num_read = num_bytes;
			return AVB_IO_RESULT_OK;
		}
		return AVB_IO_RESULT_ERROR_IO;
	}
	rc = store_read_ops((unsigned char *)partition, buffer, offset, num_bytes);
	if (rc) {
		printf("Failed to read %zdB from part[%s] at offset %lld\n",
			num_bytes, partition, offset);
		return AVB_IO_RESULT_ERROR_IO;
	}
	*out_num_read = num_bytes;

	return AVB_IO_RESULT_OK;
}

static AvbIOResult write_to_partition(AvbOps* ops, const char* partition,
		int64_t offset, size_t num_bytes, const void *buffer)
{
	uint64_t rc = 0;
	uint64_t part_bytes = 0;

	if (ops->get_size_of_partition(ops, partition, &part_bytes) != AVB_IO_RESULT_OK)
		return AVB_IO_RESULT_ERROR_NO_SUCH_PARTITION;

	if (part_bytes < offset)
		return AVB_IO_RESULT_ERROR_RANGE_OUTSIDE_PARTITION;

	if (!memcmp(partition, "dt", strlen("dt"))) {
		if (offset)
			return AVB_IO_RESULT_ERROR_IO;
		rc = store_dtb_rw((void *)buffer, num_bytes, 1);
		if (rc) {
			printf("Failed to write dtb\n");
			return AVB_IO_RESULT_ERROR_IO;
		} else {
			return AVB_IO_RESULT_OK;
		}
	} else {
		rc = store_write_ops((unsigned char *)partition, (unsigned char *)buffer,
			offset, num_bytes);
		if (rc) {
			printf("Failed to write %zdB from part[%s] at offset %lld\n",
				num_bytes, partition, offset);
			return AVB_IO_RESULT_ERROR_IO;
		}
	}

	return AVB_IO_RESULT_OK;
}

static AvbIOResult get_unique_guid_for_partition(AvbOps* ops, const char* partition,
		char *guid_buf, size_t guid_buf_size)
{
	char *s1;
	int ret;
	char part_name[128];

	memset(guid_buf, 0, guid_buf_size);
	s1 = getenv("active_slot");
	if (!s1) {
		run_command("get_valid_slot;", 0);
		s1 = getenv("active_slot");
	}
	//printf("active_slot is %s\n", s1);
	if (!memcmp(partition, "system", strlen("system"))) {
		if (s1 && (strcmp(s1, "_a") == 0))
			ret = get_partition_num_by_name("system_a");
		else if (s1 && (strcmp(s1, "_b") == 0))
			ret = get_partition_num_by_name("system_b");
		else
			ret = get_partition_num_by_name("system");

		if (ret >= 0) {
			sprintf(part_name, "/dev/mmcblk0p%d", ret + 1);
			strncpy(guid_buf, part_name, guid_buf_size);
		} else {
			printf("system part isn't exist\n");
			return AVB_IO_RESULT_ERROR_NO_SUCH_PARTITION;
		}
	} else if (!memcmp(partition, "vbmeta", strlen("vbmeta"))) {
		strncpy(guid_buf, "/dev/block/vbmeta", guid_buf_size);
	}
	return AVB_IO_RESULT_OK;
}

static AvbIOResult get_size_of_partition(AvbOps* ops, const char* partition,
		uint64_t *out_size_num_bytes)
{
	int rc = 0;

	if (!memcmp(partition, "dt", strlen("dt"))) {
		*out_size_num_bytes = DTB_PARTITION_SIZE;
	} else if (!strcmp(partition, "recovery-memory")) {
		char *filesize_str = getenv("filesize");
		uint32_t filesize = 0;

		if (filesize_str) {
			/* There is no risk in using the value to index _ctype
			 * because _ctype is an array of 256 elements
			 * and every value would fall into a posisition of _ctype.
			 */
			/* coverity[tainted_data] */
			filesize = simple_strtoul(filesize_str, NULL, 16);
		} else {
			return AVB_IO_RESULT_ERROR_IO;
		}

		*out_size_num_bytes = filesize;
	} else {
		rc = store_get_partition_size((unsigned char *)partition, out_size_num_bytes);
		if (rc) {
			printf("Failed to get partition[%s] size\n", partition);
			return AVB_IO_RESULT_ERROR_NO_SUCH_PARTITION;
		}
		*out_size_num_bytes *= 512;
	}

	return AVB_IO_RESULT_OK;
}

static AvbIOResult validate_vbmeta_public_key(AvbOps* ops, const uint8_t* public_key_data,
		size_t public_key_length, const uint8_t *public_key_metadata,
		size_t public_key_metadata_length,
		bool *out_is_trusted)
{
	*out_is_trusted = false;
	AvbIOResult ret = AVB_IO_RESULT_ERROR_IO;
	char *keybuf = NULL;
	char *partition = "misc";
	AvbKey_t key;
	uint64_t size = 0;
	int rc;
	int i = 0;

	if (!IS_FEAT_BOOT_VERIFY()) {
		key.size = 0;
		keybuf = (char *)malloc(AVB_CUSTOM_KEY_LEN_MAX);
		if (keybuf) {
			memset(keybuf, 0, AVB_CUSTOM_KEY_LEN_MAX);
			rc = store_get_partition_size((unsigned char *)partition, &size);
			if (rc == 0) {
				if (store_read_ops((unsigned char *)partition,
					(unsigned char *)keybuf, size - AVB_CUSTOM_KEY_LEN_MAX,
					AVB_CUSTOM_KEY_LEN_MAX) >= 0) {
					memcpy(&key, keybuf, sizeof(AvbKey_t));
				}
			}
		}

		if (keybuf && (strncmp(keybuf, "AVBK", 4) == 0)) {
			printf("AVB2 verify with avb_custom_key\n");
			if (key.size == public_key_length &&
				!avb_safe_memcmp(public_key_data, keybuf + sizeof(AvbKey_t),
				public_key_length)) {
				*out_is_trusted = true;
				ret = AVB_IO_RESULT_OK;
			}
			if (is_device_unlocked())
				ret = AVB_IO_RESULT_OK;
		} else {
			/**
			* When the custom key is set and the device is in the LOCKED state
			* it will boot images signed with both the built-in key as well as the custom key
			*/
			printf("AVB2 verify with default kpub size:%d, vbmeta kpub size:%ld\n",
				avb2_kpub_default_len, public_key_length);
			if (avb2_kpub_default_len == public_key_length &&
				!avb_safe_memcmp(public_key_data, avb2_kpub_default,
				public_key_length)) {
				*out_is_trusted = true;
				ret = AVB_IO_RESULT_OK;
			}
		}
	} else {
		printf("AVB2 verify with production kpub:%d, vbmeta kpub:%ld\n",
				avb2_kpub_production_len, public_key_length);
		if (avb2_kpub_production_len == public_key_length &&
				!avb_safe_memcmp(public_key_data,
					avb2_kpub_production, public_key_length)) {
			*out_is_trusted = true;
			ret = AVB_IO_RESULT_OK;
		}
		for (i = 0; i < avb2_kpub_production_len; i++) {
			if (avb2_kpub_production[i] != 0)
				break;
		}
		if (i == avb2_kpub_production_len)
			printf("ERROR: DID YOU FORGET TO CHANGE AVB2 KEY FOR SECURE BOOT?");
	}

	if (keybuf)
		free(keybuf);
	if (ret != AVB_IO_RESULT_OK)
		printf("AVB2 key in bootloader does not match with the key in vbmeta\n");
	return ret;
}

static AvbIOResult validate_public_key_for_partition(AvbOps *ops,
	const char *partition,
	const uint8_t *public_key_data,
	size_t public_key_length,
	const uint8_t *public_key_metadata,
	size_t public_key_metadata_length,
	bool *out_is_trusted,
	uint32_t *out_rollback_index_location
)
{
	AvbIOResult ret = AVB_IO_RESULT_ERROR_IO;

	if (!ops || !partition || !public_key_data || !out_is_trusted ||
			!out_rollback_index_location)
		return AVB_IO_RESULT_ERROR_INSUFFICIENT_SPACE;

	*out_is_trusted = false;

	if (!strcmp(partition, "recovery") ||
			!strcmp(partition, "recovery-memory")) {
		printf("checking for recovery partition\n");
		ret = validate_vbmeta_public_key(ops, public_key_data,
				public_key_length, public_key_metadata,
				public_key_metadata_length,
				out_is_trusted);
		*out_rollback_index_location = RECOVERY_ARB_LOCATION;
	} else {
		*out_rollback_index_location = 0;
		return AVB_IO_RESULT_ERROR_NO_SUCH_PARTITION;
	}

	return ret;
}

static AvbIOResult read_rollback_index(AvbOps* ops, size_t rollback_index_location,
		uint64_t *out_rollback_index)
{
#ifdef CONFIG_AML_ANTIROLLBACK
	uint32_t version;

	if (get_avb_antirollback(rollback_index_location, &version)) {
		*out_rollback_index = version;
	} else {
		printf("failed to read rollback index: %zd\n", rollback_index_location);
		return AVB_IO_RESULT_ERROR_NO_SUCH_VALUE;
	}
#else
	*out_rollback_index = 0;
#endif
	return AVB_IO_RESULT_OK;
}

static AvbIOResult write_rollback_index(AvbOps* ops, size_t rollback_index_location,
		uint64_t rollback_index)
{
#ifdef CONFIG_AML_ANTIROLLBACK
	uint32_t version = rollback_index;

	if (set_avb_antirollback(rollback_index_location, version))
		return AVB_IO_RESULT_OK;

	printf("failed to set rollback index: %zd, version: %u\n",
		rollback_index_location, version);
	return AVB_IO_RESULT_ERROR_NO_SUCH_VALUE;
#endif
	return AVB_IO_RESULT_OK;
}

static AvbIOResult read_is_device_unlocked(AvbOps* ops, bool* out_is_unlocked)
{
#ifdef CONFIG_AML_ANTIROLLBACK
	uint32_t lock_state;
	char *lock_s;

	if (get_avb_lock_state(&lock_state)) {
		*out_is_unlocked = !lock_state;
		lock_s = getenv("lock");
		if (*out_is_unlocked)
			lock_s[4] = '0';
		else
			lock_s[4] = '1';
		setenv("lock", lock_s);
		return AVB_IO_RESULT_OK;
	}
	printf("failed to read device lock status from rpmb\n");
	return AVB_IO_RESULT_ERROR_IO;
#else
	char *lock_s;
	LockData_t info;

	lock_s = getenv("lock");
	if (!lock_s)
		return AVB_IO_RESULT_ERROR_IO;

	memset(&info, 0, sizeof(struct LockData));

	info.version_major = (int)(lock_s[0] - '0');
	info.version_minor = (int)(lock_s[1] - '0');
	info.lock_state = (int)(lock_s[4] - '0');
	info.lock_critical_state = (int)(lock_s[5] - '0');
	info.lock_bootloader = (int)(lock_s[6] - '0');

	if (info.lock_state == 1)
		*out_is_unlocked = false;
	else
		*out_is_unlocked = true;
	return AVB_IO_RESULT_OK;
#endif
}

uint32_t create_csrs(void)
{
	int part_num = get_partition_num_by_name("factory");
	char part_name[32] = {0};
	char cmd[64] = {0};
	uint8_t buf[1] = {0};

	if (part_num >= 0)
		strcpy(part_name, "factory");
	else
		strcpy(part_name, "rsv");

	sprintf(cmd, "fatmkdir %s 0x%X:0x%X %s", "mmc", 1,
		get_partition_num_by_name(part_name), "csrs");
	if (run_command(cmd, 0)) {
		printf("command[%s] failed\n", cmd);
		return AVB_IO_RESULT_ERROR_IO;
	}

	memset(cmd, 0, sizeof(cmd));

	sprintf(cmd, "fatwrite %s 0x%X:0x%X 0x%08X %s 0x%X", "mmc", 1,
			get_partition_num_by_name(part_name),
			(uint32_t)virt_to_phys((void *)buf), "csrs/csrs.json", 1);
	if (run_command(cmd, 0)) {
		printf("command[%s] failed\n", cmd);
		return AVB_IO_RESULT_ERROR_IO;
	}
	return AVB_IO_RESULT_OK;
}

static int avb_init(void)
{
	memset(&avb_ops_, 0, sizeof(AvbOps));
	avb_ops_.read_from_partition = read_from_partition;
	avb_ops_.get_preloaded_partition = NULL;
	avb_ops_.write_to_partition = write_to_partition;
	avb_ops_.validate_vbmeta_public_key = validate_vbmeta_public_key;
	avb_ops_.read_rollback_index = read_rollback_index;
	avb_ops_.write_rollback_index = write_rollback_index;
	avb_ops_.read_is_device_unlocked = read_is_device_unlocked;
	avb_ops_.get_unique_guid_for_partition = get_unique_guid_for_partition;
	avb_ops_.get_size_of_partition = get_size_of_partition;
	avb_ops_.read_persistent_value = NULL;
	avb_ops_.write_persistent_value = NULL;
	avb_ops_.validate_public_key_for_partition = validate_public_key_for_partition;

	//avb_ops_.user_data = NULL;

	return 0;
}

int is_device_unlocked(void)
{
	AvbIOResult ret;
	bool out_is_unlocked;

	ret = read_is_device_unlocked(&avb_ops_, &out_is_unlocked);
	if (ret == AVB_IO_RESULT_OK)
		return out_is_unlocked;
	else
		return 0;
}

int avb_verify(AvbSlotVerifyData** out_data)
{
	/* The last slot must be NULL */
	const char *requested_partitions_ab[AVB_NUM_SLOT + 1] = {"boot", NULL, NULL, NULL, NULL};
	const char *requested_partitions[AVB_NUM_SLOT + 1] = {"boot", "dt", NULL, NULL, NULL};
	AvbSlotVerifyResult result = AVB_SLOT_VERIFY_RESULT_OK;
	char *s1 = NULL;
	char *ab_suffix = NULL;

	s1 = getenv("active_slot");
	if (!s1) {
		run_command("get_valid_slot;", 0);
		s1 = getenv("active_slot");
	}
	if (s1 != NULL) {
		printf("active_slot is %s\n", s1);
		if (strcmp(s1, "normal") == 0)
			ab_suffix = "";
		else
			ab_suffix = getenv("active_slot");
	}

	if (ab_suffix == NULL)
		ab_suffix = "";

	printf("ab_suffix is %s\n", ab_suffix);

	AvbSlotVerifyFlags flags = AVB_SLOT_VERIFY_FLAGS_NONE;

	avb_init();

	if (is_device_unlocked())
		flags |= AVB_SLOT_VERIFY_FLAGS_ALLOW_VERIFICATION_ERROR;

	if (!strcmp(ab_suffix, "")) {
		printf("recovery: %d\n", run_in_recovery);
		if (run_in_recovery) {
			flags |= AVB_SLOT_VERIFY_FLAGS_NO_VBMETA_PARTITION;
			memset(requested_partitions, 0, sizeof(requested_partitions));
			requested_partitions[0] = "recovery";
		}
		result = avb_slot_verify(&avb_ops_, requested_partitions, ab_suffix,
				flags,
				AVB_HASHTREE_ERROR_MODE_RESTART_AND_INVALIDATE, out_data);
	} else {
		result = avb_slot_verify(&avb_ops_, requested_partitions_ab, ab_suffix,
			flags,
			AVB_HASHTREE_ERROR_MODE_RESTART_AND_INVALIDATE, out_data);
	}

	run_in_recovery = 0;
	return result;
}

static int do_avb_verify(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	AvbSlotVerifyResult result = AVB_SLOT_VERIFY_RESULT_OK;
	AvbSlotVerifyData *out_data = NULL;
	uint32_t i = 0;

	result = (AvbSlotVerifyResult)avb_verify(&out_data);

	printf("result: %d\n", result);
	if ((result == AVB_SLOT_VERIFY_RESULT_OK) && (out_data != NULL)) {
#ifdef CONFIG_AML_ANTIROLLBACK
		uint32_t version;
		uint32_t lock_state;
#endif

		printf("ab_suffix: %s\n", out_data->ab_suffix);
		printf("vbmeta: name: %s, size: %zd, result: %d\n",
				out_data->vbmeta_images->partition_name,
				out_data->vbmeta_images->vbmeta_size,
				out_data->vbmeta_images->verify_result);
		printf("num of vbmeta: %zd\n", out_data->num_vbmeta_images);
		printf("loaded name: %s, size: %zd, preload: %d\n",
			out_data->loaded_partitions->partition_name,
			out_data->loaded_partitions->data_size,
			out_data->loaded_partitions->preloaded);
		printf("num of loaded: %zd\n", out_data->num_loaded_partitions);
		printf("cmdline: %s\n", out_data->cmdline);
		for (i = 0; i < AVB_MAX_NUMBER_OF_ROLLBACK_INDEX_LOCATIONS; i++)
			printf("rollback(%d) = %llu\n", i, out_data->rollback_indexes[i]);

#ifdef CONFIG_AML_ANTIROLLBACK
		for (i = 0; i < AVB_MAX_NUMBER_OF_ROLLBACK_INDEX_LOCATIONS; i++)
			if (get_avb_antirollback(i, &version))
				printf("rpmb rollback(%d) = %u\n", i, version);
		if (get_avb_lock_state(&lock_state))
			printf("rpmb lock state: %u\n", lock_state);
#endif

		avb_slot_verify_data_free(out_data);
	}

	return result;
}

static int do_avb_verify_memory(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	AvbSlotVerifyResult result = AVB_SLOT_VERIFY_RESULT_OK;
	AvbSlotVerifyData *out_data = NULL;
	const char *requested_partitions[2] = {NULL, NULL};
	char *avb_s = NULL;

	if (argc != 3)
		return 0;

	if (is_device_unlocked())
		return CMD_RET_SUCCESS;

	run_command("get_avb_mode;", 0);
	avb_s = getenv("avb2");
	if (!avb_s || !strcmp(avb_s, "0"))
		return CMD_RET_SUCCESS;

	if (!strcmp(argv[1], "recovery"))
		requested_partitions[0] = "recovery-memory";
	else
		return CMD_RET_FAILURE;

	memory_addr = (void *)simple_strtoul(argv[2], NULL, 16);

	AvbSlotVerifyFlags flags = AVB_SLOT_VERIFY_FLAGS_NO_VBMETA_PARTITION;

	avb_init();
	result = avb_slot_verify(&avb_ops_, requested_partitions, "",
			flags,
			AVB_HASHTREE_ERROR_MODE_RESTART_AND_INVALIDATE, &out_data);

	avb_slot_verify_data_free(out_data);

	if (result == AVB_SLOT_VERIFY_RESULT_OK)
		return CMD_RET_SUCCESS;
	else
		return CMD_RET_FAILURE;
}

static int do_avb_recovery(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	char *avb_s = NULL;

	run_in_recovery = 0;

	if (argc != 2)
		return CMD_RET_FAILURE;

	if (is_device_unlocked())
		return CMD_RET_SUCCESS;

	run_command("get_avb_mode;", 0);
	avb_s = getenv("avb2");
	if (!avb_s || !strcmp(avb_s, "0"))
		return CMD_RET_SUCCESS;

	if (!strcmp(argv[1], "1"))
		run_in_recovery = 1;
	else
		run_in_recovery = 0;

	return CMD_RET_SUCCESS;
}

uint32_t avb_get_boot_patchlevel_from_vbmeta(AvbSlotVerifyData *data)
{
	int i, j;
	AvbVBMetaData *p;
	const char *ret = NULL;
	size_t len = 0;
	char buff[9];
	unsigned long boot_patchlevel;

	if (!data)
		return 0;

	for (i = 0; i < data->num_vbmeta_images; i++) {
		p = &data->vbmeta_images[i];
		if (strcmp(p->partition_name, "vbmeta") == 0) { /* match */
			if (p->verify_result != AVB_VBMETA_VERIFY_RESULT_OK) {
				// not verified
				printf("vbmeta verify_result %d\n", p->verify_result);

				/*device lock, treat as error*/
				if (!is_device_unlocked()) {
					printf("device lock, but vbmeta verify fail\n");
					return 0;
				}
			}

			ret = avb_property_lookup(p->vbmeta_data,
				p->vbmeta_size,
				"com.android.build.boot.security_patch",
				0,
				&len);

			if (ret)
				break;
			}
		}

		if (ret) {
			for (i = 0, j = 0; i < len; i++) {
				if (ret[i] != '-' && j < 8)
					buff[j++] = ret[i];
			}
			buff[8] = '\0';
			if (!strict_strtoul(buff, 10, &boot_patchlevel))
				return (uint32_t)boot_patchlevel;
		}

		return 0;
}

static cmd_tbl_t cmd_avb_sub[] = {
	U_BOOT_CMD_MKENT(verify, 4, 0, do_avb_verify, "", ""),
	U_BOOT_CMD_MKENT(memory, 4, 0, do_avb_verify_memory, "", ""),
	U_BOOT_CMD_MKENT(recovery, 2, 0, do_avb_recovery, "", ""),
};

static int do_avb_ops(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	cmd_tbl_t *c;

	/* Strip off leading 'bmp' command argument */
	argc--;
	argv++;

	c = find_cmd_tbl(argv[0], &cmd_avb_sub[0], ARRAY_SIZE(cmd_avb_sub));

	if (c)
		return c->cmd(cmdtp, flag, argc, argv);

	cmd_usage(cmdtp);
	return CMD_RET_FAILURE;
}


U_BOOT_CMD(
		avb, 4, 0, do_avb_ops,
		"avb",
		"\nThis command will trigger related avb operations\n"
		);
