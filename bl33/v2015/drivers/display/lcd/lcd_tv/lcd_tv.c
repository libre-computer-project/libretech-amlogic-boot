/* SPDX-License-Identifier: (GPL-2.0+ OR MIT) */
/*
 * drivers/display/lcd/lcd_tv/lcd_tv.c
 *
 * Copyright (C) 2020 Amlogic, Inc. All rights reserved.
 *
 */

#include <common.h>
#include <malloc.h>
#include <asm/arch/gpio.h>
#ifdef CONFIG_OF_LIBFDT
#include <libfdt.h>
#endif
#include <amlogic/vmode.h>
#include <amlogic/aml_lcd.h>
#include "../aml_lcd_reg.h"
#include "../aml_lcd_common.h"
#include "lcd_tv.h"

/* ************************************************** *
   lcd mode function
 * ************************************************** */
static struct lcd_duration_s lcd_std_fr[] = {
	{288, 288,    1,    0},
	{240, 240,    1,    0},
	{239, 240000, 1001, 1},
	{200, 200,    1,    0},
	{192, 192,    1,    0},
	{191, 192000, 1001, 1},
	{144, 144,    1,    0},
	{120, 120,    1,    0},
	{119, 120000, 1001, 1},
	{100, 100,    1,    0},
	{96,  96,     1,    0},
	{95,  96000,  1001, 1},
	{60,  60,     1,    0},
	{59,  60000,  1001, 1},
	{50,  50,     1,    0},
	{48,  48,     1,    0},
	{47,  48000,  1001, 1},
	{0,   0,      0,    0}
};

//ref default mode compatible
static struct lcd_vmode_info_s lcd_vmode_ref[] = {
	{//0
		.name     = "600p",
		.width    = 1024,
		.height   = 600,
		.base_fr  = 60,
		.duration_index = 0,
		.duration = {
			{60,  60,     1,    0},
			{59,  60000,  1001, 1},
			{50,  50,     1,    0},
			{48,  48,     1,    0},
			{47,  48000,  1001, 1},
			{0,   0,      0,    0}
		},
		.dft_timing = NULL,
	},
	{//1
		.name     = "768p",
		.width    = 1366,
		.height   = 768,
		.base_fr  = 60,
		.duration_index = 0,
		.duration = {
			{60,  60,     1,    0},
			{59,  60000,  1001, 1},
			{50,  50,     1,    0},
			{48,  48,     1,    0},
			{47,  48000,  1001, 1},
			{0,   0,      0,    0}
		},
		.dft_timing = NULL,
	},
	{//2
		.name     = "1080p",
		.width    = 1920,
		.height   = 1080,
		.base_fr  = 60,
		.duration_index = 0,
		.duration = {
			{60,  60,     1,    0},
			{59,  60000,  1001, 1},
			{50,  50,     1,    0},
			{48,  48,     1,    0},
			{47,  48000,  1001, 1},
			{0,   0,      0,    0}
		},
		.dft_timing = NULL,
	},
	{//3
		.name     = "2160p",
		.width    = 3840,
		.height   = 2160,
		.base_fr  = 60,
		.duration_index = 0,
		.duration = {
			{60,  60,     1,    0},
			{59,  60000,  1001, 1},
			{50,  50,     1,    0},
			{48,  48,     1,    0},
			{47,  48000,  1001, 1},
			{0,   0,      0,    0}
		},
		.dft_timing = NULL,
	},
	{//4
		.name     = "invalid",
		.width    = 1920,
		.height   = 1080,
		.base_fr  = 60,
		.duration_index = 0,
		.duration = {
			{60,  60,     1,    0},
			{0,   0,      0,    0}
		},
		.dft_timing = NULL,
	},
};

static int lcd_vmode_add_list(struct aml_lcd_drv_s *pdrv, struct lcd_vmode_info_s *vmode_info)
{
	struct lcd_vmode_list_s *temp_list;
	struct lcd_vmode_list_s *cur_list;

	if (!vmode_info)
		return -1;

	/* creat list */
	cur_list = malloc(sizeof(*cur_list));
	if (!cur_list)
		return -1;
	memset(cur_list, 0, sizeof(*cur_list));
	cur_list->info = vmode_info;

	if (!pdrv->vmode_mgr.vmode_list_header) {
		pdrv->vmode_mgr.vmode_list_header = cur_list;
	} else {
		temp_list = pdrv->vmode_mgr.vmode_list_header;
		while (temp_list->next)
			temp_list = temp_list->next;
		temp_list->next = cur_list;
	}

	LCDPR("%s: name:%s, base_fr:%dhz\n",
		__func__, cur_list->info->name, cur_list->info->base_fr);

	return 0;
}

static int lcd_vmode_remove_list(struct aml_lcd_drv_s *pdrv)
{
	struct lcd_vmode_list_s *cur_list;
	struct lcd_vmode_list_s *next_list;

	cur_list = pdrv->vmode_mgr.vmode_list_header;
	while (cur_list) {
		next_list = cur_list->next;
		if (cur_list->info) {
			memset(cur_list->info, 0, sizeof(struct lcd_vmode_info_s));
			free(cur_list->info);
		}
		memset(cur_list, 0, sizeof(struct lcd_vmode_list_s));
		free(cur_list);
		cur_list = next_list;
	}
	pdrv->vmode_mgr.vmode_list_header = NULL;
	pdrv->vmode_mgr.cur_vmode_info = NULL;

	return 0;
}

static void lcd_vmode_duration_add(struct lcd_vmode_info_s *vmode_find,
		struct lcd_duration_s *duration_tablet, unsigned int size)
{
	unsigned int n, i;

	memset(vmode_find->duration, 0, sizeof(struct lcd_duration_s) * LCD_DURATION_MAX);
	n = 0;
	for (i = 0; i < size; i++) {
		if (duration_tablet[i].frame_rate == 0)
			break;
		if (duration_tablet[i].frame_rate > vmode_find->dft_timing->frame_rate_max)
			continue;
		if (duration_tablet[i].frame_rate < vmode_find->dft_timing->frame_rate_min)
			break;

		vmode_find->duration[n].frame_rate = duration_tablet[i].frame_rate;
		vmode_find->duration[n].duration_num = duration_tablet[i].duration_num;
		vmode_find->duration[n].duration_den = duration_tablet[i].duration_den;
		vmode_find->duration[n].frac = duration_tablet[i].frac;
		n++;
		if (n >= LCD_DURATION_MAX)
			break;
	}
	vmode_find->duration_cnt = n;
}

//--default ref mode: 1080p60hz, 2160p60hz...
static struct lcd_vmode_info_s *lcd_vmode_default_find(struct lcd_detail_timing_s *ptiming)
{
	struct lcd_vmode_info_s *vmode_find = NULL;
	int i, dft_vmode_size = ARRAY_SIZE(lcd_vmode_ref);

	for (i = 0; i < dft_vmode_size; i++) {
		if (ptiming->h_active == lcd_vmode_ref[i].width &&
		    ptiming->v_active == lcd_vmode_ref[i].height &&
		    ptiming->frame_rate == lcd_vmode_ref[i].base_fr) {
			vmode_find = malloc(sizeof(struct lcd_vmode_info_s));
			if (!vmode_find)
				return NULL;
			memset(vmode_find, 0, sizeof(struct lcd_vmode_info_s));
			memcpy(vmode_find, &lcd_vmode_ref[i], sizeof(struct lcd_vmode_info_s));
			vmode_find->dft_timing = ptiming;
			lcd_vmode_duration_add(vmode_find,
				lcd_vmode_ref[i].duration, LCD_DURATION_MAX);
			break;
		}
	}

	return vmode_find;
}

//--general mode: (h)x(v)p(frame_rate)hz
static struct lcd_vmode_info_s *lcd_vmode_general_find(struct lcd_detail_timing_s *ptiming)
{
	struct lcd_vmode_info_s *vmode_find = NULL;
	unsigned int std_fr_size = ARRAY_SIZE(lcd_std_fr);

	vmode_find = malloc(sizeof(struct lcd_vmode_info_s));
	if (!vmode_find)
		return NULL;
	memset(vmode_find, 0, sizeof(struct lcd_vmode_info_s));
	vmode_find->width = ptiming->h_active;
	vmode_find->height = ptiming->v_active;
	vmode_find->base_fr = ptiming->frame_rate;
	snprintf(vmode_find->name, 32, "%dx%dp", ptiming->h_active, ptiming->v_active);
	vmode_find->dft_timing = ptiming;
	lcd_vmode_duration_add(vmode_find, lcd_std_fr, std_fr_size);

	return vmode_find;
}

static void lcd_output_vmode_init(struct lcd_config_s *pconf)
{
	struct aml_lcd_drv_s *pdrv = aml_lcd_get_driver();
	struct lcd_vmode_info_s *vmode_find = NULL;
	struct lcd_detail_timing_s **timing_match;
	int i;

	if (!pconf)
		return;

	lcd_vmode_remove_list(pdrv);

	//default ref timing
	//--default mode: 1080p60hz, 2160p60hz...
	vmode_find = lcd_vmode_default_find(&pconf->lcd_timing.dft_timing);
	if (!vmode_find) {
		//--general mode: (h)x(v)p(frame_rate)hz
		vmode_find = lcd_vmode_general_find(&pconf->lcd_timing.dft_timing);
		if (!vmode_find)
			return;
	}
	lcd_vmode_add_list(pdrv, vmode_find);

	timing_match = lcd_cus_ctrl_timing_match_get(pconf);
	if (timing_match) {
		for (i = 0; i < pconf->cus_ctrl.timing_cnt; i++) {
			if (!timing_match[i])
				break;

			vmode_find = lcd_vmode_default_find(timing_match[i]);
			if (!vmode_find) {
				//--general mode: (h)x(v)p(frame_rate)hz
				vmode_find = lcd_vmode_general_find(timing_match[i]);
				if (!vmode_find)
					continue;
			}
			lcd_vmode_add_list(pdrv, vmode_find);
		}
		memset(timing_match, 0,
			pconf->cus_ctrl.timing_cnt * sizeof(struct lcd_detail_timing_s *));
		free(timing_match);
	}
}

/* ************************************************** *
 * lcd config load
 * **************************************************
 */
static void lcd_config_load_print(struct lcd_config_s *pconf)
{
	struct lcd_detail_timing_s *ptiming = &pconf->lcd_timing.dft_timing;

	LCDPR("%s, %s, %dbit, %dx%d\n",
		pconf->lcd_basic.model_name,
		lcd_type_type_to_str(pconf->lcd_basic.lcd_type),
		pconf->lcd_basic.lcd_bits,
		ptiming->h_active, ptiming->v_active);

	if (lcd_debug_print_flag == 0)
		return;

	LCDPR("h_period = %d\n", ptiming->h_period);
	LCDPR("v_period = %d\n", ptiming->v_period);

	LCDPR("h_period_min = %d\n", ptiming->h_period_min);
	LCDPR("h_period_max = %d\n", ptiming->h_period_max);
	LCDPR("v_period_min = %d\n", ptiming->v_period_min);
	LCDPR("v_period_max = %d\n", ptiming->v_period_max);
	LCDPR("pclk_min = %d\n", ptiming->pclk_min);
	LCDPR("pclk_max = %d\n", ptiming->pclk_max);

	LCDPR("hsync_width = %d\n", ptiming->hsync_width);
	LCDPR("hsync_bp = %d\n", ptiming->hsync_bp);
	LCDPR("hsync_pol = %d\n", ptiming->hsync_pol);
	LCDPR("vsync_width = %d\n", ptiming->vsync_width);
	LCDPR("vsync_bp = %d\n", ptiming->vsync_bp);
	LCDPR("vsync_pol = %d\n", ptiming->vsync_pol);

	LCDPR("fr_adjust_type = %d\n", ptiming->fr_adjust_type);
	LCDPR("ss_level = %d\n", pconf->lcd_timing.ss_level);
	LCDPR("pll_flag = %d\n", pconf->lcd_timing.pll_flag);
	LCDPR("pixel_clk = %d\n", ptiming->pixel_clk);

	if (pconf->lcd_basic.lcd_type == LCD_VBYONE) {
		LCDPR("lane_count = %d\n", pconf->lcd_control.vbyone_config->lane_count);
		LCDPR("byte_mode = %d\n", pconf->lcd_control.vbyone_config->byte_mode);
		LCDPR("region_num = %d\n", pconf->lcd_control.vbyone_config->region_num);
		LCDPR("color_fmt = %d\n", pconf->lcd_control.vbyone_config->color_fmt);
	} else if (pconf->lcd_basic.lcd_type == LCD_LVDS) {
		LCDPR("lvds_repack = %d\n", pconf->lcd_control.lvds_config->lvds_repack);
		LCDPR("pn_swap = %d\n", pconf->lcd_control.lvds_config->pn_swap);
		LCDPR("dual_port = %d\n", pconf->lcd_control.lvds_config->dual_port);
		LCDPR("port_swap = %d\n", pconf->lcd_control.lvds_config->port_swap);
		LCDPR("lane_reverse = %d\n", pconf->lcd_control.lvds_config->lane_reverse);
	} else if (pconf->lcd_basic.lcd_type == LCD_P2P) {
		LCDPR("p2p_type = %d\n", pconf->lcd_control.p2p_config->p2p_type);
		LCDPR("lane_num = %d\n", pconf->lcd_control.p2p_config->lane_num);
		LCDPR("channel_sel0 = %d\n", pconf->lcd_control.p2p_config->channel_sel0);
		LCDPR("channel_sel1 = %d\n", pconf->lcd_control.p2p_config->channel_sel1);
		LCDPR("pn_swap = %d\n", pconf->lcd_control.p2p_config->pn_swap);
		LCDPR("bit_swap = %d\n", pconf->lcd_control.p2p_config->bit_swap);
	}
}

#ifdef CONFIG_OF_LIBFDT
static int lcd_config_load_from_dts(char *dt_addr, struct lcd_config_s *pconf)
{
	int parent_offset;
	int child_offset;
	char propname[30];
	char *propdata;
	int len, i = 0;
	struct aml_lcd_drv_s *pdrv = aml_lcd_get_driver();
	struct lcd_detail_timing_s *ptiming = &pconf->lcd_timing.dft_timing;
	struct lvds_config_s *lvds_conf;
	struct vbyone_config_s *vx1_conf;
	struct mlvds_config_s *mlvds_conf;
	struct p2p_config_s *p2p_conf;
	struct phy_config_s *phy_conf;
	unsigned int temp;

	parent_offset = fdt_path_offset(dt_addr, "/lcd");
	if (parent_offset < 0) {
		LCDERR("not find /lcd node: %s\n",fdt_strerror(parent_offset));
		return -1;
	}

	propdata = (char *)fdt_getprop(dt_addr, parent_offset, "pinctrl_version", NULL);
	if (propdata) {
		pconf->pinctrl_ver = (unsigned char)(be32_to_cpup((u32*)propdata));
	} else {
		pconf->pinctrl_ver = 0;
	}
	LCDPR("pinctrl_version: %d\n", pconf->pinctrl_ver);

	/* check panel_type */
	char *panel_type = getenv("panel_type");
	if (panel_type == NULL) {
		LCDERR("no panel_type, use default lcd config\n ");
		return -1;
	}
	LCDPR("use panel_type=%s\n", panel_type);

	if (strlen(panel_type) > 25) {
		LCDERR("panel_type len is too long\n");
		return -1;
	}
	sprintf(propname, "/lcd/%s", panel_type);
	child_offset = fdt_path_offset(dt_addr, propname);
	if (child_offset < 0) {
		LCDERR("not find /lcd/%s node: %s\n",
			panel_type, fdt_strerror(child_offset));
		return -1;
	}

	propdata = (char *)fdt_getprop(dt_addr, child_offset, "model_name", NULL);
	if (propdata == NULL) {
		LCDERR("failed to get model_name\n");
		strncpy(pconf->lcd_basic.model_name, panel_type,
			sizeof(pconf->lcd_basic.model_name) - 1);
	} else {
		strncpy(pconf->lcd_basic.model_name, propdata,
			sizeof(pconf->lcd_basic.model_name) - 1);
	}
	pconf->lcd_basic.model_name[sizeof(pconf->lcd_basic.model_name) - 1]
		= '\0';

	propdata = (char *)fdt_getprop(dt_addr, child_offset, "interface", NULL);
	if (propdata == NULL) {
		LCDERR("failed to get interface\n");
		return -1;
	} else {
		pconf->lcd_basic.lcd_type = lcd_type_str_to_type(propdata);
	}

	propdata = (char *)fdt_getprop(dt_addr, child_offset, "customer_pinmux", NULL);
	if (propdata == NULL) {
		if (lcd_debug_print_flag)
			LCDPR("failed to get customer_pinmux\n");
		pconf->customer_pinmux = 0;
	} else {
		pconf->customer_pinmux = (unsigned char)(be32_to_cpup((u32*)propdata));
		LCDPR("customer_pinmux: %d\n", pconf->customer_pinmux);
	}

	propdata = (char *)fdt_getprop(dt_addr, child_offset, "config_check", NULL);
	if (!propdata) {
		pconf->lcd_basic.config_check = 0; //follow config_check_glb
	} else {
		temp = be32_to_cpup((u32 *)propdata);
		pconf->lcd_basic.config_check = temp ? 0x3 : 0x2;
		if (lcd_debug_print_flag)
			LCDPR("find config_check: %d\n", temp);
	}

	propdata = (char *)fdt_getprop(dt_addr, child_offset, "basic_setting", NULL);
	if (propdata == NULL) {
		LCDERR("failed to get basic_setting\n");
		return -1;
	} else {
		ptiming->h_active = be32_to_cpup((u32 *)propdata);
		ptiming->v_active = be32_to_cpup((((u32 *)propdata) + 1));
		ptiming->h_period = be32_to_cpup((((u32 *)propdata) + 2));
		ptiming->v_period = be32_to_cpup((((u32 *)propdata) + 3));
		pconf->lcd_basic.lcd_bits = be32_to_cpup((((u32*)propdata)+4));
		pconf->lcd_basic.screen_width = be32_to_cpup((((u32*)propdata)+5));
		pconf->lcd_basic.screen_height = be32_to_cpup((((u32*)propdata)+6));
	}

	propdata = (char *)fdt_getprop(dt_addr, child_offset, "range_setting", NULL);
	if (propdata == NULL) {
		LCDPR("no range_setting\n");
		ptiming->h_period_min = ptiming->h_period;
		ptiming->h_period_max = ptiming->h_period;
		ptiming->v_period_min = ptiming->v_period;
		ptiming->v_period_max = ptiming->v_period;
		ptiming->pclk_min = 0;
		ptiming->pclk_max = 0;
	} else {
		ptiming->h_period_min = be32_to_cpup((u32 *)propdata);
		ptiming->h_period_max = be32_to_cpup((((u32 *)propdata) + 1));
		ptiming->v_period_min = be32_to_cpup((((u32 *)propdata) + 2));
		ptiming->v_period_max = be32_to_cpup((((u32 *)propdata) + 3));
		ptiming->pclk_min = be32_to_cpup((((u32 *)propdata) + 4));
		ptiming->pclk_max = be32_to_cpup((((u32 *)propdata) + 5));
	}

	propdata = (char *)fdt_getprop(dt_addr, child_offset, "lcd_timing", NULL);
	if (propdata == NULL) {
		LCDERR("failed to get lcd_timing\n");
		return -1;
	} else {
		ptiming->hsync_width = (unsigned short)(be32_to_cpup((u32 *)propdata));
		ptiming->hsync_bp    = (unsigned short)(be32_to_cpup((((u32 *)propdata) + 1)));
		ptiming->hsync_fp = ptiming->h_period - ptiming->h_active -
			ptiming->hsync_width - ptiming->hsync_bp;
		ptiming->hsync_pol   = (unsigned short)(be32_to_cpup((((u32 *)propdata) + 2)));
		ptiming->vsync_width = (unsigned short)(be32_to_cpup((((u32 *)propdata) + 3)));
		ptiming->vsync_bp    = (unsigned short)(be32_to_cpup((((u32 *)propdata) + 4)));
		ptiming->vsync_fp = ptiming->v_period - ptiming->v_active -
			ptiming->vsync_width - ptiming->vsync_bp;
		ptiming->vsync_pol   = (unsigned short)(be32_to_cpup((((u32 *)propdata) + 5)));
	}

	propdata = (char *)fdt_getprop(dt_addr, child_offset, "pre_de", NULL);
	if (!propdata) {
		if (lcd_debug_print_flag)
			LCDERR("failed to get pre_de\n");
		pconf->lcd_timing.pre_de_h = 0;
		pconf->lcd_timing.pre_de_v = 0;
	} else {
		pconf->lcd_timing.pre_de_h = (unsigned char)(be32_to_cpup((u32 *)propdata));
		pconf->lcd_timing.pre_de_v = (unsigned char)(be32_to_cpup((((u32 *)propdata) + 1)));
	}

	propdata = (char *)fdt_getprop(dt_addr, child_offset, "clk_attr", NULL);
	if (propdata == NULL) {
		LCDERR("failed to get clk_attr\n");
		ptiming->fr_adjust_type = 0xff;
		pconf->lcd_timing.ss_level = 0;
		pconf->lcd_timing.pll_flag = 1;
		ptiming->pixel_clk = 60;
	} else {
		ptiming->fr_adjust_type = (unsigned char)(be32_to_cpup((u32 *)propdata));
		temp = be32_to_cpup((((u32 *)propdata) + 1));
		pconf->lcd_timing.ss_level = temp & 0xff;
		pconf->lcd_timing.ss_freq = (temp >> 8) & 0xf;
		pconf->lcd_timing.ss_mode = (temp >> 12) & 0xf;
		pconf->lcd_timing.pll_flag = (unsigned char)(be32_to_cpup((((u32 *)propdata) + 2)));
		ptiming->pixel_clk = be32_to_cpup((((u32 *)propdata) + 3));
	}

	lcd_clk_frame_rate_init(ptiming);
	lcd_default_to_basic_timing_init_config(pconf);

	switch (pconf->lcd_basic.lcd_type) {
	case LCD_LVDS:
		if (pconf->lcd_control.lvds_config == NULL) {
			LCDERR("lvds_config is null\n");
			return -1;
		}
		lvds_conf = pconf->lcd_control.lvds_config;
		propdata = (char *)fdt_getprop(dt_addr, child_offset, "lvds_attr", &len);
		if (propdata == NULL) {
			LCDERR("failed to get lvds_attr\n");
		} else {
			len = len / 4;
			if (len == 5) {
				lvds_conf->lvds_repack = be32_to_cpup((u32*)propdata);
				lvds_conf->dual_port   = be32_to_cpup((((u32*)propdata)+1));
				lvds_conf->pn_swap     = be32_to_cpup((((u32*)propdata)+2));
				lvds_conf->port_swap   = be32_to_cpup((((u32*)propdata)+3));
				lvds_conf->lane_reverse = be32_to_cpup((((u32*)propdata)+4));
			} else if (len == 4) {
				lvds_conf->lvds_repack = be32_to_cpup((u32*)propdata);
				lvds_conf->dual_port   = be32_to_cpup((((u32*)propdata)+1));
				lvds_conf->pn_swap     = be32_to_cpup((((u32*)propdata)+2));
				lvds_conf->port_swap   = be32_to_cpup((((u32*)propdata)+3));
				lvds_conf->lane_reverse = 0;
			} else {
				LCDERR("invalid lvds_attr parameters cnt: %d\n", len);
			}
		}

		propdata = (char *)fdt_getprop(dt_addr, child_offset, "phy_attr", &len);
		if (propdata == NULL) {
			if (lcd_debug_print_flag)
				LCDPR("failed to get phy_attr\n");
			lvds_conf->phy_vswing = LVDS_PHY_VSWING_DFT;
			lvds_conf->phy_preem  = LVDS_PHY_PREEM_DFT;
			lvds_conf->phy_clk_vswing = LVDS_PHY_CLK_VSWING_DFT;
			lvds_conf->phy_clk_preem  = LVDS_PHY_CLK_PREEM_DFT;
		} else {
			len = len / 4;
			if (len == 4) {
				lvds_conf->phy_vswing = be32_to_cpup((u32*)propdata);
				lvds_conf->phy_preem  = be32_to_cpup((((u32*)propdata)+1));
				lvds_conf->phy_clk_vswing = be32_to_cpup((((u32*)propdata)+2));
				lvds_conf->phy_clk_preem  = be32_to_cpup((((u32*)propdata)+3));
				if (lcd_debug_print_flag) {
					LCDPR("set phy vswing=0x%x, preemphasis=0x%x\n",
						lvds_conf->phy_vswing, lvds_conf->phy_preem);
					LCDPR("set phy clk_vswing=0x%x, clk_preemphasis=0x%x\n",
						lvds_conf->phy_clk_vswing, lvds_conf->phy_clk_preem);
				}
			} else if (len == 2) {
				lvds_conf->phy_vswing = be32_to_cpup((u32*)propdata);
				lvds_conf->phy_preem  = be32_to_cpup((((u32*)propdata)+1));
				lvds_conf->phy_clk_vswing = LVDS_PHY_CLK_VSWING_DFT;
				lvds_conf->phy_clk_preem  = LVDS_PHY_CLK_PREEM_DFT;
				if (lcd_debug_print_flag) {
					LCDPR("set phy vswing=0x%x, preemphasis=0x%x\n",
						lvds_conf->phy_vswing, lvds_conf->phy_preem);
				}
			} else {
				LCDERR("invalid phy_attr parameters cnt: %d\n", len);
			}

			if (!pconf->lcd_control.phy_cfg) {
				LCDERR("phy_cfg is null\n");
				return -1;
			}
			phy_conf = pconf->lcd_control.phy_cfg;
			phy_conf->lane_num = 12;
			phy_conf->vswing_level = lvds_conf->phy_vswing & 0xf;
			phy_conf->ext_pullup = (lvds_conf->phy_vswing >> 4) & 0x3;
			phy_conf->vswing =
				lcd_phy_vswing_level_to_value
					(pdrv, phy_conf->vswing_level);
			phy_conf->preem_level = lvds_conf->phy_preem;
			temp = lcd_phy_preem_level_to_value(pdrv, phy_conf->preem_level);
			for (i = 0; i < phy_conf->lane_num; i++) {
				phy_conf->lane[i].amp = 0;
				phy_conf->lane[i].preem = temp;
			}
		}
		break;
	case LCD_MLVDS:
		if (pconf->lcd_control.mlvds_config == NULL) {
			LCDERR("mlvds_config is null\n");
			return -1;
		}
		mlvds_conf = pconf->lcd_control.mlvds_config;
		propdata = (char *)fdt_getprop(dt_addr, child_offset, "minilvds_attr", &len);
		if (propdata == NULL) {
			LCDERR("failed to get minilvds_attr\n");
		} else {
			mlvds_conf->channel_num  = be32_to_cpup((u32*)propdata);
			mlvds_conf->channel_sel0 = be32_to_cpup((((u32*)propdata)+1));
			mlvds_conf->channel_sel1 = be32_to_cpup((((u32*)propdata)+2));
			mlvds_conf->clk_phase    = be32_to_cpup((((u32*)propdata)+3));
			mlvds_conf->pn_swap      = be32_to_cpup((((u32*)propdata)+4));
			mlvds_conf->bit_swap     = be32_to_cpup((((u32*)propdata)+5));
		}

		propdata = (char *)fdt_getprop(dt_addr, child_offset, "phy_attr", &len);
		if (propdata == NULL) {
			if (lcd_debug_print_flag)
				LCDPR("failed to get phy_attr\n");
			mlvds_conf->phy_vswing = LVDS_PHY_VSWING_DFT;
			mlvds_conf->phy_preem  = LVDS_PHY_PREEM_DFT;
		} else {
			mlvds_conf->phy_vswing = be32_to_cpup((u32*)propdata);
			mlvds_conf->phy_preem  = be32_to_cpup((((u32*)propdata)+1));
			if (lcd_debug_print_flag) {
				LCDPR("set phy vswing=0x%x, preemphasis=0x%x\n",
					mlvds_conf->phy_vswing, mlvds_conf->phy_preem);
			}
		}
		if (!pconf->lcd_control.phy_cfg) {
			LCDERR("phy_cfg is null\n");
			return -1;
		}
		phy_conf = pconf->lcd_control.phy_cfg;
		phy_conf->lane_num = 12;
		phy_conf->vswing_level = mlvds_conf->phy_vswing & 0xf;
		phy_conf->ext_pullup = (mlvds_conf->phy_vswing >> 4) & 0x3;
		phy_conf->vswing = lcd_phy_vswing_level_to_value(pdrv, phy_conf->vswing_level);
		phy_conf->preem_level = mlvds_conf->phy_preem;
		temp = lcd_phy_preem_level_to_value(pdrv, phy_conf->preem_level);
		for (i = 0; i < phy_conf->lane_num; i++) {
			phy_conf->lane[i].amp = 0;
			phy_conf->lane[i].preem = temp;
		}
		break;
	case LCD_VBYONE:
		if (pconf->lcd_control.vbyone_config == NULL) {
			LCDERR("vbyone_config is null\n");
			return -1;
		}
		vx1_conf = pconf->lcd_control.vbyone_config;
		propdata = (char *)fdt_getprop(dt_addr, child_offset, "vbyone_attr", NULL);
		if (propdata == NULL) {
			LCDERR("failed to get vbyone_attr\n");
		} else {
			vx1_conf->lane_count = be32_to_cpup((u32*)propdata);
			vx1_conf->region_num = be32_to_cpup((((u32*)propdata)+1));
			vx1_conf->byte_mode  = be32_to_cpup((((u32*)propdata)+2));
			vx1_conf->color_fmt  = be32_to_cpup((((u32*)propdata)+3));
		}
		propdata = (char *)fdt_getprop(dt_addr, child_offset, "phy_attr", NULL);
		if (propdata == NULL) {
			if (lcd_debug_print_flag)
				LCDPR("failed to get phy_attr\n");
			vx1_conf->phy_vswing = VX1_PHY_VSWING_DFT;
			vx1_conf->phy_preem  = VX1_PHY_PREEM_DFT;
		} else {
			vx1_conf->phy_vswing = be32_to_cpup((u32*)propdata);
			vx1_conf->phy_preem  = be32_to_cpup((((u32*)propdata)+1));
			if (lcd_debug_print_flag) {
				LCDPR("set phy vswing=0x%x, preemphasis=0x%x\n",
					vx1_conf->phy_vswing, vx1_conf->phy_preem);
			}
		}
		if (!pconf->lcd_control.phy_cfg) {
			LCDERR("phy_cfg is null\n");
			return -1;
		}
		phy_conf = pconf->lcd_control.phy_cfg;
		phy_conf->lane_num = 8;
		phy_conf->vswing_level = vx1_conf->phy_vswing & 0xf;
		phy_conf->ext_pullup = (vx1_conf->phy_vswing >> 4) & 0x3;
		phy_conf->vswing = lcd_phy_vswing_level_to_value(pdrv, phy_conf->vswing_level);
		phy_conf->preem_level = vx1_conf->phy_preem;
		temp = lcd_phy_preem_level_to_value(pdrv, phy_conf->preem_level);
		for (i = 0; i < phy_conf->lane_num; i++) {
			phy_conf->lane[i].amp = 0;
			phy_conf->lane[i].preem = temp;
		}

		propdata = (char *)fdt_getprop(dt_addr, child_offset, "vbyone_ctrl_flag", NULL);
		if (propdata == NULL) {
			if (lcd_debug_print_flag)
				LCDPR("failed to get vbyone_ctrl_flag\n");
			vx1_conf->ctrl_flag = 0;
			vx1_conf->power_on_reset_delay = VX1_PWR_ON_RESET_DLY_DFT;
			vx1_conf->hpd_data_delay = VX1_HPD_DATA_DELAY_DFT;
			vx1_conf->cdr_training_hold = VX1_CDR_TRAINING_HOLD_DFT;
			vx1_conf->vx1_sw_filter_en = 0;
			vx1_conf->vx1_sw_filter_time = VX1_SW_FILTER_TIME_DFT;
			vx1_conf->vx1_sw_filter_cnt = VX1_SW_FILTER_CNT_DFT;
			vx1_conf->vx1_sw_filter_retry_cnt = VX1_SW_FILTER_RETRY_CNT_DFT;
			vx1_conf->vx1_sw_filter_retry_delay = VX1_SW_FILTER_RETRY_DLY_DFT;
			vx1_conf->vx1_sw_cdr_detect_time = VX1_SW_CDR_DET_TIME_DFT;
			vx1_conf->vx1_sw_cdr_detect_cnt = VX1_SW_CDR_DET_CNT_DFT;
			vx1_conf->vx1_sw_cdr_timeout_cnt = VX1_SW_CDR_TIMEOUT_CNT_DFT;
		} else {
			vx1_conf->ctrl_flag = be32_to_cpup((u32*)propdata);
			vx1_conf->vx1_sw_filter_en = (vx1_conf->ctrl_flag >> 4) & 3;
			LCDPR("vbyone ctrl_flag=0x%x\n", vx1_conf->ctrl_flag);
		}
		if (vx1_conf->ctrl_flag & 0x7) {
			propdata = (char *)fdt_getprop(dt_addr, child_offset, "vbyone_ctrl_timing", NULL);
			if (propdata == NULL) {
				LCDPR("failed to get vbyone_ctrl_timing\n");
				vx1_conf->power_on_reset_delay = VX1_PWR_ON_RESET_DLY_DFT;
				vx1_conf->hpd_data_delay = VX1_HPD_DATA_DELAY_DFT;
				vx1_conf->cdr_training_hold = VX1_CDR_TRAINING_HOLD_DFT;
			} else {
				vx1_conf->power_on_reset_delay = be32_to_cpup((u32*)propdata);
				vx1_conf->hpd_data_delay = be32_to_cpup((((u32*)propdata)+1));
				vx1_conf->cdr_training_hold = be32_to_cpup((((u32*)propdata)+2));
			}
			if (lcd_debug_print_flag) {
				LCDPR("power_on_reset_delay: %d\n", vx1_conf->power_on_reset_delay);
				LCDPR("hpd_data_delay: %d\n", vx1_conf->hpd_data_delay);
				LCDPR("cdr_training_hold: %d\n", vx1_conf->cdr_training_hold);
			}
		}
		if (vx1_conf->vx1_sw_filter_en) {
			propdata = (char *)fdt_getprop(dt_addr, child_offset, "vbyone_sw_filter", NULL);
			if (propdata == NULL) {
					LCDPR("failed to get vbyone_sw_filter\n");
				vx1_conf->vx1_sw_filter_time = VX1_SW_FILTER_TIME_DFT;
				vx1_conf->vx1_sw_filter_cnt = VX1_SW_FILTER_CNT_DFT;
				vx1_conf->vx1_sw_filter_retry_cnt = VX1_SW_FILTER_RETRY_CNT_DFT;
				vx1_conf->vx1_sw_filter_retry_delay = VX1_SW_FILTER_RETRY_DLY_DFT;
				vx1_conf->vx1_sw_cdr_detect_time = VX1_SW_CDR_DET_TIME_DFT;
				vx1_conf->vx1_sw_cdr_detect_cnt = VX1_SW_CDR_DET_CNT_DFT;
				vx1_conf->vx1_sw_cdr_timeout_cnt = VX1_SW_CDR_TIMEOUT_CNT_DFT;
			} else {
				vx1_conf->vx1_sw_filter_time = be32_to_cpup((u32*)propdata);
				vx1_conf->vx1_sw_filter_cnt = be32_to_cpup((((u32*)propdata)+1));
				vx1_conf->vx1_sw_filter_retry_cnt = be32_to_cpup((((u32*)propdata)+2));
				vx1_conf->vx1_sw_filter_retry_delay = be32_to_cpup((((u32*)propdata)+3));
				vx1_conf->vx1_sw_cdr_detect_time = be32_to_cpup((((u32*)propdata)+4));
				vx1_conf->vx1_sw_cdr_detect_cnt = be32_to_cpup((((u32*)propdata)+5));
				vx1_conf->vx1_sw_cdr_timeout_cnt = be32_to_cpup((((u32*)propdata)+6));
				if (lcd_debug_print_flag) {
					LCDPR("vx1_sw_filter_en: %d\n", vx1_conf->vx1_sw_filter_en);
					LCDPR("vx1_sw_filter_time: %d\n", vx1_conf->vx1_sw_filter_time);
					LCDPR("vx1_sw_filter_cnt: %d\n", vx1_conf->vx1_sw_filter_cnt);
					LCDPR("vx1_sw_filter_retry_cnt: %d\n", vx1_conf->vx1_sw_filter_retry_cnt);
					LCDPR("vx1_sw_filter_retry_delay: %d\n", vx1_conf->vx1_sw_filter_retry_delay);
					LCDPR("vx1_sw_cdr_detect_time: %d\n", vx1_conf->vx1_sw_cdr_detect_time);
					LCDPR("vx1_sw_cdr_detect_cnt: %d\n", vx1_conf->vx1_sw_cdr_detect_cnt);
					LCDPR("vx1_sw_cdr_timeout_cnt: %d\n", vx1_conf->vx1_sw_cdr_timeout_cnt);
				}
			}
		}
		propdata = (char *)fdt_getprop(dt_addr, child_offset, "hw_filter", NULL);
		if (propdata == NULL) {
			if (lcd_debug_print_flag)
				LCDPR("failed to get hw_filter\n");
			vx1_conf->hw_filter_time = 0;
			vx1_conf->hw_filter_cnt = 0;
		} else {
			vx1_conf->hw_filter_time = be32_to_cpup((u32*)propdata);
			vx1_conf->hw_filter_cnt = be32_to_cpup((((u32*)propdata)+1));
			if (lcd_debug_print_flag) {
				LCDPR("vbyone hw_filter=0x%x 0x%x\n",
					vx1_conf->hw_filter_time,
					vx1_conf->hw_filter_cnt);
			}
		}
		break;
	case LCD_P2P:
		if (pconf->lcd_control.p2p_config == NULL) {
			LCDERR("p2p_config is null\n");
			return -1;
		}
		p2p_conf = pconf->lcd_control.p2p_config;
		propdata = (char *)fdt_getprop(dt_addr, child_offset, "p2p_attr", NULL);
		if (propdata == NULL) {
			LCDERR("failed to get p2p_attr\n");
		} else {
			p2p_conf->p2p_type = be32_to_cpup((u32*)propdata);
			p2p_conf->lane_num = be32_to_cpup((((u32*)propdata)+1));
			p2p_conf->channel_sel0  = be32_to_cpup((((u32*)propdata)+2));
			p2p_conf->channel_sel1  = be32_to_cpup((((u32*)propdata)+3));
			p2p_conf->pn_swap  = be32_to_cpup((((u32*)propdata)+4));
			p2p_conf->bit_swap  = be32_to_cpup((((u32*)propdata)+5));
		}
		propdata = (char *)fdt_getprop(dt_addr, child_offset, "phy_attr", NULL);
		if (propdata == NULL) {
			if (lcd_debug_print_flag)
				LCDPR("failed to get phy_attr\n");
			p2p_conf->phy_vswing = 0;
			p2p_conf->phy_preem  = 0;
		} else {
			p2p_conf->phy_vswing = be32_to_cpup((u32*)propdata);
			p2p_conf->phy_preem  = be32_to_cpup((((u32*)propdata)+1));
			if (lcd_debug_print_flag) {
				LCDPR("set phy vswing=0x%x, preemphasis=0x%x\n",
					p2p_conf->phy_vswing, p2p_conf->phy_preem);
			}
		}
		if (!pconf->lcd_control.phy_cfg) {
			LCDERR("phy_cfg is null\n");
			return -1;
		}
		phy_conf = pconf->lcd_control.phy_cfg;
		phy_conf->lane_num = 12;
		phy_conf->vswing_level = p2p_conf->phy_vswing & 0xf;
		phy_conf->ext_pullup = (p2p_conf->phy_vswing >> 4) & 0x3;
		phy_conf->vswing = lcd_phy_vswing_level_to_value(pdrv, phy_conf->vswing_level);
		phy_conf->preem_level = p2p_conf->phy_preem;
		temp = lcd_phy_preem_level_to_value(pdrv, phy_conf->preem_level);
		for (i = 0; i < phy_conf->lane_num; i++) {
			phy_conf->lane[i].amp = 0;
			phy_conf->lane[i].preem = temp;
		}
		break;
	default:
		LCDERR("invalid lcd type\n");
		break;
	}

	lcd_config_timing_check(&pconf->lcd_timing.dft_timing);

	/* check power_step */
	lcd_power_load_from_dts(pconf, dt_addr, child_offset);

	propdata = (char *)fdt_getprop(dt_addr, child_offset, "backlight_index", NULL);
	if (propdata == NULL) {
		LCDPR("failed to get backlight_index\n");
		pconf->backlight_index = 0xff;
		return 0;
	} else {
		pconf->backlight_index = be32_to_cpup((u32*)propdata);
	}

	return 0;
}
#endif

static int lcd_config_load_from_bsp(struct lcd_config_s *pconf)
{
	struct ext_lcd_config_s *ext_lcd = NULL;
	char *panel_type = getenv("panel_type");
	unsigned int i;
	unsigned int temp;
	struct lcd_power_step_s *power_step;
	struct aml_lcd_drv_s *pdrv = aml_lcd_get_driver();
	struct lcd_detail_timing_s *ptiming = &pconf->lcd_timing.dft_timing;

	if (panel_type == NULL) {
		LCDERR("no panel_type, use default lcd config\n ");
		return -1;
	}
	for (i = 0 ; i < LCD_NUM_MAX ; i++) {
		ext_lcd = &ext_lcd_config[i];
		if (strcmp(ext_lcd->panel_type, panel_type) == 0)
			break ;
		if (strcmp(ext_lcd->panel_type, "invalid") == 0) {
			i = LCD_NUM_MAX;
			break;
		}
	}
	if (i >= LCD_NUM_MAX) {
		LCDERR("can't find %s, use default lcd config\n ", panel_type);
		return -1;
	}
	LCDPR("use panel_type=%s\n", panel_type);

	strncpy(pconf->lcd_basic.model_name, panel_type,
		sizeof(pconf->lcd_basic.model_name) - 1);
	pconf->lcd_basic.model_name[sizeof(pconf->lcd_basic.model_name) - 1]
		= '\0';
	pconf->lcd_basic.lcd_type = ext_lcd->lcd_type;
	pconf->lcd_basic.lcd_bits = ext_lcd->lcd_bits;

	ptiming->h_active = ext_lcd->h_active;
	ptiming->v_active = ext_lcd->v_active;
	ptiming->h_period = ext_lcd->h_period;
	ptiming->v_period = ext_lcd->v_period;

	ptiming->h_period_min = ptiming->h_period;
	ptiming->h_period_max = ptiming->h_period;
	ptiming->v_period_min = ptiming->v_period;
	ptiming->v_period_max = ptiming->v_period;
	ptiming->pclk_min = 0;
	ptiming->pclk_max = 0;

	ptiming->hsync_width = ext_lcd->hsync_width;
	ptiming->hsync_bp = ext_lcd->hsync_bp;
	ptiming->hsync_fp = ptiming->h_period - ptiming->h_active -
			ptiming->hsync_width - ptiming->hsync_bp;
	ptiming->hsync_pol   = ext_lcd->hsync_pol;
	ptiming->vsync_width = ext_lcd->vsync_width;
	ptiming->vsync_bp = ext_lcd->vsync_bp;
	ptiming->vsync_fp = ptiming->v_period - ptiming->v_active -
			ptiming->vsync_width - ptiming->vsync_bp;
	ptiming->vsync_pol = ext_lcd->vsync_pol;
	pconf->lcd_timing.pre_de_h    = 0;
	pconf->lcd_timing.pre_de_v    = 0;

	/* fr_adjust_type */
	temp = ext_lcd->customer_val_0;
	if (temp == Rsv_val)
		ptiming->fr_adjust_type = 0;
	else
		ptiming->fr_adjust_type = (unsigned char)temp;
	/* ss_level */
	temp = ext_lcd->customer_val_1;
	if (temp == Rsv_val) {
		pconf->lcd_timing.ss_level = 0;
	} else {
		pconf->lcd_timing.ss_level = temp & 0xff;
		pconf->lcd_timing.ss_freq = (temp >> 8) & 0xf;
		pconf->lcd_timing.ss_mode = (temp >> 12) & 0xf;
	}
	/* clk_auto_generate */
	temp = ext_lcd->customer_val_2;
	if (temp == Rsv_val)
		pconf->lcd_timing.pll_flag = 1;
	else
		pconf->lcd_timing.pll_flag = (unsigned char)temp;
	/* clk_freq */
	temp = ext_lcd->customer_val_3;
	if (temp == Rsv_val)
		ptiming->pixel_clk = 0;
	else
		ptiming->pixel_clk = temp;

	lcd_clk_frame_rate_init(ptiming);
	lcd_default_to_basic_timing_init_config(pconf);

	if (pconf->lcd_basic.lcd_type == LCD_VBYONE) {
		if (pconf->lcd_control.vbyone_config == NULL) {
			LCDERR("vbyone_config is null\n");
			return -1;
		}
		pconf->lcd_control.vbyone_config->lane_count = ext_lcd->lcd_spc_val0;
		pconf->lcd_control.vbyone_config->region_num = ext_lcd->lcd_spc_val1;
		pconf->lcd_control.vbyone_config->byte_mode  = ext_lcd->lcd_spc_val2;
		pconf->lcd_control.vbyone_config->color_fmt  = ext_lcd->lcd_spc_val3;
		if ((ext_lcd->lcd_spc_val4 == Rsv_val) ||
			(ext_lcd->lcd_spc_val5 == Rsv_val)) {
			pconf->lcd_control.vbyone_config->phy_vswing = VX1_PHY_VSWING_DFT;
			pconf->lcd_control.vbyone_config->phy_preem  = VX1_PHY_PREEM_DFT;
		} else {
			pconf->lcd_control.vbyone_config->phy_vswing = ext_lcd->lcd_spc_val4;
			pconf->lcd_control.vbyone_config->phy_preem  = ext_lcd->lcd_spc_val5;
		}
		pconf->lcd_control.phy_cfg->lane_num = 8;
		pconf->lcd_control.phy_cfg->vswing_level =
				pconf->lcd_control.vbyone_config->phy_vswing & 0xf;
		pconf->lcd_control.phy_cfg->ext_pullup =
				(pconf->lcd_control.vbyone_config->phy_vswing >> 4) & 0x3;
		pconf->lcd_control.phy_cfg->vswing =
			lcd_phy_vswing_level_to_value
			(pdrv, pconf->lcd_control.phy_cfg->vswing_level);
		pconf->lcd_control.phy_cfg->preem_level =
			pconf->lcd_control.vbyone_config->phy_preem;
		temp = lcd_phy_preem_level_to_value
			(pdrv, pconf->lcd_control.phy_cfg->preem_level);
		for (i = 0; i < pconf->lcd_control.phy_cfg->lane_num; i++) {
			pconf->lcd_control.phy_cfg->lane[i].amp = 0;
			pconf->lcd_control.phy_cfg->lane[i].preem = temp;
		}

		if ((ext_lcd->lcd_spc_val8 == Rsv_val) ||
			(ext_lcd->lcd_spc_val9 == Rsv_val)) {
			pconf->lcd_control.vbyone_config->hw_filter_time = 0;
			pconf->lcd_control.vbyone_config->hw_filter_cnt = 0;
		} else {
			pconf->lcd_control.vbyone_config->hw_filter_time = ext_lcd->lcd_spc_val8;
			pconf->lcd_control.vbyone_config->hw_filter_cnt  = ext_lcd->lcd_spc_val9;
		}

		pconf->lcd_control.vbyone_config->ctrl_flag = 0;
		pconf->lcd_control.vbyone_config->power_on_reset_delay = VX1_PWR_ON_RESET_DLY_DFT;
		pconf->lcd_control.vbyone_config->hpd_data_delay = VX1_HPD_DATA_DELAY_DFT;
		pconf->lcd_control.vbyone_config->cdr_training_hold = VX1_CDR_TRAINING_HOLD_DFT;
		pconf->lcd_control.vbyone_config->vx1_sw_filter_en = 0;
		pconf->lcd_control.vbyone_config->vx1_sw_filter_time = VX1_SW_FILTER_TIME_DFT;
		pconf->lcd_control.vbyone_config->vx1_sw_filter_cnt = VX1_SW_FILTER_CNT_DFT;
		pconf->lcd_control.vbyone_config->vx1_sw_filter_retry_cnt = VX1_SW_FILTER_RETRY_CNT_DFT;
		pconf->lcd_control.vbyone_config->vx1_sw_filter_retry_delay = VX1_SW_FILTER_RETRY_DLY_DFT;
		pconf->lcd_control.vbyone_config->vx1_sw_cdr_detect_time = VX1_SW_CDR_DET_TIME_DFT;
		pconf->lcd_control.vbyone_config->vx1_sw_cdr_detect_cnt = VX1_SW_CDR_DET_CNT_DFT;
		pconf->lcd_control.vbyone_config->vx1_sw_cdr_timeout_cnt = VX1_SW_CDR_TIMEOUT_CNT_DFT;
	} else if (pconf->lcd_basic.lcd_type == LCD_LVDS) {
		if (pconf->lcd_control.lvds_config == NULL) {
			LCDERR("lvds_config is null\n");
			return -1;
		}
		pconf->lcd_control.lvds_config->lvds_repack = ext_lcd->lcd_spc_val0;
		pconf->lcd_control.lvds_config->dual_port   = ext_lcd->lcd_spc_val1;
		pconf->lcd_control.lvds_config->pn_swap     = ext_lcd->lcd_spc_val2;
		pconf->lcd_control.lvds_config->port_swap   = ext_lcd->lcd_spc_val3;
		pconf->lcd_control.lvds_config->lane_reverse = ext_lcd->lcd_spc_val4;
		if ((ext_lcd->lcd_spc_val5 == Rsv_val) ||
			(ext_lcd->lcd_spc_val6 == Rsv_val)) {
			pconf->lcd_control.lvds_config->phy_vswing = LVDS_PHY_VSWING_DFT;
			pconf->lcd_control.lvds_config->phy_preem  = LVDS_PHY_PREEM_DFT;
		} else {
			pconf->lcd_control.lvds_config->phy_vswing = ext_lcd->lcd_spc_val5;
			pconf->lcd_control.lvds_config->phy_preem  = ext_lcd->lcd_spc_val6;
		}
		pconf->lcd_control.phy_cfg->lane_num = 12;
		pconf->lcd_control.phy_cfg->vswing_level =
			pconf->lcd_control.lvds_config->phy_vswing & 0xf;
		pconf->lcd_control.phy_cfg->ext_pullup =
			(pconf->lcd_control.lvds_config->phy_vswing >> 4) & 0x3;
		pconf->lcd_control.phy_cfg->vswing =
			lcd_phy_vswing_level_to_value
			(pdrv, pconf->lcd_control.phy_cfg->vswing_level);
		pconf->lcd_control.phy_cfg->preem_level =
			pconf->lcd_control.lvds_config->phy_preem;
		temp = lcd_phy_preem_level_to_value
			(pdrv, pconf->lcd_control.phy_cfg->preem_level);
		for (i = 0; i < pconf->lcd_control.phy_cfg->lane_num; i++) {
			pconf->lcd_control.phy_cfg->lane[i].amp = 0;
			pconf->lcd_control.phy_cfg->lane[i].preem = temp;
		}

		if ((ext_lcd->lcd_spc_val7 == Rsv_val) ||
			(ext_lcd->lcd_spc_val8 == Rsv_val)) {
			pconf->lcd_control.lvds_config->phy_clk_vswing = LVDS_PHY_CLK_VSWING_DFT;
			pconf->lcd_control.lvds_config->phy_clk_preem  = LVDS_PHY_CLK_PREEM_DFT;
		} else {
			pconf->lcd_control.lvds_config->phy_clk_vswing = ext_lcd->lcd_spc_val7;
			pconf->lcd_control.lvds_config->phy_clk_preem  = ext_lcd->lcd_spc_val8;
		}
	} else if (pconf->lcd_basic.lcd_type == LCD_MLVDS) {
		if (pconf->lcd_control.mlvds_config == NULL) {
			LCDERR("mlvds_config is null\n");
			return -1;
		}
		pconf->lcd_control.mlvds_config->channel_num = ext_lcd->lcd_spc_val0;
		pconf->lcd_control.mlvds_config->channel_sel0 = ext_lcd->lcd_spc_val1;
		pconf->lcd_control.mlvds_config->channel_sel1 = ext_lcd->lcd_spc_val2;
		pconf->lcd_control.mlvds_config->clk_phase  = ext_lcd->lcd_spc_val3;
		pconf->lcd_control.mlvds_config->pn_swap    = ext_lcd->lcd_spc_val4;
		pconf->lcd_control.mlvds_config->bit_swap   = ext_lcd->lcd_spc_val5;
		if ((ext_lcd->lcd_spc_val6 == Rsv_val) ||
			(ext_lcd->lcd_spc_val7 == Rsv_val)) {
			pconf->lcd_control.mlvds_config->phy_vswing = LVDS_PHY_VSWING_DFT;
			pconf->lcd_control.mlvds_config->phy_preem  = LVDS_PHY_PREEM_DFT;
		} else {
			pconf->lcd_control.mlvds_config->phy_vswing = ext_lcd->lcd_spc_val6;
			pconf->lcd_control.mlvds_config->phy_preem  = ext_lcd->lcd_spc_val7;
		}
		pconf->lcd_control.phy_cfg->lane_num = 12;
		pconf->lcd_control.phy_cfg->vswing_level =
			pconf->lcd_control.mlvds_config->phy_vswing & 0xf;
		pconf->lcd_control.phy_cfg->ext_pullup =
		    (pconf->lcd_control.mlvds_config->phy_vswing >> 4) & 0x3;
		pconf->lcd_control.phy_cfg->vswing =
			lcd_phy_vswing_level_to_value
			(pdrv, pconf->lcd_control.phy_cfg->vswing_level);
		pconf->lcd_control.phy_cfg->preem_level =
			pconf->lcd_control.mlvds_config->phy_preem;
		temp = lcd_phy_preem_level_to_value
			(pdrv, pconf->lcd_control.phy_cfg->preem_level);
		for (i = 0; i < pconf->lcd_control.phy_cfg->lane_num; i++) {
			pconf->lcd_control.phy_cfg->lane[i].amp = 0;
			pconf->lcd_control.phy_cfg->lane[i].preem = temp;
		}
	} else if (pconf->lcd_basic.lcd_type == LCD_P2P) {
		if (pconf->lcd_control.p2p_config == NULL) {
			LCDERR("p2p_config is null\n");
			return -1;
		}
		pconf->lcd_control.p2p_config->p2p_type = ext_lcd->lcd_spc_val0;
		pconf->lcd_control.p2p_config->lane_num = ext_lcd->lcd_spc_val1;
		pconf->lcd_control.p2p_config->channel_sel0 = ext_lcd->lcd_spc_val2;
		pconf->lcd_control.p2p_config->channel_sel1 = ext_lcd->lcd_spc_val3;
		pconf->lcd_control.p2p_config->pn_swap    = ext_lcd->lcd_spc_val4;
		pconf->lcd_control.p2p_config->bit_swap   = ext_lcd->lcd_spc_val5;
		if ((ext_lcd->lcd_spc_val6 == Rsv_val) ||
			(ext_lcd->lcd_spc_val7 == Rsv_val)) {
			pconf->lcd_control.p2p_config->phy_vswing = VX1_PHY_VSWING_DFT;
			pconf->lcd_control.p2p_config->phy_preem  = VX1_PHY_PREEM_DFT;
		} else {
			pconf->lcd_control.p2p_config->phy_vswing = ext_lcd->lcd_spc_val6;
			pconf->lcd_control.p2p_config->phy_preem  = ext_lcd->lcd_spc_val7;
		}
		pconf->lcd_control.phy_cfg->lane_num = 12;
		pconf->lcd_control.phy_cfg->vswing_level =
			pconf->lcd_control.p2p_config->phy_vswing & 0xf;
		pconf->lcd_control.phy_cfg->ext_pullup =
			(pconf->lcd_control.p2p_config->phy_vswing >> 4) & 0x3;
		pconf->lcd_control.phy_cfg->vswing =
			lcd_phy_vswing_level_to_value
			(pdrv, pconf->lcd_control.phy_cfg->vswing_level);
		pconf->lcd_control.phy_cfg->preem_level =
			pconf->lcd_control.p2p_config->phy_preem;
		temp = lcd_phy_preem_level_to_value
			(pdrv, pconf->lcd_control.phy_cfg->preem_level);
		for (i = 0; i < pconf->lcd_control.phy_cfg->lane_num; i++) {
			pconf->lcd_control.phy_cfg->lane[i].amp = 0;
			pconf->lcd_control.phy_cfg->lane[i].preem = temp;
		}
	} else if (pconf->lcd_basic.lcd_type == LCD_TTL) {
		LCDERR("unsupport lcd_type: %d\n", pconf->lcd_basic.lcd_type);
	}

	lcd_config_timing_check(&pconf->lcd_timing.dft_timing);

	i = 0;
	while (i < LCD_PWR_STEP_MAX) {
		power_step = &ext_lcd->power_on_step[i];
		if (lcd_debug_print_flag) {
			LCDPR("power_on: step %d: type=%d, index=%d, value=%d, delay=%d\n",
				i, power_step->type, power_step->index,
				power_step->value, power_step->delay);
		}
		pconf->lcd_power->power_on_step[i].type = power_step->type;
		pconf->lcd_power->power_on_step[i].index = power_step->index;
		pconf->lcd_power->power_on_step[i].value = power_step->value;
		pconf->lcd_power->power_on_step[i].delay = power_step->delay;
		if (power_step->type >= LCD_POWER_TYPE_MAX)
			break;
		i++;
	}

	i = 0;
	while (i < LCD_PWR_STEP_MAX) {
		power_step = &ext_lcd->power_off_step[i];
		if (lcd_debug_print_flag) {
			LCDPR("power_off: step %d: type=%d, index=%d, value=%d, delay=%d\n",
				i, power_step->type, power_step->index,
				power_step->value, power_step->delay);
		}
		pconf->lcd_power->power_off_step[i].type = power_step->type;
		pconf->lcd_power->power_off_step[i].index = power_step->index;
		pconf->lcd_power->power_off_step[i].value = power_step->value;
		pconf->lcd_power->power_off_step[i].delay = power_step->delay;
		if (power_step->type >= LCD_POWER_TYPE_MAX)
			break;
		i++;
	}

	return 0;
}

static int lcd_config_load_from_unifykey_v2(struct lcd_config_s *pconf,
					    unsigned char *p,
					    unsigned int key_len,
					    unsigned int offset)
{
	struct aml_lcd_unifykey_header_s *header;
	struct phy_config_s *phy_cfg = pconf->lcd_control.phy_cfg;
	unsigned int len, size;
	int i, ret;

	header = (struct aml_lcd_unifykey_header_s *)p;
	LCDPR("unifykey version: 0x%04x\n", header->version);
	if (lcd_debug_print_flag) {
		LCDPR("unifykey header:\n");
		LCDPR("crc32             = 0x%08x\n", header->crc32);
		LCDPR("data_len          = %d\n", header->data_len);
		LCDPR("block_next_flag   = %d\n", header->block_next_flag);
		LCDPR("block_cur_size    = %d\n", header->block_cur_size);
	}

	/* step 2: check lcd parameters */
	len = offset + header->block_cur_size;
	ret = aml_lcd_unifykey_len_check(key_len, len);
	if (ret < 0) {
		LCDERR("unifykey parameters length is incorrect\n");
		return -1;
	}

	/*phy 356byte*/
	phy_cfg->flag = (*(p + LCD_UKEY_PHY_ATTR_FLAG) |
		((*(p + LCD_UKEY_PHY_ATTR_FLAG + 1)) << 8) |
		((*(p + LCD_UKEY_PHY_ATTR_FLAG + 2)) << 16) |
		((*(p + LCD_UKEY_PHY_ATTR_FLAG + 3)) << 24));

	if (phy_cfg->flag & (1 << 1)) {
		phy_cfg->vcm = (*(p + LCD_UKEY_PHY_ATTR_1) |
				*(p + LCD_UKEY_PHY_ATTR_1 + 1) << 8);
	}
	if (phy_cfg->flag & (1 << 2)) {
		phy_cfg->ref_bias = (*(p + LCD_UKEY_PHY_ATTR_2) |
				     *(p + LCD_UKEY_PHY_ATTR_2 + 1) << 8);
	}
	if (phy_cfg->flag & (1 << 3)) {
		phy_cfg->odt = (*(p + LCD_UKEY_PHY_ATTR_3) |
				*(p + LCD_UKEY_PHY_ATTR_3 + 1) << 8);
	}
	if (lcd_debug_print_flag) {
		LCDPR("%s: vcm=0x%x, ref_bias=0x%x, odt=0x%x\n",
		      __func__, phy_cfg->vcm, phy_cfg->ref_bias,
		      phy_cfg->odt);
	}

	if (phy_cfg->flag & (1 << 12)) {
		for (i = 0; i < CH_LANE_MAX; i++) {
			phy_cfg->lane[i].preem =
				*(p + LCD_UKEY_PHY_LANE_CTRL + 4 * i) |
				(*(p + LCD_UKEY_PHY_LANE_CTRL + 4 * i + 1) << 8);
			if (lcd_debug_print_flag) {
				LCDPR("%s: lane[%d]: preem=0x%x\n",
				      __func__, i,
				      phy_cfg->lane[i].preem);
			}
		}
	}

	if (phy_cfg->flag & (1 << 13)) {
		for (i = 0; i < phy_cfg->lane_num; i++) {
			phy_cfg->lane[i].amp =
				*(p + LCD_UKEY_PHY_LANE_CTRL + 4 * i + 2) |
				(*(p + LCD_UKEY_PHY_LANE_CTRL + 4 * i + 3) << 8);
			if (lcd_debug_print_flag) {
				LCDPR("%s: lane[%d]: amp=0x%x\n",
				      __func__, i,
				      phy_cfg->lane[i].amp);
			}
		}
	}

	size = LCD_UKEY_CUS_CTRL_ATTR_FLAG;
	lcd_cus_ctrl_load_from_unifykey(pconf, (p + size), (key_len - size));

	return 0;
}

static int lcd_config_load_from_unifykey(struct lcd_config_s *pconf)
{
	unsigned char *para;
	int key_len, len;
	unsigned char *p;
	const char *str;
	struct aml_lcd_unifykey_header_s *lcd_header;
	struct aml_lcd_drv_s *pdrv = aml_lcd_get_driver();
	struct lcd_detail_timing_s *ptiming = &pconf->lcd_timing.dft_timing;
	struct lvds_config_s *lvdsconf = pconf->lcd_control.lvds_config;
	struct vbyone_config_s *vx1_conf = pconf->lcd_control.vbyone_config;
	struct mlvds_config_s *mlvds_conf = pconf->lcd_control.mlvds_config;
	struct p2p_config_s *p2p_conf = pconf->lcd_control.p2p_config;
	struct phy_config_s *phy_cfg = pconf->lcd_control.phy_cfg;
	int i, ret;
	unsigned int temp;

	ret = aml_lcd_unifykey_get_size("lcd", &key_len);
	if (ret)
		return -1;

	para = (unsigned char *)malloc(sizeof(unsigned char) * key_len);
	if (!para) {
		LCDERR("%s: Not enough memory\n", __func__);
		return -1;
	}
	memset(para, 0, (sizeof(unsigned char) * key_len));

	ret = aml_lcd_unifykey_get("lcd", para, key_len);
	if (ret) {
		free(para);
		return -1;
	}

	/* step 1: check header */
	lcd_header = (struct aml_lcd_unifykey_header_s *)para;
	LCDPR("unifykey version: 0x%04x\n", lcd_header->version);
	len = LCD_UKEY_DATA_LEN_V1; /*10+36+18+31+20*/
	if (lcd_debug_print_flag) {
		LCDPR("unifykey header:\n");
		LCDPR("crc32             = 0x%08x\n", lcd_header->crc32);
		LCDPR("data_len          = %d\n", lcd_header->data_len);
		LCDPR("block_next_flag   = %d\n", lcd_header->block_next_flag);
		LCDPR("block_cur_size    = 0x%04x\n", lcd_header->block_cur_size);
	}

	/* step 2: check lcd parameters */
	ret = aml_lcd_unifykey_len_check(key_len, len);
	if (ret) {
		LCDERR("unifykey parameters length is incorrect\n");
		free(para);
		return -1;
	}

	/* basic: 36byte */
	p = para;
	str = (const char *)(p + LCD_UKEY_HEAD_SIZE);
	strncpy(pconf->lcd_basic.model_name, str,
		sizeof(pconf->lcd_basic.model_name) - 1);
	pconf->lcd_basic.model_name[sizeof(pconf->lcd_basic.model_name) - 1]
		= '\0';
	temp = *(p + LCD_UKEY_INTERFACE);
	pconf->lcd_basic.lcd_type = temp & 0x3f;
	pconf->lcd_basic.config_check = (temp >> 6) & 0x3;
	temp = *(p + LCD_UKEY_LCD_BITS_CFMT);
	pconf->lcd_basic.lcd_bits = temp & 0x3f;
	pconf->lcd_basic.screen_width = (*(p + LCD_UKEY_SCREEN_WIDTH) |
		((*(p + LCD_UKEY_SCREEN_WIDTH + 1)) << 8));
	pconf->lcd_basic.screen_height = (*(p + LCD_UKEY_SCREEN_HEIGHT) |
		((*(p + LCD_UKEY_SCREEN_HEIGHT + 1)) << 8));

	/* timing: 18byte */
	ptiming->h_active = (*(p + LCD_UKEY_H_ACTIVE) |
		((*(p + LCD_UKEY_H_ACTIVE + 1)) << 8));
	ptiming->v_active = (*(p + LCD_UKEY_V_ACTIVE)) |
		((*(p + LCD_UKEY_V_ACTIVE + 1)) << 8);
	ptiming->h_period = (*(p + LCD_UKEY_H_PERIOD)) |
		((*(p + LCD_UKEY_H_PERIOD + 1)) << 8);
	ptiming->v_period = (*(p + LCD_UKEY_V_PERIOD)) |
		((*(p + LCD_UKEY_V_PERIOD + 1)) << 8);
	temp = *(unsigned short *)(p + LCD_UKEY_HS_WIDTH_POL);
	ptiming->hsync_width = temp & 0xfff;
	ptiming->hsync_pol = (temp >> 12) & 0xf;
	ptiming->hsync_bp = (*(p + LCD_UKEY_HS_BP) |
		((*(p + LCD_UKEY_HS_BP + 1)) << 8));
	ptiming->hsync_fp = ptiming->h_period - ptiming->h_active -
			ptiming->hsync_width - ptiming->hsync_bp;
	temp = *(unsigned short *)(p + LCD_UKEY_VS_WIDTH_POL);
	ptiming->vsync_width = temp & 0xfff;
	ptiming->vsync_pol = (temp >> 12) & 0xf;
	ptiming->vsync_bp = (*(p + LCD_UKEY_VS_BP) |
		((*(p + LCD_UKEY_VS_BP + 1)) << 8));
	ptiming->vsync_fp = ptiming->v_period - ptiming->v_active -
			ptiming->vsync_width - ptiming->vsync_bp;
	pconf->lcd_timing.pre_de_h = *(p + LCD_UKEY_PRE_DE_H);
	pconf->lcd_timing.pre_de_v = *(p + LCD_UKEY_PRE_DE_V);

	/* customer: 31byte */
	ptiming->fr_adjust_type = *(p + LCD_UKEY_FR_ADJ_TYPE);
	pconf->lcd_timing.ss_level = *(p + LCD_UKEY_SS_LEVEL);
	pconf->lcd_timing.pll_flag = *(p + LCD_UKEY_CLK_AUTO_GEN);
	ptiming->pixel_clk = (*(p + LCD_UKEY_PCLK) |
		((*(p + LCD_UKEY_PCLK + 1)) << 8) |
		((*(p + LCD_UKEY_PCLK + 2)) << 16) |
		((*(p + LCD_UKEY_PCLK + 3)) << 24));
	ptiming->h_period_min = (*(p + LCD_UKEY_H_PERIOD_MIN) |
		((*(p + LCD_UKEY_H_PERIOD_MIN + 1)) << 8));
	ptiming->h_period_max = (*(p + LCD_UKEY_H_PERIOD_MAX) |
		((*(p + LCD_UKEY_H_PERIOD_MAX + 1)) << 8));
	ptiming->v_period_min = (*(p + LCD_UKEY_V_PERIOD_MIN) |
		((*(p + LCD_UKEY_V_PERIOD_MIN + 1)) << 8));
	ptiming->v_period_max = (*(p + LCD_UKEY_V_PERIOD_MAX) |
		((*(p + LCD_UKEY_V_PERIOD_MAX + 1)) << 8));
	ptiming->pclk_min = (*(p + LCD_UKEY_PCLK_MIN) |
		((*(p + LCD_UKEY_PCLK_MIN + 1)) << 8) |
		((*(p + LCD_UKEY_PCLK_MIN + 2)) << 16) |
		((*(p + LCD_UKEY_PCLK_MIN + 3)) << 24));
	ptiming->pclk_max = (*(p + LCD_UKEY_PCLK_MAX) |
		((*(p + LCD_UKEY_PCLK_MAX + 1)) << 8) |
		((*(p + LCD_UKEY_PCLK_MAX + 2)) << 16) |
		((*(p + LCD_UKEY_PCLK_MAX + 3)) << 24));
	pconf->customer_pinmux = *(p + LCD_UKEY_CUST_PINMUX);
	pconf->fr_auto_cus = *(p + LCD_UKEY_FR_AUTO_CUS);
	ptiming->frame_rate_min = *(p + LCD_UKEY_FRAME_RATE_MIN);
	ptiming->frame_rate_max = *(p + LCD_UKEY_FRAME_RATE_MAX);

	lcd_clk_frame_rate_init(ptiming);
	lcd_default_to_basic_timing_init_config(pconf);

	/* interface: 20byte */
	if (pconf->lcd_basic.lcd_type == LCD_VBYONE) {
		if (pconf->lcd_control.vbyone_config == NULL) {
			LCDERR("vbyone_config is null\n");
			free(para);
			return -1;
		}
		vx1_conf->lane_count = (*(p + LCD_UKEY_IF_ATTR_0) |
			((*(p + LCD_UKEY_IF_ATTR_0 + 1)) << 8)) & 0xff;
		vx1_conf->region_num = (*(p + LCD_UKEY_IF_ATTR_1) |
			((*(p + LCD_UKEY_IF_ATTR_1 + 1)) << 8)) & 0xff;
		vx1_conf->byte_mode = (*(p + LCD_UKEY_IF_ATTR_2) |
			((*(p + LCD_UKEY_IF_ATTR_2 + 1)) << 8)) & 0xff;
		vx1_conf->color_fmt = (*(p + LCD_UKEY_IF_ATTR_3) |
			((*(p + LCD_UKEY_IF_ATTR_3 + 1)) << 8)) & 0xff;
		vx1_conf->phy_vswing = (*(p + LCD_UKEY_IF_ATTR_4) |
			((*(p + LCD_UKEY_IF_ATTR_4 + 1)) << 8)) & 0xff;
		vx1_conf->phy_preem = (*(p + LCD_UKEY_IF_ATTR_5) |
			((*(p + LCD_UKEY_IF_ATTR_5 + 1)) << 8)) & 0xff;
		vx1_conf->hw_filter_time = *(p + LCD_UKEY_IF_ATTR_8) |
			((*(p + LCD_UKEY_IF_ATTR_8 + 1)) << 8);
		vx1_conf->hw_filter_cnt = *(p + LCD_UKEY_IF_ATTR_9) |
			((*(p + LCD_UKEY_IF_ATTR_9 + 1)) << 8);

		phy_cfg->lane_num = 8;
		phy_cfg->vswing_level = vx1_conf->phy_vswing & 0xf;
		phy_cfg->ext_pullup = (vx1_conf->phy_vswing >> 4) & 0x3;
		phy_cfg->vswing = lcd_phy_vswing_level_to_value(pdrv, phy_cfg->vswing_level);
		phy_cfg->preem_level = vx1_conf->phy_preem;
		temp = lcd_phy_preem_level_to_value(pdrv, phy_cfg->preem_level);
		for (i = 0; i < phy_cfg->lane_num; i++) {
			phy_cfg->lane[i].amp = 0;
			phy_cfg->lane[i].preem = temp;
		}
	} else if (pconf->lcd_basic.lcd_type == LCD_LVDS) {
		if (pconf->lcd_control.lvds_config == NULL) {
			LCDERR("lvds_config is null\n");
			free(para);
			return -1;
		}
		lvdsconf->lvds_repack = (*(p + LCD_UKEY_IF_ATTR_0) |
			((*(p + LCD_UKEY_IF_ATTR_0 + 1)) << 8)) & 0xff;
		lvdsconf->dual_port = (*(p + LCD_UKEY_IF_ATTR_1) |
			((*(p + LCD_UKEY_IF_ATTR_1 + 1)) << 8)) & 0xff;
		lvdsconf->pn_swap = (*(p + LCD_UKEY_IF_ATTR_2) |
			((*(p + LCD_UKEY_IF_ATTR_2 + 1)) << 8)) & 0xff;
		lvdsconf->port_swap = (*(p + LCD_UKEY_IF_ATTR_3) |
			((*(p + LCD_UKEY_IF_ATTR_3 + 1)) << 8)) & 0xff;
		lvdsconf->phy_vswing = (*(p + LCD_UKEY_IF_ATTR_4) |
			((*(p + LCD_UKEY_IF_ATTR_4 + 1)) << 8)) & 0xff;
		lvdsconf->phy_preem = (*(p + LCD_UKEY_IF_ATTR_5) |
			((*(p + LCD_UKEY_IF_ATTR_5 + 1)) << 8)) & 0xff;
		lvdsconf->phy_clk_vswing = (*(p + LCD_UKEY_IF_ATTR_6) |
			((*(p + LCD_UKEY_IF_ATTR_6 + 1)) << 8)) & 0xff;
		lvdsconf->phy_clk_preem = (*(p + LCD_UKEY_IF_ATTR_7) |
			((*(p + LCD_UKEY_IF_ATTR_7 + 1)) << 8)) & 0xff;
		lvdsconf->lane_reverse = 0;

		phy_cfg->lane_num = 12;
		phy_cfg->vswing_level = lvdsconf->phy_vswing & 0xf;
		phy_cfg->ext_pullup = (lvdsconf->phy_vswing >> 4) & 0x3;
		phy_cfg->vswing = lcd_phy_vswing_level_to_value(pdrv, phy_cfg->vswing_level);
		phy_cfg->preem_level = lvdsconf->phy_preem;
		temp = lcd_phy_preem_level_to_value(pdrv, phy_cfg->preem_level);
		for (i = 0; i < phy_cfg->lane_num; i++) {
			phy_cfg->lane[i].amp = 0;
			phy_cfg->lane[i].preem = temp;
		}
	} else if (pconf->lcd_basic.lcd_type == LCD_MLVDS) {
		if (pconf->lcd_control.mlvds_config == NULL) {
			LCDERR("mlvds_config is null\n");
			free(para);
			return -1;
		}
		mlvds_conf->channel_num = (*(p + LCD_UKEY_IF_ATTR_0) |
			((*(p + LCD_UKEY_IF_ATTR_0 + 1)) << 8)) & 0xff;
		mlvds_conf->channel_sel0 = (*(p + LCD_UKEY_IF_ATTR_1) |
			((*(p + LCD_UKEY_IF_ATTR_1 + 1)) << 8) |
			((*(p + LCD_UKEY_IF_ATTR_2)) << 16) |
			((*(p + LCD_UKEY_IF_ATTR_2 + 1)) << 24));
		mlvds_conf->channel_sel1 = (*(p + LCD_UKEY_IF_ATTR_3) |
			((*(p + LCD_UKEY_IF_ATTR_3 + 1)) << 8) |
			((*(p + LCD_UKEY_IF_ATTR_4)) << 16) |
			((*(p + LCD_UKEY_IF_ATTR_4 + 1)) << 24));
		mlvds_conf->clk_phase = (*(p + LCD_UKEY_IF_ATTR_5) |
			((*(p + LCD_UKEY_IF_ATTR_5 + 1)) << 8));
		mlvds_conf->pn_swap = (*(p + LCD_UKEY_IF_ATTR_6) |
			((*(p + LCD_UKEY_IF_ATTR_6 + 1)) << 8)) & 0xff;
		mlvds_conf->bit_swap = (*(p + LCD_UKEY_IF_ATTR_7) |
			((*(p + LCD_UKEY_IF_ATTR_7 + 1)) << 8)) & 0xff;
		mlvds_conf->phy_vswing = (*(p + LCD_UKEY_IF_ATTR_8) |
			((*(p + LCD_UKEY_IF_ATTR_8 + 1)) << 8)) & 0xff;
		mlvds_conf->phy_preem = (*(p + LCD_UKEY_IF_ATTR_9) |
			((*(p + LCD_UKEY_IF_ATTR_9 + 1)) << 8)) & 0xff;

		phy_cfg->lane_num = 12;
		phy_cfg->vswing_level = mlvds_conf->phy_vswing & 0xf;
		phy_cfg->ext_pullup = (mlvds_conf->phy_vswing >> 4) & 0x3;
		phy_cfg->vswing = lcd_phy_vswing_level_to_value(pdrv, phy_cfg->vswing_level);
		phy_cfg->preem_level = mlvds_conf->phy_preem;
		temp = lcd_phy_preem_level_to_value(pdrv, phy_cfg->preem_level);
		for (i = 0; i < phy_cfg->lane_num; i++) {
			phy_cfg->lane[i].amp = 0;
			phy_cfg->lane[i].preem = temp;
		}
	} else if (pconf->lcd_basic.lcd_type == LCD_P2P) {
		if (pconf->lcd_control.p2p_config == NULL) {
			LCDERR("p2p_config is null\n");
			free(para);
			return -1;
		}
		p2p_conf->p2p_type = (*(p + LCD_UKEY_IF_ATTR_0) |
			((*(p + LCD_UKEY_IF_ATTR_0 + 1)) << 8));
		p2p_conf->lane_num = (*(p + LCD_UKEY_IF_ATTR_1) |
			((*(p + LCD_UKEY_IF_ATTR_1 + 1)) << 8));
		p2p_conf->channel_sel0 = (*(p + LCD_UKEY_IF_ATTR_2) |
			((*(p + LCD_UKEY_IF_ATTR_2 + 1)) << 8) |
			(*(p + LCD_UKEY_IF_ATTR_3) << 16) |
			((*(p + LCD_UKEY_IF_ATTR_3 + 1)) << 24));
		p2p_conf->channel_sel1 = (*(p + LCD_UKEY_IF_ATTR_4) |
			((*(p + LCD_UKEY_IF_ATTR_4 + 1)) << 8) |
			(*(p + LCD_UKEY_IF_ATTR_5) << 16) |
			((*(p + LCD_UKEY_IF_ATTR_5 + 1)) << 24));
		p2p_conf->pn_swap = (*(p + LCD_UKEY_IF_ATTR_6) |
			((*(p + LCD_UKEY_IF_ATTR_6 + 1)) << 8));
		p2p_conf->bit_swap = (*(p + LCD_UKEY_IF_ATTR_7) |
			((*(p + LCD_UKEY_IF_ATTR_7 + 1)) << 8));
		p2p_conf->phy_vswing = (*(p + LCD_UKEY_IF_ATTR_8) |
			((*(p + LCD_UKEY_IF_ATTR_8 + 1)) << 8));
		p2p_conf->phy_preem = (*(p + LCD_UKEY_IF_ATTR_9) |
			((*(p + LCD_UKEY_IF_ATTR_9 + 1)) << 8));

		phy_cfg->lane_num = 12;
		phy_cfg->vswing_level = p2p_conf->phy_vswing & 0xf;
		phy_cfg->ext_pullup = (p2p_conf->phy_vswing >> 4) & 0x3;
		phy_cfg->vswing = lcd_phy_vswing_level_to_value(pdrv, phy_cfg->vswing_level);
		phy_cfg->preem_level = p2p_conf->phy_preem;
		temp = lcd_phy_preem_level_to_value(pdrv, phy_cfg->preem_level);
		for (i = 0; i < phy_cfg->lane_num; i++) {
			phy_cfg->lane[i].amp = 0;
			phy_cfg->lane[i].preem = temp;
		}
	} else {
		LCDERR("unsupport lcd_type: %d\n", pconf->lcd_basic.lcd_type);
	}

	if (pconf->lcd_basic.lcd_type == LCD_VBYONE) {
		vx1_conf->ctrl_flag = 0;
		vx1_conf->power_on_reset_delay = VX1_PWR_ON_RESET_DLY_DFT;
		vx1_conf->hpd_data_delay = VX1_HPD_DATA_DELAY_DFT;
		vx1_conf->cdr_training_hold = VX1_CDR_TRAINING_HOLD_DFT;
		vx1_conf->vx1_sw_filter_en = 0;
		vx1_conf->vx1_sw_filter_time = VX1_SW_FILTER_TIME_DFT;
		vx1_conf->vx1_sw_filter_cnt = VX1_SW_FILTER_CNT_DFT;
		vx1_conf->vx1_sw_filter_retry_cnt = VX1_SW_FILTER_RETRY_CNT_DFT;
		vx1_conf->vx1_sw_filter_retry_delay = VX1_SW_FILTER_RETRY_DLY_DFT;
		vx1_conf->vx1_sw_cdr_detect_time = VX1_SW_CDR_DET_TIME_DFT;
		vx1_conf->vx1_sw_cdr_detect_cnt = VX1_SW_CDR_DET_CNT_DFT;
		vx1_conf->vx1_sw_cdr_timeout_cnt = VX1_SW_CDR_TIMEOUT_CNT_DFT;
	}

	lcd_config_timing_check(&pconf->lcd_timing.dft_timing);

	/* step 3: check power sequence */
	ret = lcd_power_load_from_unifykey(pconf, para, key_len, len);
	if (ret < 0) {
		free(para);
		return -1;
	}

	if (lcd_header->version == 2) {
		p = para + lcd_header->block_cur_size;
		lcd_config_load_from_unifykey_v2(pconf, p, key_len, lcd_header->block_cur_size);
	}

	free(para);
	return 0;
}

/* ************************************************** *
 * vout server api
 * **************************************************
 */
static void lcd_list_support_mode(void)
{
	struct aml_lcd_drv_s *pdrv = aml_lcd_get_driver();
	struct lcd_vmode_list_s *temp_list;
	unsigned int frame_rate;
	int i;

	temp_list = pdrv->vmode_mgr.vmode_list_header;
	while (temp_list) {
		if (!temp_list->info)
			continue;

		for (i = 0; i < LCD_DURATION_MAX; i++) {
			frame_rate = temp_list->info->duration[i].frame_rate;
			if (frame_rate == 0)
				break;
			printf("%s%dhz\n", temp_list->info->name, frame_rate);
		}
		temp_list = temp_list->next;
	}
}

static int lcd_outputmode_is_matched(char *mode)
{
	struct aml_lcd_drv_s *pdrv = aml_lcd_get_driver();
	struct lcd_vmode_list_s *temp_list;
	char mode_name[48];
	int i;

	if (!mode)
		return -1;
	if (lcd_debug_print_flag)
		LCDPR("%s: outputmode=%s\n", __func__, mode);

	temp_list = pdrv->vmode_mgr.vmode_list_header;
	while (temp_list) {
		for (i = 0; i < LCD_DURATION_MAX; i++) {
			if (temp_list->info->duration[i].frame_rate == 0)
				break;
			memset(mode_name, 0, 48);
			sprintf(mode_name, "%s%dhz", temp_list->info->name,
					temp_list->info->duration[i].frame_rate);
			if (lcd_debug_print_flag)
				LCDPR("%s: %s\n", __func__, mode_name);
			if (strcmp(mode, mode_name))
				continue;

			if (lcd_debug_print_flag) {
				LCDPR("%s: match %s, %dx%d@%dhz\n",
					__func__, temp_list->info->name,
					temp_list->info->width, temp_list->info->height,
					temp_list->info->duration[i].frame_rate);
			}
			temp_list->info->duration_index = i;
			if (pdrv->vmode_mgr.cur_vmode_info != temp_list->info)
				pdrv->vmode_mgr.next_vmode_info = temp_list->info;
			return 0;
		}
		temp_list = temp_list->next;
	}

	LCDERR("%s: invalid mode: %s\n", __func__, mode);
	return -1;
}

static void lcd_vmode_update(struct lcd_config_s *pconf)
{
	struct aml_lcd_drv_s *pdrv = aml_lcd_get_driver();
	struct lcd_detail_timing_s *ptiming;
	unsigned int pre_pclk;
	int dur_index;

	/* clear clk flag */
	pconf->lcd_timing.clk_change &= ~(LCD_CLK_PLL_RESET);
	if (pdrv->vmode_mgr.next_vmode_info) {
		pre_pclk = pconf->lcd_timing.base_timing.pixel_clk;
		pdrv->vmode_mgr.cur_vmode_info = pdrv->vmode_mgr.next_vmode_info;
		pdrv->vmode_mgr.next_vmode_info = NULL;

		pconf->std_duration = pdrv->vmode_mgr.cur_vmode_info->duration;
		ptiming = pdrv->vmode_mgr.cur_vmode_info->dft_timing;
		memcpy(&pconf->lcd_timing.base_timing, ptiming,
			sizeof(struct lcd_detail_timing_s));
		lcd_cus_ctrl_config_update(pconf, (void *)ptiming, LCD_CUS_CTRL_SEL_TIMMING);

		//update base_timing to act_timing
		lcd_enc_timing_init_config(pconf);
		if (pconf->lcd_timing.base_timing.pixel_clk != pre_pclk)
			pconf->lcd_timing.clk_change |= LCD_CLK_PLL_RESET;
	}

	if (!pdrv->vmode_mgr.cur_vmode_info || !pconf->std_duration) {
		LCDERR("%s: cur_vmode_info or std_duration is null\n", __func__);
		return;
	}
	dur_index = pdrv->vmode_mgr.cur_vmode_info->duration_index;

	pconf->lcd_timing.act_timing.sync_duration_num =
		pconf->std_duration[dur_index].duration_num;
	pconf->lcd_timing.act_timing.sync_duration_den =
		pconf->std_duration[dur_index].duration_den;
	pconf->lcd_timing.act_timing.frac = pconf->std_duration[dur_index].frac;
	pconf->lcd_timing.act_timing.frame_rate = pconf->std_duration[dur_index].frame_rate;
	lcd_frame_rate_change(pconf);

	if (lcd_debug_print_flag) {
		LCDPR("%s: %dx%d, duration=%d:%d, dur_index=%d, clk_change=0x%x\n",
			__func__,
			pconf->lcd_timing.act_timing.h_active,
			pconf->lcd_timing.act_timing.v_active,
			pconf->lcd_timing.act_timing.sync_duration_num,
			pconf->lcd_timing.act_timing.sync_duration_den,
			dur_index, pconf->lcd_timing.clk_change);
	}
}

static int lcd_config_valid(char *mode)
{
	struct aml_lcd_drv_s *lcd_drv = aml_lcd_get_driver();
	struct lcd_config_s *pconf = lcd_drv->lcd_config;
	int ret;

	ret = lcd_outputmode_is_matched(mode);
	if (ret)
		return -1;

	/* update clk & timing config */
	lcd_vmode_update(pconf);
	lcd_tv_config_update(pconf);
	lcd_clk_generate_parameter(pconf);

	return 0;
}

static void lcd_config_init(struct lcd_config_s *pconf)
{
	char *mode_str;

	lcd_enc_timing_init_config(pconf);
	pconf->lcd_timing.clk_change = 0; /* clear clk_change flag */

	lcd_output_vmode_init(pconf);
	//assign default outputmode for multi timing
	mode_str = getenv("outputmode");
	if (mode_str)
		lcd_config_valid(mode_str);
}

int get_lcd_tv_config(char *dt_addr, int load_id)
{
	struct aml_lcd_drv_s *lcd_drv = aml_lcd_get_driver();
	int ret = 0;

	strcpy(lcd_drv->version, LCD_DRV_VERSION);
	lcd_drv->list_support_mode = lcd_list_support_mode;
	lcd_drv->outputmode_check = lcd_outputmode_is_matched;
	lcd_drv->config_valid = lcd_config_valid;
	lcd_drv->driver_init_pre = lcd_tv_driver_init_pre;
	lcd_drv->driver_init = lcd_tv_driver_init;
	lcd_drv->driver_disable = lcd_tv_driver_disable;

	if (load_id & 0x10) { /* unifykey */
		ret = lcd_config_load_from_unifykey(lcd_drv->lcd_config);
		ret = lcd_pinmux_load_config(dt_addr, lcd_drv->lcd_config);
	} else if (load_id & 0x1) { /* dts */
#ifdef CONFIG_OF_LIBFDT
		ret = lcd_config_load_from_dts(dt_addr, lcd_drv->lcd_config);
#endif
		ret = lcd_pinmux_load_config(dt_addr, lcd_drv->lcd_config);
	} else { /* bsp */
		ret = lcd_config_load_from_bsp(lcd_drv->lcd_config);
		ret = lcd_pinmux_load_config(dt_addr, lcd_drv->lcd_config);
	}
	if (ret)
		return -1;

	lcd_config_load_print(lcd_drv->lcd_config);
	lcd_config_init(lcd_drv->lcd_config);
	lcd_drv->probe_done = 1;

	return 0;
}


