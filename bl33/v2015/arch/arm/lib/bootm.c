/* Copyright (C) 2011
 * Corscience GmbH & Co. KG - Simon Schwarz <schwarz@corscience.de>
 *  - Added prep subcommand support
 *  - Reorganized source - modeled after powerpc version
 *
 * (C) Copyright 2002
 * Sysgo Real-Time Solutions, GmbH <www.elinos.com>
 * Marius Groeger <mgroeger@sysgo.de>
 *
 * Copyright (C) 2001  Erik Mouw (J.A.K.Mouw@its.tudelft.nl)
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <common.h>
#include <command.h>
#include <image.h>
#include <u-boot/zlib.h>
#include <asm/byteorder.h>
#include <libfdt.h>
#include <fdt_support.h>
#include <asm/bootm.h>
#include <asm/secure.h>
#include <linux/compiler.h>
#include <bootm.h>
#include <vxworks.h>
#include <asm/arch/timer.h>

#if defined(CONFIG_ARMV7_NONSEC) || defined(CONFIG_ARMV7_VIRT)
#include <asm/armv7.h>
#endif

#if defined(CONFIG_ZIRCON_BOOT_IMAGE)
#include <zircon/zircon.h>
#endif

#if defined(CONFIG_KEY_PRESERVE)
#include <asm/arch/cpu.h>
#include <asm/arch/secure_apb.h>
#endif

#ifdef CONFIG_AMLOGIC_TIME_PROFILE
#include <initcall.h>
#endif
#include <malloc.h>

DECLARE_GLOBAL_DATA_PTR;

static struct tag *params;

static ulong get_sp(void)
{
	ulong ret;

	asm("mov %0, sp" : "=r"(ret) : );
	return ret;
}

void arch_lmb_reserve(struct lmb *lmb)
{
	ulong sp;

	/*
	 * Booting a (Linux) kernel image
	 *
	 * Allocate space for command line and board info - the
	 * address should be as high as possible within the reach of
	 * the kernel (see CONFIG_SYS_BOOTMAPSZ settings), but in unused
	 * memory, which means far enough below the current stack
	 * pointer.
	 */
	sp = get_sp();
	debug("## Current stack ends at 0x%08lx ", sp);

	/* adjust sp by 4K to be safe */
	sp -= 4096;
	lmb_reserve(lmb, sp,
		    gd->bd->bi_dram[0].start + gd->bd->bi_dram[0].size - sp);
}

/**
 * announce_and_cleanup() - Print message and prepare for kernel boot
 *
 * @fake: non-zero to do everything except actually boot
 */
static void announce_and_cleanup(int fake)
{
	printf("\nStarting kernel ...%s\n\n", fake ?
		"(fake run for tracing)" : "");
	bootstage_mark_name(BOOTSTAGE_ID_BOOTM_HANDOFF, "start_kernel");
#ifdef CONFIG_BOOTSTAGE_FDT
	bootstage_fdt_add_report();
#endif
#ifdef CONFIG_BOOTSTAGE_REPORT
	bootstage_report();
#endif

#ifdef CONFIG_USB_DEVICE
	udc_disconnect();
#endif
	cleanup_before_linux();
}

static void setup_start_tag (bd_t *bd)
{
	params = (struct tag *)bd->bi_boot_params;

	params->hdr.tag = ATAG_CORE;
	params->hdr.size = tag_size (tag_core);

	params->u.core.flags = 0;
	params->u.core.pagesize = 0;
	params->u.core.rootdev = 0;

	params = tag_next (params);
}

static void setup_memory_tags(bd_t *bd)
{
	int i;

	for (i = 0; i < CONFIG_NR_DRAM_BANKS; i++) {
		params->hdr.tag = ATAG_MEM;
		params->hdr.size = tag_size (tag_mem32);

		params->u.mem.start = bd->bi_dram[i].start;
		params->u.mem.size = bd->bi_dram[i].size;

		params = tag_next (params);
	}
}

static void setup_commandline_tag(bd_t *bd, char *commandline)
{
	char *p;

	if (!commandline)
		return;

	/* eat leading white space */
	for (p = commandline; *p == ' '; p++);

	/* skip non-existent command lines so the kernel will still
	 * use its default command line.
	 */
	if (*p == '\0')
		return;

	params->hdr.tag = ATAG_CMDLINE;
	params->hdr.size =
		(sizeof (struct tag_header) + strlen (p) + 1 + 4) >> 2;

	strcpy (params->u.cmdline.cmdline, p);

	params = tag_next (params);
}

static void setup_initrd_tag(bd_t *bd, ulong initrd_start, ulong initrd_end)
{
	/* an ATAG_INITRD node tells the kernel where the compressed
	 * ramdisk can be found. ATAG_RDIMG is a better name, actually.
	 */
	params->hdr.tag = ATAG_INITRD2;
	params->hdr.size = tag_size (tag_initrd);

	params->u.initrd.start = initrd_start;
	params->u.initrd.size = initrd_end - initrd_start;

	params = tag_next (params);
}

static void setup_serial_tag(struct tag **tmp)
{
	struct tag *params = *tmp;
	struct tag_serialnr serialnr;

	get_board_serial(&serialnr);
	params->hdr.tag = ATAG_SERIAL;
	params->hdr.size = tag_size (tag_serialnr);
	params->u.serialnr.low = serialnr.low;
	params->u.serialnr.high= serialnr.high;
	params = tag_next (params);
	*tmp = params;
}

static void setup_revision_tag(struct tag **in_params)
{
	u32 rev = 0;

	rev = get_board_rev();
	params->hdr.tag = ATAG_REVISION;
	params->hdr.size = tag_size (tag_revision);
	params->u.revision.rev = rev;
	params = tag_next (params);
}

static void setup_end_tag(bd_t *bd)
{
	params->hdr.tag = ATAG_NONE;
	params->hdr.size = 0;
}

__weak void setup_board_tags(struct tag **in_params) {}

#ifdef CONFIG_ARM64
static void do_nonsec_virt_switch(void)
{
	smp_kick_all_cpus();
	flush_dcache_all();	/* flush cache before swtiching to EL2 */
	armv8_switch_to_el2();
#ifdef CONFIG_ARMV8_SWITCH_TO_EL1
	armv8_switch_to_el1();
#endif
}
#endif

static inline int str2long(const char *p, ulong *num)
{
	char *endptr;

	*num = simple_strtoul(p, &endptr, 16);
	return *p != '\0' && *endptr == '\0';
}

/*
 * suffix kernel bootargs to bootargs
 *
 */
static void add_kernel_bootargs(bootm_headers_t *images)
{
	int node, len_args_uboot, len_args_dts, len;
	char *bootargs_dts, *bootargs_uboot;
	char *bootargs_new;
	char  *p, *q, *t, *z, *s;
	static char kerenl_dts_update;
	char buf[256];

	if (kerenl_dts_update)
		return;

	kerenl_dts_update = 1;
	node = fdt_path_offset(images->ft_addr, "/chosen");
	if (node < 0) {
		printf("Can't find /chosen node from DTB\n");
		return;
	}
	bootargs_dts = (char *)fdt_getprop(images->ft_addr, node, "bootargs", &len);
	if (!bootargs_dts) {
		printf("Can't find bootargs property in chosen\n");
		return;
	}
	bootargs_uboot = getenv("bootargs");
	if (!bootargs_uboot)
		return;

	len_args_uboot = strlen(bootargs_uboot);
	len_args_dts = strlen(bootargs_dts);
	len = len_args_uboot + len_args_dts + 2;

	bootargs_new = (char *)malloc(len);
	if (!bootargs_new) {
		printf("fail to malloc new bootargs memory\n");
		return;
	}

	memcpy(bootargs_new, bootargs_uboot, len_args_uboot);
	bootargs_new[len_args_uboot] = ' ';
	memcpy(bootargs_new + len_args_uboot + 1, bootargs_dts, len_args_dts);
	bootargs_new[len - 1] = '\0';
	p = bootargs_new;
	while ((q = strchr(p, ' '))) {
		if (q == p) {
			p = q + 1;
			continue;
		}
		memset(buf, 0, sizeof(buf));
		if ((q - p) > sizeof(buf)) {
			memcpy(buf, p, sizeof(buf));
			printf("%s is oversized\n", buf);
			p = q + 1;
			continue;
		}
		memcpy(buf, p, q - p);
		len = strlen(buf);
		p = q + 1;
		z = p;
		while (z) {
			t = strstr(z, buf);
			if (t) {
				s = t;
				if (strchr(s, ' ') && (*(t + len) == ' ')) {
					memmove(t, t + len, z + strlen(z) - t - len + 1);
					z = t;
				} else {
					if (strlen(t) == len) {
						memmove(t, t + len, z + strlen(z) - t - len + 1);
						break;
					} else {
						z = t + len;
					}
				}
			} else {
				break;
			}
		}
	}

	setenv("bootargs", bootargs_new);
	free(bootargs_new);
}

/*
 * kernel 5.15 limit boot env number to 32, there are lots of unused/default
 * zero envs which may cause boot failed in kernel. So remove these envs
 */
static void fix_bootargs(void)
{
	static char const *remove_list[] = {
		"dolby_vision_on=",
		"hdr_policy=",
		"hdr_priority=",
		"osd_reverse=",
		"disable_ir=",
		"lcd_debug=",
		"recovery_offset=",
		"hdmi_read_edid=",
		"mem_size",
	};
	int i, len, rlen, find;
	char *cmdline, *p, *q;
	char buf[64];
	unsigned long value;

	cmdline = getenv("bootargs");
	if (!cmdline)
		return;

	p      = cmdline;
	debug("bootargs:%s\n", cmdline);
	while (*p) {
		/* get an arg */
		q = strchr(p, ' ');
		if (!q)
			break;
		rlen = strlen(q);
		find = 0;
		/* match remove args */
		for (i = 0; i < ARRAY_SIZE(remove_list); i++) {
			len = strlen(remove_list[i]);
			if (!memcmp(p, remove_list[i], len)) {
				/* copy this env to temp buffer and check it's value */
				memset(buf, 0, sizeof(buf));
				memcpy(buf, p, q - p);
				if (buf[len] == ' ') { /* empty one */
					find = 1;
				} else {
					value = -1UL;
					str2long(buf + len, &value);
					if (!value)
						find = 1;
				}
				if (find) {
					memmove(p, q + 1, rlen);
					printf("remove env:%s\n", buf);
					break;
				}
			}
		}
		if (find)
			continue;
		else
			p = q + 1;
	}
	debug("new boot args:%s\n", cmdline);
	/* update env */
	setenv("bootargs", cmdline);
}

/* Subcommand: PREP */
static void boot_prep_linux(bootm_headers_t *images)
{
	char *commandline = getenv("bootargs");

	if (IMAGE_ENABLE_OF_LIBFDT && images->ft_len) {
#ifdef CONFIG_OF_LIBFDT
		debug("using: FDT\n");
		if (image_setup_linux(images)) {
			printf("FDT creation failed! hanging...");
			hang();
		}
#endif
	} else if (BOOTM_ENABLE_TAGS) {
		debug("using: ATAGS\n");
		setup_start_tag(gd->bd);
		if (BOOTM_ENABLE_SERIAL_TAG)
			setup_serial_tag(&params);
		if (BOOTM_ENABLE_CMDLINE_TAG)
			setup_commandline_tag(gd->bd, commandline);
		if (BOOTM_ENABLE_REVISION_TAG)
			setup_revision_tag(&params);
		if (BOOTM_ENABLE_MEMORY_TAGS)
			setup_memory_tags(gd->bd);
		if (BOOTM_ENABLE_INITRD_TAG) {
			if (images->rd_start && images->rd_end) {
				setup_initrd_tag(gd->bd, images->rd_start,
						 images->rd_end);
			}
		}
		setup_board_tags(&params);
		setup_end_tag(gd->bd);
	} else {
		printf("FDT and ATAGS support not compiled in - hanging\n");
		hang();
	}
}

#if defined(CONFIG_ARMV7_NONSEC) || defined(CONFIG_ARMV7_VIRT)
bool armv7_boot_nonsec(void)
{
	char *s = getenv("bootm_boot_mode");
#ifdef CONFIG_ARMV7_BOOT_SEC_DEFAULT
	bool nonsec = false;
#else
	bool nonsec = true;
#endif

	if (s && !strcmp(s, "sec"))
		nonsec = false;

	if (s && !strcmp(s, "nonsec"))
		nonsec = true;

	return nonsec;
}
#endif

/* Subcommand: GO */
extern void jump_to_a32_kernel(unsigned long, unsigned long, unsigned long);
static void boot_jump_linux(bootm_headers_t *images, int flag)
{
#ifdef	CONFIG_KEY_PRESERVE
	(*((volatile unsigned int *)(PREG_STICKY_REG1))) |= 0x1;
#endif

#ifdef CONFIG_ARM64
	void (*kernel_entry)(void *fdt_addr, void *res0, void *res1,
			void *res2);
	int fake = (flag & BOOTM_STATE_OS_FAKE_GO);
	unsigned long machid = 0xf81;

	kernel_entry = (void (*)(void *fdt_addr, void *res0, void *res1,
				void *res2))images->ep;

	debug("## Transferring control to Linux (at address %lx)...\n",
		(ulong) kernel_entry);
	bootstage_mark(BOOTSTAGE_ID_RUN_OS);
#ifdef CONFIG_AML_KASLR_SEED
	int node, ret, len;
	char *prop, *bootargs;
	uint64_t seed;

	node = fdt_path_offset(images->ft_addr, "/chosen");
	if (node < 0)
		printf("Can't find /chosen node from DTB\n");

	bootargs = (char *)fdt_getprop(images->ft_addr, node, "bootargs", &len);
	if (!bootargs)
		printf("Can't find bootargs property in chosen\n");

	if (bootargs && strstr(bootargs, "ramoops_io_en=1")) {
		ret = fdt_appendprop_string(images->ft_addr, node, "bootargs", " nokaslr");
		if (!ret)
			printf("Not enable kaslr for debug purpose\n");
		else
			printf("Fail to set nokaslr %s\n", fdt_strerror(ret));
	} else {
		prop = (char *)fdt_getprop(images->ft_addr, node, "kaslr-seed", NULL);
		if (!prop) {
			printf("Can't find kaslr-seed property in chosen\n");
		} else {
			srand(timer_get_us());
			seed = (uint64_t)rand();
			//printf("--leo-- seed 0x%llx\n", seed);

			ret = fdt_setprop(images->ft_addr, node, "kaslr-seed", &seed, sizeof(seed));
			if (!ret)
				printf("Enable kaslr\n");
			else
				printf("Can't set kaslr-seed value in chosen\n");
		}
	}
#endif

	announce_and_cleanup(fake);

	if (!fake) {
		do_nonsec_virt_switch();
		gd->flags &= ~GD_FLG_SILENT;
		printf("uboot time: %u us\n", get_time());
	#ifdef CONFIG_AMLOGIC_TIME_PROFILE
		if (gd->time_print_flag)
			dump_initcall_time();
	#endif
		if (images->os.arch == IH_ARCH_ARM)
			jump_to_a32_kernel(images->ep, machid, (unsigned long)images->ft_addr);
		else
			kernel_entry(images->ft_addr, NULL, NULL, NULL);
	}
#else
	unsigned long machid = gd->bd->bi_arch_number;
	char *s;
	void (*kernel_entry)(int zero, int arch, uint params);
	unsigned long r2;
	int fake = (flag & BOOTM_STATE_OS_FAKE_GO);

	kernel_entry = (void (*)(int, int, uint))images->ep;

	s = getenv("machid");
	if (s) {
		strict_strtoul(s, 16, &machid);
		printf("Using machid 0x%lx from environment\n", machid);
	}

	debug("## Transferring control to Linux (at address %08lx)" \
		"...\n", (ulong) kernel_entry);
	bootstage_mark(BOOTSTAGE_ID_RUN_OS);
	announce_and_cleanup(fake);

	if (IMAGE_ENABLE_OF_LIBFDT && images->ft_len)
		r2 = (unsigned long)images->ft_addr;
	else
		r2 = gd->bd->bi_boot_params;

	if (!fake) {
#if defined(CONFIG_ARMV7_NONSEC) || defined(CONFIG_ARMV7_VIRT)
		if (armv7_boot_nonsec()) {
			armv7_init_nonsec();
			secure_ram_addr(_do_nonsec_entry)(kernel_entry,
							  0, machid, r2);
		} else
#endif
			kernel_entry(0, machid, r2);
	}
#endif
}

/* Main Entry point for arm bootm implementation
 *
 * Modeled after the powerpc implementation
 * DIFFERENCE: Instead of calling prep and go at the end
 * they are called if subcommand is equal 0.
 */
int do_bootm_linux(int flag, int argc, char * const argv[],
		   bootm_headers_t *images)
{
	add_kernel_bootargs(images);
	fix_bootargs();
	/* No need for those on ARM */
	if (flag & BOOTM_STATE_OS_BD_T || flag & BOOTM_STATE_OS_CMDLINE)
		return -1;

	if (flag & BOOTM_STATE_OS_PREP) {
		boot_prep_linux(images);
		return 0;
	}

	if (flag & (BOOTM_STATE_OS_GO | BOOTM_STATE_OS_FAKE_GO)) {
		boot_jump_linux(images, flag);
		return 0;
	}

	boot_prep_linux(images);
	boot_jump_linux(images, flag);
	return 0;
}

#ifdef CONFIG_CMD_BOOTZ

struct zimage_header {
	uint32_t	code[9];
	uint32_t	zi_magic;
	uint32_t	zi_start;
	uint32_t	zi_end;
};

#define	LINUX_ARM_ZIMAGE_MAGIC	0x016f2818

int bootz_setup(ulong image, ulong *start, ulong *end)
{
	struct zimage_header *zi;

	zi = (struct zimage_header *)map_sysmem(image, 0);
	if (zi->zi_magic != LINUX_ARM_ZIMAGE_MAGIC) {
		puts("Bad Linux ARM zImage magic!\n");
		return 1;
	}

	*start = zi->zi_start;
	*end = zi->zi_end;

	printf("Kernel image @ %#08lx [ %#08lx - %#08lx ]\n", image, *start,
	      *end);

	return 0;
}

#endif	/* CONFIG_CMD_BOOTZ */

#if defined(CONFIG_BOOTM_VXWORKS)
void boot_prep_vxworks(bootm_headers_t *images)
{
#if defined(CONFIG_OF_LIBFDT)
	int off;

	if (images->ft_addr) {
		off = fdt_path_offset(images->ft_addr, "/memory");
		if (off < 0) {
			if (arch_fixup_fdt(images->ft_addr))
				puts("## WARNING: fixup memory failed!\n");
		}
	}
#endif
	cleanup_before_linux();
}
void boot_jump_vxworks(bootm_headers_t *images)
{
	/* ARM VxWorks requires device tree physical address to be passed */
	((void (*)(void *))images->ep)(images->ft_addr);
}
#endif

#if defined(CONFIG_ZIRCON_BOOT_IMAGE)

#define ZIRCON_KERNEL_ALIGN	65536

int do_bootm_zircon(int flag, int argc, char * const argv[],
		   bootm_headers_t *images)
{
	zbi_header_t* zbi = (zbi_header_t *)images->ep;
	const zbi_header_t* kernel_hdr = &zbi[1];
	const zbi_kernel_t* kernel = (zbi_kernel_t *)&zbi[2];

	int ret = zircon_preboot(zbi);
	if (ret < 0) {
	    printf("zircon_preboot failed\n");
	    return ret;
	}

	uint32_t zbi_len = zbi->length + sizeof(zbi_header_t);
	uint32_t kernel_len = kernel_hdr->length + 2 * sizeof(zbi_header_t);

	// If zbi_len is greater than kernel_len,
	// then we have boot items after the kernel.
	// In that case we must relocate the kernel after the zbi
	if (zbi_len > kernel_len) {
		uintptr_t dest = (ulong)zbi + zbi_len;
		// align to 64K boundary
		dest = (dest + ZIRCON_KERNEL_ALIGN - 1) & ~(ZIRCON_KERNEL_ALIGN - 1);
		memcpy((void *)dest, zbi, kernel_len);
		images->ep = dest + kernel->entry;
	} else {
		images->ep = (ulong)zbi + kernel->entry;
	}

	// this will pass the zbi pointer to the kernel via x0
	images->ft_addr = (char *)zbi;
	boot_jump_linux(images, flag);
	return 0;
}
#endif
