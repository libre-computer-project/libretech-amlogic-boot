/* SPDX-License-Identifier: (GPL-2.0+ OR MIT) */
/*
 * board/amlogic/g12b_w200_v1/firmware/scp_task/pwr_ctrl.c
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
		uart_puts("use vddee new table!");
		uart_puts("\n");
		pwm_voltage_ee = pwm_voltage_table_ee_new;
		pwm_size = ARRAY_SIZE(pwm_voltage_table_ee_new);
	} else {
		uart_puts("use vddee table!");
		uart_puts("\n");
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
	/*set gpioH_8 low to power off vcc 5v*/
	writel(readl(PREG_PAD_GPIO3_EN_N) & (~(1 << 8)), PREG_PAD_GPIO3_EN_N);
	writel(readl(PERIPHS_PIN_MUX_C) & (~(0xf)), PERIPHS_PIN_MUX_C);

	gpio_state_backup(gpio_groups, ARRAY_SIZE(gpio_groups));

	/*set gpioao_4 low to power off vcck_a*/
	writel(readl(AO_GPIO_O) & (~(1 << 4)), AO_GPIO_O);
	writel(readl(AO_GPIO_O_EN_N) & (~(1 << 4)), AO_GPIO_O_EN_N);
	writel(readl(AO_RTI_PIN_MUX_REG) & (~(0xf << 16)), AO_RTI_PIN_MUX_REG);
	/*set test_n low to power off vcck_b & vcc 3.3v*/
	writel(readl(AO_GPIO_O) & (~(1 << 31)), AO_GPIO_O);
	writel(readl(AO_GPIO_O_EN_N) & (~(1 << 31)), AO_GPIO_O_EN_N);
	writel(readl(AO_RTI_PIN_MUX_REG1) & (~(0xf << 28)), AO_RTI_PIN_MUX_REG1);

	/*step down ee voltage*/
	set_vddee_voltage(CONFIG_VDDEE_SLEEP_VOLTAGE);
}

static void power_on_at_24M(unsigned int suspend_from)
{
	/*step up ee voltage*/
	set_vddee_voltage(CONFIG_VDDEE_INIT_VOLTAGE);

	/*set test_n high to power on vcck_b & vcc 3.3v*/
	writel(readl(AO_GPIO_O) | (1 << 31), AO_GPIO_O);
	writel(readl(AO_GPIO_O_EN_N) & (~(1 << 31)), AO_GPIO_O_EN_N);
	writel(readl(AO_RTI_PIN_MUX_REG1) & (~(0xf << 28)), AO_RTI_PIN_MUX_REG1);
	_udelay(100);
	/*set gpioao_4 high to power on vcck_a*/
	writel(readl(AO_GPIO_O) | (1 << 4), AO_GPIO_O);
	writel(readl(AO_GPIO_O_EN_N) & (~(1 << 4)), AO_GPIO_O_EN_N);
	writel(readl(AO_RTI_PIN_MUX_REG) & (~(0xf << 16)), AO_RTI_PIN_MUX_REG);

	_udelay(10000);
	gpio_state_restore(gpio_groups, ARRAY_SIZE(gpio_groups));
	/*set gpioH_8 low to power on vcc 5v*/
	writel(readl(PREG_PAD_GPIO3_EN_N) | (1 << 8), PREG_PAD_GPIO3_EN_N);
	writel(readl(PERIPHS_PIN_MUX_C) & (~(0xf)), PERIPHS_PIN_MUX_C);
	_udelay(10000);

}

void get_wakeup_source(void *response, unsigned int suspend_from)
{
	struct wakeup_info *p = (struct wakeup_info *)response;
	struct wakeup_gpio_info *gpio;
	unsigned val;
	unsigned i = 0;

	p->status = RESPONSE_OK;
	val = (POWER_KEY_WAKEUP_SRC | AUTO_WAKEUP_SRC | REMOTE_WAKEUP_SRC |
	       BT_WAKEUP_SRC | CEC_WAKEUP_SRC | CECB_WAKEUP_SRC);

	p->sources = val;

	/* Power Key: AO_GPIO[3]*/
	gpio = &(p->gpio_info[i]);
	gpio->wakeup_id = POWER_KEY_WAKEUP_SRC;
	gpio->gpio_in_idx = GPIOAO_3;
	gpio->gpio_in_ao = 1;
	gpio->gpio_out_idx = -1;
	gpio->gpio_out_ao = -1;
	gpio->irq = IRQ_AO_GPIO0_NUM;
	gpio->trig_type = GPIO_IRQ_FALLING_EDGE;
	p->gpio_info_count = ++i;
#ifdef CONFIG_BT_WAKEUP
	gpio = &(p->gpio_info[i]);
	gpio->wakeup_id = BT_WAKEUP_SRC;
	gpio->gpio_in_idx = GPIOX_18;
	gpio->gpio_in_ao = 0;
	gpio->gpio_out_idx = -1;
	gpio->gpio_out_ao = -1;
	gpio->irq = IRQ_GPIO1_NUM;
	gpio->trig_type	= GPIO_IRQ_FALLING_EDGE;
	p->gpio_info_count = ++i;
#endif

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
		if (irq[IRQ_AO_CEC] == IRQ_AO_CEC1_NUM ||
		    irq[IRQ_AO_CECB] == IRQ_AO_CEC2_NUM) {
			irq[IRQ_AO_CEC] = 0xFFFFFFFF;
			irq[IRQ_AO_CECB] = 0xFFFFFFFF;
			if (cec_suspend_handle())
				exit_reason = CEC_WAKEUP;
		}
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

		if (irq[IRQ_AO_GPIO0] == IRQ_AO_GPIO0_NUM) {
			irq[IRQ_AO_GPIO0] = 0xFFFFFFFF;
			if ((readl(AO_GPIO_I) & (1<<3)) == 0)
				exit_reason = POWER_KEY_WAKEUP;
		}
#ifdef CONFIG_BT_WAKEUP
		if (irq[IRQ_GPIO1] == IRQ_GPIO1_NUM) {
			irq[IRQ_GPIO1] = 0xFFFFFFFF;
			if (!(readl(PREG_PAD_GPIO2_I) & (0x01 << 18))
				&& (readl(PREG_PAD_GPIO2_O) & (0x01 << 17))
				&& !(readl(PREG_PAD_GPIO2_EN_N) & (0x01 << 17)))
				exit_reason = BT_WAKEUP;
		}
#endif
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
