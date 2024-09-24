/*
 * Copyright (c) 2021-2022 Amlogic, Inc. All rights reserved.
 *
 * SPDX-License-Identifier: MIT
 */

#include <string.h>
#include <stdio.h>
#include "FreeRTOS.h"
#include "suspend.h"
#include "task.h"
#include "gpio.h"

#include "queue.h" /* RTOS queue related API prototypes. */
#include "timers.h" /* Software timer related API prototypes. */
#include "semphr.h" /* Semaphore related API prototypes. */

#define BT_WAKE_HOST GPIOC_14 //bt_wake_host pin
#define INFO(fmt, args...) printf("[%s] " fmt "\n", __func__, ##args)

void Bt_IRQHandle(void)
{
	uint32_t buf[4] = { 0 };

	INFO("bt resume");
	vDisableGpioIRQ(BT_WAKE_HOST);
	if (!xGpioGetValue(BT_WAKE_HOST)) {
		buf[0] = BT_WAKEUP;
		INFO("power key");
		STR_Wakeup_src_Queue_Send_FromISR(buf);
	}
}

void Bt_GpioIRQRegister(void)
{
	INFO();
	xGpioSetDir(BT_WAKE_HOST, GPIO_DIR_IN);
	xRequestGpioIRQ(BT_WAKE_HOST, Bt_IRQHandle, IRQF_TRIGGER_FALLING);
}

void Bt_GpioIRQFree(void)
{
	vFreeGpioIRQ(BT_WAKE_HOST);
}
