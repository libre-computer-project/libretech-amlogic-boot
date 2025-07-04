
/*
 * board/amlogic/g12b_w400_v1/firmware/scp_task/pwr_ctrl.c
 *
 * Copyright (C) 2018 Amlogic, Inc. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/

#include <gpio.h>
#include "pwm_ctrl.h"
#include <suspend.h>
#ifdef CONFIG_CEC_WAKEUP
#include <cec_tx_reg.h>
#endif

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

#define SUSPEND_EE 1
#define SUSPEND_CPU_B 1

#if SUSPEND_EE
#define SUSPEND_CPU 1
#else
#define SUSPEND_CPU SUSPEND_CPU_B
#endif
static void set_vddee_voltage(unsigned int target_voltage)
{
	unsigned int to, pwm_size = 0;
	static int (*pwm_voltage_ee)[2];

	/* BOOT_9 = H use PWM_CFG0(0.67v-0.97v), =L use PWM_CFG1(0.69v-0.89v) */
	/*set BOOT_9 input mode*/
	/*
	writel((readl(PREG_PAD_GPIO0_EN_N) | 0x200), PREG_PAD_GPIO0_EN_N);
	if (((readl(PREG_PAD_GPIO0_EN_N) & 0x200 ) == 0x200) &&
			((readl(PREG_PAD_GPIO0_I) & 0x200 ) == 0x0)) {
		uart_puts("use vddee new table!\n");
		pwm_voltage_ee = pwm_voltage_table_ee_new;
		pwm_size = ARRAY_SIZE(pwm_voltage_table_ee_new);
	} else {
	*/
	//	uart_puts("use vddee table!\n");
		pwm_voltage_ee = pwm_voltage_table_ee;
		pwm_size = ARRAY_SIZE(pwm_voltage_table_ee);
	/*
	}
	*/

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
	uart_puts("pwr off start\n");

	/* VDDCPU_A_EN GPIOAO_10 */
	uart_puts("cpu_a ");
	writel(readl(AO_GPIO_O) & (~(1 << 10)), AO_GPIO_O);
	writel(readl(AO_GPIO_O_EN_N) & (~(1 << 10)), AO_GPIO_O_EN_N);
	writel(readl(AO_RTI_PIN_MUX_REG1) & (~(0xf << 8)), AO_RTI_PIN_MUX_REG1);
	uart_puts("off\n");

#if SUSPEND_CPU
	/* VDDCPU_B_EN GPIOAO_4 */
	uart_puts("cpu_b ");
	writel(readl(AO_GPIO_O) & (~(1 << 4)), AO_GPIO_O);
	writel(readl(AO_GPIO_O_EN_N) & (~(1 << 4)), AO_GPIO_O_EN_N);
	writel(readl(AO_RTI_PIN_MUX_REG) & (~(0xf << 16)), AO_RTI_PIN_MUX_REG);
	uart_puts("off\n");
#endif

	if (suspend_from == SYS_POWEROFF){
		/* SD CARD VOLTAGE */
		/*
		uart_puts("sd ");
		writel(readl(PREG_PAD_GPIO2_O) | (1 << 4), PREG_PAD_GPIO2_O); # UPDATE
		writel(readl(PREG_PAD_GPIO2_EN_N) & (~(1 << 4)), PREG_PAD_GPIO2_EN_N);
		uart_puts("off\n");
		*/
#if SUSPEND_EE
		/* VDDEE_EN GPIOAO_T */
		uart_puts("ee ");
		writel(readl(AO_GPIO_O) & (~(1 << 31)), AO_GPIO_O);
		writel(readl(AO_GPIO_O_EN_N) & (~(1 << 31)), AO_GPIO_O_EN_N);
		writel(readl(AO_RTI_PIN_MUX_REG1) & (~(0xf << 28)), AO_RTI_PIN_MUX_REG1);
		uart_puts("off\n");
#endif

		uart_puts("pwr off\n");
	} else {
		/*step down ee voltage*/
		uart_puts("ee ");
		set_vddee_voltage(CONFIG_VDDEE_SLEEP_VOLTAGE);
		uart_puts("lp\n");
		
		uart_puts("pwr suspend\n");
	}
}

static void power_on_at_24M(unsigned int suspend_from)
{
	uart_puts("pwr on start\n");

	if (suspend_from == SYS_POWEROFF){
		/* SD CARD VOLTAGE */
		/*
		writel(readl(PREG_PAD_GPIO2_O) | (1 << 4), PREG_PAD_GPIO2_O); # UPDATE
		writel(readl(PREG_PAD_GPIO2_EN_N) & (~(1 << 4)), PREG_PAD_GPIO2_EN_N);
		uart_puts("sd on\n");
		*/

#if SUSPEND_EE
		/* VDDEE_EN GPIOAO_T */
		uart_puts("ee ");
		writel(readl(AO_GPIO_O) | (1 << 31), AO_GPIO_O);
		writel(readl(AO_GPIO_O_EN_N) & (~(1 << 31)), AO_GPIO_O_EN_N);
		writel(readl(AO_RTI_PIN_MUX_REG1) & (~(0xf << 28)), AO_RTI_PIN_MUX_REG1);
		uart_puts("on\n");
		
		_udelay(10000);
#endif

	} else {
		/*step up ee voltage*/
		uart_puts("ee ");
		set_vddee_voltage(CONFIG_VDDEE_INIT_VOLTAGE);
		uart_puts("init\n");

		_udelay(100);
	}

#if SUSPEND_CPU
	/* VDDCPU_B_EN GPIOAO_4 */
	uart_puts("cpu_b ");
	writel(readl(AO_GPIO_O) | (1 << 4), AO_GPIO_O);
	writel(readl(AO_GPIO_O_EN_N) & (~(1 << 4)), AO_GPIO_O_EN_N);
	writel(readl(AO_RTI_PIN_MUX_REG) & (~(0xf << 16)), AO_RTI_PIN_MUX_REG);
	uart_puts("on\n");

	_udelay(100);
#endif

	/* VDDCPU_A_EN GPIOAO_10 */
	uart_puts("cpu_a ");
	writel(readl(AO_GPIO_O) | (1 << 10), AO_GPIO_O);
	writel(readl(AO_GPIO_O_EN_N) & (~(1 << 10)), AO_GPIO_O_EN_N);
	writel(readl(AO_RTI_PIN_MUX_REG1) & (~(0xf << 8)), AO_RTI_PIN_MUX_REG1);
	uart_puts("on\n");
	
	_udelay(100);

	uart_puts("pwr on\n");
}

void get_wakeup_source(void *response, unsigned int suspend_from)
{
	struct wakeup_info *p = (struct wakeup_info *)response;
	struct wakeup_gpio_info *gpio;
	unsigned val;
	unsigned i = 0;

	p->status = RESPONSE_OK;
	
	val = (REMOTE_WAKEUP_SRC | RTC_WAKEUP_SRC | BT_WAKEUP_SRC \
			| POWER_KEY_WAKEUP_SRC | AUTO_WAKEUP_SRC \
			| CEC_WAKEUP_SRC | CECB_WAKEUP_SRC \
			| ETH_PHY_GPIO_SRC);
#if SUSPEND_CPU
	if (suspend_from != SYS_POWEROFF)
#endif
		val |= ETH_PHY_GPIO_SRC;
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

	/*Eth:GPIOZ_14*/
	gpio = &(p->gpio_info[i]);
	gpio->wakeup_id = ETH_PHY_GPIO_SRC;
	gpio->gpio_in_idx = GPIOZ_14;
	gpio->gpio_in_ao = 0;
	gpio->gpio_out_idx = -1;
	gpio->gpio_out_ao = -1;
	gpio->irq = IRQ_GPIO0_NUM;
	gpio->trig_type = GPIO_IRQ_FALLING_EDGE;
	p->gpio_info_count = ++i;

#if SUSPEND_CPU
	if (suspend_from != SYS_POWEROFF){
#endif
		/* GPIOX_7 WL_BT_WAKE_HOST */
		gpio = &(p->gpio_info[i]);
		gpio->wakeup_id = BT_WAKEUP_SRC;
		gpio->gpio_in_idx = GPIOX_7;
		gpio->gpio_in_ao = 0;
		gpio->gpio_out_idx = -1;
		gpio->gpio_out_ao = -1;
		gpio->irq = IRQ_GPIO1_NUM;
		gpio->trig_type = GPIO_IRQ_FALLING_EDGE;
		p->gpio_info_count = ++i;
#if SUSPEND_CPU
	}
#endif
}
extern void __switch_idle_task(void);

static unsigned int detect_key(unsigned int suspend_from)
{
	int exit_reason = 0;
	unsigned *irq = (unsigned *)WAKEUP_SRC_IRQ_ADDR_BASE;
	init_remote();
#ifdef CONFIG_CEC_WAKEUP
		if (hdmi_cec_func_config & 0x1) {
			remote_cec_hw_reset();
			cec_node_init();
		}
#endif

	do {
#ifdef CONFIG_CEC_WAKEUP
		if (irq[IRQ_AO_CECB] == IRQ_AO_CEC2_NUM) {
			irq[IRQ_AO_CECB] = 0xFFFFFFFF;
			if (cec_power_on_check())
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

		// GPIOAO_1 UART_RX
		if (irq[IRQ_AO_GPIO0] == IRQ_AO_GPIO0_NUM) {
			irq[IRQ_AO_GPIO0] = 0xFFFFFFFF;
			if ((readl(AO_GPIO_I) & (1<<1)) == 0)
				exit_reason = POWER_KEY_WAKEUP;
		}

		// GPIOZ_14 ETHERNET INT
		if (irq[IRQ_GPIO0] == IRQ_GPIO0_NUM) {
			irq[IRQ_GPIO0] = 0xFFFFFFFF;
			if (!(readl(PREG_PAD_GPIO4_I) & (0x01 << 14))
					&& (readl(PREG_PAD_GPIO4_EN_N) & (0x01 << 14)))
				exit_reason = ETH_PHY_GPIO;
		}

#if SUSPEND_CPU
		if (suspend_from != SYS_POWEROFF){
#endif
			// GPIOX_7 WL_BT_WAKE_HOST
			if (irq[IRQ_GPIO1] == IRQ_GPIO1_NUM) {
				irq[IRQ_GPIO0] = 0xFFFFFFFF;
				if ((readl(PREG_PAD_GPIO2_I) & (1<<7)) == 0)
					exit_reason = BT_WAKEUP;
			}
#if SUSPEND_CPU
		}
#endif
		/*
		if (irq[IRQ_ETH_PTM] == IRQ_ETH_PMT_NUM) {
			irq[IRQ_ETH_PTM]= 0xFFFFFFFF;
			exit_reason = ETH_PMT_WAKEUP;
		}
		*/

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
