/* SPDX-License-Identifier: (GPL-2.0+ OR MIT) */
/*
 * arch/arm/cpu/armv8/axg/firmware/scp_task/scp_remote.c
 *
 * Copyright (C) 2020 Amlogic, Inc. All rights reserved.
 *
 */

#include <config.h>
#include "config.h"
#include "registers.h"
#include "task_apis.h"

#ifndef CONFIG_IR_REMOTE_USE_PROTOCOL
#define CONFIG_IR_REMOTE_USE_PROTOCOL 0
#endif
#if 1
typedef struct reg_remote {
	int reg;
	unsigned int val;
} reg_remote;
#define CONFIG_END 0xffffffff
#define IR_POWER_KEY_MASK 0xffffffff

//24M
static const reg_remote RDECODEMODE_NEC[] = {
	{AO_MF_IR_DEC_LDR_ACTIVE, 500 << 16 | 400 << 0},
	{AO_MF_IR_DEC_LDR_IDLE, 300 << 16 | 202 << 0},
	{AO_MF_IR_DEC_LDR_REPEAT, 150 << 16 | 80 << 0},
	{AO_MF_IR_DEC_BIT_0, 72 << 16 | 40 << 0},
	{AO_MF_IR_DEC_REG0, 7 << 28 | (0xFA0 << 12) | 0x13},
	{AO_MF_IR_DEC_STATUS, (134 << 20) | (90 << 10)},
	{AO_MF_IR_DEC_REG1, 0x9f00},
	{AO_MF_IR_DEC_REG2, 0x0},
	{AO_MF_IR_DEC_DURATN2, 0},
	{AO_MF_IR_DEC_DURATN3, 0},
	{CONFIG_END, 0}
};

static const reg_remote RDECODEMODE_DUOKAN[] = {
	{AO_MF_IR_DEC_LDR_ACTIVE, 53 << 16 | 50 << 0},
	{AO_MF_IR_DEC_LDR_IDLE, 31 << 16 | 25 << 0},
	{AO_MF_IR_DEC_LDR_REPEAT, 30 << 16 | 26 << 0},
	{AO_MF_IR_DEC_BIT_0, 61 << 16 | 55 << 0},
	{AO_MF_IR_DEC_REG0, 3 << 28 | (0x5DC << 12) | 0x13},	//body frame 30ms
	{AO_MF_IR_DEC_STATUS, (76 << 20) | 69 << 10},
	{AO_MF_IR_DEC_REG1, 0x9300},
	{AO_MF_IR_DEC_REG2, 0x10b},
	{AO_MF_IR_DEC_DURATN2, 91 << 16 | 79 << 0},
	{AO_MF_IR_DEC_DURATN3, 111 << 16 | 99 << 0},
	{CONFIG_END, 0}
};

static const reg_remote RDECODEMODE_TOSHIBA[] = {
	{AO_MF_IR_DEC_LDR_ACTIVE, 263 << 16 | 194 << 0},
	{AO_MF_IR_DEC_LDR_IDLE, 263 << 16 | 194 << 0},
	{AO_MF_IR_DEC_LDR_REPEAT, 263 << 16 | 194 << 0},
	{AO_MF_IR_DEC_BIT_0, 60 << 16 | 40 << 0},
	{AO_MF_IR_DEC_REG0, 3 << 28 | (0xFA0 << 12) | 0x13},
	{AO_MF_IR_DEC_STATUS, (124 << 20) | (100 << 10)},
	{AO_MF_IR_DEC_REG1, 0x9f50},
	{AO_MF_IR_DEC_REG2, 0x5},
	{AO_MF_IR_DEC_DURATN2, 0},
	{AO_MF_IR_DEC_DURATN3, 0},
	{CONFIG_END, 0}
};

static const reg_remote RDECODEMODE_RCA[] = {
	{AO_MF_IR_DEC_LDR_ACTIVE, ((unsigned)250 << 16) | ((unsigned)160 << 0)},	//rca leader 4000us,200* timebase
	{AO_MF_IR_DEC_LDR_IDLE, 250 << 16 | 160 << 0},	// leader idle 400
	{AO_MF_IR_DEC_LDR_REPEAT, 250 << 16 | 160 << 0},	// leader repeat
	{AO_MF_IR_DEC_BIT_0, 100 << 16 | 48 << 0},	// logic '0' or '00' 1500us
	{AO_MF_IR_DEC_REG0, 3 << 28 | (0xFA0 << 12) | 0x13},	// sys clock body time.base time = 20 body frame
	{AO_MF_IR_DEC_STATUS, (150 << 20) | (110 << 10)},	// logic '1' or '01'    2500us
	{AO_MF_IR_DEC_REG1, 0x9700},	// body long decode (8-13) //framn len = 24bit
	/*it may get the wrong customer value and key value from register if the value is set to 0x4,so the register value must set to 0x104 */
	{AO_MF_IR_DEC_REG2, 0x3904},
	{AO_MF_IR_DEC_REG3, 0x2bc},
	{AO_MF_IR_DEC_DURATN2, 0},
	{AO_MF_IR_DEC_DURATN3, 0},
	{CONFIG_END, 0}
};


static const reg_remote RDECODEMODE_NEC_TOSHIBA_2IN1[] = {
	/*used old decode  for NEC*/
	{AO_IR_DEC_LDR_ACTIVE, ((unsigned)500<<16) | ((unsigned)400<<0)},
	{AO_IR_DEC_LDR_IDLE, 300<<16 | 200<<0},/*leader idle*/
	{AO_IR_DEC_LDR_REPEAT, 150<<16|80<<0}, /*leader repeat*/
	{AO_IR_DEC_BIT_0, 72<<16|40<<0 },/*logic '0' or '00'*/
	{AO_IR_DEC_REG0, 3<<28|(0xFA0<<12)|0x13},/*20us body 108ms*/
	{AO_IR_DEC_STATUS, (134<<20)|(90<<10)},/*logic'1'or'01'*/
	{AO_IR_DEC_REG1, 0xbe10},/*body long decode (9-13)*/
		/* used new decode for toshiba*/
	{AO_MF_IR_DEC_LDR_ACTIVE, 263 << 16 | 194 << 0},
	{AO_MF_IR_DEC_LDR_IDLE, 263 << 16 | 194 << 0},
	{AO_MF_IR_DEC_LDR_REPEAT, 263 << 16 | 194 << 0},
	{AO_MF_IR_DEC_BIT_0, 60 << 16 | 40 << 0},
	{AO_MF_IR_DEC_REG0, 3 << 28 | (0xFA0 << 12) | 0x13},
	{AO_MF_IR_DEC_STATUS, (124 << 20) | (100 << 10)},
	{AO_MF_IR_DEC_REG1, 0x9f50},
	{AO_MF_IR_DEC_REG2, 0x5},
	{AO_MF_IR_DEC_DURATN2, 0},
	{AO_MF_IR_DEC_DURATN3, 0},
	{CONFIG_END, 0}
};

static const reg_remote RDECODEMODE_NEC_RCA_2IN1[] = {
	/*used old decode  for NEC*/
	{AO_IR_DEC_LDR_ACTIVE, ((unsigned)500<<16) | ((unsigned)400<<0)},
	{AO_IR_DEC_LDR_IDLE, 300<<16 | 200<<0},/*leader idle*/
	{AO_IR_DEC_LDR_REPEAT, 150<<16|80<<0}, /*leader repeat*/
	{AO_IR_DEC_BIT_0, 72<<16|40<<0 },/*logic '0' or '00'*/
	{AO_IR_DEC_REG0, 3<<28|(0xFA0<<12)|0x13},/*20us body 108ms*/
	{AO_IR_DEC_STATUS, (134<<20)|(90<<10)},/*logic'1'or'01'*/
	{AO_IR_DEC_REG1, 0xbe10},/*body long decode (9-13)*/
	/*used new decode for rca*/
	{AO_MF_IR_DEC_LDR_ACTIVE, ((unsigned)250 << 16) | ((unsigned)160 << 0)},	//rca leader 4000us,200* timebase
	{AO_MF_IR_DEC_LDR_IDLE, 250 << 16 | 160 << 0},	// leader idle 400
	{AO_MF_IR_DEC_LDR_REPEAT, 250 << 16 | 160 << 0},	// leader repeat
	{AO_MF_IR_DEC_BIT_0, 100 << 16 | 48 << 0},	// logic '0' or '00' 1500us
	{AO_MF_IR_DEC_REG0, 3 << 28 | (0xFA0 << 12) | 0x13},	// sys clock body time.base time = 20 body frame
	{AO_MF_IR_DEC_STATUS, (150 << 20) | (110 << 10)},	// logic '1' or '01'    2500us
	{AO_MF_IR_DEC_REG1, 0x9700},	// body long decode (8-13) //framn len = 24bit
	/*it may get the wrong customer value and key value from register if the value is set to 0x4,so the register value must set to 0x104 */
	{AO_MF_IR_DEC_REG2, 0x3904},
	{AO_MF_IR_DEC_REG3, 0x2bc},
	{AO_MF_IR_DEC_DURATN2, 0},
	{AO_MF_IR_DEC_DURATN3, 0},
	{CONFIG_END, 0}
};

static const reg_remote RDECODEMODE_RCMM[] = {
	/*used old decode  for NEC*/
	{AO_IR_DEC_LDR_ACTIVE, ((unsigned)500<<16) | ((unsigned)400<<0)},
	{AO_IR_DEC_LDR_IDLE, 300<<16 | 200<<0},/*leader idle*/
	{AO_IR_DEC_LDR_REPEAT, 150<<16|80<<0}, /*leader repeat*/
	{AO_IR_DEC_BIT_0, 72<<16|40<<0 },/*logic '0' or '00'*/
	{AO_IR_DEC_REG0, 3<<28|(0xFA0<<12)|0x13},/*20us body 108ms*/
	{AO_IR_DEC_STATUS, (134<<20)|(90<<10)},/*logic'1'or'01'*/
	{AO_IR_DEC_REG1, 0xbe10},/*body long decode (9-13)*/
	// used new decode
	{AO_MF_IR_DEC_LDR_ACTIVE,((unsigned)35<<16) | ((unsigned)17<<0)},//leader active
	{AO_MF_IR_DEC_LDR_IDLE, 17<<16 | 8<<0},// leader idle
	{AO_MF_IR_DEC_LDR_REPEAT,31<<16 | 11<<0}, // leader repeat
	{AO_MF_IR_DEC_BIT_0,25<<16|21<<0 },// logic '0' or '00' 1200us
	{AO_MF_IR_DEC_REG0,3<<28|(590<<12)|0x13},  // sys clock body time.base time = 20 body frame
	{AO_MF_IR_DEC_STATUS,(36<<20)|(29<<10)}, // logic '1' or '01'     2400us
	{AO_MF_IR_DEC_REG1,0x9f00},// body long decode (8-13) //framn len = 24bit //backup
	{AO_MF_IR_DEC_REG2,0x1150a},//back up
	{AO_MF_IR_DEC_DURATN2,43<<16 | 37<<0},
	{AO_MF_IR_DEC_DURATN3,50<<16 | 44<<0},
	{AO_MF_IR_DEC_REG3,1200<<0},
	{CONFIG_END,            0      }
};

static const reg_remote *remoteregsTab[] = {
	RDECODEMODE_NEC,
	RDECODEMODE_DUOKAN,
	RDECODEMODE_TOSHIBA,
	RDECODEMODE_RCA,
	RDECODEMODE_NEC_TOSHIBA_2IN1,
	RDECODEMODE_NEC_RCA_2IN1,
	RDECODEMODE_RCMM,
};

void setremotereg(const reg_remote * r)
{
	writel(r->val, r->reg);
}

int set_remote_mode(int mode)
{
	const reg_remote *reg;

	if (mode >= sizeof(remoteregsTab)/sizeof(remoteregsTab[0])) {
		uart_puts("invalid IR protocol: 0x");
		uart_put_hex(mode, 16);
		uart_puts("\n");
		return -1;
	}
	reg = remoteregsTab[mode];
	while (CONFIG_END != reg->reg)
		setremotereg(reg++);
	return 0;
}

unsigned backuAO_RTI_PIN_MUX_REG;
unsigned backuAO_IR_DEC_REG0;
unsigned backuAO_IR_DEC_REG1;
unsigned backuAO_IR_DEC_LDR_ACTIVE;
unsigned backuAO_IR_DEC_LDR_IDLE;
unsigned backuAO_IR_DEC_BIT_0;
unsigned bakeuAO_IR_DEC_LDR_REPEAT;
/*****************************************************************
**
** func : ir_remote_init
**       in this function will do pin configuration and and initialize for
**       IR Remote hardware decoder mode at 32kHZ on ARC.
**
********************************************************************/
#if 1

static int ir_remote_init_32k_mode(void)
{
	//volatile unsigned int status,data_value;
	int val = readl(AO_RTI_PINMUX_REG0);
	writel((val | (1 << 24)), AO_RTI_PINMUX_REG0);
	set_remote_mode(CONFIG_IR_REMOTE_USE_PROTOCOL);
	//status = readl(AO_MF_IR_DEC_STATUS);
	readl(AO_MF_IR_DEC_STATUS);
	//data_value = readl(AO_MF_IR_DEC_FRAME);
	readl(AO_MF_IR_DEC_FRAME);

	//step 2 : request nec_remote irq  & enable it
#if CONFIG_IR_REMOTE_USE_PROTOCOL == 3
	writel(readl(AO_IR_DEC_REG1)&(~(1<<15)),AO_IR_DEC_REG1);
#endif
	return 0;
}

void init_custom_trigger(void)
{
	ir_remote_init_32k_mode();
}
#endif

static unsigned int kk[] = {
	CONFIG_IR_REMOTE_POWER_UP_KEY_VAL1,
	CONFIG_IR_REMOTE_POWER_UP_KEY_VAL2,
	CONFIG_IR_REMOTE_POWER_UP_KEY_VAL3,
	CONFIG_IR_REMOTE_POWER_UP_KEY_VAL4,
	CONFIG_IR_REMOTE_POWER_UP_KEY_VAL5,
	CONFIG_IR_REMOTE_POWER_UP_KEY_VAL6,
	CONFIG_IR_REMOTE_POWER_UP_KEY_VAL7,
	CONFIG_IR_REMOTE_POWER_UP_KEY_VAL8,
	CONFIG_IR_REMOTE_POWER_UP_KEY_VAL9,
};

static int init_remote(void)
{
	uart_put_hex(readl(AO_IR_DEC_STATUS), 32);
	uart_put_hex(readl(AO_IR_DEC_FRAME), 32);
	init_custom_trigger();
	return 0;
}
#endif
unsigned int usr_pwr_key = 0xffffffff;
static int remote_detect_key(void)
{
	unsigned power_key;
	int j;

	if (((readl(AO_MF_IR_DEC_STATUS)) >> 3) & 0x1) { /*to judge the frame whether is effective or not*/
			if (readl(AO_MF_IR_DEC_STATUS) & 0x1) {		  /*to judge the frame whether is repeat frame or not*/
				readl(AO_MF_IR_DEC_FRAME);
				return 0;
			}
			power_key = readl(AO_MF_IR_DEC_FRAME);

			for (j = 0; j < CONFIG_IR_REMOTE_POWER_UP_KEY_CNT; j++) {
					if ((power_key & IR_POWER_KEY_MASK) == kk[j])
							return 1;
			}
			if ((power_key & IR_POWER_KEY_MASK) == usr_pwr_key)
					return 2;
	}

#ifdef CONFIG_COMPAT_IR
	if (((readl(AO_IR_DEC_STATUS)) >> 3) & 0x1) { /*to judge the frame whether is effective or not*/
			if (readl(AO_IR_DEC_STATUS) & 0x1) { 	  /*to judge the frame whether is repeat frame or not*/
				readl(AO_IR_DEC_FRAME);
				return 0;
			}
			power_key = readl(AO_IR_DEC_FRAME);
			for (j = 0; j < CONFIG_IR_REMOTE_POWER_UP_KEY_CNT; j++) {
					if ((power_key & IR_POWER_KEY_MASK) == kk[j])
							return 1;
			}
			if ((power_key & IR_POWER_KEY_MASK) == usr_pwr_key)
					return 2;
	}
#endif

	return 0;

}