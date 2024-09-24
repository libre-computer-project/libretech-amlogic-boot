// SPDX-License-Identifier: (GPL-2.0+ OR MIT)
/*
 * Copyright (c) 2019 Amlogic, Inc. All rights reserved.
 */

#include <config.h>
#include <common.h>
#include <asm/arch/io.h>
#include <command.h>
#include <asm/arch/mailbox.h>
#include <asm/arch/secure_apb.h>
#include <asm/arch/stick_mem.h>

#define INVALID_FLAG  0xFF

//stick reboot flag saved in aocpu local sram, and can
//be fetched from mailbox
static u32 stick_reboot_flag = INVALID_FLAG;

void get_stick_reboot_flag_mbx(void)
{
	scpi_send_data(AOCPU_REE_CHANNEL, CMD_GET_STICK_REBOOT_FLAG, NULL, 0,
			&stick_reboot_flag, 4);
}

u32 get_stick_reboot_flag(void)
{
	return stick_reboot_flag;
}
