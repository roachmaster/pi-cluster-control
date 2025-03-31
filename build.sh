#!/bin/bash

set -e

MODULE=$1
BUILD_DIR="build"

if [ -z "$MODULE" ]; then
  echo "Usage: ./build.sh <module_name | all>"
  exit 1
fi

# Run environment check
./bootstrap.sh

# Create build folder if missing
mkdir -p "$BUILD_DIR"
cd "$BUILD_DIR"

# Run cmake once if needed
if [ ! -f "Makefile" ]; then
  cmake ..
fi

# Build specific target or all
if [ "$MODULE" == "all" ]; then
  make
else
  make "$MODULE"
fi

echo "✅ Build complete for: $MODULE"
