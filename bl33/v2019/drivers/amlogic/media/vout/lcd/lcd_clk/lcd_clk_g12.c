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

static struct lcd_clk_ctrl_s pll_ctrl_table_g12a_path0[] = {
	/* flag             reg                 bit                   len*/
	{LCD_CLK_CTRL_EN,   HHI_HDMI_PLL_CNTL0, LCD_PLL_EN_HPLL_G12A,  1},
	{LCD_CLK_CTRL_FRAC, HHI_HDMI_PLL_CNTL1,                    0, 19},
	{LCD_CLK_CTRL_END,  LCD_CLK_REG_END,                       0,  0},
};

static struct lcd_clk_ctrl_s pll_ctrl_table_g12a_path1[] = {
	/* flag             reg                bit                  len*/
	{LCD_CLK_CTRL_EN,   HHI_GP0_PLL_CNTL0, LCD_PLL_EN_GP0_G12A,  1},
	{LCD_CLK_CTRL_FRAC, HHI_GP0_PLL_CNTL1,                   0, 19},
	{LCD_CLK_CTRL_END,  LCD_CLK_REG_END,                     0,  0},
};

static char *lcd_clk_div_sel_table[] = {
	"1",
	"2",
	"3",
	"3.5",
	"3.75",
	"4",
	"5",
	"6",
	"6.25",
	"7",
	"7.5",
	"12",
	"14",
	"15",
	"2.5",
	"4.67",
	"invalid",
};

static const unsigned int od_fb_table[2] = {1, 2};
static const unsigned int od_table[6] = {1, 2, 4, 8, 16, 32};

static void lcd_clk_generate_g12a(struct aml_lcd_drv_s *pdrv)
{
	struct lcd_clk_config_s *cconf;
	struct lcd_config_s *pconf = &pdrv->config;
	unsigned int pll_fout;
	unsigned int xd;
	unsigned int bit_rate_max = 0, bit_rate_min = 0;
	unsigned int tmp;
	int done = 0;

	cconf = get_lcd_clk_config(pdrv);
	if (!cconf)
		return;

	cconf->fout = pconf->timing.lcd_clk / 1000; /* kHz */
	cconf->err_fmin = MAX_ERROR;

	if (cconf->fout > cconf->data->xd_out_fmax) {
		LCDERR("%s: wrong lcd_clk value %dkHz\n",
			__func__, cconf->fout);
		goto generate_clk_done_g12a;
	}

	switch (pconf->basic.lcd_type) {
	case LCD_MIPI:
		cconf->xd_max = CRT_VID_DIV_MAX;
		bit_rate_max = pconf->control.mipi_cfg.local_bit_rate_max;
		bit_rate_min = pconf->control.mipi_cfg.local_bit_rate_min;
		tmp = bit_rate_max - cconf->fout;
		if (tmp >= bit_rate_min)
			bit_rate_min = tmp;

		for (xd = 1; xd <= cconf->xd_max; xd++) {
			pll_fout = cconf->fout * xd;
			if (pll_fout > bit_rate_max || pll_fout < bit_rate_min)
				continue;
			if (lcd_debug_print_flag & LCD_DBG_PR_ADV2)
				LCDPR("fout=%d, xd=%d\n", cconf->fout, xd);

			pconf->timing.bit_rate = pll_fout * 1000;
			pconf->control.mipi_cfg.clk_factor = xd;
			cconf->xd = xd;
			done = check_pll_1od(cconf, pll_fout);
			if (done)
				goto generate_clk_done_g12a;
		}
		break;
	default:
		break;
	}

generate_clk_done_g12a:
	if (done) {
		pconf->timing.pll_ctrl =
			(cconf->pll_od1_sel << PLL_CTRL_OD1) |
			(cconf->pll_n << PLL_CTRL_N) |
			(cconf->pll_m << PLL_CTRL_M);
		pconf->timing.div_ctrl =
			(CLK_DIV_SEL_1 << DIV_CTRL_DIV_SEL) |
			(cconf->xd << DIV_CTRL_XD);
		pconf->timing.clk_ctrl = (cconf->pll_frac << CLK_CTRL_FRAC);
		cconf->done = 1;
	} else {
		pconf->timing.pll_ctrl =
			(1 << PLL_CTRL_OD1) |
			(1 << PLL_CTRL_N)   |
			(50 << PLL_CTRL_M);
		pconf->timing.div_ctrl =
			(CLK_DIV_SEL_1 << DIV_CTRL_DIV_SEL) |
			(7 << DIV_CTRL_XD);
		pconf->timing.clk_ctrl = (0 << CLK_CTRL_FRAC);
		cconf->done = 0;
		LCDERR("Out of clock range\n");
	}
}

static void lcd_pll_frac_generate_g12a(struct aml_lcd_drv_s *pdrv)
{
	struct lcd_clk_config_s *cconf;
	struct lcd_config_s *pconf = &pdrv->config;
	unsigned int pll_fout;
	unsigned int od, pll_fvco;
	unsigned int m, n, od_fb, frac, offset, temp;

	cconf = get_lcd_clk_config(pdrv);
	if (!cconf)
		return;

	cconf->fout = pconf->timing.lcd_clk / 1000; /* kHz */
	od = od_table[cconf->pll_od1_sel];
	m = cconf->pll_m;
	n = cconf->pll_n;
	od_fb = cconf->pll_od_fb;

	if (lcd_debug_print_flag & LCD_DBG_PR_ADV2) {
		LCDPR("m=%d, n=%d, od=%d, xd=%d\n",
			m, n, cconf->pll_od1_sel, cconf->xd);
	}
	if (cconf->fout > cconf->data->xd_out_fmax) {
		LCDERR("%s: wrong lcd_clk value %dkHz\n",
			__func__, cconf->fout);
		return;
	}
	if (lcd_debug_print_flag & LCD_DBG_PR_ADV2)
		LCDPR("%s pclk=%d\n", __func__, cconf->fout);

	pll_fout = cconf->fout * cconf->xd;
	if (pll_fout > cconf->data->pll_out_fmax || pll_fout < cconf->data->pll_out_fmin) {
		LCDERR("%s: wrong pll_fout value %dkHz\n", __func__, pll_fout);
		return;
	}
	if (lcd_debug_print_flag & LCD_DBG_PR_ADV2)
		LCDPR("%s pll_fout=%d\n", __func__, pll_fout);

	pll_fvco = pll_fout * od;
	if (pll_fvco < cconf->data->pll_vco_fmin || pll_fvco > cconf->data->pll_vco_fmax) {
		LCDERR("%s: wrong pll_fvco value %dkHz\n", __func__, pll_fvco);
		return;
	}
	if (lcd_debug_print_flag & LCD_DBG_PR_ADV2)
		LCDPR("%s pll_fvco=%d\n", __func__, pll_fvco);

	cconf->pll_fvco = pll_fvco;
	pll_fvco = pll_fvco / od_fb_table[od_fb];
	temp = cconf->fin * m / n;
	if (pll_fvco >= temp) {
		temp = pll_fvco - temp;
		offset = 0;
	} else {
		temp = temp - pll_fvco;
		offset = 1;
	}
	if (temp >= (2 * cconf->fin)) {
		LCDERR("%s: pll changing %dkHz is too much\n",
			__func__, temp);
		return;
	}
	frac = temp * cconf->data->pll_frac_range * n / cconf->fin;
	cconf->pll_frac = frac | (offset << 11);
	if (lcd_debug_print_flag & LCD_DBG_PR_NORMAL)
		LCDPR("lcd_pll_frac_generate: frac=0x%x\n", frac);
}

static void lcd_clk_generate_hpll_g12a(struct aml_lcd_drv_s *pdrv)
{
	struct lcd_clk_config_s *cconf;
	struct lcd_config_s *pconf = &pdrv->config;
	unsigned int pll_fout;
	unsigned int clk_div_sel, xd;
	unsigned int bit_rate_max = 0, bit_rate_min = 0;
	unsigned int tmp;
	int done = 0;

	cconf = get_lcd_clk_config(pdrv);
	if (!cconf)
		return;

	cconf->fout = pconf->timing.lcd_clk / 1000; /* kHz */
	cconf->err_fmin = MAX_ERROR;

	if (cconf->fout > cconf->data->xd_out_fmax)
		LCDERR("%s: wrong lcd_clk value %dkHz\n", __func__, cconf->fout);

	switch (pconf->basic.lcd_type) {
	case LCD_MIPI:
		cconf->xd_max = CRT_VID_DIV_MAX;
		bit_rate_max = pconf->control.mipi_cfg.local_bit_rate_max;
		bit_rate_min = pconf->control.mipi_cfg.local_bit_rate_min;
		tmp = bit_rate_max - cconf->fout;
		if (tmp >= bit_rate_min)
			bit_rate_min = tmp;

		clk_div_sel = CLK_DIV_SEL_1;
		for (xd = 1; xd <= cconf->xd_max; xd++) {
			pll_fout = cconf->fout * xd;
			if (pll_fout > bit_rate_max || pll_fout < bit_rate_min)
				continue;
			if (lcd_debug_print_flag & LCD_DBG_PR_ADV2)
				LCDPR("fout=%d, xd=%d\n", cconf->fout, xd);

			pconf->timing.bit_rate = pll_fout * 1000;
			pconf->control.mipi_cfg.clk_factor = xd;
			cconf->xd = xd;
			cconf->div_sel = clk_div_sel;
			done = check_pll_3od(cconf, pll_fout);
			if (done)
				goto generate_clk_done_hpll_g12a;
		}
		break;
	default:
		break;
	}

generate_clk_done_hpll_g12a:
	if (done) {
		pconf->timing.pll_ctrl =
			(cconf->pll_od1_sel << PLL_CTRL_OD1) |
			(cconf->pll_od2_sel << PLL_CTRL_OD2) |
			(cconf->pll_od3_sel << PLL_CTRL_OD3) |
			(cconf->pll_n << PLL_CTRL_N)         |
			(cconf->pll_m << PLL_CTRL_M);
		pconf->timing.div_ctrl =
			(cconf->div_sel << DIV_CTRL_DIV_SEL) |
			(cconf->xd << DIV_CTRL_XD);
		pconf->timing.clk_ctrl = (cconf->pll_frac << CLK_CTRL_FRAC);
		cconf->done = 1;
	} else {
		pconf->timing.pll_ctrl =
			(1 << PLL_CTRL_OD1) |
			(1 << PLL_CTRL_OD2) |
			(1 << PLL_CTRL_OD3) |
			(1 << PLL_CTRL_N)   |
			(50 << PLL_CTRL_M);
		pconf->timing.div_ctrl =
			(CLK_DIV_SEL_1 << DIV_CTRL_DIV_SEL) |
			(7 << DIV_CTRL_XD);
		pconf->timing.clk_ctrl = (0 << CLK_CTRL_FRAC);
		cconf->done = 0;
		LCDERR("Out of clock range\n");
	}
}

#define PLL_WAIT_LOCK_CNT_G12A    1000
static int lcd_pll_wait_lock_g12a(int path)
{
	unsigned int pll_ctrl, pll_ctrl3, pll_ctrl6;
	unsigned int pll_lock;
	int wait_loop = PLL_WAIT_LOCK_CNT_G12A; /* 200 */
	int ret = 0;

	if (path) {
		pll_ctrl = HHI_GP0_PLL_CNTL0;
		pll_ctrl3 = HHI_GP0_PLL_CNTL3;
		pll_ctrl6 = HHI_GP0_PLL_CNTL6;
	} else {
		pll_ctrl = HHI_HDMI_PLL_CNTL0;
		pll_ctrl3 = HHI_HDMI_PLL_CNTL3;
		pll_ctrl6 = HHI_HDMI_PLL_CNTL6;
	}
	do {
		udelay(50);
		pll_lock = lcd_ana_getb(pll_ctrl, 31, 1);
		wait_loop--;
	} while ((pll_lock != 1) && (wait_loop > 0));

	if (pll_lock == 1) {
		goto pll_lock_end_g12a;
	} else {
		LCDPR("path: %d, pll try 1, lock: %d\n", path, pll_lock);
		lcd_ana_setb(pll_ctrl3, 1, 31, 1);
		wait_loop = PLL_WAIT_LOCK_CNT_G12A;
		do {
			udelay(50);
			pll_lock = lcd_ana_getb(pll_ctrl, 31, 1);
			wait_loop--;
		} while ((pll_lock != 1) && (wait_loop > 0));
	}

	if (pll_lock == 1) {
		goto pll_lock_end_g12a;
	} else {
		LCDPR("path: %d, pll try 2, lock: %d\n", path, pll_lock);
		lcd_ana_write(pll_ctrl6, 0x55540000);
		wait_loop = PLL_WAIT_LOCK_CNT_G12A;
		do {
			udelay(50);
			pll_lock = lcd_ana_getb(pll_ctrl, 31, 1);
			wait_loop--;
		} while ((pll_lock != 1) && (wait_loop > 0));
	}

	if (pll_lock != 1)
		ret = -1;

pll_lock_end_g12a:
	LCDPR("%s: path=%d, pll_lock=%d, wait_loop=%d\n",
		__func__, path, pll_lock, (PLL_WAIT_LOCK_CNT_G12A - wait_loop));
	return ret;
}

static void lcd_set_gp0_pll_g12a(struct aml_lcd_drv_s *pdrv)
{
	struct lcd_clk_config_s *cconf;
	unsigned int pll_ctrl, pll_ctrl1, pll_ctrl3, pll_ctrl4, pll_ctrl6;
	int ret, cnt = 0;

	if (lcd_debug_print_flag & LCD_DBG_PR_ADV2)
		LCDPR("%s\n", __func__);

	cconf = get_lcd_clk_config(pdrv);
	if (!cconf)
		return;

	pll_ctrl = ((1 << LCD_PLL_EN_GP0_G12A) |
		(cconf->pll_n << LCD_PLL_N_GP0_G12A) |
		(cconf->pll_m << LCD_PLL_M_GP0_G12A) |
		(cconf->pll_od1_sel << LCD_PLL_OD_GP0_G12A));
	pll_ctrl1 = (cconf->pll_frac << 0);
	if (cconf->pll_frac) {
		pll_ctrl |= (1 << 27);
		pll_ctrl3 = 0x6a285c00;
		pll_ctrl4 = 0x65771290;
		pll_ctrl6 = 0x56540000;
	} else {
		pll_ctrl3 = 0x48681c00;
		pll_ctrl4 = 0x33771290;
		pll_ctrl6 = 0x56540000;
	}

set_gp0_pll_retry_g12a:
	lcd_ana_write(HHI_GP0_PLL_CNTL0, pll_ctrl);
	lcd_ana_write(HHI_GP0_PLL_CNTL1, pll_ctrl1);
	lcd_ana_write(HHI_GP0_PLL_CNTL2, 0x00);
	lcd_ana_write(HHI_GP0_PLL_CNTL3, pll_ctrl3);
	lcd_ana_write(HHI_GP0_PLL_CNTL4, pll_ctrl4);
	lcd_ana_write(HHI_GP0_PLL_CNTL5, 0x39272000);
	lcd_ana_write(HHI_GP0_PLL_CNTL6, pll_ctrl6);
	lcd_ana_setb(HHI_GP0_PLL_CNTL0, 1, LCD_PLL_RST_GP0_G12A, 1);
	udelay(100);
	lcd_ana_setb(HHI_GP0_PLL_CNTL0, 0, LCD_PLL_RST_GP0_G12A, 1);

	ret = lcd_pll_wait_lock_g12a(1);
	if (ret) {
		if (cnt++ < PLL_RETRY_MAX)
			goto set_gp0_pll_retry_g12a;
		LCDERR("gp0_pll lock failed\n");
	}
}

static void lcd_set_hpll_g12a(struct aml_lcd_drv_s *pdrv)
{
	struct lcd_clk_config_s *cconf;
	unsigned int pll_ctrl, pll_ctrl1, pll_ctrl3, pll_ctrl4, pll_ctrl6;
	int ret, cnt = 0;

	if (lcd_debug_print_flag & LCD_DBG_PR_ADV2)
		LCDPR("%s\n", __func__);

	cconf = get_lcd_clk_config(pdrv);
	if (!cconf)
		return;

	pll_ctrl = ((1 << LCD_PLL_EN_HPLL_G12A) |
		(1 << 25) | /* clk out gate */
		(cconf->pll_n << LCD_PLL_N_HPLL_G12A) |
		(cconf->pll_m << LCD_PLL_M_HPLL_G12A) |
		(cconf->pll_od1_sel << LCD_PLL_OD1_HPLL_G12A) |
		(cconf->pll_od2_sel << LCD_PLL_OD2_HPLL_G12A) |
		(cconf->pll_od3_sel << LCD_PLL_OD3_HPLL_G12A));
	pll_ctrl1 = (cconf->pll_frac << 0);
	if (cconf->pll_frac) {
		pll_ctrl |= (1 << 27);
		pll_ctrl3 = 0x6a285c00;
		pll_ctrl4 = 0x65771290;
		pll_ctrl6 = 0x56540000;
	} else {
		pll_ctrl3 = 0x48681c00;
		pll_ctrl4 = 0x33771290;
		pll_ctrl6 = 0x56540000;
	}

set_hpll_pll_retry_g12a:
	lcd_ana_write(HHI_HDMI_PLL_CNTL0, pll_ctrl);
	lcd_ana_write(HHI_HDMI_PLL_CNTL1, pll_ctrl1);
	lcd_ana_write(HHI_HDMI_PLL_CNTL2, 0x00);
	lcd_ana_write(HHI_HDMI_PLL_CNTL3, pll_ctrl3);
	lcd_ana_write(HHI_HDMI_PLL_CNTL4, pll_ctrl4);
	lcd_ana_write(HHI_HDMI_PLL_CNTL5, 0x39272000);
	lcd_ana_write(HHI_HDMI_PLL_CNTL6, pll_ctrl6);
	lcd_ana_setb(HHI_HDMI_PLL_CNTL0, 1, LCD_PLL_RST_HPLL_G12A, 1);
	udelay(100);
	lcd_ana_setb(HHI_HDMI_PLL_CNTL0, 0, LCD_PLL_RST_HPLL_G12A, 1);

	ret = lcd_pll_wait_lock_g12a(0);
	if (ret) {
		if (cnt++ < PLL_RETRY_MAX)
			goto set_hpll_pll_retry_g12a;
		LCDERR("hpll lock failed\n");
	}
}

static void lcd_set_gp0_pll_g12b(struct aml_lcd_drv_s *pdrv)
{
	struct lcd_clk_config_s *cconf;
	unsigned int pll_ctrl, pll_ctrl1, pll_ctrl3, pll_ctrl4, pll_ctrl6;
	int ret, cnt = 0;

	if (lcd_debug_print_flag & LCD_DBG_PR_ADV2)
		LCDPR("%s\n", __func__);

	cconf = get_lcd_clk_config(pdrv);
	if (!cconf)
		return;

	pll_ctrl = ((1 << LCD_PLL_EN_GP0_G12A) |
		(cconf->pll_n << LCD_PLL_N_GP0_G12A) |
		(cconf->pll_m << LCD_PLL_M_GP0_G12A) |
		(cconf->pll_od1_sel << LCD_PLL_OD_GP0_G12A));
	pll_ctrl1 = (cconf->pll_frac << 0);
	if (cconf->pll_frac) {
		pll_ctrl |= (1 << 27);
		pll_ctrl3 = 0x6a285c00;
		pll_ctrl4 = 0x65771290;
		pll_ctrl6 = 0x56540000;
	} else {
		pll_ctrl3 = 0x48681c00;
		pll_ctrl4 = 0x33771290;
		pll_ctrl6 = 0x56540000;
	}

set_gp0_pll_retry_g12b:
	lcd_ana_write(HHI_GP0_PLL_CNTL0, pll_ctrl);
	lcd_ana_write(HHI_GP0_PLL_CNTL1, pll_ctrl1);
	lcd_ana_write(HHI_GP0_PLL_CNTL2, 0x00);
	lcd_ana_write(HHI_GP0_PLL_CNTL3, pll_ctrl3);
	lcd_ana_write(HHI_GP0_PLL_CNTL4, pll_ctrl4);
	lcd_ana_write(HHI_GP0_PLL_CNTL5, 0x39272000);
	lcd_ana_write(HHI_GP0_PLL_CNTL6, pll_ctrl6);
	lcd_ana_setb(HHI_GP0_PLL_CNTL0, 1, LCD_PLL_RST_GP0_G12A, 1);
	udelay(100);
	lcd_ana_setb(HHI_GP0_PLL_CNTL0, 0, LCD_PLL_RST_GP0_G12A, 1);

	ret = lcd_pll_wait_lock(HHI_GP0_PLL_CNTL0, LCD_PLL_LOCK_GP0_G12A);
	if (ret) {
		if (cnt++ < PLL_RETRY_MAX)
			goto set_gp0_pll_retry_g12b;
		LCDERR("gp0_pll lock failed\n");
	}
}

static void lcd_set_hpll_g12b(struct aml_lcd_drv_s *pdrv)
{
	struct lcd_clk_config_s *cconf;
	unsigned int pll_ctrl, pll_ctrl1, pll_ctrl3, pll_ctrl4, pll_ctrl6;
	int ret, cnt = 0;

	if (lcd_debug_print_flag & LCD_DBG_PR_ADV2)
		LCDPR("%s\n", __func__);

	cconf = get_lcd_clk_config(pdrv);
	if (!cconf)
		return;

	pll_ctrl = ((1 << LCD_PLL_EN_HPLL_G12A) |
		(1 << 25) | /* clk out gate */
		(cconf->pll_n << LCD_PLL_N_HPLL_G12A) |
		(cconf->pll_m << LCD_PLL_M_HPLL_G12A) |
		(cconf->pll_od1_sel << LCD_PLL_OD1_HPLL_G12A) |
		(cconf->pll_od2_sel << LCD_PLL_OD2_HPLL_G12A) |
		(cconf->pll_od3_sel << LCD_PLL_OD3_HPLL_G12A));
	pll_ctrl1 = (cconf->pll_frac << 0);
	if (cconf->pll_frac) {
		pll_ctrl |= (1 << 27);
		pll_ctrl3 = 0x6a285c00;
		pll_ctrl4 = 0x65771290;
		pll_ctrl6 = 0x56540000;
	} else {
		pll_ctrl3 = 0x48681c00;
		pll_ctrl4 = 0x33771290;
		pll_ctrl6 = 0x56540000;
	}

set_hpll_pll_retry_g12b:
	lcd_ana_write(HHI_HDMI_PLL_CNTL0, pll_ctrl);
	lcd_ana_write(HHI_HDMI_PLL_CNTL1, pll_ctrl1);
	lcd_ana_write(HHI_HDMI_PLL_CNTL2, 0x00);
	lcd_ana_write(HHI_HDMI_PLL_CNTL3, pll_ctrl3);
	lcd_ana_write(HHI_HDMI_PLL_CNTL4, pll_ctrl4);
	lcd_ana_write(HHI_HDMI_PLL_CNTL5, 0x39272000);
	lcd_ana_write(HHI_HDMI_PLL_CNTL6, pll_ctrl6);
	lcd_ana_setb(HHI_HDMI_PLL_CNTL0, 1, LCD_PLL_RST_HPLL_G12A, 1);
	udelay(100);
	lcd_ana_setb(HHI_HDMI_PLL_CNTL0, 0, LCD_PLL_RST_HPLL_G12A, 1);

	ret = lcd_pll_wait_lock(HHI_HDMI_PLL_CNTL0, LCD_PLL_LOCK_HPLL_G12A);
	if (ret) {
		if (cnt++ < PLL_RETRY_MAX)
			goto set_hpll_pll_retry_g12b;
		LCDERR("hpll lock failed\n");
	}
}

static void lcd_set_dsi_meas_clk(void)
{
	lcd_clk_setb(HHI_VDIN_MEAS_CLK_CNTL, 0, 21, 3);
	lcd_clk_setb(HHI_VDIN_MEAS_CLK_CNTL, 0, 12, 7);
	lcd_clk_setb(HHI_VDIN_MEAS_CLK_CNTL, 1, 20, 1);
}

static void lcd_set_dsi_phy_clk(int sel)
{
	if (lcd_debug_print_flag & LCD_DBG_PR_ADV2)
		LCDPR("%s\n", __func__);

	lcd_ana_setb(HHI_MIPIDSI_PHY_CLK_CNTL, sel, 12, 3);
	lcd_ana_setb(HHI_MIPIDSI_PHY_CLK_CNTL, 1, 8, 1);
	lcd_ana_setb(HHI_MIPIDSI_PHY_CLK_CNTL, 0, 0, 7);
}

static void lcd_clk_set_g12a_path0(struct aml_lcd_drv_s *pdrv)
{
	struct lcd_clk_config_s *cconf;

	cconf = get_lcd_clk_config(pdrv);
	if (!cconf)
		return;

	lcd_set_hpll_g12a(pdrv);
	lcd_set_vid_pll_div_dft(cconf);
	lcd_set_dsi_meas_clk();
	lcd_set_dsi_phy_clk(0);
}

static void lcd_clk_set_g12a_path1(struct aml_lcd_drv_s *pdrv)
{
	struct lcd_clk_config_s *cconf;

	cconf = get_lcd_clk_config(pdrv);
	if (!cconf)
		return;

	lcd_set_gp0_pll_g12a(pdrv);
	lcd_set_dsi_meas_clk();
	lcd_set_dsi_phy_clk(1);
}

static void lcd_clk_set_g12b_path0(struct aml_lcd_drv_s *pdrv)
{
	struct lcd_clk_config_s *cconf;

	cconf = get_lcd_clk_config(pdrv);
	if (!cconf)
		return;

	lcd_set_hpll_g12b(pdrv);
	lcd_set_vid_pll_div_dft(cconf);
	lcd_set_dsi_meas_clk();
	lcd_set_dsi_phy_clk(0);
}

static void lcd_clk_set_g12b_path1(struct aml_lcd_drv_s *pdrv)
{
	struct lcd_clk_config_s *cconf;

	cconf = get_lcd_clk_config(pdrv);
	if (!cconf)
		return;

	lcd_set_gp0_pll_g12b(pdrv);
	lcd_set_dsi_meas_clk();
	lcd_set_dsi_phy_clk(1);
}

static void lcd_clk_config_init_print_g12a(struct aml_lcd_drv_s *pdrv)
{
	struct lcd_clk_config_s *cconf;
	struct lcd_clk_data_s *data;

	cconf = get_lcd_clk_config(pdrv);
	if (!cconf)
		return;

	data = cconf->data;
	LCDPR("lcd clk config data init:\n"
		"vclk_sel:          %d\n"
		"pll_m_max:         %d\n"
		"pll_m_min:         %d\n"
		"pll_n_max:         %d\n"
		"pll_n_min:         %d\n"
		"pll_od_fb:         %d\n"
		"pll_frac_range:    %d\n"
		"pll_od_sel_max:    %d\n"
		"pll_ref_fmax:      %d\n"
		"pll_ref_fmin:      %d\n"
		"pll_vco_fmax:      %d\n"
		"pll_vco_fmin:      %d\n"
		"pll_out_fmax:      %d\n"
		"pll_out_fmin:      %d\n"
		"xd_out_fmax:       %d\n\n",
		data->vclk_sel,
		data->pll_m_max, data->pll_m_min,
		data->pll_n_max, data->pll_n_min,
		data->pll_od_fb, data->pll_frac_range,
		data->pll_od_sel_max,
		data->pll_ref_fmax, data->pll_ref_fmin,
		data->pll_vco_fmax, data->pll_vco_fmin,
		data->pll_out_fmax, data->pll_out_fmin,
		data->xd_out_fmax);
}

static void lcd_clk_config_print_g12a(struct aml_lcd_drv_s *pdrv)
{
	struct lcd_clk_config_s *cconf;

	cconf = get_lcd_clk_config(pdrv);
	if (!cconf)
		return;

	if (cconf->data->vclk_sel) {
		LCDPR("lcd clk config:\n"
			"vclk_sel      %d\n"
			"pll_m:        %d\n"
			"pll_n:        %d\n"
			"pll_frac:     0x%03x\n"
			"pll_fvco:     %dkHz\n"
			"pll_od:       %d\n"
			"pll_out:      %dkHz\n"
			"xd:           %d\n"
			"fout:         %dkHz\n\n",
			cconf->data->vclk_sel,
			cconf->pll_m, cconf->pll_n,
			cconf->pll_frac, cconf->pll_fvco,
			cconf->pll_od1_sel, cconf->pll_fout,
			cconf->xd, cconf->fout);
	} else {
		LCDPR("lcd clk config:\n"
			"vclk_sel        %d\n"
			"pll_m:          %d\n"
			"pll_n:          %d\n"
			"pll_frac:       0x%03x\n"
			"pll_fvco:       %dkHz\n"
			"pll_od1:        %d\n"
			"pll_od2:        %d\n"
			"pll_od3:        %d\n"
			"pll_out:        %dkHz\n"
			"div_sel:        %s(index %d)\n"
			"xd:             %d\n"
			"fout:           %dkHz\n\n",
			cconf->data->vclk_sel,
			cconf->pll_m, cconf->pll_n,
			cconf->pll_frac, cconf->pll_fvco,
			cconf->pll_od1_sel, cconf->pll_od2_sel,
			cconf->pll_od3_sel, cconf->pll_fout,
			lcd_clk_div_sel_table[cconf->div_sel],
			cconf->div_sel, cconf->xd,
			cconf->fout);
	}
}

static struct lcd_clk_data_s lcd_clk_data_g12a_path0 = {
	.pll_od_fb = PLL_OD_FB_HPLL_G12A,
	.pll_m_max = PLL_M_MAX,
	.pll_m_min = PLL_M_MIN,
	.pll_n_max = PLL_N_MAX,
	.pll_n_min = PLL_N_MIN,
	.pll_frac_range = PLL_FRAC_RANGE_HPLL_G12A,
	.pll_frac_sign_bit = PLL_FRAC_SIGN_BIT_HPLL_G12A,
	.pll_od_sel_max = PLL_OD_SEL_MAX_HPLL_G12A,
	.pll_ref_fmax = PLL_FREF_MAX,
	.pll_ref_fmin = PLL_FREF_MIN,
	.pll_vco_fmax = PLL_VCO_MAX_HPLL_G12A,
	.pll_vco_fmin = PLL_VCO_MIN_HPLL_G12A,
	.pll_out_fmax = CRT_VID_CLK_IN_MAX_G12A,
	.pll_out_fmin = PLL_VCO_MIN_HPLL_G12A / 16,
	.div_in_fmax = 0,
	.div_out_fmax = CRT_VID_CLK_IN_MAX_G12A,
	.xd_out_fmax = ENCL_CLK_IN_MAX_G12A,

	.vclk_sel = 0,
	.enc_clk_msr_id = 9,
	.pll_ctrl_table = pll_ctrl_table_g12a_path0,

	.ss_support = 0,

	.clk_generate_parameter = lcd_clk_generate_hpll_g12a,
	.pll_frac_generate = lcd_pll_frac_generate_dft,
	.set_ss_level = NULL,
	.set_ss_advance = NULL,
	.clk_ss_enable = NULL,
	.clk_set = lcd_clk_set_g12a_path0,
	.vclk_crt_set = lcd_set_vclk_crt_dft,
	.clk_disable = lcd_clk_disable_dft,
	.clk_config_init_print = lcd_clk_config_init_print_g12a,
	.clk_config_print = lcd_clk_config_print_g12a,
	.prbs_clk_config = NULL,
	.prbs_test = NULL,
};

static struct lcd_clk_data_s lcd_clk_data_g12a_path1 = {
	.pll_od_fb = PLL_OD_FB_GP0_G12A,
	.pll_m_max = PLL_M_MAX,
	.pll_m_min = PLL_M_MIN,
	.pll_n_max = PLL_N_MAX,
	.pll_n_min = PLL_N_MIN,
	.pll_frac_range = PLL_FRAC_RANGE_GP0_G12A,
	.pll_frac_sign_bit = PLL_FRAC_SIGN_BIT_GP0_G12A,
	.pll_od_sel_max = PLL_OD_SEL_MAX_GP0_G12A,
	.pll_ref_fmax = PLL_FREF_MAX,
	.pll_ref_fmin = PLL_FREF_MIN,
	.pll_vco_fmax = PLL_VCO_MAX_GP0_G12A,
	.pll_vco_fmin = PLL_VCO_MIN_GP0_G12A,
	.pll_out_fmax = CRT_VID_CLK_IN_MAX_G12A,
	.pll_out_fmin = PLL_VCO_MIN_GP0_G12A / 16,
	.div_in_fmax = 0,
	.div_out_fmax = CRT_VID_CLK_IN_MAX_G12A,
	.xd_out_fmax = ENCL_CLK_IN_MAX_G12A,

	.vclk_sel = 1,
	.enc_clk_msr_id = 9,
	.pll_ctrl_table = pll_ctrl_table_g12a_path1,

	.ss_support = 0,

	.clk_generate_parameter = lcd_clk_generate_g12a,
	.pll_frac_generate = lcd_pll_frac_generate_g12a,
	.set_ss_level = NULL,
	.set_ss_advance = NULL,
	.clk_ss_enable = NULL,
	.clk_set = lcd_clk_set_g12a_path1,
	.vclk_crt_set = lcd_set_vclk_crt_dft,
	.clk_disable = lcd_clk_disable_dft,
	.clk_config_init_print = lcd_clk_config_init_print_g12a,
	.clk_config_print = lcd_clk_config_print_g12a,
	.prbs_clk_config = NULL,
	.prbs_test = NULL,
};

static struct lcd_clk_data_s lcd_clk_data_g12b_path0 = {
	.pll_od_fb = PLL_OD_FB_HPLL_G12A,
	.pll_m_max = PLL_M_MAX,
	.pll_m_min = PLL_M_MIN,
	.pll_n_max = PLL_N_MAX,
	.pll_n_min = PLL_N_MIN,
	.pll_frac_range = PLL_FRAC_RANGE_HPLL_G12A,
	.pll_frac_sign_bit = PLL_FRAC_SIGN_BIT_HPLL_G12A,
	.pll_od_sel_max = PLL_OD_SEL_MAX_HPLL_G12A,
	.pll_ref_fmax = PLL_FREF_MAX,
	.pll_ref_fmin = PLL_FREF_MIN,
	.pll_vco_fmax = PLL_VCO_MAX_HPLL_G12A,
	.pll_vco_fmin = PLL_VCO_MIN_HPLL_G12A,
	.pll_out_fmax = CRT_VID_CLK_IN_MAX_G12A,
	.pll_out_fmin = PLL_VCO_MIN_HPLL_G12A / 16,
	.div_in_fmax = 0,
	.div_out_fmax = CRT_VID_CLK_IN_MAX_G12A,
	.xd_out_fmax = ENCL_CLK_IN_MAX_G12A,

	.vclk_sel = 0,
	.enc_clk_msr_id = 9,
	.pll_ctrl_table = pll_ctrl_table_g12a_path0,

	.ss_support = 0,

	.clk_generate_parameter = lcd_clk_generate_hpll_g12a,
	.pll_frac_generate = lcd_pll_frac_generate_dft,
	.set_ss_level = NULL,
	.set_ss_advance = NULL,
	.clk_ss_enable = NULL,
	.clk_set = lcd_clk_set_g12b_path0,
	.vclk_crt_set = lcd_set_vclk_crt_dft,
	.clk_disable = lcd_clk_disable_dft,
	.clk_config_init_print = lcd_clk_config_init_print_g12a,
	.clk_config_print = lcd_clk_config_print_g12a,
	.prbs_clk_config = NULL,
	.prbs_test = NULL,
};

static struct lcd_clk_data_s lcd_clk_data_g12b_path1 = {
	.pll_od_fb = PLL_OD_FB_GP0_G12A,
	.pll_m_max = PLL_M_MAX,
	.pll_m_min = PLL_M_MIN,
	.pll_n_max = PLL_N_MAX,
	.pll_n_min = PLL_N_MIN,
	.pll_frac_range = PLL_FRAC_RANGE_GP0_G12A,
	.pll_frac_sign_bit = PLL_FRAC_SIGN_BIT_GP0_G12A,
	.pll_od_sel_max = PLL_OD_SEL_MAX_GP0_G12A,
	.pll_ref_fmax = PLL_FREF_MAX,
	.pll_ref_fmin = PLL_FREF_MIN,
	.pll_vco_fmax = PLL_VCO_MAX_GP0_G12A,
	.pll_vco_fmin = PLL_VCO_MIN_GP0_G12A,
	.pll_out_fmax = CRT_VID_CLK_IN_MAX_G12A,
	.pll_out_fmin = PLL_VCO_MIN_GP0_G12A / 16,
	.div_in_fmax = 0,
	.div_out_fmax = CRT_VID_CLK_IN_MAX_G12A,
	.xd_out_fmax = ENCL_CLK_IN_MAX_G12A,

	.vclk_sel = 1,
	.enc_clk_msr_id = 9,
	.pll_ctrl_table = pll_ctrl_table_g12a_path1,

	.ss_support = 0,

	.clk_generate_parameter = lcd_clk_generate_g12a,
	.pll_frac_generate = lcd_pll_frac_generate_g12a,
	.set_ss_level = NULL,
	.set_ss_advance = NULL,
	.clk_ss_enable = NULL,
	.clk_set = lcd_clk_set_g12b_path1,
	.vclk_crt_set = lcd_set_vclk_crt_dft,
	.clk_disable = lcd_clk_disable_dft,
	.clk_config_init_print = lcd_clk_config_init_print_g12a,
	.clk_config_print = lcd_clk_config_print_g12a,
	.prbs_clk_config = NULL,
	.prbs_test = NULL,
};

void lcd_clk_config_chip_init_g12a(struct aml_lcd_drv_s *pdrv, struct lcd_clk_config_s *cconf)
{
	if (pdrv->clk_path) {
		cconf->data = &lcd_clk_data_g12a_path1;
		cconf->pll_od_fb = lcd_clk_data_g12a_path1.pll_od_fb;
	} else {
		cconf->data = &lcd_clk_data_g12a_path0;
		cconf->pll_od_fb = lcd_clk_data_g12a_path0.pll_od_fb;
	}
}

void lcd_clk_config_chip_init_g12b(struct aml_lcd_drv_s *pdrv, struct lcd_clk_config_s *cconf)
{
	if (pdrv->clk_path) {
		cconf->data = &lcd_clk_data_g12b_path1;
		cconf->pll_od_fb = lcd_clk_data_g12b_path1.pll_od_fb;
	} else {
		cconf->data = &lcd_clk_data_g12b_path0;
		cconf->pll_od_fb = lcd_clk_data_g12b_path0.pll_od_fb;
	}
}
