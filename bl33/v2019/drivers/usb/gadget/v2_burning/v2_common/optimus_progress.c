// SPDX-License-Identifier: (GPL-2.0+ OR MIT)
/*
 * Copyright (c) 2019 Amlogic, Inc. All rights reserved.
 */

#include "../v2_burning_i.h"
#include <amlogic/aml_mmc.h>
#include <dm/pinctrl.h>
#include <emmc_partitions.h>

#define BLOCK_SIZE 512
#define OPTIMUS_PROMPT_SIZE_MIN     (4U<<20)//mininal size to prompt burning progress step

struct ProgressInfo{
    u32     itemSzLow;
    u32     itemSzHigh;

    u8      startStep;
    u8      endStep;
    u8      totalStepNum;
    u8      currentStep;

    u32     bytesToIncOneStep;
    u32     unReportSzInByte;

    u32     bytesToUpdateStep;
    u32     reserv;

};
static struct ProgressInfo _progressInfo = {0};

int optimus_progress_init(const unsigned itemSzHigh, const unsigned itemSzLow, const u32 startStep, const u32 endStep)
{
    _progressInfo.itemSzLow     = itemSzLow;
    _progressInfo.itemSzHigh    = itemSzHigh;

    _progressInfo.startStep     = startStep;
    _progressInfo.endStep       = endStep;
    _progressInfo.currentStep   = startStep;
    _progressInfo.totalStepNum  = endStep - startStep;

    _progressInfo.unReportSzInByte  = 0;//clear it

    //ATTENTION: as divisor / is lossy, _progressInfo.bytesToIncOneStep * _progressInfo.totalStepNum <= item size, so 100% is sometimes not exactly Burn Completed!!
    _progressInfo.bytesToIncOneStep = ((((u64)itemSzHigh)<<32) + itemSzLow) / _progressInfo.totalStepNum;
    _progressInfo.bytesToUpdateStep = (OPTIMUS_PROMPT_SIZE_MIN > _progressInfo.bytesToIncOneStep) ? OPTIMUS_PROMPT_SIZE_MIN : _progressInfo.bytesToIncOneStep;


    DWN_DBG("item size 0x[%x, %x], currentStep %d, totalStepNum %d, bytesToIncOneStep 0x%x\n",
            itemSzHigh, itemSzLow, _progressInfo.currentStep, _progressInfo.totalStepNum, _progressInfo.bytesToIncOneStep);
    return 0;
}

int optimus_progress_exit(void)
{
    return 0;
}

int optimus_update_progress(const unsigned thisBurnSz)
{
    _progressInfo.unReportSzInByte += thisBurnSz;

    if (_progressInfo.bytesToUpdateStep > _progressInfo.unReportSzInByte) {
        return 0;
    }

    //if it is first time to prompt UI progress steps
    if (_progressInfo.unReportSzInByte == thisBurnSz && _progressInfo.startStep + 1 == _progressInfo.currentStep)
    {
        printf("\n");
    }

    _progressInfo.currentStep       += _progressInfo.unReportSzInByte / _progressInfo.bytesToIncOneStep;
    _progressInfo.unReportSzInByte  %= _progressInfo.bytesToIncOneStep;

    printf("Downloading %%%d\r", _progressInfo.currentStep);
    if (_progressInfo.currentStep == _progressInfo.endStep) {
        printf("\n");
    }

    return 0;
}

//outStr will be null-terminater after format
int optimus_hex_data_2_ascii_str(const unsigned char* hexData, const unsigned nBytes, char* outStr, const unsigned strSz)
{
    int i = 1;
    if (strSz < 2 * nBytes + 1) {
        DWN_ERR("strSz(%d) > 2 * nBytes(%d)\n", strSz, nBytes);
        return __LINE__;
    }

    sprintf(outStr, "%02x", hexData[0]);
    for (; i < nBytes; ++i)
    {
	sprintf(&outStr[i * 2], "%02x", hexData[i]);
    }

    return 0;
}

unsigned add_sum(const void* pBuf, const unsigned size)
{
    unsigned sum		 =	0;
    const unsigned* data = (const unsigned*)pBuf;
    unsigned wordLen 	 = size>>2;
    unsigned rest 		 = size & 3;

    for (; wordLen/4; wordLen -= 4)
    {
        sum += *data++;
        sum += *data++;
        sum += *data++;
        sum += *data++;
    }
    while (wordLen--)
    {
        sum += *data++;
    }

    if (rest == 0)
    {
        ;
    }
    else if(rest == 1)
    {
        sum += (*data) & 0xff;
    }
    else if(rest == 2)
    {
        sum += (*data) & 0xffff;
    }
    else if(rest == 3)
    {
        sum += (*data) & 0xffffff;
    }

    return sum;
}

#ifndef SCPI_CMD_USB_BOOT
#define SCPI_CMD_USB_BOOT 		0xB0	//skip to wait pc with timeout
#define SCPI_CMD_USB_UNBOOT 	0xB1	//skip to wait pc forever
#define SCPI_CMD_SDCARD_BOOT 	0xB2
#define SCPI_CMD_CLEAR_BOOT 	0xB3
static void _erase_bootloader(uint64_t arg0)
{
    if (SCPI_CMD_CLEAR_BOOT == arg0) return;//dummy as not supported

    const char* bootName = "bootloader";
    const int bootCpyNum = store_boot_copy_num(bootName);

    printf("arg0[0x%llx]\n", arg0);
    printf("set_boot_first_timeout not defined so Really erase\n");
    int iCopy = 0;
    for (; iCopy < bootCpyNum; ++iCopy) {
        store_boot_erase(bootName, iCopy);
    }
}
extern void set_boot_first_timeout(uint64_t arg0) __attribute__((weak, alias("_erase_bootloader")));

#include <asm/arch/bl31_apis.h>
#include <amlogic/cpu_id.h>
#endif//#ifndef SCPI_CMD_USB_BOOT
//I assume that store_inited yet when "bootloader_is_old"!!!!
int optimus_erase_bootloader(const char* extBootDev)
{
    if (!strcmp("usb", extBootDev))
    {
        set_boot_first_timeout(SCPI_CMD_USB_UNBOOT);
        return 0;
    }

    if (!strcmp("usb-timeout", extBootDev))
    {
        set_boot_first_timeout(SCPI_CMD_USB_BOOT);
        return 0;
    }

    if (!strcmp("sdc", extBootDev))
    {
        cpu_id_t cpuid = get_cpu_id();
        if (MESON_CPU_MAJOR_ID_C1 == cpuid.family_id && MESON_CPU_CHIP_REVISION_A == cpuid.chip_rev)
            _erase_bootloader(SCPI_CMD_SDCARD_BOOT);
        else 
            set_boot_first_timeout(SCPI_CMD_SDCARD_BOOT);
        return 0;
    }

    return 0;
}

void optimus_clear_ovd_register(void)
{
    set_boot_first_timeout(SCPI_CMD_CLEAR_BOOT);
}

#ifdef CONFIG_CMD_MMC
//erase only emmc user part and skip bootloader/env
#define _MMC_ERASE_MASK_BOOTLOADER	(1<<0)
#define _MMC_ERASE_MASK_ENV       	(1<<1)
//bit1 protect env
int usb_burn_erase_data(unsigned char init_flag)
{
	int ret = 0, i;
	struct mmc *mmc;
	struct partitions *part_info = NULL;

	mmc = find_mmc_device(1);
	if (!mmc) {
		printf("[%s]  no mmc devices available\n", __func__);
		return -1;
	}

	mmc->has_init = 0;
	pinctrl_select_state(mmc->dev, "default");

	ret = mmc_init(mmc);
	if (ret != 0) {
		DWN_ERR("mmc init failed, ret %d\n", ret);
		return -__LINE__;
	}

	for (i = 0; i < 64; i++) {
		part_info = get_partition_info_by_num(i);
		if (!part_info)
			break;
		if (!strcmp("reserved", part_info->name)) {
			printf("Part:%s is skiped\n", part_info->name);
			continue;
		}
		if ((init_flag & _MMC_ERASE_MASK_BOOTLOADER) &&
				!strcmp("bootloader", part_info->name)) {
			printf("Part:%s not erased\n", part_info->name);
			continue;
		}
		if ((init_flag & _MMC_ERASE_MASK_ENV) &&
				!strcmp("env", part_info->name)) {
			printf("Part:%s not erased\n", part_info->name);
			continue;
		}
		if (part_info->size == 0) {
			printf("Part:%s size is 0\n", part_info->name);
			continue;
		}
		if (part_info->mask_flags & PART_PROTECT_FLAG) {
			printf("Part:%s is protected\n", part_info->name);
			continue;
		}
		ret = blk_derase(mmc_get_blk_desc(mmc),
				part_info->offset / BLOCK_SIZE,
				part_info->size / BLOCK_SIZE);
		printf("Erased: %s %s\n",
				part_info->name,
				(ret == 0) ? "OK" : "ERR");
	}
	return 0;
}
#endif// #ifdef CONFIG_CMD_MMC

