/* SPDX-License-Identifier: (GPL-2.0+ OR MIT) */
/*
 * board/amlogic/tm2_t962x3_ab301_v1/firmware/scp_task/pwm_ctrl.h
 *
 * Copyright (C) 2020 Amlogic, Inc. All rights reserved.
 *
 */

#ifndef __PWM_CTRL_H__
#define __PWM_CTRL_H__

static int pwm_voltage_table_ee[][2] = {
	{ 0x00120000,  740},
	{ 0x00110001,  750},
	{ 0x00100002,  760},
	{ 0x000f0003,  770},
	{ 0x000e0004,  780},
	{ 0x000d0005,  790},
	{ 0x000c0006,  800},
	{ 0x000b0007,  810},
	{ 0x000a0008,  820},
	{ 0x00090009,  830},
	{ 0x0008000a,  840},
	{ 0x0007000b,  850},
	{ 0x0006000c,  860},
	{ 0x0005000d,  870},
	{ 0x0004000e,  880},
	{ 0x0003000f,  890},
	{ 0x00020010,  900},
	{ 0x00010011,  910},
	{ 0x00000012,  920}
};

#endif //__PWM_CTRL_H__
