/* SPDX-License-Identifier: (GPL-2.0+ OR MIT) */
/*
 * arch/arm/include/asm/arch-t5/ddr_define.h
 *
 * Copyright (C) 2020 Amlogic, Inc. All rights reserved.
 *
 */

/* board id */
#define CONFIG_BOARD_ID_MASK					0xFF
#define CONFIG_FW_INFO_MASK						0xFFFFFFFF

#define RESULT_OK							0x0
#define RESULT_FAIL							0xFF
#define RESULT_PLL_LOCK_FAIL				0x0F
#define RESULT_USB_BOOT_NEVER				0xF0

#define DDR_HDTCTRL_ENABLE_AMLOGIC_DDR4_PHY_VREF_CORRECTION					0x7
#define DDR_HDTCTRL_SHOW_DDR3_LPDDR3_TRAINING_MARGIN						0x9
#define DDR_HDTCTRL_SHOW_DDR3_LPDDR3_TRAINING_MARGIN_WRITE_DQ				0x00210005
#define DDR_HDTCTRL_SHOW_DDR3_LPDDR3_TRAINING_MARGIN_WRITE_DQM				0x00290005
#define DDR_HDTCTRL_SHOW_DDR3_LPDDR3_TRAINING_MARGIN_READ_DQ				0x003a0005

#define DDR_HDTCTRL_SHOW_DDR4_TRAINING_EYE_DATA_READ_START_1				0x00200004
#define DDR_HDTCTRL_SHOW_DDR4_TRAINING_EYE_DATA_READ_START_2				0x001e0004
#define DDR_HDTCTRL_SHOW_DDR4_TRAINING_EYE_DATA_READ_VREF					0x0014001f
#define DDR_HDTCTRL_SHOW_DDR4_TRAINING_EYE_DATA_READ_VREF_END				0x00610000

#define DDR_HDTCTRL_SHOW_DDR4_TRAINING_EYE_DATA_WRITE_START_1				0x001c0004
#define DDR_HDTCTRL_SHOW_DDR4_TRAINING_EYE_DATA_WRITE_START_2				0x00230004
#define DDR_HDTCTRL_SHOW_LPDDR4_TRAINING_TDQS2DQ							0x00dd0002
//#define DDR_HDTCTRL_SHOW_DDR4_TRAINING_EYE_DATA_WRITE_VREF				0x0014001f
//#define DDR_HDTCTRL_SHOW_DDR4_TRAINING_EYE_DATA_WRITE_VREF_END			0x00610000
#define DMC_PSTATE_MAX						4

#define CONFIG_CHIP_TYPE_DRAM				0x1F
#define CONFIG_CHIP_TYPE_PSRAM				0x2F
#define CONFIG_DDR_TYPE_DDR3				0
#define CONFIG_DDR_TYPE_DDR4				1
#define CONFIG_DDR_TYPE_LPDDR4				2
#define CONFIG_DDR_TYPE_LPDDR3				3
#define CONFIG_DDR_TYPE_LPDDR2				4
//#define CONFIG_DDR_TYPE_LPDDR4X				5
#define CONFIG_DDR_TYPE_AUTO				0xf
#define CONFIG_DDR_TYPE_AUTO_LIMIT			CONFIG_DDR_TYPE_DDR4

/* lpddr3 related define */
#define CONFIG_LPDDR3_CA_TRAINING_USE_LANE0		0
#define CONFIG_LPDDR3_CA_TRAINING_USE_LANE1		1
#define CONFIG_LPDDR3_CA_TRAINING_USE_LANE2		2
#define CONFIG_LPDDR3_CA_TRAINING_USE_LANE3		3

#define LPDDR_DIE_ROW_COL_R13_C9			0
#define LPDDR_DIE_ROW_COL_R14_C9			1
#define LPDDR_DIE_ROW_COL_R14_C10			2
#define LPDDR_DIE_ROW_COL_R13_C10			3
#define LPDDR_DIE_ROW_COL_R14_C11			4

#if 0
/* ddr channel defines */
#define CONFIG_DDR0_16BIT					1
#define CONFIG_DDR0_RANK0					2
#define CONFIG_DDR0_RANK01					3
#define CONFIG_DDR0_16BIT_2					4
#define CONFIG_DDR_CHL_AUTO					0xF
#define CONFIG_DDR0_16BIT_CH0				0x1
#define CONFIG_DDR0_16BIT_RANK01_CH0		0x4
#define CONFIG_DDR0_32BIT_RANK0_CH0			0x2
#define CONFIG_DDR0_32BIT_RANK01_CH01		0x3
#define CONFIG_DDR0_32BIT_16BIT_RANK0_CH0	0x5
#define CONFIG_DDR0_32BIT_16BIT_RANK01_CH0	0x6
#define CONFIG_DDR0_32BIT_RANK01_CH0		0x7
#define CONFIG_DDR0_32BIT_RANK0_CH01		0x8
#define ENABLE_SKIP_1D_MEM_LOAD  0x0
#define ENABLE_SKIP_1D_MEM_TRAINING  0x1
#define ENABLE_SKIP_2D_MEM_LOAD  0x2
#define ENABLE_SKIP_2D_MEM_TRAINING  0x3

#define PHY_IMEM_STEP_1D  0x1
#define PHY_IMEM_STEP_2D  0x2

#endif
#define VREF_SOC        0x1
#define VREF_DRAM       0x2


#define CFG_DDR_BASE_ADDR					0X0
#define CFG_DDR_START_OFFSET				0X01000000 //SKIP 16MB

/* ddr type identifier */
#define CONFIG_DDR_TIMMING_LPDDR2			0x02
#define CONFIG_DDR_TIMMING_LPDDR3			0x03
#define CONFIG_DDR_TIMMING_DDR3_7			0x07
#define CONFIG_DDR_TIMMING_DDR3_9			0x09
#define CONFIG_DDR_TIMMING_DDR3_11			0x0B
#define CONFIG_DDR_TIMMING_DDR3_12			0x0C
#define CONFIG_DDR_TIMMING_DDR3_13			0x0D
#define CONFIG_DDR_TIMMING_DDR3_14			0x0E

#define CONFIG_DDR_TIMMING_DDR4_1600		0x0F
#define CONFIG_DDR_TIMMING_DDR4_1866		0x10
#define CONFIG_DDR_TIMMING_DDR4_2133		0x11
#define CONFIG_DDR_TIMMING_DDR4_2400		0x12
#define CONFIG_DDR_TIMMING_DDR4_2666		0x13
#define CONFIG_DDR_TIMMING_DDR4_3200		0x14

#define CONFIG_DDR_FUNC_TEST				(1<<0)

#define CONFIG_DDR_INIT_RETRY_TOTAL			(10)
#define CONFIG_DDR_PCTL_RETRY_TOTAL			(100)

#define DDR_USE_1_RANK(chl_set)	((chl_set == CONFIG_DDR0_RANK0) || \
				(chl_set == CONFIG_DDR0_16BIT))
#define DDR_USE_2_RANK(chl_set)	((chl_set == CONFIG_DDR0_RANK01) || \
				(chl_set == CONFIG_DDR0_16BIT_2))

#ifndef CONFIG_LPDDR3_CA_TRAINING_CA0
#define CONFIG_LPDDR3_CA_TRAINING_CA0	CONFIG_LPDDR3_CA_TRAINING_USE_LANE0
#endif
#ifndef CONFIG_LPDDR3_CA_TRAINING_CA1
#define CONFIG_LPDDR3_CA_TRAINING_CA1	CONFIG_LPDDR3_CA_TRAINING_USE_LANE1
#endif

/* DMC_DDR_CTRL defines */
#define DDR_DDR4_ENABLE						(1<<22)
#define DDR_RANK1_ENABLE					(1<<21)
#define DDR_DDR4_BG_ENABLE					(1<<20)
#define DDR_16BIT_ENABLE					(1<<16)

#define DDR_RANK1_SIZE_CTRL					(3)
#define DDR_RANK0_SIZE_CTRL					(0)

/* ddr functions */
#define DDR_FUNC_D2PLL						(1<<0)
#define DDR_FUNC_LP							(1<<1)
#define DDR_FUNC_ZQ_PD						(1<<2)
#define DDR_FUNC_EXT_VREF					(1<<3)
#define DDR_FUNC_DDR4_TIMING_TEST			(1<<4)
#define DDR_FUNC_DDR_PLL_BYPASS				(1<<5)
#define DDR_FUNC_RDBI						(1<<6)
#define DDR_FUNC_LPDDR3_CA					(1<<7)
#define DDR_FUNC_PRINT_WINDOW				(1<<8)
#define DDR_FUNC_FULL_TEST					(1<<10)
#define DDR_FUNC_NONSEC_SCRAMBLE			(1<<11)
#define DDR_FUNC_LPDDR3_CA_CA0_BIT0			(1<<20)
#define DDR_FUNC_LPDDR3_CA_CA0_BIT1			(1<<21)
#define DDR_FUNC_LPDDR3_CA_CA1_BIT0			(1<<22)
#define DDR_FUNC_LPDDR3_CA_CA1_BIT1			(1<<23)
#define DDR_FUNC_LPDDR3_CA_CA0_OFFSET		(20)
#define DDR_FUNC_LPDDR3_CA_CA1_OFFSET		(22)
#define DDR_FUNC_LPDDR3_SOC_ODT_ONLY_UP		(1<<25)
#define DDR_FUNC_ENABLE_DDR_ID				(1 << 26)
#define DDR_FUNC_CONFIG_DDR_DVFS_FUNCTION	(1<<28)
#define DDR_FUNC_CONFIG_DFE_FUNCTION		(1<<29)
#define DDR_FUNC_FAST_BOOT_CHECK_CHIP_ID	(1<<30)
#define DDR_FUNC_SCRAMBLE					(1<<31)

#define DDR_FUNC							(0)

/* dwc imem/dmem */
#define DWC_MEM_LOAD_ADDR					0xFFFE0000
#define DWC_IRAM_ADDR						(0x50000)
#define DWC_IRAM_SIZE						(0x8000) /* 32K */
#define DWC_DRAM_ADDR						(0x54000)
#define DWC_DRAM_SIZE						(0x4000) /* 16K */

/* dwc apb regs */
#define UctWriteProtShadow					0xd0004
#define UctWriteOnlyShadow					0xd0032
#define UctWriteProt						0xd0031
#define UctDatWriteOnlyShadow				0xd0034

/* pctl status */
#define UPCTL_STAT_MASK					(7)
#define UPCTL_STAT_INIT					(0)
#define UPCTL_STAT_CONFIG					(1)
#define UPCTL_STAT_ACCESS					(3)
#define UPCTL_STAT_LOW_POWER				(5)

/* pctl cmds */
#define UPCTL_CMD_INIT						(0)
#define UPCTL_CMD_CONFIG					(1)
#define UPCTL_CMD_GO						(2)
#define UPCTL_CMD_SLEEP						(3)
#define UPCTL_CMD_WAKEUP					(4)


/* name id defined in firmware header */
#define DDR_NAME_ID_AML_FW						0x304c4d41 //AML0
#define DDR_NAME_ID_PIEI						0x61656165 //eaea
#define DDR_NAME_ID_DDR3						0x33333364 //d333
#define DDR_NAME_ID_DDR4						0x34343464 //d444
#define DDR_NAME_ID_DDR4_2D						0x32323464 //d422
#define DDR_NAME_ID_LPDDR3						0x33336C64 //dl33
#define DDR_NAME_ID_LPDDR4						0x34346C64 //dl44
#define DDR_NAME_ID_LPDDR4_2D					0x30346C64 //dl42
#define DDR_NAME_ID_DIAGNOSE1					0x31676464 //ddg1
#define DDR_NAME_ID_DIAGNOSE2					0x32676464 //ddg2
/* PIEI */
#define DDR_PIEI_START_FLAG						0xfeed //eaea

/* dram cfg magic */
#define DRAM_CFG_MAGIC							0x2e676663

/* flow control */
#define DDR_FIRMWARE_VERSION_1					0x00201709
#define FW_LOAD_STEP_AML_FW						0xF
#define FW_LOAD_STEP_PIEI						0
#define FW_LOAD_STEP_1D							1
#define FW_LOAD_STEP_2D							2
#define FW_LOAD_STEP_DIAG1						3
#define FW_LOAD_STEP_DIAG2						4

/* basic defines */
#define AML_AC_PINMUX_G0_TOTAL						6
#define AML_AC_PINMUX_G1_TOTAL						29
#define AML_DFI_PINMUX_TOTAL					26
#define AML_DQ_PINMUX_TOTAL						36
#define AML_DQ_BYTES_TOTAL						4


/* d2pll defines */
#define D2PLL_ENABLE									1
#define DDR_STICKY_MAGIC_NUMBER							0x20180000
#define DDR_CHIP_ID										0x30
#define DDR_STICKY_OVERRIDE_CONFIG_MESSAGE_CMD			0x1 //override config
#define DDR_STICKY_SPECIAL_FUNCTION_CMD					0x2 //special test such as shift some bdlr or parameter or interleave test
#define DDR_INIT_CONFIG_STICKY_MESSAGE_SRAM_ADDRESS		0x00040000
#define DDR_INIT_CONFIG_GLOBAL_MESSAGE_SRAM_ADDRESS		0x00050000


/* debug function*/

/* ddr configs */
#define DDR_RFC_TYPE_DDR3_512Mbx1				0
#define DDR_RFC_TYPE_DDR3_512Mbx2				1
#define DDR_RFC_TYPE_DDR3_512Mbx4				2
#define DDR_RFC_TYPE_DDR3_512Mbx8				3
#define DDR_RFC_TYPE_DDR3_512Mbx16				4
#define DDR_RFC_TYPE_DDR4_2Gbx1					5
#define DDR_RFC_TYPE_DDR4_2Gbx2					6
#define DDR_RFC_TYPE_DDR4_2Gbx4					7
#define DDR_RFC_TYPE_DDR4_2Gbx8					8

#define DDR_RFC_TYPE_LPDDR4_2Gbx1				9
#define DDR_RFC_TYPE_LPDDR4_3Gbx1				10
#define DDR_RFC_TYPE_LPDDR4_4Gbx1				11
#define DDR_RFC_TYPE_LPDDR4_6Gbx1				12
#define DDR_RFC_TYPE_LPDDR4_8Gbx1				13

#define DDR_ENABLE_FINE_TUNE_FLAG_AC_DELAY				(1<<0)
#define DDR_ENABLE_FINE_TUNE_FLAG_WRITE_DQS				(1<<1)
#define DDR_ENABLE_FINE_TUNE_FLAG_READ_DQS				(1<<2)
#define DDR_ENABLE_FINE_TUNE_FLAG_WRITE_DQ				(1<<3)
#define DDR_ENABLE_FINE_TUNE_FLAG_READ_DQ				(1<<4)

#define IMPEDENCE_120P3_240P2_480P1				1
#define IMPEDENCE_120P6_1						2
#define IMPEDENCE_120P3_240P2_480P1_ODT			3

#define IMPEDENCE_AML_SOC_DATA				1
#define IMPEDENCE_AML_SOC_AC						2


#define  VREF_DDR4_SDRAM_DAC  1
#define  VREF_LPDDR4_SDRAM_DAC  2
#define  VREF_LPDDR4X_SDRAM_DAC  3
#define  VREF_SOC_AML_DAC_LPDDR4  4
#define  VREF_SOC_AML_DAC_LPDDR4X  5
#define  VREF_SOC_AML_DAC_DDR3  6
#define  VREF_SOC_AML_DAC_DDR4  7

#define DDR_PHY_BLOCK_ANIB						0x0
#define DDR_PHY_BLOCK_DBYTE						0x1
#define DDR_PHY_BLOCK_MASTER					0x2
#define DDR_PHY_BLOCK_ACSM						0x4
#define DDR_PHY_BLOCK_UPTCL_MEMORY				0x5
#define DDR_PHY_BLOCK_PPGC						0x7
#define DDR_PHY_BLOCK_INITENG					0x9
#define DDR_PHY_BLOCK_PUB						0xC
#define DDR_PHY_BLOCK_APBONLY					0xD

/* others */ /* useless? */

/* bist */
#define CONFIG_DDR_CODE_INCLUDE_LPDDR3								0
#define CONFIG_DDR_CODE_INCLUDE_DDR4								1
#define CONFIG_DEBUG_INCLUDE_D2PLL									1
#define CONFIG_DEBUG_DDR_BIST_TEST_WINDOWS							1
#define CONFIG_DEBUG_DDR_BIST_ONLY_COMPARE_ONE_LANE					1
#define CONFIG_DEBUG_DDR_BIST_BYTE_EXTRA_PATTERN					1
#define CONFIG_DEBUG_DDR_BIST_NO_USE_FSM_INIT_VALUE					1
#define CONFIG_DEBUG_DDR_BIST_NO_USE_FSM_INIT_VALUE_USE_LINEAR		0
#define CONFIG_DEBUG_DDR_BIST_NO_USE_FSM_INIT_VALUE_USE_FAST_LINEAR	1
#define CONFIG_DEBUG_DDR_BIST_USE_OLD_METHOD_AGAIN					0
#define CONFIG_DDR_DMC_DDR_TEST										0
#define CONFIG_DDR_CPU_DDR_TEST										0
#define CONFIG_BIST_USE_THRESHOLD									0
#define CONFIG_DEBUG_DDR_BIST_TEST_2D_EYE							0

#define CONFIG_DEBUG_DDR_BIST_TEST_DATA
//#define CONFIG_DEBUG_DDR_BIST_TEST_ADD

#define DDR_BIST_LANE_DATA0						0
#define DDR_BIST_LANE_DATA1						1
#define DDR_BIST_LANE_DATA2						2
#define DDR_BIST_LANE_DATA3						3
#define DDR_BIST_LANE_AC						4

#define DDR_BIST_PATTERN_WALK_0					0
#define DDR_BIST_PATTERN_WALK_1					1
#define DDR_BIST_PATTERN_WALK_RANDOM			2
#define DDR_BIST_PATTERN_WALK_PRE				3

/* diagnose function defines */
#define CONFIG_DIAGNOSE_DISABLE					0x0
#define CONFIG_DIAGNOSE_1D						0x1
#define CONFIG_DIAGNOSE_2D						0x2
#define CONFIG_DIAGNOSE_1D_2D					0x3

#define DDR_RFC_TYPE_LPDDR4_6Gbx1				12
#define DDR_RFC_TYPE_LPDDR4_8Gbx1				13


#define 	CONFIG_BOARD_ID_DISABLE		0
#define 	CONFIG_BOARD_ID_MASK		0xFF

#define		CONFIG_DDR_TYPE_DDR3		0
#define		CONFIG_DDR_TYPE_DDR4		1
#define		CONFIG_DDR_TYPE_LPDDR4		2
#define		CONFIG_DDR_TYPE_LPDDR3		3
#define		CONFIG_DDR_TYPE_LPDDR2		4
#define		CONFIG_DDR_TYPE_LPDDR4X		5

#define		CONFIG_DDR0_16BIT_CH0		1
#define		CONFIG_DDR0_16BIT_RANK01_CH0		4
#define		CONFIG_DDR0_32BIT_RANK0_CH0		2
#define		CONFIG_DDR0_32BIT_RANK01_CH01		3
#define		CONFIG_DDR0_32BIT_16BIT_RANK0_CH0		5
#define		CONFIG_DDR0_32BIT_16BIT_RANK01_CH0		6
#define		CONFIG_DDR0_32BIT_RANK01_CH0		7
#define		CONFIG_DDR0_32BIT_RANK0_CH01		8
#define 	CONFIG_DDR0_32BIT_RANK0_16BIT_RANK1_LOW_CH0	0x9
#define 	CONFIG_DDR0_32BIT_RANK0_16BIT_RANK1_HIGH_CH0	0xa
#define 	CONFIG_DDR0_32BIT_16BIT_RANK0_CH0_MODE2	0xB
#define 	CONFIG_DDR0_32BIT_RANK0_16BIT_RANK1_LOW_CH0_MODE2	0xC

#define		CONFIG_DISABLE_D32_D63		0xf0
#define		CONFIG_DISABLE_D16_D31		0xfc

#define		CONFIG_DDR0_SIZE_0MB		0
#define		CONFIG_DDR0_SIZE_128MB		128
#define		CONFIG_DDR0_SIZE_256MB		256
#define		CONFIG_DDR0_SIZE_512MB		512
#define		CONFIG_DDR0_SIZE_768MB		768
#define		CONFIG_DDR0_SIZE_1024MB		1024
#define		CONFIG_DDR0_SIZE_1536MB		1536
#define		CONFIG_DDR0_SIZE_2048MB		2048
#define		CONFIG_DDR0_SIZE_3072MB		3072
#define		CONFIG_DDR0_SIZE_4096MB		4096
#define		CONFIG_DDR0_SIZE_AUTO_SIZE		0xffff
#define		CONFIG_DDR1_SIZE_0MB		0
#define		CONFIG_DDR1_SIZE_128MB		128
#define		CONFIG_DDR1_SIZE_256MB		256
#define		CONFIG_DDR1_SIZE_512MB		512
#define		CONFIG_DDR1_SIZE_768MB		768
#define		CONFIG_DDR1_SIZE_1024MB		1024
#define		CONFIG_DDR1_SIZE_1536MB		1536
#define		CONFIG_DDR1_SIZE_2048MB		2048
#define		CONFIG_DDR1_SIZE_3072MB		3072
#define		CONFIG_DDR1_SIZE_4096MB		4096
#define		CONFIG_DDR1_SIZE_AUTO_SIZE		0xffff

#define		CONFIG_DRAM_MODE_X4		1
#define		CONFIG_DRAM_MODE_X8		1
#define		CONFIG_DRAM_MODE_X16		0

#define		CONFIG_USE_DDR_1T_MODE		0
#define		CONFIG_USE_DDR_2T_MODE		1

#define		eLOG_CHL_0		0
#define		eLOG_CHL_1		1
#define		eLOG_CHL_2		2
#define		eLOG_CHL_3		3
#define		eLOG_CHL_4		4
#define		eLOG_CHL_5		5
#define		eLOG_CHL_6		6
#define		eLOG_CHL_7		7

#define		LOG_LEVEL_BASIC		(1<<eLOG_CHL_0)
#define		LOG_LEVEL_FULL		(1<<eLOG_CHL_0)|(1<<eLOG_CHL_1)|(1<<eLOG_CHL_2)|(1<<eLOG_CHL_3)|(1<<eLOG_CHL_4)|(1<<eLOG_CHL_5)|(1<<eLOG_CHL_6)
#define		LOG_LEVEL_DEBUG		(1<<eLOG_CHL_0)|(1<<eLOG_CHL_1)|(1<<eLOG_CHL_2)|(1<<eLOG_CHL_3)|(1<<eLOG_CHL_4)|(1<<eLOG_CHL_5)|(1<<eLOG_CHL_6)|(1<<eLOG_CHL_7)

#define		DDR_WRITE_READ_DBI_DISABLE		0
#define		DDR_READ_DBI_ENABLE		1
#define		DDR_WRITE_DBI_ENABLE		2
#define		DDR_WRITE_READ_DBI_ENABLE		3

#define		DDR_PLL_SSC_DISABLE		0
#define		DDR_PLL_SSC_3000PPM		0x3000
#define		DDR_PLL_SSC_5000PPM		0x3001
#define		DDR_PLL_SSC_6000PPM		0x3002
#define		DDR_PLL_SSC_8000PPM		0x3003
#define		DDR_PLL_SSC_9000PPM		0x3004

#define		DDR_DMC_REMAP_DDR3_32BIT		{\
				[0] = ( 5 |  6 << 5 |  7 << 10 |  8 << 15 | 9 << 20 | 10 << 25 ),\
				[1] = ( 11|  0 << 5 |  0 << 10 | 12 << 15 | 16 << 20 | 17 << 25 ),\
				[2] = ( 18| 19 << 5 | 20 << 10 | 21 << 15 | 22 << 20 | 23 << 25 ),\
				[3] = ( 24| 25 << 5 | 26 << 10 | 27 << 15 | 28 << 20 | 29 << 25 ),\
				[4] = ( 30| 13 << 5 | 14 << 10 |  15 << 15 |  0 << 20 |  0 << 25 ),\
				}

#define		DDR_DMC_REMAP_DDR4_32BIT		{\
				[0] = ( 5 |  7 << 5 |  8 << 10 |  9 << 15 | 10 << 20 | 11 << 25 ),\
				[1] = ( 12|  0 << 5 |  0 << 10 | 14 << 15 | 15 << 20 | 16 << 25 ),\
				[2] = ( 17| 18 << 5 | 19 << 10 | 21 << 15 | 22 << 20 | 23 << 25 ),\
				[3] = ( 24| 25 << 5 | 26 << 10 | 27 << 15 | 28 << 20 | 29 << 25 ),\
				[4] = ( 30| 13 << 5 | 20 << 10 |  6 << 15 |  0 << 20 |  31 << 25 ),\
				}


#define		DDR_DMC_REMAP_DDR3_16BIT		{\
				[0] = ( 0 |  5 << 5 |  6<< 10 |  7 << 15 | 8 << 20 | 9 << 25 ),\
				[1] = ( 10|  0 << 5 |  0 << 10 | 14 << 15 | 15 << 20 | 16 << 25 ),\
				[2] = ( 17|( 18 << 5) |( 19 << 10) |( 20 << 15) |( 21 << 20) | (22 << 25 )),\
				[3] = ( 23| 24 << 5 | 25 << 10 | 26 << 15 | 27 << 20 | 28 << 25 ),\
				[4] = ( 29| 11<< 5 | 12 << 10 |  13<< 15 |  0 << 20 |  0 << 25 ),\
				}

#define		DDR_DMC_REMAP_DDR4_16BIT		{\
				[0] = ( 0 |  5 << 5 |  6<< 10 |  7 << 15 | 8 << 20 | 9 << 25 ),\
				[1] = ( 10|  0 << 5 |  0 << 10 | 14 << 15 | 15 << 20 | 16 << 25 ),\
				[2] = ( 17|( 18 << 5) |( 19 << 10) |( 20 << 15) |( 21 << 20) | (22 << 25 )),\
				[3] = ( 23| 24 << 5 | 25 << 10 | 26 << 15 | 27 << 20 | 28 << 25 ),\
				[4] = ( 29| 11<< 5 | 12 << 10 |  13<< 15 |  0 << 20 |  30 << 25 ),\
				}
#define		DDR_DMC_REMAP_LPDDR4_16BIT		{\
				[0] = ( 0 |  5 << 5 |  6<< 10 |  7 << 15 | 8 << 20 | 9 << 25 ),\
				[1] = ( 10|  0 << 5 |  0 << 10 | 14 << 15 | 15 << 20 | 16 << 25 ),\
				[2] = ( 17|( 18 << 5) |( 19 << 10) |( 20 << 15) |( 21 << 20) | (22 << 25 )),\
				[3] = ( 23| 24 << 5 | 25 << 10 | 26 << 15 | 27 << 20 | 28 << 25 ),\
				[4] = ( 29| 11<< 5 | 12 << 10 |  13<< 15 |  0 << 20 |  0 << 25 ),\
				}

#define		DDR_DMC_REMAP_LPDDR4_32BIT		{\
				[0] = ( 5 |  6 << 5 |  7 << 10 |  8 << 15 |  9 << 20 | 10 << 25 ),\
				[1] = ( 11|  0 << 5 |  0 << 10 | 12 << 15 | 14 << 20 | 15 << 25 ),\
				[2] = ( 17| 18 << 5 | 19 << 10 | 21 << 15 | 22 << 20 | 23 << 25 ),\
				[3] = ( 24| 25 << 5 | 26 << 10 | 27 << 15 | 28 << 20 | 29 << 25 ),\
				[4] = ( 30| 13 << 5 | 16 << 10 | 20 << 15 |  0 << 20 |  0 << 25 ),\
				}
				//cs0 write bit0-1,cs0 read bit4-5,cs1 write bit 8-9,cs1 read bit 12-13
#define		DDR_DRAM_ODT_DISABLE		0
#define		DDR_DRAM_ODT_W_CS0_ODT0		0x1
#define		DDR_DRAM_ODT_W_CS0_ODT0_CS1_ODT1		0x201
#define		DDR_DRAM_ODT_W_CS0_ODT1_CS1_ODT0		0x102
#define		DDR_DRAM_ODT_W_CS0_ODT01_CS1_ODT01		0x303
#define		DDR_DRAM_ODT_W_CS0_ODT0_CS1_ODT1__R_CS0_ODT1_CS1_ODT0		0x1221
#define		DDR_DRAM_ODT_W_CS0_ODT1_CS1_ODT0__R_CS0_ODT1_CS1_ODT0		0x1122
#define		DDR_DRAM_ODT_W_CS0_ODT01_CS1_ODT01__R_CS0_ODT1_CS1_ODT0		0x1323
#define		DDR_DRAM_ODT_R_CS0_ODT1_CS1_ODT0		0x1020

#define		DDR_SOC_AC_DRV_0_OHM		0
#define		DDR_SOC_AC_DRV_120_OHM		120
#define		DDR_SOC_AC_DRV_80_OHM		80
#define		DDR_SOC_AC_DRV_60_OHM		60
#define		DDR_SOC_AC_DRV_40_OHM		40
#define		DDR_SOC_AC_DRV_30_OHM		30
#define		DDR_SOC_AC_DRV_24_OHM		24
#define		DDR_SOC_AC_DRV_20_OHM		20

#define		DDR_SOC_DATA_DRV_ODT_0_OHM		0
#define		DDR_SOC_DATA_DRV_ODT_240_OHM		240
#define		DDR_SOC_DATA_DRV_ODT_120_OHM		120
#define		DDR_SOC_DATA_DRV_ODT_80_OHM		80
#define		DDR_SOC_DATA_DRV_ODT_60_OHM		60
#define		DDR_SOC_DATA_DRV_ODT_48_OHM		48
#define		DDR_SOC_DATA_DRV_ODT_40_OHM		40
#define		DDR_SOC_DATA_DRV_ODT_34_OHM		34

#define		DDR_DRAM_DDR3_DRV_34_OHM		34
#define		DDR_DRAM_DDR3_DRV_40_OHM		40
#define		DDR_DRAM_DDR4_DRV_34_OHM		34
#define		DDR_DRAM_DDR4_DRV_48_OHM		48
#define		DDR_DRAM_LPDDR3_DRV_34_OHM		34
#define		DDR_DRAM_LPDDR3_DRV_40_OHM		40
#define		DDR_DRAM_LPDDR3_DRV_48_OHM		48
#define		DDR_DRAM_LPDDR4_DRV_40_OHM		40
#define		DDR_DRAM_LPDDR4_DRV_48_OHM		48
#define		DDR_DRAM_LPDDR4_DRV_60_OHM		60
#define		DDR_DRAM_LPDDR4_DRV_80_OHM		80
#define		DDR_DRAM_LPDDR4_DRV_120_OHM		120
#define		DDR_DRAM_LPDDR4_DRV_240_OHM		240

#define		DDR_DRAM_DDR3_ODT_0_OHM		0
#define		DDR_DRAM_DDR3_ODT_120_OHM		120
#define		DDR_DRAM_DDR3_ODT_60_OHM		60
#define		DDR_DRAM_DDR3_ODT_40_OHM		40
#define		DDR_DRAM_LPDDR3_ODT_0_OHM		0
#define		DDR_DRAM_LPDDR3_ODT_240_OHM		240
#define		DDR_DRAM_LPDDR3_ODT_120_OHM		120
#define		DDR_DRAM_LPDDR3_ODT_60_OHM		60
#define		DDR_DRAM_LPDDR4_ODT_0_OHM		0
#define		DDR_DRAM_LPDDR4_ODT_240_OHM		240
#define		DDR_DRAM_LPDDR4_ODT_120_OHM		120
#define		DDR_DRAM_LPDDR4_ODT_80_OHM		80
#define		DDR_DRAM_LPDDR4_ODT_60_OHM		60
#define		DDR_DRAM_LPDDR4_ODT_48_OHM		48
#define		DDR_DRAM_LPDDR4_ODT_40_OHM		40
#define		DDR_DRAM_DDR4_ODT_0_OHM		0
#define		DDR_DRAM_DDR4_ODT_34_OHM		34
#define		DDR_DRAM_DDR4_ODT_40_OHM		40
#define		DDR_DRAM_DDR4_ODT_48_OHM		48
#define		DDR_DRAM_DDR4_ODT_60_OHM		60
#define		DDR_DRAM_DDR4_ODT_80_OHM		80
#define		DDR_DRAM_DDR4_ODT_120_OHM		120
#define		DDR_DRAM_DDR4_ODT_240_OHM		240

#define		DDR_DRAM_DDR_WR_ODT_0_OHM		0
#define		DDR_DRAM_DDR3_WR_ODT_0_OHM		0
#define		DDR_DRAM_DDR3_WR_ODT_120_OHM		120
#define		DDR_DRAM_DDR3_WR_ODT_60_OHM		60
#define		DDR_DRAM_DDR4_WR_ODT_0_OHM		0
#define		DDR_DRAM_DDR4_WR_ODT_240_OHM		240
#define		DDR_DRAM_DDR4_WR_ODT_120_OHM		120
#define		DDR_DRAM_DDR4_WR_ODT_80_OHM		80

#define		DDR_DRAM_DDR_AC_ODT_0_OHM		0
#define		DDR_DRAM_LPDDR4_AC_ODT_0_OHM		0
#define		DDR_DRAM_LPDDR4_AC_ODT_240_OHM		240
#define		DDR_DRAM_LPDDR4_AC_ODT_120_OHM		120
#define		DDR_DRAM_LPDDR4_AC_ODT_80_OHM		80
#define		DDR_DRAM_LPDDR4_AC_ODT_60_OHM		60
#define		DDR_DRAM_LPDDR4_AC_ODT_48_OHM		48
#define		DDR_DRAM_LPDDR4_AC_ODT_40_OHM		40

#define		DDR_DRAM_LPDDR4_OUTPUT_2_5_VDDQ		0
#define		DDR_DRAM_LPDDR4_OUTPUT_1_3_VDDQ		1

#define		DDR_SOC_READ_DQS_GATE_MODE_WINDOW_MODE_0_DDR3		1
#define		DDR_SOC_READ_DQS_GATE_MODE_WINDOW_MODE_1_DDR4		2
#define		DDR_SOC_READ_DQS_GATE_MODE_WINDOW_MODE_2_DDR4		3
#define		DDR_SOC_READ_DQS_GATE_MODE_WINDOW_MODE_3_LPDDR4		4

#define		DDR_SOC_READ_DQS_GATE_MODE_EDGE_MODE_1_DDR3		5
#define		DDR_SOC_READ_DQS_GATE_MODE_EDGE_MODE_1_DDR4		6
#define		DDR_SOC_READ_DQS_GATE_MODE_EDGE_MODE_1_LPDDR4		7
#define		DDR_SOC_READ_DQS_GATE_MODE_EDGE_MODE_3_LPDDR4		8

#define		DDR_SOC_READ_DQS_GATE_MODE_WIDE_MODE_RPULL_0_DDR3		9
#define		DDR_SOC_READ_DQS_GATE_MODE_WIDE_MODE_RPULL_1_LPDDR4		10

#define		DDR_SOC_READ_DQS_GATE_MODE_EDGE_MODE_DQS_GATE_TRAINING_LPDDR4		11
#if 0
#define		DDR_SOC_READ_DQS_GATE_MODE_RPULL_WIDE_WINDOW		1

#define		DDR_SOC_READ_DQS_GATE_MODE_DDR3_WINDOW_MODE_0		2
#define		DDR_SOC_READ_DQS_GATE_MODE_DDR3_WINDOW_MODE_1	3
#define		DDR_SOC_READ_DQS_GATE_MODE_DDR3_WINDOW_MODE_2	4
#define		DDR_SOC_READ_DQS_GATE_MODE_DDR3_WINDOW_MODE_3	5
#define		DDR_SOC_READ_DQS_GATE_MODE_DDR3_EDGE_MODE_0		6
#define		DDR_SOC_READ_DQS_GATE_MODE_DDR3_EDGE_MODE_1	7
#define		DDR_SOC_READ_DQS_GATE_MODE_DDR3_EDGE_MODE_2	8
#define		DDR_SOC_READ_DQS_GATE_MODE_DDR3_EDGE_MODE_3	9

#define		DDR_SOC_READ_DQS_GATE_MODE_DDR4_WINDOW_MODE_0		10
#define		DDR_SOC_READ_DQS_GATE_MODE_DDR4_WINDOW_MODE_1	11
#define		DDR_SOC_READ_DQS_GATE_MODE_DDR4_WINDOW_MODE_2	12
#define		DDR_SOC_READ_DQS_GATE_MODE_DDR4_WINDOW_MODE_3	13
#define		DDR_SOC_READ_DQS_GATE_MODE_DDR4_EDGE_MODE_0		14
#define		DDR_SOC_READ_DQS_GATE_MODE_DDR4_EDGE_MODE_1	15
#define		DDR_SOC_READ_DQS_GATE_MODE_DDR4_EDGE_MODE_2	16
#define		DDR_SOC_READ_DQS_GATE_MODE_DDR4_EDGE_MODE_3	17

#define		DDR_SOC_READ_DQS_GATE_MODE_LPDDR4_WINDOW_MODE_0		18
#define		DDR_SOC_READ_DQS_GATE_MODE_LPDDR4_WINDOW_MODE_1	19
#define		DDR_SOC_READ_DQS_GATE_MODE_LPDDR4_WINDOW_MODE_2	20
#define		DDR_SOC_READ_DQS_GATE_MODE_LPDDR4_WINDOW_MODE_3	21
#define		DDR_SOC_READ_DQS_GATE_MODE_LPDDR4_EDGE_MODE_0		22
#define		DDR_SOC_READ_DQS_GATE_MODE_LPDDR4_EDGE_MODE_1	23
#define		DDR_SOC_READ_DQS_GATE_MODE_LPDDR4_EDGE_MODE_2	24
#define		DDR_SOC_READ_DQS_GATE_MODE_LPDDR4_EDGE_MODE_3	25
#endif

#define DDR_TIMMING_OFFSET(X)  (unsigned int)(unsigned long)(&(((ddr_set_t *)(0))->X))
#define DDR_TIMMING_OFFSET_SIZE(X)  sizeof(((ddr_set_t *)(0))->X)
#define DDR_TIMMING_TUNE(DDR_ID, PARA, VALUE) { DDR_ID, DDR_TIMMING_OFFSET(PARA), VALUE, DDR_TIMMING_OFFSET_SIZE(PARA), 0, 1 }
//DDR_ID
#define DDR_ADC_CH0  (0X0u << 6)
#define DDR_ADC_CH1  (0X1u << 6)
#define DDR_ADC_CH2  (0X2u << 6)
#define DDR_ADC_CH3  (0X3u << 6)

#define DDR_ADC_VALUE0  (0X0u << 0)
#define DDR_ADC_VALUE1  (0X1u << 0)
#define DDR_ADC_VALUE2  (0X2u << 0)
#define DDR_ADC_VALUE3  (0X3u << 0)
#define DDR_ADC_VALUE4  (0X4u << 0)
#define DDR_ADC_VALUE5  (0X5u << 0)
#define DDR_ADC_VALUE6  (0X6u << 0)
#define DDR_ADC_VALUE7  (0X7u << 0)
#define DDR_ADC_VALUE8  (0X8u << 0)
#define DDR_ADC_VALUE9  (0X9u << 0)
#define DDR_ADC_VALUE10  (0Xau << 0)
#define DDR_ADC_VALUE11  (0Xbu << 0)
#define DDR_ADC_VALUE12  (0Xcu << 0)
#define DDR_ADC_VALUE13  (0Xdu << 0)
#define DDR_ADC_VALUE14  (0Xeu << 0)
#define DDR_ADC_VALUE15  (0Xfu << 0)

//efuse
#define T963_H8_NTC_EID       0xC0A
#define T963_H8_SUM_EID       0xC4A
#define T963_H35_NTC_EID      0x2C1A
#define T963_H35_SUM_EID      0x2C5A
#define T963_H9_NTC_EID       0x6C2A
#define T963_H9_SUM_EID       0x6C6A
#define T963_H_NA_EID         0x1400

#define T963S_H8_NTC_EID      0xC8A
#define T963S_H8_SUM_EID      0xCCA
#define T963S_H35_SUM_EID     0x2CDA
#define T950D4_H5_NTC_EID     0x509
#define T950D4_H6_NTC_EID     0x909
#define T950D4_H8_NTC_EID     0xC0A
#define T950D4_H8_SUM_EID     0xC4A
#define T950D4_H35_NTC_EID    0x2C1A
#define T950D4_H35_SUM_EID    0x2C5A
#define T950X4_H5_NTC_EID     0xD09
#define T950X4_H8_NTC_EID     0xC8A
#define T950X4_H8_SUM_EID     0xCCA
#define T950X4_H35_SUM_EID    0x2CDA
#define T950X4_B5_SUM_EID     0x4C6