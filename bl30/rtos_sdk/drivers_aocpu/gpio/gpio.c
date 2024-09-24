/*
 * Copyright (c) 2021-2022 Amlogic, Inc. All rights reserved.
 *
 * SPDX-License-Identifier: MIT
 */

#include <stdio.h>
#include "FreeRTOS.h"
#include <register.h>
#include <common.h>
#include <task.h>
#include <gpio.h>
#include <stdbool.h>
#include "projdefs.h"
#include "gpio_drv.h"
#include "portmacro.h"

#define DRIVER_NAME "gpio"

struct BankBackup {
	uint32_t pinmux[4];
	uint32_t oen;
};

static struct BankBackup stateBackup[BANK_NUM_MAX];

static void prvEnterCritical(UBaseType_t *uxIsr)
{
	if (xPortIsIsrContext())
		*uxIsr = taskENTER_CRITICAL_FROM_ISR();
	else {
		taskENTER_CRITICAL();
		*uxIsr = 0;
	}
};

static void prvExitCritical(UBaseType_t uxSaveIsr)
{
	if (xPortIsIsrContext())
		taskEXIT_CRITICAL_FROM_ISR(uxSaveIsr);
	else {
		taskEXIT_CRITICAL();
		(void)uxSaveIsr;
	}
};

static inline void prvGpioRegWrite(uint32_t addr, uint32_t mask, uint32_t val)
{
	UBaseType_t uxSavedIsr;

	prvEnterCritical(&uxSavedIsr);
	REG32_UPDATE_BITS(addr, mask, val);
	prvExitCritical(uxSavedIsr);
}

static inline void prvGpioCalcRegAndBit(const struct GpioBank *bk, uint8_t offset,
					enum GpioRegType regType, uint16_t *reg, uint8_t *bit)
{
	*reg = bk->regs[regType].reg << 2;
	*bit = bk->regs[regType].bit + offset;
}

static inline void prvGpioGetBankAndOffset(uint16_t gpio, const struct GpioBank **bk, uint8_t *off)
{
	const struct GpioBank *gpk;

	gpk = pGetGpioBank();
	*bk = &gpk[gpio >> 5];
	*off = gpio % 32;
}

int xGpioSetDir(uint16_t gpio, enum GpioDirType dir)
{
	uint16_t reg;
	uint8_t bit;
	uint8_t offset;
	const struct GpioBank *bk;

	if (dir >= GPIO_DIR_INVALID) {
		printf("%s: invalid DIR [OUT=0, IN=1]: %d\n", DRIVER_NAME, dir);
		return -pdFREERTOS_ERRNO_EINVAL;
	}

	prvGpioGetBankAndOffset(gpio, &bk, &offset);

	prvGpioCalcRegAndBit(bk, offset, REG_DIR, &reg, &bit);

	prvGpioRegWrite(bk->domain->rGpio + reg, BIT(bit), dir ? BIT(bit) : 0);

	return 0;
}

int xGpioSetValue(uint16_t gpio, enum GpioOutLevelType level)
{
	uint16_t reg;
	uint8_t bit;
	uint8_t offset;
	const struct GpioBank *bk;

	if (level >= GPIO_LEVEL_INVALID) {
		printf("%s: invalid output level [LOW=1, HIGH=0]: %d\n", DRIVER_NAME, level);
		return -pdFREERTOS_ERRNO_EINVAL;
	}

	prvGpioGetBankAndOffset(gpio, &bk, &offset);

	prvGpioCalcRegAndBit(bk, offset, REG_OUT, &reg, &bit);

	prvGpioRegWrite(bk->domain->rGpio + reg, BIT(bit), level ? BIT(bit) : 0);

	return 0;
}

int xGpioGetValue(uint16_t gpio)
{
	uint16_t reg;
	uint8_t bit;
	uint8_t offset;
	const struct GpioBank *bk;

	prvGpioGetBankAndOffset(gpio, &bk, &offset);

	prvGpioCalcRegAndBit(bk, offset, REG_IN, &reg, &bit);

	return !!(REG32((unsigned long)bk->domain->rGpio + reg) & BIT(bit));
}

int xPinconfSet(uint16_t gpio, uint32_t flags)
{
	uint16_t reg;
	uint8_t bit;
	uint8_t offset;
	uint8_t ds_value = 0;
	const struct GpioBank *bk;
	const struct GpioRegDesc *desc;

	prvGpioGetBankAndOffset(gpio, &bk, &offset);

	prvGpioCalcRegAndBit(bk, offset, REG_PULLEN, &reg, &bit);

	if (flags & PINF_CONFIG_BIAS_DISABLE) {
		prvGpioRegWrite(bk->domain->rPullen + reg, BIT(bit), 0);
	} else if (flags & (PINF_CONFIG_BIAS_PULL_UP | PINF_CONFIG_BIAS_PULL_DOWN)) {
		prvGpioRegWrite(bk->domain->rPullen + reg, BIT(bit), BIT(bit));

		prvGpioCalcRegAndBit(bk, offset, REG_PULL, &reg, &bit);
		if (flags & PINF_CONFIG_BIAS_PULL_UP)
			prvGpioRegWrite(bk->domain->rPull + reg, BIT(bit), BIT(bit));
		else
			prvGpioRegWrite(bk->domain->rPull + reg, BIT(bit), 0);
	}

	if ((flags & PINF_CONFIG_DRV_MASK) && &bk->regs[REG_DRV] != 0) {
		prvGpioCalcRegAndBit(bk, offset, REG_DRV, &reg, &bit);
		desc = &bk->regs[REG_DRV];

		reg = desc->reg + ((desc->bit + (offset << 1)) >> 5);
		bit = (desc->bit + (offset << 1)) % 32;

		if (flags & PINF_CONFIG_DRV_STRENGTH_0)
			ds_value = 0;
		else if (flags & PINF_CONFIG_DRV_STRENGTH_1)
			ds_value = 1;
		else if (flags & PINF_CONFIG_DRV_STRENGTH_2)
			ds_value = 2;
		else if (flags & PINF_CONFIG_DRV_STRENGTH_3)
			ds_value = 3;

		prvGpioRegWrite(bk->domain->rDrv + (reg << 2), 0x3 << bit, ds_value << bit);
	}

	return 0;
}

int xPinmuxSet(uint16_t gpio, enum PinMuxType func)
{
	uint16_t reg;
	uint8_t bit;
	uint8_t offset;
	const struct GpioBank *bk;
	const struct GpioRegDesc *desc;

	if (func >= PIN_FUNC_INVALID) {
		printf("%s: invalid pin Function [0 - %d]: %d\n", DRIVER_NAME, PIN_FUNC_INVALID - 1,
		       func);
		return -pdFREERTOS_ERRNO_EINVAL;
	}

	prvGpioGetBankAndOffset(gpio, &bk, &offset);
	desc = &bk->regs[REG_MUX];

	reg = desc->reg + ((desc->bit + (offset << 2)) >> 5);
	bit = (desc->bit + (offset << 2)) % 32;

	prvGpioRegWrite(bk->domain->rMux + (reg << 2), 0xf << bit, func << bit);

	return 0;
}

static void prvOenStateHandle(const struct GpioBank *bk, struct BankBackup *bbk, bool isBackup)
{
	uint8_t reg, bit, end;

	bit = bk->regs[REG_DIR].bit;
	end = bit + bk->pin_num;
	reg = bk->regs[REG_DIR].reg;

	while (bit < end) {
		if (isBackup) {
			bbk->oen &= ~(0x1 << bit);
			bbk->oen |= REG32(bk->domain->rGpio + (reg << 2)) & (0x1 << bit);
			prvGpioRegWrite(bk->domain->rGpio + (reg << 2), 0x1 << bit, 0x1 << bit);
		} else {
			prvGpioRegWrite(bk->domain->rGpio + (reg << 2), 0x1 << bit, bbk->oen);
		}
		bit++;
	}
}

static void prvPinmuxStateHandle(const struct GpioBank *bk, struct BankBackup *bbk, bool isBackup)
{
	uint8_t reg, offset, bit, begin, end;

	begin = bk->regs[REG_MUX].bit;
	end = begin + bk->pin_num * 4;
	reg = bk->regs[REG_MUX].reg;

	while (begin < end) {
		offset = begin >> 5;
		bit = begin & 0x1f;
		if (isBackup) {
			bbk->pinmux[offset] &= ~(0xf << bit);
			bbk->pinmux[offset] |= REG32(bk->domain->rMux + ((reg + offset) << 2)) &
					       (0xf << bit);
			prvGpioRegWrite(bk->domain->rMux + ((reg + offset) << 2), 0xf << bit, 0);
		} else {
			prvGpioRegWrite(bk->domain->rMux + ((reg + offset) << 2), 0xf << bit,
					bbk->pinmux[offset]);
		}
		begin += 4;
	}
}

static int prvStrCaseCmp(const char *string1, const char *string2)
{
	char value;
	char *lp = (char *)string1;
	char *rp = (char *)string2;

	while (*lp && *rp) {
		value = ((*lp >= 'A' && *lp <= 'Z') ? (*lp - 'A' + 'a') : *lp) -
			((*rp >= 'A' && *rp <= 'Z') ? (*rp - 'A' + 'a') : *rp);
		if (value)
			return value;
		lp++;
		rp++;
	}

	return *lp - *rp;
}

static int prvBankCheck(const char *name, const struct GpioBank **bk)
{
	int index;
	const struct GpioBank *gpk = pGetGpioBank();

	/* Find bank */
	for (index = 0; index < BANK_NUM_MAX; index++) {
		if (!prvStrCaseCmp(gpk[index].name, name)) {
			*bk = &gpk[index];
			break;
		}
	}

	if (index == BANK_NUM_MAX)
		return -pdFREERTOS_ERRNO_ENXIO;

	if (!(*bk)->pin_num)
		return -pdFREERTOS_ERRNO_EINVAL;

	return index;
}

int xBankStateBackup(const char *name)
{
	int index;
	const struct GpioBank *bk;

	index = prvBankCheck(name, &bk);
	if (index < 0)
		return index;

	prvOenStateHandle(bk, &stateBackup[index], true);
	prvPinmuxStateHandle(bk, &stateBackup[index], true);

	return 0;
}

int xBankStateRestore(const char *name)
{
	int index;
	const struct GpioBank *bk;

	index = prvBankCheck(name, &bk);
	if (index < 0)
		return index;

	prvPinmuxStateHandle(bk, &stateBackup[index], false);
	prvOenStateHandle(bk, &stateBackup[index], false);

	return 0;
}
