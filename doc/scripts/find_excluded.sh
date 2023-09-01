#!/usr/bin/env bash 

mkdir -p build/
grep -PRho '^\s*\\negzeroinclude(\[\w*\])?{\K.*' src/ | sed 's/.$//' > build/included_headers
exts=(h py java bashrc sublime-build)
for ext in "${exts[@]}"; do 
  find src/ -name "*.$ext" -type f | grep -vFf ./build/included_headers
done
exit 0
