# SPDX-License-Identifier: BSD-3-Clause

cmake_minimum_required(VERSION 3.13)

project(mrblib)

if(DEFINED MRBC)
	set(MRBC_EXECUTABLE ${MRBC})
elseif (DEFINED ENV{MRBC})
	set(MRBC_EXECUTABLE $ENV{MRBC})
else()
	set(MRBC_EXECUTABLE mrbc)
endif()

set(MRBLIB_C mrblib.c)
set(TARGET_MRBLIB_C ${CMAKE_SOURCE_DIR}/src/${MRBLIB_C})

set(SOURCES
	${CMAKE_CURRENT_SOURCE_DIR}/array.rb
	${CMAKE_CURRENT_SOURCE_DIR}/global.rb
	${CMAKE_CURRENT_SOURCE_DIR}/hash.rb
	${CMAKE_CURRENT_SOURCE_DIR}/numeric.rb
	${CMAKE_CURRENT_SOURCE_DIR}/object.rb
	${CMAKE_CURRENT_SOURCE_DIR}/range.rb
	${CMAKE_CURRENT_SOURCE_DIR}/string.rb
	)

add_custom_command(OUTPUT ${MRBLIB_C}
	COMMAND ${MRBC_EXECUTABLE} -Bmrblib_bytecode --remove-lv -o ${MRBLIB_C} ${SOURCES}
	COMMAND ${CMAKE_COMMAND} -E copy_if_different ${MRBLIB_C} ${TARGET_MRBLIB_C}
	DEPENDS ${SOURCES}
	)

add_custom_target(mrblib_c
	SOURCES ${MRBLIB_C}
	)

set(VERSION VERSION)
set(TARGET_VERSION ${mrubyc_SOURCE_DIR}/src/${VERSION})
if(WIN32)
	set(GEN_VERSION_SCRIPT ${mrubyc_SOURCE_DIR}/tools/gen_version_file.bat)
else()
	set(GEN_VERSION_SCRIPT ${mrubyc_SOURCE_DIR}/tools/gen_version_file.sh)
endif()

add_custom_command(OUTPUT ${VERSION}
	COMMAND ${GEN_VERSION_SCRIPT} ${CMAKE_CURRENT_SOURCE_DIR}/global.rb
	COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_BINARY_DIR}/${VERSION} ${TARGET_VERSION}
	DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/global.rb
	)

add_custom_target(versionfile
	SOURCES ${VERSION}
	)

add_custom_target(${PROJECT_NAME}
	DEPENDS mrblib_c versionfile
	)

add_custom_target(clean_${PROJECT_NAME}
	COMMAND ${CMAKE_COMMAND} -E remove ${TARGET_MRBLIB_C}
	COMMAND ${CMAKE_COMMAND} -E remove ${TARGET_VERSION}
	)
