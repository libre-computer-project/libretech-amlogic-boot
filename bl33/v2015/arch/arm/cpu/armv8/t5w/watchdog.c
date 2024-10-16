/* SPDX-License-Identifier: (GPL-2.0+ OR MIT) */
/*
 * arch/arm/cpu/armv8/t5d/watchdog.c
 *
 * Copyright (C) 2020 Amlogic, Inc. All rights reserved.
 *
 */

#include <common.h>
#include <asm/types.h>
#include <asm/arch/romboot.h>
#include <asm/arch/watchdog.h>
#include <asm/arch/io.h>
#include <asm/arch/timer.h>

void watchdog_init(uint32_t msec)
{
	// src: 24MHz
	// div: 24000 for 1ms
	// reset ao-22 and ee-21
	*P_WATCHDOG_CNTL = (1<<24)|(1<<25)|(1<<22)|(1<<21)|(24000-1);

	// set timeout
	*P_WATCHDOG_TCNT = msec;
	*P_WATCHDOG_RESET = 0;

	// enable
	*P_WATCHDOG_CNTL |= (1<<18);
}

void watchdog_reset(void)
{
	*P_WATCHDOG_RESET = 0;
}

void watchdog_disable(void)
{
	// turn off internal counter and disable
	*P_WATCHDOG_CNTL &= ~((1<<18)|(1<<25));
}


/*
 *GPIOE_0   VDDEE_PWM
 *GPIOE_1   VDDCPU_PWM
 * */
void set_pwm_to_input(void)
{
	unsigned int val;

	val = readl(AO_RTI_PINMUX_REG1);
	val &= ~(0xff << 16);
	writel(val, AO_RTI_PINMUX_REG1);/* clear pinmux */
	val = readl(AO_GPIO_O_EN_N);
	val &= ~(0x3 << 16);
	val |= 0x3 << 16;
	writel(val, AO_GPIO_O_EN_N);/* set input mode */
	val = readl(AO_RTI_PULL_UP_EN_REG);
	val &= ~(0x3 << 16);
	writel(val, AO_RTI_PULL_UP_EN_REG);/* disable pull up/down */
}

void reset_system(void)
{
	int i;

	set_pwm_to_input();
#ifdef CONFIG_USB_DEVICE_V2
	*P_RESET1_REGISTER |= (1<<17);
	mdelay(200);
#endif
	_udelay(10000); //wait print
	while (1) {
		writel( 0x3 | (1 << 21) // sys reset en
					| (1 << 23) // interrupt en
					| (1 << 24) // clk en
					| (1 << 25) // clk div en
					| (1 << 26) // sys reset now
			, P_WATCHDOG_CNTL);
		writel(0, P_WATCHDOG_RESET);

		writel(readl(P_WATCHDOG_CNTL) | (1<<18), // watchdog en
			P_WATCHDOG_CNTL);
		for (i=0; i<100; i++)
			readl(P_WATCHDOG_CNTL);/*Deceive gcc for waiting some cycles */
	}
}

/* uboot reset interface */
void reset_cpu(unsigned long flag){
	reset_system();
}

#ifdef CONFIG_AML_UASAN
int is_register(unsigned long addr)
{
	/*
	 * skip asan range check for registers address,
	 * see mem_map.xls of this soc
	 */
	if (addr >= 0xF5800000UL && addr < 0xFFFFFFFFUL)
		return 1;
	else
		return 0;
}
#endif
