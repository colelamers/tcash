#!/bin/bash
BUILD_DIR="../build/"
EXEC_NAME="tcash"

echo "Building Debug version..."

mkdir -p "$BUILD_DIR"
cmake -S .. -B "$BUILD_DIR" -DCMAKE_BUILD_TYPE=Debug
cmake --build "$BUILD_DIR"

mv "${BUILD_DIR}${EXEC_NAME}" "../bin/debug/${EXEC_NAME}"
echo "Debug build complete."