#!/bin/bash

SCRIPT_DIR=$(dirname $0)
ROOT_DIR=$(dirname $SCRIPT_DIR)
BUILD_DIR="$ROOT_DIR/build"

"$BUILD_DIR/low_open"
"$BUILD_DIR/low_read"
