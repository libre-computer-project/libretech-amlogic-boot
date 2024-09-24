// SPDX-License-Identifier: (GPL-2.0+ OR MIT)
/*
 * Copyright (c) 2019 Amlogic, Inc. All rights reserved.
 */

/* System Headers */
#include <config.h>
#include <asm/arch/io.h>
#include <amlogic/cpu_id.h>
#include <asm/arch/cpu.h>
#include <asm/arch/timer.h>
#include <div64.h>

/* Local Headers */
#include <amlogic/media/vout/aml_vmode.h>
#ifdef CONFIG_AML_CANVAS
#include <amlogic/canvas.h>
#endif
#ifdef CONFIG_AML_VOUT
#include <amlogic/media/vout/aml_vout.h>
#endif
#include <amlogic/fb.h>
#include <video_fb.h>

/* Local Headers */
#include "osd_canvas.h"
#include "osd_log.h"
#include "osd_hw.h"
#include "osd_io.h"
#include "osd_hw_def.h"
#include "osd_fb.h"
#include "vpp.h"
#include <amlogic/media/dv/dolby_vision.h>

static bool vsync_hit;
static bool osd_vf_need_update;

int osd_log_level;
static int osd_log_level_backup;
static int in_debug_mode;
static unsigned int logo_loaded[OSD_MAX];

#ifdef CONFIG_AM_VIDEO
static struct vframe_s vf;
static struct vframe_provider_s osd_vf_prov;
static unsigned char osd_vf_prov_init;
#endif
static int g_vf_visual_width;
static int g_vf_width;
static int g_vf_height;

static int g_rotation_width;
static int g_rotation_height;

static int use_h_filter_mode = -1;
static int use_v_filter_mode = -1;

static unsigned int osd_h_filter_mode = 1;
static unsigned int osd_v_filter_mode = 1;
extern GraphicDevice fb_gdev;

static void independ_path_default_regs(void);
static void fix_vpu_clk2_default_regs(void);

static int pi_enable;
#define BLEND_DOUT_DEF_HSIZE 3840
#define BLEND_DOUT_DEF_VSIZE 2160

struct fb_layout_s fb_layout[VPU_VPP_MAX];

#ifdef AML_C3_DISPLAY
#define VOUT_OSD1_UNSUPPORT             VOUT_OSD1_TCOLOR_AG0
static void osd_setting_vout_blend(void);

struct hw_osd_reg_s hw_osd_reg_array[HW_OSD_COUNT] = {
	{
		VOUT_OSD1_CTRL_STAT,
		VOUT_OSD1_CTRL_STAT2,
		VOUT_OSD1_COLOR_ADDR,
		VOUT_OSD1_COLOR,
		VOUT_OSD1_TCOLOR_AG0,
		VOUT_OSD1_TCOLOR_AG1,
		VOUT_OSD1_TCOLOR_AG2,
		VOUT_OSD1_TCOLOR_AG3,
		VOUT_OSD1_BLK0_CFG_W0,
		VOUT_OSD1_BLK0_CFG_W1,
		VOUT_OSD1_BLK0_CFG_W2,
		VOUT_OSD1_BLK0_CFG_W3,
		VOUT_OSD1_BLK0_CFG_W4,
		VOUT_OSD1_BLK1_CFG_W4,
		VOUT_OSD1_BLK2_CFG_W4,
		VOUT_OSD1_FIFO_CTRL_STAT,

		VOUT_OSD1_SCALE_COEF_IDX,
		VOUT_OSD1_SCALE_COEF,
		VOUT_OSD1_VSC_PHASE_STEP,
		VOUT_OSD1_VSC_INI_PHASE,
		VOUT_OSD1_VSC_CTRL0,
		VOUT_OSD1_HSC_PHASE_STEP,
		VOUT_OSD1_HSC_INI_PHASE,
		VOUT_OSD1_HSC_CTRL0,
		VOUT_OSD1_SC_DUMMY_DATA,
		VOUT_OSD1_SC_CTRL0,
		VOUT_OSD1_SCI_WH_M1,
		VOUT_OSD1_SCO_H_START_END,
		VOUT_OSD1_SCO_V_START_END,

		VOUT_OSD1_UNSUPPORT,
		VOUT_OSD1_UNSUPPORT,
	},
};
#endif

#ifdef AML_OSD_HIGH_VERSION
#define VIU2_OSD1_UNSUPPORT               VIU_OSD2_TCOLOR_AG3

#ifdef reg_define
struct hw_encp_reg_s hw_vout_reg = {
	ENCP_VIDEO_MODE,
	ENCP_INFO_READ,
	ENCP_VIDEO_VAVON_BLINE,
	ENCL_INFO_READ,
	ENCL_VIDEO_VAVON_BLINE,
	ENCI_INFO_READ,
	ENCI_VFIFO2VD_LINE_TOP_START,
	ENCT_INFO_READ,
	ENCT_VIDEO_VAVON_BLINE,
};
#endif

#if defined(AML_S5_DISPLAY)
struct hw_osd_reg_s hw_osd_reg_array[HW_OSD_COUNT] = {
	{
		VIU_OSD1_CTRL_STAT,
		VIU_OSD1_CTRL_STAT2,
		VIU_OSD1_COLOR_ADDR,
		VIU_OSD1_COLOR,
		VIU_OSD1_TCOLOR_AG0,
		VIU_OSD1_TCOLOR_AG1,
		VIU_OSD1_TCOLOR_AG2,
		VIU_OSD1_TCOLOR_AG3,
		VIU_OSD1_BLK0_CFG_W0,
		VIU_OSD1_BLK0_CFG_W1,
		VIU_OSD1_BLK0_CFG_W2,
		VIU_OSD1_BLK0_CFG_W3,
		VIU_OSD1_BLK0_CFG_W4,
		VIU_OSD1_BLK1_CFG_W4,
		VIU_OSD1_BLK2_CFG_W4,
		VIU_OSD1_FIFO_CTRL_STAT,

		OSD1_PROC_SCALE_COEF_IDX,
		OSD1_PROC_SCALE_COEF,
		OSD1_PROC_VSC_PHASE_STEP,
		OSD1_PROC_VSC_INI_PHASE,
		OSD1_PROC_VSC_CTRL0,
		OSD1_PROC_HSC_PHASE_STEP,
		OSD1_PROC_HSC_INI_PHASE,
		OSD1_PROC_HSC_CTRL0,
		OSD1_PROC_SC_DUMMY_DATA,
		OSD1_PROC_SC_CTRL0,
		OSD1_PROC_SCI_WH_M1,
		OSD1_PROC_SCO_H_START_END,
		OSD1_PROC_SCO_V_START_END,

		OSD1_PROC_IN_SIZE,
		OSD1_PROC_OUT_SIZE,
	},
	{
		VIU_OSD2_CTRL_STAT,
		VIU_OSD2_CTRL_STAT2,
		VIU_OSD2_COLOR_ADDR,
		VIU_OSD2_COLOR,
		VIU_OSD2_TCOLOR_AG0,
		VIU_OSD2_TCOLOR_AG1,
		VIU_OSD2_TCOLOR_AG2,
		VIU_OSD2_TCOLOR_AG3,
		VIU_OSD2_BLK0_CFG_W0,
		VIU_OSD2_BLK0_CFG_W1,
		VIU_OSD2_BLK0_CFG_W2,
		VIU_OSD2_BLK0_CFG_W3,
		VIU_OSD2_BLK0_CFG_W4,
		VIU_OSD2_BLK1_CFG_W4,
		VIU_OSD2_BLK2_CFG_W4,
		VIU_OSD2_FIFO_CTRL_STAT,

		OSD2_PROC_SCALE_COEF_IDX,
		OSD2_PROC_SCALE_COEF,
		OSD2_PROC_VSC_PHASE_STEP,
		OSD2_PROC_VSC_INI_PHASE,
		OSD2_PROC_VSC_CTRL0,
		OSD2_PROC_HSC_PHASE_STEP,
		OSD2_PROC_HSC_INI_PHASE,
		OSD2_PROC_HSC_CTRL0,
		OSD2_PROC_SC_DUMMY_DATA,
		OSD2_PROC_SC_CTRL0,
		OSD2_PROC_SCI_WH_M1,
		OSD2_PROC_SCO_H_START_END,
		OSD2_PROC_SCO_V_START_END,

		OSD2_PROC_IN_SIZE,
		OSD2_PROC_OUT_SIZE,
	},
	{
		VIU_OSD3_CTRL_STAT,
		VIU_OSD3_CTRL_STAT2,
		VIU_OSD3_COLOR_ADDR,
		VIU_OSD3_COLOR,
		VIU_OSD3_TCOLOR_AG0,
		VIU_OSD3_TCOLOR_AG1,
		VIU_OSD3_TCOLOR_AG2,
		VIU_OSD3_TCOLOR_AG3,
		VIU_OSD3_BLK0_CFG_W0,
		VIU_OSD3_BLK0_CFG_W1,
		VIU_OSD3_BLK0_CFG_W2,
		VIU_OSD3_BLK0_CFG_W3,
		VIU_OSD3_BLK0_CFG_W4,
		VIU_OSD3_BLK1_CFG_W4,
		VIU_OSD3_BLK2_CFG_W4,
		VIU_OSD3_FIFO_CTRL_STAT,

		OSD3_PROC_SCALE_COEF_IDX,
		OSD3_PROC_SCALE_COEF,
		OSD3_PROC_VSC_PHASE_STEP,
		OSD3_PROC_VSC_INI_PHASE,
		OSD3_PROC_VSC_CTRL0,
		OSD3_PROC_HSC_PHASE_STEP,
		OSD3_PROC_HSC_INI_PHASE,
		OSD3_PROC_HSC_CTRL0,
		OSD3_PROC_SC_DUMMY_DATA,
		OSD3_PROC_SC_CTRL0,
		OSD3_PROC_SCI_WH_M1,
		OSD3_PROC_SCO_H_START_END,
		OSD3_PROC_SCO_V_START_END,

		OSD3_PROC_IN_SIZE,
		OSD3_PROC_OUT_SIZE,
	},
};
#elif defined(AML_T7_DISPLAY)
struct hw_osd_reg_s hw_osd_reg_array[HW_OSD_COUNT] = {
	{
		VIU_OSD1_CTRL_STAT,
		VIU_OSD1_CTRL_STAT2,
		VIU_OSD1_COLOR_ADDR,
		VIU_OSD1_COLOR,
		VIU_OSD1_TCOLOR_AG0,
		VIU_OSD1_TCOLOR_AG1,
		VIU_OSD1_TCOLOR_AG2,
		VIU_OSD1_TCOLOR_AG3,
		VIU_OSD1_BLK0_CFG_W0,
		VIU_OSD1_BLK0_CFG_W1,
		VIU_OSD1_BLK0_CFG_W2,
		VIU_OSD1_BLK0_CFG_W3,
		VIU_OSD1_BLK0_CFG_W4,
		VIU_OSD1_BLK1_CFG_W4,
		VIU_OSD1_BLK2_CFG_W4,
		VIU_OSD1_FIFO_CTRL_STAT,

		VPP_OSD_SCALE_COEF_IDX,
		VPP_OSD_SCALE_COEF,
		VPP_OSD_VSC_PHASE_STEP,
		VPP_OSD_VSC_INI_PHASE,
		VPP_OSD_VSC_CTRL0,
		VPP_OSD_HSC_PHASE_STEP,
		VPP_OSD_HSC_INI_PHASE,
		VPP_OSD_HSC_CTRL0,
		VPP_OSD_SC_DUMMY_DATA,
		VPP_OSD_SC_CTRL0,
		VPP_OSD_SCI_WH_M1,
		VPP_OSD_SCO_H_START_END,
		VPP_OSD_SCO_V_START_END,

		VIU2_OSD1_UNSUPPORT,
		VIU2_OSD1_UNSUPPORT,
	},
	{
		VIU_OSD2_CTRL_STAT,
		VIU_OSD2_CTRL_STAT2,
		VIU_OSD2_COLOR_ADDR,
		VIU_OSD2_COLOR,
		VIU_OSD2_TCOLOR_AG0,
		VIU_OSD2_TCOLOR_AG1,
		VIU_OSD2_TCOLOR_AG2,
		VIU_OSD2_TCOLOR_AG3,
		VIU_OSD2_BLK0_CFG_W0,
		VIU_OSD2_BLK0_CFG_W1,
		VIU_OSD2_BLK0_CFG_W2,
		VIU_OSD2_BLK0_CFG_W3,
		VIU_OSD2_BLK0_CFG_W4,
		VIU_OSD2_BLK1_CFG_W4,
		VIU_OSD2_BLK2_CFG_W4,
		VIU_OSD2_FIFO_CTRL_STAT,

		OSD2_SCALE_COEF_IDX,
		OSD2_SCALE_COEF,
		OSD2_VSC_PHASE_STEP,
		OSD2_VSC_INI_PHASE,
		OSD2_VSC_CTRL0,
		OSD2_HSC_PHASE_STEP,
		OSD2_HSC_INI_PHASE,
		OSD2_HSC_CTRL0,
		OSD2_SC_DUMMY_DATA,
		OSD2_SC_CTRL0,
		OSD2_SCI_WH_M1,
		OSD2_SCO_H_START_END,
		OSD2_SCO_V_START_END,

		VIU2_OSD1_UNSUPPORT,
		VIU2_OSD1_UNSUPPORT,
	},
	{
		VIU_OSD3_CTRL_STAT,
		VIU_OSD3_CTRL_STAT2,
		VIU_OSD3_COLOR_ADDR,
		VIU_OSD3_COLOR,
		VIU_OSD3_TCOLOR_AG0,
		VIU_OSD3_TCOLOR_AG1,
		VIU_OSD3_TCOLOR_AG2,
		VIU_OSD3_TCOLOR_AG3,
		VIU_OSD3_BLK0_CFG_W0,
		VIU_OSD3_BLK0_CFG_W1,
		VIU_OSD3_BLK0_CFG_W2,
		VIU_OSD3_BLK0_CFG_W3,
		VIU_OSD3_BLK0_CFG_W4,
		VIU_OSD3_BLK1_CFG_W4,
		VIU_OSD3_BLK2_CFG_W4,
		VIU_OSD3_FIFO_CTRL_STAT,

		OSD34_SCALE_COEF_IDX,
		OSD34_SCALE_COEF,
		OSD34_VSC_PHASE_STEP,
		OSD34_VSC_INI_PHASE,
		OSD34_VSC_CTRL0,
		OSD34_HSC_PHASE_STEP,
		OSD34_HSC_INI_PHASE,
		OSD34_HSC_CTRL0,
		OSD34_SC_DUMMY_DATA,
		OSD34_SC_CTRL0,
		OSD34_SCI_WH_M1,
		OSD34_SCO_H_START_END,
		OSD34_SCO_V_START_END,

		VIU2_OSD1_UNSUPPORT,
		VIU2_OSD1_UNSUPPORT,
	},
	{
		VIU_OSD4_CTRL_STAT,
		VIU_OSD4_CTRL_STAT2,
		VIU_OSD4_COLOR_ADDR,
		VIU_OSD4_COLOR,
		VIU_OSD4_TCOLOR_AG0,
		VIU_OSD4_TCOLOR_AG1,
		VIU_OSD4_TCOLOR_AG2,
		VIU_OSD4_TCOLOR_AG3,
		VIU_OSD4_BLK0_CFG_W0,
		VIU_OSD4_BLK0_CFG_W1,
		VIU_OSD4_BLK0_CFG_W2,
		VIU_OSD4_BLK0_CFG_W3,
		VIU_OSD4_BLK0_CFG_W4,
		VIU_OSD4_BLK1_CFG_W4,
		VIU_OSD4_BLK2_CFG_W4,
		VIU_OSD4_FIFO_CTRL_STAT,

		OSD4_SCALE_COEF_IDX,
		OSD4_SCALE_COEF,
		OSD4_VSC_PHASE_STEP,
		OSD4_VSC_INI_PHASE,
		OSD4_VSC_CTRL0,
		OSD4_HSC_PHASE_STEP,
		OSD4_HSC_INI_PHASE,
		OSD4_HSC_CTRL0,
		OSD4_SC_DUMMY_DATA,
		OSD4_SC_CTRL0,
		OSD4_SCI_WH_M1,
		OSD4_SCO_H_START_END,
		OSD4_SCO_V_START_END,

		VIU2_OSD1_UNSUPPORT,
		VIU2_OSD1_UNSUPPORT,
	},
};
#else
struct hw_osd_reg_s hw_osd_reg_array[HW_OSD_COUNT] = {
	{
		VIU_OSD1_CTRL_STAT,
		VIU_OSD1_CTRL_STAT2,
		VIU_OSD1_COLOR_ADDR,
		VIU_OSD1_COLOR,
		VIU_OSD1_TCOLOR_AG0,
		VIU_OSD1_TCOLOR_AG1,
		VIU_OSD1_TCOLOR_AG2,
		VIU_OSD1_TCOLOR_AG3,
		VIU_OSD1_BLK0_CFG_W0,
		VIU_OSD1_BLK0_CFG_W1,
		VIU_OSD1_BLK0_CFG_W2,
		VIU_OSD1_BLK0_CFG_W3,
		VIU_OSD1_BLK0_CFG_W4,
		VIU_OSD1_BLK1_CFG_W4,
		VIU_OSD1_BLK2_CFG_W4,
		VIU_OSD1_FIFO_CTRL_STAT,

		VPP_OSD_SCALE_COEF_IDX,
		VPP_OSD_SCALE_COEF,
		VPP_OSD_VSC_PHASE_STEP,
		VPP_OSD_VSC_INI_PHASE,
		VPP_OSD_VSC_CTRL0,
		VPP_OSD_HSC_PHASE_STEP,
		VPP_OSD_HSC_INI_PHASE,
		VPP_OSD_HSC_CTRL0,
		VPP_OSD_SC_DUMMY_DATA,
		VPP_OSD_SC_CTRL0,
		VPP_OSD_SCI_WH_M1,
		VPP_OSD_SCO_H_START_END,
		VPP_OSD_SCO_V_START_END,

		VIU2_OSD1_UNSUPPORT,
		VIU2_OSD1_UNSUPPORT,
	},
	{
		VIU_OSD2_CTRL_STAT,
		VIU_OSD2_CTRL_STAT2,
		VIU_OSD2_COLOR_ADDR,
		VIU_OSD2_COLOR,
		VIU_OSD2_TCOLOR_AG0,
		VIU_OSD2_TCOLOR_AG1,
		VIU_OSD2_TCOLOR_AG2,
		VIU_OSD2_TCOLOR_AG3,
		VIU_OSD2_BLK0_CFG_W0,
		VIU_OSD2_BLK0_CFG_W1,
		VIU_OSD2_BLK0_CFG_W2,
		VIU_OSD2_BLK0_CFG_W3,
		VIU_OSD2_BLK0_CFG_W4,
		VIU_OSD2_BLK1_CFG_W4,
		VIU_OSD2_BLK2_CFG_W4,
		VIU_OSD2_FIFO_CTRL_STAT,

#ifndef AML_OSD_TXHD2_DISPLAY

		VPP_OSD_SCALE_COEF_IDX,
		VPP_OSD_SCALE_COEF,
		VPP_OSD_VSC_PHASE_STEP,
		VPP_OSD_VSC_INI_PHASE,
		VPP_OSD_VSC_CTRL0,
		VPP_OSD_HSC_PHASE_STEP,
		VPP_OSD_HSC_INI_PHASE,
		VPP_OSD_HSC_CTRL0,
		VPP_OSD_SC_DUMMY_DATA,
		VPP_OSD_SC_CTRL0,
		VPP_OSD_SCI_WH_M1,
		VPP_OSD_SCO_H_START_END,
		VPP_OSD_SCO_V_START_END,
#else

		OSD2_SCALE_COEF_IDX,
		OSD2_SCALE_COEF,
		OSD2_VSC_PHASE_STEP,
		OSD2_VSC_INI_PHASE,
		OSD2_VSC_CTRL0,
		OSD2_HSC_PHASE_STEP,
		OSD2_HSC_INI_PHASE,
		OSD2_HSC_CTRL0,
		OSD2_SC_DUMMY_DATA,
		OSD2_SC_CTRL0,
		OSD2_SCI_WH_M1,
		OSD2_SCO_H_START_END,
		OSD2_SCO_V_START_END,
#endif

		VIU2_OSD1_UNSUPPORT,
		VIU2_OSD1_UNSUPPORT,
	},
	{
		VIU2_OSD1_CTRL_STAT,
		VIU2_OSD1_CTRL_STAT2,
		VIU2_OSD1_COLOR_ADDR,
		VIU2_OSD1_COLOR,
		VIU2_OSD1_TCOLOR_AG0,
		VIU2_OSD1_TCOLOR_AG1,
		VIU2_OSD1_TCOLOR_AG2,
		VIU2_OSD1_TCOLOR_AG3,
		VIU2_OSD1_BLK0_CFG_W0,
		VIU2_OSD1_BLK0_CFG_W1,
		VIU2_OSD1_BLK0_CFG_W2,
		VIU2_OSD1_BLK0_CFG_W3,
		VIU2_OSD1_BLK0_CFG_W4,
		VIU2_OSD1_BLK1_CFG_W4,
		VIU2_OSD1_BLK2_CFG_W4,
		VIU2_OSD1_FIFO_CTRL_STAT,

		VIU2_OSD1_UNSUPPORT,
		VIU2_OSD1_UNSUPPORT,
		VIU2_OSD1_UNSUPPORT,
		VIU2_OSD1_UNSUPPORT,
		VIU2_OSD1_UNSUPPORT,
		VIU2_OSD1_UNSUPPORT,
		VIU2_OSD1_UNSUPPORT,
		VIU2_OSD1_UNSUPPORT,
		VIU2_OSD1_UNSUPPORT,
		VIU2_OSD1_UNSUPPORT,
		VIU2_OSD1_UNSUPPORT,
		VIU2_OSD1_UNSUPPORT,
		VIU2_OSD1_UNSUPPORT,

		VIU2_OSD1_UNSUPPORT,
		VIU2_OSD1_UNSUPPORT,
	},
	{
		VIU2_OSD1_CTRL_STAT,
		VIU2_OSD1_CTRL_STAT2,
		VIU2_OSD1_COLOR_ADDR,
		VIU2_OSD1_COLOR,
		VIU2_OSD1_TCOLOR_AG0,
		VIU2_OSD1_TCOLOR_AG1,
		VIU2_OSD1_TCOLOR_AG2,
		VIU2_OSD1_TCOLOR_AG3,
		VIU2_OSD1_BLK0_CFG_W0,
		VIU2_OSD1_BLK0_CFG_W1,
		VIU2_OSD1_BLK0_CFG_W2,
		VIU2_OSD1_BLK0_CFG_W3,
		VIU2_OSD1_BLK0_CFG_W4,
		VIU2_OSD1_BLK1_CFG_W4,
		VIU2_OSD1_BLK2_CFG_W4,
		VIU2_OSD1_FIFO_CTRL_STAT,

		VIU2_OSD1_UNSUPPORT,
		VIU2_OSD1_UNSUPPORT,
		VIU2_OSD1_UNSUPPORT,
		VIU2_OSD1_UNSUPPORT,
		VIU2_OSD1_UNSUPPORT,
		VIU2_OSD1_UNSUPPORT,
		VIU2_OSD1_UNSUPPORT,
		VIU2_OSD1_UNSUPPORT,
		VIU2_OSD1_UNSUPPORT,
		VIU2_OSD1_UNSUPPORT,
		VIU2_OSD1_UNSUPPORT,
		VIU2_OSD1_UNSUPPORT,
		VIU2_OSD1_UNSUPPORT,

		VIU2_OSD1_UNSUPPORT,
		VIU2_OSD1_UNSUPPORT,
	},
};
#endif
#endif

#ifdef AML_C3_DISPLAY
struct hw_osd_vout_blend_reg_s hw_osd_vout_blend_reg = {
	VPU_VOUT_IRQ_CTRL,
	VPU_VOUT_BLEND_CTRL,
	VPU_VOUT_BLEND_DUMDATA,
	VPU_VOUT_BLEND_SIZE,
	VPU_VOUT_BLD_SRC0_HPOS,
	VPU_VOUT_BLD_SRC0_VPOS,
	VPU_VOUT_BLD_SRC1_HPOS,
	VPU_VOUT_BLD_SRC1_VPOS
};

struct hw_osd_vout_csc_reg_s hw_osd_vout_csc_reg = {
	VOUT_OSD1_CSC_COEF00_01,
	VOUT_OSD1_CSC_COEF02_10,
	VOUT_OSD1_CSC_COEF11_12,
	VOUT_OSD1_CSC_COEF20_21,
	VOUT_OSD1_CSC_COEF22,
	VOUT_OSD1_CSC_COEF30_31,
	VOUT_OSD1_CSC_COEF32_40,
	VOUT_OSD1_CSC_COEF41_42,
	VOUT_OSD1_CSC_CLIP,
	VOUT_OSD1_CSC_OFFSET0_1,
	VOUT_OSD1_CSC_OFFSET2,
	VOUT_OSD1_CSC_PRE_OFFSET0_1,
	VOUT_OSD1_CSC_PRE_OFFSET2,
	VOUT_OSD1_CSC_EN_CTRL
};
#endif
static unsigned int osd_filter_coefs_bicubic_sharp[] = {
	0x01fa008c, 0x01fa0100, 0xff7f0200, 0xfe7f0300,
	0xfd7e0500, 0xfc7e0600, 0xfb7d0800, 0xfb7c0900,
	0xfa7b0b00, 0xfa7a0dff, 0xf9790fff, 0xf97711ff,
	0xf87613ff, 0xf87416fe, 0xf87218fe, 0xf8701afe,
	0xf76f1dfd, 0xf76d1ffd, 0xf76b21fd, 0xf76824fd,
	0xf76627fc, 0xf76429fc, 0xf7612cfc, 0xf75f2ffb,
	0xf75d31fb, 0xf75a34fb, 0xf75837fa, 0xf7553afa,
	0xf8523cfa, 0xf8503ff9, 0xf84d42f9, 0xf84a45f9,
	0xf84848f8
};

static unsigned int osd_filter_coefs_bicubic[] = { /* bicubic	coef0 */
	0x00800000, 0x007f0100, 0xff7f0200, 0xfe7f0300, 0xfd7e0500, 0xfc7e0600,
	0xfb7d0800, 0xfb7c0900, 0xfa7b0b00, 0xfa7a0dff, 0xf9790fff, 0xf97711ff,
	0xf87613ff, 0xf87416fe, 0xf87218fe, 0xf8701afe, 0xf76f1dfd, 0xf76d1ffd,
	0xf76b21fd, 0xf76824fd, 0xf76627fc, 0xf76429fc, 0xf7612cfc, 0xf75f2ffb,
	0xf75d31fb, 0xf75a34fb, 0xf75837fa, 0xf7553afa, 0xf8523cfa, 0xf8503ff9,
	0xf84d42f9, 0xf84a45f9, 0xf84848f8
};

static unsigned int osd_filter_coefs_bilinear[] = { /* 2 point bilinear	coef1 */
	0x00800000, 0x007e0200, 0x007c0400, 0x007a0600, 0x00780800, 0x00760a00,
	0x00740c00, 0x00720e00, 0x00701000, 0x006e1200, 0x006c1400, 0x006a1600,
	0x00681800, 0x00661a00, 0x00641c00, 0x00621e00, 0x00602000, 0x005e2200,
	0x005c2400, 0x005a2600, 0x00582800, 0x00562a00, 0x00542c00, 0x00522e00,
	0x00503000, 0x004e3200, 0x004c3400, 0x004a3600, 0x00483800, 0x00463a00,
	0x00443c00, 0x00423e00, 0x00404000
};

static unsigned int osd_filter_coefs_2point_bilinear[] = {
	/* 2 point bilinear, bank_length == 2	coef2 */
	0x80000000, 0x7e020000, 0x7c040000, 0x7a060000, 0x78080000, 0x760a0000,
	0x740c0000, 0x720e0000, 0x70100000, 0x6e120000, 0x6c140000, 0x6a160000,
	0x68180000, 0x661a0000, 0x641c0000, 0x621e0000, 0x60200000, 0x5e220000,
	0x5c240000, 0x5a260000, 0x58280000, 0x562a0000, 0x542c0000, 0x522e0000,
	0x50300000, 0x4e320000, 0x4c340000, 0x4a360000, 0x48380000, 0x463a0000,
	0x443c0000, 0x423e0000, 0x40400000
};

/* filt_triangle, point_num =3, filt_len =2.6, group_num = 64 */
static unsigned int osd_filter_coefs_3point_triangle_sharp[] = {
	0x40400000, 0x3e420000, 0x3d430000, 0x3b450000,
	0x3a460000, 0x38480000, 0x37490000, 0x354b0000,
	0x344c0000, 0x324e0000, 0x314f0000, 0x2f510000,
	0x2e520000, 0x2c540000, 0x2b550000, 0x29570000,
	0x28580000, 0x265a0000, 0x245c0000, 0x235d0000,
	0x215f0000, 0x20600000, 0x1e620000, 0x1d620100,
	0x1b620300, 0x19630400, 0x17630600, 0x15640700,
	0x14640800, 0x12640a00, 0x11640b00, 0x0f650c00,
	0x0d660d00
};

static unsigned int osd_filter_coefs_3point_triangle[] = {
	0x40400000, 0x3f400100, 0x3d410200, 0x3c410300,
	0x3a420400, 0x39420500, 0x37430600, 0x36430700,
	0x35430800, 0x33450800, 0x32450900, 0x31450a00,
	0x30450b00, 0x2e460c00, 0x2d460d00, 0x2c470d00,
	0x2b470e00, 0x29480f00, 0x28481000, 0x27481100,
	0x26491100, 0x25491200, 0x24491300, 0x234a1300,
	0x224a1400, 0x214a1500, 0x204a1600, 0x1f4b1600,
	0x1e4b1700, 0x1d4b1800, 0x1c4c1800, 0x1b4c1900,
	0x1a4c1a00
};

static unsigned int osd_filter_coefs_4point_triangle[] = {
	0x20402000, 0x20402000, 0x1f3f2101, 0x1f3f2101,
	0x1e3e2202, 0x1e3e2202, 0x1d3d2303, 0x1d3d2303,
	0x1c3c2404, 0x1c3c2404, 0x1b3b2505, 0x1b3b2505,
	0x1a3a2606, 0x1a3a2606, 0x19392707, 0x19392707,
	0x18382808, 0x18382808, 0x17372909, 0x17372909,
	0x16362a0a, 0x16362a0a, 0x15352b0b, 0x15352b0b,
	0x14342c0c, 0x14342c0c, 0x13332d0d, 0x13332d0d,
	0x12322e0e, 0x12322e0e, 0x11312f0f, 0x11312f0f,
	0x10303010
};

/* 4th order (cubic) b-spline */
/* filt_cubic point_num =4, filt_len =4, group_num = 64 */
static unsigned int vpp_filter_coefs_4point_bspline[] = {
	0x15561500, 0x14561600, 0x13561700, 0x12561800,
	0x11551a00, 0x11541b00, 0x10541c00, 0x0f541d00,
	0x0f531e00, 0x0e531f00, 0x0d522100, 0x0c522200,
	0x0b522300, 0x0b512400, 0x0a502600, 0x0a4f2700,
	0x094e2900, 0x084e2a00, 0x084d2b00, 0x074c2c01,
	0x074b2d01, 0x064a2f01, 0x06493001, 0x05483201,
	0x05473301, 0x05463401, 0x04453601, 0x04433702,
	0x04423802, 0x03413a02, 0x03403b02, 0x033f3c02,
	0x033d3d03
};

/* filt_quadratic, point_num =3, filt_len =3, group_num = 64 */
static unsigned int osd_filter_coefs_3point_bspline[] = {
	0x40400000, 0x3e420000, 0x3c440000, 0x3a460000,
	0x38480000, 0x364a0000, 0x344b0100, 0x334c0100,
	0x314e0100, 0x304f0100, 0x2e500200, 0x2c520200,
	0x2a540200, 0x29540300, 0x27560300, 0x26570300,
	0x24580400, 0x23590400, 0x215a0500, 0x205b0500,
	0x1e5c0600, 0x1d5c0700, 0x1c5d0700, 0x1a5e0800,
	0x195e0900, 0x185e0a00, 0x175f0a00, 0x15600b00,
	0x14600c00, 0x13600d00, 0x12600e00, 0x11600f00,
	0x10601000
};

static unsigned int *filter_table[] = {
	osd_filter_coefs_bicubic_sharp,
	osd_filter_coefs_bicubic,
	osd_filter_coefs_bilinear,
	osd_filter_coefs_2point_bilinear,
	osd_filter_coefs_3point_triangle_sharp,
	osd_filter_coefs_3point_triangle,
	osd_filter_coefs_4point_triangle,
	vpp_filter_coefs_4point_bspline,
	osd_filter_coefs_3point_bspline
};

#define OSD_TYPE_TOP_FIELD 0
#define OSD_TYPE_BOT_FIELD 1

int is_vpp0(int index)
{
	if (index > OSD4 || index < OSD1) {
		osd_loge("%s, wrong index:%d\n", __func__, index);
		return 0;
	}

	return (osd_hw.vpp_index[index] == VPU_VPP0);
}

int is_vpp1(int index)
{
	if (index > OSD4 || index < OSD1) {
		osd_loge("%s, wrong index:%d\n", __func__, index);
		return 0;
	}

	return (osd_hw.vpp_index[index] == VPU_VPP1);
}

int is_vpp2(int index)
{
	if (index > OSD4 || index < OSD1) {
		osd_loge("%s, wrong index:%d\n", __func__, index);
		return 0;
	}

	return (osd_hw.vpp_index[index] == VPU_VPP2);
}

/* vpp2 or vpp3 */
int is_vppx(int index)
{
	return (is_vpp1(index) || is_vpp2(index));
}

int osd_get_chip_type(void)
{
	unsigned int cpu_type;

	cpu_type = get_cpu_id().family_id;
	return cpu_type;
}

void osd_vpu_power_on(void)
{
}

void osd_set_log_level(int level)
{
	osd_log_level = level;
	if (osd_log_level > 0)
		in_debug_mode = 1;
	else
		in_debug_mode = 0;
}

void stop_osd_log(void)
{
	if (in_debug_mode)
		return;

	osd_log_level_backup = osd_log_level;
	osd_log_level = -1;
}

void start_osd_log(void)
{
	if (in_debug_mode)
		return;

	osd_log_level = osd_log_level_backup;
}

void osd_get_hw_para(struct hw_para_s **para)
{
	*para = &osd_hw;
	return;
}

#ifdef CONFIG_AM_VIDEO
static struct vframe_s *osd_vf_peek(void *arg)
{
	if (osd_vf_need_update && (vf.width > 0) && (vf.height > 0))
		return &vf;
	else
		return NULL;
}

static struct vframe_s *osd_vf_get(void *arg)
{
	if (osd_vf_need_update) {
		vf_ext_light_unreg_provider(&osd_vf_prov);
		osd_vf_need_update = false;
		return &vf;
	}
	return NULL;
}

#define PROVIDER_NAME   "osd"
static const struct vframe_operations_s osd_vf_provider = {
	.peek = osd_vf_peek,
	.get  = osd_vf_get,
	.put  = NULL,
};

#endif

static inline void  osd_update_3d_mode(int enable_osd1, int enable_osd2,
				       int enable_osd3, int enable_osd4)
{
	if (enable_osd1)
		osd1_update_disp_3d_mode();
	if (enable_osd2)
		osd2_update_disp_3d_mode();
	if (enable_osd3)
		osd3_update_disp_3d_mode();
	if (enable_osd4)
		osd4_update_disp_3d_mode();
}

#if 1
static void get_encp_line(int *enc_line, int *active_line_begin)
{
#ifndef AML_C3_DISPLAY
	unsigned int reg = 0;
	unsigned int viu_sel;
	int osd_index;

	osd_index = get_osd_layer();
	if (is_vpp0(osd_index))
		viu_sel = osd_reg_read(VPU_VIU_VENC_MUX_CTRL) & 0x3;
	else
		viu_sel = (osd_reg_read(VPU_VIU_VENC_MUX_CTRL) >> 2) & 0x3;

	switch (viu_sel) {
	case 0:
		reg = osd_reg_read(ENCL_INFO_READ);
		*active_line_begin =
			osd_reg_read(ENCL_VIDEO_VAVON_BLINE);

		break;
	case 1:
		reg = osd_reg_read(ENCI_INFO_READ);
		*active_line_begin =
			osd_reg_read(ENCI_VFIFO2VD_LINE_TOP_START);
		break;
	case 2:
		reg = osd_reg_read(ENCP_INFO_READ);
		*active_line_begin =
			osd_reg_read(ENCP_VIDEO_VAVON_BLINE);
		break;
	case 3:
		reg = osd_reg_read(ENCT_INFO_READ);
		*active_line_begin =
			osd_reg_read(ENCT_VIDEO_VAVON_BLINE);
		break;
	}
	*enc_line = (reg >> 16) & 0x1fff;
	*enc_line -= (*active_line_begin);
#endif
}

static inline void wait_vsync_wakeup(void)
{
#ifndef AML_C3_DISPLAY
	int i = 0;
	int enc_line = 0;
	int active_line_begin;
	int vsync_line = 0;
	int line_after = 0;
#ifdef CONFIG_AML_VOUT
	struct vinfo_s *info = NULL;

	info = vout_get_current_vinfo();
	vsync_line = info->field_height;
#endif

	get_encp_line(&enc_line, &active_line_begin);

	/* if current line is always zero */
	if (enc_line == (0 - active_line_begin)) {
		_udelay(50);
		get_encp_line(&line_after, &active_line_begin);
		if (enc_line == (0 - active_line_begin))
			goto vsync_hit_flag;
	}

	while (enc_line < vsync_line) {
		if (i > 100000) {
			osd_logi("wait_vsync_wakeup exit\n");
			break;
		}
		i++;
		get_encp_line(&enc_line, &active_line_begin);
	}

vsync_hit_flag:
	vsync_hit = true;
#else
	int enc_line = 0;
	int active_line_begin;

	get_encp_line(&enc_line, &active_line_begin);
#endif
}
#else

static int get_encp_line(int *enc_line)
{
	int vsync_get = 0;
	unsigned int reg = 0;
	int field_status = 0;
	static int pre_field_status = 0;

	switch (osd_reg_read(VPU_VIU_VENC_MUX_CTRL) & 0x3) {
	case 0:
		reg = osd_reg_read(ENCL_INFO_READ);
		break;
	case 1:
		reg = osd_reg_read(ENCI_INFO_READ);
		break;
	case 2:
		reg = osd_reg_read(ENCP_INFO_READ);
		break;
	case 3:
		reg = osd_reg_read(ENCT_INFO_READ);
		break;
	}
	*enc_line = (reg >> 16) & 0x1fff;
	field_status = (reg >> 29) & 0x7;
	if (field_status != pre_field_status)
		vsync_get = 1;
	pre_field_status = field_status;
	return vsync_get;
}

static inline void wait_vsync_wakeup(void)
{
	int i = 0;
	int line = 0;
	int vsync_get = 0;

	vsync_get = get_encp_line(&line);
	if ((line > 0) || vsync_get) {
		while (!vsync_get) {
			if (i>100000) {
				osd_logi("wait_vsync_wakeup exit, i=%d\n", i);
				break;
			}
			i++;
			vsync_get = get_encp_line(&line);
		}
	}
	vsync_hit = true;
}
#endif

static inline void walk_through_update_list(void)
{
	u32  i, j;

	for (i = 0; i < HW_OSD_COUNT; i++) {
		j = 0;
		while (osd_hw.updated[i] && j < HW_REG_INDEX_MAX) {
			if (osd_hw.updated[i] & (1 << j)) {
				osd_hw.reg[i][j].update_func();
				remove_from_update_list(i, j);
			}
			j++;
		}
	}
}

static void osd_check_scan_mode(void)
{
#define	VOUT_ENCI	1
#define	VOUT_ENCP	2
#define	VOUT_ENCT	3
	int vmode = -1;

	osd_hw.scan_mode = SCAN_MODE_PROGRESSIVE;
#ifdef CONFIG_AML_VOUT
	vmode = vout_get_current_vmode();
#endif
	switch (vmode) {
	/* case VMODE_LCD:*/
	case VMODE_480I:
	case VMODE_480CVBS:
	case VMODE_576I:
	case VMODE_576CVBS:
	case VMODE_1080I:
	case VMODE_1080I_50HZ:
		osd_hw.scan_mode = SCAN_MODE_INTERLACE;
		break;
	default:
		break;
	}
}

#ifdef AML_C3_DISPLAY
static void irq_clr_c3(void)
{
	u32 data32, irq_src;

	data32 = osd_reg_read(hw_osd_vout_blend_reg.vpu_vout_irq_ctrl);
	if (osd_get_chip_type() == MESON_CPU_MAJOR_ID_A4) {
		irq_src = data32 >> 16;
		data32 |= irq_src;
	} else {
		data32 |= 0x01;
	}
	osd_reg_write(hw_osd_vout_blend_reg.vpu_vout_irq_ctrl, data32);
}
#endif

static void vsync_isr(void)
{
#ifndef AML_C3_DISPLAY
	unsigned int odd_even;
	unsigned int scan_line_number = 0;
#endif
	unsigned int fb0_cfg_w0, fb1_cfg_w0;

#ifdef AML_C3_DISPLAY
	irq_clr_c3();
#endif
	osd_check_scan_mode();
	if (osd_hw.scan_mode == SCAN_MODE_INTERLACE) {
		fb0_cfg_w0 = osd_reg_read(hw_osd_reg_array[0].osd_blk0_cfg_w0);
		fb1_cfg_w0 = osd_reg_read(hw_osd_reg_array[1].osd_blk0_cfg_w0);
#ifndef AML_C3_DISPLAY
		if (osd_reg_read(ENCP_VIDEO_MODE) & (1 << 12)) {
			/* 1080I */
			scan_line_number = ((osd_reg_read(ENCP_INFO_READ))
					    & 0x1fff0000) >> 16;
			if ((osd_hw.pandata[OSD1].y_start % 2) == 0) {
				if (scan_line_number >= 562) {
					/* bottom field, odd lines*/
					odd_even = 1;
				} else {
					/* top field, even lines*/
					odd_even = 0;
				}
			} else {
				if (scan_line_number >= 562) {
					/* top field, even lines*/
					odd_even = 0;
				} else {
					/* bottom field, odd lines*/
					odd_even = 1;
				}
			}
		} else {
			if ((osd_hw.pandata[OSD1].y_start % 2) == 0)
				odd_even = osd_reg_read(ENCI_INFO_READ) & 1;
			else
				odd_even = !(osd_reg_read(ENCI_INFO_READ) & 1);
		}
#endif
		fb0_cfg_w0 &= ~1;
		fb1_cfg_w0 &= ~1;
#ifndef AML_C3_DISPLAY
		fb0_cfg_w0 |= odd_even;
		fb1_cfg_w0 |= odd_even;
#endif
		osd_reg_write(hw_osd_reg_array[0].osd_blk0_cfg_w0, fb0_cfg_w0);
		osd_reg_write(hw_osd_reg_array[1].osd_blk0_cfg_w0, fb1_cfg_w0);
	}
	/* go through update list */
	if (!vsync_hit)
		wait_vsync_wakeup();
	walk_through_update_list();
	osd_update_3d_mode(osd_hw.mode_3d[OSD1].enable,
			   osd_hw.mode_3d[OSD2].enable,
			   osd_hw.mode_3d[OSD3].enable,
			   osd_hw.mode_3d[OSD4].enable);
}

void osd_wait_vsync_hw(void)
{
	//mdelay(16);
	vsync_isr();
	vsync_hit = false;
}

int osd_set_scan_mode(u32 index)
{
	u32 data32 = 0x0;
	int vmode = -1;
	int real_scan_mode = SCAN_MODE_INTERLACE;

#ifdef CONFIG_AML_VOUT
	vmode = vout_get_current_vmode();
#endif
	osd_hw.scan_mode = SCAN_MODE_PROGRESSIVE;
	if (osd_hw.fb_for_4k2k) {
		if (osd_hw.free_scale_enable[index])
			osd_hw.scale_workaround = 1;
	}
	switch (vmode) {
	/* case VMODE_LCD: */
	case VMODE_480I:
	case VMODE_480CVBS:
	case VMODE_576I:
	case VMODE_576CVBS:
		if (osd_hw.free_scale_mode[index]) {
			osd_hw.field_out_en = 1;
			switch (osd_hw.free_scale_data[index].y_end) {
			case 719:
				osd_hw.bot_type = 2;
				break;
			case 1079:
				osd_hw.bot_type = 3;
				break;
			default:
				osd_hw.bot_type = 2;
				break;
			}
		}
		osd_hw.scan_mode = real_scan_mode = SCAN_MODE_INTERLACE;
		break;
	case VMODE_1080I:
	case VMODE_1080I_50HZ:
#ifdef CONFIG_AML_VOUT_FRAMERATE_AUTOMATION
	case VMODE_1080I_59HZ:
#endif
		if (osd_hw.free_scale_mode[index]) {
			osd_hw.field_out_en = 1;
			switch (osd_hw.free_scale_data[index].y_end) {
			case 719:
				osd_hw.bot_type = 1;
				break;
			case 1079:
				osd_hw.bot_type = 2;
				break;
			default:
				osd_hw.bot_type = 1;
				break;
			}
		}
		osd_hw.scan_mode = real_scan_mode = SCAN_MODE_INTERLACE;
		break;
	case VMODE_4K2K_24HZ:
	case VMODE_4K2K_25HZ:
	case VMODE_4K2K_30HZ:
	case VMODE_4K2K_SMPTE:
	case VMODE_4K2K_SMPTE_25HZ:
	case VMODE_4K2K_SMPTE_30HZ:
	case VMODE_4K2K_SMPTE_50HZ:
	case VMODE_4K2K_SMPTE_60HZ:
	case VMODE_4K2K_SMPTE_50HZ_Y420:
	case VMODE_4K2K_SMPTE_60HZ_Y420:
		if (osd_hw.fb_for_4k2k) {
			if (osd_hw.free_scale_enable[index])
				osd_hw.scale_workaround = 1;
		}
		osd_hw.field_out_en = 0;
		break;
	default:
		if (osd_hw.free_scale_mode[index])
			osd_hw.field_out_en = 0;
		break;
	}
	if (osd_hw.free_scale_enable[index])
		osd_hw.scan_mode = SCAN_MODE_PROGRESSIVE;

	if (index == OSD1) {
		data32 = (osd_reg_read(hw_osd_reg_array[0].osd_blk0_cfg_w0) & 3) >> 1;
#ifndef AML_C3_DISPLAY
	} else if (index == OSD2) {
		if (real_scan_mode == SCAN_MODE_INTERLACE)
			return 1;
		/* data32 = (osd_reg_read(hw_osd_reg_array[1].osd_blk0_cfg_w0) & 3) >> 1; */
	} else {
		data32 = (osd_reg_read(VIU_OSD3_BLK0_CFG_W0) & 3) >> 1;
#endif
	}

	if (data32 == osd_hw.scan_mode)
		return 1;
	else
		return 0;
}

void  osd_set_gbl_alpha_hw(u32 index, u32 gbl_alpha)
{
	if (osd_hw.gbl_alpha[index] != gbl_alpha) {
		osd_hw.gbl_alpha[index] = gbl_alpha;
		add_to_update_list(index, OSD_GBL_ALPHA);
		osd_wait_vsync_hw();
	}
}

u32 osd_get_gbl_alpha_hw(u32  index)
{
	return osd_hw.gbl_alpha[index];
}

void osd_set_color_key_hw(u32 index, u32 color_index, u32 colorkey)
{
	u8 r = 0, g = 0, b = 0, a = (colorkey & 0xff000000) >> 24;
	u32 data32;

	colorkey &= 0x00ffffff;
	switch (color_index) {
	case COLOR_INDEX_16_655:
		r = (colorkey >> 10 & 0x3f) << 2;
		g = (colorkey >> 5 & 0x1f) << 3;
		b = (colorkey & 0x1f) << 3;
		break;
	case COLOR_INDEX_16_844:
		r = colorkey >> 8 & 0xff;
		g = (colorkey >> 4 & 0xf) << 4;
		b = (colorkey & 0xf) << 4;
		break;
	case COLOR_INDEX_16_565:
		r = (colorkey >> 11 & 0x1f) << 3;
		g = (colorkey >> 5 & 0x3f) << 2;
		b = (colorkey & 0x1f) << 3;
		break;
	case COLOR_INDEX_24_888_B:
		b = colorkey >> 16 & 0xff;
		g = colorkey >> 8 & 0xff;
		r = colorkey & 0xff;
		break;
	case COLOR_INDEX_24_RGB:
	case COLOR_INDEX_YUV_422:
		r = colorkey >> 16 & 0xff;
		g = colorkey >> 8 & 0xff;
		b = colorkey & 0xff;
		break;
	}
	data32 = r << 24 | g << 16 | b << 8 | a;
	if (osd_hw.color_key[index] != data32) {
		osd_hw.color_key[index] = data32;
		osd_logd2("bpp:%d--r:0x%x g:0x%x b:0x%x ,a:0x%x\n",
			  color_index, r, g, b, a);
		add_to_update_list(index, OSD_COLOR_KEY);
		osd_wait_vsync_hw();
	}
	return;
}

void  osd_srckey_enable_hw(u32  index, u8 enable)
{
	if (enable != osd_hw.color_key_enable[index]) {
		osd_hw.color_key_enable[index] = enable;
		add_to_update_list(index, OSD_COLOR_KEY_ENABLE);
		osd_wait_vsync_hw();
	}
}

void osd_set_color_mode(u32 index, const struct color_bit_define_s *color)
{
	if (color != osd_hw.color_info[index]) {
		osd_hw.color_info[index] = color;
		add_to_update_list(index, OSD_COLOR_MODE);
	}
}

void osd_update_disp_axis_hw(
	u32 index,
	u32 display_h_start,
	u32 display_h_end,
	u32 display_v_start,
	u32 display_v_end,
	u32 xoffset,
	u32 yoffset,
	u32 mode_change)
{
	struct pandata_s disp_data;
	struct pandata_s pan_data;

	if (osd_get_chip_type() == MESON_CPU_MAJOR_ID_M8) {
		if (index == OSD2)
			return;
	}
	if (NULL == osd_hw.color_info[index])
		return;
	disp_data.x_start = display_h_start;
	disp_data.y_start = display_v_start;
	disp_data.x_end = display_h_end;
	disp_data.y_end = display_v_end;
	pan_data.x_start = xoffset;
	pan_data.x_end = xoffset + (display_h_end - display_h_start);
	pan_data.y_start = yoffset;
	pan_data.y_end = yoffset + (display_v_end - display_v_start);
	/* if output mode change then reset pan ofFfset. */
	memcpy(&osd_hw.pandata[index], &pan_data, sizeof(struct pandata_s));
	memcpy(&osd_hw.dispdata[index], &disp_data, sizeof(struct pandata_s));
	if (mode_change) /* modify pandata . */
		add_to_update_list(index, OSD_COLOR_MODE);
	osd_hw.reg[index][DISP_GEOMETRY].update_func();
	osd_wait_vsync_hw();
}

/* the return stride unit is 128bit(16bytes) */
static u32 line_stride_calc(u32 fmt_mode,
			    u32 hsize,
			    u32 stride_align_32bytes)
{
	u32 line_stride = 0;
	u32 line_stride_32bytes;
	u32 line_stride_64bytes;

	switch (fmt_mode) {
	/* 2-bit LUT */
	case COLOR_INDEX_02_PAL4:
		line_stride = ((hsize << 1) + 127) >> 7;
		break;
	/* 4-bit LUT */
	case COLOR_INDEX_04_PAL16:
		line_stride = ((hsize << 2) + 127) >> 7;
		break;
	/* 8-bit LUT */
	case COLOR_INDEX_08_PAL256:
		line_stride = ((hsize << 3) + 127) >> 7;
		break;
	/* 4:2:2, 32-bit per 2 pixels */
	case COLOR_INDEX_YUV_422:
		line_stride = ((((hsize + 1) >> 1) << 5) + 127) >> 7;
		break;
	/* 16-bit LUT */
	case COLOR_INDEX_16_655:
	case COLOR_INDEX_16_844:
	case COLOR_INDEX_16_6442:
	case COLOR_INDEX_16_4444_R:
	case COLOR_INDEX_16_4642_R:
	case COLOR_INDEX_16_1555_A:
	case COLOR_INDEX_16_4444_A:
	case COLOR_INDEX_16_565:
		line_stride = ((hsize << 4) + 127) >> 7;
		break;
	/* 32-bit LUT */
	case COLOR_INDEX_32_BGRA:
	case COLOR_INDEX_32_ABGR:
	case COLOR_INDEX_32_RGBA:
	case COLOR_INDEX_32_ARGB:
		line_stride = ((hsize << 5) + 127) >> 7;
		break;
	/* 24-bit LUT */
	case COLOR_INDEX_24_6666_A:
	case COLOR_INDEX_24_6666_R:
	case COLOR_INDEX_24_8565:
	case COLOR_INDEX_24_5658:
	case COLOR_INDEX_24_888_B:
	case COLOR_INDEX_24_RGB:
		line_stride = ((hsize << 4) + (hsize << 3) + 127) >> 7;
		break;
	}
	line_stride_32bytes = ((line_stride + 1) >> 1) << 1;
	line_stride_64bytes = ((line_stride + 3) >> 2) << 2;
	/* need wr ddr is 32bytes aligned */
	if (stride_align_32bytes)
		line_stride = line_stride_32bytes;
	else
		line_stride = line_stride_64bytes;
	return line_stride;
}

#ifdef AML_OSD_HIGH_VERSION
/* only one layer */
void osd_setting_default_hwc(u32 index, struct pandata_s *disp_data)
{
	u32 width, height;
	u32 blend2_premult_en = 3, din_premult_en = 0;
	u32 blend_din_en = 0x5;
	/* blend_din0 input to blend0 */
	u32 din0_byp_blend = 0;
	/* blend1_dout to blend2 */
	u32 din2_osd_sel = 0;
	/* blend1_din3 input to blend1 */
	u32 din3_osd_sel = 0;
	u32 din_reoder_sel = 0x1;
	u32 postbld_src3_sel = 3, postbld_src4_sel = 0;
	u32 postbld_osd1_premult = 0, postbld_osd2_premult = 0;
	u32 reg_offset = 2;
	u32 shift_line = osd_hw.shift_line;

	if (osd_get_chip_type() > MESON_CPU_MAJOR_ID_TM2)
		reg_offset = 8;
	if (osd_get_chip_type() == MESON_CPU_MAJOR_ID_S5 ||
	    osd_get_chip_type() == MESON_CPU_MAJOR_ID_T7 ||
	    osd_get_chip_type() == MESON_CPU_MAJOR_ID_T3 ||
	    osd_get_chip_type() == MESON_CPU_MAJOR_ID_T5W ||
	    osd_get_chip_type() == MESON_CPU_MAJOR_ID_T5M ||
	    osd_get_chip_type() == MESON_CPU_MAJOR_ID_T3X)
		postbld_src3_sel = 4;

	/* for s5_display, OSDx to din(x+1) */
#ifdef AML_S5_DISPLAY
	blend_din_en = 1;
	index++;
#endif

	if (index == OSD1)
		din_reoder_sel = 0x4441;
	else if (index == OSD2)
		din_reoder_sel = 0x4442;
	else if (index == OSD3)
		din_reoder_sel = 0x4443;
	else if (index == OSD4)
		din_reoder_sel = 0x4444;

	/* depend on din0_premult_en */
	postbld_osd1_premult = 0;
	/* depend on din_premult_en bit 4 */
	postbld_osd2_premult = 0;
	/* osd blend ctrl */
	osd_reg_write(VIU_OSD_BLEND_CTRL,
		4				  << 29|
		blend2_premult_en << 27|
		din0_byp_blend	  << 26|
		din2_osd_sel	  << 25|
		din3_osd_sel	  << 24|
		blend_din_en	  << 20|
		din_premult_en	  << 16|
		din_reoder_sel);
	/* vpp osd1 blend ctrl */
#ifdef AML_S5_DISPLAY
	osd_reg_write(OSD1_BLEND_SRC_CTRL,
		      (postbld_src3_sel & 0xf) << 0 |
		      (postbld_osd1_premult & 0x1) << 4);
#else
	if (is_keystone_enable_for_txhd2())
		postbld_src3_sel = 0;
	osd_reg_write(OSD1_BLEND_SRC_CTRL,
		      (0 & 0xf) << 0 |
		      (0 & 0x1) << 4 |
		      (postbld_src3_sel & 0xf) << 8 |
		      (postbld_osd1_premult & 0x1) << 16 |
		      (1 & 0x1) << 20);
#endif
	/* vpp osd2 blend ctrl */
#ifdef AML_S5_DISPLAY
	osd_reg_write(OSD2_BLEND_SRC_CTRL,
		      (postbld_src4_sel & 0xf) << 0 |
		      (postbld_osd2_premult & 0x1) << 4);
#else
	osd_reg_write(OSD2_BLEND_SRC_CTRL,
		      (0 & 0xf) << 0 |
		      (0 & 0x1) << 4 |
		      (postbld_src4_sel & 0xf) << 8 |
		      (postbld_osd2_premult & 0x1) << 16 |
		      (1 & 0x1) << 20);
#endif
	/* Do later: different format select different dummy_data */
	/* used default dummy data */
	osd_reg_write(VIU_OSD_BLEND_DUMMY_DATA0,
		0x0 << 16 |
		0x0 << 8 |
		0x0);
	/* used default dummy alpha data */
	osd_reg_write(VIU_OSD_BLEND_DUMMY_ALPHA,
		0x0  << 20 |
		0x0  << 11 |
		0x0);

	width = disp_data->x_end - disp_data->x_start + 1;
	height = disp_data->y_end - disp_data->y_start + 1 + shift_line;
	/* it is setting for osdx */
	osd_reg_write(
		VIU_OSD_BLEND_DIN0_SCOPE_H + reg_offset * index,
		disp_data->x_end << 16 |
		disp_data->x_start);
	osd_reg_write(
		VIU_OSD_BLEND_DIN0_SCOPE_V + reg_offset * index,
		(disp_data->y_end + shift_line) << 16 |
		(disp_data->y_start + shift_line));
	if (index == OSD1) {
		int i;

		for (i = 1; i < 4; i++)
			osd_reg_write(
				VIU_OSD_BLEND_DIN0_SCOPE_V + reg_offset * i,
				0xffffffff);
	} else if (index == OSD2) {
		int i = 0;

		osd_reg_write(
			VIU_OSD_BLEND_DIN0_SCOPE_V + reg_offset * i,
			0xffffffff);
		for (i = 2; i < 4; i++)
			osd_reg_write(
				VIU_OSD_BLEND_DIN0_SCOPE_V + reg_offset * i,
				0xffffffff);
	} else if (index == OSD3) {
		int i = 0;

		for (i = 0; i < 2; i++)
			osd_reg_write(VIU_OSD_BLEND_DIN0_SCOPE_V +
				      reg_offset * i,
				      0xffffffff);

		i = 3;
		osd_reg_write(VIU_OSD_BLEND_DIN0_SCOPE_V + reg_offset * i,
			      0xffffffff);
	} else if (index == OSD4) {
		int i = 0;

		for (i = 0; i < 3; i++)
			osd_reg_write(VIU_OSD_BLEND_DIN0_SCOPE_V +
				      reg_offset * i,
				      0xffffffff);
	}

	osd_reg_write(VIU_OSD_BLEND_BLEND0_SIZE,
		height << 16 |
		width);
	osd_reg_write(VIU_OSD_BLEND_BLEND1_SIZE,
		height  << 16 |
		width);

#ifdef AML_S5_DISPLAY
	VSYNCOSD_WR_MPEG_REG(OSD_BLEND_DOUT0_SIZE,
			     height  << 16 | width);
	VSYNCOSD_WR_MPEG_REG(OSD_BLEND_DOUT1_SIZE,
			     height  << 16 | width);
#endif

#ifndef AML_S5_DISPLAY
	osd_reg_write(VPP_OSD1_IN_SIZE,
		height << 16 | width);
#endif
	if (!is_dolby_enable())
		osd_reg_set_bits(DOLBY_PATH_CTRL,
			0x3, 2, 2);

	/* setting blend scope */
	osd_reg_write(VPP_OSD1_BLD_H_SCOPE,
		disp_data->x_start << 16 | disp_data->x_end);
	osd_reg_write(VPP_OSD1_BLD_V_SCOPE,
		disp_data->y_start << 16 | disp_data->y_end);
}

void osd_update_blend(struct pandata_s *disp_data)
{
	u32 width, height;
#ifdef AML_S5_DISPLAY
	u32 blend_width, blend_height;
#endif
	int vmode = -1;
#ifdef AML_S5_DISPLAY
	u32 blend_dout_hsize, blend_dout_vsize;
	struct vinfo_s *vinfo = NULL;
#endif

#ifdef CONFIG_AML_VOUT
	vmode = vout_get_current_vmode();
#ifdef AML_S5_DISPLAY
	vinfo = vout_get_current_vinfo();
#endif
#endif
	switch (vmode) {
	/* case VMODE_LCD: */
	case VMODE_480I:
	case VMODE_480CVBS:
	case VMODE_576I:
	case VMODE_576CVBS:
	case VMODE_1080I:
	case VMODE_1080I_50HZ:
#ifdef CONFIG_AML_VOUT_FRAMERATE_AUTOMATION
	case VMODE_1080I_59HZ:
#endif
		disp_data->y_start /=2;
		disp_data->y_end /= 2;
		break;
	default:
		break;
	}
	width = disp_data->x_end - disp_data->x_start + 1;
	height = disp_data->y_end - disp_data->y_start + 1;

	/* setting pi */
	if (osd_hw.has_pi) {
		if (pi_enable)
			osd_reg_set_bits(OSD_PI_BYPASS_EN, 0, 0, 1);
		else
			osd_reg_set_bits(OSD_PI_BYPASS_EN, 1, 0, 1);
	}

	/* setting blend regs */
#ifdef AML_S5_DISPLAY
	blend_width = osd_hw.free_dst_data[0].x_end - osd_hw.free_dst_data[0].x_start + 1;
	blend_height = osd_hw.free_dst_data[0].y_end - osd_hw.free_dst_data[0].y_start + 1;
	if (width > 3840 && height > 2160) {
		blend_dout_hsize = BLEND_DOUT_DEF_HSIZE;
		blend_dout_vsize = BLEND_DOUT_DEF_VSIZE;
	} else {
		blend_dout_hsize = ALIGN(blend_width, 4);
		blend_dout_vsize = blend_height;
	}

	if (width > 3840 && height > 2160) {
		osd_reg_write(VIU_OSD_BLEND_DIN1_SCOPE_H,
			osd_hw.free_dst_data[0].x_end << 16 | osd_hw.free_dst_data[0].x_start);
		osd_reg_write(VIU_OSD_BLEND_DIN1_SCOPE_V,
			osd_hw.free_dst_data[0].y_end << 16 | osd_hw.free_dst_data[0].y_start);
		osd_reg_write(VPP_OSD1_BLD_H_SCOPE, vinfo->width - 1);
		osd_reg_write(VPP_OSD1_BLD_V_SCOPE, vinfo->height - 1);
	} else {
		osd_reg_write(VIU_OSD_BLEND_DIN1_SCOPE_H, (blend_width - 1) << 16);
		osd_reg_write(VIU_OSD_BLEND_DIN1_SCOPE_V, (blend_height - 1) << 16);
		osd_reg_write(VPP_OSD1_BLD_H_SCOPE,
			disp_data->x_start << 16 | disp_data->x_end);
		osd_reg_write(VPP_OSD1_BLD_V_SCOPE,
			disp_data->y_start << 16 | disp_data->y_end);
	}

	osd_reg_write(VIU_OSD_BLEND_BLEND0_SIZE,
			blend_dout_vsize << 16 | blend_dout_hsize);
	osd_reg_write(OSD_BLEND_DOUT0_SIZE,
			blend_dout_vsize << 16 | blend_dout_hsize);
#else
	/* setting blend scope */
	osd_reg_write(VPP_OSD1_BLD_H_SCOPE,
		disp_data->x_start << 16 | disp_data->x_end);
	osd_reg_write(VPP_OSD1_BLD_V_SCOPE,
		disp_data->y_start << 16 | disp_data->y_end);
#endif
	osd_reg_write(VPP_OUT_H_V_SIZE,
			width << 16 | height);

}
#endif

#ifdef AML_C3_DISPLAY
void osd_update_blend_c3(void)
{
	u32 blend_width, blend_height;

	blend_width = osd_hw.free_dst_data[0].x_end - osd_hw.free_dst_data[0].x_start + 1;
	blend_height = osd_hw.free_dst_data[0].y_end - osd_hw.free_dst_data[0].y_start + 1;
	osd_reg_write(hw_osd_vout_blend_reg.vpu_vout_blend_size,
		blend_width << 16 | blend_height);
	osd_reg_write(hw_osd_vout_blend_reg.vpu_vout_bld_src0_hpos, (blend_width - 1) << 16);
	osd_reg_write(hw_osd_vout_blend_reg.vpu_vout_bld_src0_vpos, (blend_height - 1) << 16);
}
#endif

static void osd_update_mif_linear_addr(u32 index)
{
	u32 line_stride, bpp;
	u32 fmt_mode = 0;
	u32 osd_blk1_cfg_w4, osd_blk2_cfg_w4, osd_ctrl_stat;

	switch (index) {
	case 0:
		osd_blk1_cfg_w4 = hw_osd_reg_array[0].osd_blk1_cfg_w4;
		osd_blk2_cfg_w4 = hw_osd_reg_array[0].osd_blk2_cfg_w4;
		osd_ctrl_stat = hw_osd_reg_array[0].osd_ctrl_stat;
		break;
	case 1:
		osd_blk1_cfg_w4 = hw_osd_reg_array[1].osd_blk1_cfg_w4;
		osd_blk2_cfg_w4 = hw_osd_reg_array[1].osd_blk2_cfg_w4;
		osd_ctrl_stat = hw_osd_reg_array[1].osd_ctrl_stat;
		break;
	case 2:
		osd_blk1_cfg_w4 = hw_osd_reg_array[2].osd_blk1_cfg_w4;
		osd_blk2_cfg_w4 = hw_osd_reg_array[2].osd_blk2_cfg_w4;
		osd_ctrl_stat = hw_osd_reg_array[2].osd_ctrl_stat;
		break;
	case 3:
		osd_blk1_cfg_w4 = hw_osd_reg_array[3].osd_blk1_cfg_w4;
		osd_blk2_cfg_w4 = hw_osd_reg_array[3].osd_blk2_cfg_w4;
		osd_ctrl_stat = hw_osd_reg_array[3].osd_ctrl_stat;
		break;
	default:
		osd_blk1_cfg_w4 = hw_osd_reg_array[0].osd_blk1_cfg_w4;
		osd_blk2_cfg_w4 = hw_osd_reg_array[0].osd_blk2_cfg_w4;
		osd_ctrl_stat = hw_osd_reg_array[0].osd_ctrl_stat;
		break;
	}
	if (osd_hw.color_info[index])
		fmt_mode =
			osd_hw.color_info[index]->color_index;
	bpp = osd_hw.color_info[index]->bpp / 8;
	/* 64 bytes align */
	line_stride = line_stride_calc
		(fmt_mode,
		osd_hw.fb_gem[index].width / bpp, 0);
	/* set frame addr, 8G addr, need >> 4*/
	VSYNCOSD_WR_MPEG_REG(osd_blk1_cfg_w4,
			     osd_hw.fb_gem[index].addr >> 4);
	/* set line stride */
	VSYNCOSD_WR_MPEG_REG_BITS(osd_blk2_cfg_w4,
		line_stride,
		0, 12);
	/* used phyic addr */
	VSYNCOSD_WR_MPEG_REG_BITS(osd_ctrl_stat,
		1, 2, 1);
}

static void set_fb_layout_info(u32 index, u32 fb_len)
{
	int i, offset = 0, vpp_num = 0;

	vpp_num = osd_hw.vpp_index[index];
	if (fb_layout[vpp_num].used) {
		osd_logi("%s, osd%d(vpp%d) is already set\n", __func__,
			 index, vpp_num);
		return;
	}
	for (i = 0; i < VPU_VPP_MAX; i++) {
		if (fb_layout[i].used)
			offset += fb_layout[i].fb_len;
	}
	fb_layout[vpp_num].fb_offset = offset;
	fb_layout[vpp_num].fb_len = fb_len;
	fb_layout[vpp_num].used = 1;
}

void clear_fb_layout_info(u32 index)
{
	int vpp_num = osd_hw.vpp_index[index];

	fb_layout[vpp_num].fb_offset = 0;
	fb_layout[vpp_num].fb_len = 0;
	fb_layout[vpp_num].used = 0;
}

unsigned int get_fb_offset(u32 index)
{
	int vpp_num = osd_hw.vpp_index[index];

	if (fb_layout[vpp_num].used)
		return fb_layout[vpp_num].fb_offset;

	osd_loge("%s, osd%d(vpp%d) fb_offset is not set\n",
		 __func__, index, vpp_num);
	return 0;
}

unsigned int get_fb_len(u32 index)
{
	int vpp_num = osd_hw.vpp_index[index];

	if (fb_layout[vpp_num].used)
		return fb_layout[vpp_num].fb_len;

	osd_loge("%s, osd%d(vpp%d) fb_len is not set\n",
		 __func__, index, vpp_num);
	return 0;
}

#ifdef AML_C3_DISPLAY
static void osd_setting_vout_blend(void)
{
	int axis[4] = {};

	if (osd_hw.free_dst_data[OSD1].x_end == 0 ||
		osd_hw.free_dst_data[OSD1].y_end == 0) {
		vout_get_current_axis(axis);
		osd_set_window_axis_hw(OSD1, axis[0], axis[1], axis[0] + axis[2] - 1,
			       axis[1] + axis[3] - 1);
	}

	VSYNCOSD_WR_MPEG_REG_BITS
		(VPU_VOUT_BLD_SRC1_HPOS,
		osd_hw.free_dst_data[OSD1].x_start,
		0, 13);
	VSYNCOSD_WR_MPEG_REG_BITS
		(VPU_VOUT_BLD_SRC1_HPOS,
		osd_hw.free_dst_data[OSD1].x_end,
		16, 13);

	VSYNCOSD_WR_MPEG_REG_BITS
		(VPU_VOUT_BLD_SRC1_VPOS,
		osd_hw.free_dst_data[OSD1].y_start,
		0, 13);
	VSYNCOSD_WR_MPEG_REG_BITS
		(VPU_VOUT_BLD_SRC1_VPOS,
		osd_hw.free_dst_data[OSD1].y_end,
		16, 13);
}

/* for c3 */
static void osd1_matrix_yuv2rgb(int yuv2rgb)
{
	int i;
	int mat_conv_en;
	int pre_offset[3], post_offset[3];
	int mat_coef[15];
	int rgb2yuvpre[3] = {0, 0, 0};
	int rgb2yuvpos[3] = {64, 512, 512};
	int yuv2rgbpre[3] = {-64, -512, -512};
	int yuv2rgbpos[3] = {0, 0, 0};
	static int matrix_save;

	/* matrix coef BT709 */
	int rgb2ycbcr[15] = {264, 516, 100, -152, -296, 448,
		448, -376, -72, 0, 0, 0, 0, 0, 0};
	int ycbcr2rgb[15] = {1197, 0, 1726, 1197, -193, -669,
		1197, 2202, 0, 0, 0, 0, 0, 0, 0};

	if (matrix_save == yuv2rgb)
		return;
	switch (yuv2rgb) {
	case MATRIX_BYPASS:
		mat_conv_en = 0;
		break;
	case YUV2RGB:
		mat_conv_en = 1;
		for (i = 0; i < 3; i++) {
			pre_offset[i] = yuv2rgbpre[i];
			post_offset[i] = yuv2rgbpos[i];
		}
		for (i = 0; i < 15; i++)
			mat_coef[i] = ycbcr2rgb[i];
		break;
	case RGB2YUV:
		mat_conv_en = 1;
		for (i = 0; i < 3; i++) {
			pre_offset[i] = rgb2yuvpre[i];
			post_offset[i] = rgb2yuvpos[i];
		}
		for (i = 0; i < 15; i++)
			mat_coef[i] = rgb2ycbcr[i];
		break;
	}
	matrix_save = yuv2rgb;
	if (yuv2rgb != MATRIX_BYPASS) {
		VSYNCOSD_WR_MPEG_REG
			(VOUT_OSD1_CSC_COEF00_01,
			(mat_coef[0] << 16) |
			(mat_coef[1] & 0x1FFF));
		VSYNCOSD_WR_MPEG_REG
			(VOUT_OSD1_CSC_COEF02_10,
			(mat_coef[2] << 16) |
			(mat_coef[1 * 3 + 0] & 0x1FFF));
		VSYNCOSD_WR_MPEG_REG
			(VOUT_OSD1_CSC_COEF11_12,
			(mat_coef[1 * 3 + 1] << 16) |
			(mat_coef[1 * 3 + 2] & 0x1FFF));
		VSYNCOSD_WR_MPEG_REG
			(VOUT_OSD1_CSC_COEF20_21,
			(mat_coef[2 * 3 + 0] << 16) |
			(mat_coef[2 * 3 + 1] & 0x1FFF));
		VSYNCOSD_WR_MPEG_REG
			(VOUT_OSD1_CSC_COEF22,
			mat_coef[2 * 3 + 2]);
		VSYNCOSD_WR_MPEG_REG
			(VOUT_OSD1_CSC_OFFSET0_1,
			(post_offset[0] << 16) |
			(post_offset[1] & 0xFFF));
		VSYNCOSD_WR_MPEG_REG
			(VOUT_OSD1_CSC_OFFSET2,
			post_offset[2]);
		VSYNCOSD_WR_MPEG_REG
			(VOUT_OSD1_CSC_PRE_OFFSET0_1,
			(pre_offset[0] << 16) |
			(pre_offset[1] & 0xFFF));
		VSYNCOSD_WR_MPEG_REG
			(VOUT_OSD1_CSC_PRE_OFFSET2,
			pre_offset[2]);
	}
	/* vd1_mat_en */
	VSYNCOSD_WR_MPEG_REG_BITS
		(VOUT_OSD1_CSC_EN_CTRL,
		mat_conv_en, 0, 1);
}
#endif

void osd_setup_hw(u32 index,
		  u32 xoffset,
		  u32 yoffset,
		  u32 xres,
		  u32 yres,
		  u32 xres_virtual,
		  u32 yres_virtual,
		  u32 disp_start_x,
		  u32 disp_start_y,
		  u32 disp_end_x,
		  u32 disp_end_y,
		  u32 fbmem,
		  const struct color_bit_define_s *color)
{
	struct pandata_s disp_data;
	struct pandata_s pan_data;
	int update_color_mode = 0;
	int update_geometry = 0;
	u32 w = (color->bpp * xres_virtual + 7) >> 3;
	u32 fb_len;
	char cmd[64];

	if (osd_hw.osd_ver == OSD_SIMPLE) {
		if (index >= OSD2) {
			osd_loge("AXG/A4/C3 not support osd2\n");
			return ;
		}
	}
	pan_data.x_start = xoffset;
	pan_data.y_start = yoffset;
	disp_data.x_start = disp_start_x;
	disp_data.y_start = disp_start_y;
	if (osd_hw.free_scale_enable[OSD1] && index == OSD1) {
		if (!(osd_hw.free_scale_mode[OSD1])) {
			pan_data.x_end = xoffset + g_vf_visual_width;
			pan_data.y_end = yoffset + g_vf_height;
			disp_data.x_end = disp_start_x + g_vf_width;
			disp_data.y_end = disp_start_y + g_vf_height;
		} else {
			pan_data.x_end = xoffset + (disp_end_x - disp_start_x);
			pan_data.y_end = yoffset + (disp_end_y - disp_start_y);
			disp_data.x_end = disp_end_x;
			disp_data.y_end = disp_end_y;
		}
	} else {
		pan_data.x_end = xoffset + (disp_end_x - disp_start_x);
		pan_data.y_end = yoffset + (disp_end_y - disp_start_y);
		if (likely(osd_hw.rotate[index].on_off
			   && osd_hw.rotate[index].on_off > 0)) {
			disp_data.x_end = disp_start_x + g_rotation_height;
			disp_data.y_end = disp_start_y + g_rotation_width;
		} else {
			disp_data.x_end = disp_end_x;
			disp_data.y_end = disp_end_y;
		}
	}
	if (color != osd_hw.color_info[index]) {
		update_color_mode = 1;
		osd_hw.color_info[index] = color;
	}
	if (osd_hw.fb_gem[index].addr != fbmem
	    || osd_hw.fb_gem[index].width != w
	    ||  osd_hw.fb_gem[index].height != yres_virtual) {
		osd_hw.fb_gem[index].addr = fbmem;
		osd_hw.fb_gem[index].width = w;
		osd_hw.fb_gem[index].height = yres_virtual;

		if (osd_hw.osd_ver == OSD_SIMPLE &&
			osd_get_chip_type() != MESON_CPU_MAJOR_ID_A4 &&
			osd_get_chip_type() != MESON_CPU_MAJOR_ID_C3) {
			u32 line_stride, fmt_mode, bpp;

			bpp = color->bpp/8;
			fmt_mode = color->color_index;
			line_stride = line_stride_calc(fmt_mode,
				osd_hw.fb_gem[index].width / bpp, 1);
			VSYNCOSD_WR_MPEG_REG(
				hw_osd_reg_array[0].osd_blk1_cfg_w4,
				osd_hw.fb_gem[index].addr);
			VSYNCOSD_WR_MPEG_REG_BITS(
				hw_osd_reg_array[0].osd_blk2_cfg_w4,
				line_stride,
				0, 12);
		} else if (osd_get_chip_type() == MESON_CPU_MAJOR_ID_A4) {
			osd_update_mif_linear_addr(OSD1);
		} else {
			fb_len = fb_gdev.fb_height *
				CANVAS_ALIGNED(fb_gdev.fb_width * color->bpp >> 3);
			if (!rma_test_addr) {
				set_fb_layout_info(index, fb_len);
				osd_hw.fb_gem[index].addr += get_fb_offset(index);
			}
			osd_logd("%s, set osd%d fb_addr:0x%x fb_len:%d\n",
				 __func__, index,
				 osd_hw.fb_gem[index].addr, fb_len);
			if (osd_hw.mif_linear)
				osd_update_mif_linear_addr(index);
#ifdef CONFIG_AML_CANVAS
			else
				canvas_config(osd_hw.fb_gem[index].canvas_idx,
					      osd_hw.fb_gem[index].addr,
					      CANVAS_ALIGNED(osd_hw.fb_gem[index].width),
					      osd_hw.fb_gem[index].height,
					      CANVAS_ADDR_NOWRAP, CANVAS_BLKMODE_LINEAR);
#endif
		}
		if (!rma_test_addr) {
			snprintf(cmd, sizeof(cmd), "setenv fb_addr 0x%x",
				 osd_hw.fb_gem[index].addr);
			run_command(cmd, 0);
		}
		osd_logd("osd[%d] canvas.idx =0x%x\n",
			 index, osd_hw.fb_gem[index].canvas_idx);
		osd_logd("osd[%d] canvas.addr=0x%x\n",
			 index, osd_hw.fb_gem[index].addr);
		osd_logd("osd[%d] canvas.width=%d\n",
			 index, CANVAS_ALIGNED(osd_hw.fb_gem[index].width));
		osd_logd("osd[%d] canvas.height=%d\n",
			 index, osd_hw.fb_gem[index].height);
	}
	/* osd blank only control by /sys/class/graphics/fbx/blank */
#if 0
	if (osd_hw.enable[index] == DISABLE) {
		osd_hw.enable[index] = ENABLE;
		add_to_update_list(index, OSD_ENABLE);
	}
#endif
	if (memcmp(&pan_data, &osd_hw.pandata[index],
		   sizeof(struct pandata_s)) != 0 ||
	    memcmp(&disp_data, &osd_hw.dispdata[index],
		   sizeof(struct pandata_s)) != 0) {
		update_geometry = 1;
		memcpy(&osd_hw.pandata[index], &pan_data,
		       sizeof(struct pandata_s));
		memcpy(&osd_hw.dispdata[index], &disp_data,
		       sizeof(struct pandata_s));
	}
	if (update_color_mode)
		add_to_update_list(index, OSD_COLOR_MODE);
	if (update_geometry)
		add_to_update_list(index, DISP_GEOMETRY);
	add_to_update_list(index, DISP_OSD_REVERSE);
#ifdef AML_OSD_HIGH_VERSION
	static int is_blend_set;

	if (rma_test || rma_test_addr)
		is_blend_set = 0;

	if (osd_hw.osd_ver == OSD_HIGH_ONE && is_vpp0(index) && !is_blend_set) {
		is_blend_set = 1;
		osd_setting_default_hwc(index, &disp_data);
	}
#endif
	osd_wait_vsync_hw();
}

void osd2_setup_hw(u32 index,
		  u32 xoffset,
		  u32 yoffset,
		  u32 xres,
		  u32 yres,
		  u32 xres_virtual,
		  u32 yres_virtual,
		  u32 disp_start_x,
		  u32 disp_start_y,
		  u32 disp_end_x,
		  u32 disp_end_y,
		  u32 fbmem,
		  const struct color_bit_define_s *color)
{
	struct pandata_s disp_data;
	struct pandata_s pan_data;
	int update_color_mode = 0;
	int update_geometry = 0;
	u32 w = (color->bpp * xres_virtual + 7) >> 3;

	if (osd_hw.osd_ver == OSD_SIMPLE) {
		if (index >= OSD2) {
			osd_loge("AXG not support osd2\n");
			return;
		}
	}
	pan_data.x_start = xoffset;
	pan_data.y_start = yoffset;
	disp_data.x_start = disp_start_x;
	disp_data.y_start = disp_start_y;
	if (osd_hw.free_scale_enable[OSD1] && index == OSD1) {
		if (!(osd_hw.free_scale_mode[OSD1])) {
			pan_data.x_end = xoffset + g_vf_visual_width;
			pan_data.y_end = yoffset + g_vf_height;
			disp_data.x_end = disp_start_x + g_vf_width;
			disp_data.y_end = disp_start_y + g_vf_height;
		} else {
			pan_data.x_end = xoffset + (disp_end_x - disp_start_x);
			pan_data.y_end = yoffset + (disp_end_y - disp_start_y);
			disp_data.x_end = disp_end_x;
			disp_data.y_end = disp_end_y;
		}
	} else {
		pan_data.x_end = xoffset + (disp_end_x - disp_start_x);
		pan_data.y_end = yoffset + (disp_end_y - disp_start_y);
		if (likely(osd_hw.rotate[index].on_off &&
			osd_hw.rotate[index].on_off > 0)) {
			disp_data.x_end = disp_start_x + g_rotation_height;
			disp_data.y_end = disp_start_y + g_rotation_width;
		} else {
			disp_data.x_end = disp_end_x;
			disp_data.y_end = disp_end_y;
		}
	}
	if (color != osd_hw.color_info[index]) {
		update_color_mode = 1;
		osd_hw.color_info[index] = color;
	}
	if (osd_hw.fb_gem[index].addr != fbmem ||
		osd_hw.fb_gem[index].width != w ||
		osd_hw.fb_gem[index].height != yres_virtual) {
		osd_hw.fb_gem[index].addr = fbmem;
		osd_hw.fb_gem[index].width = w;
		osd_hw.fb_gem[index].height = yres_virtual;

		if (osd_hw.osd_ver == OSD_SIMPLE) {
			u32 line_stride, fmt_mode, bpp;

			bpp = color->bpp / 8;
			fmt_mode = color->color_index;
			line_stride = line_stride_calc(fmt_mode,
				osd_hw.fb_gem[index].width / bpp, 1);
			VSYNCOSD_WR_MPEG_REG
				(hw_osd_reg_array[0].osd_blk1_cfg_w4,
				osd_hw.fb_gem[index].addr);
			VSYNCOSD_WR_MPEG_REG_BITS
				(hw_osd_reg_array[0].osd_blk2_cfg_w4,
				line_stride,
				0, 12);
		} else {
			if (osd_hw.mif_linear)
				osd_update_mif_linear_addr(index);
		}
		osd_logd("osd[%d] canvas.idx =0x%x\n",
			 index, osd_hw.fb_gem[index].canvas_idx);
		osd_logd("osd[%d] canvas.addr=0x%x\n",
			 index, osd_hw.fb_gem[index].addr);
		osd_logd("osd[%d] canvas.width=%d\n",
			 index, CANVAS_ALIGNED(osd_hw.fb_gem[index].width));
		osd_logd("osd[%d] canvas.height=%d\n",
			 index, osd_hw.fb_gem[index].height);
	}
	/* osd blank only control by /sys/class/graphics/fbx/blank */

	if (memcmp(&pan_data, &osd_hw.pandata[index],
		   sizeof(struct pandata_s)) != 0 ||
	    memcmp(&disp_data, &osd_hw.dispdata[index],
		   sizeof(struct pandata_s)) != 0) {
		update_geometry = 1;
		memcpy(&osd_hw.pandata[index], &pan_data,
		       sizeof(struct pandata_s));
		memcpy(&osd_hw.dispdata[index], &disp_data,
		       sizeof(struct pandata_s));
	}
	if (update_color_mode)
		add_to_update_list(index, OSD_COLOR_MODE);
	if (update_geometry)
		add_to_update_list(index, DISP_GEOMETRY);
	add_to_update_list(index, DISP_OSD_REVERSE);

	osd_wait_vsync_hw();
}

void osd_setpal_hw(u32 index,
		   unsigned regno,
		   unsigned red,
		   unsigned green,
		   unsigned blue,
		   unsigned transp
		  )
{
	if (regno < 256) {
		u32 pal;

		pal = ((red   & 0xff) << 24) |
		      ((green & 0xff) << 16) |
		      ((blue  & 0xff) <<  8) |
		      (transp & 0xff);
		VSYNCOSD_WR_MPEG_REG(hw_osd_reg_array[0].osd_color_addr +
			REG_OFFSET * index,
				     regno);
		VSYNCOSD_WR_MPEG_REG(hw_osd_reg_array[0].osd_color +
			REG_OFFSET * index, pal);
	}
}

void osd_get_order_hw(u32 index, u32 *order)
{
	*order = osd_hw.order & 0x3;
}

void osd_set_order_hw(u32 index, u32 order)
{
	if ((order != OSD_ORDER_01) && (order != OSD_ORDER_10))
		return;
	osd_hw.order = order;
	add_to_update_list(index, OSD_CHANGE_ORDER);
	osd_wait_vsync_hw();
}

/* vpu free scale mode */
static void osd_set_free_scale_enable_mode0(u32 index, u32 enable)
{
	static struct pandata_s save_disp_data = {0, 0, 0, 0};
#ifdef CONFIG_AM_VIDEO
#ifdef CONFIG_POST_PROCESS_MANAGER
	int mode_changed = 0;

	if ((index == OSD1) && (osd_hw.free_scale_enable[index] != enable))
		mode_changed = 1;
#endif
#endif

	osd_logi("osd%d free scale %s\n",
		 index, enable ? "ENABLE" : "DISABLE");
	enable = (enable & 0xffff ? 1 : 0);
	osd_hw.free_scale_enable[index] = enable;
	if (index == OSD1) {
		if (enable) {
			osd_vf_need_update = true;
#ifdef CONFIG_AM_VIDEO
			if ((osd_hw.free_scale_data[OSD1].x_end > 0)
			    && (osd_hw.free_scale_data[OSD1].x_end > 0)) {
				vf.width = osd_hw.free_scale_data[index].x_end -
					   osd_hw.free_scale_data[index].x_start + 1;
				vf.height =
					osd_hw.free_scale_data[index].y_end -
					osd_hw.free_scale_data[index].y_start + 1;
			} else {
				vf.width = osd_hw.free_scale_width[OSD1];
				vf.height = osd_hw.free_scale_height[OSD1];
			}
			vf.type = (VIDTYPE_NO_VIDEO_ENABLE | VIDTYPE_PROGRESSIVE
				   | VIDTYPE_VIU_FIELD | VIDTYPE_VSCALE_DISABLE);
			vf.ratio_control = DISP_RATIO_FORCECONFIG
					   | DISP_RATIO_NO_KEEPRATIO;
			if (osd_vf_prov_init == 0) {
				vf_provider_init(&osd_vf_prov,
						 PROVIDER_NAME, &osd_vf_provider, NULL);
				osd_vf_prov_init = 1;
			}
			vf_reg_provider(&osd_vf_prov);
			memcpy(&save_disp_data, &osd_hw.dispdata[OSD1],
			       sizeof(struct pandata_s));
			g_vf_visual_width =
				vf.width - 1 - osd_hw.dispdata[OSD1].x_start;
			g_vf_width = vf.width - 1;
			g_vf_height = vf.height - 1;
			osd_hw.dispdata[OSD1].x_end =
				osd_hw.dispdata[OSD1].x_start + vf.width - 1;
			osd_hw.dispdata[OSD1].y_end =
				osd_hw.dispdata[OSD1].y_start + vf.height - 1;
#endif
			osd_set_scan_mode(index);
			osd_hw.reg[index][DISP_GEOMETRY].update_func();
			osd_hw.reg[index][OSD_COLOR_MODE].update_func();
			osd_hw.reg[index][OSD_ENABLE].update_func();
		} else {
			osd_vf_need_update = false;
			osd_set_scan_mode(index);
			if (save_disp_data.x_end <= save_disp_data.x_start ||
			    save_disp_data.y_end <= save_disp_data.y_start)
				return;
			memcpy(&osd_hw.dispdata[OSD1], &save_disp_data,
			       sizeof(struct pandata_s));
			osd_hw.reg[index][DISP_GEOMETRY].update_func();
			osd_hw.reg[index][OSD_COLOR_MODE].update_func();
			osd_hw.reg[index][OSD_ENABLE].update_func();
#ifdef CONFIG_AM_VIDEO
			vf_unreg_provider(&osd_vf_prov);
#endif
		}
	} else {
		osd_hw.reg[index][DISP_GEOMETRY].update_func();
		osd_hw.reg[index][OSD_COLOR_MODE].update_func();
		osd_hw.reg[index][OSD_ENABLE].update_func();
	}
	osd_wait_vsync_hw();
#ifdef CONFIG_AM_VIDEO
#ifdef CONFIG_POST_PROCESS_MANAGER
	if (mode_changed) {
		/* extern void vf_ppmgr_reset(int type); */
		vf_ppmgr_reset(1);
	}
#endif
#endif
}

/* osd free scale mode */
static void osd_set_free_scale_enable_mode1(u32 index, u32 enable)
{
	unsigned int h_enable = 0;
	unsigned int v_enable = 0;
	int ret = 0;

	h_enable = (enable & 0xffff0000 ? 1 : 0);
	v_enable = (enable & 0xffff ? 1 : 0);
	osd_hw.free_scale[index].h_enable = h_enable;
	osd_hw.free_scale[index].v_enable = v_enable;
	osd_hw.free_scale_enable[index] = enable;
	if (osd_hw.free_scale_enable[index]) {
		if ((osd_hw.free_scale_data[index].x_end > 0) && h_enable) {
			osd_hw.free_scale_width[index] =
				osd_hw.free_scale_data[index].x_end -
				osd_hw.free_scale_data[index].x_start + 1;
		}
		if ((osd_hw.free_scale_data[index].y_end > 0) && v_enable) {
			osd_hw.free_scale_height[index] =
				osd_hw.free_scale_data[index].y_end -
				osd_hw.free_scale_data[index].y_start + 1;
		}
		ret = osd_set_scan_mode(index);
		if (ret)
			osd_hw.reg[index][OSD_COLOR_MODE].update_func();
		osd_hw.reg[index][OSD_FREESCALE_COEF].update_func();
		osd_hw.reg[index][DISP_GEOMETRY].update_func();
		osd_hw.reg[index][DISP_FREESCALE_ENABLE].update_func();
		osd_hw.reg[index][OSD_ENABLE].update_func();
	} else {
		ret = osd_set_scan_mode(index);
		if (ret)
			osd_hw.reg[index][OSD_COLOR_MODE].update_func();
		osd_hw.reg[index][DISP_GEOMETRY].update_func();
		osd_hw.reg[index][DISP_FREESCALE_ENABLE].update_func();
		osd_hw.reg[index][OSD_ENABLE].update_func();
	}
#ifdef AML_C3_DISPLAY
	osd_setting_vout_blend();
#endif
	osd_wait_vsync_hw();
}

void osd_set_free_scale_enable_hw(u32 index, u32 enable)
{
	if (osd_hw.free_scale_mode[index])
		osd_set_free_scale_enable_mode1(index, enable);
	else
		osd_set_free_scale_enable_mode0(index, enable);
}

void osd_get_free_scale_enable_hw(u32 index, u32 *free_scale_enable)
{
	*free_scale_enable = osd_hw.free_scale_enable[index];
}

void osd_set_free_scale_mode_hw(u32 index, u32 freescale_mode)
{
	osd_hw.free_scale_mode[index] = freescale_mode;
}

void osd_get_free_scale_mode_hw(u32 index, u32 *freescale_mode)
{
	*freescale_mode = osd_hw.free_scale_mode[index];
}

void osd_set_4k2k_fb_mode_hw(u32 fb_for_4k2k)
{
	osd_hw.fb_for_4k2k = fb_for_4k2k;
}

void osd_set_free_scale_width_hw(u32 index, u32 width)
{
	osd_hw.free_scale_width[index] = width;
	if (osd_hw.free_scale_enable[index] &&
	    (!osd_hw.free_scale_mode[index])) {
		osd_vf_need_update = true;
#ifdef CONFIG_AM_VIDEO
		vf.width = osd_hw.free_scale_width[index];
#endif
	}
}

void osd_get_free_scale_width_hw(u32 index, u32 *free_scale_width)
{
	*free_scale_width = osd_hw.free_scale_width[index];
}

void osd_set_free_scale_height_hw(u32 index, u32 height)
{
	osd_hw.free_scale_height[index] = height;
	if (osd_hw.free_scale_enable[index] &&
	    (!osd_hw.free_scale_mode[index])) {
		osd_vf_need_update = true;
#ifdef CONFIG_AM_VIDEO
		vf.height = osd_hw.free_scale_height[index];
#endif
	}
}

void osd_get_free_scale_height_hw(u32 index, u32 *free_scale_height)
{
	*free_scale_height = osd_hw.free_scale_height[index];
}

void osd_get_free_scale_axis_hw(u32 index, s32 *x0, s32 *y0, s32 *x1, s32 *y1)
{
	*x0 = osd_hw.free_scale_data[index].x_start;
	*y0 = osd_hw.free_scale_data[index].y_start;
	*x1 = osd_hw.free_scale_data[index].x_end;
	*y1 = osd_hw.free_scale_data[index].y_end;
}

void osd_set_free_scale_axis_hw(u32 index, s32 x0, s32 y0, s32 x1, s32 y1)
{
	osd_hw.free_scale_data[index].x_start = x0;
	osd_hw.free_scale_data[index].y_start = y0;
	osd_hw.free_scale_data[index].x_end = x1;
	osd_hw.free_scale_data[index].y_end = y1;
}

void osd_get_scale_axis_hw(u32 index, s32 *x0, s32 *y0, s32 *x1, s32 *y1)
{
	*x0 = osd_hw.scaledata[index].x_start;
	*x1 = osd_hw.scaledata[index].x_end;
	*y0 = osd_hw.scaledata[index].y_start;
	*y1 = osd_hw.scaledata[index].y_end;
}

void osd_set_scale_axis_hw(u32 index, s32 x0, s32 y0, s32 x1, s32 y1)
{
	osd_hw.scaledata[index].x_start = x0;
	osd_hw.scaledata[index].x_end = x1;
	osd_hw.scaledata[index].y_start = y0;
	osd_hw.scaledata[index].y_end = y1;
}

void osd_get_window_axis_hw(u32 index, s32 *x0, s32 *y0, s32 *x1, s32 *y1)
{
	int vmode = -1;

#ifdef CONFIG_AML_VOUT
	vmode = vout_get_current_vmode();
#endif
	switch (vmode) {
	/*case VMODE_LCD:*/
	case VMODE_480I:
	case VMODE_480CVBS:
	case VMODE_576I:
	case VMODE_576CVBS:
	case VMODE_1080I:
	case VMODE_1080I_50HZ:
#ifdef CONFIG_AML_VOUT_FRAMERATE_AUTOMATION
	case VMODE_1080I_59HZ:
#endif
		*y0 = osd_hw.free_dst_data[index].y_start * 2;
		*y1 = osd_hw.free_dst_data[index].y_end * 2;
		break;
	default:
		*y0 = osd_hw.free_dst_data[index].y_start;
		*y1 = osd_hw.free_dst_data[index].y_end;
		break;
	}
	*x0 = osd_hw.free_dst_data[index].x_start;
	*x1 = osd_hw.free_dst_data[index].x_end;
}

void osd_set_window_axis_hw(u32 index, s32 x0, s32 y0, s32 x1, s32 y1)
{
	int vmode = -1;

#ifdef CONFIG_AML_VOUT
	vmode = vout_get_current_vmode();
#endif
	switch (vmode) {
	/* case VMODE_LCD: */
	case VMODE_480I:
	case VMODE_480CVBS:
	case VMODE_576I:
	case VMODE_576CVBS:
	case VMODE_1080I:
	case VMODE_1080I_50HZ:
#ifdef CONFIG_AML_VOUT_FRAMERATE_AUTOMATION
	case VMODE_1080I_59HZ:
#endif
		osd_hw.free_dst_data[index].y_start = y0 / 2;
		osd_hw.free_dst_data[index].y_end = y1 / 2;
		break;
	default:
		osd_hw.free_dst_data[index].y_start = y0;
		osd_hw.free_dst_data[index].y_end = y1;
		break;
	}
	osd_hw.free_dst_data[index].x_start = x0;
	osd_hw.free_dst_data[index].x_end = x1;
#if defined(CONFIG_FB_OSD2_CURSOR)
	osd_hw.cursor_dispdata[index].x_start = x0;
	osd_hw.cursor_dispdata[index].x_end = x1;
	osd_hw.cursor_dispdata[index].y_start = y0;
	osd_hw.cursor_dispdata[index].y_end = y1;
#endif

	/* use pi to scale up 2X for w and h */
	if (osd_hw.has_pi) {
		u32 w = osd_hw.free_dst_data[index].x_end -
				osd_hw.free_dst_data[index].x_start + 1;
		u32 h = osd_hw.free_dst_data[index].y_end -
				osd_hw.free_dst_data[index].y_start + 1;

		if ((w > 3840 && h > 2160) || (w > 4096 && h > 2160))
			pi_enable = 1;
		else
			pi_enable = 0;

		if (pi_enable) {
			osd_hw.free_dst_data[index].x_start /= 2;
			osd_hw.free_dst_data[index].x_end =
				osd_hw.free_dst_data[index].x_start + w / 2 - 1;
			osd_hw.free_dst_data[index].y_start /= 2;
			osd_hw.free_dst_data[index].y_end =
				osd_hw.free_dst_data[index].y_start + h / 2 - 1;
		}
	}
}

void osd_get_block_windows_hw(u32 index, u32 *windows)
{
	memcpy(windows, osd_hw.block_windows[index],
	       sizeof(osd_hw.block_windows[index]));
}

void osd_set_block_windows_hw(u32 index, u32 *windows)
{
	memcpy(osd_hw.block_windows[index], windows,
	       sizeof(osd_hw.block_windows[index]));
	add_to_update_list(index, DISP_GEOMETRY);
	osd_wait_vsync_hw();
}

void osd_get_block_mode_hw(u32 index, u32 *mode)
{
	*mode = osd_hw.block_mode[index];
}

void osd_set_block_mode_hw(u32 index, u32 mode)
{
	osd_hw.block_mode[index] = mode;
	add_to_update_list(index, DISP_GEOMETRY);
	osd_wait_vsync_hw();
}

void osd_enable_3d_mode_hw(u32 index, u32 enable)
{
	osd_hw.mode_3d[index].enable = enable;
	if (enable) {
		/* when disable 3d mode ,we should return to standard state. */
		osd_hw.mode_3d[index].left_right = OSD_LEFT;
		osd_hw.mode_3d[index].l_start = osd_hw.pandata[index].x_start;
		osd_hw.mode_3d[index].l_end = (osd_hw.pandata[index].x_end +
					       osd_hw.pandata[index].x_start) >> 1;
		osd_hw.mode_3d[index].r_start = osd_hw.mode_3d[index].l_end + 1;
		osd_hw.mode_3d[index].r_end = osd_hw.pandata[index].x_end;
		osd_hw.mode_3d[index].origin_scale.h_enable =
			osd_hw.scale[index].h_enable;
		osd_hw.mode_3d[index].origin_scale.v_enable =
			osd_hw.scale[index].v_enable;
		osd_set_2x_scale_hw(index, 1, 0);
	} else {
		osd_set_2x_scale_hw(index,
				    osd_hw.mode_3d[index].origin_scale.h_enable,
				    osd_hw.mode_3d[index].origin_scale.v_enable);
	}
}

void osd_enable_hw(u32 index, u32 enable)
{
	osd_logd("osd[%d] enable: %d\n", index, enable);

	osd_hw.enable[index] = enable;
	add_to_update_list(index, OSD_ENABLE);
	osd_wait_vsync_hw();
}

u32 osd_get_state(u32 index)
{
	return VSYNCOSD_RD_MPEG_REG(hw_osd_reg_array[index].osd_ctrl_stat);
}

void osd_set_2x_scale_hw(u32 index, u16 h_scale_enable, u16 v_scale_enable)
{
	osd_logi("osd[%d] set scale, h_scale: %s, v_scale: %s\n",
		 index, h_scale_enable ? "ENABLE" : "DISABLE",
		 v_scale_enable ? "ENABLE" : "DISABLE");
	osd_logi("osd[%d].scaledata: %d %d %d %d\n",
		 index,
		 osd_hw.scaledata[index].x_start,
		 osd_hw.scaledata[index].x_end,
		 osd_hw.scaledata[index].y_start,
		 osd_hw.scaledata[index].y_end);
	osd_logi("osd[%d].pandata: %d %d %d %d\n",
		 index,
		 osd_hw.pandata[index].x_start,
		 osd_hw.pandata[index].x_end,
		 osd_hw.pandata[index].y_start,
		 osd_hw.pandata[index].y_end);
	osd_hw.scale[index].h_enable = h_scale_enable;
	osd_hw.scale[index].v_enable = v_scale_enable;
	osd_hw.reg[index][DISP_SCALE_ENABLE].update_func();
	osd_hw.reg[index][DISP_GEOMETRY].update_func();
	osd_wait_vsync_hw();
}

void osd_set_rotate_angle_hw(u32 index, u32 angle)
{
	osd_hw.rotate[index].angle = angle;
	add_to_update_list(index, DISP_OSD_ROTATE);

	osd_wait_vsync_hw();
}

void osd_get_rotate_angle_hw(u32 index, u32 *angle)
{
	*angle = osd_hw.rotate[index].angle;
}

void osd_set_rotate_on_hw(u32 index, u32 on_off)
{
	osd_hw.rotate[index].on_off = on_off;
	if (on_off) {
		g_rotation_width = osd_hw.rotation_pandata[index].x_end -
				   osd_hw.rotation_pandata[index].x_start;
		g_rotation_height = osd_hw.rotation_pandata[index].y_end -
				    osd_hw.rotation_pandata[index].y_start;
		osd_hw.dispdata[index].x_end = osd_hw.dispdata[OSD1].x_start +
					       g_rotation_height;
		osd_hw.dispdata[index].y_end = osd_hw.dispdata[OSD1].y_start +
					       g_rotation_width;
	} else {
#ifndef AML_C3_DISPLAY
		if (osd_get_chip_type() == MESON_CPU_MAJOR_ID_M8) {
			osd_reg_set_mask(VPU_SW_RESET, 1 << 8);
			osd_reg_clr_mask(VPU_SW_RESET, 1 << 8);
		}
		if (index == OSD1) {
			if (osd_get_chip_type() == MESON_CPU_MAJOR_ID_M8) {
				osd_reg_set_mask(VIU_SW_RESET, 1 << 0);
				osd_reg_clr_mask(VIU_SW_RESET, 1 << 0);
			}
			VSYNCOSD_SET_MPEG_REG_MASK(hw_osd_reg_array[0].osd_fifo_ctrl_stat,
						   1 << 0);
		} else {
			osd_reg_set_mask(VIU_SW_RESET, 1 << 1);
			osd_reg_clr_mask(VIU_SW_RESET, 1 << 1);
			VSYNCOSD_SET_MPEG_REG_MASK(hw_osd_reg_array[1].osd_fifo_ctrl_stat,
						   1 << 0);
		}
#else
		VSYNCOSD_SET_MPEG_REG_MASK(hw_osd_reg_array[0].osd_fifo_ctrl_stat,
				   1 << 0);

#endif
	}
	osd_hw.reg[index][OSD_COLOR_MODE].update_func();
	osd_hw.reg[index][DISP_GEOMETRY].update_func();
	osd_hw.reg[index][DISP_OSD_ROTATE].update_func();
	osd_wait_vsync_hw();
}

void osd_get_rotate_on_hw(u32 index, u32 *on_off)
{
	*on_off = osd_hw.rotate[index].on_off;
}

void osd_get_update_state_hw(u32 index, u32 *up_free)
{
	if (osd_vf_need_update)
		*up_free = 1;
	else
		*up_free = 0;
}

void osd_set_update_state_hw(u32 index, u32 up_free)
{
	if (up_free > 0)
		osd_vf_need_update = true;
	else
		osd_vf_need_update = false;
}

void osd_set_reverse_hw(u32 index, u32 reverse)
{
	osd_hw.osd_reverse[index] = reverse;
	add_to_update_list(index, DISP_OSD_REVERSE);
	osd_wait_vsync_hw();
}

void osd_get_reverse_hw(u32 index, u32 *reverse)
{
	*reverse = osd_hw.osd_reverse[index];
}

void osd_set_prot_canvas_hw(u32 index, s32 x_start, s32 y_start, s32 x_end,
			    s32 y_end)
{
	osd_hw.rotation_pandata[index].x_start = x_start;
	osd_hw.rotation_pandata[index].y_start = y_start;
	osd_hw.rotation_pandata[index].x_end = x_end;
	osd_hw.rotation_pandata[index].y_end = y_end;
	if (osd_hw.rotate[index].on_off && osd_hw.rotate[index].angle > 0) {
		g_rotation_width = osd_hw.rotation_pandata[index].x_end -
				   osd_hw.rotation_pandata[index].x_start;
		g_rotation_height = osd_hw.rotation_pandata[index].y_end -
				    osd_hw.rotation_pandata[index].y_start;
		osd_hw.dispdata[index].x_end = osd_hw.dispdata[OSD1].x_start +
					       g_rotation_height;
		osd_hw.dispdata[index].y_end = osd_hw.dispdata[OSD1].y_start +
					       g_rotation_width;
		osd_hw.reg[index][DISP_GEOMETRY].update_func();
		osd_hw.reg[index][OSD_COLOR_MODE].update_func();
	}
}

void osd_get_prot_canvas_hw(u32 index, s32 *x_start, s32 *y_start, s32 *x_end,
			    s32 *y_end)
{
	*x_start = osd_hw.rotation_pandata[index].x_start;
	*y_start = osd_hw.rotation_pandata[index].y_start;
	*x_end = osd_hw.rotation_pandata[index].x_end;
	*y_end = osd_hw.rotation_pandata[index].y_end;
}

void osd_pan_display_hw(u32 index, unsigned int xoffset, unsigned int yoffset)
{
	long diff_x, diff_y;

#if defined(CONFIG_FB_OSD2_CURSOR)
	if (index >= 1)
#else
	if (index >= 2)
#endif
		return;
	if (xoffset != osd_hw.pandata[index].x_start
	    || yoffset != osd_hw.pandata[index].y_start) {
		diff_x = xoffset - osd_hw.pandata[index].x_start;
		diff_y = yoffset - osd_hw.pandata[index].y_start;
		osd_hw.pandata[index].x_start += diff_x;
		osd_hw.pandata[index].x_end   += diff_x;
		osd_hw.pandata[index].y_start += diff_y;
		osd_hw.pandata[index].y_end   += diff_y;
		add_to_update_list(index, DISP_GEOMETRY);
		osd_wait_vsync_hw();
	}
#ifdef CONFIG_AM_FB_EXT
	osd_ext_clone_pan(index);
#endif
	osd_logd2("offset[%d-%d]x[%d-%d]y[%d-%d]\n",
		  xoffset, yoffset,
		  osd_hw.pandata[index].x_start,
		  osd_hw.pandata[index].x_end,
		  osd_hw.pandata[index].y_start,
		  osd_hw.pandata[index].y_end);
}

static  void  osd_update_disp_scale_enable(u32 index)
{
	if (osd_hw.scale[index].h_enable)
		VSYNCOSD_SET_MPEG_REG_MASK(hw_osd_reg_array[index].osd_blk0_cfg_w0,
			3 << 12);
	else
		VSYNCOSD_CLR_MPEG_REG_MASK(hw_osd_reg_array[index].osd_blk0_cfg_w0,
			3 << 12);
	if (osd_hw.scan_mode != SCAN_MODE_INTERLACE) {
		if (osd_hw.scale[index].v_enable)
			VSYNCOSD_SET_MPEG_REG_MASK(hw_osd_reg_array[index].osd_blk0_cfg_w0,
						   1 << 14);
		else
			VSYNCOSD_CLR_MPEG_REG_MASK(hw_osd_reg_array[index].osd_blk0_cfg_w0,
						   1 << 14);
	}
}

static  void  osd1_update_disp_scale_enable(void)
{
	osd_update_disp_scale_enable(OSD1);
}

static  void  osd2_update_disp_scale_enable(void)
{
	osd_update_disp_scale_enable(OSD2);
}

static void osd3_update_disp_scale_enable(void)
{
	osd_update_disp_scale_enable(OSD3);
}

static void osd4_update_disp_scale_enable(void)
{
	osd_update_disp_scale_enable(OSD4);
}

static void osd_super_scale_enable(u32 index)
{
#ifndef AML_C3_DISPLAY
#ifndef AML_OSD_HIGH_VERSION
	u32 data32 = 0x0;

	osd_super_scale_mem_power_on();
	/* enable osd scaler path */
	if (index == OSD1)
		data32 = 8;
	else {
		data32 = 1;       /* select osd2 input */
		data32 |= 1 << 3; /* enable osd scaler path */
	}
	VSYNCOSD_WR_MPEG_REG(hw_osd_reg_array[0].osd_sc_ctrl0, data32);
	/* enable osd super scaler */
	data32 = (1 << 0)
		 | (1 << 1)
		 | (1 << 2);
	VSYNCOSD_WR_MPEG_REG(OSDSR_CTRL_MODE, data32);
	/* config osd super scaler setting */
	VSYNCOSD_WR_MPEG_REG(OSDSR_UK_GRAD2DDIAG_LIMIT, 0xffffff);
	VSYNCOSD_WR_MPEG_REG(OSDSR_UK_GRAD2DADJA_LIMIT, 0xffffff);
	VSYNCOSD_WR_MPEG_REG(OSDSR_UK_BST_GAIN, 0x7a7a3a50);
	/* config osd super scaler input size */
	data32 = (osd_hw.free_scale_height[index] & 0x1fff)
		 | (osd_hw.free_scale_width[index] & 0x1fff) << 16;
	VSYNCOSD_WR_MPEG_REG(OSDSR_HV_SIZEIN, data32);
	/* config osd super scaler output size */
	data32 = ((osd_hw.free_dst_data[index].x_end & 0xfff) |
		  (osd_hw.free_dst_data[index].x_start & 0xfff) << 16);
	VSYNCOSD_WR_MPEG_REG(hw_osd_reg_array[0].osd_sco_h_start_end, data32);
	data32 = ((osd_hw.free_dst_data[index].y_end & 0xfff) |
		  (osd_hw.free_dst_data[index].y_start & 0xfff) << 16);
	VSYNCOSD_WR_MPEG_REG(hw_osd_reg_array[0].osd_sco_v_start_end, data32);
#endif
#endif
}

static void osd_super_scale_disable(void)
{
#ifndef AML_C3_DISPLAY
#ifndef AML_OSD_HIGH_VERSION
	/* disable osd scaler path */
	VSYNCOSD_WR_MPEG_REG(hw_osd_reg_array[0].osd_sc_ctrl0, 0);
	/* disable osd super scaler */
	VSYNCOSD_WR_MPEG_REG(OSDSR_HV_SIZEIN, 0);
	VSYNCOSD_WR_MPEG_REG(OSDSR_CTRL_MODE, 0);
	osd_super_scale_mem_power_off();
#endif
#endif
}

#define NEW_PPS_PHASE
#ifdef NEW_PPS_PHASE
#define OSD_ZOOM_BITS 20
#define OSD_PHASE_BITS 16

enum osd_f2v_vphase_type_e {
	OSD_F2V_IT2IT = 0,
	OSD_F2V_IB2IB,
	OSD_F2V_IT2IB,
	OSD_F2V_IB2IT,
	OSD_F2V_P2IT,
	OSD_F2V_P2IB,
	OSD_F2V_IT2P,
	OSD_F2V_IB2P,
	OSD_F2V_P2P,
	OSD_F2V_TYPE_MAX
};

struct osd_f2v_vphase_s {
	u8 rcv_num;
	u8 rpt_num;
	u16 phase;
};

static void f2v_get_vertical_phase(u32 zoom_ratio,
	enum osd_f2v_vphase_type_e type,
	u8 bank_length,
	struct osd_f2v_vphase_s *vphase)
{
	u8 f2v_420_in_pos_luma[OSD_F2V_TYPE_MAX] = {
		0, 2, 0, 2, 0, 0, 0, 2, 0};
	u8 f2v_420_out_pos[OSD_F2V_TYPE_MAX] = {
		0, 2, 2, 0, 0, 2, 0, 0, 0};
	s32 offset_in, offset_out;

	/* luma */
	offset_in = f2v_420_in_pos_luma[type]
		<< OSD_PHASE_BITS;
	offset_out = (f2v_420_out_pos[type] * zoom_ratio)
		>> (OSD_ZOOM_BITS - OSD_PHASE_BITS);

	vphase->rcv_num = bank_length;
	if (bank_length == 4 || bank_length == 3)
		vphase->rpt_num = 1;
	else
		vphase->rpt_num = 0;

	if (offset_in > offset_out) {
		vphase->rpt_num = vphase->rpt_num + 1;
		vphase->phase =
			((4 << OSD_PHASE_BITS) + offset_out - offset_in)
			>> 2;
	} else {
		while ((offset_in + (4 << OSD_PHASE_BITS))
			<= offset_out) {
			if (vphase->rpt_num == 1)
				vphase->rpt_num = 0;
			else
				vphase->rcv_num++;
			offset_in += 4 << OSD_PHASE_BITS;
		}
		vphase->phase = (offset_out - offset_in) >> 2;
	}
}
#endif

static void osd_update_disp_freescale_enable(u32 index, u32 reg_index)
{
	u64 hf_phase_step, vf_phase_step;
	int src_w, src_h, dst_w, dst_h;
	int bot_ini_phase, top_ini_phase;
	int vsc_ini_rcv_num, vsc_ini_rpt_p0_num;
	int vsc_bot_rcv_num = 0, vsc_bot_rpt_p0_num = 0;
	int hsc_ini_rcv_num, hsc_ini_rpt_p0_num;
	int hf_bank_len = 4;
	int vf_bank_len = 4;
	u32 data32 = 0x0;
	u32 shift_line = osd_hw.shift_line;

	osd_logi("osd%d_update_disp_freescale_enable\n", index);
	if (osd_hw.scale_workaround)
		vf_bank_len = 2;
	else
		vf_bank_len = 4;

#ifndef NEW_PPS_PHASE
	if (osd_hw.bot_type == 1) {
		vsc_bot_rcv_num = 4;
		vsc_bot_rpt_p0_num = 1;
	} else if (osd_hw.bot_type == 2) {
		vsc_bot_rcv_num = 6;
		vsc_bot_rpt_p0_num = 2;
	} else if (osd_hw.bot_type == 3) {
		vsc_bot_rcv_num = 8;
		vsc_bot_rpt_p0_num = 3;
	}
	vsc_ini_rcv_num = vf_bank_len;
	vsc_ini_rpt_p0_num =
		(vf_bank_len / 2 - 1) > 0 ? (vf_bank_len / 2 - 1) : 0;
#endif
	hsc_ini_rcv_num = hf_bank_len;
	hsc_ini_rpt_p0_num = hf_bank_len / 2 - 1;

	src_w = osd_hw.free_scale_width[index];
	src_h = osd_hw.free_scale_height[index];
	dst_w = osd_hw.free_dst_data[index].x_end -
		osd_hw.free_dst_data[index].x_start + 1;
	dst_h = osd_hw.free_dst_data[index].y_end -
		osd_hw.free_dst_data[index].y_start + 1;
	if (osd_get_chip_type() == MESON_CPU_MAJOR_ID_MG9TV) {
		/* super scaler mode */
		if (osd_hw.free_scale_mode[index] & 0x2) {
			if (osd_hw.free_scale_enable[index])
				osd_super_scale_enable(index);
			else
				osd_super_scale_disable();
			remove_from_update_list(index, DISP_FREESCALE_ENABLE);
			return;
		}
	}
	/* config osd sc control reg */
	data32 = 0x0;
	if (osd_hw.free_scale_enable[index]) {
		/* enable osd scaler */
		if (osd_hw.free_scale_mode[index] & 0x1) {
			if (osd_hw.osd_ver == OSD_NORMAL)
				data32 |= index;  /* select osd1/2 input */
			data32 |= 1 << 2; /* enable osd scaler */
			data32 |= 1 << 3; /* enable osd scaler path */
			VSYNCOSD_WR_MPEG_REG(hw_osd_reg_array[reg_index].osd_sc_ctrl0, data32);
		}
	} else {
		/* disable osd scaler path */
		VSYNCOSD_WR_MPEG_REG(hw_osd_reg_array[reg_index].osd_sc_ctrl0, 0);
	}

	hf_phase_step = (u64)src_w << 24;
	if (dst_w == 0)
		dst_w = 1;
	do_div(hf_phase_step, dst_w);
	if (shift_line) {
		vf_phase_step = (u64)(src_h - 1) << 20;
		if (dst_h == 0)
			dst_h = 1;
		do_div(vf_phase_step, dst_h);
	} else {
		vf_phase_step = (u64)src_h << 20;
		if (dst_h == 0)
			dst_h = 1;
		do_div(vf_phase_step, dst_h);
	}

#ifdef NEW_PPS_PHASE
	if (osd_hw.field_out_en) {
		struct osd_f2v_vphase_s vphase;

		f2v_get_vertical_phase(vf_phase_step,
			OSD_F2V_P2IT,
			vf_bank_len,
			&vphase);
		vsc_ini_rcv_num = vphase.rcv_num;
		vsc_ini_rpt_p0_num = vphase.rpt_num;
		top_ini_phase = vphase.phase;

		f2v_get_vertical_phase(vf_phase_step,
			OSD_F2V_P2IB,
			vf_bank_len,
			&vphase);
		vsc_bot_rcv_num = vphase.rcv_num;
		vsc_bot_rpt_p0_num = vphase.rpt_num;
		bot_ini_phase = vphase.phase;
	} else {
		struct osd_f2v_vphase_s vphase;

		f2v_get_vertical_phase(vf_phase_step,
			OSD_F2V_P2P,
			vf_bank_len,
			&vphase);
		vsc_ini_rcv_num = vphase.rcv_num;
		vsc_ini_rpt_p0_num = vphase.rpt_num;
		top_ini_phase = vphase.phase;

		vsc_bot_rcv_num = 0;
		vsc_bot_rpt_p0_num = 0;
		bot_ini_phase = 0;
	}
#else
	if (osd_hw.field_out_en) /* interface output */
		bot_ini_phase = ((vf_phase_step / 2) >> 4);
	else
		bot_ini_phase = 0;
	top_ini_phase = 0;
#endif

	vf_phase_step = (vf_phase_step << 4);
	/* config osd scaler in/out hv size */
	if (shift_line) {
		vsc_ini_rcv_num++;
		if (osd_hw.field_out_en)
			vsc_bot_rcv_num++;
	}

#ifdef AML_S5_DISPLAY
	VSYNCOSD_WR_MPEG_REG
		(hw_osd_reg_array[reg_index].osd_proc_in_size,
		 (src_h << 16) | src_w);
	VSYNCOSD_WR_MPEG_REG
		(hw_osd_reg_array[reg_index].osd_proc_out_size,
		 (dst_h << 16) | dst_w);
#endif

	data32 = 0x0;
	if (osd_hw.free_scale_enable[index]) {
		data32 = (((src_h - 1 + shift_line) & 0x1fff)
			  | ((src_w - 1) & 0x1fff) << 16);
		VSYNCOSD_WR_MPEG_REG(hw_osd_reg_array[reg_index].osd_sci_wh_m1, data32);
		data32 = ((osd_hw.free_dst_data[index].x_end & 0xfff) |
			  (osd_hw.free_dst_data[index].x_start & 0xfff) << 16);
		VSYNCOSD_WR_MPEG_REG(hw_osd_reg_array[reg_index].osd_sco_h_start_end, data32);
		data32 = ((osd_hw.free_dst_data[index].y_end & 0xfff) |
			  (osd_hw.free_dst_data[index].y_start & 0xfff) << 16);
		VSYNCOSD_WR_MPEG_REG(hw_osd_reg_array[reg_index].osd_sco_v_start_end, data32);
	}
	data32 = 0x0;
	if (osd_hw.free_scale[index].v_enable) {
		data32 |= (vf_bank_len & 0x7)
			  | ((vsc_ini_rcv_num & 0xf) << 3)
			  | ((vsc_ini_rpt_p0_num & 0x3) << 8);
		if (osd_hw.field_out_en)
			data32 |= ((vsc_bot_rcv_num & 0xf) << 11)
				  | ((vsc_bot_rpt_p0_num & 0x3) << 16)
				  | (1 << 23);
		if (osd_hw.scale_workaround)
			data32 |= 1 << 21;
		data32 |= 1 << 24;
		if (osd_get_chip_type() >= MESON_CPU_MAJOR_ID_G12B)
			data32 |= 1 << 25;
	}
	VSYNCOSD_WR_MPEG_REG(hw_osd_reg_array[reg_index].osd_vsc_ctrl0, data32);
	data32 = 0x0;
	if (osd_hw.free_scale[index].h_enable) {
		data32 |= (hf_bank_len & 0x7)
			  | ((hsc_ini_rcv_num & 0xf) << 3)
			  | ((hsc_ini_rpt_p0_num & 0x3) << 8);
		data32 |= 1 << 22;
	}
	VSYNCOSD_WR_MPEG_REG(hw_osd_reg_array[reg_index].osd_hsc_ctrl0, data32);

	data32 = top_ini_phase;
	if (osd_hw.free_scale_enable[index]) {
		data32 |= (bot_ini_phase & 0xffff) << 16;
		if (osd_hw.field_out_en) {
			if (shift_line)
				src_h--;
			if (src_h == dst_h * 2)
				data32 |= 0x80008000;
		}
		VSYNCOSD_WR_MPEG_REG_BITS(hw_osd_reg_array[reg_index].osd_hsc_phase_step,
					  hf_phase_step, 0, 28);
		VSYNCOSD_WR_MPEG_REG_BITS(hw_osd_reg_array[reg_index].osd_hsc_init_phase,
			0, 0, 16);
		VSYNCOSD_WR_MPEG_REG_BITS(hw_osd_reg_array[reg_index].osd_vsc_phase_step,
					  vf_phase_step, 0, 28);
		VSYNCOSD_WR_MPEG_REG(hw_osd_reg_array[reg_index].osd_vsc_init_phase, data32);
	}
	remove_from_update_list(index, DISP_FREESCALE_ENABLE);
}

static void osd1_update_disp_freescale_enable(void)
{
	osd_update_disp_freescale_enable(OSD1, OSD1);
}

static void osd2_update_disp_freescale_enable(void)
{
	if (is_keystone_enable_for_txhd2())
		osd_update_disp_freescale_enable(OSD2, OSD2);
	else
		osd_update_disp_freescale_enable(OSD2, OSD1);
}

#if defined(AML_T7_DISPLAY) || defined(AML_S5_DISPLAY)
static void osdx_update_disp_freescale_enable(u32 index)
{
	u64 hf_phase_step, vf_phase_step;
	int src_w, src_h, dst_w, dst_h;
	int bot_ini_phase, top_ini_phase;
	int vsc_ini_rcv_num, vsc_ini_rpt_p0_num;
	int vsc_bot_rcv_num = 0, vsc_bot_rpt_p0_num = 0;
	int hsc_ini_rcv_num, hsc_ini_rpt_p0_num;
	int hf_bank_len = 4;
	int vf_bank_len = 4;
	u32 data32 = 0x0;
	u32 shift_line = osd_hw.shift_line;
	u32 osd_sc_ctrl0 = 0, osd_sci_wh_m1 = 0;
	u32 osd_sco_h_start_end = 0, osd_sco_v_start_end = 0;
	u32 osd_sco_hsc_ctrl0 = 0, osd_sco_vsc_ctrl0 = 0;
	u32 osd_sco_hsc_phase_step = 0, osd_sco_vsc_phase_step = 0;
	u32 osd_sco_hsc_ini_phase = 0, osd_sco_vsc_ini_phase = 0;

	if (is_vpp0(index)) {
		osd_sc_ctrl0 = hw_osd_reg_array[0].osd_sc_ctrl0;
		osd_sci_wh_m1 = hw_osd_reg_array[0].osd_sci_wh_m1;
		osd_sco_h_start_end = hw_osd_reg_array[0].osd_sco_h_start_end;
		osd_sco_v_start_end = hw_osd_reg_array[0].osd_sco_v_start_end;
		osd_sco_hsc_ctrl0 = hw_osd_reg_array[0].osd_hsc_ctrl0;
		osd_sco_vsc_ctrl0 = hw_osd_reg_array[0].osd_vsc_ctrl0;
		osd_sco_hsc_phase_step = hw_osd_reg_array[0].osd_hsc_phase_step;
		osd_sco_hsc_ini_phase = hw_osd_reg_array[0].osd_hsc_init_phase;
		osd_sco_vsc_phase_step = hw_osd_reg_array[0].osd_vsc_phase_step;
		osd_sco_vsc_ini_phase = hw_osd_reg_array[0].osd_vsc_init_phase;
	} else if (is_vpp1(index)) {
		osd_sc_ctrl0 = hw_osd_reg_array[2].osd_sc_ctrl0;
		osd_sci_wh_m1 = hw_osd_reg_array[2].osd_sci_wh_m1;
		osd_sco_h_start_end = hw_osd_reg_array[2].osd_sco_h_start_end;
		osd_sco_v_start_end = hw_osd_reg_array[2].osd_sco_v_start_end;
		osd_sco_hsc_ctrl0 = hw_osd_reg_array[2].osd_hsc_ctrl0;
		osd_sco_vsc_ctrl0 = hw_osd_reg_array[2].osd_vsc_ctrl0;
		osd_sco_hsc_phase_step = hw_osd_reg_array[2].osd_hsc_phase_step;
		osd_sco_hsc_ini_phase = hw_osd_reg_array[2].osd_hsc_init_phase;
		osd_sco_vsc_phase_step = hw_osd_reg_array[2].osd_vsc_phase_step;
		osd_sco_vsc_ini_phase = hw_osd_reg_array[2].osd_vsc_init_phase;
	} else if (is_vpp2(index)) {
		osd_sc_ctrl0 = hw_osd_reg_array[3].osd_sc_ctrl0;
		osd_sci_wh_m1 = hw_osd_reg_array[3].osd_sci_wh_m1;
		osd_sco_h_start_end = hw_osd_reg_array[3].osd_sco_h_start_end;
		osd_sco_v_start_end = hw_osd_reg_array[3].osd_sco_v_start_end;
		osd_sco_hsc_ctrl0 = hw_osd_reg_array[3].osd_hsc_ctrl0;
		osd_sco_vsc_ctrl0 = hw_osd_reg_array[3].osd_vsc_ctrl0;
		osd_sco_hsc_phase_step = hw_osd_reg_array[3].osd_hsc_phase_step;
		osd_sco_hsc_ini_phase = hw_osd_reg_array[3].osd_hsc_init_phase;
		osd_sco_vsc_phase_step = hw_osd_reg_array[3].osd_vsc_phase_step;
		osd_sco_vsc_ini_phase = hw_osd_reg_array[3].osd_vsc_init_phase;
	} else {
		osd_loge("%s: invalid osd_index\n", __func__);
		return;
	}

	if (osd_hw.scale_workaround)
		vf_bank_len = 2;
	else
		vf_bank_len = 4;

#ifndef NEW_PPS_PHASE
	if (osd_hw.bot_type == 1) {
		vsc_bot_rcv_num = 4;
		vsc_bot_rpt_p0_num = 1;
	} else if (osd_hw.bot_type == 2) {
		vsc_bot_rcv_num = 6;
		vsc_bot_rpt_p0_num = 2;
	} else if (osd_hw.bot_type == 3) {
		vsc_bot_rcv_num = 8;
		vsc_bot_rpt_p0_num = 3;
	}
	vsc_ini_rcv_num = vf_bank_len;
	vsc_ini_rpt_p0_num =
		(vf_bank_len / 2 - 1) > 0 ? (vf_bank_len / 2 - 1) : 0;
#endif
	hsc_ini_rcv_num = hf_bank_len;
	hsc_ini_rpt_p0_num = hf_bank_len / 2 - 1;

	src_w = osd_hw.free_scale_width[index];
	src_h = osd_hw.free_scale_height[index];
	dst_w = osd_hw.free_dst_data[index].x_end -
		osd_hw.free_dst_data[index].x_start + 1;
	dst_h = osd_hw.free_dst_data[index].y_end -
		osd_hw.free_dst_data[index].y_start + 1;

	if (osd_get_chip_type() == MESON_CPU_MAJOR_ID_MG9TV) {
		/* super scaler mode */
		if (osd_hw.free_scale_mode[index] & 0x2) {
			if (osd_hw.free_scale_enable[index])
				osd_super_scale_enable(index);
			else
				osd_super_scale_disable();
			remove_from_update_list(index, DISP_FREESCALE_ENABLE);
			return;
		}
	}
	/* config osd sc control reg */
	data32 = 0x0;
	if (osd_hw.free_scale_enable[index]) {
		/* enable osd scaler */
		if (osd_hw.free_scale_mode[index] & 0x1) {
			data32 |= 1;      /* select osd2 input */
			data32 |= 1 << 2; /* enable osd scaler */
			data32 |= 1 << 3; /* enable osd scaler path */
			VSYNCOSD_WR_MPEG_REG(osd_sc_ctrl0, data32);
		}
	} else {
		/* disable osd scaler path */
		VSYNCOSD_WR_MPEG_REG(osd_sc_ctrl0, 0);
	}

	hf_phase_step = (u64)src_w << 24;
	if (dst_w == 0)
		dst_w = 1;
	do_div(hf_phase_step, dst_w);
	if (shift_line) {
		vf_phase_step = (u64)(src_h - 1) << 20;
		if (dst_h == 0)
			dst_h = 1;
		do_div(vf_phase_step, dst_h);
	} else {
		vf_phase_step = (u64)src_h << 20;
		if (dst_h == 0)
			dst_h = 1;
		do_div(vf_phase_step, dst_h);
	}

#ifdef NEW_PPS_PHASE
	if (osd_hw.field_out_en) {
		struct osd_f2v_vphase_s vphase;

		f2v_get_vertical_phase(vf_phase_step,
			OSD_F2V_P2IT,
			vf_bank_len,
			&vphase);
		vsc_ini_rcv_num = vphase.rcv_num;
		vsc_ini_rpt_p0_num = vphase.rpt_num;
		top_ini_phase = vphase.phase;

		f2v_get_vertical_phase(vf_phase_step,
			OSD_F2V_P2IB,
			vf_bank_len,
			&vphase);
		vsc_bot_rcv_num = vphase.rcv_num;
		vsc_bot_rpt_p0_num = vphase.rpt_num;
		bot_ini_phase = vphase.phase;
	} else {
		struct osd_f2v_vphase_s vphase;

		f2v_get_vertical_phase(vf_phase_step,
			OSD_F2V_P2P,
			vf_bank_len,
			&vphase);
		vsc_ini_rcv_num = vphase.rcv_num;
		vsc_ini_rpt_p0_num = vphase.rpt_num;
		top_ini_phase = vphase.phase;

		vsc_bot_rcv_num = 0;
		vsc_bot_rpt_p0_num = 0;
		bot_ini_phase = 0;
	}
#else
	if (osd_hw.field_out_en)	 /* interface output */
		bot_ini_phase = ((vf_phase_step / 2) >> 4);
	else
		bot_ini_phase = 0;
	top_ini_phase = 0;
#endif

	vf_phase_step = (vf_phase_step << 4);
	/* config osd scaler in/out hv size */
	if (shift_line) {
		vsc_ini_rcv_num++;
		if (osd_hw.field_out_en)
			vsc_bot_rcv_num++;
	}

#ifdef AML_S5_DISPLAY
	VSYNCOSD_WR_MPEG_REG
		(hw_osd_reg_array[index].osd_proc_in_size,
		 (src_h << 16) | src_w);
	VSYNCOSD_WR_MPEG_REG
		(hw_osd_reg_array[index].osd_proc_out_size,
		 (dst_h << 16) | dst_w);
#endif
	data32 = 0x0;
	if (osd_hw.free_scale_enable[index]) {
		data32 = (((src_h - 1 + shift_line) & 0x1fff)
			  | ((src_w - 1) & 0x1fff) << 16);
		VSYNCOSD_WR_MPEG_REG(osd_sci_wh_m1, data32);
		data32 = ((osd_hw.free_dst_data[index].x_end & 0xfff) |
			  (osd_hw.free_dst_data[index].x_start & 0xfff) << 16);
		VSYNCOSD_WR_MPEG_REG(osd_sco_h_start_end, data32);
		data32 = ((osd_hw.free_dst_data[index].y_end & 0xfff) |
			  (osd_hw.free_dst_data[index].y_start & 0xfff) << 16);
		VSYNCOSD_WR_MPEG_REG(osd_sco_v_start_end, data32);
	}
	data32 = 0x0;
	if (osd_hw.free_scale[index].h_enable) {
		data32 |= (hf_bank_len & 0x7)
			  | ((hsc_ini_rcv_num & 0xf) << 3)
			  | ((hsc_ini_rpt_p0_num & 0x3) << 8);
		data32 |= 1 << 22;
	}
	VSYNCOSD_WR_MPEG_REG(osd_sco_hsc_ctrl0, data32);
	data32 = 0x0;
	if (osd_hw.free_scale[index].v_enable) {
		data32 |= (vf_bank_len & 0x7)
			  | ((vsc_ini_rcv_num & 0xf) << 3)
			  | ((vsc_ini_rpt_p0_num & 0x3) << 8);
		if (osd_hw.field_out_en)   /* interface output */
			data32 |= ((vsc_bot_rcv_num & 0xf) << 11)
				  | ((vsc_bot_rpt_p0_num & 0x3) << 16)
				  | (1 << 23);
		if (osd_hw.scale_workaround)
			data32 |= 1 << 21;
		data32 |= 1 << 24;
		if (osd_get_chip_type() >= MESON_CPU_MAJOR_ID_G12B)
			data32 |= 1 << 25;
	}
	VSYNCOSD_WR_MPEG_REG(osd_sco_vsc_ctrl0, data32);
	data32 = top_ini_phase;
	if (osd_hw.free_scale_enable[index]) {
		data32 |= (bot_ini_phase & 0xffff) << 16;
		if (osd_hw.field_out_en) {
			if (shift_line)
				src_h--;
			if (src_h == dst_h * 2)
				data32 |= 0x80008000;
		}
		VSYNCOSD_WR_MPEG_REG_BITS(osd_sco_hsc_phase_step,
					  hf_phase_step, 0, 28);
		VSYNCOSD_WR_MPEG_REG_BITS(osd_sco_hsc_ini_phase, 0, 0, 16);
		VSYNCOSD_WR_MPEG_REG_BITS(osd_sco_vsc_phase_step,
					  vf_phase_step, 0, 28);
		VSYNCOSD_WR_MPEG_REG(osd_sco_vsc_ini_phase, data32);
	}
	if (is_vpp1(index)) {
#ifdef AML_T7_DISPLAY
		/* hdr in size */
		VSYNCOSD_WR_MPEG_REG(OSD3_HDR_IN_SIZE, dst_h << 16 | dst_w);
		/* vpp_top1 scope */
		VSYNCOSD_WR_MPEG_REG
			(VPP1_BLD_DIN1_HSCOPE,
			 (osd_hw.free_dst_data[index].x_start << 16) |
			 osd_hw.free_dst_data[index].x_end);

		VSYNCOSD_WR_MPEG_REG
			(VPP1_BLD_DIN1_VSCOPE,
			 (osd_hw.free_dst_data[index].y_start << 16) |
			 osd_hw.free_dst_data[index].y_end);

		VSYNCOSD_WR_MPEG_REG(VPP1_BLD_OUT_SIZE, dst_h << 16 | dst_w);
#endif
#ifdef AML_S5_DISPLAY
		/* vpp1 scope */
		VSYNCOSD_WR_MPEG_REG
			(VPP1_OSD3_BLD_H_SCOPE,
			 (osd_hw.free_dst_data[index].x_start << 16) |
			 osd_hw.free_dst_data[index].x_end);

		VSYNCOSD_WR_MPEG_REG
			(VPP1_OSD3_BLD_V_SCOPE,
			 (osd_hw.free_dst_data[index].y_start << 16) |
			 osd_hw.free_dst_data[index].y_end);

		VSYNCOSD_WR_MPEG_REG(VPP1_BLEND_H_V_SIZE, dst_h << 16 | dst_w);
#endif
		osd_logd2("vpp1 bld scop(%d %d %d %d)\n",
			osd_hw.free_dst_data[index].x_start,
			osd_hw.free_dst_data[index].x_end,
			osd_hw.free_dst_data[index].y_start,
			osd_hw.free_dst_data[index].y_end);
	} else if (is_vpp2(index)) {
		/* hdr in size */
		VSYNCOSD_WR_MPEG_REG(OSD4_HDR_IN_SIZE, dst_h << 16 | dst_w);
		/* vpp_top1 scope */
		VSYNCOSD_WR_MPEG_REG
			(VPP2_BLD_DIN1_HSCOPE,
			 (osd_hw.free_dst_data[index].x_start << 16) |
			 osd_hw.free_dst_data[index].x_end);

		VSYNCOSD_WR_MPEG_REG
			(VPP2_BLD_DIN1_VSCOPE,
			 (osd_hw.free_dst_data[index].y_start << 16) |
			 osd_hw.free_dst_data[index].y_end);

		VSYNCOSD_WR_MPEG_REG(VPP2_BLD_OUT_SIZE, dst_h << 16 | dst_w);

		osd_logd2("vpp2 bld scop(%d %d %d %d)\n",
			osd_hw.free_dst_data[index].x_start,
			osd_hw.free_dst_data[index].x_end,
			osd_hw.free_dst_data[index].y_start,
			osd_hw.free_dst_data[index].y_end);
	}
	remove_from_update_list(index, DISP_FREESCALE_ENABLE);
}
#endif

static void osd_update_coef(u32 index)
{
	int i;
	bool need_update_coef = false;
	int hf_coef_wren = 1;
	int vf_coef_wren = 1;
	unsigned int *hf_coef, *vf_coef;

	if (osd_hw.scale_workaround) {
		if (use_v_filter_mode != 3) {
			use_v_filter_mode = 3;
			need_update_coef = true;
		} else
			need_update_coef = false;
	} else {
		if (use_v_filter_mode != osd_v_filter_mode) {
			use_v_filter_mode = osd_v_filter_mode;
			need_update_coef = true;
		} else
			need_update_coef = false;
	}
	if (need_update_coef) {
		vf_coef = filter_table[use_v_filter_mode];
		if (vf_coef_wren) {
			osd_reg_set_bits(hw_osd_reg_array[index].osd_scale_coef_idx,
				0x0000, 0, 9);
			for (i = 0; i < 33; i++)
				osd_reg_write(hw_osd_reg_array[index].osd_scale_coef, vf_coef[i]);
		}
	}
	need_update_coef = false;
	if (use_h_filter_mode != osd_h_filter_mode) {
		use_h_filter_mode = osd_h_filter_mode;
		need_update_coef = true;
	}
	hf_coef = filter_table[use_h_filter_mode];
	if (need_update_coef) {
		if (hf_coef_wren) {
			osd_reg_set_bits(hw_osd_reg_array[index].osd_scale_coef_idx,
				0x0100, 0, 9);
			for (i = 0; i < 33; i++)
				osd_reg_write(hw_osd_reg_array[index].osd_scale_coef, hf_coef[i]);
		}
	}
}

static void osd1_update_coef(void)
{
	osd_update_coef(OSD1);
	remove_from_update_list(OSD1, OSD_FREESCALE_COEF);
}

static void osd2_update_coef(void)
{
	if (is_keystone_enable_for_txhd2())
		osd_update_coef(OSD2);
	else
		osd_update_coef(OSD1);
	remove_from_update_list(OSD2, OSD_FREESCALE_COEF);
}

#if defined(AML_T7_DISPLAY) || defined(AML_S5_DISPLAY)
static void osdx_update_coef(u32 index)
{
	int i;
	bool need_update_coef = false;
	int hf_coef_wren = 1;
	int vf_coef_wren = 1;
	unsigned int *hf_coef, *vf_coef;
	u32 osd_scale_coef_idx = 0;
	u32 osd_scale_coef = 0;
	static int osd34_use_v_filter_mode[2] = {-1, -1};
	static int osd34_use_h_filter_mode[2] = {-1, -1};
	int *use_v_filter_mode;
	int *use_h_filter_mode;

	osd_logd2("%s, index:%d\n", __func__, index);

	if (is_vpp0(index)) {
		use_v_filter_mode = &osd34_use_v_filter_mode[0];
		use_h_filter_mode = &osd34_use_h_filter_mode[0];
		osd_scale_coef_idx = hw_osd_reg_array[0].osd_scale_coef_idx;
		osd_scale_coef = hw_osd_reg_array[0].osd_scale_coef;
	} else {
		if (is_vpp1(index)) { /* OSD3->VPP1 */
			use_v_filter_mode = &osd34_use_v_filter_mode[0];
			use_h_filter_mode = &osd34_use_h_filter_mode[0];
		} else {              /* OSD4->VPP2 */
			use_v_filter_mode = &osd34_use_v_filter_mode[1];
			use_h_filter_mode = &osd34_use_h_filter_mode[1];
		}
		osd_scale_coef_idx = hw_osd_reg_array[index].osd_scale_coef_idx;
		osd_scale_coef = hw_osd_reg_array[index].osd_scale_coef;
	}

	if (osd_hw.scale_workaround) {
		if (*use_v_filter_mode != 3) {
			*use_v_filter_mode = 3;
			need_update_coef = true;
		} else {
			need_update_coef = false;
		}
	} else {
		if (*use_v_filter_mode != osd_v_filter_mode) {
			*use_v_filter_mode = osd_v_filter_mode;
			need_update_coef = true;
		} else {
			need_update_coef = false;
		}
	}
	vf_coef = filter_table[*use_v_filter_mode];
	if (need_update_coef) {
		if (vf_coef_wren) {
			osd_reg_set_bits(osd_scale_coef_idx, 0x0000, 0, 9);
			for (i = 0; i < 33; i++)
				osd_reg_write(osd_scale_coef, vf_coef[i]);
		}
	}
	need_update_coef = false;
	if (*use_h_filter_mode != osd_h_filter_mode) {
		*use_h_filter_mode = osd_h_filter_mode;
		need_update_coef = true;
	}
	hf_coef = filter_table[*use_h_filter_mode];
	if (need_update_coef) {
		if (hf_coef_wren) {
			osd_reg_set_bits(osd_scale_coef_idx, 0x0100, 0, 9);
			for (i = 0; i < 33; i++)
				osd_reg_write(osd_scale_coef, hf_coef[i]);
		}
	}
	remove_from_update_list(index, OSD_FREESCALE_COEF);
}

static void osd3_update_disp_freescale_enable(void)
{
	osdx_update_disp_freescale_enable(OSD3);
}

static void osd4_update_disp_freescale_enable(void)
{
	osdx_update_disp_freescale_enable(OSD4);
}

static void osd3_update_coef(void)
{
	osdx_update_coef(OSD3);
}

static void osd4_update_coef(void)
{
	osdx_update_coef(OSD4);
}
#else
static void osd3_update_disp_freescale_enable(void)
{
	/* do nothing */
	remove_from_update_list(OSD3, DISP_FREESCALE_ENABLE);
}

static void osd4_update_disp_freescale_enable(void)
{
	/* do nothing */
	remove_from_update_list(OSD4, DISP_FREESCALE_ENABLE);
}

static void osd3_update_coef(void)
{
	osd_update_coef(OSD1);
	remove_from_update_list(OSD3, OSD_FREESCALE_COEF);
}

static void osd4_update_coef(void)
{
	/* do nothing */
	remove_from_update_list(OSD4, OSD_FREESCALE_COEF);
}
#endif

static void osd_update_color_mode(u32 index)
{
	u32 data32 = 0;

	if (osd_hw.color_info[index]) {
		data32 = (osd_hw.scan_mode == SCAN_MODE_INTERLACE) ? 2 : 0;
		data32 |= VSYNCOSD_RD_MPEG_REG(hw_osd_reg_array[index].osd_blk0_cfg_w0)
			  & 0x30007040;
		data32 |= osd_hw.fb_gem[index].canvas_idx << 16;
		if (!osd_hw.rotate[index].on_off)
			data32 |= OSD_DATA_LITTLE_ENDIAN << 15;

		/*after t3x VIU_OSD1_BLK0_CFG_W0 format bit(bit2-bit5) has change*/
		if (osd_get_chip_type() >= MESON_CPU_MAJOR_ID_T3X &&
			osd_hw.color_info[index]->color_index == 16)
			data32 |= 2 << 2;
		else
			data32 |= osd_hw.color_info[index]->hw_colormat << 2;
		if (osd_get_chip_type() < MESON_CPU_MAJOR_ID_GXTVBB) {
			if (osd_hw.color_info[index]->color_index
				< COLOR_INDEX_YUV_422)
				data32 |= 1 << 7; /* yuv enable */
		}
		/* osd_blk_mode */
		data32 |=  osd_hw.color_info[index]->hw_blkmode << 8;
		VSYNCOSD_WR_MPEG_REG(hw_osd_reg_array[index].osd_blk0_cfg_w0, data32);
	}
	remove_from_update_list(index, OSD_COLOR_MODE);
}

static void osd1_update_color_mode(void)
{
	osd_update_color_mode(OSD1);
}

static void osd2_update_color_mode(void)
{
	osd_update_color_mode(OSD2);
}

static void osd3_update_color_mode(void)
{
	osd_update_color_mode(OSD3);
}

static void osd4_update_color_mode(void)
{
	osd_update_color_mode(OSD4);
}

#ifndef AML_C3_DISPLAY
static void osd1_update_enable(void)
{
	u32 video_enable = 0;

	if (osd_hw.free_scale_mode[OSD1]) {
		if (osd_hw.enable[OSD1] == ENABLE) {
			if (osd_hw.osd_ver <= OSD_NORMAL)
			VSYNCOSD_SET_MPEG_REG_MASK(VPP_MISC,
						   VPP_OSD1_POSTBLEND | VPP_POSTBLEND_EN);
			VSYNCOSD_SET_MPEG_REG_MASK
				(hw_osd_reg_array[0].osd_ctrl_stat, 1 << 0);
		} else {
			VSYNCOSD_CLR_MPEG_REG_MASK
				(hw_osd_reg_array[0].osd_ctrl_stat, 1 << 0);
			if (osd_hw.osd_ver <= OSD_NORMAL)
			VSYNCOSD_CLR_MPEG_REG_MASK(VPP_MISC,
						   VPP_OSD1_POSTBLEND);
		}
	} else if (osd_hw.osd_ver <= OSD_NORMAL) {
		video_enable |= VSYNCOSD_RD_MPEG_REG(VPP_MISC)&VPP_VD1_PREBLEND;
		if (osd_hw.enable[OSD1] == ENABLE) {
			if (osd_hw.free_scale_enable[OSD1]) {
				VSYNCOSD_CLR_MPEG_REG_MASK(VPP_MISC,
							   VPP_OSD1_POSTBLEND);
				VSYNCOSD_SET_MPEG_REG_MASK(VPP_MISC,
							   VPP_OSD1_PREBLEND
							   | VPP_VD1_POSTBLEND
							   | VPP_PREBLEND_EN);
			} else {
				VSYNCOSD_CLR_MPEG_REG_MASK(VPP_MISC,
							   VPP_OSD1_PREBLEND);
				if (!video_enable)
					VSYNCOSD_CLR_MPEG_REG_MASK(VPP_MISC,
								   VPP_VD1_POSTBLEND);
				VSYNCOSD_SET_MPEG_REG_MASK(VPP_MISC,
							   VPP_OSD1_POSTBLEND);
			}
		} else {
			if (osd_hw.free_scale_enable[OSD1])
				VSYNCOSD_CLR_MPEG_REG_MASK(VPP_MISC,
							   VPP_OSD1_PREBLEND);
			else
				VSYNCOSD_CLR_MPEG_REG_MASK(VPP_MISC,
							   VPP_OSD1_POSTBLEND);
		}
	}
	remove_from_update_list(OSD1, OSD_ENABLE);
}

static void osd2_update_enable(void)
{
	u32 video_enable = 0;

	if (osd_hw.free_scale_mode[OSD2]) {
		if (osd_hw.enable[OSD2] == ENABLE)
			VSYNCOSD_SET_MPEG_REG_MASK(hw_osd_reg_array[1].osd_ctrl_stat,
						   1 << 0);
		else
			VSYNCOSD_CLR_MPEG_REG_MASK(hw_osd_reg_array[1].osd_ctrl_stat,
						   1 << 0);

		/* for older chips than g12a:
		 * freescale output always on VPP_OSD1_POSTBLEND
		 * if freescale is enable, VPP_OSD1_POSTBLEND to control OSD1&OSD2
		 * if freescale is disable, VPP_OSD2_POSTBLEND to control OSD2
		 */
		if (osd_hw.osd_ver <= OSD_NORMAL) {
			if (osd_hw.free_scale_enable[OSD2]) {
				if (osd_hw.enable[OSD2] == ENABLE)
						VSYNCOSD_SET_MPEG_REG_MASK(VPP_MISC,
									   VPP_OSD1_POSTBLEND
									   | VPP_POSTBLEND_EN);
				else
					if (!osd_hw.enable[OSD1])
						VSYNCOSD_CLR_MPEG_REG_MASK(VPP_MISC,
									   VPP_OSD1_POSTBLEND);
			} else {
				if (osd_hw.enable[OSD2] == ENABLE)
						VSYNCOSD_SET_MPEG_REG_MASK(VPP_MISC,
									   VPP_OSD2_POSTBLEND
									   | VPP_POSTBLEND_EN);
				else
						VSYNCOSD_CLR_MPEG_REG_MASK(VPP_MISC,
									   VPP_OSD2_POSTBLEND);
			}
		}
	} else if (osd_hw.osd_ver <= OSD_NORMAL){
		video_enable |= VSYNCOSD_RD_MPEG_REG(VPP_MISC)&VPP_VD1_PREBLEND;
		if (osd_hw.enable[OSD2] == ENABLE) {
			if (osd_hw.free_scale_enable[OSD2]) {
				VSYNCOSD_CLR_MPEG_REG_MASK(VPP_MISC,
							   VPP_OSD2_POSTBLEND);
				VSYNCOSD_SET_MPEG_REG_MASK(VPP_MISC,
							   VPP_OSD2_PREBLEND
							   | VPP_VD1_POSTBLEND);
			} else {
				VSYNCOSD_CLR_MPEG_REG_MASK(VPP_MISC,
							   VPP_OSD2_PREBLEND);
				if (!video_enable)
					VSYNCOSD_CLR_MPEG_REG_MASK(VPP_MISC,
								   VPP_VD1_POSTBLEND);
				VSYNCOSD_SET_MPEG_REG_MASK(VPP_MISC,
							   VPP_OSD2_POSTBLEND);
			}
		} else {
			if (osd_hw.free_scale_enable[OSD2])
				VSYNCOSD_CLR_MPEG_REG_MASK(VPP_MISC,
							   VPP_OSD2_PREBLEND);
			else
				VSYNCOSD_CLR_MPEG_REG_MASK(VPP_MISC,
							   VPP_OSD2_POSTBLEND);
		}
	}
	remove_from_update_list(OSD2, OSD_ENABLE);
}
#endif

static void osd_update_enable(u32 index)
{
	if (osd_hw.free_scale_mode[index]) {
		if (osd_hw.enable[index] == ENABLE) {
			VSYNCOSD_SET_MPEG_REG_MASK
				(hw_osd_reg_array[index].osd_ctrl_stat,
				1 << 0);
#ifdef AML_C3_DISPLAY
			VSYNCOSD_WR_MPEG_REG_BITS(hw_osd_vout_blend_reg.vpu_vout_blend_ctrl,
			2, 0, 2);
#endif
		} else {
			VSYNCOSD_CLR_MPEG_REG_MASK
				(hw_osd_reg_array[index].osd_ctrl_stat,
				1 << 0);
#ifdef AML_C3_DISPLAY
			VSYNCOSD_WR_MPEG_REG_BITS(hw_osd_vout_blend_reg.vpu_vout_blend_ctrl,
			0, 0, 2);
#endif
		}
	}
	remove_from_update_list(index, OSD_ENABLE);
}

#ifdef AML_C3_DISPLAY
static void osd1_update_enable(void)
{
	osd_update_enable(OSD1);
}

static void osd2_update_enable(void)
{
	remove_from_update_list(OSD2, OSD_ENABLE);
}

#ifndef OSD_SLT_DISABLE
int test_for_c3(u32 osd_index, u32 fb_data)
{
	/*C3 slt test by probe,*/
	u32 probe_data = 0;
	u32 r_fb = (fb_data & 0xf800) >> 11;
	u32 g_fb = (fb_data & 0x07e0) >> 5;
	u32 b_fb = fb_data & 0x001f;
	u32 r_probe, g_probe,  b_probe;

	if (fb_gdev.gdfBytesPP != 2) {
		osd_loge("%d bit/pixel mode1, not support now\n",
			fb_gdev.gdfBytesPP);
		return -1;
	}
	VSYNCOSD_WR_MPEG_REG(VPU_VOUT_PROB_CTRL, 0x14);
	VSYNCOSD_WR_MPEG_REG(VPU_VOUT_PROB_SIZE,
		(osd_hw.free_dst_data[OSD1].x_end + 1) << 16
		| (osd_hw.free_dst_data[OSD1].y_end + 1));
	VSYNCOSD_WR_MPEG_REG(VPU_VOUT_PROB_POS, 0x00640064);
	_udelay(50000);
	probe_data = VSYNCOSD_RD_MPEG_REG(VPU_VOUT_RO_PROB);
	r_probe = (probe_data & 0x3ff00000) >> 25;
	g_probe = (probe_data & 0xffc00) >> 14;
	b_probe = (probe_data & 0x3ff) >> 5;
	if (r_fb == r_probe && g_fb == g_probe && b_fb == b_probe) {
		osd_logi("=== osd%d, osd_rma_test pass. ===\n", osd_index);
		return 0;
	}
	osd_loge("=== osd%d, osd_rma_test failed. ===\n", osd_index);
	osd_loge("fb_data = 0x%x  probe_data = 0x%x\n", fb_data, probe_data);
	printf("r_fb = %x r_probe = %x\n", r_fb, r_probe);
	printf("g_fb = %x g_probe = %x\n", g_fb, g_probe);
	printf("b_fb = %x b_probe = %x\n", b_fb, b_probe);
	return -1;
}
#endif
#endif

static void osd3_update_enable(void)
{
	osd_update_enable(OSD3);
}

static void osd4_update_enable(void)
{
	osd_update_enable(OSD4);
}

static void osd_update_disp_osd_reverse(u32 index)
{
	u32 val = 0;

	switch (osd_hw.osd_reverse[index]) {
	case REVERSE_XY:
	case OSD1_REVERSE_XY:
	case OSD2_REVERSE_XY:
		val = 3;
		break;
	case REVERSE_X:
	case OSD1_REVERSE_X:
	case OSD2_REVERSE_X:
		val = 1;
		break;
	case REVERSE_Y:
	case OSD1_REVERSE_Y:
	case OSD2_REVERSE_Y:
		val = 2;
		break;
	default:
		val = REVERSE_NONE;
		break;
	}

	VSYNCOSD_WR_MPEG_REG_BITS(hw_osd_reg_array[index].osd_blk0_cfg_w0,
		val, 28, 2);
	remove_from_update_list(index, DISP_OSD_REVERSE);
}

static void osd1_update_disp_osd_reverse(void)
{
	osd_update_disp_osd_reverse(OSD1);
}

static void osd2_update_disp_osd_reverse(void)
{
	osd_update_disp_osd_reverse(OSD2);
}

static void osd3_update_disp_osd_reverse(void)
{
	osd_update_disp_osd_reverse(OSD3);
}

static void osd4_update_disp_osd_reverse(void)
{
	osd_update_disp_osd_reverse(OSD4);
}

static void osd1_update_disp_osd_rotate(void)
{
	remove_from_update_list(OSD1, DISP_OSD_ROTATE);
}

static void osd2_update_disp_osd_rotate(void)
{
	remove_from_update_list(OSD2, DISP_OSD_ROTATE);
}

static void osd3_update_disp_osd_rotate(void)
{
	/* do nothing*/

	remove_from_update_list(OSD3, DISP_OSD_ROTATE);
}

static void osd4_update_disp_osd_rotate(void)
{
	/* do nothing*/

	remove_from_update_list(OSD4, DISP_OSD_ROTATE);
}

static void osd_update_color_key(u32 index)
{
	VSYNCOSD_WR_MPEG_REG(hw_osd_reg_array[index].osd_tcolor_ag0,
		osd_hw.color_key[index]);
	remove_from_update_list(index, OSD_COLOR_KEY);
}

static void osd1_update_color_key(void)
{
	osd_update_color_key(OSD1);
}

static void osd2_update_color_key(void)
{
	osd_update_color_key(OSD2);
}

static void osd3_update_color_key(void)
{
	osd_update_color_key(OSD3);
}

static void osd4_update_color_key(void)
{
	osd_update_color_key(OSD4);
}

static void osd_update_color_key_enable(u32 index)
{
	u32  data32;

	data32 = VSYNCOSD_RD_MPEG_REG(hw_osd_reg_array[index].osd_blk0_cfg_w0);
	data32 &= ~(1 << 6);
	data32 |= (osd_hw.color_key_enable[index] << 6);
	VSYNCOSD_WR_MPEG_REG(hw_osd_reg_array[index].osd_blk0_cfg_w0, data32);
	remove_from_update_list(index, OSD_COLOR_KEY_ENABLE);
}

static void osd1_update_color_key_enable(void)
{
	osd_update_color_key_enable(OSD1);
}

static void osd2_update_color_key_enable(void)
{
	osd_update_color_key_enable(OSD2);
}

static void osd3_update_color_key_enable(void)
{
	osd_update_color_key_enable(OSD3);
}

static void osd4_update_color_key_enable(void)
{
	osd_update_color_key_enable(OSD4);
}

static void osd_update_gbl_alpha(u32 index)
{
	u32  data32;

	data32 = VSYNCOSD_RD_MPEG_REG(hw_osd_reg_array[index].osd_ctrl_stat);
	data32 &= ~(0x1ff << 12);
	data32 |= osd_hw.gbl_alpha[index] << 12;
	VSYNCOSD_WR_MPEG_REG(hw_osd_reg_array[index].osd_ctrl_stat, data32);
	remove_from_update_list(index, OSD_GBL_ALPHA);
}

static void osd1_update_gbl_alpha(void)
{
	osd_update_gbl_alpha(OSD1);
}

static void osd2_update_gbl_alpha(void)
{
	osd_update_gbl_alpha(OSD2);
}

static void osd3_update_gbl_alpha(void)
{
	osd_update_gbl_alpha(OSD3);
}

static void osd4_update_gbl_alpha(void)
{
	osd_update_gbl_alpha(OSD4);
}

#ifdef AML_C3_DISPLAY
static void osd2_update_order(void)
{
	remove_from_update_list(OSD2, OSD_CHANGE_ORDER);
}

static void osd1_update_order(void)
{
	remove_from_update_list(OSD1, OSD_CHANGE_ORDER);
}

#else
static void osd2_update_order(void)
{
	switch (osd_hw.order) {
	case  OSD_ORDER_01:
		osd_reg_clr_mask(VPP_MISC, VPP_POST_FG_OSD2 | VPP_PRE_FG_OSD2);
		break;
	case  OSD_ORDER_10:
		osd_reg_set_mask(VPP_MISC, VPP_POST_FG_OSD2 | VPP_PRE_FG_OSD2);
		break;
	default:
		break;
	}
	remove_from_update_list(OSD2, OSD_CHANGE_ORDER);
}

static void osd1_update_order(void)
{
	switch (osd_hw.order) {
	case  OSD_ORDER_01:
		osd_reg_clr_mask(VPP_MISC, VPP_POST_FG_OSD2 | VPP_PRE_FG_OSD2);
		break;
	case  OSD_ORDER_10:
		osd_reg_set_mask(VPP_MISC, VPP_POST_FG_OSD2 | VPP_PRE_FG_OSD2);
		break;
	default:
		break;
	}
	remove_from_update_list(OSD1, OSD_CHANGE_ORDER);
}
#endif

static void osd3_update_order(void)
{
	/* do nothing */

	remove_from_update_list(OSD3, OSD_CHANGE_ORDER);
}

static void osd4_update_order(void)
{
	/* do nothing */

	remove_from_update_list(OSD4, OSD_CHANGE_ORDER);
}

static void osd1_2x_scale_update_geometry(void)
{
	u32 data32;

	data32 = (osd_hw.scaledata[OSD1].x_start & 0x1fff) |
		 (osd_hw.scaledata[OSD1].x_end & 0x1fff) << 16;
	VSYNCOSD_WR_MPEG_REG(hw_osd_reg_array[0].osd_blk0_cfg_w1, data32);
	data32 = ((osd_hw.scaledata[OSD1].y_start
		   + osd_hw.pandata[OSD1].y_start) & 0x1fff)
		 | ((osd_hw.scaledata[OSD1].y_end
		     + osd_hw.pandata[OSD1].y_start) & 0x1fff) << 16;
	VSYNCOSD_WR_MPEG_REG(hw_osd_reg_array[0].osd_blk0_cfg_w2, data32);
	/* adjust display x-axis */
	if (osd_hw.scale[OSD1].h_enable) {
		data32 = (osd_hw.dispdata[OSD1].x_start & 0xfff)
			 | ((osd_hw.dispdata[OSD1].x_start
			     + (osd_hw.scaledata[OSD1].x_end
				- osd_hw.scaledata[OSD1].x_start) * 2 + 1)
			    & 0xfff) << 16;
		VSYNCOSD_WR_MPEG_REG(hw_osd_reg_array[0].osd_blk0_cfg_w3, data32);
		if (osd_hw.scan_mode == SCAN_MODE_INTERLACE) {
			data32 = ((osd_hw.dispdata[OSD1].y_start >> 1) & 0xfff)
				 | (((((osd_hw.dispdata[OSD1].y_start
					+ (osd_hw.scaledata[OSD1].y_end
					   - osd_hw.scaledata[OSD1].y_start) * 2)
				       + 1) >> 1) - 1) & 0xfff) << 16;
		} else {
			data32 = (osd_hw.dispdata[OSD1].y_start & 0xfff)
				 | (((osd_hw.dispdata[OSD1].y_start
				      + (osd_hw.scaledata[OSD1].y_end
					 - osd_hw.scaledata[OSD1].y_start) * 2))
				    & 0xfff) << 16;
		}
		VSYNCOSD_WR_MPEG_REG(hw_osd_reg_array[0].osd_blk0_cfg_w4, data32);
	}
	/* adjust display y-axis */
	if (osd_hw.scale[OSD1].v_enable) {
		data32 = (osd_hw.dispdata[OSD1].x_start & 0xfff)
			 | ((osd_hw.dispdata[OSD1].x_start
			     + (osd_hw.scaledata[OSD1].x_end
				- osd_hw.scaledata[OSD1].x_start) * 2 + 1)
			    & 0xfff) << 16;
		VSYNCOSD_WR_MPEG_REG(hw_osd_reg_array[0].osd_blk0_cfg_w3, data32);
		if (osd_hw.scan_mode == SCAN_MODE_INTERLACE) {
			data32 = ((osd_hw.dispdata[OSD1].y_start >> 1) & 0xfff)
				 | (((((osd_hw.dispdata[OSD1].y_start
					+ (osd_hw.scaledata[OSD1].y_end
					   - osd_hw.scaledata[OSD1].y_start) * 2)
				       + 1) >> 1) - 1) & 0xfff) << 16;
		} else {
			data32 = (osd_hw.dispdata[OSD1].y_start & 0xfff)
				 | (((osd_hw.dispdata[OSD1].y_start
				      + (osd_hw.scaledata[OSD1].y_end
					 - osd_hw.scaledata[OSD1].y_start) * 2))
				    & 0xfff) << 16;
		}
		VSYNCOSD_WR_MPEG_REG(hw_osd_reg_array[0].osd_blk0_cfg_w4, data32);
	}
}

static void osd1_basic_update_disp_geometry(void)
{
	u32 data32;

	if (osd_get_chip_type() >= MESON_CPU_MAJOR_ID_M8) {
		data32 = (osd_hw.dispdata[OSD1].x_start & 0xfff)
			 | (osd_hw.dispdata[OSD1].x_end & 0xfff) << 16;
		VSYNCOSD_WR_MPEG_REG(hw_osd_reg_array[0].osd_blk0_cfg_w3, data32);
		if (osd_hw.scan_mode == SCAN_MODE_INTERLACE)
			data32 = ((osd_hw.dispdata[OSD1].y_start >> 1) & 0xfff)
				 | ((((osd_hw.dispdata[OSD1].y_end + 1)
				      >> 1) - 1) & 0xfff) << 16;
		else
			data32 = (osd_hw.dispdata[OSD1].y_start & 0xfff)
				 | (osd_hw.dispdata[OSD1].y_end
				    & 0xfff) << 16;
		VSYNCOSD_WR_MPEG_REG(hw_osd_reg_array[0].osd_blk0_cfg_w4, data32);
	} else {
		if (osd_hw.free_scale_mode[OSD1] == 0) {
			if (osd_hw.free_scale_enable[OSD1] == 1) {
				data32 = (osd_hw.free_scale_data[OSD1].x_start
					  & 0xfff)
					 | (osd_hw.free_scale_data[OSD1].x_end
					    & 0xfff) << 16;
				VSYNCOSD_WR_MPEG_REG(hw_osd_reg_array[0].osd_blk0_cfg_w3,
						     data32);
				data32 = (osd_hw.free_scale_data[OSD1].y_start
					  & 0xfff)
					 | (osd_hw.free_scale_data[OSD1].y_end
					    & 0xfff) << 16;
				VSYNCOSD_WR_MPEG_REG(hw_osd_reg_array[0].osd_blk0_cfg_w4,
						     data32);
			} else {
				data32 = (osd_hw.dispdata[OSD1].x_start
					  & 0xfff)
					 | (osd_hw.dispdata[OSD1].x_end
					    & 0xfff) << 16;
				VSYNCOSD_WR_MPEG_REG(hw_osd_reg_array[0].osd_blk0_cfg_w3,
						     data32);
				if (osd_hw.scan_mode == SCAN_MODE_INTERLACE)
					data32 = ((osd_hw.dispdata[OSD1].y_start
						   >> 1) & 0xfff)
						 | ((((osd_hw.dispdata[OSD1].y_end
						       + 1) >> 1) - 1)
						    & 0xfff) << 16;
				else
					data32 = (osd_hw.dispdata[OSD1].y_start
						  & 0xfff)
						 | (osd_hw.dispdata[OSD1].y_end
						    & 0xfff) << 16;
				VSYNCOSD_WR_MPEG_REG(hw_osd_reg_array[0].osd_blk0_cfg_w4,
						     data32);
			}
		} else {
			data32 = (osd_hw.dispdata[OSD1].x_start & 0xfff)
				 | (osd_hw.dispdata[OSD1].x_end & 0xfff) << 16;
			VSYNCOSD_WR_MPEG_REG(hw_osd_reg_array[0].osd_blk0_cfg_w3, data32);
			if (osd_hw.scan_mode == SCAN_MODE_INTERLACE)
				data32 = ((osd_hw.dispdata[OSD1].y_start >> 1)
					  & 0xfff)
					 | ((((osd_hw.dispdata[OSD1].y_end + 1)
					      >> 1) - 1) & 0xfff) << 16;
			else
				data32 = (osd_hw.dispdata[OSD1].y_start & 0xfff)
					 | (osd_hw.dispdata[OSD1].y_end
					    & 0xfff) << 16;
			VSYNCOSD_WR_MPEG_REG(hw_osd_reg_array[0].osd_blk0_cfg_w4, data32);
		}
	}
	/* enable osd 2x scale */
	if (osd_hw.scale[OSD1].h_enable || osd_hw.scale[OSD1].v_enable)
		osd1_2x_scale_update_geometry();
	else if (osd_hw.free_scale_enable[OSD1]
		 && (osd_hw.free_scale_data[OSD1].x_end > 0)
		 && (osd_hw.free_scale_data[OSD1].y_end > 0)
		 && (!osd_hw.rotate[OSD1].on_off)) {
		/* enable osd free scale */
		data32 = (osd_hw.free_scale_data[OSD1].x_start & 0x1fff) |
			 (osd_hw.free_scale_data[OSD1].x_end & 0x1fff) << 16;
		VSYNCOSD_WR_MPEG_REG(hw_osd_reg_array[0].osd_blk0_cfg_w1, data32);
		data32 = ((osd_hw.free_scale_data[OSD1].y_start
			   + osd_hw.pandata[OSD1].y_start) & 0x1fff)
			 | ((osd_hw.free_scale_data[OSD1].y_end
			     + osd_hw.pandata[OSD1].y_start) & 0x1fff) << 16;
		VSYNCOSD_WR_MPEG_REG(hw_osd_reg_array[0].osd_blk0_cfg_w2, data32);
	} else if (osd_hw.free_scale_enable[OSD1]
		   && (osd_hw.free_scale_data[OSD1].x_end > 0)
		   && (osd_hw.free_scale_data[OSD1].y_end > 0)
		   && (osd_hw.rotate[OSD1].on_off
		       && osd_hw.rotate[OSD1].angle > 0)) {
		data32 = (osd_hw.rotation_pandata[OSD1].x_start & 0x1fff) |
			 (osd_hw.rotation_pandata[OSD1].x_end & 0x1fff) << 16;
		VSYNCOSD_WR_MPEG_REG(hw_osd_reg_array[0].osd_blk0_cfg_w1, data32);
		data32 = ((osd_hw.rotation_pandata[OSD1].y_start
			   + osd_hw.pandata[OSD1].y_start) & 0x1fff)
			 | ((osd_hw.rotation_pandata[OSD1].y_end
			     + osd_hw.pandata[OSD1].y_start) & 0x1fff) << 16;
		VSYNCOSD_WR_MPEG_REG(hw_osd_reg_array[0].osd_blk0_cfg_w2, data32);
#ifndef AML_OSD_HIGH_VERSION
#ifndef AML_C3_DISPLAY
		if (osd_get_chip_type() == MESON_CPU_MAJOR_ID_M8)
			VSYNCOSD_WR_MPEG_REG(VPU_PROT1_Y_START_END, data32);
#endif
#endif
	} else if (osd_hw.rotate[OSD1].on_off
		   && osd_hw.rotate[OSD1].angle > 0) {
		/* enable osd rotation */
		data32 = (osd_hw.rotation_pandata[OSD1].x_start & 0x1fff) |
			 (osd_hw.rotation_pandata[OSD1].x_end & 0x1fff) << 16;
		VSYNCOSD_WR_MPEG_REG(hw_osd_reg_array[0].osd_blk0_cfg_w1, data32);
		data32 = ((osd_hw.rotation_pandata[OSD1].y_start
			   + osd_hw.pandata[OSD1].y_start) & 0x1fff)
			 | ((osd_hw.rotation_pandata[OSD1].y_end
			     + osd_hw.pandata[OSD1].y_start) & 0x1fff) << 16;
		VSYNCOSD_WR_MPEG_REG(hw_osd_reg_array[0].osd_blk0_cfg_w2, data32);
#ifndef AML_OSD_HIGH_VERSION
#ifndef AML_C3_DISPLAY
		if (osd_get_chip_type() == MESON_CPU_MAJOR_ID_M8)
			VSYNCOSD_WR_MPEG_REG(VPU_PROT1_Y_START_END, data32);
#endif
#endif
	} else {
		/* normal mode */
		data32 = (osd_hw.pandata[OSD1].x_start & 0x1fff)
			 | (osd_hw.pandata[OSD1].x_end & 0x1fff) << 16;
		VSYNCOSD_WR_MPEG_REG(hw_osd_reg_array[0].osd_blk0_cfg_w1, data32);
		data32 = (osd_hw.pandata[OSD1].y_start & 0x1fff)
			 | (osd_hw.pandata[OSD1].y_end & 0x1fff) << 16;
		VSYNCOSD_WR_MPEG_REG(hw_osd_reg_array[0].osd_blk0_cfg_w2, data32);
	}
}

static void osd1_update_disp_geometry(void)
{
	osd1_basic_update_disp_geometry();
	remove_from_update_list(OSD1, DISP_GEOMETRY);
}

static void osd_update_disp_geometry(u32 index)
{
	u32 data32;

	data32 = (osd_hw.dispdata[index].x_start & 0xfff)
		 | (osd_hw.dispdata[index].x_end & 0xfff) << 16;
	VSYNCOSD_WR_MPEG_REG(hw_osd_reg_array[index].osd_blk0_cfg_w3, data32);
	if (osd_hw.scan_mode == SCAN_MODE_INTERLACE)
		data32 = ((osd_hw.dispdata[index].y_start >> 1) & 0xfff)
			 | ((((osd_hw.dispdata[index].y_end + 1) >> 1) - 1)
			    & 0xfff) << 16;
	else
		data32 = (osd_hw.dispdata[index].y_start & 0xfff)
			 | (osd_hw.dispdata[index].y_end & 0xfff) << 16;
	VSYNCOSD_WR_MPEG_REG(hw_osd_reg_array[index].osd_blk0_cfg_w4, data32);
	if (osd_hw.scale[index].h_enable || osd_hw.scale[index].v_enable) {
#if defined(CONFIG_FB_OSD2_CURSOR)
		data32 = (osd_hw.pandata[index].x_start & 0x1fff)
			 | (osd_hw.pandata[index].x_end & 0x1fff) << 16;
		VSYNCOSD_WR_MPEG_REG(hw_osd_reg_array[index].osd_blk0_cfg_w1, data32);
		data32 = (osd_hw.pandata[index].y_start & 0x1fff)
			 | (osd_hw.pandata[index].y_end & 0x1fff) << 16;
		VSYNCOSD_WR_MPEG_REG(hw_osd_reg_array[index].osd_blk0_cfg_w2, data32);
#else
		data32 = (osd_hw.scaledata[index].x_start & 0x1fff) |
			 (osd_hw.scaledata[index].x_end & 0x1fff) << 16;
		VSYNCOSD_WR_MPEG_REG(hw_osd_reg_array[index].osd_blk0_cfg_w1, data32);
		data32 = ((osd_hw.scaledata[index].y_start
			   + osd_hw.pandata[index].y_start) & 0x1fff)
			 | ((osd_hw.scaledata[index].y_end
			     + osd_hw.pandata[index].y_start) & 0x1fff) << 16;
		VSYNCOSD_WR_MPEG_REG(hw_osd_reg_array[index].osd_blk0_cfg_w2, data32);
#endif
	} else if (osd_hw.free_scale_enable[index] &&
			(osd_hw.free_scale_data[index].x_end > 0) &&
			(osd_hw.free_scale_data[index].y_end > 0)) {
		/* enable osd free scale */
		data32 = (osd_hw.free_scale_data[index].x_start & 0x1fff)
			 | (osd_hw.free_scale_data[index].x_end & 0x1fff) << 16;
		VSYNCOSD_WR_MPEG_REG(hw_osd_reg_array[index].osd_blk0_cfg_w1, data32);
		data32 = ((osd_hw.free_scale_data[index].y_start
			   + osd_hw.pandata[index].y_start) & 0x1fff)
			 | ((osd_hw.free_scale_data[index].y_end
			     + osd_hw.pandata[index].y_start) & 0x1fff) << 16;
		VSYNCOSD_WR_MPEG_REG(hw_osd_reg_array[index].osd_blk0_cfg_w2, data32);
	} else {
		data32 = (osd_hw.pandata[index].x_start & 0x1fff)
			 | (osd_hw.pandata[index].x_end & 0x1fff) << 16;
		VSYNCOSD_WR_MPEG_REG(hw_osd_reg_array[index].osd_blk0_cfg_w1, data32);
		data32 = (osd_hw.pandata[index].y_start & 0x1fff)
			 | (osd_hw.pandata[index].y_end & 0x1fff) << 16;
		VSYNCOSD_WR_MPEG_REG(hw_osd_reg_array[index].osd_blk0_cfg_w2, data32);
	}
	remove_from_update_list(index, DISP_GEOMETRY);
}

static void osd2_update_disp_geometry(void)
{
	osd_update_disp_geometry(OSD2);
}

#ifdef AML_S5_DISPLAY
static void wr_slice_vpost(int reg_addr, int val, int slice_idx)
{
	u32 reg_offset;
	u32 reg_addr_tmp;

	reg_offset = slice_idx == 0 ? 0 :
		slice_idx == 1 ? 0x100 :
		slice_idx == 2 ? 0x700 : 0x1900;
	reg_addr_tmp = reg_addr + reg_offset * 4;
	VSYNCOSD_WR_MPEG_REG(reg_addr_tmp, val);
};

static void wr_reg_bits_slice_vpost(int reg_addr, int val, int start, int len, int slice_idx)
{
	u32 reg_offset;
	u32 reg_addr_tmp;

	reg_offset = slice_idx == 0 ? 0 :
		slice_idx == 1 ? 0x100 :
		slice_idx == 2 ? 0x700 : 0x1900;
	reg_addr_tmp = reg_addr + reg_offset * 4;
	VSYNCOSD_WR_MPEG_REG_BITS(reg_addr_tmp, val, start, len);
};

/* hw reg info set */
void vpp_post_blend_set(u32 vpp_index,
	struct vpp_post_blend_s *vpp_blend)
{
	/* setting blend scope */

	VSYNCOSD_WR_MPEG_REG(VPP_POSTBLND_H_V_SIZE,
		vpp_blend->bld_out_w | vpp_blend->bld_out_h << 16);
	/* fix display issue for t3x revb */
	if (get_cpu_id().family_id == MESON_CPU_MAJOR_ID_T3X)
		VSYNCOSD_WR_MPEG_REG(VIU_VD3_MISC,
			vpp_blend->bld_out_h);
	VSYNCOSD_WR_MPEG_REG(VPP_POST_BLEND_BLEND_DUMMY_DATA,
		vpp_blend->bld_dummy_data);
	VSYNCOSD_WR_MPEG_REG_BITS(VPP_POST_BLEND_DUMMY_ALPHA,
		0x100 | 0x000 << 16, 0, 32);
	// blend0_dummy_alpha|blend1_dummy_alpha<<16
	VSYNCOSD_WR_MPEG_REG_BITS(VPP_POST_BLEND_DUMMY_ALPHA1,
		0x000 | 0x000 << 16, 0, 32);
	// blend2_dummy_alpha|blend3_dummy_alpha<<16

	VSYNCOSD_WR_MPEG_REG_BITS(VPP_POSTBLND_CTRL,
		vpp_blend->bld_out_en, 8, 1);
	osd_logd2("%s: vpp_postblnd_h_v_size=%x\n",
		__func__, vpp_blend->bld_out_w | vpp_blend->bld_out_h << 16);
}

void vpp1_post_blend_set(struct vpp1_post_blend_s *vpp_blend)
{
	VSYNCOSD_WR_MPEG_REG(VPP1_BLEND_H_V_SIZE,
			vpp_blend->bld_out_w | vpp_blend->bld_out_h << 16);
	VSYNCOSD_WR_MPEG_REG(VPP1_BLEND_BLEND_DUMMY_DATA,
			vpp_blend->bld_dummy_data);
	VSYNCOSD_WR_MPEG_REG_BITS(VPP1_BLEND_DUMMY_ALPHA,
				0x100 | 0x000 << 16, 0, 32);
	VSYNCOSD_WR_MPEG_REG_BITS(VPP1_BLEND_DUMMY_ALPHA1,
				0x000 | 0x000 << 16, 0, 32);
	VSYNCOSD_WR_MPEG_REG(VPP1_BLD_CTRL,
			vpp_blend->bld_out_en << 31 |
			vpp_blend->vpp1_dpath_sel << 30 |
			vpp_blend->vd3_dpath_sel << 29 |
			vpp_blend->bld_din0_alpha << 20 |
			vpp_blend->bld_din0_premult_en << 16 |
			vpp_blend->bld_din1_premult_en << 17 |
			vpp_blend->bld_src2_sel << 4 |
			vpp_blend->bld_src1_sel);

	osd_logd2("%s: vpp1_postblend_h_v_size=%x\n",
		__func__, vpp_blend->bld_out_w | vpp_blend->bld_out_h << 16);
	osd_logd2("%s: vpp1_postblend_vd1_h_start_end=%x\n",
		__func__, vpp_blend->bld_din0_h_start << 16 |
		vpp_blend->bld_din0_h_end);
	osd_logd2("%s: vpp1_postblend_vd1_v_start_end=%x\n",
		__func__, vpp_blend->bld_din0_v_start << 16 |
		vpp_blend->bld_din0_v_end);
}

void vpp_post_slice_set(u32 vpp_index,
	struct vpp0_post_s *vpp_post)
{
	u32 slice_set;

	/* 2ppc2slice overlap size */
	VSYNCOSD_WR_MPEG_REG_BITS(VPP_POSTBLND_CTRL,
		vpp_post->overlap_hsize, 0, 8);
	/* slice mode */
	VSYNCOSD_WR_MPEG_REG_BITS(VPP_OBUF_RAM_CTRL,
		vpp_post->slice_num - 1, 0, 2);

	/* default = 0, 0: 4ppc to 4slice
	 * 1: 4ppc to 2slice
	 * 2: 4ppc to 1slice
	 * 3: disable
	 */
	switch (vpp_post->slice_num) {
	case 1:
		slice_set = 2;
		break;
	case 2:
		slice_set = 1;
		break;
	case 4:
		slice_set = 0;
		break;
	default:
		slice_set = 3;
		break;
	}
	VSYNCOSD_WR_MPEG_REG_BITS(VPP_4P4S_CTRL, slice_set, 0, 2);
	VSYNCOSD_WR_MPEG_REG_BITS(VPP_4S4P_CTRL, slice_set, 0, 2);
	osd_logd2("%s: vpp_4p4s_ctrl=%x\n",
		__func__, slice_set);
}

void vpp_vd1_hwin_set(u32 vpp_index,
	struct vpp0_post_s *vpp_post)
{
	u32 vd1_win_in_hsize = 0;

	if (vpp_post->vd1_hwin.vd1_hwin_en) {
		vd1_win_in_hsize = (vpp_post->vd1_hwin.vd1_hwin_in_hsize +
			SLICE_NUM - 1) / SLICE_NUM;

		VSYNCOSD_WR_MPEG_REG(VPP_POST_VD1_WIN_CUT_CTRL,
			 vpp_post->vd1_hwin.vd1_hwin_en << 31  |
			 vd1_win_in_hsize);
		osd_logd2("%s: vpp_post_vd1_win_cut_ctrl:vd1_win_in_hsize=%d\n",
			__func__, vd1_win_in_hsize);
	} else {
		VSYNCOSD_WR_MPEG_REG(VPP_POST_VD1_WIN_CUT_CTRL, 0);
	}
}

void vpp_post_proc_set(u32 vpp_index,
	struct vpp0_post_s *vpp_post)
{
	struct vpp_post_proc_s *vpp_post_proc = NULL;
	struct vpp_post_proc_slice_s *vpp_post_proc_slice = NULL;
	struct vpp_post_proc_hwin_s *vpp_post_proc_hwin = NULL;
	u32 slice_num;
	int i;

	vpp_post_proc = &vpp_post->vpp_post_proc;
	vpp_post_proc_slice = &vpp_post_proc->vpp_post_proc_slice;
	vpp_post_proc_hwin = &vpp_post_proc->vpp_post_proc_hwin;
	slice_num = vpp_post->slice_num;

	for (i = 0; i < slice_num; i++) {
		wr_slice_vpost(VPP_OUT_H_V_SIZE,
			vpp_post_proc_slice->hsize[i] << 16 |
			vpp_post_proc_slice->vsize[i], i);
		wr_reg_bits_slice_vpost(VPP_OFIFO_SIZE,
			0x800, 0, 14, i);
		/* slice hwin deal */
		wr_reg_bits_slice_vpost(VPP_SLC_DEAL_CTRL,
			vpp_post_proc_hwin->hwin_en[i], 3, 1, i);
		wr_slice_vpost(VPP_HWIN_SIZE,
			vpp_post_proc_hwin->hwin_end[i] << 16 |
			vpp_post_proc_hwin->hwin_bgn[i], i);
		wr_reg_bits_slice_vpost(VPP_ALIGN_FIFO_SIZE,
			vpp_post_proc->align_fifo_size[i], 0, 14, i);
		/* todo: for other unit bypass handle */
		osd_logd2("%s: vpp_out_h_v_size=%x\n",
			__func__, vpp_post_proc_slice->hsize[i] << 16 |
		vpp_post_proc_slice->vsize[i]);
		osd_logd2("%s: vpp_hwin_size=%x\n",
			__func__, vpp_post_proc_hwin->hwin_end[i] << 16 |
		vpp_post_proc_hwin->hwin_bgn[i]);
	}
}

void vpp1_post_proc_set(struct vpp1_post_s *vpp_post)
{
	u32 vpp1_slice = 1;
	u32 align_fifo_size[POST_SLICE_NUM] = {2048, 1536, 1024, 512};

	/* slice mode */
	VSYNCOSD_WR_MPEG_REG_BITS(VPP_OBUF_RAM_CTRL, 1, 0, 2);
	if (!vpp_post->vpp1_bypass_slice1) {
		/* slice1 vpp output need set */
		VSYNCOSD_WR_MPEG_REG(VPP_SLICE1_OUT_H_V_SIZE,
				vpp_post->vpp1_post_blend.bld_out_w << 16 |
				vpp_post->vpp1_post_blend.bld_out_h);
		VSYNCOSD_WR_MPEG_REG_BITS(VPP_SLICE1_OFIFO_SIZE,
					0x800, 0, 14);
		/* slice1 hwin disable */
		VSYNCOSD_WR_MPEG_REG_BITS(VPP_SLICE1_SLC_DEAL_CTRL,
					0, 3, 1);
		VSYNCOSD_WR_MPEG_REG_BITS(VPP_SLICE1_ALIGN_FIFO_SIZE,
					align_fifo_size[vpp1_slice],
					0, 14);
	}
	vpp1_post_blend_set(&vpp_post->vpp1_post_blend);
}

void vpp_post_padding_set(u32 vpp_index,
	struct vpp0_post_s *vpp_post)
{
	if (vpp_post->vpp_post_pad.vpp_post_pad_en) {
		/* reg_pad_hsize */
		VSYNCOSD_WR_MPEG_REG(VPP_POST_PAD_HSIZE,
			(vpp_post->vpp_post_pad.vpp_post_pad_hsize)	<< 0);
		VSYNCOSD_WR_MPEG_REG(VPP_POST_PAD_CTRL,
			vpp_post->vpp_post_pad.vpp_post_pad_dummy << 0 |
			vpp_post->vpp_post_pad.vpp_post_pad_rpt_lcol << 30 |
			vpp_post->vpp_post_pad.vpp_post_pad_en << 31);
		osd_logd2("%s: vpp_post_pad_hsize=%x\n",
			__func__, vpp_post->vpp_post_pad.vpp_post_pad_hsize);
	} else {
		VSYNCOSD_WR_MPEG_REG(VPP_POST_PAD_CTRL, 0);
	}
}
#endif
#if defined(AML_T7_DISPLAY) || defined(AML_S5_DISPLAY)
static void osd3_update_disp_geometry(void)
{
	osd_update_disp_geometry(OSD3);
}

static void osd4_update_disp_geometry(void)
{
	osd_update_disp_geometry(OSD4);
}
#else
static void osd3_update_disp_geometry(void)
{
	u32 data32;

	data32 = (osd_hw.dispdata[OSD3].x_start & 0xfff)
		 | (osd_hw.dispdata[OSD3].x_end & 0xfff) << 16;
	VSYNCOSD_WR_MPEG_REG(hw_osd_reg_array[2].osd_blk0_cfg_w3, data32);
	if (osd_hw.scan_mode == SCAN_MODE_INTERLACE)
		data32 = ((osd_hw.dispdata[OSD3].y_start >> 1) & 0xfff)
			 | ((((osd_hw.dispdata[OSD3].y_end + 1) >> 1) - 1)
			    & 0xfff) << 16;
	else
		data32 = (osd_hw.dispdata[OSD3].y_start & 0xfff)
			 | (osd_hw.dispdata[OSD3].y_end & 0xfff) << 16;
	VSYNCOSD_WR_MPEG_REG(hw_osd_reg_array[2].osd_blk0_cfg_w4, data32);

	data32 = (osd_hw.pandata[OSD3].x_start & 0x1fff)
		 | (osd_hw.pandata[OSD3].x_end & 0x1fff) << 16;
	VSYNCOSD_WR_MPEG_REG(hw_osd_reg_array[2].osd_blk0_cfg_w1, data32);
	data32 = (osd_hw.pandata[OSD3].y_start & 0x1fff)
		 | (osd_hw.pandata[OSD3].y_end & 0x1fff) << 16;
	VSYNCOSD_WR_MPEG_REG(hw_osd_reg_array[2].osd_blk0_cfg_w2, data32);

	remove_from_update_list(OSD3, DISP_GEOMETRY);
}

static void osd4_update_disp_geometry(void)
{
	remove_from_update_list(OSD4, DISP_GEOMETRY);
}
#endif

static void osd_update_disp_3d_mode(u32 index)
{
	/*step 1 . set pan data */
	u32  data32;

	if (osd_hw.mode_3d[index].left_right == OSD_LEFT) {
		data32 = (osd_hw.mode_3d[index].l_start & 0x1fff)
			 | (osd_hw.mode_3d[index].l_end & 0x1fff) << 16;
		VSYNCOSD_WR_MPEG_REG(hw_osd_reg_array[index].osd_blk0_cfg_w1, data32);
	} else {
		data32 = (osd_hw.mode_3d[index].r_start & 0x1fff)
			 | (osd_hw.mode_3d[index].r_end & 0x1fff) << 16;
		VSYNCOSD_WR_MPEG_REG(hw_osd_reg_array[index].osd_blk0_cfg_w1, data32);
	}
	osd_hw.mode_3d[index].left_right ^= 1;
}

static void osd1_update_disp_3d_mode(void)
{
	osd_update_disp_3d_mode(OSD1);
}

static void osd2_update_disp_3d_mode(void)
{
	osd_update_disp_3d_mode(OSD2);
}

static void osd3_update_disp_3d_mode(void)
{
	osd_update_disp_3d_mode(OSD3);
}

static void osd4_update_disp_3d_mode(void)
{
	osd_update_disp_3d_mode(OSD4);
}

void osd_hist_enable(u32 osd_index)
{
#ifndef AML_C3_DISPLAY
	if (osd_hw.osd_ver == OSD_HIGH_ONE) {
#ifndef AML_S5_DISPLAY
		VSYNCOSD_WR_MPEG_REG(VI_HIST_CTRL, 0x1801);
#else
		VSYNCOSD_WR_MPEG_REG(VI_HIST_CTRL, 0x3001);
#endif
	} else {
		if (OSD1 == osd_index) {
			VSYNCOSD_WR_MPEG_REG(VI_HIST_CTRL, 0x1801);
		} else if (OSD2 == osd_index) {
			VSYNCOSD_WR_MPEG_REG(VI_HIST_CTRL, 0x2001);
		} else {
			osd_loge("osd%d is not supported.\n", osd_index);
		}
	}
	osd_logd("VI_HIST_CTRL = %x\n", VSYNCOSD_RD_MPEG_REG(VI_HIST_CTRL));
#endif
}

int osd_get_hist_stat(u32 *hist_result)
{
#ifndef AML_C3_DISPLAY
	hist_result[0] = VSYNCOSD_RD_MPEG_REG(VI_HIST_MAX_MIN);
	hist_result[1] = VSYNCOSD_RD_MPEG_REG(VI_HIST_SPL_VAL);
	hist_result[2] = VSYNCOSD_RD_MPEG_REG(VI_HIST_SPL_PIX_CNT);
	hist_result[3] = VSYNCOSD_RD_MPEG_REG(VI_HIST_CHROMA_SUM);

	osd_logd("osd hist stat result:0x%x, 0x%x, 0x%x, 0x%x\n",
		hist_result[0], hist_result[1],
		hist_result[2], hist_result[3]);
#endif
	return 0;
}

void osd_set_dimm(u32 index, u32 dim_color, u32 en)
{
	u32 dimm_rgb = 0;

	dimm_rgb =
		((dim_color & 0xff000000)
		>> 24) << 22;
	dimm_rgb |=
		((dim_color & 0xff0000)
		>> 16) << 12;
	dimm_rgb |=
		((dim_color & 0xff00)
		>> 8) << 2;
	VSYNCOSD_WR_MPEG_REG(VIU_OSD2_DIMM_CTRL,
		((en ? 1 : 0) << 30) | dimm_rgb);
	VSYNCOSD_WR_MPEG_REG_BITS
		(hw_osd_reg_array[index].osd_ctrl_stat2, en ? 0x1 : 0, 14, 1);
	VSYNCOSD_WR_MPEG_REG_BITS
		(hw_osd_reg_array[index].osd_ctrl_stat2,
		dim_color & 0xff, 6, 8);
}

#ifdef VEHICLE_CONFIG
/*  UBOOT_INFO_FLAG bit definition
 *  |          31         |         30       |  29 ~ 16 |    15    |    14    |  13 ~ 0  |
 *  | uboot config finish | screen interlace | screen H | reserved | reserved | screen W |
 *
 * bit31: 0 - uboot config is finished
 *        1 - uboot config is not finished
 */
void transfer_info_to_rtos(void)
{
	struct vinfo_s *info = NULL;
	int screen_w, screen_h, interlace;
	u32 val;

#if defined CONFIG_AML_VOUT
	info = vout_get_current_vinfo();
#endif
	screen_w = info->width;
	screen_h = info->height;
	interlace = info->field_height == screen_h ? 0 : 1;

	val = (0 << 31) | (interlace << 30) | (screen_h << 16) | screen_w;
	VSYNCOSD_WR_MPEG_REG(UBOOT_INFO_FLAG, val);
}

bool is_osd2_configed(void)
{
	bool ret = false;

	if (VSYNCOSD_RD_MPEG_REG(hw_osd_reg_array[1].osd_ctrl_stat) & 0x1)
		ret = true;
	printf("%s ret=%d\n", __func__, ret);
	return ret;
}

static void osd2_config_blend(void)
{
	u32 data;
	u32 din_reoder_sel = 0, blend_din_en = 0;

	data = osd_reg_read(VIU_OSD_BLEND_CTRL);
	din_reoder_sel = data & 0xffff;
	blend_din_en = data & 0xf00000;
	din_reoder_sel &= ~0xf000;
#ifdef AML_S5_DISPLAY
	din_reoder_sel |= 3 << 12;
#else
	din_reoder_sel |= 2 << 12;
#endif
	blend_din_en &= ~0x400000;
	blend_din_en |= 1 << 23;
	data &= ~0xf0ffff;
	data |= din_reoder_sel | blend_din_en;

	osd_reg_write(VIU_OSD_BLEND_CTRL, data);

	osd_reg_write(VIU_OSD_BLEND_DIN1_SCOPE_H,
		osd_hw.free_dst_data[OSD1].x_end << 16 |
		osd_hw.free_dst_data[OSD1].x_start);
	osd_reg_write(VIU_OSD_BLEND_DIN1_SCOPE_V,
		(osd_hw.free_dst_data[OSD1].y_end) << 16 |
		(osd_hw.free_dst_data[OSD1].y_start));
}

void osd2_config_with_dimm(int *axis)
{
	osd2_layer_init();
	osd_set_free_scale_mode_hw(OSD2, 1);
	osd_set_free_scale_axis_hw(OSD2, 0, 0, fb_gdev.fb_width - 1,
				   fb_gdev.fb_height - 1);
	osd_set_window_axis_hw(OSD2, axis[0], axis[1], axis[0] + axis[2] - 1,
			       axis[1] + axis[3] - 1);
	osd_set_free_scale_enable_hw(OSD2, 0x10001);
	osd_enable_hw(OSD2, 1);
	osd_set_dimm(OSD2, 0x0000, 1);
	osd2_config_blend();
}
#endif

#if defined(AML_T7_DISPLAY) || defined(AML_S5_DISPLAY)
void osd_init_hw_viux(u32 index)
{
	u32 group, idx;
	char *osd_reverse;
	char *s = NULL;
	/* 1:vd1  2:osd1 else :close */
	u32 bld_src2_sel = 2;
	u32 osd_premult = 0;
	u32 blend_en = 1;
	u32 data32;
	u32 holdline = 8;

	/* init osd fifo control register
	 * set DDR request priority to be urgent
	 */
	if (!is_vppx(index))
		return;
	data32 = 1;

	/* hold_fifo_lines */
	if (is_vpp1(index))
		s = env_get("viu2_hold_line");
	else if (is_vpp2(index))
		s = env_get("viu3_hold_line");
	if (s) {
		holdline = simple_strtoul(s, NULL, 10);
		data32 |= holdline << 5;  /* hold_fifo_lines */
	} else {
		if (osd_hw.osd_ver == OSD_HIGH_ONE)
			data32 |= 8 << 5;  /* hold_fifo_lines */
		else
			data32 |= 4 << 5;
	}
	/* burst_len_sel: 3=64 */
	if (osd_hw.osd_ver == OSD_HIGH_ONE) {
		data32 |= 1 << 10;
		data32 |= 1 << 31;
	} else {
		data32 |= 3  << 10;
	}

	/*
	 * bit 23:22, fifo_ctrl
	 * 00 : for 1 word in 1 burst
	 * 01 : for 2 words in 1 burst
	 * 10 : for 4 words in 1 burst
	 * 11 : reserved
	 */
	data32 |= 2 << 22;
	/* bit 28:24, fifo_lim */
	data32 |= 2 << 24;

	/* fifo_depth_val: 32*8=256 */
	data32 |= 64 << 12;
	osd_reg_write(hw_osd_reg_array[index].osd_fifo_ctrl_stat, data32);

	/* just disable osd to avoid booting hang up */
	data32 = 0x0 << 0;
	data32 |= OSD_GLOBAL_ALPHA_DEF << 12;
	osd_reg_write(hw_osd_reg_array[index].osd_ctrl_stat, data32);

	/* set replaced_alpha */
	data32 = 0x1 << 14;
	data32 |= 0xff << 6;
	osd_reg_write(hw_osd_reg_array[index].osd_ctrl_stat2, data32);

	if (osd_get_chip_type() == MESON_CPU_MAJOR_ID_T3 ||
		osd_get_chip_type() == MESON_CPU_MAJOR_ID_T5M)
		osd_hw.path_ctrl_independ = 1;

	if (is_vpp1(index)) {
		/* OSD3 -> VPP1 */
		if (osd_hw.path_ctrl_independ) {
			independ_path_default_regs();
			/* osd byp osd_blend */
			osd_reg_set_bits(VIU_OSD3_PATH_CTRL, 0x1, 4, 1);
		} else {
			fix_vpu_clk2_default_regs();
			/* osd byp osd_blend */
			osd_reg_set_bits(VPP_OSD3_SCALE_CTRL, 0x7, 0, 3);
		}

#ifdef AML_T7_DISPLAY
		/* vpp_top input mux */
		osd_reg_set_bits(OSD_PATH_MISC_CTRL, OSD3 + VPP_OSD1,
				 OSD3 * 4 + 16, 4);

		/* to vpp_top1 */
		osd_reg_set_bits(PATH_START_SEL, VPU_VPP1, 24, 2);
#endif
#ifdef AML_S5_DISPLAY
		/* use vpp1 vsync */
		osd_reg_set_bits(VIU_OSD3_MISC, 1, 0, 1);
		/* 1mux3,  OSD3 -> din5 */
		osd_reg_set_bits(OSD_PROC_1MUX3_SEL, 0, 4, 2);
		/* 5mux4, select din5 */
		osd_reg_set_bits(OSD_SYS_5MUX4_SEL, 5, 8, 4);
		/* 0:select postblend 1:select vpp1 blend */
		osd_reg_set_bits(VPP1_BLD_CTRL, 1, 29, 1);
		/* 1:output to vpp slice1 0:output to venc1 directly */
		osd_reg_set_bits(VPP1_BLD_CTRL, 0, 30, 1);
#endif
		/* vpp1 osd order, premult, blend_en */
		osd_reg_set_bits(VPP1_BLD_CTRL, bld_src2_sel, 4, 4);
		osd_reg_set_bits(VPP1_BLD_CTRL, osd_premult, 17, 1);
		osd_reg_set_bits(VPP1_BLD_CTRL, blend_en, 31, 1);
	}

	if (is_vpp2(index)) {
		/* OSD4 -> VPP2 */
		if (osd_hw.path_ctrl_independ) {
			independ_path_default_regs();
			/* osd byp osd_blend */
			osd_reg_set_bits(VIU_OSD4_PATH_CTRL, 0x1, 4, 1);
		} else {
			fix_vpu_clk2_default_regs();
			/* osd byp osd_blend */
			osd_reg_set_bits(VPP_OSD4_SCALE_CTRL, 0x7, 0, 3);
		}

		/* vpp1 osd order, premult, blend_en */
		osd_reg_set_bits(VPP2_BLD_CTRL, bld_src2_sel, 4, 4);
		osd_reg_set_bits(VPP2_BLD_CTRL, osd_premult, 17, 1);
		osd_reg_set_bits(VPP2_BLD_CTRL, blend_en, 31, 1);

		/* vpp_top input mux */
		osd_reg_set_bits(OSD_PATH_MISC_CTRL, OSD4 + VPP_OSD1,
				 OSD4 * 4 + 16, 4);

		/* to vpp_top2 */
		osd_reg_set_bits(PATH_START_SEL, VPU_VPP2, 28, 2);
	}

	/* init param */
	osd_reverse = env_get("osd_reverse");
	for (group = 0; group < HW_OSD_COUNT; group++)
		for (idx = 0; idx < HW_REG_INDEX_MAX; idx++)
			osd_hw.reg[group][idx].update_func =
				hw_func_array[group][idx];

	osd_hw.updated[index] = 0;
	osd_hw.enable[index] = DISABLE;

	osd_hw.fb_gem[index].canvas_idx = OSD4_CANVAS_INDEX;
	osd_hw.gbl_alpha[index] = OSD_GLOBAL_ALPHA_DEF;
	osd_hw.color_info[index] = NULL;
	osd_hw.color_key[index] = 0xffffffff;
	osd_hw.scale[index].h_enable = 0;
	osd_hw.scale[index].v_enable = 0;
	osd_hw.mode_3d[index].enable = 0;

	if (osd_reverse) {
		if (!strcmp(osd_reverse, "all,true"))
			osd_hw.osd_reverse[index] = REVERSE_XY;
		else if (!strcmp(osd_reverse, "osd0,true") &&
				index == OSD1)
			osd_hw.osd_reverse[index] = OSD1_REVERSE_XY;
		else if (!strcmp(osd_reverse, "osd1,true") &&
				index == OSD2)
			osd_hw.osd_reverse[index] = OSD2_REVERSE_XY;
		else if (!strcmp(osd_reverse, "all,x_rev"))
			osd_hw.osd_reverse[index] = REVERSE_X;
		else if (!strcmp(osd_reverse, "osd0,x_rev") &&
				index == OSD1)
			osd_hw.osd_reverse[index] = OSD1_REVERSE_X;
		else if (!strcmp(osd_reverse, "osd1,x_rev") &&
				index == OSD2)
			osd_hw.osd_reverse[index] = OSD2_REVERSE_X;
		else if (!strcmp(osd_reverse, "all,y_rev"))
			osd_hw.osd_reverse[index] = REVERSE_Y;
		else if (!strcmp(osd_reverse, "osd0,y_rev") &&
				index == OSD1)
			osd_hw.osd_reverse[index] = OSD1_REVERSE_Y;
		else if (!strcmp(osd_reverse, "osd1,y_rev") &&
				index == OSD2)
			osd_hw.osd_reverse[index] = OSD2_REVERSE_Y;
		else
			osd_hw.osd_reverse[index] = REVERSE_NONE;
	}

	osd_hw.rotation_pandata[index].x_start = 0;
	osd_hw.rotation_pandata[index].y_start = 0;

	if (osd_get_chip_type() == MESON_CPU_MAJOR_ID_T7 ||
	    osd_get_chip_type() == MESON_CPU_MAJOR_ID_T3 ||
	    osd_get_chip_type() == MESON_CPU_MAJOR_ID_S5 ||
	    osd_get_chip_type() == MESON_CPU_MAJOR_ID_T5M ||
	    osd_get_chip_type() == MESON_CPU_MAJOR_ID_T3X)
		osd_hw.mif_linear = 1;
}
#else
void osd_init_hw_viux(u32 index)
{
	u32 group, idx, data32, holdline = 4;
	char *osd_reverse;
	char *s;

	if (!is_vpp1(index))
		return;

	osd_reverse = env_get("osd_reverse");
	s = env_get("viu2_hold_line");
	if (s)
		holdline = simple_strtoul(s, NULL, 10);
	for (group = 0; group < HW_OSD_COUNT; group++)
		for (idx = 0; idx < HW_REG_INDEX_MAX; idx++)
			osd_hw.reg[group][idx].update_func =
				hw_func_array[group][idx];

	osd_hw.updated[index] = 0;
#ifndef AML_C3_DISPLAY
	osd_reg_write(VPP2_OFIFO_SIZE, 0x7ff00800);
#endif
	/* init osd fifo control register */
	/* set DDR request priority to be urgent */
	data32 = 1;
	/* hold_fifo_lines */
	data32 |= holdline << 5;  /* hold_fifo_lines */
	/* burst_len_sel: 3=64 */
	data32 |= 1 << 10;
	data32 |= 1 << 31;

	/*
	 * bit 23:22, fifo_ctrl
	 * 00 : for 1 word in 1 burst
	 * 01 : for 2 words in 1 burst
	 * 10 : for 4 words in 1 burst
	 * 11 : reserved
	 */
	data32 |= 2 << 22;
	/* bit 28:24, fifo_lim */
	data32 |= 2 << 24;
	/* fifo_depth_val: 32 or 64 *8 = 256 or 512 */
	data32 |= 64 << 12;

	osd_reg_write(hw_osd_reg_array[index].osd_fifo_ctrl_stat, data32);

	/* disable  osd */
	data32 = 0x0 << 0;
	data32 |= OSD_GLOBAL_ALPHA_DEF << 12;
	data32 |= 0x80000000;
	osd_reg_write(hw_osd_reg_array[index].osd_ctrl_stat, data32);

	/* set replaced_alpha */
	data32 = 0x1 << 14;
	data32 |= 0xff << 6;
	osd_reg_write(hw_osd_reg_array[index].osd_ctrl_stat2, data32);
	osd_hw.enable[index] = DISABLE;

	osd_hw.fb_gem[index].canvas_idx = OSD4_CANVAS_INDEX;
	osd_hw.gbl_alpha[index] = OSD_GLOBAL_ALPHA_DEF;
	osd_hw.color_info[index] = NULL;
	osd_hw.color_key[index] = 0xffffffff;
	osd_hw.scale[index].h_enable = 0;
	osd_hw.scale[index].v_enable = 0;
	osd_hw.mode_3d[index].enable = 0;

	if (osd_reverse) {
		if (!strcmp(osd_reverse, "all,true"))
			osd_hw.osd_reverse[index] = REVERSE_XY;
		else if (!strcmp(osd_reverse, "osd0,true") &&
				index == OSD1)
			osd_hw.osd_reverse[index] = OSD1_REVERSE_XY;
		else if (!strcmp(osd_reverse, "osd1,true") &&
				index == OSD2)
			osd_hw.osd_reverse[index] = OSD2_REVERSE_XY;
		else if (!strcmp(osd_reverse, "all,x_rev"))
			osd_hw.osd_reverse[index] = REVERSE_X;
		else if (!strcmp(osd_reverse, "osd0,x_rev") &&
				index == OSD1)
			osd_hw.osd_reverse[index] = OSD1_REVERSE_X;
		else if (!strcmp(osd_reverse, "osd1,x_rev") &&
				index == OSD2)
			osd_hw.osd_reverse[index] = OSD2_REVERSE_X;
		else if (!strcmp(osd_reverse, "all,y_rev"))
			osd_hw.osd_reverse[index] = REVERSE_Y;
		else if (!strcmp(osd_reverse, "osd0,y_rev") &&
				index == OSD1)
			osd_hw.osd_reverse[index] = OSD1_REVERSE_Y;
		else if (!strcmp(osd_reverse, "osd1,y_rev") &&
				index == OSD2)
			osd_hw.osd_reverse[index] = OSD2_REVERSE_Y;
		else
			osd_hw.osd_reverse[index] = REVERSE_NONE;
	}

	osd_hw.rotation_pandata[index].x_start = 0;
	osd_hw.rotation_pandata[index].y_start = 0;
}
#endif

#ifndef AML_C3_DISPLAY
static void set_vpp_super_position(void)
{
#define PREBLD_SR0_VD1_SCALER		(1 << 1)
#define DNLP_SR1_CM			        (1 << 3)

#ifndef AML_S5_DISPLAY
	if ((osd_get_chip_type() == MESON_CPU_MAJOR_ID_G12A) ||
		(osd_get_chip_type() == MESON_CPU_MAJOR_ID_G12B) ||
		 (osd_get_chip_type() == MESON_CPU_MAJOR_ID_SM1))
		osd_reg_set_mask(VPP_MISC, PREBLD_SR0_VD1_SCALER);
	else if ((osd_get_chip_type() == MESON_CPU_MAJOR_ID_TL1) ||
		(osd_get_chip_type() >= MESON_CPU_MAJOR_ID_TM2))
		osd_reg_set_mask(VPP_MISC, DNLP_SR1_CM);
#endif
}
#endif

static void fix_vpu_clk2_default_regs(void)
{
	static int init_done;

	if (init_done) {
		osd_logd("%s, has been initialized, skip.\n", __func__);
		return;
	}
	init_done = 1;
#if defined(AML_S5_DISPLAY)
	/* default: osd byp dolby */
#ifdef CONFIG_AML_DOLBY
		if (dolby_vision_on)
			osd_reg_set_bits(OSD_DOLBY_BYPASS_EN, 0x0, 0, 1);
		else
#endif
			osd_reg_set_bits(OSD_DOLBY_BYPASS_EN, 0x1, 0, 1);
	osd_reg_set_bits(OSD_DOLBY_BYPASS_EN, 0x1, 2, 1);
	osd_reg_set_bits(OSD_DOLBY_BYPASS_EN, 0x1, 4, 1);
	osd_reg_set_bits(OSD_DOLBY_BYPASS_EN, 0x1, 6, 1);

	/* default: osd 12bit path */
	osd_reg_set_bits(VIU_OSD1_MISC, 1, 17, 1);
	osd_reg_set_bits(VIU_OSD2_MISC, 1, 17, 1);
	osd_reg_set_bits(VIU_OSD3_MISC, 1, 17, 1);
	osd_reg_set_bits(VIU_OSD4_MISC, 1, 17, 1);
	osd_reg_set_bits(OSD_DOLBY_BYPASS_EN, 0x0, 1, 1);
	osd_reg_set_bits(OSD_DOLBY_BYPASS_EN, 0x0, 3, 1);
	osd_reg_set_bits(OSD_DOLBY_BYPASS_EN, 0x0, 5, 1);
	osd_reg_set_bits(OSD_DOLBY_BYPASS_EN, 0x0, 7, 1);

	/* 2mux1, 0:use mali/mif 1:video */
	osd_reg_set_bits(VPP_INTF_OSD3_CTRL, 0, 1, 1);

	/* 1mux3,  OSD1/3 -> osd_blend */
	osd_reg_write(OSD_PROC_1MUX3_SEL, 2 << 0 | 2 << 4);

	/* disable PI */
	osd_reg_set_bits(OSD_PI_BYPASS_EN, 1, 0, 1);
	/* select din1 */
	osd_reg_set_bits(OSD_SYS_5MUX4_SEL, 1, 0, 20);
#elif defined(AML_T7_DISPLAY)
	if (osd_get_chip_type() == MESON_CPU_MAJOR_ID_T7) {
		 /* default: osd byp osd_blend */
		osd_reg_set_bits(VPP_OSD1_SCALE_CTRL, 0x2, 0, 3);
		osd_reg_set_bits(VPP_OSD2_SCALE_CTRL, 0x3, 0, 3);
		osd_reg_set_bits(VPP_OSD3_SCALE_CTRL, 0x3, 0, 3);
		osd_reg_set_bits(VPP_OSD4_SCALE_CTRL, 0x3, 0, 3);

		/* default: osd byp dolby */
		osd_reg_set_bits(VPP_VD1_DSC_CTRL, 0x1, 4, 1);
		osd_reg_set_bits(VPP_VD2_DSC_CTRL, 0x1, 4, 1);
		osd_reg_set_bits(VPP_VD3_DSC_CTRL, 0x1, 4, 1);
#ifdef CONFIG_AML_DOLBY
		if (dolby_vision_on)
			osd_reg_set_bits(MALI_AFBCD_TOP_CTRL, 0x0, 14, 1);
		else
#endif
			osd_reg_set_bits(MALI_AFBCD_TOP_CTRL, 0x1, 14, 1);
		osd_reg_set_bits(MALI_AFBCD_TOP_CTRL, 0x1, 19, 1);
		osd_reg_set_bits(MALI_AFBCD1_TOP_CTRL, 0x1, 19, 1);
		osd_reg_set_bits(MALI_AFBCD1_TOP_CTRL, 0x1, 19, 1);

		/* default: osd 12bit path */
		osd_reg_set_bits(VPP_VD1_DSC_CTRL, 0x0, 5, 1);
		osd_reg_set_bits(VPP_VD2_DSC_CTRL, 0x0, 5, 1);
		osd_reg_set_bits(VPP_VD3_DSC_CTRL, 0x0, 5, 1);
		osd_reg_set_bits(MALI_AFBCD_TOP_CTRL, 0x0, 15, 1);
		osd_reg_set_bits(MALI_AFBCD_TOP_CTRL, 0x0, 20, 1);
		osd_reg_set_bits(MALI_AFBCD1_TOP_CTRL, 0x0, 20, 1);
		osd_reg_set_bits(MALI_AFBCD1_TOP_CTRL, 0x0, 20, 1);

		/* clean vpp_top 1/2 blend default order */
		osd_reg_set_bits(VPP1_BLD_CTRL, 0x0, 0, 8);
		osd_reg_set_bits(VPP2_BLD_CTRL, 0x0, 0, 8);

		/* set vpp_top 1/2 default blend dummy */
		osd_reg_write(VPP1_BLEND_BLEND_DUMMY_DATA, 0x008080);
		osd_reg_write(VPP1_BLEND_DUMMY_ALPHA, 0xffffffff);
		osd_reg_write(VPP2_BLEND_BLEND_DUMMY_DATA, 0x008080);
		osd_reg_write(VPP2_BLEND_DUMMY_ALPHA, 0xffffffff);

	}
#endif
}

static void independ_path_default_regs(void)
{
#ifndef AML_C3_DISPLAY
	static int init_done;

	if (init_done) {
		osd_logd("%s, has been initialized, skip.\n", __func__);
		return;
	}
	init_done = 1;
	/* default: osd1_bld_din_sel -- do not osd_data_byp osd_blend */
	osd_reg_set_bits(VIU_OSD1_PATH_CTRL, 0x0, 4, 1);
	osd_reg_set_bits(VIU_OSD2_PATH_CTRL, 0x0, 4, 1);
	osd_reg_set_bits(VIU_OSD3_PATH_CTRL, 0x0, 4, 1);

	/* default: osd1_sc_path_sel -- before osd_blend or after hdr */
	osd_reg_set_bits(VIU_OSD1_PATH_CTRL, 0x0, 0, 1);
	osd_reg_set_bits(VIU_OSD2_PATH_CTRL, 0x1, 0, 1);
	osd_reg_set_bits(VIU_OSD3_PATH_CTRL, 0x1, 0, 1);

	/* default: osd byp dolby */
	osd_reg_set_bits(VIU_VD1_PATH_CTRL, 0x1, 16, 1);
	osd_reg_set_bits(VIU_VD2_PATH_CTRL, 0x1, 16, 1);
	osd_reg_set_bits(VIU_OSD1_PATH_CTRL, 0x1, 16, 1);
	osd_reg_set_bits(VIU_OSD2_PATH_CTRL, 0x1, 16, 1);
	osd_reg_set_bits(VIU_OSD3_PATH_CTRL, 0x1, 16, 1);

	/* default: osd 12bit path */
	osd_reg_set_bits(VIU_VD1_PATH_CTRL, 0x0, 17, 1);
	osd_reg_set_bits(VIU_VD2_PATH_CTRL, 0x0, 17, 1);
	osd_reg_set_bits(VIU_OSD1_PATH_CTRL, 0x0, 17, 1);
	osd_reg_set_bits(VIU_OSD2_PATH_CTRL, 0x0, 17, 1);
	osd_reg_set_bits(VIU_OSD3_PATH_CTRL, 0x0, 17, 1);

	/* clean vpp_top 1/2 blend default order */
	osd_reg_set_bits(VPP1_BLD_CTRL, 0x0, 0, 8);
	osd_reg_set_bits(VPP2_BLD_CTRL, 0x0, 0, 8);

	/* set vpp_top 1/2 default blend dummy */
	osd_reg_write(VPP1_BLEND_BLEND_DUMMY_DATA, 0x008080);
	osd_reg_write(VPP1_BLEND_DUMMY_ALPHA, 0xffffffff);
	osd_reg_write(VPP2_BLEND_BLEND_DUMMY_DATA, 0x008080);
	osd_reg_write(VPP2_BLEND_DUMMY_ALPHA, 0xffffffff);
#endif
}

static void switch_osd_to_dmcx(u32 dmc_num)
{
#ifndef AML_C3_DISPLAY
	static int init;
	u32 val = 0;

	if (init)
		return;

	init = 1;

	osd_logd("%s, dmc%d\n", __func__, dmc_num);
	if (dmc_num == 1) {
		/* OSD1->vpp_arb1 */
		val |= 1 << 20;
		/* OSD2->vpp_arb1 */
		val |= 1 << 21;
		/* OSD3->vpp_arb1 */
		val |= 1 << 24;
		/* OSD4->vpp_arb1 */
		val |= 1 << 25;
		/* mali afbcd->vpp_arb1 */
		val |= 1 << 27;
		osd_reg_write(VPP_RDARB_MODE, val);

		/* vpp_arb1->vpu arb read2 */
		osd_reg_set_bits(VPU_RDARB_MODE_L2C1, 0, 16, 1);
		osd_reg_set_bits(VPU_RDARB_MODE_L2C1, 1, 17, 1);
	} else {
		osd_reg_write(VPP_RDARB_MODE, 0);
		osd_reg_set_bits(VPU_RDARB_MODE_L2C1, 0, 16, 1);
	}
#endif
}

void osd_init_hw(u32 index)
{
	u32 group, idx, data32, data2, holdline = 8;
	char *osd_reverse;
	char *s;

	/* T5M RevA, switch osd to dmc1
	 * T5M RevB, switch osd to dmc0
	 */
	if (get_cpu_id().family_id == MESON_CPU_MAJOR_ID_T5M) {
		if (get_cpu_id().chip_rev == MESON_CPU_CHIP_REVISION_A)
			switch_osd_to_dmcx(1);
		else
			switch_osd_to_dmcx(0);
	}

#ifdef AML_T7_DISPLAY
	if (index >= OSD3) {
		/* vpp_top input mux */
		osd_reg_set_bits(OSD_PATH_MISC_CTRL, index + VPP_OSD1,
				 index * 4 + 16, 4);
		/* to vpp_top1 */
		osd_reg_set_bits(PATH_START_SEL, VPU_VPP0, index * 4 + 16, 2);
	}
#endif

	osd_reverse = env_get("osd_reverse");
	for (group = 0; group < HW_OSD_COUNT; group++)
		for (idx = 0; idx < HW_REG_INDEX_MAX; idx++)
			osd_hw.reg[group][idx].update_func =
				hw_func_array[group][idx];
	osd_hw.updated[index] = 0;

	/* set display output resolution */
#if defined CONFIG_AML_VOUT
	struct vinfo_s *info = NULL;

	info = vout_get_current_vinfo();
	if (info != NULL)
		osd_reg_write(VPP_POSTBLEND_H_SIZE, info->width);
#endif
	osd_vpu_power_on();

#ifdef AML_C3_DISPLAY
	irq_clr_c3();
#endif
	if (osd_get_chip_type() == MESON_CPU_MAJOR_ID_T3 ||
		osd_get_chip_type() == MESON_CPU_MAJOR_ID_T5W ||
		osd_get_chip_type() == MESON_CPU_MAJOR_ID_T5M)
		osd_hw.path_ctrl_independ = 1;

#ifdef AML_S5_DISPLAY
	osd_hw.has_pi = 1;
#endif

	/* here we will init default value ,these value only set once . */
	if (!logo_loaded[index]) {
		if (osd_hw.path_ctrl_independ)
			independ_path_default_regs();
		else
			fix_vpu_clk2_default_regs();
#ifndef AML_C3_DISPLAY
		/* init vpu fifo control register */
		data32 = osd_reg_read(VPP_OFIFO_SIZE);
		osd_logi("VPP_OFIFO_SIZE:0x%x\n", data32);
		if (osd_hw.osd_ver == OSD_HIGH_ONE) {
			data32 &= ~((0xfff << 20) | 0x3fff);
			data32 |= (0xfff << 20);
			if (osd_get_chip_type() == MESON_CPU_MAJOR_ID_TXHD2)
				data32 |= (0x77f + 1);
			else
				data32 |= (0xfff + 1);
			osd_reg_write(VPP_OFIFO_SIZE, data32);
		}
#endif
		/* init osd fifo control register */
		/* set DDR request priority to be urgent */
		data32 = 1;
		if ((osd_get_chip_type() == MESON_CPU_MAJOR_ID_M6TV)
		    || (osd_get_chip_type() == MESON_CPU_MAJOR_ID_MTVD)) {
			data32 |= 18 << 5;  /* hold_fifo_lines */
		} else if (osd_hw.osd_ver == OSD_SIMPLE &&
					osd_get_chip_type() != MESON_CPU_MAJOR_ID_A4 &&
					osd_get_chip_type() != MESON_CPU_MAJOR_ID_C3) {
			data32 &= ~(0x1f << 5); /* bit[9:5] HOLD_FIFO_LINES */
			data32 |= 0x18 << 5;
		} else {
			s = env_get("viu1_hold_line");
			if (s) {
				holdline = simple_strtoul(s, NULL, 10);
				data32 |= holdline << 5;  /* hold_fifo_lines */
			} else {
				if (osd_hw.osd_ver == OSD_HIGH_ONE)
					data32 |= 8 << 5;  /* hold_fifo_lines */
				else
					data32 |= 4 << 5;  /* hold_fifo_lines */
			}
		}
		/* burst_len_sel: 3=64 */
		if (osd_hw.osd_ver == OSD_HIGH_ONE ||
			osd_get_chip_type() == MESON_CPU_MAJOR_ID_A4 ||
			osd_get_chip_type() == MESON_CPU_MAJOR_ID_C3) {
			data32 |= 1 << 10;
			data32 |= 1 << 31;
		} else
			data32 |= 3  << 10;

		if (osd_get_chip_type() >= MESON_CPU_MAJOR_ID_GXBB) {
			/*
			 * bit 23:22, fifo_ctrl
			 * 00 : for 1 word in 1 burst
			 * 01 : for 2 words in 1 burst
			 * 10 : for 4 words in 1 burst
			 * 11 : reserved
			 */
			data32 |= 2 << 22;
			/* bit 28:24, fifo_lim */
			data32 |= 2 << 24;
		}
		data2 = data32;
		/* fifo_depth_val: 32*8=256 */
		if ((osd_get_chip_type() == MESON_CPU_MAJOR_ID_TXL)
			|| (osd_get_chip_type() == MESON_CPU_MAJOR_ID_TXLX))
			data32 |= 64 << 12;
		else
			data32 |= 32 << 12;
		data2 |= 32 << 12;
		osd_reg_write(hw_osd_reg_array[index].osd_fifo_ctrl_stat,
			      data32);
#ifndef AML_C3_DISPLAY
		osd_reg_set_mask(VPP_MISC, VPP_POSTBLEND_EN);
		osd_reg_clr_mask(VPP_MISC, VPP_PREBLEND_EN);
		if (osd_hw.osd_ver <= OSD_NORMAL)
			osd_reg_clr_mask(VPP_MISC,
				VPP_OSD1_POSTBLEND |
				VPP_OSD2_POSTBLEND | VPP_VD1_POSTBLEND);
#endif
		/* just disable osd to avoid booting hang up */
		data32 = 0x0 << 0;
		if (osd_get_chip_type() != MESON_CPU_MAJOR_ID_A4 &&
			osd_get_chip_type() != MESON_CPU_MAJOR_ID_C3)
			data32 |= OSD_GLOBAL_ALPHA_DEF << 12;
		else
			data32 |= 0x100 << 12;
		osd_reg_write(hw_osd_reg_array[index].osd_ctrl_stat, data32);
		/* set replaced_alpha */
		data32 = 0x1 << 14;
		data32 |= 0xff << 6;
		osd_reg_write(hw_osd_reg_array[index].osd_ctrl_stat2, data32);
		logo_loaded[index] = 1;
	}
#ifndef AML_C3_DISPLAY
	if (osd_hw.osd_ver <= OSD_NORMAL)
		osd_reg_clr_mask(VPP_MISC, VPP_POST_FG_OSD2 | VPP_PRE_FG_OSD2);
	else if (osd_hw.osd_ver > OSD_NORMAL)
		set_vpp_super_position();

	if (osd_get_chip_type() == MESON_CPU_MAJOR_ID_S4)
		osd_reg_clr_mask(VPP_MISC, VPP_WATER_MARK_10BIT);
#else
	osd1_matrix_yuv2rgb(0);
#endif
	osd_hw.order = OSD_ORDER_01;
	osd_hw.enable[index] = DISABLE;

	osd_hw.fb_gem[OSD1].canvas_idx = OSD1_CANVAS_INDEX;
	osd_hw.fb_gem[OSD2].canvas_idx = OSD2_CANVAS_INDEX;
	osd_hw.fb_gem[OSD3].canvas_idx = OSD3_CANVAS_INDEX;
	osd_hw.fb_gem[OSD4].canvas_idx = OSD4_CANVAS_INDEX;

	osd_hw.gbl_alpha[index] = OSD_GLOBAL_ALPHA_DEF;
	osd_hw.color_info[index] = NULL;
	osd_hw.color_key[index] = 0xffffffff;
	osd_hw.free_scale_enable[index] = 0;
	osd_hw.scale[index].h_enable = 0;
	osd_hw.scale[index].v_enable = 0;
	osd_hw.mode_3d[index].enable = 0;
	osd_hw.block_mode[index] = 0;
	osd_hw.free_scale[index].h_enable = 0;
	osd_hw.free_scale[index].v_enable = 0;

	if (osd_reverse) {
		if (!strcmp(osd_reverse, "all,true"))
			osd_hw.osd_reverse[index] = REVERSE_XY;
		else if (!strcmp(osd_reverse, "osd0,true") &&
				index == OSD1)
			osd_hw.osd_reverse[index] = OSD1_REVERSE_XY;
		else if (!strcmp(osd_reverse, "osd1,true") &&
				index == OSD2)
			osd_hw.osd_reverse[index] = OSD2_REVERSE_XY;
		else if (!strcmp(osd_reverse, "all,x_rev"))
			osd_hw.osd_reverse[index] = REVERSE_X;
		else if (!strcmp(osd_reverse, "osd0,x_rev") &&
				index == OSD1)
			osd_hw.osd_reverse[index] = OSD1_REVERSE_X;
		else if (!strcmp(osd_reverse, "osd1,x_rev") &&
				index == OSD2)
			osd_hw.osd_reverse[index] = OSD2_REVERSE_X;
		else if (!strcmp(osd_reverse, "all,y_rev"))
			osd_hw.osd_reverse[index] = REVERSE_Y;
		else if (!strcmp(osd_reverse, "osd0,y_rev") &&
				index == OSD1)
			osd_hw.osd_reverse[index] = OSD1_REVERSE_Y;
		else if (!strcmp(osd_reverse, "osd1,y_rev") &&
				index == OSD2)
			osd_hw.osd_reverse[index] = OSD2_REVERSE_Y;
		else
			osd_hw.osd_reverse[index] = REVERSE_NONE;
	}

	osd_hw.rotation_pandata[index].x_start = 0;
	osd_hw.rotation_pandata[index].y_start = 0;

	osd_hw.antiflicker_mode = 0;
	if (osd_get_chip_type() >= MESON_CPU_MAJOR_ID_M8) {
		osd_hw.free_scale_data[index].x_start = 0;
		osd_hw.free_scale_data[index].x_end = 0;
		osd_hw.free_scale_data[index].y_start = 0;
		osd_hw.free_scale_data[index].y_end = 0;

		osd_hw.free_scale_mode[index] = 1;

		if ((osd_get_chip_type() == MESON_CPU_MAJOR_ID_GXM)
			||(osd_get_chip_type() == MESON_CPU_MAJOR_ID_TXLX))
			osd_reg_write(hw_osd_reg_array[0].osd_sc_dummy_data,
				0x00202000);
		else if (osd_get_chip_type() ==
			MESON_CPU_MAJOR_ID_GXTVBB)
			osd_reg_write(hw_osd_reg_array[0].osd_sc_dummy_data, 0xff);
		else
			osd_reg_write(hw_osd_reg_array[0].osd_sc_dummy_data,
				0x00808000);
	} else {
		osd_hw.free_scale_mode[index] = 0;
	}
	memset(osd_hw.rotate, 0, sizeof(struct osd_rotate_s) * HW_OSD_COUNT);
	if ((osd_get_chip_type() == MESON_CPU_MAJOR_ID_G12A) ||
		((osd_get_chip_type() == MESON_CPU_MAJOR_ID_G12B) &&
		(get_cpu_id().chip_rev == MESON_CPU_CHIP_REVISION_A)))
		osd_hw.shift_line = 1;
	else
		osd_hw.shift_line = 0;
	if (osd_get_chip_type() == MESON_CPU_MAJOR_ID_T7 ||
	    osd_get_chip_type() == MESON_CPU_MAJOR_ID_T3 ||
	    osd_get_chip_type() == MESON_CPU_MAJOR_ID_S5 ||
	    osd_get_chip_type() == MESON_CPU_MAJOR_ID_T5W ||
	    osd_get_chip_type() == MESON_CPU_MAJOR_ID_T5M ||
	    osd_get_chip_type() == MESON_CPU_MAJOR_ID_T3X ||
	    osd_get_chip_type() == MESON_CPU_MAJOR_ID_C3)
		osd_hw.mif_linear = 1;

	return;
}
