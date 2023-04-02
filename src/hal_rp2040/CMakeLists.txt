# SPDX-License-Identifier: BSD-3-Clause

cmake_minimum_required(VERSION 3.13)

project(hal_rp2040)

add_library(${PROJECT_NAME} INTERFACE)

target_compile_definitions(${PROJECT_NAME} INTERFACE MRBC_USE_HAL_RP2040)

target_sources(${PROJECT_NAME} INTERFACE
	${CMAKE_CURRENT_SOURCE_DIR}/hal.c
	)

target_include_directories(${PROJECT_NAME} INTERFACE
	${CMAKE_CURRENT_SOURCE_DIR}
	)

target_link_libraries(${PROJECT_NAME} INTERFACE
	pico_stdlib
	)
