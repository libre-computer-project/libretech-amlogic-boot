// SPDX-License-Identifier: (GPL-2.0+ OR MIT)
/*
 * Copyright (c) 2019 Amlogic, Inc. All rights reserved.
 */

#include <config.h>
#include <asm/arch/io.h>
#include <asm/arch/cpu_sdio.h>
#include <asm/arch/secure_apb.h>
#include <amlogic/cpu_id.h>
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
	cpu_id_t cpuid = get_cpu_id();

	switch (port)
	{
	case SDIO_PORT_A:
		clrsetbits_le32(P_PERIPHS_PIN_MUX_3,
						0xFFFFFF, 0x111111);
		break;
	case SDIO_PORT_B:
		if (cpuid.chip_rev == 0xA)
			clrsetbits_le32(P_PAD_DS_REG1A, 0xFFFF, 0x5555);
		else if (cpuid.chip_rev == 0xB) {
			clrsetbits_le32(P_PAD_DS_REG1A, 0xFFFF, 0x5555);
			//setbits_le32(P_PAD_DS_REG1A, 0xFFFF);
			/* pull up & pull up enable */
			setbits_le32(P_PAD_PULL_UP_EN_REG1, 0x7F);
			setbits_le32(P_PAD_PULL_UP_REG1, 0x7F);
			clrbits_le32(P_PREG_PAD_GPIO5_O, 1<<17);
		}

		if (sd_debug_board_1bit_flag == 1)
			clrsetbits_le32(P_PERIPHS_PIN_MUX_9,
						((0xFF << 16) | 0xF), ((0x11 << 16) | 0x1));
		else
			clrsetbits_le32(P_PERIPHS_PIN_MUX_9,
						0xFFFFFF, 0x111111);
		break;
	case SDIO_PORT_C:
		/* set driver strength */
		if (cpuid.chip_rev == 0xA)
			writel(0x55555555, P_PAD_DS_REG0A);
		else if (cpuid.chip_rev == 0xB)
			writel(0xFFFFFFFF, P_PAD_DS_REG0A);
		/* pull up data by default */
		setbits_le32(P_PAD_PULL_UP_EN_REG0, 0x35ff);
		setbits_le32(P_PAD_PULL_UP_REG0, 0x35ff);
		/* set pinmux */
		writel(0x11111111, P_PERIPHS_PIN_MUX_0);
		clrsetbits_le32(P_PERIPHS_PIN_MUX_1,
						((0xFF << 16) | (0xF << 8) | 0xF),
						((0x1 << 20) | (0x1 << 8) | 0x1));
		/* hardware reset with pull boot12 */
		clrbits_le32(P_PREG_PAD_GPIO0_EN_N, 1<<12);
		clrbits_le32(P_PREG_PAD_GPIO0_O, 1<<12);
		udelay(10);
		setbits_le32(P_PREG_PAD_GPIO0_O, 1<<12);
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
	unsigned pinmux_9;

    switch (port) {

	case SDIO_PORT_A:
		break;
	case SDIO_PORT_B:
		pinmux_9 = readl(P_PERIPHS_PIN_MUX_9);
		clrbits_le32(P_PERIPHS_PIN_MUX_9, 0xF << 24);
		setbits_le32(P_PREG_PAD_GPIO1_EN_N, 1 << 6);
		setbits_le32(P_PAD_PULL_UP_EN_REG1, 1 << 6);
		setbits_le32(P_PAD_PULL_UP_REG1, 1 << 6);

		ret = readl(P_PREG_PAD_GPIO1_I) & (1 << 6);
		printf("%s\n", ret ? "card out" : "card in");
		if (!ret) {
			clrbits_le32(P_PERIPHS_PIN_MUX_9, 0xF << 12);
			setbits_le32(P_PREG_PAD_GPIO1_EN_N, 1 << 3);
			setbits_le32(P_PAD_PULL_UP_EN_REG1, 1 << 3);
			setbits_le32(P_PAD_PULL_UP_REG1, 1 << 3);
			/* debug board in when D3 is low */
			if (!(readl(P_PREG_PAD_GPIO1_I) & (1 << 3))) {
				/* switch uart to GPIOC(Card) */
				clrbits_le32(P_AO_RTI_PINMUX_REG0, 0xFF);
				clrsetbits_le32(P_PERIPHS_PIN_MUX_9, 0xFF << 8, 0x22 << 8);
				clrsetbits_le32(P_PERIPHS_PIN_MUX_9,
						((0xFF << 16) | 0xF), ((0x11 << 16) | 0x1));
				printf("sdio debug board detected\n");
				sd_debug_board_1bit_flag = 1;
			} else {
				//4bit card
				writel(pinmux_9, P_PERIPHS_PIN_MUX_9);
				sd_debug_board_1bit_flag = 0;
			}

		}
		break;
	default:
		break;
	}
	return ret;
}


