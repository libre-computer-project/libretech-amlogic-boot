// SPDX-License-Identifier: (GPL-2.0+ OR MIT)
/*
 * Copyright (c) 2019 Amlogic, Inc. All rights reserved.
 */

#include <common.h>
#include <asm/io.h>
#include <linux/delay.h>
#include <time.h>
#include <amlogic/media/vout/hdmitx21/hdmitx.h>
#include "hdmitx_drv.h"

/* get the corresponding bandwidth of current FRL_RATE, Unit: MHz */
u32 get_frl_bandwidth(const enum frl_rate_enum rate)
{
	const u32 frl_bandwidth[] = {
		[FRL_NONE] = 0,
		[FRL_3G3L] = 9000,
		[FRL_6G3L] = 18000,
		[FRL_6G4L] = 24000,
		[FRL_8G4L] = 32000,
		[FRL_10G4L] = 40000,
		[FRL_12G4L] = 48000,
	};

	if (rate > FRL_12G4L)
		return frl_bandwidth[FRL_12G4L];
	return frl_bandwidth[rate];
}

u32 calc_frl_bandwidth(u32 pixel_freq, enum hdmi_colorspace cs,
	enum hdmi_color_depth cd)
{
	u32 bandwidth = pixel_freq;

	if (cs == HDMI_COLORSPACE_YUV420)
		bandwidth /= 2;
	if (cs != HDMI_COLORSPACE_YUV422) {
		if (cd == COLORDEPTH_48B)
			bandwidth = bandwidth * 2;
		else if (cd == COLORDEPTH_36B)
			bandwidth = bandwidth * 3 / 2;
		else if (cd == COLORDEPTH_30B)
			bandwidth = bandwidth * 5 / 4;
		else
			bandwidth = bandwidth * 1;
	}
	/* bandwidth = tmds_bandwidth * 24 * 1.122 */
	bandwidth = bandwidth * 24;
	bandwidth = bandwidth * 561 / 500;

	return bandwidth;
}

u32 calc_tmds_bandwidth(u32 pixel_freq, enum hdmi_colorspace cs,
	enum hdmi_color_depth cd)
{
	u32 bandwidth = pixel_freq;

	if (cs == HDMI_COLORSPACE_YUV420)
		bandwidth /= 2;
	if (cs != HDMI_COLORSPACE_YUV422) {
		if (cd == COLORDEPTH_48B)
			bandwidth = bandwidth * 2;
		else if (cd == COLORDEPTH_36B)
			bandwidth = bandwidth * 3 / 2;
		else if (cd == COLORDEPTH_30B)
			bandwidth = bandwidth * 5 / 4;
		else
			bandwidth = bandwidth * 1;
	}

	return bandwidth;
}

/* for legacy HDMI2.0 or earlier modes, still select TMDS */
/* TODO DSC modes */
enum frl_rate_enum hdmitx21_select_frl_rate(bool dsc_en, enum hdmi_vic vic,
	enum hdmi_colorspace cs, enum hdmi_color_depth cd)
{
	const struct hdmi_timing *timing;
	enum frl_rate_enum rate = FRL_NONE;
	u32 tx_frl_bandwidth = 0;
	u32 tx_tmds_bandwidth = 0;

	pr_info("dsc_en %d  vic %d  cs %d  cd %d\n", dsc_en, vic, cs, cd);
	timing = hdmitx21_gettiming_from_vic(vic);
	if (!timing)
		return FRL_NONE;

	tx_tmds_bandwidth = calc_tmds_bandwidth(timing->pixel_freq / 1000, cs, cd);
	pr_info("Hactive=%d Vactive=%d Vfreq=%d TMDS_BandWidth=%d\n",
		timing->h_active, timing->v_active,
		timing->v_freq, tx_tmds_bandwidth);
	/* If the tmds bandwidth is less than 594MHz, then select the tmds mode */
	/* the HxVp48hz is new introduced in HDMI 2.1 / CEA-861-H */
	if (timing->h_active <= 4096 && timing->v_active <= 2160 &&
		timing->v_freq != 48000 && tx_tmds_bandwidth <= 594 &&
		timing->pixel_freq / 1000 < 600)
		return FRL_NONE;
	/* tx_frl_bandwidth = tmds_bandwidth * 24 * 1.122 */
	tx_frl_bandwidth = tx_tmds_bandwidth * 24;
	tx_frl_bandwidth = tx_frl_bandwidth * 561 / 500;
	for (rate = FRL_3G3L; rate < FRL_12G4L + 1; rate++) {
		if (tx_frl_bandwidth <= get_frl_bandwidth(rate)) {
			pr_info("select frl_rate as %d\n", rate);
			return rate;
		}
	}

	return FRL_NONE;
}

#define CALC_COEFF 10000

bool frl_check_full_bw(enum hdmi_colorspace cs, enum hdmi_color_depth cd, u32 pixel_clock,
	u32 h_active, enum frl_rate_enum frl_rate, u32 *tri_bytes)
{
	u32 tmds_clock = 0;
	u32 overhead_max_num = 0;
	u32 overhead_max_den = 10000;
	u32 tri_bytes_per_line = 0;
	u32 time_for_1_active_video_line = 0;
	u32 effective_link_rate = 0;
	u32 effective_chars_per_sec = 0;
	u32 effective_active_bytes_per_line = 0;
	u32 bytes_per_active_line = 0;
	u32 frl_mega_bits_rate = 0;
	u32 temp = 0;

	if (!frl_rate || !tri_bytes)
		return 0;

	if (cs == HDMI_COLORSPACE_YUV420)
		pixel_clock = pixel_clock / 2;
	tmds_clock = pixel_clock;
	tri_bytes_per_line = h_active;
	bytes_per_active_line = h_active;
	/* frl_mega_bits_rate = pixel_clock; */

	/* TCLK update */
	if (cs != HDMI_COLORSPACE_YUV422) {
		if (cd == COLORDEPTH_30B)
			tmds_clock = (pixel_clock * 5) / 4;
		else if (cd == COLORDEPTH_36B)
			tmds_clock = (pixel_clock * 3) / 2;
		else
			tmds_clock = pixel_clock;
	}
	if (cs == HDMI_COLORSPACE_YUV420)
		tri_bytes_per_line >>= 1;

	if (cs != HDMI_COLORSPACE_YUV422) {
		if (cd == COLORDEPTH_30B)
			tri_bytes_per_line = (tri_bytes_per_line * 5) / 4;
		else if (cd == COLORDEPTH_36B)
			tri_bytes_per_line = ((tri_bytes_per_line * 3) / 2);
	}
	tmds_clock = tmds_clock / CALC_COEFF;
	time_for_1_active_video_line = tri_bytes_per_line * 200;
	time_for_1_active_video_line = time_for_1_active_video_line / tmds_clock;
	time_for_1_active_video_line = time_for_1_active_video_line / 201;

	frl_mega_bits_rate = get_frl_bandwidth(frl_rate);
	if (frl_rate == FRL_3G3L || frl_rate == FRL_6G3L) {
		/* for 3 lanes, overhead max is 2.136% */
		overhead_max_num = 267;
		overhead_max_den = 12500;
	} else {
		/* for 4 lanes, overhead max is 2.184% */
		overhead_max_num = 273;
		overhead_max_den = 12500;
	}

	effective_link_rate = frl_mega_bits_rate * 1000 / CALC_COEFF;
	temp = effective_link_rate * 3 / 10000;
	effective_link_rate = effective_link_rate - temp;
	effective_chars_per_sec = effective_link_rate / 18;
	temp = effective_chars_per_sec * overhead_max_num / overhead_max_den;
	effective_chars_per_sec = effective_chars_per_sec - temp;
	effective_active_bytes_per_line =
		(effective_chars_per_sec * time_for_1_active_video_line) * 2;
	bytes_per_active_line = tri_bytes_per_line * 3;
	temp = bytes_per_active_line / 200;
	bytes_per_active_line = bytes_per_active_line + temp + 6;
	tri_bytes_per_line = ((tri_bytes_per_line * 3) >> 1) + 3;
	*tri_bytes = tri_bytes_per_line;

	pr_info("bytes_per_active_line %d  effective_active_bytes_per_line %d\n",
		bytes_per_active_line, effective_active_bytes_per_line);
	if (bytes_per_active_line >= effective_active_bytes_per_line)
		return 1;
	else
		return 0;
}

/*
 * Config hdmitx Data Flow metering
 * bw_type: 1: Full BW
 *          2: non Full BW
 *          0: default
 */
void hdmitx_dfm_cfg(u8 bw_type, u16 val)
{
	switch (bw_type) {
	case 1:
		hdmitx21_wr_reg(H21TXSB_SPARE_0_IVCTX, 0xf3);
		hdmitx21_wr_reg(H21TXSB_SPARE_1_IVCTX, 0x7d);
		hdmitx21_wr_reg(H21TXSB_SPARE_3_IVCTX, 0xff);
		hdmitx21_wr_reg(H21TXSB_SPARE_2_IVCTX, 0xd0);
		hdmitx21_wr_reg(H21TXSB_SPARE_4_IVCTX, val & 0xff);
		hdmitx21_wr_reg(H21TXSB_SPARE_5_IVCTX, (val >> 8) & 0xff);
		hdmitx21_wr_reg(H21TXSB_SPARE_6_IVCTX, 0xf3);
		break;
	case 2:
		hdmitx21_wr_reg(H21TXSB_SPARE_0_IVCTX, 0xf0);
		hdmitx21_wr_reg(H21TXSB_SPARE_1_IVCTX, 0x00);
		hdmitx21_wr_reg(H21TXSB_SPARE_3_IVCTX, 0xff);
		hdmitx21_wr_reg(H21TXSB_SPARE_2_IVCTX, 0x00);
		hdmitx21_wr_reg(H21TXSB_SPARE_4_IVCTX, 0x00);
		hdmitx21_wr_reg(H21TXSB_SPARE_5_IVCTX, 0x00);
		hdmitx21_wr_reg(H21TXSB_SPARE_6_IVCTX, 0x00);
		break;
	case 0:
	default:
		hdmitx21_wr_reg(H21TXSB_SPARE_0_IVCTX, 0x00);
		hdmitx21_wr_reg(H21TXSB_SPARE_1_IVCTX, 0x00);
		hdmitx21_wr_reg(H21TXSB_SPARE_3_IVCTX, 0x00);
		hdmitx21_wr_reg(H21TXSB_SPARE_2_IVCTX, 0x00);
		hdmitx21_wr_reg(H21TXSB_SPARE_4_IVCTX, 0x00);
		hdmitx21_wr_reg(H21TXSB_SPARE_5_IVCTX, 0x00);
		hdmitx21_wr_reg(H21TXSB_SPARE_6_IVCTX, 0x00);
		break;
	}
}

//================== LTS 1============================
static void TX_LTS_1_HDMI21_CONFIG(enum frl_rate_enum frl_rate)
{
	u8 data8;
	u8 frl_rate_sel;
	bool block_hsync;

	//Step1:Tx reads EDID
	//Assume that Rx supports FRL

	//Step2:initial Tx Phy,TODO

	//Step3:initial Tx Controller
	data8  = 0;
	data8 |= (1 << 0); //[7:0] reg_pkt_period
	hdmitx21_wr_reg(H21TXSB_PKT_PRD_IVCTX, data8);

	data8  = 0;
	data8 |= (1 << 7); //[7]reg_sw_tpi_en,SW TPI Enable
	hdmitx21_wr_reg(LM_DDC_IVCTX, data8);
	//Do other initial in config_hdmi20_tx

	//Step4:stop Tx transmission
	//--Disable AV and h21tx_sb
	block_hsync = !!(hdmitx21_rd_reg(H21TXSB_CTRL_1_IVCTX) & 0x4);
	data8  = 0;
	data8 |= (1 << 1); //reg_block_av,1'b0:Enable to hdmi2sb block write tmds data into DPRAM
	data8 |= (block_hsync << 2); //reg_block_hsync,DSC mode
	data8 |= (0 << 5); //reg_block_over,DSC mode
	data8 |= (0 << 6); //reg_block_over_val,DSC mode
	hdmitx21_wr_reg(H21TXSB_CTRL_1_IVCTX, data8);

	//--Disable h21tx_sb
	frl_rate_sel = (frl_rate > FRL_6G3L) ? 1 : 0;
	data8  = 0;
	data8 |= (0 << 0); //reg_en, Module enable
	data8 |= (1 << 4); //reg_scrambler_en
	data8 |= (frl_rate_sel << 7); //reg_lane_sel,1'b1:4lane enable;1'b0:3lane enable
	hdmitx21_wr_reg(H21TXSB_CTRL_IVCTX, data8);

	data8  = 0;
	data8 |= (0 << 5); //reg_SCDC_sel
	data8 |= (0 << 4); //reg_LTS_req
	data8 |= (0 << 0); //reg_LTS_Cmd[3:0]
	hdmitx21_wr_reg(HT_DIG_CTL0_PHY_IVCTX, data8);

	//Step2:FRL pattern
	data8  = 0;
	data8 |= (0 << 0);//reg_inj_bist_err
	data8 |= (1 << 1);//reg_en_tp,prbs_16b_gen enable
	data8 |= (0 << 2);//reg_swap_tp_bits
	data8 |= (0 << 3);//reg_en_man_fsm,tp_gen module after prbs16b
	data8 |= (0 << 4);//reg_man_fsm[3:0]
	hdmitx21_wr_reg(HT_DIG_CTL22_PHY_IVCTX, data8);

	data8  = 0;
	data8 |= (0 << 0);//reg_tf_alt_clt_en,tc fifo control enable
	data8 |= (0 << 1);//reg_tf_rec_sel,tc fifo exception handling selection
	data8 |= (0 << 2);//reg_tf_err_rcv,tc fifo error recovery scheme
	data8 |= (0 << 3);//reg_en_man_20b_fsm, enable manual 20bit calibration state
	data8 |= (0 << 4);//reg_man_20b_fsm, manual 20bit calibration state
	hdmitx21_wr_reg(HT_DIG_CTL23_PHY_IVCTX, data8);
}

static void TX_LTS_2_POLL_READY(void)
{
	u8 FLT_ready = 0;
	u8 count = 20;
	u8 data8;

	while (!FLT_ready && count--) {
		scdc21_rd_sink(0x40, &data8);
		FLT_ready = data8 & 0x40; //[6] FLT_ready
	}
}

static void TX_LTS_2_SETTING(enum frl_rate_enum frl_rate)
{
	u8 data8;
	//Step2:initial all lanes to FFE_LEVEL0
	//Config PLL and Analog Phy,TODO

	//Step3:check FRL max
	//Assume that Rx support FRL Max rate is 10G 4lane

	//Setp4:config Rx FRL_rate and FFE_level
	data8  = 0;
	//FRL_rate 0:disable frl;
	//         4'd1:3G 3Lane;
	//         4'd2:6G 3Lane;
	//         4'd3:6G 4Lane;
	//         4'd4:8G 4Lane;
	//         4'd5:10G 4Lane;
	//         4'd6:12G 4Lane.
	data8 |= (frl_rate << 0);
	//FFE_levels, Max FFE_Level supported for the current FRL rate.
	//  4'd0:FFE_LEVEL0;
	//  4'd1:FFE_LEVEL1;
	//  4'd2:FFE_LEVEL2;
	//  4'd3:FFE_LEVEL3;
	data8 |= (0 << 4);
	scdc21_wr_sink(0x31, data8);
	pr_info("configure SCDC/0x31 as %x\n", data8);
	scdc21_rd_sink(0x30, &data8);
	pr_info("read SCDC/0x30 as %x\n", data8);
	scdc21_wr_sink(0x30, 0);
	pr_info("write SCDC/0x30 as %x\n", 0);
}

static bool TX_LTS_3_POLL_FLT_UPDATE(void)
{
	u8 hdmi21_update_reg;
	u8 FLT_update = 0;
	u8 data8;
	unsigned long tmo = get_timer(0) + 200;

	while (!FLT_update && time_after(tmo, get_timer(0))) {
		scdc21_rd_sink(0x10, &data8);//Update_flag registers,0x10
		hdmi21_update_reg = data8;
		FLT_update = hdmi21_update_reg & 0x20; //[5] FLT_update
	}
	if (time_after(tmo, get_timer(0)))
		return 1;
	else
		return 0;
}

static void TX_LTS_3_READ_LTP_REQ(u16 *val)
{
	u8 data8;
	u8 ltp01;
	u8 ltp23;

	//
	scdc21_rd_sink(0x41, &data8); //[7:4]Ln1_LTP_req;[3:0]Ln0_LTP_req;
	ltp01 = data8;
	scdc21_rd_sink(0x42, &data8); //[7:4]Ln3_LTP_req;[3:0]Ln2_LTP_req;
	ltp23 = data8;

	*val = ltp01 + (ltp23 << 8);
	if (*val == 0 || *val == 0x0001 || *val == 0x0100)
		return;
	hdmitx21_wr_reg(HT_DIG_CTL1_PHY_IVCTX, ltp01);
	hdmitx21_wr_reg(HT_DIG_CTL2_PHY_IVCTX, ltp23);

	data8  = 0;
	data8 |= (0 << 0);//reg_cfg_LTP_req[7:0],prbs initial value
	hdmitx21_wr_reg(HT_DIG_CTL3_PHY_IVCTX, data8);

	data8  = 0;
	data8 |= (0 << 0);//reg_cfg_LTP_req[15:8],prbs initial value
	hdmitx21_wr_reg(HT_DIG_CTL4_PHY_IVCTX, data8);
}

static void TX_FLT_UPDATE_CLEAR(void)
{
	u8 hdmi21_update_reg;

	scdc21_rd_sink(0x10, &hdmi21_update_reg);//Update_flag registers,0x10
	if (hdmi21_update_reg & 0x10)
		scdc21_wr_sink(0x10, 0x20);//Update_flag registers,0x10
	else
		scdc21_wr_sink(0x10, hdmi21_update_reg | 0x20);//Update_flag registers,0x10
}

//======================= LTS P ========================
static void TX_LTS_P_SEND_ONLY_GAP(enum frl_rate_enum frl_rate)
{
	u8 data8;
	u8 frl_rate_sel;
	bool block_hsync;
	//Step1:start FRL transition with Gap only

	//Enable HDMI2P1
	data8  = 0;
	data8 |= (1 << 0); //reg_hdmi_en
	data8 |= (0 << 1); //reg_mhl3_en
	data8 |= (0 << 2); //reg_mhl3_priv
	data8 |= (0 << 3); //reg_cod_tdm_en
	data8 |= (1 << 4); //reg_tclk_from_io
	data8 |= (1 << 5); //reg_hdmi2p1_en !!!
	data8 |= (0 << 6); //reg_osc_en
	data8 |= (0 << 7); //reg_tclk_frm_8b10b
	hdmitx21_wr_reg(SOC_FUNC_SEL_IVCTX, data8);

	//Enable av_link dual mode
	data8  = 0;
	data8 |= (0 << 0);//reg_mhl3cts_rst,Software reset forMHL3 CTS logic
	data8 |= (0 << 4);//reg_tx_cch_inv,bitwise inversion of clock channel to PHY
	data8 |= (1 << 7);//reg_dualpp_mode.1'b1:dual pixel mode;1'b0:single pixel mode.
	hdmitx21_wr_reg(SW_RST_IVCTX, data8);

	//--Disable AV and h21tx_sb
	block_hsync = !!(hdmitx21_rd_reg(H21TXSB_CTRL_1_IVCTX) & 0x4);
	data8  = 0;
	data8 |= (1 << 1); //reg_block_av,1'b0:Enable to hdmi2sb block write tmds data into DPRAM
	data8 |= (block_hsync << 2); //reg_block_hsync,DSC mode
	data8 |= (0 << 5); //reg_block_over,DSC mode
	data8 |= (0 << 6); //reg_block_over_val,DSC mode
	hdmitx21_wr_reg(H21TXSB_CTRL_1_IVCTX, data8);

	//--Enable h21tx_sb
	frl_rate_sel = (frl_rate > FRL_6G3L) ? 1 : 0;
	data8  = 0;
	data8 |= (1 << 0); //reg_en, Module enable
	data8 |= (1 << 4); //reg_scrambler_en
	data8 |= (frl_rate_sel << 7); //reg_lane_sel,1'b1:4lane enable;1'b0:3lane enable
	hdmitx21_wr_reg(H21TXSB_CTRL_IVCTX, data8);

	//Step2:FRL pattern stop
	data8  = 0;
	data8 |= (0 << 0);//reg_inj_bist_err
	data8 |= (0 << 1);//reg_en_tp,prbs_16b_gen enable
	data8 |= (0 << 2);//reg_swap_tp_bits
	data8 |= (0 << 3);//reg_en_man_fsm,tp_gen module after prbs16b
	data8 |= (0 << 4);//reg_man_fsm[3:0]
	hdmitx21_wr_reg(HT_DIG_CTL22_PHY_IVCTX, data8);

	data8  = 0;
	data8 |= (0 << 0);//reg_tf_alt_clt_en,tc fifo control enable
	data8 |= (0 << 1);//reg_tf_rec_sel,tc fifo exception handling selection
	data8 |= (0 << 2);//reg_tf_err_rcv,tc fifo error recovery scheme
	data8 |= (0 << 3);//reg_en_man_20b_fsm, enable manual 20bit calibration state
	data8 |= (0 << 4);//reg_man_20b_fsm, manual 20bit calibration state
	hdmitx21_wr_reg(HT_DIG_CTL23_PHY_IVCTX, data8);
}

static void TX_LTS_P_POLL_FRL_START(void)
{
	u8 FRL_start = 0;
	u8 hdmi21_update_reg = 0;
	u8 data8;
	u32 count = 100;
	bool block_hsync;

	while (!FRL_start && count--) {
		scdc21_rd_sink(0x10, &hdmi21_update_reg);//Update_flag registers,0x10
		FRL_start = hdmi21_update_reg & 0x10; //[4] FRL_start
	}
	//Step2:write FLT_start to 0
	scdc21_wr_sink(0x10, hdmi21_update_reg & (~0x10));//Update_flag registers,0x10

	/* Note reset p2t fifo here will cause LG OLED55CXPCA "invalid signal" */

	//Step3:start FRL transmission with AV data
	//--Enable AV and h21tx_sb
	block_hsync = !!(hdmitx21_rd_reg(H21TXSB_CTRL_1_IVCTX) & 0x4);
	data8  = 0;
	data8 |= (0 << 1);
	data8 |= (block_hsync << 2); //reg_block_hsync,DSC mode
	data8 |= (0 << 5); //reg_block_over,DSC mode
	data8 |= (0 << 6); //reg_block_over_val,DSC mode
	hdmitx21_wr_reg(H21TXSB_CTRL_1_IVCTX, data8);

	//Step4:Clear FRL_start by writing "1"
	scdc21_wr_sink(0x10, hdmi21_update_reg | 0x10);//Update_flag registers,0x10
}

//=================================
//     hdmitx_frl_config
//=================================
static void hdmitx_frl_config(u8 color_depth, enum frl_rate_enum frl_rate)
{
	u8 data8;
	u8 frl_rate_sel;
	bool block_hsync;
	//=============================================================
	//                   HDMI2p1 configuration begin
	//=============================================================
	data8  = 0;
	data8 |= (1 << 0); //reg_hdmi_en
	data8 |= (0 << 1); //reg_mhl3_en
	data8 |= (0 << 2); //reg_mhl3_priv
	data8 |= (0 << 3); //reg_cod_tdm_en
	data8 |= (1 << 4); //reg_tclk_from_io
	data8 |= (1 << 5); //reg_hdmi2p1_en !!!
	data8 |= (0 << 6); //reg_osc_en
	data8 |= (0 << 7); //reg_tclk_frm_8b10b
	hdmitx21_wr_reg(SOC_FUNC_SEL_IVCTX, data8);

	data8  = 0;
	data8 |= (1 << 0);
	data8 |= (1 << 2);
	data8 |= (0 << 7); //reg_clkratio_sw_en
	hdmitx21_wr_reg(CLKRATIO_IVCTX, data8);

	data8  = 0;
	data8 |= ((color_depth & 0x03) << 0);
	data8 |= (0 << 2); //reg_force_idle
	data8 |= (1 << 3); //reg_dualpp_en
	data8 |= (1 << 4); //reg_in_dualpp_en
	data8 |= (0 << 5); //reg_null_pkt_en_vs_hi,Null packet Enable at VYSNC High.
	data8 |= (0 << 6); //reg_null_pkt_en,Null packet Enable.
	data8 |= (1 << 7); //reg_dc_pkt_en,Deep Color Packet Enable.
	hdmitx21_wr_reg(P2T_CTRL_IVCTX, data8);

	data8  = 0;
	data8 |= (0 << 0);//reg_mhl3cts_rst,Software reset forMHL3 CTS logic
	data8 |= (0 << 4);//reg_tx_cch_inv,bitwise inversion of clock channel to PHY
	data8 |= (1 << 7);//reg_dualpp_mode.1'b1:dual pixel mode;1'b0:single pixel mode.
	hdmitx21_wr_reg(SW_RST_IVCTX, data8);

	data8  = 0;
	data8 |= (1 << 0);//reg_legacy_dev_support
	data8 |= (0 << 1);
	data8 |= (10 << 4);
	hdmitx21_wr_reg(HDPLL_FIX0_IVCTX, data8);

	data8  = 0;
	data8 |= (0 << 0);//reg_pkt_num_cycles[5:0],Number of cycles for a data island packet
	data8 |= (1 << 6);//reg_interlace_support.
	data8 |= (0 << 7);//reg_pkt_num_cycles[6]
	hdmitx21_wr_reg(HDPLL_FIX1_IVCTX, data8);

	data8  = 0;
	data8 |= (10 << 0);//reg_con_num_cycles[3:0]
	data8 |= (0 << 4);//reg_offset_cycles_new
	data8 |= (1 << 6);//reg_hw_intrlcd_vnt_ctl
	hdmitx21_wr_reg(HDPLL_FIX_NEW_0_IVCTX, data8);

	data8  = 0;
	data8 |= (0 << 0);//reg_con_pkt_num_cycles[6:0]
	data8 |= (1 << 7);//reg_vrr_hcnt_ctl_en
	hdmitx21_wr_reg(HDPLL_FIX_NEW_1_IVCTX, data8);

	data8  = 0;
	data8 |= (1 << 0); //[7:0] reg_pkt_period
	hdmitx21_wr_reg(H21TXSB_PKT_PRD_IVCTX, data8);

	//--Enable AV and h21tx_sb
	block_hsync = !!(hdmitx21_rd_reg(H21TXSB_CTRL_1_IVCTX) & 0x4);
	data8  = 0;
	data8 |= (0 << 1); //reg_block_av,1'b1:Enable to hdmi2sb block write tmds data into DPRAM
	data8 |= (block_hsync << 2); //reg_block_hsync,DSC mode
	data8 |= (0 << 5); //reg_block_over,DSC mode
	data8 |= (0 << 6); //reg_block_over_val,DSC mode
	hdmitx21_wr_reg(H21TXSB_CTRL_1_IVCTX, data8);

	//--Disable h21tx_sb
	frl_rate_sel = (frl_rate > FRL_6G3L) ? 1 : 0;
	data8  = 0;
	data8 |= (1 << 0); //reg_en, Module enable
	//data8 |= (1 << 4); //reg_scrambler_en
	data8 |= (0 << 4); //reg_scrambler_en
	data8 |= (frl_rate_sel << 7); //reg_lane_sel,1'b1:4lane enable;1'b0:3lane enable
	hdmitx21_wr_reg(H21TXSB_CTRL_IVCTX, data8);

	//--- regtx p0 ---

	hdmitx21_wr_reg(FRL_LINK_RATE_CONFIG_IVCTX, frl_rate);

	//=============================================================
	//                   HDMI2p1 configuration end
	//=============================================================
}

bool hdmitx_frl_training_main(enum frl_rate_enum frl_rate)
{
	u16 ltp0123 = 0xAAAA;//reserved LTP
	u8 data8;
	char *ltp_en = NULL;
	bool ret;
	/* for the FRL training, the max T_FLT is 200ms */
	unsigned long tmo = get_timer(0) + 200;

	pr_info("hdmitx21: set rx frl_rate as %d\n", frl_rate);
	ltp_en = env_get("ltp_en");
	if (ltp_en && ltp_en[0] == '0') {
		pr_info("skip the FRL LTP training...\n");
		hdmitx_frl_config(0, frl_rate);
		return 1;
	}
	hdmitx21_wr_reg(AON_CYP_CTL_IVCTX, 2); // 70kHz

	hdmitx21_set_reg_bits(PWD_SRST_IVCTX, 1, 2, 1);
	hdmitx21_set_reg_bits(PWD_SRST_IVCTX, 0, 2, 1);

	scdc21_rd_sink(0x10, &data8);
	scdc21_rd_sink(0x01, &data8);
	pr_info("[FRL TRAINING] read sink version %x\n", data8);
	data8 = 0x01;
	scdc21_wr_sink(0x02, data8);
	pr_info("[FRL TRAINING] write source version %x\n", data8);
	scdc21_rd_sink(0x35, &data8);
	pr_info("[FRL TRAINING] ************** TX_LTS_1_HDMI21_CONFIG************\n");
	TX_LTS_1_HDMI21_CONFIG(frl_rate);

	pr_info("[FRL TRAINING] ************** TX_LTS_2_POLL_READY************\n");
	TX_LTS_2_POLL_READY();
	pr_info("[FRL TRAINING] ************** TX_LTS_2_SETTING************\n");
	TX_LTS_2_SETTING(frl_rate);
	if (frl_rate == FRL_NONE)
		return 1;

	hdmitx_soft_reset(BIT(0));
	while (ltp0123 != 0 && time_after(tmo, get_timer(0))) {
		pr_info("[FRL TRAINING] ************** TX_LTS_3_POLL_FLT_UPDATE************\n");
		ret = TX_LTS_3_POLL_FLT_UPDATE();
		if (!ret)
			return 0;
		pr_info("[FRL TRAINING] ************** TX_LTS_3_READ_LTP_REQ************\n");
		TX_LTS_3_READ_LTP_REQ(&ltp0123);
		pr_info("LTPn: 0x%x\n", ltp0123);
		pr_info("[FRL TRAINING] ************** TX_FLT_UPDATE_CLEAR************\n");
		TX_FLT_UPDATE_CLEAR();
	}
	if (time_before(tmo, get_timer(0)))
		return 0;

	pr_info("[FRL TRAINING] ************** TX_LTS_P_SEND_ONLY_GAP************\n");
	TX_LTS_P_SEND_ONLY_GAP(frl_rate);
	pr_info("[FRL TRAINING] ************** TX_FLT_UPDATE_CLEAR************\n");
	TX_FLT_UPDATE_CLEAR();
	pr_info("[FRL TRAINING] ************** TX_LTS_P_POLL_FRL_START************\n");
	TX_LTS_P_POLL_FRL_START();
	return 1;
}

static void frl_tx_av_enable(bool enable)
{
	hdmitx21_set_reg_bits(H21TXSB_CTRL_1_IVCTX, !enable, 1, 1);
}

static void frl_tx_sb_enable(bool enable, enum frl_rate_enum frl_rate)
{
	hdmitx21_set_reg_bits(H21TXSB_CTRL_IVCTX, !!enable, 0, 1);
	hdmitx21_set_reg_bits(H21TXSB_CTRL_IVCTX, frl_rate > FRL_6G3L ? 9 : 1, 4, 4);
}

static void stop_frl_transmission(enum frl_rate_enum frl_rate)
{
	frl_tx_av_enable(false);
	frl_tx_sb_enable(false, frl_rate);
}

void frl_tx_stop(struct hdmitx_dev *hdev)
{
	stop_frl_transmission(hdev->frl_rate);
}

bool scdc_tx_frl_cfg1_set(u8 cfg1)
{
	scdc21_wr_sink(SCDC_CONFIG_1, cfg1);

	return true;
}

u8 scdc_tx_update_flags_get(void)
{
	u8 data;

	scdc21_rd_sink(SCDC_UPDATE_0, &data);
	if (data && (data & HDMI20_UPDATE_FLAGS)) {
		/* clear the flags after reading */
		scdc21_wr_sink(SCDC_UPDATE_0, HDMI20_UPDATE_FLAGS & data);
	}

	return data;
}

bool scdc_tx_update_flags_set(u8 update_flags)
{
	u8 data;

	data = update_flags & HDMI21_UPDATE_FLAGS;
	scdc21_wr_sink(SCDC_UPDATE_0, data);

	return true;
}

