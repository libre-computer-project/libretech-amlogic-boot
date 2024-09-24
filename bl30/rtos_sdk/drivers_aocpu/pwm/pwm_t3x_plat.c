/*
 * Copyright (c) 2021-2022 Amlogic, Inc. All rights reserved.
 *
 * SPDX-License-Identifier: MIT
 */

#include "FreeRTOS.h"
#include <common.h>
#include <pwm.h>

struct xPwmMesonChip meson_pwm_chip[] = {
	{ PWM_AB, PWMAB_PWM_A, 0, CLKCTRL_PWM_CLK_AB_CTRL },
	{ PWM_CD, PWMCD_PWM_A, 0, CLKCTRL_PWM_CLK_CD_CTRL },
	{ PWM_EF, PWMEF_PWM_A, 0, CLKCTRL_PWM_CLK_EF_CTRL },
	{ PWM_GH, PWMGH_PWM_A, 0, CLKCTRL_PWM_CLK_GH_CTRL },
	{ PWM_IJ, PWMIJ_PWM_A, 0, CLKCTRL_PWM_CLK_IJ_CTRL },
};

/* VDDEE voltage table  volt must ascending */
struct xPwmMesonVoltage vddee_table[] = {
	{ 720, 0x120000}, { 730, 0x110001}, { 740, 0x100002}, { 750, 0x0f0003},
	{ 760, 0x0e0004}, { 770, 0x0d0005}, { 780, 0x0c0006}, { 790, 0x0b0007},
	{ 800, 0x0a0008}, { 810, 0x090009}, { 820, 0x08000a}, { 830, 0x07000b},
	{ 840, 0x06000c}, { 850, 0x05000d}, { 860, 0x04000e}, { 870, 0x03000f},
	{ 880, 0x020010}, { 890, 0x010011}, { 900, 0x000012},

};

/* VDDCPU voltage table  volt must ascending */
struct xPwmMesonVoltage vddcpu_table[] = {
	{ 690, 0x00240000 },  { 700, 0x00220000 },  { 710, 0x00210001 },  { 720, 0x00200002 },
	{ 730, 0x001f0003 },  { 740, 0x001e0004 },  { 750, 0x001d0005 },  { 760, 0x001c0006 },
	{ 770, 0x001b0007 },  { 780, 0x001a0008 },  { 790, 0x00190009 },  { 800, 0x0018000a },
	{ 810, 0x0017000b },  { 820, 0x0016000c },  { 830, 0x0015000d },  { 840, 0x0014000e },
	{ 850, 0x0013000f },  { 860, 0x00120010 },  { 870, 0x00110011 },  { 880, 0x00100012 },
	{ 890, 0x000f0013 },  { 900, 0x000e0014 },  { 910, 0x000d0015 },  { 920, 0x000c0016 },
	{ 930, 0x000b0017 },  { 940, 0x000a0018 },  { 950, 0x00090019 },  { 960, 0x0008001a },
	{ 970, 0x0007001b },  { 980, 0x0006001c },  { 990, 0x0005001d },  { 1000, 0x0004001e },
	{ 1010, 0x0003001f }, { 1020, 0x00020020 }, { 1030, 0x00010021 }, { 1040, 0x00000022 },
	{ 1050, 0x00000024 },
};

/*
 * todo: need processing here vddee pwmh vddcpu pwmj
 * Different boards may use different pwm channels
 */
uint32_t prvMesonVoltToPwmchip(enum pwm_voltage_id voltage_id)
{
	switch (voltage_id) {
	case VDDEE_VOLT:
		return PWM_AB;

	case VDDCPU_VOLT:
		return PWM_AB;

	default:
		break;
	}
	return PWM_MUX;
}

/*
 * todo: need processing here
 * Different boards may use different pwm channels
 */
uint32_t prvMesonVoltToPwmchannel(enum pwm_voltage_id voltage_id)
{
	switch (voltage_id) {
	case VDDEE_VOLT:
		return MESON_PWM_0;

	case VDDCPU_VOLT:
		return MESON_PWM_1;

	default:
		break;
	}
	return MESON_PWM_2;
}

struct xPwmMesonVoltage *vPwmMesonGetVoltTable(uint32_t voltage_id)
{
	switch (voltage_id) {
	case VDDEE_VOLT:
		return vddee_table;

	case VDDCPU_VOLT:
		return vddcpu_table;

	default:
		break;
	}
	return NULL;
}

uint32_t vPwmMesonGetVoltTableSize(uint32_t voltage_id)
{
	switch (voltage_id) {
	case VDDEE_VOLT:
		return sizeof(vddee_table) / sizeof(struct xPwmMesonVoltage);

	case VDDCPU_VOLT:
		return sizeof(vddcpu_table) / sizeof(struct xPwmMesonVoltage);

	default:
		break;
	}
	return 0;
}

struct xPwmMesonChip *prvIdToPwmChip(uint32_t chip_id)
{
	if (chip_id >= PWM_MUX) {
		printf("pwm chip id is invail!\n");
		return NULL;
	}

	return meson_pwm_chip + chip_id;
}
