#!/usr/bin/env bash

# This script checks for errors in c++ header files.

CPP_VERSION="c++17"
COMPILE_FLAGS="-Wall -Wextra -Wshadow -fmax-errors=3 -DLOCAL"

mkdir -p build
file="$1"
temp="build/temp.cpp"
cat > "$temp" << EOF
#include "../src/contest/template.h"
#include "../$file"
EOF
g++ -std=$CPP_VERSION $COMPILE_FLAGS "$temp" && rm a.out "$temp"
