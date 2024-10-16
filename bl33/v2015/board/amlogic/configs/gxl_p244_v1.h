/* SPDX-License-Identifier: (GPL-2.0+ OR MIT) */
/*
 * board/amlogic/configs/gxl_p244_v1.h
 *
 * Copyright (C) 2020 Amlogic, Inc. All rights reserved.
 *
 */

#ifndef __GXL_P244_V1_H__
#define __GXL_P244_V1_H__

#ifndef __SUSPEND_FIRMWARE__
#include <asm/arch/cpu.h>
#endif		/* for compile problem of A53 and m3 */

#define CONFIG_SYS_GENERIC_BOARD  1
#ifndef __SUSPEND_FIRMWARE__
#ifndef CONFIG_AML_MESON
#warning "include warning"
#endif
#endif		/* for compile problem of A53 and m3 */

/*
 * platform power init config
 */
#define CONFIG_PLATFORM_POWER_INIT
#define CONFIG_VCCK_INIT_VOLTAGE	1120
#define CONFIG_VDDEE_INIT_VOLTAGE	1000		// voltage for power up
#define CONFIG_VDDEE_SLEEP_VOLTAGE	 850		// voltage for suspend

/* configs for CEC */
#define CONFIG_CEC_OSD_NAME		"Mbox"
#define CONFIG_CEC_WAKEUP
#define CONFIG_BT_WAKEUP
#define CONFIG_INSTABOOT
/* configs for dtb in boot.img */
//#define DTB_BIND_KERNEL
/*if use uart rcu,open it*/
#define CONFIG_BT_RCU_WAKEUP

/* SMP Definitions */
#define CPU_RELEASE_ADDR		secondary_boot_func

/* config saradc*/
#define CONFIG_CMD_SARADC 1

//#define CONFIG_AML_PRODUCT_MODE 1 //
#ifdef CONFIG_AML_PRODUCT_MODE
#define CONFIG_SILENT_CONSOLE
#define CONFIG_NO_FASTBOOT_FLASHING
#define CONFIG_USB_TOOL_ENTRY   "echo product mode"
#define CONFIG_KNL_LOG_LEVEL    "loglevel=1"
#else
#define CONFIG_USB_TOOL_ENTRY   "update 1500"
#define CONFIG_KNL_LOG_LEVEL    ""
#define CONFIG_CMD_BOOTI        1
#define CONFIG_CMD_MEMORY       1
#define CONFIG_CMD_JTAG	        1
#define CONFIG_CMD_AUTOSCRIPT   1
#define CONFIG_USB_STORAGE      1
#endif

/*if disable uboot console, enable it*/
//#define CONFIG_SILENT_CONSOLE
#ifdef CONFIG_SILENT_CONSOLE
#undef CONFIG_SILENT_CONSOLE_UPDATE_ON_RELOC
#endif

/*config irblaster*/
#define CONFIG_CMD_IRBLASTER 1

/* support ext4*/
#define CONFIG_CMD_EXT4 1

#define CONFIG_FAT_WRITE 1
#define CONFIG_AML_FACTORY_PROVISION 1

#define CONFIG_AML_WATERMARK 1

/* Bootloader Control Block function
   That is used for recovery and the bootloader to talk to each other
  */
#define CONFIG_BOOTLOADER_CONTROL_BLOCK

/*a/b update */
#define CONFIG_CMD_BOOTCTOL_AVB

/* Serial config */
#define CONFIG_CONS_INDEX 2
#define CONFIG_BAUDRATE  115200
#define CONFIG_AML_MESON_SERIAL   1
#define CONFIG_SERIAL_MULTI		1

//Enable ir remote wake up for bl30
//#define CONFIG_IR_REMOTE
//#define CONFIG_AML_IRDETECT_EARLY
#define CONFIG_IR_REMOTE_POWER_UP_KEY_CNT 4
#define CONFIG_IR_REMOTE_USE_PROTOCOL 0         // 0:nec  1:duokan  2:Toshiba 3:rca 4:rcmm
#define CONFIG_IR_REMOTE_POWER_UP_KEY_VAL1 0XE51AFB04 //amlogic tv ir --- power
#define CONFIG_IR_REMOTE_POWER_UP_KEY_VAL2 0Xffffffff //amlogic tv ir --- ch+
#define CONFIG_IR_REMOTE_POWER_UP_KEY_VAL3 0xffffffff //amlogic tv ir --- ch-
#define CONFIG_IR_REMOTE_POWER_UP_KEY_VAL4 0xBA45BD02

/*smc*/
#define CONFIG_ARM_SMCCC       1

#define CONFIG_IR_REMOTE_POWER_UP_KEY_VAL5 0xffffffff
/* args/envs */
#define CONFIG_SYS_MAXARGS  64
#define CONFIG_EXTRA_ENV_SETTINGS \
        "firstboot=0\0"\
        "upgrade_step=0\0"\
        "jtag=disable\0"\
        "loadaddr=1080000\0"\
        "outputmode=1080p60hz\0" \
        "hdmimode=1080p60hz\0" \
        "cvbsmode=576cvbs\0" \
        "display_width=1920\0" \
        "display_height=1080\0" \
        "display_bpp=16\0" \
        "display_color_index=16\0" \
        "display_layer=osd1\0" \
        "display_color_fg=0xffff\0" \
        "display_color_bg=0\0" \
        "dtb_mem_addr=0x1000000\0" \
        "fb_addr=0x3d800000\0" \
        "fb_width=1920\0" \
        "fb_height=1080\0" \
        "frac_rate_policy=1\0" \
        "hdr_policy=1\0" \
        "usb_burning=" CONFIG_USB_TOOL_ENTRY "\0" \
        "otg_device=1\0"\
        "fdt_high=0x20000000\0"\
	"lock=10101000\0"\
        "try_auto_burn=update 700 750;\0"\
        "sdcburncfg=aml_sdc_burn.ini\0"\
        "sdc_burning=sdc_burn ${sdcburncfg}\0"\
        "wipe_data=successful\0"\
        "wipe_cache=successful\0"\
        "EnableSelinux=enforcing\0"\
        "recovery_part=recovery\0"\
        "recovery_offset=0\0"\
        "cvbs_drv=0\0"\
        "active_slot=normal\0"\
        "page_trace=on\0"\
	"boot_flag=0\0"\
        "boot_part=boot\0"\
        "rpmb_state=0\0"\
        "Irq_check_en=0\0"\
        "reboot_mode_android=""normal""\0"\
        "fs_type=""rootfstype=ramfs""\0"\
        "colorattribute=444,8bit\0"\
        "initargs="\
            "init=/init " CONFIG_KNL_LOG_LEVEL " console=ttyS0,115200 no_console_suspend earlycon=aml_uart,0xc81004c0 ramoops.pstore_en=1 ramoops.record_size=0x8000 ramoops.console_size=0x4000 "\
            "\0"\
        "upgrade_check="\
            "echo upgrade_step=${upgrade_step}; "\
            "if itest ${upgrade_step} == 3; then "\
                "run init_display; run storeargs; run update;"\
            "else fi;"\
            "\0"\
    "storeargs="\
            "get_bootloaderversion;" \
            "setenv bootargs ${initargs} hdr_policy=${hdr_policy} otg_device=${otg_device} reboot_mode_android=${reboot_mode_android} androidboot.selinux=${EnableSelinux} logo=${display_layer},loaded,${fb_addr},${outputmode} maxcpus=${maxcpus} vout=${outputmode},enable hdmimode=${hdmimode} frac_rate_policy=${frac_rate_policy} cvbsmode=${cvbsmode} hdmitx=${cecconfig},${colorattribute} cvbsdrv=${cvbs_drv} irq_check_en=${Irq_check_en}  androidboot.firstboot=${firstboot} jtag=${jtag}; "\
	    "setenv bootargs ${bootargs} androidboot.veritymode=enforcing androidboot.hardware=amlogic androidboot.bootloader=${bootloader_version} androidboot.build.expect.baseband=N/A;"\
        "setenv bootargs ${bootargs} page_trace=${page_trace};" \
	    "setenv bootargs ${bootargs} androidboot.rpmb_state=${rpmb_state};"\
            "run cmdline_keys;"\
            "\0"\
        "switch_bootmode="\
            "get_rebootmode;"\
            "if test ${reboot_mode} = factory_reset; then "\
                    "setenv reboot_mode_android ""normal"";"\
                    "run storeargs;"\
                    "run recovery_from_flash;"\
            "else if test ${reboot_mode} = update; then "\
                    "setenv reboot_mode_android ""normal"";"\
                    "run storeargs;"\
                    "run update;"\
            "else if test ${reboot_mode} = quiescent; then "\
                    "setenv reboot_mode_android ""quiescent"";"\
                    "run storeargs;"\
                    "setenv bootargs ${bootargs} androidboot.quiescent=1;"\
            "else if test ${reboot_mode} = recovery_quiescent; then "\
                    "setenv reboot_mode_android ""quiescent"";"\
                    "run storeargs;"\
                    "setenv bootargs ${bootargs} androidboot.quiescent=1;"\
                    "run recovery_from_flash;"\
            "else if test ${reboot_mode} = cold_boot; then "\
                    "setenv reboot_mode_android ""normal"";"\
                    "run storeargs;"\
            "else if test ${reboot_mode} = fastboot; then "\
                "setenv reboot_mode_android ""normal"";"\
                "run storeargs;"\
                "fastboot;"\
            "fi;fi;fi;fi;fi;fi;"\
            "\0" \
        "storeboot="\
            "get_system_as_root_mode;"\
            "echo system_mode: ${system_mode};"\
            "if test ${system_mode} = 1; then "\
                    "setenv bootargs ${bootargs} ro rootwait skip_initramfs;"\
            "else "\
                    "setenv bootargs ${bootargs} androidboot.force_normal_boot=1;"\
            "fi;"\
            "get_avb_mode;"\
            "echo active_slot: ${active_slot} avb2: ${avb2};"\
            "if test ${active_slot} != normal; then "\
                    "setenv bootargs ${bootargs} androidboot.slot_suffix=${active_slot};"\
            "fi;"\
            "if test ${avb2} = 0; then "\
                "if test ${active_slot} = _a; then "\
                    "setenv bootargs ${bootargs} root=/dev/mmcblk0p23;"\
                "else if test ${active_slot} = _b; then "\
                    "setenv bootargs ${bootargs} root=/dev/mmcblk0p24;"\
                "fi;fi;"\
            "fi;"\
            "if imgread kernel ${boot_part} ${loadaddr}; then bootm ${loadaddr}; fi;"\
            "run storeargs; run update;"\
            "\0"\
        "factory_reset_poweroff_protect="\
            "echo wipe_data=${wipe_data}; echo wipe_cache=${wipe_cache};"\
            "if test ${wipe_data} = failed; then "\
                "run init_display; run storeargs;"\
                "if mmcinfo; then "\
                    "run recovery_from_sdcard;"\
                "fi;"\
                "if usb start 0; then "\
                    "run recovery_from_udisk;"\
                "fi;"\
                "run recovery_from_flash;"\
            "fi; "\
            "if test ${wipe_cache} = failed; then "\
                "run init_display; run storeargs;"\
                "if mmcinfo; then "\
                    "run recovery_from_sdcard;"\
                "fi;"\
                "if usb start 0; then "\
                    "run recovery_from_udisk;"\
                "fi;"\
                "run recovery_from_flash;"\
            "fi; \0" \
         "update="\
            /*first usb burning, second sdc_burn, third ext-sd autoscr/recovery, last udisk autoscr/recovery*/\
            "run usb_burning; "\
            "run sdc_burning; "\
            "if mmcinfo; then "\
                "run recovery_from_sdcard;"\
            "fi;"\
            "if usb start 0; then "\
                "run recovery_from_udisk;"\
            "fi;"\
            "run recovery_from_flash;"\
            "\0"\
        "recovery_from_sdcard="\
            "setenv bootargs ${bootargs} aml_dt=${aml_dt} recovery_part={recovery_part} recovery_offset={recovery_offset};"\
	    "if fatload mmc 0 ${loadaddr} aml_autoscript; then "\
		    "if avb memory recovery ${loadaddr}; then " \
		    "avb recovery 1;" \
		    "autoscr ${loadaddr}; fi;"\
	    "fi;"\
            "if fatload mmc 0 ${loadaddr} recovery.img; then "\
	    "if avb memory recovery ${loadaddr}; then " \
	    "avb recovery 1;" \
                    "if fatload mmc 0 ${dtb_mem_addr} dtb.img; then echo sd dtb.img loaded; fi;"\
                    "wipeisb; "\
                    "setenv bootargs ${bootargs} ${fs_type};"\
                    "bootm ${loadaddr};fi;"\
	    "fi;"\
            "\0"\
        "recovery_from_udisk="\
            "setenv bootargs ${bootargs} aml_dt=${aml_dt} recovery_part={recovery_part} recovery_offset={recovery_offset};"\
	    "if avb memory recovery ${loadaddr}; then " \
		    "avb recovery 1;" \
		    "autoscr ${loadaddr}; fi;" \
	    "fi;"\
            "if fatload usb 0 ${loadaddr} recovery.img; then "\
		    "if avb memory recovery ${loadaddr}; then " \
		    "avb recovery 1;" \
                "if fatload usb 0 ${dtb_mem_addr} dtb.img; then echo udisk dtb.img loaded; fi;"\
                "wipeisb; "\
                "setenv bootargs ${bootargs} ${fs_type};"\
                "bootm ${loadaddr};fi;"\
		"fi;"\
            "\0"\
        "recovery_from_flash="\
            "echo active_slot: ${active_slot};"\
            "if test ${active_slot} = normal; then "\
                "setenv bootargs ${bootargs} ${fs_type} aml_dt=${aml_dt} recovery_part=${recovery_part} recovery_offset=${recovery_offset};"\
		"avb recovery 1;" \
                "if itest ${upgrade_step} == 3; then "\
                    "if ext4load mmc 1:2 ${dtb_mem_addr} /recovery/dtb.img; then echo cache dtb.img loaded; fi;"\
                    "if ext4load mmc 1:2 ${loadaddr} /recovery/recovery.img; then echo cache recovery.img loaded; wipeisb; bootm ${loadaddr}; fi;"\
                "else fi;"\
                "if imgread kernel ${recovery_part} ${loadaddr} ${recovery_offset}; then wipeisb; bootm ${loadaddr}; fi;"\
            "else "\
				"if test ${partition_mode} = normal; then "\
                    "setenv bootargs ${bootargs} ${fs_type} aml_dt=${aml_dt} recovery_part=${boot_part} recovery_offset=${recovery_offset};"\
                    "if imgread kernel ${boot_part} ${loadaddr}; then bootm ${loadaddr}; fi;"\
                "else "\
                    "setenv bootargs ${bootargs} ${fs_type} aml_dt=${aml_dt} recovery_part=${recovery_part} recovery_offset=${recovery_offset};"\
                    "if imgread kernel ${recovery_part} ${loadaddr} ${recovery_offset}; then wipeisb; bootm ${loadaddr}; fi;"\
                "fi;"\
            "fi;"\
            "\0"\
        "init_display="\
            "get_rebootmode;"\
            "echo reboot_mode:::: ${reboot_mode};"\
            "if test ${reboot_mode} = quiescent; then "\
                    "setenv reboot_mode_android ""quiescent"";"\
                    "run storeargs;"\
                    "setenv bootargs ${bootargs} androidboot.quiescent=1;"\
                    "watermark_init;osd open;osd clear;"\
            "else if test ${reboot_mode} = recovery_quiescent; then "\
                    "setenv reboot_mode_android ""quiescent"";"\
                    "run storeargs;"\
                    "setenv bootargs ${bootargs} androidboot.quiescent=1;"\
                    "watermark_init;osd open;osd clear;"\
            "else "\
                "setenv reboot_mode_android ""normal"";"\
                "run storeargs;"\
                "watermark_init;osd open;osd clear;imgread pic logo bootup $loadaddr;bmp display $bootup_offset;bmp scale; "\
            "fi;fi;"\
            "\0"\
        "cmdline_keys="\
            "if keyman init 0x1234; then "\
                "if keyman read usid ${loadaddr} str; then "\
                    "setenv bootargs ${bootargs} androidboot.serialno=${usid};"\
                    "setenv serial ${usid};"\
                "else "\
					"setenv bootargs ${bootargs} androidboot.serialno=p244${cpu_id};"\
					"setenv serial p244${cpu_id};"\
                "fi;"\
                "if keyman read mac ${loadaddr} str; then "\
                    "setenv bootargs ${bootargs} mac=${mac} androidboot.mac=${mac};"\
                "fi;"\
                "if keyman read mac_bt ${loadaddr} str; then "\
                    "setenv bootargs ${bootargs} mac_bt=${mac_bt} androidboot.mac_bt=${mac_bt};"\
                "fi;"\
                "if keyman read deviceid ${loadaddr} str; then "\
                    "setenv bootargs ${bootargs} androidboot.deviceid=${deviceid};"\
                "fi;"\
                "if keyman read region_code ${loadaddr} str; then "\
                    "setenv bootargs ${bootargs} androidboot.wificountrycode=${region_code};"\
                "else "\
                    "setenv bootargs ${bootargs} androidboot.wificountrycode=US;"\
                "fi;"\
                "if keyman read oemkey ${loadaddr} str; then "\
                    "setenv bootargs ${bootargs} androidboot.oem.key1=${oemkey};"\
                "else "\
                    "setenv bootargs ${bootargs} androidboot.oem.key1=ATV00104319;"\
                "fi;"\
            "fi;"\
	    "factory_provision init;"\
            "\0"\
        "bcb_cmd="\
            "get_avb_mode;"\
            "get_valid_slot;"\
            "\0"\
        "upgrade_key="\
            "if gpio input GPIOAO_2; then "\
			"echo detect upgrade key;"\
			"if test ${boot_flag} = 0; then "\
				"echo enter fastboot; setenv boot_flag 1; saveenv; fastboot;"\
			"else if test ${boot_flag} = 1; then "\
				"echo enter update; setenv boot_flag 2; saveenv; run update;"\
			"else "\
				"echo enter recovery; setenv boot_flag 0; saveenv; run recovery_from_flash;"\
			"fi;fi;"\
            "fi;"\
            "\0"\

#define CONFIG_PREBOOT  \
            "run bcb_cmd; "\
            "run factory_reset_poweroff_protect;"\
            "run upgrade_check;"\
            "run init_display;"\
            "run storeargs;"\
            "run upgrade_key;" \
            "bcb uboot-command;"\
            "run switch_bootmode;"
#define CONFIG_BOOTCOMMAND "run storeboot"

//#define CONFIG_ENV_IS_NOWHERE  1
#define CONFIG_ENV_SIZE   (64*1024)
#define CONFIG_FIT 1
#define CONFIG_OF_LIBFDT 1
#define CONFIG_ANDROID_BOOT_IMAGE 1
#define CONFIG_ANDROID_IMG 1
#define CONFIG_SYS_BOOTM_LEN (64<<20) /* Increase max gunzip size*/

/* cpu */
#define CONFIG_CPU_CLK					1200 //MHz. Range: 600-1800, should be multiple of 24

/* ddr */
#define CONFIG_DDR_SIZE					1024 //MB //0 means ddr size auto-detect
#define CONFIG_DDR_CLK					912  //MHz, Range: 384-1200, should be multiple of 24
#define CONFIG_DDR4_CLK					1008  //MHz, for boards which use different ddr chip
/* DDR type setting
 *    CONFIG_DDR_TYPE_LPDDR3   : LPDDR3
 *    CONFIG_DDR_TYPE_DDR3     : DDR3
 *    CONFIG_DDR_TYPE_DDR4     : DDR4
 *    CONFIG_DDR_TYPE_AUTO     : DDR3/DDR4 auto detect */
#define CONFIG_DDR_TYPE					CONFIG_DDR_TYPE_AUTO
/* DDR channel setting, please refer hardware design.
 *    CONFIG_DDR0_RANK0        : DDR0 rank0
 *    CONFIG_DDR0_RANK01       : DDR0 rank0+1
 *    CONFIG_DDR0_16BIT        : DDR0 16bit mode
 *    CONFIG_DDR_CHL_AUTO      : auto detect RANK0 / RANK0+1 */
#define CONFIG_DDR_CHANNEL_SET			CONFIG_DDR_CHL_AUTO
#define CONFIG_DDR_FULL_TEST			0 //1 for ddr full test
#define CONFIG_NR_DRAM_BANKS			1
/* ddr functions */
#define CONFIG_CMD_DDR_D2PLL			0 //0:disable, 1:enable. d2pll cmd
#define CONFIG_CMD_DDR_TEST				0 //0:disable, 1:enable. ddrtest cmd
#define CONFIG_DDR_LOW_POWER			0 //0:disable, 1:enable. ddr clk gate for lp
#define CONFIG_DDR_ZQ_PD				0 //0:disable, 1:enable. ddr zq power down
#define CONFIG_DDR_USE_EXT_VREF			0 //0:disable, 1:enable. ddr use external vref
#define CONFIG_DDR_FUNC_PRINT_WINDOW	0 //0:disable, 1:enable. print ddr training window

/* storage: emmc/nand/sd */
#define	CONFIG_STORE_COMPATIBLE 1
/*
*				storage
*		|---------|---------|
*		|					|
*		emmc<--Compatible-->nand
*					|-------|-------|
*					|				|
*					MTD<-Exclusive->NFTL
*/

/* swither for mtd nand which is for slc only. */
/* support for mtd */
//#define CONFIG_AML_MTD 1
/* support for nftl */
#define CONFIG_AML_NAND	1

#if defined(CONFIG_AML_NAND) && defined(CONFIG_AML_MTD)
#error CONFIG_AML_NAND/CONFIG_AML_MTD can not support at the sametime;
#endif

#ifdef CONFIG_AML_MTD
#define CONFIG_CMD_NAND 1
#define CONFIG_MTD_DEVICE y
/* mtd parts of ourown.*/
#define CONFIG_AML_MTDPART	1
/* mtd parts by env default way.*/
/*
#define MTDIDS_NAME_STR		"aml_nand.0"
#define MTDIDS_DEFAULT		"nand1=" MTDIDS_NAME_STR
#define MTDPARTS_DEFAULT	"mtdparts=" MTDIDS_NAME_STR ":" \
					"3M@8192K(logo),"	\
					"10M(recovery),"	\
					"8M(kernel),"	\
					"40M(rootfs),"	\
					"-(data)"
*/
#define CONFIG_CMD_UBI
#define CONFIG_CMD_UBIFS
#define CONFIG_RBTREE
#define CONFIG_CMD_NAND_TORTURE 1
#define CONFIG_CMD_MTDPARTS   1
#define CONFIG_MTD_PARTITIONS 1
#define CONFIG_SYS_MAX_NAND_DEVICE  2
#define CONFIG_SYS_NAND_BASE_LIST   {0}
#endif
/* endof CONFIG_AML_MTD */


#define CONFIG_AML_SD_EMMC 1
#ifdef	CONFIG_AML_SD_EMMC
	#define CONFIG_GENERIC_MMC 1
	#define CONFIG_CMD_MMC 1
	#define CONFIG_CMD_GPT 1
	#define	CONFIG_SYS_MMC_ENV_DEV 1
	#define CONFIG_EMMC_DDR52_EN 0
	#define CONFIG_EMMC_DDR52_CLK 35000000
    /*
        flash/erase operation region on boot1
        in bytes, 2M by default
    */
    //#define CONFIG_EMMC_BOOT1_TOUCH_REGION    (0x200000)

#endif
/* storage macro checks */
#if defined(CONFIG_AML_MTD) && defined(CONFIG_AML_NAND)
#error mtd/nftl are mutually-exclusive, only 1 nand driver can be enabled.
#endif

/* env */
#define 	CONFIG_ENV_OVERWRITE
#define 	CONFIG_CMD_SAVEENV


/* env checks */
#if (defined(CONFIG_ENV_IS_IN_AMLNAND) || defined(CONFIG_ENV_IS_IN_MMC)) && defined(CONFIG_STORE_COMPATIBLE)
#error env in amlnand/mmc already be compatible;
#endif

#define	CONFIG_PARTITIONS 1
#define CONFIG_SYS_NO_FLASH  1
//#define     CONFIG_AML_GPT

/* vpu */
#define CONFIG_AML_VPU 1
#define CONFIG_VPU_CLK_LEVEL_DFT 7

/* DISPLAY & HDMITX */
#define CONFIG_AML_HDMITX20 1
#define CONFIG_AML_CANVAS 1
#define CONFIG_AML_VOUT 1
#define CONFIG_AML_OSD 1
#define CONFIG_AML_MINUI 1
#define CONFIG_OSD_SCALE_ENABLE 1
#define CONFIG_CMD_BMP 1

#if defined(CONFIG_AML_VOUT)
#define CONFIG_AML_CVBS 1
#endif

/* USB
 * Enable CONFIG_MUSB_HCD for Host functionalities MSC, keyboard
 * Enable CONFIG_MUSB_UDD for Device functionalities.
 */
/* #define CONFIG_MUSB_UDC		1 */
#define CONFIG_CMD_USB 1
#if defined(CONFIG_CMD_USB)
	#define CONFIG_GXL_XHCI_BASE		0xc9000000
	#define CONFIG_GXL_USB_PHY2_BASE	0xd0078000
	#define CONFIG_GXL_USB_PHY3_BASE	0xd0078080
	#define CONFIG_USB_XHCI		1
	#define CONFIG_USB_XHCI_AMLOGIC_GXL 1
#endif //#if defined(CONFIG_CMD_USB)

//UBOOT fastboot config
#define CONFIG_CMD_FASTBOOT 1
#define CONFIG_FASTBOOT_FLASH_MMC_DEV 1
#ifdef CONFIG_AML_MTD
#define CONFIG_FASTBOOT_FLASH_NAND_DEV 1
#endif
#define CONFIG_FASTBOOT_FLASH 1
#define CONFIG_USB_GADGET 1
#define CONFIG_USBDOWNLOAD_GADGET 1
#define CONFIG_SYS_CACHELINE_SIZE 64
#define CONFIG_FASTBOOT_MAX_DOWN_SIZE	0x8000000
#define CONFIG_DEVICE_PRODUCT	"anning"

//UBOOT Factory usb/sdcard burning config
#define CONFIG_AML_V2_FACTORY_BURN              1       //support factory usb burning
#define CONFIG_AML_FACTORY_BURN_LOCAL_UPGRADE   1       //support factory sdcard burning
#define CONFIG_POWER_KEY_NOT_SUPPORTED_FOR_BURN 1       //There isn't power-key for factory sdcard burning
#define CONFIG_SD_BURNING_SUPPORT_UI            1       //Displaying upgrading progress bar when sdcard/udisk burning

#define CONFIG_AML_SECURITY_KEY                 1
#ifndef DTB_BIND_KERNEL
#define CONFIG_UNIFY_KEY_MANAGE                 1
#endif

/* net */
#define CONFIG_CMD_NET   1
#if defined(CONFIG_CMD_NET)
	#define CONFIG_DESIGNWARE_ETH 1
	#define CONFIG_PHYLIB	1
	#define CONFIG_NET_MULTI 1
	#define CONFIG_CMD_PING 1
	#define CONFIG_CMD_DHCP 1
	#define CONFIG_CMD_RARP 1
	#define CONFIG_HOSTNAME        arm_gxbb
	#define CONFIG_RANDOM_ETHADDR  1				   /* use random eth addr, or default */
	#define CONFIG_ETHADDR         00:15:18:01:81:31   /* Ethernet address */
	#define CONFIG_IPADDR          10.18.9.97          /* Our ip address */
	#define CONFIG_GATEWAYIP       10.18.9.1           /* Our getway ip address */
	#define CONFIG_SERVERIP        10.18.9.113         /* Tftp server ip address */
	#define CONFIG_NETMASK         255.255.255.0
#endif /* (CONFIG_CMD_NET) */

/* other devices */
#define CONFIG_EFUSE 1
#define CONFIG_SYS_I2C_AML 1
#define CONFIG_SYS_I2C_SPEED     400000

/* commands */
#define CONFIG_CMD_CACHE 1
#define CONFIG_CMD_EFUSE 1
#define CONFIG_CMD_I2C 1
#define CONFIG_CMD_FAT 1
#define CONFIG_CMD_GPIO 1
#define CONFIG_CMD_RUN
#define CONFIG_CMD_REBOOT 1
#define CONFIG_CMD_ECHO 1
#define CONFIG_CMD_MISC 1

/*file system*/
#define CONFIG_DOS_PARTITION 1
#define CONFIG_EFI_PARTITION 1
#define CONFIG_AML_PARTITION 1
#define CONFIG_MMC 1
#define CONFIG_FS_FAT 1
#define CONFIG_FS_EXT4 1
#define CONFIG_LZO 1

#define CONFIG_MDUMP_COMPRESS 1
#define CONFIG_EXT4_WRITE 1
#define CONFIG_CMD_EXT4 1
#define CONFIG_CMD_EXT4_WRITE 1

/* Cache Definitions */
//#define CONFIG_SYS_DCACHE_OFF
//#define CONFIG_SYS_ICACHE_OFF

/* other functions */
#define CONFIG_NEED_BL301	1
#define CONFIG_NEED_BL32	1
#define CONFIG_CMD_RSVMEM	1
#define CONFIG_FIP_IMG_SUPPORT	1
#define CONFIG_BOOTDELAY	1 //delay 1s
#define CONFIG_SYS_LONGHELP 1
#define CONFIG_CMD_MISC     1
#define CONFIG_CMD_ITEST    1
#define CONFIG_CMD_CPU_TEMP 1
#define CONFIG_SYS_MEM_TOP_HIDE 0x08000000 //hide 128MB for kernel reserve
#define CONFIG_MULTI_DTB	1

#define CONFIG_CMD_CHIPID 1
/* debug mode defines */
//#define CONFIG_DEBUG_MODE           1
#ifdef CONFIG_DEBUG_MODE
#define CONFIG_DDR_CLK_DEBUG        636
#define CONFIG_CPU_CLK_DEBUG        600
#endif

//support secure boot
#define CONFIG_AML_SECURE_UBOOT   1

#if defined(CONFIG_AML_SECURE_UBOOT)

//for SRAM size limitation just disable NAND
//as the socket board default has no NAND
//#undef CONFIG_AML_NAND

//unify build for generate encrypted bootloader "u-boot.bin.encrypt"
#define CONFIG_AML_CRYPTO_UBOOT   1

//unify build for generate encrypted kernel image
//SRC : "board/amlogic/(board)/boot.img"
//DST : "fip/boot.img.encrypt"
//#define CONFIG_AML_CRYPTO_IMG       1

#endif //CONFIG_AML_SECURE_UBOOT

#define CONFIG_SECURE_STORAGE 1

//build with uboot auto test
//#define CONFIG_AML_UBOOT_AUTO_TEST 1

//board customer ID
//#define CONFIG_CUSTOMER_ID  (0x6472616F624C4D41)

//anti-rollback function
//#define CONFIG_AML_ANTIROLLBACK 1

#if defined(CONFIG_CUSTOMER_ID)
  #undef CONFIG_AML_CUSTOMER_ID
  #define CONFIG_AML_CUSTOMER_ID  CONFIG_CUSTOMER_ID
#endif
#define CONFIG_INTERNAL_PHY

//#define CONFIG_AVB2
#define CONFIG_AML_KASLR_SEED
#endif

