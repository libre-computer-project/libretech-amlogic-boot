/*
 * iPAQ h2200 board configuration
 *
 * Copyright (C) 2012 Lukasz Dalek <luk0104@gmail.com>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <common.h>
#include <asm/arch/pxa.h>
#include <asm/arch/pxa-regs.h>
#include <asm/io.h>
#include <usb.h>

DECLARE_GLOBAL_DATA_PTR;

int board_eth_init(bd_t *bis)
{
	usb_eth_initialize(bis);
	return 0;
}

void reset_cpu(ulong ignore)
{
	/* Enable VLIO interface on Hamcop */
	writeb(0x1, 0x4000);

	/* Reset board (cold reset) */
	writeb(0xff, 0x4002);
}

int board_init(void)
{
	/* We have RAM, disable cache */
	dcache_disable();
	icache_disable();

	gd->bd->bi_arch_number = MACH_TYPE_H2200;

	/* address of boot parameters */
	gd->bd->bi_boot_params = 0xa0000100;

	/* Let host see that device is disconnected */
	udc_disconnect();
	mdelay(500);

	return 0;
}

int dram_init(void)
{
	/*
	 * Everything except MSC0 was already set up by
	 * 1st stage bootloader.
	 *
	 * This setting enables access to companion chip.
	 */
	clrsetbits_le32(MSC0, 0xffffffff, CONFIG_SYS_MSC0_VAL);
	gd->ram_size = CONFIG_SYS_SDRAM_SIZE;
	return 0;
}
