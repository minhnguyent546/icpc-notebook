#!/usr/bin/env bash 

CPP_VERSION="c++17"
COMPILE_FLAGS="-Wall -Wextra -Wshadow -fmax-errors=3 -DLOCAL"

COLOR_OFF='\033[0m'
BMAGENTA='\033[1;35m'

DIR="${1:-.}"
SCRIPT_DIR="${DIR}/doc/scripts"
LOG_FILE="${DIR}/build/compile.log"

trap 'rm -f "${DIR}/src/contest/template.h.gch"' EXIT

# Using precompiled header to improve performance.
echo "Precompiling ${DIR}/src/contest/template.h..."
g++ -std=$CPP_VERSION $COMPILE_FLAGS -x c++-header "${DIR}/src/contest/template.h"

headers=$(find "${DIR}/src" -name "*.h" -type f | grep -vFf "${SCRIPT_DIR}/skip_headers")
echo "Skipped headers: "
find "${DIR}/src" -name "*.h" -type f | grep -Ff "${SCRIPT_DIR}/skip_headers"
echo

declare -i pass=0
declare -a fail_headers
for header in $headers; do 
  b_header="${header#./*/}"
  echo "${b_header}:"
  ${SCRIPT_DIR}/compile_header.sh "$header"
  exitCode=$?
  if (( exitCode != 0 )); then
    echo -e "[Failed to compile ${BMAGENTA}${b_header}${COLOR_OFF}, exitCode=${exitCode}]"
    fail_headers+=("${b_header}")
  else
    echo "[ok]"
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
