#!/bin/bash
# SPDX-License-Identifier: BSD-3-Clause
# gen_version_file.sh mrblib/global.rb

if [ $# -lt 1 ]; then
        echo "missing argument"
        exit 1
fi
if [ ! -e $1 ]; then
        echo "mrblib/global.rb file does not exist"
        exit 1
fi
sed -E -e '/^[A-Z]+_VERSION/!d' $1 > VERSION 2> /dev/null
