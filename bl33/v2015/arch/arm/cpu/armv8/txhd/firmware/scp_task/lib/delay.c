/* SPDX-License-Identifier: (GPL-2.0+ OR MIT) */
/*
 * arch/arm/cpu/armv8/txhd/firmware/scp_task/lib/delay.c
 *
 * Copyright (C) 2020 Amlogic, Inc. All rights reserved.
 *
 */

#define P_EE_TIMER_E		(*((volatile unsigned *)(0xffd00000 + (0x3c62 << 2))))
#define P_AO_TIMER_E		(*((volatile unsigned *)(0xff800000 + (0x15 << 2))))
#define P_EE_TIMER_CTRL		(*((volatile unsigned *)(0xff800000 + (0x13 << 2))))
unsigned int get_time(void)
{
	return P_AO_TIMER_E;
}

void _udelay(unsigned int us)
{
	unsigned int t0 = get_time();
	P_EE_TIMER_CTRL |= (0x1 << 4);

	while (get_time() - t0 <= us)
		;
}

