/*
 * Copyright (c) 2021-2022 Amlogic, Inc. All rights reserved.
 *
 * SPDX-License-Identifier: MIT
 */

#include "FreeRTOS.h"
#include <gpio.h>
#include <leds_plat.h>
#include <leds_state.h>

/* TODO: Temporarily use static variables instead of stick mem */
static int32_t LedStickMem0;
//static int32_t LedStickMem1;

static struct LedCoord BreathInflections0[] = { { 0, 0 }, { 2500, 255 }, { 5000, 0 } };

static struct LedCoord BreathInflections1[] = { { 0, 0 }, { 5000, 255 }, { 10000, 0 } };

static struct LedCoord BreathInflections2[] = { { 0, 0 }, { 10000, 255 }, { 20000, 0 } };

static struct LedCoord BreathInflections3[] = { { 0, 0 }, { 20000, 255 }, { 40000, 0 } };

struct LedCoord *BreathInflections[LED_BREATH_MAX_COUNT] = {
	BreathInflections0,
	BreathInflections1,
	BreathInflections2,
	BreathInflections3,
};

struct LedDevice MesonLeds[] = {
	{
		.id = LED_ID_0,
		.type = LED_TYPE_PWM,
		.name = "sys_led",
		.hardware_id = MESON_PWM_INVALID,
		.pwm_chip_id = PWM_G,
		.polarity = LED_POLARITY_POSITIVE,
		.breathtime = 0,
	},
};

int32_t get_led_breath_len(uint32_t breath_id)
{
	switch (breath_id) {
	case 0:
		return sizeof(BreathInflections0) / sizeof(struct LedCoord);
	case 1:
		return sizeof(BreathInflections1) / sizeof(struct LedCoord);
	case 2:
		return sizeof(BreathInflections2) / sizeof(struct LedCoord);
	case 3:
		return sizeof(BreathInflections3) / sizeof(struct LedCoord);
	} /* end switch */

	iprintf("%s: id: %ld leds state init!\n", DRIVER_NAME, breath_id);

	return -pdFREERTOS_ERRNO_EINVAL;
}

int32_t vLedPlatInit(int32_t **stickmem)
{
	/* TODO: Here is initialization stickmem, but not doing so now */
	*stickmem = &LedStickMem0;

	/* off by default */
	return xLedsStateSetBrightness(LED_ID_0, LED_OFF);
}

int32_t vLedPinmuxInit(void)
{
	/* set pinmux */
	return xPinmuxSet(GPIOD_11, PIN_FUNC3);
}
