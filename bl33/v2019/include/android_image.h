/* SPDX-License-Identifier: BSD-2-Clause */
/*
 * This is from the Android Project,
 * Repository: https://android.googlesource.com/platform/system/core/
 * File: mkbootimg/bootimg.h
 * Commit: d162828814b08ada310846a33205befb69ef5799
 *
 * Copyright (C) 2008 The Android Open Source Project
 */

#ifndef _ANDROID_IMAGE_H_
#define _ANDROID_IMAGE_H_

#define _BA1_(cond, line) \
	extern int __build_assertion_ ## line[1 - 2*!(cond)] \
	__attribute__ ((unused))
#define _BA0_(c, x) _BA1_(c, x)
#define BUILD_ASSERT(cond) _BA0_(cond, __LINE__)

#define IOTRACE_LOAD_ADDR		0x4F00000
#define KERNEL_LOAD_HIGH_ADDR		0xD000000
#define KERNEL_DEFAULT_LOAD_ADDR	0x3000000
#define DTB_LOAD_ADDR			0x1000000
#define LOAD_ADDR_ALIGN_LENGTH		0x100000

#define BOOT_IMG_HDR_SIZE         (0x800)
#define BOOT_IMG_V3_HDR_SIZE      (0x1000)
#define VENDOR_BOOT_IMG_HDR_SIZE  (0x1000)

#define ANDR_BOOT_MAGIC            "ANDROID!"
#define ANDR_BOOT_MAGIC_SIZE      (8)
#define ANDR_BOOT_NAME_SIZE       (16)
#define ANDR_BOOT_ARGS_SIZE       (512)

#define BOOT_MAGIC                "ANDROID!"
#define BOOT_MAGIC_SIZE           (8)
#define BOOT_NAME_SIZE            (16)
#define BOOT_ARGS_SIZE            (512)
#define BOOT_EXTRA_ARGS_SIZE      (1024)

#define VENDOR_BOOT_MAGIC         "VNDRBOOT"
#define VENDOR_BOOT_MAGIC_SIZE    (8)
#define VENDOR_BOOT_ARGS_SIZE     (2048)
#define VENDOR_BOOT_NAME_SIZE     (16)

#define VENDOR_RAMDISK_TYPE_NONE	0
#define VENDOR_RAMDISK_TYPE_PLATFORM	1
#define VENDOR_RAMDISK_TYPE_RECOVERY	2
#define VENDOR_RAMDISK_TYPE_DLKM	3
#define VENDOR_RAMDISK_NAME_SIZE	32
#define VENDOR_RAMDISK_TABLE_ENTRY_BOARD_ID_SIZE	16

/* Before android R boot.img header structure */
typedef struct {
	char magic[BOOT_MAGIC_SIZE]; /*"ANDROID!"*/

	u32 kernel_size;	/* size in bytes */
	u32 kernel_addr;	/* physical load addr */

	u32 ramdisk_size;	/* size in bytes */
	u32 ramdisk_addr;	/* physical load addr */

	u32 second_size;	/* size in bytes */
	u32 second_addr;	/* physical load addr */

	u32 tags_addr;		/* physical addr for kernel tags */
	u32 page_size;		/* flash page size we assume */

	u32 header_version;	/* highest byte: 1 = boot, 2 = recovery;
				   low three bytes: kernel version */

	/* operating system version and security patch level; for
	   * version "A.B.C" and patch level "Y-M-D":
	   * ver = A << 14 | B << 7 | C         (7 bits for each of A, B, C)
	   * lvl = ((Y - 2000) & 127) << 4 | M  (7 bits for Y, 4 bits for M)
	   * os_version = ver << 11 | lvl */
	uint32_t os_version;

	char     name[BOOT_NAME_SIZE]; /* asciiz product name */

	char     cmdline[BOOT_ARGS_SIZE];

	u32      id[8]; /* timestamp / checksum / sha1 / etc */

	/* Supplemental command line data; kept here to maintain
	     binary compatibility with older versions of mkbootimg.
	  */
	uint8_t       extra_cmdline[BOOT_EXTRA_ARGS_SIZE];
	unsigned char szReserved[BOOT_IMG_HDR_SIZE - 1632];       /*align to 2KB header,1632 is size before this*/
}boot_img_hdr_t, *p_boot_img_hdr_t;

/*compile check*/
BUILD_ASSERT(sizeof(boot_img_hdr_t) == BOOT_IMG_HDR_SIZE);


typedef struct {
	boot_img_hdr_t hdr;
	unsigned char  szData[1];
}boot_img_t, * p_boot_img_t;


/* When the boot image header has a version of 3, the structure of the boot
 * image is as follows:
 *
 * +-----------------+
 * | boot header     | 1 page
 * +-----------------+
 * | kernel          | n pages
 * +-----------------+
 * | ramdisk         | m pages
 * +-----------------+
 * | second stage    | o pages
 * +-----------------+
 *
 * n = (kernel_size + page_size - 1) / page_size
 * m = (ramdisk_size + page_size - 1) / page_size
 * o = (second_size + page_size - 1) / page_size
 *
 * 0. all entities are page_size aligned in flash
 * 1. kernel and ramdisk are required (size != 0)
 * 2. second is optional (second_size == 0 -> no second)
 * 3. load each element (kernel, ramdisk, second) at
 *    the specified physical address (kernel_addr, etc)
 * 4. prepare tags at tag_addr.  kernel_args[] is
 *    appended to the kernel commandline in the tags.
 * 5. r0 = 0, r1 = MACHINE_TYPE, r2 = tags_addr
 * 6. if second_size != 0: jump to second_addr
 *    else: jump to kernel_addr
 */


#define ANDROID_R_IMG_VER  (3)
#define ANDROID_S_IMG_VER  (4)

/* Android R boot.img and vendor_boot.img structure */
typedef struct {
	char 	magic[ANDR_BOOT_MAGIC_SIZE]; /*"ANDROID!"*/

	u32 	kernel_size;	/* size in bytes */
	u32 	ramdisk_size;	/* size in bytes */

    /* Operating system version and security patch level.
       For version "A.B.C" and patch level "Y-M-D":
       (7 bits for each of A, B, C; 7 bits for (Y-2000), 4 bits for M)
       os_version = A[31:25] B[24:18] C[17:11] (Y-2000)[10:4] M[3:0]
       */

	uint32_t os_version;
	uint32_t header_size;
	uint32_t reserved[4];

	uint32_t header_version;   /* Version of the boot image header */
	char     cmdline[BOOT_ARGS_SIZE + BOOT_EXTRA_ARGS_SIZE];
	unsigned char szReserved[BOOT_IMG_V3_HDR_SIZE - 1580];       /*align to 4KB header,1580 is size before this*/
}boot_img_hdr_v3_t, * p_boot_img_hdr_v3_t;


/*compile check*/
BUILD_ASSERT(sizeof(boot_img_hdr_v3_t) == BOOT_IMG_V3_HDR_SIZE);

typedef struct {
	boot_img_hdr_v3_t hdr;
	unsigned char     szData[1];
}boot_img_v3_t, * p_boot_img_v3_t;


/* When the boot image header has a version of 3, the structure of the boot
 * image is as follows:
 *
 * +---------------------+
 * | boot header         | 4096 bytes
 * +---------------------+
 * | kernel              | m pages
 * +---------------------+
 * | ramdisk             | n pages
 * +---------------------+
 *
 * m = (kernel_size + 4096 - 1) / 4096
 * n = (ramdisk_size + 4096 - 1) / 4096
 *
 * Note that in version 3 of the boot image header, page size is fixed at 4096 bytes.
 *
 * The structure of the vendor boot image (introduced with version 3 and
 * required to be present when a v3 boot image is used) is as follows:
 *
 * +---------------------+
 * | vendor boot header  | o pages
 * +---------------------+
 * | vendor ramdisk      | p pages
 * +---------------------+
 * | dtb                 | q pages
 * +---------------------+
 * o = (2112 + page_size - 1) / page_size
 * p = (vendor_ramdisk_size + page_size - 1) / page_size
 * q = (dtb_size + page_size - 1) / page_size
 *
 * 0. all entities in the boot image are 4096-byte aligned in flash, all
 *    entities in the vendor boot image are page_size (determined by the vendor
 *    and specified in the vendor boot image header) aligned in flash
 * 1. kernel, ramdisk, vendor ramdisk, and DTB are required (size != 0)
 * 2. load the kernel and DTB at the specified physical address (kernel_addr,
 *    dtb_addr) * 3. load the vendor ramdisk at ramdisk_addr
 * 4. load the generic ramdisk immediately following the vendor ramdisk in
 *    memory
 * 5. set up registers for kernel entry as required by your architecture
 * 6. if the platform has a second stage bootloader jump to it (must be
 *    contained outside boot and vendor boot partitions), otherwise
 *    jump to kernel_addr
 */

struct vendor_boot_img_hdr {
	char     magic[VENDOR_BOOT_MAGIC_SIZE];  /*"VNDRBOOT"*/

	uint32_t header_version;   				 /*Version of the vendor boot image header*/
	uint32_t page_size;		 				 /* flash page size we assume */

	uint32_t kernel_addr; 					 /* physical load addr */
	uint32_t ramdisk_addr; 					 /* physical load addr */

	uint32_t vendor_ramdisk_size; 			 /* size in bytes */

	char     cmdline[VENDOR_BOOT_ARGS_SIZE]; /*2048B*/

	uint32_t tags_addr; 					 /* physical addr for kernel tags (if required) */
	uint8_t  name[VENDOR_BOOT_NAME_SIZE]; 	 /* 16B asciiz product name */

	uint32_t header_size;

	uint32_t dtb_size; 						 /* size in bytes for DTB image */
	uint64_t dtb_addr;						 /* physical load address for DTB image */
	/* new for v4 */
	u32 vendor_ramdisk_table_size;/* size in bytes for the vendor ramdisk table */
	u32 vendor_ramdisk_table_entry_num;/* number of entries in the vendor ramdisk table */
	u32 vendor_ramdisk_table_entry_size;
	u32 vendor_bootconfig_size;/* size in bytes for bootconfig image */
	unsigned char szReserved[VENDOR_BOOT_IMG_HDR_SIZE - 2128];
};

typedef struct vendor_boot_img_hdr vendor_boot_img_hdr_t;
typedef struct vendor_boot_img_hdr *p_vendor_boot_img_hdr_t;

struct vendor_ramdisk_table_entry_v4 {
	u32 ramdisk_size;	/* size in bytes for the ramdisk image */
	u32 ramdisk_offset;	/* offset to the ramdisk image in vendor ramdisk section */
	u32 ramdisk_type;	/* type of the ramdisk */
	u8 ramdisk_name[VENDOR_RAMDISK_NAME_SIZE];	/* asciiz ramdisk name */
	// Hardware identifiers describing the board, soc or platform which this
	// ramdisk is intended to be loaded on.
	u32 board_id[VENDOR_RAMDISK_TABLE_ENTRY_BOARD_ID_SIZE];
};

typedef struct vendor_ramdisk_table_entry_v4 *p_vendor_ramdisk_table_entry_v4_t;

/* When the boot image header has a version of 4, the structure of the boot
 * image is the same as version 3:
 *
 * +---------------------+
 * | boot header         | 4096 bytes
 * +---------------------+
 * | kernel              | m pages
 * +---------------------+
 * | ramdisk             | n pages
 * +---------------------+
 *
 * m = (kernel_size + 4096 - 1) / 4096
 * n = (ramdisk_size + 4096 - 1) / 4096
 *
 * Note that in version 4 of the boot image header, page size is fixed at 4096
 * bytes.
 *
 * The structure of the vendor boot image version 4, which is required to be
 * present when a version 4 boot image is used, is as follows:
 *
 * +------------------------+
 * | vendor boot header     | o pages
 * +------------------------+
 * | vendor ramdisk section | p pages
 * +------------------------+
 * | dtb                    | q pages
 * +------------------------+
 * | vendor ramdisk table   | r pages
 * +------------------------+
 * | bootconfig             | s pages
 * +------------------------+
 *
 * o = (2124 + page_size - 1) / page_size
 * p = (vendor_ramdisk_size + page_size - 1) / page_size
 * q = (dtb_size + page_size - 1) / page_size
 * r = (vendor_ramdisk_table_size + page_size - 1) / page_size
 * s = (vendor_bootconfig_size + page_size - 1) / page_size
 *
 * Note that in version 4 of the vendor boot image, multiple vendor ramdisks can
 * be included in the vendor boot image. The bootloader can select a subset of
 * ramdisks to load at runtime. To help the bootloader select the ramdisks, each
 * ramdisk is tagged with a type tag and a set of hardware identifiers
 * describing the board, soc or platform that this ramdisk is intended for.
 *
 * The vendor ramdisk section is consist of multiple ramdisk images concatenated
 * one after another, and vendor_ramdisk_size is the size of the section, which
 * is the total size of all the ramdisks included in the vendor boot image.
 *
 * The vendor ramdisk table holds the size, offset, type, name and hardware
 * identifiers of each ramdisk. The type field denotes the type of its content.
 * The hardware identifiers are specified in the board_id field in each table
 * entry. The board_id field is consist of a vector of unsigned integer words,
 * and the encoding scheme is defined by the hardware vendor.
 *
 * For the different type of ramdisks, there are:
 *    - VENDOR_RAMDISK_TYPE_NONE indicates the value is unspecified.
 *    - VENDOR_RAMDISK_TYPE_PLATFORM ramdisk contains platform specific bits.
 *    - VENDOR_RAMDISK_TYPE_RECOVERY ramdisk contains recovery resources.
 *    - VENDOR_RAMDISK_TYPE_DLKM ramdisk contains dynamic loadable kernel
 *      modules.
 *
 * Version 4 of the vendor boot image also adds a bootconfig section to the end
 * of the image. This section contains Boot Configuration parameters known at
 * build time. The bootloader is responsible for placing this section directly
 * after the boot image ramdisk, followed by the bootconfig trailer, before
 * entering the kernel.
 *
 * 0. all entities in the boot image are 4096-byte aligned in flash, all
 *    entities in the vendor boot image are page_size (determined by the vendor
 *    and specified in the vendor boot image header) aligned in flash
 * 1. kernel, ramdisk, and DTB are required (size != 0)
 * 2. load the kernel and DTB at the specified physical address (kernel_addr,
 *    dtb_addr)
 * 3. load the vendor ramdisks at ramdisk_addr
 * 4. load the generic ramdisk immediately following the vendor ramdisk in
 *    memory
 * 5. load the vendor bootconfig immediately following the generic ramdisk. Add
 *    additional bootconfig parameters followed by the bootconfig trailer.
 * 6. set up registers for kernel entry as required by your architecture
 * 7. if the platform has a second stage bootloader jump to it (must be
 *    contained outside boot and vendor boot partitions), otherwise
 *    jump to kernel_addr
 */
/* When the boot image header has a version of 3, the structure of the boot
 * image is as follows:
 *
 * +---------------------+
 * | boot header         | 4096 bytes
 * +---------------------+
 * | kernel              | m pages
 * +---------------------+
 * | ramdisk             | n pages
 * +---------------------+
 *
 * m = (kernel_size + 4096 - 1) / 4096
 * n = (ramdisk_size + 4096 - 1) / 4096
 *
 * Note that in version 3 of the boot image header, page size is fixed at 4096 bytes.
 *
 * The structure of the vendor boot image (introduced with version 3 and
 * required to be present when a v3 boot image is used) is as follows:
 *
 * +---------------------+
 * | vendor boot header  | o pages
 * +---------------------+
 * | vendor ramdisk      | p pages
 * +---------------------+
 * | dtb                 | q pages
 * +---------------------+
 *
 * o = (2112 + page_size - 1) / page_size
 * p = (vendor_ramdisk_size + page_size - 1) / page_size
 * q = (dtb_size + page_size - 1) / page_size
 *
 * 0. all entities in the boot image are 4096-byte aligned in flash, all
 *    entities in the vendor boot image are page_size (determined by the vendor
 *    and specified in the vendor boot image header) aligned in flash
 * 1. kernel, ramdisk, vendor ramdisk, and DTB are required (size != 0)
 * 2. load the kernel and DTB at the specified physical address (kernel_addr,
 *    dtb_addr)
 * 3. load the vendor ramdisk at ramdisk_addr
 * 4. load the generic ramdisk immediately following the vendor ramdisk in
 *    memory
 * 5. set up registers for kernel entry as required by your architecture
 * 6. if the platform has a second stage bootloader jump to it (must be
 *    contained outside boot and vendor boot partitions), otherwise
 *    jump to kernel_addr
 */
/* When a boot header is of version 0, the structure of boot image is as
 * follows:
 *
 * +-----------------+
 * | boot header     | 1 page
 * +-----------------+
 * | kernel          | n pages
 * +-----------------+
 * | ramdisk         | m pages
 * +-----------------+
 * | second stage    | o pages
 * +-----------------+
 *
 * n = (kernel_size + page_size - 1) / page_size
 * m = (ramdisk_size + page_size - 1) / page_size
 * o = (second_size + page_size - 1) / page_size
 *
 * 0. all entities are page_size aligned in flash
 * 1. kernel and ramdisk are required (size != 0)
 * 2. second is optional (second_size == 0 -> no second)
 * 3. load each element (kernel, ramdisk, second) at
 *    the specified physical address (kernel_addr, etc)
 * 4. prepare tags at tag_addr.  kernel_args[] is
 *    appended to the kernel commandline in the tags.
 * 5. r0 = 0, r1 = MACHINE_TYPE, r2 = tags_addr
 * 6. if second_size != 0: jump to second_addr
 *    else: jump to kernel_addr
 */
/* When the boot image header has a version of 2, the structure of the boot
 * image is as follows:
 *
 * +---------------------+
 * | boot header         | 1 page
 * +---------------------+
 * | kernel              | n pages
 * +---------------------+
 * | ramdisk             | m pages
 * +---------------------+
 * | second stage        | o pages
 * +---------------------+
 * | recovery dtbo/acpio | p pages
 * +---------------------+
 * | dtb                 | q pages
 * +---------------------+
 *
 * n = (kernel_size + page_size - 1) / page_size
 * m = (ramdisk_size + page_size - 1) / page_size
 * o = (second_size + page_size - 1) / page_size
 * p = (recovery_dtbo_size + page_size - 1) / page_size
 * q = (dtb_size + page_size - 1) / page_size
 *
 * 0. all entities are page_size aligned in flash
 * 1. kernel, ramdisk and DTB are required (size != 0)
 * 2. recovery_dtbo/recovery_acpio is required for recovery.img in non-A/B
 *    devices(recovery_dtbo_size != 0)
 * 3. second is optional (second_size == 0 -> no second)
 * 4. load each element (kernel, ramdisk, second, dtb) at
 *    the specified physical address (kernel_addr, etc)
 * 5. If booting to recovery mode in a non-A/B device, extract recovery
 *    dtbo/acpio and apply the correct set of overlays on the base device tree
 *    depending on the hardware/product revision.
 * 6. prepare tags at tag_addr.  kernel_args[] is
 *    appended to the kernel commandline in the tags.
 * 7. r0 = 0, r1 = MACHINE_TYPE, r2 = tags_addr
 * 8. if second_size != 0: jump to second_addr
 *    else: jump to kernel_addr
 */

typedef struct vendor_ramdisk_table_entry_v4 vendor_ramdisk_table_entry_v4_t;
typedef struct vendor_ramdisk_table_entry_v4 *p_vendor_ramdisk_table_entry_v4_t;

/*compile check*/
BUILD_ASSERT((sizeof(vendor_boot_img_hdr_t) == VENDOR_BOOT_IMG_HDR_SIZE));

typedef struct {
	vendor_boot_img_hdr_t hdr;
	unsigned char         szData[1];
}vendor_boot_img_t, * p_vendor_boot_img_t;

extern p_vendor_boot_img_t p_vender_boot_img;
extern unsigned init_boot_ramdisk_size;
bool is_android_image(void);
#endif
