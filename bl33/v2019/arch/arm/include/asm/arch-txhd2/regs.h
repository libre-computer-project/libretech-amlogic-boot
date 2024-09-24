/* SPDX-License-Identifier: (GPL-2.0+ OR MIT) */
/*
 * arch/arm/include/asm/arch-t5d/regs.h
 *
 * Copyright (C) 2020 Amlogic, Inc. All rights reserved.
 *
 */

#ifndef __AML_REG_H__
#define __AML_REG_H__
/*
 * all ramdump used regs
 */
/*
 * REG_MDUMP_ISA_TIMERE    use ISA_TIMERE    (SYSCTRL_TIMERE)
 * REG_MDUMP_WATCHDOG_CNTL use WATCHDOG_CNTL (RESETCTRL_WATCHDOG_CTRL0)
 * REG_MDUMP_WATCHDOG_TCNT use WATCHDOG_TCNT (RESETCTRL_WATCHDOG_CNT)
 * REG_MDUMP_WATCHDOG_RST  use WATCHDOG_RST  (RESETCTRL_WATCHDOG_CLR)
 */
#define REG_MDUMP_ISA_TIMERE        (volatile uint32_t *)((0x3c62  << 2) + 0xffd00000)
#define REG_MDUMP_WATCHDOG_CNTL     (volatile uint32_t *)((0x3c34  << 2) + 0xffd00000)
#define REG_MDUMP_WATCHDOG_TCNT     (volatile uint32_t *)((0x3c36  << 2) + 0xffd00000)
#define REG_MDUMP_WATCHDOG_RST      (volatile uint32_t *)((0x3c37  << 2) + 0xffd00000)

/*
 * REG_MDUMP_CPUBOOT_STATUS  use SYSCTRL_STICKY_REG6
 * REG_MDUMP_COMPRESS_BASE   use SYSCTRL_DEBUG_REG6 (P_AO_SEC_GP_CFG12)
 * REG_MDUMP_COMPRESS_SIZE   use SYSCTRL_DEBUG_REG7 (P_AO_SEC_GP_CFG13)
 * REG_MDUMP_REBOOT_MODE     use AO_SEC_SD_CFG15
 */
#define REG_MDUMP_CPUBOOT_STATUS    (0xff634400 + (0x78 << 2)) /* boot status */
#define REG_MDUMP_COMPRESS_BASE     (0xff800000 + (0x9c << 2)) /* ram compress size */
#define REG_MDUMP_COMPRESS_SIZE     (0xff800000 + (0x9d << 2)) /* ram compress start addrs */
#define REG_MDUMP_REBOOT_MODE       (0xff800000 + (0x8f << 2)) /* reboot mode */

/*
 * REG_MDUMP_SERIAL_PINMUX   use P_AO_RTI_PINMUX_REG0 (PADCTRL_PIN_MUX_REG0)
 * REG_MDUMP_TIMEBASE_CNTL   use P_AO_TIMEBASE_CNTL1 (CLKTREE_TIMEBASE_CTRL1)
 * REG_MDUMP_UART_WFIFO      use AO_UART_WFIFO (UART_B_WFIFO)
 */
#define REG_MDUMP_SERIAL_PINMUX     (0xff800000 + (0x05 << 2))
#define REG_MDUMP_TIMEBASE_CNTL     (0xff800000 + (0x15 << 2))
#define REG_MDUMP_UART_WFIFO        ((0x8c00  << 2) + 0xffd00000)

/*
 * proting from cmd/amlogic/cmd_rsvmem.c, do_rsvmem_dump.
 * #if defined(P_AO_SEC_GP_CFG3) //secure_apb.h, only g12a/g12b/t5w/txhd2/...
 *     #define REG_RSVMEM_SIZE        P_AO_SEC_GP_CFG3
 *     #define REG_RSVMEM_BL32_START  P_AO_SEC_GP_CFG4
 *     #define REG_RSVMEM_BL31_START  P_AO_SEC_GP_CFG5
 * #elif defined(SYSCTRL_SEC_STATUS_REG15) //register.h
 *     #define REG_RSVMEM_SIZE        SYSCTRL_SEC_STATUS_REG15
 *     #define REG_RSVMEM_BL32_START  SYSCTRL_SEC_STATUS_REG16
 *     #define REG_RSVMEM_BL31_START  SYSCTRL_SEC_STATUS_REG17
 * #endif
 */
#define REG_MDUMP_RSVMEM_SIZE       (0xff800000 + (0x093 << 2))
#define REG_MDUMP_RSVMEM_BL32_START (0xff800000 + (0x094 << 2))
#define REG_MDUMP_RSVMEM_BL31_START (0xff800000 + (0x095 << 2))

#endif
