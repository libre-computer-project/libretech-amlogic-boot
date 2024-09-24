/*
 * Copyright (c) 2021-2022 Amlogic, Inc. All rights reserved.
 *
 * SPDX-License-Identifier: MIT
 */

#include "aml_portable_ext.h"

#include <FreeRTOS.h>

#include "arm-smccc.h"
#include "common.h"
#include "gic.h"
#include "rtosinfo.h"
#include "task.h"

#define portMAX_IRQ_NUM 1024

#ifndef configPREPARE_CPU_HALT
#define configPREPARE_CPU_HALT()
#endif

extern xRtosInfo_t xRtosInfo;

static ipi_process_handle ipi_handler;

static unsigned char irq_mask[portMAX_IRQ_NUM / 8];

/*-----------------------------------------------------------*/
static void pvPortSetIrqMask(uint32_t irq_num, int val)
{
	int idx, bit;
	unsigned long flags;

	portIRQ_SAVE(flags);
	bit = (irq_num & 0x7);
	idx = (irq_num / 8);
	if (val)
		irq_mask[idx] |= (1 << bit);
	else
		irq_mask[idx] &= ~(1 << bit);
	portIRQ_RESTORE(flags);
}

/*-----------------------------------------------------------*/
static unsigned long prvCorePowerDown(void)
{
	struct arm_smccc_res res;

	arm_smccc_smc(0x84000002, 0, 0, 0, 0, 0, 0, 0, &res);
	return res.a0;
}

/*-----------------------------------------------------------*/
#if defined(CONFIG_SOC_T7) || defined(CONFIG_SOC_T7C)
#include "osd_wrap.h"
#endif
static void vBeforeExceptionShutdown(Halt_Action_e act)
{
	(void)act;
#if defined(CONFIG_SOC_T7) || defined(CONFIG_SOC_T7C)
	if (act == HLTACT_EXCEPTION_SYSTEM)
		osd_wrap.exception_handle();
#endif
}

/*-----------------------------------------------------------*/
#if CONFIG_BACKTRACE
#include "stack_trace.h"
int vPortTaskPtregs(TaskHandle_t task, struct pt_regs *reg)
{
	StackType_t *pxTopOfStack;
	int i;

	if (!task || task == xTaskGetCurrentTaskHandle())
		return -1;
	pxTopOfStack = *(StackType_t **)task;
	reg->sp = (unsigned long)pxTopOfStack;
	if (*pxTopOfStack)
		pxTopOfStack += 64;
	pxTopOfStack += 2;
	reg->elr = *pxTopOfStack++;
	reg->spsr = *pxTopOfStack++;
	for (i = 0; i < 31; i++) reg->regs[i] = pxTopOfStack[31 - (i ^ 1)];
	return 0;
}
#endif

/*-----------------------------------------------------------*/
#if CONFIG_LOG_BUFFER
void vPortConfigLogBuf(uint32_t pa, uint32_t len)
{
	xRtosInfo.logbuf_phy = pa;
	xRtosInfo.logbuf_len = len;
	vCacheFlushDcacheRange((unsigned long)&xRtosInfo, sizeof(xRtosInfo));
}
#endif

/*-----------------------------------------------------------*/
void vLowPowerSystem(void)
{
	taskENTER_CRITICAL();
	portDISABLE_INTERRUPTS();
	vPortRtosInfoUpdateStatus(eRtosStat_Done);
	/*set mailbox to dsp for power control!*/
	while (1) {
		__asm volatile("wfi");
	}
}

/*-----------------------------------------------------------*/
unsigned int xPortIsIsrContext(void)
{
#if CONFIG_ARM64
	return ullPortInterruptNesting == 0 ? 0 : 1;
#else
	return ulPortInterruptNesting == 0 ? 0 : 1;
#endif
}

/*-----------------------------------------------------------*/
void vPortAddIrq(uint32_t irq_num)
{
	if (irq_num >= portMAX_IRQ_NUM)
		return;
	pvPortSetIrqMask(irq_num, 1);
}

/*-----------------------------------------------------------*/
void vPortRemoveIrq(uint32_t irq_num)
{
	if (irq_num >= portMAX_IRQ_NUM)
		return;
	pvPortSetIrqMask(irq_num, 0);
}

/*-----------------------------------------------------------*/
void vPortRtosInfoUpdateStatus(uint32_t status)
{
	xRtosInfo.status = status;
	vCacheFlushDcacheRange((unsigned long)&xRtosInfo, sizeof(xRtosInfo));
}

/*-----------------------------------------------------------*/
void vPortHaltSystem(Halt_Action_e act)
{
	uint32_t irq = 0, i;

	portDISABLE_INTERRUPTS();

	for (irq = 0; irq < portMAX_IRQ_NUM; irq += 8) {
		for (i = 0; i < 8; i++) {
			if (irq_mask[irq / 8] & (1 << i))
				plat_gic_irq_unregister(irq + i);
		}
	}
	configPREPARE_CPU_HALT();

	vBeforeExceptionShutdown(act);

	vHardwareResourceRelease();

	vPortRtosInfoUpdateStatus(eRtosStat_Done);

	plat_gic_raise_softirq(1, 7);

	while (1) {
#if defined(CONFIG_SOC_T7) || defined(CONFIG_SOC_T7C)
		prvCorePowerDown();
#else
		__asm volatile("wfi");
#endif
	}
}

/*-----------------------------------------------------------*/
void vHardwareResourceRecord(void)
{
#define NOTICE_BL31_RTOS_LOAD_INFO_ADDRESS (0xF7040000 - 0x08)

#if defined(CONFIG_SOC_T7) || defined(CONFIG_SOC_T7C)
	extern void vTickTimerRecord(void);
	/* systick timer record */
	vTickTimerRecord();
#endif

	/* The real loading address of RTOS is passed to BL31 */
#if defined(CONFIG_SOC_C3) && (CONFIG_PRIMARY_CPU == 1)
	REG32(NOTICE_BL31_RTOS_LOAD_INFO_ADDRESS) = configTEXT_BASE;
	vCacheFlushDcacheRange(NOTICE_BL31_RTOS_LOAD_INFO_ADDRESS, 4);
#endif
}

/*-----------------------------------------------------------*/
#define IRQ_ARM_ISP_NUM            (145 + 32)
void vHardwareResourceRelease(void)
{
	/// timer
#if defined(CONFIG_SOC_T7) || defined(CONFIG_SOC_T7C)
	extern void vTickTimerRestore(void);
	/* systick timer restore */
	vTickTimerRestore();
#endif

	/// irq
#if defined(CONFIG_SOC_T7) || defined(CONFIG_SOC_T7C)
	/* viu1_line_n_int */
	plat_gic_irq_register_with_default(227, 0, 0);
	/* ge2d_int */
	plat_gic_irq_register_with_default(249, 0, 1);
	/* dwap_irq */
	plat_gic_irq_register_with_default(91, 0, 1);
	/* isp adapter frontend2 irq */
	plat_gic_irq_register_with_default(343, 0, 1);
	plat_gic_irq_register_with_default(321, 1, 0);
	/* timerA irq*/
	plat_gic_irq_register_with_default(32, 0, 0);
#endif

#if defined(CONFIG_SOC_C3)
	plat_gic_irq_register_with_default(IRQ_ARM_ISP_NUM, 1, 1);
#endif
}

/*-----------------------------------------------------------*/
int xRtosLoadStageIndicator(void)
{
	static int load_finished;

#if defined(CONFIG_SOC_C3) && (CONFIG_PRIMARY_CPU == 1)
	vCacheFlushDcacheRange((CONFIG_SCATTER_LOAD_ADDRESS - 0x04), 4);
	if (REG32(CONFIG_SCATTER_LOAD_ADDRESS - 0x04) == 0xaabbccdd) {
		if (!load_finished) {
			load_finished = 1;
			/* Prepare the c++ constructors environment */
			_global_constructors();
		}
		return 2;
	}
#endif

	return 1;
}

/*-----------------------------------------------------------*/
void xIpiProcessCallbackRegister(ipi_process_handle handler)
{
	ipi_handler = handler;
}

/*-----------------------------------------------------------*/
void xIpiCommonProcess(void *args)
{
	if (ipi_handler)
		ipi_handler(args);
#if defined(CONFIG_SOC_T7) || defined(CONFIG_SOC_T7C)
	vPortHaltSystem(2);
#endif
}