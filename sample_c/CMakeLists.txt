# SPDX-License-Identifier: BSD-3-Clause

cmake_minimum_required(VERSION 3.13)

if(NOT MSVC)
	add_compile_options(-Wall -Wpointer-arith -g)
endif()

add_executable(sample_scheduler
	sample_scheduler.c
	)

target_link_libraries(sample_scheduler PRIVATE
	mrubyc
	)

add_executable(sample_no_scheduler
	sample_no_scheduler.c
	)

target_link_libraries(sample_no_scheduler PRIVATE
	mrubyc
	)

add_executable(sample_include
	sample_include.c
	)

target_link_libraries(sample_include PRIVATE
	mrubyc
	)

add_executable(sample_concurrent
	sample_concurrent.c
	)

target_link_libraries(sample_concurrent PRIVATE
	mrubyc
	)

add_executable(sample_myclass
	sample_myclass.c
	)

target_link_libraries(sample_myclass PRIVATE
	mrubyc
	)
