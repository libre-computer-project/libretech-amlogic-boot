/*
 * Copyright (c) 2021-2022 Amlogic, Inc. All rights reserved.
 *
 * SPDX-License-Identifier: MIT
 */

#ifdef P_REGISTER_H
#else
#define P_REGISTER_H

//#include "p_dos_register.h"

//
// Reading file:  ./REG_LIST_RTL.h
//
// synopsys translate_off
// synopsys translate_on
//
//
// Reading file:  ../mmc_lp4/dmc_clk_freq/rtl/dmc_clk_freq.vh
//
//`ifdef DMC_FREQ_REG_DEFINE
//`else
//`define DMC_FREQ_REG_DEFINE
// -----------------------------------------------
// REG_BASE:  APB1_BASE_ADDR = 0xfe036c00
// -----------------------------------------------
//`define DMC_FREQ_REG_BASE      32'hfe036c00
#define P_AM_DDR_PLL_CNTL0 ((volatile uint32_t *)0xfe036c00)
// bit 29    : dpll_reset.
// bit 28    : dpll_en.
// bit 27:26 : dpll_clk_en
// bit 25    : dpll_inv_sel
// bit 21:19 : od1  OD1[0] : 0 /2,  1: /4.   OD1[2:1].  2'b00: /1, 2'b01: /2. 2'b10 /4. 2'b11: /8.
// bit 18:16 : od
// bit 14:10 : dpll_ref_div_n
// bit 8:0   : dpll_int_num
#define P_AM_DDR_PLL_CNTL1 ((volatile uint32_t *)0xfe036c04)
// bit 18:0    : ddr_dpll_frac
#define P_AM_DDR_PLL_CNTL2 ((volatile uint32_t *)0xfe036c08)
// bit 22:20  : fref_sel
// bit 17:16  : os_ssc
// bit 15:12  : ssc_str_m
// bit 8      : ssc_en
// bit 7:4    : ssc_dep_sel
// bit 1:0    : dpll ss_mode.
#define P_AM_DDR_PLL_CNTL3 ((volatile uint32_t *)0xfe036c0c)
// bit 31     : afc bypass
// bit 30     : afc clk sel
// bit 29     : code new
// bit 28     : dco_m_en
// bit 27     : dco_sdm_en
// bit 26     : div2
// bit 25     : div mode
// bit 24     : fast_lock mode
// bit 23     : fb_pre_div
// bit 22     : filter_mode
// bit 21     : fix_en
// bit 20     : freq_shift_en
// bit 19     : load
// bit 18     : load_en
// bit 17     : lock_f
// bit 16     : pulse_width_en
// bit 15     : sdmnc_en
// bit 14     : sdmnc_mode
// bit 13     : sdmnc_range
// bit 12     : tdc_en
// bit 11     : tdc_mode_sel
// bit 10     :  wait_en
#define P_AM_DDR_PLL_CNTL4 ((volatile uint32_t *)0xfe036c10)
// bit 1:0    : pfd_gain
// bit 7:4    : filter_pvt1
// bit 11:8   : filter pvt2
// bit 13:12  : acq_gain
// bit 18:16  : lambda0
// bit 22:20  : lambda1
// bit 26:24  : rou
// bit 30:28  : alpha
#define P_AM_DDR_PLL_CNTL5 ((volatile uint32_t *)0xfe036c14)
// bit 15:0   : reve
// bit 21:16  : lm_s
// bit 27:24  : lm_w
// bit 30:28  : adj_vco_ldo
#define P_AM_DDR_PLL_CNTL6 ((volatile uint32_t *)0xfe036c18)
// bit 15:0   : reve
// bit 21:16  : lm_s
// bit 27:24  : lm_w
// bit 30:28  : adj_vco_ldo
#define P_AM_DDR_PLL_STS ((volatile uint32_t *)0xfe036c1c)
// bit 31     : DDR_PLL_LOCK
// bit 30:19  : not used.
// bit 18     : DDR_AFC_DONE
// bit 17     : DDR_PLL_LOCK
// bit 16:7   : DDR_DPLL_OUT_RSV
// bit 6:0    : DDR_SDMNC_MONITOR
#define P_DDR_CLK_CNTL ((volatile uint32_t *)0xfe036c20)
// bit 31     ddr_pll_clk enable. enable the clock from DDR_PLL to clock generateion.
// whenever change the DDR_PLL frequency, disable the clock, after the DDR_PLL locked, then enable
// it again.
// bit 30.    ddr_pll_prod_test_en.  enable the clock to clock/32 which to clock frequency
// measurement and production test pin. bit 29.    not used. bit 28.    clock generation logic soft
// reset. 0 = reset. bit 27.    phy_4xclk phase inverter.. bit 25.    DDRPHY DfiClk/DMC clock
// selection.  1:  AM_PLL clk output /2.  0: directly output from AM_PLL . bit 24.    enable AM_PLL
// CLK output /2 function.   1: enable.  0: disable.   if try to use this clkoutput/2 function.
// bit 26.    pll_freq divide/2. 1:  use pll div/2 clock as the n_clk. 0: use pll clock as n_clk.
// this setting is used for the synopsys DDR PHY PLL fast lock mode. bit 16.   enable DMC at speed
// mbist mode. bit 2. enable dmc_clk. bit 1. not used. bit 0. enable LPDDR4-PHY clock
#define P_DDR_PHY_CTRL ((volatile uint32_t *)0xfe036c24)
// LPDDR4 power on reset need to special combination of PwrOkIn and phy_reset_n.
// bit 31:  DDr PHY power on status.  read only.
// bit 4.   DDR PHY PwrOkIn pin.
// bit 1.   DDR PHY APB soft reset_n.
// bit 0.   phy_reset_n.
#define P_AM_DDR_PLL_FREQ1_OD ((volatile uint32_t *)0xfe036c30)
// freqency set 1 PLL OD and OD1 setting. when change to freqency 1 will use this setting.
// frequency set 0 use original DDR_PLL_CNTL0 setting.
// bit 8     currunt FREQ selection.  it can forced to change to select which freqency to select,
// or it can auto changed by FREQ change hardware. bit 5:3   OD1. bit 2:0.  OD. `endif
//
// Closing file:  ../mmc_lp4/dmc_clk_freq/rtl/dmc_clk_freq.vh
//
//
// Reading file:  ../mmc_lp4/dmc/rtl/dmc_reg.vh
//
//`define DMC_REG_BASE      32'hfe036000
// -----------------------------------------------
// REG_BASE:  APB1_BASE_ADDR = 0xfe036000
// -----------------------------------------------
#define P_DMC_REQ_CTRL ((volatile uint32_t *)0xfe036000)
// bit 31~8.  Not used.
// bit 7.   enable dmc request of axibus chan 7.  DEV0.( Audio eth_top, SPICCx2).
// bit 6.   enable dmc request of axibus chan 6.  DEV1 ( EMMC, SDIO, SEC_TOP USB2).
// bit 5.   enable dmc request of axibus chan 5.  reserved for dmc_test.
// bit 4.   enable dmc request of axibus chan 4.  DSP
// bit 3.   enable dmc request of axibus chan 3.  NNA
// bit 2.   enable dmc request of axibus chan 2.  not used.
// bit 1.   enable dmc request of axibus chan 1.  Not used.
// bit 0.   enable dmc request of axibus chan 0.  CPU/A53   async interface.
// DMC CLK and RESET domain register. please check DMC_SEC_APB_CTRLx register for access details.
#define P_DMC_SOFT_RST ((volatile uint32_t *)0xfe036004)
// bit 31~8. reserved for future.
// bit 7:0. 8 AXI BUS input intefaces n_clk domain reset_n signal. 0: reset. 1: normal working
// mode. each bit for one interface.
#define P_DMC_SOFT_RST1 ((volatile uint32_t *)0xfe036008)
// To reset the Async interface, you need to disable the interface both clock domain, then reset
// both n_clk and m_clk domain bit 31~8 not used. bit 7:0.  8 AXI bus interfaces master clock
// domain reset_n signal. 0 : reset : 1 normal working mode.
#define P_DMC_SOFT_RST2 ((volatile uint32_t *)0xfe03600c)
// bit 31~11.  reserved for future.
// bit 10  DMC DFI cmd soft reset_n
// bit 9   DMC DFI MISC soft reset_n
// bit 8   DMC DFI data soft reset_n
// bit 7   DMC DFI dcu soft reset_n
// bit 6   DMC siu soft reset_n
// bit 5.  DMC test soft reset_n.  0 : reset. 1 : normal working mode.
// bit 4.  DMC low power control moudle soft reset_n.    0 : reset. 1 : normal working mode.
// bit 3.  DMC QOS monitor module soft reset_n.   0 : reset. 1 : normal working mode.
// bit 2.  DMC register modle soft reset_n.       0 : reset. 1 : normal working mode.
// bit 1.  DMC canvas transfer module soft reset_n.  0 : reset. 1 : normal working mode.
// bit 0.  DMC command buffers and command generation modules soft reset.  0 = reset. 1:
#define P_DMC_RST_STS1 ((volatile uint32_t *)0xfe036010)
// 31~24.  not used.
// 23~0.   Read only.  the DMC_SOFT_RST1 signal in n_clk domain. the purpose of this register is
// when one of the 2 clocks is too slow or too fast,  we can read this register to make sure
// another clock domain reset is done.
#define P_DMC_CLKG_CTRL0 ((volatile uint32_t *)0xfe036018)
// bit 23:16. enable the 8 ambus interfaces both main and n_clk auto clock gating function. each 1
// bit for one interface. bit 15:0.  enable the 16 axi interfaces both main and n_clk auto clock
// gating function. each 1 bit for one interface.
#define P_DMC_CLKG_CTRL1 ((volatile uint32_t *)0xfe03601c)
// bit 23:16. force to disable the 8 ambus interfaces both main and n_clk. each 1 bit for one
// interface. bit 15:0.  force to disable the 16 axi interfaces both main and n_clk. each 1 bit for
// one interface.
#define P_DMC_CLKG_CTRL2 ((volatile uint32_t *)0xfe036020)
// bit 12  enalbe auto clock gating for awcmdfifo.
// bit 11  enalbe auto clock gating for arcmdfifo.
// bit 10  enable auto clock gating for dfi command generation
// bit 9   enable auto clock gating for dram cntroller
// bit 8   enable auto clock gating for dfi data path.
// bit 7.  enalbe auto clock gating for write rsp generation.
// bit 6.  enalbe auto clock gating for read rsp generation.
// bit 5.  enalbe auto clock gating for ddr0 command filter.
// bit 4.  enalbe auto clock gating for ddr0 write reorder buffer.
// bit 3.  enalbe auto clock gating for ddr0 write data buffer.
// bit 2.  enalbe auto clock gating for ddr0 read reorder buffer.
// bit 1.  enalbe auto clock gating for read canvas.
// bit 0.  enalbe auto clock gating for write canvas.
#define P_DMC_CLKG_CTRL3 ((volatile uint32_t *)0xfe036024)
// bit 12  force to disable the clock of awcmdfifo.
// bit 11  force to disable the clock of arcmdfifo.
// bit 10  force to disable the clock of dfi command generation
// bit 9   force to disable the clock of dram cntroller
// bit 8   force to disable the clock of dfi data path.
// bit 7. force to disalbe the clock of write rsp generation.
// bit 6. force to disalbe the clock of read rsp generation.
// bit 5.  force to disalbe the clock of  command filter.
// bit 4.  force to disalbe the clock of  write reorder buffer.
// bit 3.  force to disalbe the clock of write data buffer.
// bit 2.  force to disalbe the clock of read reorder buffer.
// bit 1.  force to disalbe the clock of read canvas.
// bit 0.  force to disalbe the clock of write canvas.
#define P_DMC_MON_CTRL0 ((volatile uint32_t *)0xfe036080)
// bit 31.   qos_mon_en.    write 1 to trigger the enable. polling this bit 0, means finished.  or
// use interrupt to check finish. bit 30.   qos_mon interrupt clear.  clear the qos monitor result.
// read 1 = qos mon finish interrupt. bit 7.    BW monitor 3 enable. bit 6.    BW monitor 3 enable.
// bit 5.    BW monitor 3 enable.
// bit 4.    BW monitor 3 enable.
// bit 3.    BW monitor 3 enable.
// bit 2.    BW monitor 2 enable.
// bit 1.    BW monitor 1 enable.
// bit 0.    BW monitor 0 enable.
#define P_DMC_MON_TIMER ((volatile uint32_t *)0xfe036084)
// timer for the monitor period.
#define P_DMC_MON_ALL_IDLE_CNT ((volatile uint32_t *)0xfe036088)
// at the test period,  the whole MMC all channel IDLE time. unit, dmc clock.
#define P_DMC_MON_ALL_BW ((volatile uint32_t *)0xfe03608c)
// at the test period,  the whole MMC granted data cycles. 64bits unit.
#define P_DMC_MON_ALL16_BW ((volatile uint32_t *)0xfe036090)
// at the test period,  the whole MMC granted data cycles which goes to 16bits ddr. unit:64bits
#define P_DMC_MON0_CTRL ((volatile uint32_t *)0xfe036094)
// BW MONTIOR 0 address range ctrol.  start addrss <= AXI address[31:16] <= end address
// bit 31:16  End address[31:16]
// bit 15:0.  start address[31:16]
#define P_DMC_MON0_CTRL1 ((volatile uint32_t *)0xfe036098)
// bit 23:0.  BW monitor 0 channel select.   8 ambus port and 16 AXI port selection. 1 bit for one
// port.
// if only 1 channel selected, you can use DMC_MONx_CTRL2 to chose any subid of this selected
// channel. otherwise DMC_MONx_CTRL2 should be set 0xffff
#define P_DMC_MON0_CTRL2 ((volatile uint32_t *)0xfe03609c)
// bit 15:0.  BW monitor 0 port select for the selected channel.
#define P_DMC_MON0_BW ((volatile uint32_t *)0xfe0360a0)
// at the test period, this range granted data cycles for the seletec channel and ports.
#define P_DMC_MON1_CTRL ((volatile uint32_t *)0xfe0360a4)
// BW monitor 1 address range ctrol.  start addrss <= AXI address[31:16] <= end address
// bit 31:16  End address[31:16]
// bit 15:0.  start address[31:16]
#define P_DMC_MON1_CTRL1 ((volatile uint32_t *)0xfe0360a8)
// bit 23:0.  BW monitor 1 channel select.   8 ambus port and 16 AXI port selection. 1 bit for one
// port.
// if only 1 channel selected, you can use DMC_MONx_CTRL2 to chose any subid of this selected
// channel. otherwise DMC_MONx_CTRL2 should be set 0xffff
#define P_DMC_MON1_CTRL2 ((volatile uint32_t *)0xfe0360ac)
// bit 15:0.  BW monitor 1 port select for the selected channel.
#define P_DMC_MON1_BW ((volatile uint32_t *)0xfe0360b0)
// at the test period, this range granted data cycles for the seletec channel and ports.
#define P_DMC_MON2_CTRL ((volatile uint32_t *)0xfe0360b4)
// BW monitor 2 address range ctrol.  start addrss <= AXI address[31:16] <= end address
// bit 31:16  End address[31:16]
// bit 15:0.  start address[31:16]
#define P_DMC_MON2_CTRL1 ((volatile uint32_t *)0xfe0360b8)
// bit 23:0.  BW monitor 2 channel select.   8 ambus port and 16 AXI port selection. 1 bit for one
// port.
// if only 1 channel selected, you can use DMC_MONx_CTRL2 to chose any subid of this selected
// channel. otherwise DMC_MONx_CTRL2 should be set 0xffff
#define P_DMC_MON2_CTRL2 ((volatile uint32_t *)0xfe0360bc)
// bit 15:0.  BW monitor 2 port select for the selected channel.
#define P_DMC_MON2_BW ((volatile uint32_t *)0xfe0360c0)
// at the test period, this range granted data cycles for the seletec channel and ports.
#define P_DMC_MON3_CTRL ((volatile uint32_t *)0xfe0360c4)
// BW monitor 3 address range ctrol.  start addrss <= AXI address[31:16] <= end address
// bit 31:16  End address[31:16]
// bit 15:0.  start address[31:16]
#define P_DMC_MON3_CTRL1 ((volatile uint32_t *)0xfe0360c8)
// bit 23:0.  BW monitor 3 channel select.   8 ambus port and 16 AXI port selection. 1 bit for one
// port.
// if only 1 channel selected, you can use DMC_MONx_CTRL2 to chose any subid of this selected
// channel. otherwise DMC_MONx_CTRL2 should be set 0xffff
#define P_DMC_MON3_CTRL2 ((volatile uint32_t *)0xfe0360cc)
// bit 15:0.  BW monitor 3 port select for the selected channel.
#define P_DMC_MON3_BW ((volatile uint32_t *)0xfe0360d0)
// at the test period, this range granted data cycles for the seletec channel and ports.
#define P_DMC_MON4_CTRL ((volatile uint32_t *)0xfe0360d4)
// BW monitor 4 address range ctrol.  start addrss <= AXI address[31:16] <= end address
// bit 31:16  End address[31:16]
// bit 15:0.  start address[31:16]
#define P_DMC_MON4_CTRL1 ((volatile uint32_t *)0xfe0360d8)
// bit 23:0.  BW monitor 4 channel select.   8 ambus port and 16 AXI port selection. 1 bit for one
// port.
// if only 1 channel selected, you can use DMC_MONx_CTRL2 to chose any subid of this selected
// channel. otherwise DMC_MONx_CTRL2 should be set 0xffff
#define P_DMC_MON4_CTRL2 ((volatile uint32_t *)0xfe0360dc)
// bit 15:0.  BW monitor 4 port select for the selected channel.
#define P_DMC_MON4_BW ((volatile uint32_t *)0xfe0360e0)
// at the test period, this range granted data cycles for the seletec channel and ports.
#define P_DMC_MON5_CTRL ((volatile uint32_t *)0xfe0360e4)
// BW monitor 5 address range ctrol.  start addrss <= AXI address[31:16] <= end address
// bit 31:16  End address[31:16]
// bit 15:0.  start address[31:16]
#define P_DMC_MON5_CTRL1 ((volatile uint32_t *)0xfe0360e8)
// bit 23:0.  BW monitor 5 channel select.   8 ambus port and 16 AXI port selection. 1 bit for one
// port.
// if only 1 channel selected, you can use DMC_MONx_CTRL2 to chose any subid of this selected
// channel. otherwise DMC_MONx_CTRL2 should be set 0xffff
#define P_DMC_MON5_CTRL2 ((volatile uint32_t *)0xfe0360ec)
// bit 15:0.  BW monitor 5 port select for the selected channel.
#define P_DMC_MON5_BW ((volatile uint32_t *)0xfe0360f0)
// at the test period, this range granted data cycles for the seletec channel and ports.
#define P_DMC_MON6_CTRL ((volatile uint32_t *)0xfe0360f4)
// BW monitor 6 address range ctrol.  start addrss <= AXI address[31:16] <= end address
// bit 31:16  End address[31:16]
// bit 15:0.  start address[31:16]
#define P_DMC_MON6_CTRL1 ((volatile uint32_t *)0xfe0360f8)
// bit 23:0.  BW monitor 6 channel select.   8 ambus port and 16 AXI port selection. 1 bit for one
// port.
// if only 1 channel selected, you can use DMC_MONx_CTRL2 to chose any subid of this selected
// channel. otherwise DMC_MONx_CTRL2 should be set 0xffff
#define P_DMC_MON6_CTRL2 ((volatile uint32_t *)0xfe0360fc)
// bit 15:0.  BW monitor 6 port select for the selected channel.
#define P_DMC_MON6_BW ((volatile uint32_t *)0xfe036100)
// at the test period, this range granted data cycles for the seletec channel and ports.
#define P_DMC_MON7_CTRL ((volatile uint32_t *)0xfe036104)
// BW monitor 7 address range ctrol.  start addrss <= AXI address[31:16] <= end address
// bit 31:16  End address[31:16]
// bit 15:0.  start address[31:16]
#define P_DMC_MON7_CTRL1 ((volatile uint32_t *)0xfe036108)
// bit 23:0.  BW monitor 7 channel select.   8 ambus port and 16 AXI port selection. 1 bit for one
// port.
// if only 1 channel selected, you can use DMC_MONx_CTRL2 to chose any subid of this selected
// channel. otherwise DMC_MONx_CTRL2 should be set 0xffff
#define P_DMC_MON7_CTRL2 ((volatile uint32_t *)0xfe03610c)
// bit 15:0.  BW monitor 7 port select for the selected channel.
#define P_DMC_MON7_BW ((volatile uint32_t *)0xfe036110)
// at the test period, this range granted data cycles for the seletec channel and ports.
#define P_DMC_CMD_FILTER_CTRL1 ((volatile uint32_t *)0xfe036140)
// not used.
#define P_DMC_CMD_FILTER_CTRL2 ((volatile uint32_t *)0xfe036144)
// 31:24. keep the bank active if there's urgent level 3 read bank hit request.
// 23:16. keep the bank active if there's urgent level 2 read bank hit request.
// 15:8.  keep the bank active if there's urgent level 1 read bank hit request.
// 7:0.   keep the bank active if there's urgent level 0 read bank hit request.
#define P_DMC_CMD_FILTER_CTRL3 ((volatile uint32_t *)0xfe036148)
// bit 31.    force wbuf empty.
// bit 30:26  wbuf high level number
// bit 25:21  wbuf mid  level number
// bit 20:16  wbuf low level number
// bit 14:10  rbuf high level number
// bit 9:5    rbuf middle level number
// bit 4:0    rbuf low level number
#define P_DMC_CMD_FILTER_CTRL4 ((volatile uint32_t *)0xfe03614c)
// bit 29:25.  tITW.long
// bit 24:20.  tITW. short
// bit 19:12   tAP auto precharge the bank not used if idle that long time.
// bit 11:6    write to read accesses if there write hit request.
// bit 5:0     read to write accesses if there write hit request.
#define P_DMC_CMD_FILTER_CTRL5 ((volatile uint32_t *)0xfe036150)
// bit 31:24   Once ddr data bus switch to read, the maxmum read command number to give up the bus
// when there's write request pending for write buffer. bit 23:16   Once ddr data bus switch to
// write, the maxmum write command number to give up the bus when there's read request pending too
// long. bit 15:8.   Once ddr data bus switch to read, the minimum read command number to transfer
// back to write stage if there's still pending read request. bit 7:0.    Once ddr data bus switch
// to write, the minimum write command number to transfer back to read stage if there's still
// pending write request.
#define P_DMC_CMD_FILTER_CTRL6 ((volatile uint32_t *)0xfe036154)
// bit 31:24   write urgent 3 request pending hold num.
// bit 23:16   write urgent 2 request pending hold num.
// bit 15:8.   write urgent 1 request pending hold num.
// bit 7:0.    write urgent 0 request pending hold num.
#define P_DMC_CMD_FILTER_CTRL7 ((volatile uint32_t *)0xfe036158)
// bit 31:24.  aw_req_pedning signal assertion after wbuf full.
// bit 23:16   aw_req_pending signal hold how long if wbuf not full.
// bit 15:8    write to read waiting cycles if there write hit request.
// bit 7:0     read to write waiting cycles if there write hit request.
#define P_DMC_CMD_FILTER_CTRL8 ((volatile uint32_t *)0xfe03615c)
// bit 31:8    reserved.
// bit 7:0     rank limit to change to another rank.
#define P_DMC_CMD_BUFFER_CTRL ((volatile uint32_t *)0xfe036160)
// bit 31:26  total write buffer number. default 32.
// bit 25:20  total read buffer number. default 32.
// bit 19:8    reserved.
// bit 7:0    aw_pending_inc_num.  incease write ugent level 1 when write command waiting to in
// write buffer that long.
#define P_DMC_CMD_BUFFER_CTRL1 ((volatile uint32_t *)0xfe036164)
// bit 29:24  read buffer number in non-urgent request.
// bit 23:16  read buffer bank miss watch dog threshold.
// bit 15:12  read buffer urgent level 3 counter inc weight.
// bit 11:8   read buffer urgent level 2 counter inc weight.
// bit 7:4    read buffer urgent level 1 counter inc weight.
// bit 3:0    read buffer urgent level 0 counter inc weight.
#define P_DMC_2ARB_CTRL ((volatile uint32_t *)0xfe036170)
// 32:24. Waiting limit to use the highest urgent level in the pipelines.
// 22.    1: allow to increase 2 urgent levels if waiting time is doubled than inc_ugt_limit.
// 21:12  inc_ugt_limit.  if waiting time > inc_ugt_limit, increase the urgent level by one
// 11:6.  the final arbitration control from AXI bus(port channel 0~7).
// 5:0.   the final arbitration weight control for Ambus ( port channel 8~15).
#define P_DMC_VERSION ((volatile uint32_t *)0xfe03617c)
// read only 32'h000a0008  for sc2
#define P_DMC_AXI0_CHAN_CTRL ((volatile uint32_t *)0xfe036200)
// bit 31       enable to incr 2 urgent levels if the pending cycles is doubled.
// bit 30       enable to incr 3 urgent levels.
// bit 29:20.   write request pending cycle number  to inc urgent level if not granted.
// bit 19.      axi0 default urgent control : 1 use AWUGT/ARUGT pins in the port. 0 : use
// bit[15:14] of this register.. bit 18.      force this channel all request to be super urgent
// request. bit 17.      force this channel all request to be urgent request. bit 16.      force
// this channel all request to be non urgent request. bit 15:14    axi0 default urgent level. bit
// 13:4.    read request pending cycle number  to inc urgent level if not granted. bit 3:0 arbiter
// weight
#define P_DMC_AXI0_HOLD_CTRL ((volatile uint32_t *)0xfe036204)
// 31:24 write hold num.   max outstanding request number.
// 23:16  write hold release num. if the outstanding request == hold num, then hold this request
// unless the outstanding request number bellow the hold release number, then continue to request.
// 15:8 read hold num.   max outstanding request number.
// 7:0  read hold release num. if the outstanding request == hold num, then hold this request
// unless the outstanding request number bellow the hold release number, then continue to request.
#define P_DMC_AXI0_CHAN_CTRL1 ((volatile uint32_t *)0xfe036208)
// bit 31:28.  FIQ status
// bit 27:24.  IRQ status.
// bit 22      use ACTIVE input as clock gating control.
// bit 21:20.  chan0 QOS mode.
// bit 19:16.   AXI0 QOS high limit.
// bit 15:12    AXI0 QOS mit limit.
// bit 11  ARM  FIQ controlled super urgent enable.
// bit 10  ARM  FIQ controlled urgent enable.
// bit  9. ARM IRQ controlled super urgent enable.
// bit  8. ARM IRQ controlled urgent enable.
// bit  7.  IRQ/FIQ control enable.
// bit  6:5.  not used.
// bit 4. enable AXI0 auto urgent enable. When there's no other request, treat the AXI0 as super
// urgent request. other wise, use the bit3:0 to set the urgent. bit 3:2 A9 urgent if there's VIU
// request. bit 1:0 A9 urgent if there's request other than VIU
#define P_DMC_AXI1_CHAN_CTRL ((volatile uint32_t *)0xfe036210)
// bit 31       enable to incr 2 urgent levels if the pending cycles is doubled.
// bit 30       enable to incr 3 urgent levels.
// bit 29:20.   write request pending cycle number  to inc urgent level if not granted.
// bit 19.      axi0 default urgent control : 1 use AWUGT/ARUGT pins in the port. 0 : use
// bit[15:14] of this register.. bit 18.      force this channel all request to be super urgent
// request. bit 17.      force this channel all request to be urgent request. bit 16.      force
// this channel all request to be non urgent request. bit 15:14    axi1 default urgent level. bit
// 13:4.    read request pending cycle number  to inc urgent level if not granted. bit 3:0 canvas
// arbiter weight
#define P_DMC_AXI1_HOLD_CTRL ((volatile uint32_t *)0xfe036214)
// 31:24 write hold num.   max outstanding request number.
// 23:16  write hold release num. if the outstanding request == hold num, then hold this request
// unless the outstanding request number bellow the hold release number, then continue to request.
// 15:8 read hold num.   max outstanding request number.
// 7:0  read hold release num. if the outstanding request == hold num, then hold this request
// unless the outstanding request number bellow the hold release number, then continue to request.
#define P_DMC_AXI1_CHAN_CTRL1 ((volatile uint32_t *)0xfe036218)
// bit 31:28.  FIQ status
// bit 27:24.  IRQ status.
// bit 21:20.  Mali QOS mode.
// bit 19:16.   mail QOS high limit.
// bit 15:12    mail QOS mit limit.
// bit 11  ARM  FIQ controlled super urgent enable.
// bit 10  ARM  FIQ controlled urgent enable.
// bit  9. ARM IRQ controlled super urgent enable.
// bit  8. ARM IRQ controlled urgent enable.
// bit  7.  IRQ/FIQ control enable.
// bit  6:0.  not used.
#define P_DMC_AXI2_CHAN_CTRL ((volatile uint32_t *)0xfe036220)
// bit 31       enable to incr 2 urgent levels if the pending cycles is doubled.
// bit 30       enable to incr 3 urgent levels.
// bit 29:20.   write request pending cycle number  to inc urgent level if not granted.
// bit 19.      axi0 default urgent control : 1 use AWUGT/ARUGT pins in the port. 0 : use
// bit[15:14] of this register.. bit 18.      force this channel all request to be super urgent
// request. bit 17.      force this channel all request to be urgent request. bit 16.      force
// this channel all request to be non urgent request. bit 15:14    axi1 default urgent level. bit
// 13:4.    read request pending cycle number  to inc urgent level if not granted. bit 3:0 canvas
// arbiter weight
#define P_DMC_AXI2_HOLD_CTRL ((volatile uint32_t *)0xfe036224)
// 31:24 write hold num.   max outstanding request number.
// 23:16  write hold release num. if the outstanding request == hold num, then hold this request
// unless the outstanding request number bellow the hold release number, then continue to request.
// 15:8 read hold num.   max outstanding request number.
// 7:0  read hold release num. if the outstanding request == hold num, then hold this request
// unless the outstanding request number bellow the hold release number, then continue to request.
#define P_DMC_AXI3_CHAN_CTRL ((volatile uint32_t *)0xfe036230)
// bit 31       enable to incr 2 urgent levels if the pending cycles is doubled.
// bit 30       enable to incr 3 urgent levels.
// bit 29:20.   write request pending cycle number  to inc urgent level if not granted.
// bit 19.      axi0 default urgent control : 1 use AWUGT/ARUGT pins in the port. 0 : use
// bit[15:14] of this register.. bit 18.      force this channel all request to be super urgent
// request. bit 17.      force this channel all request to be urgent request. bit 16.      force
// this channel all request to be non urgent request. bit 15:14    axi1 default urgent level. bit
// 13:4.    read request pending cycle number  to inc urgent level if not granted. bit 3:0 canvas
// arbiter weight
#define P_DMC_AXI3_HOLD_CTRL ((volatile uint32_t *)0xfe036234)
// 31:24 write hold num.   max outstanding request number.
// 23:16  write hold release num. if the outstanding request == hold num, then hold this request
// unless the outstanding request number bellow the hold release number, then continue to request.
// 15:8 read hold num.   max outstanding request number.
// 7:0  read hold release num. if the outstanding request == hold num, then hold this request
// unless the outstanding request number bellow the hold release number, then continue to request.
#define P_DMC_AXI4_CHAN_CTRL ((volatile uint32_t *)0xfe036240)
// bit 31       enable to incr 2 urgent levels if the pending cycles is doubled.
// bit 30       enable to incr 3 urgent levels.
// bit 29:20.   write request pending cycle number  to inc urgent level if not granted.
// bit 19.      axi0 default urgent control : 1 use AWUGT/ARUGT pins in the port. 0 : use
// bit[15:14] of this register.. bit 18.      force this channel all request to be super urgent
// request. bit 17.      force this channel all request to be urgent request. bit 16.      force
// this channel all request to be non urgent request. bit 15:14    axi1 default urgent level. bit
// 13:4.    read request pending cycle number  to inc urgent level if not granted. bit 3:0 canvas
// arbiter weight
#define P_DMC_AXI4_HOLD_CTRL ((volatile uint32_t *)0xfe036244)
// 31:24 write hold num.   max outstanding request number.
// 23:16  write hold release num. if the outstanding request == hold num, then hold this request
// unless the outstanding request number bellow the hold release number, then continue to request.
// 15:8 read hold num.   max outstanding request number.
// 7:0  read hold release num. if the outstanding request == hold num, then hold this request
// unless the outstanding request number bellow the hold release number, then continue to request.
#define P_DMC_AXI5_CHAN_CTRL ((volatile uint32_t *)0xfe036250)
// not used.
#define P_DMC_AXI5_HOLD_CTRL ((volatile uint32_t *)0xfe036254)
// not used.
#define P_DMC_AXI6_CHAN_CTRL ((volatile uint32_t *)0xfe036260)
// bit 31       enable to incr 2 urgent levels if the pending cycles is doubled.
// bit 30       enable to incr 3 urgent levels.
// bit 29:20.   write request pending cycle number  to inc urgent level if not granted.
// bit 19.      axi0 default urgent control : 1 use AWUGT/ARUGT pins in the port. 0 : use
// bit[15:14] of this register.. bit 18.      force this channel all request to be super urgent
// request. bit 17.      force this channel all request to be urgent request. bit 16.      force
// this channel all request to be non urgent request. bit 15:14    axi1 default urgent level. bit
// 13:4.    read request pending cycle number  to inc urgent level if not granted. bit 3:0 canvas
// arbiter weight
#define P_DMC_AXI6_HOLD_CTRL ((volatile uint32_t *)0xfe036264)
// 31:24 write hold num.   max outstanding request number.
// 23:16  write hold release num. if the outstanding request == hold num, then hold this request
// unless the outstanding request number bellow the hold release number, then continue to request.
// 15:8 read hold num.   max outstanding request number.
// 7:0  read hold release num. if the outstanding request == hold num, then hold this request
// unless the outstanding request number bellow the hold release number, then continue to request.
#define P_DMC_AXI7_CHAN_CTRL ((volatile uint32_t *)0xfe036270)
// bit 31       enable to incr 2 urgent levels if the pending cycles is doubled.
// bit 30       enable to incr 3 urgent levels.
// bit 29:20.   write request pending cycle number  to inc urgent level if not granted.
// bit 19.      axi0 default urgent control : 1 use AWUGT/ARUGT pins in the port. 0 : use
// bit[15:14] of this register.. bit 18.      force this channel all request to be super urgent
// request. bit 17.      force this channel all request to be urgent request. bit 16.      force
// this channel all request to be non urgent request. bit 15:14    axi1 default urgent level. bit
// 13:4.    read request pending cycle number  to inc urgent level if not granted. bit 3:0 canvas
// arbiter weight
#define P_DMC_AXI7_HOLD_CTRL ((volatile uint32_t *)0xfe036274)
// 31:24 write hold num.   max outstanding request number.
// 23:16  write hold release num. if the outstanding request == hold num, then hold this request
// unless the outstanding request number bellow the hold release number, then continue to request.
// 15:8 read hold num.   max outstanding request number.
// 7:0  read hold release num. if the outstanding request == hold num, then hold this request
// unless the outstanding request number bellow the hold release number, then continue to request.
#define P_DMC_AXI7_CHAN_CTRL1 ((volatile uint32_t *)0xfe036278)
// bit 0.  wrdata hold mode.  1, after receive enough wrdata, send AWVALID. 0: send AWVALID dont
// wait WRDATA.
#define P_DMC_AXI0_CHAN_STS ((volatile uint32_t *)0xfe036300)
#define P_DMC_AXI1_CHAN_STS ((volatile uint32_t *)0xfe036304)
#define P_DMC_AXI2_CHAN_STS ((volatile uint32_t *)0xfe036308)
#define P_DMC_AXI3_CHAN_STS ((volatile uint32_t *)0xfe03630c)
#define P_DMC_AXI4_CHAN_STS ((volatile uint32_t *)0xfe036310)
#define P_DMC_AXI5_CHAN_STS ((volatile uint32_t *)0xfe036314)
#define P_DMC_AXI6_CHAN_STS ((volatile uint32_t *)0xfe036318)
#define P_DMC_AXI7_CHAN_STS ((volatile uint32_t *)0xfe03631c)
#define P_DMC_CHAN_STS ((volatile uint32_t *)0xfe036338)
// AXI0  is first CPU and Mali conbined channel from CCI-400 directly.  The first 2Gbyte address
// will go through this channel. AXI10  is the second CPU, Mali channel combined with NNA  from
// NIC-400.  The upper 2Gbyte address will go through this channel.
// read only register.
// the second mali and NNA channel IDLE.
// the second CPU channel IDLE.
// the first mali channel IDLE.
// the first CPU channel IDLE.
// bit 27      always 1
// bit 26      ddr0 write data buffer idle. 1 : idle 0: busy.
// bit 25      always 1.
// bit 24      ddr0 wbuf idle.              1 : idle 0: busy.
// bit 23:16   ambus channel idle.          1 : idle 0: busy.
// bit 15:0.   axibus channel idle.         1 : idle 0: busy.
#define P_DMC_IRQ_STS ((volatile uint32_t *)0xfe03633c)
// bit 31:3   Not used.
// bit 2 :    QOS Monitor interrupt flag.  1: means there's QOS monitor interrupt.  write 1 to
// clean this interrupt. bit 1 :    WRITE protection interrupt.  1: means there's write protection
// violation.  need to write DMC_PROT_IRQ_CTRL  bit 1to clean this bit. bit 0 :    read protection
// interrupt.   1: means there's read  protection violation.  need to write DMC_PROT_IRQ_CTRL bit 0
// to clean this bit.
#define P_DMC_PROT0_RANGE ((volatile uint32_t *)0xfe036340)
// protection 0 address range. the range define is 64Kbyte boundary.  current address [31:16] >=
// start address && current address [31:16] <= end address. bit 31:16 :   range end address. bit
// 15:0  :   range start address
#define P_DMC_PROT0_CTRL ((volatile uint32_t *)0xfe036344)
// bit 23:16. each bit to enable one of the 8 ambus channal for the protection function.
// bit 15:0   each bit to enable one of the 15 channel input for the protection function.
#define P_DMC_PROT0_CTRL1 ((volatile uint32_t *)0xfe036348)
// bit 26.  protection 0  read access protection enable.
// bit 25.  protection 0  write access block function. if enabled, the access wouldn't write to
// the DDR SDRAM.  if not enabled only generate a interrupt, but the access still wrote to DDR.
// bit 24.  protection range 0  write access protection enable.
// bit 15:0 for some AXI port subID bits
#define P_DMC_PROT1_RANGE ((volatile uint32_t *)0xfe03634c)
// protection 1 address range. the range define is 64Kbyte boundary.  current address [31:16] >=
// start address && current address [31:16] <= end address. bit 31:16 :   range end address. bit
// 15:0  :   range start address
#define P_DMC_PROT1_CTRL ((volatile uint32_t *)0xfe036350)
// bit 23:16. each bit to enable one of the 8 ambus channal for the protection function.
// bit 15:0   each bit to enable one of the 15 channel input for the protection function.
#define P_DMC_PROT1_CTRL1 ((volatile uint32_t *)0xfe036354)
// bit 26.  protection range 1 read access protection enable bit.
// bit 25.  protection 1  write access block function. if enabled, the access wouldn't write to
// the DDR SDRAM.  if not enabled only generate a interrupt, but the access still wrote to DDR.
// bit 24.  protection range 1 write access protection enable bit.
// bit 15:0 for some AXI port subID bits
#define P_DMC_PROT_VIO_0 ((volatile uint32_t *)0xfe036358)
// ddr0 write proection violation address.
#define P_DMC_PROT_VIO_1 ((volatile uint32_t *)0xfe03635c)
// bit 31:22 . not used. always 0.
// 21.    ddr0 protection 1 vilation.
// 20     ddr0 protection 0 vilation.
// 19:14. ddr0 write violation AWPROT bits. ( 6 bits for write security)
// 13:12.  Not used.
// 11:0    ddr0_write violation ID. bit 11~9 for Master ID. bit 7:4 for subid.
#define P_DMC_PROT_VIO_2 ((volatile uint32_t *)0xfe036360)
// ddr0 read prot violation address
#define P_DMC_PROT_VIO_3 ((volatile uint32_t *)0xfe036364)
// bit 31:21 . not used. always 0.
// 21     ddr0 read protection 1 violation.
// 20     ddr0 read protection 0 violation.
// 19.    not used.
// 18:16. ddr0 read violation ARPROT bits. (3 bits for read secutiry).
// 15:12. not used.
// 11:0   ddr0 read violation ID.   bit 11~9 for master ID. bit 7:4 for subid.
#define P_DMC_PROT_IRQ_CTRL ((volatile uint32_t *)0xfe036368)
// bit 2 :  protect function IRQ enable.
// bit 1 :  write protection violation.  write 1 to clean write protection vio registers.
// bit 0 :  read  protection violation.  write 1 to clean read protection vio registers.
//`define DMC_TEST_REG_BASE                32'hfe037800
// -----------------------------------------------
// REG_BASE:  APB1_BASE_ADDR = 0xfe037800
// -----------------------------------------------
#define P_DMC_TEST_STA ((volatile uint32_t *)0xfe037800)
// test start address.  for non-sha mode,  the last 5 bits would be ignored. the test address at
// 32bytes boundary.
//                     for sha mode,      address must be in 64 bytes boundary. that mean the last
//                     6 bits must be 0.
#define P_DMC_TEST_EDA ((volatile uint32_t *)0xfe037804)
// test end address.  for non-sha mode,  the last 5 bits would be ignored. the test address at
// 32bytes boundary.
//                   for sha mode,       address must be in 64 bytes boundary. that mean the last
//                   6bits must be 1.
#define P_DMC_TEST_CTRL ((volatile uint32_t *)0xfe037808)
// bit 31.  enable test.
// bit 30.  when enable test, enable the write to DDR function.
// bit 29.  when enable test, enable the read from DDR function.
// bit 28.  when enable test,  enable the sha calculation function  must be same as read enable
// but without write function. bit 27.  enabe to compare data.  when do the read enable to enable
// the error comparaion. suppose the read data should be same as the data in the write buffer.
// bit 26.  0: save sha result to test_sha_message registers.  1 : don't save.
// bit 25.  address generation type.  0: continuous increase the address in the range of test
// start address and test end address.
//                                   1: test module would pick the random address from test start
//                                   address  and test end address.
// bit 24.  done type.      0 : use the DMC_TEST_NUM register as the counter of test numbers.
//                             for write if the write command number == the DMC_TEST_NUM, the
//                             write is done. for read if the read command number == the DMC
//                             TEST_num, the read id done. for one read command can be repeated
//                             repeat number times.
//                         1 : finshed at end address.
// bit 23.  wdata type.     1 : the first write is {WD3, WD2,WD1,WD0}, then the latter is the
// previous data plus a pattern.( { + WD7,  + WD6, + WD5, + WD4}).
//                         0 : the WDATA is the data in write register.
// bit 23.  1  compare the sha result with the test sha message registers. 0 : dont compare the
// result. bit 22:20.   read repeat times.  for non-sha function, we can define multi times of the
// read. the test module would repeat the same address repeat times. bit 19.     limit write.  0:
// no outstanding write request limitation.
//                          1: limit the outstanding write commands to the number of bits [15:8]
// bit 18.     limit read.   0. no outstanding read request limitation.
//                          1. limit the read outstanding request to the number of bits[7:0].
// bit 17:16.  sha mode for sha function enabled.  00 : not used.  01 : sha1. 2: sha2-256. 3:
// sha2_224. not used in GXL fixed to be  Sha 2. bit 15:8.   write outstanding commands limit. bit
// 7:0.    read  outstanding commands limit.
#define P_DMC_TEST_NUM ((volatile uint32_t *)0xfe03780c)
// how many test command for the test if the DMC_TEST_CTRL bit 24 is 0.
#define P_DMC_TEST_WDG ((volatile uint32_t *)0xfe037810)
// 31:16.  write response watch dog.
// 15:0.   read response  watch dog.
#define P_DMC_TEST_COMP_MASK ((volatile uint32_t *)0xfe037814)
// 32bits for DMC TEST COMPARE bit enable.
// 1 : to MASK this bit.  0: compare this bit.
#define P_DMC_TEST_WSTRB0 ((volatile uint32_t *)0xfe037818)
// MPC WR FIFO command DM bit write data
// bit 31:16  the second cycle.
// bit 15:0   the first cycle.
#define P_DMC_TEST_WSTRB1 ((volatile uint32_t *)0xfe03781c)
// MPC WR FIFO command DM bit write data
// bit 31:16. the Forth cycle.
// bit 15:0.  the third cycle.
#define P_DMC_TEST_WD0 ((volatile uint32_t *)0xfe037840)
// write data 0 for write command. also for read back data comparision.
#define P_DMC_TEST_WD1 ((volatile uint32_t *)0xfe037844)
// write data 1 for write command. also for read back data comparision.
#define P_DMC_TEST_WD2 ((volatile uint32_t *)0xfe037848)
// write data 2 for write command. also for read back data comparision.
#define P_DMC_TEST_WD3 ((volatile uint32_t *)0xfe03784c)
// write data 3 for write command. also for read back data comparision.
#define P_DMC_TEST_WD4 ((volatile uint32_t *)0xfe037850)
// write data 4 for write command. also for read back data comparision.
#define P_DMC_TEST_WD5 ((volatile uint32_t *)0xfe037854)
// write data 5 for write command. also for read back data comparision.
#define P_DMC_TEST_WD6 ((volatile uint32_t *)0xfe037858)
// write data 6 for write command. also for read back data comparision.
#define P_DMC_TEST_WD7 ((volatile uint32_t *)0xfe03785c)
// write data 7 for write command. also for read back data comparision.
#define P_DMC_TEST_WD8 ((volatile uint32_t *)0xfe037860)
// write data 8 for write command. also for read back data comparision.
#define P_DMC_TEST_WD9 ((volatile uint32_t *)0xfe037864)
// write data 9 for write command. also for read back data comparision.
#define P_DMC_TEST_WD10 ((volatile uint32_t *)0xfe037868)
// write data 10 for write command. also for read back data comparision.
#define P_DMC_TEST_WD11 ((volatile uint32_t *)0xfe03786c)
// write data 11 for write command. also for read back data comparision.
#define P_DMC_TEST_WD12 ((volatile uint32_t *)0xfe037870)
// write data 12 for write command. also for read back data comparision.
#define P_DMC_TEST_WD13 ((volatile uint32_t *)0xfe037874)
// write data 13 for write command. also for read back data comparision.
#define P_DMC_TEST_WD14 ((volatile uint32_t *)0xfe037878)
// write data 14 for write command. also for read back data comparision.
#define P_DMC_TEST_WD15 ((volatile uint32_t *)0xfe03787c)
// write data 15 for write command. also for read back data comparision.
#define P_DMC_TEST_RD0 ((volatile uint32_t *)0xfe037880)
// the read back data 0.  if error happens, it would capture the first error data
#define P_DMC_TEST_RD1 ((volatile uint32_t *)0xfe037884)
// the read back data 1.  if error happens, it would capture the first error data.
#define P_DMC_TEST_RD2 ((volatile uint32_t *)0xfe037888)
// the read back data 2.  if error happens, it would capture the first error data.
#define P_DMC_TEST_RD3 ((volatile uint32_t *)0xfe03788c)
// the read back data 3.  if error happens, it would capture the first error data.
#define P_DMC_TEST_RD4 ((volatile uint32_t *)0xfe037890)
// the read back data 4.  if error happens, it would capture the first error data.
#define P_DMC_TEST_RD5 ((volatile uint32_t *)0xfe037894)
// the read back data 5.  if error happens, it would capture the first error data.
#define P_DMC_TEST_RD6 ((volatile uint32_t *)0xfe037898)
// the read back data 6.  if error happens, it would capture the first error data.
#define P_DMC_TEST_RD7 ((volatile uint32_t *)0xfe03789c)
// the read back data 7.  if error happens, it would capture the first error data.
#define P_DMC_TEST_RD8 ((volatile uint32_t *)0xfe0378a0)
// the read back data 7.  if error happens, it would capture the first error data.
#define P_DMC_TEST_RD9 ((volatile uint32_t *)0xfe0378a4)
// the read back data 7.  if error happens, it would capture the first error data.
#define P_DMC_TEST_RD10 ((volatile uint32_t *)0xfe0378a8)
// the read back data 7.  if error happens, it would capture the first error data.
#define P_DMC_TEST_RD11 ((volatile uint32_t *)0xfe0378ac)
// the read back data 7.  if error happens, it would capture the first error data.
#define P_DMC_TEST_RD12 ((volatile uint32_t *)0xfe0378b0)
// the read back data 7.  if error happens, it would capture the first error data.
#define P_DMC_TEST_RD13 ((volatile uint32_t *)0xfe0378b4)
// the read back data 7.  if error happens, it would capture the first error data.
#define P_DMC_TEST_RD14 ((volatile uint32_t *)0xfe0378b8)
// the read back data 7.  if error happens, it would capture the first error data.
#define P_DMC_TEST_RD15 ((volatile uint32_t *)0xfe0378bc)
// the read back data 7.  if error happens, it would capture the first error data.
#define P_DMC_TEST_ERR_ADDR ((volatile uint32_t *)0xfe037900)
// read only. it capature the first error address.
#define P_DMC_TEST_ERR_CNT ((volatile uint32_t *)0xfe037904)
// read only. how many data error happens in the whole test period.
#define P_DMC_TEST_STS ((volatile uint32_t *)0xfe037908)
// read only.
// bit 31,   test done bit. write 1 to clean.
// bit 30,   indicate address err
// bit 29~7.  not used.
// bit 6.    read data resp error(caused by security or rd latency).
// bit 5.    test MRR/MPR rd latency error. write 1 clear
// bit 4,    sha done.     write 1 to clean.
// bit 3,    write done.   write 1 to clean.
// bit 2,    read done.    write 1 to clean
// bit 1,    write watchdog triggered.   write 1 to clean
// bit 0,    read watchdog triggered.    write 1 to clean.
#define P_DMC_TEST_WRCMD_ADDR ((volatile uint32_t *)0xfe03790c)
// read only. the current write cmd address.
#define P_DMC_TEST_RDCMD_ADDR ((volatile uint32_t *)0xfe037910)
// read only. the current read command address.
#define P_DMC_TEST_RDRSP_ADDR ((volatile uint32_t *)0xfe037914)
// read only. the failed read response address(for error data )
//`define DMC_DRAM_REG_BASE      32'hfe036400
// -----------------------------------------------
// REG_BASE:  APB1_BASE_ADDR = 0xfe036400
// -----------------------------------------------
// there's 2 set of timing DDR timing parameter for 2 set of DDR freqency parameter.
// when change frequency, the hardware would automatically select one of these two set of timing
// parameter DMC_DRAM_* is for Frequency set 0. DMC_NFQ_* is for Freqency set 1.
#define P_DMC_DRAM_TMRD ((volatile uint32_t *)0xfe036400)
// bit 4:0.  tMRD. //MR command cycles, in DDR3/4.  in LPDDR4, it should be value of tMRW
#define P_DMC_DRAM_TRFC ((volatile uint32_t *)0xfe036404)
// bit 9:0 tRFC
#define P_DMC_DRAM_TRP ((volatile uint32_t *)0xfe036408)
// bit 21:16.  tRP for precharge all banks.
// bit 5:0.    tRP for precharge one bank.
#define P_DMC_DRAM_TRTW ((volatile uint32_t *)0xfe03640c)
// bit 31:6:   Not used.
// bit 5:0     DDR3/4 mode : tRTW.
// For LPDDR4 .  The total read command -> write command = (RL + BL/2 - tWODTON) + TDQSCK_MAX +
// tWPRE +RD(tRPST).
//                 tRTW = TDQSCK_max + tWPRE + tRD(tRPST)  + (delay margin)
#define P_DMC_DRAM_TCL ((volatile uint32_t *)0xfe036410)
// bit 5:0  tCL/tRL. read latency.
#define P_DMC_DRAM_TCWL ((volatile uint32_t *)0xfe036414)
// bit 5:0.  CWL:  write latency.
#define P_DMC_DRAM_TRAS ((volatile uint32_t *)0xfe036418)
// bit 7:0.  tRAS.  minimum active to precharge time for same bank.
#define P_DMC_DRAM_TRC ((volatile uint32_t *)0xfe03641c)
// bit 7:0.  tRC.  minimum active to active time for same bank.
#define P_DMC_DRAM_TRCD ((volatile uint32_t *)0xfe036420)
// bit 7:0  tRCD  active to read/write timing for same bank.
#define P_DMC_DRAM_TRRD ((volatile uint32_t *)0xfe036424)
// bit 21:16.  tRRD_l  active bank A to active B in same band group for DDR4.
// bit 5:0.    tRRD/tRRD_s   active bank A to active bank b time.
// tRRD_s:   active bank A to active bank b in different bank grousp for DDR4.
#define P_DMC_DRAM_TFAW ((volatile uint32_t *)0xfe036428)
// bit 8:0   tFAW.  four active command windows
#define P_DMC_DRAM_TRTP ((volatile uint32_t *)0xfe03642c)
// bit 5:0  tRTP.
#define P_DMC_DRAM_TWR ((volatile uint32_t *)0xfe036430)
// bit 5:0 tWR.
#define P_DMC_DRAM_TWTR ((volatile uint32_t *)0xfe036434)
// bit 21:16 tWTR_l   For DDR4 WTR_l.  FOR DDR3/LPDDR4 same as tWTR_s.
// bit 5:0 tWTR_s.
#define P_DMC_DRAM_TCCD ((volatile uint32_t *)0xfe036438)
// bit 19:16. tCCD/tCCD_l.
// bit 3:0 tCCD/tCCD_s    read to read command time or write to write command time.
#define P_DMC_DRAM_TEXSR ((volatile uint32_t *)0xfe03643c)
// bit 12:0. tEXSR.  EXIT SELF-REFRESH to read/write command.
#define P_DMC_DRAM_TXS ((volatile uint32_t *)0xfe036440)
// bit 9:0  tXS.  EXIT SELF_REFRESH to other command time
#define P_DMC_DRAM_TXP ((volatile uint32_t *)0xfe036444)
// bit 3:0. tXP.  EXIT power down to other command time
#define P_DMC_DRAM_TXPDLL ((volatile uint32_t *)0xfe036448)
// bit 12:0.  tXPDLL,  EXIT power down to read/write command time(need to relock PLL).
#define P_DMC_DRAM_TZQCS ((volatile uint32_t *)0xfe03644c)
// bit 11:0.  ZQCS command to other command time.
#define P_DMC_DRAM_TCKSRE ((volatile uint32_t *)0xfe036450)
// bit 4:0. enter self refresh to disable clock time.
#define P_DMC_DRAM_TCKSRX ((volatile uint32_t *)0xfe036454)
// bit 4:0. enable clock to exit self refresh time.
#define P_DMC_DRAM_TCKE ((volatile uint32_t *)0xfe036458)
// bit 4:0.  CKE high or low minimum time.
#define P_DMC_DRAM_TMOD ((volatile uint32_t *)0xfe03645c)
// bit 4:0  tMOD.  MRR/MRW to other command time. in LPDDR4, still use this register but it called
// tMRD.
#define P_DMC_DRAM_TDQS ((volatile uint32_t *)0xfe036460)
// bit 31:28 reserved
// bit 27:24 tDQS. the delay for write after read in different rank.
// bit 23:20 reserved
// bit 19:16 tDQS. the delay for read after write in different rank.
// bit 15:12 reserved
// bit 11:8  tDQS. the delay for write after write in different rank.
// bit 7:4 reserved
// bit 3:0 tDQS. the delay for read after read in different rank.
#define P_DMC_DRAM_TRSTL ((volatile uint32_t *)0xfe036464)
// not used.
#define P_DMC_DRAM_TZQLAT ((volatile uint32_t *)0xfe036468)
// bit 5:0 ZQ LATCH command to other command timing in LPDDR4 mode.
#define P_DMC_DRAM_TMRR ((volatile uint32_t *)0xfe03646c)
// bit 7:0 tMRR  not used in DMC.
#define P_DMC_DRAM_TCKESR ((volatile uint32_t *)0xfe036470)
// bit 9:0 tCKESR.   CKE low minimum pulse in self refresh mode.
#define P_DMC_DRAM_TDPD ((volatile uint32_t *)0xfe036474)
// not support.
#define P_DMC_DRAM_DFITCTRLDELAY ((volatile uint32_t *)0xfe036478)
// bit 3:0. DFI_t_ctrldealy
#define P_DMC_DRAM_DFITPHYWRDATA ((volatile uint32_t *)0xfe03647c)
// bit 5:0.  dfi_t_phy_wrdata.
#define P_DMC_DRAM_DFITPHYWRLAT ((volatile uint32_t *)0xfe036480)
// bit 5:0.  dfi_t_phy_wrlat.  in DDR3/4/LPDDR3 mode:   WL -5.   in LPDDR4 mode: WL -5 + 2.
#define P_DMC_DRAM_DFITRDDATAEN ((volatile uint32_t *)0xfe036484)
// bit 5:0.  dfi_t_rddata_en.  in DDR3/4/LPDDR3 mode: RL -5. in LPDDR4 mode : RL -5 + 1.
#define P_DMC_DRAM_DFITPHYRDLAT ((volatile uint32_t *)0xfe036488)
// bit 5:0.  dfi_t_rdlat.
#define P_DMC_DRAM_DFITCTRLUPDMIN ((volatile uint32_t *)0xfe03648c)
// bit 7:0.  CTRLUPD_MIN  minimux clock cycle to maintain CTRLUPD_REQ.
#define P_DMC_DRAM_DFITCTRLUPDMAX ((volatile uint32_t *)0xfe036490)
// bit 7:0   CTRLUPD_MAX.  maxmum clock cycle to maintain CTRLUPD_REQ if no CTRLUPD_ACK response.
#define P_DMC_DRAM_DFITREFMSKI ((volatile uint32_t *)0xfe036498)
// not used.
#define P_DMC_DRAM_DFITCTRLUPDI ((volatile uint32_t *)0xfe03649c)
// not used.
#define P_DMC_DRAM_DFITDRAMCLK ((volatile uint32_t *)0xfe0364a0)
// bit 17    dram clk1 enable.
// bit 16    dram clk0 enable.
// bit 15:8  DRAM CLK disable waiting time
// bit 7:0   DRAM CLK enable  enable timer
#define P_DMC_DRAM_DFITLPRESP ((volatile uint32_t *)0xfe0364a8)
// bit 3:0.  dfi_lp_ctrl_req response time. after dfi_lp_ctrl_req asserted, and after response
// time if there's still no dfi_lp_ack respone, then drop the dfi_lp_ctrl_req.
#define P_DMC_DRAM_TCKECK ((volatile uint32_t *)0xfe0364b0)
// bit 4:0. tCKECK  from CKE low to assert dfi_dram_clk_disable time. this time + dfi_t_ctrl_delay
#define P_DMC_DRAM_TREFI ((volatile uint32_t *)0xfe0364b4)
// write this register will update the auto refresh related register to the auto refresh control
// logic. bit 31:24:  tZQCI dmc send zqci period.  unit is how much auto refresh period. bit 23:16
// pvti  dmc send dfi_ctrlupd_req period.  unit is one auto refresh period. bit 15:8.   tREFI.dmc
// send auto refresh command period. unit is 100ns. bit 7:0.    t100ns period. unit is dmc clock
// cycles
#define P_DMC_DRAM_TSR ((volatile uint32_t *)0xfe0364b8)
// bit 5:0 tSR.  self resfresh enter to exit time.
#define P_DMC_DRAM_TCCDMW ((volatile uint32_t *)0xfe0364bc)
// bit 5:0.  4*tCCD in LPDDR4 mask write.
#define P_DMC_DRAM_TESCKE ((volatile uint32_t *)0xfe0364c0)
// bit 5:0  tESCKE.  enter self refresh to power time for LPDDR4.
#define P_DMC_DRAM_TREFI_DDR3 ((volatile uint32_t *)0xfe0364c4)
// 7:0. DDR3 SDRAM tREFI single auto refresh time . the unit is t100ns.
// use this to check in 8*tREFI time, the DMC should not sent more than 16 auto REFRESH command.
#define P_DMC_DRAM_TZQCAL ((volatile uint32_t *)0xfe0364c8)
// 11:0. ZQCAL for LPDDR4. ZQINIT/ZQoper for DDR3/4 ZQCL command.
#define P_DMC_DRAM_T10US ((volatile uint32_t *)0xfe0364cc)
// 10us clock cycle number used for LP2 mode.
#define P_DMC_DRAM_TMRRI ((volatile uint32_t *)0xfe0364d0)
// bit 7:0   tMRRI for MRR
#define P_DMC_DRAM_TXS_FAST ((volatile uint32_t *)0xfe0364d4)
// bit 9:0 DDR4 mode XS_FAST exit self_refrest to zqcl/zqcs/mrs command.
#define P_DMC_DRAM_DFIODTCFG ((volatile uint32_t *)0xfe0364d8)
// bit 12.  rank1 ODT default. default vulue for ODT[1] pins if theres no read/write activity.
// bit 11.  rank1 ODT write sel.  enable ODT[1] if there's write occur in rank1.
// bit 10.  rank1 ODT write nsel. enable ODT[1] if theres's write occur in rank0.
// bit 9.   rank1 odt read sel.   enable ODT[1] if there's read occur in rank1.
// bit 8.   rank1 odt read nsel.  enable ODT[1] if there's read occurred in rank0.
// bit 4.   rank0 ODT default.    default vulue for ODT[0] pins if theres no read/write activity.
// bit 3.   rank0 ODT write sel.  enable ODT[0] if there's write occur in rank0.
// bit 2.   rank0 ODT write nsel. enable ODT[0] if theres's write occur in rank1.
// bit 1.   rank0 odt read sel.   enable ODT[0] if there's read occur in rank0.
// bit 0.   rank0 odt read nsel.  enable ODT[0] if there's read occurred in rank1.
#define P_DMC_DRAM_DFIODTCFG1 ((volatile uint32_t *)0xfe0364dc)
// bit 27:24  ODT length for BL8 read transfer.
// bit 19:16. ODT length for BL8 write transfer.
// bit 12:8.  ODT latency for reads.  suppose to be 0.
// bit 4:0.   ODT latency for writes.  suppose to be 0.
#define P_DMC_DRAM_TWODTON ((volatile uint32_t *)0xfe0364e0)
// bit 5:0   DRAM write access ODT on time.
//   in DDR3/4 should be same as WL.
//   in LPDDR4 ODT enable  mode:  tODTLon + tODTon.min
//   In LPDDR4 ODT disable mode:  tWL.
#define P_DMC_DRAM_TRETRAIN ((volatile uint32_t *)0xfe0364e4)
// bit 15:0 LPDDR4 OSCRING retraining timer(units = auto_refresh timer). sync with autorefresh
#define P_DMC_DRAM_PHYADDRON ((volatile uint32_t *)0xfe0364e8)
// bit 5:0 PHY_CTRL_ADDR_ON for new PHY. default : 12 unit: DfiClk
#define P_DMC_DRAM_PHYWRON ((volatile uint32_t *)0xfe0364ec)
// bit 6:0 PHY_CTRL_ADDR_ON for new PHY. unit: ddr clk
// PHY_CTRL_WR_ON.  = 20 + WL + (tDQSS+ tDQS2DQ + tWPST)/ddr_clk + BL/2
#define P_DMC_DRAM_PHYRDON ((volatile uint32_t *)0xfe0364f0)
// PHY_CTRL_RD_ON.  = 20 + RL + (tDQSCK+ tRPST + tDQSQ)/ddr_clk + BL/2
#define P_DMC_DRAM_ZQCTRL ((volatile uint32_t *)0xfe0364f4)
// tZQCI bits in DMC_DRAM_TREFI  defined how many refresh period send ZQCS/ZQUPD/command.
// this register defines in 0~tZQCI period, which refresh period count to send partical
// ZQCS/ZACAL/ZQUPD command 31:24.  in LPDDR4 case when to send ZQLAT comman to both RANKs of
// LPDDR4 SDRAM 23:16.  when to send PHY ZQ UPDATE command. 15:8.   when to send ZQCS/ZQCAL to
// rank1 DDR SDRAM. 7:0.    when to senc ZQCS/ZQCAL to rank0 DDR SDRAM. timing parameter for
// frequency set 1.
#define P_DMC_NFQ_TMRD ((volatile uint32_t *)0xfe036500)
#define P_DMC_NFQ_TRFC ((volatile uint32_t *)0xfe036504)
#define P_DMC_NFQ_TRP ((volatile uint32_t *)0xfe036508)
#define P_DMC_NFQ_TRTW ((volatile uint32_t *)0xfe03650c)
#define P_DMC_NFQ_TCL ((volatile uint32_t *)0xfe036510)
#define P_DMC_NFQ_TCWL ((volatile uint32_t *)0xfe036514)
#define P_DMC_NFQ_TRAS ((volatile uint32_t *)0xfe036518)
#define P_DMC_NFQ_TRC ((volatile uint32_t *)0xfe03651c)
#define P_DMC_NFQ_TRCD ((volatile uint32_t *)0xfe036520)
#define P_DMC_NFQ_TRRD ((volatile uint32_t *)0xfe036524)
#define P_DMC_NFQ_TFAW ((volatile uint32_t *)0xfe036528)
#define P_DMC_NFQ_TRTP ((volatile uint32_t *)0xfe03652c)
#define P_DMC_NFQ_TWR ((volatile uint32_t *)0xfe036530)
#define P_DMC_NFQ_TWTR ((volatile uint32_t *)0xfe036534)
#define P_DMC_NFQ_TCCD ((volatile uint32_t *)0xfe036538)
#define P_DMC_NFQ_TEXSR ((volatile uint32_t *)0xfe03653c)
#define P_DMC_NFQ_TXS ((volatile uint32_t *)0xfe036540)
#define P_DMC_NFQ_TXP ((volatile uint32_t *)0xfe036544)
#define P_DMC_NFQ_TXPDLL ((volatile uint32_t *)0xfe036548)
#define P_DMC_NFQ_TZQCS ((volatile uint32_t *)0xfe03654c)
#define P_DMC_NFQ_TCKSRE ((volatile uint32_t *)0xfe036550)
#define P_DMC_NFQ_TCKSRX ((volatile uint32_t *)0xfe036554)
#define P_DMC_NFQ_TCKE ((volatile uint32_t *)0xfe036558)
#define P_DMC_NFQ_TMOD ((volatile uint32_t *)0xfe03655c)
#define P_DMC_NFQ_TDQS ((volatile uint32_t *)0xfe036560)
#define P_DMC_NFQ_TRSTL ((volatile uint32_t *)0xfe036564)
#define P_DMC_NFQ_TZQLAT ((volatile uint32_t *)0xfe036568)
#define P_DMC_NFQ_TMRR ((volatile uint32_t *)0xfe03656c)
#define P_DMC_NFQ_TCKESR ((volatile uint32_t *)0xfe036570)
#define P_DMC_NFQ_TDPD ((volatile uint32_t *)0xfe036574)
#define P_DMC_NFQ_DFITCTRLDELAY ((volatile uint32_t *)0xfe036578)
#define P_DMC_NFQ_DFITPHYWRDATA ((volatile uint32_t *)0xfe03657c)
#define P_DMC_NFQ_DFITPHYWRLAT ((volatile uint32_t *)0xfe036580)
#define P_DMC_NFQ_DFITRDDATAEN ((volatile uint32_t *)0xfe036584)
#define P_DMC_NFQ_DFITPHYRDLAT ((volatile uint32_t *)0xfe036588)
#define P_DMC_NFQ_DFITCTRLUPDMIN ((volatile uint32_t *)0xfe03658c)
#define P_DMC_NFQ_DFITCTRLUPDMAX ((volatile uint32_t *)0xfe036590)
#define P_DMC_NFQ_DFITREFMSKI ((volatile uint32_t *)0xfe036598)
#define P_DMC_NFQ_DFITCTRLUPDI ((volatile uint32_t *)0xfe03659c)
#define P_DMC_NFQ_DFITDRAMCLK ((volatile uint32_t *)0xfe0365a0)
#define P_DMC_NFQ_DFITLPRESP ((volatile uint32_t *)0xfe0365a8)
#define P_DMC_NFQ_TCKECK ((volatile uint32_t *)0xfe0365b0)
#define P_DMC_NFQ_TREFI ((volatile uint32_t *)0xfe0365b4)
#define P_DMC_NFQ_TSR ((volatile uint32_t *)0xfe0365b8)
#define P_DMC_NFQ_TCCDMW ((volatile uint32_t *)0xfe0365bc)
#define P_DMC_NFQ_TESCKE ((volatile uint32_t *)0xfe0365c0)
#define P_DMC_NFQ_TREFI_DDR3 ((volatile uint32_t *)0xfe0365c4)
#define P_DMC_NFQ_TZQCAL ((volatile uint32_t *)0xfe0365c8)
#define P_DMC_NFQ_T10US ((volatile uint32_t *)0xfe0365cc)
#define P_DMC_NFQ_TMRRI ((volatile uint32_t *)0xfe0365d0)
#define P_DMC_NFQ_TXS_FAST ((volatile uint32_t *)0xfe0365d4)
#define P_DMC_NFQ_DFIODTCFG ((volatile uint32_t *)0xfe0365d8)
#define P_DMC_NFQ_DFIODTCFG1 ((volatile uint32_t *)0xfe0365dc)
#define P_DMC_NFQ_TWODTON ((volatile uint32_t *)0xfe0365e0)
#define P_DMC_NFQ_TRETRAIN ((volatile uint32_t *)0xfe0365e4)
#define P_DMC_NFQ_PHYADDRON ((volatile uint32_t *)0xfe0365e8)
#define P_DMC_NFQ_PHYWRON ((volatile uint32_t *)0xfe0365ec)
#define P_DMC_NFQ_PHYRDON ((volatile uint32_t *)0xfe0365f0)
#define P_DMC_NFQ_ZQCTRL ((volatile uint32_t *)0xfe0365f4)
// end of second frequency timing parameter
#define P_DMC_DRAM_DFITPHYUPDTYPE0 ((volatile uint32_t *)0xfe036600)
// dfi_phyupd_ack hold time for dfi_phyupd_req type = 0.
#define P_DMC_DRAM_DFITPHYUPDTYPE1 ((volatile uint32_t *)0xfe036604)
// dfi_phyupd_ack hold time for dfi_phyupd_req type = 1.
#define P_DMC_DRAM_DFITPHYUPDTYPE2 ((volatile uint32_t *)0xfe036608)
// dfi_phyupd_ack hold time for dfi_phyupd_req type = 2.
#define P_DMC_DRAM_DFITPHYUPDTYPE3 ((volatile uint32_t *)0xfe03660c)
// dfi_phyupd_ack hold time for dfi_phyupd_req type = 3.
#define P_DMC_DRAM_MCFG ((volatile uint32_t *)0xfe036618)
// bit 31:27  not used.
// bit 26:24  rank1_d16_sel.  16bit mode, rank 1 byte selection.
// bit 23     not used.
// bit 22:20. rank0_d16_sel. 16bit mode, rank 0 byte selection.
// bit 19.   send PHY ZQ command  after siu self refresh exit. 1 : enable.  0 : disable.
// bit 18.   send retrain command after siu self refresh exit. 1 : enable. 0 : disable.
// bit 17.   in DDR3/4 mode, send ZQCL command after exit register triggered self refresh.
// bit 16.   send refresh command after finish frequency change. 1 : enable. 0 : disable.
// bit 15.   send refresh command after finish LPDDR4 retraining. 1 : enable. 0 : disable.
// bit 14.   1: cke init low.  0 : cke init high.
// bit 13    1: dbi write enable only for LPDDR4.
// bit 12.   1: dbi read inversion.   0:  dbi read high inversion.
// bit 11.   1: dbi read enable. 0:  dbi not enabled.
// bit 10    1: enable staggered chip select for 2 ranks DRAM.
// bit 9     1: enable send auto refresh command to DDR SDRAM when PCTL is in CFG/STOP state.
// bit 8     send auto refr cmd before enter register triggered  self refresh
// bit 7     send auto refr cmd after exit register triggered self refresh mode.
// bit 6     disable dram clock after enter register triggered self refresh.
// bit 5     send DFI_LP_REQ to PHY after enter register triggered elf refresh mode.
// bit 4     send DRAM to power down mode after enter self refresh. ONLY for LPDDR4.
// bit 3     send DFI_CTRLUPD_REQ after exit register triggered self refresh.
// bit 2     send ZQCS command after exit register triggered self refresh.
// bit 1     enable PHY triggered DFI_PHYUPD_REQ.
// bit 0     2T mode. always 1 in DDR3/4 mode.
#define P_DMC_DRAM_ZQ_CTRL ((volatile uint32_t *)0xfe03661c)
// bit 2  ZQ command must be send in different time.
// bit 1  ZQ command can be send at same time.
// bit 0  rank0 ZQ only
#define P_DMC_DRAM_MCFG1 ((volatile uint32_t *)0xfe036620)
// bit7:0 LPDDR4 WDBI mode maskwrite dbi pattern
#define P_DMC_DRAM_DFI_CTRL ((volatile uint32_t *)0xfe036624)
// bit 31 siu_dfi_lat err generation enable.  1: if dfi read latency violation, generate data
// error. 0 : disable. bit 20 phy_ctrl_rd_on phy_ctrl_wr_on ignore 16bit mode.  1: sending 0xf in
// 16bit mode.  0: sending valid byte enable in 16bit mode bit 19: dfi_init_complete wait enable.
// 1: after dfi_init_complete, wait additional EXSR time for new command. 0: phy will handle all
// the timing    after dfi_init_complete DMC can do everything they want. bit 18:  dfi_rddata_cs_n
// polariy.  0:  rank0 select = 2'b10. rank1 select = 2'b10. 1: rank0 select = 2'b01, rank1_select
// = 2'b10. bit 17:  dfi_wrdata_cs_n polariy.  0:  rank0 select = 2'b10. rank1 select = 2'b10. 1:
// rank0 select = 2'b01, rank1_select = 2'b10. bit 16:  force PHY ctrl_on  if = 1, phy_ctrl_on
// signal will keep on. bit 15 siu_dfi1_lp_en bit 14 siu_dfi_lp_ack_and bit 13 siu_dfi_lp_ack_or
// bit 12 siu_dfi1_init_start_en
// bit 11 siu_dfi_init_com_and
// bit 10 siu_dfi_init_com_or
// bit  9 siu_dfi1_freq_en
// bit  8 siu_dfi1_dram_clk_dis_en
// bit  7 siu_dfi_phyupd_type_sel
// bit  6 siu_dfi1_phyupd_ack_en
// bit  5 siu_dfi_phyupd_req_and
// bit  4 siu_dfi_phyupd_req_or
// bit  3 siu_dfi_ctrlupd_ack_and
// bit  2 siu_dfi_ctrlupd_ack_or
// bit  1 siu_dfi1_ctrlupd_req_en
// bit  0 siu_dfi1_cmd_en
#define P_DMC_DRAM_DFIINITCFG ((volatile uint32_t *)0xfe036628)
// bit 31.   dfi_init_complete status. read only.
// bit 15:14.  Frequency set 1 dfi_freq_ratio value.
// bit 12:8    Frequency set 1 dfi_freq value.
// bit 7:6     Frequency set 0 dfi_freq_ratio value.
// bit 5:1     Frequency set 0 dfi_freq value.
// bit 0.      dfi_init_start value  can be use manually config dfi_init_start signal.
#define P_DMC_DRAM_APD_CTRL ((volatile uint32_t *)0xfe036630)
// bit 19:16  DFI_LP_WAKEUP value in APD DFI_LP_REQ mode
// bit 12    1: exit power down slow mode(waiting PLL LOCK).  0 : fast mode.
// bit 11    enable DFI_LP_REQ when enter Auto power down mode.
// bit 10    disable DFI_clk_disable when enter auto power down mode.
// bit 9:0    0  disable auto power down mode.
// non zero value to enable auto power down when DMC is in idle state for this number of clock
// cycles.
#define P_DMC_DRAM_ASR_CTRL ((volatile uint32_t *)0xfe036634)
// bit 31. enable RETRAIN PHY after auto selfrefresh exit. for AM_PHY only.
// bit 30. in DDR3/4 mode, send ZQCL command after exit from auto self refresh mode.
// bit 29. enable PHY clock in LP2 mode.  1: enable. 0 : disable.
// bit 28. enable dmc wait 10us after LP2 mode exit if it's long time the PHY in LP2 mode..
// bit [27:24] DFI_LP_WAKEUP value in self refresh DFI_LP_REQ mode.
// bit 23 : send REFRESH command after exit from auto self refersh mode(ASR).
// bit 22 : send REFERSH command before enter to Auto self refresh mode(ASR).
// bit 21 : send ZQCS command after exit from Auto self refresh mode(ASR).
// bit 20 : send dfi_ctrl_upd after exit from ASR mode
// bit 19 : send power down command when enter ASR mode. //for LPDDR4 only.
// bit 18 : set the PHY enter LP2 mode after enter ASR mode.
// bit 17 : send DFI_LP_REQ  after enter ASR mode.
// bit 16 : set DFI_CLK_DISABLE after enter ASR mode.
// bit 15:0.   0 disable auto ASR mode.
// Non-zero valule enable ASR mode. when DMC is in idle state for this number of clock cycles, the
// DMC will enter ASR mode.
#define P_DMC_DRAM_REFR_CTRL ((volatile uint32_t *)0xfe036648)
// bit 22  dmc to control DFI_CTRLUPD_REQ  with zq generation together.
// bit 21  dmc to control PHY ZQ generation enable.
// bit 20  dmc to control zqlat(in LPDDR4 mode) generation enable.
// bit 19  dmc to control zqcs1 generation enable.
// bit 18  dmc to control zqcs0 generation enable.
// bit 17:8 auto refresh request pending cnt if there's page hit request.
// bit 7  retrain enable for auto refresh requent. 1: enable. 0: disable.
// bit 6  Disabled auto refresh command if over 16 auto refresh command sent in 2 TREFI_DDR3
// period bit 5  enable dmc send ZQCS command . bit 4. enable dmc send DFI_CTRUPD_REQ. bit 3:1. how
// many refresh command send for one period. = this number + 1 bit 0.  enable dmc send auto refresh
// command.
#define P_DMC_DRAM_FREQ_CTRL ((volatile uint32_t *)0xfe03664c)
// bit 31 .  write 1 to change freqency   read 0: finished.
// bit 30.   waiting for software to send some manual command.  1 : waiting. 0 : not ready yet.
// bit 29:23.  not used.
// bit 22.   after freqchenge send refresh command.
// bit 21     after Freqchange send PHY ZQ update.
// bit 20    send CTRLUPD_REQ to PHY after freq_change finished.
// bit 19:16. how many cycles to send PLL change req after init_complete signal to low.
// bit 15.   freq pre  config_en. Before freq enter stop state let DMC configure DDR SDRAM.
// bit 14.   freq post config_en. After  freq enter stop state let DMC configure DDR SDRAM.
// bit 13.   send zqcl after freq change in DDR3/4 mode.
// bit 12.   send zqcs after freq change. 1: enable. 0 not send.
// bit 11.   in AUTO MRW funcntion: the data format.  1: use USR_CMD format.  0: MRW format.
// bit 10.   AUTO MRW function:  1 use hardware auto MRW function.  0: don't do auto MRW.
// bit 9.  1 : FREQ MRW done. let FREQ change machine continue.
// bit 8   FREQ WAIT. 1 when freq change finishes, state machine stop at self refresh state in
// case there's something need to handle.
//     0 after freq change finishes  the state machine go back to access state.
// bit 7   when change PLL setting, disable dmc clock
// bit 6   when change PLL setting, disable PHY DfiClk and DfiCtlClk.
// bit 5   check vpu_sleep_en ==1 when do FREQ change.  if vpu_sleep_en == 0, just wait.
// bit 4   nxt frequency selection.  1 = freq1. 0 = freq0.
// bit 3:1.  not used.
// bit 0.   current frequency selection.
#define P_DMC_DRAM_SCFG ((volatile uint32_t *)0xfe036650)
// bit 2:0 only one bit can be high at same time.
// bit 2  1 : to ask PCTL enter ACCESS STATE.  0 : deassert the request.
// bit 1  1 : to ask PCTL enter SELF REFRESH STATE.  0 : deassert the request.
// bit 0  1 : to ask PCTL enter STOP/CONFIG STATE .  0 : deassert the request.
#define P_DMC_DRAM_STAT ((volatile uint32_t *)0xfe036654)
// bit 31     rd latency error. 1: means after dfiphytrdlat cycles, the read data still not back.
// bit 28:24   dram_sr_state
// bit 23:20   stop_st
// bit 19:15   sleep_st
// bit 14:12  ACCESS STATUS 0 :  ACCESS is in normal working mode.
// 1 :   ACCESS sending precharege command.
// 2 :   ACCESS sending AUTO REFESH command.
// 3 :   ACCESS sending DIF_CTRLUPD_REQ command.
// 4 :   ACCESS sending ZQCS command to DDR DRAM(ZQCAL for LPDDR4).
// 5 :   ACCESS sending ZQLATCH command to  LPDDR4 only.
// bit 11:8   APD STATUS:   0 :   APD_IDLE
// 1 :    APD sending PRECHARGE command
// 2 :    APD sending CKE low command
// 3 :    APD sending DISABLE DRAM CLOCK command
// 4 :    APD sending DFI_LP_CTRL_REQ
// 5 :    APD in Auto Power down mode.
// 6 :    APD deassert DFI_LP_CTRL_REQ
// 7 :    APD sending enable DRAM CLOCK command
// 8 :    APD sending out CKE high command.
// bit 7:4: DRAM_STATUS:  0  :    DRAM IDLE
// 1  :    DRAM_STOP/DRAM_CFG
// 2  :    DRAM_ACCESS
// 3  :    DRAM_SLEEP
// 4  :    DRAM APD(AUTO POWER DOWN).
// 5  :    IDLE -> STOP/CONFIG
// 6  :    STOP -> SLEEP
// 7  :    STOP -> ACCESS
// 8  :    ACCESS -> SLEEP.
// 9  :    ACCESS -> STOP
// A  :    ACCESS -> APD
// B  :    SLEEP -> STOP
// C  :    SLEEP -> ACCESS
// D  :    APD -> ACCESS
// bit 3        reserved.
// bit 2        1 : DRAM enter normal working state.
// bit 1        1 : DRAM enter sleep state. self refresh state.
// bit 0        1 : dram enter cfg state.
#define P_DMC_DRAM_STAT1 ((volatile uint32_t *)0xfe036658)
// bit 11:8  freq_st.
// 4'h0 : IDLE
// 4'h1 : FREQ_CHECK_VPU
// 4'h2 : FREQ_WAITING_STOP
// 4'h3 : FREQ_DRAM_CFG.  waiting DMC/software to send special MRW/MPC command to configure DDR
// SDRAM either before Freq change or after freq change. 4'h4 : FREQ_SELF_REFR_ST. 4'h5 :
// FREQ_SET_DFI_FREQ. 4'h6 : FREQ_DFI_INIT_START_HIGH. 4'h7 : FREQ_CHANGE PLL_ST. 4'h8 :
// FREQ_UPDATA REG. 4'h9 : FREQ_DFI_INIT_START_LOW. 4'ha : FREQ_WAITING_FINISH 4'hb : FREQ_ZQCS
// 4'hc : FREQ_ZQ_LATCH
// 4'hd : FREQ_PVT
// bit 7:5   train_st
// bit 4:0   dram_phy_st
#define P_DMC_PHY_RETRAINING_CTRL ((volatile uint32_t *)0xfe03665c)
// bit 31 :  phy_retraining enable.
// bit 30 :  check  vpu sleep_en.
// bit 25:24 : retraining dfi_freq[4:3], the [2:0] bit still use the dfi_freq bits to keep the
// frequency. bit 23:0: retraining period unit : 100ns.
#define P_DMC_DFI_ERR_STAT ((volatile uint32_t *)0xfe036660)
// LPDDR4 PHY DFI error information.
// bit 31:20. not used.
// bit 9.    ddr0_dfi_error
// bit 8:5   ddr0_dfi_error_info.
// bit 4.    ddr1_dfi_error.
// bit 3:0.  ddr1_dfi_error_info.
#define P_DMC_LP2_TIMER ((volatile uint32_t *)0xfe036668)
// bit 15:0.   timer setting to measure how long the chip is entered LP2 mode.
// this timer is 40bits counter with DMC PCLK.
// we use the high 16bits to compare this register. if the counter is large than this number, that
// means  the PHY need addition 10us after wakeup the PHY and before exit self_refresh mode.
#define P_DMC_DRAM_COMPLETE_WAIT ((volatile uint32_t *)0xfe03666c)
// read only how long to waiting for DFI_INIT_COMPLETE become high after DFI_INIT_START triggered.
#define P_DMC_DRAM_DFI_SWAP_0 ((volatile uint32_t *)0xfe036680)
// bit 5:0. dfi_act_n function select
// 6'h00 : the function itself.
// 6'h01 : act_n.
// 6'h02 : ras_n.
// 6'h03 : cas_n.
// 6'h04 : we_n.
// 6'h05 : bg[0].
// 6'h06 : bg[1].
// 6'h07 : ba[0].
// 6'h08 : ba[1].
// 6'h09 : ba[2].
// 6'h0a : a[0].
// 6'h0b : a[1].
// 6'h0c : a[2].
// 6'h0d : a[3].
// 6'h0e : a[4].
// 6'h0f : a[5].
// 6'h10 : a[6].
// 6'h11 : a[7].
// 6'h12 : a[8].
// 6'h13 : a[9].
// 6'h14 : a[10].
// 6'h15 : a[11].
// 6'h16 : a[12].
// 6'h17 : a[13].
// 6'h18 : a[14].
// 6'h19 : a[15].
// 6'h1a : a[16].
// 6'h1b : a[17].
#define P_DMC_DRAM_DFI_SWAP_1 ((volatile uint32_t *)0xfe036684)
// bit 5:0. dfi_ras_n function select
// 6'h00 : the function itself.
// 6'h01 : act_n.
// 6'h02 : ras_n.
// 6'h03 : cas_n.
// 6'h04 : we_n.
// 6'h05 : bg[0].
// 6'h06 : bg[1].
// 6'h07 : ba[0].
// 6'h08 : ba[1].
// 6'h09 : ba[2].
// 6'h0a : a[0].
// 6'h0b : a[1].
// 6'h0c : a[2].
// 6'h0d : a[3].
// 6'h0e : a[4].
// 6'h0f : a[5].
// 6'h10 : a[6].
// 6'h11 : a[7].
// 6'h12 : a[8].
// 6'h13 : a[9].
// 6'h14 : a[10].
// 6'h15 : a[11].
// 6'h16 : a[12].
// 6'h17 : a[13].
// 6'h18 : a[14].
// 6'h19 : a[15].
// 6'h1a : a[16].
// 6'h1b : a[17].
#define P_DMC_DRAM_DFI_SWAP_2 ((volatile uint32_t *)0xfe036688)
// bit 5:0. dfi_cas_n function select
// 6'h00 : the function itself.
// 6'h01 : act_n.
// 6'h02 : ras_n.
// 6'h03 : cas_n.
// 6'h04 : we_n.
// 6'h05 : bg[0].
// 6'h06 : bg[1].
// 6'h07 : ba[0].
// 6'h08 : ba[1].
// 6'h09 : ba[2].
// 6'h0a : a[0].
// 6'h0b : a[1].
// 6'h0c : a[2].
// 6'h0d : a[3].
// 6'h0e : a[4].
// 6'h0f : a[5].
// 6'h10 : a[6].
// 6'h11 : a[7].
// 6'h12 : a[8].
// 6'h13 : a[9].
// 6'h14 : a[10].
// 6'h15 : a[11].
// 6'h16 : a[12].
// 6'h17 : a[13].
// 6'h18 : a[14].
// 6'h19 : a[15].
// 6'h1a : a[16].
// 6'h1b : a[17].
#define P_DMC_DRAM_DFI_SWAP_3 ((volatile uint32_t *)0xfe03668c)
// bit 5:0. dfi_we_n function select
// 6'h00 : the function itself.
// 6'h01 : act_n.
// 6'h02 : ras_n.
// 6'h03 : cas_n.
// 6'h04 : we_n.
// 6'h05 : bg[0].
// 6'h06 : bg[1].
// 6'h07 : ba[0].
// 6'h08 : ba[1].
// 6'h09 : ba[2].
// 6'h0a : a[0].
// 6'h0b : a[1].
// 6'h0c : a[2].
// 6'h0d : a[3].
// 6'h0e : a[4].
// 6'h0f : a[5].
// 6'h10 : a[6].
// 6'h11 : a[7].
// 6'h12 : a[8].
// 6'h13 : a[9].
// 6'h14 : a[10].
// 6'h15 : a[11].
// 6'h16 : a[12].
// 6'h17 : a[13].
// 6'h18 : a[14].
// 6'h19 : a[15].
// 6'h1a : a[16].
// 6'h1b : a[17].
#define P_DMC_DRAM_DFI_SWAP_4 ((volatile uint32_t *)0xfe036690)
// bit 5:0. dfi_bg0 function select
// 6'h00 : the function itself.
// 6'h01 : act_n.
// 6'h02 : ras_n.
// 6'h03 : cas_n.
// 6'h04 : we_n.
// 6'h05 : bg[0].
// 6'h06 : bg[1].
// 6'h07 : ba[0].
// 6'h08 : ba[1].
// 6'h09 : ba[2].
// 6'h0a : a[0].
// 6'h0b : a[1].
// 6'h0c : a[2].
// 6'h0d : a[3].
// 6'h0e : a[4].
// 6'h0f : a[5].
// 6'h10 : a[6].
// 6'h11 : a[7].
// 6'h12 : a[8].
// 6'h13 : a[9].
// 6'h14 : a[10].
// 6'h15 : a[11].
// 6'h16 : a[12].
// 6'h17 : a[13].
// 6'h18 : a[14].
// 6'h19 : a[15].
// 6'h1a : a[16].
// 6'h1b : a[17].
#define P_DMC_DRAM_DFI_SWAP_5 ((volatile uint32_t *)0xfe036694)
// bit 5:0. dfi_bg[1] function select
// 6'h00 : the function itself.
// 6'h01 : act_n.
// 6'h02 : ras_n.
// 6'h03 : cas_n.
// 6'h04 : we_n.
// 6'h05 : bg[0].
// 6'h06 : bg[1].
// 6'h07 : ba[0].
// 6'h08 : ba[1].
// 6'h09 : ba[2].
// 6'h0a : a[0].
// 6'h0b : a[1].
// 6'h0c : a[2].
// 6'h0d : a[3].
// 6'h0e : a[4].
// 6'h0f : a[5].
// 6'h10 : a[6].
// 6'h11 : a[7].
// 6'h12 : a[8].
// 6'h13 : a[9].
// 6'h14 : a[10].
// 6'h15 : a[11].
// 6'h16 : a[12].
// 6'h17 : a[13].
// 6'h18 : a[14].
// 6'h19 : a[15].
// 6'h1a : a[16].
// 6'h1b : a[17].
#define P_DMC_DRAM_DFI_SWAP_6 ((volatile uint32_t *)0xfe036698)
// bit 5:0. dfi_ba[0] function select
// 6'h00 : the function itself.
// 6'h01 : act_n.
// 6'h02 : ras_n.
// 6'h03 : cas_n.
// 6'h04 : we_n.
// 6'h05 : bg[0].
// 6'h06 : bg[1].
// 6'h07 : ba[0].
// 6'h08 : ba[1].
// 6'h09 : ba[2].
// 6'h0a : a[0].
// 6'h0b : a[1].
// 6'h0c : a[2].
// 6'h0d : a[3].
// 6'h0e : a[4].
// 6'h0f : a[5].
// 6'h10 : a[6].
// 6'h11 : a[7].
// 6'h12 : a[8].
// 6'h13 : a[9].
// 6'h14 : a[10].
// 6'h15 : a[11].
// 6'h16 : a[12].
// 6'h17 : a[13].
// 6'h18 : a[14].
// 6'h19 : a[15].
// 6'h1a : a[16].
// 6'h1b : a[17].
#define P_DMC_DRAM_DFI_SWAP_7 ((volatile uint32_t *)0xfe03669c)
// bit 5:0. dfi_ba[1] function select
// 6'h00 : the function itself.
// 6'h01 : act_n.
// 6'h02 : ras_n.
// 6'h03 : cas_n.
// 6'h04 : we_n.
// 6'h05 : bg[0].
// 6'h06 : bg[1].
// 6'h07 : ba[0].
// 6'h08 : ba[1].
// 6'h09 : ba[2].
// 6'h0a : a[0].
// 6'h0b : a[1].
// 6'h0c : a[2].
// 6'h0d : a[3].
// 6'h0e : a[4].
// 6'h0f : a[5].
// 6'h10 : a[6].
// 6'h11 : a[7].
// 6'h12 : a[8].
// 6'h13 : a[9].
// 6'h14 : a[10].
// 6'h15 : a[11].
// 6'h16 : a[12].
// 6'h17 : a[13].
// 6'h18 : a[14].
// 6'h19 : a[15].
// 6'h1a : a[16].
// 6'h1b : a[17].
#define P_DMC_DRAM_DFI_SWAP_8 ((volatile uint32_t *)0xfe0366a0)
// bit 5:0. dfi_ba[2] function select
// 6'h00 : the function itself.
// 6'h01 : act_n.
// 6'h02 : ras_n.
// 6'h03 : cas_n.
// 6'h04 : we_n.
// 6'h05 : bg[0].
// 6'h06 : bg[1].
// 6'h07 : ba[0].
// 6'h08 : ba[1].
// 6'h09 : ba[2].
// 6'h0a : a[0].
// 6'h0b : a[1].
// 6'h0c : a[2].
// 6'h0d : a[3].
// 6'h0e : a[4].
// 6'h0f : a[5].
// 6'h10 : a[6].
// 6'h11 : a[7].
// 6'h12 : a[8].
// 6'h13 : a[9].
// 6'h14 : a[10].
// 6'h15 : a[11].
// 6'h16 : a[12].
// 6'h17 : a[13].
// 6'h18 : a[14].
// 6'h19 : a[15].
// 6'h1a : a[16].
// 6'h1b : a[17].
#define P_DMC_DRAM_DFI_SWAP_9 ((volatile uint32_t *)0xfe0366a4)
// bit 5:0. dfi_a[0] function select
// 6'h00 : the function itself.
// 6'h01 : act_n.
// 6'h02 : ras_n.
// 6'h03 : cas_n.
// 6'h04 : we_n.
// 6'h05 : bg[0].
// 6'h06 : bg[1].
// 6'h07 : ba[0].
// 6'h08 : ba[1].
// 6'h09 : ba[2].
// 6'h0a : a[0].
// 6'h0b : a[1].
// 6'h0c : a[2].
// 6'h0d : a[3].
// 6'h0e : a[4].
// 6'h0f : a[5].
// 6'h10 : a[6].
// 6'h11 : a[7].
// 6'h12 : a[8].
// 6'h13 : a[9].
// 6'h14 : a[10].
// 6'h15 : a[11].
// 6'h16 : a[12].
// 6'h17 : a[13].
// 6'h18 : a[14].
// 6'h19 : a[15].
// 6'h1a : a[16].
// 6'h1b : a[17].
#define P_DMC_DRAM_DFI_SWAP_10 ((volatile uint32_t *)0xfe0366a8)
// bit 5:0. dfi_a[1] function select
#define P_DMC_DRAM_DFI_SWAP_11 ((volatile uint32_t *)0xfe0366ac)
// bit 5:0. dfi_a[2] function select
#define P_DMC_DRAM_DFI_SWAP_12 ((volatile uint32_t *)0xfe0366b0)
// bit 5:0. dfi_a[3] function select
#define P_DMC_DRAM_DFI_SWAP_13 ((volatile uint32_t *)0xfe0366b4)
// bit 5:0. dfi_a[4] function select
#define P_DMC_DRAM_DFI_SWAP_14 ((volatile uint32_t *)0xfe0366b8)
// bit 5:0. dfi_a[5] function select
#define P_DMC_DRAM_DFI_SWAP_15 ((volatile uint32_t *)0xfe0366bc)
// bit 5:0. dfi_a[6] function select
#define P_DMC_DRAM_DFI_SWAP_16 ((volatile uint32_t *)0xfe0366c0)
// bit 5:0. dfi_a[7] function select
#define P_DMC_DRAM_DFI_SWAP_17 ((volatile uint32_t *)0xfe0366c4)
// bit 5:0. dfi_a[8] function select
#define P_DMC_DRAM_DFI_SWAP_18 ((volatile uint32_t *)0xfe0366c8)
// bit 5:0. dfi_a[9] function select
#define P_DMC_DRAM_DFI_SWAP_19 ((volatile uint32_t *)0xfe0366cc)
// bit 5:0. dfi_a[10] function select
#define P_DMC_DRAM_DFI_SWAP_20 ((volatile uint32_t *)0xfe0366d0)
// bit 5:0. dfi_a[11] function select
#define P_DMC_DRAM_DFI_SWAP_21 ((volatile uint32_t *)0xfe0366d4)
// bit 5:0. dfi_a[12] function select
#define P_DMC_DRAM_DFI_SWAP_22 ((volatile uint32_t *)0xfe0366d8)
// bit 5:0. dfi_a[13] function select
#define P_DMC_DRAM_DFI_SWAP_23 ((volatile uint32_t *)0xfe0366dc)
// bit 5:0. dfi_a[14] function select
#define P_DMC_DRAM_DFI_SWAP_24 ((volatile uint32_t *)0xfe0366e0)
// bit 5:0. dfi_a[15] function select
#define P_DMC_DRAM_DFI_SWAP_25 ((volatile uint32_t *)0xfe0366e4)
// bit 5:0. dfi_a[16] function select
#define P_DMC_DRAM_DFI_SWAP_26 ((volatile uint32_t *)0xfe0366e8)
// bit 5:0. dfi_a[17] function select
#define P_DMC_DRAM_CMD ((volatile uint32_t *)0xfe036740)
// bit 31. cmd done.  write 0 to clean.
// bit 30. data done. write 0 to clean.
// bit 8.  1: MPC/MRR command is in a 16bits width SDRAM. 0 : normal operation.
// bit 5.  user defined command.
// bit 4.  LPDDR4 MPC write data command( MPC WR FIFO).
// bit 3.  LPDDR4 MPC read data command (MPC RD Calibration and RD FIFO).
// bit 2.  LPDDR4 MPC-1 command ( NOP,  Start DQS interval ....)
// bit 1.  mrr command.
// bit 0.  mrw command.
#define P_DMC_DRAM_CMD_CODE ((volatile uint32_t *)0xfe036744)
// bit 31:28  user command case: = {act_n, ras_n, cas_n, we_n}
// bit 27:26. 128bits data cycles . 0: 1 clock cycles;  1: 2  clock cycles; 2: 3 clock cycles; 3:4
// clock cycles.
//           LPDDR4 : 4 clock cycles;
//           DDR3/4/LPDDR3  : 2 clock cycles.
// bit 25     MRW/MRR/MPC command rank 1 select.  1: select.  0: not select.
// bit 24.    MRW/MRR/MPC command rank 0 select.  1: select.  0: not select.
// bit 23:16  MR addr.  DDR4 case :  18:16 ba[2:0].    20:19 BG[1:0].
// bit 15:0   opcode.
#define P_DMC_DRAM_CMD_TIME ((volatile uint32_t *)0xfe036748)
// bit 31:16  PRE  CMD timer. //delay how many cycle to start the command.
// bit 15:0   POST CMD timer  //delay how many cycle after the command execute.
#define P_DMC_DRAM_WSTRB0 ((volatile uint32_t *)0xfe03674c)
#define P_DMC_DRAM_WSTRB1 ((volatile uint32_t *)0xfe036750)
#define P_DMC_DRAM_RDBI0 ((volatile uint32_t *)0xfe036754)
// MPC RD FIFO command DBI read back data
// bit 31:16  the second cycle.
// bit 15:0   the first cycle.
#define P_DMC_DRAM_RDBI1 ((volatile uint32_t *)0xfe036758)
// MPC RD FIFO command DBI read back data
// bit 31:16. the Forth cycle.
// bit 15:0.  the third cycle.
// WD0~16 and RD0~16 can be used as MRW command as Frequency change .
// WD0~16 is for Freq1 DRAM MR setting, it would send to DRAM right before FREQ0-> FREQ1
// RD0_16 is for Freq0 DRAM MR setting. it would send to DRAM right before FREQ1-> FREQ0.
// each register can be one MRW command. So total 16 MRW command can be sent to DRAM.
// The register formats:
// bit 31.   MRW/USER command enable.  1: enabled command. 0 not enabled.
// bit 30.   last MRW/USER command.   if this bit =1, After send this command, the DRAM controller
// will contine frequency next stage. bit 29:26. USER COMMAND parameter: in DDR3/DDR4.  {act_n,
// ras_n, cas_n, we_n} value for user command in LPDDR4.  bit 16: 1 4 cycles command.  0 2 cycles
// command. bit 25     MRW/USER command rank 1 select.  1: select.  0: not select. bit 24. MRW/USER
// command rank 0 select.  1: select.  0: not select. bit 23:0.  USER command. DDR3:    18:16 bank
// address. 15:0:  address. DDR4:    20:19 bank group address.   18:16: bank address. 15:0 address.
// LPDDR3:   9:0. rising edge address.  19:10.  falling edge address.
// LPDDR4.   5:0, first edge address,  11:6 second edge address, 17:12: third edge address. 23:18,
// forth edge address. MRW command format: bit 23:16  MR addr.  DDR4 case :  18:16 ba[2:0]. 20:19
// BG[1:0]. bit 15:0   opcode.
#define P_DMC_DRAM_WD0 ((volatile uint32_t *)0xfe036780)
#define P_DMC_DRAM_WD1 ((volatile uint32_t *)0xfe036784)
#define P_DMC_DRAM_WD2 ((volatile uint32_t *)0xfe036788)
#define P_DMC_DRAM_WD3 ((volatile uint32_t *)0xfe03678c)
#define P_DMC_DRAM_WD4 ((volatile uint32_t *)0xfe036790)
#define P_DMC_DRAM_WD5 ((volatile uint32_t *)0xfe036794)
#define P_DMC_DRAM_WD6 ((volatile uint32_t *)0xfe036798)
#define P_DMC_DRAM_WD7 ((volatile uint32_t *)0xfe03679c)
#define P_DMC_DRAM_WD8 ((volatile uint32_t *)0xfe0367a0)
#define P_DMC_DRAM_WD9 ((volatile uint32_t *)0xfe0367a4)
#define P_DMC_DRAM_WD10 ((volatile uint32_t *)0xfe0367a8)
#define P_DMC_DRAM_WD11 ((volatile uint32_t *)0xfe0367ac)
#define P_DMC_DRAM_WD12 ((volatile uint32_t *)0xfe0367b0)
#define P_DMC_DRAM_WD13 ((volatile uint32_t *)0xfe0367b4)
#define P_DMC_DRAM_WD14 ((volatile uint32_t *)0xfe0367b8)
#define P_DMC_DRAM_WD15 ((volatile uint32_t *)0xfe0367bc)
#define P_DMC_DRAM_RD0 ((volatile uint32_t *)0xfe0367c0)
#define P_DMC_DRAM_RD1 ((volatile uint32_t *)0xfe0367c4)
#define P_DMC_DRAM_RD2 ((volatile uint32_t *)0xfe0367c8)
#define P_DMC_DRAM_RD3 ((volatile uint32_t *)0xfe0367cc)
#define P_DMC_DRAM_RD4 ((volatile uint32_t *)0xfe0367d0)
#define P_DMC_DRAM_RD5 ((volatile uint32_t *)0xfe0367d4)
#define P_DMC_DRAM_RD6 ((volatile uint32_t *)0xfe0367d8)
#define P_DMC_DRAM_RD7 ((volatile uint32_t *)0xfe0367dc)
#define P_DMC_DRAM_RD8 ((volatile uint32_t *)0xfe0367e0)
#define P_DMC_DRAM_RD9 ((volatile uint32_t *)0xfe0367e4)
#define P_DMC_DRAM_RD10 ((volatile uint32_t *)0xfe0367e8)
#define P_DMC_DRAM_RD11 ((volatile uint32_t *)0xfe0367ec)
#define P_DMC_DRAM_RD12 ((volatile uint32_t *)0xfe0367f0)
#define P_DMC_DRAM_RD13 ((volatile uint32_t *)0xfe0367f4)
#define P_DMC_DRAM_RD14 ((volatile uint32_t *)0xfe0367f8)
#define P_DMC_DRAM_RD15 ((volatile uint32_t *)0xfe0367fc)
//`define DMC_STICKY_REG_BASE   32'hfe036800
// -----------------------------------------------
// REG_BASE:  APB1_BASE_ADDR = 0xfe036800
// -----------------------------------------------
// those register is for software save some tempary value. and because it's in RAM. it won't lose
// if DMC get reseted.
#define P_DMC_STICKY_0 ((volatile uint32_t *)0xfe036800)
#define P_DMC_STICKY_1 ((volatile uint32_t *)0xfe036804)
#define P_DMC_STICKY_2 ((volatile uint32_t *)0xfe036808)
#define P_DMC_STICKY_3 ((volatile uint32_t *)0xfe03680c)
#define P_DMC_STICKY_4 ((volatile uint32_t *)0xfe036810)
#define P_DMC_STICKY_5 ((volatile uint32_t *)0xfe036814)
#define P_DMC_STICKY_6 ((volatile uint32_t *)0xfe036818)
#define P_DMC_STICKY_7 ((volatile uint32_t *)0xfe03681c)
#define P_DMC_STICKY_8 ((volatile uint32_t *)0xfe036820)
#define P_DMC_STICKY_9 ((volatile uint32_t *)0xfe036824)
#define P_DMC_STICKY_10 ((volatile uint32_t *)0xfe036828)
#define P_DMC_STICKY_11 ((volatile uint32_t *)0xfe03682c)
#define P_DMC_STICKY_12 ((volatile uint32_t *)0xfe036830)
#define P_DMC_STICKY_13 ((volatile uint32_t *)0xfe036834)
#define P_DMC_STICKY_14 ((volatile uint32_t *)0xfe036838)
#define P_DMC_STICKY_15 ((volatile uint32_t *)0xfe03683c)
#define P_DMC_STICKY_16 ((volatile uint32_t *)0xfe036840)
#define P_DMC_STICKY_17 ((volatile uint32_t *)0xfe036844)
#define P_DMC_STICKY_18 ((volatile uint32_t *)0xfe036848)
#define P_DMC_STICKY_19 ((volatile uint32_t *)0xfe03684c)
#define P_DMC_STICKY_20 ((volatile uint32_t *)0xfe036850)
#define P_DMC_STICKY_21 ((volatile uint32_t *)0xfe036854)
#define P_DMC_STICKY_22 ((volatile uint32_t *)0xfe036858)
#define P_DMC_STICKY_23 ((volatile uint32_t *)0xfe03685c)
#define P_DMC_STICKY_24 ((volatile uint32_t *)0xfe036860)
#define P_DMC_STICKY_25 ((volatile uint32_t *)0xfe036864)
#define P_DMC_STICKY_26 ((volatile uint32_t *)0xfe036868)
#define P_DMC_STICKY_27 ((volatile uint32_t *)0xfe03686c)
#define P_DMC_STICKY_28 ((volatile uint32_t *)0xfe036870)
#define P_DMC_STICKY_29 ((volatile uint32_t *)0xfe036874)
#define P_DMC_STICKY_30 ((volatile uint32_t *)0xfe036878)
#define P_DMC_STICKY_31 ((volatile uint32_t *)0xfe03687c)
#define P_DMC_STICKY_32 ((volatile uint32_t *)0xfe036880)
#define P_DMC_STICKY_33 ((volatile uint32_t *)0xfe036884)
#define P_DMC_STICKY_34 ((volatile uint32_t *)0xfe036888)
#define P_DMC_STICKY_35 ((volatile uint32_t *)0xfe03688c)
#define P_DMC_STICKY_36 ((volatile uint32_t *)0xfe036890)
#define P_DMC_STICKY_37 ((volatile uint32_t *)0xfe036894)
#define P_DMC_STICKY_38 ((volatile uint32_t *)0xfe036898)
#define P_DMC_STICKY_39 ((volatile uint32_t *)0xfe03689c)
#define P_DMC_STICKY_40 ((volatile uint32_t *)0xfe0368a0)
#define P_DMC_STICKY_41 ((volatile uint32_t *)0xfe0368a4)
#define P_DMC_STICKY_42 ((volatile uint32_t *)0xfe0368a8)
#define P_DMC_STICKY_43 ((volatile uint32_t *)0xfe0368ac)
#define P_DMC_STICKY_44 ((volatile uint32_t *)0xfe0368b0)
#define P_DMC_STICKY_45 ((volatile uint32_t *)0xfe0368b4)
#define P_DMC_STICKY_46 ((volatile uint32_t *)0xfe0368b8)
#define P_DMC_STICKY_47 ((volatile uint32_t *)0xfe0368bc)
#define P_DMC_STICKY_48 ((volatile uint32_t *)0xfe0368c0)
#define P_DMC_STICKY_49 ((volatile uint32_t *)0xfe0368c4)
#define P_DMC_STICKY_50 ((volatile uint32_t *)0xfe0368c8)
#define P_DMC_STICKY_51 ((volatile uint32_t *)0xfe0368cc)
#define P_DMC_STICKY_52 ((volatile uint32_t *)0xfe0368d0)
#define P_DMC_STICKY_53 ((volatile uint32_t *)0xfe0368d4)
#define P_DMC_STICKY_54 ((volatile uint32_t *)0xfe0368d8)
#define P_DMC_STICKY_55 ((volatile uint32_t *)0xfe0368dc)
#define P_DMC_STICKY_56 ((volatile uint32_t *)0xfe0368e0)
#define P_DMC_STICKY_57 ((volatile uint32_t *)0xfe0368e4)
#define P_DMC_STICKY_58 ((volatile uint32_t *)0xfe0368e8)
#define P_DMC_STICKY_59 ((volatile uint32_t *)0xfe0368ec)
#define P_DMC_STICKY_60 ((volatile uint32_t *)0xfe0368f0)
#define P_DMC_STICKY_61 ((volatile uint32_t *)0xfe0368f4)
#define P_DMC_STICKY_62 ((volatile uint32_t *)0xfe0368f8)
#define P_DMC_STICKY_63 ((volatile uint32_t *)0xfe0368fc)
//`define DMC_SEC_REG_BASE                32'hfe037000
// -----------------------------------------------
// REG_BASE:  APB1_BASE_ADDR = 0xfe037000
// -----------------------------------------------
// DMC use 15bits ID to identify the input ports and ID.
// bit 14:10.
// AXI bus ID number from 0 ~15.  2, 8~10, 12~15 Not used the others defined as bellow.
// 0 : CPU and MALI.   Mali and cpu will be separated to 2 channel. CPU traffic will be assigned
// to ID = 0. Mali traffic will assigned to ID =1. 1 : Mali 3 : HDMI. 4 : HEVC.   //HEVC_F/B
// combined to one 5 : TEST. 6 : USB 7 : Device.
// 11 : DEMUX
// 16: VPU read 0.
// 17: VPU read 1.
// 18: VPU read 2.
// 19: VPU write 0.
// 20: VPU write 1.
// 21: VDEC.
// 22: HCODEC.
// 23: ge2d.
// control bit for  SubID functions for all the input.
// ARM   2 bit.    HPROT[1] == 0 : SECURE CPU;   HPROT[1] == 1 : NONSEC CPU.
// GPU   2 bit.    HPROT[2] == 1 : SECURE GPU;   HPROT[2] == 0 : NONSEC GPU access;
// HDCP  4 bits.   ID AR/AWID[1:0].
// HEVC  9 bits.   HEVC use ARUSER/AWUSER[3:0] 16 levels of security control.
// TEST  1 type.
// USB   1 type.
// DEVICE  DMA    : AR/AWID[7:3] == 4'h2.  8bits control   use AR/WID[3:1].
//         AUDIO  : AR/AWID[7:3] == 4'h6.  8bits control.  use AR/AWID[2:0].
//         the others total 16 bits use AR/AWID[7:3].  bit 2 and bit 6 not used.
// VPU the 5 VPU ports use ARSEC/AWSEC as the secruity control.
// VDEC  total 16bits.  use AR/WID[5:2]
// GE2D. total 3bits.  2 read bits, check ARID[0].  1 write bit.   AWID dont care.
// there's total 16 ranges in the whole memory range.
// 15 ranges can be defined in 64kbyte boundary start address and end address.
// the 16th range is all other space not defined by 15 ranges.
// Each range can be enabled or disabled and  each range use security level bit to select key to
// do data scramble. The ranges can be overlapped or crossover.  But from 0 to 15 ranges, the
// earlier has higher priority.
#define P_DMC_SEC_RANGE0_CTRL ((volatile uint32_t *)0xfe037000)
// bit 31:16   | 0 | range0_eda | range 0 end address  higher 16bits.
// bit 15:0    | 0 | range0_sta | range 0 start address higher 16bits.
#define P_DMC_SEC_RANGE0_CTRL1 ((volatile uint32_t *)0xfe037004)
// bit 7:5 | 0 | range0_secrity_level | range0 secruity level for DMC and DEMUX only.
// bit 4  | 0 | range0_prot_en       | range0 allow protect monitor function.  1: allowed.  0: not
// allowed. bit 3  | 0 | range0_local_des_en  | range0 data describle enable.  1: enable. 0 :
// disable. this bit works together with GLOBAL_DES_EN to decide this region data describle enable
// or not. bit 2  | 0 | range0_lock  |  lock range 0 registers. write 1 to lock range 0 register.
// can't change anymore. bit 1  | 0 | range0_key_sel | range 0 data describle key selection.  1 :
// key1. 0 : key0. bit 0  | 0 | range0_en    | range 0 enable bit. 1 : enable, 0 : disable.
#define P_DMC_SEC_RANGE1_CTRL ((volatile uint32_t *)0xfe037008)
// bit 31:16   | 0 | range1_eda | range 1 end address  higher 16bits.
// bit 15:0    | 0 | range1_sta | range 1 start address higher 16bits.
#define P_DMC_SEC_RANGE1_CTRL1 ((volatile uint32_t *)0xfe03700c)
// bit 7:5 | 0 | range1_secrity_level | range1 secruity level for DMC and DEMUX only.
// bit 4  | 0 | range1_prot_en       | range1 allow protect monitor function.  1: allowed.  0: not
// allowed. bit 3  | 0 | range1_local_des_en  | range1 data describle enable.  1: enable. 0 :
// disable. this bit works together with GLOBAL_DES_EN to decide this region data describle enable
// or not. bit 2  | 0 | range1_lock  |  lock range 1 registers. write 1 to lock range 1 register.
// can't change anymore. bit 1  | 0 | range1_key_sel | range 1 data describle key selection.  1 :
// key1. 1 : key0. bit 0  | 0 | range1_en    | range 0 enable bit. 1 : enable, 0 : disable.
#define P_DMC_SEC_RANGE2_CTRL ((volatile uint32_t *)0xfe037010)
// bit 31:16   | 0 | range2_eda | range 2 end address  higher 16bits.
// bit 15:0    | 0 | range2_sta | range 2 start address higher 16bits.
#define P_DMC_SEC_RANGE2_CTRL1 ((volatile uint32_t *)0xfe037014)
// bit 7:5 | 0 | range2_secrity_level | range2 secruity level for DMC and DEMUX only.
// bit 4  | 0 | range2_prot_en       | range2 allow protect monitor function.  1: allowed.  0: not
// allowed. bit 3  | 0 | range2_local_des_en  | range2 data describle enable.  1: enable. 0 :
// disable. this bit works together with GLOBAL_DES to decide this region data describle enable or
// not. bit 2  | 0 | range2_lock  |  lock range 2 registers. write 1 to lock range 2 register.
// can't change anymore. bit 1  | 0 | range2_key_sel | range 2 data describle key selection.  1 :
// key1. 1 : key0. bit 0  | 0 | range2_en    | range 2 enable bit. 1 : enable, 0 : disable.
#define P_DMC_SEC_RANGE3_CTRL ((volatile uint32_t *)0xfe037018)
// bit 31:16   | 0 | range3_eda | range 3 end address  higher 16bits.
// bit 15:0    | 0 | range3_sta | range 3 start address higher 16bits.
#define P_DMC_SEC_RANGE3_CTRL1 ((volatile uint32_t *)0xfe03701c)
// bit 7:5 | 0 | range3_secrity_level | range3 secruity level for DMC and DEMUX only.
// bit 4  | 0 | range3_prot_en       | range3 allow protect monitor function.  1: allowed.  0: not
// allowed. bit 3  | 0 | range3_local_des_en  | range3 data describle enable.  1: enable. 0 :
// disable. this bit works together with GLOBAL_DES to decide this region data describle enable or
// not. bit 2  | 0 | range3_lock    | lock range 3 registers. write 1 to lock range 3 related
// registers. can't change anymore. bit 1  | 0 | range3_key_sel | range 3 data describle key
// selection.  1 : key1. 1 : key0. bit 0  | 0 | range3_en      | range 3 enable bit. 1 : enable, 0
// : disable.
#define P_DMC_SEC_RANGE4_CTRL ((volatile uint32_t *)0xfe037020)
// bit 31:16   | 0 | range4_eda | range 4 end address  higher 16bits.
// bit 15:0    | 0 | range4_sta | range 4 start address higher 16bits.
#define P_DMC_SEC_RANGE4_CTRL1 ((volatile uint32_t *)0xfe037024)
// bit 7:5 | 0 | range4_secrity_level | range4 secruity level for DMC and DEMUX only.
// bit 4  | 0 | range4_prot_en       | range4 allow protect monitor function.  1: allowed.  0: not
// allowed. bit 3  | 0 | range4_local_des_en  | range4 data describle enable.  1: enable. 0 :
// disable. this bit works together with GLOBAL_DES to decide this region data describle enable or
// not. bit 2  | 0 | range4_lock    | lock range 4 registers. write 1 to lock range 4 related
// registers. can't change anymore. bit 1  | 0 | range4_key_sel | range 4 data describle key
// selection.  1 : key1. 1 : key0. bit 0  | 0 | range4_en      | range 4 enable bit. 1 : enable, 0
// : disable.
#define P_DMC_SEC_RANGE5_CTRL ((volatile uint32_t *)0xfe037028)
#define P_DMC_SEC_RANGE5_CTRL1 ((volatile uint32_t *)0xfe03702c)
#define P_DMC_SEC_RANGE6_CTRL ((volatile uint32_t *)0xfe037030)
#define P_DMC_SEC_RANGE6_CTRL1 ((volatile uint32_t *)0xfe037034)
#define P_DMC_SEC_RANGE7_CTRL ((volatile uint32_t *)0xfe037038)
#define P_DMC_SEC_RANGE7_CTRL1 ((volatile uint32_t *)0xfe03703c)
#define P_DMC_SEC_RANGE8_CTRL ((volatile uint32_t *)0xfe037040)
#define P_DMC_SEC_RANGE8_CTRL1 ((volatile uint32_t *)0xfe037044)
#define P_DMC_SEC_RANGE9_CTRL ((volatile uint32_t *)0xfe037048)
#define P_DMC_SEC_RANGE9_CTRL1 ((volatile uint32_t *)0xfe03704c)
#define P_DMC_SEC_RANGE10_CTRL ((volatile uint32_t *)0xfe037050)
#define P_DMC_SEC_RANGE10_CTRL1 ((volatile uint32_t *)0xfe037054)
#define P_DMC_SEC_RANGE11_CTRL ((volatile uint32_t *)0xfe037058)
#define P_DMC_SEC_RANGE11_CTRL1 ((volatile uint32_t *)0xfe03705c)
#define P_DMC_SEC_RANGE12_CTRL ((volatile uint32_t *)0xfe037060)
#define P_DMC_SEC_RANGE12_CTRL1 ((volatile uint32_t *)0xfe037064)
#define P_DMC_SEC_RANGE13_CTRL ((volatile uint32_t *)0xfe037068)
#define P_DMC_SEC_RANGE13_CTRL1 ((volatile uint32_t *)0xfe03706c)
#define P_DMC_SEC_RANGE14_CTRL ((volatile uint32_t *)0xfe037070)
#define P_DMC_SEC_RANGE14_CTRL1 ((volatile uint32_t *)0xfe037074)
#define P_DMC_SEC_RANGE15_CTRL1 ((volatile uint32_t *)0xfe03707c)
// default : 0
// bit 7:5 | 0 | range1_secrity_level | range1 secruity level for DMC and DEMUX only.
// bit 4  | 0 | range1_prot_en       | range1 allow protect monitor function.  1: allowed.  0: not
// allowed. bit 3  | 0 | range1_local_des_en  | range1 data describle enable.  1: enable. 0 :
// disable. this bit works together with GLOBAL_DES_EN to decide this region data describle enable
// or not. bit 2  | 0 | range1_lock  |  lock range 1 registers. write 1 to lock range 1 register.
// can't change anymore. bit 1  | 0 | range1_key_sel | range 1 data describle key selection.  1 :
// key1. 1 : key0. bit 0  | 0 | not used. range 15 is always enabled. for each range there's 96bits
// read/write subid control to control all master DDR access. the 96bits assignments
// rangex_rd_sid_en[95:0] and rangx_wr_sid_en[95:0] is as below: bit 3:0. for CPU
// ARPROT[2:1]/AWPROT[2:1] selection. CPU ARPROT[2:1] /AWPROT[2:1] define: bit0 PROT[2:1]==00: data
// secure access. bit1 PROT[2:1]==01:   data non-secure access. bit2 PROT[2:1] 10:    instruction
// secure access. bit3 PROT[2:1] 11:    instruction non-secure access. per range per sub ID access
// enable.
#define P_DMC_SEC_RANGE0_RID_CTRL0 ((volatile uint32_t *)0xfe037080)
// default : 0
// range0_rd_sid_en[31:0];
#define P_DMC_SEC_RANGE0_RID_CTRL1 ((volatile uint32_t *)0xfe037084)
// default : 0
// range0_rd_sid_en[63:32];
#define P_DMC_SEC_RANGE0_RID_CTRL2 ((volatile uint32_t *)0xfe037088)
// default : 0
// range0_rd_sid_en[95:64];
#define P_DMC_SEC_RANGE0_RID_CTRL3 ((volatile uint32_t *)0xfe03708c)
// default : 0
// not used.
#define P_DMC_SEC_RANGE0_RID_CTRL4 ((volatile uint32_t *)0xfe037090)
// default : 0 not used in
#define P_DMC_SEC_RANGE1_RID_CTRL0 ((volatile uint32_t *)0xfe037098)
// default : 0
// range1_rd_sid_en[31:0];
#define P_DMC_SEC_RANGE1_RID_CTRL1 ((volatile uint32_t *)0xfe03709c)
// default : 0
// range1_rd_sid_en[63:32];
#define P_DMC_SEC_RANGE1_RID_CTRL2 ((volatile uint32_t *)0xfe0370a0)
// default : 0
// range1_rd_sid_en[95:64];
#define P_DMC_SEC_RANGE1_RID_CTRL3 ((volatile uint32_t *)0xfe0370a4)
// not used.
#define P_DMC_SEC_RANGE1_RID_CTRL4 ((volatile uint32_t *)0xfe0370a8)
// not used.
#define P_DMC_SEC_RANGE2_RID_CTRL0 ((volatile uint32_t *)0xfe0370b0)
#define P_DMC_SEC_RANGE2_RID_CTRL1 ((volatile uint32_t *)0xfe0370b4)
#define P_DMC_SEC_RANGE2_RID_CTRL2 ((volatile uint32_t *)0xfe0370b8)
#define P_DMC_SEC_RANGE2_RID_CTRL3 ((volatile uint32_t *)0xfe0370bc)
// not used.
#define P_DMC_SEC_RANGE2_RID_CTRL4 ((volatile uint32_t *)0xfe0370c0)
// not used.
#define P_DMC_SEC_RANGE3_RID_CTRL0 ((volatile uint32_t *)0xfe0370c8)
#define P_DMC_SEC_RANGE3_RID_CTRL1 ((volatile uint32_t *)0xfe0370cc)
#define P_DMC_SEC_RANGE3_RID_CTRL2 ((volatile uint32_t *)0xfe0370d0)
#define P_DMC_SEC_RANGE3_RID_CTRL3 ((volatile uint32_t *)0xfe0370d4)
// not used.                                                                        )
#define P_DMC_SEC_RANGE3_RID_CTRL4 ((volatile uint32_t *)0xfe0370d8)
// not used.                                                                        )
#define P_DMC_SEC_RANGE4_RID_CTRL0 ((volatile uint32_t *)0xfe0370e0)
#define P_DMC_SEC_RANGE4_RID_CTRL1 ((volatile uint32_t *)0xfe0370e4)
#define P_DMC_SEC_RANGE4_RID_CTRL2 ((volatile uint32_t *)0xfe0370e8)
#define P_DMC_SEC_RANGE4_RID_CTRL3 ((volatile uint32_t *)0xfe0370ec)
// not used.
#define P_DMC_SEC_RANGE4_RID_CTRL4 ((volatile uint32_t *)0xfe0370f0)
// not used.
#define P_DMC_SEC_RANGE5_RID_CTRL0 ((volatile uint32_t *)0xfe0370f8)
#define P_DMC_SEC_RANGE5_RID_CTRL1 ((volatile uint32_t *)0xfe0370fc)
#define P_DMC_SEC_RANGE5_RID_CTRL2 ((volatile uint32_t *)0xfe037100)
#define P_DMC_SEC_RANGE5_RID_CTRL3 ((volatile uint32_t *)0xfe037104)
// not used.
#define P_DMC_SEC_RANGE5_RID_CTRL4 ((volatile uint32_t *)0xfe037108)
// not used.
#define P_DMC_SEC_RANGE6_RID_CTRL0 ((volatile uint32_t *)0xfe037110)
#define P_DMC_SEC_RANGE6_RID_CTRL1 ((volatile uint32_t *)0xfe037114)
#define P_DMC_SEC_RANGE6_RID_CTRL2 ((volatile uint32_t *)0xfe037118)
#define P_DMC_SEC_RANGE6_RID_CTRL3 ((volatile uint32_t *)0xfe03711c)
// not used.
#define P_DMC_SEC_RANGE6_RID_CTRL4 ((volatile uint32_t *)0xfe037120)
// not used.
#define P_DMC_SEC_RANGE7_RID_CTRL0 ((volatile uint32_t *)0xfe037128)
#define P_DMC_SEC_RANGE7_RID_CTRL1 ((volatile uint32_t *)0xfe03712c)
#define P_DMC_SEC_RANGE7_RID_CTRL2 ((volatile uint32_t *)0xfe037130)
#define P_DMC_SEC_RANGE7_RID_CTRL3 ((volatile uint32_t *)0xfe037134)
// not used.
#define P_DMC_SEC_RANGE7_RID_CTRL4 ((volatile uint32_t *)0xfe037138)
// not used.
#define P_DMC_SEC_RANGE8_RID_CTRL0 ((volatile uint32_t *)0xfe037140)
#define P_DMC_SEC_RANGE8_RID_CTRL1 ((volatile uint32_t *)0xfe037144)
#define P_DMC_SEC_RANGE8_RID_CTRL2 ((volatile uint32_t *)0xfe037148)
#define P_DMC_SEC_RANGE8_RID_CTRL3 ((volatile uint32_t *)0xfe03714c)
// not used.
#define P_DMC_SEC_RANGE8_RID_CTRL4 ((volatile uint32_t *)0xfe037150)
// not used.
#define P_DMC_SEC_RANGE9_RID_CTRL0 ((volatile uint32_t *)0xfe037158)
#define P_DMC_SEC_RANGE9_RID_CTRL1 ((volatile uint32_t *)0xfe03715c)
#define P_DMC_SEC_RANGE9_RID_CTRL2 ((volatile uint32_t *)0xfe037160)
#define P_DMC_SEC_RANGE9_RID_CTRL3 ((volatile uint32_t *)0xfe037164)
#define P_DMC_SEC_RANGE9_RID_CTRL4 ((volatile uint32_t *)0xfe037168)
#define P_DMC_SEC_RANGE10_RID_CTRL0 ((volatile uint32_t *)0xfe037170)
#define P_DMC_SEC_RANGE10_RID_CTRL1 ((volatile uint32_t *)0xfe037174)
#define P_DMC_SEC_RANGE10_RID_CTRL2 ((volatile uint32_t *)0xfe037178)
#define P_DMC_SEC_RANGE10_RID_CTRL3 ((volatile uint32_t *)0xfe03717c)
#define P_DMC_SEC_RANGE10_RID_CTRL4 ((volatile uint32_t *)0xfe037180)
#define P_DMC_SEC_RANGE11_RID_CTRL0 ((volatile uint32_t *)0xfe037188)
#define P_DMC_SEC_RANGE11_RID_CTRL1 ((volatile uint32_t *)0xfe03718c)
#define P_DMC_SEC_RANGE11_RID_CTRL2 ((volatile uint32_t *)0xfe037190)
#define P_DMC_SEC_RANGE11_RID_CTRL3 ((volatile uint32_t *)0xfe037194)
#define P_DMC_SEC_RANGE11_RID_CTRL4 ((volatile uint32_t *)0xfe037198)
#define P_DMC_SEC_RANGE12_RID_CTRL0 ((volatile uint32_t *)0xfe0371a0)
#define P_DMC_SEC_RANGE12_RID_CTRL1 ((volatile uint32_t *)0xfe0371a4)
#define P_DMC_SEC_RANGE12_RID_CTRL2 ((volatile uint32_t *)0xfe0371a8)
#define P_DMC_SEC_RANGE12_RID_CTRL3 ((volatile uint32_t *)0xfe0371ac)
#define P_DMC_SEC_RANGE12_RID_CTRL4 ((volatile uint32_t *)0xfe0371b0)
#define P_DMC_SEC_RANGE13_RID_CTRL0 ((volatile uint32_t *)0xfe0371b8)
#define P_DMC_SEC_RANGE13_RID_CTRL1 ((volatile uint32_t *)0xfe0371bc)
#define P_DMC_SEC_RANGE13_RID_CTRL2 ((volatile uint32_t *)0xfe0371c0)
#define P_DMC_SEC_RANGE13_RID_CTRL3 ((volatile uint32_t *)0xfe0371c4)
#define P_DMC_SEC_RANGE13_RID_CTRL4 ((volatile uint32_t *)0xfe0371c8)
#define P_DMC_SEC_RANGE14_RID_CTRL0 ((volatile uint32_t *)0xfe0371d0)
#define P_DMC_SEC_RANGE14_RID_CTRL1 ((volatile uint32_t *)0xfe0371d4)
#define P_DMC_SEC_RANGE14_RID_CTRL2 ((volatile uint32_t *)0xfe0371d8)
#define P_DMC_SEC_RANGE14_RID_CTRL3 ((volatile uint32_t *)0xfe0371dc)
#define P_DMC_SEC_RANGE14_RID_CTRL4 ((volatile uint32_t *)0xfe0371e0)
#define P_DMC_SEC_RANGE15_RID_CTRL0 ((volatile uint32_t *)0xfe0371e8)
#define P_DMC_SEC_RANGE15_RID_CTRL1 ((volatile uint32_t *)0xfe0371ec)
#define P_DMC_SEC_RANGE15_RID_CTRL2 ((volatile uint32_t *)0xfe0371f0)
#define P_DMC_SEC_RANGE15_RID_CTRL3 ((volatile uint32_t *)0xfe0371f4)
#define P_DMC_SEC_RANGE15_RID_CTRL4 ((volatile uint32_t *)0xfe0371f8)
// per range per sub ID access enable.
#define P_DMC_SEC_RANGE0_WID_CTRL0 ((volatile uint32_t *)0xfe037200)
// default : 0
// range0_wr_sid_en[31:0];
#define P_DMC_SEC_RANGE0_WID_CTRL1 ((volatile uint32_t *)0xfe037204)
// default : 0
// range0_wr_sid_en[63:32];
#define P_DMC_SEC_RANGE0_WID_CTRL2 ((volatile uint32_t *)0xfe037208)
// default : 0
// range0_wr_sid_en[95:64];
#define P_DMC_SEC_RANGE0_WID_CTRL3 ((volatile uint32_t *)0xfe03720c)
// not used.
#define P_DMC_SEC_RANGE0_WID_CTRL4 ((volatile uint32_t *)0xfe037210)
// not used.
#define P_DMC_SEC_RANGE1_WID_CTRL0 ((volatile uint32_t *)0xfe037218)
// default : 0
// range1_wr_sid_en[31:0];
#define P_DMC_SEC_RANGE1_WID_CTRL1 ((volatile uint32_t *)0xfe03721c)
// default : 0
// range1_wr_sid_en[63:32];
#define P_DMC_SEC_RANGE1_WID_CTRL2 ((volatile uint32_t *)0xfe037220)
// default : 0
// range1_wr_sid_en[95:64];
#define P_DMC_SEC_RANGE1_WID_CTRL3 ((volatile uint32_t *)0xfe037224)
// not used.
#define P_DMC_SEC_RANGE1_WID_CTRL4 ((volatile uint32_t *)0xfe037228)
// not used.
#define P_DMC_SEC_RANGE2_WID_CTRL0 ((volatile uint32_t *)0xfe037230)
#define P_DMC_SEC_RANGE2_WID_CTRL1 ((volatile uint32_t *)0xfe037234)
#define P_DMC_SEC_RANGE2_WID_CTRL2 ((volatile uint32_t *)0xfe037238)
#define P_DMC_SEC_RANGE2_WID_CTRL3 ((volatile uint32_t *)0xfe03723c)
#define P_DMC_SEC_RANGE2_WID_CTRL4 ((volatile uint32_t *)0xfe037240)
#define P_DMC_SEC_RANGE3_WID_CTRL0 ((volatile uint32_t *)0xfe037248)
#define P_DMC_SEC_RANGE3_WID_CTRL1 ((volatile uint32_t *)0xfe03724c)
#define P_DMC_SEC_RANGE3_WID_CTRL2 ((volatile uint32_t *)0xfe037250)
#define P_DMC_SEC_RANGE3_WID_CTRL3 ((volatile uint32_t *)0xfe037254)
#define P_DMC_SEC_RANGE3_WID_CTRL4 ((volatile uint32_t *)0xfe037258)
#define P_DMC_SEC_RANGE4_WID_CTRL0 ((volatile uint32_t *)0xfe037260)
#define P_DMC_SEC_RANGE4_WID_CTRL1 ((volatile uint32_t *)0xfe037264)
#define P_DMC_SEC_RANGE4_WID_CTRL2 ((volatile uint32_t *)0xfe037268)
#define P_DMC_SEC_RANGE4_WID_CTRL3 ((volatile uint32_t *)0xfe03726c)
#define P_DMC_SEC_RANGE4_WID_CTRL4 ((volatile uint32_t *)0xfe037270)
#define P_DMC_SEC_RANGE5_WID_CTRL0 ((volatile uint32_t *)0xfe037278)
#define P_DMC_SEC_RANGE5_WID_CTRL1 ((volatile uint32_t *)0xfe03727c)
#define P_DMC_SEC_RANGE5_WID_CTRL2 ((volatile uint32_t *)0xfe037280)
#define P_DMC_SEC_RANGE5_WID_CTRL3 ((volatile uint32_t *)0xfe037284)
#define P_DMC_SEC_RANGE5_WID_CTRL4 ((volatile uint32_t *)0xfe037288)
#define P_DMC_SEC_RANGE6_WID_CTRL0 ((volatile uint32_t *)0xfe037290)
#define P_DMC_SEC_RANGE6_WID_CTRL1 ((volatile uint32_t *)0xfe037294)
#define P_DMC_SEC_RANGE6_WID_CTRL2 ((volatile uint32_t *)0xfe037298)
#define P_DMC_SEC_RANGE6_WID_CTRL3 ((volatile uint32_t *)0xfe03729c)
#define P_DMC_SEC_RANGE6_WID_CTRL4 ((volatile uint32_t *)0xfe0372a0)
#define P_DMC_SEC_RANGE7_WID_CTRL0 ((volatile uint32_t *)0xfe0372a8)
#define P_DMC_SEC_RANGE7_WID_CTRL1 ((volatile uint32_t *)0xfe0372ac)
#define P_DMC_SEC_RANGE7_WID_CTRL2 ((volatile uint32_t *)0xfe0372b0)
#define P_DMC_SEC_RANGE7_WID_CTRL3 ((volatile uint32_t *)0xfe0372b4)
#define P_DMC_SEC_RANGE7_WID_CTRL4 ((volatile uint32_t *)0xfe0372b8)
#define P_DMC_SEC_RANGE8_WID_CTRL0 ((volatile uint32_t *)0xfe0372c0)
#define P_DMC_SEC_RANGE8_WID_CTRL1 ((volatile uint32_t *)0xfe0372c4)
#define P_DMC_SEC_RANGE8_WID_CTRL2 ((volatile uint32_t *)0xfe0372c8)
#define P_DMC_SEC_RANGE8_WID_CTRL3 ((volatile uint32_t *)0xfe0372cc)
#define P_DMC_SEC_RANGE8_WID_CTRL4 ((volatile uint32_t *)0xfe0372d0)
#define P_DMC_SEC_RANGE9_WID_CTRL0 ((volatile uint32_t *)0xfe0372d8)
#define P_DMC_SEC_RANGE9_WID_CTRL1 ((volatile uint32_t *)0xfe0372dc)
#define P_DMC_SEC_RANGE9_WID_CTRL2 ((volatile uint32_t *)0xfe0372e0)
#define P_DMC_SEC_RANGE9_WID_CTRL3 ((volatile uint32_t *)0xfe0372e4)
#define P_DMC_SEC_RANGE9_WID_CTRL4 ((volatile uint32_t *)0xfe0372e8)
#define P_DMC_SEC_RANGE10_WID_CTRL0 ((volatile uint32_t *)0xfe0372f0)
#define P_DMC_SEC_RANGE10_WID_CTRL1 ((volatile uint32_t *)0xfe0372f4)
#define P_DMC_SEC_RANGE10_WID_CTRL2 ((volatile uint32_t *)0xfe0372f8)
#define P_DMC_SEC_RANGE10_WID_CTRL3 ((volatile uint32_t *)0xfe0372fc)
#define P_DMC_SEC_RANGE10_WID_CTRL4 ((volatile uint32_t *)0xfe037300)
#define P_DMC_SEC_RANGE11_WID_CTRL0 ((volatile uint32_t *)0xfe037308)
#define P_DMC_SEC_RANGE11_WID_CTRL1 ((volatile uint32_t *)0xfe03730c)
#define P_DMC_SEC_RANGE11_WID_CTRL2 ((volatile uint32_t *)0xfe037310)
#define P_DMC_SEC_RANGE11_WID_CTRL3 ((volatile uint32_t *)0xfe037314)
#define P_DMC_SEC_RANGE11_WID_CTRL4 ((volatile uint32_t *)0xfe037318)
#define P_DMC_SEC_RANGE12_WID_CTRL0 ((volatile uint32_t *)0xfe037320)
#define P_DMC_SEC_RANGE12_WID_CTRL1 ((volatile uint32_t *)0xfe037324)
#define P_DMC_SEC_RANGE12_WID_CTRL2 ((volatile uint32_t *)0xfe037328)
#define P_DMC_SEC_RANGE12_WID_CTRL3 ((volatile uint32_t *)0xfe03732c)
#define P_DMC_SEC_RANGE12_WID_CTRL4 ((volatile uint32_t *)0xfe037330)
#define P_DMC_SEC_RANGE13_WID_CTRL0 ((volatile uint32_t *)0xfe037338)
#define P_DMC_SEC_RANGE13_WID_CTRL1 ((volatile uint32_t *)0xfe03733c)
#define P_DMC_SEC_RANGE13_WID_CTRL2 ((volatile uint32_t *)0xfe037340)
#define P_DMC_SEC_RANGE13_WID_CTRL3 ((volatile uint32_t *)0xfe037344)
#define P_DMC_SEC_RANGE13_WID_CTRL4 ((volatile uint32_t *)0xfe037348)
#define P_DMC_SEC_RANGE14_WID_CTRL0 ((volatile uint32_t *)0xfe037350)
#define P_DMC_SEC_RANGE14_WID_CTRL1 ((volatile uint32_t *)0xfe037354)
#define P_DMC_SEC_RANGE14_WID_CTRL2 ((volatile uint32_t *)0xfe037358)
#define P_DMC_SEC_RANGE14_WID_CTRL3 ((volatile uint32_t *)0xfe03735c)
#define P_DMC_SEC_RANGE14_WID_CTRL4 ((volatile uint32_t *)0xfe037360)
#define P_DMC_SEC_RANGE15_WID_CTRL0 ((volatile uint32_t *)0xfe037368)
#define P_DMC_SEC_RANGE15_WID_CTRL1 ((volatile uint32_t *)0xfe03736c)
#define P_DMC_SEC_RANGE15_WID_CTRL2 ((volatile uint32_t *)0xfe037370)
#define P_DMC_SEC_RANGE15_WID_CTRL3 ((volatile uint32_t *)0xfe037374)
#define P_DMC_SEC_RANGE15_WID_CTRL4 ((volatile uint32_t *)0xfe037378)
#define P_DMC_DES_CTRL ((volatile uint32_t *)0xfe037384)
// bit 31 : range15_des_en policy : 1 range15_des_en = range15_local_des_en && GLOBAL_DES_EN. 0 :
// range15_des_en = range15_local_des_en ||  GLOBAL_DES_EN. bit 30 : range14_des_en policy : 1
// range14_des_en = range14_local_des_en && GLOBAL_DES_EN. 0 : range14_des_en =
// range14_local_des_en ||  GLOBAL_DES_EN. bit 29 : range13_des_en policy : 1 range13_des_en =
// range13_local_des_en && GLOBAL_DES_EN. 0 : range13_des_en = range13_local_des_en ||
// GLOBAL_DES_EN. bit 28 : range12_des_en policy : 1 range12_des_en = range12_local_des_en &&
// GLOBAL_DES_EN. 0 : range12_des_en = range12_local_des_en ||  GLOBAL_DES_EN. bit 27 :
// range11_des_en policy : 1 range11_des_en = range11_local_des_en && GLOBAL_DES_EN. 0 :
// range11_des_en = range11_local_des_en ||  GLOBAL_DES_EN. bit 26 : range10_des_en policy : 1
// range11_des_en = range10_local_des_en && GLOBAL_DES_EN. 0 : range10_des_en =
// range10_local_des_en ||  GLOBAL_DES_EN. bit 25 : range9_des_en policy  : 1  range9_des_en =
// range9_local_des_en && GLOBAL_DES_EN. 0 :  range9_des_en =  range9_local_des_en ||
// GLOBAL_DES_EN. bit 24 : range8_des_en policy  : 1  range8_des_en =  range8_local_des_en &&
// GLOBAL_DES_EN. 0 :  range8_des_en =  range8_local_des_en ||  GLOBAL_DES_EN. bit 23 :
// range7_des_en policy  : 1  range7_des_en =  range7_local_des_en && GLOBAL_DES_EN. 0 :
// range7_des_en =  range7_local_des_en ||  GLOBAL_DES_EN. bit 22 : range6_des_en policy  : 1
// range6_des_en =  range6_local_des_en && GLOBAL_DES_EN. 0 :  range6_des_en =  range6_local_des_en
// ||  GLOBAL_DES_EN. bit 21 : range5_des_en policy  : 1  range5_des_en =  range5_local_des_en &&
// GLOBAL_DES_EN. 0 :  range5_des_en =  range5_local_des_en ||  GLOBAL_DES_EN. bit 20 :
// range4_des_en policy  : 1  range4_des_en =  range4_local_des_en && GLOBAL_DES_EN. 0 :
// range4_des_en =  range4_local_des_en ||  GLOBAL_DES_EN. bit 19 : range3_des_en policy  : 1
// range3_des_en =  range3_local_des_en && GLOBAL_DES_EN. 0 :  range3_des_en =  range3_local_des_en
// ||  GLOBAL_DES_EN. bit 18 : range2_des_en policy  : 1  range2_des_en =  range2_local_des_en &&
// GLOBAL_DES_EN. 0 :  range2_des_en =  range2_local_des_en ||  GLOBAL_DES_EN. bit 17 :
// range1_des_en policy  : 1  range1_des_en =  range1_local_des_en && GLOBAL_DES_EN. 0 :
// range1_des_en =  range1_local_des_en ||  GLOBAL_DES_EN. bit 16 : range0_des_en policy  : 1
// range0_des_en =  range0_local_des_en && GLOBAL_DES_EN. 0 :  range0_des_en =  range0_local_des_en
// ||  GLOBAL_DES_EN. bit 1 | 0 | GLOBAL_DES_EN |  1: Global DES enable. 0 : global DES disable.
// default is 0. bit 0 | 0 | DES_lock  |  one time lock bit. after write 1 to this bit,
// DMC_DES_CTRL,DMC_DES_PADDING  can't be write and read. DES KEY registers and DES_PADDING can
// only be reset by pad reset.  But it can be changed by software after watch dog reset.
#define P_DMC_DES_KEY0_REG0 ((volatile uint32_t *)0xfe037388)
// default : 0
#define P_DMC_DES_KEY0_REG1 ((volatile uint32_t *)0xfe03738c)
// default : 0
#define P_DMC_DES_KEY0_REG2 ((volatile uint32_t *)0xfe037390)
// default : 0
#define P_DMC_DES_KEY0_REG3 ((volatile uint32_t *)0xfe037394)
// default : 0
#define P_DMC_DES_KEY1_REG0 ((volatile uint32_t *)0xfe037398)
// default : 0
#define P_DMC_DES_KEY1_REG1 ((volatile uint32_t *)0xfe03739c)
// default : 0
#define P_DMC_DES_KEY1_REG2 ((volatile uint32_t *)0xfe0373a0)
// default : 0
#define P_DMC_DES_KEY1_REG3 ((volatile uint32_t *)0xfe0373a4)
// default : 0
#define P_DMC_DES_PADDING ((volatile uint32_t *)0xfe037380)
// default : 0
// bit 31:0 | 0 | des_pading | 32bits address padding used for DES dkey generation.
// FROM SC2, the APB bus provided Master ID through PUSER signals.
// there's total 8 master IDs could access DMC non-secure registers.
// we assign 1 control bit for each APB Master and each DMC non-secure register domains
// and we added one lock bits to lock this setting can't be modified any more.
#define P_DDR_APB_SEC_CTRL0 ((volatile uint32_t *)0xfe0373c0)
// APB access  control for dmc REQUEST control register access control register.
// default : 0x005
// bit 8    lock bit if this bit =  1,  this register is locked and cannot modified anymore.
// bit 7:0.  APB access enable for each APB user ID. one ID one bit. 1: enable. 0 disable.
#define P_DDR_APB_SEC_CTRL1 ((volatile uint32_t *)0xfe0373c4)
// APB access control for DMC DRAM timing parameter and DFI interface registers.
// default : 0x005
// bit 8    lock bit if this bit =  1,  this register is locked and cannot modified anymore.
// bit 7:0.  APB access enable for each APB user ID. one ID one bit. 1: enable. 0 disable.
#define P_DDR_APB_SEC_CTRL2 ((volatile uint32_t *)0xfe0373c8)
// APB access control for DMC PLL clock frequency control register.
// default : 0x005
// bit 8    lock bit if this bit =  1,  this register is locked and cannot modified anymore.
// bit 7:0.  APB access enable for each APB user ID. one ID one bit. 1: enable. 0 disable.
#define P_DDR_APB_SEC_CTRL3 ((volatile uint32_t *)0xfe0373cc)
// APB access control for DMC sticky control register.
// default : 0x005
// bit 8    lock bit if this bit =  1,  this register is locked and cannot modified anymore.
// bit 7:0.  APB access enable for each APB user ID. one ID one bit. 1: enable. 0 disable.
#define P_DDR_APB_SEC_CTRL4 ((volatile uint32_t *)0xfe0373d0)
// APB access control for DMC test control register.
// default : 0x005
// bit 8    lock bit if this bit =  1,  this register is locked and cannot modified anymore.
// bit 7:0.  APB access enable for each APB user ID. one ID one bit. 1: enable. 0 disable.
#define P_DDR_APB_SEC_CTRL5 ((volatile uint32_t *)0xfe0373d4)
// APB access control for DMC clk reset control register.
// default : 0x005
// bit 8    lock bit if this bit =  1,  this register is locked and cannot modified anymore.
// bit 7:0.  APB access enable for each APB user ID. one ID one bit. 1: enable. 0 disable.
#define P_DDR_APB_SEC_CTRL6 ((volatile uint32_t *)0xfe0373d8)
// APB access control for DMC protection register.
// default : 0x005
// bit 8    lock bit if this bit =  1,  this register is locked and cannot modified anymore.
// bit 7:0.  APB access enable for each APB user ID. one ID one bit. 1: enable. 0 disable.
#define P_DDR_APB_SEC_CTRL7 ((volatile uint32_t *)0xfe0373dc)
// APB access control for DMC normal register.
// default : 0x0ff
// bit 8    lock bit if this bit =  1,  this register is locked and cannot modified anymore.
// bit 7:0.  APB access enable for each APB user ID. one ID one bit. 1: enable. 0 disable.
#define P_DDR_APB_SEC_CTRL8 ((volatile uint32_t *)0xfe0373e0)
// APB access control for DDR PHY group regsiters.
// default : 0x50005
// bit 23:16.  APB access enable for DDR PHY group 1 register.
// bit 10  PHY IMEM control 1: force PHY IMEM output 0. 0: normal working mode.
// bit 9   PHY DMEM control 1: force PHY DMEM output 0. 0: normal working mode.
// bit 8    lock bit if this bit =  1,  this register is locked and cannot modified anymore.
// bit 7:0.  APB access enable for each APB user ID. one ID one bit. 1: enable. 0 disable.
#define P_DDR_APB_SEC_CTRL9 ((volatile uint32_t *)0xfe0373e4)
// APB access control for DMC canvas register.
// default : 0x005
// bit 8    lock bit if this bit =  1,  this register is locked and cannot modified anymore.
// bit 7:0.  APB access enable for each APB user ID. one ID one bit. 1: enable. 0 disable.
// registers to check the security protection and watch point error information.
#define P_DMC_SEC_STATUS ((volatile uint32_t *)0xfe0373e8)
// bit 31~2. not used.
// bit 6
// bit 5
// bit 4
// bit 3   1 : normal security register write violation.( APB bus WDATA not equre the register
// value when APB write).  write 1 to clean this bit to 0. bit 2   sec_alert.   1 DMC secruity
// register alert function triggered. can't clean. only reset DMC can clear this bit. bit 1   write
// security violation. bit 0.  read security violation.
#define P_DMC_VIO_ADDR0 ((volatile uint32_t *)0xfe0373ec)
// ddr0 write secure violation address.
#define P_DMC_VIO_ADDR1 ((volatile uint32_t *)0xfe0373f0)
// bit 31:26 . not used. always 0.
// 24      ddr0 secure check violation.
// 23:21.  not used.
// 20     ddr0 write address overflow. write out of DDR size.
// 19:14. ddr0 write violation AWPROT bits.  (6bits write secruity)
// 13:12  Not used.
// 11:0   ddr0_write violation ID. bit 11~9. Master ID bit 7:4 for subid.
#define P_DMC_VIO_ADDR2 ((volatile uint32_t *)0xfe0373f4)
// ddr0 read seure violation address
#define P_DMC_VIO_ADDR3 ((volatile uint32_t *)0xfe0373f8)
// bit 31:26. not used. always 0.
// 24     ddr0 read secure check violation.
// 23:21. Not used.
// 20     ddr 0 read address overflow. write out of DDR size.
// 19.    Not used.
// 18:16. ddr 0 read violation ARPROT bits. (3 bits for read security).
// 15:12. Not used.
// 11:0   ddr 0 read violation ID. bit 11~9 Marster ID. bit 7:4 subid.
#define P_DMC_DDR_CTRL ((volatile uint32_t *)0xfe037400)
// bit 27.   0 : cavnas use 64bytes boundary
// 1 : canvas use 32bytes boundary.
// bit 24:22   3'b000 : ddr3 mode.
// 3'b001 : ddr4 mode.
// 3'b010 : lpddr3 mode.
// 3'b011 : lpddr4 mode.
// bit 21.   rank1 enable bit. if 1,  rank1 used the address map is as bit 5:3 defined.
// bit 20    DDR4 BG1 enable bit.
// bit 18:   ddrphy_16b, DDR PHY DDR SDRAM data bits width.  1: 16bits. 0 : 32 bits.
// bit 16.   ddr_16b,   1: only use 16bits data in a 32bits DDR PHY data interface. 0 : normal
// data interface. bit 7:4 :  ddr1_size.  DDR rank1 size control. 4'b0000 : DDR rank 1 is 128Mbyte.
// 4'b0001 : DDR rank 1 is 256Mbyte.
// 4'b0010 : DDR rank 1 is 512Mbyte.
// 4'b0011 : DDR rank 1 is 1Gbyte.
// 4'b0100 : DDR rank 1 is 2Gbyte.
// 4'b0101 : DDR rank 1 is 4Gbyte.
// 4'b1000 : DDR rank 1 is 192Mbyte.
// 4'b1001 : DDR rank 1 is 374Mbyte.
// 4'b1010 : DDR rank 1 is 768Mbyte.
// 4'b1011 : DDR rank 1 is 1.5Gbyte.
// 4'b1100 : DDR rank 1 is 3Gbyte.
// others :  reserved.
// bit 3:0  :  ddr0_size. DDR rank0 size control.
// 4'b0000 : DDR rank 0 is 128Mbyte.
// 4'b0001 : DDR rank 0 is 256Mbyte.
// 4'b0010 : DDR rank 0 is 512Mbyte.
// 4'b0011 : DDR rank 0 is 1Gbyte.
// 4'b0100 : DDR rank 0 is 2Gbyte.
// 4'b0101 : DDR rank 0 is 4Gbyte.
// 4'b1000 : DDR rank 1 is 192Mbyte.
// 4'b1001 : DDR rank 1 is 374Mbyte.
// 4'b1010 : DDR rank 1 is 768Mbyte.
// 4'b1011 : DDR rank 1 is 1.5Gbyte.
// 4'b1100 : DDR rank 1 is 3Gbyte.
// others :  reserved.
// DDR3/4 LPDDR3/4 SDRAM address  to 32bits linear address map:
// DDR0_ADDRMAP is used to select RANK0 bank, row, col address selection.
// DDR1_ADDRMAP is used to select RANK1 bank, row, col address selection.
#define P_DDR0_ADDRMAP_0 ((volatile uint32_t *)0xfe037404)
// 29:25 ca8.
// 24:20 ca7.
// 19:15 ca6.
// 14:10 ca5.
// 9:5   ca4.
// 4:0   ca3.
#define P_DDR0_ADDRMAP_1 ((volatile uint32_t *)0xfe037408)
// 29:25 ra2.
// 24:20 ra1.
// 19:15 ra0.
// 14:10 ca11.
// 9:5   ca10.
// 4:0   ca9.
#define P_DDR0_ADDRMAP_2 ((volatile uint32_t *)0xfe03740c)
// 29:25 ra8.
// 24:20 ra7.
// 19:15 ra6.
// 14:10 ra5.
// 9:5   ra4.
// 4:0   ra3.
#define P_DDR0_ADDRMAP_3 ((volatile uint32_t *)0xfe037410)
// 29:25 ra14.
// 24:20 ra13.
// 19:15 ra12.
// 14:10 ra11.
// 9:5   ra10.
// 4:0   ra9.
#define P_DDR0_ADDRMAP_4 ((volatile uint32_t *)0xfe037414)
// 29:25 ra16 for DDR4 SDRAM
// 24:20 bg1  for DDR4 SDRAM.
// 19:15 ba2.    or bg0 for DDR4.
// 14:10 ba1.
// 9:5   ba0.
// 4:0   ra15.
#define P_DDR1_ADDRMAP_0 ((volatile uint32_t *)0xfe037418)
// 29:25 ca8.
// 24:20 ca7.
// 19:15 ca6.
// 14:10 ca5.
// 9:5   ca4.
// 4:0   ca3.
#define P_DDR1_ADDRMAP_1 ((volatile uint32_t *)0xfe03741c)
// 29:25 ra2.
// 24:20 ra1.
// 19:15 ra0.
// 14:10 ca11.
// 9:5   ca10.
// 4:0   ca9.
#define P_DDR1_ADDRMAP_2 ((volatile uint32_t *)0xfe037420)
// 29:25 ra8.
// 24:20 ra7.
// 19:15 ra6.
// 14:10 ra5.
// 9:5   ra4.
// 4:0   ra3.
#define P_DDR1_ADDRMAP_3 ((volatile uint32_t *)0xfe037424)
// 29:25 ra14.
// 24:20 ra13.
// 19:15 ra12.
// 14:10 ra11.
// 9:5   ra10.
// 4:0   ra9.
#define P_DDR1_ADDRMAP_4 ((volatile uint32_t *)0xfe037428)
// 29:25 ra16 for DDR4 SDRAM
// 24:20 bg1  for DDR4 SDRAM.
// 19:15 ba2  or bg0 for DDR4 SDRAM..
// 14:10 ba1.
// 9:5   ba0.
// 4:0   ra15.
#define P_DMC_AXI2DDR0 ((volatile uint32_t *)0xfe037480)
// for AXI address first 256MB  AXI ADDRESS[31:28] == 4'b0000.
// bit 7  ddr_data_with   0 : 32bits.  1: 16bits data in a 16bits data bus.
// bit 6  range_valid     1 : valid address 0 : not valid.
// bit 5  rank_sel,       0 : rank0.   1: rank1.
// bit 4  ddr data 16bits mode   0 : 32bits.  1: 16 bits valid data in a 32bits data bus.
// bti 3:0. remap to one rank of DDR SDRAM linear address[31:28]
#define P_DMC_AXI2DDR1 ((volatile uint32_t *)0xfe037484)
// for AXI_ADDRESS[31:28] == 4'b0001.
// bit 7  ddr_data_with   0 : 32bits.  1: 16bits data in a 16bits data bus.
// bit 6  range_valid     1 : valid address 0 : not valid.
// bit 5  rank_sel,       0 : rank0.   1: rank1.
// bit 4  ddr_data_width, 0 : 32bits.  1: 16bits.
// bti 3:0. remap to one rank of DDR SDRAM linear address[31:28]
#define P_DMC_AXI2DDR2 ((volatile uint32_t *)0xfe037488)
// for AXI_ADDRESS[31:28] == 4'b0010.
// bit 7  ddr_data_with   0 : 32bits.  1: 16bits data in a 16bits data bus.
// bit 6  range_valid     1 : valid address 0 : not valid.
// bit 5  rank_sel,       0 : rank0.   1: rank1.
// bit 4  ddr_data_width, 0 : 32bits.  1: 16bits.
// bti 3:0. remap to one rank of DDR SDRAM linear address[31:28]
#define P_DMC_AXI2DDR3 ((volatile uint32_t *)0xfe03748c)
// for AXI_ADDRESS[31:28] == 4'b0011.
// bit 7  ddr_data_with   0 : 32bits.  1: 16bits data in a 16bits data bus.
// bit 6  range_valid     1 : valid address 0 : not valid.
// bit 5  rank_sel,       0 : rank0.   1: rank1.
// bit 4  ddr_data_width, 0 : 32bits.  1: 16bits.
// bti 3:0. remap to one rank of DDR SDRAM linear address[31:28]
#define P_DMC_AXI2DDR4 ((volatile uint32_t *)0xfe037490)
// for AXI_ADDRESS[31:28] == 4'b0100.
// bit 7  ddr_data_with   0 : 32bits.  1: 16bits data in a 16bits data bus.
// bit 6  range_valid     1 : valid address 0 : not valid.
// bit 5  rank_sel,       0 : rank0.   1: rank1.
// bit 4  ddr_data_width, 0 : 32bits.  1: 16bits.
// bti 3:0. remap to one rank of DDR SDRAM linear address[31:28]
#define P_DMC_AXI2DDR5 ((volatile uint32_t *)0xfe037494)
// for AXI_ADDRESS[31:28] == 4'b0101.
// bit 7  ddr_data_with   0 : 32bits.  1: 16bits data in a 16bits data bus.
// bit 6  range_valid     1 : valid address 0 : not valid.
// bit 5  rank_sel,       0 : rank0.   1: rank1.
// bit 4  ddr_data_width, 0 : 32bits.  1: 16bits.
// bti 3:0. remap to one rank of DDR SDRAM linear address[31:28]
#define P_DMC_AXI2DDR6 ((volatile uint32_t *)0xfe037498)
// for AXI_ADDRESS[31:28] == 4'b0110.
// bit 7  ddr_data_with   0 : 32bits.  1: 16bits data in a 16bits data bus.
// bit 6  range_valid     1 : valid address 0 : not valid.
// bit 5  rank_sel,       0 : rank0.   1: rank1.
// bit 4  ddr_data_width, 0 : 32bits.  1: 16bits.
// bti 3:0. remap to one rank of DDR SDRAM linear address[31:28]
#define P_DMC_AXI2DDR7 ((volatile uint32_t *)0xfe03749c)
// for AXI_ADDRESS[31:28] == 4'b0111.
// bit 7  ddr_data_with   0 : 32bits.  1: 16bits data in a 16bits data bus.
// bit 6  range_valid     1 : valid address 0 : not valid.
// bit 5  rank_sel,       0 : rank0.   1: rank1.
// bit 4  ddr_data_width, 0 : 32bits.  1: 16bits.
// bti 3:0. remap to one rank of DDR SDRAM linear address[31:28]
#define P_DMC_AXI2DDR8 ((volatile uint32_t *)0xfe0374a0)
// for AXI_ADDRESS[31:28] == 4'b1000.
// bit 7  ddr_data_with   0 : 32bits.  1: 16bits data in a 16bits data bus.
// bit 6  range_valid     1 : valid address 0 : not valid.
// bit 5  rank_sel,       0 : rank0.   1: rank1.
// bit 4  ddr_data_width, 0 : 32bits.  1: 16bits.
// bti 3:0. remap to one rank of DDR SDRAM linear address[31:28]
#define P_DMC_AXI2DDR9 ((volatile uint32_t *)0xfe0374a4)
// for AXI_ADDRESS[31:28] == 4'b1001.
// bit 7  ddr_data_with   0 : 32bits.  1: 16bits data in a 16bits data bus.
// bit 6  range_valid     1 : valid address 0 : not valid.
// bit 5  rank_sel,       0 : rank0.   1: rank1.
// bit 4  ddr_data_width, 0 : 32bits.  1: 16bits.
// bti 3:0. remap to one rank of DDR SDRAM linear address[31:28]
#define P_DMC_AXI2DDRA ((volatile uint32_t *)0xfe0374a8)
// for AXI_ADDRESS[31:28] == 4'b1010.
// bit 7  ddr_data_with   0 : 32bits.  1: 16bits data in a 16bits data bus.
// bit 6  range_valid     1 : valid address 0 : not valid.
// bit 5  rank_sel,       0 : rank0.   1: rank1.
// bit 4  ddr_data_width, 0 : 32bits.  1: 16bits.
// bti 3:0. remap to one rank of DDR SDRAM linear address[31:28]
#define P_DMC_AXI2DDRB ((volatile uint32_t *)0xfe0374ac)
// for AXI_ADDRESS[31:28] == 4'b1011.
// bit 7  ddr_data_with   0 : 32bits.  1: 16bits data in a 16bits data bus.
// bit 6  range_valid     1 : valid address 0 : not valid.
// bit 5  rank_sel,       0 : rank0.   1: rank1.
// bit 4  ddr_data_width, 0 : 32bits.  1: 16bits.
// bti 3:0. remap to one rank of DDR SDRAM linear address[31:28]
#define P_DMC_AXI2DDRC ((volatile uint32_t *)0xfe0374b0)
// for AXI_ADDRESS[31:28] == 4'b1100.
// bit 7  ddr_data_with   0 : 32bits.  1: 16bits data in a 16bits data bus.
// bit 6  range_valid     1 : valid address 0 : not valid.
// bit 5  rank_sel,       0 : rank0.   1: rank1.
// bit 4  ddr_data_width, 0 : 32bits.  1: 16bits.
// bti 3:0. remap to one rank of DDR SDRAM linear address[31:28]
#define P_DMC_AXI2DDRD ((volatile uint32_t *)0xfe0374b4)
// for AXI_ADDRESS[31:28] == 4'b1101.
// bit 7  ddr_data_with   0 : 32bits.  1: 16bits data in a 16bits data bus.
// bit 6  range_valid     1 : valid address 0 : not valid.
// bit 5  rank_sel,       0 : rank0.   1: rank1.
// bit 4  ddr_data_width, 0 : 32bits.  1: 16bits.
// bti 3:0. remap to one rank of DDR SDRAM linear address[31:28]
#define P_DMC_AXI2DDRE ((volatile uint32_t *)0xfe0374b8)
// for AXI_ADDRESS[31:28] == 4'b1110.
// bit 7  ddr_data_with   0 : 32bits.  1: 16bits data in a 16bits data bus.
// bit 6  range_valid     1 : valid address 0 : not valid.
// bit 5  rank_sel,       0 : rank0.   1: rank1.
// bit 4  ddr_data_width, 0 : 32bits.  1: 16bits.
// bti 3:0. remap to one rank of DDR SDRAM linear address[31:28]
#define P_DMC_AXI2DDRF ((volatile uint32_t *)0xfe0374bc)
// for AXI_ADDRESS[31:28] == 4'b1111.
// bit 7  ddr_data_with   0 : 32bits.  1: 16bits data in a 16bits data bus.
// bit 6  range_valid     1 : valid address 0 : not valid.
// bit 5  rank_sel,       0 : rank0.   1: rank1.
// bit 4  ddr_data_width, 0 : 32bits.  1: 16bits.
// bti 3:0. remap to one rank of DDR SDRAM linear address[31:28]
#define P_DMC_DDR_CTRL1 ((volatile uint32_t *)0xfe0374c0)
// bit 1.  1: only allow DMA/DEMUX write data level == region security level.   0:  DMA/DEMUX
// write data level <= region sec level. bit 0. DMC_DDR_LOCK.    1: LOCK DMC_DDR_CTRL,
// DMC_DDR_CTRL1, DMC_AXI2DDRx, DDR0/1_ADDRMAP_x registers. those register can't modified any more.
//  0: all these regsiters can be read/write by secure APB access.
//
// Closing file:  ../mmc_lp4/dmc/rtl/dmc_reg.vh
//
//========================================================================
// STARTUP
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe02e000
// -----------------------------------------------
#define P_STARTUP_LOCK ((volatile uint32_t *)0xfe02e000)
#define P_STARTUP_DFU_STS ((volatile uint32_t *)0xfe02e010)
#define P_STARTUP_BOOT_SRC ((volatile uint32_t *)0xfe02e020)
#define P_STARTUP_TEE_REQ_DFU ((volatile uint32_t *)0xfe02e024)
#define P_STARTUP_BOOT_OVERRIDE ((volatile uint32_t *)0xfe02e028)
#define P_STARTUP_COLD_BOOT_CNT ((volatile uint32_t *)0xfe02e02c)
#define P_STARTUP_KEY_PRESERVE ((volatile uint32_t *)0xfe02e030)
//========================================================================
// MIPI_DSI_PHY
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe01c000
// -----------------------------------------------
//`define MIPI_DSI_PHY_START      8'h00
//`define MIPI_DSI_PHY_END        16'hffff
#define P_MIPI_DSI_PHY_CTRL ((volatile uint32_t *)0xfe01c000)
// bit 31.  soft reset for the phy. 1 = reset. 0 = dessert the reset.
// bit 30.  clock lane soft reset.
// bit 29.  data byte lane 3 soft reset.
// bit 28.  data byte lane 2 soft reset.
// bit 27.  data byte lane 1 soft reset.
// bit 26.  data byte lane 0 soft reset.
// bit 5.   LPDT data endian.  1 = transfer the high bit first. 0 : transfer the low bit first.
// bit 4.   HS data endian.
// bit 3.  force data byte lane in stop mode.
// bit 2.  force data byte lane 0 in receiver mode.
// bit 1. write 1 to sync the txclkesc input. the internal logic have to use txclkesc to decide
// Txvalid and Txready. bit 0.  enalbe the MIPI DSI PHY TxDDRClk.
#define P_MIPI_DSI_CHAN_CTRL ((volatile uint32_t *)0xfe01c004)
// bit 31.   clk lane tx_hs_en control selection.  1 = from register. 0 use clk lane state
// machine. bit 30.   register bit for clock lane tx_hs_en. bit 29.  clk lane tx_lp_en contrl
// selection.  1 = from register. 0 from clk lane state machine. bit 28.  register bit for clock
// lane tx_lp_en. bit 27.  chan0 tx_hs_en control selection. 1 = from register. 0 from chan0 state
// machine. bit 26.  register bit for chan0 tx_hs_en. bit 25.  chan0 tx_lp_en control selection. 1
// = from register. 0 from chan0 state machine. bit 24. register bit from chan0 tx_lp_en. bit 23.
// chan0 rx_lp_en control selection. 1 = from register. 0 from chan0 state machine. bit 22.
// register bit from chan0 rx_lp_en. bit 21.  chan0 contention detection enable control selection.
// 1 = from register. 0 from chan0 state machine. bit 20. register bit from chan0 contention
// dectection enable. bit 19.  chan1 tx_hs_en control selection. 1 = from register. 0 from chan0
// state machine. bit 18.  register bit for chan1 tx_hs_en. bit 17.  chan1 tx_lp_en control
// selection. 1 = from register. 0 from chan0 state machine. bit 16. register bit from chan1
// tx_lp_en. bit 15.  chan2 tx_hs_en control selection. 1 = from register. 0 from chan0 state
// machine. bit 14.  register bit for chan2 tx_hs_en. bit 13.  chan2 tx_lp_en control selection. 1
// = from register. 0 from chan0 state machine. bit 12. register bit from chan2 tx_lp_en. bit 11.
// chan3 tx_hs_en control selection. 1 = from register. 0 from chan0 state machine. bit 10.
// register bit for chan3 tx_hs_en. bit 9.  chan3 tx_lp_en control selection. 1 = from register. 0
// from chan0 state machine. bit 8. register bit from chan3 tx_lp_en. bit 4.  clk chan power down.
// this bit is also used as the power down of the whole MIPI_DSI_PHY. bit 3.  chan3 power down.
// bit 2.  chan2 power down.
// bit 1.  chan1 power down.
// bit 0.  chan0 power down.
#define P_MIPI_DSI_CHAN_STS ((volatile uint32_t *)0xfe01c008)
// bit 24.  chan0 TX->RX turn can't accept the ACK command from slave watch dog triggered.  write
// 1 to clear the status bit. bit 23.  chan0 RX ESC command watch dog triggered. write 1 to clean
// this bit. bit
#define P_MIPI_DSI_CLK_TIM ((volatile uint32_t *)0xfe01c00c)
// bit 31:24. TCLK_PREPARE.
// bit 23:16. TCLK_ZERO.
// bit 15:8.  TCLK_POST.
// bit 7:0.   TCLK_TRAIL.
#define P_MIPI_DSI_HS_TIM ((volatile uint32_t *)0xfe01c010)
// bit 31:24. THS_PREPARE.
// bit 23:16. THS_ZERO.
// bit 15:8.  THS_TRAIL.
// bit 7:0.   THS_EXIT.
#define P_MIPI_DSI_LP_TIM ((volatile uint32_t *)0xfe01c014)
// bit 31:24. tTA_GET.
// bit 23:16. tTA_GO.
// bit 15:8.  tTA_SURE.
// bit 7:0.   tLPX.
#define P_MIPI_DSI_ANA_UP_TIM ((volatile uint32_t *)0xfe01c018)
// wait time to  MIPI DIS analog ready.
#define P_MIPI_DSI_INIT_TIM ((volatile uint32_t *)0xfe01c01c)
// TINIT.
#define P_MIPI_DSI_WAKEUP_TIM ((volatile uint32_t *)0xfe01c020)
// TWAKEUP.
#define P_MIPI_DSI_LPOK_TIM ((volatile uint32_t *)0xfe01c024)
// bit 31:0 when in RxULPS state, RX receiver is in sleep mode.
// every MIPI_DSI_ULPS_CHECK period, the receiver would be enabled once, and waiting this timer
// period to get the stable input.
#define P_MIPI_DSI_LP_WCHDOG ((volatile uint32_t *)0xfe01c028)
// bit 31:0 watch dog timer for MIPI DSI LP receive state.
#define P_MIPI_DSI_ANA_CTRL ((volatile uint32_t *)0xfe01c02c)
// bit 31:0 tMBIAS.  timer to wait for analog mBIAS voltage stable.
#define P_MIPI_DSI_CLK_TIM1 ((volatile uint32_t *)0xfe01c030)
// bit 31:8  not used.
// bit 7:0    tCLK_PRE
#define P_MIPI_DSI_TURN_WCHDOG ((volatile uint32_t *)0xfe01c034)
// bit 31:0 watch dog timer for lane 0 LP turn around waiting time.
#define P_MIPI_DSI_ULPS_CHECK ((volatile uint32_t *)0xfe01c038)
// bit 31:0 when Lane0 in LP receive state,  if the another side sent Low power command,  using
// this timer to enable Tcheck the another size wakeup nor not.
#define P_MIPI_DSI_TEST_CTRL0 ((volatile uint32_t *)0xfe01c03c)
#define P_MIPI_DSI_TEST_CTRL1 ((volatile uint32_t *)0xfe01c040)
//========================================================================
//  rtc dig
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe09a000
// -----------------------------------------------
#define P_RTC_EN ((volatile uint32_t *)0xfe09a000)
#define P_RTC_TIME_REG0 ((volatile uint32_t *)0xfe09a004)
#define P_RTC_TIME_REG1 ((volatile uint32_t *)0xfe09a008)
#define P_RTC_ALARM0_REG0 ((volatile uint32_t *)0xfe09a00c)
#define P_RTC_ALARM0_REG1 ((volatile uint32_t *)0xfe09a010)
#define P_RTC_ALARM1_REG0 ((volatile uint32_t *)0xfe09a014)
#define P_RTC_ALARM1_REG1 ((volatile uint32_t *)0xfe09a018)
#define P_RTC_ALARM2_REG0 ((volatile uint32_t *)0xfe09a01c)
#define P_RTC_ALARM2_REG1 ((volatile uint32_t *)0xfe09a020)
#define P_RTC_ALARM_SEL ((volatile uint32_t *)0xfe09a024)
#define P_RTC_ALARM_TIME_SET ((volatile uint32_t *)0xfe09a028)
#define P_RTC_SEC_ADJUST_REG ((volatile uint32_t *)0xfe09a02c)
#define P_RTC_ALARM_IRQ_MASK ((volatile uint32_t *)0xfe09a030)
#define P_RTC_INT ((volatile uint32_t *)0xfe09a034)
#define P_RTC_REAL_TIME0 ((volatile uint32_t *)0xfe09a038)
#define P_RTC_REAL_TIME1 ((volatile uint32_t *)0xfe09a03c)
#define P_RTC_WIDEN_VAL ((volatile uint32_t *)0xfe09a040)
#define P_RTC_OSCIN_CTRL0 ((volatile uint32_t *)0xfe09a044)
#define P_RTC_OSCIN_CTRL1 ((volatile uint32_t *)0xfe09a048)
//========================================================================
//  Temp sensor PLL
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe020000
// -----------------------------------------------
#define P_TS_PLL_CFG_REG1 ((volatile uint32_t *)0xfe020004)
#define P_TS_PLL_CFG_REG2 ((volatile uint32_t *)0xfe020008)
#define P_TS_PLL_CFG_REG3 ((volatile uint32_t *)0xfe02000c)
#define P_TS_PLL_CFG_REG4 ((volatile uint32_t *)0xfe020010)
#define P_TS_PLL_CFG_REG5 ((volatile uint32_t *)0xfe020014)
#define P_TS_PLL_CFG_REG6 ((volatile uint32_t *)0xfe020018)
#define P_TS_PLL_CFG_REG7 ((volatile uint32_t *)0xfe02001c)
#define P_TS_PLL_STAT0 ((volatile uint32_t *)0xfe020040)
#define P_TS_PLL_STAT1 ((volatile uint32_t *)0xfe020044)
#define P_TS_PLL_STAT2 ((volatile uint32_t *)0xfe020048)
#define P_TS_PLL_STAT3 ((volatile uint32_t *)0xfe02004c)
#define P_TS_PLL_STAT4 ((volatile uint32_t *)0xfe020050)
#define P_TS_PLL_STAT5 ((volatile uint32_t *)0xfe020054)
#define P_TS_PLL_STAT6 ((volatile uint32_t *)0xfe020058)
#define P_TS_PLL_STAT7 ((volatile uint32_t *)0xfe02005c)
#define P_TS_PLL_STAT8 ((volatile uint32_t *)0xfe020060)
#define P_TS_PLL_STAT9 ((volatile uint32_t *)0xfe020064)
//========================================================================
//  Temp sensor DDR
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe022000
// -----------------------------------------------
#define P_TS_DDR_CFG_REG1 ((volatile uint32_t *)0xfe022004)
#define P_TS_DDR_CFG_REG2 ((volatile uint32_t *)0xfe022008)
#define P_TS_DDR_CFG_REG3 ((volatile uint32_t *)0xfe02200c)
#define P_TS_DDR_CFG_REG4 ((volatile uint32_t *)0xfe022010)
#define P_TS_DDR_CFG_REG5 ((volatile uint32_t *)0xfe022014)
#define P_TS_DDR_CFG_REG6 ((volatile uint32_t *)0xfe022018)
#define P_TS_DDR_CFG_REG7 ((volatile uint32_t *)0xfe02201c)
#define P_TS_DDR_STAT0 ((volatile uint32_t *)0xfe022040)
#define P_TS_DDR_STAT1 ((volatile uint32_t *)0xfe022044)
#define P_TS_DDR_STAT2 ((volatile uint32_t *)0xfe022048)
#define P_TS_DDR_STAT3 ((volatile uint32_t *)0xfe02204c)
#define P_TS_DDR_STAT4 ((volatile uint32_t *)0xfe022050)
#define P_TS_DDR_STAT5 ((volatile uint32_t *)0xfe022054)
#define P_TS_DDR_STAT6 ((volatile uint32_t *)0xfe022058)
#define P_TS_DDR_STAT7 ((volatile uint32_t *)0xfe02205c)
#define P_TS_DDR_STAT8 ((volatile uint32_t *)0xfe022060)
#define P_TS_DDR_STAT9 ((volatile uint32_t *)0xfe022064)
//========================================================================
//  Temp sensor GPU
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe035000
// -----------------------------------------------
//`define TS_GPU_CFG_REG1                         8'h01
//`define TS_GPU_CFG_REG2                         8'h02
//`define TS_GPU_CFG_REG3                         8'h03
//`define TS_GPU_CFG_REG4                         8'h04
//`define TS_GPU_CFG_REG5                         8'h05
//`define TS_GPU_CFG_REG6                         8'h06
//`define TS_GPU_CFG_REG7                         8'h07
//`define TS_GPU_STAT0                            8'h10
//`define TS_GPU_STAT1                            8'h11
//`define TS_GPU_STAT2                            8'h12
//`define TS_GPU_STAT3                            8'h13
//`define TS_GPU_STAT4                            8'h14
//`define TS_GPU_STAT5                            8'h15
//`define TS_GPU_STAT6                            8'h16
//`define TS_GPU_STAT7                            8'h17
//`define TS_GPU_STAT8                            8'h18
//`define TS_GPU_STAT9                            8'h19
//========================================================================
//  RNG
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe034000
// -----------------------------------------------
//========================================================================
//  ACODEC
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe01a000
// -----------------------------------------------
#define P_ACODEC_0 ((volatile uint32_t *)0xfe01a000)
#define P_ACODEC_1 ((volatile uint32_t *)0xfe01a004)
#define P_ACODEC_2 ((volatile uint32_t *)0xfe01a008)
#define P_ACODEC_3 ((volatile uint32_t *)0xfe01a00c)
#define P_ACODEC_4 ((volatile uint32_t *)0xfe01a010)
#define P_ACODEC_5 ((volatile uint32_t *)0xfe01a014)
#define P_ACODEC_6 ((volatile uint32_t *)0xfe01a018)
#define P_ACODEC_7 ((volatile uint32_t *)0xfe01a01c)
//========================================================================
//  AML USB PHY A
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe03c000
// -----------------------------------------------
#define P_AMLUSB_A0 ((volatile uint32_t *)0xfe03c000)
#define P_AMLUSB_A1 ((volatile uint32_t *)0xfe03c004)
#define P_AMLUSB_A2 ((volatile uint32_t *)0xfe03c008)
#define P_AMLUSB_A3 ((volatile uint32_t *)0xfe03c00c)
#define P_AMLUSB_A4 ((volatile uint32_t *)0xfe03c010)
#define P_AMLUSB_A5 ((volatile uint32_t *)0xfe03c014)
#define P_AMLUSB_A6 ((volatile uint32_t *)0xfe03c018)
#define P_AMLUSB_A7 ((volatile uint32_t *)0xfe03c01c)
#define P_AMLUSB_A8 ((volatile uint32_t *)0xfe03c020)
#define P_AMLUSB_A9 ((volatile uint32_t *)0xfe03c024)
#define P_AMLUSB_A10 ((volatile uint32_t *)0xfe03c028)
#define P_AMLUSB_A11 ((volatile uint32_t *)0xfe03c02c)
#define P_AMLUSB_A12 ((volatile uint32_t *)0xfe03c030)
#define P_AMLUSB_A13 ((volatile uint32_t *)0xfe03c034)
#define P_AMLUSB_A14 ((volatile uint32_t *)0xfe03c038)
#define P_AMLUSB_A15 ((volatile uint32_t *)0xfe03c03c)
#define P_AMLUSB_A16 ((volatile uint32_t *)0xfe03c040)
#define P_AMLUSB_A17 ((volatile uint32_t *)0xfe03c044)
#define P_AMLUSB_A18 ((volatile uint32_t *)0xfe03c048)
#define P_AMLUSB_A19 ((volatile uint32_t *)0xfe03c04c)
#define P_AMLUSB_A20 ((volatile uint32_t *)0xfe03c050)
#define P_AMLUSB_A21 ((volatile uint32_t *)0xfe03c054)
#define P_AMLUSB_A22 ((volatile uint32_t *)0xfe03c058)
#define P_AMLUSB_A23 ((volatile uint32_t *)0xfe03c05c)
#define P_AMLUSB_A24 ((volatile uint32_t *)0xfe03c060)
#define P_AMLUSB_A25 ((volatile uint32_t *)0xfe03c064)
#define P_AMLUSB_A26 ((volatile uint32_t *)0xfe03c068)
#define P_AMLUSB_A27 ((volatile uint32_t *)0xfe03c06c)
#define P_AMLUSB_A28 ((volatile uint32_t *)0xfe03c070)
#define P_AMLUSB_A29 ((volatile uint32_t *)0xfe03c074)
#define P_AMLUSB_A30 ((volatile uint32_t *)0xfe03c078)
#define P_AMLUSB_A31 ((volatile uint32_t *)0xfe03c07c)
//========================================================================
//  AML USB PHY B
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe03e000
// -----------------------------------------------
#define P_AMLUSB_B0 ((volatile uint32_t *)0xfe03e000)
#define P_AMLUSB_B1 ((volatile uint32_t *)0xfe03e004)
#define P_AMLUSB_B2 ((volatile uint32_t *)0xfe03e008)
#define P_AMLUSB_B3 ((volatile uint32_t *)0xfe03e00c)
#define P_AMLUSB_B4 ((volatile uint32_t *)0xfe03e010)
#define P_AMLUSB_B5 ((volatile uint32_t *)0xfe03e014)
#define P_AMLUSB_B6 ((volatile uint32_t *)0xfe03e018)
#define P_AMLUSB_B7 ((volatile uint32_t *)0xfe03e01c)
#define P_AMLUSB_B8 ((volatile uint32_t *)0xfe03e020)
#define P_AMLUSB_B9 ((volatile uint32_t *)0xfe03e024)
#define P_AMLUSB_B10 ((volatile uint32_t *)0xfe03e028)
#define P_AMLUSB_B11 ((volatile uint32_t *)0xfe03e02c)
#define P_AMLUSB_B12 ((volatile uint32_t *)0xfe03e030)
#define P_AMLUSB_B13 ((volatile uint32_t *)0xfe03e034)
#define P_AMLUSB_B14 ((volatile uint32_t *)0xfe03e038)
#define P_AMLUSB_B15 ((volatile uint32_t *)0xfe03e03c)
#define P_AMLUSB_B16 ((volatile uint32_t *)0xfe03e040)
#define P_AMLUSB_B17 ((volatile uint32_t *)0xfe03e044)
#define P_AMLUSB_B18 ((volatile uint32_t *)0xfe03e048)
#define P_AMLUSB_B19 ((volatile uint32_t *)0xfe03e04c)
#define P_AMLUSB_B20 ((volatile uint32_t *)0xfe03e050)
#define P_AMLUSB_B21 ((volatile uint32_t *)0xfe03e054)
#define P_AMLUSB_B22 ((volatile uint32_t *)0xfe03e058)
#define P_AMLUSB_B23 ((volatile uint32_t *)0xfe03e05c)
#define P_AMLUSB_B24 ((volatile uint32_t *)0xfe03e060)
#define P_AMLUSB_B25 ((volatile uint32_t *)0xfe03e064)
#define P_AMLUSB_B26 ((volatile uint32_t *)0xfe03e068)
#define P_AMLUSB_B27 ((volatile uint32_t *)0xfe03e06c)
#define P_AMLUSB_B28 ((volatile uint32_t *)0xfe03e070)
#define P_AMLUSB_B29 ((volatile uint32_t *)0xfe03e074)
#define P_AMLUSB_B30 ((volatile uint32_t *)0xfe03e078)
#define P_AMLUSB_B31 ((volatile uint32_t *)0xfe03e07c)
//========================================================================
//  PAD_CTRL
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe004000
// -----------------------------------------------
#define P_PADCTRL_PIN_MUX_REG0 ((volatile uint32_t *)0xfe004000)
#define P_PADCTRL_PIN_MUX_REG1 ((volatile uint32_t *)0xfe004004)
//`define PADCTRL_PIN_MUX_REG2          8'h02
#define P_PADCTRL_PIN_MUX_REG3 ((volatile uint32_t *)0xfe00400c)
#define P_PADCTRL_PIN_MUX_REG4 ((volatile uint32_t *)0xfe004010)
#define P_PADCTRL_PIN_MUX_REG5 ((volatile uint32_t *)0xfe004014)
#define P_PADCTRL_PIN_MUX_REG6 ((volatile uint32_t *)0xfe004018)
#define P_PADCTRL_PIN_MUX_REG7 ((volatile uint32_t *)0xfe00401c)
//`define PADCTRL_PIN_MUX_REG8          8'h08
#define P_PADCTRL_PIN_MUX_REG9 ((volatile uint32_t *)0xfe004024)
#define P_PADCTRL_PIN_MUX_REGA ((volatile uint32_t *)0xfe004028)
#define P_PADCTRL_PIN_MUX_REGB ((volatile uint32_t *)0xfe00402c)
#define P_PADCTRL_PIN_MUX_REGC ((volatile uint32_t *)0xfe004030)
//`define PADCTRL_PIN_MUX_REGD          8'h0d
//`define PADCTRL_PIN_MUX_REGE          8'h0e
//`define PADCTRL_PIN_MUX_REGF          8'h0f
#define P_PADCTRL_PIN_MUX_REGG ((volatile uint32_t *)0xfe004040)
#define P_PADCTRL_PIN_MUX_REGH ((volatile uint32_t *)0xfe004044)
#define P_PADCTRL_PIN_MUX_REGI ((volatile uint32_t *)0xfe004048)
#define P_PADCTRL_PIN_MUX_REGJ ((volatile uint32_t *)0xfe00404c)
#define P_PADCTRL_GPIO_IRQ_CTRL0 ((volatile uint32_t *)0xfe004080)
#define P_PADCTRL_GPIO_IRQ_CTRL1 ((volatile uint32_t *)0xfe004084)
#define P_PADCTRL_GPIO_IRQ_CTRL2 ((volatile uint32_t *)0xfe004088)
#define P_PADCTRL_GPIO_IRQ_CTRL3 ((volatile uint32_t *)0xfe00408c)
#define P_PADCTRL_GPIO_IRQ_CTRL4 ((volatile uint32_t *)0xfe004090)
#define P_PADCTRL_GPIO_IRQ_CTRL5 ((volatile uint32_t *)0xfe004094)
#define P_PADCTRL_GPIO_IRQ_CTRL6 ((volatile uint32_t *)0xfe004098)
#define P_PADCTRL_GPIO_IRQ_CTRL7 ((volatile uint32_t *)0xfe00409c)
#define P_PADCTRL_WORLD_SYNC_CTRL0 ((volatile uint32_t *)0xfe0040a0)
#define P_PADCTRL_GPIO_MSR_CTRL0 ((volatile uint32_t *)0xfe0040a4)
#define P_PADCTRL_MISC_CTRL0 ((volatile uint32_t *)0xfe0040a8)
#define P_PADCTRL_GPIOZ_I ((volatile uint32_t *)0xfe0040c0)
#define P_PADCTRL_GPIOZ_O ((volatile uint32_t *)0xfe0040c4)
#define P_PADCTRL_GPIOZ_OEN ((volatile uint32_t *)0xfe0040c8)
#define P_PADCTRL_GPIOZ_PULL_EN ((volatile uint32_t *)0xfe0040cc)
#define P_PADCTRL_GPIOZ_PULL_UP ((volatile uint32_t *)0xfe0040d0)
#define P_PADCTRL_GPIOZ_LOCK ((volatile uint32_t *)0xfe0040d4)
#define P_PADCTRL_GPIOZ_PROT ((volatile uint32_t *)0xfe0040d8)
#define P_PADCTRL_GPIOZ_DS ((volatile uint32_t *)0xfe0040dc)
#define P_PADCTRL_GPIOX_I ((volatile uint32_t *)0xfe004100)
#define P_PADCTRL_GPIOX_O ((volatile uint32_t *)0xfe004104)
#define P_PADCTRL_GPIOX_OEN ((volatile uint32_t *)0xfe004108)
#define P_PADCTRL_GPIOX_PULL_EN ((volatile uint32_t *)0xfe00410c)
#define P_PADCTRL_GPIOX_PULL_UP ((volatile uint32_t *)0xfe004110)
#define P_PADCTRL_GPIOX_LOCK ((volatile uint32_t *)0xfe004114)
#define P_PADCTRL_GPIOX_PROT ((volatile uint32_t *)0xfe004118)
#define P_PADCTRL_GPIOX_DS ((volatile uint32_t *)0xfe00411c)
#define P_PADCTRL_GPIOX_DS_EXT ((volatile uint32_t *)0xfe004120)
#define P_PADCTRL_GPIOT_I ((volatile uint32_t *)0xfe004140)
#define P_PADCTRL_GPIOT_O ((volatile uint32_t *)0xfe004144)
#define P_PADCTRL_GPIOT_OEN ((volatile uint32_t *)0xfe004148)
#define P_PADCTRL_GPIOT_PULL_EN ((volatile uint32_t *)0xfe00414c)
#define P_PADCTRL_GPIOT_PULL_UP ((volatile uint32_t *)0xfe004150)
#define P_PADCTRL_GPIOT_LOCK ((volatile uint32_t *)0xfe004154)
#define P_PADCTRL_GPIOT_PROT ((volatile uint32_t *)0xfe004158)
#define P_PADCTRL_GPIOT_DS ((volatile uint32_t *)0xfe00415c)
//`define PADCTRL_GPIOH_I               8'h50
//`define PADCTRL_GPIOH_O               8'h51
//`define PADCTRL_GPIOH_OEN             8'h52
//`define PADCTRL_GPIOH_PULL_EN         8'h53
//`define PADCTRL_GPIOH_PULL_UP         8'h54
//`define PADCTRL_GPIOH_LOCK            8'h55
//`define PADCTRL_GPIOH_PROT            8'h56
//`define PADCTRL_GPIOH_DS              8'h57
#define P_PADCTRL_GPIOD_I ((volatile uint32_t *)0xfe004180)
#define P_PADCTRL_GPIOD_O ((volatile uint32_t *)0xfe004184)
#define P_PADCTRL_GPIOD_OEN ((volatile uint32_t *)0xfe004188)
#define P_PADCTRL_GPIOD_PULL_EN ((volatile uint32_t *)0xfe00418c)
#define P_PADCTRL_GPIOD_PULL_UP ((volatile uint32_t *)0xfe004190)
#define P_PADCTRL_GPIOD_LOCK ((volatile uint32_t *)0xfe004194)
#define P_PADCTRL_GPIOD_PROT ((volatile uint32_t *)0xfe004198)
#define P_PADCTRL_GPIOD_DS ((volatile uint32_t *)0xfe00419c)
#define P_PADCTRL_GPIOE_I ((volatile uint32_t *)0xfe0041c0)
#define P_PADCTRL_GPIOE_O ((volatile uint32_t *)0xfe0041c4)
#define P_PADCTRL_GPIOE_OEN ((volatile uint32_t *)0xfe0041c8)
#define P_PADCTRL_GPIOE_PULL_EN ((volatile uint32_t *)0xfe0041cc)
#define P_PADCTRL_GPIOE_PULL_UP ((volatile uint32_t *)0xfe0041d0)
#define P_PADCTRL_GPIOE_LOCK ((volatile uint32_t *)0xfe0041d4)
#define P_PADCTRL_GPIOE_PROT ((volatile uint32_t *)0xfe0041d8)
#define P_PADCTRL_GPIOE_DS ((volatile uint32_t *)0xfe0041dc)
#define P_PADCTRL_GPIOC_I ((volatile uint32_t *)0xfe004200)
#define P_PADCTRL_GPIOC_O ((volatile uint32_t *)0xfe004204)
#define P_PADCTRL_GPIOC_OEN ((volatile uint32_t *)0xfe004208)
#define P_PADCTRL_GPIOC_PULL_EN ((volatile uint32_t *)0xfe00420c)
#define P_PADCTRL_GPIOC_PULL_UP ((volatile uint32_t *)0xfe004210)
#define P_PADCTRL_GPIOC_LOCK ((volatile uint32_t *)0xfe004214)
#define P_PADCTRL_GPIOC_PROT ((volatile uint32_t *)0xfe004218)
#define P_PADCTRL_GPIOC_DS ((volatile uint32_t *)0xfe00421c)
#define P_PADCTRL_GPIOB_I ((volatile uint32_t *)0xfe004240)
#define P_PADCTRL_GPIOB_O ((volatile uint32_t *)0xfe004244)
#define P_PADCTRL_GPIOB_OEN ((volatile uint32_t *)0xfe004248)
#define P_PADCTRL_GPIOB_PULL_EN ((volatile uint32_t *)0xfe00424c)
#define P_PADCTRL_GPIOB_PULL_UP ((volatile uint32_t *)0xfe004250)
#define P_PADCTRL_GPIOB_LOCK ((volatile uint32_t *)0xfe004254)
#define P_PADCTRL_GPIOB_PROT ((volatile uint32_t *)0xfe004258)
#define P_PADCTRL_GPIOB_DS ((volatile uint32_t *)0xfe00425c)
#define P_PADCTRL_GPIOH_I ((volatile uint32_t *)0xfe004280)
#define P_PADCTRL_GPIOH_O ((volatile uint32_t *)0xfe004284)
#define P_PADCTRL_GPIOH_OEN ((volatile uint32_t *)0xfe004288)
#define P_PADCTRL_GPIOH_PULL_EN ((volatile uint32_t *)0xfe00428c)
#define P_PADCTRL_GPIOH_PULL_UP ((volatile uint32_t *)0xfe004290)
#define P_PADCTRL_GPIOH_LOCK ((volatile uint32_t *)0xfe004294)
#define P_PADCTRL_GPIOH_PROT ((volatile uint32_t *)0xfe004298)
#define P_PADCTRL_GPIOH_DS ((volatile uint32_t *)0xfe00429c)
//`define PADCTRL_GPIOA_I               8'hA0
//`define PADCTRL_GPIOA_O               8'hA1
//`define PADCTRL_GPIOA_OEN             8'hA2
//`define PADCTRL_GPIOA_PULL_EN         8'hA3
//`define PADCTRL_GPIOA_PULL_UP         8'hA4
//`define PADCTRL_GPIOA_LOCK            8'hA5
//`define PADCTRL_GPIOA_PROT            8'hA6
//`define PADCTRL_GPIOA_DS              8'hA7
#define P_PADCTRL_TESTN_I ((volatile uint32_t *)0xfe0042c0)
#define P_PADCTRL_TESTN_O ((volatile uint32_t *)0xfe0042c4)
#define P_PADCTRL_TESTN_OEN ((volatile uint32_t *)0xfe0042c8)
#define P_PADCTRL_TESTN_PULL_EN ((volatile uint32_t *)0xfe0042cc)
#define P_PADCTRL_TESTN_PULL_UP ((volatile uint32_t *)0xfe0042d0)
#define P_PADCTRL_TESTN_LOCK ((volatile uint32_t *)0xfe0042d4)
#define P_PADCTRL_TESTN_PROT ((volatile uint32_t *)0xfe0042d8)
#define P_PADCTRL_TESTN_DS ((volatile uint32_t *)0xfe0042dc)
//`define PADCTRL_ANALOG_I              8'hC0
//`define PADCTRL_ANALOG_EN             8'hC1
#define P_PADCTRL_LOCK_PIN_MUX0 ((volatile uint32_t *)0xfe004340)
#define P_PADCTRL_LOCK_PIN_MUX1 ((volatile uint32_t *)0xfe004344)
#define P_PADCTRL_LOCK_PIN_MUX2 ((volatile uint32_t *)0xfe004348)
#define P_PADCTRL_LOCK_PIN_MUX3 ((volatile uint32_t *)0xfe00434c)
#define P_PADCTRL_LOCK_PIN_MUX4 ((volatile uint32_t *)0xfe004350)
#define P_PADCTRL_PROT_PIN_MUX0 ((volatile uint32_t *)0xfe004360)
#define P_PADCTRL_PROT_PIN_MUX1 ((volatile uint32_t *)0xfe004364)
#define P_PADCTRL_PROT_PIN_MUX2 ((volatile uint32_t *)0xfe004368)
#define P_PADCTRL_PROT_PIN_MUX3 ((volatile uint32_t *)0xfe00436c)
#define P_PADCTRL_PROT_PIN_MUX4 ((volatile uint32_t *)0xfe004370)
#define P_PADCTRL_MUTE_CTRL ((volatile uint32_t *)0xfe004380)
#define P_PADCTRL_MUTE_TDM_DISA ((volatile uint32_t *)0xfe004384)
#define P_PADCTRL_DEBUG_SEL ((volatile uint32_t *)0xfe004388)
#define P_PADCTRL_AUDIO_PAD_SEL0 ((volatile uint32_t *)0xfe00438c)
#define P_PADCTRL_AUDIO_PAD_SEL1 ((volatile uint32_t *)0xfe004390)
//========================================================================
//  SYS_CTRL
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe010000
// -----------------------------------------------
#define P_SYSCTRL_METAL_REV0 ((volatile uint32_t *)0xfe010000)
#define P_SYSCTRL_METAL_REV1 ((volatile uint32_t *)0xfe010004)
#define P_SYSCTRL_METAL_REV2 ((volatile uint32_t *)0xfe010008)
#define P_SYSCTRL_CHIP_ID ((volatile uint32_t *)0xfe01002c)
#define P_SYSCTRL_WRITEONCE1_REG0 ((volatile uint32_t *)0xfe010040)
#define P_SYSCTRL_WRITEONCE1_STICKY_REG0 ((volatile uint32_t *)0xfe010044)
#define P_SYSCTRL_WRITEONCE1_SEC_REG0 ((volatile uint32_t *)0xfe010048)
#define P_SYSCTRL_WRITEONCE1_STICKY_SEC_REG0 ((volatile uint32_t *)0xfe01004c)
#define P_SYSCTRL_WRITEONCE_REG0 ((volatile uint32_t *)0xfe010050)
#define P_SYSCTRL_WRITEONCE_REG1 ((volatile uint32_t *)0xfe010054)
#define P_SYSCTRL_WRITEONCE_SEC_REG0 ((volatile uint32_t *)0xfe010058)
#define P_SYSCTRL_WRITEONCE_STICKY_REG0 ((volatile uint32_t *)0xfe01005c)
#define P_SYSCTRL_WRITEONCE_STICKY_REG1 ((volatile uint32_t *)0xfe010060)
#define P_SYSCTRL_WRITEONCE_STICKY_SEC_REG0 ((volatile uint32_t *)0xfe010064)
#define P_SYSCTRL_TIMERA_CTRL ((volatile uint32_t *)0xfe0100c0)
#define P_SYSCTRL_TIMERA ((volatile uint32_t *)0xfe0100c4)
#define P_SYSCTRL_TIMERB_CTRL ((volatile uint32_t *)0xfe0100c8)
#define P_SYSCTRL_TIMERB ((volatile uint32_t *)0xfe0100cc)
#define P_SYSCTRL_TIMERC_CTRL ((volatile uint32_t *)0xfe0100d0)
#define P_SYSCTRL_TIMERC ((volatile uint32_t *)0xfe0100d4)
#define P_SYSCTRL_TIMERD_CTRL ((volatile uint32_t *)0xfe0100d8)
#define P_SYSCTRL_TIMERD ((volatile uint32_t *)0xfe0100dc)
#define P_SYSCTRL_SEC_TIMERA_CTRL ((volatile uint32_t *)0xfe0100e0)
#define P_SYSCTRL_SEC_TIMERA ((volatile uint32_t *)0xfe0100e4)
#define P_SYSCTRL_TIMERE_CTRL ((volatile uint32_t *)0xfe0100e8)
#define P_SYSCTRL_TIMERE ((volatile uint32_t *)0xfe0100ec)
#define P_SYSCTRL_TIMERE_HI ((volatile uint32_t *)0xfe0100f0)
#define P_SYSCTRL_TIMERF_CTRL ((volatile uint32_t *)0xfe0100f4)
#define P_SYSCTRL_TIMERF ((volatile uint32_t *)0xfe0100f8)
#define P_SYSCTRL_TIMERF_HI ((volatile uint32_t *)0xfe0100fc)
#define P_SYSCTRL_TIMERG_CTRL ((volatile uint32_t *)0xfe010100)
#define P_SYSCTRL_TIMERG ((volatile uint32_t *)0xfe010104)
#define P_SYSCTRL_TIMERH_CTRL ((volatile uint32_t *)0xfe010108)
#define P_SYSCTRL_TIMERH ((volatile uint32_t *)0xfe01010c)
#define P_SYSCTRL_TIMERI_CTRL ((volatile uint32_t *)0xfe010110)
#define P_SYSCTRL_TIMERI ((volatile uint32_t *)0xfe010114)
#define P_SYSCTRL_TIMERJ_CTRL ((volatile uint32_t *)0xfe010118)
#define P_SYSCTRL_TIMERJ ((volatile uint32_t *)0xfe01011c)
#define P_SYSCTRL_SEC_TIMERE_CTRL ((volatile uint32_t *)0xfe010120)
#define P_SYSCTRL_SEC_TIMERE ((volatile uint32_t *)0xfe010124)
#define P_SYSCTRL_SEC_TIMERE_HI ((volatile uint32_t *)0xfe010128)
#define P_SYSCTRL_OSC_RING_CTRL0 ((volatile uint32_t *)0xfe010140)
#define P_SYSCTRL_OSC_RING_CTRL1 ((volatile uint32_t *)0xfe010144)
#define P_SYSCTRL_AM2AXI_CTRL0 ((volatile uint32_t *)0xfe010148)
#define P_SYSCTRL_AM2AXI_STS ((volatile uint32_t *)0xfe01014c)
#define P_SYSCTRL_AXI_PIPE_CTRL0 ((volatile uint32_t *)0xfe010154)
#define P_SYSCTRL_AXI_PIPE_CTRL1 ((volatile uint32_t *)0xfe010158)
#define P_SYSCTRL_TIMER90K ((volatile uint32_t *)0xfe01015c)
#define P_SYSCTRL_SCR ((volatile uint32_t *)0xfe010160)
#define P_SYSCTRL_HPG_TIMER ((volatile uint32_t *)0xfe010164)
//`define SYSCTRL_VIPNANOQ_CTRL0                  10'h5A
#define P_SYSCTRL_AHB2DDR_CTRL0 ((volatile uint32_t *)0xfe01016c)
#define P_SYSCTRL_AHB2DDR_CTRL1 ((volatile uint32_t *)0xfe010170)
#define P_SYSCTRL_POC ((volatile uint32_t *)0xfe010180)
#define P_SYSCTRL_VPU_SECURE_REG0 ((volatile uint32_t *)0xfe010184)
#define P_SYSCTRL_VPU_SECURE_REG1 ((volatile uint32_t *)0xfe010188)
//`define SYSCTRL_NIC_CFG0                        10'h63                           )
#define P_SYSCTRL_ALERT_STS_STICKY ((volatile uint32_t *)0xfe010190)
#define P_SYSCTRL_ALERT_ENABLE ((volatile uint32_t *)0xfe010198)
#define P_SYSCTRL_ENABLE_SPIFC ((volatile uint32_t *)0xfe0101a0)
#define P_SYSCTRL_DEBUG_REG0 ((volatile uint32_t *)0xfe010240)
#define P_SYSCTRL_DEBUG_REG1 ((volatile uint32_t *)0xfe010244)
#define P_SYSCTRL_DEBUG_REG2 ((volatile uint32_t *)0xfe010248)
#define P_SYSCTRL_DEBUG_REG3 ((volatile uint32_t *)0xfe01024c)
#define P_SYSCTRL_DEBUG_REG4 ((volatile uint32_t *)0xfe010250)
#define P_SYSCTRL_DEBUG_REG5 ((volatile uint32_t *)0xfe010254)
#define P_SYSCTRL_DEBUG_REG6 ((volatile uint32_t *)0xfe010258)
#define P_SYSCTRL_DEBUG_REG7 ((volatile uint32_t *)0xfe01025c)
#define P_SYSCTRL_STATUS_REG0 ((volatile uint32_t *)0xfe010280)
#define P_SYSCTRL_STATUS_REG1 ((volatile uint32_t *)0xfe010284)
#define P_SYSCTRL_STATUS_REG2 ((volatile uint32_t *)0xfe010288)
#define P_SYSCTRL_STATUS_REG3 ((volatile uint32_t *)0xfe01028c)
#define P_SYSCTRL_STATUS_REG4 ((volatile uint32_t *)0xfe010290)
#define P_SYSCTRL_STATUS_REG5 ((volatile uint32_t *)0xfe010294)
#define P_SYSCTRL_STATUS_REG6 ((volatile uint32_t *)0xfe010298)
#define P_SYSCTRL_STATUS_REG7 ((volatile uint32_t *)0xfe01029c)
#define P_SYSCTRL_STICKY_REG0 ((volatile uint32_t *)0xfe0102c0)
#define P_SYSCTRL_STICKY_REG1 ((volatile uint32_t *)0xfe0102c4)
#define P_SYSCTRL_STICKY_REG2 ((volatile uint32_t *)0xfe0102c8)
#define P_SYSCTRL_STICKY_REG3 ((volatile uint32_t *)0xfe0102cc)
#define P_SYSCTRL_STICKY_REG4 ((volatile uint32_t *)0xfe0102d0)
#define P_SYSCTRL_STICKY_REG5 ((volatile uint32_t *)0xfe0102d4)
#define P_SYSCTRL_STICKY_REG6 ((volatile uint32_t *)0xfe0102d8)
#define P_SYSCTRL_STICKY_REG7 ((volatile uint32_t *)0xfe0102dc)
#define P_SYSCTRL_SEC_STATUS_REG0 ((volatile uint32_t *)0xfe010300)
#define P_SYSCTRL_SEC_STATUS_REG1 ((volatile uint32_t *)0xfe010304)
#define P_SYSCTRL_SEC_STATUS_REG2 ((volatile uint32_t *)0xfe010308)
#define P_SYSCTRL_SEC_STATUS_REG3 ((volatile uint32_t *)0xfe01030c)
#define P_SYSCTRL_SEC_STATUS_REG4 ((volatile uint32_t *)0xfe010310)
#define P_SYSCTRL_SEC_STATUS_REG5 ((volatile uint32_t *)0xfe010314)
#define P_SYSCTRL_SEC_STATUS_REG6 ((volatile uint32_t *)0xfe010318)
#define P_SYSCTRL_SEC_STATUS_REG7 ((volatile uint32_t *)0xfe01031c)
#define P_SYSCTRL_SEC_STATUS_REG8 ((volatile uint32_t *)0xfe010320)
#define P_SYSCTRL_SEC_STATUS_REG9 ((volatile uint32_t *)0xfe010324)
#define P_SYSCTRL_SEC_STATUS_REG10 ((volatile uint32_t *)0xfe010328)
#define P_SYSCTRL_SEC_STATUS_REG11 ((volatile uint32_t *)0xfe01032c)
#define P_SYSCTRL_SEC_STATUS_REG12 ((volatile uint32_t *)0xfe010330)
#define P_SYSCTRL_SEC_STATUS_REG13 ((volatile uint32_t *)0xfe010334)
#define P_SYSCTRL_SEC_STATUS_REG14 ((volatile uint32_t *)0xfe010338)
#define P_SYSCTRL_SEC_STATUS_REG15 ((volatile uint32_t *)0xfe01033c)
#define P_SYSCTRL_SEC_STATUS_REG16 ((volatile uint32_t *)0xfe010340)
#define P_SYSCTRL_SEC_STATUS_REG17 ((volatile uint32_t *)0xfe010344)
#define P_SYSCTRL_SEC_STATUS_REG18 ((volatile uint32_t *)0xfe010348)
#define P_SYSCTRL_SEC_STATUS_REG19 ((volatile uint32_t *)0xfe01034c)
#define P_SYSCTRL_SEC_STATUS_REG20 ((volatile uint32_t *)0xfe010350)
#define P_SYSCTRL_SEC_STATUS_REG21 ((volatile uint32_t *)0xfe010354)
#define P_SYSCTRL_SEC_STATUS_REG22 ((volatile uint32_t *)0xfe010358)
#define P_SYSCTRL_SEC_STATUS_REG23 ((volatile uint32_t *)0xfe01035c)
#define P_SYSCTRL_SEC_STATUS_REG24 ((volatile uint32_t *)0xfe010360)
#define P_SYSCTRL_SEC_STATUS_REG25 ((volatile uint32_t *)0xfe010364)
#define P_SYSCTRL_SEC_STATUS_REG26 ((volatile uint32_t *)0xfe010368)
#define P_SYSCTRL_SEC_STATUS_REG27 ((volatile uint32_t *)0xfe01036c)
#define P_SYSCTRL_SEC_STATUS_REG28 ((volatile uint32_t *)0xfe010370)
#define P_SYSCTRL_SEC_STATUS_REG29 ((volatile uint32_t *)0xfe010374)
#define P_SYSCTRL_SEC_STATUS_REG30 ((volatile uint32_t *)0xfe010378)
#define P_SYSCTRL_SEC_STATUS_REG31 ((volatile uint32_t *)0xfe01037c)
#define P_SYSCTRL_SEC_STICKY_REG0 ((volatile uint32_t *)0xfe010380)
#define P_SYSCTRL_SEC_STICKY_REG1 ((volatile uint32_t *)0xfe010384)
#define P_SYSCTRL_SEC_STICKY_REG2 ((volatile uint32_t *)0xfe010388)
#define P_SYSCTRL_SEC_STICKY_REG3 ((volatile uint32_t *)0xfe01038c)
#define P_SYSCTRL_SEC_STICKY_REG4 ((volatile uint32_t *)0xfe010390)
#define P_SYSCTRL_SEC_STICKY_REG5 ((volatile uint32_t *)0xfe010394)
#define P_SYSCTRL_SEC_STICKY_REG6 ((volatile uint32_t *)0xfe010398)
#define P_SYSCTRL_SEC_STICKY_REG7 ((volatile uint32_t *)0xfe01039c)
#define P_SYSCTRL_MSG_INDEX0_STICKY ((volatile uint32_t *)0xfe0103c0)
#define P_SYSCTRL_MSG_INDEX1_STICKY ((volatile uint32_t *)0xfe0103c4)
#define P_SYSCTRL_MSG_INDEX2_STICKY ((volatile uint32_t *)0xfe0103c8)
#define P_SYSCTRL_MSG_INDEX3_STICKY ((volatile uint32_t *)0xfe0103cc)
//========================================================================
//  CLK_CTRL
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe000000
// -----------------------------------------------
#define P_CLKCTRL_OSCIN_CTRL ((volatile uint32_t *)0xfe000004)
#define P_CLKCTRL_RTC_BY_OSCIN_CTRL0 ((volatile uint32_t *)0xfe000008)
#define P_CLKCTRL_RTC_BY_OSCIN_CTRL1 ((volatile uint32_t *)0xfe00000c)
#define P_CLKCTRL_RTC_CTRL ((volatile uint32_t *)0xfe000010)
#define P_CLKCTRL_CHECK_CLK_RESULT ((volatile uint32_t *)0xfe000014)
#define P_CLKCTRL_MBIST_ATSPEED_CTRL ((volatile uint32_t *)0xfe000018)
#define P_CLKCTRL_LOCK_BIT_REG0 ((volatile uint32_t *)0xfe000020)
#define P_CLKCTRL_LOCK_BIT_REG1 ((volatile uint32_t *)0xfe000024)
#define P_CLKCTRL_LOCK_BIT_REG2 ((volatile uint32_t *)0xfe000028)
#define P_CLKCTRL_LOCK_BIT_REG3 ((volatile uint32_t *)0xfe00002c)
#define P_CLKCTRL_PROT_BIT_REG0 ((volatile uint32_t *)0xfe000030)
#define P_CLKCTRL_PROT_BIT_REG1 ((volatile uint32_t *)0xfe000034)
#define P_CLKCTRL_PROT_BIT_REG2 ((volatile uint32_t *)0xfe000038)
#define P_CLKCTRL_PROT_BIT_REG3 ((volatile uint32_t *)0xfe00003c)
#define P_CLKCTRL_SYS_CLK_CTRL0 ((volatile uint32_t *)0xfe000040)
#define P_CLKCTRL_SYS_CLK_EN0_REG0 ((volatile uint32_t *)0xfe000044)
#define P_CLKCTRL_SYS_CLK_EN0_REG1 ((volatile uint32_t *)0xfe000048)
#define P_CLKCTRL_SYS_CLK_EN0_REG2 ((volatile uint32_t *)0xfe00004c)
#define P_CLKCTRL_SYS_CLK_EN0_REG3 ((volatile uint32_t *)0xfe000050)
#define P_CLKCTRL_SYS_CLK_EN1_REG0 ((volatile uint32_t *)0xfe000054)
#define P_CLKCTRL_SYS_CLK_EN1_REG1 ((volatile uint32_t *)0xfe000058)
#define P_CLKCTRL_SYS_CLK_EN1_REG2 ((volatile uint32_t *)0xfe00005c)
#define P_CLKCTRL_SYS_CLK_EN1_REG3 ((volatile uint32_t *)0xfe000060)
#define P_CLKCTRL_SYS_CLK_VPU_EN0 ((volatile uint32_t *)0xfe000064)
#define P_CLKCTRL_SYS_CLK_VPU_EN1 ((volatile uint32_t *)0xfe000068)
#define P_CLKCTRL_AXI_CLK_CTRL0 ((volatile uint32_t *)0xfe00006c)
#define P_CLKCTRL_SYSOSCIN_CTRL ((volatile uint32_t *)0xfe000070)
#define P_CLKCTRL_TST_CTRL0 ((volatile uint32_t *)0xfe000080)
#define P_CLKCTRL_TST_CTRL1 ((volatile uint32_t *)0xfe000084)
#define P_CLKCTRL_CECA_CTRL0 ((volatile uint32_t *)0xfe000088)
#define P_CLKCTRL_CECA_CTRL1 ((volatile uint32_t *)0xfe00008c)
#define P_CLKCTRL_CECB_CTRL0 ((volatile uint32_t *)0xfe000090)
#define P_CLKCTRL_CECB_CTRL1 ((volatile uint32_t *)0xfe000094)
#define P_CLKCTRL_SC_CLK_CTRL ((volatile uint32_t *)0xfe000098)
#define P_CLKCTRL_DSPA_CLK_CTRL0 ((volatile uint32_t *)0xfe00009c)
//`define CLKCTRL_DSPB_CLK_CTRL0          10'h28
#define P_CLKCTRL_RAMA_CLK_CTRL0 ((volatile uint32_t *)0xfe0000a4)
#define P_CLKCTRL_CLK12_24_CTRL ((volatile uint32_t *)0xfe0000a8)
#define P_CLKCTRL_AXI_CLK_EN0 ((volatile uint32_t *)0xfe0000ac)
#define P_CLKCTRL_AXI_CLK_EN1 ((volatile uint32_t *)0xfe0000b0)
//`define CLKCTRL_RTCPLL_CTRL0            10'h2b
//`define CLKCTRL_RTCPLL_CTRL1            10'h2c
//`define CLKCTRL_RTCPLL_CTRL2            10'h2d
//`define CLKCTRL_RTCPLL_CTRL3            10'h2e
//`define CLKCTRL_RTCPLL_CTRL4            10'h2f
//`define CLKCTRL_RTCPLL_STS              10'h28
#define P_CLKCTRL_VID_CLK_CTRL ((volatile uint32_t *)0xfe0000c0)
#define P_CLKCTRL_VID_CLK_CTRL2 ((volatile uint32_t *)0xfe0000c4)
#define P_CLKCTRL_VID_CLK_DIV ((volatile uint32_t *)0xfe0000c8)
#define P_CLKCTRL_VIID_CLK_DIV ((volatile uint32_t *)0xfe0000cc)
#define P_CLKCTRL_VIID_CLK_CTRL ((volatile uint32_t *)0xfe0000d0)
#define P_CLKCTRL_HDMI_CLK_CTRL ((volatile uint32_t *)0xfe0000e0)
#define P_CLKCTRL_VID_PLL_CLK_DIV ((volatile uint32_t *)0xfe0000e4)
#define P_CLKCTRL_VPU_CLK_CTRL ((volatile uint32_t *)0xfe0000e8)
#define P_CLKCTRL_VPU_CLKB_CTRL ((volatile uint32_t *)0xfe0000ec)
#define P_CLKCTRL_VPU_CLKC_CTRL ((volatile uint32_t *)0xfe0000f0)
#define P_CLKCTRL_VID_LOCK_CLK_CTRL ((volatile uint32_t *)0xfe0000f4)
#define P_CLKCTRL_VDIN_MEAS_CLK_CTRL ((volatile uint32_t *)0xfe0000f8)
#define P_CLKCTRL_VAPBCLK_CTRL ((volatile uint32_t *)0xfe0000fc)
#define P_CLKCTRL_HDCP22_CLK_CTRL ((volatile uint32_t *)0xfe000100)
//`define CLKCTRL_MIPIDSI_PHY_CLK_CTRL    10'h41
#define P_CLKCTRL_CDAC_CLK_CTRL ((volatile uint32_t *)0xfe000108)
//`define CLKCTRL_MIPI_CSI_PHY_CLK_CTRL   10'h43
//`define CLKCTRL_CSI2_ADAPT_CLK_CTRL     10'h44
#define P_CLKCTRL_VDEC_CLK_CTRL ((volatile uint32_t *)0xfe000140)
#define P_CLKCTRL_VDEC2_CLK_CTRL ((volatile uint32_t *)0xfe000144)
#define P_CLKCTRL_VDEC3_CLK_CTRL ((volatile uint32_t *)0xfe000148)
#define P_CLKCTRL_VDEC4_CLK_CTRL ((volatile uint32_t *)0xfe00014c)
//`define CLKCTRL_WAVE420L_CLK_CTRL       10'h54
//`define CLKCTRL_WAVE420L_CLK_CTRL2      10'h55
#define P_CLKCTRL_TS_CLK_CTRL ((volatile uint32_t *)0xfe000158)
#define P_CLKCTRL_MALI_CLK_CTRL ((volatile uint32_t *)0xfe00015c)
//`define CLKCTRL_VIPNANOQ_CLK_CTRL       10'h58
#define P_CLKCTRL_ETH_CLK_CTRL ((volatile uint32_t *)0xfe000164)
#define P_CLKCTRL_NAND_CLK_CTRL ((volatile uint32_t *)0xfe000168)
#define P_CLKCTRL_SD_EMMC_CLK_CTRL ((volatile uint32_t *)0xfe00016c)
//`define CLKCTRL_BT656_CLK_CTRL          10'h5C
#define P_CLKCTRL_SPICC_CLK_CTRL ((volatile uint32_t *)0xfe000174)
#define P_CLKCTRL_GEN_CLK_CTRL ((volatile uint32_t *)0xfe000178)
#define P_CLKCTRL_SAR_CLK_CTRL0 ((volatile uint32_t *)0xfe00017c)
#define P_CLKCTRL_PWM_CLK_AB_CTRL ((volatile uint32_t *)0xfe000180)
#define P_CLKCTRL_PWM_CLK_CD_CTRL ((volatile uint32_t *)0xfe000184)
#define P_CLKCTRL_PWM_CLK_EF_CTRL ((volatile uint32_t *)0xfe000188)
#define P_CLKCTRL_PWM_CLK_GH_CTRL ((volatile uint32_t *)0xfe00018c)
#define P_CLKCTRL_PWM_CLK_IJ_CTRL ((volatile uint32_t *)0xfe000190)
#define P_CLKCTRL_DEMOD_CLK_CTRL ((volatile uint32_t *)0xfe000200)
#define P_CLKCTRL_NNA_CLK_CNTL ((volatile uint32_t *)0xfe000220)
#define P_CLKCTRL_TIMESTAMP_CTRL ((volatile uint32_t *)0xfe000400)
#define P_CLKCTRL_TIMESTAMP_CTRL1 ((volatile uint32_t *)0xfe000404)
#define P_CLKCTRL_TIMESTAMP_CTRL2 ((volatile uint32_t *)0xfe00040c)
#define P_CLKCTRL_TIMESTAMP_RD0 ((volatile uint32_t *)0xfe000410)
#define P_CLKCTRL_TIMESTAMP_RD1 ((volatile uint32_t *)0xfe000414)
#define P_CLKCTRL_TIMEBASE_CTRL0 ((volatile uint32_t *)0xfe000418)
#define P_CLKCTRL_TIMEBASE_CTRL1 ((volatile uint32_t *)0xfe00041c)
#define P_CLKCTRL_EFUSE_CPU_CFG01 ((volatile uint32_t *)0xfe000480)
#define P_CLKCTRL_EFUSE_CPU_CFG2 ((volatile uint32_t *)0xfe000484)
#define P_CLKCTRL_EFUSE_ENCP_CFG0 ((volatile uint32_t *)0xfe000488)
#define P_CLKCTRL_EFUSE_MALI_CFG01 ((volatile uint32_t *)0xfe00048c)
#define P_CLKCTRL_EFUSE_HEVCB_CFG01 ((volatile uint32_t *)0xfe000490)
#define P_CLKCTRL_EFUSE_HEVCB_CFG2 ((volatile uint32_t *)0xfe000494)
#define P_CLKCTRL_EFUSE_LOCK ((volatile uint32_t *)0xfe000498)
//========================================================================
//  PWR_CTRL
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe00c000
// -----------------------------------------------
#define P_PWRCTRL_PWR_ACK0 ((volatile uint32_t *)0xfe00c000)
#define P_PWRCTRL_PWR_ACK1 ((volatile uint32_t *)0xfe00c004)
#define P_PWRCTRL_PWR_OFF0 ((volatile uint32_t *)0xfe00c010)
#define P_PWRCTRL_PWR_OFF1 ((volatile uint32_t *)0xfe00c014)
#define P_PWRCTRL_ISO_EN0 ((volatile uint32_t *)0xfe00c020)
#define P_PWRCTRL_ISO_EN1 ((volatile uint32_t *)0xfe00c024)
#define P_PWRCTRL_FOCRST0 ((volatile uint32_t *)0xfe00c030)
#define P_PWRCTRL_FOCRST1 ((volatile uint32_t *)0xfe00c034)
#define P_PWRCTRL_MEM_PD0 ((volatile uint32_t *)0xfe00c040)
#define P_PWRCTRL_MEM_PD1 ((volatile uint32_t *)0xfe00c044)
#define P_PWRCTRL_MEM_PD2 ((volatile uint32_t *)0xfe00c048)
#define P_PWRCTRL_MEM_PD3 ((volatile uint32_t *)0xfe00c04c)
#define P_PWRCTRL_MEM_PD4 ((volatile uint32_t *)0xfe00c050)
#define P_PWRCTRL_MEM_PD5 ((volatile uint32_t *)0xfe00c054)
#define P_PWRCTRL_MEM_PD6 ((volatile uint32_t *)0xfe00c058)
#define P_PWRCTRL_MEM_PD7 ((volatile uint32_t *)0xfe00c05c)
#define P_PWRCTRL_MEM_PD8 ((volatile uint32_t *)0xfe00c060)
#define P_PWRCTRL_MEM_PD9 ((volatile uint32_t *)0xfe00c064)
#define P_PWRCTRL_MEM_PD10 ((volatile uint32_t *)0xfe00c068)
#define P_PWRCTRL_MEM_PD11 ((volatile uint32_t *)0xfe00c06c)
#define P_PWRCTRL_MEM_PD12 ((volatile uint32_t *)0xfe00c070)
#define P_PWRCTRL_MEM_PD13 ((volatile uint32_t *)0xfe00c074)
#define P_PWRCTRL_MEM_PD14 ((volatile uint32_t *)0xfe00c078)
#define P_PWRCTRL_MEM_PD15 ((volatile uint32_t *)0xfe00c07c)
#define P_PWRCTRL_NNA_AXI_PWR_CTRL ((volatile uint32_t *)0xfe00c080)
#define P_PWRCTRL_ACCESS_CTRL ((volatile uint32_t *)0xfe00c084)
#define P_PWRCTRL_CPU0_AUTO_OFF_CTRL0 ((volatile uint32_t *)0xfe00c100)
#define P_PWRCTRL_CPU0_AUTO_OFF_CTRL1 ((volatile uint32_t *)0xfe00c104)
#define P_PWRCTRL_CPU0_AUTO_OFF_CTRL2 ((volatile uint32_t *)0xfe00c108)
#define P_PWRCTRL_CPU0_AUTO_OFF_CTRL3 ((volatile uint32_t *)0xfe00c10c)
#define P_PWRCTRL_CPU0_AUTO_OFF_CTRL4 ((volatile uint32_t *)0xfe00c110)
#define P_PWRCTRL_CPU0_TIMER_TH_01 ((volatile uint32_t *)0xfe00c120)
#define P_PWRCTRL_CPU0_TIMER_TH_23 ((volatile uint32_t *)0xfe00c124)
#define P_PWRCTRL_CPU0_TIMER_TH_45 ((volatile uint32_t *)0xfe00c128)
#define P_PWRCTRL_CPU0_TIMER_TH_67 ((volatile uint32_t *)0xfe00c12c)
#define P_PWRCTRL_CPU0_TIMER_TH_89 ((volatile uint32_t *)0xfe00c130)
#define P_PWRCTRL_CPU0_IRQ_MASK0 ((volatile uint32_t *)0xfe00c140)
#define P_PWRCTRL_CPU0_IRQ_MASK1 ((volatile uint32_t *)0xfe00c144)
#define P_PWRCTRL_CPU0_IRQ_MASK2 ((volatile uint32_t *)0xfe00c148)
#define P_PWRCTRL_CPU0_IRQ_MASK3 ((volatile uint32_t *)0xfe00c14c)
#define P_PWRCTRL_CPU0_IRQ_MASK4 ((volatile uint32_t *)0xfe00c150)
#define P_PWRCTRL_CPU0_IRQ_MASK5 ((volatile uint32_t *)0xfe00c154)
#define P_PWRCTRL_CPU0_IRQ_MASK6 ((volatile uint32_t *)0xfe00c158)
#define P_PWRCTRL_CPU0_IRQ_MASK7 ((volatile uint32_t *)0xfe00c15c)
#define P_PWRCTRL_CPU0_MEMPD_INIT_SET ((volatile uint32_t *)0xfe00c180)
#define P_PWRCTRL_CPU0_MEMPD_OFF_SET ((volatile uint32_t *)0xfe00c184)
#define P_PWRCTRL_CPU0_MEMPD_ON_A_SET ((volatile uint32_t *)0xfe00c188)
#define P_PWRCTRL_CPU0_MEMPD_ON_B_SET ((volatile uint32_t *)0xfe00c18c)
#define P_PWRCTRL_CPU0_MEMPD_ON_C_SET ((volatile uint32_t *)0xfe00c190)
#define P_PWRCTRL_CPU0_MEMPD_ON_D_SET ((volatile uint32_t *)0xfe00c194)
#define P_PWRCTRL_CPU0_MEMPD_STS ((volatile uint32_t *)0xfe00c198)
#define P_PWRCTRL_CPU0_FSM_STS0 ((volatile uint32_t *)0xfe00c19c)
#define P_PWRCTRL_CPU0_FSM_STS1 ((volatile uint32_t *)0xfe00c1a0)
#define P_PWRCTRL_CPU0_FSM_STS2 ((volatile uint32_t *)0xfe00c1a4)
#define P_PWRCTRL_CPU0_FSM_START_OFF ((volatile uint32_t *)0xfe00c1b4)
#define P_PWRCTRL_CPU0_FSM_START_ON ((volatile uint32_t *)0xfe00c1b8)
#define P_PWRCTRL_CPU0_FSM_JUMP ((volatile uint32_t *)0xfe00c1bc)
#define P_PWRCTRL_CPU1_AUTO_OFF_CTRL0 ((volatile uint32_t *)0xfe00c1c0)
#define P_PWRCTRL_CPU1_AUTO_OFF_CTRL1 ((volatile uint32_t *)0xfe00c1c4)
#define P_PWRCTRL_CPU1_AUTO_OFF_CTRL2 ((volatile uint32_t *)0xfe00c1c8)
#define P_PWRCTRL_CPU1_AUTO_OFF_CTRL3 ((volatile uint32_t *)0xfe00c1cc)
#define P_PWRCTRL_CPU1_AUTO_OFF_CTRL4 ((volatile uint32_t *)0xfe00c1d0)
#define P_PWRCTRL_CPU1_TIMER_TH_01 ((volatile uint32_t *)0xfe00c1e0)
#define P_PWRCTRL_CPU1_TIMER_TH_23 ((volatile uint32_t *)0xfe00c1e4)
#define P_PWRCTRL_CPU1_TIMER_TH_45 ((volatile uint32_t *)0xfe00c1e8)
#define P_PWRCTRL_CPU1_TIMER_TH_67 ((volatile uint32_t *)0xfe00c1ec)
#define P_PWRCTRL_CPU1_TIMER_TH_89 ((volatile uint32_t *)0xfe00c1f0)
#define P_PWRCTRL_CPU1_IRQ_MASK0 ((volatile uint32_t *)0xfe00c200)
#define P_PWRCTRL_CPU1_IRQ_MASK1 ((volatile uint32_t *)0xfe00c204)
#define P_PWRCTRL_CPU1_IRQ_MASK2 ((volatile uint32_t *)0xfe00c208)
#define P_PWRCTRL_CPU1_IRQ_MASK3 ((volatile uint32_t *)0xfe00c20c)
#define P_PWRCTRL_CPU1_IRQ_MASK4 ((volatile uint32_t *)0xfe00c210)
#define P_PWRCTRL_CPU1_IRQ_MASK5 ((volatile uint32_t *)0xfe00c214)
#define P_PWRCTRL_CPU1_IRQ_MASK6 ((volatile uint32_t *)0xfe00c218)
#define P_PWRCTRL_CPU1_IRQ_MASK7 ((volatile uint32_t *)0xfe00c21c)
#define P_PWRCTRL_CPU1_MEMPD_INIT_SET ((volatile uint32_t *)0xfe00c240)
#define P_PWRCTRL_CPU1_MEMPD_OFF_SET ((volatile uint32_t *)0xfe00c244)
#define P_PWRCTRL_CPU1_MEMPD_ON_A_SET ((volatile uint32_t *)0xfe00c248)
#define P_PWRCTRL_CPU1_MEMPD_ON_B_SET ((volatile uint32_t *)0xfe00c24c)
#define P_PWRCTRL_CPU1_MEMPD_ON_C_SET ((volatile uint32_t *)0xfe00c250)
#define P_PWRCTRL_CPU1_MEMPD_ON_D_SET ((volatile uint32_t *)0xfe00c254)
#define P_PWRCTRL_CPU1_MEMPD_STS ((volatile uint32_t *)0xfe00c258)
#define P_PWRCTRL_CPU1_FSM_STS0 ((volatile uint32_t *)0xfe00c25c)
#define P_PWRCTRL_CPU1_FSM_STS1 ((volatile uint32_t *)0xfe00c260)
#define P_PWRCTRL_CPU1_FSM_STS2 ((volatile uint32_t *)0xfe00c264)
#define P_PWRCTRL_CPU1_FSM_START_OFF ((volatile uint32_t *)0xfe00c274)
#define P_PWRCTRL_CPU1_FSM_START_ON ((volatile uint32_t *)0xfe00c278)
#define P_PWRCTRL_CPU1_FSM_JUMP ((volatile uint32_t *)0xfe00c27c)
#define P_PWRCTRL_CPU2_AUTO_OFF_CTRL0 ((volatile uint32_t *)0xfe00c280)
#define P_PWRCTRL_CPU2_AUTO_OFF_CTRL1 ((volatile uint32_t *)0xfe00c284)
#define P_PWRCTRL_CPU2_AUTO_OFF_CTRL2 ((volatile uint32_t *)0xfe00c288)
#define P_PWRCTRL_CPU2_AUTO_OFF_CTRL3 ((volatile uint32_t *)0xfe00c28c)
#define P_PWRCTRL_CPU2_AUTO_OFF_CTRL4 ((volatile uint32_t *)0xfe00c290)
#define P_PWRCTRL_CPU2_TIMER_TH_01 ((volatile uint32_t *)0xfe00c2a0)
#define P_PWRCTRL_CPU2_TIMER_TH_23 ((volatile uint32_t *)0xfe00c2a4)
#define P_PWRCTRL_CPU2_TIMER_TH_45 ((volatile uint32_t *)0xfe00c2a8)
#define P_PWRCTRL_CPU2_TIMER_TH_67 ((volatile uint32_t *)0xfe00c2ac)
#define P_PWRCTRL_CPU2_TIMER_TH_89 ((volatile uint32_t *)0xfe00c2b0)
#define P_PWRCTRL_CPU2_IRQ_MASK0 ((volatile uint32_t *)0xfe00c2c0)
#define P_PWRCTRL_CPU2_IRQ_MASK1 ((volatile uint32_t *)0xfe00c2c4)
#define P_PWRCTRL_CPU2_IRQ_MASK2 ((volatile uint32_t *)0xfe00c2c8)
#define P_PWRCTRL_CPU2_IRQ_MASK3 ((volatile uint32_t *)0xfe00c2cc)
#define P_PWRCTRL_CPU2_IRQ_MASK4 ((volatile uint32_t *)0xfe00c2d0)
#define P_PWRCTRL_CPU2_IRQ_MASK5 ((volatile uint32_t *)0xfe00c2d4)
#define P_PWRCTRL_CPU2_IRQ_MASK6 ((volatile uint32_t *)0xfe00c2d8)
#define P_PWRCTRL_CPU2_IRQ_MASK7 ((volatile uint32_t *)0xfe00c2dc)
#define P_PWRCTRL_CPU2_MEMPD_INIT_SET ((volatile uint32_t *)0xfe00c300)
#define P_PWRCTRL_CPU2_MEMPD_OFF_SET ((volatile uint32_t *)0xfe00c304)
#define P_PWRCTRL_CPU2_MEMPD_ON_A_SET ((volatile uint32_t *)0xfe00c308)
#define P_PWRCTRL_CPU2_MEMPD_ON_B_SET ((volatile uint32_t *)0xfe00c30c)
#define P_PWRCTRL_CPU2_MEMPD_ON_C_SET ((volatile uint32_t *)0xfe00c310)
#define P_PWRCTRL_CPU2_MEMPD_ON_D_SET ((volatile uint32_t *)0xfe00c314)
#define P_PWRCTRL_CPU2_MEMPD_STS ((volatile uint32_t *)0xfe00c318)
#define P_PWRCTRL_CPU2_FSM_STS0 ((volatile uint32_t *)0xfe00c31c)
#define P_PWRCTRL_CPU2_FSM_STS1 ((volatile uint32_t *)0xfe00c320)
#define P_PWRCTRL_CPU2_FSM_STS2 ((volatile uint32_t *)0xfe00c324)
#define P_PWRCTRL_CPU2_FSM_START_OFF ((volatile uint32_t *)0xfe00c334)
#define P_PWRCTRL_CPU2_FSM_START_ON ((volatile uint32_t *)0xfe00c338)
#define P_PWRCTRL_CPU2_FSM_JUMP ((volatile uint32_t *)0xfe00c33c)
#define P_PWRCTRL_CPU3_AUTO_OFF_CTRL0 ((volatile uint32_t *)0xfe00c340)
#define P_PWRCTRL_CPU3_AUTO_OFF_CTRL1 ((volatile uint32_t *)0xfe00c344)
#define P_PWRCTRL_CPU3_AUTO_OFF_CTRL2 ((volatile uint32_t *)0xfe00c348)
#define P_PWRCTRL_CPU3_AUTO_OFF_CTRL3 ((volatile uint32_t *)0xfe00c34c)
#define P_PWRCTRL_CPU3_AUTO_OFF_CTRL4 ((volatile uint32_t *)0xfe00c350)
#define P_PWRCTRL_CPU3_TIMER_TH_01 ((volatile uint32_t *)0xfe00c360)
#define P_PWRCTRL_CPU3_TIMER_TH_23 ((volatile uint32_t *)0xfe00c364)
#define P_PWRCTRL_CPU3_TIMER_TH_45 ((volatile uint32_t *)0xfe00c368)
#define P_PWRCTRL_CPU3_TIMER_TH_67 ((volatile uint32_t *)0xfe00c36c)
#define P_PWRCTRL_CPU3_TIMER_TH_89 ((volatile uint32_t *)0xfe00c370)
#define P_PWRCTRL_CPU3_IRQ_MASK0 ((volatile uint32_t *)0xfe00c380)
#define P_PWRCTRL_CPU3_IRQ_MASK1 ((volatile uint32_t *)0xfe00c384)
#define P_PWRCTRL_CPU3_IRQ_MASK2 ((volatile uint32_t *)0xfe00c388)
#define P_PWRCTRL_CPU3_IRQ_MASK3 ((volatile uint32_t *)0xfe00c38c)
#define P_PWRCTRL_CPU3_IRQ_MASK4 ((volatile uint32_t *)0xfe00c390)
#define P_PWRCTRL_CPU3_IRQ_MASK5 ((volatile uint32_t *)0xfe00c394)
#define P_PWRCTRL_CPU3_IRQ_MASK6 ((volatile uint32_t *)0xfe00c398)
#define P_PWRCTRL_CPU3_IRQ_MASK7 ((volatile uint32_t *)0xfe00c39c)
#define P_PWRCTRL_CPU3_MEMPD_INIT_SET ((volatile uint32_t *)0xfe00c3c0)
#define P_PWRCTRL_CPU3_MEMPD_OFF_SET ((volatile uint32_t *)0xfe00c3c4)
#define P_PWRCTRL_CPU3_MEMPD_ON_A_SET ((volatile uint32_t *)0xfe00c3c8)
#define P_PWRCTRL_CPU3_MEMPD_ON_B_SET ((volatile uint32_t *)0xfe00c3cc)
#define P_PWRCTRL_CPU3_MEMPD_ON_C_SET ((volatile uint32_t *)0xfe00c3d0)
#define P_PWRCTRL_CPU3_MEMPD_ON_D_SET ((volatile uint32_t *)0xfe00c3d4)
#define P_PWRCTRL_CPU3_MEMPD_STS ((volatile uint32_t *)0xfe00c3d8)
#define P_PWRCTRL_CPU3_FSM_STS0 ((volatile uint32_t *)0xfe00c3dc)
#define P_PWRCTRL_CPU3_FSM_STS1 ((volatile uint32_t *)0xfe00c3e0)
#define P_PWRCTRL_CPU3_FSM_STS2 ((volatile uint32_t *)0xfe00c3e4)
#define P_PWRCTRL_CPU3_FSM_START_OFF ((volatile uint32_t *)0xfe00c3f4)
#define P_PWRCTRL_CPU3_FSM_START_ON ((volatile uint32_t *)0xfe00c3f8)
#define P_PWRCTRL_CPU3_FSM_JUMP ((volatile uint32_t *)0xfe00c3fc)
#define P_PWRCTRL_CPUTOP_AUTO_OFF_CTRL0 ((volatile uint32_t *)0xfe00c400)
#define P_PWRCTRL_CPUTOP_AUTO_OFF_CTRL1 ((volatile uint32_t *)0xfe00c404)
#define P_PWRCTRL_CPUTOP_AUTO_OFF_CTRL2 ((volatile uint32_t *)0xfe00c408)
#define P_PWRCTRL_CPUTOP_AUTO_OFF_CTRL3 ((volatile uint32_t *)0xfe00c40c)
#define P_PWRCTRL_CPUTOP_AUTO_OFF_CTRL4 ((volatile uint32_t *)0xfe00c410)
#define P_PWRCTRL_CPUTOP_TIMER_TH_01 ((volatile uint32_t *)0xfe00c420)
#define P_PWRCTRL_CPUTOP_TIMER_TH_23 ((volatile uint32_t *)0xfe00c424)
#define P_PWRCTRL_CPUTOP_TIMER_TH_45 ((volatile uint32_t *)0xfe00c428)
#define P_PWRCTRL_CPUTOP_TIMER_TH_67 ((volatile uint32_t *)0xfe00c42c)
#define P_PWRCTRL_CPUTOP_TIMER_TH_89 ((volatile uint32_t *)0xfe00c430)
#define P_PWRCTRL_CPUTOP_IRQ_MASK0 ((volatile uint32_t *)0xfe00c440)
#define P_PWRCTRL_CPUTOP_IRQ_MASK1 ((volatile uint32_t *)0xfe00c444)
#define P_PWRCTRL_CPUTOP_IRQ_MASK2 ((volatile uint32_t *)0xfe00c448)
#define P_PWRCTRL_CPUTOP_IRQ_MASK3 ((volatile uint32_t *)0xfe00c44c)
#define P_PWRCTRL_CPUTOP_IRQ_MASK4 ((volatile uint32_t *)0xfe00c450)
#define P_PWRCTRL_CPUTOP_IRQ_MASK5 ((volatile uint32_t *)0xfe00c454)
#define P_PWRCTRL_CPUTOP_IRQ_MASK6 ((volatile uint32_t *)0xfe00c458)
#define P_PWRCTRL_CPUTOP_IRQ_MASK7 ((volatile uint32_t *)0xfe00c45c)
#define P_PWRCTRL_CPUTOP_MEMPD_INIT_SET ((volatile uint32_t *)0xfe00c480)
#define P_PWRCTRL_CPUTOP_MEMPD_OFF_SET ((volatile uint32_t *)0xfe00c484)
#define P_PWRCTRL_CPUTOP_MEMPD_ON_A_SET ((volatile uint32_t *)0xfe00c488)
#define P_PWRCTRL_CPUTOP_MEMPD_ON_B_SET ((volatile uint32_t *)0xfe00c48c)
#define P_PWRCTRL_CPUTOP_MEMPD_ON_C_SET ((volatile uint32_t *)0xfe00c490)
#define P_PWRCTRL_CPUTOP_MEMPD_ON_D_SET ((volatile uint32_t *)0xfe00c494)
#define P_PWRCTRL_CPUTOP_MEMPD_STS ((volatile uint32_t *)0xfe00c498)
#define P_PWRCTRL_CPUTOP_FSM_STS0 ((volatile uint32_t *)0xfe00c49c)
#define P_PWRCTRL_CPUTOP_FSM_STS1 ((volatile uint32_t *)0xfe00c4a0)
#define P_PWRCTRL_CPUTOP_FSM_STS2 ((volatile uint32_t *)0xfe00c4a4)
#define P_PWRCTRL_CPUTOP_FSM_START_OFF ((volatile uint32_t *)0xfe00c4b4)
#define P_PWRCTRL_CPUTOP_FSM_START_ON ((volatile uint32_t *)0xfe00c4b8)
#define P_PWRCTRL_CPUTOP_FSM_JUMP ((volatile uint32_t *)0xfe00c4bc)
#define P_PWRCTRL_DSPA_AUTO_OFF_CTRL0 ((volatile uint32_t *)0xfe00c4c0)
#define P_PWRCTRL_DSPA_AUTO_OFF_CTRL1 ((volatile uint32_t *)0xfe00c4c4)
#define P_PWRCTRL_DSPA_AUTO_OFF_CTRL2 ((volatile uint32_t *)0xfe00c4c8)
#define P_PWRCTRL_DSPA_AUTO_OFF_CTRL3 ((volatile uint32_t *)0xfe00c4cc)
#define P_PWRCTRL_DSPA_AUTO_OFF_CTRL4 ((volatile uint32_t *)0xfe00c4d0)
#define P_PWRCTRL_DSPA_TIMER_TH_01 ((volatile uint32_t *)0xfe00c4e0)
#define P_PWRCTRL_DSPA_TIMER_TH_23 ((volatile uint32_t *)0xfe00c4e4)
#define P_PWRCTRL_DSPA_TIMER_TH_45 ((volatile uint32_t *)0xfe00c4e8)
#define P_PWRCTRL_DSPA_TIMER_TH_67 ((volatile uint32_t *)0xfe00c4ec)
#define P_PWRCTRL_DSPA_TIMER_TH_89 ((volatile uint32_t *)0xfe00c4f0)
#define P_PWRCTRL_DSPA_IRQ_MASK0 ((volatile uint32_t *)0xfe00c500)
#define P_PWRCTRL_DSPA_IRQ_MASK1 ((volatile uint32_t *)0xfe00c504)
#define P_PWRCTRL_DSPA_IRQ_MASK2 ((volatile uint32_t *)0xfe00c508)
#define P_PWRCTRL_DSPA_IRQ_MASK3 ((volatile uint32_t *)0xfe00c50c)
#define P_PWRCTRL_DSPA_IRQ_MASK4 ((volatile uint32_t *)0xfe00c510)
#define P_PWRCTRL_DSPA_IRQ_MASK5 ((volatile uint32_t *)0xfe00c514)
#define P_PWRCTRL_DSPA_IRQ_MASK6 ((volatile uint32_t *)0xfe00c518)
#define P_PWRCTRL_DSPA_IRQ_MASK7 ((volatile uint32_t *)0xfe00c51c)
#define P_PWRCTRL_DSPA_MEMPD_INIT_SET ((volatile uint32_t *)0xfe00c540)
#define P_PWRCTRL_DSPA_MEMPD_OFF_SET ((volatile uint32_t *)0xfe00c544)
#define P_PWRCTRL_DSPA_MEMPD_ON_A_SET ((volatile uint32_t *)0xfe00c548)
#define P_PWRCTRL_DSPA_MEMPD_ON_B_SET ((volatile uint32_t *)0xfe00c54c)
#define P_PWRCTRL_DSPA_MEMPD_ON_C_SET ((volatile uint32_t *)0xfe00c550)
#define P_PWRCTRL_DSPA_MEMPD_ON_D_SET ((volatile uint32_t *)0xfe00c554)
#define P_PWRCTRL_DSPA_MEMPD_STS ((volatile uint32_t *)0xfe00c558)
#define P_PWRCTRL_DSPA_FSM_STS0 ((volatile uint32_t *)0xfe00c55c)
#define P_PWRCTRL_DSPA_FSM_STS1 ((volatile uint32_t *)0xfe00c560)
#define P_PWRCTRL_DSPA_FSM_STS2 ((volatile uint32_t *)0xfe00c564)
#define P_PWRCTRL_DSPA_FSM_START_OFF ((volatile uint32_t *)0xfe00c574)
#define P_PWRCTRL_DSPA_FSM_START_ON ((volatile uint32_t *)0xfe00c578)
#define P_PWRCTRL_DSPA_FSM_JUMP ((volatile uint32_t *)0xfe00c57c)
#define P_PWRCTRL_AOCPU_AUTO_OFF_CTRL0 ((volatile uint32_t *)0xfe00c580)
#define P_PWRCTRL_AOCPU_AUTO_OFF_CTRL1 ((volatile uint32_t *)0xfe00c584)
#define P_PWRCTRL_AOCPU_AUTO_OFF_CTRL2 ((volatile uint32_t *)0xfe00c588)
#define P_PWRCTRL_AOCPU_AUTO_OFF_CTRL3 ((volatile uint32_t *)0xfe00c58c)
#define P_PWRCTRL_AOCPU_AUTO_OFF_CTRL4 ((volatile uint32_t *)0xfe00c590)
#define P_PWRCTRL_AOCPU_TIMER_TH_01 ((volatile uint32_t *)0xfe00c5a0)
#define P_PWRCTRL_AOCPU_TIMER_TH_23 ((volatile uint32_t *)0xfe00c5a4)
#define P_PWRCTRL_AOCPU_TIMER_TH_45 ((volatile uint32_t *)0xfe00c5a8)
#define P_PWRCTRL_AOCPU_TIMER_TH_67 ((volatile uint32_t *)0xfe00c5ac)
#define P_PWRCTRL_AOCPU_TIMER_TH_89 ((volatile uint32_t *)0xfe00c5b0)
#define P_PWRCTRL_AOCPU_IRQ_MASK0 ((volatile uint32_t *)0xfe00c5c0)
#define P_PWRCTRL_AOCPU_IRQ_MASK1 ((volatile uint32_t *)0xfe00c5c4)
#define P_PWRCTRL_AOCPU_IRQ_MASK2 ((volatile uint32_t *)0xfe00c5c8)
#define P_PWRCTRL_AOCPU_IRQ_MASK3 ((volatile uint32_t *)0xfe00c5cc)
#define P_PWRCTRL_AOCPU_IRQ_MASK4 ((volatile uint32_t *)0xfe00c5d0)
#define P_PWRCTRL_AOCPU_IRQ_MASK5 ((volatile uint32_t *)0xfe00c5d4)
#define P_PWRCTRL_AOCPU_IRQ_MASK6 ((volatile uint32_t *)0xfe00c5d8)
#define P_PWRCTRL_AOCPU_IRQ_MASK7 ((volatile uint32_t *)0xfe00c5dc)
#define P_PWRCTRL_AOCPU_MEMPD_INIT_SET ((volatile uint32_t *)0xfe00c600)
#define P_PWRCTRL_AOCPU_MEMPD_OFF_SET ((volatile uint32_t *)0xfe00c604)
#define P_PWRCTRL_AOCPU_MEMPD_ON_A_SET ((volatile uint32_t *)0xfe00c608)
#define P_PWRCTRL_AOCPU_MEMPD_ON_B_SET ((volatile uint32_t *)0xfe00c60c)
#define P_PWRCTRL_AOCPU_MEMPD_ON_C_SET ((volatile uint32_t *)0xfe00c610)
#define P_PWRCTRL_AOCPU_MEMPD_ON_D_SET ((volatile uint32_t *)0xfe00c614)
#define P_PWRCTRL_AOCPU_MEMPD_STS ((volatile uint32_t *)0xfe00c618)
#define P_PWRCTRL_AOCPU_FSM_STS0 ((volatile uint32_t *)0xfe00c61c)
#define P_PWRCTRL_AOCPU_FSM_STS1 ((volatile uint32_t *)0xfe00c620)
#define P_PWRCTRL_AOCPU_FSM_STS2 ((volatile uint32_t *)0xfe00c624)
#define P_PWRCTRL_AOCPU_FSM_START_OFF ((volatile uint32_t *)0xfe00c634)
#define P_PWRCTRL_AOCPU_FSM_START_ON ((volatile uint32_t *)0xfe00c638)
#define P_PWRCTRL_AOCPU_FSM_JUMP ((volatile uint32_t *)0xfe00c63c)
//========================================================================
// RSA
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe042000
// -----------------------------------------------
#define P_RSA_BASE ((volatile uint32_t *)0xfe042000)
//========================================================================
//  AOCPU
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe09c000
// -----------------------------------------------
#define P_AOCPU_CPU_CTRL0 ((volatile uint32_t *)0xfe09c000)
// Bit 31:0-       0   - reserved
#define P_AOCPU_CPU_CTRL1 ((volatile uint32_t *)0xfe09c004)
// Bit 31:11-       0   - n205 address shift, 1: 0x8000_0000~0x4000_0000
// Bit 30:11-       0   - reserved
// Bit 10   -       0   - gate by sleep, 1: gate, 0: free run
// Bit  9   -       0   - RXEV for riscv input refer riscv doc
// Bit  8   -       0   - reserved
// Bit   7:6-       0   - n205_debug_sel,aocpu_core_status0 info select
// Bit   5:2-       0   - reserved
// Bit 1    -       0   - n205_i_dbg_stop
// Bit 0    -       0   - n205_pc_enable
#define P_AOCPU_CPU_CTRL2 ((volatile uint32_t *)0xfe09c008)
// Bit 31:0-       0   - reserved
#define P_AOCPU_CPU_CTRL3 ((volatile uint32_t *)0xfe09c00c)
// Bit 31:0-       0   - reserved
#define P_AOCPU_CPU_CTRL4 ((volatile uint32_t *)0xfe09c010)
// Bit 31:0-       0   - reserved
#define P_AOCPU_CPU_CTRL5 ((volatile uint32_t *)0xfe09c014)
// Bit 31:0-       0   - reserved
#define P_AOCPU_CPU_STS0 ((volatile uint32_t *)0xfe09c028)
// Bit 31:0 -       0   - n205_debug_sel==0 : n205_trace_casuse, 1:n205_trace_tval,
// 2:n205_trace_iaddr, 3:n205_trace_instr
#define P_AOCPU_CPU_STS1 ((volatile uint32_t *)0xfe09c02c)
// Bit 31   -       0   - n205_core_sleep_value
// Bit 30:29-       0   - n205_trace_priv
// Bit 28:20-       0   - reserved
// Bit 19   -       0   - n205_core_wfi_mode
// Bit 18   -       0   - n205_trace_ivalid
// Bit 17   -       0   - n205_trace_iexception
// Bit 16   -       0   - n205_trace_interrupt
// Bit 15:0 -       0   - reserved
#define P_AOCPU_CPU_STS2 ((volatile uint32_t *)0xfe09c030)
// Bit 31:0-       0   - reserved
#define P_AOCPU_CPU_STS3 ((volatile uint32_t *)0xfe09c034)
// Bit 31   -       0   - n205_hart_halted
// Bit 30   -       0   - n205_ndmreset
// Bit 29   -       0   - n205_dmactive
// Bit 28:0 -       0   - reserved
#define P_AOCPU_CPU_VECTOR ((volatile uint32_t *)0xfe09c03c)
// Bit 31:0-   0x1000_0000   - reserved
#define P_AOCPU_IRQ_SEL0 ((volatile uint32_t *)0xfe09c040)
// Bit 31:24-       0   - INTISR03 interrupt source select in int_map
// Bit 23:16-       0   - INTISR02 interrupt source select in int_map
// Bit 15:8 -       0   - INTISR01 interrupt source select in int_map
// Bit  7:0 -       0   - INTISR00 interrupt source select in int_map
#define P_AOCPU_IRQ_SEL1 ((volatile uint32_t *)0xfe09c044)
// Bit 31:24-       0   - INTISR07 interrupt source select in int_map
// Bit 23:16-       0   - INTISR06 interrupt source select in int_map
// Bit 15:8 -       0   - INTISR05 interrupt source select in int_map
// Bit  7:0 -       0   - INTISR04 interrupt source select in int_map
#define P_AOCPU_IRQ_SEL2 ((volatile uint32_t *)0xfe09c048)
// Bit 31:24-       0   - INTISR11 interrupt source select in int_map
// Bit 23:16-       0   - INTISR10 interrupt source select in int_map
// Bit 15:8 -       0   - INTISR09 interrupt source select in int_map
// Bit  7:0 -       0   - INTISR08 interrupt source select in int_map
#define P_AOCPU_IRQ_SEL3 ((volatile uint32_t *)0xfe09c04c)
// Bit 31:24-       0   - INTISR15 interrupt source select in int_map
// Bit 23:16-       0   - INTISR14 interrupt source select in int_map
// Bit 15:8 -       0   - INTISR13 interrupt source select in int_map
// Bit  7:0 -       0   - INTISR12 interrupt source select in int_map
#define P_AOCPU_IRQ_SEL4 ((volatile uint32_t *)0xfe09c050)
// Bit 31:24-       0   - INTISR19 interrupt source select in int_map
// Bit 23:16-       0   - INTISR18 interrupt source select in int_map
// Bit 15:8 -       0   - INTISR17 interrupt source select in int_map
// Bit  7:0 -       0   - INTISR16 interrupt source select in int_map
#define P_AOCPU_IRQ_SEL5 ((volatile uint32_t *)0xfe09c054)
// Bit 31:24-       0   - INTISR23 interrupt source select in int_map
// Bit 23:16-       0   - INTISR22 interrupt source select in int_map
// Bit 15:8 -       0   - INTISR21 interrupt source select in int_map
// Bit  7:0 -       0   - INTISR20 interrupt source select in int_map
#define P_AOCPU_IRQ_SEL6 ((volatile uint32_t *)0xfe09c058)
// Bit 31:24-       0   - INTISR27 interrupt source select in int_map
// Bit 23:16-       0   - INTISR26 interrupt source select in int_map
// Bit 15:8 -       0   - INTISR25 interrupt source select in int_map
// Bit  7:0 -       0   - INTISR24 interrupt source select in int_map
#define P_AOCPU_IRQ_SEL7 ((volatile uint32_t *)0xfe09c05c)
// Bit 31:24-       0   - INTISR31 interrupt source select in int_map
// Bit 23:16-       0   - INTISR30 interrupt source select in int_map
// Bit 15:8 -       0   - INTISR29 interrupt source select in int_map
// Bit  7:0 -       0   - INTISR28 interrupt source select in int_map
#define P_AOCPU_STS00_BYCPU ((volatile uint32_t *)0xfe09c060)
// Bit 31:0-       0   - reserved
#define P_AOCPU_STS01_BYCPU ((volatile uint32_t *)0xfe09c064)
// Bit 31:0-       0   - reserved
#define P_AOCPU_STS02_BYCPU ((volatile uint32_t *)0xfe09c068)
// Bit 31:0-       0   - reserved
#define P_AOCPU_STS03_BYCPU ((volatile uint32_t *)0xfe09c06c)
// Bit 31:0-       0   - reserved
#define P_AOCPU_STS04_BYCPU ((volatile uint32_t *)0xfe09c070)
// Bit 31:0-       0   - reserved
#define P_AOCPU_STS05_BYCPU ((volatile uint32_t *)0xfe09c074)
// Bit 31:0-       0   - reserved
#define P_AOCPU_STS06_BYCPU ((volatile uint32_t *)0xfe09c078)
// Bit 31:0-       0   - reserved
#define P_AOCPU_STS07_BYCPU ((volatile uint32_t *)0xfe09c07c)
// Bit 31:0-       0   - reserved
//========================================================================
//  AUCPU
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe09e000
// -----------------------------------------------
#define P_AUCPU_CPU_CTRL0 ((volatile uint32_t *)0xfe09e000)
// Bit 31:0 -       0   - reserved
#define P_AUCPU_CPU_CTRL1 ((volatile uint32_t *)0xfe09e004)
// Bit 31:11-       0   - reserved
// Bit 10   -       0   - gate by sleep
// Bit 9    -       0   - RXEV
// Bit 8    -       0   - reserved
// Bit 7:6  -       0   - n205_debug_sel,aucpu_core_status0 info select
// Bit 5:2  -       0   - reserved
// Bit 1    -       0   - n205_i_dbg_stop
// Bit 0    -       0   - n205_pc_enable
#define P_AUCPU_CPU_CTRL2 ((volatile uint32_t *)0xfe09e008)
// Bit 31:0 -       0   - reserved
#define P_AUCPU_CPU_CTRL3 ((volatile uint32_t *)0xfe09e00c)
// Bit 31:0 -       0   - reserved
#define P_AUCPU_CPU_CTRL4 ((volatile uint32_t *)0xfe09e010)
// Bit 31:0 -       0   - reserved
#define P_AUCPU_CPU_CTRL5 ((volatile uint32_t *)0xfe09e014)
// Bit 31:0 -       0   - reserved
#define P_AUCPU_CPU_STS0 ((volatile uint32_t *)0xfe09e028)
// Bit 31:0 -       0   - n205_debug_sel==0 : n205_trace_casuse, 1:n205_trace_tval,
// 2:n205_trace_iaddr, 3:n205_trace_instr
#define P_AUCPU_CPU_STS1 ((volatile uint32_t *)0xfe09e02c)
// Bit 31   -       0   - n205_core_sleep_value
// Bit 30:29-       0   - n205_trace_priv
// Bit 28:20-       0   - reserved
// Bit 19   -       0   - n205_core_wfi_mode
// Bit 18   -       0   - n205_trace_ivalid
// Bit 17   -       0   - n205_trace_iexception
// Bit 16   -       0   - n205_trace_interrupt
// Bit 15:0 -       0   - reserved
#define P_AUCPU_CPU_STS2 ((volatile uint32_t *)0xfe09e030)
// Bit 31:0 -       0   - reserved
#define P_AUCPU_CPU_STS3 ((volatile uint32_t *)0xfe09e034)
// Bit 31   -       0   - n205_hart_halted
// Bit 30   -       0   - n205_ndmreset
// Bit 29   -       0   - n205_dmactive
// Bit 28:0 -       0   - reserved
#define P_AUCPU_DMA_APB_SEL ((volatile uint32_t *)0xfe09e040)
// Bit 31:30-       0   - reserved
// Bit 0    -       0   - 1: riscv control dma, 0: ap control dma
#define P_AUCPU_IRQ_AP2RISCV ((volatile uint32_t *)0xfe09e044)
// Bit 31:0 -       0   - AP cpu send irq to riscv
#define P_AUCPU_IRQ_RISCV2AP ((volatile uint32_t *)0xfe09e048)
// Bit 31:0 -       0   - riscv send irq to AP
#define P_AUCPU_STS00_BY_AP ((volatile uint32_t *)0xfe09e080)
// Bit 31:0 -       0   - reserved
#define P_AUCPU_STS01_BY_AP ((volatile uint32_t *)0xfe09e084)
// Bit 31:0 -       0   - reserved
#define P_AUCPU_STS02_BY_AP ((volatile uint32_t *)0xfe09e088)
// Bit 31:0 -       0   - reserved
#define P_AUCPU_STS03_BY_AP ((volatile uint32_t *)0xfe09e08c)
// Bit 31:0 -       0   - reserved
#define P_AUCPU_STS04_BY_AP ((volatile uint32_t *)0xfe09e090)
// Bit 31:0 -       0   - reserved
#define P_AUCPU_STS05_BY_AP ((volatile uint32_t *)0xfe09e094)
// Bit 31:0 -       0   - reserved
#define P_AUCPU_STS06_BY_AP ((volatile uint32_t *)0xfe09e098)
// Bit 31:0 -       0   - reserved
#define P_AUCPU_STS07_BY_AP ((volatile uint32_t *)0xfe09e09c)
// Bit 31:0 -       0   - reserved
#define P_AUCPU_STS08_BY_AP ((volatile uint32_t *)0xfe09e0a0)
// Bit 31:0 -       0   - reserved
#define P_AUCPU_STS09_BY_AP ((volatile uint32_t *)0xfe09e0a4)
// Bit 31:0 -       0   - reserved
#define P_AUCPU_STS10_BY_AP ((volatile uint32_t *)0xfe09e0a8)
// Bit 31:0 -       0   - reserved
#define P_AUCPU_STS11_BY_AP ((volatile uint32_t *)0xfe09e0ac)
// Bit 31:0 -       0   - reserved
#define P_AUCPU_STS12_BY_AP ((volatile uint32_t *)0xfe09e0b0)
// Bit 31:0 -       0   - reserved
#define P_AUCPU_STS13_BY_AP ((volatile uint32_t *)0xfe09e0b4)
// Bit 31:0 -       0   - reserved
#define P_AUCPU_STS14_BY_AP ((volatile uint32_t *)0xfe09e0b8)
// Bit 31:0 -       0   - reserved
#define P_AUCPU_STS15_BY_AP ((volatile uint32_t *)0xfe09e0bc)
// Bit 31:0 -       0   - reserved
#define P_AUCPU_STS16_BY_AP ((volatile uint32_t *)0xfe09e0c0)
// Bit 31:0 -       0   - reserved
#define P_AUCPU_STS17_BY_AP ((volatile uint32_t *)0xfe09e0c4)
// Bit 31:0 -       0   - reserved
#define P_AUCPU_STS18_BY_AP ((volatile uint32_t *)0xfe09e0c8)
// Bit 31:0 -       0   - reserved
#define P_AUCPU_STS19_BY_AP ((volatile uint32_t *)0xfe09e0cc)
// Bit 31:0 -       0   - reserved
#define P_AUCPU_STS20_BY_AP ((volatile uint32_t *)0xfe09e0d0)
// Bit 31:0 -       0   - reserved
#define P_AUCPU_STS21_BY_AP ((volatile uint32_t *)0xfe09e0d4)
// Bit 31:0 -       0   - reserved
#define P_AUCPU_STS22_BY_AP ((volatile uint32_t *)0xfe09e0d8)
// Bit 31:0 -       0   - reserved
#define P_AUCPU_STS23_BY_AP ((volatile uint32_t *)0xfe09e0dc)
// Bit 31:0 -       0   - reserved
#define P_AUCPU_STS24_BY_AP ((volatile uint32_t *)0xfe09e0e0)
// Bit 31:0 -       0   - reserved
#define P_AUCPU_STS25_BY_AP ((volatile uint32_t *)0xfe09e0e4)
// Bit 31:0 -       0   - reserved
#define P_AUCPU_STS26_BY_AP ((volatile uint32_t *)0xfe09e0e8)
// Bit 31:0 -       0   - reserved
#define P_AUCPU_STS27_BY_AP ((volatile uint32_t *)0xfe09e0ec)
// Bit 31:0 -       0   - reserved
#define P_AUCPU_STS28_BY_AP ((volatile uint32_t *)0xfe09e0f0)
// Bit 31:0 -       0   - reserved
#define P_AUCPU_STS29_BY_AP ((volatile uint32_t *)0xfe09e0f4)
// Bit 31:0 -       0   - reserved
#define P_AUCPU_STS30_BY_AP ((volatile uint32_t *)0xfe09e0f8)
// Bit 31:0 -       0   - reserved
#define P_AUCPU_STS31_BY_AP ((volatile uint32_t *)0xfe09e0fc)
// Bit 31:0 -       0   - reserved
#define P_AUCPU_STS00_BY_RISCV ((volatile uint32_t *)0xfe09e100)
// Bit 31:0 -       0   - reserved
#define P_AUCPU_STS01_BY_RISCV ((volatile uint32_t *)0xfe09e104)
// Bit 31:0 -       0   - reserved
#define P_AUCPU_STS02_BY_RISCV ((volatile uint32_t *)0xfe09e108)
// Bit 31:0 -       0   - reserved
#define P_AUCPU_STS03_BY_RISCV ((volatile uint32_t *)0xfe09e10c)
// Bit 31:0 -       0   - reserved
#define P_AUCPU_STS04_BY_RISCV ((volatile uint32_t *)0xfe09e110)
// Bit 31:0 -       0   - reserved
#define P_AUCPU_STS05_BY_RISCV ((volatile uint32_t *)0xfe09e114)
// Bit 31:0 -       0   - reserved
#define P_AUCPU_STS06_BY_RISCV ((volatile uint32_t *)0xfe09e118)
// Bit 31:0 -       0   - reserved
#define P_AUCPU_STS07_BY_RISCV ((volatile uint32_t *)0xfe09e11c)
// Bit 31:0 -       0   - reserved
#define P_AUCPU_STS08_BY_RISCV ((volatile uint32_t *)0xfe09e120)
// Bit 31:0 -       0   - reserved
#define P_AUCPU_STS09_BY_RISCV ((volatile uint32_t *)0xfe09e124)
// Bit 31:0 -       0   - reserved
#define P_AUCPU_STS10_BY_RISCV ((volatile uint32_t *)0xfe09e128)
// Bit 31:0 -       0   - reserved
#define P_AUCPU_STS11_BY_RISCV ((volatile uint32_t *)0xfe09e12c)
// Bit 31:0 -       0   - reserved
#define P_AUCPU_STS12_BY_RISCV ((volatile uint32_t *)0xfe09e130)
// Bit 31:0 -       0   - reserved
#define P_AUCPU_STS13_BY_RISCV ((volatile uint32_t *)0xfe09e134)
// Bit 31:0 -       0   - reserved
#define P_AUCPU_STS14_BY_RISCV ((volatile uint32_t *)0xfe09e138)
// Bit 31:0 -       0   - reserved
#define P_AUCPU_STS15_BY_RISCV ((volatile uint32_t *)0xfe09e13c)
// Bit 31:0 -       0   - reserved
#define P_AUCPU_STS16_BY_RISCV ((volatile uint32_t *)0xfe09e140)
// Bit 31:0 -       0   - reserved
#define P_AUCPU_STS17_BY_RISCV ((volatile uint32_t *)0xfe09e144)
// Bit 31:0 -       0   - reserved
#define P_AUCPU_STS18_BY_RISCV ((volatile uint32_t *)0xfe09e148)
// Bit 31:0 -       0   - reserved
#define P_AUCPU_STS19_BY_RISCV ((volatile uint32_t *)0xfe09e14c)
// Bit 31:0 -       0   - reserved
#define P_AUCPU_STS20_BY_RISCV ((volatile uint32_t *)0xfe09e150)
// Bit 31:0 -       0   - reserved
#define P_AUCPU_STS21_BY_RISCV ((volatile uint32_t *)0xfe09e154)
// Bit 31:0 -       0   - reserved
#define P_AUCPU_STS22_BY_RISCV ((volatile uint32_t *)0xfe09e158)
// Bit 31:0 -       0   - reserved
#define P_AUCPU_STS23_BY_RISCV ((volatile uint32_t *)0xfe09e15c)
// Bit 31:0 -       0   - reserved
#define P_AUCPU_STS24_BY_RISCV ((volatile uint32_t *)0xfe09e160)
// Bit 31:0 -       0   - reserved
#define P_AUCPU_STS25_BY_RISCV ((volatile uint32_t *)0xfe09e164)
// Bit 31:0 -       0   - reserved
#define P_AUCPU_STS26_BY_RISCV ((volatile uint32_t *)0xfe09e168)
// Bit 31:0 -       0   - reserved
#define P_AUCPU_STS27_BY_RISCV ((volatile uint32_t *)0xfe09e16c)
// Bit 31:0 -       0   - reserved
#define P_AUCPU_STS28_BY_RISCV ((volatile uint32_t *)0xfe09e170)
// Bit 31:0 -       0   - reserved
#define P_AUCPU_STS29_BY_RISCV ((volatile uint32_t *)0xfe09e174)
// Bit 31:0 -       0   - reserved
#define P_AUCPU_STS30_BY_RISCV ((volatile uint32_t *)0xfe09e178)
// Bit 31:0 -       0   - reserved
#define P_AUCPU_STS31_BY_RISCV ((volatile uint32_t *)0xfe09e17c)
// Bit 31:0 -       0   - reserved
#define P_AUCPU_DEMUX_STS_BY_RISCV ((volatile uint32_t *)0xfe09e180)
// Bit 31   -       0   - read only, demux status updated
// Bit 31:8 -       0   - reserved
// Bit  7:0 -       0   - read demux chn select
#define P_AUCPU_DEMUX_STS0 ((volatile uint32_t *)0xfe09e184)
// Bit 31:0 -       0   - demux status 0
#define P_AUCPU_DEMUX_STS1 ((volatile uint32_t *)0xfe09e188)
// Bit 31:0 -       0   - demux status 1
//========================================================================
//  AXI_SRAM
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe090000
// -----------------------------------------------
#define P_SRAM_RANGE0_STA ((volatile uint32_t *)0xfe090000)
#define P_SRAM_RANGE1_STA ((volatile uint32_t *)0xfe090004)
#define P_SRAM_RANGE2_STA ((volatile uint32_t *)0xfe090008)
#define P_SRAM_RANGE3_STA ((volatile uint32_t *)0xfe09000c)
#define P_SRAM_RANGE4_STA ((volatile uint32_t *)0xfe090010)
#define P_SRAM_RANGE5_STA ((volatile uint32_t *)0xfe090014)
#define P_SRAM_RANGE6_STA ((volatile uint32_t *)0xfe090018)
#define P_SRAM_RANGE7_STA ((volatile uint32_t *)0xfe09001c)
#define P_SRAM_RANGE8_STA ((volatile uint32_t *)0xfe090020)
#define P_SRAM_RANGE9_STA ((volatile uint32_t *)0xfe090024)
#define P_SRAM_RANGE10_STA ((volatile uint32_t *)0xfe090028)
#define P_SRAM_RANGE11_STA ((volatile uint32_t *)0xfe09002c)
#define P_SRAM_RANGE12_STA ((volatile uint32_t *)0xfe090030)
#define P_SRAM_RANGE13_STA ((volatile uint32_t *)0xfe090034)
#define P_SRAM_RANGE14_STA ((volatile uint32_t *)0xfe090038)
#define P_SRAM_RANGE0_EDA ((volatile uint32_t *)0xfe09003c)
#define P_SRAM_RANGE1_EDA ((volatile uint32_t *)0xfe090040)
#define P_SRAM_RANGE2_EDA ((volatile uint32_t *)0xfe090044)
#define P_SRAM_RANGE3_EDA ((volatile uint32_t *)0xfe090048)
#define P_SRAM_RANGE4_EDA ((volatile uint32_t *)0xfe09004c)
#define P_SRAM_RANGE5_EDA ((volatile uint32_t *)0xfe090050)
#define P_SRAM_RANGE6_EDA ((volatile uint32_t *)0xfe090054)
#define P_SRAM_RANGE7_EDA ((volatile uint32_t *)0xfe090058)
#define P_SRAM_RANGE8_EDA ((volatile uint32_t *)0xfe09005c)
#define P_SRAM_RANGE9_EDA ((volatile uint32_t *)0xfe090060)
#define P_SRAM_RANGE10_EDA ((volatile uint32_t *)0xfe090064)
#define P_SRAM_RANGE11_EDA ((volatile uint32_t *)0xfe090068)
#define P_SRAM_RANGE12_EDA ((volatile uint32_t *)0xfe09006c)
#define P_SRAM_RANGE13_EDA ((volatile uint32_t *)0xfe090070)
#define P_SRAM_RANGE14_EDA ((volatile uint32_t *)0xfe090074)
#define P_SRAM_RANGE0_READ_CTRL0 ((volatile uint32_t *)0xfe090078)
#define P_SRAM_RANGE1_READ_CTRL0 ((volatile uint32_t *)0xfe09007c)
#define P_SRAM_RANGE2_READ_CTRL0 ((volatile uint32_t *)0xfe090080)
#define P_SRAM_RANGE3_READ_CTRL0 ((volatile uint32_t *)0xfe090084)
#define P_SRAM_RANGE4_READ_CTRL0 ((volatile uint32_t *)0xfe090088)
#define P_SRAM_RANGE5_READ_CTRL0 ((volatile uint32_t *)0xfe09008c)
#define P_SRAM_RANGE6_READ_CTRL0 ((volatile uint32_t *)0xfe090090)
#define P_SRAM_RANGE7_READ_CTRL0 ((volatile uint32_t *)0xfe090094)
#define P_SRAM_RANGE8_READ_CTRL0 ((volatile uint32_t *)0xfe090098)
#define P_SRAM_RANGE9_READ_CTRL0 ((volatile uint32_t *)0xfe09009c)
#define P_SRAM_RANGE10_READ_CTRL0 ((volatile uint32_t *)0xfe0900a0)
#define P_SRAM_RANGE11_READ_CTRL0 ((volatile uint32_t *)0xfe0900a4)
#define P_SRAM_RANGE12_READ_CTRL0 ((volatile uint32_t *)0xfe0900a8)
#define P_SRAM_RANGE13_READ_CTRL0 ((volatile uint32_t *)0xfe0900ac)
#define P_SRAM_RANGE14_READ_CTRL0 ((volatile uint32_t *)0xfe0900b0)
#define P_SRAM_RANGE15_READ_CTRL0 ((volatile uint32_t *)0xfe0900b4)
#define P_SRAM_RANGE0_WRITE_CTRL0 ((volatile uint32_t *)0xfe0900b8)
#define P_SRAM_RANGE1_WRITE_CTRL0 ((volatile uint32_t *)0xfe0900bc)
#define P_SRAM_RANGE2_WRITE_CTRL0 ((volatile uint32_t *)0xfe0900c0)
#define P_SRAM_RANGE3_WRITE_CTRL0 ((volatile uint32_t *)0xfe0900c4)
#define P_SRAM_RANGE4_WRITE_CTRL0 ((volatile uint32_t *)0xfe0900c8)
#define P_SRAM_RANGE5_WRITE_CTRL0 ((volatile uint32_t *)0xfe0900cc)
#define P_SRAM_RANGE6_WRITE_CTRL0 ((volatile uint32_t *)0xfe0900d0)
#define P_SRAM_RANGE7_WRITE_CTRL0 ((volatile uint32_t *)0xfe0900d4)
#define P_SRAM_RANGE8_WRITE_CTRL0 ((volatile uint32_t *)0xfe0900d8)
#define P_SRAM_RANGE9_WRITE_CTRL0 ((volatile uint32_t *)0xfe0900dc)
#define P_SRAM_RANGE10_WRITE_CTRL0 ((volatile uint32_t *)0xfe0900e0)
#define P_SRAM_RANGE11_WRITE_CTRL0 ((volatile uint32_t *)0xfe0900e4)
#define P_SRAM_RANGE12_WRITE_CTRL0 ((volatile uint32_t *)0xfe0900e8)
#define P_SRAM_RANGE13_WRITE_CTRL0 ((volatile uint32_t *)0xfe0900ec)
#define P_SRAM_RANGE14_WRITE_CTRL0 ((volatile uint32_t *)0xfe0900f0)
#define P_SRAM_RANGE15_WRITE_CTRL0 ((volatile uint32_t *)0xfe0900f4)
#define P_SRAM_RANGE0_READ_CTRL1 ((volatile uint32_t *)0xfe0900f8)
#define P_SRAM_RANGE1_READ_CTRL1 ((volatile uint32_t *)0xfe0900fc)
#define P_SRAM_RANGE2_READ_CTRL1 ((volatile uint32_t *)0xfe090100)
#define P_SRAM_RANGE3_READ_CTRL1 ((volatile uint32_t *)0xfe090104)
#define P_SRAM_RANGE4_READ_CTRL1 ((volatile uint32_t *)0xfe090108)
#define P_SRAM_RANGE5_READ_CTRL1 ((volatile uint32_t *)0xfe09010c)
#define P_SRAM_RANGE6_READ_CTRL1 ((volatile uint32_t *)0xfe090110)
#define P_SRAM_RANGE7_READ_CTRL1 ((volatile uint32_t *)0xfe090114)
#define P_SRAM_RANGE8_READ_CTRL1 ((volatile uint32_t *)0xfe090118)
#define P_SRAM_RANGE9_READ_CTRL1 ((volatile uint32_t *)0xfe09011c)
#define P_SRAM_RANGE10_READ_CTRL1 ((volatile uint32_t *)0xfe090120)
#define P_SRAM_RANGE11_READ_CTRL1 ((volatile uint32_t *)0xfe090124)
#define P_SRAM_RANGE12_READ_CTRL1 ((volatile uint32_t *)0xfe090128)
#define P_SRAM_RANGE13_READ_CTRL1 ((volatile uint32_t *)0xfe09012c)
#define P_SRAM_RANGE14_READ_CTRL1 ((volatile uint32_t *)0xfe090130)
#define P_SRAM_RANGE15_READ_CTRL1 ((volatile uint32_t *)0xfe090134)
#define P_SRAM_RANGE0_WRITE_CTRL1 ((volatile uint32_t *)0xfe090138)
#define P_SRAM_RANGE1_WRITE_CTRL1 ((volatile uint32_t *)0xfe09013c)
#define P_SRAM_RANGE2_WRITE_CTRL1 ((volatile uint32_t *)0xfe090140)
#define P_SRAM_RANGE3_WRITE_CTRL1 ((volatile uint32_t *)0xfe090144)
#define P_SRAM_RANGE4_WRITE_CTRL1 ((volatile uint32_t *)0xfe090148)
#define P_SRAM_RANGE5_WRITE_CTRL1 ((volatile uint32_t *)0xfe09014c)
#define P_SRAM_RANGE6_WRITE_CTRL1 ((volatile uint32_t *)0xfe090150)
#define P_SRAM_RANGE7_WRITE_CTRL1 ((volatile uint32_t *)0xfe090154)
#define P_SRAM_RANGE8_WRITE_CTRL1 ((volatile uint32_t *)0xfe090158)
#define P_SRAM_RANGE9_WRITE_CTRL1 ((volatile uint32_t *)0xfe09015c)
#define P_SRAM_RANGE10_WRITE_CTRL1 ((volatile uint32_t *)0xfe090160)
#define P_SRAM_RANGE11_WRITE_CTRL1 ((volatile uint32_t *)0xfe090164)
#define P_SRAM_RANGE12_WRITE_CTRL1 ((volatile uint32_t *)0xfe090168)
#define P_SRAM_RANGE13_WRITE_CTRL1 ((volatile uint32_t *)0xfe09016c)
#define P_SRAM_RANGE14_WRITE_CTRL1 ((volatile uint32_t *)0xfe090170)
#define P_SRAM_RANGE15_WRITE_CTRL1 ((volatile uint32_t *)0xfe090174)
#define P_SRAM_GLOBAL_READ_CTRL0 ((volatile uint32_t *)0xfe090178)
#define P_SRAM_GLOBAL_READ_CTRL1 ((volatile uint32_t *)0xfe09017c)
#define P_SRAM_GLOBAL_WRITE_CTRL0 ((volatile uint32_t *)0xfe090180)
#define P_SRAM_GLOBAL_WRITE_CTRL1 ((volatile uint32_t *)0xfe090184)
#define P_SRAM_SEC_CTRL0 ((volatile uint32_t *)0xfe090188)
#define P_SRAM_REG_LOCK0 ((volatile uint32_t *)0xfe09018c)
#define P_SRAM_REG_LOCK1 ((volatile uint32_t *)0xfe090190)
#define P_SRAM_REG_LOCK2 ((volatile uint32_t *)0xfe090194)
#define P_SRAM_GLOBAL_READ_CTRL0_LOCK ((volatile uint32_t *)0xfe090198)
#define P_SRAM_GLOBAL_READ_CTRL1_LOCK ((volatile uint32_t *)0xfe09019c)
#define P_SRAM_GLOBAL_WRITE_CTRL0_LOCK ((volatile uint32_t *)0xfe0901a0)
#define P_SRAM_GLOBAL_WRITE_CTRL1_LOCK ((volatile uint32_t *)0xfe0901a4)
#define P_SRAM_SEC_CTRL0_LOCK ((volatile uint32_t *)0xfe0901a8)
#define P_SRAM_STATUS_REG ((volatile uint32_t *)0xfe0901ac)
#define P_SRAM_INIT_DLY_TCNT ((volatile uint32_t *)0xfe0901b0)
//========================================================================
//  AXI_SRAM B
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe092000
// -----------------------------------------------
#define P_SRAM_B_RANGE0_STA ((volatile uint32_t *)0xfe092000)
#define P_SRAM_B_RANGE1_STA ((volatile uint32_t *)0xfe092004)
#define P_SRAM_B_RANGE2_STA ((volatile uint32_t *)0xfe092008)
#define P_SRAM_B_RANGE3_STA ((volatile uint32_t *)0xfe09200c)
#define P_SRAM_B_RANGE4_STA ((volatile uint32_t *)0xfe092010)
#define P_SRAM_B_RANGE5_STA ((volatile uint32_t *)0xfe092014)
#define P_SRAM_B_RANGE6_STA ((volatile uint32_t *)0xfe092018)
#define P_SRAM_B_RANGE7_STA ((volatile uint32_t *)0xfe09201c)
#define P_SRAM_B_RANGE8_STA ((volatile uint32_t *)0xfe092020)
#define P_SRAM_B_RANGE9_STA ((volatile uint32_t *)0xfe092024)
#define P_SRAM_B_RANGE10_STA ((volatile uint32_t *)0xfe092028)
#define P_SRAM_B_RANGE11_STA ((volatile uint32_t *)0xfe09202c)
#define P_SRAM_B_RANGE12_STA ((volatile uint32_t *)0xfe092030)
#define P_SRAM_B_RANGE13_STA ((volatile uint32_t *)0xfe092034)
#define P_SRAM_B_RANGE14_STA ((volatile uint32_t *)0xfe092038)
#define P_SRAM_B_RANGE0_EDA ((volatile uint32_t *)0xfe09203c)
#define P_SRAM_B_RANGE1_EDA ((volatile uint32_t *)0xfe092040)
#define P_SRAM_B_RANGE2_EDA ((volatile uint32_t *)0xfe092044)
#define P_SRAM_B_RANGE3_EDA ((volatile uint32_t *)0xfe092048)
#define P_SRAM_B_RANGE4_EDA ((volatile uint32_t *)0xfe09204c)
#define P_SRAM_B_RANGE5_EDA ((volatile uint32_t *)0xfe092050)
#define P_SRAM_B_RANGE6_EDA ((volatile uint32_t *)0xfe092054)
#define P_SRAM_B_RANGE7_EDA ((volatile uint32_t *)0xfe092058)
#define P_SRAM_B_RANGE8_EDA ((volatile uint32_t *)0xfe09205c)
#define P_SRAM_B_RANGE9_EDA ((volatile uint32_t *)0xfe092060)
#define P_SRAM_B_RANGE10_EDA ((volatile uint32_t *)0xfe092064)
#define P_SRAM_B_RANGE11_EDA ((volatile uint32_t *)0xfe092068)
#define P_SRAM_B_RANGE12_EDA ((volatile uint32_t *)0xfe09206c)
#define P_SRAM_B_RANGE13_EDA ((volatile uint32_t *)0xfe092070)
#define P_SRAM_B_RANGE14_EDA ((volatile uint32_t *)0xfe092074)
#define P_SRAM_B_RANGE0_READ_CTRL0 ((volatile uint32_t *)0xfe092078)
#define P_SRAM_B_RANGE1_READ_CTRL0 ((volatile uint32_t *)0xfe09207c)
#define P_SRAM_B_RANGE2_READ_CTRL0 ((volatile uint32_t *)0xfe092080)
#define P_SRAM_B_RANGE3_READ_CTRL0 ((volatile uint32_t *)0xfe092084)
#define P_SRAM_B_RANGE4_READ_CTRL0 ((volatile uint32_t *)0xfe092088)
#define P_SRAM_B_RANGE5_READ_CTRL0 ((volatile uint32_t *)0xfe09208c)
#define P_SRAM_B_RANGE6_READ_CTRL0 ((volatile uint32_t *)0xfe092090)
#define P_SRAM_B_RANGE7_READ_CTRL0 ((volatile uint32_t *)0xfe092094)
#define P_SRAM_B_RANGE8_READ_CTRL0 ((volatile uint32_t *)0xfe092098)
#define P_SRAM_B_RANGE9_READ_CTRL0 ((volatile uint32_t *)0xfe09209c)
#define P_SRAM_B_RANGE10_READ_CTRL0 ((volatile uint32_t *)0xfe0920a0)
#define P_SRAM_B_RANGE11_READ_CTRL0 ((volatile uint32_t *)0xfe0920a4)
#define P_SRAM_B_RANGE12_READ_CTRL0 ((volatile uint32_t *)0xfe0920a8)
#define P_SRAM_B_RANGE13_READ_CTRL0 ((volatile uint32_t *)0xfe0920ac)
#define P_SRAM_B_RANGE14_READ_CTRL0 ((volatile uint32_t *)0xfe0920b0)
#define P_SRAM_B_RANGE15_READ_CTRL0 ((volatile uint32_t *)0xfe0920b4)
#define P_SRAM_B_RANGE0_WRITE_CTRL0 ((volatile uint32_t *)0xfe0920b8)
#define P_SRAM_B_RANGE1_WRITE_CTRL0 ((volatile uint32_t *)0xfe0920bc)
#define P_SRAM_B_RANGE2_WRITE_CTRL0 ((volatile uint32_t *)0xfe0920c0)
#define P_SRAM_B_RANGE3_WRITE_CTRL0 ((volatile uint32_t *)0xfe0920c4)
#define P_SRAM_B_RANGE4_WRITE_CTRL0 ((volatile uint32_t *)0xfe0920c8)
#define P_SRAM_B_RANGE5_WRITE_CTRL0 ((volatile uint32_t *)0xfe0920cc)
#define P_SRAM_B_RANGE6_WRITE_CTRL0 ((volatile uint32_t *)0xfe0920d0)
#define P_SRAM_B_RANGE7_WRITE_CTRL0 ((volatile uint32_t *)0xfe0920d4)
#define P_SRAM_B_RANGE8_WRITE_CTRL0 ((volatile uint32_t *)0xfe0920d8)
#define P_SRAM_B_RANGE9_WRITE_CTRL0 ((volatile uint32_t *)0xfe0920dc)
#define P_SRAM_B_RANGE10_WRITE_CTRL0 ((volatile uint32_t *)0xfe0920e0)
#define P_SRAM_B_RANGE11_WRITE_CTRL0 ((volatile uint32_t *)0xfe0920e4)
#define P_SRAM_B_RANGE12_WRITE_CTRL0 ((volatile uint32_t *)0xfe0920e8)
#define P_SRAM_B_RANGE13_WRITE_CTRL0 ((volatile uint32_t *)0xfe0920ec)
#define P_SRAM_B_RANGE14_WRITE_CTRL0 ((volatile uint32_t *)0xfe0920f0)
#define P_SRAM_B_RANGE15_WRITE_CTRL0 ((volatile uint32_t *)0xfe0920f4)
#define P_SRAM_B_RANGE0_READ_CTRL1 ((volatile uint32_t *)0xfe0920f8)
#define P_SRAM_B_RANGE1_READ_CTRL1 ((volatile uint32_t *)0xfe0920fc)
#define P_SRAM_B_RANGE2_READ_CTRL1 ((volatile uint32_t *)0xfe092100)
#define P_SRAM_B_RANGE3_READ_CTRL1 ((volatile uint32_t *)0xfe092104)
#define P_SRAM_B_RANGE4_READ_CTRL1 ((volatile uint32_t *)0xfe092108)
#define P_SRAM_B_RANGE5_READ_CTRL1 ((volatile uint32_t *)0xfe09210c)
#define P_SRAM_B_RANGE6_READ_CTRL1 ((volatile uint32_t *)0xfe092110)
#define P_SRAM_B_RANGE7_READ_CTRL1 ((volatile uint32_t *)0xfe092114)
#define P_SRAM_B_RANGE8_READ_CTRL1 ((volatile uint32_t *)0xfe092118)
#define P_SRAM_B_RANGE9_READ_CTRL1 ((volatile uint32_t *)0xfe09211c)
#define P_SRAM_B_RANGE10_READ_CTRL1 ((volatile uint32_t *)0xfe092120)
#define P_SRAM_B_RANGE11_READ_CTRL1 ((volatile uint32_t *)0xfe092124)
#define P_SRAM_B_RANGE12_READ_CTRL1 ((volatile uint32_t *)0xfe092128)
#define P_SRAM_B_RANGE13_READ_CTRL1 ((volatile uint32_t *)0xfe09212c)
#define P_SRAM_B_RANGE14_READ_CTRL1 ((volatile uint32_t *)0xfe092130)
#define P_SRAM_B_RANGE15_READ_CTRL1 ((volatile uint32_t *)0xfe092134)
#define P_SRAM_B_RANGE0_WRITE_CTRL1 ((volatile uint32_t *)0xfe092138)
#define P_SRAM_B_RANGE1_WRITE_CTRL1 ((volatile uint32_t *)0xfe09213c)
#define P_SRAM_B_RANGE2_WRITE_CTRL1 ((volatile uint32_t *)0xfe092140)
#define P_SRAM_B_RANGE3_WRITE_CTRL1 ((volatile uint32_t *)0xfe092144)
#define P_SRAM_B_RANGE4_WRITE_CTRL1 ((volatile uint32_t *)0xfe092148)
#define P_SRAM_B_RANGE5_WRITE_CTRL1 ((volatile uint32_t *)0xfe09214c)
#define P_SRAM_B_RANGE6_WRITE_CTRL1 ((volatile uint32_t *)0xfe092150)
#define P_SRAM_B_RANGE7_WRITE_CTRL1 ((volatile uint32_t *)0xfe092154)
#define P_SRAM_B_RANGE8_WRITE_CTRL1 ((volatile uint32_t *)0xfe092158)
#define P_SRAM_B_RANGE9_WRITE_CTRL1 ((volatile uint32_t *)0xfe09215c)
#define P_SRAM_B_RANGE10_WRITE_CTRL1 ((volatile uint32_t *)0xfe092160)
#define P_SRAM_B_RANGE11_WRITE_CTRL1 ((volatile uint32_t *)0xfe092164)
#define P_SRAM_B_RANGE12_WRITE_CTRL1 ((volatile uint32_t *)0xfe092168)
#define P_SRAM_B_RANGE13_WRITE_CTRL1 ((volatile uint32_t *)0xfe09216c)
#define P_SRAM_B_RANGE14_WRITE_CTRL1 ((volatile uint32_t *)0xfe092170)
#define P_SRAM_B_RANGE15_WRITE_CTRL1 ((volatile uint32_t *)0xfe092174)
#define P_SRAM_B_GLOBAL_READ_CTRL0 ((volatile uint32_t *)0xfe092178)
#define P_SRAM_B_GLOBAL_READ_CTRL1 ((volatile uint32_t *)0xfe09217c)
#define P_SRAM_B_GLOBAL_WRITE_CTRL0 ((volatile uint32_t *)0xfe092180)
#define P_SRAM_B_GLOBAL_WRITE_CTRL1 ((volatile uint32_t *)0xfe092184)
#define P_SRAM_B_SEC_CTRL0 ((volatile uint32_t *)0xfe092188)
#define P_SRAM_B_REG_LOCK0 ((volatile uint32_t *)0xfe09218c)
#define P_SRAM_B_REG_LOCK1 ((volatile uint32_t *)0xfe092190)
#define P_SRAM_B_REG_LOCK2 ((volatile uint32_t *)0xfe092194)
#define P_SRAM_B_GLOBAL_READ_CTRL0_LOCK ((volatile uint32_t *)0xfe092198)
#define P_SRAM_B_GLOBAL_READ_CTRL1_LOCK ((volatile uint32_t *)0xfe09219c)
#define P_SRAM_B_GLOBAL_WRITE_CTRL0_LOCK ((volatile uint32_t *)0xfe0921a0)
#define P_SRAM_B_GLOBAL_WRITE_CTRL1_LOCK ((volatile uint32_t *)0xfe0921a4)
#define P_SRAM_B_SEC_CTRL0_LOCK ((volatile uint32_t *)0xfe0921a8)
#define P_SRAM_B_STATUS_REG ((volatile uint32_t *)0xfe0921ac)
#define P_SRAM_B_INIT_DLY_TCNT ((volatile uint32_t *)0xfe0921b0)
//========================================================================
//  MAILBOX
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe006000
// -----------------------------------------------
#define P_MAILBOX_WR_MBOX00 ((volatile uint32_t *)0xfe006000)
#define P_MAILBOX_WR_MBOX01 ((volatile uint32_t *)0xfe006080)
#define P_MAILBOX_WR_MBOX02 ((volatile uint32_t *)0xfe006100)
#define P_MAILBOX_WR_MBOX03 ((volatile uint32_t *)0xfe006180)
#define P_MAILBOX_WR_MBOX04 ((volatile uint32_t *)0xfe006200)
#define P_MAILBOX_WR_MBOX05 ((volatile uint32_t *)0xfe006280)
#define P_MAILBOX_WR_MBOX06 ((volatile uint32_t *)0xfe006300)
#define P_MAILBOX_WR_MBOX07 ((volatile uint32_t *)0xfe006380)
#define P_MAILBOX_WR_MBOX08 ((volatile uint32_t *)0xfe006400)
#define P_MAILBOX_WR_MBOX09 ((volatile uint32_t *)0xfe006480)
#define P_MAILBOX_WR_MBOX10 ((volatile uint32_t *)0xfe006500)
#define P_MAILBOX_WR_MBOX11 ((volatile uint32_t *)0xfe006580)
#define P_MAILBOX_WR_MBOX12 ((volatile uint32_t *)0xfe006600)
#define P_MAILBOX_WR_MBOX13 ((volatile uint32_t *)0xfe006680)
#define P_MAILBOX_WR_MBOX14 ((volatile uint32_t *)0xfe006700)
#define P_MAILBOX_WR_MBOX15 ((volatile uint32_t *)0xfe006780)
#define P_MAILBOX_RD_MBOX00 ((volatile uint32_t *)0xfe006800)
#define P_MAILBOX_RD_MBOX01 ((volatile uint32_t *)0xfe006880)
#define P_MAILBOX_RD_MBOX02 ((volatile uint32_t *)0xfe006900)
#define P_MAILBOX_RD_MBOX03 ((volatile uint32_t *)0xfe006980)
#define P_MAILBOX_RD_MBOX04 ((volatile uint32_t *)0xfe006a00)
#define P_MAILBOX_RD_MBOX05 ((volatile uint32_t *)0xfe006a80)
#define P_MAILBOX_RD_MBOX06 ((volatile uint32_t *)0xfe006b00)
#define P_MAILBOX_RD_MBOX07 ((volatile uint32_t *)0xfe006b80)
#define P_MAILBOX_RD_MBOX08 ((volatile uint32_t *)0xfe006c00)
#define P_MAILBOX_RD_MBOX09 ((volatile uint32_t *)0xfe006c80)
#define P_MAILBOX_RD_MBOX10 ((volatile uint32_t *)0xfe006d00)
#define P_MAILBOX_RD_MBOX11 ((volatile uint32_t *)0xfe006d80)
#define P_MAILBOX_RD_MBOX12 ((volatile uint32_t *)0xfe006e00)
#define P_MAILBOX_RD_MBOX13 ((volatile uint32_t *)0xfe006e80)
#define P_MAILBOX_RD_MBOX14 ((volatile uint32_t *)0xfe006f00)
#define P_MAILBOX_RD_MBOX15 ((volatile uint32_t *)0xfe006f80)
#define P_MAILBOX_LOCK_BIT0 ((volatile uint32_t *)0xfe007000)
#define P_MAILBOX_LOCK_BIT1 ((volatile uint32_t *)0xfe007004)
#define P_MAILBOX_PROT_BIT0 ((volatile uint32_t *)0xfe007008)
#define P_MAILBOX_PROT_BIT1 ((volatile uint32_t *)0xfe00700c)
#define P_MAILBOX_ACCESS_EN_IRQA_CLR ((volatile uint32_t *)0xfe007010)
#define P_MAILBOX_ACCESS_EN_IRQB_CLR ((volatile uint32_t *)0xfe007014)
#define P_MAILBOX_ACCESS_EN_IRQC_CLR ((volatile uint32_t *)0xfe007018)
#define P_MAILBOX_ACCESS_EN_IRQD_CLR ((volatile uint32_t *)0xfe00701c)
#define P_MAILBOX_IRQA_MASK ((volatile uint32_t *)0xfe007020)
#define P_MAILBOX_IRQB_MASK ((volatile uint32_t *)0xfe007024)
#define P_MAILBOX_IRQC_MASK ((volatile uint32_t *)0xfe007028)
#define P_MAILBOX_IRQD_MASK ((volatile uint32_t *)0xfe00702c)
#define P_MAILBOX_IRQ_TYPE ((volatile uint32_t *)0xfe007030)
#define P_MAILBOX_IRQA_CLR ((volatile uint32_t *)0xfe007040)
#define P_MAILBOX_IRQB_CLR ((volatile uint32_t *)0xfe007044)
#define P_MAILBOX_IRQC_CLR ((volatile uint32_t *)0xfe007048)
#define P_MAILBOX_IRQD_CLR ((volatile uint32_t *)0xfe00704c)
#define P_MAILBOX_IRQA_STS ((volatile uint32_t *)0xfe007050)
#define P_MAILBOX_IRQB_STS ((volatile uint32_t *)0xfe007054)
#define P_MAILBOX_IRQC_STS ((volatile uint32_t *)0xfe007058)
#define P_MAILBOX_IRQD_STS ((volatile uint32_t *)0xfe00705c)
#define P_MAILBOX_ACCESS_EN_MBOX00 ((volatile uint32_t *)0xfe007080)
#define P_MAILBOX_ACCESS_EN_MBOX01 ((volatile uint32_t *)0xfe007084)
#define P_MAILBOX_ACCESS_EN_MBOX02 ((volatile uint32_t *)0xfe007088)
#define P_MAILBOX_ACCESS_EN_MBOX03 ((volatile uint32_t *)0xfe00708c)
#define P_MAILBOX_ACCESS_EN_MBOX04 ((volatile uint32_t *)0xfe007090)
#define P_MAILBOX_ACCESS_EN_MBOX05 ((volatile uint32_t *)0xfe007094)
#define P_MAILBOX_ACCESS_EN_MBOX06 ((volatile uint32_t *)0xfe007098)
#define P_MAILBOX_ACCESS_EN_MBOX07 ((volatile uint32_t *)0xfe00709c)
#define P_MAILBOX_ACCESS_EN_MBOX08 ((volatile uint32_t *)0xfe0070a0)
#define P_MAILBOX_ACCESS_EN_MBOX09 ((volatile uint32_t *)0xfe0070a4)
#define P_MAILBOX_ACCESS_EN_MBOX10 ((volatile uint32_t *)0xfe0070a8)
#define P_MAILBOX_ACCESS_EN_MBOX11 ((volatile uint32_t *)0xfe0070ac)
#define P_MAILBOX_ACCESS_EN_MBOX12 ((volatile uint32_t *)0xfe0070b0)
#define P_MAILBOX_ACCESS_EN_MBOX13 ((volatile uint32_t *)0xfe0070b4)
#define P_MAILBOX_ACCESS_EN_MBOX14 ((volatile uint32_t *)0xfe0070b8)
#define P_MAILBOX_ACCESS_EN_MBOX15 ((volatile uint32_t *)0xfe0070bc)
#define P_MAILBOX_SET_MBOX00 ((volatile uint32_t *)0xfe0070c0)
#define P_MAILBOX_SET_MBOX01 ((volatile uint32_t *)0xfe0070c4)
#define P_MAILBOX_SET_MBOX02 ((volatile uint32_t *)0xfe0070c8)
#define P_MAILBOX_SET_MBOX03 ((volatile uint32_t *)0xfe0070cc)
#define P_MAILBOX_SET_MBOX04 ((volatile uint32_t *)0xfe0070d0)
#define P_MAILBOX_SET_MBOX05 ((volatile uint32_t *)0xfe0070d4)
#define P_MAILBOX_SET_MBOX06 ((volatile uint32_t *)0xfe0070d8)
#define P_MAILBOX_SET_MBOX07 ((volatile uint32_t *)0xfe0070dc)
#define P_MAILBOX_SET_MBOX08 ((volatile uint32_t *)0xfe0070e0)
#define P_MAILBOX_SET_MBOX09 ((volatile uint32_t *)0xfe0070e4)
#define P_MAILBOX_SET_MBOX10 ((volatile uint32_t *)0xfe0070e8)
#define P_MAILBOX_SET_MBOX11 ((volatile uint32_t *)0xfe0070ec)
#define P_MAILBOX_SET_MBOX12 ((volatile uint32_t *)0xfe0070f0)
#define P_MAILBOX_SET_MBOX13 ((volatile uint32_t *)0xfe0070f4)
#define P_MAILBOX_SET_MBOX14 ((volatile uint32_t *)0xfe0070f8)
#define P_MAILBOX_SET_MBOX15 ((volatile uint32_t *)0xfe0070fc)
#define P_MAILBOX_CLR_MBOX00 ((volatile uint32_t *)0xfe007100)
#define P_MAILBOX_CLR_MBOX01 ((volatile uint32_t *)0xfe007104)
#define P_MAILBOX_CLR_MBOX02 ((volatile uint32_t *)0xfe007108)
#define P_MAILBOX_CLR_MBOX03 ((volatile uint32_t *)0xfe00710c)
#define P_MAILBOX_CLR_MBOX04 ((volatile uint32_t *)0xfe007110)
#define P_MAILBOX_CLR_MBOX05 ((volatile uint32_t *)0xfe007114)
#define P_MAILBOX_CLR_MBOX06 ((volatile uint32_t *)0xfe007118)
#define P_MAILBOX_CLR_MBOX07 ((volatile uint32_t *)0xfe00711c)
#define P_MAILBOX_CLR_MBOX08 ((volatile uint32_t *)0xfe007120)
#define P_MAILBOX_CLR_MBOX09 ((volatile uint32_t *)0xfe007124)
#define P_MAILBOX_CLR_MBOX10 ((volatile uint32_t *)0xfe007128)
#define P_MAILBOX_CLR_MBOX11 ((volatile uint32_t *)0xfe00712c)
#define P_MAILBOX_CLR_MBOX12 ((volatile uint32_t *)0xfe007130)
#define P_MAILBOX_CLR_MBOX13 ((volatile uint32_t *)0xfe007134)
#define P_MAILBOX_CLR_MBOX14 ((volatile uint32_t *)0xfe007138)
#define P_MAILBOX_CLR_MBOX15 ((volatile uint32_t *)0xfe00713c)
#define P_MAILBOX_STS_MBOX00 ((volatile uint32_t *)0xfe007140)
#define P_MAILBOX_STS_MBOX01 ((volatile uint32_t *)0xfe007144)
#define P_MAILBOX_STS_MBOX02 ((volatile uint32_t *)0xfe007148)
#define P_MAILBOX_STS_MBOX03 ((volatile uint32_t *)0xfe00714c)
#define P_MAILBOX_STS_MBOX04 ((volatile uint32_t *)0xfe007150)
#define P_MAILBOX_STS_MBOX05 ((volatile uint32_t *)0xfe007154)
#define P_MAILBOX_STS_MBOX06 ((volatile uint32_t *)0xfe007158)
#define P_MAILBOX_STS_MBOX07 ((volatile uint32_t *)0xfe00715c)
#define P_MAILBOX_STS_MBOX08 ((volatile uint32_t *)0xfe007160)
#define P_MAILBOX_STS_MBOX09 ((volatile uint32_t *)0xfe007164)
#define P_MAILBOX_STS_MBOX10 ((volatile uint32_t *)0xfe007168)
#define P_MAILBOX_STS_MBOX11 ((volatile uint32_t *)0xfe00716c)
#define P_MAILBOX_STS_MBOX12 ((volatile uint32_t *)0xfe007170)
#define P_MAILBOX_STS_MBOX13 ((volatile uint32_t *)0xfe007174)
#define P_MAILBOX_STS_MBOX14 ((volatile uint32_t *)0xfe007178)
#define P_MAILBOX_STS_MBOX15 ((volatile uint32_t *)0xfe00717c)
//========================================================================
//  IRQ_CTRL
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe00a000
// -----------------------------------------------
#define P_IRQCTRL_IRQ_INV0 ((volatile uint32_t *)0xfe00a000)
#define P_IRQCTRL_IRQ_INV1 ((volatile uint32_t *)0xfe00a004)
#define P_IRQCTRL_IRQ_INV2 ((volatile uint32_t *)0xfe00a008)
#define P_IRQCTRL_IRQ_INV3 ((volatile uint32_t *)0xfe00a00c)
#define P_IRQCTRL_IRQ_INV4 ((volatile uint32_t *)0xfe00a010)
#define P_IRQCTRL_IRQ_INV5 ((volatile uint32_t *)0xfe00a014)
#define P_IRQCTRL_IRQ_INV6 ((volatile uint32_t *)0xfe00a018)
#define P_IRQCTRL_IRQ_INV7 ((volatile uint32_t *)0xfe00a01c)
#define P_IRQCTRL_MASK0_GIC ((volatile uint32_t *)0xfe00a040)
#define P_IRQCTRL_MASK1_GIC ((volatile uint32_t *)0xfe00a044)
#define P_IRQCTRL_MASK2_GIC ((volatile uint32_t *)0xfe00a048)
#define P_IRQCTRL_MASK3_GIC ((volatile uint32_t *)0xfe00a04c)
#define P_IRQCTRL_MASK4_GIC ((volatile uint32_t *)0xfe00a050)
#define P_IRQCTRL_MASK5_GIC ((volatile uint32_t *)0xfe00a054)
#define P_IRQCTRL_MASK6_GIC ((volatile uint32_t *)0xfe00a058)
#define P_IRQCTRL_MASK7_GIC ((volatile uint32_t *)0xfe00a05c)
#define P_IRQCTRL_MASK0_DSP ((volatile uint32_t *)0xfe00a080)
#define P_IRQCTRL_MASK1_DSP ((volatile uint32_t *)0xfe00a084)
#define P_IRQCTRL_MASK2_DSP ((volatile uint32_t *)0xfe00a088)
#define P_IRQCTRL_MASK3_DSP ((volatile uint32_t *)0xfe00a08c)
#define P_IRQCTRL_MASK4_DSP ((volatile uint32_t *)0xfe00a090)
#define P_IRQCTRL_MASK5_DSP ((volatile uint32_t *)0xfe00a094)
#define P_IRQCTRL_MASK6_DSP ((volatile uint32_t *)0xfe00a098)
#define P_IRQCTRL_MASK7_DSP ((volatile uint32_t *)0xfe00a09c)
#define P_IRQCTRL_MASK0_PWRCTRL ((volatile uint32_t *)0xfe00a0c0)
#define P_IRQCTRL_MASK1_PWRCTRL ((volatile uint32_t *)0xfe00a0c4)
#define P_IRQCTRL_MASK2_PWRCTRL ((volatile uint32_t *)0xfe00a0c8)
#define P_IRQCTRL_MASK3_PWRCTRL ((volatile uint32_t *)0xfe00a0cc)
#define P_IRQCTRL_MASK4_PWRCTRL ((volatile uint32_t *)0xfe00a0d0)
#define P_IRQCTRL_MASK5_PWRCTRL ((volatile uint32_t *)0xfe00a0d4)
#define P_IRQCTRL_MASK6_PWRCTRL ((volatile uint32_t *)0xfe00a0d8)
#define P_IRQCTRL_MASK7_PWRCTRL ((volatile uint32_t *)0xfe00a0dc)
#define P_IRQCTRL_MASK0_AOCPU ((volatile uint32_t *)0xfe00a100)
#define P_IRQCTRL_MASK1_AOCPU ((volatile uint32_t *)0xfe00a104)
#define P_IRQCTRL_MASK2_AOCPU ((volatile uint32_t *)0xfe00a108)
#define P_IRQCTRL_MASK3_AOCPU ((volatile uint32_t *)0xfe00a10c)
#define P_IRQCTRL_MASK4_AOCPU ((volatile uint32_t *)0xfe00a110)
#define P_IRQCTRL_MASK5_AOCPU ((volatile uint32_t *)0xfe00a114)
#define P_IRQCTRL_MASK6_AOCPU ((volatile uint32_t *)0xfe00a118)
#define P_IRQCTRL_MASK7_AOCPU ((volatile uint32_t *)0xfe00a11c)
#define P_IRQCTRL_IRQ_MODE0 ((volatile uint32_t *)0xfe00a140)
#define P_IRQCTRL_IRQ_MODE1 ((volatile uint32_t *)0xfe00a144)
#define P_IRQCTRL_IRQ_MODE2 ((volatile uint32_t *)0xfe00a148)
#define P_IRQCTRL_IRQ_MODE3 ((volatile uint32_t *)0xfe00a14c)
#define P_IRQCTRL_IRQ_MODE4 ((volatile uint32_t *)0xfe00a150)
#define P_IRQCTRL_IRQ_MODE5 ((volatile uint32_t *)0xfe00a154)
#define P_IRQCTRL_IRQ_MODE6 ((volatile uint32_t *)0xfe00a158)
#define P_IRQCTRL_IRQ_MODE7 ((volatile uint32_t *)0xfe00a15c)
#define P_IRQCTRL_IRQ_LATCH0 ((volatile uint32_t *)0xfe00a180)
#define P_IRQCTRL_IRQ_LATCH1 ((volatile uint32_t *)0xfe00a184)
#define P_IRQCTRL_IRQ_LATCH2 ((volatile uint32_t *)0xfe00a188)
#define P_IRQCTRL_IRQ_LATCH3 ((volatile uint32_t *)0xfe00a18c)
#define P_IRQCTRL_IRQ_LATCH4 ((volatile uint32_t *)0xfe00a190)
#define P_IRQCTRL_IRQ_LATCH5 ((volatile uint32_t *)0xfe00a194)
#define P_IRQCTRL_IRQ_LATCH6 ((volatile uint32_t *)0xfe00a198)
#define P_IRQCTRL_IRQ_LATCH7 ((volatile uint32_t *)0xfe00a19c)
#define P_IRQCTRL_IRQ_LATCH_CLR0 ((volatile uint32_t *)0xfe00a1c0)
#define P_IRQCTRL_IRQ_LATCH_CLR1 ((volatile uint32_t *)0xfe00a1c4)
#define P_IRQCTRL_IRQ_LATCH_CLR2 ((volatile uint32_t *)0xfe00a1c8)
#define P_IRQCTRL_IRQ_LATCH_CLR3 ((volatile uint32_t *)0xfe00a1cc)
#define P_IRQCTRL_IRQ_LATCH_CLR4 ((volatile uint32_t *)0xfe00a1d0)
#define P_IRQCTRL_IRQ_LATCH_CLR5 ((volatile uint32_t *)0xfe00a1d4)
#define P_IRQCTRL_IRQ_LATCH_CLR6 ((volatile uint32_t *)0xfe00a1d8)
#define P_IRQCTRL_IRQ_LATCH_CLR7 ((volatile uint32_t *)0xfe00a1dc)
#define P_IRQCTRL_LOCK_BIT ((volatile uint32_t *)0xfe00a200)
#define P_IRQCTRL_PROT_BIT ((volatile uint32_t *)0xfe00a204)
//========================================================================
//  RESET_CTRL - Registers
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe002000
// -----------------------------------------------
#define P_RESETCTRL_RESET0 ((volatile uint32_t *)0xfe002000)
#define P_RESETCTRL_RESET1 ((volatile uint32_t *)0xfe002004)
#define P_RESETCTRL_RESET2 ((volatile uint32_t *)0xfe002008)
#define P_RESETCTRL_RESET3 ((volatile uint32_t *)0xfe00200c)
#define P_RESETCTRL_RESET4 ((volatile uint32_t *)0xfe002010)
#define P_RESETCTRL_RESET5 ((volatile uint32_t *)0xfe002014)
#define P_RESETCTRL_RESET0_LEVEL ((volatile uint32_t *)0xfe002040)
#define P_RESETCTRL_RESET1_LEVEL ((volatile uint32_t *)0xfe002044)
#define P_RESETCTRL_RESET2_LEVEL ((volatile uint32_t *)0xfe002048)
#define P_RESETCTRL_RESET3_LEVEL ((volatile uint32_t *)0xfe00204c)
#define P_RESETCTRL_RESET4_LEVEL ((volatile uint32_t *)0xfe002050)
#define P_RESETCTRL_RESET5_LEVEL ((volatile uint32_t *)0xfe002054)
#define P_RESETCTRL_RESET0_MASK ((volatile uint32_t *)0xfe002080)
#define P_RESETCTRL_RESET1_MASK ((volatile uint32_t *)0xfe002084)
#define P_RESETCTRL_RESET2_MASK ((volatile uint32_t *)0xfe002088)
#define P_RESETCTRL_RESET3_MASK ((volatile uint32_t *)0xfe00208c)
#define P_RESETCTRL_RESET4_MASK ((volatile uint32_t *)0xfe002090)
#define P_RESETCTRL_RESET5_MASK ((volatile uint32_t *)0xfe002094)
#define P_RESETCTRL_RESET_HOLD_CYC ((volatile uint32_t *)0xfe0020c0)
#define P_RESETCTRL_WATCHDOG_CTRL0 ((volatile uint32_t *)0xfe002100)
#define P_RESETCTRL_WATCHDOG_CTRL1 ((volatile uint32_t *)0xfe002104)
#define P_RESETCTRL_WATCHDOG_CNT ((volatile uint32_t *)0xfe002108)
#define P_RESETCTRL_WATCHDOG_CLR ((volatile uint32_t *)0xfe00210c)
#define P_RESETCTRL_SEC_WATCHDOG_CTRL0 ((volatile uint32_t *)0xfe002110)
#define P_RESETCTRL_SEC_WATCHDOG_CTRL1 ((volatile uint32_t *)0xfe002114)
#define P_RESETCTRL_SEC_WATCHDOG_CNT ((volatile uint32_t *)0xfe002118)
#define P_RESETCTRL_SEC_WATCHDOG_CLR ((volatile uint32_t *)0xfe00211c)
#define P_RESETCTRL_WATCHDOG_DLY_CNT ((volatile uint32_t *)0xfe002120)
#define P_RESETCTRL_SEC_RESET0 ((volatile uint32_t *)0xfe002140)
#define P_RESETCTRL_SEC_RESET1 ((volatile uint32_t *)0xfe002144)
#define P_RESETCTRL_SEC_RESET0_LEVEL ((volatile uint32_t *)0xfe002180)
#define P_RESETCTRL_SEC_RESET1_LEVEL ((volatile uint32_t *)0xfe002184)
#define P_RESETCTRL_SEC_RESET0_MASK ((volatile uint32_t *)0xfe0021c0)
#define P_RESETCTRL_SEC_RESET1_MASK ((volatile uint32_t *)0xfe0021c4)
#define P_RESETCTRL_RESET0_LOCK ((volatile uint32_t *)0xfe002200)
#define P_RESETCTRL_RESET1_LOCK ((volatile uint32_t *)0xfe002204)
#define P_RESETCTRL_RESET2_LOCK ((volatile uint32_t *)0xfe002208)
#define P_RESETCTRL_RESET3_LOCK ((volatile uint32_t *)0xfe00220c)
#define P_RESETCTRL_RESET4_LOCK ((volatile uint32_t *)0xfe002210)
#define P_RESETCTRL_RESET5_LOCK ((volatile uint32_t *)0xfe002214)
#define P_RESETCTRL_SEC_RESET0_LOCK ((volatile uint32_t *)0xfe002220)
#define P_RESETCTRL_SEC_RESET1_LOCK ((volatile uint32_t *)0xfe002224)
#define P_RESETCTRL_RESET0_PROT ((volatile uint32_t *)0xfe002240)
#define P_RESETCTRL_RESET1_PROT ((volatile uint32_t *)0xfe002244)
#define P_RESETCTRL_RESET2_PROT ((volatile uint32_t *)0xfe002248)
#define P_RESETCTRL_RESET3_PROT ((volatile uint32_t *)0xfe00224c)
#define P_RESETCTRL_RESET4_PROT ((volatile uint32_t *)0xfe002250)
#define P_RESETCTRL_RESET5_PROT ((volatile uint32_t *)0xfe002254)
#define P_RESETCTRL_SEC_RESET0_PROT ((volatile uint32_t *)0xfe002260)
#define P_RESETCTRL_SEC_RESET1_PROT ((volatile uint32_t *)0xfe002264)
//========================================================================
//  CPU_CTRL
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe00e000
// -----------------------------------------------
#define P_CPUCTRL_SYS_CPU_RESET_CNTL ((volatile uint32_t *)0xfe00e140)
#define P_CPUCTRL_SYS_CPU_CLK_CTRL ((volatile uint32_t *)0xfe00e144)
#define P_CPUCTRL_SYS_CPU_CLK_CTRL1 ((volatile uint32_t *)0xfe00e148)
#define P_CPUCTRL_SYS_CPU_CLK_CTRL2 ((volatile uint32_t *)0xfe00e14c)
#define P_CPUCTRL_SYS_CPU_CLK_CTRL3 ((volatile uint32_t *)0xfe00e150)
#define P_CPUCTRL_SYS_CPU_CLK_CTRL4 ((volatile uint32_t *)0xfe00e154)
#define P_CPUCTRL_SYS_CPU_CLK_CTRL5 ((volatile uint32_t *)0xfe00e158)
#define P_CPUCTRL_SYS_CPU_CLK_CTRL6 ((volatile uint32_t *)0xfe00e15c)
#define P_CPUCTRL_SYS_CPU_CLK_RESULT ((volatile uint32_t *)0xfe00e160)
#define P_CPUCTRL_ROM_DISABLE ((volatile uint32_t *)0xfe00e180)
#define P_CPUCTRL_SYS_CPU_POR_CFG0 ((volatile uint32_t *)0xfe00e240)
#define P_CPUCTRL_SYS_CPU_POR_CFG1 ((volatile uint32_t *)0xfe00e244)
#define P_CPUCTRL_SYS_CPU_CFG0 ((volatile uint32_t *)0xfe00e248)
#define P_CPUCTRL_SYS_CPU_CFG1 ((volatile uint32_t *)0xfe00e24c)
#define P_CPUCTRL_SYS_CPU_CFG2 ((volatile uint32_t *)0xfe00e250)
#define P_CPUCTRL_SYS_CPU_CFG3 ((volatile uint32_t *)0xfe00e254)
#define P_CPUCTRL_SYS_CPU_CFG4 ((volatile uint32_t *)0xfe00e258)
#define P_CPUCTRL_SYS_CPU_CFG5 ((volatile uint32_t *)0xfe00e25c)
#define P_CPUCTRL_SYS_CPU_CFG6 ((volatile uint32_t *)0xfe00e260)
#define P_CPUCTRL_SYS_CPU_CFG7 ((volatile uint32_t *)0xfe00e264)
#define P_CPUCTRL_SYS_CPU_CFG8 ((volatile uint32_t *)0xfe00e268)
#define P_CPUCTRL_SYS_CPU_CFG9 ((volatile uint32_t *)0xfe00e26c)
#define P_CPUCTRL_SYS_CPU_CFG10 ((volatile uint32_t *)0xfe00e270)
#define P_CPUCTRL_SYS_CPU_CFG11 ((volatile uint32_t *)0xfe00e274)
#define P_CPUCTRL_SYS_CPU_CFG12 ((volatile uint32_t *)0xfe00e278)
#define P_CPUCTRL_SYS_CPU_CFG13 ((volatile uint32_t *)0xfe00e27c)
#define P_CPUCTRL_SYS_CPU_STATUS0 ((volatile uint32_t *)0xfe00e280)
#define P_CPUCTRL_SYS_CPU_STATUS1 ((volatile uint32_t *)0xfe00e284)
#define P_CPUCTRL_SYS_CPU_STATUS2 ((volatile uint32_t *)0xfe00e288)
#define P_CPUCTRL_SYS_CPU_STATUS3 ((volatile uint32_t *)0xfe00e28c)
#define P_CPUCTRL_SYS_CPU_STATUS4 ((volatile uint32_t *)0xfe00e290)
#define P_CPUCTRL_SYS_CPU_STATUS5 ((volatile uint32_t *)0xfe00e294)
#define P_CPUCTRL_SYS_CPU_STATUS6 ((volatile uint32_t *)0xfe00e298)
#define P_CPUCTRL_SYS_CPU_STATUS7 ((volatile uint32_t *)0xfe00e29c)
#define P_SYS_CPU_MISC ((volatile uint32_t *)0xfe00e2a0)
//========================================================================
//  SAR_ADC
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe026000
// -----------------------------------------------
#define P_SAR_ADC_REG0 ((volatile uint32_t *)0xfe026000)
#define P_SAR_ADC_CHAN_LIST ((volatile uint32_t *)0xfe026004)
#define P_SAR_ADC_AVG_CNTL ((volatile uint32_t *)0xfe026008)
#define P_SAR_ADC_REG3 ((volatile uint32_t *)0xfe02600c)
#define P_SAR_ADC_DELAY ((volatile uint32_t *)0xfe026010)
#define P_SAR_ADC_LAST_RD ((volatile uint32_t *)0xfe026014)
#define P_SAR_ADC_FIFO_RD ((volatile uint32_t *)0xfe026018)
#define P_SAR_ADC_AUX_SW ((volatile uint32_t *)0xfe02601c)
#define P_SAR_ADC_CHAN_10_SW ((volatile uint32_t *)0xfe026020)
#define P_SAR_ADC_DETECT_IDLE_SW ((volatile uint32_t *)0xfe026024)
#define P_SAR_ADC_DELTA_10 ((volatile uint32_t *)0xfe026028)
#define P_SAR_ADC_REG11 ((volatile uint32_t *)0xfe02602c)
#define P_SAR_ADC_REG12 ((volatile uint32_t *)0xfe026030)
#define P_SAR_ADC_REG13 ((volatile uint32_t *)0xfe026034)
#define P_SAR_ADC_REG14 ((volatile uint32_t *)0xfe026038)
#define P_SAR_ADC_CH0_CTRL1 ((volatile uint32_t *)0xfe02604c)
#define P_SAR_ADC_CH0_CTRL2 ((volatile uint32_t *)0xfe026050)
#define P_SAR_ADC_CH0_CTRL3 ((volatile uint32_t *)0xfe026054)
#define P_SAR_ADC_CH1_CTRL1 ((volatile uint32_t *)0xfe026058)
#define P_SAR_ADC_CH1_CTRL2 ((volatile uint32_t *)0xfe02605c)
#define P_SAR_ADC_CH1_CTRL3 ((volatile uint32_t *)0xfe026060)
#define P_SAR_ADC_CH2_CTRL1 ((volatile uint32_t *)0xfe026064)
#define P_SAR_ADC_CH2_CTRL2 ((volatile uint32_t *)0xfe026068)
#define P_SAR_ADC_CH2_CTRL3 ((volatile uint32_t *)0xfe02606c)
#define P_SAR_ADC_CH3_CTRL1 ((volatile uint32_t *)0xfe026070)
#define P_SAR_ADC_CH3_CTRL2 ((volatile uint32_t *)0xfe026074)
#define P_SAR_ADC_CH3_CTRL3 ((volatile uint32_t *)0xfe026078)
#define P_SAR_ADC_CH4_CTRL1 ((volatile uint32_t *)0xfe02607c)
#define P_SAR_ADC_CH4_CTRL2 ((volatile uint32_t *)0xfe026080)
#define P_SAR_ADC_CH4_CTRL3 ((volatile uint32_t *)0xfe026084)
#define P_SAR_ADC_CH5_CTRL1 ((volatile uint32_t *)0xfe026088)
#define P_SAR_ADC_CH5_CTRL2 ((volatile uint32_t *)0xfe02608c)
#define P_SAR_ADC_CH5_CTRL3 ((volatile uint32_t *)0xfe026090)
#define P_SAR_ADC_CH6_CTRL1 ((volatile uint32_t *)0xfe026094)
#define P_SAR_ADC_CH6_CTRL2 ((volatile uint32_t *)0xfe026098)
#define P_SAR_ADC_CH6_CTRL3 ((volatile uint32_t *)0xfe02609c)
#define P_SAR_ADC_CH7_CTRL1 ((volatile uint32_t *)0xfe0260a0)
#define P_SAR_ADC_CH7_CTRL2 ((volatile uint32_t *)0xfe0260a4)
#define P_SAR_ADC_CH7_CTRL3 ((volatile uint32_t *)0xfe0260a8)
#define P_SAR_ADC_HCIC_CTRL1 ((volatile uint32_t *)0xfe0260ac)
#define P_SAR_ADC_F1_CTRL ((volatile uint32_t *)0xfe0260b0)
#define P_SAR_ADC_F2_CTRL ((volatile uint32_t *)0xfe0260b4)
#define P_SAR_ADC_F3_CTRL ((volatile uint32_t *)0xfe0260b8)
#define P_SAR_ADC_DECI_FILTER_CTRL ((volatile uint32_t *)0xfe0260bc)
#define P_SAR_ADC_COEF_RAM_CNTL ((volatile uint32_t *)0xfe0260c0)
#define P_SAR_ADC_COEF_RAM_DATA ((volatile uint32_t *)0xfe0260c4)
#define P_SAR_ADC_FIFO_RD_NEW ((volatile uint32_t *)0xfe0260c8)
#define P_SAR_ADC_RAW ((volatile uint32_t *)0xfe0260cc)
#define P_SAR_ADC_CHNL0 ((volatile uint32_t *)0xfe0260d0)
#define P_SAR_ADC_CHNL1 ((volatile uint32_t *)0xfe0260d4)
#define P_SAR_ADC_CHNL2 ((volatile uint32_t *)0xfe0260d8)
#define P_SAR_ADC_CHNL3 ((volatile uint32_t *)0xfe0260dc)
#define P_SAR_ADC_CHNL4 ((volatile uint32_t *)0xfe0260e0)
#define P_SAR_ADC_CHNL5 ((volatile uint32_t *)0xfe0260e4)
#define P_SAR_ADC_CHNL6 ((volatile uint32_t *)0xfe0260e8)
#define P_SAR_ADC_CHNL7 ((volatile uint32_t *)0xfe0260ec)
//========================================================================
//  ANA_CTRL - Registers
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe008000
// -----------------------------------------------
#define P_ANACTRL_SYSPLL_CTRL0 ((volatile uint32_t *)0xfe008000)
#define P_ANACTRL_SYSPLL_CTRL1 ((volatile uint32_t *)0xfe008004)
#define P_ANACTRL_SYSPLL_CTRL2 ((volatile uint32_t *)0xfe008008)
#define P_ANACTRL_SYSPLL_CTRL3 ((volatile uint32_t *)0xfe00800c)
#define P_ANACTRL_SYSPLL_CTRL4 ((volatile uint32_t *)0xfe008010)
#define P_ANACTRL_SYSPLL_CTRL5 ((volatile uint32_t *)0xfe008014)
#define P_ANACTRL_SYSPLL_CTRL6 ((volatile uint32_t *)0xfe008018)
#define P_ANACTRL_SYSPLL_STS ((volatile uint32_t *)0xfe00801c)
#define P_ANACTRL_FIXPLL_CTRL0 ((volatile uint32_t *)0xfe008040)
#define P_ANACTRL_FIXPLL_CTRL1 ((volatile uint32_t *)0xfe008044)
#define P_ANACTRL_FIXPLL_CTRL2 ((volatile uint32_t *)0xfe008048)
#define P_ANACTRL_FIXPLL_CTRL3 ((volatile uint32_t *)0xfe00804c)
#define P_ANACTRL_FIXPLL_CTRL4 ((volatile uint32_t *)0xfe008050)
#define P_ANACTRL_FIXPLL_CTRL5 ((volatile uint32_t *)0xfe008054)
#define P_ANACTRL_FIXPLL_CTRL6 ((volatile uint32_t *)0xfe008058)
#define P_ANACTRL_FIXPLL_STS ((volatile uint32_t *)0xfe00805c)
#define P_ANACTRL_GP0PLL_CTRL0 ((volatile uint32_t *)0xfe008080)
#define P_ANACTRL_GP0PLL_CTRL1 ((volatile uint32_t *)0xfe008084)
#define P_ANACTRL_GP0PLL_CTRL2 ((volatile uint32_t *)0xfe008088)
#define P_ANACTRL_GP0PLL_CTRL3 ((volatile uint32_t *)0xfe00808c)
#define P_ANACTRL_GP0PLL_CTRL4 ((volatile uint32_t *)0xfe008090)
#define P_ANACTRL_GP0PLL_CTRL5 ((volatile uint32_t *)0xfe008094)
#define P_ANACTRL_GP0PLL_CTRL6 ((volatile uint32_t *)0xfe008098)
#define P_ANACTRL_GP0PLL_STS ((volatile uint32_t *)0xfe00809c)
#define P_ANACTRL_GP1PLL_CTRL0 ((volatile uint32_t *)0xfe0080c0)
#define P_ANACTRL_GP1PLL_CTRL1 ((volatile uint32_t *)0xfe0080c4)
#define P_ANACTRL_GP1PLL_CTRL2 ((volatile uint32_t *)0xfe0080c8)
#define P_ANACTRL_GP1PLL_CTRL3 ((volatile uint32_t *)0xfe0080cc)
#define P_ANACTRL_GP1PLL_CTRL4 ((volatile uint32_t *)0xfe0080d0)
#define P_ANACTRL_GP1PLL_CTRL5 ((volatile uint32_t *)0xfe0080d4)
#define P_ANACTRL_GP1PLL_CTRL6 ((volatile uint32_t *)0xfe0080d8)
#define P_ANACTRL_GP1PLL_STS ((volatile uint32_t *)0xfe0080dc)
#define P_ANACTRL_HIFIPLL_CTRL0 ((volatile uint32_t *)0xfe008100)
#define P_ANACTRL_HIFIPLL_CTRL1 ((volatile uint32_t *)0xfe008104)
#define P_ANACTRL_HIFIPLL_CTRL2 ((volatile uint32_t *)0xfe008108)
#define P_ANACTRL_HIFIPLL_CTRL3 ((volatile uint32_t *)0xfe00810c)
#define P_ANACTRL_HIFIPLL_CTRL4 ((volatile uint32_t *)0xfe008110)
#define P_ANACTRL_HIFIPLL_CTRL5 ((volatile uint32_t *)0xfe008114)
#define P_ANACTRL_HIFIPLL_CTRL6 ((volatile uint32_t *)0xfe008118)
#define P_ANACTRL_HIFIPLL_STS ((volatile uint32_t *)0xfe00811c)
//`define ANACTRL_PCIEPLL_CTRL0    8'h50
//`define ANACTRL_PCIEPLL_CTRL1    8'h51
//`define ANACTRL_PCIEPLL_CTRL2    8'h52
//`define ANACTRL_PCIEPLL_CTRL3    8'h53
//`define ANACTRL_PCIEPLL_CTRL4    8'h54
//`define ANACTRL_PCIEPLL_CTRL5    8'h55
//`define ANACTRL_PCIEPLL_STS      8'h56
#define P_ANACTRL_MPLL_CTRL0 ((volatile uint32_t *)0xfe008180)
#define P_ANACTRL_MPLL_CTRL1 ((volatile uint32_t *)0xfe008184)
#define P_ANACTRL_MPLL_CTRL2 ((volatile uint32_t *)0xfe008188)
#define P_ANACTRL_MPLL_CTRL3 ((volatile uint32_t *)0xfe00818c)
#define P_ANACTRL_MPLL_CTRL4 ((volatile uint32_t *)0xfe008190)
#define P_ANACTRL_MPLL_CTRL5 ((volatile uint32_t *)0xfe008194)
#define P_ANACTRL_MPLL_CTRL6 ((volatile uint32_t *)0xfe008198)
#define P_ANACTRL_MPLL_CTRL7 ((volatile uint32_t *)0xfe00819c)
#define P_ANACTRL_MPLL_CTRL8 ((volatile uint32_t *)0xfe0081a0)
#define P_ANACTRL_MPLL_STS ((volatile uint32_t *)0xfe0081a4)
#define P_ANACTRL_HDMIPLL_CTRL0 ((volatile uint32_t *)0xfe0081c0)
#define P_ANACTRL_HDMIPLL_CTRL1 ((volatile uint32_t *)0xfe0081c4)
#define P_ANACTRL_HDMIPLL_CTRL2 ((volatile uint32_t *)0xfe0081c8)
#define P_ANACTRL_HDMIPLL_CTRL3 ((volatile uint32_t *)0xfe0081cc)
#define P_ANACTRL_HDMIPLL_CTRL4 ((volatile uint32_t *)0xfe0081d0)
#define P_ANACTRL_HDMIPLL_CTRL5 ((volatile uint32_t *)0xfe0081d4)
#define P_ANACTRL_HDMIPLL_CTRL6 ((volatile uint32_t *)0xfe0081d8)
//`define ANACTRL_HDMIPLL_STS      8'h77
//`define ANACTRL_HDMIPLL_VLOCK    8'h79
#define P_ANACTRL_HDMIPHY_CTRL0 ((volatile uint32_t *)0xfe008200)
#define P_ANACTRL_HDMIPHY_CTRL1 ((volatile uint32_t *)0xfe008204)
#define P_ANACTRL_HDMIPHY_CTRL2 ((volatile uint32_t *)0xfe008208)
#define P_ANACTRL_HDMIPHY_CTRL3 ((volatile uint32_t *)0xfe00820c)
#define P_ANACTRL_HDMIPHY_CTRL4 ((volatile uint32_t *)0xfe008210)
#define P_ANACTRL_HDMIPHY_CTRL5 ((volatile uint32_t *)0xfe008214)
#define P_ANACTRL_HDMIPHY_STS ((volatile uint32_t *)0xfe008218)
//`define ANACTRL_MIPICSI_CTRL0    8'h90
//`define ANACTRL_MIPICSI_CTRL1    8'h91
//`define ANACTRL_MIPICSI_CTRL2    8'h92
//`define ANACTRL_MIPICSI_CTRL3    8'h93
//`define ANACTRL_MIPICSI_CTRL4    8'h94
//`define ANACTRL_MIPICSI_CTRL5    8'h95
//`define ANACTRL_MIPIDSI_CTRL0    8'hA0
//`define ANACTRL_MIPIDSI_CTRL1    8'hA1
//`define ANACTRL_MIPIDSI_CTRL2    8'hA2
//`define ANACTRL_MIPIDSI_STS      8'hA3
//`define ANACTRL_VDAC_CTRL0       8'hB0
//`define ANACTRL_VDAC_CTRL1       8'hB1
#define P_ANACTRL_POR_CTRL ((volatile uint32_t *)0xfe0082d8)
#define P_ANACTRL_LOCK_BIT ((volatile uint32_t *)0xfe0082e0)
#define P_ANACTRL_PROT_BIT ((volatile uint32_t *)0xfe0082e4)
#define P_ANACTRL_ADC_PLL_CTRL ((volatile uint32_t *)0xfe008300)
#define P_ANACTRL_ADC_PLL_CTRL1 ((volatile uint32_t *)0xfe008304)
#define P_ANACTRL_ADC_PLL_CTRL2 ((volatile uint32_t *)0xfe008308)
#define P_ANACTRL_ADC_PLL_CTRL3 ((volatile uint32_t *)0xfe00830c)
#define P_ANACTRL_ADC_PLL_CTRL4 ((volatile uint32_t *)0xfe008310)
#define P_ANACTRL_ADC_PLL_CTRL5 ((volatile uint32_t *)0xfe008314)
#define P_ANACTRL_ADC_PLL_CTRL6 ((volatile uint32_t *)0xfe008318)
//`define ANACTRL_ADC_PLL_STS      8'hC7
#define P_ANACTRL_RTCPLL_CTRL0 ((volatile uint32_t *)0xfe008340)
#define P_ANACTRL_RTCPLL_CTRL1 ((volatile uint32_t *)0xfe008344)
#define P_ANACTRL_RTCPLL_CTRL2 ((volatile uint32_t *)0xfe008348)
#define P_ANACTRL_RTCPLL_CTRL3 ((volatile uint32_t *)0xfe00834c)
#define P_ANACTRL_RTCPLL_CTRL4 ((volatile uint32_t *)0xfe008350)
#define P_ANACTRL_RTCPLL_STS ((volatile uint32_t *)0xfe008354)
//`define ANACTRL_S2_DADC_CTRL     8'hD0
//`define ANACTRL_S2_DADC_CTRL2    8'hD1
#define P_ANACTRL_CHIP_TEST_STS ((volatile uint32_t *)0xfe008380)
//========================================================================
//  Ethernet Phy
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe028000
// -----------------------------------------------
#define P_ETH_PHY_DBG_CTL0 ((volatile uint32_t *)0xfe028000)
#define P_ETH_PHY_DBG_CTL1 ((volatile uint32_t *)0xfe028004)
#define P_ETH_PHY_DBG_CFG0 ((volatile uint32_t *)0xfe028008)
#define P_ETH_PHY_DBG_CFG1 ((volatile uint32_t *)0xfe02800c)
#define P_ETH_PHY_DBG_CFG2 ((volatile uint32_t *)0xfe028010)
#define P_ETH_PHY_DBG_CFG3 ((volatile uint32_t *)0xfe028014)
#define P_ETH_PHY_DBG_CFG4 ((volatile uint32_t *)0xfe028018)
#define P_ETH_PLL_STS ((volatile uint32_t *)0xfe028040)
#define P_ETH_PLL_CTL0 ((volatile uint32_t *)0xfe028044)
#define P_ETH_PLL_CTL1 ((volatile uint32_t *)0xfe028048)
#define P_ETH_PLL_CTL2 ((volatile uint32_t *)0xfe02804c)
#define P_ETH_PLL_CTL3 ((volatile uint32_t *)0xfe028050)
#define P_ETH_PLL_CTL4 ((volatile uint32_t *)0xfe028054)
#define P_ETH_PLL_CTL5 ((volatile uint32_t *)0xfe028058)
#define P_ETH_PLL_CTL6 ((volatile uint32_t *)0xfe02805c)
#define P_ETH_PLL_CTL7 ((volatile uint32_t *)0xfe028060)
#define P_ETH_PHY_CNTL0 ((volatile uint32_t *)0xfe028080)
#define P_ETH_PHY_CNTL1 ((volatile uint32_t *)0xfe028084)
#define P_ETH_PHY_CNTL2 ((volatile uint32_t *)0xfe028088)
#define P_ETH_PHY_CNTL3 ((volatile uint32_t *)0xfe02808c)
#define P_ETH_PHY_STS0 ((volatile uint32_t *)0xfe028094)
#define P_ETH_PHY_STS1 ((volatile uint32_t *)0xfe028098)
#define P_ETH_PHY_STS2 ((volatile uint32_t *)0xfe02809c)
#define P_ETH_PHY_DBG_REG ((volatile uint32_t *)0xfe0280a0)
//========================================================================
//  Ethernet TOP
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe024000
// -----------------------------------------------
#define P_ETHTOP_CNTL0 ((volatile uint32_t *)0xfe024000)
#define P_ETHTOP_CNTL1 ((volatile uint32_t *)0xfe024004)
//========================================================================
//  I2C Slave A
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe064000
// -----------------------------------------------
#define P_I2C_S_A_CONTROL_REG ((volatile uint32_t *)0xfe064000)
#define P_I2C_S_A_SEND_REG ((volatile uint32_t *)0xfe064004)
#define P_I2C_S_A_RECV_REG ((volatile uint32_t *)0xfe064008)
#define P_I2C_S_A_CNTL1_REG ((volatile uint32_t *)0xfe06400c)
//========================================================================
//  IR RX/TX
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe084000
// -----------------------------------------------
#define P_IRCTRL_IR_DEC_LDR_ACTIVE ((volatile uint32_t *)0xfe084000)
#define P_IRCTRL_IR_DEC_LDR_IDLE ((volatile uint32_t *)0xfe084004)
#define P_IRCTRL_IR_DEC_LDR_REPEAT ((volatile uint32_t *)0xfe084008)
#define P_IRCTRL_IR_DEC_BIT_0 ((volatile uint32_t *)0xfe08400c)
#define P_IRCTRL_IR_DEC_REG0 ((volatile uint32_t *)0xfe084010)
#define P_IRCTRL_IR_DEC_FRAME ((volatile uint32_t *)0xfe084014)
#define P_IRCTRL_IR_DEC_STATUS ((volatile uint32_t *)0xfe084018)
#define P_IRCTRL_IR_DEC_REG1 ((volatile uint32_t *)0xfe08401c)
#define P_IRCTRL_MF_IR_DEC_LDR_ACTIVE ((volatile uint32_t *)0xfe084040)
#define P_IRCTRL_MF_IR_DEC_LDR_IDLE ((volatile uint32_t *)0xfe084044)
#define P_IRCTRL_MF_IR_DEC_LDR_REPEAT ((volatile uint32_t *)0xfe084048)
#define P_IRCTRL_MF_IR_DEC_BIT_0 ((volatile uint32_t *)0xfe08404c)
#define P_IRCTRL_MF_IR_DEC_REG0 ((volatile uint32_t *)0xfe084050)
#define P_IRCTRL_MF_IR_DEC_FRAME ((volatile uint32_t *)0xfe084054)
#define P_IRCTRL_MF_IR_DEC_STATUS ((volatile uint32_t *)0xfe084058)
#define P_IRCTRL_MF_IR_DEC_REG1 ((volatile uint32_t *)0xfe08405c)
#define P_IRCTRL_MF_IR_DEC_REG2 ((volatile uint32_t *)0xfe084060)
#define P_IRCTRL_MF_IR_DEC_DURATN2 ((volatile uint32_t *)0xfe084064)
#define P_IRCTRL_MF_IR_DEC_DURATN3 ((volatile uint32_t *)0xfe084068)
#define P_IRCTRL_MF_IR_DEC_FRAME1 ((volatile uint32_t *)0xfe08406c)
#define P_IRCTRL_MF_IR_DEC_STATUS1 ((volatile uint32_t *)0xfe084070)
#define P_IRCTRL_MF_IR_DEC_STATUS2 ((volatile uint32_t *)0xfe084074)
#define P_IRCTRL_MF_IR_DEC_REG3 ((volatile uint32_t *)0xfe084078)
#define P_IRCTRL_MF_IR_DEC_FRAME_RSV0 ((volatile uint32_t *)0xfe08407c)
#define P_IRCTRL_MF_IR_DEC_FRAME_RSV1 ((volatile uint32_t *)0xfe084080)
#define P_IRCTRL_MF_IR_DEC_FILTE ((volatile uint32_t *)0xfe084084)
#define P_IRCTRL_MF_IR_DEC_IRQ_CTL ((volatile uint32_t *)0xfe084088)
#define P_IRCTRL_MF_IR_DEC_FIFO_CTL ((volatile uint32_t *)0xfe08408c)
#define P_IRCTRL_MF_IR_DEC_WIDTH_NEW ((volatile uint32_t *)0xfe084090)
#define P_IRCTRL_MF_IR_DEC_REPEAT_DET ((volatile uint32_t *)0xfe084094)
#define P_IRCTRL_IR_DEC_DEMOD_CNTL0 ((volatile uint32_t *)0xfe0840c0)
#define P_IRCTRL_IR_DEC_DEMOD_CNTL1 ((volatile uint32_t *)0xfe0840c4)
#define P_IRCTRL_IR_DEC_DEMOD_IIR_THD ((volatile uint32_t *)0xfe0840c8)
#define P_IRCTRL_IR_DEC_DEMOD_THD0 ((volatile uint32_t *)0xfe0840cc)
#define P_IRCTRL_IR_DEC_DEMOD_THD1 ((volatile uint32_t *)0xfe0840d0)
#define P_IRCTRL_IR_DEC_DEMOD_SUM_CNT0 ((volatile uint32_t *)0xfe0840d4)
#define P_IRCTRL_IR_DEC_DEMOD_SUM_CNT1 ((volatile uint32_t *)0xfe0840d8)
#define P_IRCTRL_IR_DEC_DEMOD_CNT0 ((volatile uint32_t *)0xfe0840dc)
#define P_IRCTRL_IR_DEC_DEMOD_CNT1 ((volatile uint32_t *)0xfe0840e0)
#define P_IRCTRL_IR_BLASTER_ADDR0 ((volatile uint32_t *)0xfe08410c)
#define P_IRCTRL_IR_BLASTER_ADDR1 ((volatile uint32_t *)0xfe084110)
#define P_IRCTRL_IR_BLASTER_ADDR2 ((volatile uint32_t *)0xfe084114)
#define P_IRCTRL_IR_BLASTER_ADDR3 ((volatile uint32_t *)0xfe084118)
//========================================================================
//  I2C Master A
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe066000
// -----------------------------------------------
#define P_I2C_M_A_CONTROL_REG ((volatile uint32_t *)0xfe066000)
#define P_I2C_M_A_SLAVE_ADDR ((volatile uint32_t *)0xfe066004)
#define P_I2C_M_A_TOKEN_LIST0 ((volatile uint32_t *)0xfe066008)
#define P_I2C_M_A_TOKEN_LIST1 ((volatile uint32_t *)0xfe06600c)
#define P_I2C_M_A_WDATA_REG0 ((volatile uint32_t *)0xfe066010)
#define P_I2C_M_A_WDATA_REG1 ((volatile uint32_t *)0xfe066014)
#define P_I2C_M_A_RDATA_REG0 ((volatile uint32_t *)0xfe066018)
#define P_I2C_M_A_RDATA_REG1 ((volatile uint32_t *)0xfe06601c)
#define P_I2C_M_A_TIMEOUT_TH ((volatile uint32_t *)0xfe066020)
#define P_I2C_M_A_CNTL_DELY1 ((volatile uint32_t *)0xfe066024)
#define P_I2C_M_A_CNTL_DELY2 ((volatile uint32_t *)0xfe066028)
#define P_I2C_M_A_LOW_DELY ((volatile uint32_t *)0xfe06602c)
#define P_I2C_M_A_HIGH_DELY ((volatile uint32_t *)0xfe066030)
#define P_I2C_M_A_FIFO_CTRL0 ((volatile uint32_t *)0xfe066034)
#define P_I2C_M_A_FIFO_CTRL1 ((volatile uint32_t *)0xfe066038)
#define P_I2C_M_A_FIFO_PENDING ((volatile uint32_t *)0xfe06603c)
#define P_I2C_M_A_FIFO_PENDING_MASK ((volatile uint32_t *)0xfe066040)
#define P_I2C_M_A_FIFO_ST0 ((volatile uint32_t *)0xfe066044)
//========================================================================
//  I2C Master B
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe068000
// -----------------------------------------------
#define P_I2C_M_B_CONTROL_REG ((volatile uint32_t *)0xfe068000)
#define P_I2C_M_B_SLAVE_ADDR ((volatile uint32_t *)0xfe068004)
#define P_I2C_M_B_TOKEN_LIST0 ((volatile uint32_t *)0xfe068008)
#define P_I2C_M_B_TOKEN_LIST1 ((volatile uint32_t *)0xfe06800c)
#define P_I2C_M_B_WDATA_REG0 ((volatile uint32_t *)0xfe068010)
#define P_I2C_M_B_WDATA_REG1 ((volatile uint32_t *)0xfe068014)
#define P_I2C_M_B_RDATA_REG0 ((volatile uint32_t *)0xfe068018)
#define P_I2C_M_B_RDATA_REG1 ((volatile uint32_t *)0xfe06801c)
#define P_I2C_M_B_TIMEOUT_TH ((volatile uint32_t *)0xfe068020)
#define P_I2C_M_B_CNTL_DELY1 ((volatile uint32_t *)0xfe068024)
#define P_I2C_M_B_CNTL_DELY2 ((volatile uint32_t *)0xfe068028)
#define P_I2C_M_B_LOW_DELY ((volatile uint32_t *)0xfe06802c)
#define P_I2C_M_B_HIGH_DELY ((volatile uint32_t *)0xfe068030)
#define P_I2C_M_B_FIFO_CTRL0 ((volatile uint32_t *)0xfe068034)
#define P_I2C_M_B_FIFO_CTRL1 ((volatile uint32_t *)0xfe068038)
#define P_I2C_M_B_FIFO_PENDING ((volatile uint32_t *)0xfe06803c)
#define P_I2C_M_B_FIFO_PENDING_MASK ((volatile uint32_t *)0xfe068040)
#define P_I2C_M_B_FIFO_ST0 ((volatile uint32_t *)0xfe068044)
//========================================================================
//  I2C Master C
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe06a000
// -----------------------------------------------
#define P_I2C_M_C_CONTROL_REG ((volatile uint32_t *)0xfe06a000)
#define P_I2C_M_C_SLAVE_ADDR ((volatile uint32_t *)0xfe06a004)
#define P_I2C_M_C_TOKEN_LIST0 ((volatile uint32_t *)0xfe06a008)
#define P_I2C_M_C_TOKEN_LIST1 ((volatile uint32_t *)0xfe06a00c)
#define P_I2C_M_C_WDATA_REG0 ((volatile uint32_t *)0xfe06a010)
#define P_I2C_M_C_WDATA_REG1 ((volatile uint32_t *)0xfe06a014)
#define P_I2C_M_C_RDATA_REG0 ((volatile uint32_t *)0xfe06a018)
#define P_I2C_M_C_RDATA_REG1 ((volatile uint32_t *)0xfe06a01c)
#define P_I2C_M_C_TIMEOUT_TH ((volatile uint32_t *)0xfe06a020)
#define P_I2C_M_C_CNTL_DELY1 ((volatile uint32_t *)0xfe06a024)
#define P_I2C_M_C_CNTL_DELY2 ((volatile uint32_t *)0xfe06a028)
#define P_I2C_M_C_LOW_DELY ((volatile uint32_t *)0xfe06a02c)
#define P_I2C_M_C_HIGH_DELY ((volatile uint32_t *)0xfe06a030)
#define P_I2C_M_C_FIFO_CTRL0 ((volatile uint32_t *)0xfe06a034)
#define P_I2C_M_C_FIFO_CTRL1 ((volatile uint32_t *)0xfe06a038)
#define P_I2C_M_C_FIFO_PENDING ((volatile uint32_t *)0xfe06a03c)
#define P_I2C_M_C_FIFO_PENDING_MASK ((volatile uint32_t *)0xfe06a040)
#define P_I2C_M_C_FIFO_ST0 ((volatile uint32_t *)0xfe06a044)
//========================================================================
//  I2C Master D
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe06c000
// -----------------------------------------------
#define P_I2C_M_D_CONTROL_REG ((volatile uint32_t *)0xfe06c000)
#define P_I2C_M_D_SLAVE_ADDR ((volatile uint32_t *)0xfe06c004)
#define P_I2C_M_D_TOKEN_LIST0 ((volatile uint32_t *)0xfe06c008)
#define P_I2C_M_D_TOKEN_LIST1 ((volatile uint32_t *)0xfe06c00c)
#define P_I2C_M_D_WDATA_REG0 ((volatile uint32_t *)0xfe06c010)
#define P_I2C_M_D_WDATA_REG1 ((volatile uint32_t *)0xfe06c014)
#define P_I2C_M_D_RDATA_REG0 ((volatile uint32_t *)0xfe06c018)
#define P_I2C_M_D_RDATA_REG1 ((volatile uint32_t *)0xfe06c01c)
#define P_I2C_M_D_TIMEOUT_TH ((volatile uint32_t *)0xfe06c020)
#define P_I2C_M_D_CNTL_DELY1 ((volatile uint32_t *)0xfe06c024)
#define P_I2C_M_D_CNTL_DELY2 ((volatile uint32_t *)0xfe06c028)
#define P_I2C_M_D_LOW_DELY ((volatile uint32_t *)0xfe06c02c)
#define P_I2C_M_D_HIGH_DELY ((volatile uint32_t *)0xfe06c030)
#define P_I2C_M_D_FIFO_CTRL0 ((volatile uint32_t *)0xfe06c034)
#define P_I2C_M_D_FIFO_CTRL1 ((volatile uint32_t *)0xfe06c038)
#define P_I2C_M_D_FIFO_PENDING ((volatile uint32_t *)0xfe06c03c)
#define P_I2C_M_D_FIFO_PENDING_MASK ((volatile uint32_t *)0xfe06c040)
#define P_I2C_M_D_FIFO_ST0 ((volatile uint32_t *)0xfe06c044)
//========================================================================
//  I2C Master E
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe06e000
// -----------------------------------------------
#define P_I2C_M_E_CONTROL_REG ((volatile uint32_t *)0xfe06e000)
#define P_I2C_M_E_SLAVE_ADDR ((volatile uint32_t *)0xfe06e004)
#define P_I2C_M_E_TOKEN_LIST0 ((volatile uint32_t *)0xfe06e008)
#define P_I2C_M_E_TOKEN_LIST1 ((volatile uint32_t *)0xfe06e00c)
#define P_I2C_M_E_WDATA_REG0 ((volatile uint32_t *)0xfe06e010)
#define P_I2C_M_E_WDATA_REG1 ((volatile uint32_t *)0xfe06e014)
#define P_I2C_M_E_RDATA_REG0 ((volatile uint32_t *)0xfe06e018)
#define P_I2C_M_E_RDATA_REG1 ((volatile uint32_t *)0xfe06e01c)
#define P_I2C_M_E_TIMEOUT_TH ((volatile uint32_t *)0xfe06e020)
#define P_I2C_M_E_CNTL_DELY1 ((volatile uint32_t *)0xfe06e024)
#define P_I2C_M_E_CNTL_DELY2 ((volatile uint32_t *)0xfe06e028)
#define P_I2C_M_E_LOW_DELY ((volatile uint32_t *)0xfe06e02c)
#define P_I2C_M_E_HIGH_DELY ((volatile uint32_t *)0xfe06e030)
#define P_I2C_M_E_FIFO_CTRL0 ((volatile uint32_t *)0xfe06e034)
#define P_I2C_M_E_FIFO_CTRL1 ((volatile uint32_t *)0xfe06e038)
#define P_I2C_M_E_FIFO_PENDING ((volatile uint32_t *)0xfe06e03c)
#define P_I2C_M_E_FIFO_PENDING_MASK ((volatile uint32_t *)0xfe06e040)
#define P_I2C_M_E_FIFO_ST0 ((volatile uint32_t *)0xfe06e044)
//========================================================================
//  I2C Master F
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe070000
// -----------------------------------------------
#define P_I2C_M_F_CONTROL_REG ((volatile uint32_t *)0xfe070000)
#define P_I2C_M_F_SLAVE_ADDR ((volatile uint32_t *)0xfe070004)
#define P_I2C_M_F_TOKEN_LIST0 ((volatile uint32_t *)0xfe070008)
#define P_I2C_M_F_TOKEN_LIST1 ((volatile uint32_t *)0xfe07000c)
#define P_I2C_M_F_WDATA_REG0 ((volatile uint32_t *)0xfe070010)
#define P_I2C_M_F_WDATA_REG1 ((volatile uint32_t *)0xfe070014)
#define P_I2C_M_F_RDATA_REG0 ((volatile uint32_t *)0xfe070018)
#define P_I2C_M_F_RDATA_REG1 ((volatile uint32_t *)0xfe07001c)
#define P_I2C_M_F_TIMEOUT_TH ((volatile uint32_t *)0xfe070020)
#define P_I2C_M_F_CNTL_DELY1 ((volatile uint32_t *)0xfe070024)
#define P_I2C_M_F_CNTL_DELY2 ((volatile uint32_t *)0xfe070028)
#define P_I2C_M_F_LOW_DELY ((volatile uint32_t *)0xfe07002c)
#define P_I2C_M_F_HIGH_DELY ((volatile uint32_t *)0xfe070030)
#define P_I2C_M_F_FIFO_CTRL_REG ((volatile uint32_t *)0xfe070034)
#define P_I2C_M_F_STATE_REG ((volatile uint32_t *)0xfe070038)
//========================================================================
//  APB0_UART_A - Registers
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe078000
// -----------------------------------------------
#define P_UART_A_WFIFO ((volatile uint32_t *)0xfe078000)
#define P_UART_A_RFIFO ((volatile uint32_t *)0xfe078004)
#define P_UART_A_CONTROL ((volatile uint32_t *)0xfe078008)
#define P_UART_A_STATUS ((volatile uint32_t *)0xfe07800c)
#define P_UART_A_MISC ((volatile uint32_t *)0xfe078010)
#define P_UART_A_REG5 ((volatile uint32_t *)0xfe078014)
//========================================================================
//  APB0_UART_B - Registers
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe07a000
// -----------------------------------------------
#define P_UART_B_WFIFO ((volatile uint32_t *)0xfe07a000)
#define P_UART_B_RFIFO ((volatile uint32_t *)0xfe07a004)
#define P_UART_B_CONTROL ((volatile uint32_t *)0xfe07a008)
#define P_UART_B_STATUS ((volatile uint32_t *)0xfe07a00c)
#define P_UART_B_MISC ((volatile uint32_t *)0xfe07a010)
#define P_UART_B_REG5 ((volatile uint32_t *)0xfe07a014)
//========================================================================
//  APB0_UART_C - Registers
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe07c000
// -----------------------------------------------
#define P_UART_C_WFIFO ((volatile uint32_t *)0xfe07c000)
#define P_UART_C_RFIFO ((volatile uint32_t *)0xfe07c004)
#define P_UART_C_CONTROL ((volatile uint32_t *)0xfe07c008)
#define P_UART_C_STATUS ((volatile uint32_t *)0xfe07c00c)
#define P_UART_C_MISC ((volatile uint32_t *)0xfe07c010)
#define P_UART_C_REG5 ((volatile uint32_t *)0xfe07c014)
//========================================================================
//  APB0_UART_D - Registers
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe07e000
// -----------------------------------------------
#define P_UART_D_WFIFO ((volatile uint32_t *)0xfe07e000)
#define P_UART_D_RFIFO ((volatile uint32_t *)0xfe07e004)
#define P_UART_D_CONTROL ((volatile uint32_t *)0xfe07e008)
#define P_UART_D_STATUS ((volatile uint32_t *)0xfe07e00c)
#define P_UART_D_MISC ((volatile uint32_t *)0xfe07e010)
#define P_UART_D_REG5 ((volatile uint32_t *)0xfe07e014)
//========================================================================
//  APB0_UART_E - Registers
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe080000
// -----------------------------------------------
#define P_UART_E_WFIFO ((volatile uint32_t *)0xfe080000)
#define P_UART_E_RFIFO ((volatile uint32_t *)0xfe080004)
#define P_UART_E_CONTROL ((volatile uint32_t *)0xfe080008)
#define P_UART_E_STATUS ((volatile uint32_t *)0xfe08000c)
#define P_UART_E_MISC ((volatile uint32_t *)0xfe080010)
#define P_UART_E_REG5 ((volatile uint32_t *)0xfe080014)
//========================================================================
//  PWM_AB - Registers
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe058000
// -----------------------------------------------
#define P_PWMAB_PWM_A ((volatile uint32_t *)0xfe058000)
#define P_PWMAB_PWM_B ((volatile uint32_t *)0xfe058004)
#define P_PWMAB_MISC_REG_AB ((volatile uint32_t *)0xfe058008)
#define P_PWMAB_DELTA_SIGMA_AB ((volatile uint32_t *)0xfe05800c)
#define P_PWMAB_TIME_AB ((volatile uint32_t *)0xfe058010)
#define P_PWMAB_A2 ((volatile uint32_t *)0xfe058014)
#define P_PWMAB_B2 ((volatile uint32_t *)0xfe058018)
#define P_PWMAB_BLINK_AB ((volatile uint32_t *)0xfe05801c)
#define P_PWMAB_LOCK_AB ((volatile uint32_t *)0xfe058020)
//========================================================================
//  PWM_CD - Registers
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe05a000
// -----------------------------------------------
#define P_PWMCD_PWM_A ((volatile uint32_t *)0xfe05a000)
#define P_PWMCD_PWM_B ((volatile uint32_t *)0xfe05a004)
#define P_PWMCD_MISC_REG_AB ((volatile uint32_t *)0xfe05a008)
#define P_PWMCD_DELTA_SIGMA_AB ((volatile uint32_t *)0xfe05a00c)
#define P_PWMCD_TIME_AB ((volatile uint32_t *)0xfe05a010)
#define P_PWMCD_A2 ((volatile uint32_t *)0xfe05a014)
#define P_PWMCD_B2 ((volatile uint32_t *)0xfe05a018)
#define P_PWMCD_BLINK_AB ((volatile uint32_t *)0xfe05a01c)
#define P_PWMCD_LOCK_AB ((volatile uint32_t *)0xfe05a020)
//========================================================================
//  PWM_EF - Registers
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe05c000
// -----------------------------------------------
#define P_PWMEF_PWM_A ((volatile uint32_t *)0xfe05c000)
#define P_PWMEF_PWM_B ((volatile uint32_t *)0xfe05c004)
#define P_PWMEF_MISC_REG_AB ((volatile uint32_t *)0xfe05c008)
#define P_PWMEF_DELTA_SIGMA_AB ((volatile uint32_t *)0xfe05c00c)
#define P_PWMEF_TIME_AB ((volatile uint32_t *)0xfe05c010)
#define P_PWMEF_A2 ((volatile uint32_t *)0xfe05c014)
#define P_PWMEF_B2 ((volatile uint32_t *)0xfe05c018)
#define P_PWMEF_BLINK_AB ((volatile uint32_t *)0xfe05c01c)
#define P_PWMEF_LOCK_AB ((volatile uint32_t *)0xfe05c020)
//========================================================================
//  PWM_GH - Registers
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe05e000
// -----------------------------------------------
#define P_PWMGH_PWM_A ((volatile uint32_t *)0xfe05e000)
#define P_PWMGH_PWM_B ((volatile uint32_t *)0xfe05e004)
#define P_PWMGH_MISC_REG_AB ((volatile uint32_t *)0xfe05e008)
#define P_PWMGH_DELTA_SIGMA_AB ((volatile uint32_t *)0xfe05e00c)
#define P_PWMGH_TIME_AB ((volatile uint32_t *)0xfe05e010)
#define P_PWMGH_A2 ((volatile uint32_t *)0xfe05e014)
#define P_PWMGH_B2 ((volatile uint32_t *)0xfe05e018)
#define P_PWMGH_BLINK_AB ((volatile uint32_t *)0xfe05e01c)
#define P_PWMGH_LOCK_AB ((volatile uint32_t *)0xfe05e020)
//========================================================================
//  PWM_IJ - Registers
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe060000
// -----------------------------------------------
#define P_PWMIJ_PWM_A ((volatile uint32_t *)0xfe060000)
#define P_PWMIJ_PWM_B ((volatile uint32_t *)0xfe060004)
#define P_PWMIJ_MISC_REG_AB ((volatile uint32_t *)0xfe060008)
#define P_PWMIJ_DELTA_SIGMA_AB ((volatile uint32_t *)0xfe06000c)
#define P_PWMIJ_TIME_AB ((volatile uint32_t *)0xfe060010)
#define P_PWMIJ_A2 ((volatile uint32_t *)0xfe060014)
#define P_PWMIJ_B2 ((volatile uint32_t *)0xfe060018)
#define P_PWMIJ_BLINK_AB ((volatile uint32_t *)0xfe06001c)
#define P_PWMIJ_LOCK_AB ((volatile uint32_t *)0xfe060020)
//========================================================================
//  SPICC_0
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe050000
// -----------------------------------------------
#define P_SPICC0_RXDATA ((volatile uint32_t *)0xfe050000)
#define P_SPICC0_TXDATA ((volatile uint32_t *)0xfe050004)
#define P_SPICC0_CONREG ((volatile uint32_t *)0xfe050008)
#define P_SPICC0_INTREG ((volatile uint32_t *)0xfe05000c)
#define P_SPICC0_DMAREG ((volatile uint32_t *)0xfe050010)
#define P_SPICC0_STATREG ((volatile uint32_t *)0xfe050014)
#define P_SPICC0_PERIODREG ((volatile uint32_t *)0xfe050018)
#define P_SPICC0_TESTREG ((volatile uint32_t *)0xfe05001c)
#define P_SPICC0_DRADDR ((volatile uint32_t *)0xfe050020)
#define P_SPICC0_DWADDR ((volatile uint32_t *)0xfe050024)
#define P_SPICC0_LD_CNTL0 ((volatile uint32_t *)0xfe050028)
#define P_SPICC0_LD_CNTL1 ((volatile uint32_t *)0xfe05002c)
#define P_SPICC0_LD_RADDR ((volatile uint32_t *)0xfe050030)
#define P_SPICC0_LD_WADDR ((volatile uint32_t *)0xfe050034)
#define P_SPICC0_ENHANCE_CNTL ((volatile uint32_t *)0xfe050038)
#define P_SPICC0_ENHANCE_CNTL1 ((volatile uint32_t *)0xfe05003c)
#define P_SPICC0_ENHANCE_CNTL2 ((volatile uint32_t *)0xfe050040)
//========================================================================
//  SPICC_1
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe052000
// -----------------------------------------------
#define P_SPICC1_RXDATA ((volatile uint32_t *)0xfe052000)
#define P_SPICC1_TXDATA ((volatile uint32_t *)0xfe052004)
#define P_SPICC1_CONREG ((volatile uint32_t *)0xfe052008)
#define P_SPICC1_INTREG ((volatile uint32_t *)0xfe05200c)
#define P_SPICC1_DMAREG ((volatile uint32_t *)0xfe052010)
#define P_SPICC1_STATREG ((volatile uint32_t *)0xfe052014)
#define P_SPICC1_PERIODREG ((volatile uint32_t *)0xfe052018)
#define P_SPICC1_TESTREG ((volatile uint32_t *)0xfe05201c)
#define P_SPICC1_DRADDR ((volatile uint32_t *)0xfe052020)
#define P_SPICC1_DWADDR ((volatile uint32_t *)0xfe052024)
#define P_SPICC1_LD_CNTL0 ((volatile uint32_t *)0xfe052028)
#define P_SPICC1_LD_CNTL1 ((volatile uint32_t *)0xfe05202c)
#define P_SPICC1_LD_RADDR ((volatile uint32_t *)0xfe052030)
#define P_SPICC1_LD_WADDR ((volatile uint32_t *)0xfe052034)
#define P_SPICC1_ENHANCE_CNTL ((volatile uint32_t *)0xfe052038)
#define P_SPICC1_ENHANCE_CNTL1 ((volatile uint32_t *)0xfe05203c)
#define P_SPICC1_ENHANCE_CNTL2 ((volatile uint32_t *)0xfe052040)
//========================================================================
//  AIFIFO - Registers
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe046000
// -----------------------------------------------
#define P_AIU_AIFIFO_CTRL ((volatile uint32_t *)0xfe046000)
#define P_AIU_AIFIFO_STATUS ((volatile uint32_t *)0xfe046004)
#define P_AIU_AIFIFO_GBIT ((volatile uint32_t *)0xfe046008)
#define P_AIU_AIFIFO_CLB ((volatile uint32_t *)0xfe04600c)
#define P_AIU_MEM_AIFIFO_START_PTR ((volatile uint32_t *)0xfe046010)
#define P_AIU_MEM_AIFIFO_CURR_PTR ((volatile uint32_t *)0xfe046014)
#define P_AIU_MEM_AIFIFO_END_PTR ((volatile uint32_t *)0xfe046018)
#define P_AIU_MEM_AIFIFO_BYTES_AVAIL ((volatile uint32_t *)0xfe04601c)
#define P_AIU_MEM_AIFIFO_CONTROL ((volatile uint32_t *)0xfe046020)
#define P_AIU_MEM_AIFIFO_MAN_WP ((volatile uint32_t *)0xfe046024)
#define P_AIU_MEM_AIFIFO_MAN_RP ((volatile uint32_t *)0xfe046028)
#define P_AIU_MEM_AIFIFO_LEVEL ((volatile uint32_t *)0xfe04602c)
#define P_AIU_MEM_AIFIFO_BUF_CNTL ((volatile uint32_t *)0xfe046030)
#define P_AIU_MEM_AIFIFO_BUF_WRAP_COUNT ((volatile uint32_t *)0xfe046034)
#define P_AIU_MEM_AIFIFO_MEM_CTL ((volatile uint32_t *)0xfe04603c)
#define P_AIFIFO_TIME_STAMP_CNTL ((volatile uint32_t *)0xfe046040)
#define P_AIFIFO_TIME_STAMP_SYNC_0 ((volatile uint32_t *)0xfe046044)
#define P_AIFIFO_TIME_STAMP_SYNC_1 ((volatile uint32_t *)0xfe046048)
#define P_AIFIFO_TIME_STAMP_0 ((volatile uint32_t *)0xfe04604c)
#define P_AIFIFO_TIME_STAMP_1 ((volatile uint32_t *)0xfe046050)
#define P_AIFIFO_TIME_STAMP_2 ((volatile uint32_t *)0xfe046054)
#define P_AIFIFO_TIME_STAMP_3 ((volatile uint32_t *)0xfe046058)
#define P_AIFIFO_TIME_STAMP_LENGTH ((volatile uint32_t *)0xfe04605c)
//========================================================================
//  MSR_CLK - Registers
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe048000
// -----------------------------------------------
#define P_MSR_CLK_REG0 ((volatile uint32_t *)0xfe048000)
#define P_MSR_CLK_REG1 ((volatile uint32_t *)0xfe048004)
#define P_MSR_CLK_REG2 ((volatile uint32_t *)0xfe048008)
#define P_MSR_CLK_REG3 ((volatile uint32_t *)0xfe04800c)
#define P_MSR_CLK_REG4 ((volatile uint32_t *)0xfe048010)
#define P_MSR_CLK_REG5 ((volatile uint32_t *)0xfe048014)
#define P_MSR_CLK_DUTY ((volatile uint32_t *)0xfe048018)
//========================================================================
//  SPIFC - Registers
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe056000
// -----------------------------------------------
#define P_SPI_FLASH_CMD ((volatile uint32_t *)0xfe056000)
// SPI_FLASH_READ    31
// SPI_FLASH_WREN    30
// SPI_FLASH_WRDI    29
// SPI_FLASH_RDID    28
// SPI_FLASH_RDSR    27
// SPI_FLASH_WRSR    26
// SPI_FLASH_PP      25
// SPI_FLASH_SE      24
// SPI_FLASH_BE      23
// SPI_FLASH_CE      22
// SPI_FLASH_DP      21
// SPI_FLASH_RES     20
// SPI_HPM           19
// SPI_FLASH_USR     18
// SPI_FLASH_USR_ADDR 15
// SPI_FLASH_USR_DUMMY 14
// SPI_FLASH_USR_DIN   13
// SPI_FLASH_USR_DOUT   12
// SPI_FLASH_USR_DUMMY_BLEN   10
// SPI_FLASH_USR_CMD     0
#define P_SPI_FLASH_ADDR ((volatile uint32_t *)0xfe056004)
// SPI_FLASH_BYTES_LEN 24
// SPI_FLASH_ADDR_START 0
#define P_SPI_FLASH_CTRL ((volatile uint32_t *)0xfe056008)
// SPI_ENABLE_AHB    17
// SPI_SST_AAI       16
// SPI_RES_RID       15
// SPI_FREAD_DUAL    14
// SPI_READ_READ_EN  13
// SPI_CLK_DIV0      12
// SPI_CLKCNT_N      8
// SPI_CLKCNT_H      4
// SPI_CLKCNT_L      0
#define P_SPI_FLASH_CTRL1 ((volatile uint32_t *)0xfe05600c)
#define P_SPI_FLASH_STATUS ((volatile uint32_t *)0xfe056010)
#define P_SPI_FLASH_CTRL2 ((volatile uint32_t *)0xfe056014)
#define P_SPI_FLASH_CLOCK ((volatile uint32_t *)0xfe056018)
#define P_SPI_FLASH_USER ((volatile uint32_t *)0xfe05601c)
#define P_SPI_FLASH_USER1 ((volatile uint32_t *)0xfe056020)
#define P_SPI_FLASH_USER2 ((volatile uint32_t *)0xfe056024)
#define P_SPI_FLASH_USER3 ((volatile uint32_t *)0xfe056028)
#define P_SPI_FLASH_USER4 ((volatile uint32_t *)0xfe05602c)
#define P_SPI_FLASH_SLAVE ((volatile uint32_t *)0xfe056030)
#define P_SPI_FLASH_SLAVE1 ((volatile uint32_t *)0xfe056034)
#define P_SPI_FLASH_SLAVE2 ((volatile uint32_t *)0xfe056038)
#define P_SPI_FLASH_SLAVE3 ((volatile uint32_t *)0xfe05603c)
#define P_SPI_FLASH_C0 ((volatile uint32_t *)0xfe056040)
#define P_SPI_FLASH_C1 ((volatile uint32_t *)0xfe056044)
#define P_SPI_FLASH_C2 ((volatile uint32_t *)0xfe056048)
#define P_SPI_FLASH_C3 ((volatile uint32_t *)0xfe05604c)
#define P_SPI_FLASH_C4 ((volatile uint32_t *)0xfe056050)
#define P_SPI_FLASH_C5 ((volatile uint32_t *)0xfe056054)
#define P_SPI_FLASH_C6 ((volatile uint32_t *)0xfe056058)
#define P_SPI_FLASH_C7 ((volatile uint32_t *)0xfe05605c)
#define P_SPI_FLASH_B8 ((volatile uint32_t *)0xfe056060)
#define P_SPI_FLASH_B9 ((volatile uint32_t *)0xfe056064)
#define P_SPI_FLASH_B10 ((volatile uint32_t *)0xfe056068)
#define P_SPI_FLASH_B11 ((volatile uint32_t *)0xfe05606c)
#define P_SPI_FLASH_B12 ((volatile uint32_t *)0xfe056070)
#define P_SPI_FLASH_B13 ((volatile uint32_t *)0xfe056074)
#define P_SPI_FLASH_B14 ((volatile uint32_t *)0xfe056078)
#define P_SPI_FLASH_B15 ((volatile uint32_t *)0xfe05607c)
//========================================================================
//  CEC - Registers
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe044000
// -----------------------------------------------
#define P_CECA_GEN_CNTL ((volatile uint32_t *)0xfe044000)
#define P_CECA_RW_REG ((volatile uint32_t *)0xfe044004)
#define P_CECA_INTR_MASKN ((volatile uint32_t *)0xfe044008)
#define P_CECA_INTR_CLR ((volatile uint32_t *)0xfe04400c)
#define P_CECA_INTR_STAT ((volatile uint32_t *)0xfe044010)
#define P_CECB_GEN_CNTL ((volatile uint32_t *)0xfe044040)
#define P_CECB_RW_REG ((volatile uint32_t *)0xfe044044)
#define P_CECB_INTR_MASKN ((volatile uint32_t *)0xfe044048)
#define P_CECB_INTR_CLR ((volatile uint32_t *)0xfe04404c)
#define P_CECB_INTR_STAT ((volatile uint32_t *)0xfe044050)
//========================================================================
//  SMART CARD - Registers
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe038000
// -----------------------------------------------
#define P_SMARTCARD_REG0 ((volatile uint32_t *)0xfe038000)
#define P_SMARTCARD_REG1 ((volatile uint32_t *)0xfe038004)
#define P_SMARTCARD_REG2 ((volatile uint32_t *)0xfe038008)
#define P_SMARTCARD_STATUS ((volatile uint32_t *)0xfe03800c)
#define P_SMARTCARD_INTR ((volatile uint32_t *)0xfe038010)
#define P_SMARTCARD_REG5 ((volatile uint32_t *)0xfe038014)
#define P_SMARTCARD_REG6 ((volatile uint32_t *)0xfe038018)
#define P_SMARTCARD_FIFO ((volatile uint32_t *)0xfe03801c)
#define P_SMARTCARD_REG8 ((volatile uint32_t *)0xfe038020)
//========================================================================
//  CAPU
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe012000
// -----------------------------------------------
#define P_CAPU_ACCESS_EN_AHB_NNA ((volatile uint32_t *)0xfe01230c)
#define P_CAPU_ACCESS_EN_AHB_ETH ((volatile uint32_t *)0xfe012308)
#define P_CAPU_ACCESS_EN_AHB_USB0 ((volatile uint32_t *)0xfe012304)
#define P_CAPU_ACCESS_EN_AHB_USB1 ((volatile uint32_t *)0xfe012300)
#define P_CAPU_ACCESS_EN_16M_SLOT0 ((volatile uint32_t *)0xfe0122c0)
#define P_CAPU_ACCESS_EN_256K_SLOT1 ((volatile uint32_t *)0xfe012284)
#define P_CAPU_ACCESS_EN_256K_SLOT0 ((volatile uint32_t *)0xfe012280)
#define P_CAPU_ACCESS_EN_64K_SLOT5 ((volatile uint32_t *)0xfe012214)
#define P_CAPU_ACCESS_EN_64K_SLOT4 ((volatile uint32_t *)0xfe012210)
#define P_CAPU_ACCESS_EN_64K_SLOT3 ((volatile uint32_t *)0xfe01220c)
#define P_CAPU_ACCESS_EN_64K_SLOT2 ((volatile uint32_t *)0xfe012208)
#define P_CAPU_ACCESS_EN_64K_SLOT1 ((volatile uint32_t *)0xfe012204)
#define P_CAPU_ACCESS_EN_64K_SLOT0 ((volatile uint32_t *)0xfe012200)
#define P_CAPU_ACCESS_EN_8K_SLOT4F ((volatile uint32_t *)0xfe01213c)
#define P_CAPU_ACCESS_EN_8K_SLOT4E ((volatile uint32_t *)0xfe012138)
#define P_CAPU_ACCESS_EN_8K_SLOT4D ((volatile uint32_t *)0xfe012134)
#define P_CAPU_ACCESS_EN_8K_SLOT4C ((volatile uint32_t *)0xfe012130)
#define P_CAPU_ACCESS_EN_8K_SLOT4B ((volatile uint32_t *)0xfe01212c)
#define P_CAPU_ACCESS_EN_8K_SLOT4A ((volatile uint32_t *)0xfe012128)
#define P_CAPU_ACCESS_EN_8K_SLOT49 ((volatile uint32_t *)0xfe012124)
#define P_CAPU_ACCESS_EN_8K_SLOT48 ((volatile uint32_t *)0xfe012120)
#define P_CAPU_ACCESS_EN_8K_SLOT47 ((volatile uint32_t *)0xfe01211c)
#define P_CAPU_ACCESS_EN_8K_SLOT46 ((volatile uint32_t *)0xfe012118)
#define P_CAPU_ACCESS_EN_8K_SLOT45 ((volatile uint32_t *)0xfe012114)
#define P_CAPU_ACCESS_EN_8K_SLOT44 ((volatile uint32_t *)0xfe012110)
#define P_CAPU_ACCESS_EN_8K_SLOT43 ((volatile uint32_t *)0xfe01210c)
#define P_CAPU_ACCESS_EN_8K_SLOT42 ((volatile uint32_t *)0xfe012108)
#define P_CAPU_ACCESS_EN_8K_SLOT41 ((volatile uint32_t *)0xfe012104)
#define P_CAPU_ACCESS_EN_8K_SLOT40 ((volatile uint32_t *)0xfe012100)
#define P_CAPU_ACCESS_EN_8K_SLOT3F ((volatile uint32_t *)0xfe0120fc)
#define P_CAPU_ACCESS_EN_8K_SLOT3E ((volatile uint32_t *)0xfe0120f8)
#define P_CAPU_ACCESS_EN_8K_SLOT3D ((volatile uint32_t *)0xfe0120f4)
#define P_CAPU_ACCESS_EN_8K_SLOT3C ((volatile uint32_t *)0xfe0120f0)
#define P_CAPU_ACCESS_EN_8K_SLOT3B ((volatile uint32_t *)0xfe0120ec)
#define P_CAPU_ACCESS_EN_8K_SLOT3A ((volatile uint32_t *)0xfe0120e8)
#define P_CAPU_ACCESS_EN_8K_SLOT39 ((volatile uint32_t *)0xfe0120e4)
#define P_CAPU_ACCESS_EN_8K_SLOT38 ((volatile uint32_t *)0xfe0120e0)
#define P_CAPU_ACCESS_EN_8K_SLOT37 ((volatile uint32_t *)0xfe0120dc)
#define P_CAPU_ACCESS_EN_8K_SLOT36 ((volatile uint32_t *)0xfe0120d8)
#define P_CAPU_ACCESS_EN_8K_SLOT35 ((volatile uint32_t *)0xfe0120d4)
#define P_CAPU_ACCESS_EN_8K_SLOT34 ((volatile uint32_t *)0xfe0120d0)
#define P_CAPU_ACCESS_EN_8K_SLOT33 ((volatile uint32_t *)0xfe0120cc)
#define P_CAPU_ACCESS_EN_8K_SLOT32 ((volatile uint32_t *)0xfe0120c8)
#define P_CAPU_ACCESS_EN_8K_SLOT31 ((volatile uint32_t *)0xfe0120c4)
#define P_CAPU_ACCESS_EN_8K_SLOT30 ((volatile uint32_t *)0xfe0120c0)
#define P_CAPU_ACCESS_EN_8K_SLOT2F ((volatile uint32_t *)0xfe0120bc)
#define P_CAPU_ACCESS_EN_8K_SLOT2E ((volatile uint32_t *)0xfe0120b8)
#define P_CAPU_ACCESS_EN_8K_SLOT2D ((volatile uint32_t *)0xfe0120b4)
#define P_CAPU_ACCESS_EN_8K_SLOT2C ((volatile uint32_t *)0xfe0120b0)
#define P_CAPU_ACCESS_EN_8K_SLOT2B ((volatile uint32_t *)0xfe0120ac)
#define P_CAPU_ACCESS_EN_8K_SLOT2A ((volatile uint32_t *)0xfe0120a8)
#define P_CAPU_ACCESS_EN_8K_SLOT29 ((volatile uint32_t *)0xfe0120a4)
#define P_CAPU_ACCESS_EN_8K_SLOT28 ((volatile uint32_t *)0xfe0120a0)
#define P_CAPU_ACCESS_EN_8K_SLOT27 ((volatile uint32_t *)0xfe01209c)
#define P_CAPU_ACCESS_EN_8K_SLOT26 ((volatile uint32_t *)0xfe012098)
#define P_CAPU_ACCESS_EN_8K_SLOT25 ((volatile uint32_t *)0xfe012094)
#define P_CAPU_ACCESS_EN_8K_SLOT24 ((volatile uint32_t *)0xfe012090)
#define P_CAPU_ACCESS_EN_8K_SLOT23 ((volatile uint32_t *)0xfe01208c)
#define P_CAPU_ACCESS_EN_8K_SLOT22 ((volatile uint32_t *)0xfe012088)
#define P_CAPU_ACCESS_EN_8K_SLOT21 ((volatile uint32_t *)0xfe012084)
#define P_CAPU_ACCESS_EN_8K_SLOT20 ((volatile uint32_t *)0xfe012080)
#define P_CAPU_ACCESS_EN_8K_SLOT1F ((volatile uint32_t *)0xfe01207c)
#define P_CAPU_ACCESS_EN_8K_SLOT1E ((volatile uint32_t *)0xfe012078)
#define P_CAPU_ACCESS_EN_8K_SLOT1D ((volatile uint32_t *)0xfe012074)
#define P_CAPU_ACCESS_EN_8K_SLOT1C ((volatile uint32_t *)0xfe012070)
#define P_CAPU_ACCESS_EN_8K_SLOT1B ((volatile uint32_t *)0xfe01206c)
#define P_CAPU_ACCESS_EN_8K_SLOT1A ((volatile uint32_t *)0xfe012068)
#define P_CAPU_ACCESS_EN_8K_SLOT19 ((volatile uint32_t *)0xfe012064)
#define P_CAPU_ACCESS_EN_8K_SLOT18 ((volatile uint32_t *)0xfe012060)
#define P_CAPU_ACCESS_EN_8K_SLOT17 ((volatile uint32_t *)0xfe01205c)
#define P_CAPU_ACCESS_EN_8K_SLOT16 ((volatile uint32_t *)0xfe012058)
#define P_CAPU_ACCESS_EN_8K_SLOT15 ((volatile uint32_t *)0xfe012054)
#define P_CAPU_ACCESS_EN_8K_SLOT14 ((volatile uint32_t *)0xfe012050)
#define P_CAPU_ACCESS_EN_8K_SLOT13 ((volatile uint32_t *)0xfe01204c)
#define P_CAPU_ACCESS_EN_8K_SLOT12 ((volatile uint32_t *)0xfe012048)
#define P_CAPU_ACCESS_EN_8K_SLOT11 ((volatile uint32_t *)0xfe012044)
#define P_CAPU_ACCESS_EN_8K_SLOT10 ((volatile uint32_t *)0xfe012040)
#define P_CAPU_ACCESS_EN_8K_SLOT0F ((volatile uint32_t *)0xfe01203c)
#define P_CAPU_ACCESS_EN_8K_SLOT0E ((volatile uint32_t *)0xfe012038)
#define P_CAPU_ACCESS_EN_8K_SLOT0D ((volatile uint32_t *)0xfe012034)
#define P_CAPU_ACCESS_EN_8K_SLOT0C ((volatile uint32_t *)0xfe012030)
#define P_CAPU_ACCESS_EN_8K_SLOT0B ((volatile uint32_t *)0xfe01202c)
#define P_CAPU_ACCESS_EN_8K_SLOT0A ((volatile uint32_t *)0xfe012028)
#define P_CAPU_ACCESS_EN_8K_SLOT09 ((volatile uint32_t *)0xfe012024)
#define P_CAPU_ACCESS_EN_8K_SLOT08 ((volatile uint32_t *)0xfe012020)
#define P_CAPU_ACCESS_EN_8K_SLOT07 ((volatile uint32_t *)0xfe01201c)
#define P_CAPU_ACCESS_EN_8K_SLOT06 ((volatile uint32_t *)0xfe012018)
#define P_CAPU_ACCESS_EN_8K_SLOT05 ((volatile uint32_t *)0xfe012014)
#define P_CAPU_ACCESS_EN_8K_SLOT04 ((volatile uint32_t *)0xfe012010)
#define P_CAPU_ACCESS_EN_8K_SLOT03 ((volatile uint32_t *)0xfe01200c)
#define P_CAPU_ACCESS_EN_8K_SLOT02 ((volatile uint32_t *)0xfe012008)
#define P_CAPU_ACCESS_EN_8K_SLOT01 ((volatile uint32_t *)0xfe012004)
#define P_CAPU_ACCESS_EN_8K_SLOT00 ((volatile uint32_t *)0xfe012000)
//========================================================================
//  BT656
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe030000
// -----------------------------------------------
#define P_BT_CTRL ((volatile uint32_t *)0xfe030000)
#define BT_SOFT_RESET 31 // Soft reset
#define BT_JPEG_START 30
#define BT_JPEG_IGNORE_BYTES 18 // 20:18
#define BT_JPEG_IGNORE_LAST 17
#define BT_UPDATE_ST_SEL 16
#define BT_COLOR_REPEAT 15
#define BT_VIDEO_MODE 13 // 14:13
#define BT_AUTO_FMT 12
#define BT_PROG_MODE 11
#define BT_JPEG_MODE 10
#define BT_XCLK27_EN_BIT 9 // 1 : xclk27 is input.     0 : xclk27 is output.
#define BT_FID_EN_BIT 8 // 1 : enable use FID port.
#define BT_CLK27_SEL_BIT 7 // 1 : external xclk27      0 : internal clk27.
#define BT_CLK27_PHASE_BIT 6 // 1 : no inverted          0 : inverted.
#define BT_ACE_MODE_BIT 5 // 1 : auto cover error by hardware.
#define BT_SLICE_MODE_BIT 4 // 1 : no ancillay flag     0 : with ancillay flag.
#define BT_FMT_MODE_BIT 3 // 1 : ntsc                 0 : pal.
#define BT_REF_MODE_BIT 2 // 1 : from bit stream.     0 : from ports.
#define BT_MODE_BIT 1 // 1 : BT656 model          0 : SAA7118 mode.
#define BT_EN_BIT 0 // 1 : enable.
#define P_BT_VBISTART ((volatile uint32_t *)0xfe030004)
#define P_BT_VBIEND ((volatile uint32_t *)0xfe030008)
#define P_BT_FIELDSADR ((volatile uint32_t *)0xfe03000c)
#define P_BT_LINECTRL ((volatile uint32_t *)0xfe030010)
#define P_BT_VIDEOSTART ((volatile uint32_t *)0xfe030014)
#define P_BT_VIDEOEND ((volatile uint32_t *)0xfe030018)
#define P_BT_SLICELINE0 ((volatile uint32_t *)0xfe03001c)
#define P_BT_SLICELINE1 ((volatile uint32_t *)0xfe030020)
#define P_BT_PORT_CTRL ((volatile uint32_t *)0xfe030024)
#define BT_HSYNC_PHASE 0
#define BT_VSYNC_PHASE 1
#define BT_HSYNC_PULSE 2
#define BT_VSYNC_PULSE 3
#define BT_FID_PHASE 4
#define BT_FID_HSVS 5
#define BT_IDQ_EN 6
#define BT_IDQ_PHASE 7
#define BT_D8B 8
#define BT_10BTO8B 9
#define BT_FID_DELAY 10 // 12:10
#define BT_VSYNC_DELAY 13 //
#define BT_HSYNC_DELAY 16
#define BT_FID_HSVS_PCNT 19
#define BT_FID_HSVS_VS_RISING 20
#define BT_FID_HSVS_VS_FALLING 21
#define BT_VREF_FROM_VS_ONLY 22
#define BT_PORT_ACTIVE_HMODE 23
#define BT_DUAL_EDGE_CLK_EN 24
#define BT_CLK_INV_SEL 25
#define BT_DATA_ENDIAN 26
#define P_BT_SWAP_CTRL ((volatile uint32_t *)0xfe030028)
#define P_BT_601_CTRL0 ((volatile uint32_t *)0xfe030038)
#define P_BT_601_CTRL1 ((volatile uint32_t *)0xfe03003c)
#define P_BT_601_CTRL2 ((volatile uint32_t *)0xfe030040)
#define P_BT_601_CTRL3 ((volatile uint32_t *)0xfe030044)
#define P_BT_FIELD_LUMA ((volatile uint32_t *)0xfe030048)
#define P_BT_RAW_CTRL ((volatile uint32_t *)0xfe03004c)
#define P_BT_STATUS ((volatile uint32_t *)0xfe030050)
#define P_BT_INT_CTRL ((volatile uint32_t *)0xfe030054)
#define P_BT_VLINE_STATUS ((volatile uint32_t *)0xfe03005c)
#define P_BT_ERR_CNT ((volatile uint32_t *)0xfe030064)
#define P_BT_LCNT_STATUS ((volatile uint32_t *)0xfe030068)
#define P_BT_PCNT_STATUS ((volatile uint32_t *)0xfe030070)
#define P_BT_DELAY_CTRL ((volatile uint32_t *)0xfe030074)
#define P_BT_REF_000 ((volatile uint32_t *)0xfe030080)
#define P_BT_REF_001 ((volatile uint32_t *)0xfe030084)
#define P_BT_REF_010 ((volatile uint32_t *)0xfe030088)
#define P_BT_REF_011 ((volatile uint32_t *)0xfe03008c)
#define P_BT_REF_100 ((volatile uint32_t *)0xfe030090)
#define P_BT_REF_101 ((volatile uint32_t *)0xfe030094)
#define P_BT_REF_110 ((volatile uint32_t *)0xfe030098)
#define P_BT_REF_111 ((volatile uint32_t *)0xfe03009c)
//========================================================================
//  PDM
//========================================================================
//`include "../audio/rtl/pdm_reg.vh"
//
// Reading file:  REG_LIST_AUDIO_RTL.h
//
//========================================================================
//  AUDIO - Registers
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe330000
// -----------------------------------------------
#define P_EE_AUDIO_CLK_GATE_EN0 ((volatile uint32_t *)0xfe330000)
#define P_EE_AUDIO_CLK_GATE_EN1 ((volatile uint32_t *)0xfe330004)
#define P_EE_AUDIO_MCLK_A_CTRL ((volatile uint32_t *)0xfe330008)
#define P_EE_AUDIO_MCLK_B_CTRL ((volatile uint32_t *)0xfe33000c)
#define P_EE_AUDIO_MCLK_C_CTRL ((volatile uint32_t *)0xfe330010)
#define P_EE_AUDIO_MCLK_D_CTRL ((volatile uint32_t *)0xfe330014)
#define P_EE_AUDIO_MCLK_E_CTRL ((volatile uint32_t *)0xfe330018)
#define P_EE_AUDIO_MCLK_F_CTRL ((volatile uint32_t *)0xfe33001c)
#define P_EE_AUDIO_SW_RESET0 ((volatile uint32_t *)0xfe330028)
#define P_EE_AUDIO_SW_RESET1 ((volatile uint32_t *)0xfe33002c)
#define P_EE_AUDIO_CLK81_CTRL ((volatile uint32_t *)0xfe330030)
#define P_EE_AUDIO_CLK81_EN ((volatile uint32_t *)0xfe330034)
#define P_EE_AUDIO_MCLK_CTRL ((volatile uint32_t *)0xfe330038)
#define P_EE_AUDIO_MST_A_SCLK_CTRL0 ((volatile uint32_t *)0xfe330040)
#define P_EE_AUDIO_MST_A_SCLK_CTRL1 ((volatile uint32_t *)0xfe330044)
#define P_EE_AUDIO_MST_B_SCLK_CTRL0 ((volatile uint32_t *)0xfe330048)
#define P_EE_AUDIO_MST_B_SCLK_CTRL1 ((volatile uint32_t *)0xfe33004c)
#define P_EE_AUDIO_MST_C_SCLK_CTRL0 ((volatile uint32_t *)0xfe330050)
#define P_EE_AUDIO_MST_C_SCLK_CTRL1 ((volatile uint32_t *)0xfe330054)
#define P_EE_AUDIO_MST_D_SCLK_CTRL0 ((volatile uint32_t *)0xfe330058)
#define P_EE_AUDIO_MST_D_SCLK_CTRL1 ((volatile uint32_t *)0xfe33005c)
#define P_EE_AUDIO_MST_E_SCLK_CTRL0 ((volatile uint32_t *)0xfe330060)
#define P_EE_AUDIO_MST_E_SCLK_CTRL1 ((volatile uint32_t *)0xfe330064)
#define P_EE_AUDIO_MST_F_SCLK_CTRL0 ((volatile uint32_t *)0xfe330068)
#define P_EE_AUDIO_MST_F_SCLK_CTRL1 ((volatile uint32_t *)0xfe33006c)
#define P_EE_AUDIO_MST_DLY_CTRL0 ((volatile uint32_t *)0xfe330070)
#define P_EE_AUDIO_MST_DLY_CTRL1 ((volatile uint32_t *)0xfe330074)
#define P_EE_AUDIO_CLK_TDMIN_A_CTRL ((volatile uint32_t *)0xfe330080)
#define P_EE_AUDIO_CLK_TDMIN_B_CTRL ((volatile uint32_t *)0xfe330084)
#define P_EE_AUDIO_CLK_TDMIN_C_CTRL ((volatile uint32_t *)0xfe330088)
#define P_EE_AUDIO_CLK_TDMIN_LB_CTRL ((volatile uint32_t *)0xfe33008c)
#define P_EE_AUDIO_CLK_TDMOUT_A_CTRL ((volatile uint32_t *)0xfe330090)
#define P_EE_AUDIO_CLK_TDMOUT_B_CTRL ((volatile uint32_t *)0xfe330094)
#define P_EE_AUDIO_CLK_TDMOUT_C_CTRL ((volatile uint32_t *)0xfe330098)
#define P_EE_AUDIO_CLK_SPDIFIN_CTRL ((volatile uint32_t *)0xfe33009c)
#define P_EE_AUDIO_CLK_SPDIFOUT_CTRL ((volatile uint32_t *)0xfe3300a0)
#define P_EE_AUDIO_CLK_RESAMPLEA_CTRL ((volatile uint32_t *)0xfe3300a4)
#define P_EE_AUDIO_CLK_LOCKER_CTRL ((volatile uint32_t *)0xfe3300a8)
#define P_EE_AUDIO_CLK_PDMIN_CTRL0 ((volatile uint32_t *)0xfe3300ac)
#define P_EE_AUDIO_CLK_PDMIN_CTRL1 ((volatile uint32_t *)0xfe3300b0)
#define P_EE_AUDIO_CLK_SPDIFOUT_B_CTRL ((volatile uint32_t *)0xfe3300b4)
#define P_EE_AUDIO_CLK_RESAMPLEB_CTRL ((volatile uint32_t *)0xfe3300b8)
#define P_EE_AUDIO_CLK_SPDIFIN_LB_CTRL ((volatile uint32_t *)0xfe3300bc)
#define P_EE_AUDIO_CLK_EQDRC_CTRL0 ((volatile uint32_t *)0xfe3300c0)
#define P_EE_AUDIO_VAD_CLK_CTRL ((volatile uint32_t *)0xfe3300c4)
#define P_EE_AUDIO_EARCTX_CMDC_CLK_CTRL ((volatile uint32_t *)0xfe3300c8)
#define P_EE_AUDIO_EARCTX_DMAC_CLK_CTRL ((volatile uint32_t *)0xfe3300cc)
#define P_EE_AUDIO_EARCRX_CMDC_CLK_CTRL ((volatile uint32_t *)0xfe3300d0)
#define P_EE_AUDIO_EARCRX_DMAC_CLK_CTRL ((volatile uint32_t *)0xfe3300d4)
#define P_EE_AUDIO_CLK_LOCKERB_CTRL ((volatile uint32_t *)0xfe3300d8)
#define P_EE_AUDIO_CLK_TDMINB_LB_CTRL ((volatile uint32_t *)0xfe3300dc)
#define P_EE_AUDIO_CLK_PDMIN_CTRL2 ((volatile uint32_t *)0xfe3300e0)
#define P_EE_AUDIO_CLK_PDMIN_CTRL3 ((volatile uint32_t *)0xfe3300e4)
#define P_EE_AUDIO_CLK_TDMIN_D_CTRL ((volatile uint32_t *)0xfe3300e8)
#define P_EE_AUDIO_CLK_TDMOUT_D_CTRL ((volatile uint32_t *)0xfe3300ec)
#define P_EE_AUDIO_TODDR_A_CTRL0 ((volatile uint32_t *)0xfe330100)
#define P_EE_AUDIO_TODDR_A_CTRL1 ((volatile uint32_t *)0xfe330104)
#define P_EE_AUDIO_TODDR_A_START_ADDR ((volatile uint32_t *)0xfe330108)
#define P_EE_AUDIO_TODDR_A_FINISH_ADDR ((volatile uint32_t *)0xfe33010c)
#define P_EE_AUDIO_TODDR_A_INT_ADDR ((volatile uint32_t *)0xfe330110)
#define P_EE_AUDIO_TODDR_A_STATUS1 ((volatile uint32_t *)0xfe330114)
#define P_EE_AUDIO_TODDR_A_STATUS2 ((volatile uint32_t *)0xfe330118)
#define P_EE_AUDIO_TODDR_A_START_ADDRB ((volatile uint32_t *)0xfe33011c)
#define P_EE_AUDIO_TODDR_A_FINISH_ADDRB ((volatile uint32_t *)0xfe330120)
#define P_EE_AUDIO_TODDR_A_INIT_ADDR ((volatile uint32_t *)0xfe330124)
#define P_EE_AUDIO_TODDR_A_CTRL2 ((volatile uint32_t *)0xfe330128)
#define P_EE_AUDIO_TODDR_B_CTRL0 ((volatile uint32_t *)0xfe330140)
#define P_EE_AUDIO_TODDR_B_CTRL1 ((volatile uint32_t *)0xfe330144)
#define P_EE_AUDIO_TODDR_B_START_ADDR ((volatile uint32_t *)0xfe330148)
#define P_EE_AUDIO_TODDR_B_FINISH_ADDR ((volatile uint32_t *)0xfe33014c)
#define P_EE_AUDIO_TODDR_B_INT_ADDR ((volatile uint32_t *)0xfe330150)
#define P_EE_AUDIO_TODDR_B_STATUS1 ((volatile uint32_t *)0xfe330154)
#define P_EE_AUDIO_TODDR_B_STATUS2 ((volatile uint32_t *)0xfe330158)
#define P_EE_AUDIO_TODDR_B_START_ADDRB ((volatile uint32_t *)0xfe33015c)
#define P_EE_AUDIO_TODDR_B_FINISH_ADDRB ((volatile uint32_t *)0xfe330160)
#define P_EE_AUDIO_TODDR_B_INIT_ADDR ((volatile uint32_t *)0xfe330164)
#define P_EE_AUDIO_TODDR_B_CTRL2 ((volatile uint32_t *)0xfe330168)
#define P_EE_AUDIO_TODDR_C_CTRL0 ((volatile uint32_t *)0xfe330180)
#define P_EE_AUDIO_TODDR_C_CTRL1 ((volatile uint32_t *)0xfe330184)
#define P_EE_AUDIO_TODDR_C_START_ADDR ((volatile uint32_t *)0xfe330188)
#define P_EE_AUDIO_TODDR_C_FINISH_ADDR ((volatile uint32_t *)0xfe33018c)
#define P_EE_AUDIO_TODDR_C_INT_ADDR ((volatile uint32_t *)0xfe330190)
#define P_EE_AUDIO_TODDR_C_STATUS1 ((volatile uint32_t *)0xfe330194)
#define P_EE_AUDIO_TODDR_C_STATUS2 ((volatile uint32_t *)0xfe330198)
#define P_EE_AUDIO_TODDR_C_START_ADDRB ((volatile uint32_t *)0xfe33019c)
#define P_EE_AUDIO_TODDR_C_FINISH_ADDRB ((volatile uint32_t *)0xfe3301a0)
#define P_EE_AUDIO_TODDR_C_INIT_ADDR ((volatile uint32_t *)0xfe3301a4)
#define P_EE_AUDIO_TODDR_C_CTRL2 ((volatile uint32_t *)0xfe3301a8)
#define P_EE_AUDIO_FRDDR_A_CTRL0 ((volatile uint32_t *)0xfe3301c0)
#define P_EE_AUDIO_FRDDR_A_CTRL1 ((volatile uint32_t *)0xfe3301c4)
#define P_EE_AUDIO_FRDDR_A_START_ADDR ((volatile uint32_t *)0xfe3301c8)
#define P_EE_AUDIO_FRDDR_A_FINISH_ADDR ((volatile uint32_t *)0xfe3301cc)
#define P_EE_AUDIO_FRDDR_A_INT_ADDR ((volatile uint32_t *)0xfe3301d0)
#define P_EE_AUDIO_FRDDR_A_STATUS1 ((volatile uint32_t *)0xfe3301d4)
#define P_EE_AUDIO_FRDDR_A_STATUS2 ((volatile uint32_t *)0xfe3301d8)
#define P_EE_AUDIO_FRDDR_A_START_ADDRB ((volatile uint32_t *)0xfe3301dc)
#define P_EE_AUDIO_FRDDR_A_FINISH_ADDRB ((volatile uint32_t *)0xfe3301e0)
#define P_EE_AUDIO_FRDDR_A_INIT_ADDR ((volatile uint32_t *)0xfe3301e4)
#define P_EE_AUDIO_FRDDR_A_CTRL2 ((volatile uint32_t *)0xfe3301e8)
#define P_EE_AUDIO_FRDDR_B_CTRL0 ((volatile uint32_t *)0xfe330200)
#define P_EE_AUDIO_FRDDR_B_CTRL1 ((volatile uint32_t *)0xfe330204)
#define P_EE_AUDIO_FRDDR_B_START_ADDR ((volatile uint32_t *)0xfe330208)
#define P_EE_AUDIO_FRDDR_B_FINISH_ADDR ((volatile uint32_t *)0xfe33020c)
#define P_EE_AUDIO_FRDDR_B_INT_ADDR ((volatile uint32_t *)0xfe330210)
#define P_EE_AUDIO_FRDDR_B_STATUS1 ((volatile uint32_t *)0xfe330214)
#define P_EE_AUDIO_FRDDR_B_STATUS2 ((volatile uint32_t *)0xfe330218)
#define P_EE_AUDIO_FRDDR_B_START_ADDRB ((volatile uint32_t *)0xfe33021c)
#define P_EE_AUDIO_FRDDR_B_FINISH_ADDRB ((volatile uint32_t *)0xfe330220)
#define P_EE_AUDIO_FRDDR_B_INIT_ADDR ((volatile uint32_t *)0xfe330224)
#define P_EE_AUDIO_FRDDR_B_CTRL2 ((volatile uint32_t *)0xfe330228)
#define P_EE_AUDIO_FRDDR_C_CTRL0 ((volatile uint32_t *)0xfe330240)
#define P_EE_AUDIO_FRDDR_C_CTRL1 ((volatile uint32_t *)0xfe330244)
#define P_EE_AUDIO_FRDDR_C_START_ADDR ((volatile uint32_t *)0xfe330248)
#define P_EE_AUDIO_FRDDR_C_FINISH_ADDR ((volatile uint32_t *)0xfe33024c)
#define P_EE_AUDIO_FRDDR_C_INT_ADDR ((volatile uint32_t *)0xfe330250)
#define P_EE_AUDIO_FRDDR_C_STATUS1 ((volatile uint32_t *)0xfe330254)
#define P_EE_AUDIO_FRDDR_C_STATUS2 ((volatile uint32_t *)0xfe330258)
#define P_EE_AUDIO_FRDDR_C_START_ADDRB ((volatile uint32_t *)0xfe33025c)
#define P_EE_AUDIO_FRDDR_C_FINISH_ADDRB ((volatile uint32_t *)0xfe330260)
#define P_EE_AUDIO_FRDDR_C_INIT_ADDR ((volatile uint32_t *)0xfe330264)
#define P_EE_AUDIO_FRDDR_C_CTRL2 ((volatile uint32_t *)0xfe330268)
//`define EE_AUDIO_ARB_CTRL0              10'ha0
//`define EE_AUDIO_ARB_CTRL1              10'ha1
//`define EE_AUDIO_ARB_STS                10'ha8
#define P_EE_AUDIO_AM2AXI_CTRL0 ((volatile uint32_t *)0xfe330288)
#define P_EE_AUDIO_AM2AXI_CTRL1 ((volatile uint32_t *)0xfe33028c)
#define P_EE_AUDIO_AXI_ASYNC_CTRL0 ((volatile uint32_t *)0xfe330290)
#define P_EE_AUDIO_AM2AXI_STS ((volatile uint32_t *)0xfe3302a4)
#define P_EE_AUDIO_AXI_ASYNC_STS ((volatile uint32_t *)0xfe3302a8)
#define P_EE_AUDIO_LB_A_CTRL0 ((volatile uint32_t *)0xfe3302c0)
#define P_EE_AUDIO_LB_A_CTRL1 ((volatile uint32_t *)0xfe3302c4)
#define P_EE_AUDIO_LB_A_CTRL2 ((volatile uint32_t *)0xfe3302c8)
#define P_EE_AUDIO_LB_A_CTRL3 ((volatile uint32_t *)0xfe3302cc)
#define P_EE_AUDIO_LB_A_DAT_CH_ID0 ((volatile uint32_t *)0xfe3302d0)
#define P_EE_AUDIO_LB_A_DAT_CH_ID1 ((volatile uint32_t *)0xfe3302d4)
#define P_EE_AUDIO_LB_A_DAT_CH_ID2 ((volatile uint32_t *)0xfe3302d8)
#define P_EE_AUDIO_LB_A_DAT_CH_ID3 ((volatile uint32_t *)0xfe3302dc)
#define P_EE_AUDIO_LB_A_LB_CH_ID0 ((volatile uint32_t *)0xfe3302e0)
#define P_EE_AUDIO_LB_A_LB_CH_ID1 ((volatile uint32_t *)0xfe3302e4)
#define P_EE_AUDIO_LB_A_LB_CH_ID2 ((volatile uint32_t *)0xfe3302e8)
#define P_EE_AUDIO_LB_A_LB_CH_ID3 ((volatile uint32_t *)0xfe3302ec)
#define P_EE_AUDIO_LB_A_STS ((volatile uint32_t *)0xfe3302f0)
#define P_EE_AUDIO_LB_A_CHSYNC_CTRL_INSERT ((volatile uint32_t *)0xfe3302f4)
#define P_EE_AUDIO_LB_A_CHSYNC_CTRL_ORIG ((volatile uint32_t *)0xfe3302f8)
#define P_EE_AUDIO_LB_A_CTRL4 ((volatile uint32_t *)0xfe3302fc)
#define P_EE_AUDIO_TDMIN_A_CTRL ((volatile uint32_t *)0xfe330300)
#define P_EE_AUDIO_TDMIN_A_SWAP0 ((volatile uint32_t *)0xfe330304)
#define P_EE_AUDIO_TDMIN_A_MASK0 ((volatile uint32_t *)0xfe330308)
#define P_EE_AUDIO_TDMIN_A_MASK1 ((volatile uint32_t *)0xfe33030c)
#define P_EE_AUDIO_TDMIN_A_MASK2 ((volatile uint32_t *)0xfe330310)
#define P_EE_AUDIO_TDMIN_A_MASK3 ((volatile uint32_t *)0xfe330314)
#define P_EE_AUDIO_TDMIN_A_STAT ((volatile uint32_t *)0xfe330318)
#define P_EE_AUDIO_TDMIN_A_MUTE_VAL ((volatile uint32_t *)0xfe33031c)
#define P_EE_AUDIO_TDMIN_A_MUTE0 ((volatile uint32_t *)0xfe330320)
#define P_EE_AUDIO_TDMIN_A_MUTE1 ((volatile uint32_t *)0xfe330324)
#define P_EE_AUDIO_TDMIN_A_MUTE2 ((volatile uint32_t *)0xfe330328)
#define P_EE_AUDIO_TDMIN_A_MUTE3 ((volatile uint32_t *)0xfe33032c)
#define P_EE_AUDIO_TDMIN_B_CTRL ((volatile uint32_t *)0xfe330340)
#define P_EE_AUDIO_TDMIN_B_SWAP0 ((volatile uint32_t *)0xfe330344)
#define P_EE_AUDIO_TDMIN_B_MASK0 ((volatile uint32_t *)0xfe330348)
#define P_EE_AUDIO_TDMIN_B_MASK1 ((volatile uint32_t *)0xfe33034c)
#define P_EE_AUDIO_TDMIN_B_MASK2 ((volatile uint32_t *)0xfe330350)
#define P_EE_AUDIO_TDMIN_B_MASK3 ((volatile uint32_t *)0xfe330354)
#define P_EE_AUDIO_TDMIN_B_STAT ((volatile uint32_t *)0xfe330358)
#define P_EE_AUDIO_TDMIN_B_MUTE_VAL ((volatile uint32_t *)0xfe33035c)
#define P_EE_AUDIO_TDMIN_B_MUTE0 ((volatile uint32_t *)0xfe330360)
#define P_EE_AUDIO_TDMIN_B_MUTE1 ((volatile uint32_t *)0xfe330364)
#define P_EE_AUDIO_TDMIN_B_MUTE2 ((volatile uint32_t *)0xfe330368)
#define P_EE_AUDIO_TDMIN_B_MUTE3 ((volatile uint32_t *)0xfe33036c)
#define P_EE_AUDIO_TDMIN_C_CTRL ((volatile uint32_t *)0xfe330380)
#define P_EE_AUDIO_TDMIN_C_SWAP0 ((volatile uint32_t *)0xfe330384)
#define P_EE_AUDIO_TDMIN_C_MASK0 ((volatile uint32_t *)0xfe330388)
#define P_EE_AUDIO_TDMIN_C_MASK1 ((volatile uint32_t *)0xfe33038c)
#define P_EE_AUDIO_TDMIN_C_MASK2 ((volatile uint32_t *)0xfe330390)
#define P_EE_AUDIO_TDMIN_C_MASK3 ((volatile uint32_t *)0xfe330394)
#define P_EE_AUDIO_TDMIN_C_STAT ((volatile uint32_t *)0xfe330398)
#define P_EE_AUDIO_TDMIN_C_MUTE_VAL ((volatile uint32_t *)0xfe33039c)
#define P_EE_AUDIO_TDMIN_C_MUTE0 ((volatile uint32_t *)0xfe3303a0)
#define P_EE_AUDIO_TDMIN_C_MUTE1 ((volatile uint32_t *)0xfe3303a4)
#define P_EE_AUDIO_TDMIN_C_MUTE2 ((volatile uint32_t *)0xfe3303a8)
#define P_EE_AUDIO_TDMIN_C_MUTE3 ((volatile uint32_t *)0xfe3303ac)
#define P_EE_AUDIO_TDMIN_LB_CTRL ((volatile uint32_t *)0xfe3303c0)
#define P_EE_AUDIO_TDMIN_LB_SWAP0 ((volatile uint32_t *)0xfe3303c4)
#define P_EE_AUDIO_TDMIN_LB_MASK0 ((volatile uint32_t *)0xfe3303c8)
#define P_EE_AUDIO_TDMIN_LB_MASK1 ((volatile uint32_t *)0xfe3303cc)
#define P_EE_AUDIO_TDMIN_LB_MASK2 ((volatile uint32_t *)0xfe3303d0)
#define P_EE_AUDIO_TDMIN_LB_MASK3 ((volatile uint32_t *)0xfe3303d4)
#define P_EE_AUDIO_TDMIN_LB_STAT ((volatile uint32_t *)0xfe3303d8)
#define P_EE_AUDIO_TDMIN_LB_MUTE_VAL ((volatile uint32_t *)0xfe3303dc)
#define P_EE_AUDIO_TDMIN_LB_MUTE0 ((volatile uint32_t *)0xfe3303e0)
#define P_EE_AUDIO_TDMIN_LB_MUTE1 ((volatile uint32_t *)0xfe3303e4)
#define P_EE_AUDIO_TDMIN_LB_MUTE2 ((volatile uint32_t *)0xfe3303e8)
#define P_EE_AUDIO_TDMIN_LB_MUTE3 ((volatile uint32_t *)0xfe3303ec)
#define P_EE_AUDIO_SPDIFIN_CTRL0 ((volatile uint32_t *)0xfe330400)
#define P_EE_AUDIO_SPDIFIN_CTRL1 ((volatile uint32_t *)0xfe330404)
#define P_EE_AUDIO_SPDIFIN_CTRL2 ((volatile uint32_t *)0xfe330408)
#define P_EE_AUDIO_SPDIFIN_CTRL3 ((volatile uint32_t *)0xfe33040c)
#define P_EE_AUDIO_SPDIFIN_CTRL4 ((volatile uint32_t *)0xfe330410)
#define P_EE_AUDIO_SPDIFIN_CTRL5 ((volatile uint32_t *)0xfe330414)
#define P_EE_AUDIO_SPDIFIN_CTRL6 ((volatile uint32_t *)0xfe330418)
#define P_EE_AUDIO_SPDIFIN_STAT0 ((volatile uint32_t *)0xfe33041c)
#define P_EE_AUDIO_SPDIFIN_STAT1 ((volatile uint32_t *)0xfe330420)
#define P_EE_AUDIO_SPDIFIN_STAT2 ((volatile uint32_t *)0xfe330424)
#define P_EE_AUDIO_SPDIFIN_MUTE_VAL ((volatile uint32_t *)0xfe330428)
#define P_EE_AUDIO_SPDIFIN_CTRL7 ((volatile uint32_t *)0xfe33042c)
#define P_EE_AUDIO_RESAMPLEA_CTRL0 ((volatile uint32_t *)0xfe330440)
#define P_EE_AUDIO_RESAMPLEA_CTRL1 ((volatile uint32_t *)0xfe330444)
#define P_EE_AUDIO_RESAMPLEA_CTRL2 ((volatile uint32_t *)0xfe330448)
#define P_EE_AUDIO_RESAMPLEA_CTRL3 ((volatile uint32_t *)0xfe33044c)
#define P_EE_AUDIO_RESAMPLEA_COEF0 ((volatile uint32_t *)0xfe330450)
#define P_EE_AUDIO_RESAMPLEA_COEF1 ((volatile uint32_t *)0xfe330454)
#define P_EE_AUDIO_RESAMPLEA_COEF2 ((volatile uint32_t *)0xfe330458)
#define P_EE_AUDIO_RESAMPLEA_COEF3 ((volatile uint32_t *)0xfe33045c)
#define P_EE_AUDIO_RESAMPLEA_COEF4 ((volatile uint32_t *)0xfe330460)
#define P_EE_AUDIO_RESAMPLEA_STATUS1 ((volatile uint32_t *)0xfe330464)
#define P_EE_AUDIO_SPDIFOUT_STAT ((volatile uint32_t *)0xfe330480)
#define P_EE_AUDIO_SPDIFOUT_GAIN0 ((volatile uint32_t *)0xfe330484)
#define P_EE_AUDIO_SPDIFOUT_GAIN1 ((volatile uint32_t *)0xfe330488)
#define P_EE_AUDIO_SPDIFOUT_CTRL0 ((volatile uint32_t *)0xfe33048c)
#define P_EE_AUDIO_SPDIFOUT_CTRL1 ((volatile uint32_t *)0xfe330490)
#define P_EE_AUDIO_SPDIFOUT_PREAMB ((volatile uint32_t *)0xfe330494)
#define P_EE_AUDIO_SPDIFOUT_SWAP ((volatile uint32_t *)0xfe330498)
#define P_EE_AUDIO_SPDIFOUT_CHSTS0 ((volatile uint32_t *)0xfe33049c)
#define P_EE_AUDIO_SPDIFOUT_CHSTS1 ((volatile uint32_t *)0xfe3304a0)
#define P_EE_AUDIO_SPDIFOUT_CHSTS2 ((volatile uint32_t *)0xfe3304a4)
#define P_EE_AUDIO_SPDIFOUT_CHSTS3 ((volatile uint32_t *)0xfe3304a8)
#define P_EE_AUDIO_SPDIFOUT_CHSTS4 ((volatile uint32_t *)0xfe3304ac)
#define P_EE_AUDIO_SPDIFOUT_CHSTS5 ((volatile uint32_t *)0xfe3304b0)
#define P_EE_AUDIO_SPDIFOUT_CHSTS6 ((volatile uint32_t *)0xfe3304b4)
#define P_EE_AUDIO_SPDIFOUT_CHSTS7 ((volatile uint32_t *)0xfe3304b8)
#define P_EE_AUDIO_SPDIFOUT_CHSTS8 ((volatile uint32_t *)0xfe3304bc)
#define P_EE_AUDIO_SPDIFOUT_CHSTS9 ((volatile uint32_t *)0xfe3304c0)
#define P_EE_AUDIO_SPDIFOUT_CHSTSA ((volatile uint32_t *)0xfe3304c4)
#define P_EE_AUDIO_SPDIFOUT_CHSTSB ((volatile uint32_t *)0xfe3304c8)
#define P_EE_AUDIO_SPDIFOUT_MUTE_VAL ((volatile uint32_t *)0xfe3304cc)
#define P_EE_AUDIO_SPDIFOUT_GAIN2 ((volatile uint32_t *)0xfe3304d0)
#define P_EE_AUDIO_SPDIFOUT_GAIN3 ((volatile uint32_t *)0xfe3304d4)
#define P_EE_AUDIO_SPDIFOUT_GAIN_EN ((volatile uint32_t *)0xfe3304d8)
#define P_EE_AUDIO_SPDIFOUT_GAIN_CTRL ((volatile uint32_t *)0xfe3304dc)
#define P_EE_AUDIO_TDMOUT_A_CTRL0 ((volatile uint32_t *)0xfe330500)
#define P_EE_AUDIO_TDMOUT_A_CTRL1 ((volatile uint32_t *)0xfe330504)
#define P_EE_AUDIO_TDMOUT_A_SWAP0 ((volatile uint32_t *)0xfe330508)
#define P_EE_AUDIO_TDMOUT_A_MASK0 ((volatile uint32_t *)0xfe33050c)
#define P_EE_AUDIO_TDMOUT_A_MASK1 ((volatile uint32_t *)0xfe330510)
#define P_EE_AUDIO_TDMOUT_A_MASK2 ((volatile uint32_t *)0xfe330514)
#define P_EE_AUDIO_TDMOUT_A_MASK3 ((volatile uint32_t *)0xfe330518)
#define P_EE_AUDIO_TDMOUT_A_STAT ((volatile uint32_t *)0xfe33051c)
#define P_EE_AUDIO_TDMOUT_A_GAIN0 ((volatile uint32_t *)0xfe330520)
#define P_EE_AUDIO_TDMOUT_A_GAIN1 ((volatile uint32_t *)0xfe330524)
#define P_EE_AUDIO_TDMOUT_A_MUTE_VAL ((volatile uint32_t *)0xfe330528)
#define P_EE_AUDIO_TDMOUT_A_MUTE0 ((volatile uint32_t *)0xfe33052c)
#define P_EE_AUDIO_TDMOUT_A_MUTE1 ((volatile uint32_t *)0xfe330530)
#define P_EE_AUDIO_TDMOUT_A_MUTE2 ((volatile uint32_t *)0xfe330534)
#define P_EE_AUDIO_TDMOUT_A_MUTE3 ((volatile uint32_t *)0xfe330538)
#define P_EE_AUDIO_TDMOUT_A_MASK_VAL ((volatile uint32_t *)0xfe33053c)
#define P_EE_AUDIO_TDMOUT_B_CTRL0 ((volatile uint32_t *)0xfe330540)
#define P_EE_AUDIO_TDMOUT_B_CTRL1 ((volatile uint32_t *)0xfe330544)
#define P_EE_AUDIO_TDMOUT_B_SWAP0 ((volatile uint32_t *)0xfe330548)
#define P_EE_AUDIO_TDMOUT_B_MASK0 ((volatile uint32_t *)0xfe33054c)
#define P_EE_AUDIO_TDMOUT_B_MASK1 ((volatile uint32_t *)0xfe330550)
#define P_EE_AUDIO_TDMOUT_B_MASK2 ((volatile uint32_t *)0xfe330554)
#define P_EE_AUDIO_TDMOUT_B_MASK3 ((volatile uint32_t *)0xfe330558)
#define P_EE_AUDIO_TDMOUT_B_STAT ((volatile uint32_t *)0xfe33055c)
#define P_EE_AUDIO_TDMOUT_B_GAIN0 ((volatile uint32_t *)0xfe330560)
#define P_EE_AUDIO_TDMOUT_B_GAIN1 ((volatile uint32_t *)0xfe330564)
#define P_EE_AUDIO_TDMOUT_B_MUTE_VAL ((volatile uint32_t *)0xfe330568)
#define P_EE_AUDIO_TDMOUT_B_MUTE0 ((volatile uint32_t *)0xfe33056c)
#define P_EE_AUDIO_TDMOUT_B_MUTE1 ((volatile uint32_t *)0xfe330570)
#define P_EE_AUDIO_TDMOUT_B_MUTE2 ((volatile uint32_t *)0xfe330574)
#define P_EE_AUDIO_TDMOUT_B_MUTE3 ((volatile uint32_t *)0xfe330578)
#define P_EE_AUDIO_TDMOUT_B_MASK_VAL ((volatile uint32_t *)0xfe33057c)
#define P_EE_AUDIO_TDMOUT_C_CTRL0 ((volatile uint32_t *)0xfe330580)
#define P_EE_AUDIO_TDMOUT_C_CTRL1 ((volatile uint32_t *)0xfe330584)
#define P_EE_AUDIO_TDMOUT_C_SWAP0 ((volatile uint32_t *)0xfe330588)
#define P_EE_AUDIO_TDMOUT_C_MASK0 ((volatile uint32_t *)0xfe33058c)
#define P_EE_AUDIO_TDMOUT_C_MASK1 ((volatile uint32_t *)0xfe330590)
#define P_EE_AUDIO_TDMOUT_C_MASK2 ((volatile uint32_t *)0xfe330594)
#define P_EE_AUDIO_TDMOUT_C_MASK3 ((volatile uint32_t *)0xfe330598)
#define P_EE_AUDIO_TDMOUT_C_STAT ((volatile uint32_t *)0xfe33059c)
#define P_EE_AUDIO_TDMOUT_C_GAIN0 ((volatile uint32_t *)0xfe3305a0)
#define P_EE_AUDIO_TDMOUT_C_GAIN1 ((volatile uint32_t *)0xfe3305a4)
#define P_EE_AUDIO_TDMOUT_C_MUTE_VAL ((volatile uint32_t *)0xfe3305a8)
#define P_EE_AUDIO_TDMOUT_C_MUTE0 ((volatile uint32_t *)0xfe3305ac)
#define P_EE_AUDIO_TDMOUT_C_MUTE1 ((volatile uint32_t *)0xfe3305b0)
#define P_EE_AUDIO_TDMOUT_C_MUTE2 ((volatile uint32_t *)0xfe3305b4)
#define P_EE_AUDIO_TDMOUT_C_MUTE3 ((volatile uint32_t *)0xfe3305b8)
#define P_EE_AUDIO_TDMOUT_C_MASK_VAL ((volatile uint32_t *)0xfe3305bc)
#define P_EE_AUDIO_TDMINB_LB_CTRL ((volatile uint32_t *)0xfe3305c0)
#define P_EE_AUDIO_TDMINB_LB_SWAP0 ((volatile uint32_t *)0xfe3305c4)
#define P_EE_AUDIO_TDMINB_LB_MASK0 ((volatile uint32_t *)0xfe3305c8)
#define P_EE_AUDIO_TDMINB_LB_MASK1 ((volatile uint32_t *)0xfe3305cc)
#define P_EE_AUDIO_TDMINB_LB_MASK2 ((volatile uint32_t *)0xfe3305d0)
#define P_EE_AUDIO_TDMINB_LB_MASK3 ((volatile uint32_t *)0xfe3305d4)
#define P_EE_AUDIO_TDMINB_LB_STAT ((volatile uint32_t *)0xfe3305d8)
#define P_EE_AUDIO_TDMINB_LB_MUTE_VAL ((volatile uint32_t *)0xfe3305dc)
#define P_EE_AUDIO_TDMINB_LB_MUTE0 ((volatile uint32_t *)0xfe3305e0)
#define P_EE_AUDIO_TDMINB_LB_MUTE1 ((volatile uint32_t *)0xfe3305e4)
#define P_EE_AUDIO_TDMINB_LB_MUTE2 ((volatile uint32_t *)0xfe3305e8)
#define P_EE_AUDIO_TDMINB_LB_MUTE3 ((volatile uint32_t *)0xfe3305ec)
//`define EE_AUDIO_POW_DET_CTRL0          10'h180
//`define EE_AUDIO_POW_DET_CTRL1          10'h181
//`define EE_AUDIO_POW_DET_TH_HI          10'h182
//`define EE_AUDIO_POW_DET_TH_LO          10'h183
//`define EE_AUDIO_POW_DET_VALUE          10'h184
#define P_EE_AUDIO_SECURITY_CTRL0 ((volatile uint32_t *)0xfe330640)
#define P_EE_AUDIO_SECURITY_CTRL1 ((volatile uint32_t *)0xfe330644)
#define P_EE_AUDIO_SECURITY_CTRL2 ((volatile uint32_t *)0xfe330648)
#define P_EE_AUDIO_SPDIFOUT_B_STAT ((volatile uint32_t *)0xfe330680)
#define P_EE_AUDIO_SPDIFOUT_B_GAIN0 ((volatile uint32_t *)0xfe330684)
#define P_EE_AUDIO_SPDIFOUT_B_GAIN1 ((volatile uint32_t *)0xfe330688)
#define P_EE_AUDIO_SPDIFOUT_B_CTRL0 ((volatile uint32_t *)0xfe33068c)
#define P_EE_AUDIO_SPDIFOUT_B_CTRL1 ((volatile uint32_t *)0xfe330690)
#define P_EE_AUDIO_SPDIFOUT_B_PREAMB ((volatile uint32_t *)0xfe330694)
#define P_EE_AUDIO_SPDIFOUT_B_SWAP ((volatile uint32_t *)0xfe330698)
#define P_EE_AUDIO_SPDIFOUT_B_CHSTS0 ((volatile uint32_t *)0xfe33069c)
#define P_EE_AUDIO_SPDIFOUT_B_CHSTS1 ((volatile uint32_t *)0xfe3306a0)
#define P_EE_AUDIO_SPDIFOUT_B_CHSTS2 ((volatile uint32_t *)0xfe3306a4)
#define P_EE_AUDIO_SPDIFOUT_B_CHSTS3 ((volatile uint32_t *)0xfe3306a8)
#define P_EE_AUDIO_SPDIFOUT_B_CHSTS4 ((volatile uint32_t *)0xfe3306ac)
#define P_EE_AUDIO_SPDIFOUT_B_CHSTS5 ((volatile uint32_t *)0xfe3306b0)
#define P_EE_AUDIO_SPDIFOUT_B_CHSTS6 ((volatile uint32_t *)0xfe3306b4)
#define P_EE_AUDIO_SPDIFOUT_B_CHSTS7 ((volatile uint32_t *)0xfe3306b8)
#define P_EE_AUDIO_SPDIFOUT_B_CHSTS8 ((volatile uint32_t *)0xfe3306bc)
#define P_EE_AUDIO_SPDIFOUT_B_CHSTS9 ((volatile uint32_t *)0xfe3306c0)
#define P_EE_AUDIO_SPDIFOUT_B_CHSTSA ((volatile uint32_t *)0xfe3306c4)
#define P_EE_AUDIO_SPDIFOUT_B_CHSTSB ((volatile uint32_t *)0xfe3306c8)
#define P_EE_AUDIO_SPDIFOUT_B_MUTE_VAL ((volatile uint32_t *)0xfe3306cc)
#define P_EE_AUDIO_SPDIFOUT_B_GAIN2 ((volatile uint32_t *)0xfe3306d0)
#define P_EE_AUDIO_SPDIFOUT_B_GAIN3 ((volatile uint32_t *)0xfe3306d4)
#define P_EE_AUDIO_SPDIFOUT_B_GAIN_EN ((volatile uint32_t *)0xfe3306d8)
#define P_EE_AUDIO_SPDIFOUT_B_GAIN_CTRL ((volatile uint32_t *)0xfe3306dc)
#define P_EE_AUDIO_TORAM_CTRL0 ((volatile uint32_t *)0xfe330700)
#define P_EE_AUDIO_TORAM_CTRL1 ((volatile uint32_t *)0xfe330704)
#define P_EE_AUDIO_TORAM_START_ADDR ((volatile uint32_t *)0xfe330708)
#define P_EE_AUDIO_TORAM_FINISH_ADDR ((volatile uint32_t *)0xfe33070c)
#define P_EE_AUDIO_TORAM_INT_ADDR ((volatile uint32_t *)0xfe330710)
#define P_EE_AUDIO_TORAM_STATUS1 ((volatile uint32_t *)0xfe330714)
#define P_EE_AUDIO_TORAM_STATUS2 ((volatile uint32_t *)0xfe330718)
#define P_EE_AUDIO_TORAM_INIT_ADDR ((volatile uint32_t *)0xfe33071c)
#define P_EE_AUDIO_TOACODEC_CTRL0 ((volatile uint32_t *)0xfe330740)
#define P_EE_AUDIO_TOHDMITX_CTRL0 ((volatile uint32_t *)0xfe330744)
#define P_EE_AUDIO_TOVAD_CTRL0 ((volatile uint32_t *)0xfe330748)
#define P_EE_AUDIO_FRATV_CTRL0 ((volatile uint32_t *)0xfe33074c)
#define P_EE_AUDIO_RESAMPLEB_CTRL0 ((volatile uint32_t *)0xfe330780)
#define P_EE_AUDIO_RESAMPLEB_CTRL1 ((volatile uint32_t *)0xfe330784)
#define P_EE_AUDIO_RESAMPLEB_CTRL2 ((volatile uint32_t *)0xfe330788)
#define P_EE_AUDIO_RESAMPLEB_CTRL3 ((volatile uint32_t *)0xfe33078c)
#define P_EE_AUDIO_RESAMPLEB_COEF0 ((volatile uint32_t *)0xfe330790)
#define P_EE_AUDIO_RESAMPLEB_COEF1 ((volatile uint32_t *)0xfe330794)
#define P_EE_AUDIO_RESAMPLEB_COEF2 ((volatile uint32_t *)0xfe330798)
#define P_EE_AUDIO_RESAMPLEB_COEF3 ((volatile uint32_t *)0xfe33079c)
#define P_EE_AUDIO_RESAMPLEB_COEF4 ((volatile uint32_t *)0xfe3307a0)
#define P_EE_AUDIO_RESAMPLEB_STATUS1 ((volatile uint32_t *)0xfe3307a4)
#define P_EE_AUDIO_SPDIFIN_LB_CTRL0 ((volatile uint32_t *)0xfe3307c0)
#define P_EE_AUDIO_SPDIFIN_LB_CTRL1 ((volatile uint32_t *)0xfe3307c4)
#define P_EE_AUDIO_SPDIFIN_LB_CTRL6 ((volatile uint32_t *)0xfe3307d8)
#define P_EE_AUDIO_SPDIFIN_LB_STAT0 ((volatile uint32_t *)0xfe3307dc)
#define P_EE_AUDIO_SPDIFIN_LB_STAT1 ((volatile uint32_t *)0xfe3307e0)
#define P_EE_AUDIO_SPDIFIN_LB_MUTE_VAL ((volatile uint32_t *)0xfe3307e8)
#define P_EE_AUDIO_FRHDMIRX_CTRL0 ((volatile uint32_t *)0xfe330800)
#define P_EE_AUDIO_FRHDMIRX_CTRL1 ((volatile uint32_t *)0xfe330804)
#define P_EE_AUDIO_FRHDMIRX_CTRL2 ((volatile uint32_t *)0xfe330808)
#define P_EE_AUDIO_FRHDMIRX_CTRL3 ((volatile uint32_t *)0xfe33080c)
#define P_EE_AUDIO_FRHDMIRX_CTRL4 ((volatile uint32_t *)0xfe330810)
#define P_EE_AUDIO_FRHDMIRX_CTRL5 ((volatile uint32_t *)0xfe330814)
#define P_EE_AUDIO_FRHDMIRX_CTRL6 ((volatile uint32_t *)0xfe330818)
#define P_EE_AUDIO_FRHDMIRX_CTRL7 ((volatile uint32_t *)0xfe33081c)
#define P_EE_AUDIO_FRHDMIRX_STAT0 ((volatile uint32_t *)0xfe330828)
#define P_EE_AUDIO_FRHDMIRX_STAT1 ((volatile uint32_t *)0xfe33082c)
#define P_EE_AUDIO_FRHDMIRX_STAT2 ((volatile uint32_t *)0xfe330830)
#define P_EE_AUDIO_TODDR_D_CTRL0 ((volatile uint32_t *)0xfe330840)
#define P_EE_AUDIO_TODDR_D_CTRL1 ((volatile uint32_t *)0xfe330844)
#define P_EE_AUDIO_TODDR_D_START_ADDR ((volatile uint32_t *)0xfe330848)
#define P_EE_AUDIO_TODDR_D_FINISH_ADDR ((volatile uint32_t *)0xfe33084c)
#define P_EE_AUDIO_TODDR_D_INT_ADDR ((volatile uint32_t *)0xfe330850)
#define P_EE_AUDIO_TODDR_D_STATUS1 ((volatile uint32_t *)0xfe330854)
#define P_EE_AUDIO_TODDR_D_STATUS2 ((volatile uint32_t *)0xfe330858)
#define P_EE_AUDIO_TODDR_D_START_ADDRB ((volatile uint32_t *)0xfe33085c)
#define P_EE_AUDIO_TODDR_D_FINISH_ADDRB ((volatile uint32_t *)0xfe330860)
#define P_EE_AUDIO_TODDR_D_INIT_ADDR ((volatile uint32_t *)0xfe330864)
#define P_EE_AUDIO_TODDR_D_CTRL2 ((volatile uint32_t *)0xfe330868)
#define P_EE_AUDIO_FRDDR_D_CTRL0 ((volatile uint32_t *)0xfe330880)
#define P_EE_AUDIO_FRDDR_D_CTRL1 ((volatile uint32_t *)0xfe330884)
#define P_EE_AUDIO_FRDDR_D_START_ADDR ((volatile uint32_t *)0xfe330888)
#define P_EE_AUDIO_FRDDR_D_FINISH_ADDR ((volatile uint32_t *)0xfe33088c)
#define P_EE_AUDIO_FRDDR_D_INT_ADDR ((volatile uint32_t *)0xfe330890)
#define P_EE_AUDIO_FRDDR_D_STATUS1 ((volatile uint32_t *)0xfe330894)
#define P_EE_AUDIO_FRDDR_D_STATUS2 ((volatile uint32_t *)0xfe330898)
#define P_EE_AUDIO_FRDDR_D_START_ADDRB ((volatile uint32_t *)0xfe33089c)
#define P_EE_AUDIO_FRDDR_D_FINISH_ADDRB ((volatile uint32_t *)0xfe3308a0)
#define P_EE_AUDIO_FRDDR_D_INIT_ADDR ((volatile uint32_t *)0xfe3308a4)
#define P_EE_AUDIO_FRDDR_D_CTRL2 ((volatile uint32_t *)0xfe3308a8)
#define P_EE_AUDIO_LB_B_CTRL0 ((volatile uint32_t *)0xfe3308c0)
#define P_EE_AUDIO_LB_B_CTRL1 ((volatile uint32_t *)0xfe3308c4)
#define P_EE_AUDIO_LB_B_CTRL2 ((volatile uint32_t *)0xfe3308c8)
#define P_EE_AUDIO_LB_B_CTRL3 ((volatile uint32_t *)0xfe3308cc)
#define P_EE_AUDIO_LB_B_DAT_CH_ID0 ((volatile uint32_t *)0xfe3308d0)
#define P_EE_AUDIO_LB_B_DAT_CH_ID1 ((volatile uint32_t *)0xfe3308d4)
#define P_EE_AUDIO_LB_B_DAT_CH_ID2 ((volatile uint32_t *)0xfe3308d8)
#define P_EE_AUDIO_LB_B_DAT_CH_ID3 ((volatile uint32_t *)0xfe3308dc)
#define P_EE_AUDIO_LB_B_LB_CH_ID0 ((volatile uint32_t *)0xfe3308e0)
#define P_EE_AUDIO_LB_B_LB_CH_ID1 ((volatile uint32_t *)0xfe3308e4)
#define P_EE_AUDIO_LB_B_LB_CH_ID2 ((volatile uint32_t *)0xfe3308e8)
#define P_EE_AUDIO_LB_B_LB_CH_ID3 ((volatile uint32_t *)0xfe3308ec)
#define P_EE_AUDIO_LB_B_STS ((volatile uint32_t *)0xfe3308f0)
#define P_EE_AUDIO_LB_B_CHSYNC_CTRL_INSERT ((volatile uint32_t *)0xfe3308f4)
#define P_EE_AUDIO_LB_B_CHSYNC_CTRL_ORIG ((volatile uint32_t *)0xfe3308f8)
#define P_EE_AUDIO_LB_B_CTRL4 ((volatile uint32_t *)0xfe3308fc)
#define P_EE_AUDIO_TODDR_E_CTRL0 ((volatile uint32_t *)0xfe330900)
#define P_EE_AUDIO_TODDR_E_CTRL1 ((volatile uint32_t *)0xfe330904)
#define P_EE_AUDIO_TODDR_E_START_ADDR ((volatile uint32_t *)0xfe330908)
#define P_EE_AUDIO_TODDR_E_FINISH_ADDR ((volatile uint32_t *)0xfe33090c)
#define P_EE_AUDIO_TODDR_E_INT_ADDR ((volatile uint32_t *)0xfe330910)
#define P_EE_AUDIO_TODDR_E_STATUS1 ((volatile uint32_t *)0xfe330914)
#define P_EE_AUDIO_TODDR_E_STATUS2 ((volatile uint32_t *)0xfe330918)
#define P_EE_AUDIO_TODDR_E_START_ADDRB ((volatile uint32_t *)0xfe33091c)
#define P_EE_AUDIO_TODDR_E_FINISH_ADDRB ((volatile uint32_t *)0xfe330920)
#define P_EE_AUDIO_TODDR_E_INIT_ADDR ((volatile uint32_t *)0xfe330924)
#define P_EE_AUDIO_TODDR_E_CTRL2 ((volatile uint32_t *)0xfe330928)
#define P_EE_AUDIO_FRDDR_E_CTRL0 ((volatile uint32_t *)0xfe330940)
#define P_EE_AUDIO_FRDDR_E_CTRL1 ((volatile uint32_t *)0xfe330944)
#define P_EE_AUDIO_FRDDR_E_START_ADDR ((volatile uint32_t *)0xfe330948)
#define P_EE_AUDIO_FRDDR_E_FINISH_ADDR ((volatile uint32_t *)0xfe33094c)
#define P_EE_AUDIO_FRDDR_E_INT_ADDR ((volatile uint32_t *)0xfe330950)
#define P_EE_AUDIO_FRDDR_E_STATUS1 ((volatile uint32_t *)0xfe330954)
#define P_EE_AUDIO_FRDDR_E_STATUS2 ((volatile uint32_t *)0xfe330958)
#define P_EE_AUDIO_FRDDR_E_START_ADDRB ((volatile uint32_t *)0xfe33095c)
#define P_EE_AUDIO_FRDDR_E_FINISH_ADDRB ((volatile uint32_t *)0xfe330960)
#define P_EE_AUDIO_FRDDR_E_INIT_ADDR ((volatile uint32_t *)0xfe330964)
#define P_EE_AUDIO_FRDDR_E_CTRL2 ((volatile uint32_t *)0xfe330968)
#define P_EE_AUDIO_TDMIN_A_SWAP1 ((volatile uint32_t *)0xfe330980)
#define P_EE_AUDIO_TDMIN_A_MASK4 ((volatile uint32_t *)0xfe330984)
#define P_EE_AUDIO_TDMIN_A_MASK5 ((volatile uint32_t *)0xfe330988)
#define P_EE_AUDIO_TDMIN_A_MASK6 ((volatile uint32_t *)0xfe33098c)
#define P_EE_AUDIO_TDMIN_A_MASK7 ((volatile uint32_t *)0xfe330990)
#define P_EE_AUDIO_TDMIN_A_MUTE4 ((volatile uint32_t *)0xfe330994)
#define P_EE_AUDIO_TDMIN_A_MUTE5 ((volatile uint32_t *)0xfe330998)
#define P_EE_AUDIO_TDMIN_A_MUTE6 ((volatile uint32_t *)0xfe33099c)
#define P_EE_AUDIO_TDMIN_A_MUTE7 ((volatile uint32_t *)0xfe3309a0)
#define P_EE_AUDIO_TDMIN_B_SWAP1 ((volatile uint32_t *)0xfe3309c0)
#define P_EE_AUDIO_TDMIN_B_MASK4 ((volatile uint32_t *)0xfe3309c4)
#define P_EE_AUDIO_TDMIN_B_MASK5 ((volatile uint32_t *)0xfe3309c8)
#define P_EE_AUDIO_TDMIN_B_MASK6 ((volatile uint32_t *)0xfe3309cc)
#define P_EE_AUDIO_TDMIN_B_MASK7 ((volatile uint32_t *)0xfe3309d0)
#define P_EE_AUDIO_TDMIN_B_MUTE4 ((volatile uint32_t *)0xfe3309d4)
#define P_EE_AUDIO_TDMIN_B_MUTE5 ((volatile uint32_t *)0xfe3309d8)
#define P_EE_AUDIO_TDMIN_B_MUTE6 ((volatile uint32_t *)0xfe3309dc)
#define P_EE_AUDIO_TDMIN_B_MUTE7 ((volatile uint32_t *)0xfe3309e0)
#define P_EE_AUDIO_TDMIN_C_SWAP1 ((volatile uint32_t *)0xfe330a00)
#define P_EE_AUDIO_TDMIN_C_MASK4 ((volatile uint32_t *)0xfe330a04)
#define P_EE_AUDIO_TDMIN_C_MASK5 ((volatile uint32_t *)0xfe330a08)
#define P_EE_AUDIO_TDMIN_C_MASK6 ((volatile uint32_t *)0xfe330a0c)
#define P_EE_AUDIO_TDMIN_C_MASK7 ((volatile uint32_t *)0xfe330a10)
#define P_EE_AUDIO_TDMIN_C_MUTE4 ((volatile uint32_t *)0xfe330a14)
#define P_EE_AUDIO_TDMIN_C_MUTE5 ((volatile uint32_t *)0xfe330a18)
#define P_EE_AUDIO_TDMIN_C_MUTE6 ((volatile uint32_t *)0xfe330a1c)
#define P_EE_AUDIO_TDMIN_C_MUTE7 ((volatile uint32_t *)0xfe330a20)
#define P_EE_AUDIO_TDMIN_LB_SWAP1 ((volatile uint32_t *)0xfe330a40)
#define P_EE_AUDIO_TDMIN_LB_MASK4 ((volatile uint32_t *)0xfe330a44)
#define P_EE_AUDIO_TDMIN_LB_MASK5 ((volatile uint32_t *)0xfe330a48)
#define P_EE_AUDIO_TDMIN_LB_MASK6 ((volatile uint32_t *)0xfe330a4c)
#define P_EE_AUDIO_TDMIN_LB_MASK7 ((volatile uint32_t *)0xfe330a50)
#define P_EE_AUDIO_TDMIN_LB_MUTE4 ((volatile uint32_t *)0xfe330a54)
#define P_EE_AUDIO_TDMIN_LB_MUTE5 ((volatile uint32_t *)0xfe330a58)
#define P_EE_AUDIO_TDMIN_LB_MUTE6 ((volatile uint32_t *)0xfe330a5c)
#define P_EE_AUDIO_TDMIN_LB_MUTE7 ((volatile uint32_t *)0xfe330a60)
#define P_EE_AUDIO_TDMOUT_A_CTRL2 ((volatile uint32_t *)0xfe330a80)
#define P_EE_AUDIO_TDMOUT_A_SWAP1 ((volatile uint32_t *)0xfe330a84)
#define P_EE_AUDIO_TDMOUT_A_GAIN2 ((volatile uint32_t *)0xfe330a88)
#define P_EE_AUDIO_TDMOUT_A_GAIN3 ((volatile uint32_t *)0xfe330a8c)
#define P_EE_AUDIO_TDMOUT_A_MASK4 ((volatile uint32_t *)0xfe330a90)
#define P_EE_AUDIO_TDMOUT_A_MASK5 ((volatile uint32_t *)0xfe330a94)
#define P_EE_AUDIO_TDMOUT_A_MASK6 ((volatile uint32_t *)0xfe330a98)
#define P_EE_AUDIO_TDMOUT_A_MASK7 ((volatile uint32_t *)0xfe330a9c)
#define P_EE_AUDIO_TDMOUT_A_MUTE4 ((volatile uint32_t *)0xfe330aa0)
#define P_EE_AUDIO_TDMOUT_A_MUTE5 ((volatile uint32_t *)0xfe330aa4)
#define P_EE_AUDIO_TDMOUT_A_MUTE6 ((volatile uint32_t *)0xfe330aa8)
#define P_EE_AUDIO_TDMOUT_A_MUTE7 ((volatile uint32_t *)0xfe330aac)
#define P_EE_AUDIO_TDMOUT_A_GAIN_EN ((volatile uint32_t *)0xfe330ab0)
#define P_EE_AUDIO_TDMOUT_A_GAIN_CTRL ((volatile uint32_t *)0xfe330ab4)
#define P_EE_AUDIO_TDMOUT_B_CTRL2 ((volatile uint32_t *)0xfe330ac0)
#define P_EE_AUDIO_TDMOUT_B_SWAP1 ((volatile uint32_t *)0xfe330ac4)
#define P_EE_AUDIO_TDMOUT_B_GAIN2 ((volatile uint32_t *)0xfe330ac8)
#define P_EE_AUDIO_TDMOUT_B_GAIN3 ((volatile uint32_t *)0xfe330acc)
#define P_EE_AUDIO_TDMOUT_B_MASK4 ((volatile uint32_t *)0xfe330ad0)
#define P_EE_AUDIO_TDMOUT_B_MASK5 ((volatile uint32_t *)0xfe330ad4)
#define P_EE_AUDIO_TDMOUT_B_MASK6 ((volatile uint32_t *)0xfe330ad8)
#define P_EE_AUDIO_TDMOUT_B_MASK7 ((volatile uint32_t *)0xfe330adc)
#define P_EE_AUDIO_TDMOUT_B_MUTE4 ((volatile uint32_t *)0xfe330ae0)
#define P_EE_AUDIO_TDMOUT_B_MUTE5 ((volatile uint32_t *)0xfe330ae4)
#define P_EE_AUDIO_TDMOUT_B_MUTE6 ((volatile uint32_t *)0xfe330ae8)
#define P_EE_AUDIO_TDMOUT_B_MUTE7 ((volatile uint32_t *)0xfe330aec)
#define P_EE_AUDIO_TDMOUT_B_GAIN_EN ((volatile uint32_t *)0xfe330af0)
#define P_EE_AUDIO_TDMOUT_B_GAIN_CTRL ((volatile uint32_t *)0xfe330af4)
#define P_EE_AUDIO_TDMOUT_C_CTRL2 ((volatile uint32_t *)0xfe330b00)
#define P_EE_AUDIO_TDMOUT_C_SWAP1 ((volatile uint32_t *)0xfe330b04)
#define P_EE_AUDIO_TDMOUT_C_GAIN2 ((volatile uint32_t *)0xfe330b08)
#define P_EE_AUDIO_TDMOUT_C_GAIN3 ((volatile uint32_t *)0xfe330b0c)
#define P_EE_AUDIO_TDMOUT_C_MASK4 ((volatile uint32_t *)0xfe330b10)
#define P_EE_AUDIO_TDMOUT_C_MASK5 ((volatile uint32_t *)0xfe330b14)
#define P_EE_AUDIO_TDMOUT_C_MASK6 ((volatile uint32_t *)0xfe330b18)
#define P_EE_AUDIO_TDMOUT_C_MASK7 ((volatile uint32_t *)0xfe330b1c)
#define P_EE_AUDIO_TDMOUT_C_MUTE4 ((volatile uint32_t *)0xfe330b20)
#define P_EE_AUDIO_TDMOUT_C_MUTE5 ((volatile uint32_t *)0xfe330b24)
#define P_EE_AUDIO_TDMOUT_C_MUTE6 ((volatile uint32_t *)0xfe330b28)
#define P_EE_AUDIO_TDMOUT_C_MUTE7 ((volatile uint32_t *)0xfe330b2c)
#define P_EE_AUDIO_TDMOUT_C_GAIN_EN ((volatile uint32_t *)0xfe330b30)
#define P_EE_AUDIO_TDMOUT_C_GAIN_CTRL ((volatile uint32_t *)0xfe330b34)
#define P_EE_AUDIO_TDMINB_LB_SWAP1 ((volatile uint32_t *)0xfe330b40)
#define P_EE_AUDIO_TDMINB_LB_MASK4 ((volatile uint32_t *)0xfe330b44)
#define P_EE_AUDIO_TDMINB_LB_MASK5 ((volatile uint32_t *)0xfe330b48)
#define P_EE_AUDIO_TDMINB_LB_MASK6 ((volatile uint32_t *)0xfe330b4c)
#define P_EE_AUDIO_TDMINB_LB_MASK7 ((volatile uint32_t *)0xfe330b50)
#define P_EE_AUDIO_TDMINB_LB_MUTE4 ((volatile uint32_t *)0xfe330b54)
#define P_EE_AUDIO_TDMINB_LB_MUTE5 ((volatile uint32_t *)0xfe330b58)
#define P_EE_AUDIO_TDMINB_LB_MUTE6 ((volatile uint32_t *)0xfe330b5c)
#define P_EE_AUDIO_TDMINB_LB_MUTE7 ((volatile uint32_t *)0xfe330b60)
#define P_EE_AUDIO_TODDR_A_CHNUM_ID0 ((volatile uint32_t *)0xfe330c00)
#define P_EE_AUDIO_TODDR_A_CHNUM_ID1 ((volatile uint32_t *)0xfe330c04)
#define P_EE_AUDIO_TODDR_A_CHNUM_ID2 ((volatile uint32_t *)0xfe330c08)
#define P_EE_AUDIO_TODDR_A_CHNUM_ID3 ((volatile uint32_t *)0xfe330c0c)
#define P_EE_AUDIO_TODDR_A_CHNUM_ID4 ((volatile uint32_t *)0xfe330c10)
#define P_EE_AUDIO_TODDR_A_CHNUM_ID5 ((volatile uint32_t *)0xfe330c14)
#define P_EE_AUDIO_TODDR_A_CHNUM_ID6 ((volatile uint32_t *)0xfe330c18)
#define P_EE_AUDIO_TODDR_A_CHNUM_ID7 ((volatile uint32_t *)0xfe330c1c)
#define P_EE_AUDIO_TODDR_A_CHSYNC_CTRL ((volatile uint32_t *)0xfe330c3c)
#define P_EE_AUDIO_TODDR_B_CHNUM_ID0 ((volatile uint32_t *)0xfe330c40)
#define P_EE_AUDIO_TODDR_B_CHNUM_ID1 ((volatile uint32_t *)0xfe330c44)
#define P_EE_AUDIO_TODDR_B_CHNUM_ID2 ((volatile uint32_t *)0xfe330c48)
#define P_EE_AUDIO_TODDR_B_CHNUM_ID3 ((volatile uint32_t *)0xfe330c4c)
#define P_EE_AUDIO_TODDR_B_CHNUM_ID4 ((volatile uint32_t *)0xfe330c50)
#define P_EE_AUDIO_TODDR_B_CHNUM_ID5 ((volatile uint32_t *)0xfe330c54)
#define P_EE_AUDIO_TODDR_B_CHNUM_ID6 ((volatile uint32_t *)0xfe330c58)
#define P_EE_AUDIO_TODDR_B_CHNUM_ID7 ((volatile uint32_t *)0xfe330c5c)
#define P_EE_AUDIO_TODDR_B_CHSYNC_CTRL ((volatile uint32_t *)0xfe330c7c)
#define P_EE_AUDIO_TODDR_C_CHNUM_ID0 ((volatile uint32_t *)0xfe330c80)
#define P_EE_AUDIO_TODDR_C_CHNUM_ID1 ((volatile uint32_t *)0xfe330c84)
#define P_EE_AUDIO_TODDR_C_CHNUM_ID2 ((volatile uint32_t *)0xfe330c88)
#define P_EE_AUDIO_TODDR_C_CHNUM_ID3 ((volatile uint32_t *)0xfe330c8c)
#define P_EE_AUDIO_TODDR_C_CHNUM_ID4 ((volatile uint32_t *)0xfe330c90)
#define P_EE_AUDIO_TODDR_C_CHNUM_ID5 ((volatile uint32_t *)0xfe330c94)
#define P_EE_AUDIO_TODDR_C_CHNUM_ID6 ((volatile uint32_t *)0xfe330c98)
#define P_EE_AUDIO_TODDR_C_CHNUM_ID7 ((volatile uint32_t *)0xfe330c9c)
#define P_EE_AUDIO_TODDR_C_CHSYNC_CTRL ((volatile uint32_t *)0xfe330cbc)
#define P_EE_AUDIO_TODDR_D_CHNUM_ID0 ((volatile uint32_t *)0xfe330cc0)
#define P_EE_AUDIO_TODDR_D_CHNUM_ID1 ((volatile uint32_t *)0xfe330cc4)
#define P_EE_AUDIO_TODDR_D_CHNUM_ID2 ((volatile uint32_t *)0xfe330cc8)
#define P_EE_AUDIO_TODDR_D_CHNUM_ID3 ((volatile uint32_t *)0xfe330ccc)
#define P_EE_AUDIO_TODDR_D_CHNUM_ID4 ((volatile uint32_t *)0xfe330cd0)
#define P_EE_AUDIO_TODDR_D_CHNUM_ID5 ((volatile uint32_t *)0xfe330cd4)
#define P_EE_AUDIO_TODDR_D_CHNUM_ID6 ((volatile uint32_t *)0xfe330cd8)
#define P_EE_AUDIO_TODDR_D_CHNUM_ID7 ((volatile uint32_t *)0xfe330cdc)
#define P_EE_AUDIO_TODDR_D_CHSYNC_CTRL ((volatile uint32_t *)0xfe330cfc)
#define P_EE_AUDIO_TODDR_E_CHNUM_ID0 ((volatile uint32_t *)0xfe330d00)
#define P_EE_AUDIO_TODDR_E_CHNUM_ID1 ((volatile uint32_t *)0xfe330d04)
#define P_EE_AUDIO_TODDR_E_CHNUM_ID2 ((volatile uint32_t *)0xfe330d08)
#define P_EE_AUDIO_TODDR_E_CHNUM_ID3 ((volatile uint32_t *)0xfe330d0c)
#define P_EE_AUDIO_TODDR_E_CHNUM_ID4 ((volatile uint32_t *)0xfe330d10)
#define P_EE_AUDIO_TODDR_E_CHNUM_ID5 ((volatile uint32_t *)0xfe330d14)
#define P_EE_AUDIO_TODDR_E_CHNUM_ID6 ((volatile uint32_t *)0xfe330d18)
#define P_EE_AUDIO_TODDR_E_CHNUM_ID7 ((volatile uint32_t *)0xfe330d1c)
#define P_EE_AUDIO_TODDR_E_CHSYNC_CTRL ((volatile uint32_t *)0xfe330d3c)
#define P_EE_AUDIO_RSAMP_A_CHNUM_ID0 ((volatile uint32_t *)0xfe330d40)
#define P_EE_AUDIO_RSAMP_A_CHNUM_ID1 ((volatile uint32_t *)0xfe330d44)
#define P_EE_AUDIO_RSAMP_A_CHNUM_ID2 ((volatile uint32_t *)0xfe330d48)
#define P_EE_AUDIO_RSAMP_A_CHNUM_ID3 ((volatile uint32_t *)0xfe330d4c)
#define P_EE_AUDIO_RSAMP_A_CHNUM_ID4 ((volatile uint32_t *)0xfe330d50)
#define P_EE_AUDIO_RSAMP_A_CHNUM_ID5 ((volatile uint32_t *)0xfe330d54)
#define P_EE_AUDIO_RSAMP_A_CHNUM_ID6 ((volatile uint32_t *)0xfe330d58)
#define P_EE_AUDIO_RSAMP_A_CHNUM_ID7 ((volatile uint32_t *)0xfe330d5c)
#define P_EE_AUDIO_RSAMP_CHSYNC_MASK ((volatile uint32_t *)0xfe330d78)
#define P_EE_AUDIO_RSAMP_A_CHSYNC_CTRL ((volatile uint32_t *)0xfe330d7c)
#define P_EE_AUDIO_RSAMP_B_CHNUM_ID0 ((volatile uint32_t *)0xfe330d80)
#define P_EE_AUDIO_RSAMP_B_CHNUM_ID1 ((volatile uint32_t *)0xfe330d84)
#define P_EE_AUDIO_RSAMP_B_CHNUM_ID2 ((volatile uint32_t *)0xfe330d88)
#define P_EE_AUDIO_RSAMP_B_CHNUM_ID3 ((volatile uint32_t *)0xfe330d8c)
#define P_EE_AUDIO_RSAMP_B_CHNUM_ID4 ((volatile uint32_t *)0xfe330d90)
#define P_EE_AUDIO_RSAMP_B_CHNUM_ID5 ((volatile uint32_t *)0xfe330d94)
#define P_EE_AUDIO_RSAMP_B_CHNUM_ID6 ((volatile uint32_t *)0xfe330d98)
#define P_EE_AUDIO_RSAMP_B_CHNUM_ID7 ((volatile uint32_t *)0xfe330d9c)
#define P_EE_AUDIO_RSAMP_B_CHSYNC_CTRL ((volatile uint32_t *)0xfe330dbc)
#define P_EE_AUDIO_RSAMP_C_CHNUM_ID0 ((volatile uint32_t *)0xfe330dc0)
#define P_EE_AUDIO_RSAMP_C_CHNUM_ID1 ((volatile uint32_t *)0xfe330dc4)
#define P_EE_AUDIO_RSAMP_C_CHNUM_ID2 ((volatile uint32_t *)0xfe330dc8)
#define P_EE_AUDIO_RSAMP_C_CHNUM_ID3 ((volatile uint32_t *)0xfe330dcc)
#define P_EE_AUDIO_RSAMP_C_CHNUM_ID4 ((volatile uint32_t *)0xfe330dd0)
#define P_EE_AUDIO_RSAMP_C_CHNUM_ID5 ((volatile uint32_t *)0xfe330dd4)
#define P_EE_AUDIO_RSAMP_C_CHNUM_ID6 ((volatile uint32_t *)0xfe330dd8)
#define P_EE_AUDIO_RSAMP_C_CHNUM_ID7 ((volatile uint32_t *)0xfe330ddc)
#define P_EE_AUDIO_RSAMP_C_CHSYNC_CTRL ((volatile uint32_t *)0xfe330dfc)
#define P_EE_AUDIO_EXCEPTION_IRQ_STS0 ((volatile uint32_t *)0xfe330e00)
#define P_EE_AUDIO_EXCEPTION_IRQ_STS1 ((volatile uint32_t *)0xfe330e04)
#define P_EE_AUDIO_EXCEPTION_IRQ_MASK0 ((volatile uint32_t *)0xfe330e08)
#define P_EE_AUDIO_EXCEPTION_IRQ_MASK1 ((volatile uint32_t *)0xfe330e0c)
#define P_EE_AUDIO_EXCEPTION_IRQ_MODE0 ((volatile uint32_t *)0xfe330e10)
#define P_EE_AUDIO_EXCEPTION_IRQ_MODE1 ((volatile uint32_t *)0xfe330e14)
#define P_EE_AUDIO_EXCEPTION_IRQ_CLR0 ((volatile uint32_t *)0xfe330e18)
#define P_EE_AUDIO_EXCEPTION_IRQ_CLR1 ((volatile uint32_t *)0xfe330e1c)
#define P_EE_AUDIO_EXCEPTION_IRQ_INV0 ((volatile uint32_t *)0xfe330e20)
#define P_EE_AUDIO_EXCEPTION_IRQ_INV1 ((volatile uint32_t *)0xfe330e24)
#define P_EE_AUDIO_DAT_PAD_CTRL0 ((volatile uint32_t *)0xfe330e40)
#define P_EE_AUDIO_DAT_PAD_CTRL1 ((volatile uint32_t *)0xfe330e44)
#define P_EE_AUDIO_DAT_PAD_CTRL2 ((volatile uint32_t *)0xfe330e48)
#define P_EE_AUDIO_DAT_PAD_CTRL3 ((volatile uint32_t *)0xfe330e4c)
#define P_EE_AUDIO_DAT_PAD_CTRL4 ((volatile uint32_t *)0xfe330e50)
#define P_EE_AUDIO_DAT_PAD_CTRL5 ((volatile uint32_t *)0xfe330e54)
#define P_EE_AUDIO_DAT_PAD_CTRL6 ((volatile uint32_t *)0xfe330e58)
#define P_EE_AUDIO_DAT_PAD_CTRL7 ((volatile uint32_t *)0xfe330e5c)
#define P_EE_AUDIO_DAT_PAD_CTRL8 ((volatile uint32_t *)0xfe330e60)
#define P_EE_AUDIO_DAT_PAD_CTRL9 ((volatile uint32_t *)0xfe330e64)
#define P_EE_AUDIO_DAT_PAD_CTRLA ((volatile uint32_t *)0xfe330e68)
#define P_EE_AUDIO_DAT_PAD_CTRLB ((volatile uint32_t *)0xfe330e6c)
#define P_EE_AUDIO_DAT_PAD_CTRLC ((volatile uint32_t *)0xfe330e70)
#define P_EE_AUDIO_DAT_PAD_CTRLD ((volatile uint32_t *)0xfe330e74)
#define P_EE_AUDIO_DAT_PAD_CTRLE ((volatile uint32_t *)0xfe330e78)
#define P_EE_AUDIO_DAT_PAD_CTRLF ((volatile uint32_t *)0xfe330e7c)
#define P_EE_AUDIO_MCLK_PAD_CTRL0 ((volatile uint32_t *)0xfe330e80)
#define P_EE_AUDIO_MCLK_PAD_CTRL1 ((volatile uint32_t *)0xfe330e84)
#define P_EE_AUDIO_SCLK_PAD_CTRL0 ((volatile uint32_t *)0xfe330e88)
#define P_EE_AUDIO_LRCLK_PAD_CTRL0 ((volatile uint32_t *)0xfe330e8c)
#define P_EE_AUDIO_MCLK_PAD_CTRL2 ((volatile uint32_t *)0xfe330e90)
#define P_EE_AUDIO_DAT_PAD_CTRLG ((volatile uint32_t *)0xfe330e94)
#define P_EE_AUDIO_DAT_PAD_CTRLH ((volatile uint32_t *)0xfe330e98)
#define P_EE_AUDIO_TDMIN_D_CTRL ((volatile uint32_t *)0xfe330ec0)
#define P_EE_AUDIO_TDMIN_D_SWAP0 ((volatile uint32_t *)0xfe330ec4)
#define P_EE_AUDIO_TDMIN_D_MASK0 ((volatile uint32_t *)0xfe330ec8)
#define P_EE_AUDIO_TDMIN_D_MASK1 ((volatile uint32_t *)0xfe330ecc)
#define P_EE_AUDIO_TDMIN_D_MASK2 ((volatile uint32_t *)0xfe330ed0)
#define P_EE_AUDIO_TDMIN_D_MASK3 ((volatile uint32_t *)0xfe330ed4)
#define P_EE_AUDIO_TDMIN_D_STAT ((volatile uint32_t *)0xfe330ed8)
#define P_EE_AUDIO_TDMIN_D_MUTE_VAL ((volatile uint32_t *)0xfe330edc)
#define P_EE_AUDIO_TDMIN_D_MUTE0 ((volatile uint32_t *)0xfe330ee0)
#define P_EE_AUDIO_TDMIN_D_MUTE1 ((volatile uint32_t *)0xfe330ee4)
#define P_EE_AUDIO_TDMIN_D_MUTE2 ((volatile uint32_t *)0xfe330ee8)
#define P_EE_AUDIO_TDMIN_D_MUTE3 ((volatile uint32_t *)0xfe330eec)
#define P_EE_AUDIO_TDMIN_D_SWAP1 ((volatile uint32_t *)0xfe330f00)
#define P_EE_AUDIO_TDMIN_D_MASK4 ((volatile uint32_t *)0xfe330f04)
#define P_EE_AUDIO_TDMIN_D_MASK5 ((volatile uint32_t *)0xfe330f08)
#define P_EE_AUDIO_TDMIN_D_MASK6 ((volatile uint32_t *)0xfe330f0c)
#define P_EE_AUDIO_TDMIN_D_MASK7 ((volatile uint32_t *)0xfe330f10)
#define P_EE_AUDIO_TDMIN_D_MUTE4 ((volatile uint32_t *)0xfe330f14)
#define P_EE_AUDIO_TDMIN_D_MUTE5 ((volatile uint32_t *)0xfe330f18)
#define P_EE_AUDIO_TDMIN_D_MUTE6 ((volatile uint32_t *)0xfe330f1c)
#define P_EE_AUDIO_TDMIN_D_MUTE7 ((volatile uint32_t *)0xfe330f20)
#define P_EE_AUDIO_TDMOUT_D_CTRL0 ((volatile uint32_t *)0xfe330f40)
#define P_EE_AUDIO_TDMOUT_D_CTRL1 ((volatile uint32_t *)0xfe330f44)
#define P_EE_AUDIO_TDMOUT_D_SWAP0 ((volatile uint32_t *)0xfe330f48)
#define P_EE_AUDIO_TDMOUT_D_MASK0 ((volatile uint32_t *)0xfe330f4c)
#define P_EE_AUDIO_TDMOUT_D_MASK1 ((volatile uint32_t *)0xfe330f50)
#define P_EE_AUDIO_TDMOUT_D_MASK2 ((volatile uint32_t *)0xfe330f54)
#define P_EE_AUDIO_TDMOUT_D_MASK3 ((volatile uint32_t *)0xfe330f58)
#define P_EE_AUDIO_TDMOUT_D_STAT ((volatile uint32_t *)0xfe330f5c)
#define P_EE_AUDIO_TDMOUT_D_GAIN0 ((volatile uint32_t *)0xfe330f60)
#define P_EE_AUDIO_TDMOUT_D_GAIN1 ((volatile uint32_t *)0xfe330f64)
#define P_EE_AUDIO_TDMOUT_D_MUTE_VAL ((volatile uint32_t *)0xfe330f68)
#define P_EE_AUDIO_TDMOUT_D_MUTE0 ((volatile uint32_t *)0xfe330f6c)
#define P_EE_AUDIO_TDMOUT_D_MUTE1 ((volatile uint32_t *)0xfe330f70)
#define P_EE_AUDIO_TDMOUT_D_MUTE2 ((volatile uint32_t *)0xfe330f74)
#define P_EE_AUDIO_TDMOUT_D_MUTE3 ((volatile uint32_t *)0xfe330f78)
#define P_EE_AUDIO_TDMOUT_D_MASK_VAL ((volatile uint32_t *)0xfe330f7c)
#define P_EE_AUDIO_TDMOUT_D_CTRL2 ((volatile uint32_t *)0xfe330f80)
#define P_EE_AUDIO_TDMOUT_D_SWAP1 ((volatile uint32_t *)0xfe330f84)
#define P_EE_AUDIO_TDMOUT_D_GAIN2 ((volatile uint32_t *)0xfe330f88)
#define P_EE_AUDIO_TDMOUT_D_GAIN3 ((volatile uint32_t *)0xfe330f8c)
#define P_EE_AUDIO_TDMOUT_D_MASK4 ((volatile uint32_t *)0xfe330f90)
#define P_EE_AUDIO_TDMOUT_D_MASK5 ((volatile uint32_t *)0xfe330f94)
#define P_EE_AUDIO_TDMOUT_D_MASK6 ((volatile uint32_t *)0xfe330f98)
#define P_EE_AUDIO_TDMOUT_D_MASK7 ((volatile uint32_t *)0xfe330f9c)
#define P_EE_AUDIO_TDMOUT_D_MUTE4 ((volatile uint32_t *)0xfe330fa0)
#define P_EE_AUDIO_TDMOUT_D_MUTE5 ((volatile uint32_t *)0xfe330fa4)
#define P_EE_AUDIO_TDMOUT_D_MUTE6 ((volatile uint32_t *)0xfe330fa8)
#define P_EE_AUDIO_TDMOUT_D_MUTE7 ((volatile uint32_t *)0xfe330fac)
#define P_EE_AUDIO_TDMOUT_D_GAIN_EN ((volatile uint32_t *)0xfe330fb0)
#define P_EE_AUDIO_TDMOUT_D_GAIN_CTRL ((volatile uint32_t *)0xfe330fb4)
//========================================================================
//  PDM - Registers
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe331000
// -----------------------------------------------
#define P_PDM_CTRL ((volatile uint32_t *)0xfe331000)
// bit 31:   PDM enable.
// bit 30:   invert the PDM_DCLK.
// bit 29:   output mode:  1: 24bits. 0: 32 bits.
// bit 28:   bypass mode. 1: bypass all filter. directly output the PDM input to DDR. 0: normal
// mode. bit 27~9: not used. bit 16:.   PDM Asynchronous FIFO soft reset.  write 1 to soft reset
// AFIFO. bit 15:8   PDM channel reset.  0: to reset each PDM channel.  1: normal mode. bit 7:0.
// PDM channel enable. each bit for one channel.
#define P_PDM_HCIC_CTRL1 ((volatile uint32_t *)0xfe331004)
// bit 31      hcic filter enable.  1 use sinc filter. 0 bypass input to output.
// bit 29:24.  hcic final gain shift parameter.
// bit 23:16   hcic final gain multiplier.
// bit 8:4     hcic  down sample rate.
// bit 3:0     hcic  stage number. must be between 3 to 9.
#define P_PDM_HCIC_CTRL2 ((volatile uint32_t *)0xfe331008)
// Not used.
#define P_PDM_F1_CTRL ((volatile uint32_t *)0xfe33100c)
// bit 31 .   filter 1 enable.
// bit 16:15. f1 round mode.  2'b00 : sign bit at bit 49.  28bits output [49:22] round at bit 21.
// 32bits output [49:18]. 24bits output [49:26]
//                    2'b01 : sign bit at bit 50.  28bits output [50:23] round at bit 22. 32bits
//                    output [49:18]. 24bits output [49:26] 2'b10 : sign bit at bit 51.  28bits
//                    output [51:24] round at bit 23 32bits output [49:18]. 24bits output [49:26].
// bit 15:12. filter 1 down sample rate.
// bit 8:0.   filter 1 stage number.
#define P_PDM_F2_CTRL ((volatile uint32_t *)0xfe331010)
// bit 31 .   filter 2 enable.
// bit 16:15. f2 round mode.  2'b00 : round at bit 21. 2'b01 : round at bit 22.  2'b10 : round at
// bit 23. bit 15:12. filter 2 down sample rate. bit 8:0.   filter 2 stage number.
#define P_PDM_F3_CTRL ((volatile uint32_t *)0xfe331014)
// bit 31 .   filter 3 enable.
// bit 16:15. f3 round mode.  2'b00 : round at bit 21. 2'b01 : round at bit 22.  2'b10 : round at
// bit 23. bit 15:12. filter 3 down sample rate. bit 8:0.   filter 3 stage number.
#define P_PDM_HPF_CTRL ((volatile uint32_t *)0xfe331018)
// bit 31  High pass filter enable.
// bit 20:16 high pass filter shift steps. 6~19 steps.
// bit 15:0 high pass filter output factor.
#define P_PDM_CHAN_CTRL ((volatile uint32_t *)0xfe33101c)
// bit 31:24.  chan3 data sample pointer vs edge of the PDM_DCLK.
// bit 23:16   chan2 data sample pointer vs edge of the PDM_DCLK.
// bit 15:8.   chan1 data sample pointer vs edge of the PDM_DCLK.
// bit 7:0     chan0 data sample pointer vs edge of the PDM_DCLK.
#define P_PDM_CHAN_CTRL1 ((volatile uint32_t *)0xfe331020)
// bit 31:24.  chan7 data sample pointer vs edge of the PDM_DCLK.
// bit 23:16   chan6 data sample pointer vs edge of the PDM_DCLK.
// bit 15:8.   chan5 data sample pointer vs edge of the PDM_DCLK.
// bit 7:0     chan4 data sample pointer vs edge of the PDM_DCLK.
#define P_PDM_COEFF_ADDR ((volatile uint32_t *)0xfe331024)
// address of the write/read of coeff data.
#define P_PDM_COEFF_DATA ((volatile uint32_t *)0xfe331028)
// write/read data to coeff memory.
#define P_PDM_CLKG_CTRL ((volatile uint32_t *)0xfe33102c)
// auto clock gating control.  1: disable the clock gating function. the clock will awlays
// enabled. 0 : use RTL auto clock gating.
// 31:7 not used.
// bit 6  filt_ctrl module auto clock gating control.
// bit 5  sinc fifo module auto clock gating control.
// bit 4  filter module auto clock gating control.
// bit 3  apb module auto clock gating control.
// bit 2  coeff memory module auto clock gating control.
// bit 1  each channel module auto clock gating control.
// bit 0 cts_pdm_clk   auto clock gating control.
#define P_PDM_STS ((volatile uint32_t *)0xfe331030)
// bit 1  HPF filter output overflow.  means the PCLK is too slow.
// bit 0  HCIC filter output overflow. means the CTS_PDM_CLK is too slow. can't finished the
// filter function.
#define P_PDM_MUTE_VALUE ((volatile uint32_t *)0xfe331034)
#define P_PDM_MASK_NUM ((volatile uint32_t *)0xfe331038)
#define P_PDM_CHAN_CTRL2 ((volatile uint32_t *)0xfe33103c)
// bit 7:0    second sample and start FSM point vs rise edge of PDM_DCLK
//========================================================================
//  PDMB - Registers
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe334800
// -----------------------------------------------
#define P_PDMB_CTRL ((volatile uint32_t *)0xfe334800)
// bit 31:   PDM enable.
// bit 30:   invert the PDM_DCLK.
// bit 29:   output mode:  1: 24bits. 0: 32 bits.
// bit 28:   bypass mode. 1: bypass all filter. directly output the PDM input to DDR. 0: normal
// mode. bit 27~9: not used. bit 16:.   PDM Asynchronous FIFO soft reset.  write 1 to soft reset
// AFIFO. bit 15:8   PDM channel reset.  0: to reset each PDM channel.  1: normal mode. bit 7:0.
// PDM channel enable. each bit for one channel.
#define P_PDMB_HCIC_CTRL1 ((volatile uint32_t *)0xfe334804)
// bit 31      hcic filter enable.  1 use sinc filter. 0 bypass input to output.
// bit 29:24.  hcic final gain shift parameter.
// bit 23:16   hcic final gain multiplier.
// bit 8:4     hcic  down sample rate.
// bit 3:0     hcic  stage number. must be between 3 to 9.
#define P_PDMB_HCIC_CTRL2 ((volatile uint32_t *)0xfe334808)
// Not used.
#define P_PDMB_F1_CTRL ((volatile uint32_t *)0xfe33480c)
// bit 31 .   filter 1 enable.
// bit 16:15. f1 round mode.  2'b00 : sign bit at bit 49.  28bits output [49:22] round at bit 21.
// 32bits output [49:18]. 24bits output [49:26]
//                    2'b01 : sign bit at bit 50.  28bits output [50:23] round at bit 22. 32bits
//                    output [49:18]. 24bits output [49:26] 2'b10 : sign bit at bit 51.  28bits
//                    output [51:24] round at bit 23 32bits output [49:18]. 24bits output [49:26].
// bit 15:12. filter 1 down sample rate.
// bit 8:0.   filter 1 stage number.
#define P_PDMB_F2_CTRL ((volatile uint32_t *)0xfe334810)
// bit 31 .   filter 2 enable.
// bit 16:15. f2 round mode.  2'b00 : round at bit 21. 2'b01 : round at bit 22.  2'b10 : round at
// bit 23. bit 15:12. filter 2 down sample rate. bit 8:0.   filter 2 stage number.
#define P_PDMB_F3_CTRL ((volatile uint32_t *)0xfe334814)
// bit 31 .   filter 3 enable.
// bit 16:15. f3 round mode.  2'b00 : round at bit 21. 2'b01 : round at bit 22.  2'b10 : round at
// bit 23. bit 15:12. filter 3 down sample rate. bit 8:0.   filter 3 stage number.
#define P_PDMB_HPF_CTRL ((volatile uint32_t *)0xfe334818)
// bit 31  High pass filter enable.
// bit 20:16 high pass filter shift steps. 6~19 steps.
// bit 15:0 high pass filter output factor.
#define P_PDMB_CHAN_CTRL ((volatile uint32_t *)0xfe33481c)
// bit 31:24.  chan3 data sample pointer vs edge of the PDM_DCLK.
// bit 23:16   chan2 data sample pointer vs edge of the PDM_DCLK.
// bit 15:8.   chan1 data sample pointer vs edge of the PDM_DCLK.
// bit 7:0     chan0 data sample pointer vs edge of the PDM_DCLK.
#define P_PDMB_CHAN_CTRL1 ((volatile uint32_t *)0xfe334820)
// bit 31:24.  chan7 data sample pointer vs edge of the PDM_DCLK.
// bit 23:16   chan6 data sample pointer vs edge of the PDM_DCLK.
// bit 15:8.   chan5 data sample pointer vs edge of the PDM_DCLK.
// bit 7:0     chan4 data sample pointer vs edge of the PDM_DCLK.
#define P_PDMB_COEFF_ADDR ((volatile uint32_t *)0xfe334824)
// address of the write/read of coeff data.
#define P_PDMB_COEFF_DATA ((volatile uint32_t *)0xfe334828)
// write/read data to coeff memory.
#define P_PDMB_CLKG_CTRL ((volatile uint32_t *)0xfe33482c)
// auto clock gating control.  1: disable the clock gating function. the clock will awlays
// enabled. 0 : use RTL auto clock gating.
// 31:7 not used.
// bit 6  filt_ctrl module auto clock gating control.
// bit 5  sinc fifo module auto clock gating control.
// bit 4  filter module auto clock gating control.
// bit 3  apb module auto clock gating control.
// bit 2  coeff memory module auto clock gating control.
// bit 1  each channel module auto clock gating control.
// bit 0 cts_pdm_clk   auto clock gating control.
#define P_PDMB_STS ((volatile uint32_t *)0xfe334830)
// bit 1  HPF filter output overflow.  means the PCLK is too slow.
// bit 0  HCIC filter output overflow. means the CTS_PDM_CLK is too slow. can't finished the
// filter function.
#define P_PDMB_MUTE_VALUE ((volatile uint32_t *)0xfe334834)
#define P_PDMB_MASK_NUM ((volatile uint32_t *)0xfe334838)
#define P_PDMB_CHAN_CTRL2 ((volatile uint32_t *)0xfe33483c)
// bit 7:0    second sample and start FSM point vs rise edge of PDM_DCLK
//========================================================================
//  EQ DRC - Registers
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe332000
// -----------------------------------------------
#define P_AED_COEF_RAM_CNTL ((volatile uint32_t *)0xfe332000)
#define P_AED_COEF_RAM_DATA ((volatile uint32_t *)0xfe332004)
#define P_AED_EQ_EN ((volatile uint32_t *)0xfe332008)
#define P_AED_EQ_TAP_CNTL ((volatile uint32_t *)0xfe33200c)
#define P_AED_EQ_VOLUME ((volatile uint32_t *)0xfe332010)
#define P_AED_EQ_VOLUME_SLEW_CNT ((volatile uint32_t *)0xfe332014)
#define P_AED_MUTE ((volatile uint32_t *)0xfe332018)
#define P_AED_DRC_CNTL ((volatile uint32_t *)0xfe33201c)
#define P_AED_DRC_RMS_COEF0 ((volatile uint32_t *)0xfe332020)
#define P_AED_DRC_RMS_COEF1 ((volatile uint32_t *)0xfe332024)
#define P_AED_DRC_THD0 ((volatile uint32_t *)0xfe332028)
#define P_AED_DRC_THD1 ((volatile uint32_t *)0xfe33202c)
#define P_AED_DRC_THD2 ((volatile uint32_t *)0xfe332030)
#define P_AED_DRC_THD3 ((volatile uint32_t *)0xfe332034)
#define P_AED_DRC_THD4 ((volatile uint32_t *)0xfe332038)
#define P_AED_DRC_K0 ((volatile uint32_t *)0xfe33203c)
#define P_AED_DRC_K1 ((volatile uint32_t *)0xfe332040)
#define P_AED_DRC_K2 ((volatile uint32_t *)0xfe332044)
#define P_AED_DRC_K3 ((volatile uint32_t *)0xfe332048)
#define P_AED_DRC_K4 ((volatile uint32_t *)0xfe33204c)
#define P_AED_DRC_K5 ((volatile uint32_t *)0xfe332050)
#define P_AED_DRC_THD_OUT0 ((volatile uint32_t *)0xfe332054)
#define P_AED_DRC_THD_OUT1 ((volatile uint32_t *)0xfe332058)
#define P_AED_DRC_THD_OUT2 ((volatile uint32_t *)0xfe33205c)
#define P_AED_DRC_THD_OUT3 ((volatile uint32_t *)0xfe332060)
#define P_AED_DRC_OFFSET ((volatile uint32_t *)0xfe332064)
#define P_AED_DRC_RELEASE_COEF00 ((volatile uint32_t *)0xfe332068)
#define P_AED_DRC_RELEASE_COEF01 ((volatile uint32_t *)0xfe33206c)
#define P_AED_DRC_RELEASE_COEF10 ((volatile uint32_t *)0xfe332070)
#define P_AED_DRC_RELEASE_COEF11 ((volatile uint32_t *)0xfe332074)
#define P_AED_DRC_RELEASE_COEF20 ((volatile uint32_t *)0xfe332078)
#define P_AED_DRC_RELEASE_COEF21 ((volatile uint32_t *)0xfe33207c)
#define P_AED_DRC_RELEASE_COEF30 ((volatile uint32_t *)0xfe332080)
#define P_AED_DRC_RELEASE_COEF31 ((volatile uint32_t *)0xfe332084)
#define P_AED_DRC_RELEASE_COEF40 ((volatile uint32_t *)0xfe332088)
#define P_AED_DRC_RELEASE_COEF41 ((volatile uint32_t *)0xfe33208c)
#define P_AED_DRC_RELEASE_COEF50 ((volatile uint32_t *)0xfe332090)
#define P_AED_DRC_RELEASE_COEF51 ((volatile uint32_t *)0xfe332094)
#define P_AED_DRC_ATTACK_COEF00 ((volatile uint32_t *)0xfe332098)
#define P_AED_DRC_ATTACK_COEF01 ((volatile uint32_t *)0xfe33209c)
#define P_AED_DRC_ATTACK_COEF10 ((volatile uint32_t *)0xfe3320a0)
#define P_AED_DRC_ATTACK_COEF11 ((volatile uint32_t *)0xfe3320a4)
#define P_AED_DRC_ATTACK_COEF20 ((volatile uint32_t *)0xfe3320a8)
#define P_AED_DRC_ATTACK_COEF21 ((volatile uint32_t *)0xfe3320ac)
#define P_AED_DRC_ATTACK_COEF30 ((volatile uint32_t *)0xfe3320b0)
#define P_AED_DRC_ATTACK_COEF31 ((volatile uint32_t *)0xfe3320b4)
#define P_AED_DRC_ATTACK_COEF40 ((volatile uint32_t *)0xfe3320b8)
#define P_AED_DRC_ATTACK_COEF41 ((volatile uint32_t *)0xfe3320bc)
#define P_AED_DRC_ATTACK_COEF50 ((volatile uint32_t *)0xfe3320c0)
#define P_AED_DRC_ATTACK_COEF51 ((volatile uint32_t *)0xfe3320c4)
#define P_AED_DRC_LOOPBACK_CNTL ((volatile uint32_t *)0xfe3320c8)
#define P_AED_MDRC_CNTL ((volatile uint32_t *)0xfe3320cc)
#define P_AED_MDRC_RMS_COEF00 ((volatile uint32_t *)0xfe3320d0)
#define P_AED_MDRC_RMS_COEF01 ((volatile uint32_t *)0xfe3320d4)
#define P_AED_MDRC_RELEASE_COEF00 ((volatile uint32_t *)0xfe3320d8)
#define P_AED_MDRC_RELEASE_COEF01 ((volatile uint32_t *)0xfe3320dc)
#define P_AED_MDRC_ATTACK_COEF00 ((volatile uint32_t *)0xfe3320e0)
#define P_AED_MDRC_ATTACK_COEF01 ((volatile uint32_t *)0xfe3320e4)
#define P_AED_MDRC_THD0 ((volatile uint32_t *)0xfe3320e8)
#define P_AED_MDRC_K0 ((volatile uint32_t *)0xfe3320ec)
#define P_AED_MDRC_LOW_GAIN ((volatile uint32_t *)0xfe3320f0)
#define P_AED_MDRC_OFFSET0 ((volatile uint32_t *)0xfe3320f4)
#define P_AED_MDRC_RMS_COEF10 ((volatile uint32_t *)0xfe3320f8)
#define P_AED_MDRC_RMS_COEF11 ((volatile uint32_t *)0xfe3320fc)
#define P_AED_MDRC_RELEASE_COEF10 ((volatile uint32_t *)0xfe332100)
#define P_AED_MDRC_RELEASE_COEF11 ((volatile uint32_t *)0xfe332104)
#define P_AED_MDRC_ATTACK_COEF10 ((volatile uint32_t *)0xfe332108)
#define P_AED_MDRC_ATTACK_COEF11 ((volatile uint32_t *)0xfe33210c)
#define P_AED_MDRC_THD1 ((volatile uint32_t *)0xfe332110)
#define P_AED_MDRC_K1 ((volatile uint32_t *)0xfe332114)
#define P_AED_MDRC_OFFSET1 ((volatile uint32_t *)0xfe332118)
#define P_AED_MDRC_MID_GAIN ((volatile uint32_t *)0xfe33211c)
#define P_AED_MDRC_RMS_COEF20 ((volatile uint32_t *)0xfe332120)
#define P_AED_MDRC_RMS_COEF21 ((volatile uint32_t *)0xfe332124)
#define P_AED_MDRC_RELEASE_COEF20 ((volatile uint32_t *)0xfe332128)
#define P_AED_MDRC_RELEASE_COEF21 ((volatile uint32_t *)0xfe33212c)
#define P_AED_MDRC_ATTACK_COEF20 ((volatile uint32_t *)0xfe332130)
#define P_AED_MDRC_ATTACK_COEF21 ((volatile uint32_t *)0xfe332134)
#define P_AED_MDRC_THD2 ((volatile uint32_t *)0xfe332138)
#define P_AED_MDRC_K2 ((volatile uint32_t *)0xfe33213c)
#define P_AED_MDRC_OFFSET2 ((volatile uint32_t *)0xfe332140)
#define P_AED_MDRC_HIGH_GAIN ((volatile uint32_t *)0xfe332144)
#define P_AED_ED_CNTL ((volatile uint32_t *)0xfe332148)
#define P_AED_DC_EN ((volatile uint32_t *)0xfe33214c)
#define P_AED_ND_LOW_THD ((volatile uint32_t *)0xfe332150)
#define P_AED_ND_HIGH_THD ((volatile uint32_t *)0xfe332154)
#define P_AED_ND_CNT_THD ((volatile uint32_t *)0xfe332158)
#define P_AED_ND_SUM_NUM ((volatile uint32_t *)0xfe33215c)
#define P_AED_ND_CZ_NUM ((volatile uint32_t *)0xfe332160)
#define P_AED_ND_SUM_THD0 ((volatile uint32_t *)0xfe332164)
#define P_AED_ND_SUM_THD1 ((volatile uint32_t *)0xfe332168)
#define P_AED_ND_CZ_THD0 ((volatile uint32_t *)0xfe33216c)
#define P_AED_ND_CZ_THD1 ((volatile uint32_t *)0xfe332170)
#define P_AED_ND_COND_CNTL ((volatile uint32_t *)0xfe332174)
#define P_AED_ND_RELEASE_COEF0 ((volatile uint32_t *)0xfe332178)
#define P_AED_ND_RELEASE_COEF1 ((volatile uint32_t *)0xfe33217c)
#define P_AED_ND_ATTACK_COEF0 ((volatile uint32_t *)0xfe332180)
#define P_AED_ND_ATTACK_COEF1 ((volatile uint32_t *)0xfe332184)
#define P_AED_ND_CNTL ((volatile uint32_t *)0xfe332188)
#define P_AED_MIX0_LL ((volatile uint32_t *)0xfe33218c)
#define P_AED_MIX0_RL ((volatile uint32_t *)0xfe332190)
#define P_AED_MIX0_LR ((volatile uint32_t *)0xfe332194)
#define P_AED_MIX0_RR ((volatile uint32_t *)0xfe332198)
#define P_AED_CLIP_THD ((volatile uint32_t *)0xfe33219c)
#define P_AED_CH1_ND_SUM_OUT ((volatile uint32_t *)0xfe3321a0)
#define P_AED_CH2_ND_SUM_OUT ((volatile uint32_t *)0xfe3321a4)
#define P_AED_CH1_ND_CZ_OUT ((volatile uint32_t *)0xfe3321a8)
#define P_AED_CH2_ND_CZ_OUT ((volatile uint32_t *)0xfe3321ac)
#define P_AED_NOISE_STATUS ((volatile uint32_t *)0xfe3321b0)
#define P_AED_POW_CURRENT_S0 ((volatile uint32_t *)0xfe3321b4)
#define P_AED_POW_CURRENT_S1 ((volatile uint32_t *)0xfe3321b8)
#define P_AED_POW_CURRENT_S2 ((volatile uint32_t *)0xfe3321bc)
#define P_AED_POW_OUT0 ((volatile uint32_t *)0xfe3321c0)
#define P_AED_POW_OUT1 ((volatile uint32_t *)0xfe3321c4)
#define P_AED_POW_OUT2 ((volatile uint32_t *)0xfe3321c8)
#define P_AED_POW_ADJ_INDEX0 ((volatile uint32_t *)0xfe3321cc)
#define P_AED_POW_ADJ_INDEX1 ((volatile uint32_t *)0xfe3321d0)
#define P_AED_POW_ADJ_INDEX2 ((volatile uint32_t *)0xfe3321d4)
#define P_AED_DRC_GAIN_INDEX0 ((volatile uint32_t *)0xfe3321d8)
#define P_AED_DRC_GAIN_INDEX1 ((volatile uint32_t *)0xfe3321dc)
#define P_AED_DRC_GAIN_INDEX2 ((volatile uint32_t *)0xfe3321e0)
#define P_AED_CH1_VOLUME_STATE ((volatile uint32_t *)0xfe3321e4)
#define P_AED_CH2_VOLUME_STATE ((volatile uint32_t *)0xfe3321e8)
#define P_AED_CH1_VOLUME_GAIN ((volatile uint32_t *)0xfe3321ec)
#define P_AED_CH2_VOLUME_GAIN ((volatile uint32_t *)0xfe3321f0)
#define P_AED_FULL_POW_CURRENT ((volatile uint32_t *)0xfe3321f4)
#define P_AED_FULL_POW_OUT ((volatile uint32_t *)0xfe3321f8)
#define P_AED_FULL_POW_ADJ ((volatile uint32_t *)0xfe3321fc)
#define P_AED_FULL_DRC_GAIN ((volatile uint32_t *)0xfe332200)
#define P_AED_MASTER_VOLUME_STATE ((volatile uint32_t *)0xfe332204)
#define P_AED_MASTER_VOLUME_GAIN ((volatile uint32_t *)0xfe332208)
#define P_AED_TOP_CTL0 ((volatile uint32_t *)0xfe33220c)
#define P_AED_TOP_CTL1 ((volatile uint32_t *)0xfe332210)
#define P_AED_TOP_CTL2 ((volatile uint32_t *)0xfe332214)
#define P_AED_TOP_ST0 ((volatile uint32_t *)0xfe332218)
#define P_AED_TOP_ST1 ((volatile uint32_t *)0xfe33221c)
#define P_AED_EQDRC_DYNAMIC_CNTL ((volatile uint32_t *)0xfe332240)
#define P_AED_COEF_RAM_CNTL_B ((volatile uint32_t *)0xfe332244)
#define P_AED_COEF_RAM_DATA_B ((volatile uint32_t *)0xfe332248)
#define P_AED_DRC_RMS_COEF0_B ((volatile uint32_t *)0xfe33224c)
#define P_AED_DRC_RMS_COEF1_B ((volatile uint32_t *)0xfe332250)
#define P_AED_DRC_THD0_B ((volatile uint32_t *)0xfe332254)
#define P_AED_DRC_THD1_B ((volatile uint32_t *)0xfe332258)
#define P_AED_DRC_THD2_B ((volatile uint32_t *)0xfe33225c)
#define P_AED_DRC_THD3_B ((volatile uint32_t *)0xfe332260)
#define P_AED_DRC_THD4_B ((volatile uint32_t *)0xfe332264)
#define P_AED_DRC_K0_B ((volatile uint32_t *)0xfe332268)
#define P_AED_DRC_K1_B ((volatile uint32_t *)0xfe33226c)
#define P_AED_DRC_K2_B ((volatile uint32_t *)0xfe332270)
#define P_AED_DRC_K3_B ((volatile uint32_t *)0xfe332274)
#define P_AED_DRC_K4_B ((volatile uint32_t *)0xfe332278)
#define P_AED_DRC_K5_B ((volatile uint32_t *)0xfe33227c)
#define P_AED_DRC_THD_OUT0_B ((volatile uint32_t *)0xfe332280)
#define P_AED_DRC_THD_OUT1_B ((volatile uint32_t *)0xfe332284)
#define P_AED_DRC_THD_OUT2_B ((volatile uint32_t *)0xfe332288)
#define P_AED_DRC_THD_OUT3_B ((volatile uint32_t *)0xfe33228c)
#define P_AED_DRC_OFFSET_B ((volatile uint32_t *)0xfe332290)
#define P_AED_DRC_RELEASE_COEF00_B ((volatile uint32_t *)0xfe332294)
#define P_AED_DRC_RELEASE_COEF01_B ((volatile uint32_t *)0xfe332298)
#define P_AED_DRC_RELEASE_COEF10_B ((volatile uint32_t *)0xfe33229c)
#define P_AED_DRC_RELEASE_COEF11_B ((volatile uint32_t *)0xfe3322a0)
#define P_AED_DRC_RELEASE_COEF20_B ((volatile uint32_t *)0xfe3322a4)
#define P_AED_DRC_RELEASE_COEF21_B ((volatile uint32_t *)0xfe3322a8)
#define P_AED_DRC_RELEASE_COEF30_B ((volatile uint32_t *)0xfe3322ac)
#define P_AED_DRC_RELEASE_COEF31_B ((volatile uint32_t *)0xfe3322b0)
#define P_AED_DRC_RELEASE_COEF40_B ((volatile uint32_t *)0xfe3322b4)
#define P_AED_DRC_RELEASE_COEF41_B ((volatile uint32_t *)0xfe3322b8)
#define P_AED_DRC_RELEASE_COEF50_B ((volatile uint32_t *)0xfe3322bc)
#define P_AED_DRC_RELEASE_COEF51_B ((volatile uint32_t *)0xfe3322c0)
#define P_AED_DRC_ATTACK_COEF00_B ((volatile uint32_t *)0xfe3322c4)
#define P_AED_DRC_ATTACK_COEF01_B ((volatile uint32_t *)0xfe3322c8)
#define P_AED_DRC_ATTACK_COEF10_B ((volatile uint32_t *)0xfe3322cc)
#define P_AED_DRC_ATTACK_COEF11_B ((volatile uint32_t *)0xfe3322d0)
#define P_AED_DRC_ATTACK_COEF20_B ((volatile uint32_t *)0xfe3322d4)
#define P_AED_DRC_ATTACK_COEF21_B ((volatile uint32_t *)0xfe3322d8)
#define P_AED_DRC_ATTACK_COEF30_B ((volatile uint32_t *)0xfe3322dc)
#define P_AED_DRC_ATTACK_COEF31_B ((volatile uint32_t *)0xfe3322e0)
#define P_AED_DRC_ATTACK_COEF40_B ((volatile uint32_t *)0xfe3322e4)
#define P_AED_DRC_ATTACK_COEF41_B ((volatile uint32_t *)0xfe3322e8)
#define P_AED_DRC_ATTACK_COEF50_B ((volatile uint32_t *)0xfe3322ec)
#define P_AED_DRC_ATTACK_COEF51_B ((volatile uint32_t *)0xfe3322f0)
#define P_AED_MDRC_RMS_COEF00_B ((volatile uint32_t *)0xfe3322f4)
#define P_AED_MDRC_RMS_COEF01_B ((volatile uint32_t *)0xfe3322f8)
#define P_AED_MDRC_RMS_COEF10_B ((volatile uint32_t *)0xfe3322fc)
#define P_AED_MDRC_RMS_COEF11_B ((volatile uint32_t *)0xfe332300)
#define P_AED_MDRC_RMS_COEF20_B ((volatile uint32_t *)0xfe332304)
#define P_AED_MDRC_RMS_COEF21_B ((volatile uint32_t *)0xfe332308)
#define P_AED_MDRC_RELEASE_COEF00_B ((volatile uint32_t *)0xfe33230c)
#define P_AED_MDRC_RELEASE_COEF01_B ((volatile uint32_t *)0xfe332310)
#define P_AED_MDRC_RELEASE_COEF10_B ((volatile uint32_t *)0xfe332314)
#define P_AED_MDRC_RELEASE_COEF11_B ((volatile uint32_t *)0xfe332318)
#define P_AED_MDRC_RELEASE_COEF20_B ((volatile uint32_t *)0xfe33231c)
#define P_AED_MDRC_RELEASE_COEF21_B ((volatile uint32_t *)0xfe332320)
#define P_AED_MDRC_ATTACK_COEF00_B ((volatile uint32_t *)0xfe332324)
#define P_AED_MDRC_ATTACK_COEF01_B ((volatile uint32_t *)0xfe332328)
#define P_AED_MDRC_ATTACK_COEF10_B ((volatile uint32_t *)0xfe33232c)
#define P_AED_MDRC_ATTACK_COEF11_B ((volatile uint32_t *)0xfe332330)
#define P_AED_MDRC_ATTACK_COEF20_B ((volatile uint32_t *)0xfe332334)
#define P_AED_MDRC_ATTACK_COEF21_B ((volatile uint32_t *)0xfe332338)
#define P_AED_MDRC_THD0_B ((volatile uint32_t *)0xfe33233c)
#define P_AED_MDRC_THD1_B ((volatile uint32_t *)0xfe332340)
#define P_AED_MDRC_THD2_B ((volatile uint32_t *)0xfe332344)
#define P_AED_MDRC_K0_B ((volatile uint32_t *)0xfe332348)
#define P_AED_MDRC_K1_B ((volatile uint32_t *)0xfe33234c)
#define P_AED_MDRC_K2_B ((volatile uint32_t *)0xfe332350)
#define P_AED_MDRC_OFFSET0_B ((volatile uint32_t *)0xfe332354)
#define P_AED_MDRC_OFFSET1_B ((volatile uint32_t *)0xfe332358)
#define P_AED_MDRC_OFFSET2_B ((volatile uint32_t *)0xfe33235c)
#define P_AED_MDRC_LOW_GAIN_B ((volatile uint32_t *)0xfe332360)
#define P_AED_MDRC_MID_GAIN_B ((volatile uint32_t *)0xfe332364)
#define P_AED_MDRC_HIGH_GAIN_B ((volatile uint32_t *)0xfe332368)
#define P_AED_DRC_CNTL_B ((volatile uint32_t *)0xfe33236c)
#define P_AED_DRC_LOOPBACK_CNTL_B ((volatile uint32_t *)0xfe332370)
#define P_AED_MDRC_CNTL_B ((volatile uint32_t *)0xfe332374)
#define P_AED_STATUS_REG ((volatile uint32_t *)0xfe332378)
//========================================================================
//  AUDIO locker - Registers
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe331400
// -----------------------------------------------
#define P_AUD_LOCK_EN ((volatile uint32_t *)0xfe331400)
#define P_AUD_LOCK_SW_RESET ((volatile uint32_t *)0xfe331404)
#define P_AUD_LOCK_SW_LATCH ((volatile uint32_t *)0xfe331408)
#define P_AUD_LOCK_HW_LATCH ((volatile uint32_t *)0xfe33140c)
#define P_AUD_LOCK_REFCLK_SRC ((volatile uint32_t *)0xfe331410)
#define P_AUD_LOCK_REFCLK_LAT_INT ((volatile uint32_t *)0xfe331414)
#define P_AUD_LOCK_IMCLK_LAT_INT ((volatile uint32_t *)0xfe331418)
#define P_AUD_LOCK_OMCLK_LAT_INT ((volatile uint32_t *)0xfe33141c)
#define P_AUD_LOCK_REFCLK_DS_INT ((volatile uint32_t *)0xfe331420)
#define P_AUD_LOCK_IMCLK_DS_INT ((volatile uint32_t *)0xfe331424)
#define P_AUD_LOCK_OMCLK_DS_INT ((volatile uint32_t *)0xfe331428)
#define P_AUD_LOCK_INT_CLR ((volatile uint32_t *)0xfe33142c)
#define P_AUD_LOCK_GCLK_CTRL ((volatile uint32_t *)0xfe331430)
#define P_AUD_LOCK_INT_CTRL ((volatile uint32_t *)0xfe331434)
#define P_RO_REF2IMCLK_CNT_L ((volatile uint32_t *)0xfe331440)
#define P_RO_REF2IMCLK_CNT_H ((volatile uint32_t *)0xfe331444)
#define P_RO_REF2OMCLK_CNT_L ((volatile uint32_t *)0xfe331448)
#define P_RO_REF2OMCLK_CNT_H ((volatile uint32_t *)0xfe33144c)
#define P_RO_IMCLK2REF_CNT_L ((volatile uint32_t *)0xfe331450)
#define P_RO_IMCLK2REF_CNT_H ((volatile uint32_t *)0xfe331454)
#define P_RO_OMCLK2REF_CNT_L ((volatile uint32_t *)0xfe331458)
#define P_RO_OMCLK2REF_CNT_H ((volatile uint32_t *)0xfe33145c)
#define P_RO_REFCLK_PKG_CNT ((volatile uint32_t *)0xfe331460)
#define P_RO_IMCLK_PKG_CNT ((volatile uint32_t *)0xfe331464)
#define P_RO_OMCLK_PKG_CNT ((volatile uint32_t *)0xfe331468)
#define P_RO_AUD_LOCK_INT_STATUS ((volatile uint32_t *)0xfe33146c)
//========================================================================
//  AUDIO lockerB - Registers
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe334400
// -----------------------------------------------
#define P_AUD_LOCKB_EN ((volatile uint32_t *)0xfe334400)
#define P_AUD_LOCKB_SW_RESET ((volatile uint32_t *)0xfe334404)
#define P_AUD_LOCKB_SW_LATCH ((volatile uint32_t *)0xfe334408)
#define P_AUD_LOCKB_HW_LATCH ((volatile uint32_t *)0xfe33440c)
#define P_AUD_LOCKB_REFCLK_SRC ((volatile uint32_t *)0xfe334410)
#define P_AUD_LOCKB_REFCLK_LAT_INT ((volatile uint32_t *)0xfe334414)
#define P_AUD_LOCKB_IMCLK_LAT_INT ((volatile uint32_t *)0xfe334418)
#define P_AUD_LOCKB_OMCLK_LAT_INT ((volatile uint32_t *)0xfe33441c)
#define P_AUD_LOCKB_REFCLK_DS_INT ((volatile uint32_t *)0xfe334420)
#define P_AUD_LOCKB_IMCLK_DS_INT ((volatile uint32_t *)0xfe334424)
#define P_AUD_LOCKB_OMCLK_DS_INT ((volatile uint32_t *)0xfe334428)
#define P_AUD_LOCKB_INT_CLR ((volatile uint32_t *)0xfe33442c)
#define P_AUD_LOCKB_GCLK_CTRL ((volatile uint32_t *)0xfe334430)
#define P_AUD_LOCKB_INT_CTRL ((volatile uint32_t *)0xfe334434)
#define P_ROB_REF2IMCLK_CNT_L ((volatile uint32_t *)0xfe334440)
#define P_ROB_REF2IMCLK_CNT_H ((volatile uint32_t *)0xfe334444)
#define P_ROB_REF2OMCLK_CNT_L ((volatile uint32_t *)0xfe334448)
#define P_ROB_REF2OMCLK_CNT_H ((volatile uint32_t *)0xfe33444c)
#define P_ROB_IMCLK2REF_CNT_L ((volatile uint32_t *)0xfe334450)
#define P_ROB_IMCLK2REF_CNT_H ((volatile uint32_t *)0xfe334454)
#define P_ROB_OMCLK2REF_CNT_L ((volatile uint32_t *)0xfe334458)
#define P_ROB_OMCLK2REF_CNT_H ((volatile uint32_t *)0xfe33445c)
#define P_ROB_REFCLK_PKG_CNT ((volatile uint32_t *)0xfe334460)
#define P_ROB_IMCLK_PKG_CNT ((volatile uint32_t *)0xfe334464)
#define P_ROB_OMCLK_PKG_CNT ((volatile uint32_t *)0xfe334468)
#define P_ROB_AUD_LOCK_INT_STATUS ((volatile uint32_t *)0xfe33446c)
//========================================================================
//  AUDIO VAD - Registers
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe331800
// -----------------------------------------------
//
// Reading file:  VAD_REG.h
//
#define P_VAD_TOP_CTRL0 ((volatile uint32_t *)0xfe331800)
#define P_VAD_TOP_CTRL1 ((volatile uint32_t *)0xfe331804)
#define P_VAD_TOP_CTRL2 ((volatile uint32_t *)0xfe331808)
#define P_VAD_FIR_CTRL ((volatile uint32_t *)0xfe33180c)
#define P_VAD_FIR_EMP ((volatile uint32_t *)0xfe331810)
#define P_VAD_FIR_COEF0 ((volatile uint32_t *)0xfe331814)
#define P_VAD_FIR_COEF1 ((volatile uint32_t *)0xfe331818)
#define P_VAD_FIR_COEF2 ((volatile uint32_t *)0xfe33181c)
#define P_VAD_FIR_COEF3 ((volatile uint32_t *)0xfe331820)
#define P_VAD_FIR_COEF4 ((volatile uint32_t *)0xfe331824)
#define P_VAD_FIR_COEF5 ((volatile uint32_t *)0xfe331828)
#define P_VAD_FIR_COEF6 ((volatile uint32_t *)0xfe33182c)
#define P_VAD_FIR_COEF7 ((volatile uint32_t *)0xfe331830)
#define P_VAD_FIR_COEF8 ((volatile uint32_t *)0xfe331834)
#define P_VAD_FIR_COEF9 ((volatile uint32_t *)0xfe331838)
#define P_VAD_FIR_COEF10 ((volatile uint32_t *)0xfe33183c)
#define P_VAD_FIR_COEF11 ((volatile uint32_t *)0xfe331840)
#define P_VAD_FIR_COEF12 ((volatile uint32_t *)0xfe331844)
#define P_VAD_FRAME_CTRL0 ((volatile uint32_t *)0xfe331848)
#define P_VAD_FRAME_CTRL1 ((volatile uint32_t *)0xfe33184c)
#define P_VAD_FRAME_CTRL2 ((volatile uint32_t *)0xfe331850)
#define P_VAD_CEP_CTRL0 ((volatile uint32_t *)0xfe331854)
#define P_VAD_CEP_CTRL1 ((volatile uint32_t *)0xfe331858)
#define P_VAD_CEP_CTRL2 ((volatile uint32_t *)0xfe33185c)
#define P_VAD_CEP_CTRL3 ((volatile uint32_t *)0xfe331860)
#define P_VAD_CEP_CTRL4 ((volatile uint32_t *)0xfe331864)
#define P_VAD_CEP_CTRL5 ((volatile uint32_t *)0xfe331868)
#define P_VAD_DEC_CTRL ((volatile uint32_t *)0xfe33186c)
#define P_VAD_TOP_STS0 ((volatile uint32_t *)0xfe331870)
#define P_VAD_TOP_STS1 ((volatile uint32_t *)0xfe331874)
#define P_VAD_TOP_STS2 ((volatile uint32_t *)0xfe331878)
#define P_VAD_FIR_STS0 ((volatile uint32_t *)0xfe33187c)
#define P_VAD_FIR_STS1 ((volatile uint32_t *)0xfe331880)
#define P_VAD_POW_STS0 ((volatile uint32_t *)0xfe331884)
#define P_VAD_POW_STS1 ((volatile uint32_t *)0xfe331888)
#define P_VAD_POW_STS2 ((volatile uint32_t *)0xfe33188c)
#define P_VAD_FFT_STS0 ((volatile uint32_t *)0xfe331890)
#define P_VAD_FFT_STS1 ((volatile uint32_t *)0xfe331894)
#define P_VAD_SPE_STS0 ((volatile uint32_t *)0xfe331898)
#define P_VAD_SPE_STS1 ((volatile uint32_t *)0xfe33189c)
#define P_VAD_SPE_STS2 ((volatile uint32_t *)0xfe3318a0)
#define P_VAD_SPE_STS3 ((volatile uint32_t *)0xfe3318a4)
#define P_VAD_DEC_STS0 ((volatile uint32_t *)0xfe3318a8)
#define P_VAD_DEC_STS1 ((volatile uint32_t *)0xfe3318ac)
#define P_VAD_LUT_CTRL ((volatile uint32_t *)0xfe3318b0)
#define P_VAD_LUT_WR ((volatile uint32_t *)0xfe3318b4)
#define P_VAD_LUT_RD ((volatile uint32_t *)0xfe3318b8)
#define P_VAD_IN_SEL0 ((volatile uint32_t *)0xfe3318bc)
#define P_VAD_IN_SEL1 ((volatile uint32_t *)0xfe3318c0)
#define P_VAD_TO_DDR ((volatile uint32_t *)0xfe3318c4)
#define P_VAD_SYNC_CTRL0 ((volatile uint32_t *)0xfe3318c8)
#define P_VAD_SYNC_CHNUM_ID0 ((volatile uint32_t *)0xfe3318cc)
#define P_VAD_SYNC_CHNUM_ID1 ((volatile uint32_t *)0xfe3318d0)
#define P_VAD_SYNC_CHNUM_ID2 ((volatile uint32_t *)0xfe3318d4)
#define P_VAD_SYNC_CHNUM_ID3 ((volatile uint32_t *)0xfe3318d8)
#define P_VAD_SYNC_CHNUM_ID4 ((volatile uint32_t *)0xfe3318dc)
#define P_VAD_SYNC_CHNUM_ID5 ((volatile uint32_t *)0xfe3318e0)
#define P_VAD_SYNC_CHNUM_ID6 ((volatile uint32_t *)0xfe3318e4)
#define P_VAD_SYNC_CHNUM_ID7 ((volatile uint32_t *)0xfe3318e8)
//
// Closing file:  VAD_REG.h
//
//========================================================================
//  AUDIO RESAMPLEA - Registers
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe331c00
// -----------------------------------------------
//
// Reading file:  RESAMPLE.h
//
#define P_AUDIO_RSAMP_CTRL0 ((volatile uint32_t *)0xfe331c00)
// Bit   31:3      reserved
// Bit   2         reg_lock_rst      //unsigned  , default =0;
// Bit   1         reg_rsamp_rst     //unsigned  , default =0;
// Bit   0         reg_sw_rst        //unsigned  , default =0;
#define P_AUDIO_RSAMP_CTRL1 ((volatile uint32_t *)0xfe331c04)
// Bit   31:27      reg_in_lsb        //unsigned  , default =0;
// Bit   26         reg_watchdog_en   //unsigned  , default =0;
// Bit   25         reg_rsamp_rst_sel //unsigned  , default =0;
// Bit   24         reg_module_bypas  //unsigned  , default =0;
// Bit   23:18      reg_gclk_ctrl     //unsigned  , default =0;
// Bit   17:13      reg_in_msb        //unsigned  , default =23;
// Bit   12         reg_output_en     //unsigned  , default =0;
// Bit   11         reg_rsamp_en      //unsigned  , default =0;
// Bit   10         reg_filt_en       //unsigned  , default =0;
// Bit   9          reg_post_en       //unsigned  , default =0;
// Bit   8          reg_inp_mux_mode  //unsigned  , default =0;
// Bit   7:5        reserved          //unsigned  , default =2;
// Bit   4:0        reg_inp_mux       //unsigned  , default =0;
#define P_AUDIO_RSAMP_CTRL2 ((volatile uint32_t *)0xfe331c08)
// Bit 31:30    reserved              //unsigned  , default =0;
// Bit 29:24    reg_chx_size          //unsigned  , default =2;
// Bit 23:18    reserved              //unsigned  , default =0;
// Bit 17:16    reg_scl_step          //unsigned  , default =0; 0: 1/1  1: 1/2  2: 1/4
// Bit 15:8     reg_filt_tap          //unsigned  , default =63;
// Bit 7:0      reg_intp_tap          //unsigned  , default =63;
#define P_AUDIO_RSAMP_PHSINIT ((volatile uint32_t *)0xfe331c0c)
// Bit   31:28      reserved          //unsigned  , default = 0;
// Bit   27:0       reg_init_phs      //unsigned  , default = 0;
#define P_AUDIO_RSAMP_PHSSTEP ((volatile uint32_t *)0xfe331c10)
// Bit   31         reserved          //unsigned  , default = 0;
// Bit   30:0       reg_rsamp_step    //unsigned  , default = 134217728;//'h800_0000
#define P_AUDIO_RSAMP_SHIFT ((volatile uint32_t *)0xfe331c14)
// Bit   31:24       reg_rsft_iir    //unsigned  , default = 23;
// Bit   23:16       reg_rsft_blnd   //unsigned  , default = 21;
// Bit   15:8        reg_rsft_sinc   //unsigned  , default = 31;
// Bit   7:0         reg_rsft_aa     //unsigned  , default = 31;
#define P_AUDIO_RSAMP_ADJ_CTRL0 ((volatile uint32_t *)0xfe331c18)
// Bit   31:7        reserved                //unsigned
// Bit   6           reg_lock_vld_sel        //unsigned , default = 0;
// Bit   5           reg_loop_dif_clr_en     //unsigned , default = 0;
// Bit   4           reg_aout_force_en       //unsigned , default = 0;
// Bit   3           reserved                //unsigned
// Bit   2           reg_rsamp_adj_out_inv   //unsigned , default = 0;
// Bit   1           reg_rsamp_adj_force_en  //unsigned , default = 0;
// Bit   0           reg_rsamp_adj_en        //unsigned , default = 0;
#define P_AUDIO_RSAMP_ADJ_CTRL1 ((volatile uint32_t *)0xfe331c1c)
// Bit   31:16       reg_rsamp_adj_odet_step     //unsigned , default = 8;
// Bit   15:0        reg_rsamp_adj_kmax          //unsigned , default = 32768;
#define P_AUDIO_RSAMP_ADJ_SFT ((volatile uint32_t *)0xfe331c20)
// Bit   31:30       reserved                //unsigned , default = 0;
// Bit   29          reg_rsamp_adj_dif_sel   //unsigned , default = 0;
// Bit   28:24       reg_rsamp_adj_ki        //unsigned , default = 9;
// Bit   23:21       reserved                //unsigned , default = 0;
// Bit   20:16       reg_rsamp_adj_kp        //unsigned , default = 1;
// Bit   15:13       reserved                //unsigned , default = 0;
// Bit   12:8        reg_rsamp_adj_ki_sft    //unsigned , default = 6;
// Bit   7:6         reserved                //unsigned , default = 0;
// Bit   5:0         reg_rsamp_adj_out_sft   //unsigned , default = 12;
#define P_AUDIO_RSAMP_ADJ_IDET_LEN ((volatile uint32_t *)0xfe331c24)
// Bit   31:0       reg_rsamp_adj_idet_len       //unsigned , default = 10000;
#define P_AUDIO_RSAMP_ADJ_FORCE ((volatile uint32_t *)0xfe331c28)
// Bit   31:0       reg_rsamp_adj_force_err      //signed , default = 8;
#define P_AUDIO_RSAMP_ADJ_KI_FORCE ((volatile uint32_t *)0xfe331c2c)
// Bit   31:0       reg_rsamp_adj_ki_force //signed , default = 0;
#define P_AUDIO_RSAMP_WATCHDOG_THRD ((volatile uint32_t *)0xfe331c30)
// Bit   31:0       reg_watchdog_thrd      //signed , default = 32'h1000;
#define P_AUDIO_RSAMP_DBG_INFO ((volatile uint32_t *)0xfe331c34)
// Bit   31:16      reg_aout_force_hi        //unsigned , default = 0;
// Bit   15:7       reserved                 //unsigned , default = 0;
// Bit   6          reg_rsamp_dbgcnt_clr     //unsigned , default = 0;
// Bit   5          reg_rsamp_dbgcnt_vldsel  //unsigned , default = 0;
// Bit   4          reg_rsamp_dbgcnt_en      //unsigned , default = 0;
// Bit   3          reserved                 //unsigned , default = 0;
// Bit   2:0        reg_watchdog_rstsel      //unsigned , default = 4;
#define P_AUDIO_RSAMP_AOUT_FORCE ((volatile uint32_t *)0xfe331c38)
// Bit   31:0       reg_aout_force_lo        //unsigned , default = 0;
#define P_AUDIO_RSAMP_IRQ_CTRL ((volatile uint32_t *)0xfe331c3c)
// Bit   31:16      reg_irq_thrd             //unsigned , default = 0;
// Bit   15:12      reserved                 //unsigned , default = 0;
// Bit   11:8       reg_irq_sel              //unsigned , default = 0;
// Bit   7:4        reg_irq_clr              //unsigned , default = 0;
// Bit   3:0        reg_irq_en               //unsigned , default = 0;
#define P_AUDIO_RSAMP_RO_STATUS ((volatile uint32_t *)0xfe331c40)
// Bit   31:0       ro_rsamp_stat  //{din_chx_chk_err,is_idle_st,rsamp_fifo_over_cnt[7:0]}
#define P_AUDIO_RSAMP_RO_ADJ_FREQ ((volatile uint32_t *)0xfe331c44)
// Bit   31:0       ro_rsamp_adj_freq
#define P_AUDIO_RSAMP_RO_ADJ_DIFF_BAK ((volatile uint32_t *)0xfe331c48)
// Bit   31:0       ro_det_diff_bak
#define P_AUDIO_RSAMP_RO_ADJ_DIFF_DLT ((volatile uint32_t *)0xfe331c4c)
// Bit   31:0       ro_det_diff_dlt
#define P_AUDIO_RSAMP_RO_ADJ_PHS_ERR ((volatile uint32_t *)0xfe331c50)
// Bit   31:0       ro_det_phase_err
#define P_AUDIO_RSAMP_RO_ADJ_KI_OUT ((volatile uint32_t *)0xfe331c54)
// Bit   31:0       ro_rsamp_ki_out
#define P_AUDIO_RSAMP_RO_IN_CNT ((volatile uint32_t *)0xfe331c58)
// Bit   31:0       ro_rsamp_in_cnt
#define P_AUDIO_RSAMP_RO_OUT_CNT ((volatile uint32_t *)0xfe331c5c)
// Bit   31:0       ro_rsamp_out_cnt
#define P_AUDIO_RSAMP_RO_ADJ_PHS_ERR_VAR ((volatile uint32_t *)0xfe331c60)
// Bit   31:0       ro_det_phase_err_var
#define P_AUDIO_RSAMP_POST_COEF0 ((volatile uint32_t *)0xfe331c80)
// Bit   31:0       reg_post_coef0 //signed  , default = 0;
#define P_AUDIO_RSAMP_POST_COEF1 ((volatile uint32_t *)0xfe331c84)
// Bit   31:0       reg_post_coef1 //signed  , default = 0;
#define P_AUDIO_RSAMP_POST_COEF2 ((volatile uint32_t *)0xfe331c88)
// Bit   31:0       reg_post_coef2 //signed  , default = 0;
#define P_AUDIO_RSAMP_POST_COEF3 ((volatile uint32_t *)0xfe331c8c)
// Bit   31:0       reg_post_coef3 //signed  , default = 0;
#define P_AUDIO_RSAMP_POST_COEF4 ((volatile uint32_t *)0xfe331c90)
// Bit   31:0       reg_post_coef4 //signed  , default = 0;
#define P_AUDIO_RSAMP_AA_COEF_ADDR ((volatile uint32_t *)0xfe331cc0)
// Bit   31:0       reg_aa_coef_addr     //unsigned, default = 0;
#define P_AUDIO_RSAMP_AA_COEF_DATA ((volatile uint32_t *)0xfe331cc4)
// Bit   31:0       reg_aa_coef_data     //signed  , default = 0;
#define P_AUDIO_RSAMP_SINC_COEF_ADDR ((volatile uint32_t *)0xfe331d00)
// Bit   31:0       reg_sinc_coef_addr   //unsigned, default = 0;
#define P_AUDIO_RSAMP_SINC_COEF_DATA ((volatile uint32_t *)0xfe331d04)
// Bit   31:0       reg_sinc_coef_data   //signed  , default = 0;
//
// Closing file:  RESAMPLE.h
//
//========================================================================
//  AUDIO EARCTX_CMDC - Registers
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe333000
// -----------------------------------------------
//
// Reading file:  earc_tx_cmdc.h
//
#define P_EARC_TX_CMDC_TOP_CTRL0 ((volatile uint32_t *)0xfe3330c0)
// Bit   31   ,      idle2_int          unsigned, default = 0, 1: enable
// Bit   30   ,      idle1_int            unsigned, default = 0, 1: enable
// Bit   29   ,      disc2_int            unsigned, default = 0, 1: enable
// Bit   28   ,      disc1_int            unsigned, default = 0, 1: enable
// Bit   27   ,      earc_int             unsigned, default = 0, 1: enable
// Bit   26   ,      hb_status_int        unsigned, default = 0, 1: enable
// Bit   25   ,      losthb_int           unsigned, default = 0, 1: enable
// Bit   24   ,      timeout_int          unsigned, default = 0, 1: enable
// Bit   23   ,      status_ch_int        unsigned, default = 0, 1: enable
// Bit   22   ,      int_recv_finished  unsigned, default = 0, 1: enable
// Bit   21   ,      int_rdata          unsigned, default = 0, 1: enable
// Bit   20   ,      int_recv_nack       unsigned, default = 0, 1: enable
// Bit   19   ,      int_recv_norsp     unsigned, default = 0, 1: enable
// Bit   18   ,      int_recv_unexp     unsigned, default = 0, 1: enable
// Bit   17   ,      int_recv_data       unsigned, default = 0, 1: enable
// Bit   16   ,      int_recv_ack       unsigned, default = 0, 1: enable
// Bit   15   ,      int_recv_ecc_err   unsigned, default = 0, 1: enable
// Bit   14   ,      int_recv_packet    unsigned, default = 0, 1: enable
// Bit   13:0 ,      reserved
#define P_EARC_TX_CMDC_TOP_CTRL1 ((volatile uint32_t *)0xfe3330c4)
// Bit      31:0,     cmdc_top_ctrl1     //unsigned, RW, default = 0,
#define P_EARC_TX_CMDC_TOP_CTRL2 ((volatile uint32_t *)0xfe3330c8)
// Bit   31   ,     reset_idle2_int              unsigned, default = 0, 1: enable
// Bit   30   ,     reset_idle1_int            unsigned, default = 0, 1: enable
// Bit   29   ,     reset_disc2_int            unsigned, default = 0, 1: enable
// Bit   28   ,     reset_disc1_int            unsigned, default = 0, 1: enable
// Bit   27   ,     reset_earc_int             unsigned, default = 0, 1: enable
// Bit   26   ,     reset_hb_status_int        unsigned, default = 0, 1: enable
// Bit   25   ,     reset_losthb_int           unsigned, default = 0, 1: enable
// Bit   24   ,     reset_timeout_int          unsigned, default = 0, 1: enable
// Bit   23   ,     reset_status_ch_int        unsigned, default = 0, 1: enable
// Bit   22   ,     reset_int_recv_finished        unsigned, default = 0, 1: enable
// Bit   21   ,     reset_int_rdata              unsigned, default = 0, 1: enable
// Bit   20   ,     reset_int_recv_nack       unsigned, default = 0, 1: enable
// Bit   19   ,     reset_int_recv_norsp         unsigned, default = 0, 1: enable
// Bit   18   ,     reset_int_recv_unexp         unsigned, default = 0, 1: enable
// Bit   17   ,     reset_int_recv_data       unsigned, default = 0, 1: enable
// Bit   16   ,     reset_int_recv_ack       unsigned, default = 0, 1: enable
// Bit   15   ,     reset_int_recv_ecc_err       unsigned, default = 0, 1: enable
// Bit   14   ,     reset_int_recv_packet        unsigned, default = 0, 1: enable
// Bit 13:0   ,     reserved
#define P_EARC_TX_CMDC_TIMER_CTRL0 ((volatile uint32_t *)0xfe3330cc)
// Bit      31:0,     cmdc_timer_ctrl0   //unsigned, RW, default = 0,
#define P_EARC_TX_CMDC_TIMER_CTRL1 ((volatile uint32_t *)0xfe3330d0)
// Bit      31:0,     cmdc_timer_ctrl1  //unsigned, RW, default = 0,
#define P_EARC_TX_CMDC_TIMER_CTRL2 ((volatile uint32_t *)0xfe3330d4)
// Bit      31:0,     cmdc_timer_ctrl2  //unsigned, RW, default = 0,
#define P_EARC_TX_CMDC_TIMER_CTRL3 ((volatile uint32_t *)0xfe3330d8)
// Bit      31:0,     cmdc_timer_ctrl3  //unsigned, RW, default = 0,
#define P_EARC_TX_CMDC_VSM_CTRL0 ((volatile uint32_t *)0xfe3330dc)
// Bit      31,      sw_state_update         unsigned, default = 0,  XX
// Bit      30:28,   sw_state                 unsigned, default = 0,  XX
// Bit      27,      arc_initiated             unsigned, default = 0,  XX
// Bit      26,      arc_terminated             unsigned, default = 0,  XX
// Bit      25,      arc_enable                 unsigned, default = 1,  XX
// Bit      24,      man_hpd                 unsigned, default = 0,  XX
// Bit      23:22,   hpd_sel                 unsigned, default = 0,  XX
// Bit      21:20,   hpd_sel_earc            unsigned, default = 0,  XX
// Bit      19,      comma_cnt_rst           unsigned, default = 0,  XX
// Bit      18,      timeout_status_rst      unsigned, default = 0,  XX
// Bit      17,      losthb_status_rst       unsigned, default = 0,  XX
// Bit      16,      force_rst               unsigned, default = 0,  XX
// Bit      15,      auto_state_en           unsigned, default = 0,  XX
// Bit      14,      cmdc_state_en             unsigned, default = 0,  XX
// Bit      13,      noack_repeat_en            unsigned, default = 0,  XX
// Bit    12:0,      reserved
#define P_EARC_TX_CMDC_VSM_CTRL1 ((volatile uint32_t *)0xfe3330e0)
// Bit    31:9,      reserved
// Bit       8,      cntl_hpd_sel            unsigned, default = 0, 0:sel hd_hpd,1:sel hdmirx_hpd
// Bit     7:0,      comma_cnt_th            unsigned, default = 0, should bigger than 3 and small
// than 10
#define P_EARC_TX_CMDC_VSM_CTRL2 ((volatile uint32_t *)0xfe3330e4)
// Bit    31:12,      max_count_th          unsigned, default = 0,  disc1 hpd_val timing
// Bit     11:8,      reserved
// Bit        7,      reg_soft_rst          unsigned, default = 0,  disc1 hpd_val timing
// Bit      6:4,      time_sel              unsigned, default = 0,  disc1 hpd_val timing
// Bit      3:2,      soft_rst_sel          unsigned, default = 0,  disc1 hpd_val timing
// Bit      1:0,      enable_ctrl           unsigned, default = 0,  disc1 hpd_val timing
#define P_EARC_TX_CMDC_VSM_CTRL3 ((volatile uint32_t *)0xfe3330e8)
// Bit    31:12,      max_count_th          unsigned, default = 0,  disc2 heartbeat act timing
// Bit     11:8,      reserved
// Bit        7,      reg_soft_rst          unsigned, default = 0,  disc2 heartbeat act timing
// Bit      6:4,      time_sel              unsigned, default = 0,  disc2 heartbeat act timing
// Bit      3:2,      soft_rst_sel          unsigned, default = 0,  disc2 heartbeat act timing
// Bit      1:0,      enable_ctrl           unsigned, default = 0,  disc2 heartbeat act timing
#define P_EARC_TX_CMDC_VSM_CTRL4 ((volatile uint32_t *)0xfe3330ec)
// Bit    31:12,      max_count_th          unsigned, default = 0,  in disc2, no heartbeat ack
// timing Bit     11:8,      reserved Bit        7,      reg_soft_rst          unsigned, default =
// 0,  in disc2, no heartbeat ack timing Bit      6:4,      time_sel              unsigned, default
// = 0,  in disc2, no heartbeat ack timing Bit      3:2,      soft_rst_sel          unsigned,
// default = 0,  in disc2, no heartbeat ack timing Bit      1:0,      enable_ctrl unsigned, default
// = 0,  in disc2, no heartbeat ack timing
#define P_EARC_TX_CMDC_VSM_CTRL5 ((volatile uint32_t *)0xfe3330f0)
// Bit    31:12,      max_count_th          unsigned, default = 0,  in disc1 and disc2 timing out
// Bit     11:8,      reserved
// Bit        7,      reg_soft_rst          unsigned, default = 0,  in disc1 and disc2 timing out
// Bit      6:4,      time_sel              unsigned, default = 0,  in disc1 and disc2 timing out
// Bit      3:2,      soft_rst_sel          unsigned, default = 0,  in disc1 and disc2 timing out
// Bit      1:0,      enable_ctrl           unsigned, default = 0,  in disc1 and disc2 timing out
#define P_EARC_TX_CMDC_VSM_CTRL6 ((volatile uint32_t *)0xfe3330f4)
// Bit    31:12,      max_count_th          unsigned, default = 0,  in earc heartbeat act timing
// Bit     11:8,      reserved
// Bit        7,      reg_soft_rst          unsigned, default = 0,  in earc heartbeat act timing
// Bit      6:4,      time_sel              unsigned, default = 0,  in earc heartbeat act timing
// Bit      3:2,      soft_rst_sel          unsigned, default = 0,  in earc heartbeat act timing
// Bit      1:0,      enable_ctrl           unsigned, default = 0,  in earc heartbeat act timing
#define P_EARC_TX_CMDC_VSM_CTRL7 ((volatile uint32_t *)0xfe3330f8)
// Bit    31:16,      reserved
// Bit     15:8,      status_soft_val       unsigned, default = 0,  in earc heartbeat det timing
// Bit        7,      reg_soft_rst          unsigned, default = 0,  in earc heartbeat det timing
// Bit        6,      status_rst            unsigned, default = 0,  in earc heartbeat det timing
// Bit      5:4,      reserved
// Bit      3:2,      soft_rst_sel          unsigned, default = 0,  in earc heartbeat det timing
// Bit      1:0,      enable_ctrl           unsigned, default = 0,  in earc heartbeat det timing
#define P_EARC_TX_CMDC_VSM_CTRL8 ((volatile uint32_t *)0xfe3330fc)
// Bit      31:0,     cmdc_vsm_ctrl8        //unsigned, RW, default = 0,
#define P_EARC_TX_CMDC_VSM_CTRL9 ((volatile uint32_t *)0xfe333104)
// Bit      31:0,     cmdc_vsm_ctrl9        //unsigned, RW, default = 0
#define P_EARC_TX_CMDC_SENDER_CTRL0 ((volatile uint32_t *)0xfe333108)
// Bit      31:2,     sender_ctrl0                 unsigned,  default = 0,
// Bit      1,        hb_chg_conf_auto             unsigned,  default = 1,
// Bit      0,        hb_chg_auto                  unsigned,  default = 0,
#define P_EARC_TX_CMDC_PACKET_CTRL0 ((volatile uint32_t *)0xfe33310c)
// Bit        31,      packet_mode_enable          unsigned, default = 0,  packet control
// Bit        30,      free_enable                 unsigned, default = 0,  packet control
// Bit        29,      soft_rst                    unsigned, default = 0,  packet control
// Bit     28:24,      tx_ready_threshold          unsigned, default = 0,  packet control
// Bit     23:20,      reserved
// Bit      19:8,      send_pre_threshold          unsigned, default = 0,  packet control
// Bit       7:6,      reserved
// Bit         5,      state_auto_en               unsigned, default = 0, packet control
// Bit         4,      sw_state_update_en          unsigned, default = 0,  packet control
// Bit       3:0,      sw_state_value              unsigned, default = 0,  packet control
#define P_EARC_TX_CMDC_PACKET_CTRL1 ((volatile uint32_t *)0xfe333110)
// Bit        31,      ecc_endian                  unsigned, default = 0,  send
// Bit        30,      pre_start_value             unsigned, default = 0,  send
// Bit     29:21,      reserved
// Bit     20:16,      post_threshold              unsigned, default = 0,  send
// Bit     15:14,      reserved
// Bit      13:8,      pre_threshold               unsigned, default = 0,  XX
// Bit       7:0,      post_flag                   unsigned, default = 0,  XX
#define P_EARC_TX_CMDC_PACKET_CTRL2 ((volatile uint32_t *)0xfe333114)
// Bit      31:0,      pre_flag                    unsigned, default = 0,  XX
#define P_EARC_TX_CMDC_PACKET_CTRL3 ((volatile uint32_t *)0xfe333118)
// Bit      31,       recv_en                      unsigned, default = 0,  XX
// Bit      30,       recv_parity_mask             unsigned, default = 0,  XX
// Bit      29,       recv_timeout_en              unsigned, default = 0,  XX
// Bit      28,       bch_ecc_en                   unsigned, default = 0, xx
// Bit     27:16,     reserved
// Bit      15:0,     recv_timeout_threshold       unsigned, default = 0,  XX
#define P_EARC_TX_CMDC_PACKET_CTRL4 ((volatile uint32_t *)0xfe33311c)
// Bit     31:20,     reserved
// Bit      19:0,     recv_packet_head             unsigned, default = 0,  XX
#define P_EARC_TX_CMDC_PACKET_CTRL5 ((volatile uint32_t *)0xfe333120)
// Bit     31:20,     reserved
// Bit      19:0,     recv_packet_head_mask        unsigned, default = 0,  XX
#define P_EARC_TX_CMDC_PACKET_CTRL6 ((volatile uint32_t *)0xfe333124)
// Bit     31:20,     recv_pre_threshold          unsigned, default = 0,  packet control
// Bit      19:7,     reserved
// Bit         6,     recv_finished_int            unsigned, default = 0,  XX
// Bit         5,     recv_ecc_err_int             unsigned, default = 0,  XX
// Bit         4,     recv_ack_int                 unsigned, default = 0,  XX
// Bit         3,     recv_data_int                unsigned, default = 0,  XX
// Bit         2,     recv_unexp_int               unsigned, default = 0,  XX
// Bit         1,     recv_norsp_int               unsigned, default = 0,  XX
// Bit         0,     recv_nack_int                unsigned, default = 0,  XX
#define P_EARC_TX_CMDC_BIPHASE_CTRL0 ((volatile uint32_t *)0xfe333128)
// Bit     31:24,     reserved
// Bit     23:16,     ack delay threshold           unsigned, default = 0, xx
// Bit     15:10,     reserved
// Bit         9,     send_ack_en                   unsigned, default = 0,  xx
// Bit         8,     sq_val_en                     unsigned, default = 0,  XX
// Bit         7,     biphase_send_soft_rst         unsigned, default = 0,  XX
// Bit         6,     comma_soft_rst                unsigned, default = 0,  XX
// Bit         5,     fifo_rst                      unsigned, default = 0,  XX
// Bit         4,     receiver_no_sender            unsigned, default = 0,  XX
// Bit         3,     sender_free                   unsigned, default = 0,  XX
// Bit         2,     receiver_send                 unsigned, default = 0,  XX
// Bit         1,     receiver_earc                 unsigned, default = 0,  XX
// Bit         0,     receiver_free                 unsigned, default = 0,  XX
#define P_EARC_TX_CMDC_BIPHASE_CTRL1 ((volatile uint32_t *)0xfe33312c)
// Bit     31:16,     reserved
// Bit        15,     ack_enable                    unsigned, default = 0,  send
// Bit      14:8,     reserved
// Bit       7:0,     wait_threshold before ack     unsigned, default = 0,  send
#define P_EARC_TX_CMDC_BIPHASE_CTRL2 ((volatile uint32_t *)0xfe333130)
// Bit        31,     comma_detection_enable        unsigned, default = 0, comma detection
// Bit        30,     manual_reset_enable           unsigned, default = 0, manual reset select, 1:
// manual Bit        29,     manual_reset_value            unsigned, default = 0, manual reset
// control Bit     28:16,     reserved Bit      15:0,     comma_detection_threshold     unsigned,
// default = 0,
#define P_EARC_TX_CMDC_BIPHASE_CTRL3 ((volatile uint32_t *)0xfe333134)
// Bit      31:0,     cmdc_biphase_ctrl3            unsigned, default = 0,
#define P_EARC_TX_CMDC_DEVICE_ID_CTRL ((volatile uint32_t *)0xfe333138)
// Bit        31,     apb_write                     unsigned, default = 0, apb bus wr/read
// Bit        30,     apb_read                      unsigned, default = 0, apb bus wr/read
// Bit        29,     apb_rw_done                  unsigned, default = 0, apb bus wr/read
// Bit        28,     apb_rw_reset                 unsigned, default = 0, apb bus wr/read
// Bit     27:17,     reserved
// Bit        16,     hpb_rst_enable               unsigned, default = 1, hpd rst enable
// Bit      15:8,     apb_rwid                    unsigned, default = 0, apb bus wr/read
// Bit       7:0,     apbrw_start_addr            unsigned, default = 0, apb bus wr/read
#define P_EARC_TX_CMDC_DEVICE_WDATA ((volatile uint32_t *)0xfe33313c)
// Bit      31:8,     reserved
// Bit       7:0,     apb_write_data                unsigned, default = 0, apb bus wr/read
#define P_EARC_TX_CMDC_DEVICE_RDATA ((volatile uint32_t *)0xfe333140)
// Bit      31:8,     reserved
// Bit       7:0,     apb_read_data                 unsigned, default = 0, apb bus wr/read
#define P_EARC_TX_CMDC_MASTER_CTRL ((volatile uint32_t *)0xfe333144)
// Bit        31,     master_cmd_rw                 unsigned, default = 0, 1 write 0 read
// Bit        30,     master_hb_ignore              unsigned, default =0, 0:wait hb issued before
// pkt cmd, 1: pkt cmd issued immediately Bit        29,     master_idle unsigned, default = 0,
// master status Bit        28,     master_cmd_soft_rst           unsigned, default= 0, Bit 27:24,
// hb_cmd_cal_th                 unsigned, default= 0, Bit     23:16,     master_cmd_count
// unsigned, default = 0, cmd count -1 Bit      15:8,     master_cmd_id                 unsigned,
// default = 0, Bit       7:0,     master_cmd_address            unsigned, default = 0,
#define P_EARC_TX_ANA_CTRL0 ((volatile uint32_t *)0xfe333148)
// Bit      31:0,      reg_earctx_ana_ctrl0       //unsigned, RW, default = 0,
#define P_EARC_TX_ANA_CTRL1 ((volatile uint32_t *)0xfe33314c)
// Bit      31:0,      reg_earctx_ana_ctrl1       //unsigned, RW, default = 0,
#define P_EARC_TX_ANA_CTRL2 ((volatile uint32_t *)0xfe333150)
// Bit      31:0,      reg_earctx_ana_ctrl2       //unsigned, RW, default = 0,
#define P_EARC_TX_ANA_CTRL3 ((volatile uint32_t *)0xfe333154)
// Bit      31:0,      reg_earctx_ana_ctrl3       //unsigned, RW, default = 0,
#define P_EARC_TX_ANA_CTRL4 ((volatile uint32_t *)0xfe333158)
// Bit      31:0,      reg_earctx_ana_ctrl4       //unsigned, RW, default = 0,
#define P_EARC_TX_ANA_CTRL5 ((volatile uint32_t *)0xfe33315c)
// Bit      31:0,      reg_earctx_ana_ctrl5       //unsigned, RW, default = 0,
#define P_EARC_TX_ANA_STAT0 ((volatile uint32_t *)0xfe333160)
// Bit      31:0,     ro_ANA_status0              //unsigned, RO, default = 0,
#define P_EARC_TX_CMDC_STATUS0 ((volatile uint32_t *)0xfe333164)
// Bit      31:0,     ro_cmdc_status0              //unsigned, RO, default = 0,
#define P_EARC_TX_CMDC_STATUS1 ((volatile uint32_t *)0xfe333168)
// Bit      31:0,     ro_cmdc_status1              ///unsigned, RO, default = 0,
#define P_EARC_TX_CMDC_STATUS2 ((volatile uint32_t *)0xfe33316c)
// Bit      31:0,     ro_cmdc_status2              ///unsigned, RO, default = 0,
#define P_EARC_TX_CMDC_STATUS3 ((volatile uint32_t *)0xfe333170)
// Bit      31:0,     ro_cmdc_status3              ///unsigned, RO, default = 0,
#define P_EARC_TX_CMDC_STATUS4 ((volatile uint32_t *)0xfe333174)
// Bit      31:0,     ro_cmdc_status4              ///unsigned, RO, default = 0,
#define P_EARC_TX_CMDC_STATUS5 ((volatile uint32_t *)0xfe333178)
// Bit      31:0,     ro_cmdc_status5              ///unsigned, RO, default = 0,
#define P_EARC_TX_CMDC_STATUS6 ((volatile uint32_t *)0xfe33317c)
// Bit   31   ,     ro_idle2_int            unsigned, RO, default = 0
// Bit   30   ,     ro_idle1_int            unsigned, RO, default = 0
// Bit   29   ,     ro_disc2_int            unsigned, RO, default = 0
// Bit   28   ,     ro_disc1_int            unsigned, RO, default = 0
// Bit   27   ,     ro_earc_int             unsigned, RO, default = 0
// Bit   26   ,     ro_hb_status_int        unsigned, RO, default = 0
// Bit   25   ,     ro_losthb_int           unsigned, RO, default = 0
// Bit   24   ,     ro_timeout_int          unsigned, RO, default = 0
// Bit   23   ,     ro_status_ch_int        unsigned, RO, default = 0
// Bit   22   ,     ro_int_recv_finished    unsigned, RO, default = 0
// Bit   21   ,     ro_int_rdata            unsigned, RO, default = 0
// Bit   20   ,     ro_int_recv_nack        unsigned, RO, default = 0
// Bit   19   ,     ro_int_recv_norsp       unsigned, RO, default = 0
// Bit   18   ,     ro_int_recv_unexp       unsigned, RO, default = 0
// Bit   17   ,     ro_int_recv_data        unsigned, RO, default = 0
// Bit   16   ,     ro_int_recv_ack         unsigned, RO, default = 0
// Bit   15   ,     ro_int_recv_ecc_err     unsigned, RO, default = 0
// Bit   14   ,     ro_int_recv_packet      unsigned, RO, default = 0
// Bit 13:0   ,     reserved
//
// Closing file:  earc_tx_cmdc.h
//
//========================================================================
//  AUDIO EARCTX_DMAC - Registers
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe333400
// -----------------------------------------------
//
// Reading file:  earctx_dmac.h
//
#define P_EARCTX_DMAC_TOP_CTRL0 ((volatile uint32_t *)0xfe333400)
// Bit 31,       reg_top_reg_sync             ,default = 0,Bit 3:0 sync to clk10m,pluse auto clear
// Bit 30,       reg_top_soft_rst             ,default = 0
// Bit 29:26,    reserved
// Bit 25:24,    reg_debug_mux                ,default = 0
// Bit 23:21,    reserved
// Bit 20,       reg_slow_sync_scan_reg       ,default = 0
// Bit 19,       reg_fe_sf_scan_reg           ,default = 0
// Bit 18,       reg_fe_slow_sync_scan_reg    ,default = 0
// Bit 17,       reg_top_sf_scan_reg          ,default = 0
// Bit 16,       reg_top_slow_sync_scan_reg   ,default = 0
// Bit 15:4,     reserved
// Bit 3,        reg_spdif_tx_en_force        ,default = 0,spdif_tx_en force enable
// Bit 2,        reg_spdif_tx_en_force_value  ,default = 0,spdif_tx_en force value
// Bit 1,        reg_dmac_tx_en_force         ,default = 0,dmac_tx_en force enable
// Bit 0,        reg_dmac_tx_en_force_value   ,default = 0,dmac_tx_en force value
#define P_EARCTX_MUTE_VAL ((volatile uint32_t *)0xfe333404)
// Bit 31:0,     reg_spdif_mute_val     ,default = 0,when biahpase encode mute,the channel
// value,with reg_mute_l/reg_mute_r
#define P_EARCTX_SPDIFOUT_GAIN0 ((volatile uint32_t *)0xfe333408)
// Bit 31:24,    reg_gain_ch3     ,default = 0,channel 3 gain
// Bit 23:16,    reg_gain_ch2     ,default = 0,channel 2 gain
// Bit 15:8,     reg_gain_ch1     ,default = 0,channel 1 gain
// Bit 7:0,      reg_gain_ch0     ,default = 0,channel 0 gain
#define P_EARCTX_SPDIFOUT_GAIN1 ((volatile uint32_t *)0xfe33340c)
// Bit 31:24,    reg_gain_ch7     ,default = 0,channel 7 gain
// Bit 23:16,    reg_gain_ch6     ,default = 0,channel 6 gain
// Bit 15:8,     reg_gain_ch5     ,default = 0,channel 5 gain
// Bit 7:0,      reg_gain_ch4     ,default = 0,channel 4 gain
#define P_EARCTX_SPDIFOUT_CTRL0 ((volatile uint32_t *)0xfe333410)
// Bit 31,     reg_work_start      ,default = 0,biphase work start,pluse
// Bit 30,     reg_work_clr        ,default = 0,biphase work clear,pluse
// Bit 29,     reg_rst_afifo_out_n ,default = 0,afifo out reset
// Bit 28,     reg_rst_afifo_in_n  ,default = 0,afifo in reset
// Bit 27,     reg_hold_for_tdm    ,default = 0,add delay to mathc TDM out when share buff
// Bit 26,     reg_userdata_sel    ,default = 0,user Bit select : 0 from reg_userdata_set 1 from
// data[29] Bit 25,     reg_userdata_set    ,default = 0 Bit 24,     reg_chdata_sel      ,default =
// 0,0 :from reg_chstst 1 from data[30] Bit 23,     reserved Bit 22,     reg_mute_l ,default = 0,r
// channel mute ,with reg_mute_val Bit 21,     reg_mute_r          ,default = 0,l channel mute
// ,with reg_mute_val Bit 20,     reg_data_sel        ,default = 0,0 data from 31Bit 1 data from
// 27bit Bit 19,     reg_out_msb_first   ,default = 0,0 lsb first 1 msb first Bit 18, reg_valid_sel
// ,default = 0,biphase encode valid Bit value sel : 0 from data 1 from reg_valid_set Bit 17,
// reg_valid_set       ,default = 0,biphase encode valid Bit value Bit 16, reg_mute_hold_init_en
// ,default = 0,when c_mute_hold_last_err_corrt valid,clear work enable, initial biphase encode Bit
// 15:12,  reserved Bit 0,      reg_parity_mask     ,default = 0,Bit 0 is initial parity value
#define P_EARCTX_SPDIFOUT_CTRL1 ((volatile uint32_t *)0xfe333414)
// Bit 31,     reg_eq_drc_sel      ,default = 0,set 1 select eq_drc data
// Bit 30,     reg_keep_req_ddr_init ,default = 0,reg_keep_req_ddr_init
// Bit 29:28,  reserved
// Bit 27,     reg_gain_en         ,default = 0,gain enable
// Bit 26:24,  reg_frddr_sel       ,default = 0,from ddr selet
// Bit 23:16,  reg_wait_cnt        ,default = 0,wait some time when enalble set to 1
// Bit 15:13,  reserved
// Bit 12:8,   reg_frddr_msb       ,default = 0,msb position of data
// Bit 7,      reg_force_start     ,default = 0,set 1 no need ack from frddr to transmit channel
// status Bit 6:4,    reg_frddr_type      ,default = 0 Bit 3:0,    reserved
#define P_EARCTX_SPDIFOUT_PREAMB ((volatile uint32_t *)0xfe333418)
// Bit 31,     reg_premable_Z_set      ,default = 0,user 8'b11101000 1 user 7:0
// Bit 30,     reg_premable_Y_set      ,default = 0,user 8'b11100100 1 user 15:8
// Bit 29,     reg_premable_X_set      ,default = 0,user 8'b11100010 1 user 23:16
// Bit 28:24,  reserved
// Bit 23:16,  reg_premable_X_value    ,default = 0
// Bit 15:8,   reg_premable_Y_value    ,default = 0
// Bit 7:0,    reg_premable_Z_value    ,default = 0
#define P_EARCTX_SPDIFOUT_SWAP ((volatile uint32_t *)0xfe33341c)
// Bit 31:16,  reg_hold_cnt        ,default = 0,hold start cnt ,valid when reg_hold_for_tdm set 1
// Bit 15,     reg_init_send_en    ,default = 0,send 01 squence some times after initial done from
// frddr set Bit 14:0,   reg_init_send_cnt   ,default = 0,send 01 squence time ,valid when
// reg_init_send_en set 1
#define P_EARCTX_ERR_CORRT_CTRL0 ((volatile uint32_t *)0xfe333420)
// Bit 31:24,  reserved
// Bit 23,     reg_bch_in_reverse       ,default = 0,bch input data generate in 24it data reverse
// Bit 22,     reg_bch_out_ecc_reverse  ,default = 0,bch output ecc  reverse
// Bit 21,     reg_bch_out_data_reverse ,default = 0,bch output data reverse
// Bit 20,     reg_bch_out_ecc_msb      ,default = 0,bch output ecc position
// Bit 19:17,  reserved
// Bit 16,     reg_ubit_fifo_init_n,default = 0,fifo in  initial
// Bit 15:14,  reserved
// Bit 13:12,  reg_gain_shift      ,default = 0,gain x 1/2/4/8
// Bit 11,     reg_mix_lr          ,default = 0,l/r mix
// Bit 10:8,   reg_spdifout_r_sel  ,default = 0,r channel select
// Bit 7,      reserved
// Bit 6:4,    reg_spdifout_l_sel  ,default = 0,l channel select
// Bit 3:0,    reg_iu_interval     ,default = 0,iu transmit interval
#define P_EARCTX_ERR_CORRT_CTRL1 ((volatile uint32_t *)0xfe333424)
// Bit 31,     reg_ubit_fifo_wr    ,default = 0,iu data write enable,pluse,auto clr in reg.v
// Bit 30:8,   reserved
// Bit 7:0,    reg_ubit_fifo_wdata ,default = 0,iu data
#define P_EARCTX_ERR_CORRT_CTRL2 ((volatile uint32_t *)0xfe333428)
// Bit 31,     reg_mute_clear       ,default = 0,mute clear,pluse,auto clr in reg.v
// Bit 30,     reg_mute_start       ,default = 0,mute start,pluse,auto clr in reg.v
// Bit 29:28,  reserved
// Bit 27:16,  reg_mute_block_num   ,default = 0,mute block number
// Bit 15:8,   reg_mute_ch_Bit      ,default = 0,mute Bit at channel statue which bit
// Bit 7:3,    reserved
// Bit 2,      reg_mute_data_sel    ,default = 0,mute data sel: 0 data 1 reg_mute_data_value
// Bit 1:0,    reg_mute_mode        ,default = 0,0:always mute 1:mute block number and dis mute
// 2:mute bolck number and hold bus
#define P_EARCTX_ERR_CORRT_CTRL3 ((volatile uint32_t *)0xfe33342c)
// Bit 31:30,  reserved
// Bit 29,     reg_bch_en           ,default = 0,bch generate enable
// Bit 28:24,  reg_bch_msb          ,default = 0,bch data msb position in audio data
// Bit 23:0,   reg_mute_data_value  ,default = 0,mute value,only for audio data part
#define P_EARCTX_ERR_CORRT_CTRL4 ((volatile uint32_t *)0xfe333430)
// Bit 31,    reg_ubit_fifo_lr_swap        ,default = 0,//user Bit lr swap
// Bit 30,    reg_ubit_fifo_lr_same        ,default = 0,//l/r channel use same Bit user bit
// Bit 29:25, reg_data_msb                 ,default = 0,audio data msb postion in input data
// Bit 24,    reg_data_rsv                 ,default = 0,audio data msb/lsb
// Bit 23,    reg_ubit_value               ,default = 0,user Bit value
// Bit 22,    reg_vbit_value               ,default = 0,valid Bit value
// Bit 21,    reg_data_sel                 ,default = 0,//data sel: 0 data 1 reg_mute_data_value
// Bit 20:19, reg_ubit_sel                 ,default = 0,//userBit sel: 0 data 1 reg_value 2 fifo
// data Bit 18,    reg_vbit_sel                 ,default = 0,//validBit sel: 0 data 1 reg_value Bit
// 17,    reg_chst_sel                 ,default = 0,//chanel status sel: 0 data 1 reg_value Bit 16,
// reg_ubit_fifo_less_irq_en    ,default = 0,fifo_less_thd irq enable Bit 15:8,
// reg_ubit_fifo_start_thd      ,default = 0,start transmit iu after fifo level greater than this
// value Bit 7:0,   reg_ubit_fifo_less_thd       ,default = 0,generate irq,when fifo level less
// than this value
#define P_EARCTX_ERR_CORRT_STAT0 ((volatile uint32_t *)0xfe333434)
// Bit 31:0,  ro_err_corrt_stat0          ,default = 0,
#define P_EARCTX_SPDIFOUT_CHSTS0 ((volatile uint32_t *)0xfe333438)
// Bit 31:0,  reg_changel_a_status         ,default =0,channel A status[31:0]
#define P_EARCTX_SPDIFOUT_CHSTS1 ((volatile uint32_t *)0xfe33343c)
// Bit 31:0,  reg_changel_a_status         ,default =0,channel A status[63:32]
#define P_EARCTX_SPDIFOUT_CHSTS2 ((volatile uint32_t *)0xfe333440)
// Bit 31:0,  reg_changel_a_status         ,default =0,channel A status[95:64]
#define P_EARCTX_SPDIFOUT_CHSTS3 ((volatile uint32_t *)0xfe333444)
// Bit 31:0,  reg_changel_a_status         ,default =0,channel A status[127:96]
#define P_EARCTX_SPDIFOUT_CHSTS4 ((volatile uint32_t *)0xfe333448)
// Bit 31:0,  reg_changel_a_status         ,default =0,channel A status[159:128]
#define P_EARCTX_SPDIFOUT_CHSTS5 ((volatile uint32_t *)0xfe33344c)
// Bit 31:0,  reg_changel_a_status         ,default =0,channel A status[191:160]
#define P_EARCTX_SPDIFOUT_CHSTS6 ((volatile uint32_t *)0xfe333450)
// Bit 31:0,  reg_changel_b_status         ,default =0,channel B status[31:0]
#define P_EARCTX_SPDIFOUT_CHSTS7 ((volatile uint32_t *)0xfe333454)
// Bit 31:0,  reg_changel_b_status         ,default =0,channel B status[63:32]
#define P_EARCTX_SPDIFOUT_CHSTS8 ((volatile uint32_t *)0xfe333458)
// Bit 31:0,  reg_changel_b_status         ,default =0,channel B status[95:64]
#define P_EARCTX_SPDIFOUT_CHSTS9 ((volatile uint32_t *)0xfe33345c)
// Bit 31:0,  reg_changel_b_status         ,default =0,channel B status[127:96]
#define P_EARCTX_SPDIFOUT_CHSTSA ((volatile uint32_t *)0xfe333460)
// Bit 31:0,  reg_changel_b_status         ,default =0,channel B status[159:128]
#define P_EARCTX_SPDIFOUT_CHSTSB ((volatile uint32_t *)0xfe333464)
// Bit 31:0,  reg_changel_b_status         ,default =0,channel B status[191:160]
#define P_EARCTX_FE_CTRL0 ((volatile uint32_t *)0xfe333468)
// Bit 31,    reg_mute_hold_clr      ,default = 0,clear mute hold statues,pluse, auto clr
// Bit 30,    reg_work_enable        ,default = 0,wore enable
// Bit 29,    reg_dmac_invt          ,default = 0,fe out invent
// Bit 28,    reg_hold_time_en       ,default = 0,hold min time enable
// Bit 27,    reg_hold_soft_clr_en   ,default = 0,0 auto clear hold at next valid 1 clear hold
// with reg_mute_hold_clr Bit 26:24, reg_hold_time_tick_sel ,default = 0,hold min time tick select
// Bit 23:0,  reg_hold_min_time      ,default = 0,hold min time
#define P_EARCTX_FE_STAT0 ((volatile uint32_t *)0xfe33346c)
// Bit 31:0,  ro_fe_stat0          ,default = 0,
#define P_EARCTX_SPDIFOUT_STAT ((volatile uint32_t *)0xfe333470)
// Bit 31:0,  ro_spdifout_stat     ,default = 0,
#define P_EARCTX_SPDIFOUT_CTRL2 ((volatile uint32_t *)0xfe333474)
// Bit 31:28,  reserved
// Bit 27:16,  reg_clr_by_init      ,default = 0,reg_clr_by_init
// Bit 15:0 ,  reg_mask             ,default = 0,reg_mask
#define P_EARCTX_SPDIFOUT_GAIN2 ((volatile uint32_t *)0xfe333478)
// Bit 31:0,  spdifout_gain2        ,default = 0,spdifout gain2
#define P_EARCTX_SPDIFOUT_GAIN3 ((volatile uint32_t *)0xfe33347c)
// Bit 31:0,  spdifout_gain3        ,default = 0,spdifout gain3
#define P_EARCTX_SPDIFOUT_GAIN4 ((volatile uint32_t *)0xfe333480)
// Bit 31:0,  spdifout_gain4        ,default = 0,spdifout gain4
#define P_EARCTX_SPDIFOUT_GAIN5 ((volatile uint32_t *)0xfe333484)
// Bit 31:0,  spdifout_gain5        ,default = 0,spdifout gain5
//
//
// Closing file:  earctx_dmac.h
//
//========================================================================
//  AUDIO EARCTX_TOP  - Registers
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe333600
// -----------------------------------------------
//
// Reading file:  earctx_top.h
//
#define P_EARCTX_TOP_CTRL0 ((volatile uint32_t *)0xfe333600)
// Bit   31:18,   reserved
// Bit   17:16,   reg_earctx_debug_mux     unsigned, default = 0, debug mux
// Bit   15,      reg_slow_sync_scan_reg   unsigned, default = 0, reg_slow_sync_scan_reg
// Bit   14:12,   reserved
// Bit   11,      reg_hdmi_hpd_invt        unsigned, default = 0, hdmi_hpd invent
// Bit   10,      reg_hdmi_hpd_value       unsigned, default = 0, hdmi_hpd mux = 3,register value
// Bit   9:8,     reg_hdmi_hpd_mux         unsigned, default = 0, hdmi_hpd mux
// Bit   7,       reg_earctx_hd_hpd_invt   unsigned, default = 0, earctx_hd_hdp invent
// Bit   6,       reg_earctx_hd_hpd_value  unsigned, default = 0, earctx_hd_hdp mux = 3,register
// value Bit   5:4,     reg_earctx_hd_hdp_mux    unsigned, default = 0, earctx_hd_hdp mux Bit 3:2,
// reserved Bit   1,       reg_earctx_force_mode_en unsigned, default = 0, force mode enale Bit 0,
// reg_earctx_force_mode    unsigned, default = 0, force mode value
#define P_EARCTX_DMAC_INT_MASK ((volatile uint32_t *)0xfe333604)
// Bit   31:6,  reserved
// Bit   5:0,   reg_dmac_int_mask             unsigned, default = 0, dmac int mask
#define P_EARCTX_DMAC_INT_PENDING ((volatile uint32_t *)0xfe333608)
// Bit   31:6,  reserved
// Bit   5:0,   reg_dmac_int_mask             unsigned, default = 0, dmac int pending,read only
#define P_EARCTX_CMDC_INT_MASK ((volatile uint32_t *)0xfe33360c)
// Bit   31:18,  reserved
// Bit   17:0,   reg_cmdc_int_mask             unsigned, default = 0, cmdc int mask
#define P_EARCTX_CMDC_INT_PENDING ((volatile uint32_t *)0xfe333610)
// Bit   31:18,  reserved
// Bit   17:0,   reg_cmdc_int_mask             unsigned, default = 0, cmdc int pending,read only
#define P_EARCTX_ANA_CTRL0 ((volatile uint32_t *)0xfe333614)
// Bit   31:0,   reg_earctx_ana_ctrl0          unsigned, default = 0
#define P_EARCTX_ANA_CTRL1 ((volatile uint32_t *)0xfe333618)
// Bit   31:0,   reg_earctx_ana_ctrl0          unsigned, default = 0
#define P_EARCTX_ANA_CTRL2 ((volatile uint32_t *)0xfe33361c)
// Bit   31:0,   reg_earctx_ana_ctrl0          unsigned, default = 0
#define P_EARCTX_ANA_STAT0 ((volatile uint32_t *)0xfe333620)
// Bit   31:0,   reg_earctx_ana_ctrl0          unsigned, default = 0
//
// Closing file:  earctx_top.h
//
//========================================================================
//  AUDIO EARCRX_CMDC - Registers
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe333800
// -----------------------------------------------
//
// Reading file:  earc_rx_cmdc.h
//
#define P_EARC_RX_CMDC_TOP_CTRL0 ((volatile uint32_t *)0xfe333800)
// Bit   31   ,     idle2_int                 unsigned, default = 0, 1: enable
// Bit   30   ,     idle1_int                 unsigned, default = 0, 1: enable
// Bit   29   ,     disc2_int                 unsigned, default = 0, 1: enable
// Bit   28   ,     disc1_int                 unsigned, default = 0, 1: enable
// Bit   27   ,     earc_int                  unsigned, default = 0, 1: enable
// Bit   26   ,     hb_status_int             unsigned, default = 0, 1: enable
// Bit   25   ,     losthb_int                unsigned, default = 0, 1: enable
// Bit   24   ,     timeout_int               unsigned, default = 0, 1: enable
// Bit   23   ,     status_ch_int             unsigned, default = 0, 1: enable
// Bit   22   ,     int_rec_invalid_id        unsigned, default = 0, 1: enable
// Bit   21   ,     int_rec_invalid_offset    unsigned, default = 0, 1: enable
// Bit   20   ,     int_rec_unexp             unsigned, default = 0, 1: enable
// Bit   19   ,     int_rec_ecc_err           unsigned, default = 0, 1: enable
// Bit   18   ,     int_rec_parity_err        unsigned, default = 0, 1: enable
// Bit   17   ,     int_recv_packet           unsigned, default = 0, 1: enable
// Bit   16   ,     int_rec_time_out          unsigned, default = 0, 1: enable
// Bit   15   ,     cmdc_debug0               unsigned, default = 0, 1: enable
// Bit   14   ,     cmdc_debug1               unsigned, default = 0, 1: enable
// Bit   13   ,     cmdc_debug2               unsigned, default = 0, 1: enable
// Bit   12:7 ,     reserved
// Bit    6   ,     mute_select               unsigned, default = 0, 1: use bit5, 0: earc off
// Bit    5   ,     mute_contrl               unsigned, default = 0, value of mannul mute control
// Bit    4:0 ,     reserved
#define P_EARC_RX_CMDC_TOP_CTRL1 ((volatile uint32_t *)0xfe333804)
// Bit      31:13,  reserved
// Bit      12:8,   reg_scan_reg             unsigned, RW, default = 0,
// Bit      7:5,    reserved
// Bit      4:0,    reg_top_soft_rst         unsigned, RW, default = 0,
#define P_EARC_RX_CMDC_TOP_CTRL2 ((volatile uint32_t *)0xfe333808)
// Bit      31,         reset_idle2_int                unsigned, default =0
// Bit      30,         reset_idle1_int                unsigned, default =0
// Bit      29,         reset_disc2_int                unsigned, default =0
// Bit      28,         reset_disc1_int                unsigned, default =0
// Bit      27,         reset_earc_int                 unsigned, default =0
// Bit      26,         reset_hb_status_int            unsigned, default =0
// Bit      25,         reset_losthb_int               unsigned, default =0
// Bit      24,         reset_timeout_int              unsigned, default =0
// Bit      23,         reset_status_ch_int            unsigned, default =0
// Bit      22,         reset_int_rec_invalid_id       unsigned, default =0
// Bit      21,         reset_int_rec_invalid_offset   unsigned, default =0
// Bit      20,         reset_int_rec_unexp            unsigned, default =0
// Bit      19,         reset_int_rec_ecc_err          unsigned, default =0
// Bit      18,         reset_int_rec_parity_err       unsigned, default =0
// Bit      17,         reset_int_recv_packet          unsigned, default =0
// Bit      16,         reset_int_rec_time_out         unsigned, default =0
// Bit      15:0,       reserved
#define P_EARC_RX_CMDC_TIMER_CTRL0 ((volatile uint32_t *)0xfe33380c)
// Bit      31:0,   ro_cmdc_status0         unsigned, RO, default = 0,
#define P_EARC_RX_CMDC_TIMER_CTRL1 ((volatile uint32_t *)0xfe333810)
// Bit      31:0,   ro_cmdc_status0         unsigned, RO, default = 0,
#define P_EARC_RX_CMDC_TIMER_CTRL2 ((volatile uint32_t *)0xfe333814)
// Bit      31:0,    ro_cmdc_status0         unsigned, RO, default = 0,
#define P_EARC_RX_CMDC_TIMER_CTRL3 ((volatile uint32_t *)0xfe333818)
// Bit      31:0,    ro_cmdc_status0         unsigned, RO, default = 0,
#define P_EARC_RX_CMDC_VSM_CTRL0 ((volatile uint32_t *)0xfe33381c)
// Bit      31,      sw_state_update         unsigned, default = 0,  XX
// Bit      30:28,   sw_state                unsigned, default = 0,  XX
// Bit      27,      arc_initiated           unsigned, default = 0,  XX
// Bit      26,      arc_terminated          unsigned, default = 0,  XX
// Bit      25,      arc_enable              unsigned, default = 0,  XX
// Bit      24,      man_hpd                 unsigned, default = 0,  XX
// Bit      23:22,   hpd_sel                 unsigned, default = 0,  XX
// Bit      21:20,   hpd_sel_earc            unsigned, default = 0,  XX
// Bit      19,      comma_cnt_rst           unsigned, default = 0,  XX
// Bit      18,      timeout_status_rst      unsigned, default = 0,  XX
// Bit      17,      losthb_status_rst       unsigned, default = 0,  XX
// Bit      16,      force_rst               unsigned, default = 0,  XX
// Bit      15,      auto_state              unsigned, default = 0,  XX
// Bit      14,      cmdc_state_en           unsigned, default = 0,  XX
// Bit    13:0,      reserved
#define P_EARC_RX_CMDC_VSM_CTRL1 ((volatile uint32_t *)0xfe333820)
// Bit    31:12,      max_count_th          unsigned, default = 0,  idle done timing
// Bit     11:8,      reserved
// Bit        7,      reg_soft_rst          unsigned, default = 0,  idle done timing
// Bit      6:4,      time_sel              unsigned, default = 0,  idle done timing
// Bit      3:2,      soft_rst_sel          unsigned, default = 0,  idle done timing
// Bit      1:0,      enable_ctrl           unsigned, default = 0,  idle done timing
#define P_EARC_RX_CMDC_VSM_CTRL2 ((volatile uint32_t *)0xfe333824)
// Bit    31:12,      max_count_th          unsigned, default = 0,  comma off done timing
// Bit     11:8,      reserved
// Bit        7,      reg_soft_rst          unsigned, default = 0,  comma off done timing
// Bit      6:4,      time_sel              unsigned, default = 0,  comma off done timing
// Bit      3:2,      soft_rst_sel          unsigned, default = 0,  comma off done timing
// Bit      1:0,      enable_ctrl           unsigned, default = 0,  comma off done timing
#define P_EARC_RX_CMDC_VSM_CTRL3 ((volatile uint32_t *)0xfe333828)
// Bit    31:12,      max_count_th          unsigned, default = 0,  earc_time out timing
// Bit     11:8,      reserved
// Bit        7,      reg_soft_rst          unsigned, default = 0,  earc_time out timing
// Bit      6:4,      time_sel              unsigned, default = 0,  earc_time out timing
// Bit      3:2,      soft_rst_sel          unsigned, default = 0,  earc_time out timing
// Bit      1:0,      enable_ctrl           unsigned, default = 0,  earc_time out timing
#define P_EARC_RX_CMDC_VSM_CTRL4 ((volatile uint32_t *)0xfe33382c)
// Bit    31:12,      max_count_th          unsigned, default = 0,  heartbeat lost timing
// Bit     11:8,      reserved
// Bit        7,      reg_soft_rst          unsigned, default = 0,  heartbeat lost timing
// Bit      6:4,      time_sel              unsigned, default = 0,  heartbeat lost timing
// Bit      3:2,      soft_rst_sel          unsigned, default = 0,  heartbeat lost timing
// Bit      1:0,      enable_ctrl           unsigned, default = 0,  heartbeat lost timing
#define P_EARC_RX_CMDC_VSM_CTRL5 ((volatile uint32_t *)0xfe333830)
// Bit    31:16,      reserved
// Bit     15:8,      status_soft           unsigned, default = 0,  in earc heartbeat det timing
// Bit        7,      reg_soft_rst          unsigned, default = 0,  in earc heartbeat det timing
// Bit        6,      status_rst            unsigned, default = 0,  in earc heartbeat det timing
// Bit      5:4,      reserved
// Bit      3:2,      soft_rst_sel          unsigned, default = 0,  in earc heartbeat det timing
// Bit      1:0,      enable_ctrl           unsigned, default = 0,  in earc heartbeat det timing
#define P_EARC_RX_CMDC_VSM_CTRL6 ((volatile uint32_t *)0xfe333834)
// Bit    31:17,      reserved
// Bit        16,     cntl_hpd_sel          unsigned, default = 0,  in earc heartbeat det timing
// Bit      15:4,     cntl_hpd_valid_width  unsigned, default = 0,  in earc heartbeat det timing
// Bit      3:0,      cntl_hpd_glitch_width unsigned, default = 0,  in earc heartbeat det timing
#define P_EARC_RX_CMDC_VSM_CTRL7 ((volatile uint32_t *)0xfe333838)
// Bit      31:0,     vsm_ctrl7             unsigned,  default = 0,
#define P_EARC_RX_CMDC_VSM_CTRL8 ((volatile uint32_t *)0xfe33383c)
// Bit      31:0,     vsm_ctrl8             unsigned,  default = 0,
#define P_EARC_RX_CMDC_VSM_CTRL9 ((volatile uint32_t *)0xfe333840)
// Bit      31:0,     vsm_ctrl9             unsigned,  default = 0,
#define P_EARC_RX_CMDC_SENDER_CTRL0 ((volatile uint32_t *)0xfe333844)
// Bit      31:2,     reserved
// Bit      1,        hb_chg_conf_auto          unsigned,  default = 0,
// Bit      0,        hb_chg_auto               unsigned,  default = 1,
#define P_EARC_RX_CMDC_PACKET_CTRL0 ((volatile uint32_t *)0xfe333848)
// Bit        31,      packet_mode_enable          unsigned, default = 0,  packet control
// Bit        30,      free_enable                 unsigned, default = 0,  packet control
// Bit        29,      soft_rst_man                unsigned, default = 0,  packet control
// Bit     28:24,      ready_th                    unsigned, default = 0,  packet control
// Bit     23:20,      reserved
// Bit      19:8,      send_pre_th                 unsigned, default = 0,  packet control
// Bit       7:5,      reserved
// Bit         4,      sw_state_update             unsigned, default = 0,  packet control
// Bit       3:0,      sw_state                    unsigned, default = 0,  packet control
#define P_EARC_RX_CMDC_PACKET_CTRL1 ((volatile uint32_t *)0xfe33384c)
// Bit        31,      ecc_endian                  unsigned, default = 0,  send
// Bit        30,      pre_reg_st                  unsigned, default = 0,  send
// Bit     29:21,      reserved
// Bit     20:16,      post_th                     unsigned, default = 0,  send
// Bit     15:14,      reserved
// Bit      13:8,      pre_th                      unsigned, default = 0,
// Bit       7:0,      post_flag                   unsigned, default = 0,
#define P_EARC_RX_CMDC_PACKET_CTRL2 ((volatile uint32_t *)0xfe333850)
// Bit      31:0,      pre_flag                    unsigned, default = 0,  X
#define P_EARC_RX_CMDC_PACKET_CTRL3 ((volatile uint32_t *)0xfe333854)
// Bit      31,       cmdc_en                      unsigned, default = 0,  XX
// Bit      30,       cmdc_parity_mask             unsigned, default = 0,  XX
// Bit      29,       imeout_en                    unsigned, default = 0,  XX
// Bit      28,       ecc_check_en                 unsigned, default = 0,  XX
// Bit      27,       rev_debug_en                 unsigned, default = 0,  XX
// Bit     26:16,     reserved
// Bit      15:0,     timeout_th                   unsigned, default = 0,  X
#define P_EARC_RX_CMDC_PACKET_CTRL4 ((volatile uint32_t *)0xfe333858)
// Bit      31,       ack_ignore                   unsigned, default = 0,  XX
// Bit      30,       cmdc_tail_check_mask         unsigned, default = 0,  XX
// Bit     29:20,     reserved
// Bit      19:0,     cmdc_packet_head             unsigned, default = 0,  XX
#define P_EARC_RX_CMDC_PACKET_CTRL5 ((volatile uint32_t *)0xfe33385c)
// Bit     31:24,     rev_debug_mask               unsigned, default = 0,  XX
// Bit     23:20,     reserved
// Bit      19:0,     cmdc_packet_head_mask        unsigned, default = 0,  XX
#define P_EARC_RX_CMDC_PACKET_CTRL6 ((volatile uint32_t *)0xfe333860)
// Bit     31:20,     recv_pre_threshold          unsigned, default = 0,  packet control
// Bit      19:9,     reserved
// Bit         8,     rec_packet_d                 unsigned, default = 0,  XX
// Bit         7,     rec_parity_err_cnt		      unsigned, default = 0,  XX
// Bit         6,     rec_ecc_err_cnt		      unsigned, default = 0,  XX
// Bit         5,     rec_unexp_cnt			      unsigned, default = 0,  XX
// Bit         4,     rec_invalid_offset_cnt	      unsigned, default = 0,  XX
// Bit         3,     rec_invalid_id_cnt		      unsigned, default = 0,  XX
// Bit         2,     rec_timeout_cnt		      unsigned, default = 0,  XX
// Bit         1,     rec_w_cnt				      unsigned, default = 0,  XX
// Bit         0,     rec_r_cnt				      unsigned, default = 0,  X
#define P_EARC_RX_CMDC_BIPHASE_CTRL0 ((volatile uint32_t *)0xfe333864)
// Bit     31:24,     reg_tns                       unsigned, default = 7, xx
// Bit     23:16,     delay_th                      unsigned, default = 0, xx
// Bit     15:10,     reserved
// Bit         9,     send_ack_en                   unsigned, default = 0,  xx
// Bit         8,     sq_val_en                     unsigned, default = 0,  XX
// Bit         7,     biphase_send_soft_rst         unsigned, default = 0,  XX
// Bit         6,     comma_soft_rst                unsigned, default = 0,  XX
// Bit         5,     fifo_rst                      unsigned, default = 0,  XX
// Bit         4,     receiver_no_sender            unsigned, default = 0,  XX
// Bit         3,     sender_free                   unsigned, default = 0,  XX
// Bit         2,     receiver_send                 unsigned, default = 0,  XX
// Bit         1,     receiver_earc                 unsigned, default = 0,  XX
// Bit         0,     receiver_free                 unsigned, default = 0,  XX
#define P_EARC_RX_CMDC_BIPHASE_CTRL1 ((volatile uint32_t *)0xfe333868)
// Bit     31:16,     reserved
// Bit        15,     ack_val_en                      unsigned, default = 0,  send
// Bit      14:8,     reserved
// Bit       7:0,     width                        unsigned, default = 0,  send
#define P_EARC_RX_CMDC_BIPHASE_CTRL2 ((volatile uint32_t *)0xfe33386c)
// Bit      31,        ack_val_en                  unsigned, default = 0,  send
// Bit      30:20,     reserved
// Bit       19:16,    ack_rate                   unsigned, default = 0,  comma send
// Bit       15:0,     width                         unsigned, default = 0,  comma sen
#define P_EARC_RX_CMDC_BIPHASE_CTRL3 ((volatile uint32_t *)0xfe333870)
// Bit      31:0,     biphase_ctrl3                 unsigned, default = 0,
#define P_EARC_RX_CMDC_DEVICE_ID_CTRL ((volatile uint32_t *)0xfe333874)
// Bit        31,     apb_write                     unsigned, default = 0, apb bus wr/read
// Bit        30,     apb_read                      unsigned, default = 0, apb bus wr/read
// Bit        29,     apb_w_r_done                  unsigned, default = 0, apb bus wr/read
// Bit        28,     apb_w_r_reset                 unsigned, default = 0, apb bus wr/read
// Bit     27:16,     reserved
// Bit      15:8,     apb_w_r_id                    unsigned, default = 0, apb bus wr/read
// Bit       7:0,     apb_w_r_start_addr            unsigned, default = 0, apb bus wr/read
#define P_EARC_RX_CMDC_DEVICE_WDATA ((volatile uint32_t *)0xfe333878)
// Bit      31:8,     reserved
// Bit       7:0,     apb_write_data                unsigned, default = 0, apb bus wr/rea
#define P_EARC_RX_CMDC_DEVICE_RDATA ((volatile uint32_t *)0xfe33387c)
// Bit      31:8,     reserved
// Bit       7:0,     apb_read_data                 unsigned, default = 0, apb bus wr/rea
#define P_EARC_RX_ANA_CTRL0 ((volatile uint32_t *)0xfe333880)
// Bit      31:0,     ana_ctrl0                     unsigned, default = 0,
#define P_EARC_RX_ANA_CTRL1 ((volatile uint32_t *)0xfe333884)
// Bit      31:0,     ana_ctrl1                     unsigned, default = 0,
#define P_EARC_RX_ANA_CTRL2 ((volatile uint32_t *)0xfe333888)
// Bit      31:0,     ana_ctrl2                     unsigned, default = 0,
#define P_EARC_RX_ANA_CTRL3 ((volatile uint32_t *)0xfe33388c)
// Bit      31:0,     ana_ctrl3                     unsigned, default = 0,
#define P_EARC_RX_ANA_CTRL4 ((volatile uint32_t *)0xfe333890)
// Bit      31:0,     ana_ctrl4                     unsigned, default = 0,
#define P_EARC_RX_ANA_CTRL5 ((volatile uint32_t *)0xfe333894)
// Bit      31:0,     ana_ctrl5                     unsigned, default = 0,
#define P_EARC_RX_ANA_STAT0 ((volatile uint32_t *)0xfe333898)
// Bit      31:0,     ro_ANA_status0              unsigned, RO, default = 0,
#define P_EARC_RX_CMDC_STATUS0 ((volatile uint32_t *)0xfe33389c)
// Bit      31:0,     ro_cmdc_status0              unsigned, RO, default = 0,
#define P_EARC_RX_CMDC_STATUS1 ((volatile uint32_t *)0xfe3338a0)
// Bit      31:0,     ro_cmdc_status1              unsigned, RO, default = 0,
#define P_EARC_RX_CMDC_STATUS2 ((volatile uint32_t *)0xfe3338a4)
// Bit      31:0,     ro_cmdc_status2              unsigned, RO, default = 0,
#define P_EARC_RX_CMDC_STATUS3 ((volatile uint32_t *)0xfe3338a8)
// Bit      31:0,     ro_cmdc_status3              unsigned, RO, default = 0,
#define P_EARC_RX_CMDC_STATUS4 ((volatile uint32_t *)0xfe3338ac)
// Bit      31:0,     ro_cmdc_status4              unsigned, RO, default = 0,
#define P_EARC_RX_CMDC_STATUS5 ((volatile uint32_t *)0xfe3338b0)
// Bit      31:0,     ro_cmdc_status5              unsigned, RO, default = 0,
#define P_EARC_RX_CMDC_STATUS6 ((volatile uint32_t *)0xfe3338b4)
// Bit      31,         ro_idle2_int                unsigned, RO, dfault =0
// Bit      30,         ro_idle1_int                unsigned, RO, dfault =0
// Bit      29,         ro_disc2_int                unsigned, RO, dfault =0
// Bit      28,         ro_disc1_int                unsigned, RO, dfault =0
// Bit      27,         ro_earc_int                 unsigned, RO, dfault =0
// Bit      26,         ro_hb_status_int            unsigned, RO, dfault =0
// Bit      25,         ro_losthb_int               unsigned, RO, dfault =0
// Bit      24,         ro_timeout_int              unsigned, RO, dfault =0
// Bit      23,         ro_status_ch_int            unsigned, RO, dfault =0
// Bit      22,         ro_int_rec_invalid_id       unsigned, RO, dfault =0
// Bit      21,         ro_int_rec_invalid_offset   unsigned, RO, dfault =0
// Bit      20,         ro_int_rec_unexp            unsigned, RO, dfault =0
// Bit      19,         ro_int_rec_ecc_err          unsigned, RO, dfault =0
// Bit      18,         ro_int_rec_parity_err       unsigned, RO, dfault =0
// Bit      17,         ro_int_recv_packet          unsigned, RO, dfault =0
// Bit      16,         ro_int_rec_time_out         unsigned, RO, dfault =0
// Bit      15:0,       reserved
//
// Closing file:  earc_rx_cmdc.h
//
//========================================================================
//  AUDIO EARCRX_DMAC - Registers
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe333c00
// -----------------------------------------------
//
// Reading file:  earcrx_dmac.h
//
#define P_EARCRX_DMAC_TOP_CTRL0 ((volatile uint32_t *)0xfe333c00)
// Bit   31,     reg_top_work_en               unsigned, default = 0, top work enable
// Bit   30,     reg_top_soft_rst              unsigned, default = 0, top soft reset
// Bit   29:23,  reserved
// Bit   22:20,  reg_dmac_debug_sel            unsigned, default = 0, dmac debug select
// Bit   19:18,  reserved
// Bit   17,     reg_dmac_valid_sel            unsigned, default = 0, dmac sync without clk
// Bit   16,     reg_dmac_without_clk          unsigned, default = 0, dmac sync without clk
// Bit   15,     reg_sf_sync_scan_reg          unsigned, default = 0, rst_n soft reset scan reg
// Bit   14,     reserved
// Bit   13,     reg_slow_sync_scan_reg        unsigned, default = 0, rst_n sync clk_slow scan reg
// Bit   12,     reg_a_sync_scan_reg           unsigned, default = 0, rst_n sync clk_analog scan
// reg Bit   11,     reg_slow_auto_gate            unsigned, default = 0, clk_slow auto gate Bit
// 10,     reg_a_auto_gate               unsigned, default = 0, clk_analog auto gate Bit   9:0,
// reserved
#define P_EARCRX_DMAC_SYNC_CTRL0 ((volatile uint32_t *)0xfe333c04)
// Bit   31,     reg_work_enable               unsigned, default = 0, dmac sync module work enable
// Bit   30,     reg_rst_afifo_out_n           unsigned, default = 0, afifo out reset
// Bit   29,     reg_rst_afifo_in_n            unsigned, default = 0, afifo in reset
// Bit   28:17,  reserved
// Bit   16,     reg_ana_buf_data_sel_en       unsigned, default = 0, data from analog delay
// enable Bit   15,     reserved Bit   14:12,  reg_ana_buf_data_sel          unsigned, default = 0,
// delay cycles Bit   11,     reserved Bit   10:8,   reg_ana_clr_cnt               unsigned,
// default = 0, valid last how many 0 will clear Bit   7,      reserved Bit   6:4, reg_ana_set_cnt
// unsigned, default = 0, valid last how may 1 will set Bit   3:1,    reserved Bit   0,
// reg_dmacin_phase              unsigned, default = 0, dmac data invert
#define P_EARCRX_DMAC_SYNC_STAT0 ((volatile uint32_t *)0xfe333c08)
// Bit   31:0,   reg_dmac_sync_stat0           unsigned, default = 0
#define P_EARCRX_SPDIFIN_SAMPLE_CTRL0 ((volatile uint32_t *)0xfe333c0c)
// Bit   31,     reg_work_enable               unsigned, default = 0, spdif in sample enable
// Bit   30,     reg_spdifin_phase             unsigned, default = 0, spdif in invert
// Bit   29,     reg_debug_en                  unsigned, default = 0, debug single enable
// Bit   28,     reg_width_sel                 unsigned, default = 0, 0 detect by max_width 1
// detect by min_width Bit   27:23,  reserved Bit   22:20,  reg_sample_mode               unsigned,
// default = 0, value Bit   19:0,   reg_base_timer                unsigned, default = 0, base timer
// to detect sample mode change
#define P_EARCRX_SPDIFIN_SAMPLE_CTRL1 ((volatile uint32_t *)0xfe333c10)
// Bit   31,     reg_force_sample_mode         unsigned, default = 0, 0 auto detect sample mode 1
// force a fixed sample mode with reg_sample_mode Bit   30,     reserved Bit   29:20,
// reg_sample_mode0_timer_th     unsigned, default = 0, mode0 threathold time Bit   19:10,
// reg_sample_mode1_timer_th     unsigned, default = 0, mode1 threathold time Bit   9:0,
// reg_sample_mode2_timer_th     unsigned, default = 0, mode2 threathold time
#define P_EARCRX_SPDIFIN_SAMPLE_CTRL2 ((volatile uint32_t *)0xfe333c14)
// Bit   31:30,  reserved
// Bit   29:20,  reg_sample_mode3_timer_th     unsigned, default = 0, mode3 threathold time
// Bit   19:10,  reg_sample_mode4_timer_th     unsigned, default = 0, mode4 threathold time
// Bit   9:0,    reg_sample_mode5_timer_th     unsigned, default = 0, mode5 threathold time
#define P_EARCRX_SPDIFIN_SAMPLE_CTRL3 ((volatile uint32_t *)0xfe333c18)
// Bit   31:24,  reg_sample_mode0_timer        unsigned, default = 0, mode0 sample time
// Bit   23:16,  reg_sample_mode1_timer        unsigned, default = 0, mode1 sample time
// Bit   15:8,   reg_sample_mode2_timer        unsigned, default = 0, mode2 sample time
// Bit   7:0,    reg_sample_mode3_timer        unsigned, default = 0, mode3 sample time
#define P_EARCRX_SPDIFIN_SAMPLE_CTRL4 ((volatile uint32_t *)0xfe333c1c)
// Bit   31:24,  reg_sample_mode4_timer        unsigned, default = 0, mode4 sample time
// Bit   23:16,  reg_sample_mode5_timer        unsigned, default = 0, mode5 sample time
// Bit   15:8,   reg_sample_mode6_timer        unsigned, default = 0, mode6 sample time
// Bit   7:0,    reserved
#define P_EARCRX_SPDIFIN_SAMPLE_CTRL5 ((volatile uint32_t *)0xfe333c20)
// Bit   31,     reg_sq_filt_en                unsigned, default = 0, dmac_sqout filter enable
// Bit   30,     reg_spdif_sqout_phase         unsigned, default = 0, dmac_sqout invert
// Bit   29:27,  reg_filter_tick_sel           unsigned, default = 0, dmac_sqout filter tick
// select Bit   26:24,  reg_filter_sel                unsigned, default = 0, dmac_sqout filter
// select Bit   23:20,  reserved Bit   19:0,   reg_sq_filt_timer             unsigned, default = 0,
// dmac_sqout filter tick
#define P_EARCRX_SPDIFIN_SAMPLE_STAT0 ((volatile uint32_t *)0xfe333c24)
// Bit   31:0,   reg_spdifin_sample_stat0      unsigned, default = 0
#define P_EARCRX_SPDIFIN_SAMPLE_STAT1 ((volatile uint32_t *)0xfe333c28)
// Bit   31:0,   reg_spdifin_sample_stat1      unsigned, default = 0
#define P_EARCRX_SPDIFIN_MUTE_VAL ((volatile uint32_t *)0xfe333c2c)
// Bit   31:0,   reg_spdifin_mute_val          unsigned, default = 0, spdif in mute value
#define P_EARCRX_SPDIFIN_CTRL0 ((volatile uint32_t *)0xfe333c30)
// Bit   31,     reg_work_enable               unsigned, default = 0, spdifin wore enable
// Bit   30,     reg_chnum_sel                 unsigned, default = 0, 0 ch_num = 0~383  1 ch_num =
// 0~1 Bit   29:28,  reserved Bit   27,     reg_debug_en                  unsigned, default = 0,
// debug enable Bit   26,     reg_chnum_en                  unsigned, default = 0, star add ch_cnt
// to ch_num Bit   25,     reg_findpapb_en               unsigned, default = 0, papb check enalbe
// Bit   24,     reg_nonpcm2pcm_en             unsigned, default = 0, nonpcm2pcm_th enable
// Bit   23:12,  reg_nonpcm2pcm_th             unsigned, default = 0, if long time didn't detect
// PaPb again,will generate irq Bit   11:8,   reg_ch_status_sel             unsigned, default = 0,
// for stat1/stat2 Bit   7,      reg_mute_l                    unsigned, default = 0, mute channel
// l Bit   6,      reg_mute_r                    unsigned, default = 0, mute channel r Bit   5:4,
// reserved Bit   3,      reg_check_valid               unsigned, default = 0, valid check enable
// Bit   2,      reg_check_parity              unsigned, default = 0, parity check enable
// Bit   1,      reg_invert_data               unsigned, default = 0, spdif data invert
// Bit   0,      reserved
#define P_EARCRX_SPDIFIN_CTRL1 ((volatile uint32_t *)0xfe333c34)
// Bit   31:24,  reserved
// Bit   31:24,  reg_clr_internal_sts          unsigned, default = 0, internal irq status clear
// Bit   23:12,  reg_mute_block_check_thd      unsigned, default = 0, mute block check time thd
// Bit   11:9,   reg_mute_block_check_tick_sel unsigned, default = 0, mute block check tick sel
// Bit   8,      reg_papb_ext_sync             unsigned, default = 0, ext 0 sync check for papb
// Bit   7:0,    reg_papb_ext_mask             unsigned, default = 0, sync 0 mask
#define P_EARCRX_SPDIFIN_CTRL2 ((volatile uint32_t *)0xfe333c38)
// Bit   31:24,  reg_mute_bit                   unsigned, default = 0, mute bit in channel st
// Bit   23:19,  reg_mute_block_num             unsigned, default = 0, mute min block number to
// declare Bit   18,     reg_mute_lr_ch_sel             unsigned, default = 0, mute bit in channel
// st L or R Bit   17,     reg_mute_block_check_en        unsigned, default = 0, mute block number
// check enable Bit   16,     reg_earc_cps_chst_clr_en       unsigned, default = 0, auto clear
// compress mode when channel status not compress Bit   15,     reg_earc_cps_nonpcm2pcm_clr_en
// unsigned, default = 0, auto clear compress mode when nonpcm2pcm Bit   14,     reg_earc_auto
// unsigned, default = 0, auto change earc/arc Bit   13,     reg_earcin_papb_lr unsigned, default =
// 0, user l or r channel status to check papb Bit   12,     reg_earcin_check_papb unsigned,
// default = 0, 0:data valid after 1 block;1: in 1st block if exit papb ,data valid after papb Bit
// 11,     reg_earcin_start_papb          unsigned, default = 0, start write toddr 1:from papb
// check,0 from preamble Z,valid when reg_earcin_check_papb set Bit   10, reg_formatchange_auto_rst
// unsigned, default = 0, auto reset will detect format change Bit   9, reg_earcin_cpsb_pcpd_sel
// unsigned, default = 0, compress B pcpd select : 1:next 4th subframe data 0:next sub frame data
// Bit   8:4,    reg_earc_papb_msb             unsigned, default = 0, papb msb position in data
// Bit   3,      reg_earcin_spdif_force        unsigned, default = 0, when in arc mode,spdif on
// force enable Bit   2,      reg_earcin_spdif_force_set    unsigned, default = 0, force value Bit
// 1,      reg_earcin_mode_force         unsigned, default = 0, earc mode force enable Bit   0,
// reg_earcin_mode_force_set     unsigned, default = 0, force value
#define P_EARCRX_SPDIFIN_CTRL3 ((volatile uint32_t *)0xfe333c3c)
// Bit   31:16,  reg_earc_pa_value             unsigned, default = 0, earc mode pa value
// Bit   15:0,   reg_earc_pb_value             unsigned, default = 0, earc mode pb value
#define P_EARCRX_SPDIFIN_STAT0 ((volatile uint32_t *)0xfe333c40)
// Bit   31:0,   reg_spdifin_stat0             unsigned, default = 0
#define P_EARCRX_SPDIFIN_STAT1 ((volatile uint32_t *)0xfe333c44)
// Bit   31:0,   reg_spdifin_stat1             unsigned, default = 0
#define P_EARCRX_SPDIFIN_STAT2 ((volatile uint32_t *)0xfe333c48)
// Bit   31:0,   reg_spdifin_stat2             unsigned, default = 0
#define P_EARCRX_DMAC_UBIT_CTRL0 ((volatile uint32_t *)0xfe333c4c)
// Bit   31,     reg_work_enable               unsigned, default = 0, dmac user bit decode enable
// Bit   30:24,  reg_iu_sync                   unsigned, default = 0, iu sync value
// Bit   23:16,  reg_fifo_thd                  unsigned, default = 0, generate irq when fifo level
// pass some threthold Bit   15,     reg_max_dist_en               unsigned, default = 0, max
// distance bewteen IUs to set lost Bit   14,     reg_iu_sync_en                unsigned, default =
// 0, iu sync code enable 0 : all iu to fifo 1 only sync iu packet to fifo Bit   13:12, reg_user_lr
// unsigned, default = 0, 00 off 01 use l channel userbit 10 use r channel userbit 11 user lr
// channel userbit Bit   11:8,   reg_max_dist                  unsigned, default = 0, max distance
// bewteen IUs value Bit   7,      reg_fifo_thd_en               unsigned, default = 0, fifo_thd
// irq enable Bit   6,      reg_fifo_lost_init_en         unsigned, default = 0, when lost,initial
// fifo Bit   5,      reg_fifo_init                 unsigned, default = 0, fifo initial Bit   4:0,
// reg_data_bit                  unsigned, default = 0, user bit position in data
#define P_EARCRX_IU_RDATA ((volatile uint32_t *)0xfe333c50)
// Bit   31:8,   reserved
// Bit   7:0,    i_iu_rdata                    unsigned, default = 0, iu data,read only
#define P_EARCRX_DMAC_UBIT_STAT0 ((volatile uint32_t *)0xfe333c54)
// Bit   31:0,   reg_dmac_ubit_stat0           unsigned, default = 0
#define P_EARCRX_ERR_CORRECT_CTRL0 ((volatile uint32_t *)0xfe333c58)
// Bit   31,     reg_work_enable               unsigned, default = 0, err correct work enable
// Bit   30,     reserved
// Bit   29,     reg_rst_afifo_out_n           unsigned, default = 0, reset afifo out side
// Bit   28,     reg_rst_afifo_in_n            unsigned, default = 0, reset afifo in side
// Bit   27,     reg_lr_check                  unsigned, default = 0, enable lr_check
// Bit   26:7,   reserved
// Bit   6,      reg_bchout_data_ml            unsigned, default = 0, bch output 16bit data msb is
// 27 or 19 Bit   5,      reg_bchout_data_rsv           unsigned, default = 0, bch output data
// revers Bit   4,      reg_bchin_ecc_ml              unsigned, default = 0, bch input ecc msb/lsb
// Bit   3,      reg_bchin_ecc_rsv             unsigned, default = 0, bch input ecc revers
// Bit   2,      reg_bchin_data_rsv            unsigned, default = 0, bch input data revers
// Bit   1,      reg_force_set                 unsigned, default = 0, 0 off 1 compress audio mode
// Bit   0,      reg_force_en                  unsigned, default = 0, force work mode enable
#define P_EARCRX_ERR_CORRECT_STAT0 ((volatile uint32_t *)0xfe333c5c)
// Bit   31:0,   reg_err_correct_stat0         unsigned, default = 0
#define P_EARCRX_ANA_RST_CTRL0 ((volatile uint32_t *)0xfe333c60)
// Bit   31,     reg_work_enable               unsigned, default = 0, analog reset check work
// enable Bit   30,     reg_ana_rst_sf_en             unsigned, default = 0, analog reset from
// register enable Bit   29,     reg_ana_rst_sf                unsigned, default = 0, soft reset
// value Bit   28,     reserved Bit   27:23,  reg_new_format_pos_num        unsigned, default = 0,
// when new format data in, hold reset after N posedge Bit   22:20,  reg_dmacrx_div2_thd_tick_sel
// unsigned, default = 0, earcrx_div2 hold thresthold tick select Bit   19:0,   reg_earcrx_div2_thd
// unsigned, default = 0, earcrx_div2 hold thresthold
#define P_EARCRX_ANA_RST_CTRL1 ((volatile uint32_t *)0xfe333c64)
// Bit   31,     reg_dmacrx_data_filt_en       unsigned, default = 0, filter enable
// Bit   30:28,  reg_dmacrx_data_filter_sel    unsigned, default = 0, filter select
// Bit   27:25,  reg_dmacrx_data_tick_sel      unsigned, default = 0, filter tick sel
// Bit   24:16,  reg_dmacrx_data_time          unsigned, default = 0, filter tick time
// Bit   15,     reg_dmacrx_sqout_filt_en      unsigned, default = 0, filter enable
// Bit   14:12,  reg_dmacrx_sqout_filter_sel   unsigned, default = 0, filter select
// Bit   11:9,   reg_dmacrx_sqout_tick_sel     unsigned, default = 0, filter tick sel
// Bit   8:0,    reg_dmacrx_sqout_time         unsigned, default = 0, filter tick time
#define P_EARCRX_SPDIFIN_CTRL4 ((volatile uint32_t *)0xfe333c80)
// Bit   31,     reserved
// Bit   30,     reg_add_ch_r                        unsigned, default = 0, reg_add_ch_r
// Bit   29,     reg_bc_val0_en                      unsigned, default = 0, reg_bc_val0_en
// Bit   28:20,  reg_stable_mask                     unsigned, default = 0, reg_stable_mask
// Bit   19:16,  reg_stable_zcnt                     unsigned, default = 0, reg_stable_zcnt
// Bit   15:0 ,  reserved
#define P_EARCRX_SPDIFIN_CTRL5 ((volatile uint32_t *)0xfe333c84)
// Bit   31,     reg_st_timeout_sts_clr              unsigned, default = 0, reg_st_timeout_sts_clr
// Bit   30:28,  reserved
// Bit   27:16,  reg_st_timeout_check_thd            unsigned, default = 0,
// reg_st_timeout_check_thd Bit   15,     reserved Bit   14:12,  reg_st_timeout_check_tick_sel
// unsigned, default = 0, reg_st_timeout_check_tick_sel Bit   11,     reg_st_timeout_check_en
// unsigned, default = 0, reg_st_timeout_check_en Bit   10:9,   reserved Bit   8:0,
// reg_stable_int_mask                 unsigned, default = 0, reg_stable_int_mask
#define P_EARCRX_SPDIFIN_CTRL6 ((volatile uint32_t *)0xfe333c88)
// Bit   31:17,  reserved
// Bit   16,     reg_check_time_en                   unsigned, default = 0, reg_check_time_en
// Bit   15:0,   reg_check_time_thd                  unsigned, default = 0, reg_check_time_thd
#define P_EARCRX_DMAC_SYNC_CTRL1 ((volatile uint32_t *)0xfe333c8c)
// Bit   31:19,  reserved
// Bit   18,     reg_auto_neg_int_en                 unsigned, default = 0, reg_auto_neg_int_en
// Bit   17,     reg_auto_stable_clr                 unsigned, default = 0, reg_auto_stable_clr
// Bit   16,     reg_auto_stable_en                  unsigned, default = 0, reg_auto_stable_en
// Bit   15:0,   reg_auto_stable_thd                 unsigned, default = 0, reg_auto_stable_thd
#define P_EARCRX_SPDIFIN_SAMPLE_CTRL6 ((volatile uint32_t *)0xfe333c90)
// Bit   31:18,  reserved
// Bit   17,     reg_hold_tri_sample                 unsigned, default = 0, reg_hold_tri_sample
// Bit   16,     reg_sample_mode_filter_en           unsigned, default = 0,
// reg_sample_mode_filter_en Bit   15:8,   reg_stable_cyc_min                  unsigned, default =
// 0, reg_stable_cyc_min Bit   7:0,    reg_stable_cyc_max                  unsigned, default = 0,
// reg_stable_cyc_max
#define P_EARCRX_DMAC_SYNC_CTRL2 ((volatile uint32_t *)0xfe333c94)
// Bit   31,     reg_unstable_t0_err_clr             unsigned, default = 0,
// reg_unstable_t0_err_clr Bit   30:20,  reserved Bit   19,     reg_unstable_t0_check_en unsigned,
// default = 0, reg_unstable_t0_check_en Bit   18:16,  reg_unstable_t0_tick_sel unsigned, default =
// 0, reg_unstable_t0_tick_sel Bit   15:0,   reg_unstable_t0_thd                 unsigned, default
// = 0, reg_unstable_t0_thd
#define P_EARCRX_DMAC_SYNC_CTRL3 ((volatile uint32_t *)0xfe333c98)
// Bit   31,     reg_unstable_t1_err_clr             unsigned, default = 0,
// reg_unstable_t1_err_clr Bit   30:20,  reserved Bit   19,     reg_unstable_t1_check_en unsigned,
// default = 0, reg_unstable_t1_check_en Bit   18:16,  reg_unstable_t1_tick_sel unsigned, default =
// 0, reg_unstable_t1_tick_sel Bit   15:0,   reg_unstable_t1_thd                 unsigned, default
// = 0, reg_unstable_t1_thd
#define P_EARCRX_DMAC_SYNC_CTRL4 ((volatile uint32_t *)0xfe333c9c)
// Bit   31,     reg_unstable_t2_err_clr             unsigned, default = 0,
// reg_unstable_t2_err_clr Bit   30:20,  reserved Bit   19,     reg_unstable_t2_check_en unsigned,
// default = 0, reg_unstable_t2_check_en Bit   18:16,  reg_unstable_t2_tick_sel unsigned, default =
// 0, reg_unstable_t2_tick_sel Bit   15:0,   reg_unstable_t2_thd                 unsigned, default
// = 0, reg_unstable_t2_thd
#define P_EARCRX_DMAC_SYNC_STAT1 ((volatile uint32_t *)0xfe333ca0)
// Bit   31:0,   reg_dmac_sync_stat1           unsigned, default = 0
#define P_EARCRX_DMAC_SYNC_STAT2 ((volatile uint32_t *)0xfe333ca4)
// Bit   31:0,   reg_dmac_sync_stat2           unsigned, default = 0
#define P_EARCRX_DMAC_SYNC_STAT3 ((volatile uint32_t *)0xfe333ca8)
// Bit   31:0,   reg_dmac_sync_stat3           unsigned, default = 0
//
// Closing file:  earcrx_dmac.h
//
//========================================================================
//  AUDIO EARCRX_TOP  - Registers
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe333e00
// -----------------------------------------------
//
// Reading file:  earcrx_top.h
//
#define P_EARCRX_TOP_CTRL0 ((volatile uint32_t *)0xfe333e00)
// Bit   31:10,  reserved
// Bit   9:8,    reg_top_debug_sel             unsigned, default = 0, top debug select
// Bit   7,      reg_spdif_rx_en_force         unsigned, default = 0, force spdif_rx_en to
// reg_spdif_rx_en_force_value Bit   6,      reg_spdif_rx_en_force_value   unsigned, default = 0,
// value Bit   5,      reg_spdif_rx_sqen_force       unsigned, default = 0, force spdif_rx_sqen to
// reg_spdif_rx_sqe Bit   4,      reg_spdif_rx_sqen_force_value unsigned, default = 0, value Bit 3,
// reg_dmacrx_en_force           unsigned, default = 0, force dmacrx_en to
// reg_dmacrx_en_force_value Bit   2,      reg_dmacrx_en_force_value     unsigned, default = 0,
// value Bit   1,      reg_dmacrx_sqen_force         unsigned, default = 0, force dmacrx_sqen to
// reg_dmacrx_sqen_force_value Bit   0,      reg_dmacrx_sqen_force_value   unsigned, default = 0,
// value
#define P_EARCRX_DMAC_INT_MASK ((volatile uint32_t *)0xfe333e04)
// Bit   31:30,  reserved
// Bit   29:0,   reg_dmac_int_mask             unsigned, default = 0, dmac int mask
#define P_EARCRX_DMAC_INT_PENDING ((volatile uint32_t *)0xfe333e08)
// Bit   31:30,  reserved
// Bit   29:0,   reg_dmac_int_mask             unsigned, default = 0, dmac int pending,read only
#define P_EARCRX_CMDC_INT_MASK ((volatile uint32_t *)0xfe333e0c)
// Bit   31:16,  reserved
// Bit   15:0,   reg_cmdc_int_mask             unsigned, default = 0, cmdc int mask
#define P_EARCRX_CMDC_INT_PENDING ((volatile uint32_t *)0xfe333e10)
// Bit   31:18,  reserved
// Bit   17:0,   reg_cmdc_int_mask             unsigned, default = 0, cmdc int pending,read only
#define P_EARCRX_ANA_CTRL0 ((volatile uint32_t *)0xfe333e14)
// Bit   31:0,   reg_earcrx_ana_ctrl0          unsigned, default = 0
#define P_EARCRX_ANA_CTRL1 ((volatile uint32_t *)0xfe333e18)
// Bit   31:0,   reg_earcrx_ana_ctrl0          unsigned, default = 0
#define P_EARCRX_ANA_STAT0 ((volatile uint32_t *)0xfe333e1c)
// Bit   31:0,   reg_earcrx_ana_ctrl0          unsigned, default = 0
#define P_EARCRX_PLL_CTRL0 ((volatile uint32_t *)0xfe333e20)
// Bit   31:0,   reg_earcrx_ana_ctrl0          unsigned, default = 0
#define P_EARCRX_PLL_CTRL1 ((volatile uint32_t *)0xfe333e24)
// Bit   31:0,   reg_earcrx_ana_ctrl0          unsigned, default = 0
#define P_EARCRX_PLL_CTRL2 ((volatile uint32_t *)0xfe333e28)
// Bit   31:0,   reg_earcrx_ana_ctrl0          unsigned, default = 0
#define P_EARCRX_PLL_CTRL3 ((volatile uint32_t *)0xfe333e2c)
// Bit   31:0,   reg_earcrx_ana_ctrl0          unsigned, default = 0
#define P_EARCRX_PLL_STAT0 ((volatile uint32_t *)0xfe333e30)
// Bit   31:0,   reg_earcrx_ana_ctrl0          unsigned, default = 0
//
// Closing file:  earcrx_top.h
//
//========================================================================
//  AUDIO RESAMPLEB - Registers
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe334000
// -----------------------------------------------
//
// Reading file:  RESAMPLEB.h
//
#define P_AUDIO_RSAMPB_CTRL0 ((volatile uint32_t *)0xfe334000)
// Bit   31:3      reserved
// Bit   2         reg_lock_rst      //unsigned  , default =0;
// Bit   1         reg_rsamp_rst     //unsigned  , default =0;
// Bit   0         reg_sw_rst        //unsigned  , default =0;
#define P_AUDIO_RSAMPB_CTRL1 ((volatile uint32_t *)0xfe334004)
// Bit   31:27      reserved          //unsigned  , default =0;
// Bit   26         reg_watchdog_en   //unsigned  , default =0;
// Bit   25         reg_rsamp_rst_sel //unsigned  , default =0;
// Bit   24         reg_module_bypas  //unsigned  , default =0;
// Bit   23:18      reg_gclk_ctrl     //unsigned  , default =0;
// Bit   17:13      reg_in_msb        //unsigned  , default =23;
// Bit   12         reg_output_en     //unsigned  , default =0;
// Bit   11         reg_rsamp_en      //unsigned  , default =0;
// Bit   10         reg_filt_en       //unsigned  , default =0;
// Bit   9          reg_post_en       //unsigned  , default =0;
// Bit   8          reg_inp_mux_mode  //unsigned  , default =0;
// Bit   7:4        reserved          //unsigned  , default =2;
// Bit   3:0        reg_inp_mux       //unsigned  , default =0;
#define P_AUDIO_RSAMPB_CTRL2 ((volatile uint32_t *)0xfe334008)
// Bit 31:30    reserved              //unsigned  , default =0;
// Bit 29:24    reg_chx_size          //unsigned  , default =2;
// Bit 23:18    reserved              //unsigned  , default =0;
// Bit 17:16    reg_scl_step          //unsigned  , default =0; 0: 1/1  1: 1/2  2: 1/4
// Bit 15:8     reg_filt_tap          //unsigned  , default =63;
// Bit 7:0      reg_intp_tap          //unsigned  , default =63;
#define P_AUDIO_RSAMPB_PHSINIT ((volatile uint32_t *)0xfe33400c)
// Bit   31:28      reserved          //unsigned  , default = 0;
// Bit   27:0       reg_init_phs      //unsigned  , default = 0;
#define P_AUDIO_RSAMPB_PHSSTEP ((volatile uint32_t *)0xfe334010)
// Bit   31         reserved          //unsigned  , default = 0;
// Bit   30:0       reg_rsamp_step    //unsigned  , default = 134217728;//'h800_0000
#define P_AUDIO_RSAMPB_SHIFT ((volatile uint32_t *)0xfe334014)
// Bit   31:24       reg_rsft_iir    //unsigned  , default = 23;
// Bit   23:16       reg_rsft_blnd   //unsigned  , default = 21;
// Bit   15:8        reg_rsft_sinc   //unsigned  , default = 31;
// Bit   7:0         reg_rsft_aa     //unsigned  , default = 31;
#define P_AUDIO_RSAMPB_ADJ_CTRL0 ((volatile uint32_t *)0xfe334018)
// Bit   31:3        reserved                //unsigned
// Bit   2           reg_rsamp_adj_out_inv   //unsigned , default = 0;
// Bit   1           reg_rsamp_adj_force_en  //unsigned , default = 0;
// Bit   0           reg_rsamp_adj_en        //unsigned , default = 0;
#define P_AUDIO_RSAMPB_ADJ_CTRL1 ((volatile uint32_t *)0xfe33401c)
// Bit   31:16       reg_rsamp_adj_odet_step     //unsigned , default = 8;
// Bit   15:0        reg_rsamp_adj_kmax          //unsigned , default = 32768;
#define P_AUDIO_RSAMPB_ADJ_SFT ((volatile uint32_t *)0xfe334020)
// Bit   31:30       reserved                //unsigned , default = 0;
// Bit   29          reg_rsamp_adj_dif_sel   //unsigned , default = 0;
// Bit   28:24       reg_rsamp_adj_ki        //unsigned , default = 9;
// Bit   23:21       reserved                //unsigned , default = 0;
// Bit   20:16       reg_rsamp_adj_kp        //unsigned , default = 1;
// Bit   15:13       reserved                //unsigned , default = 0;
// Bit   12:8        reg_rsamp_adj_ki_sft    //unsigned , default = 6;
// Bit   7:6         reserved                //unsigned , default = 0;
// Bit   5:0         reg_rsamp_adj_out_sft   //unsigned , default = 12;
#define P_AUDIO_RSAMPB_ADJ_IDET_LEN ((volatile uint32_t *)0xfe334024)
// Bit   31:0       reg_rsamp_adj_idet_len       //unsigned , default = 10000;
#define P_AUDIO_RSAMPB_ADJ_FORCE ((volatile uint32_t *)0xfe334028)
// Bit   31:0       reg_rsamp_adj_force_err      //signed , default = 8;
#define P_AUDIO_RSAMPB_ADJ_KI_FORCE ((volatile uint32_t *)0xfe33402c)
// Bit   31:0       reg_rsamp_adj_ki_force //signed , default = 0;
#define P_AUDIO_RSAMPB_WATCHDOG_THRD ((volatile uint32_t *)0xfe334030)
// Bit   31:0       reg_watchdog_thrd      //signed , default = 32'h1000;
#define P_AUDIO_RSAMPB_RO_STATUS ((volatile uint32_t *)0xfe334040)
// Bit   31:0       ro_rsamp_stat  //{din_chx_chk_err,is_idle_st,rsamp_fifo_over_cnt[7:0]}
#define P_AUDIO_RSAMPB_RO_ADJ_FREQ ((volatile uint32_t *)0xfe334044)
// Bit   31:0       ro_rsamp_adj_freq
#define P_AUDIO_RSAMPB_RO_ADJ_DIFF_BAK ((volatile uint32_t *)0xfe334048)
// Bit   31:0       ro_det_diff_bak
#define P_AUDIO_RSAMPB_RO_ADJ_DIFF_DLT ((volatile uint32_t *)0xfe33404c)
// Bit   31:0       ro_det_diff_dlt
#define P_AUDIO_RSAMPB_RO_ADJ_PHS_ERR ((volatile uint32_t *)0xfe334050)
// Bit   31:0       ro_det_phase_err
#define P_AUDIO_RSAMPB_RO_ADJ_KI_OUT ((volatile uint32_t *)0xfe334054)
// Bit   31:0       ro_rsamp_ki_out
#define P_AUDIO_RSAMPB_RO_IN_CNT ((volatile uint32_t *)0xfe334058)
// Bit   31:0       ro_rsamp_in_cnt
#define P_AUDIO_RSAMPB_RO_OUT_CNT ((volatile uint32_t *)0xfe33405c)
// Bit   31:0       ro_rsamp_out_cnt
#define P_AUDIO_RSAMPB_RO_ADJ_PHS_ERR_VAR ((volatile uint32_t *)0xfe334060)
// Bit   31:0       ro_det_phase_err_var
#define P_AUDIO_RSAMPB_POST_COEF0 ((volatile uint32_t *)0xfe334080)
// Bit   31:0       reg_post_coef0 //signed  , default = 0;
#define P_AUDIO_RSAMPB_POST_COEF1 ((volatile uint32_t *)0xfe334084)
// Bit   31:0       reg_post_coef1 //signed  , default = 0;
#define P_AUDIO_RSAMPB_POST_COEF2 ((volatile uint32_t *)0xfe334088)
// Bit   31:0       reg_post_coef2 //signed  , default = 0;
#define P_AUDIO_RSAMPB_POST_COEF3 ((volatile uint32_t *)0xfe33408c)
// Bit   31:0       reg_post_coef3 //signed  , default = 0;
#define P_AUDIO_RSAMPB_POST_COEF4 ((volatile uint32_t *)0xfe334090)
// Bit   31:0       reg_post_coef4 //signed  , default = 0;
#define P_AUDIO_RSAMPB_AA_COEF_ADDR ((volatile uint32_t *)0xfe3340c0)
// Bit   31:0       reg_aa_coef_addr     //unsigned, default = 0;
#define P_AUDIO_RSAMPB_AA_COEF_DATA ((volatile uint32_t *)0xfe3340c4)
// Bit   31:0       reg_aa_coef_data     //signed  , default = 0;
#define P_AUDIO_RSAMPB_SINC_COEF_ADDR ((volatile uint32_t *)0xfe334100)
// Bit   31:0       reg_sinc_coef_addr   //unsigned, default = 0;
#define P_AUDIO_RSAMPB_SINC_COEF_DATA ((volatile uint32_t *)0xfe334104)
// Bit   31:0       reg_sinc_coef_data   //signed  , default = 0;
//
// Closing file:  RESAMPLEB.h
//
//========================================================================
//  AUDIO TOP_VAD - Registers
//========================================================================
// -----------------------------------------------
// REG_BASE:  APB0_BASE_ADDR = 0xfe334c00
// -----------------------------------------------
#define P_EE_AUDIO2_CLK81_CTRL ((volatile uint32_t *)0xfe334c00)
#define P_EE_AUDIO2_CLK81_EN ((volatile uint32_t *)0xfe334c04)
#define P_EE_AUDIO2_SW_RESET0 ((volatile uint32_t *)0xfe334c08)
#define P_EE_AUDIO2_CLK_GATE_EN0 ((volatile uint32_t *)0xfe334c0c)
#define P_EE_AUDIO2_SECURITY_CTRL0 ((volatile uint32_t *)0xfe334c10)
#define P_EE_AUDIO2_SECURITY_CTRL1 ((volatile uint32_t *)0xfe334c14)
#define P_EE_AUDIO2_MCLK_VAD_CTRL ((volatile uint32_t *)0xfe334c40)
#define P_EE_AUDIO2_VAD_CLK_CTRL ((volatile uint32_t *)0xfe334c44)
#define P_EE_AUDIO2_MST_DLY_CTRL0 ((volatile uint32_t *)0xfe334c48)
#define P_EE_AUDIO2_MST_VAD_SCLK_CTRL0 ((volatile uint32_t *)0xfe334c4c)
#define P_EE_AUDIO2_MST_VAD_SCLK_CTRL1 ((volatile uint32_t *)0xfe334c50)
#define P_EE_AUDIO2_CLK_TDMIN_VAD_CTRL ((volatile uint32_t *)0xfe334c54)
#define P_EE_AUDIO2_CLK_PDMIN_CTRL0 ((volatile uint32_t *)0xfe334c58)
#define P_EE_AUDIO2_CLK_PDMIN_CTRL1 ((volatile uint32_t *)0xfe334c5c)
#define P_EE_AUDIO2_AUD_VAD_PAD_CTRL0 ((volatile uint32_t *)0xfe334c60)
#define P_EE_AUDIO2_TOVAD_CTRL0 ((volatile uint32_t *)0xfe334c80)
#define P_EE_AUDIO2_TODDR_VAD_CTRL0 ((volatile uint32_t *)0xfe334cc0)
#define P_EE_AUDIO2_TODDR_VAD_CTRL1 ((volatile uint32_t *)0xfe334cc4)
#define P_EE_AUDIO2_TODDR_VAD_CTRL2 ((volatile uint32_t *)0xfe334cc8)
#define P_EE_AUDIO2_TODDR_VAD_START_ADDR ((volatile uint32_t *)0xfe334ccc)
#define P_EE_AUDIO2_TODDR_VAD_INIT_ADDR ((volatile uint32_t *)0xfe334cd0)
#define P_EE_AUDIO2_TODDR_VAD_FINISH_ADDR ((volatile uint32_t *)0xfe334cd4)
#define P_EE_AUDIO2_TODDR_VAD_START_ADDRB ((volatile uint32_t *)0xfe334cd8)
#define P_EE_AUDIO2_TODDR_VAD_FINISH_ADDRB ((volatile uint32_t *)0xfe334cdc)
#define P_EE_AUDIO2_TODDR_VAD_INT_ADDR ((volatile uint32_t *)0xfe334ce0)
#define P_EE_AUDIO2_TODDR_VAD_STATUS1 ((volatile uint32_t *)0xfe334ce4)
#define P_EE_AUDIO2_TODDR_VAD_STATUS2 ((volatile uint32_t *)0xfe334ce8)
#define P_EE_AUDIO2_TDMIN_VAD_CTRL ((volatile uint32_t *)0xfe334d00)
#define P_EE_AUDIO2_TDMIN_VAD_SWAP0 ((volatile uint32_t *)0xfe334d04)
#define P_EE_AUDIO2_TDMIN_VAD_SWAP1 ((volatile uint32_t *)0xfe334d08)
#define P_EE_AUDIO2_TDMIN_VAD_MUTE_VAL ((volatile uint32_t *)0xfe334d0c)
#define P_EE_AUDIO2_TDMIN_VAD_STAT ((volatile uint32_t *)0xfe334d10)
#define P_EE_AUDIO2_TDMIN_VAD_MUTE0 ((volatile uint32_t *)0xfe334d40)
#define P_EE_AUDIO2_TDMIN_VAD_MUTE1 ((volatile uint32_t *)0xfe334d44)
#define P_EE_AUDIO2_TDMIN_VAD_MUTE2 ((volatile uint32_t *)0xfe334d48)
#define P_EE_AUDIO2_TDMIN_VAD_MUTE3 ((volatile uint32_t *)0xfe334d4c)
#define P_EE_AUDIO2_TDMIN_VAD_MUTE4 ((volatile uint32_t *)0xfe334d50)
#define P_EE_AUDIO2_TDMIN_VAD_MUTE5 ((volatile uint32_t *)0xfe334d54)
#define P_EE_AUDIO2_TDMIN_VAD_MUTE6 ((volatile uint32_t *)0xfe334d58)
#define P_EE_AUDIO2_TDMIN_VAD_MUTE7 ((volatile uint32_t *)0xfe334d5c)
#define P_EE_AUDIO2_TDMIN_VAD_MASK0 ((volatile uint32_t *)0xfe334d60)
#define P_EE_AUDIO2_TDMIN_VAD_MASK1 ((volatile uint32_t *)0xfe334d64)
#define P_EE_AUDIO2_TDMIN_VAD_MASK2 ((volatile uint32_t *)0xfe334d68)
#define P_EE_AUDIO2_TDMIN_VAD_MASK3 ((volatile uint32_t *)0xfe334d6c)
#define P_EE_AUDIO2_TDMIN_VAD_MASK4 ((volatile uint32_t *)0xfe334d70)
#define P_EE_AUDIO2_TDMIN_VAD_MASK5 ((volatile uint32_t *)0xfe334d74)
#define P_EE_AUDIO2_TDMIN_VAD_MASK6 ((volatile uint32_t *)0xfe334d78)
#define P_EE_AUDIO2_TDMIN_VAD_MASK7 ((volatile uint32_t *)0xfe334d7c)
#define P_EE_AUDIO2_VAD_DAT_PAD_CTRL0 ((volatile uint32_t *)0xfe334d80)
#define P_EE_AUDIO2_VAD_DAT_PAD_CTRL1 ((volatile uint32_t *)0xfe334d84)
#define P_EE_AUDIO2_TODDR_VAD_CHNUM_ID0 ((volatile uint32_t *)0xfe334dc0)
#define P_EE_AUDIO2_TODDR_VAD_CHNUM_ID1 ((volatile uint32_t *)0xfe334dc4)
#define P_EE_AUDIO2_TODDR_VAD_CHNUM_ID2 ((volatile uint32_t *)0xfe334dc8)
#define P_EE_AUDIO2_TODDR_VAD_CHNUM_ID3 ((volatile uint32_t *)0xfe334dcc)
#define P_EE_AUDIO2_TODDR_VAD_CHNUM_ID4 ((volatile uint32_t *)0xfe334dd0)
#define P_EE_AUDIO2_TODDR_VAD_CHNUM_ID5 ((volatile uint32_t *)0xfe334dd4)
#define P_EE_AUDIO2_TODDR_VAD_CHNUM_ID6 ((volatile uint32_t *)0xfe334dd8)
#define P_EE_AUDIO2_TODDR_VAD_CHNUM_ID7 ((volatile uint32_t *)0xfe334ddc)
#define P_EE_AUDIO2_TODDR_VAD_CHSYNC_CTRL ((volatile uint32_t *)0xfe334dfc)
#define P_EE_AUDIO2_VAD_AM2AXI_CTRL0 ((volatile uint32_t *)0xfe334e00)
#define P_EE_AUDIO2_VAD_AXIWR_ASYNC_CTRL0 ((volatile uint32_t *)0xfe334e04)
#define P_EE_AUDIO2_VAD_AM2AXI_STAT ((volatile uint32_t *)0xfe334e20)
#define P_EE_AUDIO2_VAD_AXIWR_ASYNC_STAT ((volatile uint32_t *)0xfe334e24)
#define P_EE_AUDIO2_EXCEPTION_IRQ_STS0 ((volatile uint32_t *)0xfe334e40)
#define P_EE_AUDIO2_EXCEPTION_IRQ_MASK0 ((volatile uint32_t *)0xfe334e44)
#define P_EE_AUDIO2_EXCEPTION_IRQ_MODE0 ((volatile uint32_t *)0xfe334e48)
#define P_EE_AUDIO2_EXCEPTION_IRQ_CLR0 ((volatile uint32_t *)0xfe334e4c)
#define P_EE_AUDIO2_EXCEPTION_IRQ_INV0 ((volatile uint32_t *)0xfe334e50)
//
// Closing file:  REG_LIST_AUDIO_RTL.h
//
//
// Reading file:  REG_LIST_DSP_RTL.h
//
// synopsys translate_off
// synopsys translate_on
//========================================================================
//  DSPA - Registers
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe340000
// -----------------------------------------------
#define P_DSP_CFG0 ((volatile uint32_t *)0xfe340000)
#define P_DSP_CFG1 ((volatile uint32_t *)0xfe340004)
#define P_DSP_CFG2 ((volatile uint32_t *)0xfe340008)
#define P_DSP_IMPWIRE ((volatile uint32_t *)0xfe34000c)
#define P_DSP_RESET_VEC ((volatile uint32_t *)0xfe340010)
#define P_DSP_SEC_CFG0 ((volatile uint32_t *)0xfe340018)
#define P_DSP_SEC_CFG1 ((volatile uint32_t *)0xfe34001c)
#define P_DSP_IRQ_CTRL0 ((volatile uint32_t *)0xfe340040)
#define P_DSP_IRQ_CTRL1 ((volatile uint32_t *)0xfe340044)
#define P_DSP_IRQ_CTRL2 ((volatile uint32_t *)0xfe340048)
#define P_DSP_IRQ_CTRL3 ((volatile uint32_t *)0xfe34004c)
#define P_DSP_IRQ_CTRL4 ((volatile uint32_t *)0xfe340050)
#define P_DSP_IRQ_CTRL5 ((volatile uint32_t *)0xfe340054)
#define P_DSP_IRQ_CTRL6 ((volatile uint32_t *)0xfe340058)
#define P_DSP_IRQ_CTRL7 ((volatile uint32_t *)0xfe34005c)
#define P_DSP_IRQ_CTRL8 ((volatile uint32_t *)0xfe340060)
#define P_DSP_IRQ_CTRL9 ((volatile uint32_t *)0xfe340064)
#define P_DSP_IRQ_STS ((volatile uint32_t *)0xfe34007c)
#define P_DSP_REMAP0 ((volatile uint32_t *)0xfe340080)
#define P_DSP_REMAP1 ((volatile uint32_t *)0xfe340084)
#define P_DSP_REMAP2 ((volatile uint32_t *)0xfe340088)
#define P_DSP_STS0 ((volatile uint32_t *)0xfe340100)
#define P_DSP_STS1 ((volatile uint32_t *)0xfe340104)
#define P_DSP_STS2 ((volatile uint32_t *)0xfe340108)
#define P_DSP_STS3 ((volatile uint32_t *)0xfe34010c)
#define P_DSP_STS4 ((volatile uint32_t *)0xfe340110)
#define P_DSP_STS5 ((volatile uint32_t *)0xfe340114)
#define P_DSP_QIF_CTRL ((volatile uint32_t *)0xfe340200)
#define P_DSP_QIF_STS ((volatile uint32_t *)0xfe340204)
#define P_DSP_WRFIFO_TOCPUA ((volatile uint32_t *)0xfe340208)
#define P_DSP_WRFIFO_TOCPUB ((volatile uint32_t *)0xfe34020c)
#define P_DSP_WRFIFO_TODSP ((volatile uint32_t *)0xfe340210)
#define P_DSP_RDFIFO_FRCPUA ((volatile uint32_t *)0xfe340220)
#define P_DSP_RDFIFO_FRCPUB ((volatile uint32_t *)0xfe340224)
#define P_DSP_RDFIFO_FRDSP ((volatile uint32_t *)0xfe340228)
#define P_DSP_PM_CTRL ((volatile uint32_t *)0xfe340240)
#define P_DSP_PDEBUGDATA_STS ((volatile uint32_t *)0xfe340244)
#define P_DSP_PDEBUGINST_STS ((volatile uint32_t *)0xfe340248)
#define P_DSP_PDEBUGLS0STAT_STS ((volatile uint32_t *)0xfe34024c)
#define P_DSP_PDEBUGLS1STAT_STS ((volatile uint32_t *)0xfe340250)
#define P_DSP_PDEBUGOUTPIF_STS ((volatile uint32_t *)0xfe340254)
#define P_DSP_PDEBUGPC_STS ((volatile uint32_t *)0xfe340258)
#define P_DSP_PDEBUGPREFETCHL1FILL_STS ((volatile uint32_t *)0xfe34025c)
#define P_DSP_PDEBUGPREFETCHLOOKUP_STS ((volatile uint32_t *)0xfe340260)
#define P_DSP_PDEBUGSTATUS_STS ((volatile uint32_t *)0xfe340264)
//========================================================================
//  DSPB - Registers
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe350000
// -----------------------------------------------
#define P_DSPB_CFG0 ((volatile uint32_t *)0xfe350000)
#define P_DSPB_CFG1 ((volatile uint32_t *)0xfe350004)
#define P_DSPB_CFG2 ((volatile uint32_t *)0xfe350008)
#define P_DSPB_IMPWIRE ((volatile uint32_t *)0xfe35000c)
#define P_DSPB_RESET_VEC ((volatile uint32_t *)0xfe350010)
#define P_DSPB_SEC_CFG0 ((volatile uint32_t *)0xfe350018)
#define P_DSPB_SEC_CFG1 ((volatile uint32_t *)0xfe35001c)
#define P_DSPB_IRQ_CTRL0 ((volatile uint32_t *)0xfe350040)
#define P_DSPB_IRQ_CTRL1 ((volatile uint32_t *)0xfe350044)
#define P_DSPB_IRQ_CTRL2 ((volatile uint32_t *)0xfe350048)
#define P_DSPB_IRQ_CTRL3 ((volatile uint32_t *)0xfe35004c)
#define P_DSPB_IRQ_CTRL4 ((volatile uint32_t *)0xfe350050)
#define P_DSPB_IRQ_CTRL5 ((volatile uint32_t *)0xfe350054)
#define P_DSPB_IRQ_CTRL6 ((volatile uint32_t *)0xfe350058)
#define P_DSPB_IRQ_CTRL7 ((volatile uint32_t *)0xfe35005c)
#define P_DSPB_IRQ_CTRL8 ((volatile uint32_t *)0xfe350060)
#define P_DSPB_IRQ_CTRL9 ((volatile uint32_t *)0xfe350064)
#define P_DSPB_IRQ_STS ((volatile uint32_t *)0xfe35007c)
#define P_DSPB_REMAP0 ((volatile uint32_t *)0xfe350080)
#define P_DSPB_REMAP1 ((volatile uint32_t *)0xfe350084)
#define P_DSPB_REMAP2 ((volatile uint32_t *)0xfe350088)
#define P_DSPB_STS0 ((volatile uint32_t *)0xfe350100)
#define P_DSPB_STS1 ((volatile uint32_t *)0xfe350104)
#define P_DSPB_STS2 ((volatile uint32_t *)0xfe350108)
#define P_DSPB_STS3 ((volatile uint32_t *)0xfe35010c)
#define P_DSPB_STS4 ((volatile uint32_t *)0xfe350110)
#define P_DSPB_STS5 ((volatile uint32_t *)0xfe350114)
#define P_DSPB_QIF_CTRL ((volatile uint32_t *)0xfe350200)
#define P_DSPB_QIF_STS ((volatile uint32_t *)0xfe350204)
#define P_DSPB_WRFIFO_TOCPUA ((volatile uint32_t *)0xfe350208)
#define P_DSPB_WRFIFO_TOCPUB ((volatile uint32_t *)0xfe35020c)
#define P_DSPB_WRFIFO_TODSP ((volatile uint32_t *)0xfe350210)
#define P_DSPB_RDFIFO_FRCPUA ((volatile uint32_t *)0xfe350220)
#define P_DSPB_RDFIFO_FRCPUB ((volatile uint32_t *)0xfe350224)
#define P_DSPB_RDFIFO_FRDSP ((volatile uint32_t *)0xfe350228)
#define P_DSPB_PM_CTRL ((volatile uint32_t *)0xfe350240)
#define P_DSPB_PDEBUGDATA_STS ((volatile uint32_t *)0xfe350244)
#define P_DSPB_PDEBUGINST_STS ((volatile uint32_t *)0xfe350248)
#define P_DSPB_PDEBUGLS0STAT_STS ((volatile uint32_t *)0xfe35024c)
#define P_DSPB_PDEBUGLS1STAT_STS ((volatile uint32_t *)0xfe350250)
#define P_DSPB_PDEBUGOUTPIF_STS ((volatile uint32_t *)0xfe350254)
#define P_DSPB_PDEBUGPC_STS ((volatile uint32_t *)0xfe350258)
#define P_DSPB_PDEBUGPREFETCHL1FILL_STS ((volatile uint32_t *)0xfe35025c)
#define P_DSPB_PDEBUGPREFETCHLOOKUP_STS ((volatile uint32_t *)0xfe350260)
#define P_DSPB_PDEBUGSTATUS_STS ((volatile uint32_t *)0xfe350264)
// synopsys translate_off
// synopsys translate_on
//
// Closing file:  REG_LIST_DSP_RTL.h
//
//
// Reading file:  REG_LIST_SECURITY_RTL.h
//
//
// Title:      REG_LIST_SECURITY_RTL.h
//
// Author:     shan.luan
//
// Created:    23:09:44 28/02/2020
//
// Description:
//
// Note:
//
// History:
//
//========================================================================
//  TS_DEMUX_REG - Registers
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe444000
// -----------------------------------------------
#define P_RCH_READY_CHANNEL_0 ((volatile uint32_t *)0xfe444000)
#define P_RCH_READY_CHANNEL_1 ((volatile uint32_t *)0xfe444020)
#define P_RCH_READY_CHANNEL_2 ((volatile uint32_t *)0xfe444040)
#define P_RCH_READY_CHANNEL_3 ((volatile uint32_t *)0xfe444060)
#define P_RCH_READY_CHANNEL_4 ((volatile uint32_t *)0xfe444080)
#define P_RCH_READY_CHANNEL_5 ((volatile uint32_t *)0xfe4440a0)
#define P_RCH_READY_CHANNEL_6 ((volatile uint32_t *)0xfe4440c0)
#define P_RCH_READY_CHANNEL_7 ((volatile uint32_t *)0xfe4440e0)
#define P_RCH_READY_CHANNEL_8 ((volatile uint32_t *)0xfe444100)
#define P_RCH_READY_CHANNEL_9 ((volatile uint32_t *)0xfe444120)
#define P_RCH_READY_CHANNEL_10 ((volatile uint32_t *)0xfe444140)
#define P_RCH_READY_CHANNEL_11 ((volatile uint32_t *)0xfe444160)
#define P_RCH_READY_CHANNEL_12 ((volatile uint32_t *)0xfe444180)
#define P_RCH_READY_CHANNEL_13 ((volatile uint32_t *)0xfe4441a0)
#define P_RCH_READY_CHANNEL_14 ((volatile uint32_t *)0xfe4441c0)
#define P_RCH_READY_CHANNEL_15 ((volatile uint32_t *)0xfe4441e0)
#define P_RCH_READY_CHANNEL_16 ((volatile uint32_t *)0xfe444200)
#define P_RCH_READY_CHANNEL_17 ((volatile uint32_t *)0xfe444220)
#define P_RCH_READY_CHANNEL_18 ((volatile uint32_t *)0xfe444240)
#define P_RCH_READY_CHANNEL_19 ((volatile uint32_t *)0xfe444260)
#define P_RCH_READY_CHANNEL_20 ((volatile uint32_t *)0xfe444280)
#define P_RCH_READY_CHANNEL_21 ((volatile uint32_t *)0xfe4442a0)
#define P_RCH_READY_CHANNEL_22 ((volatile uint32_t *)0xfe4442c0)
#define P_RCH_READY_CHANNEL_23 ((volatile uint32_t *)0xfe4442e0)
#define P_RCH_READY_CHANNEL_24 ((volatile uint32_t *)0xfe444300)
#define P_RCH_READY_CHANNEL_25 ((volatile uint32_t *)0xfe444320)
#define P_RCH_READY_CHANNEL_26 ((volatile uint32_t *)0xfe444340)
#define P_RCH_READY_CHANNEL_27 ((volatile uint32_t *)0xfe444360)
#define P_RCH_READY_CHANNEL_28 ((volatile uint32_t *)0xfe444380)
#define P_RCH_READY_CHANNEL_29 ((volatile uint32_t *)0xfe4443a0)
#define P_RCH_READY_CHANNEL_30 ((volatile uint32_t *)0xfe4443c0)
#define P_RCH_READY_CHANNEL_31 ((volatile uint32_t *)0xfe4443e0)
#define P_RCH_STATUS_CHANNEL_0 ((volatile uint32_t *)0xfe444004)
#define P_RCH_STATUS_CHANNEL_1 ((volatile uint32_t *)0xfe444024)
#define P_RCH_STATUS_CHANNEL_2 ((volatile uint32_t *)0xfe444044)
#define P_RCH_STATUS_CHANNEL_3 ((volatile uint32_t *)0xfe444064)
#define P_RCH_STATUS_CHANNEL_4 ((volatile uint32_t *)0xfe444084)
#define P_RCH_STATUS_CHANNEL_5 ((volatile uint32_t *)0xfe4440a4)
#define P_RCH_STATUS_CHANNEL_6 ((volatile uint32_t *)0xfe4440c4)
#define P_RCH_STATUS_CHANNEL_7 ((volatile uint32_t *)0xfe4440e4)
#define P_RCH_STATUS_CHANNEL_8 ((volatile uint32_t *)0xfe444104)
#define P_RCH_STATUS_CHANNEL_9 ((volatile uint32_t *)0xfe444124)
#define P_RCH_STATUS_CHANNEL_10 ((volatile uint32_t *)0xfe444144)
#define P_RCH_STATUS_CHANNEL_11 ((volatile uint32_t *)0xfe444164)
#define P_RCH_STATUS_CHANNEL_12 ((volatile uint32_t *)0xfe444184)
#define P_RCH_STATUS_CHANNEL_13 ((volatile uint32_t *)0xfe4441a4)
#define P_RCH_STATUS_CHANNEL_14 ((volatile uint32_t *)0xfe4441c4)
#define P_RCH_STATUS_CHANNEL_15 ((volatile uint32_t *)0xfe4441e4)
#define P_RCH_STATUS_CHANNEL_16 ((volatile uint32_t *)0xfe444204)
#define P_RCH_STATUS_CHANNEL_17 ((volatile uint32_t *)0xfe444224)
#define P_RCH_STATUS_CHANNEL_18 ((volatile uint32_t *)0xfe444244)
#define P_RCH_STATUS_CHANNEL_19 ((volatile uint32_t *)0xfe444264)
#define P_RCH_STATUS_CHANNEL_20 ((volatile uint32_t *)0xfe444284)
#define P_RCH_STATUS_CHANNEL_21 ((volatile uint32_t *)0xfe4442a4)
#define P_RCH_STATUS_CHANNEL_22 ((volatile uint32_t *)0xfe4442c4)
#define P_RCH_STATUS_CHANNEL_23 ((volatile uint32_t *)0xfe4442e4)
#define P_RCH_STATUS_CHANNEL_24 ((volatile uint32_t *)0xfe444304)
#define P_RCH_STATUS_CHANNEL_25 ((volatile uint32_t *)0xfe444324)
#define P_RCH_STATUS_CHANNEL_26 ((volatile uint32_t *)0xfe444344)
#define P_RCH_STATUS_CHANNEL_27 ((volatile uint32_t *)0xfe444364)
#define P_RCH_STATUS_CHANNEL_28 ((volatile uint32_t *)0xfe444384)
#define P_RCH_STATUS_CHANNEL_29 ((volatile uint32_t *)0xfe4443a4)
#define P_RCH_STATUS_CHANNEL_30 ((volatile uint32_t *)0xfe4443c4)
#define P_RCH_STATUS_CHANNEL_31 ((volatile uint32_t *)0xfe4443e4)
#define P_RCH_CFG_CHANNEL_0 ((volatile uint32_t *)0xfe444008)
#define P_RCH_CFG_CHANNEL_1 ((volatile uint32_t *)0xfe444028)
#define P_RCH_CFG_CHANNEL_2 ((volatile uint32_t *)0xfe444048)
#define P_RCH_CFG_CHANNEL_3 ((volatile uint32_t *)0xfe444068)
#define P_RCH_CFG_CHANNEL_4 ((volatile uint32_t *)0xfe444088)
#define P_RCH_CFG_CHANNEL_5 ((volatile uint32_t *)0xfe4440a8)
#define P_RCH_CFG_CHANNEL_6 ((volatile uint32_t *)0xfe4440c8)
#define P_RCH_CFG_CHANNEL_7 ((volatile uint32_t *)0xfe4440e8)
#define P_RCH_CFG_CHANNEL_8 ((volatile uint32_t *)0xfe444108)
#define P_RCH_CFG_CHANNEL_9 ((volatile uint32_t *)0xfe444128)
#define P_RCH_CFG_CHANNEL_10 ((volatile uint32_t *)0xfe444148)
#define P_RCH_CFG_CHANNEL_11 ((volatile uint32_t *)0xfe444168)
#define P_RCH_CFG_CHANNEL_12 ((volatile uint32_t *)0xfe444188)
#define P_RCH_CFG_CHANNEL_13 ((volatile uint32_t *)0xfe4441a8)
#define P_RCH_CFG_CHANNEL_14 ((volatile uint32_t *)0xfe4441c8)
#define P_RCH_CFG_CHANNEL_15 ((volatile uint32_t *)0xfe4441e8)
#define P_RCH_CFG_CHANNEL_16 ((volatile uint32_t *)0xfe444208)
#define P_RCH_CFG_CHANNEL_17 ((volatile uint32_t *)0xfe444228)
#define P_RCH_CFG_CHANNEL_18 ((volatile uint32_t *)0xfe444248)
#define P_RCH_CFG_CHANNEL_19 ((volatile uint32_t *)0xfe444268)
#define P_RCH_CFG_CHANNEL_20 ((volatile uint32_t *)0xfe444288)
#define P_RCH_CFG_CHANNEL_21 ((volatile uint32_t *)0xfe4442a8)
#define P_RCH_CFG_CHANNEL_22 ((volatile uint32_t *)0xfe4442c8)
#define P_RCH_CFG_CHANNEL_23 ((volatile uint32_t *)0xfe4442e8)
#define P_RCH_CFG_CHANNEL_24 ((volatile uint32_t *)0xfe444308)
#define P_RCH_CFG_CHANNEL_25 ((volatile uint32_t *)0xfe444328)
#define P_RCH_CFG_CHANNEL_26 ((volatile uint32_t *)0xfe444348)
#define P_RCH_CFG_CHANNEL_27 ((volatile uint32_t *)0xfe444368)
#define P_RCH_CFG_CHANNEL_28 ((volatile uint32_t *)0xfe444388)
#define P_RCH_CFG_CHANNEL_29 ((volatile uint32_t *)0xfe4443a8)
#define P_RCH_CFG_CHANNEL_30 ((volatile uint32_t *)0xfe4443c8)
#define P_RCH_CFG_CHANNEL_31 ((volatile uint32_t *)0xfe4443e8)
#define P_RCH_ADDR_CHANNEL_0 ((volatile uint32_t *)0xfe44400c)
#define P_RCH_ADDR_CHANNEL_1 ((volatile uint32_t *)0xfe44402c)
#define P_RCH_ADDR_CHANNEL_2 ((volatile uint32_t *)0xfe44404c)
#define P_RCH_ADDR_CHANNEL_3 ((volatile uint32_t *)0xfe44406c)
#define P_RCH_ADDR_CHANNEL_4 ((volatile uint32_t *)0xfe44408c)
#define P_RCH_ADDR_CHANNEL_5 ((volatile uint32_t *)0xfe4440ac)
#define P_RCH_ADDR_CHANNEL_6 ((volatile uint32_t *)0xfe4440cc)
#define P_RCH_ADDR_CHANNEL_7 ((volatile uint32_t *)0xfe4440ec)
#define P_RCH_ADDR_CHANNEL_8 ((volatile uint32_t *)0xfe44410c)
#define P_RCH_ADDR_CHANNEL_9 ((volatile uint32_t *)0xfe44412c)
#define P_RCH_ADDR_CHANNEL_10 ((volatile uint32_t *)0xfe44414c)
#define P_RCH_ADDR_CHANNEL_11 ((volatile uint32_t *)0xfe44416c)
#define P_RCH_ADDR_CHANNEL_12 ((volatile uint32_t *)0xfe44418c)
#define P_RCH_ADDR_CHANNEL_13 ((volatile uint32_t *)0xfe4441ac)
#define P_RCH_ADDR_CHANNEL_14 ((volatile uint32_t *)0xfe4441cc)
#define P_RCH_ADDR_CHANNEL_15 ((volatile uint32_t *)0xfe4441ec)
#define P_RCH_ADDR_CHANNEL_16 ((volatile uint32_t *)0xfe44420c)
#define P_RCH_ADDR_CHANNEL_17 ((volatile uint32_t *)0xfe44422c)
#define P_RCH_ADDR_CHANNEL_18 ((volatile uint32_t *)0xfe44424c)
#define P_RCH_ADDR_CHANNEL_19 ((volatile uint32_t *)0xfe44426c)
#define P_RCH_ADDR_CHANNEL_20 ((volatile uint32_t *)0xfe44428c)
#define P_RCH_ADDR_CHANNEL_21 ((volatile uint32_t *)0xfe4442ac)
#define P_RCH_ADDR_CHANNEL_22 ((volatile uint32_t *)0xfe4442cc)
#define P_RCH_ADDR_CHANNEL_23 ((volatile uint32_t *)0xfe4442ec)
#define P_RCH_ADDR_CHANNEL_24 ((volatile uint32_t *)0xfe44430c)
#define P_RCH_ADDR_CHANNEL_25 ((volatile uint32_t *)0xfe44432c)
#define P_RCH_ADDR_CHANNEL_26 ((volatile uint32_t *)0xfe44434c)
#define P_RCH_ADDR_CHANNEL_27 ((volatile uint32_t *)0xfe44436c)
#define P_RCH_ADDR_CHANNEL_28 ((volatile uint32_t *)0xfe44438c)
#define P_RCH_ADDR_CHANNEL_29 ((volatile uint32_t *)0xfe4443ac)
#define P_RCH_ADDR_CHANNEL_30 ((volatile uint32_t *)0xfe4443cc)
#define P_RCH_ADDR_CHANNEL_31 ((volatile uint32_t *)0xfe4443ec)
#define P_RCH_LEN_CHANNEL_0 ((volatile uint32_t *)0xfe444010)
#define P_RCH_LEN_CHANNEL_1 ((volatile uint32_t *)0xfe444030)
#define P_RCH_LEN_CHANNEL_2 ((volatile uint32_t *)0xfe444050)
#define P_RCH_LEN_CHANNEL_3 ((volatile uint32_t *)0xfe444070)
#define P_RCH_LEN_CHANNEL_4 ((volatile uint32_t *)0xfe444090)
#define P_RCH_LEN_CHANNEL_5 ((volatile uint32_t *)0xfe4440b0)
#define P_RCH_LEN_CHANNEL_6 ((volatile uint32_t *)0xfe4440d0)
#define P_RCH_LEN_CHANNEL_7 ((volatile uint32_t *)0xfe4440f0)
#define P_RCH_LEN_CHANNEL_8 ((volatile uint32_t *)0xfe444110)
#define P_RCH_LEN_CHANNEL_9 ((volatile uint32_t *)0xfe444130)
#define P_RCH_LEN_CHANNEL_10 ((volatile uint32_t *)0xfe444150)
#define P_RCH_LEN_CHANNEL_11 ((volatile uint32_t *)0xfe444170)
#define P_RCH_LEN_CHANNEL_12 ((volatile uint32_t *)0xfe444190)
#define P_RCH_LEN_CHANNEL_13 ((volatile uint32_t *)0xfe4441b0)
#define P_RCH_LEN_CHANNEL_14 ((volatile uint32_t *)0xfe4441d0)
#define P_RCH_LEN_CHANNEL_15 ((volatile uint32_t *)0xfe4441f0)
#define P_RCH_LEN_CHANNEL_16 ((volatile uint32_t *)0xfe444210)
#define P_RCH_LEN_CHANNEL_17 ((volatile uint32_t *)0xfe444230)
#define P_RCH_LEN_CHANNEL_18 ((volatile uint32_t *)0xfe444250)
#define P_RCH_LEN_CHANNEL_19 ((volatile uint32_t *)0xfe444270)
#define P_RCH_LEN_CHANNEL_20 ((volatile uint32_t *)0xfe444290)
#define P_RCH_LEN_CHANNEL_21 ((volatile uint32_t *)0xfe4442b0)
#define P_RCH_LEN_CHANNEL_22 ((volatile uint32_t *)0xfe4442d0)
#define P_RCH_LEN_CHANNEL_23 ((volatile uint32_t *)0xfe4442f0)
#define P_RCH_LEN_CHANNEL_24 ((volatile uint32_t *)0xfe444310)
#define P_RCH_LEN_CHANNEL_25 ((volatile uint32_t *)0xfe444330)
#define P_RCH_LEN_CHANNEL_26 ((volatile uint32_t *)0xfe444350)
#define P_RCH_LEN_CHANNEL_27 ((volatile uint32_t *)0xfe444370)
#define P_RCH_LEN_CHANNEL_28 ((volatile uint32_t *)0xfe444390)
#define P_RCH_LEN_CHANNEL_29 ((volatile uint32_t *)0xfe4443b0)
#define P_RCH_LEN_CHANNEL_30 ((volatile uint32_t *)0xfe4443d0)
#define P_RCH_LEN_CHANNEL_31 ((volatile uint32_t *)0xfe4443f0)
#define P_RCH_RD_LEN_CHANNEL_0 ((volatile uint32_t *)0xfe444014)
#define P_RCH_RD_LEN_CHANNEL_1 ((volatile uint32_t *)0xfe444034)
#define P_RCH_RD_LEN_CHANNEL_2 ((volatile uint32_t *)0xfe444054)
#define P_RCH_RD_LEN_CHANNEL_3 ((volatile uint32_t *)0xfe444074)
#define P_RCH_RD_LEN_CHANNEL_4 ((volatile uint32_t *)0xfe444094)
#define P_RCH_RD_LEN_CHANNEL_5 ((volatile uint32_t *)0xfe4440b4)
#define P_RCH_RD_LEN_CHANNEL_6 ((volatile uint32_t *)0xfe4440d4)
#define P_RCH_RD_LEN_CHANNEL_7 ((volatile uint32_t *)0xfe4440f4)
#define P_RCH_RD_LEN_CHANNEL_8 ((volatile uint32_t *)0xfe444114)
#define P_RCH_RD_LEN_CHANNEL_9 ((volatile uint32_t *)0xfe444134)
#define P_RCH_RD_LEN_CHANNEL_10 ((volatile uint32_t *)0xfe444154)
#define P_RCH_RD_LEN_CHANNEL_11 ((volatile uint32_t *)0xfe444174)
#define P_RCH_RD_LEN_CHANNEL_12 ((volatile uint32_t *)0xfe444194)
#define P_RCH_RD_LEN_CHANNEL_13 ((volatile uint32_t *)0xfe4441b4)
#define P_RCH_RD_LEN_CHANNEL_14 ((volatile uint32_t *)0xfe4441d4)
#define P_RCH_RD_LEN_CHANNEL_15 ((volatile uint32_t *)0xfe4441f4)
#define P_RCH_RD_LEN_CHANNEL_16 ((volatile uint32_t *)0xfe444214)
#define P_RCH_RD_LEN_CHANNEL_17 ((volatile uint32_t *)0xfe444234)
#define P_RCH_RD_LEN_CHANNEL_18 ((volatile uint32_t *)0xfe444254)
#define P_RCH_RD_LEN_CHANNEL_19 ((volatile uint32_t *)0xfe444274)
#define P_RCH_RD_LEN_CHANNEL_20 ((volatile uint32_t *)0xfe444294)
#define P_RCH_RD_LEN_CHANNEL_21 ((volatile uint32_t *)0xfe4442b4)
#define P_RCH_RD_LEN_CHANNEL_22 ((volatile uint32_t *)0xfe4442d4)
#define P_RCH_RD_LEN_CHANNEL_23 ((volatile uint32_t *)0xfe4442f4)
#define P_RCH_RD_LEN_CHANNEL_24 ((volatile uint32_t *)0xfe444314)
#define P_RCH_RD_LEN_CHANNEL_25 ((volatile uint32_t *)0xfe444334)
#define P_RCH_RD_LEN_CHANNEL_26 ((volatile uint32_t *)0xfe444354)
#define P_RCH_RD_LEN_CHANNEL_27 ((volatile uint32_t *)0xfe444374)
#define P_RCH_RD_LEN_CHANNEL_28 ((volatile uint32_t *)0xfe444394)
#define P_RCH_RD_LEN_CHANNEL_29 ((volatile uint32_t *)0xfe4443b4)
#define P_RCH_RD_LEN_CHANNEL_30 ((volatile uint32_t *)0xfe4443d4)
#define P_RCH_RD_LEN_CHANNEL_31 ((volatile uint32_t *)0xfe4443f4)
#define P_RCH_PTR_CHANNEL_0 ((volatile uint32_t *)0xfe444018)
#define P_RCH_PTR_CHANNEL_1 ((volatile uint32_t *)0xfe444038)
#define P_RCH_PTR_CHANNEL_2 ((volatile uint32_t *)0xfe444058)
#define P_RCH_PTR_CHANNEL_3 ((volatile uint32_t *)0xfe444078)
#define P_RCH_PTR_CHANNEL_4 ((volatile uint32_t *)0xfe444098)
#define P_RCH_PTR_CHANNEL_5 ((volatile uint32_t *)0xfe4440b8)
#define P_RCH_PTR_CHANNEL_6 ((volatile uint32_t *)0xfe4440d8)
#define P_RCH_PTR_CHANNEL_7 ((volatile uint32_t *)0xfe4440f8)
#define P_RCH_PTR_CHANNEL_8 ((volatile uint32_t *)0xfe444118)
#define P_RCH_PTR_CHANNEL_9 ((volatile uint32_t *)0xfe444138)
#define P_RCH_PTR_CHANNEL_10 ((volatile uint32_t *)0xfe444158)
#define P_RCH_PTR_CHANNEL_11 ((volatile uint32_t *)0xfe444178)
#define P_RCH_PTR_CHANNEL_12 ((volatile uint32_t *)0xfe444198)
#define P_RCH_PTR_CHANNEL_13 ((volatile uint32_t *)0xfe4441b8)
#define P_RCH_PTR_CHANNEL_14 ((volatile uint32_t *)0xfe4441d8)
#define P_RCH_PTR_CHANNEL_15 ((volatile uint32_t *)0xfe4441f8)
#define P_RCH_PTR_CHANNEL_16 ((volatile uint32_t *)0xfe444218)
#define P_RCH_PTR_CHANNEL_17 ((volatile uint32_t *)0xfe444238)
#define P_RCH_PTR_CHANNEL_18 ((volatile uint32_t *)0xfe444258)
#define P_RCH_PTR_CHANNEL_19 ((volatile uint32_t *)0xfe444278)
#define P_RCH_PTR_CHANNEL_20 ((volatile uint32_t *)0xfe444298)
#define P_RCH_PTR_CHANNEL_21 ((volatile uint32_t *)0xfe4442b8)
#define P_RCH_PTR_CHANNEL_22 ((volatile uint32_t *)0xfe4442d8)
#define P_RCH_PTR_CHANNEL_23 ((volatile uint32_t *)0xfe4442f8)
#define P_RCH_PTR_CHANNEL_24 ((volatile uint32_t *)0xfe444318)
#define P_RCH_PTR_CHANNEL_25 ((volatile uint32_t *)0xfe444338)
#define P_RCH_PTR_CHANNEL_26 ((volatile uint32_t *)0xfe444358)
#define P_RCH_PTR_CHANNEL_27 ((volatile uint32_t *)0xfe444378)
#define P_RCH_PTR_CHANNEL_28 ((volatile uint32_t *)0xfe444398)
#define P_RCH_PTR_CHANNEL_29 ((volatile uint32_t *)0xfe4443b8)
#define P_RCH_PTR_CHANNEL_30 ((volatile uint32_t *)0xfe4443d8)
#define P_RCH_PTR_CHANNEL_31 ((volatile uint32_t *)0xfe4443f8)
#define P_RCH_PKT_SYNC_STATUS_CHANNEL_0 ((volatile uint32_t *)0xfe44401c)
#define P_RCH_PKT_SYNC_STATUS_CHANNEL_1 ((volatile uint32_t *)0xfe44403c)
#define P_RCH_PKT_SYNC_STATUS_CHANNEL_2 ((volatile uint32_t *)0xfe44405c)
#define P_RCH_PKT_SYNC_STATUS_CHANNEL_3 ((volatile uint32_t *)0xfe44407c)
#define P_RCH_PKT_SYNC_STATUS_CHANNEL_4 ((volatile uint32_t *)0xfe44409c)
#define P_RCH_PKT_SYNC_STATUS_CHANNEL_5 ((volatile uint32_t *)0xfe4440bc)
#define P_RCH_PKT_SYNC_STATUS_CHANNEL_6 ((volatile uint32_t *)0xfe4440dc)
#define P_RCH_PKT_SYNC_STATUS_CHANNEL_7 ((volatile uint32_t *)0xfe4440fc)
#define P_RCH_PKT_SYNC_STATUS_CHANNEL_8 ((volatile uint32_t *)0xfe44411c)
#define P_RCH_PKT_SYNC_STATUS_CHANNEL_9 ((volatile uint32_t *)0xfe44413c)
#define P_RCH_PKT_SYNC_STATUS_CHANNEL_10 ((volatile uint32_t *)0xfe44415c)
#define P_RCH_PKT_SYNC_STATUS_CHANNEL_11 ((volatile uint32_t *)0xfe44417c)
#define P_RCH_PKT_SYNC_STATUS_CHANNEL_12 ((volatile uint32_t *)0xfe44419c)
#define P_RCH_PKT_SYNC_STATUS_CHANNEL_13 ((volatile uint32_t *)0xfe4441bc)
#define P_RCH_PKT_SYNC_STATUS_CHANNEL_14 ((volatile uint32_t *)0xfe4441dc)
#define P_RCH_PKT_SYNC_STATUS_CHANNEL_15 ((volatile uint32_t *)0xfe4441fc)
#define P_RCH_PKT_SYNC_STATUS_CHANNEL_16 ((volatile uint32_t *)0xfe44421c)
#define P_RCH_PKT_SYNC_STATUS_CHANNEL_17 ((volatile uint32_t *)0xfe44423c)
#define P_RCH_PKT_SYNC_STATUS_CHANNEL_18 ((volatile uint32_t *)0xfe44425c)
#define P_RCH_PKT_SYNC_STATUS_CHANNEL_19 ((volatile uint32_t *)0xfe44427c)
#define P_RCH_PKT_SYNC_STATUS_CHANNEL_20 ((volatile uint32_t *)0xfe44429c)
#define P_RCH_PKT_SYNC_STATUS_CHANNEL_21 ((volatile uint32_t *)0xfe4442bc)
#define P_RCH_PKT_SYNC_STATUS_CHANNEL_22 ((volatile uint32_t *)0xfe4442dc)
#define P_RCH_PKT_SYNC_STATUS_CHANNEL_23 ((volatile uint32_t *)0xfe4442fc)
#define P_RCH_PKT_SYNC_STATUS_CHANNEL_24 ((volatile uint32_t *)0xfe44431c)
#define P_RCH_PKT_SYNC_STATUS_CHANNEL_25 ((volatile uint32_t *)0xfe44433c)
#define P_RCH_PKT_SYNC_STATUS_CHANNEL_26 ((volatile uint32_t *)0xfe44435c)
#define P_RCH_PKT_SYNC_STATUS_CHANNEL_27 ((volatile uint32_t *)0xfe44437c)
#define P_RCH_PKT_SYNC_STATUS_CHANNEL_28 ((volatile uint32_t *)0xfe44439c)
#define P_RCH_PKT_SYNC_STATUS_CHANNEL_29 ((volatile uint32_t *)0xfe4443bc)
#define P_RCH_PKT_SYNC_STATUS_CHANNEL_30 ((volatile uint32_t *)0xfe4443dc)
#define P_RCH_PKT_SYNC_STATUS_CHANNEL_31 ((volatile uint32_t *)0xfe4443fc)
#define P_WCH_READY_CHANNEL_0 ((volatile uint32_t *)0xfe445000)
#define P_WCH_READY_CHANNEL_1 ((volatile uint32_t *)0xfe445020)
#define P_WCH_READY_CHANNEL_2 ((volatile uint32_t *)0xfe445040)
#define P_WCH_READY_CHANNEL_3 ((volatile uint32_t *)0xfe445060)
#define P_WCH_READY_CHANNEL_4 ((volatile uint32_t *)0xfe445080)
#define P_WCH_READY_CHANNEL_5 ((volatile uint32_t *)0xfe4450a0)
#define P_WCH_READY_CHANNEL_6 ((volatile uint32_t *)0xfe4450c0)
#define P_WCH_READY_CHANNEL_7 ((volatile uint32_t *)0xfe4450e0)
#define P_WCH_READY_CHANNEL_8 ((volatile uint32_t *)0xfe445100)
#define P_WCH_READY_CHANNEL_9 ((volatile uint32_t *)0xfe445120)
#define P_WCH_READY_CHANNEL_10 ((volatile uint32_t *)0xfe445140)
#define P_WCH_READY_CHANNEL_11 ((volatile uint32_t *)0xfe445160)
#define P_WCH_READY_CHANNEL_12 ((volatile uint32_t *)0xfe445180)
#define P_WCH_READY_CHANNEL_13 ((volatile uint32_t *)0xfe4451a0)
#define P_WCH_READY_CHANNEL_14 ((volatile uint32_t *)0xfe4451c0)
#define P_WCH_READY_CHANNEL_15 ((volatile uint32_t *)0xfe4451e0)
#define P_WCH_READY_CHANNEL_16 ((volatile uint32_t *)0xfe445200)
#define P_WCH_READY_CHANNEL_17 ((volatile uint32_t *)0xfe445220)
#define P_WCH_READY_CHANNEL_18 ((volatile uint32_t *)0xfe445240)
#define P_WCH_READY_CHANNEL_19 ((volatile uint32_t *)0xfe445260)
#define P_WCH_READY_CHANNEL_20 ((volatile uint32_t *)0xfe445280)
#define P_WCH_READY_CHANNEL_21 ((volatile uint32_t *)0xfe4452a0)
#define P_WCH_READY_CHANNEL_22 ((volatile uint32_t *)0xfe4452c0)
#define P_WCH_READY_CHANNEL_23 ((volatile uint32_t *)0xfe4452e0)
#define P_WCH_READY_CHANNEL_24 ((volatile uint32_t *)0xfe445300)
#define P_WCH_READY_CHANNEL_25 ((volatile uint32_t *)0xfe445320)
#define P_WCH_READY_CHANNEL_26 ((volatile uint32_t *)0xfe445340)
#define P_WCH_READY_CHANNEL_27 ((volatile uint32_t *)0xfe445360)
#define P_WCH_READY_CHANNEL_28 ((volatile uint32_t *)0xfe445380)
#define P_WCH_READY_CHANNEL_29 ((volatile uint32_t *)0xfe4453a0)
#define P_WCH_READY_CHANNEL_30 ((volatile uint32_t *)0xfe4453c0)
#define P_WCH_READY_CHANNEL_31 ((volatile uint32_t *)0xfe4453e0)
#define P_WCH_READY_CHANNEL_32 ((volatile uint32_t *)0xfe445400)
#define P_WCH_READY_CHANNEL_33 ((volatile uint32_t *)0xfe445420)
#define P_WCH_READY_CHANNEL_34 ((volatile uint32_t *)0xfe445440)
#define P_WCH_READY_CHANNEL_35 ((volatile uint32_t *)0xfe445460)
#define P_WCH_READY_CHANNEL_36 ((volatile uint32_t *)0xfe445480)
#define P_WCH_READY_CHANNEL_37 ((volatile uint32_t *)0xfe4454a0)
#define P_WCH_READY_CHANNEL_38 ((volatile uint32_t *)0xfe4454c0)
#define P_WCH_READY_CHANNEL_39 ((volatile uint32_t *)0xfe4454e0)
#define P_WCH_READY_CHANNEL_40 ((volatile uint32_t *)0xfe445500)
#define P_WCH_READY_CHANNEL_41 ((volatile uint32_t *)0xfe445520)
#define P_WCH_READY_CHANNEL_42 ((volatile uint32_t *)0xfe445540)
#define P_WCH_READY_CHANNEL_43 ((volatile uint32_t *)0xfe445560)
#define P_WCH_READY_CHANNEL_44 ((volatile uint32_t *)0xfe445580)
#define P_WCH_READY_CHANNEL_45 ((volatile uint32_t *)0xfe4455a0)
#define P_WCH_READY_CHANNEL_46 ((volatile uint32_t *)0xfe4455c0)
#define P_WCH_READY_CHANNEL_47 ((volatile uint32_t *)0xfe4455e0)
#define P_WCH_READY_CHANNEL_48 ((volatile uint32_t *)0xfe445600)
#define P_WCH_READY_CHANNEL_49 ((volatile uint32_t *)0xfe445620)
#define P_WCH_READY_CHANNEL_50 ((volatile uint32_t *)0xfe445640)
#define P_WCH_READY_CHANNEL_51 ((volatile uint32_t *)0xfe445660)
#define P_WCH_READY_CHANNEL_52 ((volatile uint32_t *)0xfe445680)
#define P_WCH_READY_CHANNEL_53 ((volatile uint32_t *)0xfe4456a0)
#define P_WCH_READY_CHANNEL_54 ((volatile uint32_t *)0xfe4456c0)
#define P_WCH_READY_CHANNEL_55 ((volatile uint32_t *)0xfe4456e0)
#define P_WCH_READY_CHANNEL_56 ((volatile uint32_t *)0xfe445700)
#define P_WCH_READY_CHANNEL_57 ((volatile uint32_t *)0xfe445720)
#define P_WCH_READY_CHANNEL_58 ((volatile uint32_t *)0xfe445740)
#define P_WCH_READY_CHANNEL_59 ((volatile uint32_t *)0xfe445760)
#define P_WCH_READY_CHANNEL_60 ((volatile uint32_t *)0xfe445780)
#define P_WCH_READY_CHANNEL_61 ((volatile uint32_t *)0xfe4457a0)
#define P_WCH_READY_CHANNEL_62 ((volatile uint32_t *)0xfe4457c0)
#define P_WCH_READY_CHANNEL_63 ((volatile uint32_t *)0xfe4457e0)
#define P_WCH_READY_CHANNEL_64 ((volatile uint32_t *)0xfe445800)
#define P_WCH_READY_CHANNEL_65 ((volatile uint32_t *)0xfe445820)
#define P_WCH_READY_CHANNEL_66 ((volatile uint32_t *)0xfe445840)
#define P_WCH_READY_CHANNEL_67 ((volatile uint32_t *)0xfe445860)
#define P_WCH_READY_CHANNEL_68 ((volatile uint32_t *)0xfe445880)
#define P_WCH_READY_CHANNEL_69 ((volatile uint32_t *)0xfe4458a0)
#define P_WCH_READY_CHANNEL_70 ((volatile uint32_t *)0xfe4458c0)
#define P_WCH_READY_CHANNEL_71 ((volatile uint32_t *)0xfe4458e0)
#define P_WCH_READY_CHANNEL_72 ((volatile uint32_t *)0xfe445900)
#define P_WCH_READY_CHANNEL_73 ((volatile uint32_t *)0xfe445920)
#define P_WCH_READY_CHANNEL_74 ((volatile uint32_t *)0xfe445940)
#define P_WCH_READY_CHANNEL_75 ((volatile uint32_t *)0xfe445960)
#define P_WCH_READY_CHANNEL_76 ((volatile uint32_t *)0xfe445980)
#define P_WCH_READY_CHANNEL_77 ((volatile uint32_t *)0xfe4459a0)
#define P_WCH_READY_CHANNEL_78 ((volatile uint32_t *)0xfe4459c0)
#define P_WCH_READY_CHANNEL_79 ((volatile uint32_t *)0xfe4459e0)
#define P_WCH_READY_CHANNEL_80 ((volatile uint32_t *)0xfe445a00)
#define P_WCH_READY_CHANNEL_81 ((volatile uint32_t *)0xfe445a20)
#define P_WCH_READY_CHANNEL_82 ((volatile uint32_t *)0xfe445a40)
#define P_WCH_READY_CHANNEL_83 ((volatile uint32_t *)0xfe445a60)
#define P_WCH_READY_CHANNEL_84 ((volatile uint32_t *)0xfe445a80)
#define P_WCH_READY_CHANNEL_85 ((volatile uint32_t *)0xfe445aa0)
#define P_WCH_READY_CHANNEL_86 ((volatile uint32_t *)0xfe445ac0)
#define P_WCH_READY_CHANNEL_87 ((volatile uint32_t *)0xfe445ae0)
#define P_WCH_READY_CHANNEL_88 ((volatile uint32_t *)0xfe445b00)
#define P_WCH_READY_CHANNEL_89 ((volatile uint32_t *)0xfe445b20)
#define P_WCH_READY_CHANNEL_90 ((volatile uint32_t *)0xfe445b40)
#define P_WCH_READY_CHANNEL_91 ((volatile uint32_t *)0xfe445b60)
#define P_WCH_READY_CHANNEL_92 ((volatile uint32_t *)0xfe445b80)
#define P_WCH_READY_CHANNEL_93 ((volatile uint32_t *)0xfe445ba0)
#define P_WCH_READY_CHANNEL_94 ((volatile uint32_t *)0xfe445bc0)
#define P_WCH_READY_CHANNEL_95 ((volatile uint32_t *)0xfe445be0)
#define P_WCH_READY_CHANNEL_96 ((volatile uint32_t *)0xfe445c00)
#define P_WCH_READY_CHANNEL_97 ((volatile uint32_t *)0xfe445c20)
#define P_WCH_READY_CHANNEL_98 ((volatile uint32_t *)0xfe445c40)
#define P_WCH_READY_CHANNEL_99 ((volatile uint32_t *)0xfe445c60)
#define P_WCH_READY_CHANNEL_100 ((volatile uint32_t *)0xfe445c80)
#define P_WCH_READY_CHANNEL_101 ((volatile uint32_t *)0xfe445ca0)
#define P_WCH_READY_CHANNEL_102 ((volatile uint32_t *)0xfe445cc0)
#define P_WCH_READY_CHANNEL_103 ((volatile uint32_t *)0xfe445ce0)
#define P_WCH_READY_CHANNEL_104 ((volatile uint32_t *)0xfe445d00)
#define P_WCH_READY_CHANNEL_105 ((volatile uint32_t *)0xfe445d20)
#define P_WCH_READY_CHANNEL_106 ((volatile uint32_t *)0xfe445d40)
#define P_WCH_READY_CHANNEL_107 ((volatile uint32_t *)0xfe445d60)
#define P_WCH_READY_CHANNEL_108 ((volatile uint32_t *)0xfe445d80)
#define P_WCH_READY_CHANNEL_109 ((volatile uint32_t *)0xfe445da0)
#define P_WCH_READY_CHANNEL_110 ((volatile uint32_t *)0xfe445dc0)
#define P_WCH_READY_CHANNEL_111 ((volatile uint32_t *)0xfe445de0)
#define P_WCH_READY_CHANNEL_112 ((volatile uint32_t *)0xfe445e00)
#define P_WCH_READY_CHANNEL_113 ((volatile uint32_t *)0xfe445e20)
#define P_WCH_READY_CHANNEL_114 ((volatile uint32_t *)0xfe445e40)
#define P_WCH_READY_CHANNEL_115 ((volatile uint32_t *)0xfe445e60)
#define P_WCH_READY_CHANNEL_116 ((volatile uint32_t *)0xfe445e80)
#define P_WCH_READY_CHANNEL_117 ((volatile uint32_t *)0xfe445ea0)
#define P_WCH_READY_CHANNEL_118 ((volatile uint32_t *)0xfe445ec0)
#define P_WCH_READY_CHANNEL_119 ((volatile uint32_t *)0xfe445ee0)
#define P_WCH_READY_CHANNEL_120 ((volatile uint32_t *)0xfe445f00)
#define P_WCH_READY_CHANNEL_121 ((volatile uint32_t *)0xfe445f20)
#define P_WCH_READY_CHANNEL_122 ((volatile uint32_t *)0xfe445f40)
#define P_WCH_READY_CHANNEL_123 ((volatile uint32_t *)0xfe445f60)
#define P_WCH_READY_CHANNEL_124 ((volatile uint32_t *)0xfe445f80)
#define P_WCH_READY_CHANNEL_125 ((volatile uint32_t *)0xfe445fa0)
#define P_WCH_READY_CHANNEL_126 ((volatile uint32_t *)0xfe445fc0)
#define P_WCH_READY_CHANNEL_127 ((volatile uint32_t *)0xfe445fe0)
#define P_WCH_DEBUG_CHANNEL_0 ((volatile uint32_t *)0xfe445004)
#define P_WCH_DEBUG_CHANNEL_1 ((volatile uint32_t *)0xfe445024)
#define P_WCH_DEBUG_CHANNEL_2 ((volatile uint32_t *)0xfe445044)
#define P_WCH_DEBUG_CHANNEL_3 ((volatile uint32_t *)0xfe445064)
#define P_WCH_DEBUG_CHANNEL_4 ((volatile uint32_t *)0xfe445084)
#define P_WCH_DEBUG_CHANNEL_5 ((volatile uint32_t *)0xfe4450a4)
#define P_WCH_DEBUG_CHANNEL_6 ((volatile uint32_t *)0xfe4450c4)
#define P_WCH_DEBUG_CHANNEL_7 ((volatile uint32_t *)0xfe4450e4)
#define P_WCH_DEBUG_CHANNEL_8 ((volatile uint32_t *)0xfe445104)
#define P_WCH_DEBUG_CHANNEL_9 ((volatile uint32_t *)0xfe445124)
#define P_WCH_DEBUG_CHANNEL_10 ((volatile uint32_t *)0xfe445144)
#define P_WCH_DEBUG_CHANNEL_11 ((volatile uint32_t *)0xfe445164)
#define P_WCH_DEBUG_CHANNEL_12 ((volatile uint32_t *)0xfe445184)
#define P_WCH_DEBUG_CHANNEL_13 ((volatile uint32_t *)0xfe4451a4)
#define P_WCH_DEBUG_CHANNEL_14 ((volatile uint32_t *)0xfe4451c4)
#define P_WCH_DEBUG_CHANNEL_15 ((volatile uint32_t *)0xfe4451e4)
#define P_WCH_DEBUG_CHANNEL_16 ((volatile uint32_t *)0xfe445204)
#define P_WCH_DEBUG_CHANNEL_17 ((volatile uint32_t *)0xfe445224)
#define P_WCH_DEBUG_CHANNEL_18 ((volatile uint32_t *)0xfe445244)
#define P_WCH_DEBUG_CHANNEL_19 ((volatile uint32_t *)0xfe445264)
#define P_WCH_DEBUG_CHANNEL_20 ((volatile uint32_t *)0xfe445284)
#define P_WCH_DEBUG_CHANNEL_21 ((volatile uint32_t *)0xfe4452a4)
#define P_WCH_DEBUG_CHANNEL_22 ((volatile uint32_t *)0xfe4452c4)
#define P_WCH_DEBUG_CHANNEL_23 ((volatile uint32_t *)0xfe4452e4)
#define P_WCH_DEBUG_CHANNEL_24 ((volatile uint32_t *)0xfe445304)
#define P_WCH_DEBUG_CHANNEL_25 ((volatile uint32_t *)0xfe445324)
#define P_WCH_DEBUG_CHANNEL_26 ((volatile uint32_t *)0xfe445344)
#define P_WCH_DEBUG_CHANNEL_27 ((volatile uint32_t *)0xfe445364)
#define P_WCH_DEBUG_CHANNEL_28 ((volatile uint32_t *)0xfe445384)
#define P_WCH_DEBUG_CHANNEL_29 ((volatile uint32_t *)0xfe4453a4)
#define P_WCH_DEBUG_CHANNEL_30 ((volatile uint32_t *)0xfe4453c4)
#define P_WCH_DEBUG_CHANNEL_31 ((volatile uint32_t *)0xfe4453e4)
#define P_WCH_DEBUG_CHANNEL_32 ((volatile uint32_t *)0xfe445404)
#define P_WCH_DEBUG_CHANNEL_33 ((volatile uint32_t *)0xfe445424)
#define P_WCH_DEBUG_CHANNEL_34 ((volatile uint32_t *)0xfe445444)
#define P_WCH_DEBUG_CHANNEL_35 ((volatile uint32_t *)0xfe445464)
#define P_WCH_DEBUG_CHANNEL_36 ((volatile uint32_t *)0xfe445484)
#define P_WCH_DEBUG_CHANNEL_37 ((volatile uint32_t *)0xfe4454a4)
#define P_WCH_DEBUG_CHANNEL_38 ((volatile uint32_t *)0xfe4454c4)
#define P_WCH_DEBUG_CHANNEL_39 ((volatile uint32_t *)0xfe4454e4)
#define P_WCH_DEBUG_CHANNEL_40 ((volatile uint32_t *)0xfe445504)
#define P_WCH_DEBUG_CHANNEL_41 ((volatile uint32_t *)0xfe445524)
#define P_WCH_DEBUG_CHANNEL_42 ((volatile uint32_t *)0xfe445544)
#define P_WCH_DEBUG_CHANNEL_43 ((volatile uint32_t *)0xfe445564)
#define P_WCH_DEBUG_CHANNEL_44 ((volatile uint32_t *)0xfe445584)
#define P_WCH_DEBUG_CHANNEL_45 ((volatile uint32_t *)0xfe4455a4)
#define P_WCH_DEBUG_CHANNEL_46 ((volatile uint32_t *)0xfe4455c4)
#define P_WCH_DEBUG_CHANNEL_47 ((volatile uint32_t *)0xfe4455e4)
#define P_WCH_DEBUG_CHANNEL_48 ((volatile uint32_t *)0xfe445604)
#define P_WCH_DEBUG_CHANNEL_49 ((volatile uint32_t *)0xfe445624)
#define P_WCH_DEBUG_CHANNEL_50 ((volatile uint32_t *)0xfe445644)
#define P_WCH_DEBUG_CHANNEL_51 ((volatile uint32_t *)0xfe445664)
#define P_WCH_DEBUG_CHANNEL_52 ((volatile uint32_t *)0xfe445684)
#define P_WCH_DEBUG_CHANNEL_53 ((volatile uint32_t *)0xfe4456a4)
#define P_WCH_DEBUG_CHANNEL_54 ((volatile uint32_t *)0xfe4456c4)
#define P_WCH_DEBUG_CHANNEL_55 ((volatile uint32_t *)0xfe4456e4)
#define P_WCH_DEBUG_CHANNEL_56 ((volatile uint32_t *)0xfe445704)
#define P_WCH_DEBUG_CHANNEL_57 ((volatile uint32_t *)0xfe445724)
#define P_WCH_DEBUG_CHANNEL_58 ((volatile uint32_t *)0xfe445744)
#define P_WCH_DEBUG_CHANNEL_59 ((volatile uint32_t *)0xfe445764)
#define P_WCH_DEBUG_CHANNEL_60 ((volatile uint32_t *)0xfe445784)
#define P_WCH_DEBUG_CHANNEL_61 ((volatile uint32_t *)0xfe4457a4)
#define P_WCH_DEBUG_CHANNEL_62 ((volatile uint32_t *)0xfe4457c4)
#define P_WCH_DEBUG_CHANNEL_63 ((volatile uint32_t *)0xfe4457e4)
#define P_WCH_DEBUG_CHANNEL_64 ((volatile uint32_t *)0xfe445804)
#define P_WCH_DEBUG_CHANNEL_65 ((volatile uint32_t *)0xfe445824)
#define P_WCH_DEBUG_CHANNEL_66 ((volatile uint32_t *)0xfe445844)
#define P_WCH_DEBUG_CHANNEL_67 ((volatile uint32_t *)0xfe445864)
#define P_WCH_DEBUG_CHANNEL_68 ((volatile uint32_t *)0xfe445884)
#define P_WCH_DEBUG_CHANNEL_69 ((volatile uint32_t *)0xfe4458a4)
#define P_WCH_DEBUG_CHANNEL_70 ((volatile uint32_t *)0xfe4458c4)
#define P_WCH_DEBUG_CHANNEL_71 ((volatile uint32_t *)0xfe4458e4)
#define P_WCH_DEBUG_CHANNEL_72 ((volatile uint32_t *)0xfe445904)
#define P_WCH_DEBUG_CHANNEL_73 ((volatile uint32_t *)0xfe445924)
#define P_WCH_DEBUG_CHANNEL_74 ((volatile uint32_t *)0xfe445944)
#define P_WCH_DEBUG_CHANNEL_75 ((volatile uint32_t *)0xfe445964)
#define P_WCH_DEBUG_CHANNEL_76 ((volatile uint32_t *)0xfe445984)
#define P_WCH_DEBUG_CHANNEL_77 ((volatile uint32_t *)0xfe4459a4)
#define P_WCH_DEBUG_CHANNEL_78 ((volatile uint32_t *)0xfe4459c4)
#define P_WCH_DEBUG_CHANNEL_79 ((volatile uint32_t *)0xfe4459e4)
#define P_WCH_DEBUG_CHANNEL_80 ((volatile uint32_t *)0xfe445a04)
#define P_WCH_DEBUG_CHANNEL_81 ((volatile uint32_t *)0xfe445a24)
#define P_WCH_DEBUG_CHANNEL_82 ((volatile uint32_t *)0xfe445a44)
#define P_WCH_DEBUG_CHANNEL_83 ((volatile uint32_t *)0xfe445a64)
#define P_WCH_DEBUG_CHANNEL_84 ((volatile uint32_t *)0xfe445a84)
#define P_WCH_DEBUG_CHANNEL_85 ((volatile uint32_t *)0xfe445aa4)
#define P_WCH_DEBUG_CHANNEL_86 ((volatile uint32_t *)0xfe445ac4)
#define P_WCH_DEBUG_CHANNEL_87 ((volatile uint32_t *)0xfe445ae4)
#define P_WCH_DEBUG_CHANNEL_88 ((volatile uint32_t *)0xfe445b04)
#define P_WCH_DEBUG_CHANNEL_89 ((volatile uint32_t *)0xfe445b24)
#define P_WCH_DEBUG_CHANNEL_90 ((volatile uint32_t *)0xfe445b44)
#define P_WCH_DEBUG_CHANNEL_91 ((volatile uint32_t *)0xfe445b64)
#define P_WCH_DEBUG_CHANNEL_92 ((volatile uint32_t *)0xfe445b84)
#define P_WCH_DEBUG_CHANNEL_93 ((volatile uint32_t *)0xfe445ba4)
#define P_WCH_DEBUG_CHANNEL_94 ((volatile uint32_t *)0xfe445bc4)
#define P_WCH_DEBUG_CHANNEL_95 ((volatile uint32_t *)0xfe445be4)
#define P_WCH_DEBUG_CHANNEL_96 ((volatile uint32_t *)0xfe445c04)
#define P_WCH_DEBUG_CHANNEL_97 ((volatile uint32_t *)0xfe445c24)
#define P_WCH_DEBUG_CHANNEL_98 ((volatile uint32_t *)0xfe445c44)
#define P_WCH_DEBUG_CHANNEL_99 ((volatile uint32_t *)0xfe445c64)
#define P_WCH_DEBUG_CHANNEL_100 ((volatile uint32_t *)0xfe445c84)
#define P_WCH_DEBUG_CHANNEL_101 ((volatile uint32_t *)0xfe445ca4)
#define P_WCH_DEBUG_CHANNEL_102 ((volatile uint32_t *)0xfe445cc4)
#define P_WCH_DEBUG_CHANNEL_103 ((volatile uint32_t *)0xfe445ce4)
#define P_WCH_DEBUG_CHANNEL_104 ((volatile uint32_t *)0xfe445d04)
#define P_WCH_DEBUG_CHANNEL_105 ((volatile uint32_t *)0xfe445d24)
#define P_WCH_DEBUG_CHANNEL_106 ((volatile uint32_t *)0xfe445d44)
#define P_WCH_DEBUG_CHANNEL_107 ((volatile uint32_t *)0xfe445d64)
#define P_WCH_DEBUG_CHANNEL_108 ((volatile uint32_t *)0xfe445d84)
#define P_WCH_DEBUG_CHANNEL_109 ((volatile uint32_t *)0xfe445da4)
#define P_WCH_DEBUG_CHANNEL_110 ((volatile uint32_t *)0xfe445dc4)
#define P_WCH_DEBUG_CHANNEL_111 ((volatile uint32_t *)0xfe445de4)
#define P_WCH_DEBUG_CHANNEL_112 ((volatile uint32_t *)0xfe445e04)
#define P_WCH_DEBUG_CHANNEL_113 ((volatile uint32_t *)0xfe445e24)
#define P_WCH_DEBUG_CHANNEL_114 ((volatile uint32_t *)0xfe445e44)
#define P_WCH_DEBUG_CHANNEL_115 ((volatile uint32_t *)0xfe445e64)
#define P_WCH_DEBUG_CHANNEL_116 ((volatile uint32_t *)0xfe445e84)
#define P_WCH_DEBUG_CHANNEL_117 ((volatile uint32_t *)0xfe445ea4)
#define P_WCH_DEBUG_CHANNEL_118 ((volatile uint32_t *)0xfe445ec4)
#define P_WCH_DEBUG_CHANNEL_119 ((volatile uint32_t *)0xfe445ee4)
#define P_WCH_DEBUG_CHANNEL_120 ((volatile uint32_t *)0xfe445f04)
#define P_WCH_DEBUG_CHANNEL_121 ((volatile uint32_t *)0xfe445f24)
#define P_WCH_DEBUG_CHANNEL_122 ((volatile uint32_t *)0xfe445f44)
#define P_WCH_DEBUG_CHANNEL_123 ((volatile uint32_t *)0xfe445f64)
#define P_WCH_DEBUG_CHANNEL_124 ((volatile uint32_t *)0xfe445f84)
#define P_WCH_DEBUG_CHANNEL_125 ((volatile uint32_t *)0xfe445fa4)
#define P_WCH_DEBUG_CHANNEL_126 ((volatile uint32_t *)0xfe445fc4)
#define P_WCH_DEBUG_CHANNEL_127 ((volatile uint32_t *)0xfe445fe4)
#define P_WCH_CFG_CHANNEL_0 ((volatile uint32_t *)0xfe445008)
#define P_WCH_CFG_CHANNEL_1 ((volatile uint32_t *)0xfe445028)
#define P_WCH_CFG_CHANNEL_2 ((volatile uint32_t *)0xfe445048)
#define P_WCH_CFG_CHANNEL_3 ((volatile uint32_t *)0xfe445068)
#define P_WCH_CFG_CHANNEL_4 ((volatile uint32_t *)0xfe445088)
#define P_WCH_CFG_CHANNEL_5 ((volatile uint32_t *)0xfe4450a8)
#define P_WCH_CFG_CHANNEL_6 ((volatile uint32_t *)0xfe4450c8)
#define P_WCH_CFG_CHANNEL_7 ((volatile uint32_t *)0xfe4450e8)
#define P_WCH_CFG_CHANNEL_8 ((volatile uint32_t *)0xfe445108)
#define P_WCH_CFG_CHANNEL_9 ((volatile uint32_t *)0xfe445128)
#define P_WCH_CFG_CHANNEL_10 ((volatile uint32_t *)0xfe445148)
#define P_WCH_CFG_CHANNEL_11 ((volatile uint32_t *)0xfe445168)
#define P_WCH_CFG_CHANNEL_12 ((volatile uint32_t *)0xfe445188)
#define P_WCH_CFG_CHANNEL_13 ((volatile uint32_t *)0xfe4451a8)
#define P_WCH_CFG_CHANNEL_14 ((volatile uint32_t *)0xfe4451c8)
#define P_WCH_CFG_CHANNEL_15 ((volatile uint32_t *)0xfe4451e8)
#define P_WCH_CFG_CHANNEL_16 ((volatile uint32_t *)0xfe445208)
#define P_WCH_CFG_CHANNEL_17 ((volatile uint32_t *)0xfe445228)
#define P_WCH_CFG_CHANNEL_18 ((volatile uint32_t *)0xfe445248)
#define P_WCH_CFG_CHANNEL_19 ((volatile uint32_t *)0xfe445268)
#define P_WCH_CFG_CHANNEL_20 ((volatile uint32_t *)0xfe445288)
#define P_WCH_CFG_CHANNEL_21 ((volatile uint32_t *)0xfe4452a8)
#define P_WCH_CFG_CHANNEL_22 ((volatile uint32_t *)0xfe4452c8)
#define P_WCH_CFG_CHANNEL_23 ((volatile uint32_t *)0xfe4452e8)
#define P_WCH_CFG_CHANNEL_24 ((volatile uint32_t *)0xfe445308)
#define P_WCH_CFG_CHANNEL_25 ((volatile uint32_t *)0xfe445328)
#define P_WCH_CFG_CHANNEL_26 ((volatile uint32_t *)0xfe445348)
#define P_WCH_CFG_CHANNEL_27 ((volatile uint32_t *)0xfe445368)
#define P_WCH_CFG_CHANNEL_28 ((volatile uint32_t *)0xfe445388)
#define P_WCH_CFG_CHANNEL_29 ((volatile uint32_t *)0xfe4453a8)
#define P_WCH_CFG_CHANNEL_30 ((volatile uint32_t *)0xfe4453c8)
#define P_WCH_CFG_CHANNEL_31 ((volatile uint32_t *)0xfe4453e8)
#define P_WCH_CFG_CHANNEL_32 ((volatile uint32_t *)0xfe445408)
#define P_WCH_CFG_CHANNEL_33 ((volatile uint32_t *)0xfe445428)
#define P_WCH_CFG_CHANNEL_34 ((volatile uint32_t *)0xfe445448)
#define P_WCH_CFG_CHANNEL_35 ((volatile uint32_t *)0xfe445468)
#define P_WCH_CFG_CHANNEL_36 ((volatile uint32_t *)0xfe445488)
#define P_WCH_CFG_CHANNEL_37 ((volatile uint32_t *)0xfe4454a8)
#define P_WCH_CFG_CHANNEL_38 ((volatile uint32_t *)0xfe4454c8)
#define P_WCH_CFG_CHANNEL_39 ((volatile uint32_t *)0xfe4454e8)
#define P_WCH_CFG_CHANNEL_40 ((volatile uint32_t *)0xfe445508)
#define P_WCH_CFG_CHANNEL_41 ((volatile uint32_t *)0xfe445528)
#define P_WCH_CFG_CHANNEL_42 ((volatile uint32_t *)0xfe445548)
#define P_WCH_CFG_CHANNEL_43 ((volatile uint32_t *)0xfe445568)
#define P_WCH_CFG_CHANNEL_44 ((volatile uint32_t *)0xfe445588)
#define P_WCH_CFG_CHANNEL_45 ((volatile uint32_t *)0xfe4455a8)
#define P_WCH_CFG_CHANNEL_46 ((volatile uint32_t *)0xfe4455c8)
#define P_WCH_CFG_CHANNEL_47 ((volatile uint32_t *)0xfe4455e8)
#define P_WCH_CFG_CHANNEL_48 ((volatile uint32_t *)0xfe445608)
#define P_WCH_CFG_CHANNEL_49 ((volatile uint32_t *)0xfe445628)
#define P_WCH_CFG_CHANNEL_50 ((volatile uint32_t *)0xfe445648)
#define P_WCH_CFG_CHANNEL_51 ((volatile uint32_t *)0xfe445668)
#define P_WCH_CFG_CHANNEL_52 ((volatile uint32_t *)0xfe445688)
#define P_WCH_CFG_CHANNEL_53 ((volatile uint32_t *)0xfe4456a8)
#define P_WCH_CFG_CHANNEL_54 ((volatile uint32_t *)0xfe4456c8)
#define P_WCH_CFG_CHANNEL_55 ((volatile uint32_t *)0xfe4456e8)
#define P_WCH_CFG_CHANNEL_56 ((volatile uint32_t *)0xfe445708)
#define P_WCH_CFG_CHANNEL_57 ((volatile uint32_t *)0xfe445728)
#define P_WCH_CFG_CHANNEL_58 ((volatile uint32_t *)0xfe445748)
#define P_WCH_CFG_CHANNEL_59 ((volatile uint32_t *)0xfe445768)
#define P_WCH_CFG_CHANNEL_60 ((volatile uint32_t *)0xfe445788)
#define P_WCH_CFG_CHANNEL_61 ((volatile uint32_t *)0xfe4457a8)
#define P_WCH_CFG_CHANNEL_62 ((volatile uint32_t *)0xfe4457c8)
#define P_WCH_CFG_CHANNEL_63 ((volatile uint32_t *)0xfe4457e8)
#define P_WCH_CFG_CHANNEL_64 ((volatile uint32_t *)0xfe445808)
#define P_WCH_CFG_CHANNEL_65 ((volatile uint32_t *)0xfe445828)
#define P_WCH_CFG_CHANNEL_66 ((volatile uint32_t *)0xfe445848)
#define P_WCH_CFG_CHANNEL_67 ((volatile uint32_t *)0xfe445868)
#define P_WCH_CFG_CHANNEL_68 ((volatile uint32_t *)0xfe445888)
#define P_WCH_CFG_CHANNEL_69 ((volatile uint32_t *)0xfe4458a8)
#define P_WCH_CFG_CHANNEL_70 ((volatile uint32_t *)0xfe4458c8)
#define P_WCH_CFG_CHANNEL_71 ((volatile uint32_t *)0xfe4458e8)
#define P_WCH_CFG_CHANNEL_72 ((volatile uint32_t *)0xfe445908)
#define P_WCH_CFG_CHANNEL_73 ((volatile uint32_t *)0xfe445928)
#define P_WCH_CFG_CHANNEL_74 ((volatile uint32_t *)0xfe445948)
#define P_WCH_CFG_CHANNEL_75 ((volatile uint32_t *)0xfe445968)
#define P_WCH_CFG_CHANNEL_76 ((volatile uint32_t *)0xfe445988)
#define P_WCH_CFG_CHANNEL_77 ((volatile uint32_t *)0xfe4459a8)
#define P_WCH_CFG_CHANNEL_78 ((volatile uint32_t *)0xfe4459c8)
#define P_WCH_CFG_CHANNEL_79 ((volatile uint32_t *)0xfe4459e8)
#define P_WCH_CFG_CHANNEL_80 ((volatile uint32_t *)0xfe445a08)
#define P_WCH_CFG_CHANNEL_81 ((volatile uint32_t *)0xfe445a28)
#define P_WCH_CFG_CHANNEL_82 ((volatile uint32_t *)0xfe445a48)
#define P_WCH_CFG_CHANNEL_83 ((volatile uint32_t *)0xfe445a68)
#define P_WCH_CFG_CHANNEL_84 ((volatile uint32_t *)0xfe445a88)
#define P_WCH_CFG_CHANNEL_85 ((volatile uint32_t *)0xfe445aa8)
#define P_WCH_CFG_CHANNEL_86 ((volatile uint32_t *)0xfe445ac8)
#define P_WCH_CFG_CHANNEL_87 ((volatile uint32_t *)0xfe445ae8)
#define P_WCH_CFG_CHANNEL_88 ((volatile uint32_t *)0xfe445b08)
#define P_WCH_CFG_CHANNEL_89 ((volatile uint32_t *)0xfe445b28)
#define P_WCH_CFG_CHANNEL_90 ((volatile uint32_t *)0xfe445b48)
#define P_WCH_CFG_CHANNEL_91 ((volatile uint32_t *)0xfe445b68)
#define P_WCH_CFG_CHANNEL_92 ((volatile uint32_t *)0xfe445b88)
#define P_WCH_CFG_CHANNEL_93 ((volatile uint32_t *)0xfe445ba8)
#define P_WCH_CFG_CHANNEL_94 ((volatile uint32_t *)0xfe445bc8)
#define P_WCH_CFG_CHANNEL_95 ((volatile uint32_t *)0xfe445be8)
#define P_WCH_CFG_CHANNEL_96 ((volatile uint32_t *)0xfe445c08)
#define P_WCH_CFG_CHANNEL_97 ((volatile uint32_t *)0xfe445c28)
#define P_WCH_CFG_CHANNEL_98 ((volatile uint32_t *)0xfe445c48)
#define P_WCH_CFG_CHANNEL_99 ((volatile uint32_t *)0xfe445c68)
#define P_WCH_CFG_CHANNEL_100 ((volatile uint32_t *)0xfe445c88)
#define P_WCH_CFG_CHANNEL_101 ((volatile uint32_t *)0xfe445ca8)
#define P_WCH_CFG_CHANNEL_102 ((volatile uint32_t *)0xfe445cc8)
#define P_WCH_CFG_CHANNEL_103 ((volatile uint32_t *)0xfe445ce8)
#define P_WCH_CFG_CHANNEL_104 ((volatile uint32_t *)0xfe445d08)
#define P_WCH_CFG_CHANNEL_105 ((volatile uint32_t *)0xfe445d28)
#define P_WCH_CFG_CHANNEL_106 ((volatile uint32_t *)0xfe445d48)
#define P_WCH_CFG_CHANNEL_107 ((volatile uint32_t *)0xfe445d68)
#define P_WCH_CFG_CHANNEL_108 ((volatile uint32_t *)0xfe445d88)
#define P_WCH_CFG_CHANNEL_109 ((volatile uint32_t *)0xfe445da8)
#define P_WCH_CFG_CHANNEL_110 ((volatile uint32_t *)0xfe445dc8)
#define P_WCH_CFG_CHANNEL_111 ((volatile uint32_t *)0xfe445de8)
#define P_WCH_CFG_CHANNEL_112 ((volatile uint32_t *)0xfe445e08)
#define P_WCH_CFG_CHANNEL_113 ((volatile uint32_t *)0xfe445e28)
#define P_WCH_CFG_CHANNEL_114 ((volatile uint32_t *)0xfe445e48)
#define P_WCH_CFG_CHANNEL_115 ((volatile uint32_t *)0xfe445e68)
#define P_WCH_CFG_CHANNEL_116 ((volatile uint32_t *)0xfe445e88)
#define P_WCH_CFG_CHANNEL_117 ((volatile uint32_t *)0xfe445ea8)
#define P_WCH_CFG_CHANNEL_118 ((volatile uint32_t *)0xfe445ec8)
#define P_WCH_CFG_CHANNEL_119 ((volatile uint32_t *)0xfe445ee8)
#define P_WCH_CFG_CHANNEL_120 ((volatile uint32_t *)0xfe445f08)
#define P_WCH_CFG_CHANNEL_121 ((volatile uint32_t *)0xfe445f28)
#define P_WCH_CFG_CHANNEL_122 ((volatile uint32_t *)0xfe445f48)
#define P_WCH_CFG_CHANNEL_123 ((volatile uint32_t *)0xfe445f68)
#define P_WCH_CFG_CHANNEL_124 ((volatile uint32_t *)0xfe445f88)
#define P_WCH_CFG_CHANNEL_125 ((volatile uint32_t *)0xfe445fa8)
#define P_WCH_CFG_CHANNEL_126 ((volatile uint32_t *)0xfe445fc8)
#define P_WCH_CFG_CHANNEL_127 ((volatile uint32_t *)0xfe445fe8)
#define P_WCH_ADDR_CHANNEL_0 ((volatile uint32_t *)0xfe44500c)
#define P_WCH_ADDR_CHANNEL_1 ((volatile uint32_t *)0xfe44502c)
#define P_WCH_ADDR_CHANNEL_2 ((volatile uint32_t *)0xfe44504c)
#define P_WCH_ADDR_CHANNEL_3 ((volatile uint32_t *)0xfe44506c)
#define P_WCH_ADDR_CHANNEL_4 ((volatile uint32_t *)0xfe44508c)
#define P_WCH_ADDR_CHANNEL_5 ((volatile uint32_t *)0xfe4450ac)
#define P_WCH_ADDR_CHANNEL_6 ((volatile uint32_t *)0xfe4450cc)
#define P_WCH_ADDR_CHANNEL_7 ((volatile uint32_t *)0xfe4450ec)
#define P_WCH_ADDR_CHANNEL_8 ((volatile uint32_t *)0xfe44510c)
#define P_WCH_ADDR_CHANNEL_9 ((volatile uint32_t *)0xfe44512c)
#define P_WCH_ADDR_CHANNEL_10 ((volatile uint32_t *)0xfe44514c)
#define P_WCH_ADDR_CHANNEL_11 ((volatile uint32_t *)0xfe44516c)
#define P_WCH_ADDR_CHANNEL_12 ((volatile uint32_t *)0xfe44518c)
#define P_WCH_ADDR_CHANNEL_13 ((volatile uint32_t *)0xfe4451ac)
#define P_WCH_ADDR_CHANNEL_14 ((volatile uint32_t *)0xfe4451cc)
#define P_WCH_ADDR_CHANNEL_15 ((volatile uint32_t *)0xfe4451ec)
#define P_WCH_ADDR_CHANNEL_16 ((volatile uint32_t *)0xfe44520c)
#define P_WCH_ADDR_CHANNEL_17 ((volatile uint32_t *)0xfe44522c)
#define P_WCH_ADDR_CHANNEL_18 ((volatile uint32_t *)0xfe44524c)
#define P_WCH_ADDR_CHANNEL_19 ((volatile uint32_t *)0xfe44526c)
#define P_WCH_ADDR_CHANNEL_20 ((volatile uint32_t *)0xfe44528c)
#define P_WCH_ADDR_CHANNEL_21 ((volatile uint32_t *)0xfe4452ac)
#define P_WCH_ADDR_CHANNEL_22 ((volatile uint32_t *)0xfe4452cc)
#define P_WCH_ADDR_CHANNEL_23 ((volatile uint32_t *)0xfe4452ec)
#define P_WCH_ADDR_CHANNEL_24 ((volatile uint32_t *)0xfe44530c)
#define P_WCH_ADDR_CHANNEL_25 ((volatile uint32_t *)0xfe44532c)
#define P_WCH_ADDR_CHANNEL_26 ((volatile uint32_t *)0xfe44534c)
#define P_WCH_ADDR_CHANNEL_27 ((volatile uint32_t *)0xfe44536c)
#define P_WCH_ADDR_CHANNEL_28 ((volatile uint32_t *)0xfe44538c)
#define P_WCH_ADDR_CHANNEL_29 ((volatile uint32_t *)0xfe4453ac)
#define P_WCH_ADDR_CHANNEL_30 ((volatile uint32_t *)0xfe4453cc)
#define P_WCH_ADDR_CHANNEL_31 ((volatile uint32_t *)0xfe4453ec)
#define P_WCH_ADDR_CHANNEL_32 ((volatile uint32_t *)0xfe44540c)
#define P_WCH_ADDR_CHANNEL_33 ((volatile uint32_t *)0xfe44542c)
#define P_WCH_ADDR_CHANNEL_34 ((volatile uint32_t *)0xfe44544c)
#define P_WCH_ADDR_CHANNEL_35 ((volatile uint32_t *)0xfe44546c)
#define P_WCH_ADDR_CHANNEL_36 ((volatile uint32_t *)0xfe44548c)
#define P_WCH_ADDR_CHANNEL_37 ((volatile uint32_t *)0xfe4454ac)
#define P_WCH_ADDR_CHANNEL_38 ((volatile uint32_t *)0xfe4454cc)
#define P_WCH_ADDR_CHANNEL_39 ((volatile uint32_t *)0xfe4454ec)
#define P_WCH_ADDR_CHANNEL_40 ((volatile uint32_t *)0xfe44550c)
#define P_WCH_ADDR_CHANNEL_41 ((volatile uint32_t *)0xfe44552c)
#define P_WCH_ADDR_CHANNEL_42 ((volatile uint32_t *)0xfe44554c)
#define P_WCH_ADDR_CHANNEL_43 ((volatile uint32_t *)0xfe44556c)
#define P_WCH_ADDR_CHANNEL_44 ((volatile uint32_t *)0xfe44558c)
#define P_WCH_ADDR_CHANNEL_45 ((volatile uint32_t *)0xfe4455ac)
#define P_WCH_ADDR_CHANNEL_46 ((volatile uint32_t *)0xfe4455cc)
#define P_WCH_ADDR_CHANNEL_47 ((volatile uint32_t *)0xfe4455ec)
#define P_WCH_ADDR_CHANNEL_48 ((volatile uint32_t *)0xfe44560c)
#define P_WCH_ADDR_CHANNEL_49 ((volatile uint32_t *)0xfe44562c)
#define P_WCH_ADDR_CHANNEL_50 ((volatile uint32_t *)0xfe44564c)
#define P_WCH_ADDR_CHANNEL_51 ((volatile uint32_t *)0xfe44566c)
#define P_WCH_ADDR_CHANNEL_52 ((volatile uint32_t *)0xfe44568c)
#define P_WCH_ADDR_CHANNEL_53 ((volatile uint32_t *)0xfe4456ac)
#define P_WCH_ADDR_CHANNEL_54 ((volatile uint32_t *)0xfe4456cc)
#define P_WCH_ADDR_CHANNEL_55 ((volatile uint32_t *)0xfe4456ec)
#define P_WCH_ADDR_CHANNEL_56 ((volatile uint32_t *)0xfe44570c)
#define P_WCH_ADDR_CHANNEL_57 ((volatile uint32_t *)0xfe44572c)
#define P_WCH_ADDR_CHANNEL_58 ((volatile uint32_t *)0xfe44574c)
#define P_WCH_ADDR_CHANNEL_59 ((volatile uint32_t *)0xfe44576c)
#define P_WCH_ADDR_CHANNEL_60 ((volatile uint32_t *)0xfe44578c)
#define P_WCH_ADDR_CHANNEL_61 ((volatile uint32_t *)0xfe4457ac)
#define P_WCH_ADDR_CHANNEL_62 ((volatile uint32_t *)0xfe4457cc)
#define P_WCH_ADDR_CHANNEL_63 ((volatile uint32_t *)0xfe4457ec)
#define P_WCH_ADDR_CHANNEL_64 ((volatile uint32_t *)0xfe44580c)
#define P_WCH_ADDR_CHANNEL_65 ((volatile uint32_t *)0xfe44582c)
#define P_WCH_ADDR_CHANNEL_66 ((volatile uint32_t *)0xfe44584c)
#define P_WCH_ADDR_CHANNEL_67 ((volatile uint32_t *)0xfe44586c)
#define P_WCH_ADDR_CHANNEL_68 ((volatile uint32_t *)0xfe44588c)
#define P_WCH_ADDR_CHANNEL_69 ((volatile uint32_t *)0xfe4458ac)
#define P_WCH_ADDR_CHANNEL_70 ((volatile uint32_t *)0xfe4458cc)
#define P_WCH_ADDR_CHANNEL_71 ((volatile uint32_t *)0xfe4458ec)
#define P_WCH_ADDR_CHANNEL_72 ((volatile uint32_t *)0xfe44590c)
#define P_WCH_ADDR_CHANNEL_73 ((volatile uint32_t *)0xfe44592c)
#define P_WCH_ADDR_CHANNEL_74 ((volatile uint32_t *)0xfe44594c)
#define P_WCH_ADDR_CHANNEL_75 ((volatile uint32_t *)0xfe44596c)
#define P_WCH_ADDR_CHANNEL_76 ((volatile uint32_t *)0xfe44598c)
#define P_WCH_ADDR_CHANNEL_77 ((volatile uint32_t *)0xfe4459ac)
#define P_WCH_ADDR_CHANNEL_78 ((volatile uint32_t *)0xfe4459cc)
#define P_WCH_ADDR_CHANNEL_79 ((volatile uint32_t *)0xfe4459ec)
#define P_WCH_ADDR_CHANNEL_80 ((volatile uint32_t *)0xfe445a0c)
#define P_WCH_ADDR_CHANNEL_81 ((volatile uint32_t *)0xfe445a2c)
#define P_WCH_ADDR_CHANNEL_82 ((volatile uint32_t *)0xfe445a4c)
#define P_WCH_ADDR_CHANNEL_83 ((volatile uint32_t *)0xfe445a6c)
#define P_WCH_ADDR_CHANNEL_84 ((volatile uint32_t *)0xfe445a8c)
#define P_WCH_ADDR_CHANNEL_85 ((volatile uint32_t *)0xfe445aac)
#define P_WCH_ADDR_CHANNEL_86 ((volatile uint32_t *)0xfe445acc)
#define P_WCH_ADDR_CHANNEL_87 ((volatile uint32_t *)0xfe445aec)
#define P_WCH_ADDR_CHANNEL_88 ((volatile uint32_t *)0xfe445b0c)
#define P_WCH_ADDR_CHANNEL_89 ((volatile uint32_t *)0xfe445b2c)
#define P_WCH_ADDR_CHANNEL_90 ((volatile uint32_t *)0xfe445b4c)
#define P_WCH_ADDR_CHANNEL_91 ((volatile uint32_t *)0xfe445b6c)
#define P_WCH_ADDR_CHANNEL_92 ((volatile uint32_t *)0xfe445b8c)
#define P_WCH_ADDR_CHANNEL_93 ((volatile uint32_t *)0xfe445bac)
#define P_WCH_ADDR_CHANNEL_94 ((volatile uint32_t *)0xfe445bcc)
#define P_WCH_ADDR_CHANNEL_95 ((volatile uint32_t *)0xfe445bec)
#define P_WCH_ADDR_CHANNEL_96 ((volatile uint32_t *)0xfe445c0c)
#define P_WCH_ADDR_CHANNEL_97 ((volatile uint32_t *)0xfe445c2c)
#define P_WCH_ADDR_CHANNEL_98 ((volatile uint32_t *)0xfe445c4c)
#define P_WCH_ADDR_CHANNEL_99 ((volatile uint32_t *)0xfe445c6c)
#define P_WCH_ADDR_CHANNEL_100 ((volatile uint32_t *)0xfe445c8c)
#define P_WCH_ADDR_CHANNEL_101 ((volatile uint32_t *)0xfe445cac)
#define P_WCH_ADDR_CHANNEL_102 ((volatile uint32_t *)0xfe445ccc)
#define P_WCH_ADDR_CHANNEL_103 ((volatile uint32_t *)0xfe445cec)
#define P_WCH_ADDR_CHANNEL_104 ((volatile uint32_t *)0xfe445d0c)
#define P_WCH_ADDR_CHANNEL_105 ((volatile uint32_t *)0xfe445d2c)
#define P_WCH_ADDR_CHANNEL_106 ((volatile uint32_t *)0xfe445d4c)
#define P_WCH_ADDR_CHANNEL_107 ((volatile uint32_t *)0xfe445d6c)
#define P_WCH_ADDR_CHANNEL_108 ((volatile uint32_t *)0xfe445d8c)
#define P_WCH_ADDR_CHANNEL_109 ((volatile uint32_t *)0xfe445dac)
#define P_WCH_ADDR_CHANNEL_110 ((volatile uint32_t *)0xfe445dcc)
#define P_WCH_ADDR_CHANNEL_111 ((volatile uint32_t *)0xfe445dec)
#define P_WCH_ADDR_CHANNEL_112 ((volatile uint32_t *)0xfe445e0c)
#define P_WCH_ADDR_CHANNEL_113 ((volatile uint32_t *)0xfe445e2c)
#define P_WCH_ADDR_CHANNEL_114 ((volatile uint32_t *)0xfe445e4c)
#define P_WCH_ADDR_CHANNEL_115 ((volatile uint32_t *)0xfe445e6c)
#define P_WCH_ADDR_CHANNEL_116 ((volatile uint32_t *)0xfe445e8c)
#define P_WCH_ADDR_CHANNEL_117 ((volatile uint32_t *)0xfe445eac)
#define P_WCH_ADDR_CHANNEL_118 ((volatile uint32_t *)0xfe445ecc)
#define P_WCH_ADDR_CHANNEL_119 ((volatile uint32_t *)0xfe445eec)
#define P_WCH_ADDR_CHANNEL_120 ((volatile uint32_t *)0xfe445f0c)
#define P_WCH_ADDR_CHANNEL_121 ((volatile uint32_t *)0xfe445f2c)
#define P_WCH_ADDR_CHANNEL_122 ((volatile uint32_t *)0xfe445f4c)
#define P_WCH_ADDR_CHANNEL_123 ((volatile uint32_t *)0xfe445f6c)
#define P_WCH_ADDR_CHANNEL_124 ((volatile uint32_t *)0xfe445f8c)
#define P_WCH_ADDR_CHANNEL_125 ((volatile uint32_t *)0xfe445fac)
#define P_WCH_ADDR_CHANNEL_126 ((volatile uint32_t *)0xfe445fcc)
#define P_WCH_ADDR_CHANNEL_127 ((volatile uint32_t *)0xfe445fec)
#define P_WCH_LEN_CHANNEL_0 ((volatile uint32_t *)0xfe445010)
#define P_WCH_LEN_CHANNEL_1 ((volatile uint32_t *)0xfe445030)
#define P_WCH_LEN_CHANNEL_2 ((volatile uint32_t *)0xfe445050)
#define P_WCH_LEN_CHANNEL_3 ((volatile uint32_t *)0xfe445070)
#define P_WCH_LEN_CHANNEL_4 ((volatile uint32_t *)0xfe445090)
#define P_WCH_LEN_CHANNEL_5 ((volatile uint32_t *)0xfe4450b0)
#define P_WCH_LEN_CHANNEL_6 ((volatile uint32_t *)0xfe4450d0)
#define P_WCH_LEN_CHANNEL_7 ((volatile uint32_t *)0xfe4450f0)
#define P_WCH_LEN_CHANNEL_8 ((volatile uint32_t *)0xfe445110)
#define P_WCH_LEN_CHANNEL_9 ((volatile uint32_t *)0xfe445130)
#define P_WCH_LEN_CHANNEL_10 ((volatile uint32_t *)0xfe445150)
#define P_WCH_LEN_CHANNEL_11 ((volatile uint32_t *)0xfe445170)
#define P_WCH_LEN_CHANNEL_12 ((volatile uint32_t *)0xfe445190)
#define P_WCH_LEN_CHANNEL_13 ((volatile uint32_t *)0xfe4451b0)
#define P_WCH_LEN_CHANNEL_14 ((volatile uint32_t *)0xfe4451d0)
#define P_WCH_LEN_CHANNEL_15 ((volatile uint32_t *)0xfe4451f0)
#define P_WCH_LEN_CHANNEL_16 ((volatile uint32_t *)0xfe445210)
#define P_WCH_LEN_CHANNEL_17 ((volatile uint32_t *)0xfe445230)
#define P_WCH_LEN_CHANNEL_18 ((volatile uint32_t *)0xfe445250)
#define P_WCH_LEN_CHANNEL_19 ((volatile uint32_t *)0xfe445270)
#define P_WCH_LEN_CHANNEL_20 ((volatile uint32_t *)0xfe445290)
#define P_WCH_LEN_CHANNEL_21 ((volatile uint32_t *)0xfe4452b0)
#define P_WCH_LEN_CHANNEL_22 ((volatile uint32_t *)0xfe4452d0)
#define P_WCH_LEN_CHANNEL_23 ((volatile uint32_t *)0xfe4452f0)
#define P_WCH_LEN_CHANNEL_24 ((volatile uint32_t *)0xfe445310)
#define P_WCH_LEN_CHANNEL_25 ((volatile uint32_t *)0xfe445330)
#define P_WCH_LEN_CHANNEL_26 ((volatile uint32_t *)0xfe445350)
#define P_WCH_LEN_CHANNEL_27 ((volatile uint32_t *)0xfe445370)
#define P_WCH_LEN_CHANNEL_28 ((volatile uint32_t *)0xfe445390)
#define P_WCH_LEN_CHANNEL_29 ((volatile uint32_t *)0xfe4453b0)
#define P_WCH_LEN_CHANNEL_30 ((volatile uint32_t *)0xfe4453d0)
#define P_WCH_LEN_CHANNEL_31 ((volatile uint32_t *)0xfe4453f0)
#define P_WCH_LEN_CHANNEL_32 ((volatile uint32_t *)0xfe445410)
#define P_WCH_LEN_CHANNEL_33 ((volatile uint32_t *)0xfe445430)
#define P_WCH_LEN_CHANNEL_34 ((volatile uint32_t *)0xfe445450)
#define P_WCH_LEN_CHANNEL_35 ((volatile uint32_t *)0xfe445470)
#define P_WCH_LEN_CHANNEL_36 ((volatile uint32_t *)0xfe445490)
#define P_WCH_LEN_CHANNEL_37 ((volatile uint32_t *)0xfe4454b0)
#define P_WCH_LEN_CHANNEL_38 ((volatile uint32_t *)0xfe4454d0)
#define P_WCH_LEN_CHANNEL_39 ((volatile uint32_t *)0xfe4454f0)
#define P_WCH_LEN_CHANNEL_40 ((volatile uint32_t *)0xfe445510)
#define P_WCH_LEN_CHANNEL_41 ((volatile uint32_t *)0xfe445530)
#define P_WCH_LEN_CHANNEL_42 ((volatile uint32_t *)0xfe445550)
#define P_WCH_LEN_CHANNEL_43 ((volatile uint32_t *)0xfe445570)
#define P_WCH_LEN_CHANNEL_44 ((volatile uint32_t *)0xfe445590)
#define P_WCH_LEN_CHANNEL_45 ((volatile uint32_t *)0xfe4455b0)
#define P_WCH_LEN_CHANNEL_46 ((volatile uint32_t *)0xfe4455d0)
#define P_WCH_LEN_CHANNEL_47 ((volatile uint32_t *)0xfe4455f0)
#define P_WCH_LEN_CHANNEL_48 ((volatile uint32_t *)0xfe445610)
#define P_WCH_LEN_CHANNEL_49 ((volatile uint32_t *)0xfe445630)
#define P_WCH_LEN_CHANNEL_50 ((volatile uint32_t *)0xfe445650)
#define P_WCH_LEN_CHANNEL_51 ((volatile uint32_t *)0xfe445670)
#define P_WCH_LEN_CHANNEL_52 ((volatile uint32_t *)0xfe445690)
#define P_WCH_LEN_CHANNEL_53 ((volatile uint32_t *)0xfe4456b0)
#define P_WCH_LEN_CHANNEL_54 ((volatile uint32_t *)0xfe4456d0)
#define P_WCH_LEN_CHANNEL_55 ((volatile uint32_t *)0xfe4456f0)
#define P_WCH_LEN_CHANNEL_56 ((volatile uint32_t *)0xfe445710)
#define P_WCH_LEN_CHANNEL_57 ((volatile uint32_t *)0xfe445730)
#define P_WCH_LEN_CHANNEL_58 ((volatile uint32_t *)0xfe445750)
#define P_WCH_LEN_CHANNEL_59 ((volatile uint32_t *)0xfe445770)
#define P_WCH_LEN_CHANNEL_60 ((volatile uint32_t *)0xfe445790)
#define P_WCH_LEN_CHANNEL_61 ((volatile uint32_t *)0xfe4457b0)
#define P_WCH_LEN_CHANNEL_62 ((volatile uint32_t *)0xfe4457d0)
#define P_WCH_LEN_CHANNEL_63 ((volatile uint32_t *)0xfe4457f0)
#define P_WCH_LEN_CHANNEL_64 ((volatile uint32_t *)0xfe445810)
#define P_WCH_LEN_CHANNEL_65 ((volatile uint32_t *)0xfe445830)
#define P_WCH_LEN_CHANNEL_66 ((volatile uint32_t *)0xfe445850)
#define P_WCH_LEN_CHANNEL_67 ((volatile uint32_t *)0xfe445870)
#define P_WCH_LEN_CHANNEL_68 ((volatile uint32_t *)0xfe445890)
#define P_WCH_LEN_CHANNEL_69 ((volatile uint32_t *)0xfe4458b0)
#define P_WCH_LEN_CHANNEL_70 ((volatile uint32_t *)0xfe4458d0)
#define P_WCH_LEN_CHANNEL_71 ((volatile uint32_t *)0xfe4458f0)
#define P_WCH_LEN_CHANNEL_72 ((volatile uint32_t *)0xfe445910)
#define P_WCH_LEN_CHANNEL_73 ((volatile uint32_t *)0xfe445930)
#define P_WCH_LEN_CHANNEL_74 ((volatile uint32_t *)0xfe445950)
#define P_WCH_LEN_CHANNEL_75 ((volatile uint32_t *)0xfe445970)
#define P_WCH_LEN_CHANNEL_76 ((volatile uint32_t *)0xfe445990)
#define P_WCH_LEN_CHANNEL_77 ((volatile uint32_t *)0xfe4459b0)
#define P_WCH_LEN_CHANNEL_78 ((volatile uint32_t *)0xfe4459d0)
#define P_WCH_LEN_CHANNEL_79 ((volatile uint32_t *)0xfe4459f0)
#define P_WCH_LEN_CHANNEL_80 ((volatile uint32_t *)0xfe445a10)
#define P_WCH_LEN_CHANNEL_81 ((volatile uint32_t *)0xfe445a30)
#define P_WCH_LEN_CHANNEL_82 ((volatile uint32_t *)0xfe445a50)
#define P_WCH_LEN_CHANNEL_83 ((volatile uint32_t *)0xfe445a70)
#define P_WCH_LEN_CHANNEL_84 ((volatile uint32_t *)0xfe445a90)
#define P_WCH_LEN_CHANNEL_85 ((volatile uint32_t *)0xfe445ab0)
#define P_WCH_LEN_CHANNEL_86 ((volatile uint32_t *)0xfe445ad0)
#define P_WCH_LEN_CHANNEL_87 ((volatile uint32_t *)0xfe445af0)
#define P_WCH_LEN_CHANNEL_88 ((volatile uint32_t *)0xfe445b10)
#define P_WCH_LEN_CHANNEL_89 ((volatile uint32_t *)0xfe445b30)
#define P_WCH_LEN_CHANNEL_90 ((volatile uint32_t *)0xfe445b50)
#define P_WCH_LEN_CHANNEL_91 ((volatile uint32_t *)0xfe445b70)
#define P_WCH_LEN_CHANNEL_92 ((volatile uint32_t *)0xfe445b90)
#define P_WCH_LEN_CHANNEL_93 ((volatile uint32_t *)0xfe445bb0)
#define P_WCH_LEN_CHANNEL_94 ((volatile uint32_t *)0xfe445bd0)
#define P_WCH_LEN_CHANNEL_95 ((volatile uint32_t *)0xfe445bf0)
#define P_WCH_LEN_CHANNEL_96 ((volatile uint32_t *)0xfe445c10)
#define P_WCH_LEN_CHANNEL_97 ((volatile uint32_t *)0xfe445c30)
#define P_WCH_LEN_CHANNEL_98 ((volatile uint32_t *)0xfe445c50)
#define P_WCH_LEN_CHANNEL_99 ((volatile uint32_t *)0xfe445c70)
#define P_WCH_LEN_CHANNEL_100 ((volatile uint32_t *)0xfe445c90)
#define P_WCH_LEN_CHANNEL_101 ((volatile uint32_t *)0xfe445cb0)
#define P_WCH_LEN_CHANNEL_102 ((volatile uint32_t *)0xfe445cd0)
#define P_WCH_LEN_CHANNEL_103 ((volatile uint32_t *)0xfe445cf0)
#define P_WCH_LEN_CHANNEL_104 ((volatile uint32_t *)0xfe445d10)
#define P_WCH_LEN_CHANNEL_105 ((volatile uint32_t *)0xfe445d30)
#define P_WCH_LEN_CHANNEL_106 ((volatile uint32_t *)0xfe445d50)
#define P_WCH_LEN_CHANNEL_107 ((volatile uint32_t *)0xfe445d70)
#define P_WCH_LEN_CHANNEL_108 ((volatile uint32_t *)0xfe445d90)
#define P_WCH_LEN_CHANNEL_109 ((volatile uint32_t *)0xfe445db0)
#define P_WCH_LEN_CHANNEL_110 ((volatile uint32_t *)0xfe445dd0)
#define P_WCH_LEN_CHANNEL_111 ((volatile uint32_t *)0xfe445df0)
#define P_WCH_LEN_CHANNEL_112 ((volatile uint32_t *)0xfe445e10)
#define P_WCH_LEN_CHANNEL_113 ((volatile uint32_t *)0xfe445e30)
#define P_WCH_LEN_CHANNEL_114 ((volatile uint32_t *)0xfe445e50)
#define P_WCH_LEN_CHANNEL_115 ((volatile uint32_t *)0xfe445e70)
#define P_WCH_LEN_CHANNEL_116 ((volatile uint32_t *)0xfe445e90)
#define P_WCH_LEN_CHANNEL_117 ((volatile uint32_t *)0xfe445eb0)
#define P_WCH_LEN_CHANNEL_118 ((volatile uint32_t *)0xfe445ed0)
#define P_WCH_LEN_CHANNEL_119 ((volatile uint32_t *)0xfe445ef0)
#define P_WCH_LEN_CHANNEL_120 ((volatile uint32_t *)0xfe445f10)
#define P_WCH_LEN_CHANNEL_121 ((volatile uint32_t *)0xfe445f30)
#define P_WCH_LEN_CHANNEL_122 ((volatile uint32_t *)0xfe445f50)
#define P_WCH_LEN_CHANNEL_123 ((volatile uint32_t *)0xfe445f70)
#define P_WCH_LEN_CHANNEL_124 ((volatile uint32_t *)0xfe445f90)
#define P_WCH_LEN_CHANNEL_125 ((volatile uint32_t *)0xfe445fb0)
#define P_WCH_LEN_CHANNEL_126 ((volatile uint32_t *)0xfe445fd0)
#define P_WCH_LEN_CHANNEL_127 ((volatile uint32_t *)0xfe445ff0)
#define P_WCH_WR_LEN_CHANNEL_0 ((volatile uint32_t *)0xfe445014)
#define P_WCH_WR_LEN_CHANNEL_1 ((volatile uint32_t *)0xfe445034)
#define P_WCH_WR_LEN_CHANNEL_2 ((volatile uint32_t *)0xfe445054)
#define P_WCH_WR_LEN_CHANNEL_3 ((volatile uint32_t *)0xfe445074)
#define P_WCH_WR_LEN_CHANNEL_4 ((volatile uint32_t *)0xfe445094)
#define P_WCH_WR_LEN_CHANNEL_5 ((volatile uint32_t *)0xfe4450b4)
#define P_WCH_WR_LEN_CHANNEL_6 ((volatile uint32_t *)0xfe4450d4)
#define P_WCH_WR_LEN_CHANNEL_7 ((volatile uint32_t *)0xfe4450f4)
#define P_WCH_WR_LEN_CHANNEL_8 ((volatile uint32_t *)0xfe445114)
#define P_WCH_WR_LEN_CHANNEL_9 ((volatile uint32_t *)0xfe445134)
#define P_WCH_WR_LEN_CHANNEL_10 ((volatile uint32_t *)0xfe445154)
#define P_WCH_WR_LEN_CHANNEL_11 ((volatile uint32_t *)0xfe445174)
#define P_WCH_WR_LEN_CHANNEL_12 ((volatile uint32_t *)0xfe445194)
#define P_WCH_WR_LEN_CHANNEL_13 ((volatile uint32_t *)0xfe4451b4)
#define P_WCH_WR_LEN_CHANNEL_14 ((volatile uint32_t *)0xfe4451d4)
#define P_WCH_WR_LEN_CHANNEL_15 ((volatile uint32_t *)0xfe4451f4)
#define P_WCH_WR_LEN_CHANNEL_16 ((volatile uint32_t *)0xfe445214)
#define P_WCH_WR_LEN_CHANNEL_17 ((volatile uint32_t *)0xfe445234)
#define P_WCH_WR_LEN_CHANNEL_18 ((volatile uint32_t *)0xfe445254)
#define P_WCH_WR_LEN_CHANNEL_19 ((volatile uint32_t *)0xfe445274)
#define P_WCH_WR_LEN_CHANNEL_20 ((volatile uint32_t *)0xfe445294)
#define P_WCH_WR_LEN_CHANNEL_21 ((volatile uint32_t *)0xfe4452b4)
#define P_WCH_WR_LEN_CHANNEL_22 ((volatile uint32_t *)0xfe4452d4)
#define P_WCH_WR_LEN_CHANNEL_23 ((volatile uint32_t *)0xfe4452f4)
#define P_WCH_WR_LEN_CHANNEL_24 ((volatile uint32_t *)0xfe445314)
#define P_WCH_WR_LEN_CHANNEL_25 ((volatile uint32_t *)0xfe445334)
#define P_WCH_WR_LEN_CHANNEL_26 ((volatile uint32_t *)0xfe445354)
#define P_WCH_WR_LEN_CHANNEL_27 ((volatile uint32_t *)0xfe445374)
#define P_WCH_WR_LEN_CHANNEL_28 ((volatile uint32_t *)0xfe445394)
#define P_WCH_WR_LEN_CHANNEL_29 ((volatile uint32_t *)0xfe4453b4)
#define P_WCH_WR_LEN_CHANNEL_30 ((volatile uint32_t *)0xfe4453d4)
#define P_WCH_WR_LEN_CHANNEL_31 ((volatile uint32_t *)0xfe4453f4)
#define P_WCH_WR_LEN_CHANNEL_32 ((volatile uint32_t *)0xfe445414)
#define P_WCH_WR_LEN_CHANNEL_33 ((volatile uint32_t *)0xfe445434)
#define P_WCH_WR_LEN_CHANNEL_34 ((volatile uint32_t *)0xfe445454)
#define P_WCH_WR_LEN_CHANNEL_35 ((volatile uint32_t *)0xfe445474)
#define P_WCH_WR_LEN_CHANNEL_36 ((volatile uint32_t *)0xfe445494)
#define P_WCH_WR_LEN_CHANNEL_37 ((volatile uint32_t *)0xfe4454b4)
#define P_WCH_WR_LEN_CHANNEL_38 ((volatile uint32_t *)0xfe4454d4)
#define P_WCH_WR_LEN_CHANNEL_39 ((volatile uint32_t *)0xfe4454f4)
#define P_WCH_WR_LEN_CHANNEL_40 ((volatile uint32_t *)0xfe445514)
#define P_WCH_WR_LEN_CHANNEL_41 ((volatile uint32_t *)0xfe445534)
#define P_WCH_WR_LEN_CHANNEL_42 ((volatile uint32_t *)0xfe445554)
#define P_WCH_WR_LEN_CHANNEL_43 ((volatile uint32_t *)0xfe445574)
#define P_WCH_WR_LEN_CHANNEL_44 ((volatile uint32_t *)0xfe445594)
#define P_WCH_WR_LEN_CHANNEL_45 ((volatile uint32_t *)0xfe4455b4)
#define P_WCH_WR_LEN_CHANNEL_46 ((volatile uint32_t *)0xfe4455d4)
#define P_WCH_WR_LEN_CHANNEL_47 ((volatile uint32_t *)0xfe4455f4)
#define P_WCH_WR_LEN_CHANNEL_48 ((volatile uint32_t *)0xfe445614)
#define P_WCH_WR_LEN_CHANNEL_49 ((volatile uint32_t *)0xfe445634)
#define P_WCH_WR_LEN_CHANNEL_50 ((volatile uint32_t *)0xfe445654)
#define P_WCH_WR_LEN_CHANNEL_51 ((volatile uint32_t *)0xfe445674)
#define P_WCH_WR_LEN_CHANNEL_52 ((volatile uint32_t *)0xfe445694)
#define P_WCH_WR_LEN_CHANNEL_53 ((volatile uint32_t *)0xfe4456b4)
#define P_WCH_WR_LEN_CHANNEL_54 ((volatile uint32_t *)0xfe4456d4)
#define P_WCH_WR_LEN_CHANNEL_55 ((volatile uint32_t *)0xfe4456f4)
#define P_WCH_WR_LEN_CHANNEL_56 ((volatile uint32_t *)0xfe445714)
#define P_WCH_WR_LEN_CHANNEL_57 ((volatile uint32_t *)0xfe445734)
#define P_WCH_WR_LEN_CHANNEL_58 ((volatile uint32_t *)0xfe445754)
#define P_WCH_WR_LEN_CHANNEL_59 ((volatile uint32_t *)0xfe445774)
#define P_WCH_WR_LEN_CHANNEL_60 ((volatile uint32_t *)0xfe445794)
#define P_WCH_WR_LEN_CHANNEL_61 ((volatile uint32_t *)0xfe4457b4)
#define P_WCH_WR_LEN_CHANNEL_62 ((volatile uint32_t *)0xfe4457d4)
#define P_WCH_WR_LEN_CHANNEL_63 ((volatile uint32_t *)0xfe4457f4)
#define P_WCH_WR_LEN_CHANNEL_64 ((volatile uint32_t *)0xfe445814)
#define P_WCH_WR_LEN_CHANNEL_65 ((volatile uint32_t *)0xfe445834)
#define P_WCH_WR_LEN_CHANNEL_66 ((volatile uint32_t *)0xfe445854)
#define P_WCH_WR_LEN_CHANNEL_67 ((volatile uint32_t *)0xfe445874)
#define P_WCH_WR_LEN_CHANNEL_68 ((volatile uint32_t *)0xfe445894)
#define P_WCH_WR_LEN_CHANNEL_69 ((volatile uint32_t *)0xfe4458b4)
#define P_WCH_WR_LEN_CHANNEL_70 ((volatile uint32_t *)0xfe4458d4)
#define P_WCH_WR_LEN_CHANNEL_71 ((volatile uint32_t *)0xfe4458f4)
#define P_WCH_WR_LEN_CHANNEL_72 ((volatile uint32_t *)0xfe445914)
#define P_WCH_WR_LEN_CHANNEL_73 ((volatile uint32_t *)0xfe445934)
#define P_WCH_WR_LEN_CHANNEL_74 ((volatile uint32_t *)0xfe445954)
#define P_WCH_WR_LEN_CHANNEL_75 ((volatile uint32_t *)0xfe445974)
#define P_WCH_WR_LEN_CHANNEL_76 ((volatile uint32_t *)0xfe445994)
#define P_WCH_WR_LEN_CHANNEL_77 ((volatile uint32_t *)0xfe4459b4)
#define P_WCH_WR_LEN_CHANNEL_78 ((volatile uint32_t *)0xfe4459d4)
#define P_WCH_WR_LEN_CHANNEL_79 ((volatile uint32_t *)0xfe4459f4)
#define P_WCH_WR_LEN_CHANNEL_80 ((volatile uint32_t *)0xfe445a14)
#define P_WCH_WR_LEN_CHANNEL_81 ((volatile uint32_t *)0xfe445a34)
#define P_WCH_WR_LEN_CHANNEL_82 ((volatile uint32_t *)0xfe445a54)
#define P_WCH_WR_LEN_CHANNEL_83 ((volatile uint32_t *)0xfe445a74)
#define P_WCH_WR_LEN_CHANNEL_84 ((volatile uint32_t *)0xfe445a94)
#define P_WCH_WR_LEN_CHANNEL_85 ((volatile uint32_t *)0xfe445ab4)
#define P_WCH_WR_LEN_CHANNEL_86 ((volatile uint32_t *)0xfe445ad4)
#define P_WCH_WR_LEN_CHANNEL_87 ((volatile uint32_t *)0xfe445af4)
#define P_WCH_WR_LEN_CHANNEL_88 ((volatile uint32_t *)0xfe445b14)
#define P_WCH_WR_LEN_CHANNEL_89 ((volatile uint32_t *)0xfe445b34)
#define P_WCH_WR_LEN_CHANNEL_90 ((volatile uint32_t *)0xfe445b54)
#define P_WCH_WR_LEN_CHANNEL_91 ((volatile uint32_t *)0xfe445b74)
#define P_WCH_WR_LEN_CHANNEL_92 ((volatile uint32_t *)0xfe445b94)
#define P_WCH_WR_LEN_CHANNEL_93 ((volatile uint32_t *)0xfe445bb4)
#define P_WCH_WR_LEN_CHANNEL_94 ((volatile uint32_t *)0xfe445bd4)
#define P_WCH_WR_LEN_CHANNEL_95 ((volatile uint32_t *)0xfe445bf4)
#define P_WCH_WR_LEN_CHANNEL_96 ((volatile uint32_t *)0xfe445c14)
#define P_WCH_WR_LEN_CHANNEL_97 ((volatile uint32_t *)0xfe445c34)
#define P_WCH_WR_LEN_CHANNEL_98 ((volatile uint32_t *)0xfe445c54)
#define P_WCH_WR_LEN_CHANNEL_99 ((volatile uint32_t *)0xfe445c74)
#define P_WCH_WR_LEN_CHANNEL_100 ((volatile uint32_t *)0xfe445c94)
#define P_WCH_WR_LEN_CHANNEL_101 ((volatile uint32_t *)0xfe445cb4)
#define P_WCH_WR_LEN_CHANNEL_102 ((volatile uint32_t *)0xfe445cd4)
#define P_WCH_WR_LEN_CHANNEL_103 ((volatile uint32_t *)0xfe445cf4)
#define P_WCH_WR_LEN_CHANNEL_104 ((volatile uint32_t *)0xfe445d14)
#define P_WCH_WR_LEN_CHANNEL_105 ((volatile uint32_t *)0xfe445d34)
#define P_WCH_WR_LEN_CHANNEL_106 ((volatile uint32_t *)0xfe445d54)
#define P_WCH_WR_LEN_CHANNEL_107 ((volatile uint32_t *)0xfe445d74)
#define P_WCH_WR_LEN_CHANNEL_108 ((volatile uint32_t *)0xfe445d94)
#define P_WCH_WR_LEN_CHANNEL_109 ((volatile uint32_t *)0xfe445db4)
#define P_WCH_WR_LEN_CHANNEL_110 ((volatile uint32_t *)0xfe445dd4)
#define P_WCH_WR_LEN_CHANNEL_111 ((volatile uint32_t *)0xfe445df4)
#define P_WCH_WR_LEN_CHANNEL_112 ((volatile uint32_t *)0xfe445e14)
#define P_WCH_WR_LEN_CHANNEL_113 ((volatile uint32_t *)0xfe445e34)
#define P_WCH_WR_LEN_CHANNEL_114 ((volatile uint32_t *)0xfe445e54)
#define P_WCH_WR_LEN_CHANNEL_115 ((volatile uint32_t *)0xfe445e74)
#define P_WCH_WR_LEN_CHANNEL_116 ((volatile uint32_t *)0xfe445e94)
#define P_WCH_WR_LEN_CHANNEL_117 ((volatile uint32_t *)0xfe445eb4)
#define P_WCH_WR_LEN_CHANNEL_118 ((volatile uint32_t *)0xfe445ed4)
#define P_WCH_WR_LEN_CHANNEL_119 ((volatile uint32_t *)0xfe445ef4)
#define P_WCH_WR_LEN_CHANNEL_120 ((volatile uint32_t *)0xfe445f14)
#define P_WCH_WR_LEN_CHANNEL_121 ((volatile uint32_t *)0xfe445f34)
#define P_WCH_WR_LEN_CHANNEL_122 ((volatile uint32_t *)0xfe445f54)
#define P_WCH_WR_LEN_CHANNEL_123 ((volatile uint32_t *)0xfe445f74)
#define P_WCH_WR_LEN_CHANNEL_124 ((volatile uint32_t *)0xfe445f94)
#define P_WCH_WR_LEN_CHANNEL_125 ((volatile uint32_t *)0xfe445fb4)
#define P_WCH_WR_LEN_CHANNEL_126 ((volatile uint32_t *)0xfe445fd4)
#define P_WCH_WR_LEN_CHANNEL_127 ((volatile uint32_t *)0xfe445ff4)
#define P_WCH_PTR_CHANNEL_0 ((volatile uint32_t *)0xfe445018)
#define P_WCH_PTR_CHANNEL_1 ((volatile uint32_t *)0xfe445038)
#define P_WCH_PTR_CHANNEL_2 ((volatile uint32_t *)0xfe445058)
#define P_WCH_PTR_CHANNEL_3 ((volatile uint32_t *)0xfe445078)
#define P_WCH_PTR_CHANNEL_4 ((volatile uint32_t *)0xfe445098)
#define P_WCH_PTR_CHANNEL_5 ((volatile uint32_t *)0xfe4450b8)
#define P_WCH_PTR_CHANNEL_6 ((volatile uint32_t *)0xfe4450d8)
#define P_WCH_PTR_CHANNEL_7 ((volatile uint32_t *)0xfe4450f8)
#define P_WCH_PTR_CHANNEL_8 ((volatile uint32_t *)0xfe445118)
#define P_WCH_PTR_CHANNEL_9 ((volatile uint32_t *)0xfe445138)
#define P_WCH_PTR_CHANNEL_10 ((volatile uint32_t *)0xfe445158)
#define P_WCH_PTR_CHANNEL_11 ((volatile uint32_t *)0xfe445178)
#define P_WCH_PTR_CHANNEL_12 ((volatile uint32_t *)0xfe445198)
#define P_WCH_PTR_CHANNEL_13 ((volatile uint32_t *)0xfe4451b8)
#define P_WCH_PTR_CHANNEL_14 ((volatile uint32_t *)0xfe4451d8)
#define P_WCH_PTR_CHANNEL_15 ((volatile uint32_t *)0xfe4451f8)
#define P_WCH_PTR_CHANNEL_16 ((volatile uint32_t *)0xfe445218)
#define P_WCH_PTR_CHANNEL_17 ((volatile uint32_t *)0xfe445238)
#define P_WCH_PTR_CHANNEL_18 ((volatile uint32_t *)0xfe445258)
#define P_WCH_PTR_CHANNEL_19 ((volatile uint32_t *)0xfe445278)
#define P_WCH_PTR_CHANNEL_20 ((volatile uint32_t *)0xfe445298)
#define P_WCH_PTR_CHANNEL_21 ((volatile uint32_t *)0xfe4452b8)
#define P_WCH_PTR_CHANNEL_22 ((volatile uint32_t *)0xfe4452d8)
#define P_WCH_PTR_CHANNEL_23 ((volatile uint32_t *)0xfe4452f8)
#define P_WCH_PTR_CHANNEL_24 ((volatile uint32_t *)0xfe445318)
#define P_WCH_PTR_CHANNEL_25 ((volatile uint32_t *)0xfe445338)
#define P_WCH_PTR_CHANNEL_26 ((volatile uint32_t *)0xfe445358)
#define P_WCH_PTR_CHANNEL_27 ((volatile uint32_t *)0xfe445378)
#define P_WCH_PTR_CHANNEL_28 ((volatile uint32_t *)0xfe445398)
#define P_WCH_PTR_CHANNEL_29 ((volatile uint32_t *)0xfe4453b8)
#define P_WCH_PTR_CHANNEL_30 ((volatile uint32_t *)0xfe4453d8)
#define P_WCH_PTR_CHANNEL_31 ((volatile uint32_t *)0xfe4453f8)
#define P_WCH_PTR_CHANNEL_32 ((volatile uint32_t *)0xfe445418)
#define P_WCH_PTR_CHANNEL_33 ((volatile uint32_t *)0xfe445438)
#define P_WCH_PTR_CHANNEL_34 ((volatile uint32_t *)0xfe445458)
#define P_WCH_PTR_CHANNEL_35 ((volatile uint32_t *)0xfe445478)
#define P_WCH_PTR_CHANNEL_36 ((volatile uint32_t *)0xfe445498)
#define P_WCH_PTR_CHANNEL_37 ((volatile uint32_t *)0xfe4454b8)
#define P_WCH_PTR_CHANNEL_38 ((volatile uint32_t *)0xfe4454d8)
#define P_WCH_PTR_CHANNEL_39 ((volatile uint32_t *)0xfe4454f8)
#define P_WCH_PTR_CHANNEL_40 ((volatile uint32_t *)0xfe445518)
#define P_WCH_PTR_CHANNEL_41 ((volatile uint32_t *)0xfe445538)
#define P_WCH_PTR_CHANNEL_42 ((volatile uint32_t *)0xfe445558)
#define P_WCH_PTR_CHANNEL_43 ((volatile uint32_t *)0xfe445578)
#define P_WCH_PTR_CHANNEL_44 ((volatile uint32_t *)0xfe445598)
#define P_WCH_PTR_CHANNEL_45 ((volatile uint32_t *)0xfe4455b8)
#define P_WCH_PTR_CHANNEL_46 ((volatile uint32_t *)0xfe4455d8)
#define P_WCH_PTR_CHANNEL_47 ((volatile uint32_t *)0xfe4455f8)
#define P_WCH_PTR_CHANNEL_48 ((volatile uint32_t *)0xfe445618)
#define P_WCH_PTR_CHANNEL_49 ((volatile uint32_t *)0xfe445638)
#define P_WCH_PTR_CHANNEL_50 ((volatile uint32_t *)0xfe445658)
#define P_WCH_PTR_CHANNEL_51 ((volatile uint32_t *)0xfe445678)
#define P_WCH_PTR_CHANNEL_52 ((volatile uint32_t *)0xfe445698)
#define P_WCH_PTR_CHANNEL_53 ((volatile uint32_t *)0xfe4456b8)
#define P_WCH_PTR_CHANNEL_54 ((volatile uint32_t *)0xfe4456d8)
#define P_WCH_PTR_CHANNEL_55 ((volatile uint32_t *)0xfe4456f8)
#define P_WCH_PTR_CHANNEL_56 ((volatile uint32_t *)0xfe445718)
#define P_WCH_PTR_CHANNEL_57 ((volatile uint32_t *)0xfe445738)
#define P_WCH_PTR_CHANNEL_58 ((volatile uint32_t *)0xfe445758)
#define P_WCH_PTR_CHANNEL_59 ((volatile uint32_t *)0xfe445778)
#define P_WCH_PTR_CHANNEL_60 ((volatile uint32_t *)0xfe445798)
#define P_WCH_PTR_CHANNEL_61 ((volatile uint32_t *)0xfe4457b8)
#define P_WCH_PTR_CHANNEL_62 ((volatile uint32_t *)0xfe4457d8)
#define P_WCH_PTR_CHANNEL_63 ((volatile uint32_t *)0xfe4457f8)
#define P_WCH_PTR_CHANNEL_64 ((volatile uint32_t *)0xfe445818)
#define P_WCH_PTR_CHANNEL_65 ((volatile uint32_t *)0xfe445838)
#define P_WCH_PTR_CHANNEL_66 ((volatile uint32_t *)0xfe445858)
#define P_WCH_PTR_CHANNEL_67 ((volatile uint32_t *)0xfe445878)
#define P_WCH_PTR_CHANNEL_68 ((volatile uint32_t *)0xfe445898)
#define P_WCH_PTR_CHANNEL_69 ((volatile uint32_t *)0xfe4458b8)
#define P_WCH_PTR_CHANNEL_70 ((volatile uint32_t *)0xfe4458d8)
#define P_WCH_PTR_CHANNEL_71 ((volatile uint32_t *)0xfe4458f8)
#define P_WCH_PTR_CHANNEL_72 ((volatile uint32_t *)0xfe445918)
#define P_WCH_PTR_CHANNEL_73 ((volatile uint32_t *)0xfe445938)
#define P_WCH_PTR_CHANNEL_74 ((volatile uint32_t *)0xfe445958)
#define P_WCH_PTR_CHANNEL_75 ((volatile uint32_t *)0xfe445978)
#define P_WCH_PTR_CHANNEL_76 ((volatile uint32_t *)0xfe445998)
#define P_WCH_PTR_CHANNEL_77 ((volatile uint32_t *)0xfe4459b8)
#define P_WCH_PTR_CHANNEL_78 ((volatile uint32_t *)0xfe4459d8)
#define P_WCH_PTR_CHANNEL_79 ((volatile uint32_t *)0xfe4459f8)
#define P_WCH_PTR_CHANNEL_80 ((volatile uint32_t *)0xfe445a18)
#define P_WCH_PTR_CHANNEL_81 ((volatile uint32_t *)0xfe445a38)
#define P_WCH_PTR_CHANNEL_82 ((volatile uint32_t *)0xfe445a58)
#define P_WCH_PTR_CHANNEL_83 ((volatile uint32_t *)0xfe445a78)
#define P_WCH_PTR_CHANNEL_84 ((volatile uint32_t *)0xfe445a98)
#define P_WCH_PTR_CHANNEL_85 ((volatile uint32_t *)0xfe445ab8)
#define P_WCH_PTR_CHANNEL_86 ((volatile uint32_t *)0xfe445ad8)
#define P_WCH_PTR_CHANNEL_87 ((volatile uint32_t *)0xfe445af8)
#define P_WCH_PTR_CHANNEL_88 ((volatile uint32_t *)0xfe445b18)
#define P_WCH_PTR_CHANNEL_89 ((volatile uint32_t *)0xfe445b38)
#define P_WCH_PTR_CHANNEL_90 ((volatile uint32_t *)0xfe445b58)
#define P_WCH_PTR_CHANNEL_91 ((volatile uint32_t *)0xfe445b78)
#define P_WCH_PTR_CHANNEL_92 ((volatile uint32_t *)0xfe445b98)
#define P_WCH_PTR_CHANNEL_93 ((volatile uint32_t *)0xfe445bb8)
#define P_WCH_PTR_CHANNEL_94 ((volatile uint32_t *)0xfe445bd8)
#define P_WCH_PTR_CHANNEL_95 ((volatile uint32_t *)0xfe445bf8)
#define P_WCH_PTR_CHANNEL_96 ((volatile uint32_t *)0xfe445c18)
#define P_WCH_PTR_CHANNEL_97 ((volatile uint32_t *)0xfe445c38)
#define P_WCH_PTR_CHANNEL_98 ((volatile uint32_t *)0xfe445c58)
#define P_WCH_PTR_CHANNEL_99 ((volatile uint32_t *)0xfe445c78)
#define P_WCH_PTR_CHANNEL_100 ((volatile uint32_t *)0xfe445c98)
#define P_WCH_PTR_CHANNEL_101 ((volatile uint32_t *)0xfe445cb8)
#define P_WCH_PTR_CHANNEL_102 ((volatile uint32_t *)0xfe445cd8)
#define P_WCH_PTR_CHANNEL_103 ((volatile uint32_t *)0xfe445cf8)
#define P_WCH_PTR_CHANNEL_104 ((volatile uint32_t *)0xfe445d18)
#define P_WCH_PTR_CHANNEL_105 ((volatile uint32_t *)0xfe445d38)
#define P_WCH_PTR_CHANNEL_106 ((volatile uint32_t *)0xfe445d58)
#define P_WCH_PTR_CHANNEL_107 ((volatile uint32_t *)0xfe445d78)
#define P_WCH_PTR_CHANNEL_108 ((volatile uint32_t *)0xfe445d98)
#define P_WCH_PTR_CHANNEL_109 ((volatile uint32_t *)0xfe445db8)
#define P_WCH_PTR_CHANNEL_110 ((volatile uint32_t *)0xfe445dd8)
#define P_WCH_PTR_CHANNEL_111 ((volatile uint32_t *)0xfe445df8)
#define P_WCH_PTR_CHANNEL_112 ((volatile uint32_t *)0xfe445e18)
#define P_WCH_PTR_CHANNEL_113 ((volatile uint32_t *)0xfe445e38)
#define P_WCH_PTR_CHANNEL_114 ((volatile uint32_t *)0xfe445e58)
#define P_WCH_PTR_CHANNEL_115 ((volatile uint32_t *)0xfe445e78)
#define P_WCH_PTR_CHANNEL_116 ((volatile uint32_t *)0xfe445e98)
#define P_WCH_PTR_CHANNEL_117 ((volatile uint32_t *)0xfe445eb8)
#define P_WCH_PTR_CHANNEL_118 ((volatile uint32_t *)0xfe445ed8)
#define P_WCH_PTR_CHANNEL_119 ((volatile uint32_t *)0xfe445ef8)
#define P_WCH_PTR_CHANNEL_120 ((volatile uint32_t *)0xfe445f18)
#define P_WCH_PTR_CHANNEL_121 ((volatile uint32_t *)0xfe445f38)
#define P_WCH_PTR_CHANNEL_122 ((volatile uint32_t *)0xfe445f58)
#define P_WCH_PTR_CHANNEL_123 ((volatile uint32_t *)0xfe445f78)
#define P_WCH_PTR_CHANNEL_124 ((volatile uint32_t *)0xfe445f98)
#define P_WCH_PTR_CHANNEL_125 ((volatile uint32_t *)0xfe445fb8)
#define P_WCH_PTR_CHANNEL_126 ((volatile uint32_t *)0xfe445fd8)
#define P_WCH_PTR_CHANNEL_127 ((volatile uint32_t *)0xfe445ff8)
#define P_WCMD_CNT_CHANNEL_0 ((volatile uint32_t *)0xfe44501c)
#define P_WCMD_CNT_CHANNEL_1 ((volatile uint32_t *)0xfe44503c)
#define P_WCMD_CNT_CHANNEL_2 ((volatile uint32_t *)0xfe44505c)
#define P_WCMD_CNT_CHANNEL_3 ((volatile uint32_t *)0xfe44507c)
#define P_WCMD_CNT_CHANNEL_4 ((volatile uint32_t *)0xfe44509c)
#define P_WCMD_CNT_CHANNEL_5 ((volatile uint32_t *)0xfe4450bc)
#define P_WCMD_CNT_CHANNEL_6 ((volatile uint32_t *)0xfe4450dc)
#define P_WCMD_CNT_CHANNEL_7 ((volatile uint32_t *)0xfe4450fc)
#define P_WCMD_CNT_CHANNEL_8 ((volatile uint32_t *)0xfe44511c)
#define P_WCMD_CNT_CHANNEL_9 ((volatile uint32_t *)0xfe44513c)
#define P_WCMD_CNT_CHANNEL_10 ((volatile uint32_t *)0xfe44515c)
#define P_WCMD_CNT_CHANNEL_11 ((volatile uint32_t *)0xfe44517c)
#define P_WCMD_CNT_CHANNEL_12 ((volatile uint32_t *)0xfe44519c)
#define P_WCMD_CNT_CHANNEL_13 ((volatile uint32_t *)0xfe4451bc)
#define P_WCMD_CNT_CHANNEL_14 ((volatile uint32_t *)0xfe4451dc)
#define P_WCMD_CNT_CHANNEL_15 ((volatile uint32_t *)0xfe4451fc)
#define P_WCMD_CNT_CHANNEL_16 ((volatile uint32_t *)0xfe44521c)
#define P_WCMD_CNT_CHANNEL_17 ((volatile uint32_t *)0xfe44523c)
#define P_WCMD_CNT_CHANNEL_18 ((volatile uint32_t *)0xfe44525c)
#define P_WCMD_CNT_CHANNEL_19 ((volatile uint32_t *)0xfe44527c)
#define P_WCMD_CNT_CHANNEL_20 ((volatile uint32_t *)0xfe44529c)
#define P_WCMD_CNT_CHANNEL_21 ((volatile uint32_t *)0xfe4452bc)
#define P_WCMD_CNT_CHANNEL_22 ((volatile uint32_t *)0xfe4452dc)
#define P_WCMD_CNT_CHANNEL_23 ((volatile uint32_t *)0xfe4452fc)
#define P_WCMD_CNT_CHANNEL_24 ((volatile uint32_t *)0xfe44531c)
#define P_WCMD_CNT_CHANNEL_25 ((volatile uint32_t *)0xfe44533c)
#define P_WCMD_CNT_CHANNEL_26 ((volatile uint32_t *)0xfe44535c)
#define P_WCMD_CNT_CHANNEL_27 ((volatile uint32_t *)0xfe44537c)
#define P_WCMD_CNT_CHANNEL_28 ((volatile uint32_t *)0xfe44539c)
#define P_WCMD_CNT_CHANNEL_29 ((volatile uint32_t *)0xfe4453bc)
#define P_WCMD_CNT_CHANNEL_30 ((volatile uint32_t *)0xfe4453dc)
#define P_WCMD_CNT_CHANNEL_31 ((volatile uint32_t *)0xfe4453fc)
#define P_WCMD_CNT_CHANNEL_32 ((volatile uint32_t *)0xfe44541c)
#define P_WCMD_CNT_CHANNEL_33 ((volatile uint32_t *)0xfe44543c)
#define P_WCMD_CNT_CHANNEL_34 ((volatile uint32_t *)0xfe44545c)
#define P_WCMD_CNT_CHANNEL_35 ((volatile uint32_t *)0xfe44547c)
#define P_WCMD_CNT_CHANNEL_36 ((volatile uint32_t *)0xfe44549c)
#define P_WCMD_CNT_CHANNEL_37 ((volatile uint32_t *)0xfe4454bc)
#define P_WCMD_CNT_CHANNEL_38 ((volatile uint32_t *)0xfe4454dc)
#define P_WCMD_CNT_CHANNEL_39 ((volatile uint32_t *)0xfe4454fc)
#define P_WCMD_CNT_CHANNEL_40 ((volatile uint32_t *)0xfe44551c)
#define P_WCMD_CNT_CHANNEL_41 ((volatile uint32_t *)0xfe44553c)
#define P_WCMD_CNT_CHANNEL_42 ((volatile uint32_t *)0xfe44555c)
#define P_WCMD_CNT_CHANNEL_43 ((volatile uint32_t *)0xfe44557c)
#define P_WCMD_CNT_CHANNEL_44 ((volatile uint32_t *)0xfe44559c)
#define P_WCMD_CNT_CHANNEL_45 ((volatile uint32_t *)0xfe4455bc)
#define P_WCMD_CNT_CHANNEL_46 ((volatile uint32_t *)0xfe4455dc)
#define P_WCMD_CNT_CHANNEL_47 ((volatile uint32_t *)0xfe4455fc)
#define P_WCMD_CNT_CHANNEL_48 ((volatile uint32_t *)0xfe44561c)
#define P_WCMD_CNT_CHANNEL_49 ((volatile uint32_t *)0xfe44563c)
#define P_WCMD_CNT_CHANNEL_50 ((volatile uint32_t *)0xfe44565c)
#define P_WCMD_CNT_CHANNEL_51 ((volatile uint32_t *)0xfe44567c)
#define P_WCMD_CNT_CHANNEL_52 ((volatile uint32_t *)0xfe44569c)
#define P_WCMD_CNT_CHANNEL_53 ((volatile uint32_t *)0xfe4456bc)
#define P_WCMD_CNT_CHANNEL_54 ((volatile uint32_t *)0xfe4456dc)
#define P_WCMD_CNT_CHANNEL_55 ((volatile uint32_t *)0xfe4456fc)
#define P_WCMD_CNT_CHANNEL_56 ((volatile uint32_t *)0xfe44571c)
#define P_WCMD_CNT_CHANNEL_57 ((volatile uint32_t *)0xfe44573c)
#define P_WCMD_CNT_CHANNEL_58 ((volatile uint32_t *)0xfe44575c)
#define P_WCMD_CNT_CHANNEL_59 ((volatile uint32_t *)0xfe44577c)
#define P_WCMD_CNT_CHANNEL_60 ((volatile uint32_t *)0xfe44579c)
#define P_WCMD_CNT_CHANNEL_61 ((volatile uint32_t *)0xfe4457bc)
#define P_WCMD_CNT_CHANNEL_62 ((volatile uint32_t *)0xfe4457dc)
#define P_WCMD_CNT_CHANNEL_63 ((volatile uint32_t *)0xfe4457fc)
#define P_WCMD_CNT_CHANNEL_64 ((volatile uint32_t *)0xfe44581c)
#define P_WCMD_CNT_CHANNEL_65 ((volatile uint32_t *)0xfe44583c)
#define P_WCMD_CNT_CHANNEL_66 ((volatile uint32_t *)0xfe44585c)
#define P_WCMD_CNT_CHANNEL_67 ((volatile uint32_t *)0xfe44587c)
#define P_WCMD_CNT_CHANNEL_68 ((volatile uint32_t *)0xfe44589c)
#define P_WCMD_CNT_CHANNEL_69 ((volatile uint32_t *)0xfe4458bc)
#define P_WCMD_CNT_CHANNEL_70 ((volatile uint32_t *)0xfe4458dc)
#define P_WCMD_CNT_CHANNEL_71 ((volatile uint32_t *)0xfe4458fc)
#define P_WCMD_CNT_CHANNEL_72 ((volatile uint32_t *)0xfe44591c)
#define P_WCMD_CNT_CHANNEL_73 ((volatile uint32_t *)0xfe44593c)
#define P_WCMD_CNT_CHANNEL_74 ((volatile uint32_t *)0xfe44595c)
#define P_WCMD_CNT_CHANNEL_75 ((volatile uint32_t *)0xfe44597c)
#define P_WCMD_CNT_CHANNEL_76 ((volatile uint32_t *)0xfe44599c)
#define P_WCMD_CNT_CHANNEL_77 ((volatile uint32_t *)0xfe4459bc)
#define P_WCMD_CNT_CHANNEL_78 ((volatile uint32_t *)0xfe4459dc)
#define P_WCMD_CNT_CHANNEL_79 ((volatile uint32_t *)0xfe4459fc)
#define P_WCMD_CNT_CHANNEL_80 ((volatile uint32_t *)0xfe445a1c)
#define P_WCMD_CNT_CHANNEL_81 ((volatile uint32_t *)0xfe445a3c)
#define P_WCMD_CNT_CHANNEL_82 ((volatile uint32_t *)0xfe445a5c)
#define P_WCMD_CNT_CHANNEL_83 ((volatile uint32_t *)0xfe445a7c)
#define P_WCMD_CNT_CHANNEL_84 ((volatile uint32_t *)0xfe445a9c)
#define P_WCMD_CNT_CHANNEL_85 ((volatile uint32_t *)0xfe445abc)
#define P_WCMD_CNT_CHANNEL_86 ((volatile uint32_t *)0xfe445adc)
#define P_WCMD_CNT_CHANNEL_87 ((volatile uint32_t *)0xfe445afc)
#define P_WCMD_CNT_CHANNEL_88 ((volatile uint32_t *)0xfe445b1c)
#define P_WCMD_CNT_CHANNEL_89 ((volatile uint32_t *)0xfe445b3c)
#define P_WCMD_CNT_CHANNEL_90 ((volatile uint32_t *)0xfe445b5c)
#define P_WCMD_CNT_CHANNEL_91 ((volatile uint32_t *)0xfe445b7c)
#define P_WCMD_CNT_CHANNEL_92 ((volatile uint32_t *)0xfe445b9c)
#define P_WCMD_CNT_CHANNEL_93 ((volatile uint32_t *)0xfe445bbc)
#define P_WCMD_CNT_CHANNEL_94 ((volatile uint32_t *)0xfe445bdc)
#define P_WCMD_CNT_CHANNEL_95 ((volatile uint32_t *)0xfe445bfc)
#define P_WCMD_CNT_CHANNEL_96 ((volatile uint32_t *)0xfe445c1c)
#define P_WCMD_CNT_CHANNEL_97 ((volatile uint32_t *)0xfe445c3c)
#define P_WCMD_CNT_CHANNEL_98 ((volatile uint32_t *)0xfe445c5c)
#define P_WCMD_CNT_CHANNEL_99 ((volatile uint32_t *)0xfe445c7c)
#define P_WCMD_CNT_CHANNEL_100 ((volatile uint32_t *)0xfe445c9c)
#define P_WCMD_CNT_CHANNEL_101 ((volatile uint32_t *)0xfe445cbc)
#define P_WCMD_CNT_CHANNEL_102 ((volatile uint32_t *)0xfe445cdc)
#define P_WCMD_CNT_CHANNEL_103 ((volatile uint32_t *)0xfe445cfc)
#define P_WCMD_CNT_CHANNEL_104 ((volatile uint32_t *)0xfe445d1c)
#define P_WCMD_CNT_CHANNEL_105 ((volatile uint32_t *)0xfe445d3c)
#define P_WCMD_CNT_CHANNEL_106 ((volatile uint32_t *)0xfe445d5c)
#define P_WCMD_CNT_CHANNEL_107 ((volatile uint32_t *)0xfe445d7c)
#define P_WCMD_CNT_CHANNEL_108 ((volatile uint32_t *)0xfe445d9c)
#define P_WCMD_CNT_CHANNEL_109 ((volatile uint32_t *)0xfe445dbc)
#define P_WCMD_CNT_CHANNEL_110 ((volatile uint32_t *)0xfe445ddc)
#define P_WCMD_CNT_CHANNEL_111 ((volatile uint32_t *)0xfe445dfc)
#define P_WCMD_CNT_CHANNEL_112 ((volatile uint32_t *)0xfe445e1c)
#define P_WCMD_CNT_CHANNEL_113 ((volatile uint32_t *)0xfe445e3c)
#define P_WCMD_CNT_CHANNEL_114 ((volatile uint32_t *)0xfe445e5c)
#define P_WCMD_CNT_CHANNEL_115 ((volatile uint32_t *)0xfe445e7c)
#define P_WCMD_CNT_CHANNEL_116 ((volatile uint32_t *)0xfe445e9c)
#define P_WCMD_CNT_CHANNEL_117 ((volatile uint32_t *)0xfe445ebc)
#define P_WCMD_CNT_CHANNEL_118 ((volatile uint32_t *)0xfe445edc)
#define P_WCMD_CNT_CHANNEL_119 ((volatile uint32_t *)0xfe445efc)
#define P_WCMD_CNT_CHANNEL_120 ((volatile uint32_t *)0xfe445f1c)
#define P_WCMD_CNT_CHANNEL_121 ((volatile uint32_t *)0xfe445f3c)
#define P_WCMD_CNT_CHANNEL_122 ((volatile uint32_t *)0xfe445f5c)
#define P_WCMD_CNT_CHANNEL_123 ((volatile uint32_t *)0xfe445f7c)
#define P_WCMD_CNT_CHANNEL_124 ((volatile uint32_t *)0xfe445f9c)
#define P_WCMD_CNT_CHANNEL_125 ((volatile uint32_t *)0xfe445fbc)
#define P_WCMD_CNT_CHANNEL_126 ((volatile uint32_t *)0xfe445fdc)
#define P_WCMD_CNT_CHANNEL_127 ((volatile uint32_t *)0xfe445ffc)
#define P_DMX_RDMA_INT_MASK ((volatile uint32_t *)0xfe446000)
#define P_DMX_WDMA_INT_MASK_0 ((volatile uint32_t *)0xfe446004)
#define P_DMX_WDMA_INT_MASK_1 ((volatile uint32_t *)0xfe446008)
#define P_DMX_WDMA_INT_MASK_2 ((volatile uint32_t *)0xfe44600c)
#define P_DMX_WDMA_INT_MASK_3 ((volatile uint32_t *)0xfe446010)
#define P_DMX_CLEAN_W_BATCH_0 ((volatile uint32_t *)0xfe446014)
#define P_DMX_CLEAN_W_BATCH_1 ((volatile uint32_t *)0xfe446018)
#define P_DMX_CLEAN_W_BATCH_2 ((volatile uint32_t *)0xfe44601c)
#define P_DMX_CLEAN_W_BATCH_3 ((volatile uint32_t *)0xfe446020)
#define P_DMX_CLEAN_RDMA ((volatile uint32_t *)0xfe446024)
#define P_DMX_CLEAN_WDMA_0 ((volatile uint32_t *)0xfe446028)
#define P_DMX_CLEAN_WDMA_1 ((volatile uint32_t *)0xfe44602c)
#define P_DMX_CLEAN_WDMA_2 ((volatile uint32_t *)0xfe446030)
#define P_DMX_CLEAN_WDMA_3 ((volatile uint32_t *)0xfe446034)
#define P_DMX_RDMA_ACTIVE ((volatile uint32_t *)0xfe446038)
#define P_DMX_WDMA_ACTIVE_0 ((volatile uint32_t *)0xfe44603c)
#define P_DMX_WDMA_ACTIVE_1 ((volatile uint32_t *)0xfe446040)
#define P_DMX_WDMA_ACTIVE_2 ((volatile uint32_t *)0xfe446044)
#define P_DMX_WDMA_ACTIVE_3 ((volatile uint32_t *)0xfe446048)
#define P_DMX_DMA_RDONE ((volatile uint32_t *)0xfe44604c)
#define P_DMX_DMA_WDONE_0 ((volatile uint32_t *)0xfe446050)
#define P_DMX_DMA_WDONE_1 ((volatile uint32_t *)0xfe446054)
#define P_DMX_DMA_WDONE_2 ((volatile uint32_t *)0xfe446058)
#define P_DMX_DMA_WDONE_3 ((volatile uint32_t *)0xfe44605c)
#define P_DMX_RDES_ERR ((volatile uint32_t *)0xfe446060)
#define P_DMX_RDES_LEN_ERR ((volatile uint32_t *)0xfe446064)
#define P_DMX_WDES_ERR_0 ((volatile uint32_t *)0xfe446068)
#define P_DMX_WDES_ERR_1 ((volatile uint32_t *)0xfe44606c)
#define P_DMX_WDES_ERR_2 ((volatile uint32_t *)0xfe446070)
#define P_DMX_WDES_ERR_3 ((volatile uint32_t *)0xfe446074)
#define P_DMX_DMA_BATCH_END_0 ((volatile uint32_t *)0xfe446078)
#define P_DMX_DMA_BATCH_END_1 ((volatile uint32_t *)0xfe44607c)
#define P_DMX_DMA_BATCH_END_2 ((volatile uint32_t *)0xfe446080)
#define P_DMX_DMA_BATCH_END_3 ((volatile uint32_t *)0xfe446084)
#define P_DMX_WDES_EOC_DONE_0 ((volatile uint32_t *)0xfe446088)
#define P_DMX_WDES_EOC_DONE_1 ((volatile uint32_t *)0xfe44608c)
#define P_DMX_WDES_EOC_DONE_2 ((volatile uint32_t *)0xfe446090)
#define P_DMX_WDES_EOC_DONE_3 ((volatile uint32_t *)0xfe446094)
#define P_DMX_WCH_RESP_ERR0 ((volatile uint32_t *)0xfe446098)
#define P_DMX_WCH_RESP_ERR1 ((volatile uint32_t *)0xfe44609c)
#define P_DMX_WCH_RESP_ERR2 ((volatile uint32_t *)0xfe4460a0)
#define P_DMX_WCH_RESP_ERR3 ((volatile uint32_t *)0xfe4460a4)
#define P_DMX_UPDT_PKT_SYNC ((volatile uint32_t *)0xfe4460c0)
#define P_DMX_RCHN_CFG ((volatile uint32_t *)0xfe4460c4)
#define P_DMX_WCHN_CFG ((volatile uint32_t *)0xfe4460c8)
#define P_DMX_MEM_PD_CRTL ((volatile uint32_t *)0xfe4460cc)
#define P_DMX_DMA_BUS_CFG ((volatile uint32_t *)0xfe4460d0)
#define P_DMX_DMA_GMW_CFG ((volatile uint32_t *)0xfe4460d4)
#define P_DMX_DMA_GMR_CFG ((volatile uint32_t *)0xfe4460d8)
//========================================================================
//  TS OUTPUT REG - Registers
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe442c00
// -----------------------------------------------
#define P_TS_OUTPUT_PID_RDY ((volatile uint32_t *)0xfe442c00)
#define P_TS_OUTPUT_TEE_LOCK ((volatile uint32_t *)0xfe442c04)
#define P_TS_OUTPUT_PID_CFG ((volatile uint32_t *)0xfe442c08)
#define P_TS_OUTPUT_PID_DAT ((volatile uint32_t *)0xfe442c0c)
#define P_TS_OUTPUT_OUT_CFG ((volatile uint32_t *)0xfe442c10)
#define P_TS_OUTPUT_PCR_TAB_ENTRY_0 ((volatile uint32_t *)0xfe442c40)
#define P_TS_OUTPUT_PCR_TAB_ENTRY_1 ((volatile uint32_t *)0xfe442c44)
#define P_TS_OUTPUT_PCR_TAB_ENTRY_2 ((volatile uint32_t *)0xfe442c48)
#define P_TS_OUTPUT_PCR_TAB_ENTRY_3 ((volatile uint32_t *)0xfe442c4c)
#define P_TS_OUTPUT_PCR_TAB_ENTRY_4 ((volatile uint32_t *)0xfe442c50)
#define P_TS_OUTPUT_PCR_TAB_ENTRY_5 ((volatile uint32_t *)0xfe442c54)
#define P_TS_OUTPUT_PCR_TAB_ENTRY_6 ((volatile uint32_t *)0xfe442c58)
#define P_TS_OUTPUT_PCR_TAB_ENTRY_7 ((volatile uint32_t *)0xfe442c5c)
#define P_TS_OUTPUT_PCR_TAB_ENTRY_8 ((volatile uint32_t *)0xfe442c60)
#define P_TS_OUTPUT_PCR_TAB_ENTRY_9 ((volatile uint32_t *)0xfe442c64)
#define P_TS_OUTPUT_PCR_TAB_ENTRY_10 ((volatile uint32_t *)0xfe442c68)
#define P_TS_OUTPUT_PCR_TAB_ENTRY_11 ((volatile uint32_t *)0xfe442c6c)
#define P_TS_OUTPUT_PCR_TAB_ENTRY_12 ((volatile uint32_t *)0xfe442c70)
#define P_TS_OUTPUT_PCR_TAB_ENTRY_13 ((volatile uint32_t *)0xfe442c74)
#define P_TS_OUTPUT_PCR_TAB_ENTRY_14 ((volatile uint32_t *)0xfe442c78)
#define P_TS_OUTPUT_PCR_TAB_ENTRY_15 ((volatile uint32_t *)0xfe442c7c)
#define P_TS_OUTPUT_SID_TAB_0_1 ((volatile uint32_t *)0xfe442c80)
#define P_TS_OUTPUT_SID_TAB_2_3 ((volatile uint32_t *)0xfe442c84)
#define P_TS_OUTPUT_SID_TAB_4_5 ((volatile uint32_t *)0xfe442c88)
#define P_TS_OUTPUT_SID_TAB_6_7 ((volatile uint32_t *)0xfe442c8c)
#define P_TS_OUTPUT_SID_TAB_8_9 ((volatile uint32_t *)0xfe442c90)
#define P_TS_OUTPUT_SID_TAB_10_11 ((volatile uint32_t *)0xfe442c94)
#define P_TS_OUTPUT_SID_TAB_12_13 ((volatile uint32_t *)0xfe442c98)
#define P_TS_OUTPUT_SID_TAB_14_15 ((volatile uint32_t *)0xfe442c9c)
#define P_TS_OUTPUT_SID_TAB_16_17 ((volatile uint32_t *)0xfe442ca0)
#define P_TS_OUTPUT_SID_TAB_18_19 ((volatile uint32_t *)0xfe442ca4)
#define P_TS_OUTPUT_SID_TAB_20_21 ((volatile uint32_t *)0xfe442ca8)
#define P_TS_OUTPUT_SID_TAB_22_23 ((volatile uint32_t *)0xfe442cac)
#define P_TS_OUTPUT_SID_TAB_24_25 ((volatile uint32_t *)0xfe442cb0)
#define P_TS_OUTPUT_SID_TAB_26_27 ((volatile uint32_t *)0xfe442cb4)
#define P_TS_OUTPUT_SID_TAB_28_29 ((volatile uint32_t *)0xfe442cb8)
#define P_TS_OUTPUT_SID_TAB_30_31 ((volatile uint32_t *)0xfe442cbc)
#define P_TS_OUTPUT_SID_TAB_32_33 ((volatile uint32_t *)0xfe442cc0)
#define P_TS_OUTPUT_SID_TAB_34_35 ((volatile uint32_t *)0xfe442cc4)
#define P_TS_OUTPUT_SID_TAB_36_37 ((volatile uint32_t *)0xfe442cc8)
#define P_TS_OUTPUT_SID_TAB_38_39 ((volatile uint32_t *)0xfe442ccc)
#define P_TS_OUTPUT_SID_TAB_40_41 ((volatile uint32_t *)0xfe442cd0)
#define P_TS_OUTPUT_SID_TAB_42_43 ((volatile uint32_t *)0xfe442cd4)
#define P_TS_OUTPUT_SID_TAB_44_45 ((volatile uint32_t *)0xfe442cd8)
#define P_TS_OUTPUT_SID_TAB_46_47 ((volatile uint32_t *)0xfe442cdc)
#define P_TS_OUTPUT_SID_TAB_48_49 ((volatile uint32_t *)0xfe442ce0)
#define P_TS_OUTPUT_SID_TAB_50_51 ((volatile uint32_t *)0xfe442ce4)
#define P_TS_OUTPUT_SID_TAB_52_53 ((volatile uint32_t *)0xfe442ce8)
#define P_TS_OUTPUT_SID_TAB_54_55 ((volatile uint32_t *)0xfe442cec)
#define P_TS_OUTPUT_SID_TAB_56_57 ((volatile uint32_t *)0xfe442cf0)
#define P_TS_OUTPUT_SID_TAB_58_59 ((volatile uint32_t *)0xfe442cf4)
#define P_TS_OUTPUT_SID_TAB_60_61 ((volatile uint32_t *)0xfe442cf8)
#define P_TS_OUTPUT_SID_TAB_62_63 ((volatile uint32_t *)0xfe442cfc)
#define P_TS_OUTPUT_ES_TAB_0 ((volatile uint32_t *)0xfe442d00)
#define P_TS_OUTPUT_ES_TAB_1 ((volatile uint32_t *)0xfe442d04)
#define P_TS_OUTPUT_ES_TAB_2 ((volatile uint32_t *)0xfe442d08)
#define P_TS_OUTPUT_ES_TAB_3 ((volatile uint32_t *)0xfe442d0c)
#define P_TS_OUTPUT_ES_TAB_4 ((volatile uint32_t *)0xfe442d10)
#define P_TS_OUTPUT_ES_TAB_5 ((volatile uint32_t *)0xfe442d14)
#define P_TS_OUTPUT_ES_TAB_6 ((volatile uint32_t *)0xfe442d18)
#define P_TS_OUTPUT_ES_TAB_7 ((volatile uint32_t *)0xfe442d1c)
#define P_TS_OUTPUT_ES_TAB_8 ((volatile uint32_t *)0xfe442d20)
#define P_TS_OUTPUT_ES_TAB_9 ((volatile uint32_t *)0xfe442d24)
#define P_TS_OUTPUT_ES_TAB_10 ((volatile uint32_t *)0xfe442d28)
#define P_TS_OUTPUT_ES_TAB_11 ((volatile uint32_t *)0xfe442d2c)
#define P_TS_OUTPUT_ES_TAB_12 ((volatile uint32_t *)0xfe442d30)
#define P_TS_OUTPUT_ES_TAB_13 ((volatile uint32_t *)0xfe442d34)
#define P_TS_OUTPUT_ES_TAB_14 ((volatile uint32_t *)0xfe442d38)
#define P_TS_OUTPUT_ES_TAB_15 ((volatile uint32_t *)0xfe442d3c)
#define P_TS_OUTPUT_ES_TAB_16 ((volatile uint32_t *)0xfe442d40)
#define P_TS_OUTPUT_ES_TAB_17 ((volatile uint32_t *)0xfe442d44)
#define P_TS_OUTPUT_ES_TAB_18 ((volatile uint32_t *)0xfe442d48)
#define P_TS_OUTPUT_ES_TAB_19 ((volatile uint32_t *)0xfe442d4c)
#define P_TS_OUTPUT_ES_TAB_20 ((volatile uint32_t *)0xfe442d50)
#define P_TS_OUTPUT_ES_TAB_21 ((volatile uint32_t *)0xfe442d54)
#define P_TS_OUTPUT_ES_TAB_22 ((volatile uint32_t *)0xfe442d58)
#define P_TS_OUTPUT_ES_TAB_23 ((volatile uint32_t *)0xfe442d5c)
#define P_TS_OUTPUT_ES_TAB_24 ((volatile uint32_t *)0xfe442d60)
#define P_TS_OUTPUT_ES_TAB_25 ((volatile uint32_t *)0xfe442d64)
#define P_TS_OUTPUT_ES_TAB_26 ((volatile uint32_t *)0xfe442d68)
#define P_TS_OUTPUT_ES_TAB_27 ((volatile uint32_t *)0xfe442d6c)
#define P_TS_OUTPUT_ES_TAB_28 ((volatile uint32_t *)0xfe442d70)
#define P_TS_OUTPUT_ES_TAB_29 ((volatile uint32_t *)0xfe442d74)
#define P_TS_OUTPUT_ES_TAB_30 ((volatile uint32_t *)0xfe442d78)
#define P_TS_OUTPUT_ES_TAB_31 ((volatile uint32_t *)0xfe442d7c)
#define P_TS_OUTPUT_ES_TAB_32 ((volatile uint32_t *)0xfe442d80)
#define P_TS_OUTPUT_ES_TAB_33 ((volatile uint32_t *)0xfe442d84)
#define P_TS_OUTPUT_ES_TAB_34 ((volatile uint32_t *)0xfe442d88)
#define P_TS_OUTPUT_ES_TAB_35 ((volatile uint32_t *)0xfe442d8c)
#define P_TS_OUTPUT_ES_TAB_36 ((volatile uint32_t *)0xfe442d90)
#define P_TS_OUTPUT_ES_TAB_37 ((volatile uint32_t *)0xfe442d94)
#define P_TS_OUTPUT_ES_TAB_38 ((volatile uint32_t *)0xfe442d98)
#define P_TS_OUTPUT_ES_TAB_39 ((volatile uint32_t *)0xfe442d9c)
#define P_TS_OUTPUT_ES_TAB_40 ((volatile uint32_t *)0xfe442da0)
#define P_TS_OUTPUT_ES_TAB_41 ((volatile uint32_t *)0xfe442da4)
#define P_TS_OUTPUT_ES_TAB_42 ((volatile uint32_t *)0xfe442da8)
#define P_TS_OUTPUT_ES_TAB_43 ((volatile uint32_t *)0xfe442dac)
#define P_TS_OUTPUT_ES_TAB_44 ((volatile uint32_t *)0xfe442db0)
#define P_TS_OUTPUT_ES_TAB_45 ((volatile uint32_t *)0xfe442db4)
#define P_TS_OUTPUT_ES_TAB_46 ((volatile uint32_t *)0xfe442db8)
#define P_TS_OUTPUT_ES_TAB_47 ((volatile uint32_t *)0xfe442dbc)
#define P_TS_OUTPUT_ES_TAB_48 ((volatile uint32_t *)0xfe442dc0)
#define P_TS_OUTPUT_ES_TAB_49 ((volatile uint32_t *)0xfe442dc4)
#define P_TS_OUTPUT_ES_TAB_50 ((volatile uint32_t *)0xfe442dc8)
#define P_TS_OUTPUT_ES_TAB_51 ((volatile uint32_t *)0xfe442dcc)
#define P_TS_OUTPUT_ES_TAB_52 ((volatile uint32_t *)0xfe442dd0)
#define P_TS_OUTPUT_ES_TAB_53 ((volatile uint32_t *)0xfe442dd4)
#define P_TS_OUTPUT_ES_TAB_54 ((volatile uint32_t *)0xfe442dd8)
#define P_TS_OUTPUT_ES_TAB_55 ((volatile uint32_t *)0xfe442ddc)
#define P_TS_OUTPUT_ES_TAB_56 ((volatile uint32_t *)0xfe442de0)
#define P_TS_OUTPUT_ES_TAB_57 ((volatile uint32_t *)0xfe442de4)
#define P_TS_OUTPUT_ES_TAB_58 ((volatile uint32_t *)0xfe442de8)
#define P_TS_OUTPUT_ES_TAB_59 ((volatile uint32_t *)0xfe442dec)
#define P_TS_OUTPUT_ES_TAB_60 ((volatile uint32_t *)0xfe442df0)
#define P_TS_OUTPUT_ES_TAB_61 ((volatile uint32_t *)0xfe442df4)
#define P_TS_OUTPUT_ES_TAB_62 ((volatile uint32_t *)0xfe442df8)
#define P_TS_OUTPUT_ES_TAB_63 ((volatile uint32_t *)0xfe442dfc)
#define P_TS_OUTPUT_PCR_REG_LSB_0 ((volatile uint32_t *)0xfe442e00)
#define P_TS_OUTPUT_PCR_REG_MSB_0 ((volatile uint32_t *)0xfe442e04)
#define P_TS_OUTPUT_PCR_REG_LSB_1 ((volatile uint32_t *)0xfe442e08)
#define P_TS_OUTPUT_PCR_REG_MSB_1 ((volatile uint32_t *)0xfe442e0c)
#define P_TS_OUTPUT_PCR_REG_LSB_2 ((volatile uint32_t *)0xfe442e10)
#define P_TS_OUTPUT_PCR_REG_MSB_2 ((volatile uint32_t *)0xfe442e14)
#define P_TS_OUTPUT_PCR_REG_LSB_3 ((volatile uint32_t *)0xfe442e18)
#define P_TS_OUTPUT_PCR_REG_MSB_3 ((volatile uint32_t *)0xfe442e1c)
#define P_TS_OUTPUT_PCR_REG_LSB_4 ((volatile uint32_t *)0xfe442e20)
#define P_TS_OUTPUT_PCR_REG_MSB_4 ((volatile uint32_t *)0xfe442e24)
#define P_TS_OUTPUT_PCR_REG_LSB_5 ((volatile uint32_t *)0xfe442e28)
#define P_TS_OUTPUT_PCR_REG_MSB_5 ((volatile uint32_t *)0xfe442e2c)
#define P_TS_OUTPUT_PCR_REG_LSB_6 ((volatile uint32_t *)0xfe442e30)
#define P_TS_OUTPUT_PCR_REG_MSB_6 ((volatile uint32_t *)0xfe442e34)
#define P_TS_OUTPUT_PCR_REG_LSB_7 ((volatile uint32_t *)0xfe442e38)
#define P_TS_OUTPUT_PCR_REG_MSB_7 ((volatile uint32_t *)0xfe442e3c)
#define P_TS_OUTPUT_PCR_REG_LSB_8 ((volatile uint32_t *)0xfe442e40)
#define P_TS_OUTPUT_PCR_REG_MSB_8 ((volatile uint32_t *)0xfe442e44)
#define P_TS_OUTPUT_PCR_REG_LSB_9 ((volatile uint32_t *)0xfe442e48)
#define P_TS_OUTPUT_PCR_REG_MSB_9 ((volatile uint32_t *)0xfe442e4c)
#define P_TS_OUTPUT_PCR_REG_LSB_10 ((volatile uint32_t *)0xfe442e50)
#define P_TS_OUTPUT_PCR_REG_MSB_10 ((volatile uint32_t *)0xfe442e54)
#define P_TS_OUTPUT_PCR_REG_LSB_11 ((volatile uint32_t *)0xfe442e58)
#define P_TS_OUTPUT_PCR_REG_MSB_11 ((volatile uint32_t *)0xfe442e5c)
#define P_TS_OUTPUT_PCR_REG_LSB_12 ((volatile uint32_t *)0xfe442e60)
#define P_TS_OUTPUT_PCR_REG_MSB_12 ((volatile uint32_t *)0xfe442e64)
#define P_TS_OUTPUT_PCR_REG_LSB_13 ((volatile uint32_t *)0xfe442e68)
#define P_TS_OUTPUT_PCR_REG_MSB_13 ((volatile uint32_t *)0xfe442e6c)
#define P_TS_OUTPUT_PCR_REG_LSB_14 ((volatile uint32_t *)0xfe442e70)
#define P_TS_OUTPUT_PCR_REG_MSB_14 ((volatile uint32_t *)0xfe442e74)
#define P_TS_OUTPUT_PCR_REG_LSB_15 ((volatile uint32_t *)0xfe442e78)
#define P_TS_OUTPUT_PCR_REG_MSB_15 ((volatile uint32_t *)0xfe442e7c)
//========================================================================
//  TSD DESC AES REG - Registers
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe442000
// -----------------------------------------------
#define P_TSD_PID_RDY ((volatile uint32_t *)0xfe442000)
#define P_TSD_TEE_LOCK ((volatile uint32_t *)0xfe442004)
#define P_TSD_PID_STS ((volatile uint32_t *)0xfe44200c)
#define P_TSD_PID_TABLE_LSB_0 ((volatile uint32_t *)0xfe442010)
#define P_TSD_PID_TABLE_MSB_0 ((volatile uint32_t *)0xfe442014)
#define P_TSD_PID_TABLE_LSB_1 ((volatile uint32_t *)0xfe442018)
#define P_TSD_PID_TABLE_MSB_1 ((volatile uint32_t *)0xfe44201c)
#define P_TSD_PID_TABLE_LSB_2 ((volatile uint32_t *)0xfe442020)
#define P_TSD_PID_TABLE_MSB_2 ((volatile uint32_t *)0xfe442024)
#define P_TSD_PID_TABLE_LSB_3 ((volatile uint32_t *)0xfe442028)
#define P_TSD_PID_TABLE_MSB_3 ((volatile uint32_t *)0xfe44202c)
#define P_TSD_PID_TABLE_LSB_4 ((volatile uint32_t *)0xfe442030)
#define P_TSD_PID_TABLE_MSB_4 ((volatile uint32_t *)0xfe442034)
#define P_TSD_PID_TABLE_LSB_5 ((volatile uint32_t *)0xfe442038)
#define P_TSD_PID_TABLE_MSB_5 ((volatile uint32_t *)0xfe44203c)
#define P_TSD_PID_TABLE_LSB_6 ((volatile uint32_t *)0xfe442040)
#define P_TSD_PID_TABLE_MSB_6 ((volatile uint32_t *)0xfe442044)
#define P_TSD_PID_TABLE_LSB_7 ((volatile uint32_t *)0xfe442048)
#define P_TSD_PID_TABLE_MSB_7 ((volatile uint32_t *)0xfe44204c)
#define P_TSD_PID_TABLE_LSB_8 ((volatile uint32_t *)0xfe442050)
#define P_TSD_PID_TABLE_MSB_8 ((volatile uint32_t *)0xfe442054)
#define P_TSD_PID_TABLE_LSB_9 ((volatile uint32_t *)0xfe442058)
#define P_TSD_PID_TABLE_MSB_9 ((volatile uint32_t *)0xfe44205c)
#define P_TSD_PID_TABLE_LSB_10 ((volatile uint32_t *)0xfe442060)
#define P_TSD_PID_TABLE_MSB_10 ((volatile uint32_t *)0xfe442064)
#define P_TSD_PID_TABLE_LSB_11 ((volatile uint32_t *)0xfe442068)
#define P_TSD_PID_TABLE_MSB_11 ((volatile uint32_t *)0xfe44206c)
#define P_TSD_PID_TABLE_LSB_12 ((volatile uint32_t *)0xfe442070)
#define P_TSD_PID_TABLE_MSB_12 ((volatile uint32_t *)0xfe442074)
#define P_TSD_PID_TABLE_LSB_13 ((volatile uint32_t *)0xfe442078)
#define P_TSD_PID_TABLE_MSB_13 ((volatile uint32_t *)0xfe44207c)
#define P_TSD_PID_TABLE_LSB_14 ((volatile uint32_t *)0xfe442080)
#define P_TSD_PID_TABLE_MSB_14 ((volatile uint32_t *)0xfe442084)
#define P_TSD_PID_TABLE_LSB_15 ((volatile uint32_t *)0xfe442088)
#define P_TSD_PID_TABLE_MSB_15 ((volatile uint32_t *)0xfe44208c)
#define P_TSD_PID_TABLE_LSB_16 ((volatile uint32_t *)0xfe442090)
#define P_TSD_PID_TABLE_MSB_16 ((volatile uint32_t *)0xfe442094)
#define P_TSD_PID_TABLE_LSB_17 ((volatile uint32_t *)0xfe442098)
#define P_TSD_PID_TABLE_MSB_17 ((volatile uint32_t *)0xfe44209c)
#define P_TSD_PID_TABLE_LSB_18 ((volatile uint32_t *)0xfe4420a0)
#define P_TSD_PID_TABLE_MSB_18 ((volatile uint32_t *)0xfe4420a4)
#define P_TSD_PID_TABLE_LSB_19 ((volatile uint32_t *)0xfe4420a8)
#define P_TSD_PID_TABLE_MSB_19 ((volatile uint32_t *)0xfe4420ac)
#define P_TSD_PID_TABLE_LSB_20 ((volatile uint32_t *)0xfe4420b0)
#define P_TSD_PID_TABLE_MSB_20 ((volatile uint32_t *)0xfe4420b4)
#define P_TSD_PID_TABLE_LSB_21 ((volatile uint32_t *)0xfe4420b8)
#define P_TSD_PID_TABLE_MSB_21 ((volatile uint32_t *)0xfe4420bc)
#define P_TSD_PID_TABLE_LSB_22 ((volatile uint32_t *)0xfe4420c0)
#define P_TSD_PID_TABLE_MSB_22 ((volatile uint32_t *)0xfe4420c4)
#define P_TSD_PID_TABLE_LSB_23 ((volatile uint32_t *)0xfe4420c8)
#define P_TSD_PID_TABLE_MSB_23 ((volatile uint32_t *)0xfe4420cc)
#define P_TSD_PID_TABLE_LSB_24 ((volatile uint32_t *)0xfe4420d0)
#define P_TSD_PID_TABLE_MSB_24 ((volatile uint32_t *)0xfe4420d4)
#define P_TSD_PID_TABLE_LSB_25 ((volatile uint32_t *)0xfe4420d8)
#define P_TSD_PID_TABLE_MSB_25 ((volatile uint32_t *)0xfe4420dc)
#define P_TSD_PID_TABLE_LSB_26 ((volatile uint32_t *)0xfe4420e0)
#define P_TSD_PID_TABLE_MSB_26 ((volatile uint32_t *)0xfe4420e4)
#define P_TSD_PID_TABLE_LSB_27 ((volatile uint32_t *)0xfe4420e8)
#define P_TSD_PID_TABLE_MSB_27 ((volatile uint32_t *)0xfe4420ec)
#define P_TSD_PID_TABLE_LSB_28 ((volatile uint32_t *)0xfe4420f0)
#define P_TSD_PID_TABLE_MSB_28 ((volatile uint32_t *)0xfe4420f4)
#define P_TSD_PID_TABLE_LSB_29 ((volatile uint32_t *)0xfe4420f8)
#define P_TSD_PID_TABLE_MSB_29 ((volatile uint32_t *)0xfe4420fc)
#define P_TSD_PID_TABLE_LSB_30 ((volatile uint32_t *)0xfe442100)
#define P_TSD_PID_TABLE_MSB_30 ((volatile uint32_t *)0xfe442104)
#define P_TSD_PID_TABLE_LSB_31 ((volatile uint32_t *)0xfe442108)
#define P_TSD_PID_TABLE_MSB_31 ((volatile uint32_t *)0xfe44210c)
#define P_TSD_PID_TABLE_LSB_32 ((volatile uint32_t *)0xfe442110)
#define P_TSD_PID_TABLE_MSB_32 ((volatile uint32_t *)0xfe442114)
#define P_TSD_PID_TABLE_LSB_33 ((volatile uint32_t *)0xfe442118)
#define P_TSD_PID_TABLE_MSB_33 ((volatile uint32_t *)0xfe44211c)
#define P_TSD_PID_TABLE_LSB_34 ((volatile uint32_t *)0xfe442120)
#define P_TSD_PID_TABLE_MSB_34 ((volatile uint32_t *)0xfe442124)
#define P_TSD_PID_TABLE_LSB_35 ((volatile uint32_t *)0xfe442128)
#define P_TSD_PID_TABLE_MSB_35 ((volatile uint32_t *)0xfe44212c)
#define P_TSD_PID_TABLE_LSB_36 ((volatile uint32_t *)0xfe442130)
#define P_TSD_PID_TABLE_MSB_36 ((volatile uint32_t *)0xfe442134)
#define P_TSD_PID_TABLE_LSB_37 ((volatile uint32_t *)0xfe442138)
#define P_TSD_PID_TABLE_MSB_37 ((volatile uint32_t *)0xfe44213c)
#define P_TSD_PID_TABLE_LSB_38 ((volatile uint32_t *)0xfe442140)
#define P_TSD_PID_TABLE_MSB_38 ((volatile uint32_t *)0xfe442144)
#define P_TSD_PID_TABLE_LSB_39 ((volatile uint32_t *)0xfe442148)
#define P_TSD_PID_TABLE_MSB_39 ((volatile uint32_t *)0xfe44214c)
#define P_TSD_PID_TABLE_LSB_40 ((volatile uint32_t *)0xfe442150)
#define P_TSD_PID_TABLE_MSB_40 ((volatile uint32_t *)0xfe442154)
#define P_TSD_PID_TABLE_LSB_41 ((volatile uint32_t *)0xfe442158)
#define P_TSD_PID_TABLE_MSB_41 ((volatile uint32_t *)0xfe44215c)
#define P_TSD_PID_TABLE_LSB_42 ((volatile uint32_t *)0xfe442160)
#define P_TSD_PID_TABLE_MSB_42 ((volatile uint32_t *)0xfe442164)
#define P_TSD_PID_TABLE_LSB_43 ((volatile uint32_t *)0xfe442168)
#define P_TSD_PID_TABLE_MSB_43 ((volatile uint32_t *)0xfe44216c)
#define P_TSD_PID_TABLE_LSB_44 ((volatile uint32_t *)0xfe442170)
#define P_TSD_PID_TABLE_MSB_44 ((volatile uint32_t *)0xfe442174)
#define P_TSD_PID_TABLE_LSB_45 ((volatile uint32_t *)0xfe442178)
#define P_TSD_PID_TABLE_MSB_45 ((volatile uint32_t *)0xfe44217c)
#define P_TSD_PID_TABLE_LSB_46 ((volatile uint32_t *)0xfe442180)
#define P_TSD_PID_TABLE_MSB_46 ((volatile uint32_t *)0xfe442184)
#define P_TSD_PID_TABLE_LSB_47 ((volatile uint32_t *)0xfe442188)
#define P_TSD_PID_TABLE_MSB_47 ((volatile uint32_t *)0xfe44218c)
#define P_TSD_PID_TABLE_LSB_48 ((volatile uint32_t *)0xfe442190)
#define P_TSD_PID_TABLE_MSB_48 ((volatile uint32_t *)0xfe442194)
#define P_TSD_PID_TABLE_LSB_49 ((volatile uint32_t *)0xfe442198)
#define P_TSD_PID_TABLE_MSB_49 ((volatile uint32_t *)0xfe44219c)
#define P_TSD_PID_TABLE_LSB_50 ((volatile uint32_t *)0xfe4421a0)
#define P_TSD_PID_TABLE_MSB_50 ((volatile uint32_t *)0xfe4421a4)
#define P_TSD_PID_TABLE_LSB_51 ((volatile uint32_t *)0xfe4421a8)
#define P_TSD_PID_TABLE_MSB_51 ((volatile uint32_t *)0xfe4421ac)
#define P_TSD_PID_TABLE_LSB_52 ((volatile uint32_t *)0xfe4421b0)
#define P_TSD_PID_TABLE_MSB_52 ((volatile uint32_t *)0xfe4421b4)
#define P_TSD_PID_TABLE_LSB_53 ((volatile uint32_t *)0xfe4421b8)
#define P_TSD_PID_TABLE_MSB_53 ((volatile uint32_t *)0xfe4421bc)
#define P_TSD_PID_TABLE_LSB_54 ((volatile uint32_t *)0xfe4421c0)
#define P_TSD_PID_TABLE_MSB_54 ((volatile uint32_t *)0xfe4421c4)
#define P_TSD_PID_TABLE_LSB_55 ((volatile uint32_t *)0xfe4421c8)
#define P_TSD_PID_TABLE_MSB_55 ((volatile uint32_t *)0xfe4421cc)
#define P_TSD_PID_TABLE_LSB_56 ((volatile uint32_t *)0xfe4421d0)
#define P_TSD_PID_TABLE_MSB_56 ((volatile uint32_t *)0xfe4421d4)
#define P_TSD_PID_TABLE_LSB_57 ((volatile uint32_t *)0xfe4421d8)
#define P_TSD_PID_TABLE_MSB_57 ((volatile uint32_t *)0xfe4421dc)
#define P_TSD_PID_TABLE_LSB_58 ((volatile uint32_t *)0xfe4421e0)
#define P_TSD_PID_TABLE_MSB_58 ((volatile uint32_t *)0xfe4421e4)
#define P_TSD_PID_TABLE_LSB_59 ((volatile uint32_t *)0xfe4421e8)
#define P_TSD_PID_TABLE_MSB_59 ((volatile uint32_t *)0xfe4421ec)
#define P_TSD_PID_TABLE_LSB_60 ((volatile uint32_t *)0xfe4421f0)
#define P_TSD_PID_TABLE_MSB_60 ((volatile uint32_t *)0xfe4421f4)
#define P_TSD_PID_TABLE_LSB_61 ((volatile uint32_t *)0xfe4421f8)
#define P_TSD_PID_TABLE_MSB_61 ((volatile uint32_t *)0xfe4421fc)
#define P_TSD_PID_TABLE_LSB_62 ((volatile uint32_t *)0xfe442200)
#define P_TSD_PID_TABLE_MSB_62 ((volatile uint32_t *)0xfe442204)
#define P_TSD_PID_TABLE_LSB_63 ((volatile uint32_t *)0xfe442208)
#define P_TSD_PID_TABLE_MSB_63 ((volatile uint32_t *)0xfe44220c)
//========================================================================
// SECURE TOP REG - Registers
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe440300
// -----------------------------------------------
#define P_SEC_TOP_CFG_LOCKABLE ((volatile uint32_t *)0xfe440300)
#define P_SEC_TOP_CFG_LOCK ((volatile uint32_t *)0xfe440304)
#define P_SEC_TOP_CFG_WTO ((volatile uint32_t *)0xfe440308)
#define P_SEC_TOP_N2_GENOUT ((volatile uint32_t *)0xfe44030c)
#define P_SEC_TOP_CFG_REG ((volatile uint32_t *)0xfe440310)
#define P_SEC_TOP_NSK_CTRL ((volatile uint32_t *)0xfe440314)
#define P_SEC_TOP_AKL_STS ((volatile uint32_t *)0xfe440318)
#define P_SEC_TOP_ND_STATUS ((volatile uint32_t *)0xfe44031c)
#define P_SEC_TOP_CFG_DEMUX ((volatile uint32_t *)0xfe440320)
#define P_SEC_TOP_CFG_DIF ((volatile uint32_t *)0xfe440330)
#define P_SEC_TOP_NSK_HASH0 ((volatile uint32_t *)0xfe440340)
#define P_SEC_TOP_NSK_HASH1 ((volatile uint32_t *)0xfe440344)
#define P_SEC_TOP_NSK_HASH2 ((volatile uint32_t *)0xfe440348)
#define P_SEC_TOP_NSK_HASH3 ((volatile uint32_t *)0xfe44034c)
#define P_SEC_TOP_PATH0_CTRL ((volatile uint32_t *)0xfe4403a0)
#define P_SEC_TOP_PATH1_CTRL ((volatile uint32_t *)0xfe4403a4)
#define P_SEC_TOP_PATH2_CTRL ((volatile uint32_t *)0xfe4403a8)
#define P_SEC_TOP_PATH3_CTRL ((volatile uint32_t *)0xfe4403ac)
#define P_SEC_TOP_DEMOD_PKT_CFG0 ((volatile uint32_t *)0xfe4403b0)
#define P_SEC_TOP_DEMOD_PKT_CFG1 ((volatile uint32_t *)0xfe4403b4)
#define P_SEC_TOP_DEMOD_PKT_CFG2 ((volatile uint32_t *)0xfe4403b8)
#define P_SEC_TOP_DEMOD_PKT_CFG3 ((volatile uint32_t *)0xfe4403bc)
#define P_SEC_TOP_DEMOD_FIFO_CFG0 ((volatile uint32_t *)0xfe4403c0)
#define P_SEC_TOP_DEMOD_FIFO_CFG1 ((volatile uint32_t *)0xfe4403c4)
#define P_SEC_TOP_TS_O_PATH_CTRL ((volatile uint32_t *)0xfe4403c8)
#define P_SEC_TOP_CLEAN_DEMOD_INT ((volatile uint32_t *)0xfe4403cc)
#define P_SEC_TOP_DEMOD_INT_MASK ((volatile uint32_t *)0xfe4403d0)
#define P_SEC_TOP_DEMOD_INT_STATUS ((volatile uint32_t *)0xfe4403d4)
#define P_SEC_TOP_TS_CHN0_ERR_STATUS ((volatile uint32_t *)0xfe4403d8)
#define P_SEC_TOP_TS_CHN1_ERR_STATUS ((volatile uint32_t *)0xfe4403dc)
#define P_SEC_TOP_TS_CHN2_ERR_STATUS ((volatile uint32_t *)0xfe4403e0)
#define P_SEC_TOP_TS_CHN3_ERR_STATUS ((volatile uint32_t *)0xfe4403e4)
//========================================================================
// TSE DESC AES REG - Registers
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe442800
// -----------------------------------------------
#define P_TSE_PID_RDY ((volatile uint32_t *)0xfe442800)
#define P_TSE_TEE_LOCK ((volatile uint32_t *)0xfe442804)
#define P_TSE_PID_STS ((volatile uint32_t *)0xfe44280c)
#define P_TSE_PID_TABLE_LSB_0 ((volatile uint32_t *)0xfe442810)
#define P_TSE_PID_TABLE_MSB_0 ((volatile uint32_t *)0xfe442814)
#define P_TSE_PID_TABLE_LSB_1 ((volatile uint32_t *)0xfe442818)
#define P_TSE_PID_TABLE_MSB_1 ((volatile uint32_t *)0xfe44281c)
#define P_TSE_PID_TABLE_LSB_2 ((volatile uint32_t *)0xfe442820)
#define P_TSE_PID_TABLE_MSB_2 ((volatile uint32_t *)0xfe442824)
#define P_TSE_PID_TABLE_LSB_3 ((volatile uint32_t *)0xfe442828)
#define P_TSE_PID_TABLE_MSB_3 ((volatile uint32_t *)0xfe44282c)
#define P_TSE_PID_TABLE_LSB_4 ((volatile uint32_t *)0xfe442830)
#define P_TSE_PID_TABLE_MSB_4 ((volatile uint32_t *)0xfe442834)
#define P_TSE_PID_TABLE_LSB_5 ((volatile uint32_t *)0xfe442838)
#define P_TSE_PID_TABLE_MSB_5 ((volatile uint32_t *)0xfe44283c)
#define P_TSE_PID_TABLE_LSB_6 ((volatile uint32_t *)0xfe442840)
#define P_TSE_PID_TABLE_MSB_6 ((volatile uint32_t *)0xfe442844)
#define P_TSE_PID_TABLE_LSB_7 ((volatile uint32_t *)0xfe442848)
#define P_TSE_PID_TABLE_MSB_7 ((volatile uint32_t *)0xfe44284c)
#define P_TSE_PID_TABLE_LSB_8 ((volatile uint32_t *)0xfe442850)
#define P_TSE_PID_TABLE_MSB_8 ((volatile uint32_t *)0xfe442854)
#define P_TSE_PID_TABLE_LSB_9 ((volatile uint32_t *)0xfe442858)
#define P_TSE_PID_TABLE_MSB_9 ((volatile uint32_t *)0xfe44285c)
#define P_TSE_PID_TABLE_LSB_10 ((volatile uint32_t *)0xfe442860)
#define P_TSE_PID_TABLE_MSB_10 ((volatile uint32_t *)0xfe442864)
#define P_TSE_PID_TABLE_LSB_11 ((volatile uint32_t *)0xfe442868)
#define P_TSE_PID_TABLE_MSB_11 ((volatile uint32_t *)0xfe44286c)
#define P_TSE_PID_TABLE_LSB_12 ((volatile uint32_t *)0xfe442870)
#define P_TSE_PID_TABLE_MSB_12 ((volatile uint32_t *)0xfe442874)
#define P_TSE_PID_TABLE_LSB_13 ((volatile uint32_t *)0xfe442878)
#define P_TSE_PID_TABLE_MSB_13 ((volatile uint32_t *)0xfe44287c)
#define P_TSE_PID_TABLE_LSB_14 ((volatile uint32_t *)0xfe442880)
#define P_TSE_PID_TABLE_MSB_14 ((volatile uint32_t *)0xfe442884)
#define P_TSE_PID_TABLE_LSB_15 ((volatile uint32_t *)0xfe442888)
#define P_TSE_PID_TABLE_MSB_15 ((volatile uint32_t *)0xfe44288c)
#define P_TSE_PID_TABLE_LSB_16 ((volatile uint32_t *)0xfe442890)
#define P_TSE_PID_TABLE_MSB_16 ((volatile uint32_t *)0xfe442894)
#define P_TSE_PID_TABLE_LSB_17 ((volatile uint32_t *)0xfe442898)
#define P_TSE_PID_TABLE_MSB_17 ((volatile uint32_t *)0xfe44289c)
#define P_TSE_PID_TABLE_LSB_18 ((volatile uint32_t *)0xfe4428a0)
#define P_TSE_PID_TABLE_MSB_18 ((volatile uint32_t *)0xfe4428a4)
#define P_TSE_PID_TABLE_LSB_19 ((volatile uint32_t *)0xfe4428a8)
#define P_TSE_PID_TABLE_MSB_19 ((volatile uint32_t *)0xfe4428ac)
#define P_TSE_PID_TABLE_LSB_20 ((volatile uint32_t *)0xfe4428b0)
#define P_TSE_PID_TABLE_MSB_20 ((volatile uint32_t *)0xfe4428b4)
#define P_TSE_PID_TABLE_LSB_21 ((volatile uint32_t *)0xfe4428b8)
#define P_TSE_PID_TABLE_MSB_21 ((volatile uint32_t *)0xfe4428bc)
#define P_TSE_PID_TABLE_LSB_22 ((volatile uint32_t *)0xfe4428c0)
#define P_TSE_PID_TABLE_MSB_22 ((volatile uint32_t *)0xfe4428c4)
#define P_TSE_PID_TABLE_LSB_23 ((volatile uint32_t *)0xfe4428c8)
#define P_TSE_PID_TABLE_MSB_23 ((volatile uint32_t *)0xfe4428cc)
#define P_TSE_PID_TABLE_LSB_24 ((volatile uint32_t *)0xfe4428d0)
#define P_TSE_PID_TABLE_MSB_24 ((volatile uint32_t *)0xfe4428d4)
#define P_TSE_PID_TABLE_LSB_25 ((volatile uint32_t *)0xfe4428d8)
#define P_TSE_PID_TABLE_MSB_25 ((volatile uint32_t *)0xfe4428dc)
#define P_TSE_PID_TABLE_LSB_26 ((volatile uint32_t *)0xfe4428e0)
#define P_TSE_PID_TABLE_MSB_26 ((volatile uint32_t *)0xfe4428e4)
#define P_TSE_PID_TABLE_LSB_27 ((volatile uint32_t *)0xfe4428e8)
#define P_TSE_PID_TABLE_MSB_27 ((volatile uint32_t *)0xfe4428ec)
#define P_TSE_PID_TABLE_LSB_28 ((volatile uint32_t *)0xfe4428f0)
#define P_TSE_PID_TABLE_MSB_28 ((volatile uint32_t *)0xfe4428f4)
#define P_TSE_PID_TABLE_LSB_29 ((volatile uint32_t *)0xfe4428f8)
#define P_TSE_PID_TABLE_MSB_29 ((volatile uint32_t *)0xfe4428fc)
#define P_TSE_PID_TABLE_LSB_30 ((volatile uint32_t *)0xfe442900)
#define P_TSE_PID_TABLE_MSB_30 ((volatile uint32_t *)0xfe442904)
#define P_TSE_PID_TABLE_LSB_31 ((volatile uint32_t *)0xfe442908)
#define P_TSE_PID_TABLE_MSB_31 ((volatile uint32_t *)0xfe44290c)
#define P_TSE_PID_TABLE_LSB_32 ((volatile uint32_t *)0xfe442910)
#define P_TSE_PID_TABLE_MSB_32 ((volatile uint32_t *)0xfe442914)
#define P_TSE_PID_TABLE_LSB_33 ((volatile uint32_t *)0xfe442918)
#define P_TSE_PID_TABLE_MSB_33 ((volatile uint32_t *)0xfe44291c)
#define P_TSE_PID_TABLE_LSB_34 ((volatile uint32_t *)0xfe442920)
#define P_TSE_PID_TABLE_MSB_34 ((volatile uint32_t *)0xfe442924)
#define P_TSE_PID_TABLE_LSB_35 ((volatile uint32_t *)0xfe442928)
#define P_TSE_PID_TABLE_MSB_35 ((volatile uint32_t *)0xfe44292c)
#define P_TSE_PID_TABLE_LSB_36 ((volatile uint32_t *)0xfe442930)
#define P_TSE_PID_TABLE_MSB_36 ((volatile uint32_t *)0xfe442934)
#define P_TSE_PID_TABLE_LSB_37 ((volatile uint32_t *)0xfe442938)
#define P_TSE_PID_TABLE_MSB_37 ((volatile uint32_t *)0xfe44293c)
#define P_TSE_PID_TABLE_LSB_38 ((volatile uint32_t *)0xfe442940)
#define P_TSE_PID_TABLE_MSB_38 ((volatile uint32_t *)0xfe442944)
#define P_TSE_PID_TABLE_LSB_39 ((volatile uint32_t *)0xfe442948)
#define P_TSE_PID_TABLE_MSB_39 ((volatile uint32_t *)0xfe44294c)
#define P_TSE_PID_TABLE_LSB_40 ((volatile uint32_t *)0xfe442950)
#define P_TSE_PID_TABLE_MSB_40 ((volatile uint32_t *)0xfe442954)
#define P_TSE_PID_TABLE_LSB_41 ((volatile uint32_t *)0xfe442958)
#define P_TSE_PID_TABLE_MSB_41 ((volatile uint32_t *)0xfe44295c)
#define P_TSE_PID_TABLE_LSB_42 ((volatile uint32_t *)0xfe442960)
#define P_TSE_PID_TABLE_MSB_42 ((volatile uint32_t *)0xfe442964)
#define P_TSE_PID_TABLE_LSB_43 ((volatile uint32_t *)0xfe442968)
#define P_TSE_PID_TABLE_MSB_43 ((volatile uint32_t *)0xfe44296c)
#define P_TSE_PID_TABLE_LSB_44 ((volatile uint32_t *)0xfe442970)
#define P_TSE_PID_TABLE_MSB_44 ((volatile uint32_t *)0xfe442974)
#define P_TSE_PID_TABLE_LSB_45 ((volatile uint32_t *)0xfe442978)
#define P_TSE_PID_TABLE_MSB_45 ((volatile uint32_t *)0xfe44297c)
#define P_TSE_PID_TABLE_LSB_46 ((volatile uint32_t *)0xfe442980)
#define P_TSE_PID_TABLE_MSB_46 ((volatile uint32_t *)0xfe442984)
#define P_TSE_PID_TABLE_LSB_47 ((volatile uint32_t *)0xfe442988)
#define P_TSE_PID_TABLE_MSB_47 ((volatile uint32_t *)0xfe44298c)
#define P_TSE_PID_TABLE_LSB_48 ((volatile uint32_t *)0xfe442990)
#define P_TSE_PID_TABLE_MSB_48 ((volatile uint32_t *)0xfe442994)
#define P_TSE_PID_TABLE_LSB_49 ((volatile uint32_t *)0xfe442998)
#define P_TSE_PID_TABLE_MSB_49 ((volatile uint32_t *)0xfe44299c)
#define P_TSE_PID_TABLE_LSB_50 ((volatile uint32_t *)0xfe4429a0)
#define P_TSE_PID_TABLE_MSB_50 ((volatile uint32_t *)0xfe4429a4)
#define P_TSE_PID_TABLE_LSB_51 ((volatile uint32_t *)0xfe4429a8)
#define P_TSE_PID_TABLE_MSB_51 ((volatile uint32_t *)0xfe4429ac)
#define P_TSE_PID_TABLE_LSB_52 ((volatile uint32_t *)0xfe4429b0)
#define P_TSE_PID_TABLE_MSB_52 ((volatile uint32_t *)0xfe4429b4)
#define P_TSE_PID_TABLE_LSB_53 ((volatile uint32_t *)0xfe4429b8)
#define P_TSE_PID_TABLE_MSB_53 ((volatile uint32_t *)0xfe4429bc)
#define P_TSE_PID_TABLE_LSB_54 ((volatile uint32_t *)0xfe4429c0)
#define P_TSE_PID_TABLE_MSB_54 ((volatile uint32_t *)0xfe4429c4)
#define P_TSE_PID_TABLE_LSB_55 ((volatile uint32_t *)0xfe4429c8)
#define P_TSE_PID_TABLE_MSB_55 ((volatile uint32_t *)0xfe4429cc)
#define P_TSE_PID_TABLE_LSB_56 ((volatile uint32_t *)0xfe4429d0)
#define P_TSE_PID_TABLE_MSB_56 ((volatile uint32_t *)0xfe4429d4)
#define P_TSE_PID_TABLE_LSB_57 ((volatile uint32_t *)0xfe4429d8)
#define P_TSE_PID_TABLE_MSB_57 ((volatile uint32_t *)0xfe4429dc)
#define P_TSE_PID_TABLE_LSB_58 ((volatile uint32_t *)0xfe4429e0)
#define P_TSE_PID_TABLE_MSB_58 ((volatile uint32_t *)0xfe4429e4)
#define P_TSE_PID_TABLE_LSB_59 ((volatile uint32_t *)0xfe4429e8)
#define P_TSE_PID_TABLE_MSB_59 ((volatile uint32_t *)0xfe4429ec)
#define P_TSE_PID_TABLE_LSB_60 ((volatile uint32_t *)0xfe4429f0)
#define P_TSE_PID_TABLE_MSB_60 ((volatile uint32_t *)0xfe4429f4)
#define P_TSE_PID_TABLE_LSB_61 ((volatile uint32_t *)0xfe4429f8)
#define P_TSE_PID_TABLE_MSB_61 ((volatile uint32_t *)0xfe4429fc)
#define P_TSE_PID_TABLE_LSB_62 ((volatile uint32_t *)0xfe442a00)
#define P_TSE_PID_TABLE_MSB_62 ((volatile uint32_t *)0xfe442a04)
#define P_TSE_PID_TABLE_LSB_63 ((volatile uint32_t *)0xfe442a08)
#define P_TSE_PID_TABLE_MSB_63 ((volatile uint32_t *)0xfe442a0c)
//========================================================================
// TSN DESC REG - Registers
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe442400
// -----------------------------------------------
#define P_TSN_PID_RDY ((volatile uint32_t *)0xfe442400)
#define P_TSN_TEE_LOCK ((volatile uint32_t *)0xfe442404)
#define P_TSN_PID_STS ((volatile uint32_t *)0xfe44240c)
#define P_TSN_PID_TABLE_0 ((volatile uint32_t *)0xfe442410)
#define P_TSN_PID_TABLE_1 ((volatile uint32_t *)0xfe442414)
#define P_TSN_PID_TABLE_2 ((volatile uint32_t *)0xfe442418)
#define P_TSN_PID_TABLE_3 ((volatile uint32_t *)0xfe44241c)
#define P_TSN_PID_TABLE_4 ((volatile uint32_t *)0xfe442420)
#define P_TSN_PID_TABLE_5 ((volatile uint32_t *)0xfe442424)
#define P_TSN_PID_TABLE_6 ((volatile uint32_t *)0xfe442428)
#define P_TSN_PID_TABLE_7 ((volatile uint32_t *)0xfe44242c)
#define P_TSN_PID_TABLE_8 ((volatile uint32_t *)0xfe442430)
#define P_TSN_PID_TABLE_9 ((volatile uint32_t *)0xfe442434)
#define P_TSN_PID_TABLE_10 ((volatile uint32_t *)0xfe442438)
#define P_TSN_PID_TABLE_11 ((volatile uint32_t *)0xfe44243c)
#define P_TSN_PID_TABLE_12 ((volatile uint32_t *)0xfe442440)
#define P_TSN_PID_TABLE_13 ((volatile uint32_t *)0xfe442444)
#define P_TSN_PID_TABLE_14 ((volatile uint32_t *)0xfe442448)
#define P_TSN_PID_TABLE_15 ((volatile uint32_t *)0xfe44244c)
#define P_TSN_PID_TABLE_16 ((volatile uint32_t *)0xfe442450)
#define P_TSN_PID_TABLE_17 ((volatile uint32_t *)0xfe442454)
#define P_TSN_PID_TABLE_18 ((volatile uint32_t *)0xfe442458)
#define P_TSN_PID_TABLE_19 ((volatile uint32_t *)0xfe44245c)
#define P_TSN_PID_TABLE_20 ((volatile uint32_t *)0xfe442460)
#define P_TSN_PID_TABLE_21 ((volatile uint32_t *)0xfe442464)
#define P_TSN_PID_TABLE_22 ((volatile uint32_t *)0xfe442468)
#define P_TSN_PID_TABLE_23 ((volatile uint32_t *)0xfe44246c)
#define P_TSN_PID_TABLE_24 ((volatile uint32_t *)0xfe442470)
#define P_TSN_PID_TABLE_25 ((volatile uint32_t *)0xfe442474)
#define P_TSN_PID_TABLE_26 ((volatile uint32_t *)0xfe442478)
#define P_TSN_PID_TABLE_27 ((volatile uint32_t *)0xfe44247c)
#define P_TSN_PID_TABLE_28 ((volatile uint32_t *)0xfe442480)
#define P_TSN_PID_TABLE_29 ((volatile uint32_t *)0xfe442484)
#define P_TSN_PID_TABLE_30 ((volatile uint32_t *)0xfe442488)
#define P_TSN_PID_TABLE_31 ((volatile uint32_t *)0xfe44248c)
#define P_TSN_PID_TABLE_32 ((volatile uint32_t *)0xfe442490)
#define P_TSN_PID_TABLE_33 ((volatile uint32_t *)0xfe442494)
#define P_TSN_PID_TABLE_34 ((volatile uint32_t *)0xfe442498)
#define P_TSN_PID_TABLE_35 ((volatile uint32_t *)0xfe44249c)
#define P_TSN_PID_TABLE_36 ((volatile uint32_t *)0xfe4424a0)
#define P_TSN_PID_TABLE_37 ((volatile uint32_t *)0xfe4424a4)
#define P_TSN_PID_TABLE_38 ((volatile uint32_t *)0xfe4424a8)
#define P_TSN_PID_TABLE_39 ((volatile uint32_t *)0xfe4424ac)
#define P_TSN_PID_TABLE_40 ((volatile uint32_t *)0xfe4424b0)
#define P_TSN_PID_TABLE_41 ((volatile uint32_t *)0xfe4424b4)
#define P_TSN_PID_TABLE_42 ((volatile uint32_t *)0xfe4424b8)
#define P_TSN_PID_TABLE_43 ((volatile uint32_t *)0xfe4424bc)
#define P_TSN_PID_TABLE_44 ((volatile uint32_t *)0xfe4424c0)
#define P_TSN_PID_TABLE_45 ((volatile uint32_t *)0xfe4424c4)
#define P_TSN_PID_TABLE_46 ((volatile uint32_t *)0xfe4424c8)
#define P_TSN_PID_TABLE_47 ((volatile uint32_t *)0xfe4424cc)
#define P_TSN_PID_TABLE_48 ((volatile uint32_t *)0xfe4424d0)
#define P_TSN_PID_TABLE_49 ((volatile uint32_t *)0xfe4424d4)
#define P_TSN_PID_TABLE_50 ((volatile uint32_t *)0xfe4424d8)
#define P_TSN_PID_TABLE_51 ((volatile uint32_t *)0xfe4424dc)
#define P_TSN_PID_TABLE_52 ((volatile uint32_t *)0xfe4424e0)
#define P_TSN_PID_TABLE_53 ((volatile uint32_t *)0xfe4424e4)
#define P_TSN_PID_TABLE_54 ((volatile uint32_t *)0xfe4424e8)
#define P_TSN_PID_TABLE_55 ((volatile uint32_t *)0xfe4424ec)
#define P_TSN_PID_TABLE_56 ((volatile uint32_t *)0xfe4424f0)
#define P_TSN_PID_TABLE_57 ((volatile uint32_t *)0xfe4424f4)
#define P_TSN_PID_TABLE_58 ((volatile uint32_t *)0xfe4424f8)
#define P_TSN_PID_TABLE_59 ((volatile uint32_t *)0xfe4424fc)
#define P_TSN_PID_TABLE_60 ((volatile uint32_t *)0xfe442500)
#define P_TSN_PID_TABLE_61 ((volatile uint32_t *)0xfe442504)
#define P_TSN_PID_TABLE_62 ((volatile uint32_t *)0xfe442508)
#define P_TSN_PID_TABLE_63 ((volatile uint32_t *)0xfe44250c)
#define P_TSN_PID_TABLE_64 ((volatile uint32_t *)0xfe442510)
#define P_TSN_PID_TABLE_65 ((volatile uint32_t *)0xfe442514)
#define P_TSN_PID_TABLE_66 ((volatile uint32_t *)0xfe442518)
#define P_TSN_PID_TABLE_67 ((volatile uint32_t *)0xfe44251c)
#define P_TSN_PID_TABLE_68 ((volatile uint32_t *)0xfe442520)
#define P_TSN_PID_TABLE_69 ((volatile uint32_t *)0xfe442524)
#define P_TSN_PID_TABLE_70 ((volatile uint32_t *)0xfe442528)
#define P_TSN_PID_TABLE_71 ((volatile uint32_t *)0xfe44252c)
#define P_TSN_PID_TABLE_72 ((volatile uint32_t *)0xfe442530)
#define P_TSN_PID_TABLE_73 ((volatile uint32_t *)0xfe442534)
#define P_TSN_PID_TABLE_74 ((volatile uint32_t *)0xfe442538)
#define P_TSN_PID_TABLE_75 ((volatile uint32_t *)0xfe44253c)
#define P_TSN_PID_TABLE_76 ((volatile uint32_t *)0xfe442540)
#define P_TSN_PID_TABLE_77 ((volatile uint32_t *)0xfe442544)
#define P_TSN_PID_TABLE_78 ((volatile uint32_t *)0xfe442548)
#define P_TSN_PID_TABLE_79 ((volatile uint32_t *)0xfe44254c)
#define P_TSN_PID_TABLE_80 ((volatile uint32_t *)0xfe442550)
#define P_TSN_PID_TABLE_81 ((volatile uint32_t *)0xfe442554)
#define P_TSN_PID_TABLE_82 ((volatile uint32_t *)0xfe442558)
#define P_TSN_PID_TABLE_83 ((volatile uint32_t *)0xfe44255c)
#define P_TSN_PID_TABLE_84 ((volatile uint32_t *)0xfe442560)
#define P_TSN_PID_TABLE_85 ((volatile uint32_t *)0xfe442564)
#define P_TSN_PID_TABLE_86 ((volatile uint32_t *)0xfe442568)
#define P_TSN_PID_TABLE_87 ((volatile uint32_t *)0xfe44256c)
#define P_TSN_PID_TABLE_88 ((volatile uint32_t *)0xfe442570)
#define P_TSN_PID_TABLE_89 ((volatile uint32_t *)0xfe442574)
#define P_TSN_PID_TABLE_90 ((volatile uint32_t *)0xfe442578)
#define P_TSN_PID_TABLE_91 ((volatile uint32_t *)0xfe44257c)
#define P_TSN_PID_TABLE_92 ((volatile uint32_t *)0xfe442580)
#define P_TSN_PID_TABLE_93 ((volatile uint32_t *)0xfe442584)
#define P_TSN_PID_TABLE_94 ((volatile uint32_t *)0xfe442588)
#define P_TSN_PID_TABLE_95 ((volatile uint32_t *)0xfe44258c)
#define P_TSN_PID_TABLE_96 ((volatile uint32_t *)0xfe442590)
#define P_TSN_PID_TABLE_97 ((volatile uint32_t *)0xfe442594)
#define P_TSN_PID_TABLE_98 ((volatile uint32_t *)0xfe442598)
#define P_TSN_PID_TABLE_99 ((volatile uint32_t *)0xfe44259c)
#define P_TSN_PID_TABLE_100 ((volatile uint32_t *)0xfe4425a0)
#define P_TSN_PID_TABLE_101 ((volatile uint32_t *)0xfe4425a4)
#define P_TSN_PID_TABLE_102 ((volatile uint32_t *)0xfe4425a8)
#define P_TSN_PID_TABLE_103 ((volatile uint32_t *)0xfe4425ac)
#define P_TSN_PID_TABLE_104 ((volatile uint32_t *)0xfe4425b0)
#define P_TSN_PID_TABLE_105 ((volatile uint32_t *)0xfe4425b4)
#define P_TSN_PID_TABLE_106 ((volatile uint32_t *)0xfe4425b8)
#define P_TSN_PID_TABLE_107 ((volatile uint32_t *)0xfe4425bc)
#define P_TSN_PID_TABLE_108 ((volatile uint32_t *)0xfe4425c0)
#define P_TSN_PID_TABLE_109 ((volatile uint32_t *)0xfe4425c4)
#define P_TSN_PID_TABLE_110 ((volatile uint32_t *)0xfe4425c8)
#define P_TSN_PID_TABLE_111 ((volatile uint32_t *)0xfe4425cc)
#define P_TSN_PID_TABLE_112 ((volatile uint32_t *)0xfe4425d0)
#define P_TSN_PID_TABLE_113 ((volatile uint32_t *)0xfe4425d4)
#define P_TSN_PID_TABLE_114 ((volatile uint32_t *)0xfe4425d8)
#define P_TSN_PID_TABLE_115 ((volatile uint32_t *)0xfe4425dc)
#define P_TSN_PID_TABLE_116 ((volatile uint32_t *)0xfe4425e0)
#define P_TSN_PID_TABLE_117 ((volatile uint32_t *)0xfe4425e4)
#define P_TSN_PID_TABLE_118 ((volatile uint32_t *)0xfe4425e8)
#define P_TSN_PID_TABLE_119 ((volatile uint32_t *)0xfe4425ec)
#define P_TSN_PID_TABLE_120 ((volatile uint32_t *)0xfe4425f0)
#define P_TSN_PID_TABLE_121 ((volatile uint32_t *)0xfe4425f4)
#define P_TSN_PID_TABLE_122 ((volatile uint32_t *)0xfe4425f8)
#define P_TSN_PID_TABLE_123 ((volatile uint32_t *)0xfe4425fc)
#define P_TSN_PID_TABLE_124 ((volatile uint32_t *)0xfe442600)
#define P_TSN_PID_TABLE_125 ((volatile uint32_t *)0xfe442604)
#define P_TSN_PID_TABLE_126 ((volatile uint32_t *)0xfe442608)
#define P_TSN_PID_TABLE_127 ((volatile uint32_t *)0xfe44260c)
//========================================================================
// RNG REG - Registers
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe440700
// -----------------------------------------------
#define P_RNG_TEE_READY ((volatile uint32_t *)0xfe440700)
#define P_RNG_TEE_LOCK ((volatile uint32_t *)0xfe440704)
#define P_RNG_TEE_CFG ((volatile uint32_t *)0xfe440708)
#define P_RNG_TEE_NIST_OUT ((volatile uint32_t *)0xfe44070c)
#define P_RNG_TEE_OUT0 ((volatile uint32_t *)0xfe440710)
#define P_RNG_TEE_OUT1 ((volatile uint32_t *)0xfe440714)
#define P_RNG_TEE_OUT2 ((volatile uint32_t *)0xfe440718)
#define P_RNG_TEE_OUT3 ((volatile uint32_t *)0xfe44071c)
#define P_RNG_CFG_RING ((volatile uint32_t *)0xfe440740)
#define P_RNG_CFG_RESEED ((volatile uint32_t *)0xfe440744)
#define P_RNG_CFG_HEALTH ((volatile uint32_t *)0xfe440748)
#define P_RNG_CFG_MISC ((volatile uint32_t *)0xfe44074c)
#define P_RNG_REE_READY ((volatile uint32_t *)0xfe440780)
#define P_RNG_REE_DEBUG ((volatile uint32_t *)0xfe440784)
#define P_RNG_REE_CFG ((volatile uint32_t *)0xfe440788)
#define P_RNG_REE_OUT0 ((volatile uint32_t *)0xfe440790)
#define P_RNG_REE_OUT1 ((volatile uint32_t *)0xfe440794)
#define P_RNG_REE_OUT2 ((volatile uint32_t *)0xfe440798)
#define P_RNG_REE_OUT3 ((volatile uint32_t *)0xfe44079c)
//========================================================================
// OTP REG - Registers
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe440000
// -----------------------------------------------
#define P_OTP_TEE_RDY ((volatile uint32_t *)0xfe440000)
#define P_OTP_TEE_DEBUG ((volatile uint32_t *)0xfe440004)
#define P_OTP_TEE_CFG ((volatile uint32_t *)0xfe440008)
#define P_OTP_TEE_WR_DAT ((volatile uint32_t *)0xfe440010)
#define P_OTP_TEE_RD_DAT ((volatile uint32_t *)0xfe440020)
#define P_OTP_LIC_A ((volatile uint32_t *)0xfe440040)
#define P_OTP_AML_ID_L ((volatile uint32_t *)0xfe440080)
#define P_OTP_AML_ID_H ((volatile uint32_t *)0xfe440084)
#define P_OTP_ACGK_ID_L ((volatile uint32_t *)0xfe440088)
#define P_OTP_ACGK_ID_H ((volatile uint32_t *)0xfe44008c)
#define P_OTP_DVGK_ID_L ((volatile uint32_t *)0xfe440090)
#define P_OTP_DVGK_ID_H ((volatile uint32_t *)0xfe440094)
#define P_OTP_DVUK_ID_L ((volatile uint32_t *)0xfe440098)
#define P_OTP_DVUK_ID_H ((volatile uint32_t *)0xfe44009c)
#define P_OTP_DGPK_ID_L ((volatile uint32_t *)0xfe4400a0)
#define P_OTP_DGPK_ID_H ((volatile uint32_t *)0xfe4400a4)
#define P_OTP_SECPU_ID_L ((volatile uint32_t *)0xfe4400a8)
#define P_OTP_SECPU_ID_H ((volatile uint32_t *)0xfe4400ac)
#define P_OTP_ETSI012_ID_L ((volatile uint32_t *)0xfe4400b0)
#define P_OTP_ETSI012_ID_H ((volatile uint32_t *)0xfe4400b4)
#define P_OTP_ETSI3_ID_L ((volatile uint32_t *)0xfe4400b8)
#define P_OTP_ETSI3_ID_H ((volatile uint32_t *)0xfe4400bc)
#define P_OTP_MSR_ID_L ((volatile uint32_t *)0xfe4400c0)
#define P_OTP_MSR_ID_H ((volatile uint32_t *)0xfe4400c4)
#define P_OTP_VO_ID_L ((volatile uint32_t *)0xfe4400c8)
#define P_OTP_VO_ID_H ((volatile uint32_t *)0xfe4400cc)
#define P_OTP_NUID_ID_L ((volatile uint32_t *)0xfe4400d0)
#define P_OTP_NUID_ID_H ((volatile uint32_t *)0xfe4400d4)
#define P_OTP_CONAX_ID_L ((volatile uint32_t *)0xfe4400d8)
#define P_OTP_CONAX_ID_H ((volatile uint32_t *)0xfe4400dc)
#define P_OTP_NSK_ID_L ((volatile uint32_t *)0xfe4400e0)
#define P_OTP_NSK_ID_H ((volatile uint32_t *)0xfe4400e4)
#define P_OTP_REE_RDY ((volatile uint32_t *)0xfe440100)
#define P_OTP_REE_DEBUG ((volatile uint32_t *)0xfe440104)
#define P_OTP_REE_CFG ((volatile uint32_t *)0xfe440108)
#define P_OTP_MRK_CHKNUM ((volatile uint32_t *)0xfe44010c)
#define P_OTP_REE_RD_DAT ((volatile uint32_t *)0xfe440120)
//========================================================================
// KL REG - Registers
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe440200
// -----------------------------------------------
#define P_MKL_TEE_RDY ((volatile uint32_t *)0xfe440200)
#define P_MKL_TEE_DEBUG ((volatile uint32_t *)0xfe440204)
#define P_MKL_TEE_CFG ((volatile uint32_t *)0xfe440208)
#define P_MKL_TEE_CMD ((volatile uint32_t *)0xfe44020c)
#define P_MKL_TEE_EK ((volatile uint32_t *)0xfe440210)
#define P_MKL_TEE_CR_0 ((volatile uint32_t *)0xfe440270)
#define P_MKL_TEE_CR_1 ((volatile uint32_t *)0xfe440274)
#define P_MKL_TEE_CR_2 ((volatile uint32_t *)0xfe440278)
#define P_MKL_TEE_CR_3 ((volatile uint32_t *)0xfe44027c)
#define P_MKL_REE_RDY ((volatile uint32_t *)0xfe440280)
#define P_MKL_REE_DEBUG ((volatile uint32_t *)0xfe440284)
#define P_MKL_REE_CFG ((volatile uint32_t *)0xfe440288)
#define P_MKL_REE_CMD ((volatile uint32_t *)0xfe44028c)
#define P_MKL_REE_EK ((volatile uint32_t *)0xfe440290)
//========================================================================
// DMA REG - Registers
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe440400
// -----------------------------------------------
#define P_DMA_CORE_DSC_0 ((volatile uint32_t *)0xfe440400)
#define P_DMA_CORE_DSC_1 ((volatile uint32_t *)0xfe440404)
#define P_DMA_CORE_DSC_2 ((volatile uint32_t *)0xfe440408)
#define P_DMA_CORE_DSC_3 ((volatile uint32_t *)0xfe44040c)
#define P_DMA_CORE_DSC_4 ((volatile uint32_t *)0xfe440410)
#define P_DMA_CORE_DSC_5 ((volatile uint32_t *)0xfe440414)
#define P_DMA_CORE_IRQ_STS_0 ((volatile uint32_t *)0xfe440420)
#define P_DMA_CORE_IRQ_STS_1 ((volatile uint32_t *)0xfe440424)
#define P_DMA_CORE_IRQ_STS_2 ((volatile uint32_t *)0xfe440428)
#define P_DMA_CORE_IRQ_STS_3 ((volatile uint32_t *)0xfe44042c)
#define P_DMA_CORE_IRQ_STS_4 ((volatile uint32_t *)0xfe440430)
#define P_DMA_CORE_IRQ_STS_5 ((volatile uint32_t *)0xfe440434)
#define P_DMA_CORE_CFG_REG ((volatile uint32_t *)0xfe440440)
#define P_DMA_CORE_CFG_SEC_LSB ((volatile uint32_t *)0xfe440444)
#define P_DMA_CORE_CFG_SEC_MSB ((volatile uint32_t *)0xfe440448)
//========================================================================
// KT REG - Registers
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe440500
// -----------------------------------------------
#define P_KT_TEE_RDY ((volatile uint32_t *)0xfe440500)
#define P_KT_TEE_RDY2 ((volatile uint32_t *)0xfe440504)
#define P_KT_TEE_CFG ((volatile uint32_t *)0xfe440508)
#define P_KT_TEE_STS ((volatile uint32_t *)0xfe44050c)
#define P_KT_TEE_KEY0 ((volatile uint32_t *)0xfe440510)
#define P_KT_TEE_KEY1 ((volatile uint32_t *)0xfe440514)
#define P_KT_TEE_KEY2 ((volatile uint32_t *)0xfe440518)
#define P_KT_TEE_KEY3 ((volatile uint32_t *)0xfe44051c)
#define P_KT_REE_RDY ((volatile uint32_t *)0xfe440580)
#define P_KT_REE_RDY2 ((volatile uint32_t *)0xfe440584)
#define P_KT_REE_CFG ((volatile uint32_t *)0xfe440588)
#define P_KT_REE_STS ((volatile uint32_t *)0xfe44058c)
#define P_KT_REE_KEY0 ((volatile uint32_t *)0xfe440590)
#define P_KT_REE_KEY1 ((volatile uint32_t *)0xfe440594)
#define P_KT_REE_KEY2 ((volatile uint32_t *)0xfe440598)
#define P_KT_REE_KEY3 ((volatile uint32_t *)0xfe44059c)
//========================================================================
// CERT REG - Registers
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe440600
// -----------------------------------------------
//========================================================================
// SP REG - Registers
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe441000
// -----------------------------------------------
// ree domian
#define P_REE_SCPU2REE_CSR_ADDR ((volatile uint32_t *)0xfe441c00)
#define P_REE_SCPU2REE_DATA_ST_ADDR ((volatile uint32_t *)0xfe441e00)
#define P_REE_SCPU2REE_DATA_ED_ADDR ((volatile uint32_t *)0xfe441e7c)
#define P_REE_REE2SCPU_CSR_ADDR ((volatile uint32_t *)0xfe441800)
#define P_REE_REE2SCPU_DATA_ST_ADDR ((volatile uint32_t *)0xfe441a00)
#define P_REE_REE2SCPU_DATA_ED_ADDR ((volatile uint32_t *)0xfe441a7c)
// tee domian                                                                       )
#define P_TEE_SCPU2TEE_CSR_ADDR ((volatile uint32_t *)0xfe441400)
#define P_TEE_SCPU2TEE_DATA_ST_ADDR ((volatile uint32_t *)0xfe441600)
#define P_TEE_SCPU2TEE_DATA_ED_ADDR ((volatile uint32_t *)0xfe44167c)
#define P_TEE_TEE2SCPU_CSR_ADDR ((volatile uint32_t *)0xfe441000)
#define P_TEE_TEE2SCPU_DATA_ST_ADDR ((volatile uint32_t *)0xfe441200)
#define P_TEE_TEE2SCPU_DATA_ED_ADDR ((volatile uint32_t *)0xfe44127c)
//========================================================================
// NSK REG - Registers
//========================================================================
// -----------------------------------------------
// REG_BASE:  REGISTER_BASE_ADDR = 0xfe450000
// -----------------------------------------------
//
// Closing file:  REG_LIST_SECURITY_RTL.h
//
//`include "REG_LIST_DEMUX_RTL.h"
// synopsys translate_off
// synopsys translate_on
//
// Closing file:  ./REG_LIST_RTL.h
//

#endif // P_REGISTER_H