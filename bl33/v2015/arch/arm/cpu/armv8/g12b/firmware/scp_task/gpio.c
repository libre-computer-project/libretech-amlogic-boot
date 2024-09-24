enum {
	GPIO_BOOT = 1,
	GPIO_C,
	GPIO_X,
	GPIO_H,
	GPIO_Z,
	GPIO_A,

	GPIO_INVALID
};

struct gpio_reg {
	unsigned char bank;
	unsigned int reg_pinmux;
	unsigned int reg_oen;
	unsigned char num;
};

#define GPIO_BANK_NUM	6
static struct gpio_reg gpio_regs[GPIO_BANK_NUM] = {
	{GPIO_BOOT, PERIPHS_PIN_MUX_0, PREG_PAD_GPIO0_EN_N, 16},
	{GPIO_C,    PERIPHS_PIN_MUX_9, PREG_PAD_GPIO1_EN_N, 8},
	{GPIO_X,    PERIPHS_PIN_MUX_3, PREG_PAD_GPIO2_EN_N, 20},
	{GPIO_H,    PERIPHS_PIN_MUX_B, PREG_PAD_GPIO3_EN_N, 9},
	{GPIO_Z,    PERIPHS_PIN_MUX_6, PREG_PAD_GPIO4_EN_N, 16},
	{GPIO_A,    PERIPHS_PIN_MUX_D, PREG_PAD_GPIO5_EN_N, 16}
};

static unsigned int gpio_backup[GPIO_BANK_NUM][5];   //5 = pinmux * 4 + oen * 1

static void gpio_state_backup(unsigned char *gpio_groups, unsigned char num)
{
	unsigned char i, j, k;

	for (i = 0; i < num; i++)
		for (j = 0; j < GPIO_BANK_NUM; j++)
			if (gpio_groups[i] == gpio_regs[j].bank) {
				gpio_backup[i][0] = readl(gpio_regs[j].reg_oen);
				writel(0xffffffff, gpio_regs[j].reg_oen);

				for (k = 0; k < gpio_regs[j].num / 8; k++) {
					gpio_backup[i][k + 1] = readl(gpio_regs[j].reg_pinmux +
								      0x4 * k);
					writel(0x0, gpio_regs[j].reg_pinmux + 0x4 * k);
				}
				if (gpio_regs[j].num % 8) {
					gpio_backup[i][k + 1] = readl(gpio_regs[j].reg_pinmux +
								      0x4 * k);
					writel(0x0, gpio_regs[j].reg_pinmux + 0x4 * k);
				}

				break;
			}
}

static void gpio_state_restore(unsigned char *gpio_groups, unsigned char num)
{
	unsigned char i, j, k;

	for (i = 0; i < num; i++)
		for (j = 0; j < GPIO_BANK_NUM; j++)
			if (gpio_groups[i] == gpio_regs[j].bank) {
				writel(gpio_backup[i][0], gpio_regs[j].reg_oen);

				for (k = 0; k < gpio_regs[j].num / 8; k++) {
					writel(gpio_backup[i][k + 1],
					     gpio_regs[j].reg_pinmux + 0x4 * k);
				}

				if (gpio_regs[j].num % 8) {
					writel(gpio_backup[i][k + 1],
					     gpio_regs[j].reg_pinmux + 0x4 * k);
				}

				break;
			}
}
