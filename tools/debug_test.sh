#!/bin/bash
# SPDX-License-Identifier: BSD-3-Clause
# debug_test.sh <> <>

if [ $# -lt 2 ]; then
        echo "missing argument"
        exit 1
fi

gdb $(OPTION) --directory $1 --args $2
