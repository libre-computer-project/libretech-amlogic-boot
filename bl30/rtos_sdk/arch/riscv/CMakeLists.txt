# Copyright (c) 2021-2022 Amlogic, Inc. All rights reserved.

# SPDX-License-Identifier: MIT

aml_add_library()

aml_library_include_directories(
	${CMAKE_CURRENT_SOURCE_DIR}
)

aml_library_sources(
	start.S
	vtable.S
	handlers.c
)

aml_library_link_libraries(kernel__${KERNEL})

aml_link_libraries()
