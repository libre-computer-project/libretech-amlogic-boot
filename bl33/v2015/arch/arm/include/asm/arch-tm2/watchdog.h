/* SPDX-License-Identifier: (GPL-2.0+ OR MIT) */
/*
 * arch/arm/include/asm/arch-tm2/watchdog.h
 *
 * Copyright (C) 2020 Amlogic, Inc. All rights reserved.
 *
 */

#ifndef _BOOT_ROM_WATCHDOG_H
#define _BOOT_ROM_WATCHDOG_H

#include <asm/arch/secure_apb.h>

//#include "common.h"

void watchdog_init(uint32_t msec);
void watchdog_reset(void);
void reset_system(void);
void watchdog_disable(void);

/* uboot reset interface */
void reset_cpu(unsigned long flag);

#endif /* _BOOT_ROM_WATCHDOG_H */
