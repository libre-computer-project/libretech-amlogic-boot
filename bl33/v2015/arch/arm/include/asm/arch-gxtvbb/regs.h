/* SPDX-License-Identifier: (GPL-2.0+ OR MIT) */
/*
 * arch/arm/include/asm/arch-gxtvbb/regs.h
 *
 * Copyright (C) 2020 Amlogic, Inc. All rights reserved.
 *
 */

/* readme */

/* asm/arch/regs.h
 * registers collect from fragmented places in each drivers/files,
 * since regs changes a lot after txlx chip, all registers need
 * managed orderly.
*/

/* bus base */
#define REG_BASE_AOBUS                  (0xc8100000L)
#define REG_BASE_PERIPHS                (0xc8834400L)
#define REG_BASE_CBUS                   (0xc1100000L)
#define REG_BASE_HIU                    (0xc883c000L)
#define REG_BASE_VCBUS                  (0xd0100000L)
#define DMC_REG_BASE                    (0xc8838000L)


// asm/arch/efuse.h
#define ASSIST_HW_REV                              0x1f53

// arch/arm/include/asm/arch/i2c.h
#define I2C_M_0_CONTROL_REG                        0x2140
/*#define I2C_M_0_SLAVE_ADDR                         0x2141
#define I2C_M_0_TOKEN_LIST0                        0x2142
#define I2C_M_0_TOKEN_LIST1                        0x2143
#define I2C_M_0_WDATA_REG0                         0x2144
#define I2C_M_0_WDATA_REG1                         0x2145
#define I2C_M_0_RDATA_REG0                         0x2146
#define I2C_M_0_RDATA_REG1                         0x2147
*/
#define I2C_S_CONTROL_REG                          0x2150
#define I2C_M_1_CONTROL_REG                        0x21f0
#define I2C_M_2_CONTROL_REG 					   0x21f8
#define I2C_M_3_CONTROL_REG                        0x2348


/* spi nor flash */
#define P_SPI_FLASH_CMD     (volatile unsigned int *)0xc1108c80
#define P_SPI_FLASH_ADDR    (volatile unsigned int *)0xc1108c84
#define P_SPI_FLASH_CTRL    (volatile unsigned int *)0xc1108c88
#define P_SPI_FLASH_STATUS  (volatile unsigned int *)0xc1108c90
#define P_SPI_USER_REG      (volatile unsigned int *)0xc1108c9c
#define P_SPI_FLASH_C0      (volatile unsigned int *)0xc1108cc0
#define P_SPI_START_ADDR    (volatile unsigned int *)0xCC000000

// drivers/mtd/spi/spi_flash_amlogic.h
#if 0
#define P_PERIPHS_PIN_MUX_4		0xc88344c0
#define P_PERIPHS_PIN_MUX_5		0xc88344c4
#endif
#define SPI_FLASH_CMD                              0x2320
    #define SPI_FLASH_READ    31
    #define SPI_FLASH_WREN    30
    #define SPI_FLASH_WRDI    29
    #define SPI_FLASH_RDID    28
    #define SPI_FLASH_RDSR    27
    #define SPI_FLASH_WRSR    26
    #define SPI_FLASH_PP      25
    #define SPI_FLASH_SE      24
    #define SPI_FLASH_BE      23
    #define SPI_FLASH_CE      22
    #define SPI_FLASH_DP      21
    #define SPI_FLASH_RES     20
    #define SPI_HPM           19
    #define SPI_FLASH_USR     18
    #define SPI_FLASH_USR_ADDR 15
    #define SPI_FLASH_USR_DUMMY 14
    #define SPI_FLASH_USR_DIN   13
    #define SPI_FLASH_USR_DOUT   12
    #define SPI_FLASH_USR_DUMMY_BLEN   10
    #define SPI_FLASH_USR_CMD     0
#define SPI_FLASH_ADDR                             0x2321
    #define SPI_FLASH_BYTES_LEN 24
    #define SPI_FLASH_ADDR_START 0
#define SPI_FLASH_CTRL                             0x2322
    #define SPI_ENABLE_AHB    17
    #define SPI_SST_AAI       16
    #define SPI_RES_RID       15
    #define SPI_FREAD_DUAL    14
    #define SPI_READ_READ_EN  13
    #define SPI_CLK_DIV0      12
    #define SPI_CLKCNT_N      8
    #define SPI_CLKCNT_H      4
    #define SPI_CLKCNT_L      0
#define SPI_FLASH_CTRL1                            0x2323
#define SPI_FLASH_STATUS                           0x2324
#define SPI_FLASH_CTRL2                            0x2325
#define SPI_FLASH_CLOCK                            0x2326
#define SPI_FLASH_USER                             0x2327
#define SPI_FLASH_USER1                            0x2328
#define SPI_FLASH_USER2                            0x2329
#define SPI_FLASH_USER3                            0x232a
#define SPI_FLASH_USER4                            0x232b
#define SPI_FLASH_SLAVE                            0x232c
#define SPI_FLASH_SLAVE1                           0x232d
#define SPI_FLASH_SLAVE2                           0x232e
#define SPI_FLASH_SLAVE3                           0x232f
#define SPI_FLASH_C0                               0x2330
#define SPI_FLASH_C1                               0x2331
#define SPI_FLASH_C2                               0x2332
#define SPI_FLASH_C3                               0x2333
#define SPI_FLASH_C4                               0x2334
#define SPI_FLASH_C5                               0x2335
#define SPI_FLASH_C6                               0x2336
#define SPI_FLASH_C7                               0x2337
#define SPI_FLASH_B8                               0x2338
#define SPI_FLASH_B9                               0x2339
#define SPI_FLASH_B10                              0x233a
#define SPI_FLASH_B11                              0x233b
#define SPI_FLASH_B12                              0x233c
#define SPI_FLASH_B13                              0x233d
#define SPI_FLASH_B14                              0x233e
#define SPI_FLASH_B15                              0x233f


/* ----------------------------
 clock measure (4)
 ---------------------------- */
#define MSR_CLK_DUTY                               0x21d6
#define MSR_CLK_REG0                               0x21d7
#define MSR_CLK_REG1                               0x21d8
#define MSR_CLK_REG2                               0x21d9
#define P_MSR_CLK_DUTY CBUS_REG_ADDR(MSR_CLK_DUTY)
#define P_MSR_CLK_REG0 CBUS_REG_ADDR(MSR_CLK_REG0)
#define P_MSR_CLK_REG1 CBUS_REG_ADDR(MSR_CLK_REG1)
#define P_MSR_CLK_REG2 CBUS_REG_ADDR(MSR_CLK_REG2)

/* below UART0,UART1,AO_UART is m8 addr,it is placed is for compiling pass */
/* -------------------------------
// UART0
// ---------------------------- */
#define UART0_WFIFO                                0x2130
#define UART0_RFIFO                                0x2131
#define UART0_CONTROL                              0x2132
#define UART0_STATUS                               0x2133
#define UART0_MISC                                 0x2134
#define UART0_REG5                                 0x2135
/* ----------------------------
// UART1
----------------------------*/
#define UART1_WFIFO                                0x2137
#define UART1_RFIFO                                0x2138
#define UART1_CONTROL                              0x2139
#define UART1_STATUS                               0x213a
#define UART1_MISC                                 0x213b
#define UART1_REG5                                 0x213c

/* usb burning */



/* romboot.h */
#define P_ISA_TIMERE                 (volatile uint32_t *)0xc1109988
#define P_ASSIST_POR_CONFIG          (volatile uint32_t *)0xc1107d54
#define P_RESET1_REGISTER            (volatile uint32_t *)0xc1104408
#define P_WATCHDOG_CNTL              (volatile uint32_t *)0xc11098d0
#define P_WATCHDOG_CNTL1             (volatile uint32_t *)0xc11098d4
#define P_WATCHDOG_TCNT              (volatile uint32_t *)0xc11098d8
#define P_WATCHDOG_RESET             (volatile uint32_t *)0xc11098dc


/* aml_vpu_reg.h */
#define RESET0_REGISTER                 0x1101
#define RESET1_REGISTER                 0x1102
#define RESET2_REGISTER                 0x1103
#define RESET3_REGISTER                 0x1104
#define RESET4_REGISTER                 0x1105
#define RESET5_REGISTER                 0x1106
#define RESET6_REGISTER                 0x1107
#define RESET7_REGISTER                 0x1108
#define RESET0_MASK                     0x1110
#define RESET1_MASK                     0x1111
#define RESET2_MASK                     0x1112
#define RESET3_MASK                     0x1113
#define RESET4_MASK                     0x1114
#define RESET5_MASK                     0x1115
#define RESET6_MASK                     0x1116
#define RESET7_MASK                     0x1118
#define RESET0_LEVEL                    0x1120
#define RESET1_LEVEL                    0x1121
#define RESET2_LEVEL                    0x1122
#define RESET3_LEVEL                    0x1123
#define RESET4_LEVEL                    0x1124
#define RESET5_LEVEL                    0x1125
#define RESET6_LEVEL                    0x1126
#define RESET7_LEVEL                    0x1127

/* ********************************
 * PWM:  CBUS
 * ******************************** */
#define PWM_PWM_A                                  0x2154
#define PWM_PWM_B                                  0x2155
#define PWM_MISC_REG_AB                            0x2156
#define PWM_PWM_C                                  0x2190
#define PWM_PWM_D                                  0x2191
#define PWM_MISC_REG_CD                            0x2192
#define PWM_PWM_E                                  0x21b0
#define PWM_PWM_F                                  0x21b1
#define PWM_MISC_REG_EF                            0x21b2

/* ********************************
 * TCON:  VCBUS_BASE = 0x14
 * ******************************** */
/* TCON_L register */
#define L_GAMMA_CNTL_PORT                          0x1400
#define L_GAMMA_DATA_PORT                          0x1401
#define L_GAMMA_ADDR_PORT                          0x1402
#define L_GAMMA_VCOM_HSWITCH_ADDR                  0x1403
#define L_RGB_BASE_ADDR                            0x1405
#define L_RGB_COEFF_ADDR                           0x1406
#define L_POL_CNTL_ADDR                            0x1407
#define L_DITH_CNTL_ADDR                           0x1408
#define L_GAMMA_PROBE_CTRL                         0x1409
/* read only */
#define L_GAMMA_PROBE_COLOR_L                      0x140a
#define L_GAMMA_PROBE_COLOR_H                      0x140b
#define L_GAMMA_PROBE_HL_COLOR                     0x140c
#define L_GAMMA_PROBE_POS_X                        0x140d
#define L_GAMMA_PROBE_POS_Y                        0x140e
#define L_STH1_HS_ADDR                             0x1410
#define L_STH1_HE_ADDR                             0x1411
#define L_STH1_VS_ADDR                             0x1412
#define L_STH1_VE_ADDR                             0x1413
#define L_STH2_HS_ADDR                             0x1414
#define L_STH2_HE_ADDR                             0x1415
#define L_STH2_VS_ADDR                             0x1416
#define L_STH2_VE_ADDR                             0x1417
#define L_OEH_HS_ADDR                              0x1418
#define L_OEH_HE_ADDR                              0x1419
#define L_OEH_VS_ADDR                              0x141a
#define L_OEH_VE_ADDR                              0x141b
#define L_VCOM_HSWITCH_ADDR                        0x141c
#define L_VCOM_VS_ADDR                             0x141d
#define L_VCOM_VE_ADDR                             0x141e
#define L_CPV1_HS_ADDR                             0x141f
#define L_CPV1_HE_ADDR                             0x1420
#define L_CPV1_VS_ADDR                             0x1421
#define L_CPV1_VE_ADDR                             0x1422
#define L_CPV2_HS_ADDR                             0x1423
#define L_CPV2_HE_ADDR                             0x1424
#define L_CPV2_VS_ADDR                             0x1425
#define L_CPV2_VE_ADDR                             0x1426
#define L_STV1_HS_ADDR                             0x1427
#define L_STV1_HE_ADDR                             0x1428
#define L_STV1_VS_ADDR                             0x1429
#define L_STV1_VE_ADDR                             0x142a
#define L_STV2_HS_ADDR                             0x142b
#define L_STV2_HE_ADDR                             0x142c
#define L_STV2_VS_ADDR                             0x142d
#define L_STV2_VE_ADDR                             0x142e
#define L_OEV1_HS_ADDR                             0x142f
#define L_OEV1_HE_ADDR                             0x1430
#define L_OEV1_VS_ADDR                             0x1431
#define L_OEV1_VE_ADDR                             0x1432
#define L_OEV2_HS_ADDR                             0x1433
#define L_OEV2_HE_ADDR                             0x1434
#define L_OEV2_VS_ADDR                             0x1435
#define L_OEV2_VE_ADDR                             0x1436
#define L_OEV3_HS_ADDR                             0x1437
#define L_OEV3_HE_ADDR                             0x1438
#define L_OEV3_VS_ADDR                             0x1439
#define L_OEV3_VE_ADDR                             0x143a
#define L_LCD_PWR_ADDR                             0x143b
#define L_LCD_PWM0_LO_ADDR                         0x143c
#define L_LCD_PWM0_HI_ADDR                         0x143d
#define L_LCD_PWM1_LO_ADDR                         0x143e
#define L_LCD_PWM1_HI_ADDR                         0x143f
#define L_INV_CNT_ADDR                             0x1440
#define L_TCON_MISC_SEL_ADDR                       0x1441
#define L_DUAL_PORT_CNTL_ADDR                      0x1442
#define MLVDS_CLK_CTL1_HI                          0x1443
#define MLVDS_CLK_CTL1_LO                          0x1444
/* [31:30] enable mlvds clocks
 * [24]    mlvds_clk_half_delay       24 // Bit 0
 * [23:0]  mlvds_clk_pattern           0 // Bit 23:0    */
#define L_TCON_DOUBLE_CTL                          0x1449
#define L_TCON_PATTERN_HI                          0x144a
#define L_TCON_PATTERN_LO                          0x144b
#define LDIM_BL_ADDR_PORT                          0x144e
#define LDIM_BL_DATA_PORT                          0x144f
#define L_DE_HS_ADDR                               0x1451
#define L_DE_HE_ADDR                               0x1452
#define L_DE_VS_ADDR                               0x1453
#define L_DE_VE_ADDR                               0x1454
#define L_HSYNC_HS_ADDR                            0x1455
#define L_HSYNC_HE_ADDR                            0x1456
#define L_HSYNC_VS_ADDR                            0x1457
#define L_HSYNC_VE_ADDR                            0x1458
#define L_VSYNC_HS_ADDR                            0x1459
#define L_VSYNC_HE_ADDR                            0x145a
#define L_VSYNC_VS_ADDR                            0x145b
#define L_VSYNC_VE_ADDR                            0x145c
/* bit 8 -- vfifo_mcu_enable
 * bit 7 -- halt_vs_de
 * bit 6 -- R8G8B8_format
 * bit 5 -- R6G6B6_format (round to 6 bits)
 * bit 4 -- R5G6B5_format
 * bit 3 -- dac_dith_sel
 * bit 2 -- lcd_mcu_enable_de     -- ReadOnly
 * bit 1 -- lcd_mcu_enable_vsync  -- ReadOnly
 * bit 0 -- lcd_mcu_enable */
#define L_LCD_MCU_CTL                              0x145d

/* **************************************************************************
   Vbyone registers  (Note: no MinLVDS in G9tv, share the register)
 ************************************************************************** */
#define VBO_CTRL_L                                 0x1460
#define VBO_CTRL_H                                 0x1461
#define VBO_SOFT_RST                               0x1462
#define VBO_LANES                                  0x1463
#define VBO_VIN_CTRL                               0x1464
#define VBO_ACT_VSIZE                              0x1465
#define VBO_REGION_00                              0x1466
#define VBO_REGION_01                              0x1467
#define VBO_REGION_02                              0x1468
#define VBO_REGION_03                              0x1469
#define VBO_VBK_CTRL_0                             0x146a
#define VBO_VBK_CTRL_1                             0x146b
#define VBO_HBK_CTRL                               0x146c
#define VBO_PXL_CTRL                               0x146d
#define VBO_LANE_SKEW_L                            0x146e
#define VBO_LANE_SKEW_H                            0x146f
#define VBO_GCLK_LANE_L                            0x1470
#define VBO_GCLK_LANE_H                            0x1471
#define VBO_GCLK_MAIN                              0x1472
#define VBO_STATUS_L                               0x1473
#define VBO_STATUS_H                               0x1474
#define VBO_LANE_OUTPUT                            0x1475
#define LCD_PORT_SWAP                              0x1476
#define VBO_TMCHK_THRD_L                           0x1478
#define VBO_TMCHK_THRD_H                           0x1479
#define VBO_FSM_HOLDER_L                           0x147a
#define VBO_FSM_HOLDER_H                           0x147b
#define VBO_INTR_STATE_CTRL                        0x147c
#define VBO_INTR_UNMASK                            0x147d
#define VBO_TMCHK_HSYNC_STATE_L                    0x147e
#define VBO_TMCHK_HSYNC_STATE_H                    0x147f
#define VBO_TMCHK_VSYNC_STATE_L                    0x14f4
#define VBO_TMCHK_VSYNC_STATE_H                    0x14f5
#define VBO_TMCHK_VDE_STATE_L                      0x14f6
#define VBO_TMCHK_VDE_STATE_H                      0x14f7
#define VBO_INTR_STATE                             0x14f8
#define VBO_INFILTER_CTRL                          0x14f9
#define VBO_INSGN_CTRL                             0x14fa

#define LVDS_BLANK_DATA_HI                         0x14ce
#define LVDS_BLANK_DATA_LO                         0x14cf
   /* 31:30 */
   #define     LVDS_blank_data_reserved 30
   /* 29:20 */
   #define     LVDS_blank_data_r        20
   /* 19:10 */
   #define     LVDS_blank_data_g        10
   /*  9:0 */
   #define     LVDS_blank_data_b         0
#define LVDS_PACK_CNTL_ADDR                        0x14d0
   #define     LVDS_USE_TCON    7
   #define     LVDS_DUAL        6
   #define     PN_SWP           5
   #define     LSB_FIRST        4
   #define     LVDS_RESV        3
   #define     ODD_EVEN_SWP     2
   #define     LVDS_REPACK      0

/* LVDS */
#define LVDS_GEN_CNTL                              0x14e0
#define LVDS_PHY_CNTL0                             0x14e1
#define LVDS_PHY_CNTL1                             0x14e2
#define LVDS_PHY_CNTL2                             0x14e3
#define LVDS_PHY_CNTL3                             0x14e4
#define LVDS_PHY_CNTL4                             0x14e5
#define LVDS_PHY_CNTL5                             0x14e6
#define LVDS_SRG_TEST                              0x14e8
#define LVDS_BIST_MUX0                             0x14e9
#define LVDS_BIST_MUX1                             0x14ea
#define LVDS_BIST_FIXED0                           0x14eb
#define LVDS_BIST_FIXED1                           0x14ec
#define LVDS_BIST_CNTL0                            0x14ed
#define LVDS_CLKB_CLKA                             0x14ee
#define LVDS_PHY_CLK_CNTL                          0x14ef
#define LVDS_SER_EN                                0x14f0
#define LVDS_PHY_CNTL6                             0x14f1
#define LVDS_PHY_CNTL7                             0x14f2
#define LVDS_PHY_CNTL8                             0x14f3

/* ********************************
 * Video Interface:  VENC_VCBUS_BASE = 0x1b
 * ******************************** */
#define VENC_INTCTRL                               0x1b6e

/* ********************************
 * ENCL:  VCBUS_BASE = 0x1c
 * ******************************** */
/* ENCL */
/* bit 15:8 -- vfifo2vd_vd_sel
 * bit 7 -- vfifo2vd_drop
 * bit 6:1 -- vfifo2vd_delay
 * bit 0 -- vfifo2vd_en */
#define ENCL_VFIFO2VD_CTL                          0x1c90
/* bit 12:0 -- vfifo2vd_pixel_start */
#define ENCL_VFIFO2VD_PIXEL_START                  0x1c91
/* bit 12:00 -- vfifo2vd_pixel_end */
#define ENCL_VFIFO2VD_PIXEL_END                    0x1c92
/* bit 10:0 -- vfifo2vd_line_top_start */
#define ENCL_VFIFO2VD_LINE_TOP_START               0x1c93
/* bit 10:00 -- vfifo2vd_line_top_end */
#define ENCL_VFIFO2VD_LINE_TOP_END                 0x1c94
/* bit 10:00 -- vfifo2vd_line_bot_start */
#define ENCL_VFIFO2VD_LINE_BOT_START               0x1c95
/* bit 10:00 -- vfifo2vd_line_bot_end */
#define ENCL_VFIFO2VD_LINE_BOT_END                 0x1c96
#define ENCL_VFIFO2VD_CTL2                         0x1c97
#define ENCL_TST_EN                                0x1c98
#define ENCL_TST_MDSEL                             0x1c99
#define ENCL_TST_Y                                 0x1c9a
#define ENCL_TST_CB                                0x1c9b
#define ENCL_TST_CR                                0x1c9c
#define ENCL_TST_CLRBAR_STRT                       0x1c9d
#define ENCL_TST_CLRBAR_WIDTH                      0x1c9e
#define ENCL_TST_VDCNT_STSET                       0x1c9f

/* ENCL registers */
#define ENCL_VIDEO_EN                              0x1ca0
#define ENCL_VIDEO_Y_SCL                           0x1ca1
#define ENCL_VIDEO_PB_SCL                          0x1ca2
#define ENCL_VIDEO_PR_SCL                          0x1ca3
#define ENCL_VIDEO_Y_OFFST                         0x1ca4
#define ENCL_VIDEO_PB_OFFST                        0x1ca5
#define ENCL_VIDEO_PR_OFFST                        0x1ca6
/* ----- Video mode */
#define ENCL_VIDEO_MODE                            0x1ca7
#define ENCL_VIDEO_MODE_ADV                        0x1ca8
/* --------------- Debug pins */
#define ENCL_DBG_PX_RST                            0x1ca9
#define ENCL_DBG_LN_RST                            0x1caa
#define ENCL_DBG_PX_INT                            0x1cab
#define ENCL_DBG_LN_INT                            0x1cac
/* ----------- Video Advanced setting */
#define ENCL_VIDEO_YFP1_HTIME                      0x1cad
#define ENCL_VIDEO_YFP2_HTIME                      0x1cae
#define ENCL_VIDEO_YC_DLY                          0x1caf
#define ENCL_VIDEO_MAX_PXCNT                       0x1cb0
#define ENCL_VIDEO_HAVON_END                       0x1cb1
#define ENCL_VIDEO_HAVON_BEGIN                     0x1cb2
#define ENCL_VIDEO_VAVON_ELINE                     0x1cb3
#define ENCL_VIDEO_VAVON_BLINE                     0x1cb4
#define ENCL_VIDEO_HSO_BEGIN                       0x1cb5
#define ENCL_VIDEO_HSO_END                         0x1cb6
#define ENCL_VIDEO_VSO_BEGIN                       0x1cb7
#define ENCL_VIDEO_VSO_END                         0x1cb8
#define ENCL_VIDEO_VSO_BLINE                       0x1cb9
#define ENCL_VIDEO_VSO_ELINE                       0x1cba
#define ENCL_VIDEO_MAX_LNCNT                       0x1cbb
#define ENCL_VIDEO_BLANKY_VAL                      0x1cbc
#define ENCL_VIDEO_BLANKPB_VAL                     0x1cbd
#define ENCL_VIDEO_BLANKPR_VAL                     0x1cbe
#define ENCL_VIDEO_HOFFST                          0x1cbf
#define ENCL_VIDEO_VOFFST                          0x1cc0
#define ENCL_VIDEO_RGB_CTRL                        0x1cc1
#define ENCL_VIDEO_FILT_CTRL                       0x1cc2
#define ENCL_VIDEO_OFLD_VPEQ_OFST                  0x1cc3
#define ENCL_VIDEO_OFLD_VOAV_OFST                  0x1cc4
#define ENCL_VIDEO_MATRIX_CB                       0x1cc5
#define ENCL_VIDEO_MATRIX_CR                       0x1cc6
#define ENCL_VIDEO_RGBIN_CTRL                      0x1cc7
#define ENCL_MAX_LINE_SWITCH_POINT                 0x1cc8
#define ENCL_DACSEL_0                              0x1cc9
#define ENCL_DACSEL_1                              0x1cca

/* osd_reg.h */
/* vpp2 */
#define VPP2_DUMMY_DATA 0x1900
#define VPP2_LINE_IN_LENGTH 0x1901
#define VPP2_PIC_IN_HEIGHT 0x1902
#define VPP2_SCALE_COEF_IDX 0x1903
#define VPP2_SCALE_COEF 0x1904
#define VPP2_VSC_REGION12_STARTP 0x1905
#define VPP2_VSC_REGION34_STARTP 0x1906
#define VPP2_VSC_REGION4_ENDP 0x1907
#define VPP2_VSC_START_PHASE_STEP 0x1908
#define VPP2_VSC_REGION0_PHASE_SLOPE 0x1909
#define VPP2_VSC_REGION1_PHASE_SLOPE 0x190a
#define VPP2_VSC_REGION3_PHASE_SLOPE 0x190b
#define VPP2_VSC_REGION4_PHASE_SLOPE 0x190c
#define VPP2_VSC_PHASE_CTRL 0x190d
#define VPP2_VSC_INI_PHASE 0x190e
#define VPP2_HSC_REGION12_STARTP 0x1910
#define VPP2_HSC_REGION34_STARTP 0x1911
#define VPP2_HSC_REGION4_ENDP 0x1912
#define VPP2_HSC_START_PHASE_STEP 0x1913
#define VPP2_HSC_REGION0_PHASE_SLOPE 0x1914
#define VPP2_HSC_REGION1_PHASE_SLOPE 0x1915
#define VPP2_HSC_REGION3_PHASE_SLOPE 0x1916
#define VPP2_HSC_REGION4_PHASE_SLOPE 0x1917
#define VPP2_HSC_PHASE_CTRL 0x1918
#define VPP2_SC_MISC 0x1919
#define VPP2_PREBLEND_VD1_H_START_END 0x191a
#define VPP2_PREBLEND_VD1_V_START_END 0x191b
#define VPP2_POSTBLEND_VD1_H_START_END 0x191c
#define VPP2_POSTBLEND_VD1_V_START_END 0x191d
#define VPP2_PREBLEND_H_SIZE 0x1920
#define VPP2_POSTBLEND_H_SIZE 0x1921
#define VPP2_HOLD_LINES 0x1922
#define VPP2_BLEND_ONECOLOR_CTRL 0x1923
#define VPP2_PREBLEND_CURRENT_XY 0x1924
#define VPP2_POSTBLEND_CURRENT_XY 0x1925
#define VPP2_MISC 0x1926
#define VPP2_OFIFO_SIZE 0x1927
#define VPP2_FIFO_STATUS 0x1928
#define VPP2_SMOKE_CTRL 0x1929
#define VPP2_SMOKE1_VAL 0x192a
#define VPP2_SMOKE2_VAL 0x192b
#define VPP2_SMOKE1_H_START_END 0x192d
#define VPP2_SMOKE1_V_START_END 0x192e
#define VPP2_SMOKE2_H_START_END 0x192f
#define VPP2_SMOKE2_V_START_END 0x1930
#define VPP2_SCO_FIFO_CTRL 0x1933
#define VPP2_HSC_PHASE_CTRL1 0x1934
#define VPP2_HSC_INI_PAT_CTRL 0x1935
#define VPP2_VADJ_CTRL 0x1940
#define VPP2_VADJ1_Y 0x1941
#define VPP2_VADJ1_MA_MB 0x1942
#define VPP2_VADJ1_MC_MD 0x1943
#define VPP2_VADJ2_Y 0x1944
#define VPP2_VADJ2_MA_MB 0x1945
#define VPP2_VADJ2_MC_MD 0x1946
#define VPP2_MATRIX_PROBE_COLOR 0x195c
#define VPP2_MATRIX_HL_COLOR 0x195d
#define VPP2_MATRIX_PROBE_POS 0x195e
#define VPP2_MATRIX_CTRL 0x195f
#define VPP2_MATRIX_COEF00_01 0x1960
#define VPP2_MATRIX_COEF02_10 0x1961
#define VPP2_MATRIX_COEF11_12 0x1962
#define VPP2_MATRIX_COEF20_21 0x1963
#define VPP2_MATRIX_COEF22 0x1964
#define VPP2_MATRIX_OFFSET0_1 0x1965
#define VPP2_MATRIX_OFFSET2 0x1966
#define VPP2_MATRIX_PRE_OFFSET0_1 0x1967
#define VPP2_MATRIX_PRE_OFFSET2 0x1968
#define VPP2_DUMMY_DATA1 0x1969
#define VPP2_GAINOFF_CTRL0 0x196a
#define VPP2_GAINOFF_CTRL1 0x196b
#define VPP2_GAINOFF_CTRL2 0x196c
#define VPP2_GAINOFF_CTRL3 0x196d
#define VPP2_GAINOFF_CTRL4 0x196e
#define VPP2_CHROMA_ADDR_PORT 0x1970
#define VPP2_CHROMA_DATA_PORT 0x1971
#define VPP2_GCLK_CTRL0 0x1972
#define VPP2_GCLK_CTRL1 0x1973
#define VPP2_SC_GCLK_CTRL 0x1974
#define VPP2_MISC1 0x1976
#define VPP2_DNLP_CTRL_00 0x1981
#define VPP2_DNLP_CTRL_01 0x1982
#define VPP2_DNLP_CTRL_02 0x1983
#define VPP2_DNLP_CTRL_03 0x1984
#define VPP2_DNLP_CTRL_04 0x1985
#define VPP2_DNLP_CTRL_05 0x1986
#define VPP2_DNLP_CTRL_06 0x1987
#define VPP2_DNLP_CTRL_07 0x1988
#define VPP2_DNLP_CTRL_08 0x1989
#define VPP2_DNLP_CTRL_09 0x198a
#define VPP2_DNLP_CTRL_10 0x198b
#define VPP2_DNLP_CTRL_11 0x198c
#define VPP2_DNLP_CTRL_12 0x198d
#define VPP2_DNLP_CTRL_13 0x198e
#define VPP2_DNLP_CTRL_14 0x198f
#define VPP2_DNLP_CTRL_15 0x1990
#define VPP2_VE_ENABLE_CTRL 0x19a1
#define VPP2_VE_DEMO_LEFT_TOP_SCREEN_WIDTH 0x19a2
#define VPP2_VE_DEMO_CENTER_BAR 0x19a3
#define VPP2_VE_H_V_SIZE 0x19a4
#define VPP2_VDO_MEAS_CTRL 0x19a8
#define VPP2_VDO_MEAS_VS_COUNT_HI 0x19a9
#define VPP2_VDO_MEAS_VS_COUNT_LO 0x19aa
#define VPP2_OSD_VSC_PHASE_STEP 0x19c0
#define VPP2_OSD_VSC_INI_PHASE 0x19c1
#define VPP2_OSD_VSC_CTRL0 0x19c2
#define VPP2_OSD_HSC_PHASE_STEP 0x19c3
#define VPP2_OSD_HSC_INI_PHASE 0x19c4
#define VPP2_OSD_HSC_CTRL0 0x19c5
#define VPP2_OSD_HSC_INI_PAT_CTRL 0x19c6
#define VPP2_OSD_SC_DUMMY_DATA 0x19c7
#define VPP2_OSD_SC_CTRL0 0x19c8
#define VPP2_OSD_SCI_WH_M1 0x19c9
#define VPP2_OSD_SCO_H_START_END 0x19ca
#define VPP2_OSD_SCO_V_START_END 0x19cb
#define VPP2_OSD_SCALE_COEF_IDX 0x19cc
#define VPP2_OSD_SCALE_COEF 0x19cd
#define VPP2_INT_LINE_NUM 0x19ce

/* viu */
#define VIU_ADDR_START 0x1a00
#define VIU_ADDR_END 0x1aff
#define VIU_SW_RESET 0x1a01
#define VIU_MISC_CTRL0 0x1a06
#define D2D3_INTF_LENGTH 0x1a08
#define D2D3_INTF_CTRL0 0x1a09
#define VIU_OSD1_CTRL_STAT 0x1a10
#define VIU_OSD1_CTRL_STAT2 0x1a2d
#define VIU_OSD1_COLOR_ADDR 0x1a11
#define VIU_OSD1_COLOR 0x1a12
#define VIU_OSD1_TCOLOR_AG0 0x1a17
#define VIU_OSD1_TCOLOR_AG1 0x1a18
#define VIU_OSD1_TCOLOR_AG2 0x1a19
#define VIU_OSD1_TCOLOR_AG3 0x1a1a
#define VIU_OSD1_BLK0_CFG_W0 0x1a1b
#define VIU_OSD1_BLK1_CFG_W0 0x1a1f
#define VIU_OSD1_BLK2_CFG_W0 0x1a23
#define VIU_OSD1_BLK3_CFG_W0 0x1a27
#define VIU_OSD1_BLK0_CFG_W1 0x1a1c
#define VIU_OSD1_BLK1_CFG_W1 0x1a20
#define VIU_OSD1_BLK2_CFG_W1 0x1a24
#define VIU_OSD1_BLK3_CFG_W1 0x1a28
#define VIU_OSD1_BLK0_CFG_W2 0x1a1d
#define VIU_OSD1_BLK1_CFG_W2 0x1a21
#define VIU_OSD1_BLK2_CFG_W2 0x1a25
#define VIU_OSD1_BLK3_CFG_W2 0x1a29
#define VIU_OSD1_BLK0_CFG_W3 0x1a1e
#define VIU_OSD1_BLK1_CFG_W3 0x1a22
#define VIU_OSD1_BLK2_CFG_W3 0x1a26
#define VIU_OSD1_BLK3_CFG_W3 0x1a2a
#define VIU_OSD1_BLK0_CFG_W4 0x1a13
#define VIU_OSD1_BLK1_CFG_W4 0x1a14
#define VIU_OSD1_BLK2_CFG_W4 0x1a15
#define VIU_OSD1_BLK3_CFG_W4 0x1a16
#define VIU_OSD1_FIFO_CTRL_STAT 0x1a2b
#define VIU_OSD1_TEST_RDDATA 0x1a2c
#define VIU_OSD1_PROT_CTRL 0x1a2e
#define VIU_OSD2_CTRL_STAT 0x1a30
#define VIU_OSD2_CTRL_STAT2 0x1a4d
#define VIU_OSD2_COLOR_ADDR 0x1a31
#define VIU_OSD2_COLOR 0x1a32
#define VIU_OSD2_HL1_H_START_END 0x1a33
#define VIU_OSD2_HL1_V_START_END 0x1a34
#define VIU_OSD2_HL2_H_START_END 0x1a35
#define VIU_OSD2_HL2_V_START_END 0x1a36
#define VIU_OSD2_TCOLOR_AG0 0x1a37
#define VIU_OSD2_TCOLOR_AG1 0x1a38
#define VIU_OSD2_TCOLOR_AG2 0x1a39
#define VIU_OSD2_TCOLOR_AG3 0x1a3a
#define VIU_OSD2_BLK0_CFG_W0 0x1a3b
#define VIU_OSD2_BLK1_CFG_W0 0x1a3f
#define VIU_OSD2_BLK2_CFG_W0 0x1a43
#define VIU_OSD2_BLK3_CFG_W0 0x1a47
#define VIU_OSD2_BLK0_CFG_W1 0x1a3c
#define VIU_OSD2_BLK1_CFG_W1 0x1a40
#define VIU_OSD2_BLK2_CFG_W1 0x1a44
#define VIU_OSD2_BLK3_CFG_W1 0x1a48
#define VIU_OSD2_BLK0_CFG_W2 0x1a3d
#define VIU_OSD2_BLK1_CFG_W2 0x1a41
#define VIU_OSD2_BLK2_CFG_W2 0x1a45
#define VIU_OSD2_BLK3_CFG_W2 0x1a49
#define VIU_OSD2_BLK0_CFG_W3 0x1a3e
#define VIU_OSD2_BLK1_CFG_W3 0x1a42
#define VIU_OSD2_BLK2_CFG_W3 0x1a46
#define VIU_OSD2_BLK3_CFG_W3 0x1a4a
#define VIU_OSD2_BLK0_CFG_W4 0x1a64
#define VIU_OSD2_BLK1_CFG_W4 0x1a65
#define VIU_OSD2_BLK2_CFG_W4 0x1a66
#define VIU_OSD2_BLK3_CFG_W4 0x1a67
#define VIU_OSD2_FIFO_CTRL_STAT 0x1a4b
#define VIU_OSD2_TEST_RDDATA 0x1a4c
#define VIU_OSD2_PROT_CTRL 0x1a4e

#define VD1_IF0_GEN_REG 0x1a50
#define VD1_IF0_CANVAS0 0x1a51
#define VD1_IF0_CANVAS1 0x1a52
#define VD1_IF0_LUMA_X0 0x1a53
#define VD1_IF0_LUMA_Y0 0x1a54
#define VD1_IF0_CHROMA_X0 0x1a55
#define VD1_IF0_CHROMA_Y0 0x1a56
#define VD1_IF0_LUMA_X1 0x1a57
#define VD1_IF0_LUMA_Y1 0x1a58
#define VD1_IF0_CHROMA_X1 0x1a59
#define VD1_IF0_CHROMA_Y1 0x1a5a
#define VD1_IF0_RPT_LOOP 0x1a5b
#define VD1_IF0_LUMA0_RPT_PAT 0x1a5c
#define VD1_IF0_CHROMA0_RPT_PAT 0x1a5d
#define VD1_IF0_LUMA1_RPT_PAT 0x1a5e
#define VD1_IF0_CHROMA1_RPT_PAT 0x1a5f
#define VD1_IF0_LUMA_PSEL 0x1a60
#define VD1_IF0_CHROMA_PSEL 0x1a61
#define VD1_IF0_DUMMY_PIXEL 0x1a62
#define VD1_IF0_LUMA_FIFO_SIZE 0x1a63
#define VD1_IF0_RANGE_MAP_Y 0x1a6a
#define VD1_IF0_RANGE_MAP_CB 0x1a6b
#define VD1_IF0_RANGE_MAP_CR 0x1a6c
#define VD1_IF0_GEN_REG2 0x1a6d
#define VD1_IF0_PROT_CNTL 0x1a6e
#define VIU_VD1_FMT_CTRL 0x1a68
#define VIU_VD1_FMT_W 0x1a69
#define VD2_IF0_GEN_REG 0x1a70
#define VD2_IF0_CANVAS0 0x1a71
#define VD2_IF0_CANVAS1 0x1a72
#define VD2_IF0_LUMA_X0 0x1a73
#define VD2_IF0_LUMA_Y0 0x1a74
#define VD2_IF0_CHROMA_X0 0x1a75
#define VD2_IF0_CHROMA_Y0 0x1a76
#define VD2_IF0_LUMA_X1 0x1a77
#define VD2_IF0_LUMA_Y1 0x1a78
#define VD2_IF0_CHROMA_X1 0x1a79
#define VD2_IF0_CHROMA_Y1 0x1a7a
#define VD2_IF0_RPT_LOOP 0x1a7b
#define VD2_IF0_LUMA0_RPT_PAT 0x1a7c
#define VD2_IF0_CHROMA0_RPT_PAT 0x1a7d
#define VD2_IF0_LUMA1_RPT_PAT 0x1a7e
#define VD2_IF0_CHROMA1_RPT_PAT 0x1a7f
#define VD2_IF0_LUMA_PSEL 0x1a80
#define VD2_IF0_CHROMA_PSEL 0x1a81
#define VD2_IF0_DUMMY_PIXEL 0x1a82
#define VD2_IF0_LUMA_FIFO_SIZE 0x1a83
#define VD2_IF0_RANGE_MAP_Y 0x1a8a
#define VD2_IF0_RANGE_MAP_CB 0x1a8b
#define VD2_IF0_RANGE_MAP_CR 0x1a8c
#define VD2_IF0_GEN_REG2 0x1a8d
#define VD2_IF0_PROT_CNTL 0x1a8e
#define VIU_VD2_FMT_CTRL 0x1a88
#define VIU_VD2_FMT_W 0x1a89

/* vpp */
#define VPP_DUMMY_DATA 0x1d00
#define VPP_LINE_IN_LENGTH 0x1d01
#define VPP_PIC_IN_HEIGHT 0x1d02
#define VPP_SCALE_COEF_IDX 0x1d03
#define VPP_SCALE_COEF 0x1d04
#define VPP_VSC_REGION12_STARTP 0x1d05
#define VPP_VSC_REGION34_STARTP 0x1d06
#define VPP_VSC_REGION4_ENDP 0x1d07
#define VPP_VSC_START_PHASE_STEP 0x1d08
#define VPP_VSC_REGION0_PHASE_SLOPE 0x1d09
#define VPP_VSC_REGION1_PHASE_SLOPE 0x1d0a
#define VPP_VSC_REGION3_PHASE_SLOPE 0x1d0b
#define VPP_VSC_REGION4_PHASE_SLOPE 0x1d0c
#define VPP_VSC_PHASE_CTRL 0x1d0d
#define VPP_VSC_INI_PHASE 0x1d0e
#define VPP_HSC_REGION12_STARTP 0x1d10
#define VPP_HSC_REGION34_STARTP 0x1d11
#define VPP_HSC_REGION4_ENDP 0x1d12
#define VPP_HSC_START_PHASE_STEP 0x1d13
#define VPP_HSC_REGION0_PHASE_SLOPE 0x1d14
#define VPP_HSC_REGION1_PHASE_SLOPE 0x1d15
#define VPP_HSC_REGION3_PHASE_SLOPE 0x1d16
#define VPP_HSC_REGION4_PHASE_SLOPE 0x1d17
#define VPP_HSC_PHASE_CTRL 0x1d18
#define VPP_SC_MISC 0x1d19
#define VPP_PREBLEND_VD1_H_START_END 0x1d1a
#define VPP_PREBLEND_VD1_V_START_END 0x1d1b
#define VPP_POSTBLEND_VD1_H_START_END 0x1d1c
#define VPP_POSTBLEND_VD1_V_START_END 0x1d1d
#define VPP_BLEND_VD2_H_START_END 0x1d1e
#define VPP_BLEND_VD2_V_START_END 0x1d1f
#define VPP_PREBLEND_H_SIZE 0x1d20
#define VPP_POSTBLEND_H_SIZE 0x1d21
#define VPP_HOLD_LINES 0x1d22
#define VPP_BLEND_ONECOLOR_CTRL 0x1d23
#define VPP_PREBLEND_CURRENT_XY 0x1d24
#define VPP_POSTBLEND_CURRENT_XY 0x1d25
#define VPP_MISC 0x1d26
#define VPP_OFIFO_SIZE 0x1d27
#define VPP_FIFO_STATUS 0x1d28
#define VPP_SMOKE_CTRL 0x1d29
#define VPP_SMOKE1_VAL 0x1d2a
#define VPP_SMOKE2_VAL 0x1d2b
#define VPP_SMOKE3_VAL 0x1d2c
#define VPP_SMOKE1_H_START_END 0x1d2d
#define VPP_SMOKE1_V_START_END 0x1d2e
#define VPP_SMOKE2_H_START_END 0x1d2f
#define VPP_SMOKE2_V_START_END 0x1d30
#define VPP_SMOKE3_H_START_END 0x1d31
#define VPP_SMOKE3_V_START_END 0x1d32
#define VPP_SCO_FIFO_CTRL 0x1d33
#define VPP_HSC_PHASE_CTRL1 0x1d34
#define VPP_HSC_INI_PAT_CTRL 0x1d35
#define VPP_VADJ_CTRL 0x1d40
#define VPP_VADJ1_Y 0x1d41
#define VPP_VADJ1_MA_MB 0x1d42
#define VPP_VADJ1_MC_MD 0x1d43
#define VPP_VADJ2_Y 0x1d44
#define VPP_VADJ2_MA_MB 0x1d45
#define VPP_VADJ2_MC_MD 0x1d46
#define VPP_HSHARP_CTRL 0x1d50
#define VPP_HSHARP_LUMA_THRESH01 0x1d51
#define VPP_HSHARP_LUMA_THRESH23 0x1d52
#define VPP_HSHARP_CHROMA_THRESH01 0x1d53
#define VPP_HSHARP_CHROMA_THRESH23 0x1d54
#define VPP_HSHARP_LUMA_GAIN 0x1d55
#define VPP_HSHARP_CHROMA_GAIN 0x1d56
#define VPP_MATRIX_PROBE_COLOR 0x1d5c
#define VPP_MATRIX_HL_COLOR 0x1d5d
#define VPP_MATRIX_PROBE_POS 0x1d5e
#define VPP_MATRIX_CTRL 0x1d5f
#define VPP_MATRIX_COEF00_01 0x1d60
#define VPP_MATRIX_COEF02_10 0x1d61
#define VPP_MATRIX_COEF11_12 0x1d62
#define VPP_MATRIX_COEF20_21 0x1d63
#define VPP_MATRIX_COEF22 0x1d64
#define VPP_MATRIX_OFFSET0_1 0x1d65
#define VPP_MATRIX_OFFSET2 0x1d66
#define VPP_MATRIX_PRE_OFFSET0_1 0x1d67
#define VPP_MATRIX_PRE_OFFSET2 0x1d68
#define VPP_DUMMY_DATA1 0x1d69
#define VPP_GAINOFF_CTRL0 0x1d6a
#define VPP_GAINOFF_CTRL1 0x1d6b
#define VPP_GAINOFF_CTRL2 0x1d6c
#define VPP_GAINOFF_CTRL3 0x1d6d
#define VPP_GAINOFF_CTRL4 0x1d6e
#define VPP_CHROMA_ADDR_PORT 0x1d70
#define VPP_CHROMA_DATA_PORT 0x1d71
#define VPP_GCLK_CTRL0 0x1d72
#define VPP_GCLK_CTRL1 0x1d73
#define VPP_SC_GCLK_CTRL 0x1d74
#define VPP_MISC1 0x1d76
#define VPP_BLACKEXT_CTRL 0x1d80
#define VPP_DNLP_CTRL_00 0x1d81
#define VPP_DNLP_CTRL_01 0x1d82
#define VPP_DNLP_CTRL_02 0x1d83
#define VPP_DNLP_CTRL_03 0x1d84
#define VPP_DNLP_CTRL_04 0x1d85
#define VPP_DNLP_CTRL_05 0x1d86
#define VPP_DNLP_CTRL_06 0x1d87
#define VPP_DNLP_CTRL_07 0x1d88
#define VPP_DNLP_CTRL_08 0x1d89
#define VPP_DNLP_CTRL_09 0x1d8a
#define VPP_DNLP_CTRL_10 0x1d8b
#define VPP_DNLP_CTRL_11 0x1d8c
#define VPP_DNLP_CTRL_12 0x1d8d
#define VPP_DNLP_CTRL_13 0x1d8e
#define VPP_DNLP_CTRL_14 0x1d8f
#define VPP_DNLP_CTRL_15 0x1d90
#define VPP_PEAKING_HGAIN 0x1d91
#define VPP_PEAKING_VGAIN 0x1d92
#define VPP_PEAKING_NLP_1 0x1d93
#define VPP_PEAKING_NLP_2 0x1d94
#define VPP_PEAKING_NLP_3 0x1d95
#define VPP_PEAKING_NLP_4 0x1d96
#define VPP_PEAKING_NLP_5 0x1d97
#define VPP_SHARP_LIMIT 0x1d98
#define VPP_VLTI_CTRL 0x1d99
#define VPP_HLTI_CTRL 0x1d9a
#define VPP_CTI_CTRL 0x1d9b
#define VPP_BLUE_STRETCH_1 0x1d9c
#define VPP_BLUE_STRETCH_2 0x1d9d
#define VPP_BLUE_STRETCH_3 0x1d9e
#define VPP_CCORING_CTRL 0x1da0
#define VPP_VE_ENABLE_CTRL 0x1da1
#define VPP_VE_DEMO_LEFT_TOP_SCREEN_WIDTH 0x1da2
#define VPP_VE_DEMO_CENTER_BAR 0x1da3
#define VPP_VE_H_V_SIZE 0x1da4
#define VPP_VDO_MEAS_CTRL 0x1da8
#define VPP_VDO_MEAS_VS_COUNT_HI 0x1da9
#define VPP_VDO_MEAS_VS_COUNT_LO 0x1daa
#define VPP_INPUT_CTRL 0x1dab
#define VPP_CTI_CTRL2 0x1dac
#define VPP_PEAKING_SAT_THD1 0x1dad
#define VPP_PEAKING_SAT_THD2 0x1dae
#define VPP_PEAKING_SAT_THD3 0x1daf
#define VPP_PEAKING_SAT_THD4 0x1db0
#define VPP_PEAKING_SAT_THD5 0x1db1
#define VPP_PEAKING_SAT_THD6 0x1db2
#define VPP_PEAKING_SAT_THD7 0x1db3
#define VPP_PEAKING_SAT_THD8 0x1db4
#define VPP_PEAKING_SAT_THD9 0x1db5
#define VPP_PEAKING_GAIN_ADD1 0x1db6
#define VPP_PEAKING_GAIN_ADD2 0x1db7
#define VPP_PEAKING_DNLP 0x1db8
#define VPP_SHARP_DEMO_WIN_CTRL1 0x1db9
#define VPP_SHARP_DEMO_WIN_CTRL2 0x1dba
#define VPP_FRONT_HLTI_CTRL 0x1dbb
#define VPP_FRONT_CTI_CTRL 0x1dbc
#define VPP_FRONT_CTI_CTRL2 0x1dbd
#define VPP_OSD_VSC_PHASE_STEP 0x1dc0
#define VPP_OSD_VSC_INI_PHASE 0x1dc1
#define VPP_OSD_VSC_CTRL0 0x1dc2
#define VPP_OSD_HSC_PHASE_STEP 0x1dc3
#define VPP_OSD_HSC_INI_PHASE 0x1dc4
#define VPP_OSD_HSC_CTRL0 0x1dc5
#define VPP_OSD_HSC_INI_PAT_CTRL 0x1dc6
#define VPP_OSD_SC_DUMMY_DATA 0x1dc7
#define VPP_OSD_SC_CTRL0 0x1dc8
#define VPP_OSD_SCI_WH_M1 0x1dc9
#define VPP_OSD_SCO_H_START_END 0x1dca
#define VPP_OSD_SCO_V_START_END 0x1dcb
#define VPP_OSD_SCALE_COEF_IDX 0x1dcc
#define VPP_OSD_SCALE_COEF 0x1dcd
#define VPP_INT_LINE_NUM 0x1dce

/* viu2 */
#define VIU2_ADDR_START 0x1e00
#define VIU2_ADDR_END 0x1eff
#define VIU2_SW_RESET 0x1e01
#define VIU2_OSD1_CTRL_STAT 0x1e10
#define VIU2_OSD1_CTRL_STAT2 0x1e2d
#define VIU2_OSD1_COLOR_ADDR 0x1e11
#define VIU2_OSD1_COLOR 0x1e12
#define VIU2_OSD1_TCOLOR_AG0 0x1e17
#define VIU2_OSD1_TCOLOR_AG1 0x1e18
#define VIU2_OSD1_TCOLOR_AG2 0x1e19
#define VIU2_OSD1_TCOLOR_AG3 0x1e1a
#define VIU2_OSD1_BLK0_CFG_W0 0x1e1b
#define VIU2_OSD1_BLK1_CFG_W0 0x1e1f
#define VIU2_OSD1_BLK2_CFG_W0 0x1e23
#define VIU2_OSD1_BLK3_CFG_W0 0x1e27
#define VIU2_OSD1_BLK0_CFG_W1 0x1e1c
#define VIU2_OSD1_BLK1_CFG_W1 0x1e20
#define VIU2_OSD1_BLK2_CFG_W1 0x1e24
#define VIU2_OSD1_BLK3_CFG_W1 0x1e28
#define VIU2_OSD1_BLK0_CFG_W2 0x1e1d
#define VIU2_OSD1_BLK1_CFG_W2 0x1e21
#define VIU2_OSD1_BLK2_CFG_W2 0x1e25
#define VIU2_OSD1_BLK3_CFG_W2 0x1e29
#define VIU2_OSD1_BLK0_CFG_W3 0x1e1e
#define VIU2_OSD1_BLK1_CFG_W3 0x1e22
#define VIU2_OSD1_BLK2_CFG_W3 0x1e26
#define VIU2_OSD1_BLK3_CFG_W3 0x1e2a
#define VIU2_OSD1_BLK0_CFG_W4 0x1e13
#define VIU2_OSD1_BLK1_CFG_W4 0x1e14
#define VIU2_OSD1_BLK2_CFG_W4 0x1e15
#define VIU2_OSD1_BLK3_CFG_W4 0x1e16
#define VIU2_OSD1_FIFO_CTRL_STAT 0x1e2b
#define VIU2_OSD1_TEST_RDDATA 0x1e2c
#define VIU2_OSD1_PROT_CTRL 0x1e2e
#define VIU2_OSD2_CTRL_STAT 0x1e30
#define VIU2_OSD2_CTRL_STAT2 0x1e4d
#define VIU2_OSD2_COLOR_ADDR 0x1e31
#define VIU2_OSD2_COLOR 0x1e32
#define VIU2_OSD2_HL1_H_START_END 0x1e33
#define VIU2_OSD2_HL1_V_START_END 0x1e34
#define VIU2_OSD2_HL2_H_START_END 0x1e35
#define VIU2_OSD2_HL2_V_START_END 0x1e36
#define VIU2_OSD2_TCOLOR_AG0 0x1e37
#define VIU2_OSD2_TCOLOR_AG1 0x1e38
#define VIU2_OSD2_TCOLOR_AG2 0x1e39
#define VIU2_OSD2_TCOLOR_AG3 0x1e3a
#define VIU2_OSD2_BLK0_CFG_W0 0x1e3b
#define VIU2_OSD2_BLK1_CFG_W0 0x1e3f
#define VIU2_OSD2_BLK2_CFG_W0 0x1e43
#define VIU2_OSD2_BLK3_CFG_W0 0x1e47
#define VIU2_OSD2_BLK0_CFG_W1 0x1e3c
#define VIU2_OSD2_BLK1_CFG_W1 0x1e40
#define VIU2_OSD2_BLK2_CFG_W1 0x1e44
#define VIU2_OSD2_BLK3_CFG_W1 0x1e48
#define VIU2_OSD2_BLK0_CFG_W2 0x1e3d
#define VIU2_OSD2_BLK1_CFG_W2 0x1e41
#define VIU2_OSD2_BLK2_CFG_W2 0x1e45
#define VIU2_OSD2_BLK3_CFG_W2 0x1e49
#define VIU2_OSD2_BLK0_CFG_W3 0x1e3e
#define VIU2_OSD2_BLK1_CFG_W3 0x1e42
#define VIU2_OSD2_BLK2_CFG_W3 0x1e46
#define VIU2_OSD2_BLK3_CFG_W3 0x1e4a
#define VIU2_OSD2_BLK0_CFG_W4 0x1e64
#define VIU2_OSD2_BLK1_CFG_W4 0x1e65
#define VIU2_OSD2_BLK2_CFG_W4 0x1e66
#define VIU2_OSD2_BLK3_CFG_W4 0x1e67
#define VIU2_OSD2_FIFO_CTRL_STAT 0x1e4b
#define VIU2_OSD2_TEST_RDDATA 0x1e4c
#define VIU2_OSD2_PROT_CTRL 0x1e4e
#define VIU2_VD1_IF0_GEN_REG 0x1e50
#define VIU2_VD1_IF0_CANVAS0 0x1e51
#define VIU2_VD1_IF0_CANVAS1 0x1e52
#define VIU2_VD1_IF0_LUMA_X0 0x1e53
#define VIU2_VD1_IF0_LUMA_Y0 0x1e54
#define VIU2_VD1_IF0_CHROMA_X0 0x1e55
#define VIU2_VD1_IF0_CHROMA_Y0 0x1e56
#define VIU2_VD1_IF0_LUMA_X1 0x1e57
#define VIU2_VD1_IF0_LUMA_Y1 0x1e58
#define VIU2_VD1_IF0_CHROMA_X1 0x1e59
#define VIU2_VD1_IF0_CHROMA_Y1 0x1e5a
#define VIU2_VD1_IF0_RPT_LOOP 0x1e5b
#define VIU2_VD1_IF0_LUMA0_RPT_PAT 0x1e5c
#define VIU2_VD1_IF0_CHROMA0_RPT_PAT 0x1e5d
#define VIU2_VD1_IF0_LUMA1_RPT_PAT 0x1e5e
#define VIU2_VD1_IF0_CHROMA1_RPT_PAT 0x1e5f
#define VIU2_VD1_IF0_LUMA_PSEL 0x1e60
#define VIU2_VD1_IF0_CHROMA_PSEL 0x1e61
#define VIU2_VD1_IF0_DUMMY_PIXEL 0x1e62
#define VIU2_VD1_IF0_LUMA_FIFO_SIZE 0x1e63
#define VIU2_VD1_IF0_RANGE_MAP_Y 0x1e6a
#define VIU2_VD1_IF0_RANGE_MAP_CB 0x1e6b
#define VIU2_VD1_IF0_RANGE_MAP_CR 0x1e6c
#define VIU2_VD1_IF0_GEN_REG2 0x1e6d
#define VIU2_VD1_IF0_PROT_CNTL 0x1e6e
#define VIU2_VD1_FMT_CTRL 0x1e68
#define VIU2_VD1_FMT_W 0x1e69

/* encode */
#define ENCP_VFIFO2VD_CTL 0x1b58
#define ENCP_VFIFO2VD_PIXEL_START 0x1b59
#define ENCP_VFIFO2VD_PIXEL_END 0x1b5a
#define ENCP_VFIFO2VD_LINE_TOP_START 0x1b5b
#define ENCP_VFIFO2VD_LINE_TOP_END 0x1b5c
#define ENCP_VFIFO2VD_LINE_BOT_START 0x1b5d
#define ENCP_VFIFO2VD_LINE_BOT_END 0x1b5e
#define VENC_SYNC_ROUTE 0x1b60
#define VENC_VIDEO_EXSRC 0x1b61
#define VENC_DVI_SETTING 0x1b62
#define VENC_C656_CTRL 0x1b63
#define VENC_UPSAMPLE_CTRL0 0x1b64
#define VENC_UPSAMPLE_CTRL1 0x1b65
#define VENC_UPSAMPLE_CTRL2 0x1b66
#define TCON_INVERT_CTL 0x1b67
#define VENC_VIDEO_PROG_MODE 0x1b68
#define VENC_ENCI_LINE 0x1b69
#define VENC_ENCI_PIXEL 0x1b6a
#define VENC_ENCP_LINE 0x1b6b
#define VENC_ENCP_PIXEL 0x1b6c
#define VENC_STATA 0x1b6d
#define VENC_INTCTRL 0x1b6e
#define VENC_INTFLAG 0x1b6f
#define VENC_VIDEO_TST_EN 0x1b70
#define VENC_VIDEO_TST_MDSEL 0x1b71
#define VENC_VIDEO_TST_Y 0x1b72
#define VENC_VIDEO_TST_CB 0x1b73
#define VENC_VIDEO_TST_CR 0x1b74
#define VENC_VIDEO_TST_CLRBAR_STRT 0x1b75
#define VENC_VIDEO_TST_CLRBAR_WIDTH 0x1b76
#define VENC_VIDEO_TST_VDCNT_STSET 0x1b77
#define VENC_VDAC_DACSEL0 0x1b78
#define VENC_VDAC_DACSEL1 0x1b79
#define VENC_VDAC_DACSEL2 0x1b7a
#define VENC_VDAC_DACSEL3 0x1b7b
#define VENC_VDAC_DACSEL4 0x1b7c
#define VENC_VDAC_DACSEL5 0x1b7d
#define VENC_VDAC_SETTING 0x1b7e
#define VENC_VDAC_TST_VAL 0x1b7f
#define VENC_VDAC_DAC0_GAINCTRL 0x1bf0
#define VENC_VDAC_DAC0_OFFSET 0x1bf1
#define VENC_VDAC_DAC1_GAINCTRL 0x1bf2
#define VENC_VDAC_DAC1_OFFSET 0x1bf3
#define VENC_VDAC_DAC2_GAINCTRL 0x1bf4
#define VENC_VDAC_DAC2_OFFSET 0x1bf5
#define VENC_VDAC_DAC3_GAINCTRL 0x1bf6
#define VENC_VDAC_DAC3_OFFSET 0x1bf7
#define VENC_VDAC_DAC4_GAINCTRL 0x1bf8
#define VENC_VDAC_DAC4_OFFSET 0x1bf9
#define VENC_VDAC_DAC5_GAINCTRL 0x1bfa
#define VENC_VDAC_DAC5_OFFSET 0x1bfb
#define VENC_VDAC_FIFO_CTRL 0x1bfc
#define ENCL_TCON_INVERT_CTL 0x1bfd
#define ENCP_VIDEO_EN 0x1b80
#define ENCP_VIDEO_SYNC_MODE 0x1b81
#define ENCP_MACV_EN 0x1b82
#define ENCP_VIDEO_Y_SCL 0x1b83
#define ENCP_VIDEO_PB_SCL 0x1b84
#define ENCP_VIDEO_PR_SCL 0x1b85
#define ENCP_VIDEO_SYNC_SCL 0x1b86
#define ENCP_VIDEO_MACV_SCL 0x1b87
#define ENCP_VIDEO_Y_OFFST 0x1b88
#define ENCP_VIDEO_PB_OFFST 0x1b89
#define ENCP_VIDEO_PR_OFFST 0x1b8a
#define ENCP_VIDEO_SYNC_OFFST 0x1b8b
#define ENCP_VIDEO_MACV_OFFST 0x1b8c
#define ENCP_VIDEO_MODE 0x1b8d
#define ENCP_VIDEO_MODE_ADV 0x1b8e
#define ENCP_DBG_PX_RST 0x1b90
#define ENCP_DBG_LN_RST 0x1b91
#define ENCP_DBG_PX_INT 0x1b92
#define ENCP_DBG_LN_INT 0x1b93
#define ENCP_VIDEO_YFP1_HTIME 0x1b94
#define ENCP_VIDEO_YFP2_HTIME 0x1b95
#define ENCP_VIDEO_YC_DLY 0x1b96
#define ENCP_VIDEO_MAX_PXCNT 0x1b97
#define ENCP_VIDEO_HSPULS_BEGIN 0x1b98
#define ENCP_VIDEO_HSPULS_END 0x1b99
#define ENCP_VIDEO_HSPULS_SWITCH 0x1b9a
#define ENCP_VIDEO_VSPULS_BEGIN 0x1b9b
#define ENCP_VIDEO_VSPULS_END 0x1b9c
#define ENCP_VIDEO_VSPULS_BLINE 0x1b9d
#define ENCP_VIDEO_VSPULS_ELINE 0x1b9e
#define ENCP_VIDEO_EQPULS_BEGIN 0x1b9f
#define ENCP_VIDEO_EQPULS_END 0x1ba0
#define ENCP_VIDEO_EQPULS_BLINE 0x1ba1
#define ENCP_VIDEO_EQPULS_ELINE 0x1ba2
#define ENCP_VIDEO_HAVON_END 0x1ba3
#define ENCP_VIDEO_HAVON_BEGIN 0x1ba4
#define ENCP_VIDEO_VAVON_ELINE 0x1baf
#define ENCP_VIDEO_VAVON_BLINE 0x1ba6
#define ENCP_VIDEO_HSO_BEGIN 0x1ba7
#define ENCP_VIDEO_HSO_END 0x1ba8
#define ENCP_VIDEO_VSO_BEGIN 0x1ba9
#define ENCP_VIDEO_VSO_END 0x1baa
#define ENCP_VIDEO_VSO_BLINE 0x1bab
#define ENCP_VIDEO_VSO_ELINE 0x1bac
#define ENCP_VIDEO_SYNC_WAVE_CURVE 0x1bad
#define ENCP_VIDEO_MAX_LNCNT 0x1bae
#define ENCP_VIDEO_SY_VAL 0x1bb0
#define ENCP_VIDEO_SY2_VAL 0x1bb1
#define ENCP_VIDEO_BLANKY_VAL 0x1bb2
#define ENCP_VIDEO_BLANKPB_VAL 0x1bb3
#define ENCP_VIDEO_BLANKPR_VAL 0x1bb4
#define ENCP_VIDEO_HOFFST 0x1bb5
#define ENCP_VIDEO_VOFFST 0x1bb6
#define ENCP_VIDEO_RGB_CTRL 0x1bb7
#define ENCP_VIDEO_FILT_CTRL 0x1bb8
#define ENCP_VIDEO_OFLD_VPEQ_OFST 0x1bb9
#define ENCP_VIDEO_OFLD_VOAV_OFST 0x1bba
#define ENCP_VIDEO_MATRIX_CB 0x1bbb
#define ENCP_VIDEO_MATRIX_CR 0x1bbc
#define ENCP_VIDEO_RGBIN_CTRL 0x1bbd
#define ENCP_MACV_BLANKY_VAL 0x1bc0
#define ENCP_MACV_MAXY_VAL 0x1bc1
#define ENCP_MACV_1ST_PSSYNC_STRT 0x1bc2
#define ENCP_MACV_PSSYNC_STRT 0x1bc3
#define ENCP_MACV_AGC_STRT 0x1bc4
#define ENCP_MACV_AGC_END 0x1bc5
#define ENCP_MACV_WAVE_END 0x1bc6
#define ENCP_MACV_STRTLINE 0x1bc7
#define ENCP_MACV_ENDLINE 0x1bc8
#define ENCP_MACV_TS_CNT_MAX_L 0x1bc9
#define ENCP_MACV_TS_CNT_MAX_H 0x1bca
#define ENCP_MACV_TIME_DOWN 0x1bcb
#define ENCP_MACV_TIME_LO 0x1bcc
#define ENCP_MACV_TIME_UP 0x1bcd
#define ENCP_MACV_TIME_RST 0x1bce
#define ENCP_VBI_CTRL 0x1bd0
#define ENCP_VBI_SETTING 0x1bd1
#define ENCP_VBI_BEGIN 0x1bd2
#define ENCP_VBI_WIDTH 0x1bd3
#define ENCP_VBI_HVAL 0x1bd4
#define ENCP_VBI_DATA0 0x1bd5
#define ENCP_VBI_DATA1 0x1bd6
#define C656_HS_ST 0x1be0
#define C656_HS_ED 0x1be1
#define C656_VS_LNST_E 0x1be2
#define C656_VS_LNST_O 0x1be3
#define C656_VS_LNED_E 0x1be4
#define C656_VS_LNED_O 0x1be5
#define C656_FS_LNST 0x1be6
#define C656_FS_LNED 0x1be7
#define ENCI_VIDEO_MODE 0x1b00
#define ENCI_VIDEO_MODE_ADV 0x1b01
#define ENCI_VIDEO_FSC_ADJ 0x1b02
#define ENCI_VIDEO_BRIGHT 0x1b03
#define ENCI_VIDEO_CONT 0x1b04
#define ENCI_VIDEO_SAT 0x1b05
#define ENCI_VIDEO_HUE 0x1b06
#define ENCI_VIDEO_SCH 0x1b07
#define ENCI_SYNC_MODE 0x1b08
#define ENCI_SYNC_CTRL 0x1b09
#define ENCI_SYNC_HSO_BEGIN 0x1b0a
#define ENCI_SYNC_HSO_END 0x1b0b
#define ENCI_SYNC_VSO_EVN 0x1b0c
#define ENCI_SYNC_VSO_ODD 0x1b0d
#define ENCI_SYNC_VSO_EVNLN 0x1b0e
#define ENCI_SYNC_VSO_ODDLN 0x1b0f
#define ENCI_SYNC_HOFFST 0x1b10
#define ENCI_SYNC_VOFFST 0x1b11
#define ENCI_SYNC_ADJ 0x1b12
#define ENCI_RGB_SETTING 0x1b13
#define ENCI_DE_H_BEGIN 0x1b16
#define ENCI_DE_H_END 0x1b17
#define ENCI_DE_V_BEGIN_EVEN 0x1b18
#define ENCI_DE_V_END_EVEN 0x1b19
#define ENCI_DE_V_BEGIN_ODD 0x1b1a
#define ENCI_DE_V_END_ODD 0x1b1b
#define ENCI_VBI_SETTING 0x1b20
#define ENCI_VBI_CCDT_EVN 0x1b21
#define ENCI_VBI_CCDT_ODD 0x1b22
#define ENCI_VBI_CC525_LN 0x1b23
#define ENCI_VBI_CC625_LN 0x1b24
#define ENCI_VBI_WSSDT 0x1b25
#define ENCI_VBI_WSS_LN 0x1b26
#define ENCI_VBI_CGMSDT_L 0x1b27
#define ENCI_VBI_CGMSDT_H 0x1b28
#define ENCI_VBI_CGMS_LN 0x1b29
#define ENCI_VBI_TTX_HTIME 0x1b2a
#define ENCI_VBI_TTX_LN 0x1b2b
#define ENCI_VBI_TTXDT0 0x1b2c
#define ENCI_VBI_TTXDT1 0x1b2d
#define ENCI_VBI_TTXDT2 0x1b2e
#define ENCI_VBI_TTXDT3 0x1b2f
#define ENCI_MACV_N0 0x1b30
#define ENCI_MACV_N1 0x1b31
#define ENCI_MACV_N2 0x1b32
#define ENCI_MACV_N3 0x1b33
#define ENCI_MACV_N4 0x1b34
#define ENCI_MACV_N5 0x1b35
#define ENCI_MACV_N6 0x1b36
#define ENCI_MACV_N7 0x1b37
#define ENCI_MACV_N8 0x1b38
#define ENCI_MACV_N9 0x1b39
#define ENCI_MACV_N10 0x1b3a
#define ENCI_MACV_N11 0x1b3b
#define ENCI_MACV_N12 0x1b3c
#define ENCI_MACV_N13 0x1b3d
#define ENCI_MACV_N14 0x1b3e
#define ENCI_MACV_N15 0x1b3f
#define ENCI_MACV_N16 0x1b40
#define ENCI_MACV_N17 0x1b41
#define ENCI_MACV_N18 0x1b42
#define ENCI_MACV_N19 0x1b43
#define ENCI_MACV_N20 0x1b44
#define ENCI_MACV_N21 0x1b45
#define ENCI_MACV_N22 0x1b46
#define ENCI_DBG_PX_RST 0x1b48
#define ENCI_DBG_FLDLN_RST 0x1b49
#define ENCI_DBG_PX_INT 0x1b4a
#define ENCI_DBG_FLDLN_INT 0x1b4b
#define ENCI_DBG_MAXPX 0x1b4c
#define ENCI_DBG_MAXLN 0x1b4d
#define ENCI_MACV_MAX_AMP 0x1b50
#define ENCI_MACV_PULSE_LO 0x1b51
#define ENCI_MACV_PULSE_HI 0x1b52
#define ENCI_MACV_BKP_MAX 0x1b53
#define ENCI_CFILT_CTRL 0x1b54
#define ENCI_CFILT7 0x1b55
#define ENCI_YC_DELAY 0x1b56
#define ENCI_VIDEO_EN 0x1b57
#define ENCI_DVI_HSO_BEGIN 0x1c00
#define ENCI_DVI_HSO_END 0x1c01
#define ENCI_DVI_VSO_BLINE_EVN 0x1c02
#define ENCI_DVI_VSO_BLINE_ODD 0x1c03
#define ENCI_DVI_VSO_ELINE_EVN 0x1c04
#define ENCI_DVI_VSO_ELINE_ODD 0x1c05
#define ENCI_DVI_VSO_BEGIN_EVN 0x1c06
#define ENCI_DVI_VSO_BEGIN_ODD 0x1c07
#define ENCI_DVI_VSO_END_EVN 0x1c08
#define ENCI_DVI_VSO_END_ODD 0x1c09
#define ENCI_CFILT_CTRL2 0x1c0a
#define ENCI_DACSEL_0 0x1c0b
#define ENCI_DACSEL_1 0x1c0c
#define ENCP_DACSEL_0 0x1c0d
#define ENCP_DACSEL_1 0x1c0e
#define ENCP_MAX_LINE_SWITCH_POINT 0x1c0f
#define ENCI_TST_EN 0x1c10
#define ENCI_TST_MDSEL 0x1c11
#define ENCI_TST_Y 0x1c12
#define ENCI_TST_CB 0x1c13
#define ENCI_TST_CR 0x1c14
#define ENCI_TST_CLRBAR_STRT 0x1c15
#define ENCI_TST_CLRBAR_WIDTH 0x1c16
#define ENCI_TST_VDCNT_STSET 0x1c17
#define ENCI_VFIFO2VD_CTL 0x1c18
#define ENCI_VFIFO2VD_PIXEL_START 0x1c19
#define ENCI_VFIFO2VD_PIXEL_END 0x1c1a
#define ENCI_VFIFO2VD_LINE_TOP_START 0x1c1b
#define ENCI_VFIFO2VD_LINE_TOP_END 0x1c1c
#define ENCI_VFIFO2VD_LINE_BOT_START 0x1c1d
#define ENCI_VFIFO2VD_LINE_BOT_END 0x1c1e
#define ENCI_VFIFO2VD_CTL2 0x1c1f
#define ENCT_VFIFO2VD_CTL 0x1c20
#define ENCT_VFIFO2VD_PIXEL_START 0x1c21
#define ENCT_VFIFO2VD_PIXEL_END 0x1c22
#define ENCT_VFIFO2VD_LINE_TOP_START 0x1c23
#define ENCT_VFIFO2VD_LINE_TOP_END 0x1c24
#define ENCT_VFIFO2VD_LINE_BOT_START 0x1c25
#define ENCT_VFIFO2VD_LINE_BOT_END 0x1c26
#define ENCT_VFIFO2VD_CTL2 0x1c27
#define ENCT_TST_EN 0x1c28
#define ENCT_TST_MDSEL 0x1c29
#define ENCT_TST_Y 0x1c2a
#define ENCT_TST_CB 0x1c2b
#define ENCT_TST_CR 0x1c2c
#define ENCT_TST_CLRBAR_STRT 0x1c2d
#define ENCT_TST_CLRBAR_WIDTH 0x1c2e
#define ENCT_TST_VDCNT_STSET 0x1c2f
#define ENCP_DVI_HSO_BEGIN 0x1c30
#define ENCP_DVI_HSO_END 0x1c31
#define ENCP_DVI_VSO_BLINE_EVN 0x1c32
#define ENCP_DVI_VSO_BLINE_ODD 0x1c33
#define ENCP_DVI_VSO_ELINE_EVN 0x1c34
#define ENCP_DVI_VSO_ELINE_ODD 0x1c35
#define ENCP_DVI_VSO_BEGIN_EVN 0x1c36
#define ENCP_DVI_VSO_BEGIN_ODD 0x1c37
#define ENCP_DVI_VSO_END_EVN 0x1c38
#define ENCP_DVI_VSO_END_ODD 0x1c39
#define ENCP_DE_H_BEGIN 0x1c3a
#define ENCP_DE_H_END 0x1c3b
#define ENCP_DE_V_BEGIN_EVEN 0x1c3c
#define ENCP_DE_V_END_EVEN 0x1c3d
#define ENCP_DE_V_BEGIN_ODD 0x1c3e
#define ENCP_DE_V_END_ODD 0x1c3f
#define ENCI_SYNC_LINE_LENGTH 0x1c40
#define ENCI_SYNC_PIXEL_EN 0x1c41
#define ENCI_SYNC_TO_LINE_EN 0x1c42
#define ENCI_SYNC_TO_PIXEL 0x1c43
#define ENCP_SYNC_LINE_LENGTH 0x1c44
#define ENCP_SYNC_PIXEL_EN 0x1c45
#define ENCP_SYNC_TO_LINE_EN 0x1c46
#define ENCP_SYNC_TO_PIXEL 0x1c47
#define ENCT_SYNC_LINE_LENGTH 0x1c48
#define ENCT_SYNC_PIXEL_EN 0x1c49
#define ENCT_SYNC_TO_LINE_EN 0x1c4a
#define ENCT_SYNC_TO_PIXEL 0x1c4b
#define ENCL_SYNC_LINE_LENGTH 0x1c4c
#define ENCL_SYNC_PIXEL_EN 0x1c4d
#define ENCL_SYNC_TO_LINE_EN 0x1c4e
#define ENCL_SYNC_TO_PIXEL 0x1c4f
#define ENCP_VFIFO2VD_CTL2 0x1c50
#define VENC_DVI_SETTING_MORE 0x1c51
#define VENC_VDAC_DAC4_FILT_CTRL0 0x1c54
#define VENC_VDAC_DAC4_FILT_CTRL1 0x1c55
#define VENC_VDAC_DAC5_FILT_CTRL0 0x1c56
#define VENC_VDAC_DAC5_FILT_CTRL1 0x1c57
#define VENC_VDAC_DAC0_FILT_CTRL0 0x1c58
#define VENC_VDAC_DAC0_FILT_CTRL1 0x1c59
#define VENC_VDAC_DAC1_FILT_CTRL0 0x1c5a
#define VENC_VDAC_DAC1_FILT_CTRL1 0x1c5b
#define VENC_VDAC_DAC2_FILT_CTRL0 0x1c5c
#define VENC_VDAC_DAC2_FILT_CTRL1 0x1c5d
#define VENC_VDAC_DAC3_FILT_CTRL0 0x1c5e
#define VENC_VDAC_DAC3_FILT_CTRL1 0x1c5f

#define ENCT_VIDEO_VAVON_BLINE    0x1c74

#define RDMA_AHB_START_ADDR_MAN 0x1100
#define RDMA_AHB_END_ADDR_MAN 0x1101
#define RDMA_AHB_START_ADDR_1 0x1102
#define RDMA_AHB_END_ADDR_1 0x1103
#define RDMA_AHB_START_ADDR_2 0x1104
#define RDMA_AHB_END_ADDR_2 0x1105
#define RDMA_AHB_START_ADDR_3 0x1106
#define RDMA_AHB_END_ADDR_3 0x1107
#define RDMA_AHB_START_ADDR_4 0x1108
#define RDMA_AHB_END_ADDR_4 0x1109
#define RDMA_AHB_START_ADDR_5 0x110a
#define RDMA_AHB_END_ADDR_5 0x110b
#define RDMA_AHB_START_ADDR_6 0x110c
#define RDMA_AHB_END_ADDR_6 0x110d
#define RDMA_AHB_START_ADDR_7 0x110e
#define RDMA_AHB_END_ADDR_7 0x110f
#define RDMA_ACCESS_AUTO 0x1110
#define RDMA_ACCESS_AUTO2 0x1111
#define RDMA_ACCESS_AUTO3 0x1112
#define RDMA_ACCESS_MAN 0x1113
#define RDMA_CTRL 0x1114
#define RDMA_STATUS 0x1115
#define RDMA_STATUS2 0x1116
#define RDMA_STATUS3 0x1117

#define VPU_OSD1_MMC_CTRL 0x2701
#define VPU_OSD2_MMC_CTRL 0x2702
#define VPU_VD1_MMC_CTRL 0x2703
#define VPU_VD2_MMC_CTRL 0x2704
#define VPU_DI_IF1_MMC_CTRL 0x2705
#define VPU_DI_MEM_MMC_CTRL 0x2706
#define VPU_DI_INP_MMC_CTRL 0x2707
#define VPU_DI_MTNRD_MMC_CTRL 0x2708
#define VPU_DI_CHAN2_MMC_CTRL 0x2709
#define VPU_DI_MTNWR_MMC_CTRL 0x270a
#define VPU_DI_NRWR_MMC_CTRL 0x270b
#define VPU_DI_DIWR_MMC_CTRL 0x270c
#define VPU_VDIN0_MMC_CTRL 0x270d
#define VPU_VDIN1_MMC_CTRL 0x270e
#define VPU_BT656_MMC_CTRL 0x270f
#define VPU_TVD3D_MMC_CTRL 0x2710
#define VPU_TVDVBI_MMC_CTRL 0x2711
#define VPU_TVDVBI_VSLATCH_ADDR 0x2712
#define VPU_TVDVBI_WRRSP_ADDR 0x2713
#define VPU_VDIN_PRE_ARB_CTRL 0x2714
#define VPU_VDISP_PRE_ARB_CTRL 0x2715
#define VPU_VPUARB2_PRE_ARB_CTRL 0x2716
#define VPU_OSD3_MMC_CTRL 0x2717
#define VPU_OSD4_MMC_CTRL 0x2718
#define VPU_VD3_MMC_CTRL 0x2719
#define VPU_VIU_VENC_MUX_CTRL 0x271a
#define VPU_HDMI_SETTING 0x271b
#define ENCI_INFO_READ 0x271c
#define ENCP_INFO_READ 0x271d
#define ENCT_INFO_READ 0x271e
#define ENCL_INFO_READ 0x271f
#define VPU_SW_RESET 0x2720
#define VPU_D2D3_MMC_CTRL 0x2721
#define VPU_CONT_MMC_CTRL 0x2722
#define VPU_CLK_GATE 0x2723
#define VPU_RDMA_MMC_CTRL 0x2724
#define VPU_MEM_PD_REG0 0x2725
#define VPU_MEM_PD_REG1 0x2726
#define VPU_HDMI_DATA_OVR 0x2727
#define VPU_PROT1_MMC_CTRL 0x2728
#define VPU_PROT2_MMC_CTRL 0x2729
#define VPU_PROT3_MMC_CTRL 0x272a
#define VPU_ARB4_V1_MMC_CTRL 0x272b
#define VPU_ARB4_V2_MMC_CTRL 0x272c
#define VPU_VPU_PWM_V0 0x2730
#define VPU_VPU_PWM_V1 0x2731
#define VPU_VPU_PWM_V2 0x2732
#define VPU_VPU_PWM_V3 0x2733
#define VPU_VPU_PWM_H0 0x2734
#define VPU_VPU_PWM_H1 0x2735
#define VPU_VPU_PWM_H2 0x2736
#define VPU_VPU_PWM_H3 0x2737
#define VPU_MISC_CTRL 0x2740
#define VPU_ISP_GCLK_CTRL0 0x2741
#define VPU_ISP_GCLK_CTRL1 0x2742
#define VPU_VDIN_ASYNC_HOLD_CTRL 0x2743
#define VPU_VDISP_ASYNC_HOLD_CTRL 0x2744
#define VPU_VPUARB2_ASYNC_HOLD_CTRL 0x2745

#define VPU_PROT1_CLK_GATE 0x2750
#define VPU_PROT1_GEN_CNTL 0x2751
#define VPU_PROT1_X_START_END 0x2752
#define VPU_PROT1_Y_START_END 0x2753
#define VPU_PROT1_Y_LEN_STEP 0x2754
#define VPU_PROT1_RPT_LOOP 0x2755
#define VPU_PROT1_RPT_PAT 0x2756
#define VPU_PROT1_DDR 0x2757
#define VPU_PROT1_RBUF_ROOM 0x2758
#define VPU_PROT1_STAT_0 0x2759
#define VPU_PROT1_STAT_1 0x275a
#define VPU_PROT1_STAT_2 0x275b
#define VPU_PROT1_REQ_ONOFF 0x275c
#define VPU_PROT2_CLK_GATE 0x2760
#define VPU_PROT2_GEN_CNTL 0x2761
#define VPU_PROT2_X_START_END 0x2762
#define VPU_PROT2_Y_START_END 0x2763
#define VPU_PROT2_Y_LEN_STEP 0x2764
#define VPU_PROT2_RPT_LOOP 0x2765
#define VPU_PROT2_RPT_PAT 0x2766
#define VPU_PROT2_DDR 0x2767
#define VPU_PROT2_RBUF_ROOM 0x2768
#define VPU_PROT2_STAT_0 0x2769
#define VPU_PROT2_STAT_1 0x276a
#define VPU_PROT2_STAT_2 0x276b
#define VPU_PROT2_REQ_ONOFF 0x276c
#define VPU_PROT3_CLK_GATE 0x2770
#define VPU_PROT3_GEN_CNTL 0x2771
#define VPU_PROT3_X_START_END 0x2772
#define VPU_PROT3_Y_START_END 0x2773
#define VPU_PROT3_Y_LEN_STEP 0x2774
#define VPU_PROT3_RPT_LOOP 0x2775
#define VPU_PROT3_RPT_PAT 0x2776
#define VPU_PROT3_DDR 0x2777
#define VPU_PROT3_RBUF_ROOM 0x2778
#define VPU_PROT3_STAT_0 0x2779
#define VPU_PROT3_STAT_1 0x277a
#define VPU_PROT3_STAT_2 0x277b
#define VPU_PROT3_REQ_ONOFF 0x277c

/* osd super scale */
#define OSDSR_HV_SIZEIN 0x3130
#define OSDSR_CTRL_MODE 0x3131
#define OSDSR_ABIC_HCOEF 0x3132
#define OSDSR_YBIC_HCOEF 0x3133
#define OSDSR_CBIC_HCOEF 0x3134
#define OSDSR_ABIC_VCOEF 0x3135
#define OSDSR_YBIC_VCOEF 0x3136
#define OSDSR_CBIC_VCOEF 0x3137
#define OSDSR_VAR_PARA 0x3138
#define OSDSR_CONST_PARA 0x3139
#define OSDSR_RKE_EXTWIN 0x313a
#define OSDSR_UK_GRAD2DDIAG_TH_RATE 0x313b
#define OSDSR_UK_GRAD2DDIAG_LIMIT 0x313c
#define OSDSR_UK_GRAD2DADJA_TH_RATE 0x313d
#define OSDSR_UK_GRAD2DADJA_LIMIT 0x313e
#define OSDSR_UK_BST_GAIN 0x313f

/* canvas.h */
#define DC_CAV_LUT_DATAL        (0x12 << 2)
#define DC_CAV_LUT_DATAH        (0x13 << 2)
#define DC_CAV_LUT_ADDR         (0x14 << 2)
#define DC_CAV_LUT_RDATAL       (0x15 << 2)
#define DC_CAV_LUT_RDATAH       (0x16 << 2)

/* aml_vpp_reg.h */
/* ********************************
 * Video post-processing:  VPP_VCBUS_BASE = 0x1d
 * ******************************** */
/* Bit 31  vd1_bgosd_exchange_en for preblend
// Bit 30  vd1_bgosd_exchange_en for postblend
// bit 28   color management enable
// Bit 27,  reserved
// Bit 26:18, reserved
// Bit 17, osd2 enable for preblend
// Bit 16, osd1 enable for preblend
// Bit 15, reserved
// Bit 14, vd1 enable for preblend
// Bit 13, osd2 enable for postblend
// Bit 12, osd1 enable for postblend
// Bit 11, reserved
// Bit 10, vd1 enable for postblend
// Bit 9,  if true, osd1 is alpha premultiplied
// Bit 8,  if true, osd2 is alpha premultiplied
// Bit 7,  postblend module enable
// Bit 6,  preblend module enable
// Bit 5,  if true, osd2 foreground compared with osd1 in preblend
// Bit 4,  if true, osd2 foreground compared with osd1 in postblend
// Bit 3,
// Bit 2,  if true, disable resetting async fifo every vsync, otherwise every
//           vsync the aync fifo will be reseted.
// Bit 1,
// Bit 0    if true, the output result of VPP is saturated */
#define VPP2_MISC                                  0x1926
/* Bit 31  vd1_bgosd_exchange_en for preblend
// Bit 30  vd1_bgosd_exchange_en for postblend
// Bit 28   color management enable
// Bit 27,  if true, vd2 use viu2 output as the input, otherwise use normal
//            vd2 from memory
// Bit 26:18, vd2 alpha
// Bit 17, osd2 enable for preblend
// Bit 16, osd1 enable for preblend
// Bit 15, vd2 enable for preblend
// Bit 14, vd1 enable for preblend
// Bit 13, osd2 enable for postblend
// Bit 12, osd1 enable for postblend
// Bit 11, vd2 enable for postblend
// Bit 10, vd1 enable for postblend
// Bit 9,  if true, osd1 is alpha premultiplied
// Bit 8,  if true, osd2 is alpha premultiplied
// Bit 7,  postblend module enable
// Bit 6,  preblend module enable
// Bit 5,  if true, osd2 foreground compared with osd1 in preblend
// Bit 4,  if true, osd2 foreground compared with osd1 in postblend
// Bit 3,
// Bit 2,  if true, disable resetting async fifo every vsync, otherwise every
//           vsync the aync fifo will be reseted.
// Bit 1,
// Bit 0    if true, the output result of VPP is saturated */
#define VPP_MISC                                   0x1d26

#define VPP2_POSTBLEND_H_SIZE                      0x1921
#define VPP_POSTBLEND_H_SIZE                       0x1d21
/* Bit 3    minus black level enable for vadj2
 * Bit 2    Video adjustment enable for vadj2
 * Bit 1    minus black level enable for vadj1
 * Bit 0    Video adjustment enable for vadj1 */
#define VPP_VADJ_CTRL                              0x1d40
/* Bit 16:8  brightness, signed value
 * Bit 7:0  contrast, unsigned value, contrast from  0 <= contrast <2 */
#define VPP_VADJ1_Y                                0x1d41
/* cb' = cb*ma + cr*mb
 * cr' = cb*mc + cr*md
 * all are bit 9:0, signed value, -2 < ma/mb/mc/md < 2 */
#define VPP_VADJ1_MA_MB                            0x1d42
#define VPP_VADJ1_MC_MD                            0x1d43
/* Bit 16:8  brightness, signed value
 * Bit 7:0   contrast, unsigned value, contrast from  0 <= contrast <2 */
#define VPP_VADJ2_Y                                0x1d44
/* cb' = cb*ma + cr*mb
 * cr' = cb*mc + cr*md
 * all are bit 9:0, signed value, -2 < ma/mb/mc/md < 2 */
#define VPP_VADJ2_MA_MB                            0x1d45
#define VPP_VADJ2_MC_MD                            0x1d46

#define VPP_MATRIX_CTRL                            0x1d5f
/* Bit 28:16 coef00 */
/* Bit 12:0  coef01 */
#define VPP_MATRIX_COEF00_01                       0x1d60
/* Bit 28:16 coef02 */
/* Bit 12:0  coef10 */
#define VPP_MATRIX_COEF02_10                       0x1d61
/* Bit 28:16 coef11 */
/* Bit 12:0  coef12 */
#define VPP_MATRIX_COEF11_12                       0x1d62
/* Bit 28:16 coef20 */
/* Bit 12:0  coef21 */
#define VPP_MATRIX_COEF20_21                       0x1d63
#define VPP_MATRIX_COEF22                          0x1d64
/* Bit 26:16 offset0 */
/* Bit 10:0  offset1 */
#define VPP_MATRIX_OFFSET0_1                       0x1d65
/* Bit 10:0  offset2 */
#define VPP_MATRIX_OFFSET2                         0x1d66
/* Bit 26:16 pre_offset0 */
/* Bit 10:0  pre_offset1 */
#define VPP_MATRIX_PRE_OFFSET0_1                   0x1d67
/* Bit 10:0  pre_offset2 */
#define VPP_MATRIX_PRE_OFFSET2                     0x1d68
/* dummy data used in the VPP postblend */
/* Bit 23:16    Y */
/* Bit 15:8     CB */
/* Bit 7:0      CR */
#define VPP_DUMMY_DATA1                            0x1d69
/* gxm has no super-core */
#define VPP_DOLBY_CTRL 0x1d93
#define VIU_MISC_CTRL1 0x1a07

#define VIU_OSD1_MATRIX_CTRL 0x1a90
#define VIU_OSD1_MATRIX_COEF00_01 0x1a91
#define VIU_OSD1_MATRIX_COEF02_10 0x1a92
#define VIU_OSD1_MATRIX_COEF11_12 0x1a93
#define VIU_OSD1_MATRIX_COEF20_21 0x1a94
#define VIU_OSD1_MATRIX_COLMOD_COEF42 0x1a95
#define VIU_OSD1_MATRIX_OFFSET0_1 0x1a96
#define VIU_OSD1_MATRIX_OFFSET2 0x1a97
#define VIU_OSD1_MATRIX_PRE_OFFSET0_1 0x1a98
#define VIU_OSD1_MATRIX_PRE_OFFSET2 0x1a99
#define VIU_OSD1_MATRIX_COEF22_30 0x1a9d
#define VIU_OSD1_MATRIX_COEF31_32 0x1a9e
#define VIU_OSD1_MATRIX_COEF40_41 0x1a9f

#define VIU_OSD2_CTRL_STAT2             0x1a4d

#define XVYCC_LUT_R_ADDR_PORT   0x315e
#define XVYCC_LUT_R_DATA_PORT   0x315f
#define XVYCC_LUT_G_ADDR_PORT   0x3160
#define XVYCC_LUT_G_DATA_PORT   0x3161
#define XVYCC_LUT_B_ADDR_PORT   0x3162
#define XVYCC_LUT_B_DATA_PORT   0x3163
#define XVYCC_LUT_CTL           0x3165

#define VIU_EOTF_CTL 0x31d0

#define VIU_EOTF_LUT_ADDR_PORT 0x31d6
#define VIU_EOTF_LUT_DATA_PORT 0x31d7
#define VPP_MATRIX_CLIP 0x1dde
#define VPP_CLIP_MISC1 0x1dda
#define VPP_MATRIX_COEF13_14 0x1ddb
#define VPP_MATRIX_COEF23_24 0x1ddc
#define VPP_MATRIX_COEF15_25 0x1ddd


#define VIU_OSD1_BLK0_CFG_W0 0x1a1b
#define VIU_OSD1_MATRIX_CTRL 0x1a90
#define VIU_OSD1_MATRIX_COEF00_01 0x1a91
#define VIU_OSD1_MATRIX_COEF02_10 0x1a92
#define VIU_OSD1_MATRIX_COEF11_12 0x1a93
#define VIU_OSD1_MATRIX_COEF20_21 0x1a94
#define VIU_OSD1_MATRIX_COLMOD_COEF42 0x1a95
#define VIU_OSD1_MATRIX_OFFSET0_1 0x1a96
#define VIU_OSD1_MATRIX_OFFSET2 0x1a97
#define VIU_OSD1_MATRIX_PRE_OFFSET0_1 0x1a98
#define VIU_OSD1_MATRIX_PRE_OFFSET2 0x1a99
#define VIU_OSD1_MATRIX_COEF22_30 0x1a9d
#define VIU_OSD1_MATRIX_COEF31_32 0x1a9e
#define VIU_OSD1_MATRIX_COEF40_41 0x1a9f
#define VIU_OSD1_EOTF_CTL 0x1ad4
#define VIU_OSD1_EOTF_COEF00_01 0x1ad5
#define VIU_OSD1_EOTF_COEF02_10 0x1ad6
#define VIU_OSD1_EOTF_COEF11_12 0x1ad7
#define VIU_OSD1_EOTF_COEF20_21 0x1ad8
#define VIU_OSD1_EOTF_COEF22_RS 0x1ad9
#define VIU_OSD1_EOTF_LUT_ADDR_PORT 0x1ada
#define VIU_OSD1_EOTF_LUT_DATA_PORT 0x1adb
#define VIU_OSD1_OETF_CTL 0x1adc
#define VIU_OSD1_OETF_LUT_ADDR_PORT 0x1add
#define VIU_OSD1_OETF_LUT_DATA_PORT 0x1ade

#define VIU_OSD2_CTRL_STAT2 0x1a4d

#define VPU_RDARB_MODE_L1C1                        (0x2790)
#define VPU_RDARB_MODE_L1C2                        (0x2799)
#define VPU_RDARB_MODE_L2C1                        (0x279d)
#define VPU_WRARB_MODE_L2C1                        (0x27a2)

//========================================================================
//  VI_HIST_SPL register    (16'h2e00 - 16'h2eff)
//========================================================================
//`define VI_HIST_SPL_VCBUS_BASE                   8'h2e
//
// Reading file:  vi_hist_spl_reg.h
//
// synopsys translate_off
// synopsys translate_on
// ----------------------------
// VI_HIST_SPL 0x2e
// ----------------------------
// -----------------------------------------------
// CBUS_BASE:  VI_HIST_SPL_VCBUS_BASE = 0x2e
// -----------------------------------------------
//BIT 14: 34bin only, 0&255 and other 32bins
//Bit 13:11 hist_din_sel, 00: from vdin0 dout,  1: from vdin1, 2: from nr dout, 3: di output, 4: vpp output, 5: vd1_din, 6: vd2_din, 7:osd1_dout
//Bit 10:8   hist_din_comp_mux, mux of [29:22], [19:12], [9:2] for hist detect
//Bit 7:5   hist_dnlp_low   the real pixels in each bins got by VI_DNLP_HISTXX should multiple with 2^(dnlp_low+3)
//Bit 3:2   hist_din_sel    the source used for hist statistics.  00: from matrix0 dout,  01: from vsc_dout, 10: from matrix1 dout, 11: form matrix1 din
//Bit 1     hist_win_en     1'b0: hist used for full picture; 1'b1: hist used for pixels within hist window
//Bit 0     hist_spl_en     1'b0: disable hist readback; 1'b1: enable hist readback
#define   VI_HIST_CTRL                             (0x2e00)
#define P_VI_HIST_CTRL                             (volatile unsigned int *)((0x2e00  << 2) + 0xff900000)
//Bit 28:16 hist_hstart  horizontal start value to define hist window
//Bit 12:0  hist_hend    horizontal end value to define hist window
#define   VI_HIST_H_START_END                      (0x2e01)
#define P_VI_HIST_H_START_END                      (volatile unsigned int *)((0x2e01  << 2) + 0xff900000)
//Bit 28:16 hist_vstart  vertical start value to define hist window
//Bit 12:0  hist_vend    vertical end value to define hist window
#define   VI_HIST_V_START_END                      (0x2e02)
#define P_VI_HIST_V_START_END                      (volatile unsigned int *)((0x2e02  << 2) + 0xff900000)
//Bit 15:8  hist_max    maximum value
//Bit 7:0   hist_min    minimum value
//read only
#define   VI_HIST_MAX_MIN                          (0x2e03)
#define P_VI_HIST_MAX_MIN                          (volatile unsigned int *)((0x2e03  << 2) + 0xff900000)
//Bit 31:0  hist_spl_rd
//counts for the total luma value
//read only
#define   VI_HIST_SPL_VAL                          (0x2e04)
#define P_VI_HIST_SPL_VAL                          (volatile unsigned int *)((0x2e04  << 2) + 0xff900000)
//Bit 21:0  hist_spl_pixel_count
//counts for the total calculated pixels
//read only
#define   VI_HIST_SPL_PIX_CNT                      (0x2e05)
#define P_VI_HIST_SPL_PIX_CNT                      (volatile unsigned int *)((0x2e05  << 2) + 0xff900000)
//Bit 31:0  hist_chroma_sum
//counts for the total chroma value
//read only
#define   VI_HIST_CHROMA_SUM                       (0x2e06)
#define P_VI_HIST_CHROMA_SUM                       (volatile unsigned int *)((0x2e06  << 2) + 0xff900000)
