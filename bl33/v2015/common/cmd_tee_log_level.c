/* SPDX-License-Identifier: (GPL-2.0+ OR MIT) */
/*
 * common/cmd_tee_log_level.c
 *
 * Copyright (C) 2020 Amlogic, Inc. All rights reserved.
 *
 */

#include <common.h>
#include <linux/arm-smccc.h>

#define FUNCID_UPDATE_TEE_TRACE_LEVEL        0xb2000016

static int atoi(const char* str)
{
	int ret = 0;

	if (!str)
		return ret;

	while ( *str != '\0') {
		if (('0' <= *str) && (*str <= '9')) {
			ret = ret * 10 + (*str++ - '0');
		} else {
			ret = 0;
			break;
		}
	}

	return ret;
}

static uint32_t update_log_level(uint32_t log_level)
{
	struct arm_smccc_res res;

	arm_smccc_smc(FUNCID_UPDATE_TEE_TRACE_LEVEL, log_level, 0, 0, 0, 0, 0, 0, &res);
	return res.a0;
}

int exec(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	uint32_t log_level = 0;
	uint32_t updated_log_level = 0;

	if (argc != 2) {
		printf("BL33: parameter error,\n"
				"Usage:\ntee_log_level [log_level],\n"
				"the min log level is 1, and the max log level is related to"
				" Secure OS version\n");
		return 0;
	}

	log_level = atoi(argv[1]);
	updated_log_level = update_log_level(log_level);
	if (log_level < updated_log_level) {
		printf("BL33: the min log level is %d\n", updated_log_level);
	} else if (log_level > updated_log_level) {
		printf("BL33: the max log level is %d\n", updated_log_level);
	}
	printf("BL33: the updated log level is %d\n", updated_log_level);

	return 0;
}

/* -------------------------------------------------------------------- */
U_BOOT_CMD(
		tee_log_level, CONFIG_SYS_MAXARGS, 0, exec,
		"update tee log level",
		"[log_level],\nthe min log level is 1, and the max log level is"
		" related to Secure OS version"
);
