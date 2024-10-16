/* SPDX-License-Identifier: (GPL-2.0+ OR MIT) */
/*
 * board/amlogic/txl_t950_skt_v1/firmware/scp_task/dvfs_board.c
 *
 * Copyright (C) 2020 Amlogic, Inc. All rights reserved.
 *
 */

#include "pwm_ctrl.h"

#define CHIP_ADJUST 20
#define RIPPLE_ADJUST 30

struct scpi_opp_entry cpu_dvfs_tbl[] = {
	DVFS( 100000000,  900+CHIP_ADJUST+RIPPLE_ADJUST),
	DVFS( 250000000,  900+CHIP_ADJUST+RIPPLE_ADJUST),
	DVFS( 500000000,  900+CHIP_ADJUST+RIPPLE_ADJUST),
	DVFS( 667000000,  900+CHIP_ADJUST+RIPPLE_ADJUST),
	DVFS(1000000000,  910+CHIP_ADJUST+RIPPLE_ADJUST),
	DVFS(1200000000,  970+CHIP_ADJUST+RIPPLE_ADJUST),
	DVFS(1296000000, 1010+CHIP_ADJUST+RIPPLE_ADJUST),
	DVFS(1416000000, 1090+CHIP_ADJUST+RIPPLE_ADJUST),
};



#define P_PIN_MUX_REG3         (*((volatile unsigned *)(0xda834400 + (0x2f << 2))))
#define P_PIN_MUX_REG4         (*((volatile unsigned *)(0xda834400 + (0x30 << 2))))

#define P_PWM_MISC_REG_AB	(*((volatile unsigned *)(0xc1100000 + (0x2156 << 2))))
#define P_PWM_PWM_A		(*((volatile unsigned *)(0xc1100000 + (0x2154 << 2))))

/*
 * gpioao_9 pwm_ao_b is used to adjust VDD_EE
 */


enum pwm_id {
	pwm_a = 0,
};


void pwm_init(int id)
{
	/*
	 * TODO: support more pwm controllers, right now only support PWM_B
	 */
	unsigned int reg;
	reg = P_PWM_MISC_REG_AB;
	reg &= ~(0x7f << 8);
	reg |=  ((1 << 15) | (1 << 0));
	P_PWM_MISC_REG_AB = reg;
	/*
	 * default set to max voltage
	 */
	P_PWM_PWM_A = pwm_voltage_table[ARRAY_SIZE(pwm_voltage_table) - 1][0];
	reg  = P_PIN_MUX_REG3;
	reg &= ~(1 << 21);
	P_PIN_MUX_REG3 = reg;

	reg  = P_PIN_MUX_REG4;
	reg &= ~(1 << 26);		// clear PWM_VS
	reg |=  (1 << 17);		// enable PWM_A
	P_PIN_MUX_REG4 = reg;


	_udelay(200);
}

int dvfs_get_voltage(void)
{
	int i = 0;
	unsigned int reg_val;

	reg_val = P_PWM_PWM_A;
	for (i = 0; i < ARRAY_SIZE(pwm_voltage_table); i++) {
		if (pwm_voltage_table[i][0] == reg_val) {
			return i;
		}
	}
	if (i >= ARRAY_SIZE(pwm_voltage_table)) {
	    return -1;
	}
	return -1;
}

void set_dvfs(unsigned int domain, unsigned int index)
{
	int cur, to;
	static int init_flag = 0;

	if (!init_flag) {
		pwm_init(pwm_a);
		init_flag = 1;
	}
	cur = dvfs_get_voltage();
	for (to = 0; to < ARRAY_SIZE(pwm_voltage_table); to++) {
		if (pwm_voltage_table[to][1] >= cpu_dvfs_tbl[index].volt_mv) {
			break;
		}
	}
	if (to >= ARRAY_SIZE(pwm_voltage_table)) {
		to = ARRAY_SIZE(pwm_voltage_table) - 1;
	}
	if (cur < 0 || cur >=ARRAY_SIZE(pwm_voltage_table)) {
		P_PWM_PWM_A = pwm_voltage_table[to][0];
		_udelay(200);
		return ;
	}
	while (cur != to) {
		/*
		 * if target step is far away from current step, don't change
		 * voltage by one-step-done. You should change voltage step by
		 * step to make sure voltage output is stable
		 */
		if (cur < to) {
			if (cur < to - 3) {
				cur += 3;
			} else {
				cur = to;
			}
		} else {
			if (cur > to + 3) {
				cur -= 3;
			} else {
				cur = to;
			}
		}
		P_PWM_PWM_A = pwm_voltage_table[cur][0];
		_udelay(100);
	}
	_udelay(200);
}
void get_dvfs_info_board(unsigned int domain,
		unsigned char *info_out, unsigned int *size_out)
{
	unsigned int cnt;
	cnt = ARRAY_SIZE(cpu_dvfs_tbl);

	buf_opp.latency = 200;
	buf_opp.count = cnt;
	memset(&buf_opp.opp[0], 0,
	       MAX_DVFS_OPPS * sizeof(struct scpi_opp_entry));

	memcpy(&buf_opp.opp[0], cpu_dvfs_tbl ,
		cnt * sizeof(struct scpi_opp_entry));

	memcpy(info_out, &buf_opp, sizeof(struct scpi_opp));
	*size_out = sizeof(struct scpi_opp);
	return;
}
