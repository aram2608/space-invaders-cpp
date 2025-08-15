#!/bin/bash

export VCPKG_ROOT=~/dev/tools/vcpkg

cmake -B si -S . -DCMAKE_TOOLCHAIN_FILE=$VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake
cmake --build si