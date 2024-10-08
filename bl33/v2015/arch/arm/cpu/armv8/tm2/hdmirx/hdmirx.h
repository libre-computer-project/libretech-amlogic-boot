/* SPDX-License-Identifier: (GPL-2.0+ OR MIT) */
/*
 * arch/arm/cpu/armv8/tm2/hdmirx/hdmirx.h
 *
 * Copyright (C) 2020 Amlogic, Inc. All rights reserved.
 *
 */

#ifndef _HDMIRX_H
#define _HDMIRX_H

enum port_sts {
	E_PORT0,
	E_PORT1,
	E_PORT2,
	E_PORT3,
	E_PORT_NUM,
	E_5V_LOST = 0xfd,
	E_HPD_RESET = 0xfe,
	E_INIT = 0xff,
};

struct hdmirx_data_s {
	unsigned char repeater;/*if hdmitx exist,set 1*/
	unsigned char dbg_en;
	unsigned int port_map;
	int up_phy_addr;/*d c b a 4bit*/
	unsigned char *edid_buf;
	int edid_size;
};

/* EDID */
#define EDID_DEFAULT_START		132
#define EDID_DESCRIP_OFFSET		2
#define EDID_BLOCK1_OFFSET		128
#define EDID_DEFAULT_LEN	256

#define EDID_CLK_DIV 9 /* sys clk/(9+1) = 20M */
#define ACR_MODE 0

void hdmirx_hw_init(unsigned int port_map,
						  unsigned char *pedid_data,
						  int edid_size);
#endif

