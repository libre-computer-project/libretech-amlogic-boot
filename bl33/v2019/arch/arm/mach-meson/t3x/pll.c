// SPDX-License-Identifier: (GPL-2.0+ OR MIT)
/*
 * Copyright (c) 2019 Amlogic, Inc. All rights reserved.
 */

#include <common.h>
#include <command.h>
#include <asm/io.h>
#include <asm/arch/secure_apb.h>
#include <../clk-pll.h>
#include <linux/kernel.h>

#define SECURE_PLL_CLK		0x82000098
#define SECURE_CPU_CLK		0x82000099

#define CLKCTRL_PCIEPLL_CTRL0			(0xfe008000 + (0x50 << 2))
#define CLKCTRL_PCIEPLL_CTRL1			(0xfe008000 + (0x51 << 2))
#define CLKCTRL_PCIEPLL_CTRL2			(0xfe008000 + (0x52 << 2))
#define CLKCTRL_PCIEPLL_CTRL3			(0xfe008000 + (0x53 << 2))

/* PLL secure clock index */
enum sec_pll {
	SECID_SYS0_DCO_PLL = 0,
	SECID_SYS0_DCO_PLL_DIS,
	SECID_SYS0_PLL_OD,
	SECID_SYS1_DCO_PLL,
	SECID_SYS1_DCO_PLL_DIS,
	SECID_SYS1_PLL_OD,
	SECID_CPU_CLK_SEL,
	SECID_CPU_CLK_RD,
	SECID_CPU_CLK_DYN,
	SECID_A76_CLK_SEL,
	SECID_A76_CLK_RD,
	SECID_A76_CLK_DYN,
	SECID_DSU_CLK_SEL,
	SECID_DSU_CLK_RD,
	SECID_DSU_CLK_DYN,
	SECID_DSU_FINAL_CLK_SEL,
	SECID_DSU_FINAL_CLK_RD,
	SECID_SYS_CLK_RD,
	SECID_SYS_CLK_DYN,
	SECID_AXI_CLK_RD,
	SECID_AXI_CLK_DYN,
	SECID_SYS2_DCO_PLL,
	SECID_SYS2_DCO_PLL_DIS,
	SECID_SYS2_PLL_OD,
	SECID_SYS3_DCO_PLL,
	SECID_SYS3_DCO_PLL_DIS,
	SECID_SYS3_PLL_OD,
	SECID_PLL_TEST,
	/*
	 * make it usable for all SoCs in Kernel clk debug driver,
	 * if the secid exceed 100, Update it
	 */
	SECID_SECURE_RD = 100,
	SECID_SECURE_WR,
};

unsigned int store;

int t3x_sys0_pll_prepare(struct meson_clk_pll_data *pll)
{
	struct arm_smccc_res res;

	/* store rate */
	meson_pll_store_rate(pll);

	/* Set fixed clk to 1G, Switch to fixed clk first */
	arm_smccc_smc(SECURE_CPU_CLK, SECID_CPU_CLK_DYN,
	1, 0, 0, 0, 0, 0, &res);

	meson_switch_cpu_clk(SECURE_CPU_CLK, SECID_CPU_CLK_SEL, 0);

	/* Switch dsu to cpu0 */
	arm_smccc_smc(SECURE_CPU_CLK, SECID_DSU_CLK_SEL,
	(0x1 << 31), (0 << 31), 0, 0, 0, 0, &res);

	return 0;
}

void t3x_sys0_pll_unprepare(struct meson_clk_pll_data *pll)
{
	struct arm_smccc_res res;

	/* restore rate */
	meson_pll_restore_rate(pll);

	/* Switch back cpu to sys pll */
	meson_switch_cpu_clk(SECURE_CPU_CLK, SECID_CPU_CLK_SEL, 1);

	/* Switch back dsu to sys3 pll */
	arm_smccc_smc(SECURE_CPU_CLK, SECID_DSU_CLK_SEL,
	(0x1 << 31), (0x1 << 31), 0, 0, 0, 0, &res);
}

static const struct pll_params_table t3x_sys_pll_table[] = {
	PLL_PARAMS(83, 1, 0), /*DCO=1992M OD=1992M restore*/
	PLL_PARAMS(126, 1, 1), /*DCO=3024M OD=1512M*/
	{ /* sentinel */ }
};

static unsigned int t3x_sys_pll_default_rate[] = {1512, 1992};

static const struct reg_sequence t3x_sys0_pll_init_regs[] = {
	{ .reg = CLKCTRL_SYS0PLL_CTRL0, .def = 0x20011086 },
	{ .reg = CLKCTRL_SYS0PLL_CTRL0, .def = 0x30011086 },
	{ .reg = CLKCTRL_SYS0PLL_CTRL1, .def = 0x3420500f },
	{ .reg = CLKCTRL_SYS0PLL_CTRL2, .def = 0x00023041 },
	{ .reg = CLKCTRL_SYS0PLL_CTRL3, .def = 0x0, .delay_us = 20 },
	{ .reg = CLKCTRL_SYS0PLL_CTRL0, .def = 0x10011086, .delay_us = 20},
	{ .reg = CLKCTRL_SYS0PLL_CTRL2, .def = 0x00023001 }
};

struct meson_clk_pll_data t3x_sys0_pll = {
	.name = "sys0",
	.en = {
		.reg = CLKCTRL_SYS0PLL_CTRL0,
		.shift   = 28,
		.width   = 1,
	},
	.m = {
		.reg = CLKCTRL_SYS0PLL_CTRL0,
		.shift   = 0,
		.width   = 8,
	},
	.n = {
		.reg = CLKCTRL_SYS0PLL_CTRL0,
		.shift   = 16,
		.width   = 5,
	},
	.od = {
		.reg = CLKCTRL_SYS0PLL_CTRL0,
		.shift	 = 12,
		.width	 = 3,
	},
	.def_rate = t3x_sys_pll_default_rate,
	.def_cnt = ARRAY_SIZE(t3x_sys_pll_default_rate),
	.table = t3x_sys_pll_table,
	.init_regs = t3x_sys0_pll_init_regs,
	.init_count = ARRAY_SIZE(t3x_sys0_pll_init_regs),
	.l = {
		.reg = CLKCTRL_SYS0PLL_CTRL0,
		.shift   = 31,
		.width   = 1,
	},
	.rst = {
		.reg = CLKCTRL_SYS0PLL_CTRL0,
		.shift   = 29,
		.width   = 1,
	},
	.ops = &(const struct meson_pll_test_ops) {
		.pll_prepare = t3x_sys0_pll_prepare,
		.pll_unprepare = t3x_sys0_pll_unprepare,
		.pll_disable = meson_secure_pll_disable,
		.pll_set_rate = meson_secure_pll_set_rate,
		.pll_set_parm_rate = meson_secure_pll_set_parm_rate,
		.pll_rate_to_msr = meson_div16_to_msr,

	},
	.smc_id = SECURE_PLL_CLK,
	.secid_disable = SECID_SYS0_DCO_PLL_DIS,
	.secid_test = SECID_PLL_TEST,
	.secid = SECID_SYS0_DCO_PLL,
	.clkmsr_id = 23,
	.clkmsr_margin = 10,
};

int t3x_sys1_pll_prepare(struct meson_clk_pll_data *pll)
{
	struct arm_smccc_res res;
	unsigned int tmp;

	/* store rate */
	meson_pll_store_rate(pll);

	/* enable sys1 pll clkmsr */
	arm_smccc_smc(SECURE_CPU_CLK, SECID_SECURE_RD,
	CPUCTRL_SYS_CPU_CLK_CTRL6, 0, 0, 0, 0, 0, &res);
	tmp = res.a0;
	store = res.a0;
	tmp |= (1 << 12) | (1 << 13);
	arm_smccc_smc(SECURE_CPU_CLK, SECID_SECURE_WR,
	CPUCTRL_SYS_CPU_CLK_CTRL6, tmp, 0, 0, 0, 0, &res);

	return 0;
}

void t3x_sys1_pll_unprepare(struct meson_clk_pll_data *pll)
{
	struct arm_smccc_res res;

	/* restore rate */
	meson_pll_restore_rate(pll);

	/* restore the clkmsr setting */
	arm_smccc_smc(SECURE_CPU_CLK, SECID_SECURE_WR,
	CPUCTRL_SYS_CPU_CLK_CTRL6, store, 0, 0, 0, 0, &res);
}

static const struct pll_params_table t3x_sys1_pll_table[] = {
	PLL_PARAMS(67, 1, 0), /*DCO=1608M OD=1608M restore*/
	PLL_PARAMS(83, 1, 0), /*DCO=1992M OD=1992M */
	PLL_PARAMS(126, 1, 1), /*DCO=3024M OD=1512M*/
	{ /* sentinel */ }
};

static unsigned int t3x_sys1_pll_default_rate[] = {1512, 1608, 1992};

static const struct reg_sequence t3x_sys1_pll_init_regs[] = {
	{ .reg = CLKCTRL_SYS1PLL_CTRL0, .def = 0x20011086 },
	{ .reg = CLKCTRL_SYS1PLL_CTRL0, .def = 0x30011086 },
	{ .reg = CLKCTRL_SYS1PLL_CTRL1, .def = 0x3420500f },
	{ .reg = CLKCTRL_SYS1PLL_CTRL2, .def = 0x00023041 },
	{ .reg = CLKCTRL_SYS1PLL_CTRL3, .def = 0x0, .delay_us = 20 },
	{ .reg = CLKCTRL_SYS1PLL_CTRL0, .def = 0x10011086, .delay_us = 20 },
	{ .reg = CLKCTRL_SYS1PLL_CTRL2, .def = 0x00023001 }
};

struct meson_clk_pll_data t3x_sys1_pll = {
	.name = "sys1",
	.en = {
		.reg = CLKCTRL_SYS1PLL_CTRL0,
		.shift   = 28,
		.width   = 1,
	},
	.m = {
		.reg = CLKCTRL_SYS1PLL_CTRL0,
		.shift   = 0,
		.width   = 8,
	},
	.n = {
		.reg = CLKCTRL_SYS1PLL_CTRL0,
		.shift   = 16,
		.width   = 5,
	},
	.od = {
		.reg = CLKCTRL_SYS1PLL_CTRL0,
		.shift	 = 12,
		.width	 = 3,
	},
	.def_rate = t3x_sys1_pll_default_rate,
	.def_cnt = ARRAY_SIZE(t3x_sys1_pll_default_rate),
	.table = t3x_sys1_pll_table,
	.init_regs = t3x_sys1_pll_init_regs,
	.init_count = ARRAY_SIZE(t3x_sys1_pll_init_regs),
	.l = {
		.reg = CLKCTRL_SYS1PLL_CTRL0,
		.shift   = 31,
		.width   = 1,
	},
	.rst = {
		.reg = CLKCTRL_SYS1PLL_CTRL0,
		.shift   = 29,
		.width   = 1,
	},
	.ops = &(const struct meson_pll_test_ops) {
		.pll_prepare = t3x_sys1_pll_prepare,
		.pll_unprepare = t3x_sys1_pll_unprepare,
		.pll_disable = meson_secure_pll_disable,
		.pll_set_rate = meson_secure_pll_set_rate,
		.pll_set_parm_rate = meson_secure_pll_set_parm_rate,
		.pll_rate_to_msr = meson_div16_to_msr,
	},
	.smc_id = SECURE_PLL_CLK,
	.secid_disable = SECID_SYS1_DCO_PLL_DIS,
	.secid_test = SECID_PLL_TEST,
	.secid = SECID_SYS1_DCO_PLL,
	.clkmsr_id = 23,
	.clkmsr_margin = 10
};

int t3x_sys3_pll_prepare(struct meson_clk_pll_data *pll)
{
	struct arm_smccc_res res;
	unsigned int tmp;

	/* store rate */
	meson_pll_store_rate(pll);

	/* Set dsu dyn = 1G  */
	arm_smccc_smc(SECURE_CPU_CLK, SECID_DSU_CLK_DYN,
	1, 0, 0, 0, 0, 0, &res);

	/* set dsu to 1G, avoid dsu beyond its max frequency 1.6G */
	meson_switch_cpu_clk(SECURE_CPU_CLK, SECID_DSU_CLK_SEL, 0);

	/* enable sys1 pll clkmsr */
	arm_smccc_smc(SECURE_CPU_CLK, SECID_SECURE_RD,
	CPUCTRL_SYS_CPU_CLK_CTRL6, 0, 0, 0, 0, 0, &res);
	tmp = res.a0;
	store = res.a0;
	tmp &= ~(1 << 13);
	arm_smccc_smc(SECURE_CPU_CLK, SECID_SECURE_WR,
	CPUCTRL_SYS_CPU_CLK_CTRL6, tmp, 0, 0, 0, 0, &res);

	return 0;
}

void t3x_sys3_pll_unprepare(struct meson_clk_pll_data *pll)
{
	struct arm_smccc_res res;

	/* restore rate */
	meson_pll_restore_rate(pll);

	/* switch dsu back to sys3 pll */
	meson_switch_cpu_clk(SECURE_CPU_CLK, SECID_DSU_CLK_SEL, 1);

	/* restore the clkmsr setting */
	arm_smccc_smc(SECURE_CPU_CLK, SECID_SECURE_WR,
	CPUCTRL_SYS_CPU_CLK_CTRL6, store, 0, 0, 0, 0, &res);
}

static const struct pll_params_table t3x_sys3_pll_table[] = {
	PLL_PARAMS(67, 1, 0), /*DCO=1608M OD=1608M */
	PLL_PARAMS(83, 1, 0), /*DCO=1992M OD=1992M */
	PLL_PARAMS(126, 1, 1), /*DCO=3024M OD=1512M restore */
	{ /* sentinel */ }
};

static unsigned int t3x_sys3_pll_default_rate[] = {1512, 1608, 1992};

static const struct reg_sequence t3x_sys3_pll_init_regs[] = {
	{ .reg = CLKCTRL_SYS3PLL_CTRL0, .def = 0x20011086 },
	{ .reg = CLKCTRL_SYS3PLL_CTRL0, .def = 0x30011086 },
	{ .reg = CLKCTRL_SYS3PLL_CTRL1, .def = 0x3420500f },
	{ .reg = CLKCTRL_SYS3PLL_CTRL2, .def = 0x00023041 },
	{ .reg = CLKCTRL_SYS3PLL_CTRL3, .def = 0x0, .delay_us = 20 },
	{ .reg = CLKCTRL_SYS3PLL_CTRL0, .def = 0x10011086, .delay_us = 20 },
	{ .reg = CLKCTRL_SYS3PLL_CTRL2, .def = 0x00023001 }
};

struct meson_clk_pll_data t3x_sys3_pll = {
	.name = "sys3",
	.en = {
		.reg = CLKCTRL_SYS3PLL_CTRL0,
		.shift   = 28,
		.width   = 1,
	},
	.m = {
		.reg = CLKCTRL_SYS3PLL_CTRL0,
		.shift   = 0,
		.width   = 8,
	},
	.n = {
		.reg = CLKCTRL_SYS3PLL_CTRL0,
		.shift   = 16,
		.width   = 5,
	},
	.od = {
		.reg = CLKCTRL_SYS3PLL_CTRL0,
		.shift	 = 12,
		.width	 = 3,
	},
	.def_rate = t3x_sys3_pll_default_rate,
	.def_cnt = ARRAY_SIZE(t3x_sys3_pll_default_rate),
	.table = t3x_sys3_pll_table,
	.init_regs = t3x_sys3_pll_init_regs,
	.init_count = ARRAY_SIZE(t3x_sys3_pll_init_regs),
	.l = {
		.reg = CLKCTRL_SYS3PLL_CTRL0,
		.shift   = 31,
		.width   = 1,
	},
	.rst = {
		.reg = CLKCTRL_SYS3PLL_CTRL0,
		.shift   = 29,
		.width   = 1,
	},
	.ops = &(const struct meson_pll_test_ops) {
		.pll_prepare = t3x_sys3_pll_prepare,
		.pll_unprepare = t3x_sys3_pll_unprepare,
		.pll_disable = meson_secure_pll_disable,
		.pll_set_rate = meson_secure_pll_set_rate,
		.pll_set_parm_rate = meson_secure_pll_set_parm_rate,
		.pll_rate_to_msr = meson_div16_to_msr,
	},
	.smc_id = SECURE_PLL_CLK,
	.secid_disable = SECID_SYS3_DCO_PLL_DIS,
	.secid_test = SECID_PLL_TEST,
	.secid = SECID_SYS3_DCO_PLL,
	.clkmsr_id = 23,
	.clkmsr_margin = 10
};

static const struct pll_params_table t3x_sys2_pll_table[] = {
	PLL_PARAMS(67, 1, 0), /*DCO=1608M OD=1608M */
	PLL_PARAMS(126, 1, 1), /*DCO=3024M OD=1512M */
	{ /* sentinel */ }
};

static unsigned int t3x_sys2_pll_default_rate[] = { 1512, 1608 };

static const struct reg_sequence t3x_sys2_pll_init_regs[] = {
	{ .reg = CLKCTRL_SYS2PLL_CTRL0, .def = 0x20011086 },
	{ .reg = CLKCTRL_SYS2PLL_CTRL0, .def = 0x30011086 },
	{ .reg = CLKCTRL_SYS2PLL_CTRL1, .def = 0x3420500f },
	{ .reg = CLKCTRL_SYS2PLL_CTRL2, .def = 0x00023041 },
	{ .reg = CLKCTRL_SYS2PLL_CTRL3, .def = 0x0, .delay_us = 20 },
	{ .reg = CLKCTRL_SYS2PLL_CTRL0, .def = 0x10011086, .delay_us = 20 },
	{ .reg = CLKCTRL_SYS2PLL_CTRL2, .def = 0x00023001 }
};

struct meson_clk_pll_data t3x_sys2_pll = {
	.name = "sys2",
	.en = {
		.reg = CLKCTRL_SYS2PLL_CTRL0,
		.shift   = 28,
		.width   = 1,
	},
	.m = {
		.reg = CLKCTRL_SYS2PLL_CTRL0,
		.shift   = 0,
		.width   = 8,
	},
	.n = {
		.reg = CLKCTRL_SYS2PLL_CTRL0,
		.shift   = 16,
		.width   = 5,
	},
	.od = {
		.reg = CLKCTRL_SYS2PLL_CTRL0,
		.shift	 = 12,
		.width	 = 3,
	},
	.def_rate = t3x_sys2_pll_default_rate,
	.def_cnt = ARRAY_SIZE(t3x_sys2_pll_default_rate),
	.table = t3x_sys2_pll_table,
	.init_regs = t3x_sys2_pll_init_regs,
	.init_count = ARRAY_SIZE(t3x_sys2_pll_init_regs),
	.l = {
		.reg = CLKCTRL_SYS2PLL_CTRL0,
		.shift   = 31,
		.width   = 1,
	},
	.rst = {
		.reg = CLKCTRL_SYS3PLL_CTRL0,
		.shift   = 29,
		.width   = 1,
	},
	.ops = &(const struct meson_pll_test_ops) {
		.pll_set_rate = meson_secure_pll_set_rate,
		.pll_set_parm_rate = meson_secure_pll_set_parm_rate,
	},
	.smc_id = SECURE_PLL_CLK,
	.secid_disable = SECID_SYS2_DCO_PLL_DIS,
	.secid_test = SECID_PLL_TEST,
	.secid = SECID_SYS2_DCO_PLL,
	.clkmsr_id = 22,
	.clkmsr_margin = 2
};

static unsigned int t3x_gp0_pll_default_rate[] = {375, 750};

/* set the od = 2, clkmsr can not measure 6000M */
static const struct pll_params_table t3x_gp0_pll_table[] = {
	PLL_PARAMS(126, 1, 1), /* DCO = 3024M  OD = 1152M for restore */
	PLL_PARAMS(125, 1, 2), /* DCO = 3000M  OD = 750M */
	PLL_PARAMS(125, 1, 3), /* DCO = 3000M  OD = 375M */
	{ /* sentinel */  }
};

static const struct reg_sequence t3x_gp0_init_regs[] = {
	{ .reg = CLKCTRL_GP0PLL_CTRL0,  .def = 0x20010460 },
	{ .reg = CLKCTRL_GP0PLL_CTRL0,  .def = 0x30010460 },
	{ .reg = CLKCTRL_GP0PLL_CTRL1,  .def = 0x03a00000 },
	{ .reg = CLKCTRL_GP0PLL_CTRL2,  .def = 0x00040000 },
	{ .reg = CLKCTRL_GP0PLL_CTRL3,  .def = 0x090da000, .delay_us = 20 },
	{ .reg = CLKCTRL_GP0PLL_CTRL0,  .def = 0x10010460, .delay_us = 20 },
	{ .reg = CLKCTRL_GP0PLL_CTRL3,  .def = 0x090da200 },
};

struct meson_clk_pll_data t3x_gp0_pll = {
	.name = "gp0",
	.en = {
		.reg = CLKCTRL_GP0PLL_CTRL0,
		.shift   = 28,
		.width   = 1,
	},
	.m = {
		.reg = CLKCTRL_GP0PLL_CTRL0,
		.shift   = 0,
		.width   = 9,
	},
	.n = {
		.reg = CLKCTRL_GP0PLL_CTRL0,
		.shift   = 16,
		.width   = 5,
	},
	.od = {
		.reg = CLKCTRL_GP0PLL_CTRL0,
		.shift	 = 10,
		.width	 = 3,
	},
	.def_rate = t3x_gp0_pll_default_rate,
	.def_cnt = ARRAY_SIZE(t3x_gp0_pll_default_rate),
	.table = t3x_gp0_pll_table,
	.init_regs = t3x_gp0_init_regs,
	.init_count = ARRAY_SIZE(t3x_gp0_init_regs),
	.l = {
		.reg = CLKCTRL_GP0PLL_CTRL0,
		.shift   = 31,
		.width   = 1,
	},
	.rst = {
		.reg = CLKCTRL_GP0PLL_CTRL0,
		.shift   = 29,
		.width   = 1,
	},
	.ops = &(const struct meson_pll_test_ops) {
		.pll_prepare = meson_pll_store_rate,
		.pll_unprepare = meson_pll_restore_rate,
	},
	.clkmsr_id = 20,
	.clkmsr_margin = 2
};

static const struct reg_sequence t3x_gp1_init_regs[] = {
	{ .reg = CLKCTRL_GP1PLL_CTRL0,  .def = 0x20010460 },
	{ .reg = CLKCTRL_GP1PLL_CTRL0,  .def = 0x30010460 },
	{ .reg = CLKCTRL_GP1PLL_CTRL1,  .def = 0x03a00000 },
	{ .reg = CLKCTRL_GP1PLL_CTRL2,  .def = 0x00040000 },
	{ .reg = CLKCTRL_GP1PLL_CTRL3,  .def = 0x090da000, .delay_us = 20 },
	{ .reg = CLKCTRL_GP1PLL_CTRL0,  .def = 0x10010460, .delay_us = 20 },
	{ .reg = CLKCTRL_GP1PLL_CTRL3,  .def = 0x090da200 },
};

struct meson_clk_pll_data t3x_gp1_pll = {
	.name = "gp1",
	.en = {
		.reg = CLKCTRL_GP1PLL_CTRL0,
		.shift   = 28,
		.width   = 1,
	},
	.m = {
		.reg = CLKCTRL_GP1PLL_CTRL0,
		.shift   = 0,
		.width   = 9,
	},
	.n = {
		.reg = CLKCTRL_GP1PLL_CTRL0,
		.shift   = 16,
		.width   = 5,
	},
	.od = {
		.reg = CLKCTRL_GP1PLL_CTRL0,
		.shift	 = 10,
		.width	 = 3,
	},
	.def_rate = t3x_gp0_pll_default_rate,
	.def_cnt = ARRAY_SIZE(t3x_gp0_pll_default_rate),
	.table = t3x_gp0_pll_table,
	.init_regs = t3x_gp1_init_regs,
	.init_count = ARRAY_SIZE(t3x_gp1_init_regs),
	.l = {
		.reg = CLKCTRL_GP1PLL_CTRL0,
		.shift   = 31,
		.width   = 1,
	},
	.rst = {
		.reg = CLKCTRL_GP1PLL_CTRL0,
		.shift   = 29,
		.width   = 1,
	},
	.ops = &(const struct meson_pll_test_ops) {
		.pll_prepare = meson_pll_store_rate,
		.pll_unprepare = meson_pll_restore_rate,
	},
	.clkmsr_id = 21,
	.clkmsr_margin = 2
};

static const struct pll_params_table t3x_hifi_pll_table[] = {
	PLL_PARAMS(126, 1, 1), /* DCO = 3024M  PLL = 1512M */
	PLL_PARAMS(67, 1, 0), /* DCO = 1608M  PLL = 1608M */
	{ /* sentinel */  }
};

static unsigned int t3x_hifi_pll_default_rate[] = {1512, 1608};

static const struct reg_sequence t3x_hifi_init_regs[] = {
	{ .reg = CLKCTRL_HIFIPLL_CTRL0, .def = 0x20010460 },
	{ .reg = CLKCTRL_HIFIPLL_CTRL0, .def = 0x30010460 },
	{ .reg = CLKCTRL_HIFIPLL_CTRL1,	.def = 0x03a00000 },
	{ .reg = CLKCTRL_HIFIPLL_CTRL2,	.def = 0x00040000 },
	{ .reg = CLKCTRL_HIFIPLL_CTRL3,	.def = 0x090da000, .delay_us = 20 },
	{ .reg = CLKCTRL_HIFIPLL_CTRL0, .def = 0x10010460, .delay_us = 20 },
	{ .reg = CLKCTRL_HIFIPLL_CTRL3, .def = 0x090da200 },
};

struct meson_clk_pll_data t3x_hifi_pll = {
	.name = "hifi",
	.en = {
		.reg = CLKCTRL_HIFIPLL_CTRL0,
		.shift   = 28,
		.width   = 1,
	},
	.m = {
		.reg = CLKCTRL_HIFIPLL_CTRL0,
		.shift   = 0,
		.width   = 8,
	},
	.n = {
		.reg = CLKCTRL_HIFIPLL_CTRL0,
		.shift   = 16,
		.width   = 5,
	},
	.od = {
		.reg = CLKCTRL_HIFIPLL_CTRL0,
		.shift	 = 10,
		.width	 = 3,
	},
	.def_rate = t3x_hifi_pll_default_rate,
	.def_cnt = ARRAY_SIZE(t3x_hifi_pll_default_rate),
	.table = t3x_hifi_pll_table,
	.init_regs = t3x_hifi_init_regs,
	.init_count = ARRAY_SIZE(t3x_hifi_init_regs),
	.l = {
		.reg = CLKCTRL_HIFIPLL_CTRL0,
		.shift   = 31,
		.width   = 1,
	},
	.rst = {
		.reg = CLKCTRL_HIFIPLL_CTRL0,
		.shift   = 29,
		.width   = 1,
	},
	.ops = &(const struct meson_pll_test_ops) {
		.pll_prepare = meson_pll_store_rate,
		.pll_unprepare = meson_pll_restore_rate,
	},
	.clkmsr_id = 19,
	.clkmsr_margin = 2
};

static const struct reg_sequence t3x_hifi1_init_regs[] = {
	{ .reg = CLKCTRL_HIFI1PLL_CTRL0, .def = 0x20010460 },
	{ .reg = CLKCTRL_HIFI1PLL_CTRL0, .def = 0x30010460 },
	{ .reg = CLKCTRL_HIFI1PLL_CTRL1, .def = 0x03a00000 },
	{ .reg = CLKCTRL_HIFI1PLL_CTRL2, .def = 0x00040000 },
	{ .reg = CLKCTRL_HIFI1PLL_CTRL3, .def = 0x090da000, .delay_us = 20 },
	{ .reg = CLKCTRL_HIFI1PLL_CTRL0, .def = 0x10010460, .delay_us = 20 },
	{ .reg = CLKCTRL_HIFI1PLL_CTRL3, .def = 0x090da200 },
};

struct meson_clk_pll_data t3x_hifi1_pll = {
	.name = "hifi1",
	.en = {
		.reg = CLKCTRL_HIFI1PLL_CTRL0,
		.shift   = 28,
		.width   = 1,
	},
	.m = {
		.reg = CLKCTRL_HIFI1PLL_CTRL0,
		.shift   = 0,
		.width   = 8,
	},
	.n = {
		.reg = CLKCTRL_HIFI1PLL_CTRL0,
		.shift   = 16,
		.width   = 5,
	},
	.od = {
		.reg = CLKCTRL_HIFI1PLL_CTRL0,
		.shift	 = 10,
		.width	 = 3,
	},
	.def_rate = t3x_hifi_pll_default_rate,
	.def_cnt = ARRAY_SIZE(t3x_hifi_pll_default_rate),
	.table = t3x_hifi_pll_table,
	.init_regs = t3x_hifi1_init_regs,
	.init_count = ARRAY_SIZE(t3x_hifi_init_regs),
	.l = {
		.reg = CLKCTRL_HIFI1PLL_CTRL0,
		.shift   = 31,
		.width   = 1,
	},
	.rst = {
		.reg = CLKCTRL_HIFI1PLL_CTRL0,
		.shift   = 29,
		.width   = 1,
	},
	.ops = &(const struct meson_pll_test_ops) {
		.pll_prepare = meson_pll_store_rate,
		.pll_unprepare = meson_pll_restore_rate,
	},
	.clkmsr_id = 44,
	.clkmsr_margin = 2
};

/* pcie pll = dco/n/2 */
unsigned long meson_pcie_pll_recalc_rate(struct meson_clk_pll_data *pll)
{
	u8 n = (readl(ANACTRL_PCIEPLL_CTRL0) >> 16) & 0x1f;
	u8 m = (readl(ANACTRL_PCIEPLL_CTRL0) >> 8) & 0xff;

	return ((24000000 * m) / n) >> 1;
}

static unsigned int t3x_pcie_default_rate[] = {100};

static const struct reg_sequence t3x_pcie_init_regs[] = {
	{ .reg = CLKCTRL_PCIEPLL_CTRL0, .def = 0x000f7d06 },
	{ .reg = CLKCTRL_PCIEPLL_CTRL1, .def = 0xf0002dd3 },
	{ .reg = CLKCTRL_PCIEPLL_CTRL2, .def = 0x55813041, .delay_us = 20 },
	{ .reg = CLKCTRL_PCIEPLL_CTRL0, .def = 0x000f7d07, .delay_us = 20 },
	{ .reg = CLKCTRL_PCIEPLL_CTRL0, .def = 0x000f7d01, .delay_us = 20 },
	{ .reg = CLKCTRL_PCIEPLL_CTRL3, .def = 0x000300e1 }
};

struct meson_clk_pll_data t3x_pcie_pll = {
	.name = "pcie",
	.en = {
		.reg = CLKCTRL_PCIEPLL_CTRL0,
		.shift   = 28,
		.width   = 1,
	},
	.m = {
		.reg = CLKCTRL_PCIEPLL_CTRL0,
		.shift   = 8,
		.width   = 8,
	},
	.n = {
		.reg = CLKCTRL_PCIEPLL_CTRL0,
		.shift   = 16,
		.width   = 5,
	},
	.def_rate = t3x_pcie_default_rate,
	.def_cnt = ARRAY_SIZE(t3x_pcie_default_rate),
	.init_regs = t3x_pcie_init_regs,
	.init_count = ARRAY_SIZE(t3x_pcie_init_regs),
	.l = {
		.reg = CLKCTRL_PCIEPLL_CTRL0,
		.shift   = 31,
		.width   = 1,
	},
	.ops = &(const struct meson_pll_test_ops) {
		//.pll_prepare = meson_pll_store_rate,
		//.pll_unprepare = meson_pll_restore_rate,
		.pll_recalc = meson_pcie_pll_recalc_rate,
		.pll_set_rate = meson_pll_set_one_rate,
	},
	.clkmsr_id = 25,
	.clkmsr_margin = 2
};

struct meson_clk_pll_data *t3x_pll_list[] = {
	&t3x_sys0_pll,
	&t3x_sys1_pll,
	&t3x_sys3_pll,
	&t3x_sys2_pll,
	&t3x_gp0_pll,
	&t3x_gp1_pll,
	&t3x_hifi_pll,
	&t3x_hifi1_pll,
	&t3x_pcie_pll
};

void t3x_meson_plls_all_test(void)
{
	for (int i = 0; i < ARRAY_SIZE(t3x_pll_list); i++)
		meson_pll_test(t3x_pll_list[i]);
}

void t3x_meson_hdmirx_plls_test(int argc, char * const argv[])
{
	/* todo: need add hdmirx plls test */
}

void t3x_meson_tcon_plls_test(int argc, char * const argv[])
{
	/* todo: need add tcon plls test */
}

void t3x_meson_plls_test(int argc, char * const argv[])
{
	struct meson_clk_pll_data *pll;

	pll = meson_pll_find_by_name(t3x_pll_list, ARRAY_SIZE(t3x_pll_list), argv[1]);
	if (!pll) {
		printf("The pll is not supported Or wrong pll name\n");
		return;
	}

	if ((argc - 2) == pll->init_count)
		meson_pll_parm_test(pll, argv);
	else if (argc == 2)
		meson_pll_test(pll);
	else
		printf("The pll cmd argc is error!\n");

	return;
}

int pll_test(int argc, char * const argv[])
{
	if (!strcmp("all", argv[1]))
		t3x_meson_plls_all_test();
	else if (!strcmp("tcon", argv[1]))
		t3x_meson_tcon_plls_test(argc, argv);
	else if (!strcmp("hdmirx", argv[1]))
		t3x_meson_hdmirx_plls_test(argc, argv);
	else
		t3x_meson_plls_test(argc, argv);

	return 0;
}
