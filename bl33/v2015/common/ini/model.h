/* SPDX-License-Identifier: (GPL-2.0+ OR MIT) */
/*
 * common/ini/model.h
 *
 * Copyright (C) 2020 Amlogic, Inc. All rights reserved.
 *
 */

#ifndef __PAEL_INI_H__
#define __PAEL_INI_H__
#include "ini_size_define.h"

#ifdef __cplusplus
extern "C" {
#endif

extern int handle_model_list(void);
extern int handle_model_sum(void);

#ifdef __cplusplus
}
#endif

#pragma pack (1)

#define DEBUG_NORMAL        (1 << 0)
#define DEBUG_LCD           (1 << 1)
#define DEBUG_LCD_EXTERN    (1 << 2)
#define DEBUG_BACKLIGHT     (1 << 3)
#define DEBUG_MISC          (1 << 4)
#define DEBUG_TCON          (1 << 5)
#define DEBUG_LCD_CUS_CTRL  (1 << 6)
#define DEBUG_LCD_OPTICAL   (1 << 7)

enum lcd_type_e {
	LCD_RGB = 0,
	LCD_LVDS,
	LCD_VBYONE,
	LCD_MIPI,
	LCD_MLVDS,
	LCD_P2P,
	LCD_EDP,
	LCD_BT656,
	LCD_BT1120,
	LCD_TYPE_MAX,
};

enum bl_ctrl_method_e {
	BL_CTRL_GPIO = 0,
	BL_CTRL_PWM,
	BL_CTRL_PWM_COMBO,
	BL_CTRL_LOCAL_DIMMING,
	BL_CTRL_EXTERN,
	BL_CTRL_MAX,
};

enum bl_pwm_method_e {
	BL_PWM_NEGATIVE = 0,
	BL_PWM_POSITIVE,
	BL_PWM_METHOD_MAX,
};

enum bl_pwm_port_e {
	BL_PWM_A = 0,
	BL_PWM_B,
	BL_PWM_C,
	BL_PWM_D,
	BL_PWM_E,
	BL_PWM_F,
	BL_PWM_G,
	BL_PWM_H,
	BL_PWM_I,
	BL_PWM_J,
	BL_PWM_AO_A = 0x50,
	BL_PWM_AO_B,
	BL_PWM_AO_C,
	BL_PWM_AO_D,
	BL_PWM_AO_E,
	BL_PWM_AO_F,
	BL_PWM_AO_G,
	BL_PWM_AO_H,
	BL_PWM_VS = 0xa0,
	BL_PWM_MAX = 0xff,
};

enum lcd_ldim_mode_e {
	LDIM_MODE_LR_SIDE = 0,
	LDIM_MODE_TB_SIDE,
	LDIM_MODE_DIRECT,
	LDIM_MODE_MAX,
};

enum lcd_extern_type_e {
	LCD_EXTERN_I2C = 0,
	LCD_EXTERN_SPI,
	LCD_EXTERN_MIPI,
	LCD_EXTERN_MAX,
};
#define LCD_EXTERN_I2C_BUS_INVALID 0xff

#define CC_LCD_NAME_LEN_MAX        (30)

struct lcd_header_s {
	unsigned int crc32;
	unsigned short data_len;
	unsigned char version;
	unsigned char block_next_flag;
	unsigned short block_cur_size;
};

struct lcd_basic_s {
	char model_name[CC_LCD_NAME_LEN_MAX];
	unsigned char lcd_if_chk; /*[5:0]interface, [7:6]:config_check*/
	unsigned char lcd_bits_cfmt; /*bit[5:0]lcd_bits, bit[7:6]input_cfmt*/
	unsigned short screen_width;  /* screen physical width in "mm" unit */
	unsigned short screen_height; /* screen physical height in "mm" unit */
};

struct lcd_timming_s {
	unsigned short h_active; /* Horizontal display area */
	unsigned short v_active; /* Vertical display area */
	unsigned short h_period; /* Horizontal total period time */
	unsigned short v_period; /* Vertical total period time */
	unsigned short hsync_width_pol;/*bit[11:0]hs_width, bit[15:12]hs_pol */
	unsigned short hsync_bp;
	unsigned char pre_de_h;
	unsigned short vsync_width_pol;/*bit[11:0]vs_width, bit[15:12]vs_pol */
	unsigned short vsync_bp;
	unsigned char pre_de_v;
};

struct lcd_customer_s {
	unsigned char fr_adjust_type;
	unsigned char ss_level;
	unsigned char clk_auto_gen;
	unsigned int pixel_clk;
	unsigned short h_period_min;
	unsigned short h_period_max;
	unsigned short v_period_min;
	unsigned short v_period_max;
	unsigned int pixel_clk_min;
	unsigned int pixel_clk_max;
	unsigned char vlock_val_0;
	unsigned char vlock_val_1;
	unsigned char vlock_val_2;
	unsigned char vlock_val_3;
	unsigned char custom_pinmux;
	unsigned char fr_auto_cus;
	unsigned char frame_rate_min;
	unsigned char frame_rate_max;
};

struct lcd_interface_s {
	unsigned short if_attr_0; //vbyone_attr lane_count
	unsigned short if_attr_1; //vbyone_attr region_num
	unsigned short if_attr_2; //vbyone_attr byte_mode
	unsigned short if_attr_3; //vbyone_attr color_fmt
	unsigned short if_attr_4; //phy_attr vswing_level
	unsigned short if_attr_5; //phy_attr preemphasis_level
	unsigned short if_attr_6; //reversed
	unsigned short if_attr_7; //reversed
	unsigned short if_attr_8; //reversed
	unsigned short if_attr_9; //reversed
};

#define CC_LCD_PWR_ITEM_CNT    (4)
struct lcd_pwr_s {
	unsigned char pwr_step_type;
	unsigned char pwr_step_index;
	unsigned char pwr_step_val;
	unsigned short pwr_step_delay;
};

#define CC_MAX_PWR_SEQ_CNT     (50)

struct lcd_attr_s {
	struct lcd_header_s head;
	struct lcd_basic_s basic;
	struct lcd_timming_s timming;
	struct lcd_customer_s customer;
	struct lcd_interface_s interface;
	struct lcd_pwr_s pwr[CC_MAX_PWR_SEQ_CNT];
};

struct lcd_phy_s {
	unsigned int   phy_attr_flag; //each bit enable one attr behind
	unsigned short phy_attr_0; //2byte //vswing
	unsigned short phy_attr_1; //2byte //vcm
	unsigned short phy_attr_2; //2byte //ref bias switch
	unsigned short phy_attr_3; //2byte //odt
	unsigned short phy_attr_4; //2byte //current/voltage mode
	unsigned short phy_attr_5; //2byte //reserved
	unsigned short phy_attr_6; //2byte //reserved
	unsigned short phy_attr_7; //2byte //reserved
	unsigned short phy_attr_8; //2byte //reserved
	unsigned short phy_attr_9; //2byte //reserved
	unsigned short phy_attr_10; //2byte //reserved
	unsigned short phy_attr_11; //2byte //reserved
	unsigned int   phy_lane_ctrl[64]; //64 *2byte lane_reg //
	unsigned char  phy_lane_pn_swap[8]; //64bit //pn_swap
	unsigned char  phy_lane_swap[64]; //64byte //channel_swap
};

#define LCD_CUS_CTRL_ATTR_CNT_MAX        32

#define LCD_CUS_CTRL_TYPE_UFR            0x00
#define LCD_CUS_CTRL_TYPE_DFR            0x01
#define LCD_CUS_CTRL_TYPE_EXTEND_TMG     0x02
#define LCD_CUS_CTRL_TYPE_CLK_ADV        0x03
#define LCD_CUS_CTRL_TYPE_TCON_SW_POL    0x10
#define LCD_CUS_CTRL_TYPE_TCON_SW_PDF    0x11
#define LCD_CUS_CTRL_TYPE_MAX            0xff

struct lcd_dfr_timing_s {
	unsigned short htotal;
	unsigned short vtotal;
	unsigned short vtotal_min;
	unsigned short vtotal_max;
	unsigned short frame_rate_min;
	unsigned short frame_rate_max;
	unsigned short hpw;
	unsigned short hbp;
	unsigned short vpw;
	unsigned short vbp;
};

struct lcd_cus_ctrl_extend_tmg_s {
	unsigned short hactive;
	unsigned short vactive;
	unsigned short htotal;
	unsigned short vtotal;

	unsigned short hpw_pol;//[15:12]hs_pol, [11:0]hpw
	unsigned short hbp;
	unsigned short vpw_pol;//[15:12]vs_pol, [11:0]vpw
	unsigned short vbp;
	unsigned char fr_adjust_type;
	unsigned int pixel_clk;

	unsigned short htotal_min;
	unsigned short htotal_max;
	unsigned short vtotal_min;
	unsigned short vtotal_max;
	unsigned short frame_rate_min;
	unsigned short frame_rate_max;
	unsigned int pclk_min;
	unsigned int pclk_max;
};

#define SWPDF_MAX_BLOCK 16
#define SWPDF_MAX_ACT 16
struct lcd_cus_swpdf_block_s {
	unsigned short x;
	unsigned short y;
	unsigned char w;
	unsigned char h;
	unsigned int mat_val0;
	unsigned int mat_val1;
	unsigned int mat_val2;
	unsigned int mat_val3;
};

struct lcd_cus_swpdf_act_s {
	unsigned int reg;
	unsigned int mask;
	unsigned int val;
	unsigned char bus;
};

#define LCD_CUS_CTRL_MAX        18244
#define LCD_CUS_CTRL_DATA_MAX   18240
struct lcd_cus_ctrl_s {
	unsigned int  ctrl_attr_en;    //4byte   //each bit enable one attr behind
	unsigned char data[LCD_CUS_CTRL_DATA_MAX];
};

struct lcd_v2_attr_s {
	struct lcd_header_s head;
	struct lcd_phy_s phy;
	struct lcd_cus_ctrl_s cus_ctrl;
};

#define CC_BL_NAME_LEN_MAX        (30)

struct bl_header_s {
	unsigned int crc32;
	unsigned short data_len;
	unsigned short version;
	unsigned short rev;
};

struct bl_basic_s {
	char bl_name[CC_BL_NAME_LEN_MAX];
};

struct bl_level_s {
	unsigned short bl_level_uboot;
	unsigned short bl_level_kernel;
	unsigned short bl_level_max;
	unsigned short bl_level_min;
	unsigned short bl_level_mid;
	unsigned short bl_level_mid_mapping;
};

struct bl_method_s {
	unsigned char bl_method;
	unsigned char bl_en_gpio;
	unsigned char bl_en_gpio_on;
	unsigned char bl_en_gpio_off;
	unsigned short bl_on_delay;
	unsigned short bl_off_delay;
};

struct bl_pwm_s {
	unsigned short pwm_on_delay;
	unsigned short pwm_off_delay;

	unsigned char pwm_method;
	unsigned char pwm_port;
	unsigned int pwm_freq;
	unsigned char pwm_duty_max;
	unsigned char pwm_duty_min;
	unsigned char pwm_gpio;
	unsigned char pwm_gpio_off;

	unsigned char pwm2_method;
	unsigned char pwm2_port;
	unsigned int pwm2_freq;
	unsigned char pwm2_duty_max;
	unsigned char pwm2_duty_min;
	unsigned char pwm2_gpio;
	unsigned char pwm2_gpio_off;

	unsigned short pwm_level_max;
	unsigned short pwm_level_min;
	unsigned short pwm2_level_max;
	unsigned short pwm2_level_min;
};

struct bl_ldim_s {
	unsigned char ldim_row;
	unsigned char ldim_col;
	unsigned char ldim_mode;
	unsigned char ldim_dev_index;

	unsigned short ldim_attr_4;
	unsigned short ldim_attr_5;
	unsigned short ldim_attr_6;
	unsigned short ldim_attr_7;
	unsigned short ldim_attr_8;
	unsigned short ldim_attr_9;
};

struct bl_custome_s {
	unsigned short custome_val_0;
	unsigned short custome_val_1;
	unsigned short custome_val_2;
	unsigned short custome_val_3;
	unsigned short custome_val_4;
};

struct bl_attr_s {
	struct bl_header_s head;
	struct bl_basic_s basic;
	struct bl_level_s level;
	struct bl_method_s method;
	struct bl_pwm_s pwm;
	struct bl_ldim_s ldim;         //v2
	struct bl_custome_s custome;   //v2
};

#define CC_LCD_EXT_NAME_LEN_MAX        (30)

struct lcd_ext_header_s {
	unsigned int crc32;
	unsigned short data_len;
	unsigned short version;
	unsigned short rev;
};

#define LCD_EXTERN_CMD_SIZE_DYNAMIC    0xff
#define LCD_EXTERN_INIT_ON_MAX         3000
#define LCD_EXTERN_INIT_OFF_MAX        100

struct lcd_ext_basic_s {
	char ext_name[CC_LCD_EXT_NAME_LEN_MAX];
	unsigned char ext_index;  // set it as 0
	unsigned char ext_type;   // LCD_EXTERN_I2C, LCD_EXTERN_SPI, LCD_EXTERN_MIPI
	unsigned char ext_status; // 1 is okay, 0 is disable
};

struct lcd_ext_type_s {
	unsigned char value_0;     //i2c_addr           //spi_gpio_cs
	unsigned char value_1;     //i2c_second_addr    //spi_gpio_clk
	unsigned char value_2;     //i2c_bus            //spi_gpio_data
	unsigned char value_3;     //cmd_size           //spi_clk_freq[bit 7:0]  //unit: hz
	unsigned char value_4;                          //spi_clk_freq[bit 15:8]
	unsigned char value_5;                          //spi_clk_freq[bit 23:16]
	unsigned char value_6;                          //spi_clk_freq[bit 31:24]
	unsigned char value_7;                          //spi_clk_pol
	unsigned char value_8;                          //cmd_size
	unsigned char value_9;     //reserved for future usage
};

#define CC_EXT_CMD_MAX_CNT           (300)

#define LCD_EXTERN_INIT_CMD           0x00
#define LCD_EXTERN_INIT_CMD2          0x01  //only for special i2c device
#define LCD_EXTERN_INIT_NONE          0x10
#define LCD_EXTERN_INIT_GPIO          0xf0
#define LCD_EXTERN_INIT_END           0xff

struct lcd_ext_attr_s {
	struct lcd_ext_header_s head;
	struct lcd_ext_basic_s basic;
	struct lcd_ext_type_s type;
	unsigned char cmd_data[LCD_EXTERN_INIT_ON_MAX+LCD_EXTERN_INIT_OFF_MAX];
};

struct panel_misc_s {
	char version[8];
	char outputmode[64];
	char connector_type[64];
	unsigned char panel_reverse;
};

struct lcd_tcon_spi_block_s {
	unsigned short data_type;
	unsigned short data_index;
	unsigned int data_flag;
	unsigned int spi_offset;
	unsigned int spi_size;
	unsigned int param_cnt;
};

struct lcd_optical_attr_s {
	struct lcd_header_s head;
	unsigned int hdr_support;
	unsigned int features;
	unsigned int primaries_r_x;
	unsigned int primaries_r_y;
	unsigned int primaries_g_x;
	unsigned int primaries_g_y;
	unsigned int primaries_b_x;
	unsigned int primaries_b_y;
	unsigned int white_point_x;
	unsigned int white_point_y;
	unsigned int luma_max;
	unsigned int luma_min;
	unsigned int luma_avg;
	unsigned int adv_val[10];
};

#define CC_MAX_SUPPORT_PANEL_CNT          (128)

#define CC_MAX_PANEL_ALL_INFO_TAG_SIZE    (16)
#define CS_PANEL_ALL_INFO_TAG_CONTENT     "panel_all_info"

struct all_info_header_s {
	unsigned int crc32;
	unsigned short data_len;
	unsigned short version;
	unsigned char tag[CC_MAX_PANEL_ALL_INFO_TAG_SIZE];
	unsigned int max_panel_cnt;
	unsigned int cur_panel_cnt;
	unsigned int sec_off;
	unsigned int sec_cnt;
	unsigned int sec_size;
	unsigned int sec_len;
	unsigned int item_head_off;
	unsigned int item_head_cnt;
	unsigned int item_head_size;
	unsigned int item_head_len;
	unsigned int def_flag;
	unsigned char rev[12];
};

#define CC_MAX_PANEL_ALL_ONE_SEC_TAG_SIZE        (16)
#define CC_MAX_PANEL_ALL_ONE_SEC_TAG_CONTENT     "panel_all_data0"

extern int model_debug_flag;

int transBufferData(const char *data_str, unsigned int data_buf[]);

#ifdef CONFIG_AML_LCD
extern int glcd_cus_ctrl_cnt;

int handle_lcd_cus_ctrl(struct lcd_v2_attr_s *p_attr);
#endif

unsigned char model_data_checksum(unsigned char *buf, unsigned int len);
unsigned char model_data_lrc(unsigned char *buf, unsigned int len);

#endif //__PAEL_INI_H__
