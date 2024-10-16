/*
 * (C) Copyright 2008 Stefan Roese <sr@denx.de>, DENX Software Engineering
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#define GPIO1_BASE		0x00088000
#define GPIO2_BASE		0x0008c000

/* Instances */
#define GPIO_INSTANCES		2

/*  Relative offsets of the register addresses */
#define GPIO_SWPORTA_DR_OFFS	0x00000000
#define GPIO_SWPORTA_DR(base)	((base) + GPIO_SWPORTA_DR_OFFS)
#define GPIO_SWPORTA_DDR_OFFS	0x00000004
#define GPIO_SWPORTA_DDR(base)	((base) + GPIO_SWPORTA_DDR_OFFS)
#define GPIO_EXT_PORTA_OFFS	0x00000050
#define GPIO_EXT_PORTA(base)	((base) + GPIO_EXT_PORTA_OFFS)
