#Object files and dependency definitions
BL2_2 = $(kernel_BUILD_DIR)/bl2.bin
RTOS_ELF = $(kernel_BUILD_DIR)/${KERNEL}.elf
RTOS_LOAD_A = $(kernel_BUILD_DIR)/rtos_1.bin
RTOS_LOAD_B = $(kernel_BUILD_DIR)/rtos_2.bin

#toolchain
OBJCOPY:=$(TOOLCHAIN_KEYWORD)-objcopy

#Specify link segment
late_load_list+=.late.data .late.rodata .late.text

.PHONY: scatter
scatter:
	@${OBJCOPY} -O binary $(addprefix -R ,$(late_load_list)) ${RTOS_ELF} ${RTOS_LOAD_A};
	@${OBJCOPY} -O binary $(addprefix -j ,$(late_load_list)) ${RTOS_ELF} ${RTOS_LOAD_B};
#./scripts/package_bl2-2.sh ${BL2_2} ${RTOS_LOAD_A} ${RTOS_LOAD_B} ${kernel_BUILD_DIR}
