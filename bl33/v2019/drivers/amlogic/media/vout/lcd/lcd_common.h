/* SPDX-License-Identifier: (GPL-2.0+ OR MIT) */
/*
 * Copyright (c) 2019 Amlogic, Inc. All rights reserved.
 */

#ifndef _AML_LCD_COMMON_H
#define _AML_LCD_COMMON_H
#include <div64.h>
#include <amlogic/media/vout/lcd/aml_lcd.h>
#include "./lcd_clk/lcd_clk_config.h"
#include "lcd_unifykey.h"

/* 20181106: init version */
/* 20201211: support t5/t5d/t7 */
/* 20210222: support multi driver index */
/* 20210409: update lvds & vbyone regs for t7*/
/* 20210412: add t3 support*/
/* 20210514: add extern driver support*/
/* 20210518: update t7 & t3 lvds lane setting*/
/* 20210616: fix t3 clk ss mistake*/
/* 20210625: add tcon multi lut support*/
/* 20211009: support 59 & 47 frame rate for tv mode*/
/* 20211106: support vrr config*/
/* 20211210: support load tcon bin by ioctl*/
/* 20211216: support phy adjust by lane*/
/* 20211229: update multi lut init and switch flow*/
/* 20211230: support lcd driver DLG switch flow*/
/* 20220121: update custom_pinmux and fr_auto_dis support*/
/* 20220216: update vrr config when display mode change*/
/* 20220421: fix lcd clk mistake for vmode change with fr_adj_type 4*/
/* 20220701: add c3 support*/
/* 20220718: support t5,t5w,t3 set vswing in low common type*/
/* 20220809: fix tcon axi mem mistake for DLG tcon bin*/
/* 20221111: modify edp transmit_unit_size to 48(temporary)*/
/* 20221115: support force unfit mipi-dsi bit_rate_max*/
/* 20221116: add T5W support*/
/* 20221215: remove unnecessary tcon top reset*/
/* 20221216: optimize lcd clk code*/
/* 20230222: update tcon tee memory debug info*/
/* 20230303: fix hdmi mode 47hz & 95hz timing*/
/* 20230313: update tcon debug info print*/
/* 20230319: optimize phy code*/
/* 20230505: t3x support */
/* 20230615: txhd2 support */
/* 20230705: t3x fix tconless phy setting */
/* 20230802: add t5m,t5w,t3x set phy lane amp*/
/* 20230815: add full-link-training and EDID-timing for eDP */
/* 20230816: optimize clk accuracy*/
/* 20230821: update lcd ss support*/
/* 20230823: add dma driver for tcon lut*/
/* 20230906: support pdf action */
/* 20230907: t3x revB OD secure memory support */
/* 20230912: bypass phy data buffer */
/* 20230915: update phy setting for txhd2 */
/* 20230918: support ultra refresh rate function*/
/* 20231011: t3x dual display support */
/* 20231012: optimize clk management*/
/* 20231205: add lcd config check*/
/* 20231218: update timing management*/
/* 20240118: MIPI DSI arch adjust*/
/* 20240129: update display mode management*/
/* 20240218: optimize lcd config check sequence*/
/* 20240222: update custom control support*/
/* 20240226: add tcon init_table pre_proc*/
/* 20240307: update swpdf support*/
/* 20240318: optimize tcon reserved memory */
/* 20240319: add tcon pre_proc_clk_en control*/
#define LCD_DRV_VERSION    "20240319"

extern unsigned long clk_util_clk_msr(unsigned long clk_mux);

void mdelay(unsigned long n);

static inline unsigned long long lcd_do_div(unsigned long long num, unsigned int den)
{
	unsigned long long ret = num;

	do_div(ret, den);

	return ret;
}

static inline unsigned long long lcd_diff(unsigned long long a, unsigned long long b)
{
	return (a >= b) ? (a - b) : (b - a);
}

static inline unsigned long long div_around(unsigned long long num, unsigned int den)
{
	unsigned long long ret = num + den / 2;

	if (den == 1)
		return num;

	do_div(ret, den);

	return ret;
}

void lcd_display_init_test(struct aml_lcd_drv_s *pdrv);
void lcd_display_init_reg_dump(struct aml_lcd_drv_s *pdrv);

#define LCD_CMA_PAGE_SIZE_1K (1 * 1024)
#define LCD_CMA_PAGE_SIZE_2K (2 * 1024)
#define LCD_CMA_PAGE_SIZE_4K (4 * 1024)
#define LCD_CMA_PAGE_SIZE_8K (8 * 1024)

/* lcd common */
void lcd_cma_pool_init(struct aml_lcd_cma_mem *cma,
		phys_addr_t pa, unsigned long size, unsigned int page_size);
int lcd_cma_delect_dts(char *dt_addr, struct aml_lcd_drv_s *pdrv);
void *lcd_cma_pool_simple_alloc(struct aml_lcd_cma_mem *cma, unsigned long size);
void *lcd_alloc_dma_buffer(struct aml_lcd_drv_s *pdrv, unsigned long size);

int lcd_type_str_to_type(const char *str);
char *lcd_type_type_to_str(int type);
int lcd_mode_str_to_mode(const char *str);
char *lcd_mode_mode_to_str(int mode);

void lcd_encl_on(struct aml_lcd_drv_s *pdrv);
int lcd_config_timing_check(struct aml_lcd_drv_s *pdrv, struct lcd_detail_timing_s *ptiming);
int lcd_base_config_load_from_dts(char *dt_addr, struct aml_lcd_drv_s *pdrv);
int lcd_base_config_load_from_bsp(struct aml_lcd_drv_s *pdrv);
void lcd_panel_config_load_to_drv(struct aml_lcd_drv_s *pdrv);
int lcd_get_panel_config(char *dt_addr, int load_id, struct aml_lcd_drv_s *pdrv);
void lcd_clk_frame_rate_init(struct lcd_detail_timing_s *ptiming);
void lcd_default_to_basic_timing_init_config(struct aml_lcd_drv_s *pdrv);
void lcd_enc_timing_init_config(struct aml_lcd_drv_s *pdrv);

int lcd_fr_is_frac(struct aml_lcd_drv_s *pdrv, unsigned int frame_rate);
int lcd_vmode_frac_is_support(struct aml_lcd_drv_s *pdrv, unsigned int frame_rate);
int lcd_frame_rate_change(struct aml_lcd_drv_s *pdrv);
void lcd_pinmux_set(struct aml_lcd_drv_s *pdrv, int status);
void lcd_vbyone_bit_rate_config(struct aml_lcd_drv_s *pdrv);
void lcd_mlvds_bit_rate_config(struct aml_lcd_drv_s *pdrv);
void lcd_p2p_bit_rate_config(struct aml_lcd_drv_s *pdrv);
void lcd_mipi_dsi_bit_rate_config(struct aml_lcd_drv_s *pdrv);
void lcd_edp_bit_rate_config(struct aml_lcd_drv_s *pdrv);

/* lcd cus_ctrl */
void lcd_cus_ctrl_dump_raw_data(struct aml_lcd_drv_s *pdrv);
void lcd_cus_ctrl_dump_info(struct aml_lcd_drv_s *pdrv);
int lcd_cus_ctrl_load_from_dts(struct aml_lcd_drv_s *pdrv, struct device_node *child);
int lcd_cus_ctrl_load_from_unifykey(struct aml_lcd_drv_s *pdrv, unsigned char *buf,
		unsigned int max_size);
void lcd_cus_ctrl_config_remove(struct aml_lcd_drv_s *pdrv);
int lcd_cus_ctrl_config_update(struct aml_lcd_drv_s *pdrv, void *param, unsigned int mask_sel);
void lcd_cus_ctrl_state_clear(struct aml_lcd_drv_s *pdrv, unsigned int mask_sel);
int lcd_cus_ctrl_timing_is_valid(struct aml_lcd_drv_s *pdrv);
int lcd_cus_ctrl_timing_is_activated(struct aml_lcd_drv_s *pdrv);
struct lcd_detail_timing_s **lcd_cus_ctrl_timing_match_get(struct aml_lcd_drv_s *pdrv);

/* lcd venc */
void lcd_wait_vsync(struct aml_lcd_drv_s *pdrv);
unsigned int lcd_get_encl_line_cnt(struct aml_lcd_drv_s *pdrv);
unsigned int lcd_get_max_line_cnt(struct aml_lcd_drv_s *pdrv);
void lcd_debug_test(struct aml_lcd_drv_s *pdrv, unsigned int num);
void lcd_set_venc_timing(struct aml_lcd_drv_s *pdrv);
void lcd_set_venc(struct aml_lcd_drv_s *pdrv);
void lcd_venc_enable(struct aml_lcd_drv_s *pdrv, int flag);
void lcd_mute_set(struct aml_lcd_drv_s *pdrv,  unsigned char flag);
int lcd_venc_probe(struct aml_lcd_data_s *pdata);

/* lcd clk*/
struct lcd_clk_config_s *get_lcd_clk_config(struct aml_lcd_drv_s *pdrv);
void lcd_clk_config_print(struct aml_lcd_drv_s *pdrv);
void lcd_get_ss(struct aml_lcd_drv_s *pdrv);
int lcd_set_ss(struct aml_lcd_drv_s *pdrv, unsigned int level,
	       unsigned int freq, unsigned int mode);
void lcd_update_clk_frac(struct aml_lcd_drv_s *pdrv);
void lcd_set_clk(struct aml_lcd_drv_s *pdrv);
void lcd_disable_clk(struct aml_lcd_drv_s *pdrv);
void lcd_clk_generate_parameter(struct aml_lcd_drv_s *pdrv);
void lcd_clk_config_probe(struct aml_lcd_drv_s *pdrv);
int aml_lcd_prbs_test(struct aml_lcd_drv_s *pdrv, unsigned int ms, unsigned int mode_flag);

/* lcd phy */
void lcd_phy_tcon_chpi_bbc_init_tl1(struct lcd_config_s *pconf);
unsigned int lcd_phy_vswing_level_to_value(struct aml_lcd_drv_s *pdrv, unsigned int level);
unsigned int lcd_phy_amp_dft_value(struct aml_lcd_drv_s *pdrv);
unsigned int lcd_phy_preem_level_to_value(struct aml_lcd_drv_s *pdrv, unsigned int level);
void lcd_phy_set(struct aml_lcd_drv_s *pdrv, int status);
int lcd_phy_probe(struct aml_lcd_drv_s *pdrv);
int lcd_phy_config_init(struct aml_lcd_data_s *pdata);

/* lcd dphy */
void lcd_mipi_dphy_set(struct aml_lcd_drv_s *pdrv, unsigned char on_off);
void lcd_edp_dphy_set(struct aml_lcd_drv_s *pdrv, unsigned char on_off);
void lcd_lvds_dphy_set(struct aml_lcd_drv_s *pdrv, unsigned char on_off);
void lcd_vbyone_dphy_set(struct aml_lcd_drv_s *pdrv, unsigned char on_off);
#ifdef CONFIG_AML_LCD_TCON
void lcd_mlvds_dphy_set(struct aml_lcd_drv_s *pdrv, unsigned char on_off);
void lcd_p2p_dphy_set(struct aml_lcd_drv_s *pdrv, unsigned char on_off);
#endif

/* lcd lvds*/
void lcd_lvds_enable(struct aml_lcd_drv_s *pdrv);
void lcd_lvds_disable(struct aml_lcd_drv_s *pdrv);

/* lcd vbyone*/
void lcd_vbyone_enable(struct aml_lcd_drv_s *pdrv);
void lcd_vbyone_disable(struct aml_lcd_drv_s *pdrv);
void lcd_vbyone_sw_reset(struct aml_lcd_drv_s *pdrv);
void lcd_vbyone_wait_timing_stable(struct aml_lcd_drv_s *pdrv);
void lcd_vbyone_cdr_training_hold(struct aml_lcd_drv_s *pdrv, int flag);
void lcd_vbyone_wait_hpd(struct aml_lcd_drv_s *pdrv);
void lcd_vbyone_wait_stable(struct aml_lcd_drv_s *pdrv);
void lcd_vbyone_hw_filter(struct aml_lcd_drv_s *pdrv, int flag);

/* lcd tcon */
#ifdef CONFIG_AML_LCD_TCON
void lcd_tcon_info_print(struct aml_lcd_drv_s *pdrv);
int lcd_tcon_top_init(struct aml_lcd_drv_s *pdrv);
int lcd_tcon_enable(struct aml_lcd_drv_s *pdrv);
void lcd_tcon_disable(struct aml_lcd_drv_s *pdrv);
void lcd_tcon_global_reset(struct aml_lcd_drv_s *pdrv);
void lcd_tcon_dbg_check(struct aml_lcd_drv_s *pdrv, struct lcd_detail_timing_s *ptiming);
int lcd_tcon_probe(char *dt_addr, struct aml_lcd_drv_s *pdrv, int load_id);
#endif

/* lcd gpio */
int lcd_gpio_name_map_num(const char *name);
int lcd_gpio_set(int gpio, int value);
unsigned int lcd_gpio_input_get(int gpio);

/* lcd debug */
int lcd_debug_info_len(int num);
void lcd_info_print(struct aml_lcd_drv_s *pdrv);
void lcd_reg_print(struct aml_lcd_drv_s *pdrv);
void lcd_vbyone_rst(struct aml_lcd_drv_s *pdrv);
int lcd_vbyone_cdr(struct aml_lcd_drv_s *pdrv);
int lcd_vbyone_lock(struct aml_lcd_drv_s *pdrv);
void lcd_debug_probe(struct aml_lcd_drv_s *pdrv);
// int lcd_prbs_test(struct aml_lcd_drv_s *pdrv, unsigned int s, unsigned int mode_flag);

/* lcd driver */
#ifdef CONFIG_AML_LCD_TV
int lcd_mode_tv_init(struct aml_lcd_drv_s *pdrv);
#endif

#ifdef CONFIG_AML_LCD_TABLET
int lcd_mode_tablet_init(struct aml_lcd_drv_s *pdrv);
/* @dsi_common.c */
void lcd_dsi_init_table_load_dts(char *dtaddr, int offset, struct dsi_config_s *dconf);
void lcd_dsi_init_table_load_bsp(struct dsi_config_s *dconf);
void lcd_dsi_tx_ctrl(struct aml_lcd_drv_s *pdrv, unsigned char en);
unsigned long long lcd_dsi_get_min_bitrate(struct aml_lcd_drv_s *pdrv);
/* @dsi_debug.c */
void lcd_dsi_info_print(struct lcd_config_s *pconf);
void lcd_dsi_set_operation_mode(struct aml_lcd_drv_s *pdrv, unsigned char op_mode);
void lcd_dsi_write_cmd(struct aml_lcd_drv_s *pdrv, unsigned char *payload);
unsigned char lcd_dsi_read(struct aml_lcd_drv_s *pdrv,
			unsigned char *payload, unsigned char *rd_data, unsigned char rd_byte_len);
/* @dsi_addons/dsi_check_panel.c */
int mipi_dsi_check_state(struct aml_lcd_drv_s *pdrv, unsigned char reg, unsigned char cnt);

/* @lcd_eDP.c */
void dptx_DPCD_dump(struct aml_lcd_drv_s *pdrv);
int eDP_debug_test(struct aml_lcd_drv_s *pdrv, char *str, int num);
void edp_tx_ctrl(struct aml_lcd_drv_s *pdrv, int flag);
#endif

void lcd_wait_vsync(struct aml_lcd_drv_s *pdrv);

/* aml_bl driver */
void aml_bl_probe_single(unsigned char index, int load_id);
void aml_bl_remove_all(void);
int aml_bl_index_add(int drv_index, int conf_index);
int aml_bl_index_remove(int drv_index);
int aml_bl_init(void);
void aml_bl_driver_enable(int index);
void aml_bl_driver_disable(int index);
void aml_bl_set_level(int index, unsigned int level);
unsigned int aml_bl_get_level(int index);
void aml_bl_config_print(int index);
int aml_bl_pwm_reg_config_init(struct aml_lcd_data_s *pdata);

#endif

