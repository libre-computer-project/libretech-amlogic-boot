/* SPDX-License-Identifier: (GPL-2.0+ OR MIT) */
/*
 * board/amlogic/g12b_w400_v1/firmware/scp_task/pwr_ctrl.c
 *
 * Copyright (C) 2020 Amlogic, Inc. All rights reserved.
 *
 */

#include <gpio.h>
#include "pwm_ctrl.h"
#ifdef CONFIG_CEC_WAKEUP
#include <hdmi_cec_arc.h>
#endif
#include <gpio.c>

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

unsigned char gpio_groups[] = {};

static void set_vddee_voltage(unsigned int target_voltage)
{
	unsigned int to, pwm_size = 0;
	static int (*pwm_voltage_ee)[2];

	/* BOOT_9 = H use PWM_CFG0(0.67v-0.97v), =L use PWM_CFG1(0.69v-0.89v) */
	/*set BOOT_9 input mode*/
	writel((readl(PREG_PAD_GPIO0_EN_N) | 0x200), PREG_PAD_GPIO0_EN_N);
	if (((readl(PREG_PAD_GPIO0_EN_N) & 0x200 ) == 0x200) &&
			((readl(PREG_PAD_GPIO0_I) & 0x200 ) == 0x0)) {
		uart_puts("use vddee new table!\n");
		pwm_voltage_ee = pwm_voltage_table_ee_new;
		pwm_size = ARRAY_SIZE(pwm_voltage_table_ee_new);
	} else {
		uart_puts("use vddee table!\n");
		pwm_voltage_ee = pwm_voltage_table_ee;
		pwm_size = ARRAY_SIZE(pwm_voltage_table_ee);
	}

	for (to = 0; to < pwm_size; to++) {
		if (pwm_voltage_ee[to][1] >= target_voltage) {
			break;
		}
	}

	if (to >= pwm_size) {
		to = pwm_size - 1;
	}

	writel(*(*(pwm_voltage_ee + to)), AO_PWM_PWM_B);
}

static void power_off_at_24M(unsigned int suspend_from)
{
	if (suspend_from == SYS_POWEROFF)
		uart_puts("powering off\n");
	else
		uart_puts("suspending\n");

	gpio_state_backup(gpio_groups, ARRAY_SIZE(gpio_groups));

	/* GPIOAO_10 */
	uart_puts("regulator: cpu_a");
	writel(readl(AO_GPIO_O) & (~(1 << 10)), AO_GPIO_O);
	writel(readl(AO_GPIO_O_EN_N) & (~(1 << 10)), AO_GPIO_O_EN_N);
	writel(readl(AO_RTI_PIN_MUX_REG1) & (~(0xf << 8)), AO_RTI_PIN_MUX_REG);
	uart_puts(" off\n");

	/* GPIOAO_4 */
	uart_puts("regulator: cpu_b");
	writel(readl(AO_GPIO_O) & (~(1 << 4)), AO_GPIO_O);
	writel(readl(AO_GPIO_O_EN_N) & (~(1 << 4)), AO_GPIO_O_EN_N);
	writel(readl(AO_RTI_PIN_MUX_REG) & (~(0xf << 16)), AO_RTI_PIN_MUX_REG);
	uart_puts(" off\n");

	if (suspend_from == SYS_POWEROFF){
		/* TEST_N */
		uart_puts("regulator: 3v3 and ee");
		writel(readl(AO_GPIO_O) & (~(1 << 31)), AO_GPIO_O);
		writel(readl(AO_GPIO_O_EN_N) & (~(1 << 31)), AO_GPIO_O_EN_N);
		writel(readl(AO_RTI_PIN_MUX_REG1) & (~(0xf << 28)), AO_RTI_PIN_MUX_REG1);
		uart_puts(" off\n");
	} else {
		/*step down ee voltage*/
		uart_puts("regulator: ee sleep\n");
		set_vddee_voltage(CONFIG_VDDEE_SLEEP_VOLTAGE);
	}

	if (suspend_from == SYS_POWEROFF)
		uart_puts("powered off\n");
	else
		uart_puts("suspended\n");
}

static void power_on_at_24M(unsigned int suspend_from)
{
	if (suspend_from == SYS_POWEROFF)
		uart_puts("powering on\n");
	else
		uart_puts("resuming\n");

	/*step up ee voltage*/
	uart_puts("regulator: ee init\n");
	set_vddee_voltage(CONFIG_VDDEE_INIT_VOLTAGE);

	if (suspend_from == SYS_POWEROFF){
		/* TEST_N */
		uart_puts("regulator: 3v3 and ee");
		writel(readl(AO_GPIO_O) | (1 << 31), AO_GPIO_O);
		writel(readl(AO_GPIO_O_EN_N) & (~(1 << 31)), AO_GPIO_O_EN_N);
		writel(readl(AO_RTI_PIN_MUX_REG1) & (~(0xf << 28)), AO_RTI_PIN_MUX_REG1);
		uart_puts(" on\n");
		_udelay(100);
	}

	/* GPIOAO_4 */
	uart_puts("regulator: cpu_b");
	writel(readl(AO_GPIO_O) | (1 << 4), AO_GPIO_O);
	writel(readl(AO_GPIO_O_EN_N) & (~(1 << 4)), AO_GPIO_O_EN_N);
	writel(readl(AO_RTI_PIN_MUX_REG) & (~(0xf << 16)), AO_RTI_PIN_MUX_REG);
	uart_puts(" on\n");

	/* GPIOAO_10 */
	uart_puts("regulator: cpu_a");
	writel(readl(AO_GPIO_O) | (1 << 10), AO_GPIO_O);
	writel(readl(AO_GPIO_O_EN_N) & (~(1 << 10)), AO_GPIO_O_EN_N);
	writel(readl(AO_RTI_PIN_MUX_REG1) & (~(0xf << 8)), AO_RTI_PIN_MUX_REG);
	uart_puts(" on\n");

	_udelay(10000);

	gpio_state_restore(gpio_groups, ARRAY_SIZE(gpio_groups));

	if (suspend_from == SYS_POWEROFF)
		uart_puts("powered on\n");
	else
		uart_puts("resumed\n");
}

void get_wakeup_source(void *response, unsigned int suspend_from)
{
	struct wakeup_info *p = (struct wakeup_info *)response;
	struct wakeup_gpio_info *gpio;
	unsigned val;
	unsigned i = 0;

	p->status = RESPONSE_OK;
	val = (
			POWER_KEY_WAKEUP_SRC | 
			AUTO_WAKEUP_SRC | 
			REMOTE_WAKEUP_SRC |
			ETH_PMT_WAKEUP_SRC | 
			ETH_PHY_GPIO_SRC | 
			CEC_WAKEUP_SRC | 
			CECB_WAKEUP_SRC | 
			RTC_WAKEUP_SRC
		);

	p->sources = val;

	/* GPIOAO_1 */
	gpio = &(p->gpio_info[i]);
	gpio->wakeup_id = POWER_KEY_WAKEUP_SRC;
	gpio->gpio_in_idx = GPIOAO_1;
	gpio->gpio_in_ao = 1;
	gpio->gpio_out_idx = -1;
	gpio->gpio_out_ao = -1;
	gpio->irq = IRQ_AO_GPIO0_NUM;
	gpio->trig_type = GPIO_IRQ_FALLING_EDGE;
	p->gpio_info_count = ++i;

	/* GPIOZ_14 */
	gpio = &(p->gpio_info[i]);
	gpio->wakeup_id = ETH_PHY_GPIO_SRC;
	gpio->gpio_in_idx = GPIOZ_14;
	gpio->gpio_in_ao = 0;
	gpio->gpio_out_idx = -1;
	gpio->gpio_out_ao = -1;
	gpio->irq = IRQ_GPIO1_NUM;
	gpio->trig_type = GPIO_IRQ_FALLING_EDGE;
	p->gpio_info_count = ++i;

	/* BOOT_5 */
	gpio = &(p->gpio_info[i]);
	gpio->wakeup_id = POWER_KEY_WAKEUP_SRC;
	gpio->gpio_in_idx = BOOT_5;
	gpio->gpio_in_ao = 0;
	gpio->gpio_out_idx = -1;
	gpio->gpio_out_ao = -1;
	gpio->irq = IRQ_GPIO0_NUM;
	gpio->trig_type = GPIO_IRQ_FALLING_EDGE;
	p->gpio_info_count = ++i;
}
extern void __switch_idle_task(void);

static unsigned int detect_key(unsigned int suspend_from)
{
	int exit_reason = 0;
	unsigned *irq = (unsigned *)WAKEUP_SRC_IRQ_ADDR_BASE;
	init_remote();
#ifdef CONFIG_CEC_WAKEUP
	cec_start_config();
#endif

	do {
		#ifdef CONFIG_CEC_WAKEUP
		if (cec_suspend_wakeup_chk())
			exit_reason = CEC_WAKEUP;
		/*if (irq[IRQ_AO_CEC] == IRQ_AO_CEC1_NUM ||*/
		 /*   irq[IRQ_AO_CECB] == IRQ_AO_CEC2_NUM) {*/
		irq[IRQ_AO_CEC] = 0xFFFFFFFF;
		irq[IRQ_AO_CECB] = 0xFFFFFFFF;
		if (cec_suspend_handle())
			exit_reason = CEC_WAKEUP;
		/*}*/
		#endif

		if (irq[IRQ_AO_IR_DEC] == IRQ_AO_IR_DEC_NUM) {
			irq[IRQ_AO_IR_DEC] = 0xFFFFFFFF;
			if (remote_detect_key())
				exit_reason = REMOTE_WAKEUP;
		}

		if (irq[IRQ_VRTC] == IRQ_VRTC_NUM) {
			irq[IRQ_VRTC] = 0xFFFFFFFF;
			exit_reason = RTC_WAKEUP;
		}

		/* GPIOAO_1 */
		if (irq[IRQ_AO_GPIO0] == IRQ_AO_GPIO0_NUM) {
			irq[IRQ_AO_GPIO0] = 0xFFFFFFFF;
			if ((readl(AO_GPIO_I) & (1<<1)) == 0)
				exit_reason = POWER_KEY_WAKEUP;
		}
		if (suspend_from != SYS_POWEROFF){
			/* GPIOZ_14 */
			if (irq[IRQ_GPIO1] == IRQ_GPIO1_NUM) {
				irq[IRQ_GPIO1] = 0xFFFFFFFF;
				if (!(readl(PREG_PAD_GPIO4_I) & (0x01 << 14))
						&& (readl(PREG_PAD_GPIO4_EN_N) & (0x01 << 14)))
					exit_reason = ETH_PHY_GPIO;
			}

			/* BOOT_5 */
			if (irq[IRQ_GPIO0] == IRQ_GPIO0_NUM) {
				irq[IRQ_GPIO0] = 0xFFFFFFFF;
				if (!(readl(PREG_PAD_GPIO0_I) & (0x01 << 5)))
					exit_reason = POWER_KEY_WAKEUP;
			}
		}

		if (irq[IRQ_ETH_PTM] == IRQ_ETH_PMT_NUM) {
			irq[IRQ_ETH_PTM]= 0xFFFFFFFF;
			exit_reason = ETH_PMT_WAKEUP;
		}

		if (exit_reason)
			break;
		else
			__switch_idle_task();
	} while (1);

	return exit_reason;
}

static void pwr_op_init(struct pwr_op *pwr_op)
{
	pwr_op->power_off_at_24M = power_off_at_24M;
	pwr_op->power_on_at_24M = power_on_at_24M;
	pwr_op->detect_key = detect_key;
	pwr_op->get_wakeup_source = get_wakeup_source;
}
