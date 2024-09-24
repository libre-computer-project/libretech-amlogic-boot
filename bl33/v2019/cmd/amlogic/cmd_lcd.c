// SPDX-License-Identifier: (GPL-2.0+ OR MIT)
/*
 * Copyright (c) 2019 Amlogic, Inc. All rights reserved.
 */

#include <common.h>
#include <command.h>
#include <malloc.h>
#include <amlogic/media/vout/lcd/aml_lcd.h>

static unsigned int lcd_parse_vout_name(char *name)
{
	char *p, *frac_str;
	unsigned int frac = 0;

	p = strchr(name, ',');
	if (!p) {
		frac = 0;
	} else {
		frac_str = p + 1;
		*p = '\0';
		if (strcmp(frac_str, "frac") == 0)
			frac = 1;
	}

	return frac;
}

static int do_lcd_probe(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	aml_lcd_driver_probe(0);
	return 0;
}

static int do_lcd_enable(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	char *mode, *str;
	unsigned int frac;

	str = env_get("outputmode");
	if (!str) {
		printf("no outputmode\n");
		return -1;
	}

	mode = (char *)malloc(64);
	if (!mode) {
		printf("%s: create mode failed\n", __func__);
		return -1;
	}
	memset(mode, 0, 64);
	sprintf(mode, "%s", str);
	frac = lcd_parse_vout_name(mode);

	aml_lcd_driver_enable(0, mode, frac);

	free(mode);
	return 0;
}

static int do_lcd_disable(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	aml_lcd_driver_disable(0);
	return 0;
}

static int do_lcd_ss(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	int value, temp;
	int ret = 0;

	if (argc == 1)
		return -1;

	if (strcmp(argv[1], "level") == 0) {
		if (argc == 3) {
			value = (unsigned int)simple_strtoul(argv[2], NULL, 10);
			value &= 0xff;
			aml_lcd_driver_set_ss(0, value, 0xff, 0xff);
		} else {
			ret = -1;
		}
	} else if (strcmp(argv[1], "freq") == 0) {
		if (argc == 3) {
			value = (unsigned int)simple_strtoul(argv[2], NULL, 10);
			value &= 0xf;
			aml_lcd_driver_set_ss(0, 0xff, value, 0xff);
		} else {
			ret = -1;
		}
	} else if (strcmp(argv[1], "mode") == 0) {
		if (argc == 3) {
			value = (unsigned int)simple_strtoul(argv[2], NULL, 10);
			value &= 0xf;
			aml_lcd_driver_set_ss(0, 0xff, 0xff, value);
		} else {
			ret = -1;
		}
	} else if (strcmp(argv[1], "set") == 0) {
		if (argc == 3) {
			value = (unsigned int)simple_strtoul(argv[2], NULL, 16);
			value &= 0xffff;
			temp = value >> 8;
			aml_lcd_driver_set_ss(0, (value & 0xff),
				((temp >> LCD_CLK_SS_BIT_FREQ) & 0xf),
				((temp >> LCD_CLK_SS_BIT_MODE) & 0xf));
		} else {
			ret = -1;
		}
	} else if (strcmp(argv[1], "get") == 0) {
		aml_lcd_driver_get_ss(0);
	} else {
		ret = -1;
	}
	return ret;
}

static int do_lcd_clk(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	aml_lcd_driver_clk_info(0);
	return 0;
}

static int do_lcd_print(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	unsigned int val = 0;

	if (argc == 1)
		return -1;
	val = (unsigned int)simple_strtoul(argv[1], NULL, 16);

	aml_lcd_driver_debug_print(0, val);

	return 0;
}

static int do_lcd_info(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	aml_lcd_driver_info(0);
	return 0;
}

#ifdef CONFIG_AML_LCD_TCON
static int do_lcd_tcon(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	struct aml_lcd_drv_s *pdrv = aml_lcd_get_driver(0);
	unsigned int addr, val, len;
	int ret = 0, i;

	if (argc == 1)
		return -1;

	if (!pdrv) {
		printf("no lcd driver\n");
		return 0;
	}
	if (strcmp(argv[1], "reg") == 0) {
		if (pdrv->tcon_reg_print)
			pdrv->tcon_reg_print();
		else
			printf("no lcd tcon_reg_print\n");
	} else if (strcmp(argv[1], "table") == 0) {
		if (pdrv->tcon_table_print)
			pdrv->tcon_table_print();
		else
			printf("no lcd tcon_table_print\n");
	} else if (strcmp(argv[1], "tw") == 0) {
		addr = (unsigned int)simple_strtoul(argv[2], NULL, 16);
		val = (unsigned int)simple_strtoul(argv[3], NULL, 16);
		if (pdrv->tcon_table_write) {
			val = pdrv->tcon_table_write(addr, val);
			printf("write tcon table[0x%04x] = 0x%02x\n",
			       addr, val);
		} else {
			printf("no tcon_table_write\n");
		}
	} else if (strcmp(argv[1], "tr") == 0) {
		addr = (unsigned int)simple_strtoul(argv[2], NULL, 16);
		if (pdrv->tcon_table_read) {
			val = pdrv->tcon_table_read(addr);
			printf("read tcon table[0x%04x] = 0x%02x\n",
			       addr, val);
		} else {
			printf("no tcon_table_write\n");
		}
	} else if (strcmp(argv[1], "wb") == 0) {
		if (pdrv->tcon_reg_write) {
			addr = (unsigned int)simple_strtoul(argv[2], NULL, 16);
			val = (unsigned int)simple_strtoul(argv[3], NULL, 16);
			pdrv->tcon_reg_write(addr, val, 1);
			printf
			("tcon byte write: 0x%04x = 0x%02x, readback 0x%02x\n",
			 addr, val, pdrv->tcon_reg_read(addr, 1));
		} else {
			printf("no tcon_reg_write\n");
		}
	} else if (strcmp(argv[1], "rb") == 0) {
		if (pdrv->tcon_reg_read) {
			addr = (unsigned int)simple_strtoul(argv[2], NULL, 16);
			val = pdrv->tcon_reg_read(addr, 1);
			printf("tcon byte read: 0x%04x = 0x%02x\n", addr, val);
		} else {
			printf("no tcon_reg_read\n");
		}
	} else if (strcmp(argv[1], "db") == 0) {
		if (pdrv->tcon_reg_read) {
			addr = (unsigned int)simple_strtoul(argv[2], NULL, 16);
			len = (unsigned int)simple_strtoul(argv[3], NULL, 10);
			printf("tcon byte reg dump:\n");
			for (i = 0; i < len; i++) {
				val = pdrv->tcon_reg_read((addr + i), 1);
				printf("  0x%04x = 0x%02x\n", (addr + i), val);
			}
		} else {
			printf("no tcon_reg_read\n");
		}
	} else if (strcmp(argv[1], "w") == 0) {
		if (pdrv->tcon_reg_write) {
			addr = (unsigned int)simple_strtoul(argv[2], NULL, 16);
			val = (unsigned int)simple_strtoul(argv[3], NULL, 16);
			pdrv->tcon_reg_write(addr, val, 0);
			printf("tcon write: 0x%04x = 0x%08x, readback 0x%08x\n",
			       addr, val, pdrv->tcon_reg_read(addr, 0));
		} else {
			printf("no tcon_reg_write\n");
		}
	} else if (strcmp(argv[1], "r") == 0) {
		if (pdrv->tcon_reg_read) {
			addr = (unsigned int)simple_strtoul(argv[2], NULL, 16);
			val = pdrv->tcon_reg_read(addr, 0);
			printf("tcon read: 0x%04x = 0x%08x\n", addr, val);
		} else {
			printf("no tcon_reg_read\n");
		}
	} else if (strcmp(argv[1], "d") == 0) {
		if (pdrv->tcon_reg_read) {
			addr = (unsigned int)simple_strtoul(argv[2], NULL, 16);
			len = (unsigned int)simple_strtoul(argv[3], NULL, 10);
			printf("tcon reg dump:\n");
			for (i = 0; i < len; i++) {
				val = pdrv->tcon_reg_read((addr + i), 0);
				printf("  0x%04x = 0x%08x\n", (addr + i), val);
			}
		} else {
			printf("no tcon_reg_read\n");
		}
	} else if (strcmp(argv[1], "vac") == 0 ||
		   strcmp(argv[1], "demura") == 0 ||
		   strcmp(argv[1], "acc") == 0) {
		if (pdrv->tcon_lut_print_tl1)
			pdrv->tcon_lut_print_tl1(argv[1]);
		else
			printf("no lcd tcon_lut_print\n");
	} else if (strcmp(argv[1], "data") == 0) {
		if (argc == 3) {
			i = (unsigned char)simple_strtoul(argv[2], NULL, 10);
			if (pdrv->tcon_data_print)
				pdrv->tcon_data_print(i);
			else
				printf("no lcd tcon_data_print\n");
		} else {
			if (pdrv->tcon_data_print)
				pdrv->tcon_data_print(0xff);
			else
				printf("no lcd tcon_data_print\n");
		}
	} else if (strcmp(argv[1], "tee") == 0) {
		if (strcmp(argv[2], "on") == 0)
			val = 1;
		else
			val = 0;
		if (pdrv->tcon_mem_tee_protect)
			pdrv->tcon_mem_tee_protect(val);
		else
			printf("no lcd tcon_mem_tee_protect\n");
	} else if (strcmp(argv[1], "spi") == 0) {
		if (pdrv->tcon_spi_print)
			pdrv->tcon_spi_print();
		else
			printf("no lcd tcon_spi_print\n");
	} else if (strcmp(argv[1], "check") == 0) {
		if (pdrv->tcon_forbidden_check)
			pdrv->tcon_forbidden_check();
		else
			printf("no lcd tcon_forbidden_check\n");
	} else {
		ret = -1;
	}
	return ret;
}
#endif

static int do_lcd_vbyone(cmd_tbl_t *cmdtp, int flag, int argc,
			 char * const argv[])
{
	int ret = 0;

	if (argc == 1)
		return -1;

	if (strcmp(argv[1], "rst") == 0) {
		aml_lcd_vbyone_rst(0);
	} else if (strcmp(argv[1], "cdr") == 0) {
		ret = aml_lcd_vbyone_cdr(0);
		if (ret)
			printf("[0]: vbyone force cdr fail!\n");
		else
			printf("[0]: vbyone force cdr ok.\n");
	} else if (strcmp(argv[1], "lock") == 0) {
		ret = aml_lcd_vbyone_lock(0);
		if (ret)
			printf("[0]: vbyone force lock fail!\n");
		else
			printf("[0]: vbyone force lock ok.\n");
	} else {
		return 0;
	}

	return 0;
}

static int do_lcd_edp(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	int ret = 0, num;

	if (argc == 1)
		return -1;

	num = argc > 2 ? simple_strtoul(argv[2], NULL, 10) : -1;

	ret = aml_lcd_edp_debug(0, argv[1], num);
	return ret;
}

static int do_lcd_reg(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	aml_lcd_driver_reg_info(0);
	return 0;
}

static int do_lcd_test(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	unsigned int num;

	if (argc == 1)
		return -1;

	num = (unsigned int)simple_strtoul(argv[1], NULL, 10);
	aml_lcd_driver_test(0, num);
	return 0;
}

static int do_lcd_check(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	aml_lcd_config_check(0);
	return 0;
}

static int do_lcd_prbs(cmd_tbl_t *cmdtp, int flag, int argc,
		       char * const argv[])
{
	unsigned int ms, prbs_mode_flag;

	if (argc == 1)
		return -1;

	if (strcmp(argv[1], "vx1") == 0) {
		if (argc == 3)
			prbs_mode_flag = LCD_PRBS_MODE_VX1;
		else
			return -1;
		ms = (unsigned int)simple_strtoul(argv[2], NULL, 10);
	} else if (strcmp(argv[1], "lvds") == 0) {
		if (argc == 3)
			prbs_mode_flag = LCD_PRBS_MODE_LVDS;
		else
			return -1;
		ms = (unsigned int)simple_strtoul(argv[2], NULL, 10);
	} else {
		prbs_mode_flag = LCD_PRBS_MODE_LVDS | LCD_PRBS_MODE_VX1;
		ms = (unsigned int)simple_strtoul(argv[1], NULL, 10);
	}

	aml_lcd_driver_prbs(0, ms, prbs_mode_flag);
	return 0;
}

static int do_lcd_key(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	int tmp = 0;

	if (argc == 1)
		return -1;

	if (strcmp(argv[1], "dump") == 0) {
		if (argc == 3) {
			if (strcmp(argv[2], "tcon") == 0)
				tmp = (1 << 1);
			else
				tmp = (1 << 0);
		} else {
			tmp = (1 << 0);
		}
		aml_lcd_driver_unifykey_dump(0, tmp);
	}
	return 0;
}

#ifdef CONFIG_AML_LCD_EXTERN
static int do_lcd_ext(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	unsigned int temp;

	if (argc == 1)
		return -1;

	if (strcmp(argv[1], "info") == 0) {
		aml_lcd_driver_ext_info(0);
	} else if (strcmp(argv[1], "power") == 0) {
		if (argc < 3)
			return -1;
		temp = simple_strtoul(argv[2], NULL, 10);
		if (temp)
			aml_lcd_driver_ext_power_on(0);
		else
			aml_lcd_driver_ext_power_off(0);
	}

	return 0;
}
#endif

static int do_lcd_bl(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	unsigned int level;
	int ret = 0;

	if (argc == 1)
		return -1;

	if (strcmp(argv[1], "on") == 0) {
		aml_lcd_driver_bl_on(0);
	} else if (strcmp(argv[1], "off") == 0) {
		aml_lcd_driver_bl_off(0);
	} else if (strcmp(argv[1], "set") == 0) {
		if (argc == 3) {
			level = (unsigned int)simple_strtoul(argv[2], NULL, 10);
			aml_lcd_driver_set_bl_level(0, level);
		} else {
			ret = -1;
		}
	} else if (strcmp(argv[1], "get") == 0) {
		level = aml_lcd_driver_get_bl_level(0);
		printf("lcd get_bl_level: %d\n", level);
	} else if (strcmp(argv[1], "info") == 0) {
		aml_lcd_driver_bl_config_print(0);
	} else {
		ret = -1;
	}
	return ret;
}

static int do_lcd1_probe(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	aml_lcd_driver_probe(1);
	return 0;
}

static int do_lcd1_enable(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	char *mode, *str;
	unsigned int frac;

	str = env_get("outputmode2");
	if (!str) {
		printf("no outputmode2\n");
		return -1;
	}

	mode = (char *)malloc(64);
	if (!mode) {
		printf("%s: create mode failed\n", __func__);
		return -1;
	}
	memset(mode, 0, 64);
	sprintf(mode, "%s", str);
	frac = lcd_parse_vout_name(mode);

	aml_lcd_driver_enable(1, mode, frac);

	free(mode);
	return 0;
}

static int do_lcd1_disable(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	aml_lcd_driver_disable(1);
	return 0;
}

static int do_lcd1_ss(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	int value, temp;
	int ret = 0;

	if (argc == 1)
		return -1;

	if (strcmp(argv[1], "level") == 0) {
		if (argc == 3) {
			value = (unsigned int)simple_strtoul(argv[2], NULL, 10);
			value &= 0xff;
			aml_lcd_driver_set_ss(1, value, 0xff, 0xff);
		} else {
			ret = -1;
		}
	} else if (strcmp(argv[1], "freq") == 0) {
		if (argc == 3) {
			value = (unsigned int)simple_strtoul(argv[2], NULL, 10);
			value &= 0xf;
			aml_lcd_driver_set_ss(1, 0xff, value, 0xff);
		} else {
			ret = -1;
		}
	} else if (strcmp(argv[1], "mode") == 0) {
		if (argc == 3) {
			value = (unsigned int)simple_strtoul(argv[2], NULL, 10);
			value &= 0xf;
			aml_lcd_driver_set_ss(1, 0xff, 0xff, value);
		} else {
			ret = -1;
		}
	} else if (strcmp(argv[1], "set") == 0) {
		if (argc == 3) {
			value = (unsigned int)simple_strtoul(argv[2], NULL, 16);
			value &= 0xffff;
			temp = value >> 8;
			aml_lcd_driver_set_ss(1, (value & 0xff),
				((temp >> LCD_CLK_SS_BIT_FREQ) & 0xf),
				((temp >> LCD_CLK_SS_BIT_MODE) & 0xf));
		} else {
			ret = -1;
		}
	} else if (strcmp(argv[1], "get") == 0) {
		aml_lcd_driver_get_ss(1);
	} else {
		ret = -1;
	}
	return ret;
}

static int do_lcd1_clk(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	aml_lcd_driver_clk_info(1);
	return 0;
}

static int do_lcd1_print(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	unsigned int val = 0;

	if (argc == 1)
		return -1;
	val = (unsigned int)simple_strtoul(argv[1], NULL, 16);

	aml_lcd_driver_debug_print(1, val);

	return 0;
}

static int do_lcd1_info(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	aml_lcd_driver_info(1);
	return 0;
}

static int do_lcd1_vbyone(cmd_tbl_t *cmdtp, int flag, int argc,
			 char * const argv[])
{
	int ret = 0;

	if (argc == 1)
		return -1;

	if (strcmp(argv[1], "rst") == 0) {
		aml_lcd_vbyone_rst(1);
	} else if (strcmp(argv[1], "cdr") == 0) {
		ret = aml_lcd_vbyone_cdr(1);
		if (ret)
			printf("[1]: vbyone force cdr fail!\n");
		else
			printf("[1]: vbyone force cdr ok.\n");
	} else if (strcmp(argv[1], "lock") == 0) {
		ret = aml_lcd_vbyone_lock(1);
		if (ret)
			printf("[1]: vbyone force lock fail!\n");
		else
			printf("[1]: vbyone force lock ok.\n");
	} else {
		return 0;
	}

	return ret;
}

static int do_lcd1_edp(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	int ret = 0, num;

	if (argc == 1)
		return -1;

	num = argc > 2 ? simple_strtoul(argv[2], NULL, 10) : 0;

	ret = aml_lcd_edp_debug(1, argv[1], num);
	return ret;
}

static int do_lcd1_reg(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	aml_lcd_driver_reg_info(1);
	return 0;
}

static int do_lcd1_test(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	unsigned int num;

	if (argc == 1)
		return -1;

	num = (unsigned int)simple_strtoul(argv[1], NULL, 10);
	aml_lcd_driver_test(1, num);
	return 0;
}

static int do_lcd1_check(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	aml_lcd_config_check(1);
	return 0;
}

static int do_lcd1_prbs(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	unsigned int ms, prbs_mode_flag;

	if (argc == 1)
		return -1;

	if (strcmp(argv[1], "vx1") == 0) {
		if (argc == 3)
			prbs_mode_flag = LCD_PRBS_MODE_VX1;
		else
			return -1;
		ms = (unsigned int)simple_strtoul(argv[2], NULL, 10);
	} else if (strcmp(argv[1], "lvds") == 0) {
		if (argc == 3)
			prbs_mode_flag = LCD_PRBS_MODE_LVDS;
		else
			return -1;
		ms = (unsigned int)simple_strtoul(argv[2], NULL, 10);
	} else {
		prbs_mode_flag = LCD_PRBS_MODE_LVDS | LCD_PRBS_MODE_VX1;
		ms = (unsigned int)simple_strtoul(argv[1], NULL, 10);
	}

	aml_lcd_driver_prbs(1, ms, prbs_mode_flag);
	return 0;
}

static int do_lcd1_key(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	int tmp = 0;

	if (argc == 1)
		return -1;

	if (strcmp(argv[1], "dump") == 0) {
		if (argc == 3) {
			if (strcmp(argv[2], "tcon") == 0)
				tmp = (1 << 1);
			else
				tmp = (1 << 0);
		} else {
			tmp = (1 << 0);
		}
		aml_lcd_driver_unifykey_dump(1, tmp);
	}
	return 0;
}

#ifdef CONFIG_AML_LCD_EXTERN
static int do_lcd1_ext(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	unsigned int temp;

	if (argc == 1)
		return -1;

	if (strcmp(argv[1], "info") == 0) {
		aml_lcd_driver_ext_info(1);
	} else if (strcmp(argv[1], "power") == 0) {
		if (argc < 3)
			return -1;
		temp = simple_strtoul(argv[2], NULL, 10);
		if (temp)
			aml_lcd_driver_ext_power_on(1);
		else
			aml_lcd_driver_ext_power_off(1);
	}

	return 0;
}
#endif

static int do_lcd1_bl(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	unsigned int level;
	int ret = 0;

	if (argc == 1)
		return -1;

	if (strcmp(argv[1], "on") == 0) {
		aml_lcd_driver_bl_on(1);
	} else if (strcmp(argv[1], "off") == 0) {
		aml_lcd_driver_bl_off(1);
	} else if (strcmp(argv[1], "set") == 0) {
		if (argc == 3) {
			level = (unsigned int)simple_strtoul(argv[2], NULL, 10);
			aml_lcd_driver_set_bl_level(1, level);
		} else {
			ret = -1;
		}
	} else if (strcmp(argv[1], "get") == 0) {
		level = aml_lcd_driver_get_bl_level(1);
		printf("lcd1 get_bl_level: %d\n", level);
	} else if (strcmp(argv[1], "info") == 0) {
		aml_lcd_driver_bl_config_print(1);
	} else {
		ret = -1;
	}
	return ret;
}

static int do_lcd2_probe(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	aml_lcd_driver_probe(2);
	return 0;
}

static int do_lcd2_enable(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	char *mode, *str;
	unsigned int frac;

	str = env_get("outputmode3");
	if (!str) {
		printf("no outputmode3\n");
		return -1;
	}

	mode = (char *)malloc(64);
	if (!mode) {
		printf("%s: create mode failed\n", __func__);
		return -1;
	}
	memset(mode, 0, 64);
	sprintf(mode, "%s", str);
	frac = lcd_parse_vout_name(mode);

	aml_lcd_driver_enable(2, mode, frac);

	free(mode);
	return 0;
}

static int do_lcd2_disable(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	aml_lcd_driver_disable(2);
	return 0;
}

static int do_lcd2_ss(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	int value, temp;
	int ret = 0;

	if (argc == 1)
		return -1;

	if (strcmp(argv[1], "level") == 0) {
		if (argc == 3) {
			value = (unsigned int)simple_strtoul(argv[2], NULL, 10);
			value &= 0xff;
			aml_lcd_driver_set_ss(2, value, 0xff, 0xff);
		} else {
			ret = -1;
		}
	} else if (strcmp(argv[1], "freq") == 0) {
		if (argc == 3) {
			value = (unsigned int)simple_strtoul(argv[2], NULL, 10);
			value &= 0xf;
			aml_lcd_driver_set_ss(2, 0xff, value, 0xff);
		} else {
			ret = -1;
		}
	} else if (strcmp(argv[1], "mode") == 0) {
		if (argc == 3) {
			value = (unsigned int)simple_strtoul(argv[2], NULL, 10);
			value &= 0xf;
			aml_lcd_driver_set_ss(2, 0xff, 0xff, value);
		} else {
			ret = -1;
		}
	} else if (strcmp(argv[1], "set") == 0) {
		if (argc == 3) {
			value = (unsigned int)simple_strtoul(argv[2], NULL, 16);
			value &= 0xffff;
			temp = value >> 8;
			aml_lcd_driver_set_ss(2, (value & 0xff),
				((temp >> LCD_CLK_SS_BIT_FREQ) & 0xf),
				((temp >> LCD_CLK_SS_BIT_MODE) & 0xf));
		} else {
			ret = -1;
		}
	} else if (strcmp(argv[1], "get") == 0) {
		aml_lcd_driver_get_ss(2);
	} else {
		ret = -1;
	}
	return ret;
}

static int do_lcd2_clk(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	aml_lcd_driver_clk_info(2);
	return 0;
}

static int do_lcd2_print(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	unsigned int val = 0;

	if (argc == 1)
		return -1;
	val = (unsigned int)simple_strtoul(argv[1], NULL, 16);

	aml_lcd_driver_debug_print(2, val);

	return 0;
}

static int do_lcd2_info(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	aml_lcd_driver_info(2);
	return 0;
}

static int do_lcd2_reg(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	aml_lcd_driver_reg_info(2);
	return 0;
}

static int do_lcd2_test(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	unsigned int num;

	if (argc == 1)
		return -1;

	num = (unsigned int)simple_strtoul(argv[1], NULL, 10);
	aml_lcd_driver_test(2, num);
	return 0;
}

static int do_lcd2_check(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	aml_lcd_config_check(2);
	return 0;
}

static int do_lcd2_prbs(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	unsigned int ms, prbs_mode_flag;

	if (argc == 1)
		return -1;

	if (strcmp(argv[1], "vx1") == 0) {
		if (argc == 3)
			prbs_mode_flag = LCD_PRBS_MODE_VX1;
		else
			return -1;
		ms = (unsigned int)simple_strtoul(argv[2], NULL, 10);
	} else if (strcmp(argv[1], "lvds") == 0) {
		if (argc == 3)
			prbs_mode_flag = LCD_PRBS_MODE_LVDS;
		else
			return -1;
		ms = (unsigned int)simple_strtoul(argv[2], NULL, 10);
	} else {
		prbs_mode_flag = LCD_PRBS_MODE_LVDS | LCD_PRBS_MODE_VX1;
		ms = (unsigned int)simple_strtoul(argv[1], NULL, 10);
	}

	aml_lcd_driver_prbs(2, ms, prbs_mode_flag);
	return 0;
}

static int do_lcd2_key(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	int tmp = 0;

	if (argc == 1)
		return -1;

	if (strcmp(argv[1], "dump") == 0) {
		if (argc == 3) {
			if (strcmp(argv[2], "tcon") == 0)
				tmp = (1 << 1);
			else
				tmp = (1 << 0);
		} else {
			tmp = (1 << 0);
		}
		aml_lcd_driver_unifykey_dump(2, tmp);
	}
	return 0;
}

#ifdef CONFIG_AML_LCD_EXTERN
static int do_lcd2_ext(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	unsigned int temp;

	if (argc == 1)
		return -1;

	if (strcmp(argv[1], "info") == 0) {
		aml_lcd_driver_ext_info(2);
	} else if (strcmp(argv[1], "power") == 0) {
		if (argc < 3)
			return -1;
		temp = simple_strtoul(argv[2], NULL, 10);
		if (temp)
			aml_lcd_driver_ext_power_on(2);
		else
			aml_lcd_driver_ext_power_off(2);
	}

	return 0;
}
#endif

static int do_lcd2_bl(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	unsigned int level;
	int ret = 0;

	if (argc == 1)
		return -1;

	if (strcmp(argv[1], "on") == 0) {
		aml_lcd_driver_bl_on(2);
	} else if (strcmp(argv[1], "off") == 0) {
		aml_lcd_driver_bl_off(2);
	} else if (strcmp(argv[1], "set") == 0) {
		if (argc == 3) {
			level = (unsigned int)simple_strtoul(argv[2], NULL, 10);
			aml_lcd_driver_set_bl_level(2, level);
		} else {
			ret = -1;
		}
	} else if (strcmp(argv[1], "get") == 0) {
		level = aml_lcd_driver_get_bl_level(2);
		printf("lcd2 get_bl_level: %d\n", level);
	} else if (strcmp(argv[1], "info") == 0) {
		aml_lcd_driver_bl_config_print(2);
	} else {
		ret = -1;
	}
	return ret;
}

static int do_mipi_dsi_cmd(int index, cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	int temp, i;
	unsigned char rd_c[4] = {0, 0, 0, 0};
	unsigned char wr_c[32] = {0};

	if (argc < 3)
		return -1;

	temp = (unsigned int)simple_strtoul(argv[2], NULL, 10);

	if (strcmp(argv[1], "mpmode") == 0) {
		aml_lcd_mipi_dsi_mode(index, temp);
		return 0;
	}

	if (argc < 4)
		return -1;

	wr_c[0] = (unsigned char)simple_strtoul(argv[2], NULL, 16); // data_type
	wr_c[1] = (unsigned char)simple_strtoul(argv[3], NULL, 10); // count
	for (i = 0; i < (wr_c[1] > 30 ? 30 : wr_c[1]); i++)
		wr_c[i + 2] = (unsigned char)simple_strtoul(argv[4 + i], NULL, 16); // count

	if (strcmp(argv[1], "mpread") == 0) {
		temp = aml_lcd_mipi_dsi_read(index, &wr_c[0], &rd_c[0], 4);
		if (temp < 0 || temp > 4) {
			printf("lcd%d mipi dsi read failed\n", index);
			return 0;
		}
		printf("lcd%d mipi dsi read %d: ", index, temp);
		while (temp) {
			printf("0x%02x ", rd_c[temp - 1]);
			temp--;
		}
		printf("\n");
		return 0;
	} else if (strcmp(argv[1], "mpcmd") == 0) {
		aml_lcd_mipi_dsi_cmd(index, &wr_c[0]);
		return 0;
	}
	return -1;
}

static int do_lcd_dsi(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	return do_mipi_dsi_cmd(0, cmdtp, flag, argc, argv);
}

static int do_lcd1_dsi(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	return do_mipi_dsi_cmd(1, cmdtp, flag, argc, argv);
}

static cmd_tbl_t cmd_lcd_sub[] = {
	U_BOOT_CMD_MKENT(probe,   2, 0, do_lcd_probe,    "", ""),
	U_BOOT_CMD_MKENT(enable,  2, 0, do_lcd_enable,   "", ""),
	U_BOOT_CMD_MKENT(disable, 2, 0, do_lcd_disable,  "", ""),
	U_BOOT_CMD_MKENT(ss,      4, 0, do_lcd_ss,       "", ""),
	U_BOOT_CMD_MKENT(clk,     2, 0, do_lcd_clk,      "", ""),
	U_BOOT_CMD_MKENT(print,   3, 0, do_lcd_print,    "", ""),
	U_BOOT_CMD_MKENT(info,    2, 0, do_lcd_info,     "", ""),
#ifdef CONFIG_AML_LCD_TCON
	U_BOOT_CMD_MKENT(tcon,    3, 0, do_lcd_tcon,     "", ""),
#endif
	U_BOOT_CMD_MKENT(vbyone,  3, 0, do_lcd_vbyone,   "", ""),
	U_BOOT_CMD_MKENT(edp,     3, 0, do_lcd_edp,      "", ""),
	U_BOOT_CMD_MKENT(dsi,    32, 0, do_lcd_dsi,      "", ""),
	U_BOOT_CMD_MKENT(reg,     2, 0, do_lcd_reg,      "", ""),
	U_BOOT_CMD_MKENT(test,    3, 0, do_lcd_test,     "", ""),
	U_BOOT_CMD_MKENT(check,   2, 0, do_lcd_check,    "", ""),
	U_BOOT_CMD_MKENT(prbs,    2, 0, do_lcd_prbs,     "", ""),
	U_BOOT_CMD_MKENT(key,     4, 0, do_lcd_key,      "", ""),
#ifdef CONFIG_AML_LCD_EXTERN
	U_BOOT_CMD_MKENT(ext,     4, 0, do_lcd_ext,      "", ""),
#endif
	U_BOOT_CMD_MKENT(bl,      4, 0, do_lcd_bl,       "", ""),
};

static cmd_tbl_t cmd_lcd1_sub[] = {
	U_BOOT_CMD_MKENT(probe,   2, 0, do_lcd1_probe,   "", ""),
	U_BOOT_CMD_MKENT(enable,  2, 0, do_lcd1_enable,  "", ""),
	U_BOOT_CMD_MKENT(disable, 2, 0, do_lcd1_disable, "", ""),
	U_BOOT_CMD_MKENT(ss,      4, 0, do_lcd1_ss,      "", ""),
	U_BOOT_CMD_MKENT(clk,     2, 0, do_lcd1_clk,     "", ""),
	U_BOOT_CMD_MKENT(print,   3, 0, do_lcd1_print,   "", ""),
	U_BOOT_CMD_MKENT(info,    2, 0, do_lcd1_info,    "", ""),
	U_BOOT_CMD_MKENT(vbyone,  3, 0, do_lcd1_vbyone,  "", ""),
	U_BOOT_CMD_MKENT(edp,     3, 0, do_lcd1_edp,     "", ""),
	U_BOOT_CMD_MKENT(dsi,    32, 0, do_lcd1_dsi,     "", ""),
	U_BOOT_CMD_MKENT(reg,     2, 0, do_lcd1_reg,     "", ""),
	U_BOOT_CMD_MKENT(test,    3, 0, do_lcd1_test,    "", ""),
	U_BOOT_CMD_MKENT(check,   2, 0, do_lcd1_check,   "", ""),
	U_BOOT_CMD_MKENT(prbs,    2, 0, do_lcd1_prbs,    "", ""),
	U_BOOT_CMD_MKENT(key,     4, 0, do_lcd1_key,     "", ""),
#ifdef CONFIG_AML_LCD_EXTERN
	U_BOOT_CMD_MKENT(ext,     4, 0, do_lcd1_ext,     "", ""),
#endif
	U_BOOT_CMD_MKENT(bl,      4, 0, do_lcd1_bl,      "", ""),
};

static cmd_tbl_t cmd_lcd2_sub[] = {
	U_BOOT_CMD_MKENT(probe,   2, 0, do_lcd2_probe,   "", ""),
	U_BOOT_CMD_MKENT(enable,  2, 0, do_lcd2_enable,  "", ""),
	U_BOOT_CMD_MKENT(disable, 2, 0, do_lcd2_disable, "", ""),
	U_BOOT_CMD_MKENT(ss,      4, 0, do_lcd2_ss,      "", ""),
	U_BOOT_CMD_MKENT(clk,     2, 0, do_lcd2_clk,     "", ""),
	U_BOOT_CMD_MKENT(print,   3, 0, do_lcd2_print,   "", ""),
	U_BOOT_CMD_MKENT(info,    2, 0, do_lcd2_info,    "", ""),
	U_BOOT_CMD_MKENT(reg,     2, 0, do_lcd2_reg,     "", ""),
	U_BOOT_CMD_MKENT(test,    3, 0, do_lcd2_test,    "", ""),
	U_BOOT_CMD_MKENT(check,   2, 0, do_lcd2_check,   "", ""),
	U_BOOT_CMD_MKENT(prbs,    2, 0, do_lcd2_prbs,    "", ""),
	U_BOOT_CMD_MKENT(key,     4, 0, do_lcd2_key,     "", ""),
#ifdef CONFIG_AML_LCD_EXTERN
	U_BOOT_CMD_MKENT(ext,     4, 0, do_lcd2_ext,     "", ""),
#endif
	U_BOOT_CMD_MKENT(bl,      4, 0, do_lcd2_bl,      "", ""),
};

static int do_lcd(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	cmd_tbl_t *c;

	/* Strip off leading 'bmp' command argument */
	argc--;
	argv++;

	c = find_cmd_tbl(argv[0], &cmd_lcd_sub[0], ARRAY_SIZE(cmd_lcd_sub));

	if (c) {
		return c->cmd(cmdtp, flag, argc, argv);
	} else {
		cmd_usage(cmdtp);
		return 1;
	}
}

U_BOOT_CMD(
	lcd, 32, 0, do_lcd, "lcd sub-system",
	"lcd probe        - probe lcd parameters\n"
	"lcd enable       - enable lcd module\n"
	"lcd disable      - disable lcd module\n"
	"lcd ss           - lcd pll spread spectrum operation\n"
	"lcd bl           - lcd backlight operation\n"
	"lcd clk          - show lcd pll & clk parameters\n"
	"lcd info         - show lcd parameters\n"
#ifdef CONFIG_AML_LCD_TCON
	"lcd tcon         - show lcd tcon debug\n"
#endif
	"lcd vbyone       - show lcd vbyone debug\n"
	"lcd reg          - dump lcd registers\n"
	"lcd test         - show lcd bist pattern\n"
	"lcd check        - show lcd bist pattern\n"
	"lcd key          - show lcd unifykey test\n"
#ifdef CONFIG_AML_LCD_EXTERN
	"lcd ext          - show lcd extern information\n"
#endif
);

static int do_lcd1(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	cmd_tbl_t *c;

	/* Strip off leading 'bmp' command argument */
	argc--;
	argv++;

	c = find_cmd_tbl(argv[0], &cmd_lcd1_sub[0], ARRAY_SIZE(cmd_lcd1_sub));

	if (c) {
		return c->cmd(cmdtp, flag, argc, argv);
	} else {
		cmd_usage(cmdtp);
		return 1;
	}
}

U_BOOT_CMD(
	lcd1, 32, 0, do_lcd1, "lcd1 sub-system",
	"lcd1 probe        - probe lcd parameters\n"
	"lcd1 enable       - enable lcd module\n"
	"lcd1 disable      - disable lcd module\n"
	"lcd1 ss           - lcd pll spread spectrum operation\n"
	"lcd1 bl           - lcd backlight operation\n"
	"lcd1 clk          - show lcd pll & clk parameters\n"
	"lcd1 info         - show lcd parameters\n"
#ifdef CONFIG_AML_LCD_TCON
	"lcd1 tcon         - show lcd tcon debug\n"
#endif
	"lcd1 vbyone       - show lcd vbyone debug\n"
	"lcd1 reg          - dump lcd registers\n"
	"lcd1 test         - show lcd bist pattern\n"
	"lcd1 key          - show lcd unifykey test\n"
#ifdef CONFIG_AML_LCD_EXTERN
	"lcd1 ext          - show lcd extern information\n"
#endif
);

static int do_lcd2(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	cmd_tbl_t *c;

	/* Strip off leading 'bmp' command argument */
	argc--;
	argv++;

	c = find_cmd_tbl(argv[0], &cmd_lcd2_sub[0], ARRAY_SIZE(cmd_lcd2_sub));

	if (c) {
		return c->cmd(cmdtp, flag, argc, argv);
	} else {
		cmd_usage(cmdtp);
		return 1;
	}
}

U_BOOT_CMD(
	lcd2, 5, 0, do_lcd2, "lcd2 sub-system",
	"lcd2 probe        - probe lcd parameters\n"
	"lcd2 enable       - enable lcd module\n"
	"lcd2 disable      - disable lcd module\n"
	"lcd2 ss           - lcd pll spread spectrum operation\n"
	"lcd2 bl           - lcd backlight operation\n"
	"lcd2 clk          - show lcd pll & clk parameters\n"
	"lcd2 info         - show lcd parameters\n"
	"lcd2 reg          - dump lcd registers\n"
	"lcd2 test         - show lcd bist pattern\n"
	"lcd2 key          - show lcd unifykey test\n"
#ifdef CONFIG_AML_LCD_EXTERN
	"lcd2 ext          - show lcd extern information\n"
#endif
);

#ifdef CONFIG_AML_LCD_TCON
#define DBG_TCON_REG_8_bit             1
#define DBG_TCON_REG_32_bit            0

static int do_aml_tcon_reg(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	struct aml_lcd_drv_s *pdrv = aml_lcd_get_driver(0);
	unsigned int addr, mask, val, temp, bit_width, len;
	int ret = 0, i;

	if (!pdrv) {
		printf("for_tool:ERROR\n");
		printf("no lcd driver\n");
		return 0;
	}
	if (!pdrv->tcon_reg_write) {
		printf("for_tool:ERROR\n");
		printf("tcon_reg_write is null\n");
		return 0;
	}
	if (!pdrv->tcon_reg_read) {
		printf("for_tool:ERROR\n");
		printf("tcon_reg_read is null\n");
		return 0;
	}
	if (strcmp(argv[1], "wn") == 0) {
		if (argc < 5) {
			printf("for_tool:ERROR\n");
			printf("argc is not enough\n");
			return 0;
		}
		if (strcmp(argv[2], "8") == 0) {
			bit_width = DBG_TCON_REG_8_bit;
		} else if (strcmp(argv[2], "32") == 0) {
			bit_width = DBG_TCON_REG_32_bit;
		} else {
			printf("for_tool:ERROR\n");
			printf("aml_tcon reg bit_width %s invalid\n", argv[2]);
			return 0;
		}
		addr = (unsigned int)simple_strtoul(argv[3], NULL, 16);
		len = (unsigned int)simple_strtoul(argv[4], NULL, 10);
		if (len == 0 || len > 16) {
			printf("for_tool:ERROR\n");
			printf("aml_tcon reg len %d not support\n", len);
			return 0;
		}
		if (argc < (len + 5)) {
			printf("for_tool:ERROR\n");
			printf("aml_tcon reg data cnt %d not enough\n", (argc - 5));
			return 0;
		}
		for (i = 0; i < len; i++) {
			val = (unsigned int)simple_strtoul(argv[5 + i], NULL, 16);
			pdrv->tcon_reg_write(addr + i, val, bit_width);
		}
		printf("for_tool:");
		if (bit_width == DBG_TCON_REG_8_bit) {
			for (i = 0; i < len; i++) {
				temp = pdrv->tcon_reg_read(addr + i, bit_width);
				printf("0x%04x=0x%02x ", addr + i, temp);
			}
		} else {
			for (i = 0; i < len; i++) {
				temp = pdrv->tcon_reg_read(addr + i, bit_width);
				printf("0x%04x=0x%08x ", addr + i, temp);
			}
		}
		printf("\n");
	} else if (strcmp(argv[1], "wm") == 0) {
		if (argc < 6) {
			printf("for_tool:ERROR\n");
			printf("argc is not enough\n");
			return 0;
		}
		if (strcmp(argv[2], "8") == 0) {
			bit_width = DBG_TCON_REG_8_bit;
		} else if (strcmp(argv[2], "32") == 0) {
			bit_width = DBG_TCON_REG_32_bit;
		} else {
			printf("for_tool:ERROR\n");
			printf("aml_tcon reg bit_width %s invalid\n", argv[2]);
			return 0;
		}
		addr = (unsigned int)simple_strtoul(argv[3], NULL, 16);
		mask = (unsigned int)simple_strtoul(argv[4], NULL, 16);
		val = (unsigned int)simple_strtoul(argv[5], NULL, 16);

		temp = pdrv->tcon_reg_read(addr, bit_width);
		temp &= ~mask;
		temp |= val & mask;
		pdrv->tcon_reg_write(addr, temp, bit_width);
		printf("for_tool:");
		temp = pdrv->tcon_reg_read(addr, bit_width);
		if (bit_width == DBG_TCON_REG_8_bit)
			printf("0x%04x=0x%02x\n", addr, temp);
		else
			printf("0x%04x=0x%08x\n", addr, temp);
	} else if (strcmp(argv[1], "ws") == 0) {
		if (argc < 5) {
			printf("for_tool:ERROR\n");
			printf("argc is not enough\n");
			return 0;
		}
		if (strcmp(argv[2], "8") == 0) {
			bit_width = DBG_TCON_REG_8_bit;
		} else if (strcmp(argv[2], "32") == 0) {
			bit_width = DBG_TCON_REG_32_bit;
		} else {
			printf("for_tool:ERROR\n");
			printf("aml_tcon reg bit_width %s invalid\n", argv[2]);
			return 0;
		}
		addr = (unsigned int)simple_strtoul(argv[3], NULL, 16);
		len = (unsigned int)simple_strtoul(argv[4], NULL, 10);
		if (len == 0 || len > 16) {
			printf("for_tool:ERROR\n");
			printf("aml_tcon reg len %d not support\n", len);
			return 0;
		}
		if (argc < (len + 5)) {
			printf("for_tool:ERROR\n");
			printf("aml_tcon reg data cnt %d not enough\n", (argc - 5));
			return 0;
		}
		for (i = 0; i < len; i++) {
			val = (unsigned int)simple_strtoul(argv[5 + i], NULL, 16);
			pdrv->tcon_reg_write(addr, val, bit_width);
		}
		printf("for_tool:");
		if (bit_width == DBG_TCON_REG_8_bit) {
			for (i = 0; i < len; i++) {
				temp = pdrv->tcon_reg_read(addr, bit_width);
				printf("0x%04x=0x%02x ", addr, temp);
			}
		} else {
			for (i = 0; i < len; i++) {
				temp = pdrv->tcon_reg_read(addr, bit_width);
				printf("0x%04x=0x%08x ", addr, temp);
			}
		}
		printf("\n");
	} else if (strcmp(argv[1], "rn") == 0) {
		if (argc < 4) {
			printf("for_tool:ERROR\n");
			printf("argc is not enough\n");
			return 0;
		}
		if (strcmp(argv[2], "8") == 0) {
			bit_width = DBG_TCON_REG_8_bit;
		} else if (strcmp(argv[2], "32") == 0) {
			bit_width = DBG_TCON_REG_32_bit;
		} else {
			printf("for_tool:ERROR\n");
			printf("aml_tcon reg bit_width %s invalid\n", argv[2]);
			return 0;
		}
		addr = (unsigned int)simple_strtoul(argv[3], NULL, 16);
		if (argc == 4)
			len = 1;
		else
			len = (unsigned int)simple_strtoul(argv[4], NULL, 10);
		if (len == 0 || len > 16) {
			printf("for_tool:ERROR\n");
			printf("aml_tcon reg len %d not support\n", len);
			return 0;
		}
		printf("for_tool:");
		if (bit_width == DBG_TCON_REG_8_bit) {
			for (i = 0; i < len; i++) {
				temp = pdrv->tcon_reg_read(addr + i, bit_width);
				printf("0x%04x=0x%02x ", addr + i, temp);
			}
		} else {
			for (i = 0; i < len; i++) {
				temp = pdrv->tcon_reg_read(addr + i, bit_width);
				printf("0x%04x=0x%08x ", addr + i, temp);
			}
		}
		printf("\n");
	} else {
		printf("for_tool:ERROR\n");
		ret = -1;
	}
	return ret;
}

static cmd_tbl_t cmd_aml_tcon_sub[] = {
	U_BOOT_CMD_MKENT(reg,   32, 0, do_aml_tcon_reg, "", ""),
};

static int do_aml_tcon(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	cmd_tbl_t *c;

	/* Strip off leading 'bmp' command argument */
	argc--;
	argv++;

	c = find_cmd_tbl(argv[0], &cmd_aml_tcon_sub[0], ARRAY_SIZE(cmd_aml_tcon_sub));

	if (c)
		return c->cmd(cmdtp, flag, argc, argv);

	cmd_usage(cmdtp);
	return 1;
}

U_BOOT_CMD(aml_tcon,	32,	0,	do_aml_tcon,
	"aml_tcon sub-system",
	"aml_tcon reg        - aml_tcon reg access\n"
);
#endif
