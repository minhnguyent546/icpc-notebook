#!/usr/bin/env bash

# This script checks for errors in c++ header files.

CXX="${CXX:-g++}"
CPP_VERSION="c++17"
COMPILE_FLAGS="-Wall -Wextra -Wshadow -fmax-errors=3"

trap 'rm -f "$temp" "$exec_file"' EXIT

mkdir -p build
file="$1"
temp="$(mktemp build/temp.XXXXXX.cpp)"
exec_file="${temp%.cpp}.out"
cat > "$temp" << EOF
#include "../src/contest/template.h"
#include "../$file"
EOF
$CXX -std=$CPP_VERSION $COMPILE_FLAGS "$temp" -o "$exec_file"
