// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright 2014 Broadcom Corporation.
 */

#include <config.h>
#include <common.h>
#include <blk.h>
#include <fastboot.h>
#include <fastboot-internal.h>
#include <fb_mmc.h>
#include <image-sparse.h>
#include <part.h>
#include <mmc.h>
#include <div64.h>
#include <linux/compat.h>
#include <android_image.h>
#include <amlogic/aml_mmc.h>
#include <emmc_partitions.h>

#define FASTBOOT_MAX_BLK_WRITE 16384

#define BOOT_PARTITION_NAME "boot"

struct fb_mmc_sparse {
	struct blk_desc	*dev_desc;
};

static int part_get_info_by_name_or_alias(struct blk_desc *dev_desc,
		const char *name, disk_partition_t *info)
{
	int ret;

	ret = part_get_info_by_name(dev_desc, name, info);
	if (ret < 0) {
		/* strlen("fastboot_partition_alias_") + 32(part_name) + 1 */
		char env_alias_name[25 + 32 + 1];
		char *aliased_part_name;

		/* check for alias */
		strncpy(env_alias_name, "fastboot_partition_alias_", 26);
		strncat(env_alias_name, name, 32);
		aliased_part_name = env_get(env_alias_name);
		if (aliased_part_name != NULL)
			ret = part_get_info_by_name(dev_desc,
					aliased_part_name, info);
	}
	return ret;
}

/**
 * fb_mmc_blk_write() - Write/erase MMC in chunks of FASTBOOT_MAX_BLK_WRITE
 *
 * @block_dev: Pointer to block device
 * @start: First block to write/erase
 * @blkcnt: Count of blocks
 * @buffer: Pointer to data buffer for write or NULL for erase
 */
static lbaint_t fb_mmc_blk_write(struct blk_desc *block_dev, lbaint_t start,
				 lbaint_t blkcnt, const void *buffer)
{
	lbaint_t blk = start;
	lbaint_t blks_written;
	lbaint_t cur_blkcnt;
	lbaint_t blks = 0;
	int i;

	if (buffer) {
		for (i = 0; i < blkcnt; i += FASTBOOT_MAX_BLK_WRITE) {
			cur_blkcnt = min((int)blkcnt - i, FASTBOOT_MAX_BLK_WRITE);
			if (fastboot_progress_callback)
				fastboot_progress_callback("writing");
			blks_written = blk_dwrite(block_dev, blk, cur_blkcnt,
						  buffer + (i * block_dev->blksz));
			blk += blks_written;
			blks += blks_written;
		}
	} else {
		if (fastboot_progress_callback)
			fastboot_progress_callback("erasing");
		blks = blk_derase(block_dev, start, blkcnt);
	}

	return blks;
}

static lbaint_t fb_mmc_sparse_write(struct sparse_storage *info,
		lbaint_t blk, lbaint_t blkcnt, const void *buffer)
{
	struct fb_mmc_sparse *sparse = info->priv;
	struct blk_desc *dev_desc = sparse->dev_desc;

	return fb_mmc_blk_write(dev_desc, blk, blkcnt, buffer);
}

static lbaint_t fb_mmc_sparse_reserve(struct sparse_storage *info,
		lbaint_t blk, lbaint_t blkcnt)
{
	return blkcnt;
}

static void write_raw_image(struct blk_desc *dev_desc, disk_partition_t *info,
		const char *part_name, void *buffer,
		u32 download_bytes, char *response)
{
	lbaint_t blkcnt;
	lbaint_t blks;

	/* determine number of blocks to write */
	blkcnt = ((download_bytes + (info->blksz - 1)) & ~(info->blksz - 1));
	blkcnt = lldiv(blkcnt, info->blksz);

	if (blkcnt > info->size) {
		pr_err("too large for partition: '%s'\n", part_name);
		fastboot_fail("too large for partition", response);
		return;
	}

	puts("Flashing Raw Image\n");

	blks = fb_mmc_blk_write(dev_desc, info->start, blkcnt, buffer);

	if (blks != blkcnt) {
		pr_err("failed writing to device %d\n", dev_desc->devnum);
		fastboot_fail("failed writing to device", response);
		return;
	}

	printf("........ wrote " LBAFU " bytes to '%s'\n", blkcnt * info->blksz,
	       part_name);
	fastboot_okay(NULL, response);
}

#ifdef CONFIG_ANDROID_BOOT_IMAGE
/**
 * Read Android boot image header from boot partition.
 *
 * @param[in] dev_desc MMC device descriptor
 * @param[in] info Boot partition info
 * @param[out] hdr Where to store read boot image header
 *
 * @return Boot image header sectors count or 0 on error
 */
static lbaint_t fb_mmc_get_boot_header(struct blk_desc *dev_desc,
				       disk_partition_t *info,
				       boot_img_hdr_t *hdr,
				       char *response)
{
	ulong sector_size;		/* boot partition sector size */
	lbaint_t hdr_sectors;		/* boot image header sectors count */
	int res;

	/* Calculate boot image sectors count */
	sector_size = info->blksz;
	hdr_sectors = DIV_ROUND_UP(sizeof(boot_img_hdr_t), sector_size);
	if (hdr_sectors == 0) {
		pr_err("invalid number of boot sectors: 0\n");
		fastboot_fail("invalid number of boot sectors: 0", response);
		return 0;
	}

	/* Read the boot image header */
	res = blk_dread(dev_desc, info->start, hdr_sectors, (void *)hdr);
	if (res != hdr_sectors) {
		pr_err("cannot read header from boot partition\n");
		fastboot_fail("cannot read header from boot partition",
			      response);
		return 0;
	}

	/* Check boot header magic string */
	res = android_image_check_header(hdr);
	if (res != 0) {
		pr_err("bad boot image magic\n");
		fastboot_fail("boot partition not initialized", response);
		return 0;
	}

	return hdr_sectors;
}

/**
 * Write downloaded zImage to boot partition and repack it properly.
 *
 * @param dev_desc MMC device descriptor
 * @param download_buffer Address to fastboot buffer with zImage in it
 * @param download_bytes Size of fastboot buffer, in bytes
 *
 * @return 0 on success or -1 on error
 */
static int fb_mmc_update_zimage(struct blk_desc *dev_desc,
				void *download_buffer,
				u32 download_bytes,
				char *response)
{
	uintptr_t hdr_addr;			/* boot image header address */
	boot_img_hdr_t *hdr;		/* boot image header */
	lbaint_t hdr_sectors;			/* boot image header sectors */
	u8 *ramdisk_buffer;
	u32 ramdisk_sector_start;
	u32 ramdisk_sectors;
	u32 kernel_sector_start;
	u32 kernel_sectors;
	u32 sectors_per_page;
	disk_partition_t info;
	int res;

	puts("Flashing zImage\n");

	/* Get boot partition info */
	res = part_get_info_by_name(dev_desc, BOOT_PARTITION_NAME, &info);
	if (res < 0) {
		pr_err("cannot find boot partition\n");
		fastboot_fail("cannot find boot partition", response);
		return -1;
	}

	/* Put boot image header in fastboot buffer after downloaded zImage */
	hdr_addr = (uintptr_t)download_buffer + ALIGN(download_bytes, PAGE_SIZE);
	hdr = (boot_img_hdr_t *)hdr_addr;

	/* Read boot image header */
	hdr_sectors = fb_mmc_get_boot_header(dev_desc, &info, hdr, response);
	if (hdr_sectors == 0) {
		pr_err("unable to read boot image header\n");
		fastboot_fail("unable to read boot image header", response);
		return -1;
	}

	/* Check if boot image has second stage in it (we don't support it) */
	if (hdr->second_size > 0) {
		pr_err("moving second stage is not supported yet\n");
		fastboot_fail("moving second stage is not supported yet",
			      response);
		return -1;
	}

	/* Extract ramdisk location */
	sectors_per_page = hdr->page_size / info.blksz;
	ramdisk_sector_start = info.start + sectors_per_page;
	ramdisk_sector_start += DIV_ROUND_UP(hdr->kernel_size, hdr->page_size) *
					     sectors_per_page;
	ramdisk_sectors = DIV_ROUND_UP(hdr->ramdisk_size, hdr->page_size) *
				       sectors_per_page;

	/* Read ramdisk and put it in fastboot buffer after boot image header */
	ramdisk_buffer = (u8 *)hdr + (hdr_sectors * info.blksz);
	res = blk_dread(dev_desc, ramdisk_sector_start, ramdisk_sectors,
			ramdisk_buffer);
	if (res != ramdisk_sectors) {
		pr_err("cannot read ramdisk from boot partition\n");
		fastboot_fail("cannot read ramdisk from boot partition",
			      response);
		return -1;
	}

	/* Write new kernel size to boot image header */
	hdr->kernel_size = download_bytes;
	res = blk_dwrite(dev_desc, info.start, hdr_sectors, (void *)hdr);
	if (res == 0) {
		pr_err("cannot writeback boot image header\n");
		fastboot_fail("cannot write back boot image header", response);
		return -1;
	}

	/* Write the new downloaded kernel */
	kernel_sector_start = info.start + sectors_per_page;
	kernel_sectors = DIV_ROUND_UP(hdr->kernel_size, hdr->page_size) *
				      sectors_per_page;
	res = blk_dwrite(dev_desc, kernel_sector_start, kernel_sectors,
			 download_buffer);
	if (res == 0) {
		pr_err("cannot write new kernel\n");
		fastboot_fail("cannot write new kernel", response);
		return -1;
	}

	/* Write the saved ramdisk back */
	ramdisk_sector_start = info.start + sectors_per_page;
	ramdisk_sector_start += DIV_ROUND_UP(hdr->kernel_size, hdr->page_size) *
					     sectors_per_page;
	res = blk_dwrite(dev_desc, ramdisk_sector_start, ramdisk_sectors,
			 ramdisk_buffer);
	if (res == 0) {
		pr_err("cannot write back original ramdisk\n");
		fastboot_fail("cannot write back original ramdisk", response);
		return -1;
	}

	puts("........ zImage was updated in boot partition\n");
	fastboot_okay(NULL, response);
	return 0;
}
#endif

/**
 * fastboot_mmc_get_part_info() - Lookup eMMC partion by name
 *
 * @part_name: Named partition to lookup
 * @dev_desc: Pointer to returned blk_desc pointer
 * @part_info: Pointer to returned disk_partition_t
 * @response: Pointer to fastboot response buffer
 */
int fastboot_mmc_get_part_info(char *part_name, struct blk_desc **dev_desc,
			       disk_partition_t *part_info, char *response)
{
	int r;

	*dev_desc = blk_get_dev("mmc", CONFIG_FASTBOOT_FLASH_MMC_DEV);
	if (!*dev_desc) {
		fastboot_fail("block device not found", response);
		return -ENOENT;
	}
	if (!part_name) {
		fastboot_fail("partition not found", response);
		return -ENOENT;
	}

	r = part_get_info_by_name_or_alias(*dev_desc, part_name, part_info);
	if (r < 0) {
		fastboot_fail("partition not found", response);
		return r;
	}

	return r;
}

/* erase or flash, when buffer is not NULL, it's write */
static void fb_mmc_bootloader_ops(const char *cmd,
				  struct blk_desc *dev_desc,
				  void *buffer, unsigned int bytes,
				  char *response)
{
	char *delim = "-";
	char *hwpart;
	int map = 0, ret = 0;
	char *scmd = (char *) cmd;
	char *ops[] = {"erase", "write"};

	hwpart = strchr(scmd, (int)*delim);

	if (!hwpart) {
		map = AML_BL_USER;
	} else if (!strcmp(hwpart, "-boot0")) {
		map = AML_BL_BOOT0;
	} else if (!strcmp(hwpart, "-boot1")) {
		map = AML_BL_BOOT1;
	}
	if (map) {
		if (buffer)
			ret = amlmmc_write_bootloader(CONFIG_FASTBOOT_FLASH_MMC_DEV, map,
						      bytes, buffer);
		else
			ret = amlmmc_erase_bootloader(CONFIG_FASTBOOT_FLASH_MMC_DEV, map);
		if (ret) {
			printf("failed %s %s from device %d", (buffer? ops[1]: ops[0]),
				cmd, dev_desc->devnum);
			fastboot_fail("failed bootloader operating to device", response);
			return;
		}
		printf("........ %s  %s\n", (buffer? ops[1]: ops[0]), cmd);
		fastboot_okay("", response);
	} else
		fastboot_fail("failed operating from device", response);
	return;
}

/**
 * write bootloader on user/boot0/boot1
 * according to bootloader name.
 */
static void fb_mmc_write_bootloader(const char *cmd,
				    struct blk_desc *dev_desc,
				    void *buffer, unsigned int bytes,
				    char *response)
{
	return fb_mmc_bootloader_ops(cmd, dev_desc, buffer, bytes, response);
}

/**
 * erase bootloader on user/boot0/boot1
 * according to bootloader name.
 */
static void fb_mmc_erase_bootloader(const char *cmd, struct blk_desc *dev_desc,
				    char *response)
{
	return fb_mmc_bootloader_ops(cmd, dev_desc, NULL, 0, response);
}

/**
 * fastboot_mmc_flash_write() - Write image to eMMC for fastboot
 *
 * @cmd: Named partition to write image to
 * @download_buffer: Pointer to image data
 * @download_bytes: Size of image data
 * @response: Pointer to fastboot response buffer
 */
void fastboot_mmc_flash_write(const char *cmd, void *download_buffer,
			      u32 download_bytes, char *response)
{
	struct blk_desc *dev_desc;
#ifndef DTB_BIND_KERNEL
	int ret = 0;
#endif
	disk_partition_t info;
	struct mmc *mmc = find_mmc_device(CONFIG_FASTBOOT_FLASH_MMC_DEV);

	if (mmc == NULL) {
		pr_err("invalid mmc device\n");
		fastboot_fail("invalid mmc device", response);
		return;
	}

	dev_desc = blk_get_dev("mmc", CONFIG_FASTBOOT_FLASH_MMC_DEV);
	if (!dev_desc || dev_desc->type == DEV_TYPE_UNKNOWN) {
		pr_err("invalid mmc device\n");
		fastboot_fail("invalid mmc device", response);
		return;
	}

#if CONFIG_IS_ENABLED(EFI_PARTITION)
	if (strcmp(cmd, CONFIG_FASTBOOT_GPT_NAME) == 0) {
		printf("%s: updating MBR, Primary and Backup GPT(s)\n",
		       __func__);
		if (is_valid_gpt_buf(dev_desc, download_buffer)) {
			printf("%s: invalid GPT - refusing to write to flash\n",
			       __func__);
			fastboot_fail("invalid GPT partition", response);
			return;
		}
		if (write_mbr_and_gpt_partitions(dev_desc, download_buffer)) {
			printf("%s: writing GPT partitions failed\n", __func__);
			fastboot_fail("writing GPT partitions failed",
				      response);
			return;
		}
		printf("........ success\n");
		fastboot_okay(NULL, response);
		return;
	}
#endif

#if CONFIG_IS_ENABLED(DOS_PARTITION)
	if (strcmp(cmd, CONFIG_FASTBOOT_MBR_NAME) == 0) {
		printf("%s: updating MBR\n", __func__);
		if (is_valid_dos_buf(download_buffer)) {
			printf("%s: invalid MBR - refusing to write to flash\n",
			       __func__);
			fastboot_fail("invalid MBR partition", response);
			return;
		}
		if (write_mbr_partition(dev_desc, download_buffer)) {
			printf("%s: writing MBR partition failed\n", __func__);
			fastboot_fail("writing MBR partition failed",
				      response);
			return;
		}
		if (mmc_device_init(mmc) != 0) {
			printf(" update gpt partition table fail\n");
			fastboot_fail("fastboot update gpt partition fail", response);
			return;
		}
		printf("........ success\n");
		fastboot_okay(NULL, response);
		return;
	}
#endif

#ifdef CONFIG_ANDROID_BOOT_IMAGE
	if (strncasecmp(cmd, "zimage", 6) == 0) {
		fb_mmc_update_zimage(dev_desc, download_buffer,
				     download_bytes, response);
		return;
	}
#endif

	if (strcmp(cmd, "dtb") == 0) {
#ifndef DTB_BIND_KERNEL
		if (gpt_partition)
			erase_gpt_part_table(dev_desc);
		ret = dtb_write(download_buffer);
		if (ret)
			fastboot_fail("fastboot write dtb fail", response);
		else {
			if (!gpt_partition) {
				/* renew partition table @ once*/
				printf("renew partition table\n");
				if (renew_partition_tbl(download_buffer))
					fastboot_fail("fastboot write dtb fail", response);
			}
			fastboot_okay("", response);
		}
#else
	fastboot_fail("dtb is bind in kernel, return", response);
#endif
	} else if (strcmp(cmd, "bootloader") == 0 ||
		strcmp(cmd, "bootloader-boot0") == 0 ||
		strcmp(cmd, "bootloader-boot1") == 0) {
		fb_mmc_write_bootloader(cmd, dev_desc, download_buffer,
					download_bytes, response);
		return;
	} else {
		if (part_get_info_by_name_or_alias(dev_desc, cmd, &info) < 0) {
			pr_err("cannot find partition: '%s'\n", cmd);
			fastboot_fail("cannot find partition", response);
			return;
		}

		if (is_sparse_image(download_buffer)) {
			struct fb_mmc_sparse sparse_priv;
			struct sparse_storage sparse;
			int err;

			sparse_priv.dev_desc = dev_desc;

			sparse.blksz = info.blksz;
			sparse.start = info.start;
			sparse.size = info.size;
			sparse.write = fb_mmc_sparse_write;
			sparse.reserve = fb_mmc_sparse_reserve;
			sparse.mssg = fastboot_fail;

			printf("Flashing sparse image at offset " LBAFU "\n",
			       sparse.start);

			sparse.priv = &sparse_priv;
			err = write_sparse_image(&sparse, cmd, download_buffer,
						 response);
			if (!err)
				fastboot_okay(NULL, response);
		} else {
			write_raw_image(dev_desc, &info, cmd, download_buffer,
					download_bytes, response);
		}
	}
}

/**
 * fastboot_mmc_flash_erase() - Erase eMMC for fastboot
 *
 * @cmd: Named partition to erase
 * @response: Pointer to fastboot response buffer
 */
void fastboot_mmc_erase(const char *cmd, char *response)
{
	int ret;
	struct blk_desc *dev_desc;
	disk_partition_t info;
	lbaint_t blks, blks_start, blks_size, grp_size;
	struct mmc *mmc = find_mmc_device(CONFIG_FASTBOOT_FLASH_MMC_DEV);

	if (mmc == NULL) {
		pr_err("invalid mmc device\n");
		fastboot_fail("invalid mmc device", response);
		return;
	}

	dev_desc = blk_get_dev("mmc", CONFIG_FASTBOOT_FLASH_MMC_DEV);
	if (!dev_desc || dev_desc->type == DEV_TYPE_UNKNOWN) {
		pr_err("invalid mmc device\n");
		fastboot_fail("invalid mmc device", response);
		return;
	}

#if CONFIG_IS_ENABLED(EFI_PARTITION)
		if (strcmp(cmd, CONFIG_FASTBOOT_GPT_NAME) == 0) {
			printf("%s: erase gpt, cmd:%s\n", __func__, cmd);
			ret = erase_gpt_part_table(dev_desc);
			if (ret) {
				fastboot_fail("failed erase gpt", response);
				return;
			}
			fastboot_okay("", response);
			return;
		}
#endif

	if (strcmp(cmd, "dtb") == 0) {
#ifndef DTB_BIND_KERNEL
		extern int emmc_erase_rsv(struct mmc *mmc, char *rsv_part);
		ret = emmc_erase_rsv(mmc, (char *)cmd);
		if (ret) {
			fastboot_fail("fastboot erase dtb fail", response);
			return;
		}
		fastboot_okay(NULL, response);
#else
	fastboot_fail("dtb is bind in kernel, return", response);
#endif
	} else if (!strncmp(cmd, "bootloader", strlen("bootloader"))) {
		fb_mmc_erase_bootloader(cmd, dev_desc, response);
		return;
	} else {
		ret = part_get_info_by_name_or_alias(dev_desc, cmd, &info);
		if (ret < 0) {
			pr_err("cannot find partition: '%s'\n", cmd);
			fastboot_fail("cannot find partition", response);
			return;
		}

		/* Align blocks to erase group size to avoid erasing other partitions */
		grp_size = mmc->erase_grp_size;
		blks_start = (info.start + grp_size - 1) & ~(grp_size - 1);
		if (info.size >= grp_size)
			blks_size = (info.size - (blks_start - info.start)) &
					(~(grp_size - 1));
		else
			blks_size = 0;

		printf("Erasing blocks " LBAFU " to " LBAFU " due to alignment\n",
		       blks_start, blks_start + blks_size);

		blks = fb_mmc_blk_write(dev_desc, blks_start, blks_size, NULL);

		if (blks) {
			pr_err("failed erasing from device %d\n", dev_desc->devnum);
			fastboot_fail("failed erasing from device", response);
			return;
		}

		printf("........ erased " LBAFU " bytes from '%s'\n",
		       blks_size * info.blksz, cmd);
		fastboot_okay(NULL, response);
	}
}
