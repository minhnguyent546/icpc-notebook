#!/usr/bin/env bash 

CPP_VERSION="c++17"
COMPILE_FLAGS="-Wall -Wextra -Wshadow -fmax-errors=3 -DLOCAL"

COLOR_OFF='\033[0m'
BMAGENTA='\033[1;35m'
BGREEN='\033[1;32m'
NORMAL_TO_NANO="1000000000"

DIR="${1:-.}"
SCRIPT_DIR="${DIR}/doc/scripts"
BUILD_DIR="${DIR}/build"
LOG_FILE="${BUILD_DIR}/compile.log"

trap 'rm -f "${DIR}/src/contest/template.h.gch"' EXIT

# Using precompiled header to improve performance.
echo "Precompiling ${DIR}/src/contest/template.h..."
g++ -std=$CPP_VERSION $COMPILE_FLAGS -x c++-header "${DIR}/src/contest/template.h"

if [ ! -f "${SCRIPT_DIR}/skip_headers" ]; then
  touch "${SCRIPT_DIR}/skip_headers"
fi
headers=$(find "${DIR}/src" -name "*.h" -type f | grep -vFf "${SCRIPT_DIR}/skip_headers")
echo "Skipped headers: "
find "${DIR}/src" -name "*.h" -type f | grep -Ff "${SCRIPT_DIR}/skip_headers"
echo

[[ ! -d "${BUILD_DIR}" ]] && mkdir -p "$BUILD_DIR"

declare -i pass=0
declare -a fail_headers
for header in $headers; do
  b_header="${header#./*/}"
  echo "${b_header}:"
  start_time=$(date +%s%N)
  ${SCRIPT_DIR}/compile_header.sh "$header"
  exitCode=$?
  end_time=$(date +%s%N)
  elapsed=$(echo "($end_time - $start_time) / $NORMAL_TO_NANO" | bc -l)
  if (( exitCode != 0 )); then
    echo -e "[Failed to compile ${BMAGENTA}${b_header}${COLOR_OFF}, exitCode=${exitCode}]"
    fail_headers+=("${b_header}")
  else
    printf "[${BGREEN}OK${COLOR_OFF}, finished in %0.1fs]\n" "$elapsed"
    pass+=1
  fi
  echo
done 2> "${LOG_FILE}"

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
