/* SPDX-License-Identifier: (GPL-2.0+ OR MIT) */
/*
 * arch/arm/cpu/armv8/t5d/sdio.c
 *
 * Copyright (C) 2020 Amlogic, Inc. All rights reserved.
 *
 */

#include <config.h>
#include <asm/arch/io.h>
#include <asm/arch/cpu_sdio.h>
#include <asm/arch/secure_apb.h>
#include <asm/cpu_id.h>
#include <common.h>

void  cpu_sd_emmc_pwr_prepare(unsigned port)
{
//    switch(port)
//    {
//        case SDIO_PORT_A:
//            clrbits_le32(P_PREG_PAD_GPIO4_EN_N,0x30f);
//            clrbits_le32(P_PREG_PAD_GPIO4_O   ,0x30f);
//            clrbits_le32(P_PERIPHS_PIN_MUX_8,0x3f);
//            break;
//        case SDIO_PORT_B:
//            clrbits_le32(P_PREG_PAD_GPIO5_EN_N,0x3f<<23);
//            clrbits_le32(P_PREG_PAD_GPIO5_O   ,0x3f<<23);
//            clrbits_le32(P_PERIPHS_PIN_MUX_2,0x3f<<10);
//            break;
//        case SDIO_PORT_C:
//            //clrbits_le32(P_PREG_PAD_GPIO3_EN_N,0xc0f);
//            //clrbits_le32(P_PREG_PAD_GPIO3_O   ,0xc0f);
//            //clrbits_le32(P_PERIPHS_PIN_MUX_6,(0x3f<<24));break;
//            break;
//    }

    /**
        do nothing here
    */
}
unsigned sd_debug_board_1bit_flag = 0;
int cpu_sd_emmc_init(unsigned port)
{
	switch (port)
	{
	case SDIO_PORT_A:
		clrsetbits_le32(P_PERIPHS_PIN_MUX_3,
						0xFFFFFF, 0x111111);
		break;
	case SDIO_PORT_B:
		clrsetbits_le32(P_PAD_DS_REG5A, 0xFFF, 0xaaa);
		setbits_le32(P_PAD_PULL_UP_EN_REG5, 0x3F);
		setbits_le32(P_PAD_PULL_UP_REG5, 0x3F);
		/*
		clrbits_le32(P_PREG_PAD_GPIO5_O, 1<<17);
		*/
		clrsetbits_le32(P_PERIPHS_PIN_MUX_F,
				0xFFFFFF, 0x111111);
		break;
	case SDIO_PORT_C:
		/* set driver strength */
		clrsetbits_le32(P_PAD_DS_REG0A, 0XFFFFFF, 0XABAAAA);
		/* pull up data by default */
		setbits_le32(P_PAD_PULL_UP_EN_REG0, 0xfff);
		setbits_le32(P_PAD_PULL_UP_REG0, 0xfff);

		/* set pinmux */
		writel(0x11111111, P_PERIPHS_PIN_MUX_0);
		clrsetbits_le32(P_PERIPHS_PIN_MUX_1,
						(0xFFFF),
						((0x1 << 12) | (0x1 << 8) | 0x1));
		/* hardware reset with pull boot9 */
		clrbits_le32(P_PREG_PAD_GPIO0_EN_N, 1<<9);
		clrbits_le32(P_PREG_PAD_GPIO0_O, 1<<9);
		udelay(10);
		setbits_le32(P_PREG_PAD_GPIO0_O, 1<<9);
		break;
	default:
		return -1;
	}
	return 0;
}

/* return:
	0: insert
	1: not insert
 */
__weak int  sd_emmc_detect(unsigned port)
{
	int ret = 0;
	unsigned int pinmux_f;
    switch (port) {
	case SDIO_PORT_A:
		break;
	case SDIO_PORT_B:
		pinmux_f = readl(P_PERIPHS_PIN_MUX_F);
		clrbits_le32(P_PERIPHS_PIN_MUX_G, 0xF << 8);
		setbits_le32(P_PREG_PAD_GPIO5_EN_N, 1 << 10);
		setbits_le32(P_PAD_PULL_UP_EN_REG5, 1 << 10);
		setbits_le32(P_PAD_PULL_UP_REG5, 1 << 10);

		ret = readl(P_PREG_PAD_GPIO5_I) & (1 << 10);
		printf("%s\n", ret ? "card out" : "card in");
		if (!ret) {
			clrbits_le32(P_PERIPHS_PIN_MUX_F, 0xF << 12);
			setbits_le32(P_PREG_PAD_GPIO5_EN_N, 1 << 3);
			setbits_le32(P_PAD_PULL_UP_EN_REG5, 1 << 3);
			setbits_le32(P_PAD_PULL_UP_REG5, 1 << 3);
			if (!(readl(P_PREG_PAD_GPIO5_I) & (1 << 3))) {
				printf("error: debug board is not support in t5w\n");
			} else {
				//4bit card
				writel(pinmux_f, P_PERIPHS_PIN_MUX_F);
				sd_debug_board_1bit_flag = 0;
			}

		}
		break;
	default:
		break;
	}
	return ret;
}

__weak void sd_emmc_para_config(struct sd_emmc_global_regs *reg,
		unsigned int clock, unsigned int port)
{
	unsigned int clk = reg->gclock;

	if (port == SDIO_PORT_C || port == SDIO_PORT_B) {
		clk &= ~(3 << Cfg_co_phase);
		clk |= (3 << Cfg_co_phase);
	}
	reg->gclock = clk;
	return;
}
