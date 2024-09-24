/* SPDX-License-Identifier: (GPL-2.0+ OR MIT) */
/*
 * arch/arm/cpu/armv8/axg/bl31_apis.c
 *
 * Copyright (C) 2020 Amlogic, Inc. All rights reserved.
 *
 */

/*
 * Trustzone API
 */

#include <asm/arch/io.h>
#include <asm/arch/efuse.h>
#include <asm/cache.h>
#include <asm/arch/bl31_apis.h>
#include <asm/cpu_id.h>
#include <asm/arch/secure_apb.h>
#include <linux/arm-smccc.h>

static long sharemem_input_base;
static long sharemem_output_base;

long get_sharemem_info(unsigned long function_id)
{
	struct arm_smccc_res res;

	arm_smccc_smc(function_id, 0, 0, 0, 0, 0, 0, 0, &res);

	return res.a0;
}

int32_t set_boot_params(const keymaster_boot_params *boot_params)
{
	/* Fake function for the reason that set_boot_params is not
	 * supported for this platform */
	return -1;
}

#ifdef CONFIG_EFUSE
#ifdef CONFIG_EFUSE_OBJ_API
uint32_t meson_efuse_obj_read(
	uint32_t obj_id,
	uint8_t *buff,
	uint32_t *size)
{
	uint32_t rc = EFUSE_OBJ_ERR_UNKNOWN;
	uint32_t len = 0;
	struct arm_smccc_res res;

	if (!sharemem_input_base)
		sharemem_input_base =
			get_sharemem_info(GET_SHARE_MEM_INPUT_BASE);

	if (!sharemem_output_base)
		sharemem_output_base =
			get_sharemem_info(GET_SHARE_MEM_OUTPUT_BASE);

	arm_smccc_smc(EFUSE_OBJ_READ, obj_id, *size, 0, 0, 0, 0, 0, &res);

	rc = res.a0;
	len = res.a1;

	if (rc == EFUSE_OBJ_SUCCESS) {
		if (*size >= len) {
			memcpy(buff, (const void *)sharemem_output_base, len);
			*size = len;
		}
		else
			rc = EFUSE_OBJ_ERR_SIZE;
	}

	return rc;
}

uint32_t meson_efuse_obj_write(
	uint32_t obj_id,
	uint8_t *buff,
	uint32_t size)
{
	uint32_t rc = EFUSE_OBJ_ERR_UNKNOWN;
	struct arm_smccc_res res;

	if (!sharemem_input_base)
		sharemem_input_base =
			get_sharemem_info(GET_SHARE_MEM_INPUT_BASE);

	if (!sharemem_output_base)
		sharemem_output_base =
			get_sharemem_info(GET_SHARE_MEM_OUTPUT_BASE);

	arm_smccc_smc(EFUSE_OBJ_WRITE, obj_id, size, 0, 0, 0, 0, 0, &res);

	rc = res.a0;
	return rc;
}
#endif /* CONFIG_EFUSE_OBJ_API */

int32_t meson_trustzone_efuse(struct efuse_hal_api_arg *arg)
{
	int ret;
	unsigned cmd, offset, size;
	unsigned long *retcnt = (unsigned long *)(arg->retcnt_phy);
	struct arm_smccc_res res;

	if (!sharemem_input_base)
		sharemem_input_base =
			get_sharemem_info(GET_SHARE_MEM_INPUT_BASE);
	if (!sharemem_output_base)
		sharemem_output_base =
			get_sharemem_info(GET_SHARE_MEM_OUTPUT_BASE);

	if (arg->cmd == EFUSE_HAL_API_READ)
		cmd = EFUSE_READ;
	else if (arg->cmd == EFUSE_HAL_API_WRITE)
		cmd = EFUSE_WRITE;
	else
		cmd = EFUSE_WRITE_PATTERN;
	offset = arg->offset;
	size = arg->size;

	arm_smccc_smc(cmd, offset, size, 0, 0, 0, 0, 0, &res);

	ret = res.a0;
	*retcnt = res.a0;

	if ((arg->cmd == EFUSE_HAL_API_READ) && (ret != 0))
		memcpy((void *)arg->buffer_phy,
		       (const void *)sharemem_output_base, ret);

	if (!ret)
		return -1;
	else
		return 0;
}

int32_t meson_trustzone_efuse_get_max(struct efuse_hal_api_arg *arg)
{
	int32_t ret;
	int cmd = -1;
	struct arm_smccc_res res;

	if (arg->cmd == EFUSE_HAL_API_USER_MAX)
		cmd = EFUSE_USER_MAX;

	arm_smccc_smc(cmd, 0, 0, 0, 0, 0, 0, 0, &res);
	ret = res.a0;

	if (!ret)
		return -1;
	else
		return ret;
}

ssize_t meson_trustzone_efuse_writepattern(const char *buf, size_t count)
{
	struct efuse_hal_api_arg arg;
	unsigned long retcnt;

	if (count != EFUSE_BYTES)
		return 0;	/* Past EOF */

	arg.cmd = EFUSE_HAL_API_WRITE_PATTERN;
	arg.offset = 0;
	arg.size = count;
	arg.buffer_phy = (unsigned long)buf;
	arg.retcnt_phy = (unsigned long)&retcnt;
	int ret;
	ret = meson_trustzone_efuse(&arg);
	return ret;
}
#endif

uint64_t meson_trustzone_efuse_check(unsigned char *addr)
{
	struct sram_hal_api_arg arg = {};
	struct arm_smccc_res res;

	arg.cmd = SRAM_HAL_API_CHECK_EFUSE;
	arg.req_len = 0x1000000;
	arg.res_len = 0;
	arg.req_phy_addr = (unsigned long)addr;
	arg.res_phy_addr = (unsigned long)NULL;

	arm_smccc_smc(CALL_TRUSTZONE_HAL_API, TRUSTZONE_HAL_API_SRAM,
					(unsigned long)(&arg), 0, 0, 0, 0, 0, &res);
	return res.a0;
}

void debug_efuse_cmd(unsigned long cmd)
{
	struct arm_smccc_res res;

	arm_smccc_smc(cmd, 0, 0, 0, 0, 0, 0, 0, &res);
}

void bl31_debug_efuse_write_pattern(const char *buf)
{
	if (!sharemem_input_base)
		sharemem_input_base =
			get_sharemem_info(GET_SHARE_MEM_INPUT_BASE);
	memcpy((void *)sharemem_input_base, (const void *)buf, 512);

	debug_efuse_cmd(DEBUG_EFUSE_WRITE_PATTERN);
}

void bl31_debug_efuse_read_pattern(char *buf)
{
	if (!sharemem_output_base)
		sharemem_output_base =
			get_sharemem_info(GET_SHARE_MEM_OUTPUT_BASE);
	debug_efuse_cmd(DEBUG_EFUSE_READ_PATTERN);

	memcpy((void *)buf, (const void *)sharemem_output_base, 512);
}

void aml_set_jtag_state(unsigned state, unsigned select)
{
	uint64_t command;
	struct arm_smccc_res res;

	if (state == JTAG_STATE_ON)
		command = JTAG_ON;
	else
		command = JTAG_OFF;
	arm_smccc_smc(command, select, 0, 0, 0, 0, 0, 0, &res);
}

unsigned aml_get_reboot_reason(void)
{
	unsigned int reason;
	struct arm_smccc_res res;

	arm_smccc_smc(GET_REBOOT_REASON, 0, 0, 0, 0, 0, 0, 0, &res);
	reason = (unsigned int)(res.a0 & 0xffffffff);
	return reason;
}

unsigned aml_reboot(uint64_t function_id, uint64_t arg0, uint64_t arg1, uint64_t arg2)
{
	struct arm_smccc_res res;

	arm_smccc_smc(function_id, arg0, arg1, arg2, 0, 0, 0, 0, &res);
	return (unsigned int)res.a0;
}

void aml_set_reboot_reason(uint64_t function_id, uint64_t arg0, uint64_t arg1, uint64_t arg2)
{
	struct arm_smccc_res res;

	arm_smccc_smc(function_id, arg0, arg1, arg2, 0, 0, 0, 0, &res);
}

unsigned long aml_sec_boot_check(unsigned long nType,
	unsigned long pBuffer,
	unsigned long nLength,
	unsigned long nOption)
{
	uint64_t ret = 1;
	struct arm_smccc_res res;

//#define AML_SECURE_LOG_TE

#if defined(AML_SECURE_LOG_TE)
	#define AML_GET_TE(a) do{a = *((volatile unsigned int*)0xc1109988);}while(0);
	unsigned nT1,nT2,nT3;
#else
	#define AML_GET_TE(...)
#endif

	AML_GET_TE(nT1);

	arm_smccc_smc(AML_DATA_PROCESS, nType, pBuffer, nLength, nOption, 0, 0, 0, &res);
	ret = res.a0;

	AML_GET_TE(nT2);;

	flush_dcache_range((unsigned long )pBuffer, (unsigned long )pBuffer+nLength);

	AML_GET_TE(nT3);

#if defined(AML_SECURE_LOG_TE)
	printf("aml log : dec use %d(us) , flush cache used %d(us)\n",
		nT2 - nT1, nT3 - nT2);
#endif

	return ret;
}

void set_usb_boot_function(unsigned long command)
{
	struct arm_smccc_res res;

	arm_smccc_smc(SET_USB_BOOT_FUNC, command, 0, 0, 0, 0, 0, 0, &res);
}

void aml_system_off(void)
{
	/* TODO: Add poweroff capability */
	aml_reboot(0x82000042, 1, 0, 0);
	aml_reboot(0x84000008, 0, 0, 0);
}

int __get_chip_id(unsigned char *buff, unsigned int size)
{
	struct arm_smccc_res res;

	if (buff == NULL || size < 16)
		return -1;

	if (!sharemem_output_base)
		sharemem_output_base =
			get_sharemem_info(GET_SHARE_MEM_OUTPUT_BASE);

	if (sharemem_output_base) {
		arm_smccc_smc(GET_CHIP_ID, 2, 0, 0, 0, 0, 0, 0, &res);

		if (res.a0 == 0) {
			int version = *((unsigned int *)sharemem_output_base);

			if (version == 2) {
				memcpy(buff, (void *)sharemem_output_base + 4, 16);
			}
			else {
				/**
				 * Legacy 12-byte chip ID read out, transform data
				 * to expected order format.
				 */
				uint32_t chip_info = readl(P_AO_SEC_SD_CFG8);
				uint8_t *ch;
				int i;

				((uint32_t *)buff)[0] =
					((chip_info & 0xff000000)	|	// Family ID
					((chip_info << 8) & 0xff0000)	|	// Chip Revision
					((chip_info >> 8) & 0xff00));		// Package ID

				((uint32_t *)buff)[0] = htonl(((uint32_t *)buff)[0]);

				/* Transform into expected order for display */
				ch = (uint8_t *)(sharemem_output_base + 4);
				for (i = 0; i < 12; i++)
					buff[i + 4] = ch[11 - i];
			}

			return 0;
		}
	}

	return -1;
}
