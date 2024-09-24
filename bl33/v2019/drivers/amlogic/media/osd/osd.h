/* SPDX-License-Identifier: (GPL-2.0+ OR MIT) */
/*
 * Copyright (c) 2019 Amlogic, Inc. All rights reserved.
 */

#ifndef _OSD_H_
#define _OSD_H_

#include <amlogic/color.h>

/* OSD device ioctl definition */
#define FBIOPUT_OSD_SRCKEY_ENABLE        0x46fa
#define FBIOPUT_OSD_SRCCOLORKEY          0x46fb
#define FBIOPUT_OSD_SET_GBL_ALPHA        0x4500
#define FBIOGET_OSD_GET_GBL_ALPHA        0x4501
#define FBIOPUT_OSD_2X_SCALE             0x4502
#define FBIOPUT_OSD_ENABLE_3D_MODE       0x4503
#define FBIOPUT_OSD_FREE_SCALE_ENABLE    0x4504
#define FBIOPUT_OSD_FREE_SCALE_WIDTH     0x4505
#define FBIOPUT_OSD_FREE_SCALE_HEIGHT    0x4506
#define FBIOPUT_OSD_ORDER                0x4507
#define FBIOGET_OSD_ORDER                0x4508
#define FBIOGET_OSD_SCALE_AXIS           0x4509
#define FBIOPUT_OSD_SCALE_AXIS           0x450a
#define FBIOGET_OSD_BLOCK_WINDOWS        0x450b
#define FBIOPUT_OSD_BLOCK_WINDOWS        0x450c
#define FBIOGET_OSD_BLOCK_MODE           0x450d
#define FBIOPUT_OSD_BLOCK_MODE           0x450e
#define FBIOGET_OSD_FREE_SCALE_AXIS      0x450f
#define FBIOPUT_OSD_FREE_SCALE_AXIS      0x4510
#define FBIOPUT_OSD_FREE_SCALE_MODE      0x4511
#define FBIOGET_OSD_WINDOW_AXIS          0x4512
#define FBIOPUT_OSD_WINDOW_AXIS          0x4513
#define FBIOGET_OSD_FLUSH_RATE           0x4514
#define FBIOPUT_OSD_REVERSE              0x4515
#define FBIOPUT_OSD_ROTATE_ON            0x4516
#define FBIOPUT_OSD_ROTATE_ANGLE         0x4517
#define FBIOPUT_OSD_SYNC_ADD             0x4518

/* OSD color definition */
#define KEYCOLOR_FLAG_TARGET  1
#define KEYCOLOR_FLAG_ONHOLD  2
#define KEYCOLOR_FLAG_CURRENT 4

#define HW_OSD_COUNT 4
/* OSD block definition */
#define HW_OSD_BLOCK_COUNT 4
#define HW_OSD_BLOCK_REG_COUNT (HW_OSD_BLOCK_COUNT*2)
#define HW_OSD_BLOCK_ENABLE_MASK        0x000F
#define HW_OSD_BLOCK_ENABLE_0           0x0001 /* osd blk0 enable */
#define HW_OSD_BLOCK_ENABLE_1           0x0002 /* osd blk1 enable */
#define HW_OSD_BLOCK_ENABLE_2           0x0004 /* osd blk2 enable */
#define HW_OSD_BLOCK_ENABLE_3           0x0008 /* osd blk3 enable */
#define HW_OSD_BLOCK_LAYOUT_MASK        0xFFFF0000
#define HW_OSD_BLOCK_LAYOUT_HORIZONTAL  0x00010000
#define HW_OSD_BLOCK_LAYOUT_VERTICAL    0x00020000
#define HW_OSD_BLOCK_LAYOUT_GRID        0x00030000
#define HW_OSD_BLOCK_LAYOUT_CUSTOMER    0xFFFF0000

#define OSD_LEFT 0
#define OSD_RIGHT 1
#define OSD_ORDER_01 1
#define OSD_ORDER_10 2
#define OSD_GLOBAL_ALPHA_DEF 0xff
#define OSD_DATA_BIG_ENDIAN 0
#define OSD_DATA_LITTLE_ENDIAN 1
#define OSD_TC_ALPHA_ENABLE_DEF 0  /* disable tc_alpha */

#define INT_VIU_VSYNC 35
#define INT_VIU2_VSYNC 45
extern int int_rdma;

#define OSD_MAX_BUF_NUM 3  /* fence relative */

enum osd_enable_e {
	DISABLE = 0,
	ENABLE
};

enum scan_mode_e {
	SCAN_MODE_INTERLACE,
	SCAN_MODE_PROGRESSIVE
};

struct color_bit_define_s {
	enum color_index_e color_index;
	u8 hw_colormat;
	u8 hw_blkmode;

	u8 red_offset;
	u8 red_length;
	u8 red_msb_right;

	u8 green_offset;
	u8 green_length;
	u8 green_msb_right;

	u8 blue_offset;
	u8 blue_length;
	u8 blue_msb_right;

	u8 transp_offset;
	u8 transp_length;
	u8 transp_msb_right;

	u8 color_type;
	u8 bpp;
};

struct osd_ctl_s {
	u32 xres_virtual;
	u32 yres_virtual;
	u32 xres;
	u32 yres;
	u32 disp_start_x; /* coordinate of screen */
	u32 disp_start_y;
	u32 disp_end_x;
	u32 disp_end_y;
	u32 addr;
	u32 index;
};

struct osd_info_s {
	u32 index;
	u32 osd_reverse;
};

struct para_osd_info_s {
	char *name;
	u32 info;
	u32 prev_idx;
	u32 next_idx;
	u32 cur_group_start;
	u32 cur_group_end;
};

enum osd_dev_e {
	DEV_OSD0 = 0,
	DEV_OSD1,
	DEV_ALL,
	DEV_MAX
};

enum reverse_info_e {
	REVERSE_NONE = 0,  /* no rotaion */
	REVERSE_XY,        /* x+y rotation */
	OSD1_REVERSE_XY,   /* osd1 x+y rotation */
	OSD2_REVERSE_XY,   /* osd2 x+y rotation */
	REVERSE_X,         /* x rotation */
	OSD1_REVERSE_X,    /* osd1 x rotation */
	OSD2_REVERSE_X,    /* osd2 x rotation */
	REVERSE_Y,         /* y rotaion */
	OSD1_REVERSE_Y,    /* osd1 y rotation */
	OSD2_REVERSE_Y,    /* osd2 y rotation */
	REVERSE_MAX
};

enum hw_reg_index_e {
	OSD_COLOR_MODE = 0,
	OSD_ENABLE,
	OSD_COLOR_KEY,
	OSD_COLOR_KEY_ENABLE,
	OSD_GBL_ALPHA,
	OSD_CHANGE_ORDER,
	OSD_FREESCALE_COEF,
	DISP_GEOMETRY,
	DISP_SCALE_ENABLE,
	DISP_FREESCALE_ENABLE,
	DISP_OSD_REVERSE,
	DISP_OSD_ROTATE,
	HW_REG_INDEX_MAX
};

enum osd_ver_e {
	OSD_SIMPLE = 0,
	OSD_NORMAL,
	OSD_HIGH_ONE,
	OSD_HIGH_OTHER
};

enum vpp_mux_input_type {
	VPP_DIN_NONE = 0,
	VPP_OSD1,
	VPP_OSD2,
	VPP_OSD3,
	VPP_OSD4,
};

enum vpp_vsync_type {
	VPU_VPP0,
	VPU_VPP1,
	VPU_VPP2,
	VPU_VPP_MAX
};

enum matrix_type_e {
	MATRIX_BYPASS = 0,
	YUV2RGB,
	RGB2YUV
};

struct pandata_s {
	s32 x_start;
	s32 x_end;
	s32 y_start;
	s32 y_end;
};

struct fb_geometry_s {
	u32 width;  /* in byte unit */
	u32 height;
	u32 canvas_idx;
	u32 addr;
};

struct osd_scale_s {
	u16 h_enable;
	u16 v_enable;
};

struct osd_3d_mode_s {
	struct osd_scale_s origin_scale;
	u16 enable;
	u16 left_right;
	u16 l_start;
	u16 l_end;
	u16 r_start;
	u16 r_end;
};

struct osd_rotate_s {
	u32 on_off;
	u32 angle;
};

typedef void (*update_func_t)(void);
struct hw_list_s {
	update_func_t update_func;
};

struct hw_para_s {
	struct pandata_s pandata[HW_OSD_COUNT];
	struct pandata_s dispdata[HW_OSD_COUNT];
	struct pandata_s scaledata[HW_OSD_COUNT];
	struct pandata_s free_scale_data[HW_OSD_COUNT];
	struct pandata_s free_dst_data[HW_OSD_COUNT];
	struct pandata_s rotation_pandata[HW_OSD_COUNT];
	struct pandata_s cursor_dispdata[HW_OSD_COUNT];

	u32 gbl_alpha[HW_OSD_COUNT];
	u32 color_key[HW_OSD_COUNT];
	u32 color_key_enable[HW_OSD_COUNT];
	u32 enable[HW_OSD_COUNT];
	u32 reg_status_save;
#ifdef FIQ_VSYNC
	bridge_item_t fiq_handle_item;
#endif
	struct osd_scale_s scale[HW_OSD_COUNT];
	struct osd_scale_s free_scale[HW_OSD_COUNT];
	u32 free_scale_enable[HW_OSD_COUNT];
	u32 free_scale_width[HW_OSD_COUNT];
	u32 free_scale_height[HW_OSD_COUNT];
	struct fb_geometry_s fb_gem[HW_OSD_COUNT];
	const struct color_bit_define_s *color_info[HW_OSD_COUNT];
	u32 scan_mode;
	u32 order;
	struct osd_3d_mode_s mode_3d[HW_OSD_COUNT];
	u32 updated[HW_OSD_COUNT];
	u32 block_windows[HW_OSD_COUNT][HW_OSD_BLOCK_REG_COUNT];
	u32 block_mode[HW_OSD_COUNT];
	u32 free_scale_mode[HW_OSD_COUNT];
	u32 osd_reverse[HW_OSD_COUNT];
	struct osd_rotate_s rotate[HW_OSD_COUNT];
	struct hw_list_s reg[HW_OSD_COUNT][HW_REG_INDEX_MAX];
	u32 field_out_en;
	u32 scale_workaround;
	u32 fb_for_4k2k;
	u32 antiflicker_mode;
	u32 angle[HW_OSD_COUNT];
	u32 clone[HW_OSD_COUNT];
	u32 vpp_index[HW_OSD_COUNT];
	u32 bot_type;
	u32 osd_ver;
	u32 shift_line;
	u32 mif_linear;
	u32 path_ctrl_independ;
	u32 viux_scale_cap;
	u32 has_pi;
};

struct hw_osd_reg_s {
	u32 osd_ctrl_stat; /* VIU_OSD1_CTRL_STAT */
	u32 osd_ctrl_stat2;/* VIU_OSD1_CTRL_STAT2 */
	u32 osd_color_addr;/* VIU_OSD1_COLOR_ADDR */
	u32 osd_color;/* VIU_OSD1_COLOR */
	u32 osd_tcolor_ag0; /* VIU_OSD1_TCOLOR_AG0 */
	u32 osd_tcolor_ag1; /* VIU_OSD1_TCOLOR_AG1 */
	u32 osd_tcolor_ag2; /* VIU_OSD1_TCOLOR_AG2 */
	u32 osd_tcolor_ag3; /* VIU_OSD1_TCOLOR_AG3 */
	u32 osd_blk0_cfg_w0;/* VIU_OSD1_BLK0_CFG_W0 */
	u32 osd_blk0_cfg_w1;/* VIU_OSD1_BLK0_CFG_W1 */
	u32 osd_blk0_cfg_w2;/* VIU_OSD1_BLK0_CFG_W2 */
	u32 osd_blk0_cfg_w3;/* VIU_OSD1_BLK0_CFG_W3 */
	u32 osd_blk0_cfg_w4;/* VIU_OSD1_BLK0_CFG_W4 */
	u32 osd_blk1_cfg_w4;/* VIU_OSD1_BLK1_CFG_W4 */
	u32 osd_blk2_cfg_w4;/* VIU_OSD1_BLK2_CFG_W4 */
	u32 osd_fifo_ctrl_stat;/* VIU_OSD1_FIFO_CTRL_STAT */
	//u32 osd_prot_ctrl;/* VIU_OSD1_PROT_CTRL */
	//u32 osd_mali_unpack_ctrl;/* VIU_OSD1_MALI_UNPACK_CTRL */
	//u32 osd_dimm_ctrl;/* VIU_OSD1_DIMM_CTRL */
	//u32 osd_matrix_en_ctrl;

	u32 osd_scale_coef_idx;/* VPP_OSD_SCALE_COEF_IDX */
	u32 osd_scale_coef;/* VPP_OSD_SCALE_COEF */
	u32 osd_vsc_phase_step;/* VPP_OSD_VSC_PHASE_STEP */
	u32 osd_vsc_init_phase;/* VPP_OSD_VSC_INI_PHASE */
	u32 osd_vsc_ctrl0;/* VPP_OSD_VSC_CTRL0 */
	u32 osd_hsc_phase_step;/* VPP_OSD_HSC_PHASE_STEP */
	u32 osd_hsc_init_phase;/* VPP_OSD_HSC_INI_PHASE */
	u32 osd_hsc_ctrl0;/* VPP_OSD_HSC_CTRL0 */
	u32 osd_sc_dummy_data;/* VPP_OSD_SC_DUMMY_DATA */
	u32 osd_sc_ctrl0;/* VPP_OSD_SC_CTRL0 */
	u32 osd_sci_wh_m1;/* VPP_OSD_SCI_WH_M1 */
	u32 osd_sco_h_start_end;/* VPP_OSD_SCO_H_START_END */
	u32 osd_sco_v_start_end;/* VPP_OSD_SCO_V_START_END */
	u32 osd_proc_in_size;    /* OSD1_PROC_IN_SIZE */
	u32 osd_proc_out_size;   /* OSD1_PROC_OUT_SIZE */
};

struct hw_osd_vout_blend_reg_s {
	u32 vpu_vout_irq_ctrl;
	u32 vpu_vout_blend_ctrl;
	u32 vpu_vout_blend_dumdata;
	u32 vpu_vout_blend_size;
	u32 vpu_vout_bld_src0_hpos;
	u32 vpu_vout_bld_src0_vpos;
	u32 vpu_vout_bld_src1_hpos;
	u32 vpu_vout_bld_src1_vpos;
};

struct hw_osd_vout_csc_reg_s {
	u32 vout_osd1_csc_coef00_01;
	u32 vout_osd1_csc_coef02_10;
	u32 vout_osd1_csc_coef11_12;
	u32 vout_osd1_csc_coef20_21;
	u32 vout_osd1_csc_coef22;
	u32 vout_osd1_csc_coef30_31;
	u32 vout_osd1_csc_coef32_40;
	u32 vout_osd1_csc_coef41_42;
	u32 vout_osd1_csc_clip;
	u32 vout_osd1_csc_offset0_1;
	u32 vout_osd1_csc_offset2;
	u32 vout_osd1_csc_pre_offset0_1;
	u32 vout_osd1_csc_pre_offset2;
	u32 vout_osd1_csc_en_ctrl;
};

#ifdef AML_S5_DISPLAY
/* VPP POST input src: 3VD, 2 OSD */
/* S5 only VD1, VD2 */
#define VPP_POST_VD_NUM   3
#define VPP_POST_OSD_NUM  2
#define VPP_POST_NUM (VPP_POST_VD_NUM + VPP_POST_OSD_NUM)

#define POST_SLICE_NUM    4

struct slice_info {
	u32 hsize;     /*slice hsize*/
	u32 vsize;     /*slice vsize*/
};

struct vpp_post_info_t {
	u32 slice_num;   /*valid slice num*/
	u32 overlap_hsize;
	u32 vpp_post_blend_hsize;   /*blend out hsize*/
	u32 vpp_post_blend_vsize;   /*blend out vsize*/
	struct slice_info slice[POST_SLICE_NUM];
};

struct vpp_post_blend_s {
	u32 bld_out_en;
	u32 bld_out_w;
	u32 bld_out_h;
	u32 bld_out_premult;

	u32 bld_src1_sel;	  //1:din0	2:din1 3:din2 4:din3 5:din4 else :close
	u32 bld_src2_sel;	  //1:din0	2:din1 3:din2 4:din3 5:din4 else :close
	u32 bld_src3_sel;	  //1:din0	2:din1 3:din2 4:din3 5:din4 else :close
	u32 bld_src4_sel;	  //1:din0	2:din1 3:din2 4:din3 5:din4 else :close
	u32 bld_src5_sel;	  //1:din0	2:din1 3:din2 4:din3 5:din4 else :close
	u32 bld_dummy_data;

	//usually the bottom layer set 1, for example postbld_src1_sel = 1,set 0x1
	u32 bld_din0_premult_en;
	u32 bld_din1_premult_en;
	u32 bld_din2_premult_en;
	u32 bld_din3_premult_en;
	u32 bld_din4_premult_en;

	//u32 vd1_index;//VPP_VD1/VPP_VD2/VPP_VD3
	u32 bld_din0_h_start;
	u32 bld_din0_h_end;
	u32 bld_din0_v_start;
	u32 bld_din0_v_end;
	u32 bld_din0_alpha;

	//u32 vd2_index;//VPP_VD1/VPP_VD2/VPP_VD3
	u32 bld_din1_h_start;
	u32 bld_din1_h_end;
	u32 bld_din1_v_start;
	u32 bld_din1_v_end;
	u32 bld_din1_alpha;

	//u32 vd3_index;//VPP_VD1/VPP_VD2/VPP_VD3
	u32 bld_din2_h_start;
	u32 bld_din2_h_end;
	u32 bld_din2_v_start;
	u32 bld_din2_v_end;
	u32 bld_din2_alpha;

	//u32 osd1_index;//VPP_OSD1/VPP_OSD2/VPP_OSD3/VPP_OSD4
	u32 bld_din3_h_start;
	u32 bld_din3_h_end;
	u32 bld_din3_v_start;
	u32 bld_din3_v_end;

	//u32 osd2_index;//VPP_OSD1/VPP_OSD2/VPP_OSD3/VPP_OSD4
	u32 bld_din4_h_start;
	u32 bld_din4_h_end;
	u32 bld_din4_v_start;
	u32 bld_din4_v_end;
};

struct vd1_hwin_s {
	u32 vd1_hwin_en;
	u32 vd1_hwin_in_hsize;
	/* hwin cut out before to blend */
	u32 vd1_hwin_out_hsize;
};

struct vpp_post_pad_s {
	u32 vpp_post_pad_en;
	u32 vpp_post_pad_hsize;
	u32 vpp_post_pad_dummy;
	/* 1: padding with last colum */
	/* 0: padding with vpp_post_pad_dummy val */
	u32 vpp_post_pad_rpt_lcol;
};

struct vpp_post_hwin_s {
	u32 vpp_post_hwin_en;
	u32 vpp_post_dout_hsize;
	u32 vpp_post_dout_vsize;
};

struct vpp_post_proc_slice_s {
	u32 hsize[POST_SLICE_NUM];
	u32 vsize[POST_SLICE_NUM];
};

struct vpp_post_proc_hwin_s {
	u32 hwin_en[POST_SLICE_NUM];
	u32 hwin_bgn[POST_SLICE_NUM];
	u32 hwin_end[POST_SLICE_NUM];
};

struct vpp_post_proc_s {
	struct vpp_post_proc_slice_s vpp_post_proc_slice;
	struct vpp_post_proc_hwin_s vpp_post_proc_hwin;
	u32 align_fifo_size[POST_SLICE_NUM];
	u32 gamma_bypass;
	u32 ccm_bypass;
	u32 vadj2_bypass;
	u32 lut3d_bypass;
	u32 gain_off_bypass;
	u32 vwm_bypass;
};

struct vpp_post_input_s {
	u32 slice_num;
	u32 overlap_hsize;
	u32 din_hsize[VPP_POST_NUM];
	u32 din_vsize[VPP_POST_NUM];
	u32 din_x_start[VPP_POST_NUM];
	u32 din_y_start[VPP_POST_NUM];
	u32 bld_out_hsize;
	u32 bld_out_vsize;
	/* means vd1 4s4p padding */
	u32 vd1_padding_en;
	u32 vd1_size_before_padding;
	u32 vd1_size_after_padding;
};

struct vpp0_post_s {
	u32 slice_num;
	u32 overlap_hsize;
	struct vd1_hwin_s vd1_hwin;
	struct vpp_post_blend_s vpp_post_blend;
	struct vpp_post_pad_s vpp_post_pad;
	struct vpp_post_hwin_s vpp_post_hwin;
	struct vpp_post_proc_s vpp_post_proc;
};

struct vpp1_post_blend_s {
	u32 bld_out_en;
	u32 bld_out_w;
	u32 bld_out_h;
	//0: vpp1 walk slice1 to venc1; 1: vpp1 bypass slice1 to venc1
	u32 vpp1_dpath_sel;
	//0:select postblend 1:select vpp1 blend
	u32 vd3_dpath_sel;
	u32 bld_out_premult;
	u32 bld_dummy_data;

	//usually the bottom layer set 1, for example postbld_src1_sel = 1,set 0x1
	u32 bld_din0_premult_en;
	u32 bld_din1_premult_en;

	//VD3
	u32 bld_din0_h_start;
	u32 bld_din0_h_end;
	u32 bld_din0_v_start;
	u32 bld_din0_v_end;
	u32 bld_din0_alpha;

	//OSD3
	u32 bld_din1_h_start;
	u32 bld_din1_h_end;
	u32 bld_din1_v_start;
	u32 bld_din1_v_end;
	u32 bld_din1_alpha;

	//1:din0(vd3)  2:din1(osd3) 3:din2 4:din3 5:din4 else :close
	u32 bld_src1_sel;
	u32 bld_src2_sel;
};

struct vpp1_post_s {
	bool vpp1_en;
	bool vpp1_bypass_slice1;
	u32 slice_num;
	u32 overlap_hsize;
	struct vpp1_post_blend_s vpp1_post_blend;
};

struct vpp_post_s {
	struct vpp0_post_s vpp0_post;
	struct vpp1_post_s vpp1_post;
};
#endif

extern int rma_test;
extern int rma_test_addr;
extern struct hw_osd_reg_s hw_osd_reg_array[HW_OSD_COUNT];
#ifdef AML_S5_DISPLAY
struct vpp_post_info_t *get_vpp_post_amdv_info(void);
#endif

#endif /* _OSD_H_ */
