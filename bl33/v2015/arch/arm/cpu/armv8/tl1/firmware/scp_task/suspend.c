/* SPDX-License-Identifier: (GPL-2.0+ OR MIT) */
/*
 * arch/arm/cpu/armv8/tl1/firmware/scp_task/suspend.c
 *
 * Copyright (C) 2020 Amlogic, Inc. All rights reserved.
 *
 */

#include "config.h"
#include "registers.h"
#include "task_apis.h"
#include "suspend.h"
unsigned int time;
#include <scp_remote.c>

#include <scp_adc.c>
#include <pwr_ctrl.c>
#include <hdmi_cec_arc.c>

static struct pwr_op pwr_op_d;
static struct pwr_op *p_pwr_op;

void suspend_pwr_ops_init(void)
{
	p_pwr_op = &pwr_op_d;
	pwr_op_init(p_pwr_op);
}

void suspend_get_wakeup_source(void *response, unsigned int suspend_from)
{
	if (!p_pwr_op->get_wakeup_source)
		return;
	p_pwr_op->get_wakeup_source(response, suspend_from);
}

/*
 *suspend_from defines who call this function.
 * 1: suspend
 * 0: power off
*/
void enter_suspend(unsigned int suspend_from)
{
	int exit_reason = UDEFINED_WAKEUP;
	#ifdef CONFIG_CEC_WAKEUP
		hdmi_cec_func_config = readl(P_AO_DEBUG_REG0) & 0xff;
		uart_puts(CEC_VERSION);
		uart_puts("\n");
		uart_puts("cec enter suspend cfg:0x");
		uart_put_hex(hdmi_cec_func_config, 16);
		uart_puts("\n");
	#endif
	if (p_pwr_op->power_off_at_24M)
		p_pwr_op->power_off_at_24M(suspend_from);

	exit_reason = p_pwr_op->detect_key(suspend_from);

	if (p_pwr_op->power_on_at_24M)
		p_pwr_op->power_on_at_24M(suspend_from);

	uart_puts("exit_reason:0x");
	uart_put_hex(exit_reason, 8);
	uart_puts("\n");
	set_wakeup_method(exit_reason);

}