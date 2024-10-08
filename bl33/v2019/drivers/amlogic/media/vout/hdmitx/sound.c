// SPDX-License-Identifier: (GPL-2.0+ OR MIT)
/*
 * Copyright (c) 2019 Amlogic, Inc. All rights reserved.
 */

#include <asm/arch/io.h>
#include <asm/arch/register.h>
#include <common.h>
#include <amlogic/auge_sound.h>
#include <asm/arch/cpu.h>
#include <amlogic/cpu_id.h>

struct aiu_958_channel_status {
	unsigned short chstat0_l;
	unsigned short chstat1_l;
	unsigned short chstat0_r;
	unsigned short chstat1_r;
};

static int audiobus_read(unsigned long reg, unsigned int *val)
{
	*val = readl(reg);
	return 0;
}

static void hhi_write(unsigned long reg, unsigned int val)
{
	writel(val, reg);
}

static void audiobus_write(unsigned long reg, unsigned int val)
{
	writel(val, reg);
}

static int audiobus_update_bits(unsigned int reg, unsigned int mask,
				unsigned int value)
{
	bool change;
	unsigned int old, new;

	audiobus_read(reg, &old);

	new = (old & ~mask) | (value & mask);
	change = old != new;
	if (change)
		audiobus_write(reg, new);

	return change;
}

static void aml_set_audio_spdif_clk(void)
{
	/*mpll0: 491520000 */
	// TODO
	if (0)
		hhi_write(0, 0x543);
	//hhi_write(ANACTRL_MPLL_CTRL0, 0x543);
	//hhi_write(ANACTRL_MPLL_CTRL1, 0xC040046B);
	//hhi_write(ANACTRL_MPLL_CTRL2, 0x40000033);

	/* audio clk gate */
	audiobus_write(EE_AUDIO_CLK_GATE_EN0,
		       1 << 17  /* spdifout */
		       | 1 << 9 /* frddra */
		       | 1 << 0 /* ddr_arb */);

	/*hifipll 1179.648M for s4/s4d*/
	if (get_cpu_id().family_id == MESON_CPU_MAJOR_ID_S4 ||
		get_cpu_id().family_id == MESON_CPU_MAJOR_ID_S4D)
		audiobus_write(EE_AUDIO_CLK_SPDIFOUT_CTRL,
				1 << 31   /* enable */
				| 4 << 24 /* hifipll0 */
				| 0xbf << 0  /* dividor */);
	else
		/*hifipll 491.52M*/
		audiobus_write(EE_AUDIO_CLK_SPDIFOUT_CTRL,
				1 << 31   /* enable */
				| 4 << 24 /* hifipll0 */
				| 0x4f << 0  /* dividor */);
}

static void aml_spdif_fifo_ctrl(void)
{
	/* reg mute val */
	audiobus_write(EE_AUDIO_SPDIFOUT_MUTE_VAL, 0x0);

	/* mask lane0 L/R, lsb first,  insert data from 31bits */
	audiobus_update_bits(EE_AUDIO_SPDIFOUT_CTRL0,
			     0x1<<22 | 0x1<<21 | 0x1 << 20 | 0x1 << 19 | 0xffff << 0,
			     0x1<<22 | 0x1<<21 | 0x0 << 20 | 0x0 << 19 | 0x3 << 0);

	/* split 64bits ddr data to 2 sample */
	/* msb position of data */
	/* frddr_A */
	audiobus_update_bits(EE_AUDIO_SPDIFOUT_CTRL1,
			     0x3 << 24 | 0x1f << 8 | 0x7 << 4,
			     0 << 24 | (32 - 1) << 8 | 3 << 4);

	audiobus_write(EE_AUDIO_SPDIFOUT_SWAP, 0x1 << 4);
}

static void spdifout_set_pcm_chsts(struct aiu_958_channel_status *set)
{
	if (!set) {
		printf("%s(), error set NULL point\n", __func__);
		return;
	}

	audiobus_write(EE_AUDIO_SPDIFOUT_CHSTS0,
		       set->chstat1_l << 16 | set->chstat0_l);
	audiobus_write(EE_AUDIO_SPDIFOUT_CHSTS6,
		       set->chstat1_r << 16 | set->chstat0_r);
}

void frddr_init_without_mngr(void)
{
	unsigned int start_addr, end_addr, int_addr;
	static int buf[256];

	memset(buf, 0x0, sizeof(buf));
	start_addr = virt_to_phys(buf);
	end_addr = start_addr + sizeof(buf) - 1;
	int_addr = sizeof(buf) / 64;

/*some chip not use arb, and not define*/
#ifdef EE_AUDIO_ARB_CTRL0
	audiobus_write(EE_AUDIO_ARB_CTRL0, 0x800000ff);
#endif
	audiobus_write(EE_AUDIO_FRDDR_A_START_ADDR, start_addr);

	audiobus_write(EE_AUDIO_FRDDR_A_INIT_ADDR, start_addr);

	audiobus_write(EE_AUDIO_FRDDR_A_FINISH_ADDR, end_addr);

	audiobus_write(EE_AUDIO_FRDDR_A_INT_ADDR, int_addr);

	audiobus_write(EE_AUDIO_FRDDR_A_CTRL1,
		       (0x40 - 1) << 24 | (0x20 - 1) << 16 | 2 << 8 | 0 << 0);

	audiobus_write(EE_AUDIO_FRDDR_A_CTRL0,
		       1 << 31
		       | 0 << 24
		       | 4 << 16
	);

	/* src0 enable, src0 select spdifout */
	audiobus_write(EE_AUDIO_FRDDR_A_CTRL2, 1 << 4 | 3 << 0);
}

static void aml_spdif_enable(void)
{
	/* reset */
	audiobus_update_bits(EE_AUDIO_SPDIFOUT_CTRL0, 3 << 28, 0);
	audiobus_update_bits(EE_AUDIO_SPDIFOUT_CTRL0, 1 << 29, 1 << 29);
	audiobus_update_bits(EE_AUDIO_SPDIFOUT_CTRL0, 1 << 28, 1 << 28);
	/* enable */
	audiobus_update_bits(EE_AUDIO_SPDIFOUT_CTRL0, 1 << 31, 1 << 31);

	/* tohdmitx enable */
	audiobus_write(EE_AUDIO_TOHDMITX_CTRL0,
		       1 << 3   /* spdif_clk_cap_inv */
		       | 0 << 2 /* spdif_clk_inv */
		       | 0 << 1 /* spdif_out */
		       | 0 << 0 /* spdif_clk */
	);
	audiobus_update_bits(EE_AUDIO_TOHDMITX_CTRL0,
			     0x1 << 30, 0x1 << 30);

	audiobus_update_bits(EE_AUDIO_TOHDMITX_CTRL0,
			     0x1 << 31, 0x1 << 31);
}

static void aml_spdif_play(void)
{
	struct aiu_958_channel_status chstat;

	chstat.chstat0_l = 0x0100;
	chstat.chstat0_r = 0x0100;
	chstat.chstat1_l = 0X200;
	chstat.chstat1_r = 0X200;

	aml_spdif_fifo_ctrl();
	spdifout_set_pcm_chsts(&chstat);
	frddr_init_without_mngr();
	aml_spdif_enable();
}

int aml_audio_init(void)
{
	printf("%s\n", __func__);

	aml_set_audio_spdif_clk();
	aml_spdif_play();

	return 0;
}

