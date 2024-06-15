#!/bin/bash

SCRIPT_DIR=$(dirname $0)
ROOT_DIR=$(dirname $SCRIPT_DIR)
BUILD_DIR="$ROOT_DIR/build"

# server open
echo "server open at port 9190"
"$BUILD_DIR/server/server" 9190 &
echo "server pid: $!"

# client open
echo "client open"
"$BUILD_DIR/client/client" 127.0.0.1 9190
