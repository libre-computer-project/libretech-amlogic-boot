// SPDX-License-Identifier: (GPL-2.0+ OR MIT)
/*
 * Copyright (c) 2019 Amlogic, Inc. All rights reserved.
 */

#include <common.h>
#include <command.h>
#include <environment.h>
#include <malloc.h>
#include <asm/byteorder.h>
#ifdef CONFIG_AML_HDMITX20
#include <amlogic/media/vout/hdmitx/hdmitx.h>
#else
#include <amlogic/media/vout/hdmitx21/hdmitx.h>
#endif
#include <amlogic/media/dv/dolby_vision.h>
#include <asm/arch/cpu.h>
#include <amlogic/cpu_id.h>

#define DV_MODE_720P50HZ                "720p50hz"
#define DV_MODE_720P                    "720p60hz"
#define DV_MODE_1080P24HZ               "1080p24hz"
#define DV_MODE_1080P50HZ               "1080p50hz"
#define DV_MODE_1080P                   "1080p60hz"
#define DV_MODE_4K2K24HZ                "2160p24hz"
#define DV_MODE_4K2K25HZ                "2160p25hz"
#define DV_MODE_4K2K30HZ                "2160p30hz"
#define DV_MODE_4K2K50HZ                "2160p50hz"
#define DV_MODE_4K2K60HZ                "2160p60hz"
#define DV_MODE_LIST_SIZE               10

#define MODE_640x480p                   "640x480p60hz"
#define MODE_480I                       "480i60hz"
#define MODE_480P                       "480p60hz"
#define MODE_480CVBS                    "480cvbs"
#define MODE_576I                       "576i50hz"
#define MODE_576P                       "576p50hz"
#define MODE_576CVBS                    "576cvbs"
#define MODE_720P50HZ                   "720p50hz"
#define MODE_720P                       "720p60hz"
#define MODE_720P100HZ                  "1280x720p100hz"
#define MODE_720P120HZ                  "1280x720p120hz"
#define MODE_768P                       "768p60hz"
#define MODE_1080P24HZ                  "1080p24hz"
#define MODE_1080P25HZ                  "1080p25hz"
#define MODE_1080P30HZ                  "1080p30hz"
#define MODE_1080I50HZ                  "1080i50hz"
#define MODE_1080P50HZ                  "1080p50hz"
#define MODE_1080I                      "1080i60hz"
#define MODE_1080P                      "1080p60hz"
#define MODE_1080P100HZ                 "1920x1080p100hz"
#define MODE_1080P120HZ                 "1920x1080p120hz"
#define MODE_1440P50HZ                  "2560x1440p50hz"
#define MODE_1440P60HZ                  "2560x1440p60hz"
#define MODE_1440P100HZ                 "2560x1440p100hz"
#define MODE_1440P120HZ                 "2560x1440p120hz"

#define MODE_4K2K24HZ                   "2160p24hz"
#define MODE_4K2K25HZ                   "2160p25hz"
#define MODE_4K2K30HZ                   "2160p30hz"
#define MODE_4K2K50HZ                   "2160p50hz"
#define MODE_4K2K60HZ                   "2160p60hz"

#define MODE_4K2K100HZ                  "3840x2160p100hz"
#define MODE_4K2K120HZ                  "3840x2160p120hz"
#define MODE_4K2KSMPTE                  "smpte24hz"
#define MODE_4K2KSMPTE30HZ              "smpte30hz"
#define MODE_4K2KSMPTE50HZ              "smpte50hz"
#define MODE_4K2KSMPTE60HZ              "smpte60hz"
#define MODE_8K4K24HZ                   "7680x4320p24hz"
#define MODE_8K4K25HZ                   "7680x4320p25hz"
#define MODE_8K4K30HZ                   "7680x4320p30hz"
#define MODE_8K4K48HZ                   "7680x4320p48hz"
#define MODE_8K4K50HZ                   "7680x4320p50hz"
#define MODE_8K4K60HZ                   "7680x4320p60hz"

#define MODE_PANEL                      "panel"
#define MODE_PAL_M                      "pal_m"
#define MODE_PAL_N                      "pal_n"
#define MODE_NTSC_M                     "ntsc_m"

#define COLOR_YCBCR444_12BIT             "444,12bit"
#define COLOR_YCBCR444_10BIT             "444,10bit"
#define COLOR_YCBCR444_8BIT              "444,8bit"
#define COLOR_YCBCR422_12BIT             "422,12bit"
#define COLOR_YCBCR422_10BIT             "422,10bit"
#define COLOR_YCBCR422_8BIT              "422,8bit"
#define COLOR_YCBCR420_12BIT             "420,12bit"
#define COLOR_YCBCR420_10BIT             "420,10bit"
#define COLOR_YCBCR420_8BIT              "420,8bit"
#define COLOR_RGB_12BIT                  "rgb,12bit"
#define COLOR_RGB_10BIT                  "rgb,10bit"
#define COLOR_RGB_8BIT                   "rgb,8bit"

static const char *DISPLAY_MODE_LIST[] = {
	MODE_640x480p,
	MODE_480I,
	MODE_480P,
	/* MODE_480CVBS, */
	MODE_576I,
	MODE_576P,
	/* MODE_576CVBS, */
	MODE_720P,
	MODE_720P50HZ,
	MODE_720P100HZ,
	MODE_720P120HZ,
	MODE_1080P24HZ,
	MODE_1080P25HZ,
	MODE_1080P30HZ,
	MODE_1080I50HZ,
	MODE_1080P50HZ,
	MODE_1080I,
	MODE_1080P,
	MODE_1080P100HZ,
	MODE_1080P120HZ,
	MODE_1440P50HZ,
	MODE_1440P60HZ,
	MODE_1440P100HZ,
	MODE_1440P120HZ,
	MODE_4K2K24HZ,
	MODE_4K2K25HZ,
	MODE_4K2K30HZ,
	MODE_4K2K50HZ,
	MODE_4K2K60HZ,
	MODE_4K2KSMPTE,
	MODE_4K2KSMPTE30HZ,
	MODE_4K2KSMPTE50HZ,
	MODE_4K2KSMPTE60HZ,
	MODE_4K2K100HZ,
	MODE_4K2K120HZ,
	MODE_8K4K24HZ,
	MODE_8K4K25HZ,
	MODE_8K4K30HZ,
	MODE_8K4K48HZ,
	MODE_8K4K50HZ,
	MODE_8K4K60HZ
	/* MODE_768P,  */
	/* MODE_PANEL, */
	/* MODE_PAL_M, */
	/* MODE_PAL_N, */
	/* MODE_NTSC_M, */
};

/* for check hdr 4k support or not */
static const char * const MODE_4K_LIST[] = {
	MODE_4K2K60HZ,
	MODE_4K2K50HZ,
};

/* for check hdr non-4k support or not
 * interface mode is lower priority as some android
 * version may removed interlace mode.
 * descending order
 */
static const char * const MODE_NON4K_LIST[] = {
	MODE_1080P,
	MODE_1080P50HZ,
	MODE_720P,
	MODE_720P50HZ,
	MODE_576P,
	MODE_480P,
	MODE_1080I,
	MODE_1080I50HZ,
	MODE_576I,
	MODE_480I,
};

/* ascending order */
static const char *MODE_RESOLUTION_FIRST[] = {
	MODE_480I,
	MODE_576I,
	MODE_1080I50HZ,
	MODE_1080I,
	MODE_640x480p,
	MODE_480P,
	MODE_576P,
	MODE_720P50HZ,
	MODE_720P,
	MODE_1080P50HZ,
	MODE_1080P,
	MODE_4K2K24HZ,
	MODE_4K2K25HZ,
	MODE_4K2K30HZ,
	MODE_4K2K50HZ,
	MODE_4K2K60HZ,
	MODE_8K4K24HZ,
	MODE_8K4K25HZ,
	MODE_8K4K30HZ,
	MODE_8K4K48HZ,
	MODE_8K4K50HZ,
	MODE_8K4K60HZ
};

/* ascending order */
static const char *MODE_FRAMERATE_FIRST[] = {
	MODE_480I,
	MODE_576I,
	MODE_1080I50HZ,
	MODE_1080I,
	MODE_640x480p,
	MODE_480P,
	MODE_576P,
	MODE_720P50HZ,
	MODE_720P,
	MODE_4K2K24HZ,
	MODE_4K2K25HZ,
	MODE_4K2K30HZ,
	MODE_1080P50HZ,
	MODE_1080P,
	MODE_4K2K50HZ,
	MODE_4K2K60HZ,
	MODE_8K4K50HZ,
	MODE_8K4K60HZ
};

/* this is prior selected list for sdr of
 * 4k2k50hz, 4k2k60hz smpte50hz, smpte60hz
 * for user change resolution case in sysctl.
 * descending order
 */
static const char *COLOR_ATTRIBUTE_LIST1[] = {
	COLOR_YCBCR420_10BIT,
	COLOR_YCBCR422_12BIT,
	COLOR_YCBCR420_8BIT,
	COLOR_YCBCR444_8BIT,
	COLOR_RGB_8BIT
};

/* this is prior selected list for hdr and sdr of
 * non 4k50/60hz display mode.
 * under HDR priority && auto best is off, it may
 * change from TV_A (1080p60hz 444,10bit HDR) to
 * TV_B witch support 1080p60hz 444,8bit maximum.
 * should keep mode(1080p60hz) witch user selected,
 * and 8bit depth(sdr) is kept in select list for
 * safety of corner case.
 * i.e. if HDR cs/cd is not supported, may select
 * 8bit mode.
 * also for user change resolution case in sysctl.
 * descending order
 */
static const char *COLOR_ATTRIBUTE_LIST2[] = {
	COLOR_YCBCR422_12BIT,
	COLOR_YCBCR444_10BIT,
	COLOR_RGB_10BIT,
	COLOR_YCBCR444_8BIT,
	COLOR_RGB_8BIT
};

/* this is prior selected list for sdr of
 * non 4k50/60hz display mode
 * descending order
 */
static const char *SDR_NON4K_COLOR_ATTRIBUTE_LIST[] = {
	COLOR_YCBCR444_8BIT,
	COLOR_RGB_8BIT,
	COLOR_YCBCR422_12BIT,
	COLOR_YCBCR444_10BIT,
	COLOR_RGB_10BIT,
};

/* this is prior selected list of Low Power Mode
 * 4k2k50hz, 4k2k60hz smpte50hz, smpte60hz
 */
static const char *COLOR_ATTRIBUTE_LIST3[] = {
	COLOR_YCBCR420_8BIT,
	COLOR_YCBCR420_10BIT,
	COLOR_YCBCR422_8BIT,
	COLOR_YCBCR422_10BIT,
	COLOR_YCBCR444_8BIT,
	COLOR_RGB_8BIT,
	COLOR_YCBCR420_12BIT,
	COLOR_YCBCR422_12BIT
};

/* this is prior selected list of
 * Low Power Mode other display mode
 */
static const char *COLOR_ATTRIBUTE_LIST4[] = {
	COLOR_YCBCR444_8BIT,
	COLOR_YCBCR422_8BIT,
	COLOR_RGB_8BIT,
	COLOR_YCBCR444_10BIT,
	COLOR_YCBCR422_10BIT,
	COLOR_RGB_10BIT,
	COLOR_YCBCR444_12BIT,
	COLOR_YCBCR422_12BIT,
	COLOR_RGB_12BIT
};

/* this is prior selected list of HDR non 4k50/60 colorspace
 * descending order
 */
static const char *HDR_NON4K_COLOR_ATTRIBUTE_LIST[] = {
	COLOR_YCBCR422_12BIT,
	COLOR_YCBCR444_10BIT,
	COLOR_RGB_10BIT,
	COLOR_YCBCR444_12BIT,
	COLOR_RGB_12BIT,
};

/* this is prior selected list of HDR 4k colorspace(2160p60hz/2160p50hz)
 * descending order
 */
static const char *HDR_4K_COLOR_ATTRIBUTE_LIST[] = {
	COLOR_YCBCR420_10BIT,
	COLOR_YCBCR422_12BIT,
};

/* support format lists */
static const char *disp_mode_t[] = {
	"480i60hz", /* 16:9 */
	"576i50hz",
	"480p60hz",
	"576p50hz",
	"720p60hz",
	"1080i60hz",
	"1080p60hz",
	"1080p120hz",
	"720p50hz",
	"1080i50hz",
	"1080p30hz",
	"1080p50hz",
	"1080p25hz",
	"1080p24hz",
	"2560x1080p50hz",
	"2560x1080p60hz",
	"2160p30hz",
	"2160p25hz",
	"2160p24hz",
	"smpte24hz",
	"smpte25hz",
	"smpte30hz",
	"smpte50hz",
	"smpte60hz",
	"2160p50hz",
	"2160p60hz",
	/* VESA modes */
	"640x480p60hz",
	"800x480p60hz",
	"800x600p60hz",
	"852x480p60hz",
	"854x480p60hz",
	"1024x600p60hz",
	"1024x768p60hz",
	"1152x864p75hz",
	"1280x600p60hz",
	"1280x768p60hz",
	"1280x800p60hz",
	"1280x960p60hz",
	"1280x1024p60hz",
	"1360x768p60hz",
	"1366x768p60hz",
	"1400x1050p60hz",
	"1440x900p60hz",
	"1440x2560p60hz",
	"1600x900p60hz",
	"1600x1200p60hz",
	"1680x1050p60hz",
	"1920x1200p60hz",
	"2160x1200p90hz",
	"2560x1440p60hz",
	"2560x1600p60hz",
	"3440x1440p60hz",
	"2400x1200p90hz",
	"3840x1080p60hz",
	NULL
};

static bool hdmi_sink_disp_mode_sup(struct input_hdmi_data *hdmi_data, char *disp_mode);

static bool is_best_outputmode(void)
{
	char *is_bestmode = env_get("is.bestmode");

	return !is_bestmode || (strcmp(is_bestmode, "true") == 0);
}

static bool is_best_color_space(void)
{
	char *user_cs = env_get("user_colorattribute");

	if (!user_cs)
		return true;
	else if (!strstr(user_cs, "bit"))
		return true;

	return false;
}

static bool is_framerate_priority(void)
{
	char *framerate_priority = env_get("framerate_priority");

	return !framerate_priority || (strcmp(framerate_priority, "true") == 0);
}

/* Hdr Resolution Priority enable or not, false:disable true:enable
 * note that the ubootenv name may be confused. the actual meaning is:
 * when connected to HDR TV which only support 4K60hz 420_8bit maximum,
 * if this ubootenv is true/null, then it will select 1080p deep_color
 * (thus to output HDR) as netflix request;
 * if this ubootenv is false, then it will select 4k with 8bit(SDR)
 * for special project usage.
 */
static bool is_hdr_resolution_priority(void)
{
	char *hdr_resolution_priority = env_get("hdr_resolution_priority");

	return !hdr_resolution_priority || (strcmp(hdr_resolution_priority, "true") == 0);
}

/* import from kernel */
static inline bool package_id_is(unsigned int id)
{
	return get_cpu_id().package_id == id;
}

static inline bool is_meson_gxl_cpu(void)
{
	return get_cpu_id().family_id == MESON_CPU_MAJOR_ID_GXL;
}

static inline bool is_meson_gxl_package_805X(void)
{
	return is_meson_gxl_cpu() && package_id_is(0x30);
}

static inline bool is_meson_gxl_package_805Y(void)
{
	return is_meson_gxl_cpu() && package_id_is(0xb0);
}

/* below items has feature limited, may need extra judgement */
bool is_hdmitx_limited_1080p(void)
{
#ifdef CONFIG_AML_HDMITX20
	struct hdmitx_dev *hdev = hdmitx_get_hdev();
#else
	struct hdmitx_dev *hdev = get_hdmitx21_device();
#endif

	if (is_meson_gxl_package_805X())
		return true;
	else if (is_meson_gxl_package_805Y())
		return true;
	else if (hdev->limit_res_1080p == 1)
		return true;
	else
		return false;
}

bool is_support_4k(void)
{
	if (is_hdmitx_limited_1080p())
		return false;
	return true;
}

static bool is_support_deepcolor(void)
{
	return true;
}

static bool is_low_powermode(void)
{
	return false;
}

/* for application, the actually hdr_priority may be 0x10000030
 * and the string hdr_priority will be like 268435504
 * so here needs coverting such string to hex value
 */
int get_hdr_strategy_priority(void)
{
	unsigned int hdr_strategy_priority = 0;

	hdr_strategy_priority = env_get_ulong("hdr_priority", 10, ~0UL);
	return (int)hdr_strategy_priority;
}

static int get_hdr_priority(void)
{
	unsigned int hdr_priority = get_hdr_strategy_priority();
	hdr_priority_e value = DOLBY_VISION_PRIORITY;

	if (hdr_priority != -1) {
		if (((hdr_priority >> 28) & 0xf) == 0) {
			unsigned int strategy1 = hdr_priority & 0xf;

			if (strategy1 == 2)
				value = SDR_PRIORITY;
			else if (strategy1 == 1)
				value = HDR10_PRIORITY;
			else
				value = DOLBY_VISION_PRIORITY;
		}
	} else {
		value = DOLBY_VISION_PRIORITY;
	}

	return (int)value;
}

int get_hdr_policy(void)
{
	char *hdr_policy = env_get("hdr_policy");
	hdr_policy_e value = HDR_POLICY_SINK;

	if (hdr_policy) {
		if (strcmp(hdr_policy, "0") == 0)
			value = HDR_POLICY_SINK;
		else if (strcmp(hdr_policy, "1") == 0)
			value = HDR_POLICY_SOURCE;
		else if (strcmp(hdr_policy, "4") == 0)
			value = HDR_POLICY_FORCE;
		else
			printf("error ubootenv value of hdr_policy\n");
	} else {
		value = HDR_POLICY_SINK;
	}

	return (int)value;
}

static hdr_force_mode_e get_hdr_force_mode(void)
{
	char *hdr_force_mode = env_get("hdr_force_mode");
	int force_mode = 0;

	if (hdr_force_mode)
		force_mode = strtoul(hdr_force_mode, NULL, 10);
	else
		force_mode = FORCE_DV;

	return (hdr_force_mode_e)force_mode;
}

bool is_tv_support_hdr(struct hdmitx_dev *hdev)
{
	struct hdr_info *hdr;
	struct hdr10_plus_info *hdr10p;

	if (!hdev)
		return false;
	hdr = &hdev->RXCap.hdr_info;
	hdr10p = &hdev->RXCap.hdr10plus_info;
	if (hdr->hdr_sup_eotf_smpte_st_2084 || hdr->hdr_sup_eotf_hlg)
		return true;
	if (hdr10p->ieeeoui == HDR10_PLUS_IEEE_OUI &&
		hdr10p->application_version != 0xFF)
		return true;
	return false;
}

bool is_tv_support_dv(struct hdmitx_dev *hdev)
{
	/*todo*/
	struct dv_info *dv;

	if (!hdev)
		return false;
	dv = &(hdev->RXCap.dv_info);

	if ((dv->ieeeoui != DV_IEEE_OUI) || (dv->block_flag != CORRECT))
		return false;
	return true;
}

bool is_dv_preference(struct hdmitx_dev *hdev)
{
	int hdr_priority = get_hdr_priority();
	hdr_policy_e hdr_policy = get_hdr_policy();
	hdr_force_mode_e hdr_force_mode = get_hdr_force_mode();

	if (!hdev)
		return false;
	if (hdr_priority != DOLBY_VISION_PRIORITY) {
		printf("not prefer dv, hdr_priority:%d\n", hdr_priority);
		return false;
	}

	/* not force dv */
	if (hdr_policy == HDR_POLICY_FORCE &&
		hdr_force_mode != MESON_HDR_FORCE_MODE_DV) {
		printf("not force dv, hdr_policy:%d hdr_force_mode:%d\n",
			hdr_policy, hdr_force_mode);
	return false;
	}

	if (is_dolby_enabled() && is_tv_support_dv(hdev))
		return true;
	else
		return false;
}

bool is_hdr_preference(struct hdmitx_dev *hdev)
{
	int hdr_priority = get_hdr_priority();
	hdr_policy_e hdr_policy = get_hdr_policy();
	hdr_force_mode_e hdr_force_mode = get_hdr_force_mode();
	bool hdr_resolution_priority = is_hdr_resolution_priority();

	if (!hdev)
		return false;

	/* not prefer hdr */
	if (!hdr_resolution_priority) {
		printf("not prefer hdr, hdr_resolution_priority:%d\n", hdr_resolution_priority);
		return false;
	}
	/* not force hdr */
	if (hdr_policy == HDR_POLICY_FORCE &&
		!(hdr_force_mode == MESON_HDR_FORCE_MODE_HDR10 ||
		hdr_force_mode == MESON_HDR_FORCE_MODE_HLG ||
		hdr_force_mode == MESON_HDR_FORCE_MODE_HDR10PLUS)) {
		printf("not force hdr, hdr_policy:%d hdr_force_mode:%d\n",
			hdr_policy, hdr_force_mode);
		return false;
	}

	if ((hdr_priority == DOLBY_VISION_PRIORITY ||
		hdr_priority == HDR10_PRIORITY) &&
		is_tv_support_hdr(hdev))
		return true;
	else
		return false;
}

/* decide output dolby status by uboot dolby vision driver */
/* uboot hdmi driver will update this value follow below policy,
 * 1.hdr_policy = always
 * dv type = sink-led -> dolby_status = 1
 * dv type = source-led -> dolby_status = 2
 * dv type = dolby disable -> dolby_status = 0
 * 2.hdr_policy = adaptive -> dolby_status = 0

 * systemcontrol save current dv output status
 * dolby_status = 0 -> dolby vision disable
 * dolby_status = 1 -> std mode(sink-led)
 * dolby_status = 2 -> LL YUV(source-led)
 * dolby_status = 3 -> LL RGB
 */
int get_ubootenv_dv_status(void)
{
	char *dolby_status = NULL;

	dolby_status = env_get("dolby_status");

	if (!dolby_status) {
		printf("no ubootenv dolby_status\n");
		return DOLBY_VISION_DISABLE;
	}
	if (!strcmp(dolby_status, DOLBY_VISION_SET_STD))
		return DOLBY_VISION_STD_ENABLE;
	else if (!strcmp(dolby_status, DOLBY_VISION_SET_LL_YUV))
		return DOLBY_VISION_LL_YUV;
	else if (!strcmp(dolby_status, DOLBY_VISION_SET_LL_RGB))
		return DOLBY_VISION_LL_RGB;
	else
		return DOLBY_VISION_DISABLE;
}

/* user_prefer_dv_type is used to save user select dolby vision
 * output mode. Note: if the user has not set it, it will be empty or "none".
 * dv_type = 0 ->dolby vision disable
 * dv_type = 1 ->std mode(sink-led)
 * dv_type = 2 ->LL YUV(source-led)
 * dv_type = 3 ->LL RGB
 */
int get_ubootenv_dv_type(void)
{
	char *dv_type = NULL;

	dv_type = env_get("user_prefer_dv_type");

	if (!dv_type) {
		printf("no ubootenv user_prefer_dv_type\n");
		return DV_NONE;
	}
	if (!strcmp(dv_type, "none"))
		return DV_NONE;
	else if (!strcmp(dv_type, DOLBY_VISION_SET_STD))
		return DOLBY_VISION_STD_ENABLE;
	else if (!strcmp(dv_type, DOLBY_VISION_SET_LL_YUV))
		return DOLBY_VISION_LL_YUV;
	else if (!strcmp(dv_type, DOLBY_VISION_SET_LL_RGB))
		return DOLBY_VISION_LL_RGB;
	else
		return DOLBY_VISION_DISABLE;
}

bool is_dolby_enabled(void)
{
	if (get_ubootenv_dv_status() != DOLBY_VISION_DISABLE)
		return true;
	else
		return false;
}

static int resolve_resolution_value(const char *mode, int flag)
{
	bool validmode = false;
	int i;

	if (!mode)
		return -1;

	if (strlen(mode) != 0) {
		for (i = 0; i < ARRAY_SIZE(DISPLAY_MODE_LIST); i++) {
			if (strcmp(mode, DISPLAY_MODE_LIST[i]) == 0) {
				validmode = true;
				break;
			}
		}
	}
	if (!validmode) {
		printf("the resolveResolution mode [%s] is not valid\n", mode);
		return -1;
	}

	if (is_framerate_priority() && flag == FRAMERATE_PRIORITY) {
		for (i = 0; i < ARRAY_SIZE(MODE_FRAMERATE_FIRST); i++) {
			if (strcmp(mode, MODE_FRAMERATE_FIRST[i]) == 0)
				return i;
		}
	} else {
		for (i = 0; i < ARRAY_SIZE(MODE_RESOLUTION_FIRST); i++) {
			if (strcmp(mode, MODE_RESOLUTION_FIRST[i]) == 0)
				return i;
		}
	}

	return -1;
}

/* need update DV CAP */
static int update_dv_type(struct input_hdmi_data *hdmi_data)
{
	/* 1.read dolby vision mode from prop(env) */
	int type;
	struct dv_info *dv = NULL;

	if (!hdmi_data)
		return DOLBY_VISION_DISABLE;

	type = hdmi_data->ubootenv_dv_type;
	dv = &hdmi_data->prxcap->dv_info;

	/* 2.check tv support or not */
	if ((type == 1) && (dv->support_DV_RGB_444_8BIT == 1)) {
		return DOLBY_VISION_STD_ENABLE;
	} else if ((type == 2) && (dv->support_LL_YCbCr_422_12BIT == 1)) {
		return DOLBY_VISION_LL_YUV;
	} else if ((type == 3) &&
		((dv->support_LL_RGB_444_10BIT == 1) ||
		(dv->support_LL_RGB_444_12BIT == 1))) {
		return DOLBY_VISION_LL_RGB;
	} else if (type == 0) {
		return DOLBY_VISION_DISABLE;
	}

	/* 3.dolby vision best policy:
	 * STD->LL_YUV->LL_RGB for netflix request
	 * LL_YUV->STD->LL_RGB for dolby vision request
	 */
	printf("NOTE: DV type is changed!\n");
	if ((dv->support_DV_RGB_444_8BIT == 1) ||
	    (dv->support_LL_YCbCr_422_12BIT == 1)) {
		if (dv->support_DV_RGB_444_8BIT == 1)
			return DOLBY_VISION_STD_ENABLE;
		else if (dv->support_LL_YCbCr_422_12BIT == 1)
			return DOLBY_VISION_LL_YUV;
	} else if ((dv->support_LL_RGB_444_10BIT == 1) ||
		   (dv->support_LL_RGB_444_12BIT == 1)) {
		return DOLBY_VISION_LL_RGB;
	}

	return DOLBY_VISION_DISABLE;
}

static void update_dv_attr(struct input_hdmi_data *hdmi_data, char *dv_attr)
{
	int dv_type;
	struct dv_info *dv = NULL;
	if (!hdmi_data || !dv_attr)
		return;

	dv_type = hdmi_data->ubootenv_dv_type;
	dv = &hdmi_data->prxcap->dv_info;

	switch (dv_type) {
	case DOLBY_VISION_STD_ENABLE:
		strcpy(dv_attr, "444,8bit");
		break;
	case DOLBY_VISION_LL_YUV:
		strcpy(dv_attr, "422,12bit");
		break;
	case DOLBY_VISION_LL_RGB:
		if (dv->support_LL_RGB_444_12BIT == 1)
			strcpy(dv_attr, "444,12bit");
		else if (dv->support_LL_RGB_444_10BIT == 1)
			strcpy(dv_attr, "444,10bit");

		break;
	default:
		strcpy(dv_attr, "444,8bit");
		break;
	}

	printf("dv_type :%d dv_attr:%s", dv_type, dv_attr);
}

static bool is_dv_support_mode(struct input_hdmi_data *hdmi_data, char *mode)
{
	bool valid = false;
	struct dv_info *dv = NULL;
	char dv_displaymode[MODE_LEN] = {0};

	if (!hdmi_data || !mode)
		return false;

	dv = &hdmi_data->prxcap->dv_info;
	/* maximum DV mode */
	if (dv->sup_2160p60hz == 1)
		strcpy(dv_displaymode, DV_MODE_4K2K60HZ);
	else
		strcpy(dv_displaymode, DV_MODE_4K2K30HZ);

	if (!hdmi_sink_disp_mode_sup(hdmi_data, mode))
		return false;

	if (!strcmp(mode, MODE_1080P100HZ)) {
		if (dv->sup_1080p120hz)
			valid = true;
	} else if (!strcmp(mode, MODE_1080P120HZ)) {
		if (dv->sup_1080p120hz)
			valid = true;
	} else if (resolve_resolution_value(mode, RESOLUTION_PRIORITY) >
		resolve_resolution_value(dv_displaymode, RESOLUTION_PRIORITY) ||
		strstr(mode, "480p") || strstr(mode, "576p") ||
		strstr(mode, "smpte") || strstr(mode, "4096") || strstr(mode, "i")) {
		/* sync with system, don't support DV under some mode,
		 * refer to SWPL-83949 and SWPL-159807
		 */
		valid = false;
	} else {
		valid = true;
	}

	return valid;
}

/* 1.For previous android version, the mode list in UI is filtered, if
 * current mode not support DV(e.g. 4k60hz, and EDID only support it
 * with Y420), then it's filtered and not list on UI.
 * 2.But setting menu for android U is from Google, the mode list of UI is
 * from framework->hwc->drm and won't filter out as previous android S.
 * if the TV only support 2160p30hz DV and only support 2160p60hz
 * 420 8bit, firstly user select hdmi output 1080p60hz 422 12bit dv,
 * then switch to 2160p60hz, hwc will set 2160p60hz 422 12bit to driver,
 * then it will cause no signal. So need to run hdr process when
 * current resolution not support dv.
 * 3.return 0: mode support DV, -1: mode not support DV
 */
/* note below flag true is only for android R/S/U trunk + android U openlinux + linux:
 * which means that if current mode not support DV, it will keep the selected resolution,
 * and fallback to hdr policy to get hdr cs/cd.
 * For R/S openlinux, the behaviour is as flag set false, which means that if current mode
 * not support DV, it will downgrade to lower resolution to output DV
 */
static bool amdv_policy_fallback_hdr = true;

static int update_dv_displaymode(struct input_hdmi_data *hdmi_data,
	char *final_displaymode)
{
	char dv_displaymode[MODE_LEN] = {0};
	char cur_outputmode[MODE_LEN] = {0};
	int dv_type;
	struct dv_info *dv = NULL;
	int ret = 0;

	if (!hdmi_data || !final_displaymode)
		return ret;
	dv_type = hdmi_data->ubootenv_dv_type;

	strcpy(cur_outputmode, hdmi_data->ubootenv_hdmimode);
	dv = &hdmi_data->prxcap->dv_info;
	/* maximum DV mode */
	if (dv->sup_2160p60hz == 1)
		strcpy(dv_displaymode, DV_MODE_4K2K60HZ);
	else
		strcpy(dv_displaymode, DV_MODE_4K2K30HZ);

	if (is_best_outputmode()) {
		if (dv->parity) {
			/* TV support dolby vision 2160p60hz case */
			if (!strcmp(dv_displaymode, DV_MODE_4K2K60HZ)) {
				if (dv_type == DOLBY_VISION_LL_RGB)
					strcpy(final_displaymode, DV_MODE_1080P);
				else
					strcpy(final_displaymode, DV_MODE_4K2K60HZ);
			} else {
				strcpy(final_displaymode, DV_MODE_1080P);
			}
		} else if (!strcmp(dv_displaymode, DV_MODE_4K2K60HZ)) {
			if (dv_type == DOLBY_VISION_LL_RGB)
				strcpy(final_displaymode, DV_MODE_1080P);
			 else
				strcpy(final_displaymode, DV_MODE_4K2K60HZ);
		} else {
			if (!strcmp(dv_displaymode, DV_MODE_4K2K30HZ) ||
			    !strcmp(dv_displaymode, DV_MODE_4K2K25HZ) ||
			    !strcmp(dv_displaymode, DV_MODE_4K2K24HZ))
				strcpy(final_displaymode, DV_MODE_1080P);
			else
				strcpy(final_displaymode, dv_displaymode);
		}
	} else {
		/* if current disp_mode is outside of maximum dv disp_mode */
		if (!is_dv_support_mode(hdmi_data, cur_outputmode)) {
			if (amdv_policy_fallback_hdr) {
				ret = -1;
				printf("cur_outputmode:%s doesn't support dv", cur_outputmode);
			} else if (!strcmp(dv_displaymode, MODE_4K2K30HZ) ||
				!strcmp(dv_displaymode, MODE_4K2K25HZ) ||
				!strcmp(dv_displaymode, MODE_4K2K24HZ)) {
				/* TV support dolby vision support 2160p30/25/24hz
				 * prefer 1080p
				 */
				strcpy(final_displaymode, MODE_1080P);
			} else {
				/* use maximum DV mode */
				strcpy(final_displaymode, dv_displaymode);
			}
		} else {
			strcpy(final_displaymode, cur_outputmode);
		}
	}

	printf("final_displaymode:%s, cur_outputmode:%s, dv_displaymode:%s",
	       final_displaymode, cur_outputmode, dv_displaymode);
	return ret;
}

/* for some non-std TV, it declare 4k while MAX_TMDS_CLK
 * not match 4K format, so filter out mode list by
 * check if basic color space/depth is supported
 * or not under this resolution
 * note that disp_mode should not contain colorspace, such as 420
 */
static bool hdmi_sink_disp_mode_sup(struct input_hdmi_data *hdmi_data, char *disp_mode)
{
	enum hdmi_vic vic = HDMI_UNKNOWN;

	if (!hdmi_data || !disp_mode)
		return false;

	vic = hdmitx_edid_vic_tab_map_vic(disp_mode);

	if (_is_y420_vic(vic)) {
		if (hdmitx_chk_mode_attr_sup(hdmi_data, disp_mode, "420,8bit"))
			return true;
		if (hdmitx_chk_mode_attr_sup(hdmi_data, disp_mode, "rgb,8bit"))
			return true;
		if (hdmitx_chk_mode_attr_sup(hdmi_data, disp_mode, "444,8bit"))
			return true;
		if (hdmitx_chk_mode_attr_sup(hdmi_data, disp_mode, "422,12bit"))
			return true;
	} else {
		if (hdmitx_chk_mode_attr_sup(hdmi_data, disp_mode, "rgb,8bit"))
			return true;
		if (hdmitx_chk_mode_attr_sup(hdmi_data, disp_mode, "444,8bit"))
			return true;
		if (hdmitx_chk_mode_attr_sup(hdmi_data, disp_mode, "422,12bit"))
			return true;
	}
	return false;
}

/* get the highest hdmi mode by edid */
static void get_highest_hdmimode(struct input_hdmi_data *hdmi_data, char *mode)
{
	char value[MODE_LEN] = {0};
	char mode_tmp[MODE_LEN];
	int i;

	if (!hdmi_data || !mode)
		return;
	/* i timing need to output for spec edid during HDMI CTS,
	 * use 480i60hz as base mode
	 */
	strcpy(value, "480i60hz");

	for (i = 0; disp_mode_t[i]; i++) {
		memset(mode_tmp, 0, sizeof(mode_tmp));
		strncpy(mode_tmp, disp_mode_t[i], MODE_LEN - 1);
		if (!hdmi_sink_disp_mode_sup(hdmi_data, mode_tmp))
			continue;
		if (resolve_resolution_value(mode_tmp, FRAMERATE_PRIORITY) >
		    resolve_resolution_value(value, FRAMERATE_PRIORITY)) {
			memset(value, 0, MODE_LEN);
			strcpy(value, mode_tmp);
		}
	}

	strcpy(mode, value);
	printf("set HDMI to highest edid mode: %s\n", mode);
}

/* check if the edid support current hdmi mode */
static void filter_hdmimode(struct input_hdmi_data *hdmi_data, char *mode)
{
	if (!hdmi_data || !mode)
		return;

	if (hdmi_sink_disp_mode_sup(hdmi_data, hdmi_data->ubootenv_hdmimode)) {
		strcpy(mode, hdmi_data->ubootenv_hdmimode);
	} else {
		/* old mode is not support in this TV,
		 * so switch to best mode.
		 */
		get_highest_hdmimode(hdmi_data, mode);
	}
}

static void get_hdmi_outputmode(struct input_hdmi_data *hdmi_data, char *mode)
{
	struct hdmitx_dev *hdev = NULL;

	if (!hdmi_data || !mode)
		return;

	hdev = container_of(hdmi_data->prxcap,
			struct hdmitx_dev, RXCap);

    /* Fall back to 480p if EDID can't be parsed */
    /* actually won't go into this edid parsing decision
     * as it will be decided outside
     */
	if (!edid_parsing_ok(hdev)) {
		strcpy(mode, DEFAULT_HDMI_MODE);
		printf("EDID parsing error detected\n");
		return;
	}

	if (is_best_outputmode())
		get_highest_hdmimode(hdmi_data, mode);
	else
		filter_hdmimode(hdmi_data, mode);
}

static void get_best_color_attr(struct input_hdmi_data *hdmi_data,
	const char *outputmode, char *colorattribute)
{
	int length = 0;
	const char **color_list = NULL;
	char temp_mode[MODE_LEN] = {0};
	int i;
	struct hdmitx_dev *hdev = NULL;

	if (!hdmi_data || !outputmode || !colorattribute)
		return;

	hdev = container_of(hdmi_data->prxcap,
		struct hdmitx_dev, RXCap);

	/* filter some color value options, aimed at some modes. */
	if (!strcmp(outputmode, MODE_4K2K60HZ) ||
	    !strcmp(outputmode, MODE_4K2K50HZ) ||
	    !strcmp(outputmode, MODE_4K2KSMPTE60HZ) ||
	    !strcmp(outputmode, MODE_4K2KSMPTE50HZ) ||
	    !strcmp(outputmode, MODE_4K2K100HZ) ||
	    !strcmp(outputmode, MODE_4K2K120HZ) ||
		!strcmp(outputmode, MODE_8K4K60HZ) ||
		!strcmp(outputmode, MODE_8K4K50HZ) ||
		!strcmp(outputmode, MODE_8K4K48HZ) ||
		!strcmp(outputmode, MODE_8K4K30HZ) ||
		!strcmp(outputmode, MODE_8K4K25HZ) ||
		!strcmp(outputmode, MODE_8K4K24HZ)) {
		if (is_low_powermode()) {
			color_list = COLOR_ATTRIBUTE_LIST3;
			length = ARRAY_SIZE(COLOR_ATTRIBUTE_LIST3);
		} else {
			color_list = COLOR_ATTRIBUTE_LIST1;
			length = ARRAY_SIZE(COLOR_ATTRIBUTE_LIST1);
		}
	} else {
		if (is_low_powermode()) {
			color_list = COLOR_ATTRIBUTE_LIST4;
			length = ARRAY_SIZE(COLOR_ATTRIBUTE_LIST4);
		} else if (is_hdr_preference(hdev)) {
			/* hdr non 4k50/60hz color format priority table */
			/* ex:connect 2160p60 420 8bit TV, when switch to
			 * 1080p60, 10bit first for hdr, switch 2160p60,
			 * only 420 8bit
			 */
			color_list = COLOR_ATTRIBUTE_LIST2;
			length = ARRAY_SIZE(COLOR_ATTRIBUTE_LIST2);
		} else {
			/* sdr non 4k50/60hz color format priority table */
			color_list = SDR_NON4K_COLOR_ATTRIBUTE_LIST;
			length = ARRAY_SIZE(SDR_NON4K_COLOR_ATTRIBUTE_LIST);
		}
	}

	for (i = 0; i < length; i++) {
		memset(temp_mode, 0, sizeof(temp_mode));
		strncpy(temp_mode, outputmode, MODE_LEN - 1);
		if ((strlen(temp_mode) + strlen(color_list[i])) < MODE_LEN)
			strcat(temp_mode, color_list[i]);
		if (is_supported_mode_attr(hdmi_data, temp_mode)) {
			printf("support current mode:[%s], deep color:[%s]\n",
			       outputmode, color_list[i]);
			strcpy(colorattribute, color_list[i]);
			break;
		}
	}
}

static void get_hdmi_colorattribute(struct input_hdmi_data *hdmi_data,
	const char *outputmode, char *colorattribute)
{
	char temp_mode[MODE_LEN] = {0};

	if (!hdmi_data || !outputmode || !colorattribute)
		return;
	/* if dc_cap is null, use default color format */
	/* should never encounter this case */
	if (false) {
		if (!strcmp(outputmode, MODE_4K2K60HZ) ||
		    !strcmp(outputmode, MODE_4K2K50HZ) ||
		    !strcmp(outputmode, MODE_4K2KSMPTE60HZ) ||
		    !strcmp(outputmode, MODE_4K2KSMPTE50HZ) ||
		    !strcmp(outputmode, MODE_4K2K100HZ) ||
		    !strcmp(outputmode, MODE_4K2K120HZ) ||
			!strcmp(outputmode, MODE_8K4K60HZ) ||
			!strcmp(outputmode, MODE_8K4K50HZ) ||
			!strcmp(outputmode, MODE_8K4K48HZ) ||
			!strcmp(outputmode, MODE_8K4K30HZ) ||
			!strcmp(outputmode, MODE_8K4K25HZ) ||
			!strcmp(outputmode, MODE_8K4K24HZ)) {
			strcpy(colorattribute, DEFAULT_COLOR_FORMAT_4K);
		} else {
			strcpy(colorattribute, DEFAULT_COLOR_FORMAT);
		}

		printf("Do not find sink color list, use default color attribute:%s\n",
		       colorattribute);
		return;
	}

	/* use ubootenv.var.colorattribute when best color space policy is disable */
	/* will check resolution + color format be support TV EDID */
	if (!is_best_color_space()) {
		strcpy(temp_mode, hdmi_data->ubootenv_hdmimode);
		strcat(temp_mode, hdmi_data->ubootenv_colorattribute);
		if (is_supported_mode_attr(hdmi_data, temp_mode))
			strcpy(colorattribute,
			       hdmi_data->ubootenv_colorattribute);
		else
			get_best_color_attr(hdmi_data, outputmode,
					    colorattribute);
	} else {
		get_best_color_attr(hdmi_data, outputmode, colorattribute);
	}

	/* if colorAttr is null above steps,
	 * will defines a initial value
	 */
	if (!strstr(colorattribute, "bit"))
		strcpy(colorattribute, DEFAULT_COLOR_FORMAT);
}

static void update_hdmi_deepcolor(struct input_hdmi_data *hdmi_data,
	const char *outputmode, char *colorattribute)
{
	if (!hdmi_data || !outputmode || !colorattribute)
		return;
	if (is_support_deepcolor())
		get_hdmi_colorattribute(hdmi_data, outputmode, colorattribute);
	else
		strcpy(colorattribute, "default");

	printf("colorattribute = %s\n", colorattribute);
}

int dolbyvision_scene_process(struct input_hdmi_data *hdmi_data,
	struct scene_output_info *output_info)
{
	int dv_type = DOLBY_VISION_DISABLE;
	int ret = 0;

	if (!hdmi_data || !output_info)
		return ret;
	/* 1.update dolby vision output type */
	dv_type = update_dv_type(hdmi_data);
	output_info->final_dv_type = dv_type;
	printf("dv final_type:%d\n", output_info->final_dv_type);

	/* update param */
	hdmi_data->ubootenv_dv_type = dv_type;
	/* 2. update dolby vision output output mode and colorspace */
	/* 2.1 update dolby vision deepcolor */
	update_dv_attr(hdmi_data, output_info->final_deepcolor);
	printf("dv final_deepcolor:%s\n", output_info->final_deepcolor);

	/* 2.2 update dolby vision output mode */
	ret = update_dv_displaymode(hdmi_data, output_info->final_displaymode);
	printf("dv final_displaymode:%s", output_info->final_displaymode);
	return ret;
}

/* check 4k50/4k60 hdr support or not */
static bool is_support_4k60hdr(struct input_hdmi_data *hdmi_data,
	scene_output_info_t *output_info)
{
	int colorList_length = 0;
	int resolutionList_length	= 0;
	int i = 0;
	int j = 0;
	char temp_mode[MODE_LEN] = {0};

	if (!hdmi_data || !output_info)
		return false;

	colorList_length = ARRAY_SIZE(HDR_4K_COLOR_ATTRIBUTE_LIST);
	resolutionList_length = ARRAY_SIZE(MODE_4K_LIST);

	for (i = 0; i < colorList_length; i++) {
		for (j = 0; j < resolutionList_length; j++) {
			memset(temp_mode, 0, sizeof(temp_mode));
			strncpy(temp_mode, MODE_4K_LIST[j], MODE_LEN - 1);
			if (strlen(temp_mode) + strlen(HDR_4K_COLOR_ATTRIBUTE_LIST[i]) <
				MODE_LEN)
				strcat(temp_mode, HDR_4K_COLOR_ATTRIBUTE_LIST[i]);
			if (is_supported_mode_attr(hdmi_data, temp_mode)) {
				printf("%s mode:[%s], deep color:[%s]\n",
					__func__, MODE_4K_LIST[j], HDR_4K_COLOR_ATTRIBUTE_LIST[i]);
				strcpy(output_info->final_deepcolor,
					HDR_4K_COLOR_ATTRIBUTE_LIST[i]);
				strcpy(output_info->final_displaymode,
					MODE_4K_LIST[j]);
				return true;
			}
		}
	}
	printf("%s 4k50/60hz hdr not support\n", __func__);
	return false;
}

/* check non 4k hdr support or not */
static bool is_support_non4k_hdr(struct input_hdmi_data *hdmi_data,
	scene_output_info_t *output_info)
{
	int colorList_length = 0;
	int resolutionList_length   = 0;
	int i = 0;
	int j = 0;
	char temp_mode[MODE_LEN] = {0};

	if (!hdmi_data || !output_info)
		return false;

	colorList_length = ARRAY_SIZE(HDR_NON4K_COLOR_ATTRIBUTE_LIST);
	resolutionList_length = ARRAY_SIZE(MODE_NON4K_LIST);

	for (i = 0; i < colorList_length; i++) {
		for (j = 0; j < resolutionList_length; j++) {
			memset(temp_mode, 0, sizeof(temp_mode));
			strncpy(temp_mode, MODE_NON4K_LIST[j], MODE_LEN - 1);
			if (strlen(temp_mode) + strlen(HDR_NON4K_COLOR_ATTRIBUTE_LIST[i]) <
				MODE_LEN)
				strcat(temp_mode, HDR_NON4K_COLOR_ATTRIBUTE_LIST[i]);
			if (is_supported_mode_attr(hdmi_data, temp_mode)) {
				printf("%s mode:[%s], deep color:[%s]\n",
					__func__, MODE_NON4K_LIST[j],
					HDR_NON4K_COLOR_ATTRIBUTE_LIST[i]);
				strcpy(output_info->final_deepcolor,
					HDR_NON4K_COLOR_ATTRIBUTE_LIST[i]);
				strcpy(output_info->final_displaymode,
					MODE_NON4K_LIST[j]);
				return true;
			}
		}
	}

	printf("%s non 4k hdr not support\n", __func__);
	return false;
}

static bool find_hdr_prefer_mode(struct input_hdmi_data *hdmi_data,
	scene_output_info_t *output_info)
{
	bool find = false;

	if (!hdmi_data || !output_info)
		return find;

	/* if box can support 4k case
	 * find prefer 4k50/60hz hdr resolution and color format based on edid
	 */
	if (is_support_4k())
		find = is_support_4k60hdr(hdmi_data, output_info);

	/* 1.not find 4k hdr mode case 2. box not support 4k case
	 * find prefer non 4k hdr resolution and color format based on edid
	 */
	if (!find)
		find = is_support_non4k_hdr(hdmi_data, output_info);

	return find;
}

void hdr_scene_process(struct input_hdmi_data *hdmi_data,
	scene_output_info_t *output_info)
{
	bool find = false;
	char temp_mode[MODE_LEN] = {0};
	char colorattribute[MODE_LEN] = {0};
	const char **resolutionList = NULL;
	int resolutionList_length = 0;
	const char **colorList = NULL;
	int colorList_length = 0;
	int j = 0;

	if (!hdmi_data || !output_info)
		return;

	if (is_best_outputmode() && is_best_color_space()) {
		/* case1: both best mode/color are selected */

		find = find_hdr_prefer_mode(hdmi_data, output_info);
		if (!find)
			printf("%s not find hdr support mode\n", __func__);
	} else if (is_best_outputmode()) {
		/* case2: best_color_space is disabled, use user selected color */

		if (is_framerate_priority()) {
			resolutionList = MODE_FRAMERATE_FIRST;
			resolutionList_length = ARRAY_SIZE(MODE_FRAMERATE_FIRST);
		} else {
			resolutionList = MODE_RESOLUTION_FIRST;
			resolutionList_length = ARRAY_SIZE(MODE_RESOLUTION_FIRST);
		}

		for (j = resolutionList_length - 1; j >= 0; j--) {
			memset(temp_mode, 0, sizeof(temp_mode));
			strncpy(temp_mode, resolutionList[j], MODE_LEN - 1);
			if (hdmitx_chk_mode_attr_sup(hdmi_data, temp_mode,
				hdmi_data->ubootenv_colorattribute)) {
				printf("%s mode:[%s], deep color:[%s]\n",
					__func__, resolutionList[j],
					hdmi_data->ubootenv_colorattribute);
				strcpy(output_info->final_displaymode, resolutionList[j]);
				strcpy(output_info->final_deepcolor,
					hdmi_data->ubootenv_colorattribute);
				find = true;
				break;
			}
		}
	} else if (is_best_color_space()) {
		/* case3: is_best_mode is disabled, use user selected mode */

		if (!strcmp(hdmi_data->ubootenv_hdmimode, MODE_4K2K60HZ) ||
			!strcmp(hdmi_data->ubootenv_hdmimode, MODE_4K2K50HZ) ||
			!strcmp(hdmi_data->ubootenv_hdmimode, MODE_4K2KSMPTE60HZ) ||
			!strcmp(hdmi_data->ubootenv_hdmimode, MODE_4K2KSMPTE50HZ) ||
			!strcmp(hdmi_data->ubootenv_hdmimode, MODE_4K2K100HZ) ||
			!strcmp(hdmi_data->ubootenv_hdmimode, MODE_4K2K120HZ) ||
			!strcmp(hdmi_data->ubootenv_hdmimode, MODE_8K4K60HZ) ||
			!strcmp(hdmi_data->ubootenv_hdmimode, MODE_8K4K50HZ) ||
			!strcmp(hdmi_data->ubootenv_hdmimode, MODE_8K4K48HZ) ||
			!strcmp(hdmi_data->ubootenv_hdmimode, MODE_8K4K30HZ) ||
			!strcmp(hdmi_data->ubootenv_hdmimode, MODE_8K4K25HZ) ||
			!strcmp(hdmi_data->ubootenv_hdmimode, MODE_8K4K24HZ)) {
			//2160p50hz 2160p60hz 3840x2160p60hz 3840x2160p50hz case
			//use 4k color format table
			colorList = COLOR_ATTRIBUTE_LIST1;
			colorList_length = ARRAY_SIZE(COLOR_ATTRIBUTE_LIST1);
		} else {
			//except 2160p60hz 2160p50hz 3840x2160p60hz 3840x2160p60hz case
			//use non-4k color format table
			colorList = COLOR_ATTRIBUTE_LIST2;
			colorList_length = ARRAY_SIZE(COLOR_ATTRIBUTE_LIST2);
		}

		for (j = 0; j < colorList_length; j++) {
			memset(colorattribute, 0, sizeof(colorattribute));
			strncpy(colorattribute, colorList[j], MODE_LEN - 1);
			if (hdmitx_chk_mode_attr_sup(hdmi_data,
				hdmi_data->ubootenv_hdmimode, colorattribute)) {
				printf("%s mode:[%s], deep color:[%s]\n",
					__func__, hdmi_data->ubootenv_hdmimode, colorList[j]);
				strcpy(output_info->final_displaymode,
					hdmi_data->ubootenv_hdmimode);
				strcpy(output_info->final_deepcolor, colorList[j]);
				find = true;
				break;
			}
		}
	} else {
		/* case4: neither best mode/color_space is enabled, use user selected mode/cs */
		if (hdmitx_chk_mode_attr_sup(hdmi_data, hdmi_data->ubootenv_hdmimode,
			hdmi_data->ubootenv_colorattribute)) {
			printf("support current mode:[%s], deep color:[%s]\n",
				hdmi_data->ubootenv_hdmimode, hdmi_data->ubootenv_colorattribute);
			strcpy(output_info->final_displaymode, hdmi_data->ubootenv_hdmimode);
			strcpy(output_info->final_deepcolor, hdmi_data->ubootenv_colorattribute);
			find = true;
		} else if (hdmi_sink_disp_mode_sup(hdmi_data, hdmi_data->ubootenv_hdmimode)) {
			printf("support current mode:[%s]\n", hdmi_data->ubootenv_hdmimode);
			get_best_color_attr(hdmi_data, hdmi_data->ubootenv_hdmimode,
				colorattribute);
			strcpy(output_info->final_displaymode, hdmi_data->ubootenv_hdmimode);
			strcpy(output_info->final_deepcolor, colorattribute);
			find = true;
		}
	}

	/* not find support mode and colorspace and try best policy */
	if (!find && !(is_best_outputmode() && is_best_color_space())) {
		/* for case2/3/4, if not find proper mode/cs,
		 * use best policy enable case
		 */
		find = find_hdr_prefer_mode(hdmi_data, output_info);
		if (!find)
			printf("%s not find hdr support mode2\n", __func__);
	}
}

/* SDR scene policy process */
void sdr_scene_process(struct input_hdmi_data *hdmi_data, struct scene_output_info *output_info)
{
	char outputmode[MODE_LEN] = {0};
	char colorattribute[MODE_LEN] = {0};

	if (!hdmi_data || !output_info)
		return;
	/* 1.choose resolution, frame rate */
	get_hdmi_outputmode(hdmi_data, outputmode);
	if (strlen(outputmode) == 0)
		strcpy(outputmode, DEFAULT_HDMI_MODE);
	strcpy(output_info->final_displaymode, outputmode);

	/* 2.choose color format, bit-depth */
	update_hdmi_deepcolor(hdmi_data, outputmode, colorattribute);
	strcpy(output_info->final_deepcolor, colorattribute);
	printf("sdr final_displaymode:%s, final_deepcolor:%s\n",
		output_info->final_displaymode, output_info->final_deepcolor);
}

void get_hdmi_data(struct hdmitx_dev *hdev, struct input_hdmi_data *data)
{
	char *hdmimode;
	char *colorattribute;

	if (!hdev || !data)
		return;
	/* 1."hdmimode" is used to save user manually selected mode,
	 * note that if auto best mode is on, it means no user manual
	 * operation. then this env will be default "none" or NULL
	 * 2."user_colorattribute" is used to save user manually
	 * selected color space/depth.
	 * while
	 * 3."outputmode" is used to save the actual output hdmi mode
	 * 4."colorattribute" is used to save the actual output color space/depth
	 */
	hdmimode = env_get("hdmimode");
	colorattribute = env_get("user_colorattribute");

	/* the default value here is just an init value in
	 * case the env is null. if it's null/none, it will
	 * select the auto best mode/color by policy
	 */
	if (!hdmimode || !strcmp(hdmimode, "none"))
		hdmimode = DEFAULT_HDMI_MODE;
	if (!colorattribute || !strcmp(colorattribute, "none"))
		colorattribute = DEFAULT_COLOR_FORMAT;
	strcpy(data->ubootenv_hdmimode, hdmimode);
	strcpy(data->ubootenv_colorattribute, colorattribute);
	/* if user not select dv_type in menu, while dolby_status is 1/2
	 * which means that currently DV is enabled, then uboot will
	 * select a dv_type by policy;
	 * else, dv_type will be the same as dolby_status
	 */
	data->ubootenv_dv_type = get_ubootenv_dv_type();
	data->hdr_priority = get_hdr_priority();
	data->hdr_policy = get_hdr_policy();
	data->hdr_force_mode = get_hdr_force_mode();
	#if 0
	data->isbestpolicy = is_best_outputmode();
	data->isSupport4K30Hz = is_support_4k30hz();
	data->isSupport4K = is_support_4k();
	data->isDeepColor = is_support_deepcolor();
	data->isLowPowerMode = is_low_powermode();
	data->isframeratepriority = is_framerate_priority();
	#endif
	data->prxcap = &hdev->RXCap;
	/* memcpy(&(data->prxcap), &(hdev->RXCap), sizeof(hdev->RXCap)); */
	printf("ubootenv user_dv_type: %d, dv_sts:%d, hdr_priority: %d, hdr_policy: %d\n",
	       get_ubootenv_dv_type(),
	       get_ubootenv_dv_status(),
	       data->hdr_priority,
	       data->hdr_policy);
	printf("ubootenv best_mode: %d, best_color: %d, framerate_priority:%d, hdr_force_mode:%d\n",
	       is_best_outputmode(),
	       is_best_color_space(),
	       is_framerate_priority(),
	       data->hdr_force_mode);
}
