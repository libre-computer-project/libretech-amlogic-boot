/* SPDX-License-Identifier: (GPL-2.0+ OR MIT) */
/*
 * arch/arm/cpu/armv8/tl1/firmware/scp_task/lib/delay.c
 *
 * Copyright (C) 2020 Amlogic, Inc. All rights reserved.
 *
 */

#define P_AO_TIMER_E		(*((volatile unsigned *)(0xff800000 + (0xf9 << 2))))
unsigned int get_time(void)
{
	return P_AO_TIMER_E;
}

void _udelay(unsigned int us)
{
	unsigned int t0 = get_time();

	while (get_time() - t0 <= us)
		;
}

