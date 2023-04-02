#!/bin/bash
# SPDX-License-Identifier: BSD-3-Clause
# build_docker.sh <MRUBY_TAG file> [<CURRENT_MRUBY_TAG file>]

if [ $# -lt 1 ]; then
	echo "missing argument"
	exit 1
fi
if [ ! -e $1 ]; then
	echo "MRUBY_TAG file does not exist"
	exit 1
fi
MRUBY_TAG=${MRUBY_TAG:-$(cat $1)}
USER_ID=${USER_ID:-$(id -u)}

if [ $# -ge 2 ]; then
	if [ ! -e $2 ]; then
		echo "CURRENT_MRUBY_TAG file does not exist"
		exit 1
	fi
	CURRENT_MRUBY_TAG=$(cat $2)
	if [ "$CURRENT_MRUBY_TAG" = "$MRUBY_TAG" ]; then
		echo "skip docker build."
		exit 0
	fi
fi

docker build -t mrubyc-dev --build-arg MRUBY_TAG=$MRUBY_TAG --build-arg USER_ID=$USER_ID $options .
