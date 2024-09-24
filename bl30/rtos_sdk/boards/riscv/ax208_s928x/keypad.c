/*
 * Copyright (c) 2021-2023 Amlogic, Inc. All rights reserved.
 *
 * SPDX-License-Identifier: MIT
 */

#include <stdio.h>
#include <string.h>
#include "FreeRTOS.h"
#include "soc.h"
#include "keypad.h"
#include "gpio.h"
#include "saradc.h"
#include "suspend.h"
#include "vad_suspend.h"

/* GPIO KEY ID */
//#define GPIO_KEY_ID_WIFI_WAKE		GPIOX_7

/* ADC KEY ID */
#define ADC_KEY_ID_VOL_DEC		521
#define ADC_KEY_ID_VOL_INC		522
#define ADC_KEY_ID_POWER		523

static void vGpioKeyCallBack(struct xReportEvent event)
{
	uint32_t buf[4] = { 0 };
#ifdef KEYPAD_USED
	switch (event.ulCode) {
	case GPIO_KEY_ID_WIFI_WAKE:
		buf[0] = POWER_KEY_WAKEUP;
		STR_Wakeup_src_Queue_Send_FromISR(buf);
		wakeup_dsp();
		break;
	default:
		break;
	}
#endif
	printf("GPIO key event 0x%x, key code %d, responseTicks %d\n", event.event, event.ulCode,
	       event.responseTime);
}

static void vAdcKeyCallBack(struct xReportEvent event)
{
	uint32_t buf[4] = { 0 };

	switch (event.ulCode) {
	case ADC_KEY_ID_POWER:
		buf[0] = POWER_KEY_WAKEUP;
		STR_Wakeup_src_Queue_Send_FromISR(buf);
		wakeup_dsp();
		break;
	default:
		break;
	}

	printf("ADC key event 0x%x, key code %d, responseTime %d\n", event.event, event.ulCode,
	       event.responseTime);
}

struct xGpioKeyInfo gpioKeyInfo[] = {
	//GPIO_KEY_INFO(GPIO_KEY_ID_WIFI_WAKE, HIGH, EVENT_SHORT, vGpioKeyCallBack, NULL)
};

struct xAdcKeyInfo adcKeyInfo[] = {
	ADC_KEY_INFO(ADC_KEY_ID_POWER, 0, SARADC_CH0, EVENT_SHORT, vAdcKeyCallBack, NULL),
};

void vKeyPadInit(void)
{
	vCreateAdcKey(adcKeyInfo, sizeof(adcKeyInfo) / sizeof(struct xAdcKeyInfo));
	vAdcKeyEnable();
	vCreateGpioKey(gpioKeyInfo, sizeof(gpioKeyInfo) / sizeof(struct xGpioKeyInfo));
	vGpioKeyEnable();
}

void vKeyPadDeinit(void)
{
	vAdcKeyDisable();
	vDestroyAdcKey();
	vGpioKeyDisable();
	vDestroyGpioKey();
}
