#!/bin/bash
# SPDX-License-Identifier: BSD-3-Clause
# get_current_mruby_tag.sh

docker run mrubyc-dev /bin/sh -c 'cd /work/mruby && git status | ruby -e"puts STDIN.first.split(\" \")[-1]"' > CURRENT_MRUBY_TAG 2> /dev/null
