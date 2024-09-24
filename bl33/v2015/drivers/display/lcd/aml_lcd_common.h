/*
 * driver/display/lcd/aml_lcd_common.h
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the named License,
 * or any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 */

#ifndef _AML_LCD_COMMON_H
#define _AML_LCD_COMMON_H
#include <div64.h>
#include <amlogic/aml_lcd.h>
#include "aml_lcd_clk_config.h"
#include "aml_lcd_unifykey.h"

/* 20180718: mute: wait vsync for display shadow */
/* 20180928: tl1 support, optimize clk config */
/* 20181012: tl1 support tcon */
/* 20181212: tl1 update p2p config and pll setting */
/* 20181225: update phy config */
/* 20190108: tl1 support tablet mode */
/* 20190115: tl1 tcon all interface support */
/* 20190118: support tcon bin data management */
/* 20190225: fix tcon axi_mem detect mistake for kernel 64bit */
/* 20190308: add more panel clk_ss_level step for tl1*/
/* 20190911: add lcd_tcon_load_data for tl1*/
/* 20191025: tcon chpi phy setting update*/
/* 20191115: add lcd_tcon_load_data chk_data for tl1*/
/* 20191227: vbyone hw filter disable support*/
/* 20200610: correct P2P CHPI tx low common setting*/
/* 20200710: tconless new data format*/
/* 20200827: add lcd driver support for T5 chip*/
/* 20200927: add tcon support for T5 chip*/
/* 20201019: optimize tcon axi reserved memory config and data crc32*/
/* 20201027: add tcon support for txhd*/
/* 20201105: optimize big size tcon bin parse in tvconfig*/
/* 20201116: optimize phy ctrl compatibility*/
/* 20210311: add global reset to clear tcon last state*/
/* 20210608: add tcon multi lut support*/
/* 20211009: support 59 & 47 frame rate for tv mode*/
/* 20211009: add t5w support*/
/* 20211210: support load tcon bin by ioctl*/
/* 20211229: update multi lut init and switch flow*/
/* 20220421: fix lcd clk mistake for vmode change with fr_adj_type 4*/
/* 20220629: add ini ver2 support and support phy lane contrl*/
/* 20220719: support t5,t5w,t3 set vswing level in low common type*/
/* 20220809: fix tcon axi mem mistake for DLG tcon bin*/
/* 20221101: update pinmux contrl*/
/* 20221215: remove unnecessary tcon top reset*/
/* 20230104: update lcd_ctrl and lcd_debug bootargs parameters*/
/* 20230222: update tcon tee memory debug info*/
/* 20230303: fix hdmi mode 47hz & 95hz timing*/
/* 20230313: update tcon debug info print*/
/* 20230802: add t5m,t5w,t3x set phy lane amp*/
/* 20230816: optimize clk accuracy*/
/* 20230821: update lcd ss support*/
/* 20230912: bypass phy data buffer */
/* 20231205: add lcd config check*/
/* 20231218: update timing management*/
/* 20240129: update display mode management*/
/* 20240218: optimize lcd config check sequence*/
/* 20240222: update custom control support*/
/* 20240307: update swpdf support*/
#define LCD_DRV_VERSION    "20240307"

#define LCD_STATUS_IF_ON      (1 << 0)
#define LCD_STATUS_ENCL_ON    (1 << 1)
#define VPP_OUT_SATURATE            (1 << 0)

extern void mdelay(unsigned long n);
extern unsigned int lcd_debug_test;

static inline unsigned long long lcd_do_div(unsigned long long num, unsigned int den)
{
	unsigned long long ret = num;

	do_div(ret, den);

	return ret;
}

/* lcd common */
extern int lcd_type_str_to_type(const char *str);
extern char *lcd_type_type_to_str(int type);
extern int lcd_mode_str_to_mode(const char *str);
extern char *lcd_mode_mode_to_str(int mode);

int lcd_config_timing_check(struct lcd_detail_timing_s *ptiming);
extern int lcd_power_load_from_dts(struct lcd_config_s *pconf,
		char *dt_addr, int child_offset);
extern int lcd_power_load_from_unifykey(struct lcd_config_s *pconf,
		unsigned char *buf, int key_len, int len);
extern int lcd_pinmux_load_config(char *dt_addr, struct lcd_config_s *pconf);
void lcd_clk_frame_rate_init(struct lcd_detail_timing_s *ptiming);
void lcd_default_to_basic_timing_init_config(struct lcd_config_s *pconf);
void lcd_enc_timing_init_config(struct lcd_config_s *pconf);
int lcd_frame_rate_change(struct lcd_config_s *pconf);

/* lcd cus_ctrl */
void lcd_cus_ctrl_dump_raw_data(struct lcd_config_s *pconf);
void lcd_cus_ctrl_dump_info(struct lcd_config_s *pconf);
int lcd_cus_ctrl_load_from_dts(struct lcd_config_s *pconf, char *dt_addr);
int lcd_cus_ctrl_load_from_unifykey(struct lcd_config_s *pconf, unsigned char *buf,
		unsigned int max_size);
void lcd_cus_ctrl_config_remove(struct lcd_config_s *pconf);
int lcd_cus_ctrl_config_update(struct lcd_config_s *pconf, void *param, unsigned int mask_sel);
void lcd_cus_ctrl_state_clear(struct lcd_config_s *pconf, unsigned int mask_sel);
int lcd_cus_ctrl_timing_is_valid(struct lcd_config_s *pconf);
int lcd_cus_ctrl_timing_is_activated(struct lcd_config_s *pconf);
struct lcd_detail_timing_s **lcd_cus_ctrl_timing_match_get(struct lcd_config_s *pconf);

/* lcd phy */
unsigned int lcd_phy_vswing_level_to_value(struct aml_lcd_drv_s *pdrv, unsigned int level);
unsigned int lcd_phy_preem_level_to_value(struct aml_lcd_drv_s *pdrv, unsigned int level);
extern void lcd_lvds_phy_set(struct lcd_config_s *pconf, int status);
extern void lcd_vbyone_phy_set(struct lcd_config_s *pconf, int status);
extern void lcd_mlvds_phy_set(struct lcd_config_s *pconf, int status);
extern void lcd_p2p_phy_set(struct lcd_config_s *pconf, int status);
extern void lcd_mipi_phy_set(struct lcd_config_s *pconf, int status);
extern int lcd_phy_probe(void);
extern void lcd_phy_tcon_chpi_bbc_init_tl1(struct lcd_config_s *pconf);

/* lcd tcon */
#ifdef CONFIG_AML_LCD_TCON
extern void lcd_tcon_info_print(void);
int lcd_tcon_top_init(struct lcd_config_s *pconf);
extern int lcd_tcon_enable(struct lcd_config_s *pconf);
extern void lcd_tcon_disable(struct lcd_config_s *pconf);
extern int lcd_tcon_probe(char *dt_addr, struct aml_lcd_drv_s *lcd_drv, int load_id);
void lcd_tcon_dbg_check(struct lcd_detail_timing_s *ptiming);
#endif

/* lcd pinctrl */
int lcd_pinmux_probe(unsigned int cpu_type);
void lcd_pinmux_set_mask(unsigned int n, unsigned int _mask);
void lcd_pinmux_clr_mask(unsigned int n, unsigned int _mask);
void lcd_pinmux_set(int status);
extern int aml_lcd_gpio_name_map_num(const char *name);
extern int aml_lcd_gpio_set(int gpio, int value);
extern unsigned int aml_lcd_gpio_input_get(int gpio);

/* lcd debug */
int lcd_debug_info_len(int num);
extern void aml_lcd_debug_test(unsigned int num);
extern void aml_lcd_mute_setting(unsigned char flag);
extern void aml_lcd_info_print(void);
extern void aml_lcd_reg_print(void);
void aml_lcd_vbyone_rst(void);
int aml_lcd_vbyone_cdr(void);
int aml_lcd_vbyone_lock(void);
extern void aml_lcd_debug_probe(struct aml_lcd_drv_s *lcd_drv);
int aml_lcd_prbs_test(unsigned int s, unsigned int mode_flag);

/* lcd driver */
extern int get_lcd_tv_config(char *dt_addr, int load_id);
extern int get_lcd_tablet_config(char *dt_addr, int load_id);

extern void lcd_wait_vsync(void);

/* aml_bl driver */
extern void aml_bl_config_print(void);
extern void aml_bl_pwm_config_update(struct bl_config_s *bconf);
extern void aml_bl_set_level(unsigned int level);
extern unsigned int aml_bl_get_level(void);
extern void aml_bl_power_ctrl(int status, int delay_flag);
extern int aml_bl_config_load(char *dt_addr, int load_id);
#ifdef CONFIG_AML_LOCAL_DIMMING
extern int ldim_config_load_from_dts(char *dt_addr, int child_offset);
extern int ldim_config_load_from_unifykey(unsigned char *para);
extern int ldim_config_load(char *dt_addr);
#endif

void bl_pwm_ctrl(struct bl_pwm_config_s *bl_pwm, int status);
#ifdef CONFIG_OF_LIBFDT
enum bl_pwm_port_e bl_pwm_str_to_num(const char *str);
#endif
#endif

