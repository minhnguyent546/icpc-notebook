#!/usr/bin/env bash 

CPP_VERSION="c++17"
COMPILE_FLAGS="-Wall -Wextra -Wshadow -fmax-errors=3 -DLOCAL"

DIR="${1:-.}"
SCRIPT_DIR="${DIR}/doc/scripts"

# Using precompiled header to improve performance.
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
		echo "[Fail to compile ${b_header}, exit Code=${exitCode}]"
		fail_headers+=("${b_header}")
	else
		echo "[ok]"
		pass+=1
	fi
	echo 
done

rm -f "${DIR}/src/contest/template.h.gch"

fail=${#fail_headers[@]}
if (( fail == 0 )); then
	echo "Everything is good."
	exit 0
else
	echo "Pass $pass/$(( pass + fail ))"
	echo "Failed headers: "
	# echo "${fail_headers[@]}"
	for header in "${fail_headers[@]}"; do 
		echo "$header"
	done
	exit 1
fi
