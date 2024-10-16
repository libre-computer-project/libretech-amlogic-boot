/* SPDX-License-Identifier: (GPL-2.0+ OR MIT) */
/*
 * arch/arm/include/asm/arch-gxl/thermal.h
 *
 * Copyright (C) 2020 Amlogic, Inc. All rights reserved.
 *
 */

#define SAR_ADC_BASE			0xc1100000+0x21a0*4

#define SAR_ADC_REG0 			SAR_ADC_BASE +(0x0*4)//0xc1108680
#define SAR_ADC_CHAN_LIST		SAR_ADC_BASE +(0x1*4)//0xc1108684
#define SAR_ADC_AVG_CNTL		SAR_ADC_BASE +(0x2*4)//0xc1108688
#define SAR_ADC_REG3			SAR_ADC_BASE +(0x3*4)//0xc110868c
#define SAR_ADC_DELAY			SAR_ADC_BASE +(0x4*4)//0xc1108690
#define SAR_ADC_LAST_RD			SAR_ADC_BASE +(0x5*4)//0xc1108694
#define SAR_ADC_FIFO_RD			SAR_ADC_BASE +(0x6*4)//0xc1108698
#define SAR_ADC_AUX_SW			SAR_ADC_BASE +(0x7*4)//0xc110869c
#define SAR_ADC_CHAN_10_SW		SAR_ADC_BASE +(0x8*4)//0xc11086a0
#define SAR_ADC_DETECT_IDLE_SW	SAR_ADC_BASE +(0x9*4)//0xc11086a4
#define SAR_ADC_DELTA_10		SAR_ADC_BASE +(0xa*4)//0xc11086a8
#define SAR_ADC_REG11			SAR_ADC_BASE +(0xb*4)//0xc11086ac
#define SAR_ADC_REG12			(SAR_ADC_BASE + (0xc<<2))
#define SAR_ADC_REG13			(SAR_ADC_BASE + (0xd<<2))

#define SAR_CLK_CNTL			HHI_SAR_CLK_CNTL
#define SAR_BUS_CLK_EN			HHI_GCLK_MPEG2

#define EN_BIT					22
#define FLAG_BUSY_KERNEL		(1<<14)
#define FLAG_BUSY_BL30			(1<<15)

#define SAMPLE_BIT_MASK			0xfff  /*12bit*/
