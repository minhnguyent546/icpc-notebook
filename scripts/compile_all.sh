#!/usr/bin/env bash

CXX="${CXX:-g++}"
CPP_VERSION="c++17"
COMPILE_FLAGS="-Wall -Wextra -Wshadow -Wfloat-equal -fmax-errors=3 -pedantic"

COLOR_OFF='\033[0m'
BMAGENTA='\033[1;35m'
BGREEN='\033[1;32m'
BRED='\033[1;31m'
NORMAL_TO_NANO="1000000000"

usage() {
  echo "Usage: $0 [-j jobs] [dir]"
  echo "  -j jobs   number of headers to compile in parallel (default: 2)"
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
SCRIPT_DIR="${DIR}/scripts"
BUILD_DIR="${DIR}/build"
LOG_FILE="${BUILD_DIR}/compile.log"
RESULT_DIR="$(mktemp -d)"

trap 'rm -f "${DIR}/src/contest/template.h.gch"; rm -rf "${RESULT_DIR}"' EXIT

script_start_time=$(date +%s%N)

# Using precompiled header to improve performance.
echo "Precompiling ${DIR}/src/contest/template.h with ${CXX}..."
$CXX -std=$CPP_VERSION $COMPILE_FLAGS -x c++-header "${DIR}/src/contest/template.h"

if [ ! -f "${SCRIPT_DIR}/skip_headers" ]; then
  touch "${SCRIPT_DIR}/skip_headers"
fi
headers=($(find "${DIR}/src" -name "*.h" -type f | grep -vFf "${SCRIPT_DIR}/skip_headers"))
echo "Skipped headers: "
find "${DIR}/src" -name "*.h" -type f | grep -Ff "${SCRIPT_DIR}/skip_headers"
echo

[[ ! -d "${BUILD_DIR}" ]] && mkdir -p "$BUILD_DIR"

declare -i pass=0
declare -a fail_headers

header_size="${#headers[@]}"

compile_one() {
  local idx="$1"
  local header="$2"
  local b_header="${header#./*/}"
  local start_time end_time elapsed status
  start_time=$(date +%s%N)
  "${SCRIPT_DIR}"/compile_header.sh "$header"
  local exit_code=$?
  end_time=$(date +%s%N)
  elapsed=$(echo "($end_time - $start_time) / $NORMAL_TO_NANO" | bc -l)
  if (( exit_code != 0 )); then
    status="${BRED}FAILED${COLOR_OFF}"
  else
    status="${BGREEN}OK${COLOR_OFF}"
  fi
  printf "[%d/%d] %s:\n[%b, finished in %0.1fs]\n\n" \
    "$idx" "$header_size" "$b_header" "$status" "$elapsed" > "${RESULT_DIR}/${idx}.out"
  # Written last: its existence marks the result as complete.
  echo "$exit_code" > "${RESULT_DIR}/${idx}.status"
}

# Prints finished results in the original header order.
declare -i next_to_print=1
print_ready() {
  while (( next_to_print <= header_size )) && [[ -f "${RESULT_DIR}/${next_to_print}.status" ]]; do
    cat "${RESULT_DIR}/${next_to_print}.out"
    next_to_print+=1
  done
}

echo "Compiling ${header_size} headers with ${JOBS} job(s)..."
echo

for i in "${!headers[@]}"; do
  while (( $(jobs -rp | wc -l) >= JOBS )); do
    wait -n
    print_ready
  done
  compile_one "$(( i + 1 ))" "${headers[$i]}" 2> "${RESULT_DIR}/$(( i + 1 )).log" &
done
while [[ -n "$(jobs -rp)" ]]; do
  wait -n
  print_ready
done
wait
print_ready

# Collect results in the original header order.
: > "${LOG_FILE}"
for i in "${!headers[@]}"; do
  idx=$(( i + 1 ))
  cat "${RESULT_DIR}/${idx}.log" >> "${LOG_FILE}"
  if [[ "$(cat "${RESULT_DIR}/${idx}.status" 2>/dev/null)" == "0" ]]; then
    pass+=1
  else
    fail_headers+=("${headers[$i]#./*/}")
  fi
done

script_end_time=$(date +%s%N)
script_elapsed=$(echo "($script_end_time - $script_start_time) / $NORMAL_TO_NANO" | bc -l)
printf "[Elapsed time: %0.1fs]\n" "$script_elapsed"

fail=${#fail_headers[@]}
if (( fail == 0 )); then
  echo "Everything is good."
  rm -f "${LOG_FILE}"
  exit 0
else
  echo "Passed: $pass/$(( pass + fail ))"
  echo "Failed headers: "
  for header in "${fail_headers[@]}"; do
    echo "  $header"
  done
  echo "Log file: ${LOG_FILE}"
  exit 1
fi
