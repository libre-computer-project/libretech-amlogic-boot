
/*
 * Copyright (C) 2015 Amlogic, Inc. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/

#ifndef __BOARD_CFG_H__
#define __BOARD_CFG_H__

#include <asm/arch/cpu.h>
#include <amlogic/base_env.h>

/*
 * platform power init config
 */

#define AML_VCCK_INIT_VOLTAGE	  1009	    //VCCK power up voltage
#define AML_VDDEE_INIT_VOLTAGE    840       // VDDEE power up voltage
/*Distinguish whether to use efuse to adjust vddee*/
#define CONFIG_PDVFS_ENABLE

/* AVB */
#define CONFIG_AML_AVB2_ANTIROLLBACK 1
#define CONFIG_AVB_VERIFY 1
#define CONFIG_SUPPORT_EMMC_RPMB 1
#define CONFIG_AML_DEV_ID 1

/* SMP Definitions */
#define CPU_RELEASE_ADDR		secondary_boot_func

/* Bootloader Control Block function
   That is used for recovery and the bootloader to talk to each other
  */
#if 0
#define CONFIG_BOOTLOADER_CONTROL_BLOCK
#endif

/* Serial config */
#define CONFIG_CONS_INDEX 2
#define CONFIG_BAUDRATE  115200

/*hign console baudrate*/
#define CONFIG_HIGH_CONSOLE_BAUD			1

/* Enable ir remote wake up for bl30 */
#define AML_IR_REMOTE_POWER_UP_KEY_VAL1 0xef10fe01 //amlogic tv ir --- power
#define AML_IR_REMOTE_POWER_UP_KEY_VAL2 0XBB44FB04 //amlogic tv ir --- ch+
#define AML_IR_REMOTE_POWER_UP_KEY_VAL3 0xF20DFE01 //amlogic tv ir --- ch-
#define AML_IR_REMOTE_POWER_UP_KEY_VAL4 0XBA45BD02 //amlogic small ir--- power
#define AML_IR_REMOTE_POWER_UP_KEY_VAL5 0xe51afb04
#define AML_IR_REMOTE_POWER_UP_KEY_VAL6 0xFFFFFFFF
#define AML_IR_REMOTE_POWER_UP_KEY_VAL7 0xFFFFFFFF
#define AML_IR_REMOTE_POWER_UP_KEY_VAL8 0xFFFFFFFF
#define AML_IR_REMOTE_POWER_UP_KEY_VAL9 0xFFFFFFFF

/*config the default parameters for adc power key*/
#define AML_ADC_POWER_KEY_CHAN   2  /*channel range: 0-7*/
#define AML_ADC_POWER_KEY_VAL    0  /*sample value range: 0-1023*/

//#define CONFIG_BOOTLOADER_CONTROL_BLOCK

//USB_POWEROFF
#define AMLOGIC_USB_POWER

/* args/envs */
#define CONFIG_SYS_MAXARGS  64
#define CONFIG_EXTRA_ENV_SETTINGS \
	CONFIG_EXTRA_ENV_SETTINGS_BASE \
		"silent=1\0"\
		"systemsuspend_switch=1\0"\
		"ddr_resume=0\0"\
		"otg_device=1\0" \
		"panel_type=lvds_1\0" \
		"lcd_ctrl=0x00000000\0" \
		"lcd_debug=0x00000000\0" \
		"outputmode=1080p60hz\0" \
		"hdmimode=none\0" \
		"connector_type=LVDS-A\0" \
		"cvbsmode=576cvbs\0" \
		"vout_init=disable\0" \
		"model_name=FHD2HDMI\0" \
		"gamma=0\0" \
		"display_width=1920\0" \
		"display_height=1080\0" \
		"display_bpp=16\0" \
		"display_color_index=16\0" \
		"display_layer=osd0\0" \
		"display_color_fg=0xffff\0" \
		"display_color_bg=0\0" \
		"dtb_mem_addr=0x01000000\0" \
		"fb_width=1920\0" \
		"fb_height=1080\0" \
		"frac_rate_policy=1\0" \
		"usb_burning=" CONFIG_USB_TOOL_ENTRY "\0" \
		"fdt_high=0x20000000\0"\
		"sdcburncfg=aml_sdc_burn.ini\0"\
		"EnableSelinux=enforcing\0" \
		"recovery_part=recovery\0"\
		"lock=10101000\0"\
		"cvbs_drv=0\0"\
		"osd_reverse=0\0"\
		"video_reverse=0\0"\
	"board=t963d4\0"\
		"upgrade_key_flag=2\0"\
		"suspend=off\0"\
		"powermode=on\0"\
		"ffv_wake=off\0"\
		"ffv_freeze=off\0"\
		"edid_14_dir=/odm/etc/tvconfig/hdmi/port1_14.bin\0" \
		"edid_20_dir=/odm/etc/tvconfig/hdmi/port1_20.bin\0" \
		"edid_select=0\0" \
		"port_map=0x4321\0" \
		"cec_fun=0x2F\0" \
		"logic_addr=0x0\0" \
		"cec_ac_wakeup=1\0" \
		"check_connector_type="\
		"setenv bootconfig ${bootconfig} androidboot.connector_type=${connector_type};"\
		"\0"\
        "initargs="\
		"init=/init " CONFIG_KNL_LOG_LEVEL "console=ttyS0,115200 "\
		"no_console_suspend earlycon=aml-uart,0xfe07a000 scramble_reg=0xfe02e030 "\
		"ramoops.pstore_en=1 ramoops.record_size=0x8000 ramoops.console_size=0x4000 "\
		"loop.max_part=4 scsi_mod.scan=async xhci_hcd.quirks=0x800000 "\
		"loglevel=4 isolcpus=4 "\
            "\0"\
        "upgrade_check="\
			"run upgrade_check_base;"\
			"\0"\
	"storeargs="\
		"get_bootloaderversion;" \
		"run storeargs_base;"\
		"setenv bootargs ${bootargs} powermode=${powermode} "\
		"lcd_ctrl=${lcd_ctrl} lcd_debug=${lcd_debug} "\
		"outputmode=${outputmode} gamma=${gamma};"\
		"run check_connector_type; " \
		"run cmdline_keys;"\
		"\0"\
	"cec_init="\
		"echo cec_ac_wakeup=${cec_ac_wakeup}; "\
		"if test ${cec_ac_wakeup} = 1; then "\
			"cec ${logic_addr} ${cec_fun}; "\
			"if test ${edid_select} = 1111; then "\
				"hdmirx init ${port_map} ${edid_20_dir}; "\
			"else "\
				"hdmirx init ${port_map} ${edid_14_dir}; "\
			"fi;"\
		"fi;"\
		"\0"\
	"ffv_freeze_action="\
		"run cec_init;"\
		"setenv ffv_freeze on;"\
		"setenv bootargs ${bootargs} ffv_freeze=on"\
		"\0"\
	"cold_boot_normal_check="\
		"setenv bootargs ${bootargs} ffv_freeze=off; "\
		/*"run try_auto_burn;uboot wake up "*/\
		"if test ${powermode} = on; then "\
			/*"run try_auto_burn; "*/\
		"else if test ${powermode} = standby; then "\
			"run cec_init;"\
			"if test ${systemsuspend_switch} = 0;then systemoff; fi;"\
		"else if test ${powermode} = last; then "\
			"echo suspend=${suspend}; "\
			"if test ${suspend} = off; then "\
				/*"run try_auto_burn; "*/\
			"else if test ${suspend} = on; then "\
				"run cec_init;"\
				"if test ${systemsuspend_switch} = 0;then systemoff; fi;"\
			"else if test ${suspend} = shutdown; then "\
				"run cec_init;"\
				"if test ${systemsuspend_switch} = 0;then systemoff; fi;"\
			"fi; fi; fi; "\
		"fi; fi; fi; "\
		"\0"\
	"switch_bootmode="\
		"setenv ffv_freeze off;"\
		"echo reboot_mode : ${reboot_mode};"\
		"if test ${reboot_mode} = factory_reset; then "\
				"run recovery_from_flash;"\
		"else if test ${reboot_mode} = update; then "\
				"run update;"\
		"else if test ${reboot_mode} = quiescent; then "\
				"setenv bootconfig ${bootconfig} androidboot.quiescent=1;"\
		"else if test ${reboot_mode} = recovery_quiescent; then "\
				"setenv bootconfig ${bootconfig} androidboot.quiescent=1;"\
				"run recovery_from_flash;"\
		"else if test ${reboot_mode} = cold_boot; then "\
			"echo cold boot: ffv_wake=${ffv_wake} "\
			"powermode=${powermode} suspend=${suspend};"\
			"if test ${ffv_wake} = on; then "\
				"if test ${powermode} = on; then "\
					"setenv bootargs ${bootargs} ffv_freeze=off; "\
				"else if test ${powermode} = standby; then "\
					"run ffv_freeze_action; "\
				"else if test ${powermode} = last; then "\
					"if test ${suspend} = off; then "\
						"setenv bootargs ${bootargs} ffv_freeze=off; "\
					"else if test ${suspend} = on; then "\
						"run ffv_freeze_action; "\
					"else if test ${suspend} = shutdown; then "\
						"run ffv_freeze_action; "\
					"fi; fi; fi; "\
				"fi; fi; fi; "\
			"else "\
				"run cold_boot_normal_check;"\
			"fi; "\
		"else if test ${reboot_mode} = ffv_reboot; then "\
			"if test ${ffv_wake} = on; then "\
				"run ffv_freeze_action; "\
			"fi; "\
		"else if test ${reboot_mode} = fastboot; then "\
			"fastboot 1;"\
		"fi;fi;fi;fi;fi;fi;fi;"\
		"\0" \
	"reset_suspend="\
		"if test ${ffv_freeze} != on; then "\
			"if test ${suspend} = on || test ${suspend} = shutdown; then "\
				"setenv suspend off;"\
				"saveenv;"\
			"fi;"\
		"fi;"\
		"\0" \
		"storeboot="\
			"run storeboot_base;"\
			"\0"\
		"update="\
			"run update_base;"\
			"\0"\
		"enter_fastboot="\
			"fastboot 1;"\
			"\0"\
		"recovery_from_fat_dev="\
			"run recovery_from_fat_dev_base;"\
			"\0"\
		"recovery_from_udisk="\
			"run recovery_from_udisk_base;"\
			"\0"\
		"recovery_from_sdcard="\
			"run recovery_from_sdcard_base;"\
			"\0"\
		"recovery_from_flash="\
			"run recovery_from_flash_base;"\
			"\0"\
		"bcb_cmd="\
			"run bcb_cmd_base;"\
			"\0"\
		"load_bmp_logo="\
			"run load_bmp_logo_base;"\
			"\0"\
	"init_display="\
		"get_rebootmode;"\
		"echo reboot_mode:::: ${reboot_mode};"\
		"if test ${reboot_mode} = quiescent; then "\
			"setenv dolby_status 0;"\
			"setenv dolby_vision_on 0;"\
			"setenv bootconfig ${bootconfig} androidboot.quiescent=1;"\
			"osd open;osd clear;"\
		"else if test ${reboot_mode} = recovery_quiescent; then "\
			"setenv dolby_status 0;"\
			"setenv dolby_vision_on 0;"\
			"setenv bootconfig ${bootconfig} androidboot.quiescent=1;"\
			"osd open;osd clear;"\
		"else "\
			"osd open;osd clear;run load_bmp_logo;bmp scale;vout output ${outputmode};"\
		"fi;fi;"\
		"\0"\
	"check_display="\
		"echo check_display reboot_mode : ${reboot_mode} ,powermode : ${powermode};"\
		"if test ${reboot_mode} = ffv_reboot; then "\
			"if test ${ffv_wake} = on; then "\
				"echo ffv reboot no display; "\
			"else "\
				"run init_display; "\
			"fi; "\
		"else if test ${reboot_mode} = cold_boot; then "\
			"if test ${powermode} = standby; then "\
				"setenv ddr_resume 1;"\
			"else if test ${powermode} = last; then "\
				"if test ${suspend} != off; then "\
					"setenv ddr_resume 1;"\
				"fi;"\
			"fi;fi;"\
			"if test ${powermode} = on; then "\
				"echo powermode : ${powermode} ,need to init_display; "\
				"run init_display; "\
			"else if test ${powermode} = standby; then "\
				"echo reboot: ${reboot_mode} suspend: ${suspend};"\
				"run init_display; "\
			"else if test ${powermode} = last; then "\
				"if test ${suspend} = off; then "\
					"echo suspend : ${suspend} ,need to init_display; "\
					"run init_display; "\
				"fi; "\
			"fi;fi;fi; "\
		"else "\
			"echo reboot_mode is normal;"\
			"run init_display; "\
		"fi;fi; "\
		"\0"\
		"cmdline_keys="\
			"setenv usid t963d4${cpu_id};"\
			"run cmdline_keys_base;"\
			"\0"\
		"upgrade_key="\
			"run upgrade_key_base;"\
			"echo usr key;"\
			"\0"\

#define CONFIG_PREBOOT  \
            "run upgrade_check;"\
	/*"run init_display;"*/\
	"get_rebootmode;"\
	"run check_display;"\
	"run storeargs;"\
            "run upgrade_key;" \
            "bcb uboot-command;" \
	"run switch_bootmode;" \
	"run reset_suspend;"

//#define CONFIG_ENV_IS_NOWHERE  1
#define CONFIG_ENV_SIZE   (64*1024)
#define CONFIG_FIT 1
#define CONFIG_OF_LIBFDT 1
#define CONFIG_ANDROID_BOOT_IMAGE 1
#define CONFIG_SYS_BOOTM_LEN (64<<20) /* Increase max gunzip size*/

/* ATTENTION */
/* DDR configs move to board/amlogic/[board]/firmware/timing.c */

/* running in sram */
//#define UBOOT_RUN_IN_SRAM
#ifdef UBOOT_RUN_IN_SRAM
#define CONFIG_SYS_INIT_SP_ADDR				(0x00300000)
/* Size of malloc() pool */
#define CONFIG_SYS_MALLOC_LEN				(256*1024)
#else
#define CONFIG_SYS_INIT_SP_ADDR				(0x00300000)
#define CONFIG_SYS_MALLOC_LEN				(112 * 1024 * 1024)
#endif

//#define CONFIG_NR_DRAM_BANKS			1
/* ddr functions */
#define DDR_FULL_TEST            0 //0:disable, 1:enable. ddr full test
#define DDR_LOW_POWER            0 //0:disable, 1:enable. ddr clk gate for lp
#define DDR_ZQ_PD                0 //0:disable, 1:enable. ddr zq power down
#define DDR_USE_EXT_VREF         0 //0:disable, 1:enable. ddr use external vref
#define DDR4_TIMING_TEST         0 //0:disable, 1:enable. ddr4 timing test function
#define DDR_PLL_BYPASS           0 //0:disable, 1:enable. ddr pll bypass function

/* storage: emmc/nand/sd */
#define CONFIG_ENV_OVERWRITE
/* #define 	CONFIG_CMD_SAVEENV */
/* fixme, need fix*/

#if (defined(CONFIG_ENV_IS_IN_AMLNAND) || defined(CONFIG_ENV_IS_IN_MMC)) && defined(CONFIG_STORE_COMPATIBLE)
#error env in amlnand/mmc already be compatible;
#endif

/*
*				storage
*		|---------|---------|
*		|					|
*		emmc<--Compatible-->nand
*					|-------|-------|
*					|		|
*					MTD<-Exclusive->NFTL
*					|
*			|***************|***************|
*			slc-nand	SPI-nand	SPI-nor
*			(raw nand)
*/
/* axg only support slc nand */
/* swither for mtd nand which is for slc only. */


#if defined(CONFIG_AML_NAND) && defined(CONFIG_MESON_NFC)
#error CONFIG_AML_NAND/CONFIG_MESON_NFC can not support at the sametime;
#endif

#if (defined(CONFIG_AML_NAND) || defined(CONFIG_MESON_NFC)) && defined(CONFIG_MESON_FBOOT)
#error CONFIG_AML_NAND/CONFIG_MESON_NFC CONFIG _MESON_FBOOT can not support at the sametime;
#endif

#if defined(CONFIG_SPI_NAND) && defined(CONFIG_MTD_SPI_NAND) && defined(CONFIG_MESON_NFC)
#error CONFIG_SPI_NAND/CONFIG_MTD_SPI_NAND/CONFIG_MESON_NFC can not support at the sametime;
#endif

/* #define		CONFIG_AML_SD_EMMC 1 */
#ifdef		CONFIG_AML_SD_EMMC
	#define 	CONFIG_GENERIC_MMC 1
	#define 	CONFIG_CMD_MMC 1
	#define CONFIG_CMD_GPT 1
	#define	CONFIG_SYS_MMC_ENV_DEV 1
	#define CONFIG_EMMC_DDR52_EN 0
	#define CONFIG_EMMC_DDR52_CLK 35000000
#endif
#define		CONFIG_PARTITIONS 1
#if 0
#define 	CONFIG_SYS_NO_FLASH  1
#endif

#if defined CONFIG_MESON_NFC || defined CONFIG_SPI_NAND || defined CONFIG_MTD_SPI_NAND
	#define CONFIG_SYS_MAX_NAND_DEVICE  2
#endif

/* vpu */
#define AML_VPU_CLK_LEVEL_DFT 7

/* LCD */

/* osd */
#define OSD_SCALE_ENABLE
#define AML_OSD_HIGH_VERSION
#define AML_T7_DISPLAY

/* USB
 * Enable CONFIG_MUSB_HCD for Host functionalities MSC, keyboard
 * Enable CONFIG_MUSB_UDD for Device functionalities.
 */
/* #define CONFIG_MUSB_UDC		1 */
/* #define CONFIG_CMD_USB 1 */

#define USB_PHY2_PLL_PARAMETER_1	0x09400414
#define USB_PHY2_PLL_PARAMETER_2	0x927e0000
#define USB_PHY2_PLL_PARAMETER_3	0xAC5F49E5

#define USB_G12x_PHY_PLL_SETTING_1	(0xfe18)
#define USB_G12x_PHY_PLL_SETTING_2	(0xfff)
#define USB_G12x_PHY_PLL_SETTING_3	(0x78000)
#define USB_G12x_PHY_PLL_SETTING_4	(0xe0004)
#define USB_G12x_PHY_PLL_SETTING_5	(0xe000c)

#define AML_TXLX_USB        1
#define AML_USB_M31_PHY		1
#define AML_USB_V2             1
#define USB_GENERAL_BIT         3
#define USB_PHY21_BIT           4

/* UBOOT fastboot config */


/* UBOOT Factory usb/sdcard burning config */

/* net */
/* #define CONFIG_CMD_NET   1 */
#define CONFIG_ETH_DESIGNWARE
#if defined(CONFIG_CMD_NET)
	#define CONFIG_DESIGNWARE_ETH 1
	#define CONFIG_PHYLIB	1
	#define CONFIG_NET_MULTI 1
	#define CONFIG_CMD_PING 1
	#define CONFIG_CMD_DHCP 1
	#define CONFIG_CMD_RARP 1
	#define CONFIG_HOSTNAME        "arm_gxbb"
#if 0
	#define CONFIG_RANDOM_ETHADDR  1				   /* use random eth addr, or default */
#endif
	#define CONFIG_ETHADDR         00:15:18:01:81:31   /* Ethernet address */
	#define CONFIG_IPADDR          10.18.9.97          /* Our ip address */
	#define CONFIG_GATEWAYIP       10.18.9.1           /* Our getway ip address */
	#define CONFIG_SERVERIP        10.18.9.113         /* Tftp server ip address */
	#define CONFIG_NETMASK         255.255.255.0
#endif /* (CONFIG_CMD_NET) */

#define MAC_ADDR_NEW  1

/* other devices */
#define CONFIG_SHA1 1
#define CONFIG_MD5 1

/* commands */
/* #define CONFIG_CMD_PLLTEST 1 */

/*file system*/
#define CONFIG_DOS_PARTITION 1
#define CONFIG_EFI_PARTITION 1
/* #define CONFIG_MMC 1 */
#define CONFIG_FS_FAT 1
#define CONFIG_FS_EXT4 1
#define CONFIG_LZO 1

#define CONFIG_FAT_WRITE 1
#define CONFIG_AML_FACTORY_PROVISION 1

/* Cache Definitions */
/* #define CONFIG_SYS_DCACHE_OFF */
/* #define CONFIG_SYS_ICACHE_OFF */

/* other functions */
#define CONFIG_LIBAVB		1

/* define CONFIG_SYS_MEM_TOP_HIDE 8M space for free buffer */
#define CONFIG_SYS_MEM_TOP_HIDE		0x00800000

#define CONFIG_CPU_ARMV8

//use sha2 command
#define CONFIG_CMD_SHA2

//use startdsp command
#define CONFIG_CMD_STARTDSP

//use cache command
#define CONFIG_CMD_CACHE

//use hardware sha2
//#define CONFIG_AML_HW_SHA2

//Replace avb2 software SHA256 to utilize armce
#define CONFIG_AVB2_UBOOT_SHA256

#define CONFIG_MULTI_DTB    1

#define CONFIG_RX_RTERM		1

#define CONFIG_CMD_HDMIRX   1

#define CONFIG_CMD_CEC		1
/* support secure boot */
#define CONFIG_AML_SECURE_UBOOT   1

#if defined(CONFIG_AML_SECURE_UBOOT)

/* unify build for generate encrypted bootloader "u-boot.bin.encrypt" */
#define CONFIG_AML_CRYPTO_UBOOT   1
//#define CONFIG_AML_SIGNED_UBOOT   1
/* unify build for generate encrypted kernel image
   SRC : "board/amlogic/(board)/boot.img"
   DST : "fip/boot.img.encrypt" */
/* #define CONFIG_AML_CRYPTO_IMG       1 */

#endif /* CONFIG_AML_SECURE_UBOOT */

#define CONFIG_FIP_IMG_SUPPORT  1

/* config ramdump to debug kernel panic */
#define CONFIG_FULL_RAMDUMP

#define BL32_SHARE_MEM_SIZE  0x800000
#define CONFIG_AML_KASLR_SEED

#endif
