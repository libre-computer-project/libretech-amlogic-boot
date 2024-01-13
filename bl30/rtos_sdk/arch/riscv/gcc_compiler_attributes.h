/*
 * Copyright (c) 2021-2022 Amlogic, Inc. All rights reserved.
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef __GCC_COMPILER_ATTRIBUTES_H__
#define __GCC_COMPILER_ATTRIBUTES_H__

#ifndef __weak
#define __weak __attribute__((__weak__))
#endif

#ifndef __noinline
#define __noinline __attribute__((noinline))
#endif

#ifndef __packed
#define __packed __attribute__((__packed__))
#endif

#endif /* __GCC_COMPILER_ATTRIBUTES_H__ */
