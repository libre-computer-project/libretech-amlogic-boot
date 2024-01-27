#!/bin/sh

set -xe

TOOLCHAIN_PATH="/opt"

GCC_ARM_NONE_EABI_URL="https://releases.linaro.org/archive/13.11/components/toolchain/binaries/gcc-linaro-arm-none-eabi-4.8-2013.11_linux.tar.xz"
GCC_ARM_NONE_EABI_PATH="gcc-linaro-arm-none-eabi-4.8-2013.11_linux"

GCC_AARCH64_ELF_URL="https://releases.linaro.org/components/toolchain/binaries/7.3-2018.05/aarch64-elf/gcc-linaro-7.3.1-2018.05-x86_64_aarch64-elf.tar.xz"
GCC_AARCH64_ELF_PATH="gcc-linaro-7.3.1-2018.05-x86_64_aarch64-elf"

if ! [ -d $TOOLCHAIN_PATH/$GCC_ARM_NONE_EABI_PATH ]
then
	curl -L $GCC_ARM_NONE_EABI_URL |
	tar xJ -C $TOOLCHAIN_PATH
fi

if ! [ -d $TOOLCHAIN_PATH/$GCC_AARCH64_ELF_PATH ]
then
	curl -L $GCC_AARCH64_ELF_URL |
	tar xJ -C $TOOLCHAIN_PATH
fi
