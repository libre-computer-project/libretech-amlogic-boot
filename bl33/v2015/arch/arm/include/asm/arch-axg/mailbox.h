/* SPDX-License-Identifier: (GPL-2.0+ OR MIT) */
/*
 * arch/arm/include/asm/arch-axg/mailbox.h
 *
 * Copyright (C) 2020 Amlogic, Inc. All rights reserved.
 *
 */


#ifndef __GXBB_MAILBOX_H_
#define __GXBB_MAILBOX_H_

#define SCPI_CMD_SENSOR_VALUE 0x1C
#define SCPI_CMD_SET_USR_DATA 0x20
#define SCPI_CMD_WAKEUP_REASON_GET 0x30
#define SCPI_CMD_OPEN_SCP_LOG 0xC4
#define SCPI_CMD_THERMAL_CALIB 0xC5

#define LOW_PRIORITY	0
#define HIGH_PRIORITY 1

#define P_SHARE_SRAM_BASE    0xfffc0000
#define MHU_HIGH_SCP_TO_AP_PAYLOAD		0x13400
#define MHU_HIGH_AP_TO_SCP_PAYLOAD		0x13600
#define MHU_LOW_SCP_TO_AP_PAYLOAD		0x13000
#define MHU_LOW_AP_TO_SCP_PAYLOAD		0x13200

enum scpi_client_id {
	SCPI_CL_NONE,
	SCPI_CL_CLOCKS,
	SCPI_CL_DVFS,
	SCPI_CL_POWER,
	SCPI_CL_THERMAL,
	SCPI_CL_REMOTE,
	SCPI_CL_LED_TIMER,
	SCPI_MAX = 0xff,
};

enum scpi_error_codes {
	SCPI_SUCCESS = 0, /* Success */
	SCPI_ERR_PARAM = 1, /* Invalid parameter(s) */
	SCPI_ERR_ALIGN = 2, /* Invalid alignment */
	SCPI_ERR_SIZE = 3, /* Invalid size */
	SCPI_ERR_HANDLER = 4, /* Invalid handler/callback */
	SCPI_ERR_ACCESS = 5, /* Invalid access/permission denied */
	SCPI_ERR_RANGE = 6, /* Value out of range */
	SCPI_ERR_TIMEOUT = 7, /* Timeout has occurred */
	SCPI_ERR_NOMEM = 8, /* Invalid memory area or pointer */
	SCPI_ERR_PWRSTATE = 9, /* Invalid power state */
	SCPI_ERR_SUPPORT = 10, /* Not supported or disabled */
	SCPI_ERR_DEVICE = 11, /* Device error */
	SCPI_ERR_MAX
};

void open_scp_log(unsigned int channel);
int thermal_calibration(unsigned int type, unsigned int data);
int thermal_get_value(unsigned int sensor_id, unsigned int *value);
int send_usr_data(unsigned int client_id, unsigned int *val, unsigned int size);
int wakeup_reason_get_value(unsigned int *reason);

 #endif
