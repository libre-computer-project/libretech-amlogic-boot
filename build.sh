#!/bin/bash

TOOLCHAIN_PATH="/opt"

usage()
{
	echo "Please specify board type"
	echo " support list:"
	echo "  * aml-s905d3-cc"
	echo "  * aml-a311d-cc"
	echo "  * aml-a311d-cc-v01"
	echo
}
config=
soc=
if [ $1x = x ]
then
	usage
	exit 1
elif [ $1 = aml-s905d3-cc ]
then
	config=g12a_u200_v1
	soc=g12a
elif [ $1 = aml-a311d-cc ]
then
	config=g12b_w400_v1
	soc=g12b
elif [ $1 = aml-a311d-cc-v01 ]
then
	config=g12b_w400_v1
	soc=g12b
else
	echo Unknown board type $1
	exit 1
fi

export PATH="$TOOLCHAIN_PATH/gcc-linaro-arm-none-eabi-4.8-2013.11_linux/bin:$PATH"
export PATH="$TOOLCHAIN_PATH/gcc-linaro-7.3.1-2018.05-x86_64_aarch64-elf/bin:$PATH"
export CROSS_COMPILE=aarch64-elf-

. ./fip/mk_script.sh $config

files="_tmp/bl2_new.bin _tmp/bl30_new.bin _tmp/bl31.img $soc/aml_ddr.fw $soc/aml_encrypt_$soc"

if ! [ -d out ]
then
	mkdir out
fi

for f in $files
do
	cp fip/$f out
done
