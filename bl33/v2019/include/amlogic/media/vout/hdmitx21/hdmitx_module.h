/* SPDX-License-Identifier: (GPL-2.0+ OR MIT) */
/*
 * Copyright (c) 2019 Amlogic, Inc. All rights reserved.
 */

#ifndef __HDMITX_MODULE_H__
#define __HDMITX_MODULE_H__
#ifndef __HDMITX_MODULE21_H__
#define __HDMITX_MODULE21_H__

#include "hdmi_common.h"
#include "hdmitx_ext.h"
#include <amlogic/media/vout/dsc.h>

#define HZ 100000000 // TODO

struct hdmitx_dev {
	struct {
		int (*get_hpd_state)(void);
		int (*read_edid)(unsigned char *buf);
		void (*turn_off)(void);
		void (*list_support_modes)(void);
		void (*dump_regs)(void);
		void (*test_bist)(unsigned int mode);
		void (*test_prbs)(void);
		void (*set_div40)(bool div40);
		void (*output_blank)(unsigned int blank);
	} hwop;
	struct {
		u32 enable;
		union hdmi_infoframe vend;
		union hdmi_infoframe avi;
		union hdmi_infoframe spd;
		union hdmi_infoframe aud;
		union hdmi_infoframe drm;
	} infoframes;
	u32 colormetry;
	unsigned char rawedid[EDID_BLK_SIZE * EDID_BLK_NO];
	struct rx_cap RXCap;
	struct hdmi_format_para *para;
	enum hdmi_vic vic;
	enum frl_rate_enum frl_rate; /* for mode setting */
	enum frl_rate_enum manual_frl_rate; /* for manual setting */
	u8 tx_max_frl_rate; /* configure in dts file */
	bool flt_train_st; /* 0 means FLT train failed */
	u32 dsc_en;
	u8 dsc_policy;
	u32 dfm_type;
	/* pps data and clk info from dsc module */
	struct dsc_offer_tx_data dsc_data;
	unsigned int frac_rate_policy;
	unsigned int mode420;
	unsigned int dc30;
	enum eotf_type hdmi_current_eotf_type;
	enum mode_type hdmi_current_tunnel_mode;
	/* Add dongle_mode, clock, phy may be different from mbox */
	unsigned int dongle_mode;
	/* edid_check = 0 is default check
	 * Bit 0     (0x01)  don't check block header
	 * Bit 1     (0x02)  don't check edid checksum
	 * Bit 0+1   (0x03)  don't check both block header and checksum
	 */
	unsigned int edid_check;
	unsigned char limit_res_1080p;
	unsigned char enc_idx;
	int dv_en;
	int qms_en; /* qms function enable */
	enum hdmi_vic brr_vic; /* qms BRR vic */
	unsigned char pxp_mode; /* for running at pxp only */
	enum amhdmitx_chip_e chip_type;
	bool hpd_state;
	/* efuse ctrl state
	 * 1 disable the function
	 * 0 dont disable the function
	 */
	bool efuse_dis_hdmi_4k60;	/* 4k50,60hz */
	bool efuse_dis_output_4k;	/* all 4k resolution */
	bool efuse_dis_hdcp_tx22;	/* hdcptx22 */
	bool efuse_dis_hdmi_tx3d;	/* 3d */
};

struct hdmitx_dev *get_hdmitx21_device(void);
void hdmitx21_mux_ddc(void);
u32 get_frl_bandwidth(const enum frl_rate_enum rate);
u32 calc_frl_bandwidth(u32 pixel_freq, enum hdmi_colorspace cs,
	enum hdmi_color_depth cd);
u32 calc_tmds_bandwidth(u32 pixel_freq, enum hdmi_colorspace cs,
	enum hdmi_color_depth cd);
enum frl_rate_enum hdmitx21_select_frl_rate(bool dsc_en, enum hdmi_vic vic,
	enum hdmi_colorspace cs, enum hdmi_color_depth cd);
bool hdmitx_frl_training_main(enum frl_rate_enum frl_rate);
int hdmitx21_read_edid(u8 *_rx_edid);
void scdc21_rd_sink(u8 adr, u8 *val);
void scdc21_wr_sink(u8 adr, u8 val);
struct hdmi_format_para *hdmitx21_get_fmt_paras(enum hdmi_vic vic);
const struct hdmi_timing *hdmitx21_get_timing_para0(void);
int hdmitx21_timing_size(void);
void hdmitx21_set_clk(struct hdmitx_dev *hdev);
void hdmitx_set_clkdiv(struct hdmitx_dev *hdev);
const struct hdmi_timing *hdmitx21_gettiming_from_vic(enum hdmi_vic vic);
struct hdmi_format_para *hdmitx21_get_fmtpara(const char *mode,
	const char *attr);
struct hdmi_format_para *hdmitx21_get_fmt_name(char const *name, char const *attr);
struct hdmi_format_para *hdmitx21_tst_fmt_name(char const *name, char const *attr);
struct hdmi_format_para *hdmitx21_match_dtd_paras(struct dtd *t);

void hdmitx21_set(struct hdmitx_dev *hdev);
void hdmitx21_select_frl(struct hdmitx_dev *hdev);
void hdmitx_module_disable(void);
void hdmitx21_dump_regs(void);
void hdmitx21_infoframe_send(u16 info_type, u8 *body);
int hdmitx21_infoframe_rawget(u8 info_type, u8 *body);

/* there are 2 ways to send out infoframes
 * xxx_infoframe_set() will take use of struct xxx_infoframe_set
 * xxx_infoframe_rawset() will directly send with rawdata
 * if info, hb, or pb == NULL, disable send infoframe
 */
void hdmi_vend_infoframe_set(struct hdmi_vendor_infoframe *info);
void hdmi_vend_infoframe_rawset(u8 *hb, u8 *pb);
void hdmi_vend_infoframe2_rawset(u8 *hb, u8 *pb);
void hdmi_avi_infoframe_set(struct hdmi_avi_infoframe *info);
void hdmi_avi_infoframe_rawset(u8 *hb, u8 *pb);
void hdmi_spd_infoframe_set(struct hdmi_spd_infoframe *info);
void hdmi_audio_infoframe_set(struct hdmi_audio_infoframe *info);
void hdmi_audio_infoframe_rawset(u8 *hb, u8 *pb);
void hdmi_drm_infoframe_set(struct hdmi_drm_infoframe *info);
void hdmi_drm_infoframe_rawset(u8 *hb, u8 *pb);
void hdmi_avi_infoframe_config(enum avi_component_conf conf, u8 val);

bool edid_parsing_ok(struct hdmitx_dev *hdev);
/* Parsing RAW EDID data from edid to prxcap */
unsigned int hdmi_edid_parsing(unsigned char *edid, struct rx_cap *prxcap);
void dsc_cap_show(struct rx_cap *prxcap);
void get_hdmi_data(struct hdmitx_dev *hdev, struct input_hdmi_data *data);
bool is_dolby_enabled(void);
bool is_tv_support_dv(struct hdmitx_dev *hdev);
bool is_dv_preference(struct hdmitx_dev *hdev);
bool is_hdr_preference(struct hdmitx_dev *hdev);
int dolbyvision_scene_process(hdmi_data_t *hdmi_data,
	scene_output_info_t *output_info);
void sdr_scene_process(hdmi_data_t *hdmi_data,
	scene_output_info_t *output_info);
void hdr_scene_process(struct input_hdmi_data *hdmi_data,
	scene_output_info_t *output_info);
bool _is_y420_vic(enum hdmi_vic vic);

void get_hdmi_data(struct hdmitx_dev *hdev, hdmi_data_t *data);
/* bool pre_process_str(char *name); */
struct hdmi_format_para *hdmi_tst_fmt_name(char const *name, char const *attr);
bool is_support_4k(void);
bool is_supported_mode_attr(hdmi_data_t *hdmi_data, char *mode_attr);
bool hdmitx_chk_mode_attr_sup(hdmi_data_t *hdmi_data, char *mode, char *attr);
int get_ubootenv_dv_type(void);
int get_ubootenv_dv_status(void);
int get_hdr_policy(void);
void hdmitx_phy_pre_init(struct hdmitx_dev *hdev);
void hdmitx_set_phypara(enum hdmi_phy_para mode);
int hdmitx_get_hpd_state(void);
void hdmitx_turnoff(void);
void hdmitx_test_prbs(void);
struct hdr_info *hdmitx_get_rx_hdr_info(void);
enum hdmi_vic hdmitx_edid_get_VIC(struct hdmitx_dev *hdev,
	const char *disp_mode, char force_flag);
const char *hdmitx_edid_vic_to_string(enum hdmi_vic vic);
enum hdmi_vic hdmitx_edid_vic_tab_map_vic(const char *disp_mode);
bool is_supported_mode_attr(struct input_hdmi_data *hdmi_data, char *mode_attr);
void hdmitx_set_drm_pkt(struct master_display_info_s *data);
void hdmitx_set_vsif_pkt(enum eotf_type type, enum mode_type tunnel_mode,
	struct dv_vsif_para *data);
bool is_hdmi_mode(char *mode);
void vrr_init_qms_para(struct hdmitx_dev *hdev);
enum hdmi_vic hdmitx_find_brr_vic(enum hdmi_vic vic);

/* the hdmitx output limits to 1080p */
bool is_hdmitx_limited_1080p(void);
bool is_vic_over_limited_1080p(enum hdmi_vic vic);
const struct hdmi_timing *hdmitx21_match_dtd_timing(struct dtd *t);
bool hdmitx_edid_check_valid_mode(struct hdmitx_dev *hdev,
	struct hdmi_format_para *para);
void hdmitx_dsc_cvtem_pkt_send(struct dsc_pps_data_s *pps,
	struct hdmi_timing *timing);
void hdmitx_dsc_cvtem_pkt_disable(void);
enum hdmi_vic hdmitx21_get_prefer_vic(struct hdmitx_dev *hdev, enum hdmi_vic vic);
#undef printk
#define printk printf
#undef pr_info
#define pr_info printf

// TODO
#define hdmitx_debug() printf("hdmitx21: %s[%d]\n", __func__, __LINE__)
#endif
#endif
