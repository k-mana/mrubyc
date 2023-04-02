REM SPDX-License-Identifier: BSD-3-Clause
REM run_test.bat TEST=<> SRC=<> CC=<> [QEMU=<>]

:ARGPARSE
IF "%1" == "TEST" (
	CALL :set_test %2
	SHIFT
) ELSE IF "%1" == "SRC" (
	CALL :set_src %2
	SHIFT
) ELSE IF "%1" == "CC" (
	CALL :set_cc %2
	SHIFT
) ELSE IF "%1" == "QEMU" (
	CALL :set_qemu %2
	SHIFT
)
SHIFT
IF NOT "%1" == "" GOTO ARGPARSE

docker run --mount type=bind,src=%SRC%,dst=/work/mrubyc -e CFLAGS="-DMRBC_INT64 %CFLAGS%" mrubyc-dev /bin/sh -c "cmake -S . -B %TEST_DIR% -MRBC=/work/mruby/build/host/bin/mrbc -DMRBC_USE_HAL=posix -DMRBC_USE_MATH=1 -DMAX_SYMBOLS_COUNT=1000;cd %TEST_DIR%;CC=%CC% QEMU=%QEMU% bundle exec mrubyc-test --every=10 --mrbc-path=/work/mruby/build/host/bin/mrbc %file%"

GOTO :EOF

:set_test
	SET TEST_DIR=%1
	EXIT /B 0

:set_src
	SET SRC=%1
	EXIT /B 0

:set_cc
	SET CC=%1
	EXIT /B 0

:set_qemu
	set QEMU=%1
	EXIT /B 0
