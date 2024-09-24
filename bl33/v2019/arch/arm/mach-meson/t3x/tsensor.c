#include <common.h>
#include <asm/io.h>
#include <command.h>
#include <asm/arch/secure_apb.h>
#include <asm/arch/mailbox.h>
#include <asm/arch/tsensor.h>
#include <asm/arch/bl31_apis.h>
#include <linux/arm-smccc.h>
#include <asm/arch/pwr_ctrl.h>
#include <linux/arm-smccc.h>

#define SENSOR_CALIBRATION_VALID_BITS	16
#ifndef SENSOR_CALIBRATION_VALID_BITS
#error "Need define macro < SENSOR_CALIBRATION_VALID_BITS >"
#else
#define SENSOR_CALIBRATION_DATA_MASK	((1 << SENSOR_CALIBRATION_VALID_BITS) - 1)

#if SENSOR_CALIBRATION_VALID_BITS == 14
#define TRIM_FLAG_POS	(13)
#define SIGN_FLAG_POS	(12)
#elif SENSOR_CALIBRATION_VALID_BITS == 16
#define TRIM_FLAG_POS	(15)
#define SIGN_FLAG_POS	(14)
#endif

#define BIT(nr)				(1UL << (nr))
#define TRIM_FLAG	(BIT(TRIM_FLAG_POS))
#define SIGN_FLAG	(BIT(SIGN_FLAG_POS))
#define DATA_BITS	(SENSOR_CALIBRATION_VALID_BITS - 2)
#endif

#define BITS_MASK(x)	((1 << (x)) - 1)
#define SENSOR_VERSION_TYPE	0xf

int tsensor_tz_calibration(unsigned int type, unsigned int data)
{
	struct arm_smccc_res res;
	int ret;

	arm_smccc_smc(TSENSOR_CALI_SET, type, data, 0, 0, 0, 0, 0, &res);
	ret = res.a0;

	if (!ret)
		return -1;
	else
		return 0;
}

int thermal_cali_data_read(uint32_t type, uint32_t *outbuf, int32_t size)
{
	long sharemem_output_base = 0;
	struct arm_smccc_res res;

	sharemem_output_base = get_sharemem_info(GET_SHARE_MEM_OUTPUT_BASE);

	arm_smccc_smc(TSENSOR_CALI_READ, type, 0, 0, 0, 0, 0, 0, &res);
	flush_cache(sharemem_output_base, size);
	memcpy((void *)outbuf, (void *)sharemem_output_base, size);
	return 0;
}

int r1p1_codetotemp(unsigned long value, unsigned int u_efuse)
{
	int64_t temp;

	temp = (value * ts_m) * (1 << 16) / (100 * (1 << 16) + ts_n * value);
	if (u_efuse & 0x8000) {
		temp = ((temp - (u_efuse & 0x7fff)) * ts_a / (1 << 16) - ts_b) / 10;
	} else {
		temp = ((temp + (u_efuse & 0x7fff)) * ts_a / (1 << 16) - ts_b) / 10;
	}
	return temp;
}

static int read_temperature(uint32_t nu, uint32_t thermal_base, uint32_t thermal_sts)
{
	uint32_t ret;
	unsigned int u_efuse;
	unsigned int value_ts, value_all_ts;
	int tmp = -1;
	int i, cnt;
	char buf[2];

	/*enable thermal1*/
	writel(T_CONTROL_DATA, thermal_base);
	writel(T_TSCLK_DATA, CLKCTRL_TS_CLK_CTRL);
	thermal_cali_data_read(nu, &ret, 4);
	printf("type1: ret = %x\n", ret);
	mdelay(5);
	buf[0] = (ret) & 0xff;
	buf[1] = (ret >> 8) & 0xff;
	u_efuse = buf[1];
	u_efuse = (u_efuse << 8) | buf[0];
	value_ts = 0;
	value_all_ts = 0;
	cnt = 0;
	for (i = 0; i <= 10; i++) {
		udelay(50);
		value_ts = readl(thermal_sts) & 0xffff;
	}
	for (i = 0; i <= T_AVG_NUM; i++) {
		udelay(T_DLY_TIME);
		value_ts = readl(thermal_sts) & 0xffff;
		if (value_ts >= T_VALUE_MIN &&
				value_ts <= T_VALUE_MAX) {
			value_all_ts += value_ts;
			cnt++;
		}
	}
	value_ts =  value_all_ts / cnt;
	printf("tsensor avg: 0x%x, u_efuse: 0x%x\n", value_ts, u_efuse);
	if (value_ts == 0) {
		printf("tsensor read temp is zero\n");
		return -1;
	}
	tmp = r1p1_codetotemp(value_ts, u_efuse);
	printf("temp1: %d\n", tmp);

	return tmp;
}

unsigned int r1p1_temptocode(unsigned long value, int tempbase)
{
	unsigned long tmp1, tmp2, u_efuse, signbit;

	printf("a b m n: %d, %d, %d, %d\n", ts_a, ts_b, ts_m, ts_n);
	tmp1 = ((tempbase * 10 + ts_b) * (1 << 16)) / ts_a; /*ideal u*/
	printf("%s : tmp1: 0x%lx\n", __func__, tmp1);
	tmp2 = (ts_m * value * (1 << 16)) / ((1 << 16) * 100 + ts_n * value);
	printf("%s : tmp2: 0x%lx\n", __func__, tmp2);
	signbit = ((tmp1 > tmp2) ? 0 : 1);
	u_efuse = (tmp1 > tmp2) ? (tmp1 - tmp2) : (tmp2 - tmp1);
	if (u_efuse >> DATA_BITS) {
		printf("Tsensor calibration overflow...\n");
		u_efuse = 0;
	} else {
		u_efuse = (signbit << SIGN_FLAG_POS) | u_efuse;
		u_efuse = SIGN_FLAG | u_efuse;
	}
	return u_efuse;
}

static int r1p1_temp_trim(uint32_t tempbase, uint32_t tempver,
		uint32_t nu, uint32_t thermal_base, uint32_t thermal_sts)
{
	unsigned int u_efuse, index_ts;
	unsigned int value_ts, value_all_ts;
	int i, cnt;

	printf("r1p1 temp trim type: 0x%x\n", nu);
	value_ts = 0;
	value_all_ts = 0;
	index_ts = nu;
	cnt = 0;
	/*enable thermal1*/
	writel(T_CONTROL_DATA, thermal_base);
	writel(T_TSCLK_DATA, CLKCTRL_TS_CLK_CTRL);
	for (i = 0; i <= 10; i++) {
		udelay(50);
		value_ts = readl(thermal_sts) & 0xffff;
	}
	for (i = 0; i <= T_AVG_NUM; i++) {
		udelay(T_DLY_TIME);
		value_ts = readl(thermal_sts) & 0xffff;
		printf("tsensor read: 0x%x\n", value_ts);
		if (value_ts >= T_VALUE_MIN &&
				value_ts <= T_VALUE_MAX) {
			value_all_ts += value_ts;
			cnt++;
		}
	}
	value_ts =  value_all_ts / cnt;
	printf("tsensor avg: 0x%x\n", value_ts);
	if (value_ts == 0) {
		printf("pll tsensor read temp is zero\n");
		return -1;
	}
	u_efuse = r1p1_temptocode(value_ts, tempbase);
	printf("ts efuse:%d\n", u_efuse);
	if (!(u_efuse & TRIM_FLAG)) {
		printf("tsensor calibration fail...\n");
		return -1;
	//	u_efuse = u_efuse | 0x4000;
	}
	printf("ts efuse:0x%x, index: %d\n", u_efuse, index_ts);
	if (tsensor_tz_calibration(index_ts, u_efuse) < 0) {
		printf("a73 tsensor thermal_calibration send error\n");
		return -1;
	}

	return 0;
}

int temp_read_entry(void)
{
	unsigned int ret, ver;
	uint32_t data = 0;

	thermal_cali_data_read(1, &data, 4);
	ver = (data >> 24) & 0xff;
	if (0 == (ver & T_VER_MASK)) {
		printf("tsensor no trimmed: calidata:0x%x\n", data);
		return -1;
	}
	ret = (ver & 0xf) >> 2;
	switch (ret) {
		case 0x0:
			printf("temp type no support\n");
		break;
		case 0x2:
			printf("temp type no support\n");
		break;
		case 0x1:
			printf("---- CPU ----\n");
			read_temperature(1, TS_CPU_CFG_REG1, TS_CPU_STAT0);
			printf("---- GPU ----\n");
			read_temperature(2, TS_GPU_CFG_REG1, TS_GPU_STAT0);
			printf("---- VPU ----\n");
			read_temperature(3, TS_VPU_CFG_REG1, TS_VPU_STAT0);
			printf("---- DOS ----\n");
			read_temperature(4, TS_DOS_CFG_REG1, TS_DOS_STAT0);
			printf("---- NNA ----\n");
			pwr_ctrl_psci_smc(20, 1);
			read_temperature(5, TS_NNA_CFG_REG1, TS_NNA_STAT0);
			printf("read the thermal\n");
		break;
		case 0x3:
			printf("temp type no support\n");
			return -1;
		break;
		}
	return 0;
}

int temp_trim_entry(int tempbase, int tempver)
{
	unsigned int  ver;
	uint32_t data;

	thermal_cali_data_read(1, &data, 4);
	ver = (data >> 24) & 0xff;
	if (ver & T_VER_MASK) {
		printf("tsensor trimmed: cali data: 0x%x\n", data);
		return -1;
	}

	printf("tsensor input trim tempver, tempver:0x%x\n", tempver);
	switch (tempver) {
	case 0x84:
		r1p1_temp_trim(tempbase, tempver, 1, TS_CPU_CFG_REG1, TS_CPU_STAT0);
		r1p1_temp_trim(tempbase, tempver, 2, TS_GPU_CFG_REG1, TS_GPU_STAT0);
		r1p1_temp_trim(tempbase, tempver, 3, TS_VPU_CFG_REG1, TS_VPU_STAT0);
		r1p1_temp_trim(tempbase, tempver, 4, TS_DOS_CFG_REG1, TS_DOS_STAT0);
		r1p1_temp_trim(tempbase, tempver, 5, TS_NNA_CFG_REG1, TS_NNA_STAT0);
		tsensor_tz_calibration(SENSOR_VERSION_TYPE, 0);
		printf("triming the thermal by bbt-sw\n");
	break;
	case 0x85:
		r1p1_temp_trim(tempbase, tempver, 1, TS_CPU_CFG_REG1, TS_CPU_STAT0);
		r1p1_temp_trim(tempbase, tempver, 2, TS_GPU_CFG_REG1, TS_GPU_STAT0);
		r1p1_temp_trim(tempbase, tempver, 3, TS_VPU_CFG_REG1, TS_VPU_STAT0);
		r1p1_temp_trim(tempbase, tempver, 4, TS_DOS_CFG_REG1, TS_DOS_STAT0);
		r1p1_temp_trim(tempbase, tempver, 5, TS_NNA_CFG_REG1, TS_NNA_STAT0);
		tsensor_tz_calibration(SENSOR_VERSION_TYPE, 1);
		printf("triming the thermal by bbt-ops\n");
	break;
	case 0x87:
		r1p1_temp_trim(tempbase, tempver, 1, TS_CPU_CFG_REG1, TS_CPU_STAT0);
		r1p1_temp_trim(tempbase, tempver, 2, TS_GPU_CFG_REG1, TS_GPU_STAT0);
		r1p1_temp_trim(tempbase, tempver, 3, TS_VPU_CFG_REG1, TS_VPU_STAT0);
		r1p1_temp_trim(tempbase, tempver, 4, TS_DOS_CFG_REG1, TS_DOS_STAT0);
		r1p1_temp_trim(tempbase, tempver, 5, TS_NNA_CFG_REG1, TS_NNA_STAT0);
		tsensor_tz_calibration(SENSOR_VERSION_TYPE, 3);
		printf("triming the thermal by slt\n");
	break;
	default:
		printf("thermal version not support!!!Please check!\n");
		return -1;
	}
	return 0;
}

int temp_cooling_entry(void)
{
#ifdef CONFIG_AML_TSENSOR_COOL
	int temp, temp1, i;

	while (1) {
		temp = r1p1_temp_read(1);
		for (i = 3; i < 6; i++) {
			temp1 = r1p1_temp_read(i);
			temp = temp > temp1 ? temp : temp1;
		}
		if (temp <= CONFIG_HIGH_TEMP_COOL) {
			printf("device cool done\n");
			break;
		}
		mdelay(2000);
		printf("warning: temp %d over %d, cooling\n", temp,
			CONFIG_HIGH_TEMP_COOL);
	}
#endif
	return 0;
}
