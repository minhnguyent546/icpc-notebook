#!/usr/bin/env bash

FLAGS="-std=c++17 -DLOCAL -D_GLIBCXX_DEBUG -Wall -Wextra -pedantic"
g++ "$FLAGS" gen.cpp -o gen.out
g++ "$FLAGS" brute.cpp -o brute.out
g++ "$FLAGS" sol.cpp -o sol.out

num_tests="${1:-1000000}"
for (( i = 0; i < num_tests; ++i )); do
  ./gen.out > in
  ./brute.out < in > ans
  ./sol.out < in > out
  diff -Zb ans out || break
  echo "Test $i passed"
done
