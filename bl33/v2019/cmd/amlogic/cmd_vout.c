// SPDX-License-Identifier: (GPL-2.0+ OR MIT)
/*
 * Copyright (c) 2019 Amlogic, Inc. All rights reserved.
 */

#include <common.h>
#include <command.h>
#include <environment.h>
#include <malloc.h>
#include <asm/byteorder.h>
#ifdef CONFIG_AML_VPP
#include <amlogic/media/vpp/vpp.h>
#endif
#include <amlogic/media/vout/aml_vout.h>
#ifdef CONFIG_AML_HDMITX
#ifdef CONFIG_AML_HDMITX20
#include <amlogic/media/vout/hdmitx/hdmitx.h>
#else
#include <amlogic/media/vout/hdmitx21/hdmitx.h>
#endif
#endif

#ifdef CONFIG_AML_CVBS
#include <amlogic/media/vout/aml_cvbs.h>
#endif
#ifdef CONFIG_AML_LCD
#include <amlogic/media/vout/lcd/aml_lcd.h>
#endif

#include <amlogic/cpu_id.h>

#if defined(CONFIG_AML_CVBS) || defined(CONFIG_AML_HDMITX) || defined(CONFIG_AML_LCD)
#ifdef CONFIG_AML_VPP
static unsigned int vpp_viu1_cm_state = VPP_CM_INVALID;
#endif
#endif

#ifdef CONFIG_AML_HDMITX
static int vout_hdmi_hpd(int hpd_st)
{
#ifdef CONFIG_AML_LCD
	unsigned int mux_sel = VIU_MUX_MAX, venc_sel = VIU_MUX_MAX;
	char *mode;
#endif
	char *hdmimode;
	char *cvbsmode;
	char *colorattribute;

#ifdef CONFIG_AML_LCD
	mode = env_get("outputmode");
	mux_sel = aml_lcd_driver_outputmode_check(mode, 0);
	venc_sel = mux_sel & 0xf;
	if (venc_sel == VIU_MUX_ENCL) {
		printf("%s: lcd no need hpd detect\n", __func__);
		return 0;
	}
#endif
	/*get hdmi mode and colorattribute from env */
	hdmimode = env_get("hdmimode");
	if (hdmimode)
		printf("%s: hdmimode=%s\n", __func__, hdmimode);

	colorattribute = env_get("colorattribute");
	if (colorattribute)
		printf("%s: colorattribute=%s\n", __func__, colorattribute);

	/* if hpd_st high, output mode will be saved on hdmi side */
	if (!hpd_st) {
		cvbsmode = env_get("cvbsmode");
		if (cvbsmode)
			env_set("outputmode", cvbsmode);
		env_set("hdmichecksum", "0x00000000");
		//run_command("saveenv", 0);
	} else {
		if (!strstr(env_get("outputmode"), "hz"))
			env_set("outputmode", "1080p60hz");
	}

	return 1;
}

static int vout2_hdmi_hpd(int hpd_st)
{
#ifdef CONFIG_AML_LCD
	unsigned int mux_sel = VIU_MUX_MAX, venc_sel = VIU_MUX_MAX;
	char *mode;
#endif
	char *hdmimode;
	char *cvbsmode;
	char *colorattribute;

#ifdef CONFIG_AML_LCD
	mode = env_get("outputmode2");
	mux_sel = aml_lcd_driver_outputmode_check(mode, 0);
	venc_sel = mux_sel & 0xf;
	if (venc_sel == VIU_MUX_ENCL) {
		return 0;
	}
#endif
	/*get hdmi mode and colorattribute from env */
	hdmimode = env_get("hdmimode");
	if (hdmimode)
		printf("%s: hdmimode=%s\n", __func__, hdmimode);
	colorattribute = env_get("colorattribute");
	if (colorattribute)
		printf("%s: colorattribute=%s\n", __func__, colorattribute);
	/* if hpd_st high, output mode will be saved on hdmi side */
	if (!hpd_st) {
		cvbsmode = env_get("cvbsmode");
		if (cvbsmode)
			env_set("outputmode2", cvbsmode);
		env_set("hdmichecksum", "0x00000000");
		//run_command("saveenv", 0);
	} else {
		if (!strstr(env_get("outputmode2"), "hz"))
			env_set("outputmode2", "1080p60hz");
	}

	return 0;
}

int do_hpd_detect(cmd_tbl_t *cmdtp, int flag, int argc,
		  char *const argv[])
{
	char *st;
	int hpd_st = 0;
	unsigned long i = 0;
	/* some TV sets pull hpd high 1.3S after detect pwr5v high */
	unsigned long hdmitx_hpd_wait_cnt = 15;
#ifdef CONFIG_AML_HDMITX20
	struct hdmitx_dev *hdev = hdmitx_get_hdev();
#else
	struct hdmitx_dev *hdev = get_hdmitx21_device();
#endif
	int ret = 0;

	st = env_get("hdmitx_hpd_bypass");
	if (st && (strcmp((const char *)(uintptr_t)st[0], "1") == 0)) {
		printf("hdmitx_hpd_bypass detect\n");
		return 0;
	}
	st = env_get("hdmitx_hpd_wait_cnt");
	if (st)
		hdmitx_hpd_wait_cnt = simple_strtoul(st, NULL, 10);
	hpd_st = hdev->hwop.get_hpd_state();

	if (!hpd_st) {
		/* For some TV, they cost extra time to pullup HPD after 5V */

		for (i = 0; i < hdmitx_hpd_wait_cnt; i++) {
			mdelay(100);
			hpd_st = hdev->hwop.get_hpd_state();
			if (hpd_st) {
				printf("hpd delay %lu ms\n", (i + 1) * 100);
				break;
			}
		}
	}
	printf("%s, hpd_state=%d\n", __func__, hpd_st);

	ret = vout_hdmi_hpd(hpd_st);
	if (!ret)
		vout2_hdmi_hpd(hpd_st);

	hdev->hpd_state = hpd_st;
	return hpd_st;
}
#endif

#if defined(CONFIG_AML_CVBS) || defined(CONFIG_AML_HDMITX) || defined(CONFIG_AML_LCD)
static unsigned int vout_parse_vout_name(char *name)
{
	char *p, *frac_str;
	unsigned int frac = 0;

	p = strchr(name, ',');
	if (!p) {
		frac = 0;
	} else {
		frac_str = p + 1;
		*p = '\0';
		if (strcmp(frac_str, "frac") == 0)
			frac = 1;
	}

	return frac;
}
#endif

static int do_vout_list(cmd_tbl_t * cmdtp, int flag, int argc, char * const argv[])
{
#ifdef CONFIG_AML_HDMITX
#ifdef CONFIG_AML_HDMITX20
	struct hdmitx_dev *hdmitx_device = hdmitx_get_hdev();
#else
	struct hdmitx_dev *hdmitx_device = get_hdmitx21_device();
#endif
#endif

#ifdef CONFIG_AML_HDMITX
	if (!hdmitx_device) {
		printf("\nerror: hdmitx device is null\n");
	} else {
		printf("\nvalid hdmi mode:\n");
		hdmitx_device->hwop.list_support_modes();
	}
#endif

#ifdef CONFIG_AML_CVBS
	printf("\nvalid cvbs mode:\n");
	cvbs_show_valid_vmode();
#endif

#ifdef CONFIG_AML_LCD
	printf("\nvalid lcd mode:\n");
	aml_lcd_driver_list_support_mode();
#endif

	return CMD_RET_SUCCESS;
}

static int do_vout_prepare(cmd_tbl_t *cmdtp, int flag, int argc, char *const argv[])
{
#if defined(CONFIG_AML_CVBS) || defined(CONFIG_AML_HDMITX) || defined(CONFIG_AML_LCD)
	char mode[64]; //use stack instead of heap for smp
	unsigned int mux_sel = VIU_MUX_MAX, venc_sel = VIU_MUX_MAX;
	unsigned int frac;
#endif
#ifdef CONFIG_AML_HDMITX
#ifdef CONFIG_AML_VPP
	unsigned int fmt_mode = 0;
#endif
#endif
#ifdef CONFIG_AML_LCD
	unsigned int venc_index;
#endif

	if (argc != 2)
		return CMD_RET_FAILURE;

#if defined(CONFIG_AML_CVBS) || defined(CONFIG_AML_HDMITX) || defined(CONFIG_AML_LCD)
	memset(mode, 0, 64);
	sprintf(mode, "%s", argv[1]);
	frac = vout_parse_vout_name(mode);
#endif

#ifdef CONFIG_AML_CVBS
	mux_sel = cvbs_outputmode_check(mode, frac);
	venc_sel = mux_sel & 0xf;
	if (venc_sel == VIU_MUX_ENCI) {
		vout_viu_mux(VOUT_VIU2_SEL, mux_sel);
#ifdef CONFIG_AML_VPP
		vpp_viu1_cm_state = VPP_CM_YUV;
		vpp_matrix_update(VPP_CM_YUV);
#endif
		return CMD_RET_SUCCESS;
	}
#endif

#ifdef CONFIG_AML_HDMITX
#ifdef CONFIG_AML_VOUT
#ifdef CONFIG_AML_VPP
	struct vinfo_s *vinfo;

	vinfo = vout_get_current_vinfo();
	fmt_mode = vinfo->vpp_post_out_color_fmt;
#endif
#endif

	if (frac == 0) { /* remove frac support in outputmode */
		mux_sel = hdmi_outputmode_check(mode, frac);
		venc_sel = mux_sel & 0xf;
		if (venc_sel < VIU_MUX_MAX) {
			vout_viu_mux(VOUT_VIU2_SEL, mux_sel);
#ifdef CONFIG_AML_VPP
			if (fmt_mode == 1) {
				vpp_viu1_cm_state = VPP_CM_RGB;
				vpp_matrix_update(VPP_CM_RGB);
			} else {
				vpp_viu1_cm_state = VPP_CM_YUV;
				vpp_matrix_update(VPP_CM_YUV);
			}
#endif
			return CMD_RET_SUCCESS;
		}
	}
#endif

#ifdef CONFIG_AML_LCD
	mux_sel = aml_lcd_driver_outputmode_check(mode, frac);
	venc_sel = mux_sel & 0xf;
	venc_index = (mux_sel >> 4) & 0xf;
	if (venc_sel == VIU_MUX_ENCL) {
		vout_viu_mux(VOUT_VIU2_SEL, mux_sel);
#ifdef CONFIG_AML_VPP
		vpp_viu1_cm_state = VPP_CM_RGB;
		vpp_matrix_update(VPP_CM_RGB);
#endif
		aml_lcd_driver_prepare(venc_index, mode, frac);
		return CMD_RET_SUCCESS;
	}
#endif

	return CMD_RET_FAILURE;
}

static int do_vout_output(cmd_tbl_t *cmdtp, int flag, int argc, char *const argv[])
{
#if defined(CONFIG_AML_CVBS) || defined(CONFIG_AML_HDMITX) || defined(CONFIG_AML_LCD)
	char mode[64]; //use stack instead of heap for smp
	unsigned int frac;
	unsigned int mux_sel = VIU_MUX_MAX, venc_sel = VIU_MUX_MAX;
#endif
#ifdef CONFIG_AML_HDMITX
#ifdef CONFIG_AML_VPP
	unsigned int fmt_mode = 0;
#endif
#endif
#ifdef CONFIG_AML_HDMITX
	char str[64];
#endif
#ifdef CONFIG_AML_LCD
	unsigned int venc_index;
#endif

	if (argc != 2)
		return CMD_RET_FAILURE;

#if defined(CONFIG_AML_CVBS) || defined(CONFIG_AML_HDMITX) || defined(CONFIG_AML_LCD)
	memset(mode, 0, 64);
	sprintf(mode, "%s", argv[1]);
	frac = vout_parse_vout_name(mode);
#endif

#ifdef CONFIG_AML_CVBS
	mux_sel = cvbs_outputmode_check(mode, frac);
	venc_sel = mux_sel & 0xf;
	if (venc_sel == VIU_MUX_ENCI) {
		vout_viu_mux(VOUT_VIU1_SEL, mux_sel);
#ifdef CONFIG_AML_VPP
		if (vpp_viu1_cm_state != VPP_CM_YUV)
			vpp_matrix_update(VPP_CM_YUV);
#endif
		if (cvbs_set_vmode(mode) == 0) {
			run_command("setenv vout_init enable", 0);
			return CMD_RET_SUCCESS;
		}
	}
#endif

#ifdef CONFIG_AML_HDMITX
#ifdef CONFIG_AML_VOUT
#ifdef CONFIG_AML_VPP
	struct vinfo_s *vinfo;

	vinfo = vout_get_current_vinfo();
	fmt_mode = vinfo->vpp_post_out_color_fmt;
#endif
#endif

	if (frac == 0) { /* remove frac support in outputmode */
		mux_sel = hdmi_outputmode_check(mode, frac);
		venc_sel = mux_sel & 0xf;
		if (venc_sel < VIU_MUX_MAX) {
			vout_viu_mux(VOUT_VIU1_SEL, mux_sel);
#ifdef CONFIG_AML_VPP
			if (fmt_mode == 1) {
				if (vpp_viu1_cm_state != VPP_CM_RGB)
					vpp_matrix_update(VPP_CM_RGB);
			} else {
				if (vpp_viu1_cm_state != VPP_CM_YUV)
					vpp_matrix_update(VPP_CM_YUV);
			}
#endif
			/* //remove frac support in outputmode
			 *if (frac)
			 *	setenv("frac_rate_policy", "1");
			 *else
			 *	setenv("frac_rate_policy", "0");
			 */
			memset(str, 0, sizeof(str));
			sprintf(str, "hdmitx output %s", mode);
			if (run_command(str, 0) == CMD_RET_SUCCESS)
				run_command("setenv vout_init enable", 0);
			return CMD_RET_SUCCESS;
		}
	}
#endif

#ifdef CONFIG_AML_LCD
	mux_sel = aml_lcd_driver_outputmode_check(mode, frac);
	venc_sel = mux_sel & 0xf;
	venc_index = (mux_sel >> 4) & 0xf;
	if (venc_sel == VIU_MUX_ENCL) {
		vout_viu_mux(VOUT_VIU1_SEL, mux_sel);
#ifdef CONFIG_AML_VPP
		if (vpp_viu1_cm_state != VPP_CM_RGB)
			vpp_matrix_update(VPP_CM_RGB);
#endif
		aml_lcd_driver_enable(venc_index, mode, frac);
		run_command("setenv vout_init enable", 0);
		return CMD_RET_SUCCESS;
	}
#endif

	printf("outputmode[%s] is invalid\n", argv[1]);

	return CMD_RET_FAILURE;
}

static int do_vout2_list(cmd_tbl_t * cmdtp, int flag, int argc, char * const argv[])
{
#ifdef CONFIG_AML_HDMITX
#ifdef CONFIG_AML_HDMITX20
	struct hdmitx_dev *hdmitx_device = hdmitx_get_hdev();
#else
	struct hdmitx_dev *hdmitx_device = get_hdmitx21_device();
#endif
#endif

#ifdef CONFIG_AML_HDMITX
	if (!hdmitx_device) {
		printf("\nerror: hdmitx device is null\n");
	} else {
		printf("\nvalid hdmi mode:\n");
		hdmitx_device->hwop.list_support_modes();
	}
#endif

#ifdef CONFIG_AML_CVBS
	printf("\nvalid cvbs mode:\n");
	cvbs_show_valid_vmode();
#endif

#ifdef CONFIG_AML_LCD
	printf("\nvalid lcd mode:\n");
	aml_lcd_driver_list_support_mode();
#endif

	return CMD_RET_SUCCESS;
}

static int do_vout2_output(cmd_tbl_t *cmdtp, int flag, int argc, char *const argv[])
{
#if defined(CONFIG_AML_CVBS) || defined(CONFIG_AML_HDMITX) || defined(CONFIG_AML_LCD)
	char mode[64]; //use stack instead of heap for smp
	unsigned int frac;
	unsigned int mux_sel = VIU_MUX_MAX, venc_sel = VIU_MUX_MAX;
#endif
#ifdef CONFIG_AML_HDMITX
	char str[64];
#endif
#ifdef CONFIG_AML_LCD
	unsigned int venc_index;
#endif

#ifdef CONFIG_AML_VPP
	if (get_cpu_id().family_id == MESON_CPU_MAJOR_ID_TXHD2)
		vpp_matrix_update(VPP_CM_RGB);
#endif

	if (argc != 2)
		return CMD_RET_FAILURE;

#if defined(CONFIG_AML_CVBS) || defined(CONFIG_AML_HDMITX) || defined(CONFIG_AML_LCD)
	memset(mode, 0, 64);
	sprintf(mode, "%s", argv[1]);
	frac = vout_parse_vout_name(mode);
#endif

#ifdef CONFIG_AML_CVBS
	mux_sel = cvbs_outputmode_check(mode, frac);
	venc_sel = mux_sel & 0xf;
	if (venc_sel == VIU_MUX_ENCI) {
		if (cvbs_set_vmode(mode) == 0) {
			run_command("setenv vout2_init enable", 0);
			return CMD_RET_SUCCESS;
		}
	}
#endif

#ifdef CONFIG_AML_HDMITX
	if (frac == 0) { /* remove frac support in outputmode */
		mux_sel = hdmi_outputmode_check(mode, frac);
		venc_sel = mux_sel & 0xf;
		if (venc_sel < VIU_MUX_MAX) {
			/* //remove frac support in outputmode
			 *if (frac)
			 *	setenv("frac_rate_policy", "1");
			 *else
			 *	setenv("frac_rate_policy", "0");
			 */
			memset(str, 0, sizeof(str));
			sprintf(str, "hdmitx output %s", mode);
			run_command(str, 0);
			run_command("setenv vout2_init enable", 0);
			return CMD_RET_SUCCESS;
		}
	}
#endif

#ifdef CONFIG_AML_LCD
	mux_sel = aml_lcd_driver_outputmode_check(mode, frac);
	venc_sel = mux_sel & 0xf;
	venc_index = (mux_sel >> 4) & 0xf;
	if (venc_sel == VIU_MUX_ENCL) {
		aml_lcd_driver_enable(venc_index, mode, frac);
		run_command("setenv vout2_init enable", 0);
		return CMD_RET_SUCCESS;
	}
#endif

	printf("outputmode[%s] is invalid\n", argv[1]);

	return CMD_RET_FAILURE;
}

static int do_vout2_prepare(cmd_tbl_t *cmdtp, int flag, int argc, char *const argv[])
{
#if defined(CONFIG_AML_CVBS) || defined(CONFIG_AML_HDMITX) || defined(CONFIG_AML_LCD)
	char mode[64]; //use stack instead of heap for smp
	unsigned int frac;
	unsigned int mux_sel = VIU_MUX_MAX, venc_sel = VIU_MUX_MAX;
#endif
#ifdef CONFIG_AML_LCD
	unsigned int venc_index;
#endif

	if (argc != 2)
		return CMD_RET_FAILURE;

#if defined(CONFIG_AML_CVBS) || defined(CONFIG_AML_HDMITX) || defined(CONFIG_AML_LCD)
	memset(mode, 0, 64);
	sprintf(mode, "%s", argv[1]);
	frac = vout_parse_vout_name(mode);
#endif

#ifdef CONFIG_AML_CVBS
	mux_sel = cvbs_outputmode_check(mode, frac);
	venc_sel = mux_sel & 0xf;
	if (venc_sel == VIU_MUX_ENCI) {
		vout_viu_mux(VOUT_VIU2_SEL, mux_sel);
#ifdef CONFIG_AML_VPP
		vpp_viu2_matrix_update(VPP_CM_YUV);
#endif
		return CMD_RET_SUCCESS;
	}
#endif

#ifdef CONFIG_AML_HDMITX
	mux_sel = hdmi_outputmode_check(mode, frac);
	venc_sel = mux_sel & 0xf;
	if (venc_sel < VIU_MUX_MAX) {
		vout_viu_mux(VOUT_VIU2_SEL, mux_sel);
#ifdef CONFIG_AML_VPP
		vpp_viu2_matrix_update(VPP_CM_YUV);
#endif
		return CMD_RET_SUCCESS;
	}
#endif

#ifdef CONFIG_AML_LCD
	mux_sel = aml_lcd_driver_outputmode_check(mode, frac);
	venc_sel = mux_sel & 0xf;
	venc_index = (mux_sel >> 4) & 0xf;
	if (venc_sel == VIU_MUX_ENCL) {
		vout_viu_mux(VOUT_VIU2_SEL, mux_sel);
#ifdef CONFIG_AML_VPP
		vpp_viu2_matrix_update(VPP_CM_RGB);
#endif
		aml_lcd_driver_prepare(venc_index, mode, frac);
		return CMD_RET_SUCCESS;
	}
#endif

	return CMD_RET_FAILURE;
}

static int do_vout3_list(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
#ifdef CONFIG_AML_HDMITX
#ifdef CONFIG_AML_HDMITX20
	struct hdmitx_dev *hdmitx_device = hdmitx_get_hdev();
#else
	struct hdmitx_dev *hdmitx_device = get_hdmitx21_device();
#endif
#endif

#ifdef CONFIG_AML_HDMITX
	if (!hdmitx_device) {
		printf("\nerror: hdmitx device is null\n");
	} else {
		printf("\nvalid hdmi mode:\n");
		hdmitx_device->hwop.list_support_modes();
	}
#endif

#ifdef CONFIG_AML_CVBS
	printf("\nvalid cvbs mode:\n");
	cvbs_show_valid_vmode();
#endif

#ifdef CONFIG_AML_LCD
	printf("\nvalid lcd mode:\n");
	aml_lcd_driver_list_support_mode();
#endif

	return CMD_RET_SUCCESS;
}

static int do_vout3_output(cmd_tbl_t *cmdtp, int flag, int argc, char *const argv[])
{
#if defined(CONFIG_AML_CVBS) || defined(CONFIG_AML_HDMITX) || defined(CONFIG_AML_LCD)
	char mode[64]; //use stack instead of heap for smp
	unsigned int frac;
	unsigned int mux_sel = VIU_MUX_MAX, venc_sel = VIU_MUX_MAX;
#endif
#ifdef CONFIG_AML_HDMITX
	char str[64];
#endif
#ifdef CONFIG_AML_LCD
	unsigned int venc_index;
#endif

	if (argc != 2)
		return CMD_RET_FAILURE;

#if defined(CONFIG_AML_CVBS) || defined(CONFIG_AML_HDMITX) || defined(CONFIG_AML_LCD)
	memset(mode, 0, 64);
	sprintf(mode, "%s", argv[1]);
	frac = vout_parse_vout_name(mode);
#endif

#ifdef CONFIG_AML_CVBS
	mux_sel = cvbs_outputmode_check(mode, frac);
	venc_sel = mux_sel & 0xf;
	if (venc_sel == VIU_MUX_ENCI) {
		if (cvbs_set_vmode(mode) == 0) {
			run_command("setenv vout3_init enable", 0);
			return CMD_RET_SUCCESS;
		}
	}
#endif

#ifdef CONFIG_AML_HDMITX
	if (frac == 0) { /* remove frac support in outputmode */
		mux_sel = hdmi_outputmode_check(mode, frac);
		venc_sel = mux_sel & 0xf;
		if (venc_sel < VIU_MUX_MAX) {
			/* //remove frac support in outputmode
			 *if (frac)
			 *	setenv("frac_rate_policy", "1");
			 *else
			 *	setenv("frac_rate_policy", "0");
			 */
			memset(str, 0, sizeof(str));
			sprintf(str, "hdmitx output %s", mode);
			run_command(str, 0);
			run_command("setenv vout3_init enable", 0);
			return CMD_RET_SUCCESS;
		}
	}
#endif

#ifdef CONFIG_AML_LCD
	mux_sel = aml_lcd_driver_outputmode_check(mode, frac);
	venc_sel = mux_sel & 0xf;
	venc_index = (mux_sel >> 4) & 0xf;
	if (venc_sel == VIU_MUX_ENCL) {
		aml_lcd_driver_enable(venc_index, mode, frac);
		run_command("setenv vout3_init enable", 0);
		return CMD_RET_SUCCESS;
	}
#endif

	printf("outputmode[%s] is invalid\n", argv[1]);

	return CMD_RET_FAILURE;
}

static int do_vout3_prepare(cmd_tbl_t *cmdtp, int flag, int argc, char *const argv[])
{
#if defined(CONFIG_AML_CVBS) || defined(CONFIG_AML_HDMITX) || defined(CONFIG_AML_LCD)
	char mode[64]; //use stack instead of heap for smp
	unsigned int frac;
	unsigned int mux_sel = VIU_MUX_MAX, venc_sel = VIU_MUX_MAX;
#endif
#ifdef CONFIG_AML_LCD
	unsigned int venc_index;
#endif

	if (argc != 2)
		return CMD_RET_FAILURE;

#if defined(CONFIG_AML_CVBS) || defined(CONFIG_AML_HDMITX) || defined(CONFIG_AML_LCD)
	memset(mode, 0, 64);
	sprintf(mode, "%s", argv[1]);
	frac = vout_parse_vout_name(mode);
#endif

#ifdef CONFIG_AML_CVBS
	mux_sel = cvbs_outputmode_check(mode, frac);
	venc_sel = mux_sel & 0xf;
	if (venc_sel == VIU_MUX_ENCI) {
		vout_viu_mux(VOUT_VIU3_SEL, mux_sel);
#ifdef CONFIG_AML_VPP
		vpp_viu3_matrix_update(VPP_CM_YUV);
#endif
		return CMD_RET_SUCCESS;
	}
#endif

#ifdef CONFIG_AML_HDMITX
	mux_sel = hdmi_outputmode_check(mode, frac);
	venc_sel = mux_sel & 0xf;
	if (venc_sel < VIU_MUX_MAX) {
		vout_viu_mux(VOUT_VIU3_SEL, mux_sel);
#ifdef CONFIG_AML_VPP
		vpp_viu3_matrix_update(VPP_CM_YUV);
#endif
		return CMD_RET_SUCCESS;
	}
#endif

#ifdef CONFIG_AML_LCD
	mux_sel = aml_lcd_driver_outputmode_check(mode, frac);
	venc_sel = mux_sel & 0xf;
	venc_index = (mux_sel >> 4) & 0xf;
	if (venc_sel == VIU_MUX_ENCL) {
		vout_viu_mux(VOUT_VIU3_SEL, mux_sel);
#ifdef CONFIG_AML_VPP
		//vpp_viu2_matrix_update(VPP_CM_RGB);
#endif
		aml_lcd_driver_prepare(venc_index, mode, frac);
		return CMD_RET_SUCCESS;
	}
#endif

	return CMD_RET_FAILURE;
}

static int do_vout_info(cmd_tbl_t * cmdtp, int flag, int argc, char * const argv[])
{
	vout_vinfo_dump();

	return CMD_RET_SUCCESS;
}

static cmd_tbl_t cmd_vout_sub[] = {
	U_BOOT_CMD_MKENT(list, 1, 1, do_vout_list, "", ""),
	U_BOOT_CMD_MKENT(prepare, 3, 1, do_vout_prepare, "", ""),
	U_BOOT_CMD_MKENT(output, 3, 1, do_vout_output, "", ""),
	U_BOOT_CMD_MKENT(info, 1, 1, do_vout_info, "", ""),
};

static int do_vout(cmd_tbl_t *cmdtp, int flag, int argc, char *const argv[])
{
	cmd_tbl_t *c;

	if (argc < 2)
		return cmd_usage(cmdtp);

	argc--;
	argv++;

	c = find_cmd_tbl(argv[0], &cmd_vout_sub[0], ARRAY_SIZE(cmd_vout_sub));

	if (c)
		return  c->cmd(cmdtp, flag, argc, argv);
	else
		return cmd_usage(cmdtp);
}

U_BOOT_CMD(vout, CONFIG_SYS_MAXARGS, 1, do_vout,
	"VOUT sub-system",
	"vout [list | output format | info]\n"
	"    list : list for valid video mode names.\n"
	"    format : perfered output video mode\n"
	"    info : dump vinfo\n"
);

static cmd_tbl_t cmd_vout2_sub[] = {
	U_BOOT_CMD_MKENT(list, 1, 1, do_vout2_list, "", ""),
	U_BOOT_CMD_MKENT(prepare, 3, 1, do_vout2_prepare, "", ""),
	U_BOOT_CMD_MKENT(output, 3, 1, do_vout2_output, "", ""),
	U_BOOT_CMD_MKENT(info, 1, 1, do_vout_info, "", ""),
};

static int do_vout2(cmd_tbl_t *cmdtp, int flag, int argc, char *const argv[])
{
	cmd_tbl_t *c;

	if (argc < 2)
		return cmd_usage(cmdtp);

	argc--;
	argv++;

	c = find_cmd_tbl(argv[0], &cmd_vout2_sub[0], ARRAY_SIZE(cmd_vout2_sub));

	if (c)
		return  c->cmd(cmdtp, flag, argc, argv);
	else
		return cmd_usage(cmdtp);
}

U_BOOT_CMD(vout2, CONFIG_SYS_MAXARGS, 1, do_vout2,
	"VOUT2 sub-system",
	"vout2 [list | prepare format | output format | info]\n"
	"    list : list for valid video mode names.\n"
	"    format : perfered output video mode\n"
	"    info : dump vinfo\n"
);

static cmd_tbl_t cmd_vout3_sub[] = {
	U_BOOT_CMD_MKENT(list, 1, 1, do_vout3_list, "", ""),
	U_BOOT_CMD_MKENT(prepare, 3, 1, do_vout3_prepare, "", ""),
	U_BOOT_CMD_MKENT(output, 3, 1, do_vout3_output, "", ""),
	U_BOOT_CMD_MKENT(info, 1, 1, do_vout_info, "", ""),
};

static int do_vout3(cmd_tbl_t *cmdtp, int flag, int argc, char *const argv[])
{
	cmd_tbl_t *c;

	if (argc < 2)
		return cmd_usage(cmdtp);

	argc--;
	argv++;

	c = find_cmd_tbl(argv[0], &cmd_vout3_sub[0], ARRAY_SIZE(cmd_vout3_sub));

	if (c)
		return  c->cmd(cmdtp, flag, argc, argv);
	else
		return cmd_usage(cmdtp);
}

U_BOOT_CMD(vout3, CONFIG_SYS_MAXARGS, 1, do_vout3,
	"VOUT3 sub-system",
	"vout3 [list | prepare format | output format | info]\n"
	"    list : list for valid video mode names.\n"
	"    format : perfered output video mode\n"
	"    info : dump vinfo\n"
);

