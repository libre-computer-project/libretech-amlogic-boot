/*
 * config_defaults.h - sane defaults for everyone
 *
 * Copyright (c) 2009 Analog Devices Inc.
 *
 * Licensed under the GPL-2 or later.
 */

#ifndef _CONFIG_DEFAULTS_H_
#define _CONFIG_DEFAULTS_H_

/* Support bootm-ing different OSes */
#define CONFIG_BOOTM_LINUX 1
#define CONFIG_BOOTM_NETBSD 1
#define CONFIG_BOOTM_PLAN9 1
#define CONFIG_BOOTM_RTEMS 1
#define CONFIG_BOOTM_VXWORKS 1

#define CONFIG_GZIP 1
#define CONFIG_BZIP2 1
#define CONFIG_ZLIB 1
#define CONFIG_PARTITIONS 1

#ifndef CONFIG_SPL_BUILD
#define CONFIG_DM_WARN
#define CONFIG_DM_DEVICE_REMOVE
#define CONFIG_DM_STDIO
#endif

#endif
