#!/bin/bash

SCRIPT_DIR=$(dirname $0)
ROOT_DIR=$(dirname $SCRIPT_DIR)
BUILD_DIR="$ROOT_DIR/build"

"$BUILD_DIR/server" 8080 &
"$BUILD_DIR/client" 127.0.0.1 8080
