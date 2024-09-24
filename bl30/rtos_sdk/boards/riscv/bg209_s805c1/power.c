/*
 * Copyright (c) 2021-2022 Amlogic, Inc. All rights reserved.
 *
 * SPDX-License-Identifier: MIT
 */

#include <stdio.h>
#include "FreeRTOS.h"
#include "common.h"
#include "gpio.h"
#include "ir.h"
#include "eth.h"
#include "soc.h"
#include "suspend.h"
#include "task.h"
#include "gpio.h"
#include "pwm.h"
#include "pwm_plat.h"
#include "keypad.h"
#include "timer_source.h"
#include "vad_suspend.h"
#include "wakeup.h"
#include "power.h"
#include "mailbox-api.h"


#include "hdmi_cec.h"
static TaskHandle_t cecTask;

static int vdd_ee;
static TaskHandle_t vadTask;

static struct IRPowerKey prvPowerKeyList[] = {
	{ 0xef10fe01, IR_NORMAL }, /* ref tv pwr */
	{ 0xba45bd02, IR_NORMAL }, /* small ir pwr */
	{ 0xef10fb04, IR_NORMAL }, /* old ref tv pwr */
	{ 0xe51afb04, IR_NORMAL },
	{ 0x3ac5bd02, IR_CUSTOM },
	{}
};

static void vIRHandler(struct IRPowerKey *pkey)
{
	uint32_t buf[4] = { 0 };

	if (pkey->type == IR_NORMAL)
		buf[0] = REMOTE_WAKEUP;
	else if (pkey->type == IR_CUSTOM)
		buf[0] = REMOTE_CUS_WAKEUP;

	/* do sth below  to wakeup*/
	STR_Wakeup_src_Queue_Send_FromISR(buf);
};

static void *xMboxVadWakeup(void *msg)
{
	uint32_t buf[4] = { 0 };

	buf[0] = VAD_WAKEUP;
	STR_Wakeup_src_Queue_Send(buf);

	return NULL;
}

void str_hw_init(void)
{
	int ret;
	/*enable device & wakeup source interrupt*/
	vIRInit(MODE_HARD_NEC, GPIOD_2, PIN_FUNC1, prvPowerKeyList, ARRAY_SIZE(prvPowerKeyList),
		vIRHandler);
	vETHInit(0);

	xTaskCreate(vCEC_task, "CECtask", configMINIMAL_STACK_SIZE,
		    NULL, CEC_TASK_PRI, &cecTask);

	vBackupAndClearGpioIrqReg();
	vGpioIRQInit();
	vKeyPadInit();
}

void str_hw_disable(void)
{
	/*disable wakeup source interrupt*/
	vIRDeint();
	vETHDeint();

	if (cecTask) {
		vTaskDelete(cecTask);
		cec_req_irq(0);
	}

	vKeyPadDeinit();
	vRestoreGpioIrqReg();
}

#define DVB_PWR_EN_GPIO	GPIO_TEST_N
#define VCC5V_GPIO	GPIOZ_6
void str_power_on(int shutdown_flag)
{
	int ret;

	(void)shutdown_flag;

	/***set vdd_ee val***/
	ret = vPwmMesonsetvoltage(VDDEE_VOLT, vdd_ee);
	if (ret < 0) {
		printf("VDD_EE pwm set fail\n");
		return;
	}
	/***power on vcc3.3v en***/
	ret = xGpioSetDir(DVB_PWR_EN_GPIO, GPIO_DIR_OUT);
	if (ret < 0) {
		printf("vcc3.3v en pin set gpio dir fail\n");
		return;
	}

	ret = xGpioSetValue(DVB_PWR_EN_GPIO, GPIO_LEVEL_LOW);
	if (ret < 0) {
		printf("DVB_PWR en pin gpio val fail\n");
		return;
	}

	/***power on vcc_5v***/
	ret = xGpioSetDir(VCC5V_GPIO, GPIO_DIR_OUT);
	if (ret < 0) {
		printf("vcc_5v set gpio dir fail\n");
		return;
	}

	ret = xGpioSetValue(VCC5V_GPIO, GPIO_LEVEL_HIGH);
	if (ret < 0) {
		printf("vcc_5v gpio val fail\n");
		return;
	}
	/*Wait POWERON_VDDCPU_DELAY for VDDCPU stable*/
	vTaskDelay(POWERON_VDDCPU_DELAY);

	printf("vdd_cpu on\n");
}

void str_power_off(int shutdown_flag)
{
	int ret;

	(void)shutdown_flag;

	/***power off vcc_5v***/
	ret = xGpioSetDir(VCC5V_GPIO, GPIO_DIR_OUT);
	if (ret < 0) {
		printf("vcc_5v set gpio dir fail\n");
		return;
	}

	ret = xGpioSetValue(VCC5V_GPIO, GPIO_LEVEL_LOW);
	if (ret < 0) {
		printf("vcc_5v gpio val fail\n");
		return;
	}
	/***power off vcc3.3v en***/
	ret = xGpioSetDir(DVB_PWR_EN_GPIO, GPIO_DIR_OUT);
	if (ret < 0) {
		printf("vcc3.3v en pin set gpio dir fail\n");
		return;
	}
	ret = xGpioSetValue(DVB_PWR_EN_GPIO, GPIO_LEVEL_HIGH);
	if (ret < 0) {
		printf("vcc3.3v en pin gpio val fail\n");
		return;
	}
	/***set vdd_ee val***/
	vdd_ee = vPwmMesongetvoltage(VDDEE_VOLT);
	if (vdd_ee < 0) {
		printf("vdd_EE pwm get fail\n");
		return;
	}

	ret = vPwmMesonsetvoltage(VDDEE_VOLT, 869);
	if (ret < 0) {
		printf("vdd_EE pwm set fail\n");
		return;
	}

	printf("Power down done.\n");
}
