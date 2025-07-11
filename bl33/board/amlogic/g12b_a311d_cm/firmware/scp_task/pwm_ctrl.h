/*
* Copyright (C) 2017 Amlogic, Inc. All rights reserved.
* *
This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* (at your option) any later version.
* *
This program is distributed in the hope that it will be useful, but WITHOUT
* ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
* FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
* more details.
* *
You should have received a copy of the GNU General Public License along
* with this program; if not, write to the Free Software Foundation, Inc.,
* 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
* *
Description:
*/

#ifndef __PWM_CTRL_H__
#define __PWM_CTRL_H__
static int pwm_voltage_table_ee[][2] = {
	{ 0x1c0000,  681},
	{ 0x1b0001,  691},
	{ 0x1a0002,  701},
	{ 0x190003,  711},
	{ 0x180004,  721},
	{ 0x170005,  731},
	{ 0x160006,  741},
	{ 0x150007,  751},
	{ 0x140008,  761},
	{ 0x130009,  772},
	{ 0x12000a,  782},
	{ 0x11000b,  792},
	{ 0x10000c,  802},
	{ 0x0f000d,  812},
	{ 0x0e000e,  822},
	{ 0x0d000f,  832},
	{ 0x0c0010,  842},
	{ 0x0b0011,  852},
	{ 0x0a0012,  862},
	{ 0x090013,  872},
	{ 0x080014,  882},
	{ 0x070015,  892},
	{ 0x060016,  902},
	{ 0x050017,  912},
	{ 0x040018,  922},
	{ 0x030019,  932},
	{ 0x02001a,  942},
	{ 0x01001b,  952},
	{ 0x00001c,  962}
};
/*
static int pwm_voltage_table_ee_new[][2] = {
	{ 0x120000,  700},
	{ 0x110001,  710},
	{ 0x100002,  720},
	{ 0x0f0003,  730},
	{ 0x0e0004,  740},
	{ 0x0d0005,  750},
	{ 0x0c0006,  760},
	{ 0x0b0007,  770},
	{ 0x0a0008,  780},
	{ 0x090009,  790},
	{ 0x08000a,  800},
	{ 0x07000b,  810},
	{ 0x06000c,  820},
	{ 0x05000d,  830},
	{ 0x04000e,  840},
	{ 0x03000f,  850},
	{ 0x020010,  860},
	{ 0x010011,  870},
	{ 0x000012,  880},
};
*/
#endif //__PWM_CTRL_H__
