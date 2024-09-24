// SPDX-License-Identifier: (GPL-2.0+ OR MIT)
/*
 * Copyright (c) 2019 Amlogic, Inc. All rights reserved.
 */

#include <config.h>
#include <common.h>
#include <asm/arch/io.h>
#include <command.h>
#include <malloc.h>
#include <asm/arch/mailbox.h>
#include <asm/arch/secure_apb.h>

#define aml_writel32(value, reg)	writel(value, reg)
#define aml_readl32(reg)		readl(reg)

static inline void mbwrite(uint32_t to, void *from, long count)
{
	int i = 0;
	int len = count / 4 + ((count % 4) ? 1 : 0);
	uint32_t *p = from;

	while (len > 0) {
		aml_writel32(p[i], to + (4 * i));
		len--;
		i++;
	}
}

static inline void mbread(void *to, uint32_t from, long count)
{
	int i = 0;
	int len = count / 4 + ((count % 4) ? 1 : 0);
	uint32_t *p = to;

	while (len > 0) {
		p[i] = aml_readl32(from + (4 * i));
		len--;
		i++;
	}
}

static inline void mbclean(uint32_t to, long count)
{
	int i = 0;
	int len = count / 4 + ((count % 4) ? 1 : 0);

	while (len > 0) {
		aml_writel32(0, to + (4 * i));
		len--;
		i++;
	}
}

/* Return if AOCPU is alive by checking AOCPU tick count */
static uint32_t is_aocpu_alive(void)
{
	uint32_t aocpu_tick_count_1;
	uint32_t aocpu_tick_count_2;
	uint32_t ret;

	aocpu_tick_count_1 = aml_readl32(AOCPU_TICK_CNT_RD_ADDR);
	printf("%s: aocpu_tick_count_1 = %x\n", __func__, aocpu_tick_count_1);
	/* Wait for 50 msec to let tick count update */
	mdelay(50);
	aocpu_tick_count_2 = aml_readl32(AOCPU_TICK_CNT_RD_ADDR);
	printf("%s: aocpu_tick_count_2 = %x\n", __func__, aocpu_tick_count_2);
	if (aocpu_tick_count_1 == aocpu_tick_count_2)
		ret = 0;
	else
		ret = 1;

	return ret;
}

/* Return timerE value (seconds) */
static uint32_t read_timer_e(void)
{
	unsigned long long time64 = 0, time_high = 0;
	uint32_t time = 0;

	/*timeE high+low, first read low, second read high*/
	time64 = aml_readl32(TIMERE_LOW_REG);
	time_high = aml_readl32(TIMERE_HIG_REG);
	time64 += (time_high << 32);
	time64 = time64 / 1000000;
	time = (uint32_t)time64;

	return time;
}

int mhu_get_addr(uint32_t chan, uint32_t *mboxset, uint32_t *mboxsts,
		 uint32_t *mboxwr, uint32_t *mboxrd,
		 uint32_t *mboxirqclr, uint32_t *mboxid)
{
	int ret = 0;

	switch (chan) {
	case AOCPU_REE_CHANNEL:
		*mboxset = REE2AO_SET_ADDR;
		*mboxsts = REE2AO_STS_ADDR;
		*mboxwr = REE2AO_WR_ADDR;
		*mboxrd = REE2AO_RD_ADDR;
		*mboxirqclr = REE2AO_IRQCLR_ADDR;
		*mboxid = REE2AO_MBOX_ID;
		break;
	default:
		printf("[BL33]: no support chan 0x%x\n", chan);
		ret = -1;
		break;
	};
	return ret;
}

void mhu_message_start(uint32_t mboxsts)
{
	/* Make sure any previous command has finished */
	while (aml_readl32(mboxsts) != 0)
		;
}

void mhu_build_payload(uint32_t mboxwr, void *message, uint32_t size)
{
	if (size > (MHU_PAYLOAD_SIZE - MHU_DATA_OFFSET)) {
		printf("bl33: scpi send input size error\n");
		return;
	}
	if (size == 0)
		return;
	mbwrite(mboxwr + MHU_DATA_OFFSET, message, size);
}

void mhu_get_payload(uint32_t mboxwr, uint32_t mboxrd, void *message, uint32_t size)
{
	if (size > (MHU_PAYLOAD_SIZE - MHU_DATA_OFFSET)) {
		printf("bl33: scpi send input size error\n");
		return;
	}
	if (size == 0)
		return;
	mbread(message, mboxrd + MHU_DATA_OFFSET, size);
	mbclean(mboxwr, MHU_PAYLOAD_SIZE);
}

void mhu_message_send(uint32_t mboxset, uint32_t command, uint32_t size)
{
	uint32_t mbox_cmd;

	mbox_cmd = MHU_CMD_BUILD(command, size + MHU_DATA_OFFSET);
	aml_writel32(mbox_cmd, mboxset);
}

uint32_t mhu_message_wait(uint32_t mboxset, uint32_t mboxsts,
	uint32_t command, uint32_t size)
{
	/* Wait for response from other core */
	uint32_t response;
	uint32_t time_stamp_start = 0;
	uint32_t time_stamp_end = 0;
	uint32_t time_elapse = 0;
	uint32_t retry_cnt = 2;
	uint32_t aocpu_alive;
	uint32_t mbox_cmd;

	time_stamp_start = read_timer_e();
	while ((response = aml_readl32(mboxsts))) {
		time_stamp_end = read_timer_e();
		time_elapse = time_stamp_end - time_stamp_start;
		/* Set mailbox wait time out: 1 second */
		if (time_elapse > 1) {
			printf("%s: warning: mailbox wait time out, send fail!\n",
				__func__);
			aocpu_alive = is_aocpu_alive();
			if (aocpu_alive)
				printf("%s: aocpu is alive!\n", __func__);
			else
				printf("%s: aocpu is not alive!\n", __func__);

			if (retry_cnt == 0)
				break;
			retry_cnt--;

			printf("%s: mailbox send retry\n", __func__);
			mbox_cmd = MHU_CMD_BUILD(command, size + MHU_DATA_OFFSET);
			aml_writel32(0, mboxset);
			aml_writel32(mbox_cmd, mboxset);
			time_stamp_start = read_timer_e();
		}
	}

	return response;
}

void mhu_message_end(uint32_t mboxwr, uint32_t mboxirqclr, uint32_t mboxid)
{
	/* Clear all datas in mailbox buffer */
	mbclean(mboxwr, MHU_PAYLOAD_SIZE);
	/* Clear irq_clr */
	aml_writel32(MHU_ACK_MASK(mboxid), mboxirqclr);
}

void mhu_init(void)
{
	aml_writel32(0xffffffffu, REE2AO_CLR_ADDR);
	printf("[BL33] mhu init done fifo-v2\n");
}

int scpi_send_data(uint32_t chan, uint32_t command,
		   void *sendmessage, uint32_t sendsize,
		   void *revmessage, uint32_t revsize)
{
	uint32_t mboxset = 0;
	uint32_t mboxsts = 0;
	uint32_t mboxwr = 0;
	uint32_t mboxrd = 0;
	uint32_t mboxirqclr = 0;
	uint32_t mboxid = 0;
	int ret = 0;

	ret = mhu_get_addr(chan, &mboxset, &mboxsts,
			&mboxwr, &mboxrd,
			&mboxirqclr, &mboxid);
	if (ret) {
		printf("bl33: mhu get addr fail\n");
		return ret;
	}
	mhu_message_start(mboxsts);
	if (sendmessage && sendsize != 0)
		mhu_build_payload(mboxwr, sendmessage, sendsize);
	mhu_message_send(mboxset, command, sendsize);
	mhu_message_wait(mboxset, mboxsts, command, sendsize);
	if (revmessage && revsize != 0)
		mhu_get_payload(mboxwr, mboxrd, revmessage, revsize);
	mhu_message_end(mboxwr, mboxirqclr, mboxid);
	return ret;
}
