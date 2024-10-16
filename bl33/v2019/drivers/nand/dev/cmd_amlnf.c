// SPDX-License-Identifier: (GPL-2.0+ OR MIT)
/*
 * Copyright (c) 2019 Amlogic, Inc. All rights reserved.
 */

#include <config.h>
#include <common.h>
#include <command.h>
#include "../include/amlnf_dev.h"
/* #include <vsprintf.h> //include in common.h */
/*#include <exports.h>*/



#ifdef AML_NAND_UBOOT
extern void amlnf_disprotect(char *name);
extern struct amlnand_phydev *aml_phy_get_dev(const char * name);
extern struct amlnf_dev* aml_nftl_get_dev(const char * name);
extern void amlnf_get_chip_size(u64 *size);
extern void show_phydev_list(void);
extern void show_ldev_list(void);

#endif
extern void amlnf_dump_chipinfo(void);
extern int roomboot_nand_read(struct amlnand_phydev *phydev);
extern int roomboot_nand_write(struct amlnand_phydev *phydev);
extern int nand_read_ops(struct amlnand_phydev *phydev);
extern int nand_write_ops(struct amlnand_phydev *phydev);
extern int nand_erase(struct amlnand_phydev *phydev);
extern void amlnand_dump_page(struct amlnand_phydev *phydev);
extern int  amlnf_erase_ops(uint64_t off, uint64_t erase_len,unsigned char scrub_flag);
extern int  amlnf_markbad_reserved_ops(uint32_t start_blk);
extern u8 amlnf_boot_cpys(const char *part_name);
extern u64 amlnf_boot_copy_size(const char *part_name);


#if (AML_CFG_DTB_RSV_EN)
extern int amlnf_dtb_save(u8 *buf, int len);
extern int amlnf_dtb_read(u8 *buf, int len);
extern int amlnf_dtb_erase(void);
#endif

#if (AML_CFG_KEY_RSV_EN)
extern int amlnf_key_write(u8 *buf, int len, uint32_t *actual_length);
extern int amlnf_key_read(u8 * buf, int len, uint32_t *actual_length);
extern int amlnf_key_erase(void);
#endif

extern int amlnf_init(unsigned char flag);
extern int amlnf_exit(void);
//static int plane_mode;
struct amlnf_dev * nftl_device = NULL;
struct amlnand_phydev *phy_device=NULL;
static int nand_protect = 1;

static inline int isstring(char *p)
{
	char *endptr = p;
	while (*endptr != '\0') {
		if (!(((*endptr >= '0') && (*endptr <= '9'))
			|| ((*endptr >= 'a') && (*endptr <= 'f'))
			|| ((*endptr >= 'A') && (*endptr <= 'F'))
			|| (*endptr == 'x') || (*endptr == 'X')))
			return 1;
		endptr++;
	}

	return 0;
}

#ifdef AML_NAND_UBOOT
/*
 * repack.
 **/
 #if 0
unsigned long strtoul(const char *cp, char **endp,
				unsigned int base)
{
	return simple_strtoul(cp, endp, base);
}
 #endif

#endif /* AML_NAND_UBOOT */

#if 0
static inline int str2long(char *p, ulong *num)
{
	char *endptr;
	*num = strtoul(p, &endptr, 16);
	return (*p != '\0' && *endptr == '\0') ? 1 : 0;
}
#endif

static inline int str2longlong(char *p, u64 *num)
{
	char *endptr;
#ifndef AML_NAND_UBOOT
	*num = strtoull(p, &endptr, 16);
#else
	*num = simple_strtoul(p, &endptr, 16);
#endif
	if (*endptr != '\0') {
		switch (*endptr) {
		case 'g':
		case 'G':
			*num <<= 10;
		case 'm':
		case 'M':
			*num <<= 10;
		case 'k':
		case 'K':
			*num <<= 10;
			endptr++;
			break;
		}
	}
	return (*p != '\0' && *endptr == '\0') ? 1 : 0;
}

static int arg_off_size(int argc, char *argv[],
	u64 chipsize,
	u64 *off,
	u64 *size)
{
	if (argc >= 1) {
		if (!(str2longlong(argv[0], (u64 *)off))) {
			aml_nand_msg("'%s' is not a number", argv[0]);
			return -1;
		}
	} else
		*off = 0;

	if (argc >= 2) {
		if (!(str2longlong(argv[1], (u64 *)size))) {
			aml_nand_dbg("'%s' is not a number", argv[1]);
			return -1;
		}
	} else
		*size = chipsize - *off;

	if (*size == chipsize)
		aml_nand_msg("whole chip/dev");
	else
		aml_nand_msg("offset 0x%llx, size 0x%llx", *off, *size);

	return 0;
}

#define AML_NFTL_ALIGN_SIZE	    512
#define AML_NFTL_ALIGN_SHIFT	9
u8 local_buf[AML_NFTL_ALIGN_SIZE];

int amlnand_read(struct amlnf_dev *nftl_dev,
		u8 *buf,
		u64 offset,	/* in bytes */
		u64 size)	/* in bytes */
{
	u32 ret = 0;
	u64 head_sector;
	u64 head_start_bytes;
	u64 head_bytes_num;

	u64 mid_sector;
	u64 mid_len;

	u64 tail_sector;
	u64 tail_bytes_num;

	mid_len = offset >> AML_NFTL_ALIGN_SHIFT;	/* in sector */
	head_start_bytes = offset - (mid_len << AML_NFTL_ALIGN_SHIFT);
	head_bytes_num = AML_NFTL_ALIGN_SIZE - head_start_bytes;
	head_sector = offset >> AML_NFTL_ALIGN_SHIFT;
	CMD_LINE
	if (head_bytes_num >= size) {
		CMD_LINE
		ret |= nftl_dev->read_sector(nftl_dev,
			head_sector,
			1,
			local_buf);
		memcpy(buf, local_buf+head_start_bytes, size);
		return ret;
	}
	CMD_LINE
	if ((offset % AML_NFTL_ALIGN_SIZE) != 0) {
		ret |= nftl_dev->read_sector(nftl_dev, head_sector, 1, local_buf);
		memcpy(buf, local_buf+head_start_bytes, head_bytes_num);
		CMD_LINE
		buf += head_bytes_num;
		offset += head_bytes_num;
		size -= head_bytes_num;
	}

	if (size > AML_NFTL_ALIGN_SIZE) {
		mid_len = size >> AML_NFTL_ALIGN_SHIFT;
		mid_sector = offset >> AML_NFTL_ALIGN_SHIFT;
		CMD_LINE
		ret |= nftl_dev->read_sector(nftl_dev,
			mid_sector,
			mid_len,
			buf);
		buf += mid_len << AML_NFTL_ALIGN_SHIFT;
		offset += mid_len << AML_NFTL_ALIGN_SHIFT;
		size = size - (mid_len << AML_NFTL_ALIGN_SHIFT);
	}

	if (size == 0)
		return ret;
	CMD_LINE
	tail_sector = offset >> AML_NFTL_ALIGN_SHIFT;
	tail_bytes_num = size;
	ret |= nftl_dev->read_sector(nftl_dev, tail_sector, 1, local_buf);
	memcpy(buf, local_buf, tail_bytes_num);
	CMD_LINE
	return ret;
}

int amlnand_write(struct amlnf_dev *nftl_dev,
	u8 *buf,
	u64 offset,
	u64 size)
{
	u32 ret = 0;
	u64 head_sector;
	u64 head_start_bytes;
	u64 head_bytes_num;

	u64 mid_sector;
	u64 mid_len;

	u64 tail_sector;
	u64 tail_bytes_num;

	CMD_LINE
	mid_len = offset >> AML_NFTL_ALIGN_SHIFT;
	head_start_bytes = offset - (mid_len << AML_NFTL_ALIGN_SHIFT);
	head_bytes_num = AML_NFTL_ALIGN_SIZE - head_start_bytes;
	head_sector = offset >> AML_NFTL_ALIGN_SHIFT;
	CMD_LINE
	if (head_bytes_num >= size) {
		ret |= nftl_dev->read_sector(nftl_dev,
			head_sector,
			1,
			local_buf);
		memcpy(local_buf+head_start_bytes, buf, size);
		ret |= nftl_dev->write_sector(nftl_dev,
			head_sector,
			1,
			local_buf);
		goto flush;
	}
	CMD_LINE

    if ((offset % AML_NFTL_ALIGN_SIZE) != 0) {                     //sectore alignment
	    ret |= nftl_dev->read_sector(nftl_dev, head_sector, 1, local_buf);
	    memcpy(local_buf+head_start_bytes, buf, head_bytes_num);
	    ret |= nftl_dev->write_sector(nftl_dev, head_sector, 1, local_buf);


	    buf += head_bytes_num;
	    offset += head_bytes_num;
	    size -= head_bytes_num;
	}

	if (size > AML_NFTL_ALIGN_SIZE) {            //why 4
		CMD_LINE
		mid_len = size >> AML_NFTL_ALIGN_SHIFT;
		mid_sector = offset >> AML_NFTL_ALIGN_SHIFT;
		ret |= nftl_dev->write_sector(nftl_dev,
			mid_sector,
			mid_len,
			buf);
		buf += mid_len << AML_NFTL_ALIGN_SHIFT;
		offset += mid_len << AML_NFTL_ALIGN_SHIFT;
		size = size - (mid_len << AML_NFTL_ALIGN_SHIFT);
	}

	if (size == 0)
		goto flush;
	CMD_LINE
	tail_sector = offset >> AML_NFTL_ALIGN_SHIFT;
	tail_bytes_num = size;
	ret |= nftl_dev->read_sector(nftl_dev, tail_sector, 1, local_buf);
	memcpy(local_buf, buf, tail_bytes_num);
	ret |= nftl_dev->write_sector(nftl_dev, tail_sector, 1, local_buf);

flush:
	CMD_LINE
	ret = nftl_dev->flush((struct amlnf_dev *)nftl_dev);
	if (ret < 0) {
		aml_nand_msg("nftl flush cache failed");
		ret = -1;
	}
	CMD_LINE
	return ret;
}

/**
 * @usage: get size of the partition
 *
 * @name: part_name, when it's null the target
 * 		  will return normal device size(nfcache,
 *		  nfcode,nfdata).
 *
 * @return: size of the partition
 * 			>0 : success
 *			0  : failed
 */
u64 amlnf_get_size(const char *part_name)
{
	u64 size = 0;
	struct amlnf_dev *nftl_dev = NULL;
	/*struct amlnand_phydev *phydev = NULL;*/

	if (!part_name) {
		#if 0
		aml_nand_msg("part name null");
		phydev = aml_phy_get_dev(NAND_CACHE_NAME);
		if (!phydev) {
			aml_nand_msg("nfcache phydev be NULL!");
			return 0;
		}
		size += phydev->size;

		phydev = aml_phy_get_dev(NAND_CODE_NAME);
		if (!phydev) {
			aml_nand_msg("nfcode phydev be NULL!");
			return 0;
		}
		size += phydev->size;

		phydev = aml_phy_get_dev(NAND_DATA_NAME);
		if (!phydev) {
			aml_nand_msg("nfdata phydev be NULL!");
			return 0;
		}
		size += phydev->size;
		#endif
		amlnf_get_chip_size(&size);
		return size;
	}

	nftl_dev = aml_nftl_get_dev(part_name);
	if (!nftl_dev) {
		aml_nand_msg("nftl_dev be NULL");
		return 0;
	}

	size = (nftl_dev->size_sector)<<9;
	aml_nand_msg("nftl_dev->name =%s, size: %lld",
		nftl_dev->name,size);
	return size;
}

/**
 * @usage: read data from normal device
 *
 * @part_name: part_name, when it's null the target
 * 		  will regards as (nfcache) device.
 * @off: offset to the 0 address of partition/device
 * @size: the amount of bytes to read
 * @dest: pointer of target buffer
 *
 * @return: result of the operation
 * 			0 = success
 * 			other = fail
 */
int amlnf_read(const char *part_name, loff_t off, size_t size,void *dest)
{
	struct amlnf_dev *nftl_dev = NULL;
	struct amlnand_phydev *phydev = NULL;
	struct phydev_ops  *devops = NULL;
	char ret = 0xff;

	if (!part_name)	{
		aml_nand_msg("part name null");
		phydev = aml_phy_get_dev(NAND_CACHE_NAME);

		devops = &(phydev->ops);

		memset(devops, 0x0, sizeof(struct phydev_ops));
		devops->addr = (u64)off;
		devops->len = (u64)size;
		devops->mode = NAND_HW_ECC;
		devops->datbuf = (u8 *)dest;

		if (devops->addr + devops->len > phydev->size) {
			aml_nand_msg("Attemp to read out side nfcache dev area");
			return -1;
		}

		ret = nand_read_ops(phydev);
		if (ret < 0)
			aml_nand_msg("nand read failed");
		return ret;
	}

	nftl_dev = aml_nftl_get_dev(part_name);
	if (!nftl_dev) {
		aml_nand_msg("nftl_dev be null");
		return -1;
	}

	ret = amlnand_read(nftl_dev, (u8 *)dest, (u64)off, (u64)size);
	if (ret == 0)
		aml_nand_msg("read success");
	return ret;
}

/**
 * @usage: write data to normal device
 *
 * @part_name: part_name, when it's null the target
 * 		  will regards as (nfcache) device.
 * @off: offset to the 0 address of partition/device
 * @size: the amount of bytes to read
 * @source: pointer of target buffer
 *
 * @return: result of the operation
 * 			0 = success
 * 			other = fail
 */
int amlnf_write(const char *part_name, loff_t off, size_t size, void *source)
{
	struct amlnf_dev *nftl_dev = NULL;
	struct amlnand_phydev *phydev = NULL;
	struct phydev_ops *devops = NULL;
	char ret = 0xff;

	if (!part_name) {
		aml_nand_msg("part name null");
		phydev = aml_phy_get_dev(NAND_CACHE_NAME);

		devops = &(phydev->ops);
		memset(devops, 0x0, sizeof(struct phydev_ops));
		devops->addr = (u64)off;
		devops->len = (u64)size;
		devops->mode = NAND_HW_ECC;
		devops->datbuf = (u8 *)source;

		if (devops->addr + devops->len > phydev->size) {
			aml_nand_msg("Attemp to write out side nfcache dev area");
			return -1;
		}

		ret = nand_write_ops(phydev);
		if (ret < 0)
			aml_nand_msg("nand write failed");

		return ret;
	}

	nftl_dev = aml_nftl_get_dev(part_name);
	if (!nftl_dev) {
		aml_nand_msg("nftl dev null");
		return -1;
	}

	ret = amlnand_write(nftl_dev, (u8 *)source, (u64)off, (u64)size);
	if (!ret)
		aml_nand_msg("write success");

	return ret;
}

/**
 * @usage: erase the phydev device
 *
 * @phydev_name: device(nfboot,nfcache,nfcode,nfdata).
 * @off: offset to the 0 address of partition/device
 * @size: the amount of bytes to erase
 * @check_flag: Is need to erase the bad blk
 * 			0 = no erase
 * 			1 = erase all bad blk
 * @return: result of the operation
 * 			0 = success
 * 			other = fail
 */
 int aml_phydev_erase(char *phydev_name, u64 off, u64 size, u8 check_flag)
{
	struct amlnand_phydev *phydev = NULL;
	struct phydev_ops *devops = NULL;

	int percent = 0;
	int percent_complete = -1;
	char ret = 0xff;
	u64 erase_addr, erase_len, erase_off;

	phydev = aml_phy_get_dev(phydev_name);
	if (!phydev) {
		aml_nand_msg("phydev be null");
		return -1;
	}

	devops = &(phydev->ops);
	erase_addr = erase_off = off;
	erase_len = size;

	aml_nand_msg("off1 : %llx, size1: %llx",off, size);
	if (erase_len < phydev->erasesize) {
		aml_nand_msg("erase size 0x%016llx smaller than one blk size 0x%08x",
			erase_len, phydev->erasesize);
		aml_nand_msg("erasing 0x%08x instead", phydev->erasesize);
		erase_len = phydev->erasesize;
	}

	for (; erase_addr < erase_off + erase_len;
	erase_addr += phydev->erasesize) {
		memset(devops, 0x0, sizeof(struct phydev_ops));
		devops->addr = erase_addr;
		devops->len = phydev->erasesize;
		devops->mode = NAND_HW_ECC;

		/* do not check bad block in uboot area! */
		if (!check_flag) {
			ret = phydev->block_isbad(phydev);
			if (ret > 0) {
				aml_nand_msg("\rSkipping bad block at 0x%08llx",
					erase_addr);
				continue;
			} else if (ret < 0) {
				aml_nand_msg("get blk failed: ret= %d addr= %llx",
					ret, erase_addr);
				return -1;
			}
		}
		ret = nand_erase(phydev);
		if (ret < 0) {
			aml_nand_msg("\nAMLNAND Erase fail: %d %llx\n",
				ret, erase_addr);
			ret = phydev->block_markbad(phydev);
			if (ret < 0)
				aml_nand_msg("bad blk mark fail: %llx\n",
				erase_addr);
			continue;
		}
		percent = (erase_addr *100) / (erase_off + erase_len);
		if ((percent != percent_complete) && ((percent % 10) == 0)) {
			percent_complete = percent;
			aml_nand_msg("erase %d %%-%d %% complete",
				percent, percent+10);
		}
	}
	aml_nand_msg("NAND %s %s\n", "Erase",
		(ret < 0) ? "Erase" : "ok");
	return 0;
}

/**
 * @usage: erase the normal device
 *
 * @part_name: partition name, when it's null the target
 * 		  will regards as all normal device(nfcache,
 * 		  nfcode,nfdata).
 * @off: offset to the 0 address of device
 * @size: the amount of bytes to erase
 * @scrub_flag: scrub flag(scrub operats will works only
 *			when the device support)
 * 			0 = no scrub, just erase
 * 			1 = use scrub operats instead of erase,erase
 *			all chipsize include bootloader
 * @return: result of the operation
 * 			0 = success
 * 			other = fail
 */
int amlnf_erase(const char *part_name, loff_t off, size_t size, int scrub_flag)
{
	struct amlnand_phydev *phydev = NULL;
	u8 check_flag = 0;
	char *dev_name = NULL;

	aml_nand_msg("amlnf erase Enter");
	if (!part_name) {
		aml_nand_msg("part name null");
		if (!size) {
			uint64_t chipsize = 0;
			amlnf_get_chip_size(&chipsize);
			amlnf_erase_ops(off, chipsize, scrub_flag);
		} else
		amlnf_erase_ops(off, size, scrub_flag);
		#if 0
		list_for_each_entry(phydev, &nphy_dev_list,list){
			if (phydev != NULL) {
				if (strncmp((char *)phydev->name, NAND_BOOT_NAME,
				strlen((const char*)NAND_BOOT_NAME))) {
					off = 0;
					size = phydev->size;
					aml_phydev_erase((char *)phydev->name, (u64)off, (u64)size, check_flag);
				}
			}
		}
		#endif
		return 0;
	}

	if (strcmp(part_name, "boot") == 0) {
		dev_name = NAND_BOOT_NAME;
		check_flag = 1;
	}
	else if (strcmp(part_name, "code") == 0)
		dev_name = NAND_CODE_NAME;
	else if (strcmp(part_name, "cache") == 0)
		dev_name = NAND_CACHE_NAME;
	else if (strcmp(part_name, "data") == 0)
		dev_name = NAND_DATA_NAME;
	else {
		aml_nand_msg("input wrong name!! %s",dev_name);
		return -1;
	}

	phydev = aml_phy_get_dev(dev_name);
	if (!phydev) {
		aml_nand_msg("phydev be NULL");
		return  -1;
	}

	if (size == 0)
		size = phydev->size;

	aml_phydev_erase(dev_name, (u64)off, (u64)size, check_flag);
	return 0;
}

/**
 * @usage: read the bootloader from storage device
 *
 * @name: only can be "bootloader"
 * @copy: which copy you want read,mlc support read the nst cpy
 * @size: the amount of bytes to read
 * @buf: pointer of the target buffer
 *
 * @return: result of the operation
 * 			0 = success
 * 			other = fail
 */
int amlnf_boot_read(const char *part_name, uint8_t copy, size_t size, void *buf)
{
	struct amlnand_phydev *phydev = NULL;
	char *dev_name = NULL;
	struct phydev_ops  *devops = NULL;
	char ret = 0;


	if (strcmp(part_name, "bootloader") == 0) {
		dev_name = NAND_BOOT_NAME;
	} else {
		aml_nand_msg("no tpl");
		ret = -1;
		return ret;
	}

	phydev = aml_phy_get_dev(dev_name);
	if (!phydev) {
		aml_nand_msg("phydev be NULL");
		ret = -1;
		return ret;
	}

	devops = &(phydev->ops);
	memset(devops, 0x0, sizeof(struct phydev_ops));
	devops->addr = 0;
	devops->len = size;
	devops->mode = NAND_HW_ECC;
	devops->datbuf = buf;
	ret = roomboot_nand_read(phydev);
	if (ret < 0) {
		aml_nand_msg("nand read uboot failed");
	}

	return ret;
}

/**
 * @usage: write the bootloaderinto storage device
 *
 * @name: only can be "bootloader"
 * @copy: which copy you want write,
 * 		  it will write to all copies when copy = BOOT_OPS_ALL
 * @size: the amount of bytes to write
 * @buf: pointer of the source buffer
 *
 * @return: result of the operation
 * 			0 = success
 * 			other = fail
 */
 int amlnf_boot_write(const char *part_name, uint8_t copy, size_t size, void *buf)
{
	struct amlnand_phydev *phydev = NULL;
	char *dev_name = NULL;
	struct phydev_ops  *devops = NULL;
	char ret = 0;

	if (strcmp(part_name, "bootloader") == 0) {
		dev_name = NAND_BOOT_NAME;
	} else {
		aml_nand_msg("no tpl");
		ret = -1;
		return ret;
	}

	phydev = aml_phy_get_dev(dev_name);
	if (!phydev) {
		aml_nand_msg("phydev be NULL");
		ret = -1;
		return ret;
	}

	devops = &(phydev->ops);
	memset(devops, 0x0, sizeof(struct phydev_ops));
	devops->addr = 0;
	devops->len = size;
	devops->mode = NAND_HW_ECC;
	devops->datbuf = buf;
	ret = roomboot_nand_write(phydev);
	if (ret < 0) {
		aml_nand_msg("nand write uboot failed");
	}

	return ret;
}

/**
 * @usage: erase the bootloader/
 *
 * @name: only can be "bootloader"
 * @copy: it will erase all copies
 *
 * @return: result of the operation
 * 			0 = success
 * 			other = fail
 */
int amlnf_boot_erase(const char *part_name, uint8_t copy)
{
	struct amlnand_phydev *phydev = NULL;
	u8 check_flag = 0;
	char *dev_name =NULL;
	u64 off, size;
	char ret = 0xff;

	if (strcmp(part_name, "bootloader") == 0) {
		dev_name = NAND_BOOT_NAME;
		check_flag = 1;
	} else {
		aml_nand_msg("no tpl");
		ret = -1;
		return ret;
	}

	phydev = aml_phy_get_dev(dev_name);
	if (!phydev) {
		aml_nand_msg("phydev be null");
		return -1;
	}
	off =0;
	size = phydev->size;
	aml_phydev_erase(dev_name, off, size, check_flag);
	return 0;
}





extern void dbg_phyop(void);
static int do_amlnfphy(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	struct amlnand_phydev *phydev = NULL;
	struct phydev_ops  *devops = NULL;
	struct amlnf_dev *nftl_dev;

	unsigned long addr;
	u64 chipsize, erase_addr, erase_len, erase_off, off, size;
	u8 devread, nfread_flag;
	int  start_secor, length,  ret = 0;
	char *cmd, *protect_name;
	char *dev_name = NULL;
	unsigned long markbad_reserved_addr = 0;

	/* at least two arguments please */
	if (argc < 1)
		goto usage;

	cmd = argv[1];

	/* for dbg entry! */
	if (strcmp(cmd, "dbg") == 0) {
		dbg_phyop();
		return 0;
	}

	/* show boot flag!*/
	if (strcmp(cmd, "boot") == 0) {
		aml_nand_msg("bootflag not use yet!");
		return 0;
	}
	if (strcmp(cmd, "bootloader") == 0) {
		return 0;
	}


	if (strcmp(cmd, "device") == 0) {
	   //printk("argc %d\n", argc);
		if (argc == 2) {
			show_phydev_list();
			return 0;
		}
		return 0;
	}

	if (strcmp(cmd, "env") == 0) {
		aml_nand_dbg("env relocate");
		env_relocate();
		return 0;
	}

	if (strcmp(cmd, "disprotect") == 0) {
		protect_name = argv[2];
		/* fixme, using amlnf_chip*/
		amlnf_disprotect(protect_name);
		return 0;
	}

	if (strcmp(cmd, "exit") == 0) {
		amlnf_exit();
		return 0;
	}

	if (strcmp(cmd, "init") == 0) {
		putc('\n');
		/*int init_flag = (ulong)strtoul(argv[2], NULL, 16);*/
		int init_flag = (ulong)simple_strtoul(argv[2], NULL, 16);
		/* flag = 0, indicate normal boot; */
		/* flag = 1, indicate update, with data; */
		/* flag = 2, indicate need erase */

		aml_nand_msg("init_flag:%x",init_flag);
		ret = amlnf_init(init_flag);
		if (ret) {
			aml_nand_msg("nand_init failed ret:%x", ret);
			return ret;
		}

		if (init_flag == 5) {
			aml_nand_msg("amlnf pre return %d",ret);
			return ret;
		}

		phydev = aml_phy_get_dev(NAND_CODE_NAME);
		if (!phydev) {
			aml_nand_msg("phydev be NULL");
			goto usage;
		}
		return 0;
	}
	//ldevice
	if (strcmp(cmd, "ldevice") == 0) {
	   //printk("argc %d\n", argc);
	   if (argc == 2) {
		   show_ldev_list();
		   return 0;
	   }
	   //fixme,
	   goto usage;
	   return 0;
	}

	if ((strcmp(cmd, "read_byte") == 0)
		|| (strcmp(cmd, "write_byte") == 0)
		|| (strcmp(cmd, "lwrite") == 0)
		||(strcmp(cmd, "lread") == 0)) {
		if (argc < 6)
			goto usage;

		dev_name = argv[2];
		/*addr = (ulong)strtoul(argv[3], NULL, 16);*/
		addr = (ulong)simple_strtoul(argv[3], NULL, 16);
		nfread_flag = 0;
		if ((strncmp(cmd, "read_byte", 9) == 0)
			||(strncmp(cmd, "lread", 5) == 0) )
			nfread_flag = 1;

		if (arg_off_size(argc - 4, (char **)(argv + 4), 0x0, &off, &size) != 0) {
			goto usage;
		}

		if (nfread_flag)
			ret = amlnf_read(dev_name, (loff_t)off, (size_t)size, (void *)addr);
		else
			ret = amlnf_write(dev_name, (loff_t)off, (size_t)size, (void *)addr);

		aml_nand_msg(" 0x%llx bytes %s : %s",
				size,
				nfread_flag ? "read_byte" : "write_byte",
				ret ? "ERROR" : "OK");

		return ret;
	}

	if ((strcmp(cmd, "read") == 0) || (strcmp(cmd, "write") == 0)) {
		if (argc < 6)
			goto usage;

		dev_name = argv[2];
		nftl_dev = NULL;
		nftl_dev = aml_nftl_get_dev(dev_name);
		if (!nftl_dev) {
			aml_nand_msg("nftl_dev be NULL");
			return -1;
		}
		aml_nand_dbg("nftl_dev->nand_dev->writesize =%x",
				nftl_dev->nand_dev->writesize);
		aml_nand_dbg("nftl_dev->nand_dev->erasesize =%x",
				nftl_dev->nand_dev->erasesize);
		aml_nand_dbg("nftl_dev->name =%s", nftl_dev->name);

		/*addr = (ulong)strtoul(argv[3], NULL, 16);*/
		addr = (ulong)simple_strtoul(argv[3], NULL, 16);

		nfread_flag = strncmp(cmd, "read", 4) == 0;
		/* 1 = read, 0 = write */
		aml_nand_msg("NAND %s: addr:%lx",
			nfread_flag ? "read" : "write",
			addr);

		if (arg_off_size(argc - 4, (char **)(argv + 4), 0x0, &off, &size) != 0)
			goto usage;

		if (off % 512) {
			start_secor = ((int) (off / 512) + 1);
			aml_nand_dbg("secor+1");
		} else
			start_secor = (int) (off / 512);

		if (size % 512) {
			length = ((int)((size / 512))+1);
			aml_nand_dbg("length+1");
		} else
			length = (int)((size / 512));

		aml_nand_dbg("start_secor =%d", start_secor);
		aml_nand_dbg("length_sector =%d", length);

		if (nfread_flag) {
			ret = nftl_dev->read_sector(nftl_dev,
				start_secor,
				length,
				(u8 *)addr);
			if (ret < 0) {
				aml_nand_dbg("read %d sector  failed", length);
				return -1;
			}
		} else {
			ret = nftl_dev->write_sector(nftl_dev,
				start_secor,
				length,
				(u8 *)addr);
			if (ret < 0) {
				aml_nand_dbg("write %d sector  failed", length);
				return -1;
			}
			ret = nftl_dev->flush(nftl_dev);
			if (ret < 0) {
				aml_nand_dbg("nftl flush cache failed");
				return -1;
			}
		}

		aml_nand_msg(" %d sector %s : %s",
			length,
			nfread_flag ? "read" : "write",
			ret ? "ERROR" : "OK");
		return ret;
	}

	if (strcmp(cmd, "chipinfo") == 0) {
		putc('\n');
		amlnf_dump_chipinfo();
		return 0;
	}

	if (strcmp(cmd, "size") == 0) {
		if (argc < 4)
			goto usage;

		dev_name = argv[2];
		/*addr = (ulong)strtoul(argv[3], NULL, 16);*/
		addr = (ulong)simple_strtoul(argv[3], NULL, 16);
		*(u64 *)addr  = amlnf_get_size(dev_name);
		return 0;
	}

	if (strncmp(cmd, "rom_protect", 9) == 0) {
		if (argc < 2)
			goto usage;

		if (strncmp(argv[2], "on", 2) == 0)
			nand_protect = 1;
		else if (strncmp(argv[2], "off", 3) == 0)
			nand_protect = 0;
		else
			goto usage;

		return	0;
	}

	if ((strcmp(cmd, "rom_write") == 0)
		|| (strcmp(cmd, "rom_read") == 0)) {
		nfread_flag = 0;
		if (strncmp(cmd, "rom_read", 8) == 0)
				nfread_flag = 1;

		if (argc < 4)
			goto usage;

		/*addr = (ulong)strtoul(argv[2], NULL, 16);*/
		addr = (ulong)simple_strtoul(argv[2], NULL, 16);
		aml_nand_msg("AMLNAND %s: ",
			nfread_flag ? "rom_read" : "rom_write");

		struct amlnand_phydev *tmp_phydev = phydev;
		struct phydev_ops  *tmp_devops = devops;

		phydev = aml_phy_get_dev(NAND_BOOT_NAME);
		if (!phydev) {
			aml_nand_msg("phydev be NULL");
			return -1;
		}
		devops = &(phydev->ops);
		aml_nand_dbg("phydev->name =%s", phydev->name);
		amldev_dumpinfo(phydev);

		if (arg_off_size(argc - 3,
			(char **)(argv + 3),
			phydev->size,
			&off,
			&size) != 0)
			return -1;

		memset(devops, 0x0, sizeof(struct phydev_ops));

		devops->addr = off;
		devops->len = size;
		devops->mode = NAND_HW_ECC;
		devops->datbuf = (u8 *)addr;

		if (nfread_flag) {
			ret = roomboot_nand_read(phydev);
			if (ret < 0)
				aml_nand_msg("nand read uboot failed");
		} else {
			ret = roomboot_nand_write(phydev);
			if (ret < 0)
				aml_nand_msg("nand write uboot failed");
		}

		aml_nand_msg("%llu bytes %s : %s",
				size,
				nfread_flag ? "rom_read" : "rom_write",
				ret ? "ERROR" : "OK");

		phydev = tmp_phydev;
		devops = tmp_devops;

		return ret;
	}
#if (AML_CFG_DTB_RSV_EN)
	if ((strcmp(cmd, "dtb_write") == 0)
		|| (strcmp(cmd, "dtb_read") == 0)) {
		nfread_flag = 0;
		if (strncmp(cmd, "dtb_read", 8) == 0)
				nfread_flag = 1;

		if (argc < 3)
			goto usage;

		/*addr = (ulong)strtoul(argv[2], NULL, 16);
		size = (ulong)strtoul(argv[3], NULL, 16);*/
		addr = (ulong)simple_strtoul(argv[2], NULL, 16);
		size = (ulong)simple_strtoul(argv[3], NULL, 16);

		aml_nand_msg("cmd %s: ",
			nfread_flag ? "dtb_read" : "dtb_write");

		//memset(devops, 0x0, sizeof(struct phydev_ops));

		if (nfread_flag) {
			ret = amlnf_dtb_read((u8 *)addr, (int)size);
			if (ret < 0)
				aml_nand_msg("nand read dtd failed");
		} else {
			ret = amlnf_dtb_save((u8 *)addr, (int)size);
			if (ret < 0)
				aml_nand_msg("nand write dtd failed");
		}

		aml_nand_msg("%llu bytes %s : %s",
				size,
				nfread_flag ? "dtd_read" : "dtd_write",
				ret ? "ERROR" : "OK");
		return ret;
	}

	if (strcmp(cmd, "dtb_erase") == 0) {
		ret = amlnf_dtb_erase();
		aml_nand_msg("dtb erase %s", ret ? "Fail" : "Okay");
		return ret;
	}
#endif
	/* need full environments */
#if (AML_CFG_KEY_RSV_EN)
	uint32_t actual_length;
	if ((strcmp(cmd, "key_write") == 0)
		|| (strcmp(cmd, "key_read") == 0)) {
		nfread_flag = 0;
		if (strncmp(cmd, "key_read", 8) == 0)
				nfread_flag = 1;

		if (argc < 3)
			goto usage;

		/*addr = (ulong)strtoul(argv[2], NULL, 16);
		size = (ulong)strtoul(argv[3], NULL, 16);*/
		addr = (ulong)simple_strtoul(argv[2], NULL, 16);
		size = (ulong)simple_strtoul(argv[3], NULL, 16);

		aml_nand_msg("cmd %s: ",
			nfread_flag ? "key_read" : "key_write");

		//memset(devops, 0x0, sizeof(struct phydev_ops));

		if (nfread_flag) {
			ret = amlnf_key_read((u8 *)addr, (int)size, &actual_length);
			if (ret < 0)
				aml_nand_msg("nand read key failed");
		} else {
			ret = amlnf_key_write((u8 *)addr, (int)size, &actual_length);
			if (ret < 0)
				aml_nand_msg("nand write key failed");
		}

		aml_nand_msg("%llu bytes %s : %s",
				size,
				nfread_flag ? "key_read" : "key_write",
				ret ? "ERROR" : "OK");
		return ret;
	}

	if (strcmp(cmd, "key_erase") == 0) {
		ret = amlnf_key_erase();
		aml_nand_msg("key erase %s", ret ? "Fail" : "Okay");
		return ret;
	}
#endif
	/* avoid fail... */
	amlnf_get_chip_size(&chipsize);

	if ((strcmp(cmd, "devread") == 0) || (strcmp(cmd, "devwrite") == 0)) {

		if (argc < 6)
			goto usage;

		dev_name = argv[2];
		if (strcmp(dev_name, "boot") == 0)
			dev_name = NAND_BOOT_NAME;
		else if (strcmp(dev_name, "code") == 0)
			dev_name = NAND_CODE_NAME;
		else if (strcmp(dev_name, "cache") == 0)
			dev_name = NAND_CACHE_NAME;
		else if (strcmp(dev_name, "data") == 0)
			dev_name = NAND_DATA_NAME;
		else {
			aml_nand_msg("input wrong name!! %s", dev_name);
			goto usage;
		}
		/*addr = (ulong)strtoul(argv[3], NULL, 16);*/
		addr = (ulong)simple_strtoul(argv[3], NULL, 16);
		aml_nand_dbg("addr = %llx", addr);

		devread = strncmp(cmd, "devread", 7) == 0;
		/* 1 = devread, 0 = devwrite */
		aml_nand_msg("NAND %s: addr:%lx",
			devread ? "devread" : "devwrite",
			addr);

		if (arg_off_size(argc - 4,
			(char **)(argv + 4),
			chipsize,
			&off,
			&size) != 0)
			goto usage;

		phydev = aml_phy_get_dev(dev_name);
		if (!phydev) {
			aml_nand_msg("phydev be NULL");
			return -1;
		}
		devops = &(phydev->ops);

		memset(devops, 0x0, sizeof(struct phydev_ops));
		devops->addr = off;
		devops->len = size;
		devops->mode = NAND_HW_ECC;
		devops->datbuf = (u8 *)addr;

		if (devread) {
			ret = nand_read_ops(phydev);
			if (ret < 0)
				aml_nand_dbg("nand read failed");
		} else {
			ret = nand_write_ops(phydev);
			if (ret < 0)
				aml_nand_dbg("nand write failed");
		}

		aml_nand_msg("%llu bytes %s : %s",
			size,
			devread ? "devread" : "devwrite",
			ret ? "ERROR" : "OK");
		return 0;
	}

	if ((strcmp(cmd, "deverase") == 0)) {
		if (argc < 4)
			goto usage;

		int without_check = 0;
		dev_name = argv[2];

		if (strcmp(dev_name, "boot") == 0) {
			dev_name = NAND_BOOT_NAME;
			/* do not check bad block in uboot area! */
			without_check = 1;
		}
		else if (strcmp(dev_name, "code") == 0)
			dev_name = NAND_CODE_NAME;
		else if (strcmp(dev_name, "cache") == 0)
			dev_name = NAND_CACHE_NAME;
		else if (strcmp(dev_name, "data") == 0)
			dev_name = NAND_DATA_NAME;
		else {
			aml_nand_msg("input wrong name!! %s", dev_name);
			goto usage;
		}

		phydev = aml_phy_get_dev(dev_name);
		if (!phydev) {
			aml_nand_msg("phydev be NULL");
			return -1;
		}

		if (!strcmp(argv[3], "whole")) {
			off = 0;
			size = phydev->size;
			printf("whole dev.\n");
		} else {
			if (argc < 3)
				goto usage;
			if ((arg_off_size(argc - 3,
					(char **)(argv + 3),
					phydev->size,
					&off,
					&size) != 0))
				goto usage;
			//aml_nand_msg("off:0x%llx size:%llx.\n", off, size);
		}
		aml_nand_msg("off:0x%llx size:%llx.\n", off, size);
		aml_phydev_erase(dev_name, (u64)off, (u64)size, without_check);
		/*dev_name = argv[2];
		amlnf_erase(dev_name, (loff_t)off, (size_t)size, without_check);*/ /*for test*/
		return 0;
	}

	if (strcmp(cmd, "dump") == 0) {
		dev_name = argv[2];
		if (strcmp(dev_name, "boot") == 0)
			dev_name = NAND_BOOT_NAME;
		else if (strcmp(dev_name, "cache") == 0)
			dev_name = NAND_CACHE_NAME;
		else if (strcmp(dev_name, "code") == 0)
			dev_name = NAND_CODE_NAME;
		else if (strcmp(dev_name, "data") == 0)
			dev_name = NAND_DATA_NAME;
		else {
			aml_nand_msg("input wrong name!! %s", dev_name);
			goto usage;
		}
		/*addr = (ulong)strtoul(argv[3], NULL, 16);*/
		addr = (ulong)simple_strtoul(argv[3], NULL, 16);
		aml_nand_dbg("addr = %llx", addr);

		if (arg_off_size(argc - 4,
			(char **)(argv + 4),
			chipsize,
			&off,
			&size) != 0)
			goto usage;

		phydev = aml_phy_get_dev(dev_name);
		if (!phydev) {
			aml_nand_msg("phydev be NULL");
			return -1;
		}

		devops = &(phydev->ops);
		memset(devops, 0x0, sizeof(struct phydev_ops));
		devops->addr = off;
		devops->len = phydev->writesize;
		devops->oobbuf = NULL;
		devops->datbuf = (u8 *)addr;
		devops->mode = NAND_SOFT_ECC;

		amlnand_dump_page(phydev);
		return 0;
	}

	if ((strcmp(cmd, "scrub") == 0) || (strcmp(cmd, "erase") == 0)) {
		int scrub_flag = !strncmp(cmd, "scrub", 5);
		if (argc < 2)
			goto usage;

		if (scrub_flag) {
			puts("Warning:"
				"devscrub option will erase all factory set "\
				"bad blocks !\n"\
				"         "\
				"There is no reliable way to recover them.\n"\
				"         "\
				"Use this command only for testing purposes "\
				"if you\n"\
				"         "\
				"are sure of what you are doing !\n"
				"\nReally scrub this NAND flash ? < y/N >"\
				"\n");
			scrub_flag = 0;
			if (nand_protect) {
				if (getc() == 'y') {
					puts("y");
					if (getc() == '\r')
						scrub_flag = 1;
					else {
						puts("scrub aborted\n");
						return -1;
					}
				} else {
					puts("scrub aborted\n");
					return -1;
				}
			} else
			    scrub_flag = 1;
		}

		if (!strcmp(argv[2], "whole")) {
			off = 0;
			/* ((u64)flash->chipsize << 20); */
			size = chipsize;
			erase_addr = erase_off = off;
			erase_len = size;
			printf("whole dev.\n");
		} else {
			if ((arg_off_size(argc - 2,
				(char **)(argv + 2),
				chipsize,
				&off,
				&size) != 0))
				goto usage;
			erase_addr = erase_off = off;
			erase_len = size;
		}

		erase_addr = erase_off = off;
		erase_len = size;
		ret = amlnf_erase_ops(off, erase_len, scrub_flag);
		if (ret < 0)
			aml_nand_msg("nand erase failed");
		return ret;
	}
    if (strcmp(cmd, "markbad") == 0) {

		if (argc < 4) {
			goto usage;
		}

		dev_name = argv[2];
		if (strcmp(dev_name, "boot") == 0) {
			dev_name = NAND_BOOT_NAME;
		}
		else if(strcmp(dev_name, "code") == 0){
			dev_name = NAND_CODE_NAME;
		}else if(strcmp(dev_name, "cache") == 0){
			dev_name = NAND_CACHE_NAME;
		}else if(strcmp(dev_name, "data") == 0){
			dev_name = NAND_DATA_NAME;
		}else{
			aml_nand_msg("input wrong name!! %s",dev_name);
			goto usage;
		}
		phydev = aml_phy_get_dev(dev_name);
		if (!phydev) {
			aml_nand_msg("phydev be NULL");
			return -1;
		}

		devops = &(phydev->ops);

		if ((arg_off_size(argc - 3, (char **)(argv + 3), phydev->size, &off, &size) != 0)) {
			goto usage;
		}
		aml_nand_dbg("off:0x%llx size:%llx.\n", off, size);
		erase_addr =erase_off= off;
		erase_len = size;


		aml_nand_dbg("erase_len = %llx",erase_len);
		aml_nand_dbg("erase_off = %llx",erase_off);

		if (erase_len < phydev->erasesize) {
			printf("Warning: markbad size 0x%08x smaller than one "	\
				   "block 0x%08x\n",(unsigned int)erase_len, phydev->erasesize);
			printf("		 markbad 0x%08x instead\n", phydev->erasesize);
			erase_len = phydev->erasesize;
		}

        for (; erase_addr <erase_off + erase_len; erase_addr +=  phydev->erasesize) {
            memset(devops, 0x0, sizeof(struct phydev_ops));
            devops->addr = erase_addr;
            devops->len = phydev->erasesize;
            devops->mode = NAND_HW_ECC;

             ret = phydev->block_isbad(phydev);
            if (ret > 0) {
                printf("\rSkipping bad block at 0x%08llx\n", erase_addr);
                continue;

            } else if (ret < 0) {
                printf("\n:AMLNAND get bad block failed: ret=%d at addr=%llx\n",ret, erase_addr);
                return -1;
            }

            ret = phydev->block_markbad(phydev);
            if (ret < 0)
                printf("AMLNAND bad block mark failed: %llx\n", erase_addr);

        }
		printf("NAND %s %s\n", "MARKBAD", (ret <0) ? "ERROR" : "OK");
		return 0;
	}
    if (strcmp(cmd, "markbad_reserved") == 0) {

		if (argc < 3) {
			goto usage;
		}

		if (!(str2long(argv[2], (unsigned long*)&markbad_reserved_addr))) {
			aml_nand_dbg("'%s' is not a number", argv[2]);
			goto usage;
		}
		printf("mark_reserved block:%d\n", (int)markbad_reserved_addr);
		ret = amlnf_markbad_reserved_ops(markbad_reserved_addr);

		printf("NAND %s %s\n", "MARKBAD", (ret <0) ? "ERROR" : "OK");
		return 0;
	}
usage:
	printf("may be invalid argus, check again.\n");
	cmd_usage(cmdtp);
	return 1;
}

#ifdef CONFIG_SYS_LONGHELP
static char amlnand_help_text[] =
	"init - init amlnand_phy here\n"
	"chipinfo - show aml chip information\n"
	"device[dev] - show or set current device\n"
	"partition* [part] - show or set current partition\n"
	"plane[dev] - show or set current plane mode\n"
	"read - addr off|partition size\n"
	"write - addr off|partition size\n"
	"    read/write 'size' bytes starting at offset 'off'\n"
	"    to/from memory address 'addr', skipping bad blocks.\n"
	"erase[clean|whole][off size] - erase 'size' bytes from\n"
	"    offset 'off' (entire device if not specified)\n"
	"dump  addr off\n"
	"    show the raw data to addr at offset off\n"
	"read_byte - addr off|partition size\n"
	"write_byte - addr off|partition size\n"
	"    read_byte/write_byte 'size' bytes starting at offset 'off'\n"
	"    to/from memory address 'addr', skipping bad blocks.\n"
	"devread  - addr off|partition size\n"
	"devwrite - addr off|partition size\n"
	"    read/write 'size' bytes starting at offset 'off' in device[dev]\n"
	"    to/from memory address 'addr', skipping bad blocks.\n"
	"deverase[whole][off size] - erase 'size' bytes from\n"
	"    offset 'off' (entire device if not specified) in device[dev]\n"
	"markbad addr - mark block bad at addr\n"
	"mark_reserved reserved_blk_NO -mark reserved_blk_NO bad \n"
	"ldevice[dev] - show/get nftl(logic) device by name\n"
	"rom_read/write addr off cnt - read/write uboot.\n"
	"boot - show boot flag"
#if (AML_CFG_DTB_RSV_EN)
	"dtb_read/write addr cnt - read/write dtd.\n"
	"dtb_erase - erase dtb!\n"
#endif
#if (AML_CFG_KEY_RSV_EN)
	"key_read/write addr cnt - read/write dtd.\n"
	"key_erase - erase keys!\n"
#endif
	"";
#endif

U_BOOT_CMD(
	amlnf, CONFIG_SYS_MAXARGS, 0, do_amlnfphy,
	"aml nand sub-system",
	amlnand_help_text
);


