#!/bin/bash
# SPDX-License-Identifier: BSD-3-Clause
# get_mruby_tag.sh mrblib/globa.rb

if [ $# -lt 1 ]; then
        echo "missing argument"
        exit 1
fi
if [ ! -e $1 ]; then
        echo "mrblib/global.rb file does not exist"
        exit 1
fi
grep MRUBY_VERSION $1 | sed 's/MRUBY_VERSION *= *"\(.*\)"/\1/' > MRUBY_TAG 2> /dev/null
