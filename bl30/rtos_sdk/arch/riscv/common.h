/*
 * Copyright (c) 2021-2022 Amlogic, Inc. All rights reserved.
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef __COMMON_H
#define __COMMON_H

#ifdef __cplusplus
extern "C" {
#endif
#include <stdint.h>
#include <errno.h>

/* Macros to access registers */
#define REG32_ADDR(addr) ((volatile uint32_t *)(uintptr_t)(addr))
#define REG16_ADDR(addr) ((volatile uint16_t *)(uintptr_t)(addr))
#define REG8_ADDR(addr) ((volatile uint8_t *)(uintptr_t)(addr))

#define REG32(addr) (*REG32_ADDR(addr))
#define REG16(addr) (*REG16_ADDR(addr))
#define REG8(addr) (*REG8_ADDR(addr))

#define BIT(nr) (1UL << (nr))
#define REG32_UPDATE_BITS(addr, mask, val)                                                         \
	do {                                                                                       \
		uint32_t _v = REG32((unsigned long)addr);                                          \
		_v &= (~(mask));                                                                   \
		_v |= ((val) & (mask));                                                            \
		REG32((unsigned long)addr) = _v;                                                   \
	} while (0)

static inline int generic_ffs(int x)
{
	int r = 1;

	if (!x)
		return 0;
	if (!(x & 0xffff)) {
		x >>= 16;
		r += 16;
	}
	if (!(x & 0xff)) {
		x >>= 8;
		r += 8;
	}
	if (!(x & 0xf)) {
		x >>= 4;
		r += 4;
	}
	if (!(x & 3)) {
		x >>= 2;
		r += 2;
	}
	if (!(x & 1)) {
		x >>= 1;
		r += 1;
	}
	return r;
}
#define ffs(x) generic_ffs(x)

#ifndef FIELD_PREP
#define FIELD_PREP(_mask, _val) (((typeof(_mask))(_val) << (ffs(_mask) - 1)) & (_mask))
#endif

#ifndef FIELD_GET
#define FIELD_GET(_mask, _reg) ((typeof(_mask))(((_reg) & (_mask)) >> (ffs(_mask) - 1)))
#endif

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

#define BITS_PER_LONG (sizeof(unsigned long) == 8 ? 64 : 32)
#define GENMASK(h, l) (((~0UL) << (l)) & (~0UL >> (BITS_PER_LONG - 1 - (h))))
#define IS_ALIGNED(x, a) (((unsigned long)(x) & ((unsigned long)(a)-1)) == 0)
#define _RET_IP_ ((unsigned long)__builtin_return_address(0))
#define _THIS_IP_                                                                                  \
	({                                                                                         \
		__label__ __here;                                                                  \
__here:                                                                                    \
		(unsigned long)&&__here;                                                           \
	})
#define __round_mask(x, y) ((__typeof__(x))((y)-1))
#define round_up(x, y) ((((x)-1) | __round_mask(x, y)) + 1)
#define round_down(x, y) ((x) & ~__round_mask(x, y))

typedef uint64_t u64;
typedef uint32_t u32;
typedef uint16_t u16;
typedef uint8_t u8;
typedef int64_t s64;
typedef int32_t s32;
typedef int16_t s16;
typedef int8_t s8;

#ifndef BIT
#define BIT(x) (1 << (x))
#endif

#ifdef __cplusplus
}
#endif
#endif
