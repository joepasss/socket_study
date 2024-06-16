#!/bin/bash

SCRIPT_DIR=$(dirname $0)
ROOT_DIR=$(dirname $SCRIPT_DIR)

if [ ! -d "$ROOT_DIR/build" ]; then
	mkdir $ROOT_DIR/build
fi

cmake -B "$ROOT_DIR/build" -S "$ROOT_DIR"

cd "$ROOT_DIR/build"

make
