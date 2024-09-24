/*
 * Copyright (c) 2021-2022 Amlogic, Inc. All rights reserved.
 *
 * SPDX-License-Identifier: MIT
 */

#include "FreeRTOS.h"
#include <register.h>
#include <common.h>
#include <gpio.h>
#include "projdefs.h"
#include "gpio_drv.h"
#include "gpio_irq.h"
#include "portmacro.h"

/* gpio irq controller EE */
#define IRQ_GPIO0_NUM 67
#define IRQ_GPIO1_NUM 68
#define IRQ_GPIO2_NUM 69
#define IRQ_GPIO3_NUM 70

/* gpio irq controller AO */
#define IRQ_AO_GPIO0_NUM 17
#define IRQ_AO_GPIO1_NUM 18

#define EE_IRQ_REG_EDGE_POL 0x00
#define EE_IRQ_REG_PIN_03_SEL 0x04
#define EE_IRQ_REG_PIN_47_SEL 0x08
#define EE_IRQ_REG_FILTER_SEL 0x0c

#define EE_GPIO_IRQ_POL_EDGE_MASK(x) (BIT(x) | BIT(16 + x))
#define EE_GPIO_IRQ_POL(x) BIT(16 + (x))
#define EE_GPIO_IRQ_EDGE(x) BIT(x)
#define EE_GPIO_IRQ_FILTER_SHIFT(x) ((x) << 2)
#define EE_GPIO_IRQ_SEL_SHIFT(x) (((x) << 3) % 32)
#define EE_GPIO_IRQ_BOTH(x) BIT(8 + (x))

#define AO_GPIO_NUM 10
#define AO_GPIO_IRQ_POL_EDGE_MASK(x) (BIT(16 + x) | BIT(18 + x))
#define AO_GPIO_IRQ_POL(x) BIT(16 + (x))
#define AO_GPIO_IRQ_EDGE(x) BIT(18 + (x))
#define AO_GPIO_IRQ_FILTER_SHIFT(x) (8 + ((x) << 2))
#define AO_GPIO_IRQ_SEL_SHIFT(x) ((x) << 2)
#define AO_GPIO_IRQ_BOTH(x) (BIT((x) + 20))

static const struct GpioDomain aoDomain = {
	.name = "AO",
	.rPullen = AO_GPIO_O_EN_N,
	.rPull = AO_GPIO_O_EN_N,
	.rGpio = AO_GPIO_O_EN_N,
	.rMux = AO_RTI_PINMUX_REG0,
	.rDrv = AO_PAD_DS_A,
};

static const struct GpioDomain eeDomain = {
	.name = "EE",
	.rPullen = PAD_PULL_UP_EN_REG0,
	.rPull = PAD_PULL_UP_REG0,
	.rGpio = PREG_PAD_GPIO0_EN_N,
	.rMux = PERIPHS_PIN_MUX_0,
	.rDrv = PAD_DS_REG0A,
};

static const struct GpioBank gpioBanks[BANK_NUM_MAX] = {
	/* name   pin_num   domain   pullen   pull   dir   out   in   mux   drv  */
	BANK_V2("D",  11, &aoDomain, 3,  0,  2,  0,  0,  0,  4,  0,  1,  0,    0,  0,    0,  0),
	BANK_V2("H",  24, &eeDomain, 2,  0,  2,  0,  6,  0,  7,  0,  8,  0,    5,  0,    3,  0),
	BANK_V2("B",  14, &eeDomain, 0,  0,  0,  0,  0,  0,  1,  0,  2,  0,    0,  0,    0,  0),
	BANK_V2("Z1",  8, &eeDomain, 1,  0,  1,  0,  3,  0,  4,  0,  5,  0,    4,  0,    1,  0),
	BANK_V2("Z2", 12, &eeDomain, 1,  7,  1,  7,  3,  7,  4,  7,  5,  7,    8,  0,    1, 14),
	BANK_V2("W",  13, &eeDomain, 3,  0,  3,  0,  9,  0, 10,  0, 11,  0,    2,  0,    5,  0),
	BANK_V2("E",   2, &aoDomain, 3, 16,  2, 16,  0, 16,  4, 16,  1, 16,    1, 16,    1, 16),
	BANK_V2("M",  30, &eeDomain, 4,  0,  4,  0, 12,  0, 13,  0, 14,  0,  0xa,  0,    6,  0),
	BANK_V2("C1",  8, &eeDomain, 5,  0,  5,  0, 16,  0, 17,  0, 18,  0,  0xf,  0, 0x28,  0),
	BANK_V2("C2",  8, &eeDomain, 4,  8,  4,  8, 16,  8, 17,  8, 18,  8, 0x2a,  0, 0x28,  8),
	BANK_V2("H2",  2, &eeDomain, 2, 24,  2, 24,  6, 24,  7, 24,  8, 24, 0x2b,  0,    3, 24),
};

static struct ParentIRQDesc eeIRQs[] = {
	[GPIO_EE_IRQ_L0] = PARENT_IRQ_BK(NULL, 0, GPIO_INVALID, IRQ_GPIO0_NUM),
	[GPIO_EE_IRQ_L1] = PARENT_IRQ_BK(NULL, 0, GPIO_INVALID, IRQ_GPIO1_NUM),
	[GPIO_EE_IRQ_L2] = PARENT_IRQ_BK(NULL, 0, GPIO_INVALID, IRQ_GPIO2_NUM),
	[GPIO_EE_IRQ_L3] = PARENT_IRQ_BK(NULL, 0, GPIO_INVALID, IRQ_GPIO3_NUM),
};

static struct ParentIRQDesc aoIRQs[] = {
	[GPIO_AO_IRQ_L0] = PARENT_IRQ_BK(NULL, 0, GPIO_INVALID, IRQ_AO_GPIO0_NUM),
	[GPIO_AO_IRQ_L1] = PARENT_IRQ_BK(NULL, 0, GPIO_INVALID, IRQ_AO_GPIO1_NUM),

};

static const struct GpioIRQBank irqBanks[BANK_NUM_MAX] = {
	GPIO_IRQ_BK("D", 0, aoIRQs, ARRAY_SIZE(aoIRQs)),
	GPIO_IRQ_BK("H", 11, eeIRQs, ARRAY_SIZE(eeIRQs)),
	GPIO_IRQ_BK("B", 52, eeIRQs, ARRAY_SIZE(eeIRQs)),
	GPIO_IRQ_BK("Z1", 66, eeIRQs, ARRAY_SIZE(eeIRQs)),
	GPIO_IRQ_BK("Z2", 74, eeIRQs, ARRAY_SIZE(eeIRQs)),
	GPIO_IRQ_BK("W", 86, eeIRQs, ARRAY_SIZE(eeIRQs)),
	GPIO_IRQ_BK("E", 99, eeIRQs, ARRAY_SIZE(eeIRQs)),
	GPIO_IRQ_BK("M", 101, eeIRQs, ARRAY_SIZE(eeIRQs)),
	GPIO_IRQ_BK("C1", 37, eeIRQs, ARRAY_SIZE(eeIRQs)),
	GPIO_IRQ_BK("C2", 45, eeIRQs, ARRAY_SIZE(eeIRQs)),
	GPIO_IRQ_BK("H2", 35, eeIRQs, ARRAY_SIZE(eeIRQs)),
};

const struct GpioBank *pGetGpioBank(void)
{
	return gpioBanks;
}

const struct GpioIRQBank *pGetGpioIrqBank(void)
{
	return irqBanks;
}

static void prvGpioEEsetupIRQ(uint16_t irqNum, uint8_t line, uint32_t flags)
{
	uint32_t val = 0;

	REG32_UPDATE_BITS(GPIO_EE_IRQ_BASE + EE_IRQ_REG_FILTER_SEL,
			  0x7 << EE_GPIO_IRQ_FILTER_SHIFT(line),
			  0x7 << EE_GPIO_IRQ_FILTER_SHIFT(line));

	if (flags & IRQF_TRIGGER_BOTH) {
		val |= EE_GPIO_IRQ_BOTH(line);
		REG32_UPDATE_BITS(GPIO_EE_IRQ_BASE, EE_GPIO_IRQ_BOTH(line), val);
		goto out;
	}

	if (flags & (IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING))
		val |= EE_GPIO_IRQ_EDGE(line);

	if (flags & (IRQF_TRIGGER_LOW | IRQF_TRIGGER_FALLING))
		val |= EE_GPIO_IRQ_POL(line);

	REG32_UPDATE_BITS(GPIO_EE_IRQ_BASE, EE_GPIO_IRQ_POL_EDGE_MASK(line), val);

out:
	REG32_UPDATE_BITS(GPIO_EE_IRQ_BASE + ((line > GPIO_EE_IRQ_L3) ? EE_IRQ_REG_PIN_47_SEL :
									EE_IRQ_REG_PIN_03_SEL),
			  0xff << EE_GPIO_IRQ_SEL_SHIFT(line),
			  irqNum << EE_GPIO_IRQ_SEL_SHIFT(line));
}

static void prvGpioAOsetupIRQ(uint16_t irqNum, uint8_t line, uint32_t flags)
{
	uint32_t val = 0;

	if (flags & IRQF_TRIGGER_BOTH)
		val |= AO_GPIO_IRQ_BOTH(line);

	if (flags & (IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING))
		val |= AO_GPIO_IRQ_EDGE(line);

	if (flags & (IRQF_TRIGGER_LOW | IRQF_TRIGGER_FALLING))
		val |= AO_GPIO_IRQ_POL(line);

	val |= (0x7 << AO_GPIO_IRQ_FILTER_SHIFT(line));

	val |= (irqNum << AO_GPIO_IRQ_SEL_SHIFT(line));

	if (GPIO_AO_IRQ_BASE == 0)
		return;

	REG32_UPDATE_BITS(GPIO_AO_IRQ_BASE,
			  (AO_GPIO_IRQ_POL_EDGE_MASK(line) | (AO_GPIO_IRQ_BOTH(line)) |
			   (0x7 << AO_GPIO_IRQ_FILTER_SHIFT(line)) |
			   (0xf << AO_GPIO_IRQ_SEL_SHIFT(line))),
			  val);
}

void prvGpioPlatIrqSetup(uint16_t irqNum, uint8_t line, uint32_t flags)
{
	if (irqNum > AO_GPIO_NUM)
		prvGpioEEsetupIRQ(irqNum, line, flags);
	else
		prvGpioAOsetupIRQ(irqNum, line, flags);
}
