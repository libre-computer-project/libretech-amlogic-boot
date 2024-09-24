# Copyright (c) 2021-2022 Amlogic, Inc. All rights reserved.

# SPDX-License-Identifier: MIT

cmake_minimum_required(VERSION 3.13.1)

set(SDK_BASE $ENV{SDK_BASE})
set(ARCH $ENV{ARCH})
set(SPLIT_ARCH_DIR $ENV{SPLIT_ARCH_DIR})
set(ARCH_DIR ${SDK_BASE}/arch/${ARCH})
set(SOC $ENV{SOC})
set(BOARD $ENV{BOARD})
set(CROSS_COMPILER $ENV{CROSS_COMPILER})
set(KERNEL $ENV{KERNEL})
set(PRODUCT $ENV{PRODUCT})

if(NOT SPLIT_ARCH_DIR)
    set(SOC_DIR ${SDK_BASE}/soc/${ARCH}/${SOC})
    set(BOARD_DIR ${SDK_BASE}/boards/${ARCH}/${BOARD})
else()
    set(SOC_DIR ${SDK_BASE}/soc/${ARCH}/${SPLIT_ARCH_DIR}/${SOC})
    set(BOARD_DIR ${SDK_BASE}/boards/${ARCH}/${SPLIT_ARCH_DIR}/${BOARD})
endif()

set(SDK_OUT ${CMAKE_BINARY_DIR})
set(PROJECT_BINARY_DIR ${CMAKE_BINARY_DIR})
set(PROJECT_SOURCE_DIR ${SDK_BASE})
set(APPLICATION_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(COLLECT_LINK_LIBRARIES ""  CACHE INTERNAL "")
set(COLLECT_LINK_OBJS ""  CACHE INTERNAL "")
set(COLLECT_IS_CPP_LIBRARIES "0"  CACHE INTERNAL "")

set(CMAKE_EXECUTABLE_SUFFIX ".elf")

if(EXISTS   ${APPLICATION_SOURCE_DIR}/prj_${BOARD}.conf)
    set(CONF_FILE ${APPLICATION_SOURCE_DIR}/prj_${BOARD}.conf)
elseif(EXISTS   ${APPLICATION_SOURCE_DIR}/prj.conf)
    set(CONF_FILE ${APPLICATION_SOURCE_DIR}/prj.conf)
endif()

message(STATUS "CMAKE_SOURCE_DIR: ${CMAKE_SOURCE_DIR}")
message(STATUS "CMAKE_BINARY_DIR: ${CMAKE_BINARY_DIR}")

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    if(NOT "${ARCH}" STREQUAL "xtensa")
        add_compile_options(-fdiagnostics-color=always)
    endif()
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    if(NOT "${ARCH}" STREQUAL "xtensa")
        add_compile_options(-fcolor-diagnostics)
    endif()
endif()

include(${SDK_BASE}/build_system/cmake/extensions.cmake)
include(${SDK_BASE}/build_system/cmake/python.cmake)
include(${SDK_BASE}/build_system/cmake/kconfig.cmake)
include(${SDK_BASE}/build_system/cmake/toolchains/${ARCH}_compiler.cmake)

set(TARGET_NAME $ENV{KERNEL})

# Do not prefix the output library file.
set(CMAKE_STATIC_LIBRARY_PREFIX "")

set(CMAKE_C_FLAGS "-imacros${AUTOCONF_H}")
set(CMAKE_CXX_FLAGS "-imacros${AUTOCONF_H}")
set(CMAKE_ASM_FLAGS "-imacros${AUTOCONF_H}")

if(EXISTS ${ARCH_DIR}/compiler_options.cmake)
    include(${ARCH_DIR}/compiler_options.cmake)
endif()
if(EXISTS ${SOC_DIR}/compiler_options.cmake)
    include(${SOC_DIR}/compiler_options.cmake)
endif()
if(EXISTS ${BOARD_DIR}/compiler_options.cmake)
    include(${BOARD_DIR}/compiler_options.cmake)
endif()

message(STATUS TARGET_NAME: ${TARGET_NAME})
add_executable(${TARGET_NAME})
add_subdirectory(${SDK_BASE} ${SDK_OUT}/obj)

# Linker flags
target_link_options(
    ${TARGET_NAME}
    PUBLIC ${common_flags} ${linker_flags}
)

if($ENV{COMPILER} STREQUAL "clang+llvm")
	if(CONFIG_LIBC_STD AND CONFIG_LIBC_AML)
		set(SYSTEM_LIBS m c nosys)
	elseif(CONFIG_LIBC_AML)
		set(SYSTEM_LIBS m)
	elseif(CONFIG_LIBC_STD)
		set(SYSTEM_LIBS m c)
	else()
		set(SYSTEM_LIBS m)
	endif()
elseif($ENV{COMPILER} STREQUAL "xcc")
	set(SYSTEM_LIBS m gcc)
else()
	#compiler gcc
	if(CONFIG_LIBC_STD AND CONFIG_LIBC_AML)
		set(SYSTEM_LIBS m c gcc nosys)
	elseif(CONFIG_LIBC_AML)
		set(SYSTEM_LIBS gcc m)
	elseif(CONFIG_LIBC_STD)
		set(SYSTEM_LIBS m c gcc)
	else()
		set(SYSTEM_LIBS m gcc)
	endif()
endif()

if("${COLLECT_IS_CPP_LIBRARIES}" STREQUAL "1")
	message(STATUS "link c++ stand library for C++ use lib")
	set(SYSTEM_LIBS ${SYSTEM_LIBS} stdc++ c g gcc nosys)
endif()

if(CONFIG_LTO_OPTIMIZATION AND $ENV{COMPILER} STREQUAL "gcc")
	message(STATUS "gcc LTO optimization enabled")
	set(LTO_SYMBOL_WRAP -u__wrap__malloc_r -u__wrap__free_r -u__wrap__realloc_r -u__wrap__calloc_r
	-u__wrap__getpid_r -u__wrap__kill_r -u_isatty -u_fstat)
endif()

if(CONFIG_XTENSA)
#arch XTENSA not support LTO option
    add_custom_command(TARGET ${TARGET_NAME} PRE_BUILD COMMAND ${CMAKE_C_COMPILER} -I ${BOARD_DIR} -E -xc -P ${BOARD_DIR}/lsp_dsp/memmap.ld > ${BOARD_DIR}/lsp_dsp/memmap.xmm)
    add_custom_command(TARGET ${TARGET_NAME} PRE_BUILD COMMAND ${CMAKE_LDGEN_COMPILER} -b ${BOARD_DIR}/lsp_dsp/ >/dev/null)
    target_link_libraries(
        ${TARGET_NAME}
        -Wl,--start-group
        ${COLLECT_LINK_OBJS}
        ${SYSTEM_LIBS} ${COLLECT_LINK_LIBRARIES}
        -Wl,--end-group
        -mlsp="${BOARD_DIR}/lsp_dsp/"
)
elseif(CONFIG_ARM64 OR CONFIG_ARM)
    if(CONFIG_LIB_MCUBOOT_BOOTLOADER)
        add_custom_command(TARGET ${TARGET_NAME} PRE_BUILD COMMAND ${CMAKE_C_COMPILER} -I ${BOARD_DIR} -DCONFIG_EXCEPTION_SVC=1 -DCONFIG_LIB_MCUBOOT_BOOTLOADER=1 -E -xc -P ${SDK_BASE}/boards/${ARCH}/lscript > ${BOARD_DIR}/lscript.ld)
    else()
        add_custom_command(TARGET ${TARGET_NAME} PRE_BUILD COMMAND ${CMAKE_C_COMPILER} -I ${BOARD_DIR} -DCONFIG_EXCEPTION_SVC=1 -E -xc -P ${SDK_BASE}/boards/${ARCH}/lscript > ${BOARD_DIR}/lscript.ld)
    endif()

    target_link_libraries(
        ${TARGET_NAME}
        -Wl,--start-group
        ${LTO_SYMBOL_WRAP}
        ${COLLECT_LINK_OBJS}
        ${SYSTEM_LIBS} ${COLLECT_LINK_LIBRARIES}
        -Wl,--end-group
        -T"${BOARD_DIR}/lscript.ld"
    )
elseif(CONFIG_RISCV)
add_custom_command(TARGET ${TARGET_NAME} PRE_BUILD COMMAND ${CMAKE_C_COMPILER} -I ${BOARD_DIR} -E -xc -P ${BOARD_DIR}/lscript.ld > ${BOARD_DIR}/lscript)
    target_link_libraries(
        ${TARGET_NAME}
        -Wl,--start-group
        ${LTO_SYMBOL_WRAP}
        ${COLLECT_LINK_OBJS}
        ${SYSTEM_LIBS} ${COLLECT_LINK_LIBRARIES}
        -Wl,--end-group
        -T"${BOARD_DIR}/lscript"
    )
endif()

#Generate binary file from elf
compiler_generate_binary_output(${TARGET_NAME})

#Generate lst file from lst
if($ENV{COMPILER} STREQUAL "clang+llvm")
	compiler_generate_lst_output(${TARGET_NAME} -D)
elseif($ENV{COMPILER} STREQUAL "xcc")
	compiler_generate_lst_output(${TARGET_NAME} -D)
else()
	#compiler gcc
	compiler_generate_lst_output(${TARGET_NAME} -S)
endif()

#Generate module memory size information
generate_module_info_output(${TARGET_NAME})
