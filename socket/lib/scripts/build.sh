#!/bin/bash

SCRIPT_DIR=$(dirname $0)
ROOT_DIR=$(dirname $SCRIPT_DIR)

cmake -S "$ROOT_DIR" -B "$ROOT_DIR/build"
cd "$ROOT_DIR/build"
make
