#!/bin/bash
cd ..

# Hardcoded directories to check
dirs=("src" "include" "tests")
c_std="23"

# Hardcoded include paths from your CMakeLists.txt
includes=(
    "-I${PWD}/libs/pugixml-1.15/src"
    "-I${PWD}/include"
    "-I${PWD}/include/helper"
)

for dir in "${dirs[@]}"; do
  if [ ! -d "$dir" ]; then
    printf "\e[37mWarning: $dir is not a directory or doesn't exist."
    continue
  fi

  echo "Checking directory: $dir"

  # Find .cpp and .hpp files recursively
  find "$dir" \( -name '*.cpp' -o -name '*.hpp' \) | while read -r file; do
    echo "Checking syntax of: $file"
    
    # Run g++ syntax check with  with includes
    g++ -fsyntax-only -std=c++"${c_std}" -Wall -Wextra -Werror -pedantic -Wconversion -Wsign-conversion -Wshadow -Wnull-dereference -Wold-style-cast -Woverloaded-virtual -Wdouble-promotion -Wformat=2 -Wimplicit-fallthrough -Wswitch-enum -Wuninitialized  "${includes[@]}" "$file"
    
    if [ $? -ne 0 ]; then
      echo "\e[36mSyntax errors found in $file"
    fi
  done
done
