#!/bin/bash
BUILD_DIR="../build/"
EXEC_NAME="tcash"

echo "Building Release version..."

mkdir -p "$BUILD_DIR"
cmake -S .. -B "$BUILD_DIR" -DCMAKE_BUILD_TYPE=Release
cmake --build "$BUILD_DIR"

mv "${BUILD_DIR}tcash" "../bin/release/${EXEC_NAME}"
echo "Release build complete."