// SPDX-License-Identifier: (GPL-2.0+ OR MIT)
/*
 * Copyright (c) 2019 Amlogic, Inc. All rights reserved.
 */

#include <common.h>
#include <malloc.h>
#include <amlogic/media/vout/lcd/aml_lcd.h>
#include "../lcd_reg.h"
#include "../lcd_common.h"
#include "lcd_clk_config.h"
#include "lcd_clk_ctrl.h"
#include "lcd_clk_utils.h"

static unsigned int tcon_div[5][3] = {
	/* div_mux, div2/4_sel, div4_bypass */
	{1, 0, 1},  /* div1 */
	{0, 0, 1},  /* div2 */
	{0, 1, 1},  /* div4 */
	{0, 0, 0},  /* div8 */
	{0, 1, 0},  /* div16 */
};

static void lcd_pll_ss_enable(struct aml_lcd_drv_s *pdrv, int status)
{
	struct lcd_clk_config_s *cconf;
	unsigned int pll_ctrl2;
	unsigned int flag;

	cconf = get_lcd_clk_config(pdrv);
	if (!cconf)
		return;

	pll_ctrl2 = lcd_ana_read(HHI_TCON_PLL_CNTL2);
	pll_ctrl2 &= ~((1 << 15) | (0xf << 16) | (0xf << 28));

	if (status) {
		if (cconf->ss_level > 0)
			flag = 1;
		else
			flag = 0;
	} else {
		flag = 0;
	}

	if (flag) {
		cconf->ss_en = 1;
		pll_ctrl2 |= ((1 << 15) | (cconf->ss_dep_sel << 28) | (cconf->ss_str_m << 16));
		LCDPR("[%d]: pll ss enable: level: %d, %dppm\n",
			pdrv->index, cconf->ss_level, cconf->ss_ppm);
	} else {
		cconf->ss_en = 0;
		LCDPR("[%d]: pll ss disable\n", pdrv->index);
	}
	lcd_ana_write(HHI_TCON_PLL_CNTL2, pll_ctrl2);
}

static void lcd_set_pll_ss_level(struct aml_lcd_drv_s *pdrv)
{
	struct lcd_clk_config_s *cconf;
	unsigned int pll_ctrl2;
	int ret;

	cconf = get_lcd_clk_config(pdrv);
	if (!cconf)
		return;

	pll_ctrl2 = lcd_ana_read(HHI_TCON_PLL_CNTL2);
	pll_ctrl2 &= ~((1 << 15) | (0xf << 16) | (0xf << 28));

	if (cconf->ss_level > 0) {
		ret = lcd_pll_ss_level_generate(cconf);
		if (ret == 0) {
			cconf->ss_en = 1;
			pll_ctrl2 |= ((1 << 15) |
				      (cconf->ss_dep_sel << 28) |
				      (cconf->ss_str_m << 16));
			LCDPR("[%d]: set pll spread spectrum: level: %d, %dppm\n",
				pdrv->index, cconf->ss_level, cconf->ss_ppm);
		}
	} else {
		cconf->ss_en = 0;
		LCDPR("[%d]: set pll spread spectrum: disable\n", pdrv->index);
	}
	lcd_ana_write(HHI_TCON_PLL_CNTL2, pll_ctrl2);
}

static void lcd_set_pll_ss_advance(struct aml_lcd_drv_s *pdrv)
{
	struct lcd_clk_config_s *cconf;
	unsigned int pll_ctrl2;
	unsigned int freq, mode;

	cconf = get_lcd_clk_config(pdrv);
	if (!cconf)
		return;

	freq = cconf->ss_freq;
	mode = cconf->ss_mode;
	pll_ctrl2 = lcd_ana_read(HHI_TCON_PLL_CNTL2);
	pll_ctrl2 &= ~(0x7 << 24); /* ss_freq */
	pll_ctrl2 |= (freq << 24);
	pll_ctrl2 &= ~(0x3 << 22); /* ss_mode */
	pll_ctrl2 |= (mode << 22);
	lcd_ana_write(HHI_TCON_PLL_CNTL2, pll_ctrl2);

	LCDPR("set pll spread spectrum: freq=%d, mode=%d\n", freq, mode);
}

static void lcd_pll_frac_set(struct aml_lcd_drv_s *pdrv, unsigned int frac)
{
	struct lcd_clk_config_s *cconf;
	unsigned int reg, val;

	cconf = get_lcd_clk_config(pdrv);
	if (!cconf)
		return;

	reg = HHI_TCON_PLL_CNTL1;
	val = lcd_ana_read(reg);
	lcd_ana_setb(reg, frac, 0, 17);
	if (lcd_debug_print_flag & LCD_DBG_PR_NORMAL) {
		LCDPR("[%d]: %s: reg 0x%x: 0x%08x->0x%08x\n",
			pdrv->index, __func__, reg, val, lcd_ana_read(reg));
	}
	LCDPR("[%d]: %s: pll_frac=0x%x\n", pdrv->index, __func__, frac);
}

static void lcd_set_pll(struct aml_lcd_drv_s *pdrv)
{
	struct lcd_clk_config_s *cconf;
	unsigned int pll_ctrl, pll_ctrl1;
	unsigned int tcon_div_sel;
	int ret, cnt = 0;

	if (lcd_debug_print_flag & LCD_DBG_PR_ADV2)
		LCDPR("%s\n", __func__);
	cconf = get_lcd_clk_config(pdrv);
	if (!cconf)
		return;

	tcon_div_sel = cconf->pll_tcon_div_sel;
	pll_ctrl = ((0x3 << 17) | /* gate ctrl */
		(tcon_div[tcon_div_sel][2] << 16) |
		(cconf->pll_n << 10) |
		(cconf->pll_m << 0) |
		(cconf->pll_od3_sel << 19) |
		(cconf->pll_od2_sel << 23) |
		(cconf->pll_od1_sel << 21));
	pll_ctrl1 = (1 << 28) |
		(tcon_div[tcon_div_sel][0] << 22) |
		(tcon_div[tcon_div_sel][1] << 21) |
		((1 << 20) | /* sdm_en */
		(cconf->pll_frac << 0));

set_pll_retry_tl1:
	lcd_ana_write(HHI_TCON_PLL_CNTL0, pll_ctrl);
	udelay(10);
	lcd_ana_setb(HHI_TCON_PLL_CNTL0, 1, 29, 1); //reset
	udelay(10);
	lcd_ana_setb(HHI_TCON_PLL_CNTL0, 1, 28, 1); //en
	udelay(10);
	lcd_ana_write(HHI_TCON_PLL_CNTL1, pll_ctrl1);
	udelay(10);
	lcd_ana_write(HHI_TCON_PLL_CNTL2, 0x0000110c);
	udelay(10);
	lcd_ana_write(HHI_TCON_PLL_CNTL3, 0x10051400);
	udelay(10);
	lcd_ana_setb(HHI_TCON_PLL_CNTL4, 0x0100c0, 0, 24);
	udelay(10);
	lcd_ana_setb(HHI_TCON_PLL_CNTL4, 0x8300c0, 0, 24);
	udelay(10);
	lcd_ana_setb(HHI_TCON_PLL_CNTL0, 1, 26, 1);
	udelay(10);
	lcd_ana_setb(HHI_TCON_PLL_CNTL0, 0, 29, 1); //release reset
	udelay(10);
	lcd_ana_write(HHI_TCON_PLL_CNTL2, 0x0000300c);

	ret = lcd_pll_wait_lock(HHI_TCON_PLL_CNTL0, 31);
	if (ret) {
		if (cnt++ < PLL_RETRY_MAX)
			goto set_pll_retry_tl1;
		LCDERR("hpll lock failed\n");
	} else {
		udelay(100);
		lcd_ana_setb(HHI_TCON_PLL_CNTL2, 1, 5, 1);
	}

	if (cconf->ss_level > 0) {
		lcd_set_pll_ss_level(pdrv);
		lcd_set_pll_ss_advance(pdrv);
	}
}

#ifdef CONFIG_AML_LCD_TCON
static void lcd_set_tcon_clk_t5w(struct aml_lcd_drv_s *pdrv)
{
	struct lcd_config_s *pconf = &pdrv->config;
	unsigned int val;

	if (pdrv->config.basic.lcd_type != LCD_MLVDS &&
	    pdrv->config.basic.lcd_type != LCD_P2P)
		return;

	if (lcd_debug_print_flag & LCD_DBG_PR_NORMAL)
		LCDPR("[%d]: %s\n", pdrv->index, __func__);

	switch (pconf->basic.lcd_type) {
	case LCD_MLVDS:
		val = pconf->control.mlvds_cfg.clk_phase & 0xfff;
		lcd_ana_setb(HHI_TCON_PLL_CNTL1, (val & 0xf), 24, 4);
		lcd_ana_setb(HHI_TCON_PLL_CNTL4, ((val >> 4) & 0xf), 28, 4);
		lcd_ana_setb(HHI_TCON_PLL_CNTL4, ((val >> 8) & 0xf), 24, 4);

		/* tcon_clk */
		if (pconf->timing.enc_clk >= 100000000) /* 25M */
			lcd_clk_write(HHI_TCON_CLK_CNTL, (1 << 7) | (1 << 6) | (0xf << 0));
		else /* 12.5M */
			lcd_clk_write(HHI_TCON_CLK_CNTL, (1 << 7) | (1 << 6) | (0x1f << 0));
		break;
	case LCD_P2P:
		/* tcon_clk 50M */
		lcd_clk_write(HHI_TCON_CLK_CNTL, (1 << 7) | (1 << 6) | (7 << 0));
		break;
	default:
		break;
	}

	/* global reset tcon, take effect when pixel_clk ready */
	lcd_tcon_global_reset(pdrv);
}
#endif

static void lcd_clk_set_t5w(struct aml_lcd_drv_s *pdrv)
{
	struct lcd_clk_config_s *cconf;

	cconf = get_lcd_clk_config(pdrv);
	if (!cconf)
		return;

	lcd_set_pll(pdrv);
	lcd_set_vid_pll_div_dft(cconf);
}

static void lcd_set_vclk_crt(struct aml_lcd_drv_s *pdrv)
{
	struct lcd_clk_config_s *cconf;

	if (lcd_debug_print_flag & LCD_DBG_PR_ADV2)
		LCDPR("%s\n", __func__);
	cconf = get_lcd_clk_config(pdrv);
	if (!cconf)
		return;

#ifdef CONFIG_AML_LCD_PXP
	/* setup the XD divider value */
	lcd_clk_setb(HHI_VIID_CLK0_DIV, 0, VCLK2_XD, 8);
	udelay(5);
	/* select vid_pll_clk */
	lcd_clk_setb(HHI_VIID_CLK0_CTRL, 7, VCLK2_CLK_IN_SEL, 3);
#else
	/* setup the XD divider value */
	lcd_clk_setb(HHI_VIID_CLK0_DIV, (cconf->xd - 1), VCLK2_XD, 8);
	udelay(5);
	/* select vid_pll_clk */
	lcd_clk_setb(HHI_VIID_CLK0_CTRL, cconf->data->vclk_sel,
		VCLK2_CLK_IN_SEL, 3);
#endif
	lcd_clk_setb(HHI_VIID_CLK0_CTRL, 1, VCLK2_EN, 1);
	udelay(2);

	/* [15:12] encl_clk_sel, select vclk2_div1 */
	lcd_clk_setb(HHI_VIID_CLK0_DIV, 8, ENCL_CLK_SEL, 4);
	/* release vclk2_div_reset and enable vclk2_div */
	lcd_clk_setb(HHI_VIID_CLK0_DIV, 1, VCLK2_XD_EN, 2);
	udelay(5);

	lcd_clk_setb(HHI_VIID_CLK0_CTRL, 1, VCLK2_DIV1_EN, 1);
	lcd_clk_setb(HHI_VIID_CLK0_CTRL, 1, VCLK2_SOFT_RST, 1);
	udelay(10);
	lcd_clk_setb(HHI_VIID_CLK0_CTRL, 0, VCLK2_SOFT_RST, 1);
	udelay(5);

	/* enable CTS_ENCL clk gate */
	lcd_clk_setb(HHI_VID_CLK0_CTRL2, 1, ENCL_GATE_VCLK, 1);
}

//special setting by lcd interface
static void lcd_clktree_set(struct aml_lcd_drv_s *pdrv)
{
#ifdef CONFIG_AML_LCD_TCON
	if (pdrv->index == 0) /* tcon_clk invalid for lcd1 */
		lcd_set_tcon_clk_t5w(pdrv);
#endif
}

static void lcd_clk_disable(struct aml_lcd_drv_s *pdrv)
{
	/*encl_clk_gate*/
	lcd_clk_setb(HHI_VID_CLK_CNTL2, 0, 3, 1);

	/* close vclk2_div gate: 0x104b[4:0] */
	lcd_clk_setb(HHI_VIID_CLK_CNTL, 0, 0, 5);
	lcd_clk_setb(HHI_VIID_CLK_CNTL, 0, 19, 1); //vclk2_en

	lcd_ana_setb(HHI_TCON_PLL_CNTL0, 0, 28, 1); //disable
	lcd_ana_setb(HHI_TCON_PLL_CNTL0, 1, 29, 1); //reset
}

static void lcd_prbs_set_pll_vx1(struct aml_lcd_drv_s *pdrv)
{
	int cnt = 0, ret;

lcd_prbs_retry_pll_vx1_tl1:
	lcd_ana_write(HHI_TCON_PLL_CNTL0, 0x000f04f7);
	udelay(10);
	lcd_ana_setb(HHI_TCON_PLL_CNTL0, 1, LCD_PLL_RST_TL1, 1);
	udelay(10);
	lcd_ana_setb(HHI_TCON_PLL_CNTL0, 1, LCD_PLL_EN_TL1, 1);
	udelay(10);
	lcd_ana_write(HHI_TCON_PLL_CNTL1, 0x10110000);
	udelay(10);
	lcd_ana_write(HHI_TCON_PLL_CNTL2, 0x00001108);
	udelay(10);
	lcd_ana_write(HHI_TCON_PLL_CNTL3, 0x10051400);
	udelay(10);
	lcd_ana_write(HHI_TCON_PLL_CNTL4, 0x010100c0);
	udelay(10);
	lcd_ana_write(HHI_TCON_PLL_CNTL4, 0x038300c0);
	udelay(10);
	lcd_ana_setb(HHI_TCON_PLL_CNTL0, 1, 26, 1);
	udelay(10);
	lcd_ana_setb(HHI_TCON_PLL_CNTL0, 0, LCD_PLL_RST_TL1, 1);
	udelay(10);
	lcd_ana_write(HHI_TCON_PLL_CNTL2, 0x00003008);
	udelay(10);
	lcd_ana_write(HHI_TCON_PLL_CNTL2, 0x00003028);
	udelay(10);

	ret = lcd_pll_wait_lock(HHI_TCON_PLL_CNTL0, LCD_PLL_LOCK_TL1);
	if (ret) {
		if (cnt++ < PLL_RETRY_MAX)
			goto lcd_prbs_retry_pll_vx1_tl1;
		LCDERR("pll lock failed\n");
	}

	/* pll_div */
	lcd_clk_setb(HHI_VIID_CLK_CNTL, 0, VCLK2_EN, 1);
	udelay(5);

	/* Disable the div output clock */
	lcd_ana_setb(HHI_VID_PLL_CLK_DIV, 0, 19, 1);
	lcd_ana_setb(HHI_VID_PLL_CLK_DIV, 0, 15, 1);

	lcd_ana_setb(HHI_VID_PLL_CLK_DIV, 0, 18, 1);
	lcd_ana_setb(HHI_VID_PLL_CLK_DIV, 0, 16, 2);
	lcd_ana_setb(HHI_VID_PLL_CLK_DIV, 0, 15, 1);
	lcd_ana_setb(HHI_VID_PLL_CLK_DIV, 0, 0, 14);

	lcd_ana_setb(HHI_VID_PLL_CLK_DIV, 2, 16, 2);
	lcd_ana_setb(HHI_VID_PLL_CLK_DIV, 1, 15, 1);
	lcd_ana_setb(HHI_VID_PLL_CLK_DIV, 0x739c, 0, 15);
	lcd_ana_setb(HHI_VID_PLL_CLK_DIV, 0, 15, 1);

	/* Enable the final output clock */
	lcd_ana_setb(HHI_VID_PLL_CLK_DIV, 1, 19, 1);
}

static void lcd_prbs_set_pll_lvds(struct aml_lcd_drv_s *pdrv)
{
	int cnt = 0, ret;

lcd_prbs_retry_pll_lvds_tl1:
	lcd_ana_write(HHI_TCON_PLL_CNTL0, 0x008e049f);
	udelay(10);
	lcd_ana_write(HHI_TCON_PLL_CNTL0, 0x208e049f);
	udelay(10);
	lcd_ana_write(HHI_TCON_PLL_CNTL0, 0x3006049f);
	udelay(10);
	lcd_ana_write(HHI_TCON_PLL_CNTL1, 0x10000000);
	udelay(10);
	lcd_ana_write(HHI_TCON_PLL_CNTL2, 0x00001102);
	udelay(10);
	lcd_ana_write(HHI_TCON_PLL_CNTL3, 0x10051400);
	udelay(10);
	lcd_ana_write(HHI_TCON_PLL_CNTL4, 0x010100c0);
	udelay(10);
	lcd_ana_write(HHI_TCON_PLL_CNTL4, 0x038300c0);
	udelay(10);
	lcd_ana_write(HHI_TCON_PLL_CNTL0, 0x348e049f);
	udelay(10);
	lcd_ana_write(HHI_TCON_PLL_CNTL0, 0x148e049f);
	udelay(10);
	lcd_ana_write(HHI_TCON_PLL_CNTL2, 0x00003002);
	udelay(10);
	lcd_ana_write(HHI_TCON_PLL_CNTL2, 0x00003022);
	udelay(10);

	ret = lcd_pll_wait_lock(HHI_TCON_PLL_CNTL0, LCD_PLL_LOCK_TL1);
	if (ret) {
		if (cnt++ < PLL_RETRY_MAX)
			goto lcd_prbs_retry_pll_lvds_tl1;
		LCDERR("pll lock failed\n");
	}

	/* pll_div */
	lcd_clk_setb(HHI_VIID_CLK_CNTL, 0, VCLK2_EN, 1);
	udelay(5);

	/* Disable the div output clock */
	lcd_ana_setb(HHI_VID_PLL_CLK_DIV, 0, 19, 1);
	lcd_ana_setb(HHI_VID_PLL_CLK_DIV, 0, 15, 1);

	lcd_ana_setb(HHI_VID_PLL_CLK_DIV, 0, 18, 1);
	lcd_ana_setb(HHI_VID_PLL_CLK_DIV, 0, 16, 2);
	lcd_ana_setb(HHI_VID_PLL_CLK_DIV, 0, 15, 1);
	lcd_ana_setb(HHI_VID_PLL_CLK_DIV, 0, 0, 14);

	lcd_ana_setb(HHI_VID_PLL_CLK_DIV, 1, 16, 2);
	lcd_ana_setb(HHI_VID_PLL_CLK_DIV, 1, 15, 1);
	lcd_ana_setb(HHI_VID_PLL_CLK_DIV, 0x3c78, 0, 15);
	lcd_ana_setb(HHI_VID_PLL_CLK_DIV, 0, 15, 1);

	/* Enable the final output clock */
	lcd_ana_setb(HHI_VID_PLL_CLK_DIV, 1, 19, 1);
}

static void lcd_prbs_config_clk(struct aml_lcd_drv_s *pdrv, unsigned int lcd_prbs_mode)
{
	unsigned int reg_vid2_clk_div, reg_vid2_clk_ctrl, reg_vid_clk_ctrl2;

	if (lcd_debug_print_flag & LCD_DBG_PR_NORMAL)
		LCDPR("%s\n", __func__);

	reg_vid2_clk_div = HHI_VIID_CLK0_DIV;
	reg_vid2_clk_ctrl = HHI_VIID_CLK0_CTRL;
	reg_vid_clk_ctrl2 = HHI_VID_CLK0_CTRL2;

	if (lcd_prbs_mode == LCD_PRBS_MODE_VX1) {
		lcd_clk_setb(reg_vid2_clk_ctrl, 0, VCLK2_EN, 1);
		lcd_prbs_set_pll_vx1(pdrv);
	} else if (lcd_prbs_mode == LCD_PRBS_MODE_LVDS) {
		lcd_clk_setb(reg_vid2_clk_ctrl, 0, VCLK2_EN, 1);
		lcd_prbs_set_pll_lvds(pdrv);
	} else {
		LCDERR("%s: unsupport lcd_prbs_mode %d\n",
		       __func__, lcd_prbs_mode);
		return;
	}

	lcd_clk_setb(reg_vid2_clk_div, 0, VCLK2_XD, 8);
	udelay(5);

	/* select vid_pll_clk */
	lcd_clk_setb(reg_vid2_clk_ctrl, 0, VCLK2_CLK_IN_SEL, 3);
	lcd_clk_setb(reg_vid2_clk_ctrl, 1, VCLK2_EN, 1);
	udelay(5);

	/* [15:12] encl_clk_sel, select vclk2_div1 */
	lcd_clk_setb(reg_vid2_clk_div, 8, ENCL_CLK_SEL, 4);
	/* release vclk2_div_reset and enable vclk2_div */
	lcd_clk_setb(reg_vid2_clk_div, 1, VCLK2_XD_EN, 2);
	udelay(5);

	lcd_clk_setb(reg_vid2_clk_ctrl, 1, VCLK2_DIV1_EN, 1);
	lcd_clk_setb(reg_vid2_clk_ctrl, 1, VCLK2_SOFT_RST, 1);
	udelay(10);
	lcd_clk_setb(reg_vid2_clk_ctrl, 0, VCLK2_SOFT_RST, 1);
	udelay(5);

	/* enable CTS_ENCL clk gate */
	lcd_clk_setb(reg_vid_clk_ctrl2, 1, ENCL_GATE_VCLK, 1);

	if (lcd_debug_print_flag & LCD_DBG_PR_NORMAL)
		LCDPR("%s ok\n", __func__);
}

static struct lcd_clk_data_s lcd_clk_data_t5w = {
	.pll_od_fb = 0,
	.pll_m_max = 511,
	.pll_m_min = 2,
	.pll_n_max = 1,
	.pll_n_min = 1,
	.pll_frac_range = (1 << 17),
	.pll_frac_sign_bit = 18,
	.pll_od_sel_max = 3,
	.pll_ref_fmax = 25000000,
	.pll_ref_fmin = 5000000,
	.pll_vco_fmax = 6000000000ULL,
	.pll_vco_fmin = 3000000000ULL,
	.pll_out_fmax = 3100000000ULL,
	.pll_out_fmin = 187500000,
	.div_in_fmax = 3100000000ULL,
	.div_out_fmax = 750000000,
	.xd_out_fmax = 750000000,
	.od_cnt = 3,
	.have_tcon_div = 1,
	.have_pll_div = 1,
	.phy_clk_location = 0,

	.vclk_sel = 0,
	.enc_clk_msr_id = 6,

	.div_sel_max = CLK_DIV_SEL_MAX,
	.xd_max = 256,
	.phy_div_max = 256,

	.ss_support = 1,
	.ss_level_max = 60,
	.ss_freq_max = 6,
	.ss_mode_max = 2,
	.ss_dep_base = 500, //ppm
	.ss_dep_sel_max = 12,
	.ss_str_m_max = 10,

	.clk_parameter_init = NULL,
	.clk_generate_parameter = lcd_clk_generate_dft,
	.pll_frac_generate = lcd_pll_frac_generate_dft,
	.set_ss_level = lcd_set_pll_ss_level,
	.set_ss_advance = lcd_set_pll_ss_advance,
	.clk_ss_enable = lcd_pll_ss_enable,
	.pll_frac_set = lcd_pll_frac_set,
	.clk_set = lcd_clk_set_t5w,
	.vclk_crt_set = lcd_set_vclk_crt,
	.clk_disable = lcd_clk_disable,
	.clktree_set = lcd_clktree_set,
	.clk_config_init_print = lcd_clk_config_init_print_dft,
	.clk_config_print = lcd_clk_config_print_dft,
	.prbs_clk_config = lcd_prbs_config_clk,
	.prbs_test = NULL,
};

void lcd_clk_config_chip_init_t5w(struct aml_lcd_drv_s *pdrv, struct lcd_clk_config_s *cconf)
{
	cconf->data = &lcd_clk_data_t5w;
	cconf->pll_od_fb = lcd_clk_data_t5w.pll_od_fb;
}
