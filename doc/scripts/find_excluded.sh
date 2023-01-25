#!/usr/bin/env bash 

mkdir -p build/
grep -PRho '^\s*\\negzeroinclude(\[\w*\])?{\K.*' ../../src/ | sed 's/.$//' > build/included_headers
extensions=(h py java bashrc sublime-build)
for extension in "${extensions[@]}"; do 
	find ../../src/ -name "*.$extension" | grep -vFf ./build/included_headers
done
