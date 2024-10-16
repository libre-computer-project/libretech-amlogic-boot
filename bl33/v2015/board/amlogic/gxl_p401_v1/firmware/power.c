/* SPDX-License-Identifier: (GPL-2.0+ OR MIT) */
/*
 * board/amlogic/gxl_p401_v1/firmware/power.c
 *
 * Copyright (C) 2020 Amlogic, Inc. All rights reserved.
 *
 */

#include "config.h"
#include <serial.h>
//#include <stdio.h>

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

static int pwm_voltage_table[][2] = {
	{ 0x1c0000,  860},
	{ 0x1b0001,  870},
	{ 0x1a0002,  880},
	{ 0x190003,  890},
	{ 0x180004,  900},
	{ 0x170005,  910},
	{ 0x160006,  920},
	{ 0x150007,  930},
	{ 0x140008,  940},
	{ 0x130009,  950},
	{ 0x12000a,  960},
	{ 0x11000b,  970},
	{ 0x10000c,  980},
	{ 0x0f000d,  990},
	{ 0x0e000e, 1000},
	{ 0x0d000f, 1010},
	{ 0x0c0010, 1020},
	{ 0x0b0011, 1030},
	{ 0x0a0012, 1040},
	{ 0x090013, 1050},
	{ 0x080014, 1060},
	{ 0x070015, 1070},
	{ 0x060016, 1080},
	{ 0x050017, 1090},
	{ 0x040018, 1100},
	{ 0x030019, 1110},
	{ 0x02001a, 1120},
	{ 0x01001b, 1130},
	{ 0x00001c, 1140}
};
#define P_PIN_MUX_REG1         (*((volatile unsigned *)(0xda834400 + (0x2d << 2))))
#define P_PIN_MUX_REG2         (*((volatile unsigned *)(0xda834400 + (0x2e << 2))))
#define P_PIN_MUX_REG3		(*((volatile unsigned *)(0xda834400 + (0x2f << 2))))
#define P_PIN_MUX_REG7		(*((volatile unsigned *)(0xda834400 + (0x33 << 2))))
#define P_PIN_MUX_REG8		(*((volatile unsigned *)(0xda834400 + (0x34 << 2))))
#define P_PIN_MUX_AO_REG	(*((volatile unsigned *)(0xc8100000 + (0x5 << 2))))

#define P_PWM_MISC_REG_AB	(*((volatile unsigned *)(0xc1100000 + (0x2156 << 2))))
#define P_PWM_PWM_B		(*((volatile unsigned *)(0xc1100000 + (0x2155 << 2))))
#define P_PWM_MISC_REG_CD	(*((volatile unsigned *)(0xc1100000 + (0x2192 << 2))))
#define P_PWM_PWM_D		(*((volatile unsigned *)(0xc1100000 + (0x2191 << 2))))

#define P_PWM_MISC_REG_EF	(*((volatile unsigned *)(0xc1100000 + (0x21b2 << 2))))
#define P_PWM_PWM_F		(*((volatile unsigned *)(0xc1100000 + (0x21b1 << 2))))

#undef P_AO_PWM_MISC_REG_AB
#undef P_AO_PWM_PWM_A
#define P_AO_PWM_MISC_REG_AB	(*((volatile unsigned *)(0xc8100400 + (0x56 << 2))))
#define P_AO_PWM_PWM_A		(*((volatile unsigned *)(0xc8100400 + (0x54 << 2))))

#define P_EE_TIMER_E		(*((volatile unsigned *)(0xc1100000 + (0x2662 << 2))))

enum pwm_id {
    pwm_a = 0,
    pwm_b,
    pwm_c,
    pwm_d,
    pwm_e,
    pwm_f,
    pwm_ao_a,
};

unsigned int _get_time(void)
{
	return P_EE_TIMER_E;
}

void _udelay_(unsigned int us)
{
	unsigned int t0 = _get_time();

	while (_get_time() - t0 <= us)
		;
}

void pwm_init(int id)
{
	unsigned int reg;

	/*
	 * TODO: support more pwm controllers, right now only support
	 * PWM_B, PWM_D
	 */

	switch (id) {
	case pwm_b:
		reg = P_PWM_MISC_REG_AB;
		reg &= ~(0x7f << 16);
		reg |=  ((1 << 23) | (1 << 1));
		P_PWM_MISC_REG_AB = reg;
		/*
		 * default set to max voltage
		 */
		P_PWM_PWM_B = pwm_voltage_table[ARRAY_SIZE(pwm_voltage_table) - 1][0];
		reg  = P_PIN_MUX_REG1;
		reg &= ~(1 << 10);
		P_PIN_MUX_REG1 = reg;

		reg  = P_PIN_MUX_REG2;
		reg &= ~(1 << 5);
		reg |=  (1 << 11);		// enable PWM_B
		P_PIN_MUX_REG2 = reg;
		break;

	case pwm_ao_a:
		reg = P_AO_PWM_MISC_REG_AB;
		reg &= ~(0x7f << 8);
		reg |=  ((1 << 15) | (1 << 0));
		P_AO_PWM_MISC_REG_AB = reg;
		/*
		 * default set to max voltage
		 */
		P_AO_PWM_PWM_A = pwm_voltage_table[ARRAY_SIZE(pwm_voltage_table) - 1][0];
		reg  = P_PIN_MUX_AO_REG;
		reg &= ~(1 << 9);
		reg &= ~(1 << 7);
		P_PIN_MUX_AO_REG = reg;

		reg  = P_PIN_MUX_AO_REG;
		reg |=  (1 << 22);		// enable PWM_AO_A
		P_PIN_MUX_AO_REG = reg;
		break;

	case pwm_f:
		reg = P_PWM_MISC_REG_EF;
		reg &= ~(0x7f << 16);
		reg |=  ((1 << 23) | (1 << 1));
		P_PWM_MISC_REG_EF = reg;
		/*
		 * default set to max voltage
		 */
		P_PWM_PWM_F = pwm_voltage_table[ARRAY_SIZE(pwm_voltage_table) - 1][0];
		reg  = P_PIN_MUX_REG8;
		reg &= ~(1 << 29);
		P_PIN_MUX_REG8 = reg;

		reg  = P_PIN_MUX_REG8;
		reg |=  (1 << 30);		// enable PWM_F
		P_PIN_MUX_REG8 = reg;
		break;

	default:
		break;
	}

	_udelay_(200);
}

void pwm_set_voltage(unsigned int id, unsigned int voltage)
{
	int to;

	for (to = 0; to < ARRAY_SIZE(pwm_voltage_table); to++) {
		if (pwm_voltage_table[to][1] >= voltage) {
			break;
		}
	}
	if (to >= ARRAY_SIZE(pwm_voltage_table)) {
		to = ARRAY_SIZE(pwm_voltage_table) - 1;
	}
	switch (id) {
	case pwm_b:
		P_PWM_PWM_B = pwm_voltage_table[to][0];
		break;
	case pwm_f:
		P_PWM_PWM_F = pwm_voltage_table[to][0];
		break;
	case pwm_ao_a:
		P_AO_PWM_PWM_A = pwm_voltage_table[to][0];
		break;
	default:
		break;
	}
	_udelay_(200);
}

void power_init(int mode)
{
	pwm_init(pwm_b);
	pwm_init(pwm_ao_a);
	pwm_init(pwm_f);
	serial_puts("set vdd cpu_a to ");
	serial_put_dec(CONFIG_VCCKA_INIT_VOLTAGE);
	serial_puts(" mv\n");
	pwm_set_voltage(pwm_ao_a, CONFIG_VCCKA_INIT_VOLTAGE);

	serial_puts("set vdd cpu_b to ");
	serial_put_dec(CONFIG_VCCKB_INIT_VOLTAGE);
	serial_puts(" mv\n");
	pwm_set_voltage(pwm_f, CONFIG_VCCKB_INIT_VOLTAGE);

	serial_puts("set vddee to ");
	serial_put_dec(CONFIG_VDDEE_INIT_VOLTAGE);
	serial_puts(" mv\n");
	pwm_set_voltage(pwm_b, CONFIG_VDDEE_INIT_VOLTAGE);
}
