/* SPDX-License-Identifier: (GPL-2.0+ OR MIT) */
/*
 * drivers/display/lcd/lcd_tablet/lcd_tablet.c
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
#include <amlogic/aml_lcd.h>
#include "../aml_lcd_reg.h"
#include "../aml_lcd_common.h"
#include "lcd_tablet.h"
#include "mipi_dsi_util.h"

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
	LCDPR("clk = %dHz\n", ptiming->pixel_clk);

	if (pconf->lcd_basic.lcd_type == LCD_TTL) {
		LCDPR("clk_pol = %d\n", pconf->lcd_control.ttl_config->clk_pol);
		LCDPR("sync_valid = %d\n", pconf->lcd_control.ttl_config->sync_valid);
		LCDPR("swap_ctrl = %d\n", pconf->lcd_control.ttl_config->swap_ctrl);
	} else if (pconf->lcd_basic.lcd_type == LCD_LVDS) {
		LCDPR("lvds_repack = %d\n", pconf->lcd_control.lvds_config->lvds_repack);
		LCDPR("pn_swap = %d\n", pconf->lcd_control.lvds_config->pn_swap);
		LCDPR("dual_port = %d\n", pconf->lcd_control.lvds_config->dual_port);
		LCDPR("port_swap = %d\n", pconf->lcd_control.lvds_config->port_swap);
		LCDPR("lane_reverse = %d\n", pconf->lcd_control.lvds_config->lane_reverse);
	} else if (pconf->lcd_basic.lcd_type == LCD_VBYONE) {
		LCDPR("lane_count = %d\n", pconf->lcd_control.vbyone_config->lane_count);
		LCDPR("byte_mode = %d\n", pconf->lcd_control.vbyone_config->byte_mode);
		LCDPR("region_num = %d\n", pconf->lcd_control.vbyone_config->region_num);
		LCDPR("color_fmt = %d\n", pconf->lcd_control.vbyone_config->color_fmt);
	} else if (pconf->lcd_basic.lcd_type == LCD_MIPI) {
		if (pconf->lcd_control.mipi_config->check_en) {
			LCDPR("check_reg = 0x%02x\n",
				pconf->lcd_control.mipi_config->check_reg);
			LCDPR("check_cnt = %d\n",
				pconf->lcd_control.mipi_config->check_cnt);
		}
		LCDPR("lane_num = %d\n",
			pconf->lcd_control.mipi_config->lane_num);
		LCDPR("bit_rate_max = %d\n",
			pconf->lcd_control.mipi_config->bit_rate_max);
		LCDPR("pclk_lanebyteclk_factor = %d\n",
			pconf->lcd_control.mipi_config->factor_numerator);
		LCDPR("operation_mode_init = %d\n",
			pconf->lcd_control.mipi_config->operation_mode_init);
		LCDPR("operation_mode_disp = %d\n",
			pconf->lcd_control.mipi_config->operation_mode_display);
		LCDPR("video_mode_type = %d\n",
			pconf->lcd_control.mipi_config->video_mode_type);
		LCDPR("clk_always_hs = %d\n",
			pconf->lcd_control.mipi_config->clk_always_hs);
		LCDPR("phy_switch = %d\n",
			pconf->lcd_control.mipi_config->phy_switch);
		LCDPR("extern_init = %d\n",
			pconf->lcd_control.mipi_config->extern_init);
	}
}

#ifdef CONFIG_OF_LIBFDT
static int lcd_config_load_from_dts(char *dt_addr, struct lcd_config_s *pconf)
{
	int parent_offset;
	int child_offset;
	char propname[30];
	char *propdata;
	int i = 0;
	struct aml_lcd_drv_s *pdrv = aml_lcd_get_driver();
	struct lcd_detail_timing_s *ptiming = &pconf->lcd_timing.dft_timing;
	struct lvds_config_s *lvds_conf;
	struct vbyone_config_s *vx1_conf;
	struct phy_config_s *phy_conf;
	unsigned int temp;
	int len;

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

	snprintf(propname, 30, "/lcd/%s", panel_type);
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
		ptiming->fr_adjust_type = 0;
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
	if (pconf->lcd_timing.pll_flag == 0) {
		propdata = (char *)fdt_getprop(dt_addr, child_offset, "clk_para", NULL);
		if (propdata == NULL) {
			LCDERR("failed to get clk_para\n");
			pconf->lcd_timing.pll_ctrl = 0x00140248;
			pconf->lcd_timing.div_ctrl = 0x00000901;
			pconf->lcd_timing.clk_ctrl = 0x000000c0;
		} else {
			pconf->lcd_timing.pll_ctrl = be32_to_cpup((u32*)propdata);
			pconf->lcd_timing.div_ctrl = be32_to_cpup((((u32*)propdata)+1));
			pconf->lcd_timing.clk_ctrl = be32_to_cpup((((u32*)propdata)+2));
		}
	}

	lcd_clk_frame_rate_init(ptiming);
	lcd_default_to_basic_timing_init_config(pconf);

	switch (pconf->lcd_basic.lcd_type) {
	case LCD_TTL:
		if (pconf->lcd_control.ttl_config == NULL) {
			LCDERR("ttl_config is null\n");
			return -1;
		}
		propdata = (char *)fdt_getprop(dt_addr, child_offset, "ttl_attr", NULL);
		if (propdata == NULL) {
			LCDERR("failed to get ttl_attr\n");
		} else {
			pconf->lcd_control.ttl_config->clk_pol = be32_to_cpup((u32*)propdata);
			pconf->lcd_control.ttl_config->sync_valid =
				(((be32_to_cpup((((u32*)propdata)+1))) << 1) |
				((be32_to_cpup((((u32*)propdata)+2))) << 0));
			pconf->lcd_control.ttl_config->swap_ctrl =
				(((be32_to_cpup((((u32*)propdata)+3))) << 1) |
				((be32_to_cpup((((u32*)propdata)+4))) << 0));
		}
		break;
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
				lvds_conf->lvds_repack =
					be32_to_cpup((u32 *)propdata);
				lvds_conf->dual_port =
					be32_to_cpup((((u32 *)propdata) + 1));
				lvds_conf->pn_swap     =
					be32_to_cpup((((u32 *)propdata) + 2));
				lvds_conf->port_swap   =
					be32_to_cpup((((u32 *)propdata) + 3));
				lvds_conf->lane_reverse =
					be32_to_cpup((((u32 *)propdata) + 4));
			} else if (len == 4) {
				lvds_conf->lvds_repack =
					be32_to_cpup((u32 *)propdata);
				lvds_conf->dual_port   =
					be32_to_cpup((((u32 *)propdata) + 1));
				lvds_conf->pn_swap     =
					be32_to_cpup((((u32 *)propdata) + 2));
				lvds_conf->port_swap   =
					be32_to_cpup((((u32 *)propdata) + 3));
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
				lvds_conf->phy_vswing =
					be32_to_cpup((u32 *)propdata);
				lvds_conf->phy_preem  =
					be32_to_cpup((((u32 *)propdata) + 1));
				lvds_conf->phy_clk_vswing =
					be32_to_cpup((((u32 *)propdata) + 2));
				lvds_conf->phy_clk_preem  =
					be32_to_cpup((((u32 *)propdata) + 3));
				if (lcd_debug_print_flag) {
					LCDPR("set vswing=0x%x, preem=0x%x\n",
					      lvds_conf->phy_vswing,
					      lvds_conf->phy_preem);
					LCDPR("set clk vswing=0x%x, preem=0x%x\n",
					      lvds_conf->phy_clk_vswing,
					      lvds_conf->phy_clk_preem);
				}
			} else if (len == 2) {
				lvds_conf->phy_vswing =
					be32_to_cpup((u32 *)propdata);
				lvds_conf->phy_preem  =
					be32_to_cpup((((u32 *)propdata) + 1));
				lvds_conf->phy_clk_vswing =
					LVDS_PHY_CLK_VSWING_DFT;
				lvds_conf->phy_clk_preem  =
					LVDS_PHY_CLK_PREEM_DFT;
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
			vx1_conf->lane_count =
				be32_to_cpup((u32 *)propdata);
			vx1_conf->region_num =
				be32_to_cpup((((u32 *)propdata) + 1));
			vx1_conf->byte_mode  =
				be32_to_cpup((((u32 *)propdata) + 2));
			vx1_conf->color_fmt  =
				be32_to_cpup((((u32 *)propdata) + 3));
		}
		propdata = (char *)fdt_getprop(dt_addr, child_offset, "phy_attr", NULL);
		if (propdata == NULL) {
			if (lcd_debug_print_flag)
				LCDPR("failed to get phy_attr\n");
			vx1_conf->phy_vswing = VX1_PHY_VSWING_DFT;
			vx1_conf->phy_preem  = VX1_PHY_PREEM_DFT;
		} else {
			vx1_conf->phy_vswing =
				be32_to_cpup((u32 *)propdata);
			vx1_conf->phy_preem  =
				be32_to_cpup((((u32 *)propdata) + 1));
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

		propdata = (char *)fdt_getprop(dt_addr, child_offset, "hw_filter", NULL);
		if (propdata == NULL) {
			if (lcd_debug_print_flag)
				LCDPR("failed to get hw_filter\n");
			vx1_conf->hw_filter_time = 0;
			vx1_conf->hw_filter_cnt = 0;
		} else {
			vx1_conf->hw_filter_time =
				be32_to_cpup((u32 *)propdata);
			vx1_conf->hw_filter_cnt =
				be32_to_cpup((((u32 *)propdata) + 1));
			if (lcd_debug_print_flag) {
				LCDPR("vbyone hw_filter=0x%x 0x%x\n",
					vx1_conf->hw_filter_time,
					vx1_conf->hw_filter_cnt);
			}
		}
		break;
	case LCD_MIPI:
		if (pconf->lcd_control.mipi_config == NULL) {
			LCDERR("mipi_config is null\n");
			return -1;
		}
		propdata = (char *)fdt_getprop(dt_addr, child_offset, "mipi_attr", NULL);
		if (propdata == NULL) {
			LCDERR("failed to get mipi_attr\n");
		} else {
			pconf->lcd_control.mipi_config->lane_num = be32_to_cpup((u32 *)propdata);
			pconf->lcd_control.mipi_config->bit_rate_max =
				be32_to_cpup((((u32 *)propdata) + 1));
			pconf->lcd_control.mipi_config->factor_numerator = be32_to_cpup((((u32*)propdata)+2));
			pconf->lcd_control.mipi_config->factor_denominator = 100;
			pconf->lcd_control.mipi_config->operation_mode_init = be32_to_cpup((((u32*)propdata)+3));
			pconf->lcd_control.mipi_config->operation_mode_display = be32_to_cpup((((u32*)propdata)+4));
			pconf->lcd_control.mipi_config->video_mode_type = be32_to_cpup((((u32*)propdata)+5));
			pconf->lcd_control.mipi_config->clk_always_hs = be32_to_cpup((((u32*)propdata)+6));
			pconf->lcd_control.mipi_config->phy_switch = be32_to_cpup((((u32*)propdata)+7));
		}

		pconf->lcd_control.mipi_config->check_en = 0;
		pconf->lcd_control.mipi_config->check_reg = 0xff;
		pconf->lcd_control.mipi_config->check_cnt = 0;
		lcd_mipi_dsi_init_table_detect(dt_addr, child_offset, pconf->lcd_control.mipi_config, 1);
		lcd_mipi_dsi_init_table_detect(dt_addr, child_offset, pconf->lcd_control.mipi_config, 0);

		propdata = (char *)fdt_getprop(dt_addr, child_offset, "extern_init", NULL);
		if (propdata == NULL) {
			LCDERR("failed to get extern_init\n");
		} else {
			pconf->lcd_control.mipi_config->extern_init = be32_to_cpup((u32*)propdata);
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
	unsigned int i, j;
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
			break;
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
	/* lcd_clk */
	temp = ext_lcd->customer_val_3;
	if (temp == Rsv_val)
		ptiming->pixel_clk = 60;
	else
		ptiming->pixel_clk = temp;

	lcd_clk_frame_rate_init(ptiming);
	lcd_default_to_basic_timing_init_config(pconf);

	if (pconf->lcd_basic.lcd_type == LCD_TTL) {
		if (pconf->lcd_control.ttl_config == NULL) {
			LCDERR("ttl_config is null\n");
			return -1;
		}
		pconf->lcd_control.ttl_config->clk_pol = ext_lcd->lcd_spc_val0;
		pconf->lcd_control.ttl_config->sync_valid =
			((ext_lcd->lcd_spc_val1 << 1) |
			(ext_lcd->lcd_spc_val2 << 0));
		pconf->lcd_control.ttl_config->swap_ctrl =
			((ext_lcd->lcd_spc_val3 << 1) |
			(ext_lcd->lcd_spc_val4 << 0));
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
	} else if (pconf->lcd_basic.lcd_type == LCD_VBYONE) {
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
	} else if (pconf->lcd_basic.lcd_type == LCD_MIPI) {
		if (pconf->lcd_control.mipi_config == NULL) {
			LCDERR("mipi_config is null\n");
			return -1;
		}
		pconf->lcd_control.mipi_config->lane_num = ext_lcd->lcd_spc_val0;
		pconf->lcd_control.mipi_config->bit_rate_max   = ext_lcd->lcd_spc_val1;
		pconf->lcd_control.mipi_config->factor_numerator = ext_lcd->lcd_spc_val2;
		pconf->lcd_control.mipi_config->operation_mode_init     = ext_lcd->lcd_spc_val3;
		pconf->lcd_control.mipi_config->operation_mode_display   = ext_lcd->lcd_spc_val4;
		pconf->lcd_control.mipi_config->video_mode_type = ext_lcd->lcd_spc_val5;
		pconf->lcd_control.mipi_config->clk_always_hs  = ext_lcd->lcd_spc_val6;
		pconf->lcd_control.mipi_config->phy_switch = ext_lcd->lcd_spc_val7;
		pconf->lcd_control.mipi_config->factor_denominator = 100;

		pconf->lcd_control.mipi_config->check_en = 0;
		pconf->lcd_control.mipi_config->check_reg = 0xff;
		pconf->lcd_control.mipi_config->check_cnt = 0;
		lcd_mipi_dsi_init_table_check_bsp(pconf->lcd_control.mipi_config, 1);
		lcd_mipi_dsi_init_table_check_bsp(pconf->lcd_control.mipi_config, 0);

		if (ext_lcd->lcd_spc_val9 == Rsv_val)
			pconf->lcd_control.mipi_config->extern_init = 0xff;
		else
			pconf->lcd_control.mipi_config->extern_init = ext_lcd->lcd_spc_val9;
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

	i = 0;
	while (i < LCD_CPU_GPIO_NUM_MAX) {
		if (strcmp(pconf->lcd_power->cpu_gpio[i], "invalid") == 0)
			break;
		i++;
	}
	for (j = i; j < LCD_CPU_GPIO_NUM_MAX; j++) {
		strcpy(pconf->lcd_power->cpu_gpio[j], "invalid");
	}

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
	struct phy_config_s *phy_cfg = pconf->lcd_control.phy_cfg;
	int i, ret;
	unsigned int temp;

	ret = aml_lcd_unifykey_get_size("lcd", &key_len);
	if (ret)
		return -1;
	if (lcd_debug_print_flag)
		LCDPR("%s: size: 0x%x\n", __func__, key_len);
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
	switch (lcd_header->version) {
	case 2:
		len = LCD_UKEY_DATA_LEN_V2; /*10+36+18+31+20+44+10*/
		break;
	default:
		len = LCD_UKEY_DATA_LEN_V1; /*10+36+18+31+20*/
		break;
	}
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
	ptiming->hsync_bp = (*(p + LCD_UKEY_HS_BP) | ((*(p + LCD_UKEY_HS_BP + 1)) << 8));
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
	temp = *(p + LCD_UKEY_CLK_AUTO_GEN);
	pconf->lcd_timing.pll_flag = temp & 0xf;
	ptiming->pixel_clk = (*(p + LCD_UKEY_PCLK) |
		((*(p + LCD_UKEY_PCLK + 1)) << 8) |
		((*(p + LCD_UKEY_PCLK + 2)) << 16) |
		((*(p + LCD_UKEY_PCLK + 3)) << 24));
	ptiming->h_period_min = (*(p + LCD_UKEY_H_PERIOD_MIN) |
		((*(p + LCD_UKEY_H_PERIOD_MIN + 1)) << 8));
	ptiming->h_period_max = (*(p + LCD_UKEY_H_PERIOD_MAX) |
		((*(p + LCD_UKEY_H_PERIOD_MAX + 1)) << 8));
	ptiming->v_period_min = (*(p + LCD_UKEY_V_PERIOD_MIN) |
		((*(p  + LCD_UKEY_V_PERIOD_MIN + 1)) << 8));
	ptiming->v_period_max = (*(p + LCD_UKEY_V_PERIOD_MAX) |
		((*(p + LCD_UKEY_V_PERIOD_MAX + 1)) << 8));
	ptiming->pclk_min = (*(p + LCD_UKEY_PCLK_MIN) |
		((*(p + LCD_UKEY_PCLK_MIN + 1)) << 8) |
		((*(p + LCD_UKEY_PCLK_MIN + 2)) << 16) | ((*(p + LCD_UKEY_PCLK_MIN + 3)) << 24));
	ptiming->pclk_max = (*(p + LCD_UKEY_PCLK_MAX) | ((*(p + LCD_UKEY_PCLK_MAX + 1)) << 8) |
		((*(p + LCD_UKEY_PCLK_MAX + 2)) << 16) | ((*(p + LCD_UKEY_PCLK_MAX + 3)) << 24));

	lcd_clk_frame_rate_init(ptiming);
	lcd_default_to_basic_timing_init_config(pconf);

	/* interface: 20byte */
	if (pconf->lcd_basic.lcd_type == LCD_LVDS) {
		if (pconf->lcd_control.lvds_config == NULL) {
			LCDERR("lvds_config is null\n");
			free(para);
			return -1;
		}
		if (lcd_header->version == 2) {
			pconf->lcd_control.lvds_config->lvds_repack =
					(*(p + LCD_UKEY_IF_ATTR_0) |
					((*(p + LCD_UKEY_IF_ATTR_0 + 1)) << 8)) & 0xff;
			pconf->lcd_control.lvds_config->dual_port =
					(*(p + LCD_UKEY_IF_ATTR_1) |
					((*(p + LCD_UKEY_IF_ATTR_1 + 1)) << 8)) & 0xff;
			pconf->lcd_control.lvds_config->pn_swap =
					(*(p + LCD_UKEY_IF_ATTR_2) |
					((*(p + LCD_UKEY_IF_ATTR_2 + 1)) << 8)) & 0xff;
			pconf->lcd_control.lvds_config->port_swap =
					(*(p + LCD_UKEY_IF_ATTR_3) |
					((*(p + LCD_UKEY_IF_ATTR_3 + 1)) << 8)) & 0xff;
			pconf->lcd_control.lvds_config->lane_reverse =
					(*(p + LCD_UKEY_IF_ATTR_4) |
					((*(p + LCD_UKEY_IF_ATTR_4 + 1)) << 8)) & 0xff;
		} else {
			pconf->lcd_control.lvds_config->lvds_repack =
					(*(p + LCD_UKEY_IF_ATTR_0) |
					((*(p + LCD_UKEY_IF_ATTR_0 + 1)) << 8)) & 0xff;
			pconf->lcd_control.lvds_config->dual_port =
					(*(p + LCD_UKEY_IF_ATTR_1) |
					((*(p + LCD_UKEY_IF_ATTR_1 + 1)) << 8)) & 0xff;
			pconf->lcd_control.lvds_config->pn_swap =
					(*(p + LCD_UKEY_IF_ATTR_2) |
					((*(p + LCD_UKEY_IF_ATTR_2 + 1)) << 8)) & 0xff;
			pconf->lcd_control.lvds_config->port_swap =
					(*(p + LCD_UKEY_IF_ATTR_3) |
					((*(p + LCD_UKEY_IF_ATTR_3 + 1)) << 8)) & 0xff;
			pconf->lcd_control.lvds_config->phy_vswing =
					(*(p + LCD_UKEY_IF_ATTR_4) |
					((*(p + LCD_UKEY_IF_ATTR_4 + 1)) << 8)) & 0xff;
			pconf->lcd_control.lvds_config->phy_preem =
					(*(p + LCD_UKEY_IF_ATTR_5) |
					((*(p + LCD_UKEY_IF_ATTR_5 + 1)) << 8)) & 0xff;
			pconf->lcd_control.lvds_config->phy_clk_vswing =
					(*(p + LCD_UKEY_IF_ATTR_6) |
					((*(p + LCD_UKEY_IF_ATTR_6 + 1)) << 8)) & 0xff;
			pconf->lcd_control.lvds_config->phy_clk_preem =
					(*(p + LCD_UKEY_IF_ATTR_7) |
					((*(p + LCD_UKEY_IF_ATTR_7 + 1)) << 8)) & 0xff;

			pconf->lcd_control.lvds_config->lane_reverse = 0;
			phy_cfg->lane_num = 12;
			phy_cfg->vswing_level = lvdsconf->phy_vswing & 0xf;
			phy_cfg->ext_pullup = (lvdsconf->phy_vswing >> 4) & 0x3;
			phy_cfg->vswing =
				lcd_phy_vswing_level_to_value(pdrv, phy_cfg->vswing_level);
			phy_cfg->preem_level = lvdsconf->phy_preem;
			temp = lcd_phy_preem_level_to_value(pdrv, phy_cfg->preem_level);
			for (i = 0; i < phy_cfg->lane_num; i++) {
				phy_cfg->lane[i].amp = 0;
				phy_cfg->lane[i].preem = temp;
			}
		}
	} else if (pconf->lcd_basic.lcd_type == LCD_TTL) {
		if (pconf->lcd_control.ttl_config == NULL) {
			LCDERR("ttl_config is null\n");
			free(para);
			return -1;
		}
		pconf->lcd_control.ttl_config->clk_pol =
			(*(p + LCD_UKEY_IF_ATTR_0) |
			((*(p + LCD_UKEY_IF_ATTR_0 + 1)) << 8)) & 0x1;
		temp = (*(p + LCD_UKEY_IF_ATTR_1) |
			((*(p + LCD_UKEY_IF_ATTR_1 + 1)) << 8)) & 0x1; /* de_valid */
		pconf->lcd_control.ttl_config->sync_valid = (temp << 1);
		temp = (*(p + LCD_UKEY_IF_ATTR_2) |
			((*(p + LCD_UKEY_IF_ATTR_2 + 1)) << 8)) & 0x1; /* hvsync_valid */
		pconf->lcd_control.ttl_config->sync_valid |= (temp << 0);
		temp = (*(p + LCD_UKEY_IF_ATTR_3) |
			((*(p + LCD_UKEY_IF_ATTR_3 + 1)) << 8)) & 0x1; /* rb_swap */
		pconf->lcd_control.ttl_config->swap_ctrl = (temp << 1);
		temp = (*(p + LCD_UKEY_IF_ATTR_4) |
			((*(p + LCD_UKEY_IF_ATTR_4 + 1)) << 8)) & 0x1; /* bit_swap */
		pconf->lcd_control.ttl_config->swap_ctrl |= (temp << 0);
	} else if (pconf->lcd_basic.lcd_type == LCD_VBYONE) {
		if (pconf->lcd_control.vbyone_config == NULL) {
			LCDERR("vbyone_config is null\n");
			free(para);
			return -1;
		}
		if (lcd_header->version == 2) {
			pconf->lcd_control.vbyone_config->lane_count =
				(*(p + LCD_UKEY_IF_ATTR_0) |
				((*(p + LCD_UKEY_IF_ATTR_0 + 1)) << 8)) & 0xff;
			pconf->lcd_control.vbyone_config->region_num =
				(*(p + LCD_UKEY_IF_ATTR_1) |
				((*(p + LCD_UKEY_IF_ATTR_1 + 1)) << 8)) & 0xff;
			pconf->lcd_control.vbyone_config->byte_mode  =
				(*(p + LCD_UKEY_IF_ATTR_2) |
				((*(p + LCD_UKEY_IF_ATTR_2 + 1)) << 8)) & 0xff;
			pconf->lcd_control.vbyone_config->color_fmt  =
				(*(p + LCD_UKEY_IF_ATTR_3) |
				((*(p + LCD_UKEY_IF_ATTR_3 + 1)) << 8)) & 0xff;
		} else {
			pconf->lcd_control.vbyone_config->lane_count =
				(*(p + LCD_UKEY_IF_ATTR_0) |
				((*(p + LCD_UKEY_IF_ATTR_0 + 1)) << 8)) & 0xff;
			pconf->lcd_control.vbyone_config->region_num =
				(*(p + LCD_UKEY_IF_ATTR_1) |
				((*(p + LCD_UKEY_IF_ATTR_1 + 1)) << 8)) & 0xff;
			pconf->lcd_control.vbyone_config->byte_mode  =
				(*(p + LCD_UKEY_IF_ATTR_2) |
				((*(p + LCD_UKEY_IF_ATTR_2 + 1)) << 8)) & 0xff;
			pconf->lcd_control.vbyone_config->color_fmt  =
				(*(p + LCD_UKEY_IF_ATTR_3) |
				((*(p + LCD_UKEY_IF_ATTR_3 + 1)) << 8)) & 0xff;
			pconf->lcd_control.vbyone_config->phy_vswing =
				(*(p + LCD_UKEY_IF_ATTR_4) |
				((*(p + LCD_UKEY_IF_ATTR_4 + 1)) << 8)) & 0xff;
			pconf->lcd_control.vbyone_config->phy_preem =
				(*(p + LCD_UKEY_IF_ATTR_5) |
				((*(p + LCD_UKEY_IF_ATTR_5 + 1)) << 8)) & 0xff;
			pconf->lcd_control.vbyone_config->hw_filter_time =
				*(p + LCD_UKEY_IF_ATTR_8) |
				((*(p + LCD_UKEY_IF_ATTR_8 + 1)) << 8);
			pconf->lcd_control.vbyone_config->hw_filter_cnt =
				*(p + LCD_UKEY_IF_ATTR_9) |
				((*(p + LCD_UKEY_IF_ATTR_9 + 1)) << 8);
			phy_cfg->lane_num = 8;
			phy_cfg->vswing_level = vx1_conf->phy_vswing & 0xf;
			phy_cfg->ext_pullup = (vx1_conf->phy_vswing >> 4) & 0x3;
			phy_cfg->vswing =
				lcd_phy_vswing_level_to_value(pdrv, phy_cfg->vswing_level);
			phy_cfg->preem_level = vx1_conf->phy_preem;
			temp = lcd_phy_preem_level_to_value(pdrv, phy_cfg->preem_level);
			for (i = 0; i < phy_cfg->lane_num; i++) {
				phy_cfg->lane[i].amp = 0;
				phy_cfg->lane[i].preem = temp;
			}
		}
	} else
		LCDERR("unsupport lcd_type: %d\n", pconf->lcd_basic.lcd_type);

	if (lcd_header->version == 2) {
		/* phy: 10byte */ /* v2 */
		if (pconf->lcd_basic.lcd_type == LCD_LVDS) {
			pconf->lcd_control.lvds_config->phy_vswing = *(p +LCD_UKEY_PHY_ATTR_0);
			pconf->lcd_control.lvds_config->phy_preem = *(p + LCD_UKEY_PHY_ATTR_1);
			pconf->lcd_control.lvds_config->phy_clk_vswing = *(p + LCD_UKEY_PHY_ATTR_2);
			pconf->lcd_control.lvds_config->phy_clk_preem = *(p + LCD_UKEY_PHY_ATTR_3);
		} else if (pconf->lcd_basic.lcd_type == LCD_VBYONE) {
			pconf->lcd_control.vbyone_config->phy_vswing =
				(*(p + LCD_UKEY_PHY_ATTR_0) |
				((*(p + LCD_UKEY_PHY_ATTR_0 + 1)) << 8)) & 0xff;
			pconf->lcd_control.vbyone_config->phy_preem =
				(*(p + LCD_UKEY_PHY_ATTR_1) |
				((*(p + LCD_UKEY_PHY_ATTR_1 + 1)) << 8)) & 0xff;
		}
	}

	/* step 3: check power sequence */
	ret = lcd_power_load_from_unifykey(pconf, para, key_len, len);
	if (ret < 0) {
		free(para);
		return -1;
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
	printf("panel\n");
}

static int lcd_outputmode_is_matched(char *mode)
{
	if (strcmp(mode, "panel")) {
		LCDERR("outputmode[%s] is not support\n", mode);
		return -1;
	}

	return 0;
}

static int lcd_config_valid(char *mode)
{
	int ret;

	ret = lcd_outputmode_is_matched(mode);
	if (ret)
		return -1;

	return 0;
}

static void lcd_config_init(struct lcd_config_s *pconf)
{
	lcd_enc_timing_init_config(pconf);

	lcd_tablet_config_update(pconf);
	lcd_clk_generate_parameter(pconf);
	pconf->lcd_timing.clk_change = 0; /* clear clk_change flag */
}

int get_lcd_tablet_config(char *dt_addr, int load_id)
{
	struct aml_lcd_drv_s *lcd_drv = aml_lcd_get_driver();
	int ret = 0;

	strcpy(lcd_drv->version, LCD_DRV_VERSION);
	lcd_drv->list_support_mode = lcd_list_support_mode;
	lcd_drv->outputmode_check = lcd_outputmode_is_matched;
	lcd_drv->config_valid = lcd_config_valid;
	lcd_drv->driver_init_pre = lcd_tablet_driver_init_pre;
	lcd_drv->driver_init = lcd_tablet_driver_init;
	lcd_drv->driver_disable = lcd_tablet_driver_disable;

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

	lcd_config_init(lcd_drv->lcd_config);
	lcd_config_load_print(lcd_drv->lcd_config);
	lcd_drv->probe_done = 1;

	return 0;
}


