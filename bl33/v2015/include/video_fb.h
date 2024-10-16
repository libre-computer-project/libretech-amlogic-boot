/*
 * (C) Copyright 1997-2002 ELTEC Elektronik AG
 * Frank Gottschling <fgottschling@eltec.de>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

/*
 * smiLynxEM.h
 * Silicon Motion graphic interface for sm810/sm710/sm712 accelerator
 *
 *
 *  modification history
 *  --------------------
 *  04-18-2002 Rewritten for U-Boot <fgottschling@eltec.de>.
 */

#ifndef _VIDEO_FB_H_
#define _VIDEO_FB_H_

#if defined(CONFIG_SYS_CONSOLE_FG_COL) && defined(CONFIG_SYS_CONSOLE_BG_COL)
#define CONSOLE_BG_COL            CONFIG_SYS_CONSOLE_BG_COL
#define CONSOLE_FG_COL            CONFIG_SYS_CONSOLE_FG_COL
#else
#define CONSOLE_BG_COL            0x00
#define CONSOLE_FG_COL            0xa0
#endif

/*
 * Graphic Data Format (GDF) bits for VIDEO_DATA_FORMAT
 */
#define GDF__8BIT_INDEX         0
#define GDF_15BIT_555RGB        1
#define GDF_16BIT_565RGB        2
#define GDF_32BIT_X888RGB       3
#define GDF_24BIT_888RGB        4
#define GDF__8BIT_332RGB        5

/******************************************************************************/
/* Export Graphic Driver Control                                              */
/******************************************************************************/

typedef struct graphic_device {
    unsigned int isaBase;
    unsigned int pciBase;
    unsigned int dprBase;
    unsigned int vprBase;
    unsigned int cprBase;
    unsigned int frameAdrs;
    unsigned int memSize;
    unsigned int fb_width;
    unsigned int fb_height;
    unsigned int mode;
    unsigned int gdfIndex;
    unsigned int gdfBytesPP;
    unsigned int fg;
    unsigned int bg;
    unsigned int plnSizeX;
    unsigned int plnSizeY;
    unsigned int winSizeX;
    unsigned int winSizeY;
    char modeIdent[80];
} GraphicDevice;


/******************************************************************************/
/* Export Graphic Functions                                                   */
/******************************************************************************/

void *video_hw_init (int display_mode);       /* returns GraphicDevice struct or NULL */
int get_osd_layer(void);
u32 osd_canvas_align(u32 x);

#define CANVAS_ALIGNED(x) osd_canvas_align(x)

#ifdef VIDEO_HW_BITBLT
void video_hw_bitblt (
    unsigned int bpp,             /* bytes per pixel */
    unsigned int src_x,           /* source pos x */
    unsigned int src_y,           /* source pos y */
    unsigned int dst_x,           /* dest pos x */
    unsigned int dst_y,           /* dest pos y */
    unsigned int dim_x,           /* frame width */
    unsigned int dim_y            /* frame height */
    );
#endif

#ifdef VIDEO_HW_RECTFILL
void video_hw_rectfill (
    unsigned int bpp,             /* bytes per pixel */
    unsigned int dst_x,           /* dest pos x */
    unsigned int dst_y,           /* dest pos y */
    unsigned int dim_x,           /* frame width */
    unsigned int dim_y,           /* frame height */
    unsigned int color            /* fill color */
     );
#endif

void video_set_lut (
    unsigned int index,           /* color number */
    unsigned char r,              /* red */
    unsigned char g,              /* green */
    unsigned char b               /* blue */
    );
#ifdef CONFIG_VIDEO_HW_CURSOR
void video_set_hw_cursor(int x, int y); /* x y in pixel */
void video_init_hw_cursor(int font_width, int font_height);
#endif

enum display_mode_e {
	MIDDLE_MODE,
	RECT_MODE,
	FULL_SCREEN_MODE,
};

enum pci_type_e {
	BMP_PIC,
	RAW_PIC,
};

typedef struct {
	int width;
	int height;
	int row_bytes;
	int pixel_bytes;
	unsigned char *data;
} grsurface;

typedef struct {
	grsurface *texture;
	int char_width;
	int char_height;
} grfont;

int screen_init(void);
void screen_uninit(void);
int gr_init_ext_font(const char *font, grfont **dest);
int surface_loadbmp(grsurface **surface, const char *filename);
int surface_loadbmp_from_addr(grsurface **surface, long addr);
void surface_disaplay(grsurface *surface, int sx, int sy, int dx, int dy);
void screen_setcolor(unsigned int color);
void screen_drawtextline(const grfont *font, int x, int y, const char *s, bool bold);
void screen_fillrect(int x, int y, int w, int h);
void screen_update(void);
void res_free_surface(grsurface *surface);
const grfont *gr_sys_font(void);
#endif /*_VIDEO_FB_H_ */
