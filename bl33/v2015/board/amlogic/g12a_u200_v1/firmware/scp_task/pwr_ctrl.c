/* SPDX-License-Identifier: (GPL-2.0+ OR MIT) */
/*
 * board/amlogic/g12a_u200_v1/firmware/scp_task/pwr_ctrl.c
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

#define MESON_CPU_MAJOR_ID_G12A		0x28

unsigned char gpio_groups[] = {};

static int is_cpu_id_g12a(void)
{
	unsigned int cpu_id_reg = readl(P_AO_SEC_SD_CFG8);
	unsigned int family_id = (cpu_id_reg >> 24) & (0XFF);

	if (family_id == MESON_CPU_MAJOR_ID_G12A)
		return 1;
	else
		return 0;
}

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

	/* GPIOH_8 5V_EN ACTIVE_HIGH */
	uart_puts("regulator: 5v");
	writel(readl(PREG_PAD_GPIO3_EN_N) & (~(1 << 8)), PREG_PAD_GPIO3_EN_N);
	writel(readl(PERIPHS_PIN_MUX_C) & (~(0xf)), PERIPHS_PIN_MUX_C);
	uart_puts(" off\n");

	gpio_state_backup(gpio_groups, ARRAY_SIZE(gpio_groups));

	if (suspend_from == SYS_POWEROFF){
		/* TEST_N CPU_B and VCC3_3V ACTIVE_HIGH */
		uart_puts("regulator: cpu_b and 3v3");
		writel(readl(AO_GPIO_O) & (~(1 << 31)), AO_GPIO_O);
		writel(readl(AO_GPIO_O_EN_N) & (~(1 << 31)), AO_GPIO_O_EN_N);
		writel(readl(AO_RTI_PIN_MUX_REG1) & (~(0xf << 28)), AO_RTI_PIN_MUX_REG1);
		uart_puts(" off\n");
	}

	/*step down ee voltage*/
	uart_puts("regulator: ee sleep\n");
	set_vddee_voltage(CONFIG_VDDEE_SLEEP_VOLTAGE);

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

	uart_puts("regulator: ee init\n");
	/*
	 * sm1 ac200 board share BSP code with g12a_u200_v1
	 */
	if (is_cpu_id_g12a()) {
		/*g12a_u200_v1 step up ee voltage*/
		set_vddee_voltage(CONFIG_VDDEE_INIT_VOLTAGE);
	} else {
		/*sm1 ac200 step up ee voltage*/
		set_vddee_voltage(CONFIG_VDDEE_INIT_VOLTAGE_SM1);
	}

	if (suspend_from == SYS_POWEROFF){
		uart_puts("regulator: 3v3");
		/* TEST_N CPU_B and VCC3_3V ACTIVE_HIGH */
		writel(readl(AO_GPIO_O) | (1 << 31), AO_GPIO_O);
		writel(readl(AO_GPIO_O_EN_N) & (~(1 << 31)), AO_GPIO_O_EN_N);
		writel(readl(AO_RTI_PIN_MUX_REG1) & (~(0xf << 28)), AO_RTI_PIN_MUX_REG1);
		uart_puts(" on\n");
		_udelay(100);
	}

	_udelay(10000);

	gpio_state_restore(gpio_groups, ARRAY_SIZE(gpio_groups));

	/* GPIOH_8 5V_EN ACTIVE_HIGH */
	uart_puts("regulator: 5v");
	writel(readl(PREG_PAD_GPIO3_EN_N) | (1 << 8), PREG_PAD_GPIO3_EN_N);
	writel(readl(PERIPHS_PIN_MUX_C) & (~(0xf)), PERIPHS_PIN_MUX_C);
	uart_puts(" on\n");
	_udelay(10000);

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
			CEC_WAKEUP_SRC |
			CECB_WAKEUP_SRC |
			RTC_WAKEUP_SRC
		);

	p->sources = val;

	/* GPIOAO_1 UART_RX */
	gpio = &(p->gpio_info[i]);
	gpio->wakeup_id = POWER_KEY_WAKEUP_SRC;
	gpio->gpio_in_idx = GPIOAO_1;
	gpio->gpio_in_ao = 1;
	gpio->gpio_out_idx = -1;
	gpio->gpio_out_ao = -1;
	gpio->irq = IRQ_AO_GPIO0_NUM;
	gpio->trig_type = GPIO_IRQ_FALLING_EDGE;
	p->gpio_info_count = ++i;

	if (suspend_from != SYS_POWEROFF){
		/*Eth:GPIOZ_14*/
		gpio = &(p->gpio_info[i]);
		gpio->wakeup_id = ETH_PHY_GPIO_SRC;
		gpio->gpio_in_idx = GPIOZ_14;
		gpio->gpio_in_ao = 0;
		gpio->gpio_out_idx = -1;
		gpio->gpio_out_ao = -1;
		gpio->irq = IRQ_GPIO1_NUM;
		gpio->trig_type = GPIO_IRQ_FALLING_EDGE;
		p->gpio_info_count = ++i;

		/* BOOT_5 Button K11 4.7K Pull Down*/
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

		/* GPIOAO_1 UART_RX */
		if (irq[IRQ_AO_GPIO0] == IRQ_AO_GPIO0_NUM) {
			irq[IRQ_AO_GPIO0] = 0xFFFFFFFF;
			if ((readl(AO_GPIO_I) & (1<<1)) == 0)
				exit_reason = POWER_KEY_WAKEUP;
		}
		if (suspend_from != SYS_POWEROFF){
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
