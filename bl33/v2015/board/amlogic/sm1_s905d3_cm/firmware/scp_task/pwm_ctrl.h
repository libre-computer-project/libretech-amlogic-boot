/* SPDX-License-Identifier: (GPL-2.0+ OR MIT) */
/*
 * board/amlogic/g12a_u200_v1/firmware/scp_task/pwm_ctrl.h
 *
 * Copyright (C) 2020 Amlogic, Inc. All rights reserved.
 *
 */

#ifndef __PWM_CTRL_H__
#define __PWM_CTRL_H__

static int pwm_voltage_table_ee_new[][2] = {
	{ 0x120000,  700},
	{ 0x110001,  710},
	{ 0x100002,  720},
	{ 0x0f0003,  730},
	{ 0x0e0004,  740},
	{ 0x0d0005,  750},
	{ 0x0c0006,  760},
	{ 0x0b0007,  770},
	{ 0x0a0008,  780},
	{ 0x090009,  790},
	{ 0x08000a,  800},
	{ 0x07000b,  810},
	{ 0x06000c,  820},
	{ 0x05000d,  830},
	{ 0x04000e,  840},
	{ 0x03000f,  850},
	{ 0x020010,  860},
	{ 0x010011,  870},
	{ 0x000012,  880},
};
#endif //__PWM_CTRL_H__
