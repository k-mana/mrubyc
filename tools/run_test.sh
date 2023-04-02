#!/bin/bash
# SPDX-License-Identifier: BSD-3-Clause
# run_test.sh

while [ $# -gt 0 ]
do
	ARG=$1
	case $ARG in
		TEST=*)
			TEST_DIR=${ARG#TEST=}
			;;
		SRC=*)
			SRC=${ARG#SRC=}
			;;
		CC=*)
			CC=${CC:-${ARG#CC=}}
			;;
		QEMU=*)
			QEMU=${QEMU:-${ARG#QEMU=}}
			;;
		*)
			;;
	esac
	shift
done

docker run --mount type=bind,src=$SRC/,dst=/work/mrubyc -e CFLAGS="-DMRBC_INT64 $CFLAGS" mrubyc-dev /bin/sh -c "cmake -S . -B $TEST_DIR -DMRBC=/work/mruby/build/host/bin/mrbc -DMRBC_USE_HAL=posix -DMRBC_USE_MATH=1 -DMAX_SYMBOLS_COUNT=1000;cd $TEST_DIR;CC=$CC QEMU=$QEMU bundle exec mrubyc-test --every=10 --mrbc-path=/work/mruby/build/host/bin/mrbc $file"
