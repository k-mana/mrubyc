# SPDX-License-Identifier: BSD-3-Clause

cmake_minimum_required(VERSION 3.13)

project(mrubyc)

add_subdirectory(mrblib)
add_subdirectory(support)
add_subdirectory(src)

add_custom_target(mrubyc_lib
	DEPENDS mrblib mrubyc
	)

option(MRUBYC_SAMPLE "Building mruby/c samples" ON)
if(MRUBYC_SAMPLE)
add_subdirectory(sample_c)

add_custom_target(mrubyc_bin
	DEPENDS sample_concurrent sample_include sample_myclass sample_no_scheduler sample_scheduler
	)
endif()

find_package(Doxygen QUIET)

add_custom_target(docs
	COMMAND ${DOXYGEN_EXECUTABLE} Doxyfile
	WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
	)

file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/test/tmp)
file(RELATIVE_PATH TEST_DIR ${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/test)
file(RELATIVE_PATH TEST_TMP_DIR ${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_BINARY_DIR}/test/tmp)
file(RELATIVE_PATH MRUBYC_SRC_DIR ${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/src)
file(RELATIVE_PATH MRUBY_LIB_DIR ${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/test)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Mrubycfile.in ${CMAKE_CURRENT_BINARY_DIR}/Mrubycfile)

set(GLOBAL_RB ${mrblib_SOURCE_DIR}/global.rb)
file(STRINGS ${GLOBAL_RB} MRUBY_VERSION REGEX "MRUBY_VERSION")
string(REGEX REPLACE "MRUBY_VERSION *= *\"(.*)\"" "\\1" MRUBY_TAG ${MRUBY_VERSION})
file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/MRUBY_TAG "${MRUBY_TAG}")
file(TOUCH ${CMAKE_CURRENT_BINARY_DIR}/DOCKER_BUILD_DONE)

if(WIN32)
	set(GET_MRUBY_TAG_SCRIPT ${CMAKE_CURRENT_SOURCE_DIR}/tools/get_mruby_tag.bat)
	set(GET_CURRENT_MRUBY_TAG_SCRIPT ${CMAKE_CURRENT_SOURCE_DIR}/tools/get_current_mruby_tag.bat)
	set(BUILD_DOCKER_SCRIPT ${CMAKE_CURRENT_SOURCE_DIR}/tools/build_docker.bat)
	set(RUN_TEST_SCRIPT ${CMAKE_CURRENT_SOURCE_DIR}/tools/run_test.bat)
else()
	set(GET_MRUBY_TAG_SCRIPT ${CMAKE_CURRENT_SOURCE_DIR}/tools/get_mruby_tag.sh)
	set(GET_CURRENT_MRUBY_TAG_SCRIPT ${CMAKE_CURRENT_SOURCE_DIR}/tools/get_current_mruby_tag.sh)
	set(BUILD_DOCKER_SCRIPT ${CMAKE_CURRENT_SOURCE_DIR}/tools/build_docker.sh)
	set(RUN_TEST_SCRIPT ${CMAKE_CURRENT_SOURCE_DIR}/tools/run_test.sh)
	set(DEBUG_TEST_SCRIPT ${CMAKE_CURRENT_SOURCE_DIR}/tools/debug_test.sh)
endif()

add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/MRUBY_TAG
	COMMAND ${GET_MRUBY_TAG_SCRIPT} ${GLOBAL_RB}
	DEPENDS ${GLOBAL_RB}
	)

add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/CURRENT_MRUBY_TAG
	COMMAND ${GET_CURRENT_MRUBY_TAG_SCRIPT}
	DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/DOCKER_BUILD_DONE
	)

add_custom_target(check_tag
	COMMAND ${BUILD_DOCKER_SCRIPT} ${CMAKE_CURRENT_BINARY_DIR}/MRUBY_TAG ${CMAKE_CURRENT_BINARY_DIR}/CURRENT_MRUBY_TAG
	COMMAND ${CMAKE_COMMAND} -E touch ${CMAKE_CURRENT_BINARY_DIR}/DOCKER_BUILD_DONE
	WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
	USES_TERMINAL
	DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/MRUBY_TAG ${CMAKE_CURRENT_BINARY_DIR}/CURRENT_MRUBY_TAG
	)

add_custom_target(setup_test
	COMMAND ${BUILD_DOCKER_SCRIPT} ${CMAKE_CURRENT_BINARY_DIR}/MRUBY_TAG
	COMMAND ${CMAKE_COMMAND} -E touch ${CMAKE_CURRENT_BINARY_DIR}/DOCKER_BUILD_DONE
	WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
	USES_TERMINAL
	)

add_custom_target(test_host
	COMMAND ${RUN_TEST_SCRIPT} TEST=test_host SRC=${CMAKE_CURRENT_SOURCE_DIR} CC=gcc
	DEPENDS check_tag
	)

add_custom_target(test_arm
	COMMAND ${RUN_TEST_SCRIPT} TEST=test_arm SRC=${CMAKE_CURRENT_SOURCE_DIR} CC=arm-linux-gnueabi-gcc QEMU=qemu-arm-static
	DEPENDS check_tag
	)

add_custom_target(test
	DEPENDS test_host test_arm
	)

if(NOT WIN32)
add_custom_target(debug_test
	COMMAND ${DEBUG_TEST_SCRIPT} ${CMAKE_CURRENT_SOURCE_DIR}/src ${CMAKE_CURRENT_SOURCE_DIR}/test_host/test/tmp/test
	)
endif()
