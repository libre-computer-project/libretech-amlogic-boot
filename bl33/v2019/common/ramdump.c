// SPDX-License-Identifier: (GPL-2.0+ OR MIT)
/*
 * Copyright (c) 2019 Amlogic, Inc. All rights reserved.
 */

#include <common.h>
#include <asm/arch/bl31_apis.h>
#include <asm/arch/secure_apb.h>
#include <ramdump.h>
#include <emmc_partitions.h>
#include <usb.h>
#include <asm/arch/regs.h>

#define DEBUG_RAMDUMP	0
#define AMLOGIC_KERNEL_PANIC		0x0c
#define AMLOGIC_WATCHDOG_REBOOT		0x0d
#ifdef CONFIG_USB_STORAGE
static void wait_usb_dev(void);
#endif
#undef CONFIG_DUMP_COMPRESS_HEAD
#ifdef CONFIG_DUMP_COMPRESS_HEAD
static void dump_info(unsigned int addr, unsigned int size, const char *info)
{
	int i = 0;

	printf("\nDUMP %s 0X%08x :", info, addr);
	for (i = 0; i < size; i += 4) {
		if (0 == (i % 32))
			printf("\n[0x%08x] ", addr + i);
		printf("%08x ", readl(addr + i));
	}
	printf("\n\n");
}

int parse_dump_file_v2(const char *base, unsigned long size)
{
	struct ram_compress_file_header_v2 *fhead;
	struct ram_compress_section_header_v2 csh;
	struct section_info *seg_tbl;
	unsigned long seg_offset;
	unsigned int idx;
	int cnt = 0, csh_size = 0;

	// check ramdump version >= v2.0
	if ((!strncmp(base, COMPRESS_TAG_HEAD, COMPRESS_TAG_SIZE - 1)) &&
		(!strncmp(base, COMPRESS_TAG_BL3Z, COMPRESS_TAG_SIZE - 1))) {
		printf("# Check the crash file head error, exit.\n");
		return -1;
	}

	// dump crash section head
	fhead = (struct ram_compress_file_header_v2 *)base;
	printf("# total number  of segment is %d\n", fhead->section_count);
	if (fhead->section_count > 10) {
		printf("# crash file head error. exit.\n");
		return -1;
	}

	seg_tbl = malloc(sizeof(struct section_info) * fhead->section_count);
	printf("# total compress file size is 0x%08lx\n", fhead->file_size);
	csh_size = sizeof(struct ram_compress_section_header_v2);
	seg_offset = (unsigned long)fhead + sizeof(struct ram_compress_file_header_v2);
	printf("# crash file fhead  offset is 0x%08lx\n", seg_offset);

	for (cnt = 0; cnt < fhead->section_count; cnt++) {
		memset(&csh, 0, sizeof(csh));
		if (seg_offset > ((unsigned long)base + size))
			continue;

		memcpy((void *)&csh, (char *)seg_offset, sizeof(csh));
		if (csh.section_index > fhead->section_count) {
			printf("csh.section_index(%d) >  fhead->section_count(%d), error, exit.\n",
					csh.section_index, fhead->section_count);
			return -1;
		}

		if (csh.compress_type == RAM_COMPRESS_ERROR ||
			csh.compress_type > RAM_COMPRESS_MAX)
			continue;

		idx = csh.section_index - 1;
		seg_tbl[idx].offset   = seg_offset + sizeof(csh);
		seg_tbl[idx].type     = csh.compress_type;
		seg_tbl[idx].raw_size = csh.raw_size;
		seg_tbl[idx].zip_size = csh.zip_size;
		seg_tbl[idx].val      = csh.set_value;
		seg_offset           += csh.zip_size;
	}

	// dump section table
	printf("\n-----------------------------------------------------------\n");
	printf("idx      offset  type    orig size     zip size    val\n");
	printf("-----------------------------------------------------------\n");
	for (cnt = 0; cnt < fhead->section_count; cnt++) {
		if (seg_tbl[cnt].type == RAM_COMPRESS_ERROR ||
			seg_tbl[cnt].type > RAM_COMPRESS_MAX)
			continue;
		printf(" %2d, 0x%08lx,   %2u,  0x%08lx,  0x%08lx,  0x%02x\n",
		       cnt + 1, seg_tbl[cnt].offset,
		       seg_tbl[cnt].type, seg_tbl[cnt].raw_size,
		       seg_tbl[cnt].zip_size, seg_tbl[cnt].val);
	}
	printf("-----------------------------------------------------------\n");

	// printf section table
	for (cnt = 0; cnt < fhead->section_count; cnt++) {
		if (seg_tbl[cnt].type == RAM_COMPRESS_ERROR ||
			seg_tbl[cnt].type > RAM_COMPRESS_MAX)
			continue;
		dump_info((unsigned int)seg_tbl[cnt].offset - csh_size, csh_size, "crash section head");
	}

	return 0;
}
#endif

unsigned long ramdump_base = 0;
unsigned long ramdump_size = 0;
unsigned int get_reboot_mode(void)
{
	uint32_t reboot_mode_val = ((readl(REG_MDUMP_REBOOT_MODE) >> 12) & 0xf);
	return reboot_mode_val;
}

void ramdump_init(void)
{
	unsigned int data, reboot_mode;

	printf("%s, base reg:0x%08x, size reg:0x%08x\n", __func__,
				REG_MDUMP_COMPRESS_BASE, REG_MDUMP_COMPRESS_SIZE);
	ramdump_base = readl(REG_MDUMP_COMPRESS_BASE);
	ramdump_size = readl(REG_MDUMP_COMPRESS_SIZE);
#if defined(CONFIG_MDUMP_COMPRESS) && defined(CONFIG_COMPRESSED_ADDR)
	printf("%s, ramdump_base(0x%08lx) is overwritten as 0x%08x\n",
			__func__, ramdump_base, CONFIG_COMPRESSED_ADDR);
	ramdump_base = (unsigned long)CONFIG_COMPRESSED_ADDR;
#endif
	if (ramdump_base & 0x80) {
		/* 0x80: The flag indicates that the addr exceeds 4G. */
		/* real size = size[31:0] + addr[6:0]<<32 */
		ramdump_size += (ramdump_base & 0x7f) << 32;
		/* real addr = addr[31:8] << 8 */
		ramdump_base = (ramdump_base & 0xffffff00) << 8;
	}

	data = readl(REG_MDUMP_CPUBOOT_STATUS);
	writel(data & ~RAMDUMP_STICKY_DATA_MASK, REG_MDUMP_CPUBOOT_STATUS);
	printf("%s, add:%lx, size:%lx\n", __func__, ramdump_base, ramdump_size);

#ifdef CONFIG_DUMP_COMPRESS_HEAD
	dump_info((unsigned int)ramdump_base, 0x80, "bl33 check COMPRESS DATA 1");
#endif

	reboot_mode = get_reboot_mode();
	if ((reboot_mode == AMLOGIC_WATCHDOG_REBOOT ||
			reboot_mode == AMLOGIC_KERNEL_PANIC)) {
		if (ramdump_base && ramdump_size) {
#ifdef CONFIG_DUMP_COMPRESS_HEAD
			parse_dump_file_v2((char *)ramdump_base, ramdump_size);
#endif
			ramdump_save_compress_data();
		}
	}
}

#ifdef CONFIG_USB_STORAGE
static void wait_usb_dev(void)
{
	int print_cnt = 0, ret;

	while (1) {
		run_command("usb start", 1);
		mdelay(2000);
		run_command("usb reset", 1);
		ret = usb_stor_scan(1);
		if (ret) {
			if (!(print_cnt & 0x1f)) {
				print_cnt++;
				printf("ramdump: can't find usb device, please insert Udisk.\n\n");
			}
			mdelay(15000);
			continue;
		} else {
			run_command("usb dev", 1);
			break;
		}
	}
}
#endif
/*
 * NOTE: this is a default implementation for writing compressed ramdump data
 * to /data/ partition for Android platform. You can read out dumpfile in
 * path /data/crashdump-1.bin when enter Android for crash analyze.
 * by default, /data/ partition for android is EXT4 fs.
 *
 * TODO:
 *    If you are using different fs or OS on your platform, implement compress
 *    data save command for your fs and OS in your board.c with same function
 *    name "ramdump_save_compress_data".
 */
__weak int ramdump_save_compress_data(void)
{
	char cmd[128] = {0};
	char *env;
	int ret = 0;

	env = env_get("ramdump_enable");
	if (!env || strcmp(env, "1") != 0)
		return 0;

	env = env_get("ramdump_location");
	if (!env)
		return 0;

	printf("ramdump_location:%s\n", env);
	/* currently we only support write to usb disk */
	if (strncmp(env, "usb", 3)) {
		printf("not supported location\n");
		return 0;
	}
#ifdef CONFIG_USB_STORAGE
	wait_usb_dev();
#endif
	printf("\nPrepare to save crash file: base=0x%08lx, size=0x%08lx (%ld MB)\n",
			ramdump_base, ramdump_size, ramdump_size / 1024 / 1024);
	sprintf(cmd, "fatwrite usb 0 %lx crashdump-1.bin %lx\n",
		ramdump_base, ramdump_size);
	printf("CMD:%s\n", cmd);
#ifdef CONFIG_USB_STORAGE
	printf("It may take about 3 minutes, please wait...\n");
	ret = run_command(cmd, 0);
	if (ret != 0) {
		printf("run fatwrite usb ERROR!\n");
		return -1;
	}
	printf("run fatwrite usb OK!\n");
#else
	printf("CONFIG_USB_STORAGE is not defined! Could it be in PRODUCT mode?\n");
	printf("ERROR: The usb drv is not available!\n");
#endif
	printf("Rebooting in 5 seconds ...\n\n\n");
	mdelay(5000);
	run_command("reboot", 1);
	return ret;
}

static void ramdump_env_setup(unsigned long addr, unsigned long size)
{
	unsigned int data[10] = {
		0x8E9C929F, 0x9E9C9791,
		0xD28C9191, 0x97949B8D,
		0x888B92,   0xCEBB97,
		0x938E9B90, 0x978D8D97,
		0xC8009B8A, 0xB99CDB
	};
	char *line, *o;
	unsigned char *p;
	int i;

	p = (unsigned char *)data;
	for (i = 0; i < 40; i++)
		p[i] = ~(p[i] - 1);

	/*
	 * TODO: Make sure address for fdt_high and initrd_high
	 * are suitable for all boards
	 *
	 * usually kernel load address is 0x010800000
	 * Make sure:
	 * (kernel image size + ramdisk size) <
	 * (initrd_high - 0x010800000)
	 * dts file size < (fdt_high - initrd_high)
	 */
	//env_set("initrd_high", "0x0BB00000");
	//env_set("fdt_high",    "0x0BE00000");
	line = env_get("bootargs");
	if (!line)
		return;

	i = strlen(line);
	o = malloc(i + 128);
	if (!o)
		return;

	memset(o, 0, i + 128);
	sprintf(o, "%s=%s ramdump=%lx,%lx  %s\n",
			(char *)data, (char *)(data + 6), addr, size, line);
	env_set("bootargs", o);
	free(o);
	line = NULL;

#if DEBUG_RAMDUMP
	run_command("printenv bootargs", 1);
	printf("\n");
#endif
}

static int overwrite_bl33z_rsvmem_info(unsigned long addr, unsigned long size)
{
	int address_cells = 0;
	unsigned long align_size = PAGE_ALIGN(size);
	char cmd[0x80];

	address_cells = fdt_address_cells(gd->fdt_blob, 0);
	if (address_cells < 1) {
		printf("%s, bad #address-cells !\n", __func__);
		return -1;
	}
	printf("%s, get fdt #address-cells = %d\n", __func__, address_cells);

	memset(cmd, 0, sizeof(cmd));
	if (address_cells == 2)
		sprintf(cmd,
			"fdt set /reserved-memory/ramdump_bl33z reg '<0x0 0x%08lx 0x0 0x%08lx>'",
			addr, align_size);
	else
		sprintf(cmd, "fdt set /reserved-memory/ramdump_bl33z reg '<0x%08lx 0x%08lx>'",
						addr, align_size);

	printf("%s\n", cmd);
	run_command(cmd, 0);

	printf("fdt set /reserved-memory/ramdump_bl33z status okay\n");
	run_command("fdt set /reserved-memory/ramdump_bl33z status okay", 0);

	return 0;
}

static int reduce_dts_reserved_memory(void)
{
	int address_cells = 0;

	address_cells = fdt_address_cells(gd->fdt_blob, 0);
	if (address_cells < 1) {
		printf("%s, bad #address-cells !\n", __func__);
		return -1;
	}
	printf("%s, get fdt #address-cells = %d\n", __func__, address_cells);
	if (address_cells == 2) {
		printf("\nReduce dts reserved memory:\n");
		printf("   * disabled logo_reserved\n");
		run_command("fdt set /reserved-memory/linux,meson-fb  reg '<0x0 0x0 0x0 0x0>'", 0);
		printf("   * disabled vdin1_cma_reserved\n");
		run_command("fdt set /reserved-memory/linux,vdin1_cma reg '<0x0 0x0 0x0 0x0>'", 0);
		printf("   * disabled ion_cma_reserved\n");
		run_command("fdt set /reserved-memory/linux,ion-dev   size '<0 0>'", 0);
		printf("   * disabled dsp_fw_reserved\n");
		run_command("fdt set /reserved-memory/linux,dsp_fw    size '<0 0>'", 0);
		printf("   * disabled lcd_tcon_reserved\n");
		run_command("fdt set /reserved-memory/linux,lcd_tcon  reg '<0x0 0x0 0x0 0x0>'", 0);
		printf("   * reduce codec_mm_cma_reserved\n");
		run_command("fdt set /reserved-memory/linux,codec_mm_cma size '<0x0 0x5000000>'", 0);
		printf("   * reduce ion_fb_reserved, display\n");
		run_command("fdt set /reserved-memory/linux,ion-fb    size '<0x0 0x1000000>'", 0);
	} else {
		printf("\nReduce dts reserved memory:\n");
		printf("   * disabled logo_reserved\n");
		run_command("fdt set /reserved-memory/linux,meson-fb  reg '<0x0 0x0>'", 0);
		printf("   * disabled vdin1_cma_reserved\n");
		run_command("fdt set /reserved-memory/linux,vdin1_cma reg '<0x0 0x0>'", 0);
		printf("   * disabled ion_cma_reserved\n");
		run_command("fdt set /reserved-memory/linux,ion-dev   size '<0>'", 0);
		printf("   * disabled dsp_fw_reserved\n");
		run_command("fdt set /reserved-memory/linux,dsp_fw    size '<0>'", 0);
		printf("   * disabled lcd_tcon_reserved\n");
		run_command("fdt set /reserved-memory/linux,lcd_tcon  reg '<0x0 0x0>'", 0);
		printf("   * reduce codec_mm_cma_reserved\n");
		run_command("fdt set /reserved-memory/linux,codec_mm_cma size '<0x5000000>'", 0);
		printf("   * reduce ion_fb_reserved, display\n");
		run_command("fdt set /reserved-memory/linux,ion-fb    size '<0x1000000>'", 0);
	}

	//run_command("fdt print /reserved-memory", 0);
	return 0;
}

void check_ramdump(void)
{
	unsigned long size = 0;
	unsigned long addr = 0;
	char *env;
	int reboot_mode;
	char str[128] = "";
	unsigned int ddr_scramble_reg = 0xfe02e030;

	env = env_get("ramdump_enable");
	printf("%s, ramdump_enable = %s\n", __func__, env);
	if (env) {
		if (!strcmp(env, "1")) {
			reboot_mode = get_reboot_mode();
			if ((reboot_mode == AMLOGIC_WATCHDOG_REBOOT ||
			     reboot_mode == AMLOGIC_KERNEL_PANIC)) {
				addr = ramdump_base;
				size = ramdump_size;
				printf("%s, addr:%lx, size:%lx\n",
					__func__, addr, size);
				if (addr && size) {
					ramdump_env_setup(addr, size);
#ifdef CONFIG_DUMP_COMPRESS_HEAD
					dump_info((unsigned int)ramdump_base, 0x80, "bl33 check COMPRESS DATA 2");
#endif
					env = env_get("ramdump_location");
					if (!strncmp(env, "data", 4)) {
						printf("Crash file will save to Android /data.\n");
						reduce_dts_reserved_memory();
						overwrite_bl33z_rsvmem_info(addr, size);
						env_set("initrd_high", "0x0BB00000");
						env_set("fdt_high",    "0x0BE00000");
					}
				} else {
					ramdump_env_setup(0, 0);
				}
			} else {
				ramdump_env_setup(0, 0);
			}
#ifndef	CONFIG_MDUMP_COMPRESS
			//ramdump bl33z
			printf("%s, fdt: rsvmem ramdump_bl33z enable.\n", __func__);
			run_command("fdt set /reserved-memory/ramdump_bl33z status okay", 0);
#endif
			//ddr scramble
			sprintf(str, "setenv initargs ${initargs} scramble_reg=0x%08x",
						ddr_scramble_reg);
			printf("set_scramble: %s\n", str);
			run_command(str, 0);
		}
	}
}
