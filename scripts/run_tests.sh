#!/usr/bin/env bash

# This script compiles and runs all tests in tests/.
# Files starting with `_` are skipped.

CXX="${CXX:-g++}"
CPP_VERSION="c++17"
COMPILE_FLAGS="-O2 -Wall -Wextra -Wshadow -Wfloat-equal -fmax-errors=3 -pedantic"
TIME_LIMIT="${TIME_LIMIT:-60}" # seconds per test

COLOR_OFF='\033[0m'
BGREEN='\033[1;32m'
BRED='\033[1;31m'
NORMAL_TO_NANO="1000000000"

usage() {
  echo "Usage: $0 [-j jobs] [dir]"
  echo "  -j jobs   number of tests to run in parallel (default: 2)"
}

JOBS=2
while getopts "j:h" opt; do
  case "$opt" in
    j) JOBS="$OPTARG" ;;
    h) usage; exit 0 ;;
    *) usage >&2; exit 2 ;;
  esac
done
shift $(( OPTIND - 1 ))

if [[ ! "$JOBS" =~ ^[1-9][0-9]*$ ]]; then
  echo "error: number of jobs must be a positive integer, got '${JOBS}'" >&2
  exit 2
fi

DIR="${1:-.}"
BUILD_DIR="${DIR}/build"
LOG_FILE="${BUILD_DIR}/tests.log"
RESULT_DIR="$(mktemp -d)"

trap 'rm -rf "${RESULT_DIR}"' EXIT

script_start_time=$(date +%s%N)

tests=($(find "${DIR}/tests" -name "*.cpp" -type f ! -name "_*" | sort))
echo "Skipped tests: "
find "${DIR}/tests" -name "_*.cpp" -type f | sort
echo

[[ ! -d "${BUILD_DIR}" ]] && mkdir -p "$BUILD_DIR"

declare -i pass=0
declare -a fail_tests

test_size="${#tests[@]}"

run_one() {
  local idx="$1"
  local test="$2"
  local b_test="${test#./*/}"
  local exec_file="${RESULT_DIR}/${idx}.bin"
  local start_time end_time elapsed status exit_code
  start_time=$(date +%s%N)
  if ! $CXX -std=$CPP_VERSION $COMPILE_FLAGS "$test" -o "$exec_file"; then
    exit_code=1
    status="${BRED}COMPILE ERROR${COLOR_OFF}"
  else
    timeout "$TIME_LIMIT" "$exec_file" > /dev/null
    exit_code=$?
    if (( exit_code == 124 )); then
      status="${BRED}TIMEOUT${COLOR_OFF}"
    elif (( exit_code != 0 )); then
      status="${BRED}FAILED${COLOR_OFF}"
    else
      status="${BGREEN}OK${COLOR_OFF}"
    fi
  fi
  end_time=$(date +%s%N)
  elapsed=$(echo "($end_time - $start_time) / $NORMAL_TO_NANO" | bc -l)
  printf "[%d/%d] %s:\n[%b, finished in %0.1fs]\n\n" \
    "$idx" "$test_size" "$b_test" "$status" "$elapsed" > "${RESULT_DIR}/${idx}.out"
  # Written last: its existence marks the result as complete.
  echo "$exit_code" > "${RESULT_DIR}/${idx}.status"
}

# Prints finished results in the original test order.
declare -i next_to_print=1
print_ready() {
  while (( next_to_print <= test_size )) && [[ -f "${RESULT_DIR}/${next_to_print}.status" ]]; do
    cat "${RESULT_DIR}/${next_to_print}.out"
    next_to_print+=1
  done
}

echo "Running ${test_size} tests with ${CXX} and ${JOBS} job(s)..."
echo

for i in "${!tests[@]}"; do
  while (( $(jobs -rp | wc -l) >= JOBS )); do
    wait -n
    print_ready
  done
  run_one "$(( i + 1 ))" "${tests[$i]}" 2> "${RESULT_DIR}/$(( i + 1 )).log" &
done
while [[ -n "$(jobs -rp)" ]]; do
  wait -n
  print_ready
done
wait
print_ready

# Collect results in the original test order.
: > "${LOG_FILE}"
for i in "${!tests[@]}"; do
  idx=$(( i + 1 ))
  cat "${RESULT_DIR}/${idx}.log" >> "${LOG_FILE}"
  if [[ "$(cat "${RESULT_DIR}/${idx}.status" 2>/dev/null)" == "0" ]]; then
    pass+=1
  else
    fail_tests+=("${tests[$i]#./*/}")
  fi
done

script_end_time=$(date +%s%N)
script_elapsed=$(echo "($script_end_time - $script_start_time) / $NORMAL_TO_NANO" | bc -l)
printf "[Elapsed time: %0.1fs]\n" "$script_elapsed"

fail=${#fail_tests[@]}
if (( fail == 0 )); then
  echo "Everything is good."
  rm -f "${LOG_FILE}"
  exit 0
else
  echo "Passed: $pass/$(( pass + fail ))"
  echo "Failed tests: "
  for test in "${fail_tests[@]}"; do
    echo "  $test"
  done
  echo "Log file: ${LOG_FILE}"
  exit 1
fi
