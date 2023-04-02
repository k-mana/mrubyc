# SPDX-License-Identifier: BSD-3-Clause

cmake_minimum_required(VERSION 3.13)

if (DEFINED MRBC_USE_HAL)
	string(TOLOWER hal_${MRBC_USE_HAL} HAL_DIR)
elseif(DEFINED ENV{MRBC_USE_HAL})
	set(HAL_DIR $ENV{MRBC_USE_HAL})
elseif(DEFINED ENV{MRBC_USE_HAL_POSIX})
	set(HAL_DIR hal_posix)
elseif(DEFINED ENV{MRBC_USE_HAL_PSOC5LP})
	set(HAL_DIR hal_psoc5lp)
elseif(DEFINED ENV{MRBC_USE_HAL_ESP32})
	set(HAL_DIR hal_esp32)
elseif(DEFINED ENV{MRBC_USE_HAL_PIC24})
	set(HAL_DIR hal_pic24)
elseif(DEFINED ENV{MRBC_USE_HAL_RP2040})
	set(HAL_DIR hal_rp2040)
else()
	set(HAL_DIR hal_posix)
endif()
message(STATUS "Selected HAL: ${HAL_DIR}")

if(DEFINED MAX_VM_COUNT)
	add_compile_definitions(MAX_MV_COUNT=${MAX_VM_COUNT})
	message(STATUS "MAX_VM_COUNT: ${MAX_VM_COUNT}")
endif()

if(DEFINED MAX_REGS_SIZE)
	add_compile_definitions(MAX_REGS_SIZE=${MAX_REGS_SIZE})
	message(STATUS "MAX_REGS_SIZE: ${MAX_REGS_SIZE}")
endif()

if(DEFINED MAX_SYMBOLS_COUNT)
	add_compile_definitions(MAX_SYMBOLS_COUNT=${MAX_SYMBOLS_COUNT})
	message(STATUS "MAX_SYMBOLS_COUNT: ${MAX_SYMBOLS_COUNT}")
endif()

if(DEFINED MRBC_USE_FLOAT)
	add_compile_definitions(MRBC_USE_FLOAT=${MRBC_USE_FLOAT})
	message(STATUS "MRBC_USE_FLOAT: ${MRBC_USE_FLOAT}")
endif()

if(DEFINED MRBC_USE_MATH)
	add_compile_definitions(MRBC_USE_MATH=${MRBC_USE_MATH})
	message(STATUS "MRBC_USE_MATH: ${MRBC_USE_MATH}")
	if(NOT ${MRBC_USE_MATH} EQUAL 0)
		if(NOT MSVC)
			list(APPEND LIBS -lm)
		endif()
	endif()
endif()

if(DEFINED MRBC_USE_STRING)
	add_compile_definitions(MRBC_USE_STRING=${MRBC_USE_STRING})
	message(STATUS "MRBC_USE_STRING: ${MRBC_USE_STRING}")
endif()

if({MRBC_ENDIAN STREQUAL "big")
	add_compile_definitions(MRBC_BIG_ENDIAN)
	message(STATUS "MRBC_BIG_ENDIAN")
elseif(MRBC_ENDIAN STREQUAL "little")
	add_compile_definitions(MRBC_LITTLE_ENDIAN)
	message(STATUS "MRBC_LITTLE_ENDIAN")
endif()

if(MRBC_REQUIRE_ALIGNMENT EQUAL 32)
	add_compile_definitions(MRBC_REQUIRE_32BIT_ALIGNMENT)
	message(STATUS "MRBC_REQUIRE_32BIT_ALIGNMENT")
elseif(MRBC_REQUIRE_ALIGNMENT EQUAL 64)
	add_compile_definitions(MRBC_REQUIRE_64BIT_ALIGNMENT)
	message(STATUS "MRBC_REQUIRE_64BIT_ALIGNMENT")
endif()

if(NOT MSVC)
	add_compile_options(-Wall -Wpointer-arith -g)
endif()

add_subdirectory(${HAL_DIR})

add_library(mrubyc STATIC)

target_sources(mrubyc PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/alloc.c
	${CMAKE_CURRENT_SOURCE_DIR}/c_array.c
	${CMAKE_CURRENT_SOURCE_DIR}/c_hash.c
	${CMAKE_CURRENT_SOURCE_DIR}/c_math.c
	${CMAKE_CURRENT_SOURCE_DIR}/c_numeric.c
	${CMAKE_CURRENT_SOURCE_DIR}/c_object.c
	${CMAKE_CURRENT_SOURCE_DIR}/c_range.c
	${CMAKE_CURRENT_SOURCE_DIR}/c_string.c
	${CMAKE_CURRENT_SOURCE_DIR}/class.c
	${CMAKE_CURRENT_SOURCE_DIR}/console.c
	${CMAKE_CURRENT_SOURCE_DIR}/error.c
	${CMAKE_CURRENT_SOURCE_DIR}/global.c
	${CMAKE_CURRENT_SOURCE_DIR}/keyvalue.c
	${CMAKE_CURRENT_SOURCE_DIR}/load.c
	${CMAKE_CURRENT_SOURCE_DIR}/mrblib.c
	${CMAKE_CURRENT_SOURCE_DIR}/rrt0.c
	${CMAKE_CURRENT_SOURCE_DIR}/symbol.c
	${CMAKE_CURRENT_SOURCE_DIR}/value.c
	${CMAKE_CURRENT_SOURCE_DIR}/vm.c
	)

target_include_directories(mrubyc PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}
	)

target_link_libraries(mrubyc PUBLIC
	${HAL_DIR}
	${LIBS}
	)

find_package(Ruby QUIET)

if(MAKE_SYMBOL_TABLE)
	set(MAKE_SYMBOL_TABLE ${MAKE_SYMBOL_TABLE})
elseif(DEFINED ENV{MAKE_SYMBOL_TABLE})
	set(MAKE_SYMBOL_TABLE $ENV{MAKE_SYMBOL_TABLE})
else()
	set(MAKE_SYMBOL_TABLE ${support_SOURCE_DIR}/make_symbol_table.rb)
endif()

if(DEFINED MAKE_METHOD_TABLE)
	set(MAKE_METHOD_TABLE ${MAKE_METHOD_TABLE})
elseif(DEFINED ENV{MAKE_METHOD_TABLE})
	set(MAKE_METHOD_TABLE $ENV{MAKE_METHOD_TABLE})
else()
	set(MAKE_METHOD_TABLE ${support_SOURCE_DIR}/make_method_table.rb)
endif()

function(add_make_method_table SOURCE TARGET)
	add_custom_command(OUTPUT ${TARGET} ${ARGN}
		COMMAND ${Ruby_EXECUTABLE} ${MAKE_METHOD_TABLE} ${CMAKE_CURRENT_SOURCE_DIR}/${SOURCE}
		COMMAND ${CMAKE_COMMAND} -E copy_if_different ${TARGET} ${ARGN} ${CMAKE_CURRENT_SOURCE_DIR}
		DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/${SOURCE}
		)
	set(METHOD_TABLE_HEADERS ${METHOD_TABLE_HEADERS} ${TARGET} ${ARGN} PARENT_SCOPE)
	foreach(v IN LISTS TARGET ARGN)
		set(AUTOGEN_METHOD_TABLE ${AUTOGEN_METHOD_TABLE} ${CMAKE_CURRENT_SOURCE_DIR}/${v})
	endforeach()
	set(AUTOGEN_METHOD_TABLE ${AUTOGEN_METHOD_TABLE} PARENT_SCOPE)
endfunction()

add_make_method_table(c_array.c _autogen_class_array.h)
add_make_method_table(c_numeric.c _autogen_class_integer.h _autogen_class_float.h)
add_make_method_table(c_hash.c _autogen_class_hash.h)
add_make_method_table(c_math.c _autogen_class_math.h)
add_make_method_table(c_object.c _autogen_class_object.h)
add_make_method_table(c_range.c _autogen_class_range.h)
add_make_method_table(c_string.c _autogen_class_string.h)
add_make_method_table(symbol.c _autogen_class_symbol.h)
add_make_method_table(error.c _autogen_class_exception.h)

set(SYMBOL_TABLE_HEADER _autogen_builtin_symbol.h)
set(AUTOGEN_SYMBOL_TABLE ${CMAKE_CURRENT_SOURCE_DIR}/${SYMBOL_TABLE_HEADER})

add_custom_target(autogen
	SOURCES ${SYMBOL_TABLE_HEADER}
	)

add_custom_command(OUTPUT ${SYMBOL_TABLE_HEADER}
	COMMAND ${Ruby_EXECUTABLE} ${MAKE_SYMBOL_TABLE} --path-c ${CMAKE_CURRENT_SOURCE_DIR} --path-rb ${mrblib_SOURCE_DIR} -o ${SYMBOL_TABLE_HEADER}
	COMMAND ${CMAKE_COMMAND} -E copy_if_different ${SYMBOL_TABLE_HEADER} ${CMAKE_CURRENT_SOURCE_DIR}
	DEPENDS ${METHOD_TABLE_HEADERS}
	)

add_custom_target(clean_autogen
	COMMAND ${CMAKE_COMMAND} -E remove ${METHOD_TABLE_HEADERS}
	COMMAND ${CMAKE_COMMAND} -E remove ${AUTOGEN_METHOD_TABLE}
	COMMAND ${CMAKE_COMMAND} -E remove ${SYMBOL_TABLE_HEADER}
	COMMAND ${CMAKE_COMMAND} -E remove ${AUTOGEN_SYMBOL_TABLE}
	)
