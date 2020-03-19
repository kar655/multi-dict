#!/bin/bash

# make
passed=0
all=0

for f in $(find "$2" -name "*.in"); do
  echo -n "Testing ${f%.in}: "
  tmpOut=$(mktemp "TestXXXXXX.out")
  tmpErr=$(mktemp "TestXXXXXX.err")

  # time
  "$1" <"$f" >"$tmpOut" 2>"$tmpErr"
  # valgrind -q --error-exitcode=15 --leak-check=full --show-leak-kinds=all --errors-for-leak-kinds=all "$1" <"$f" >"$tmpOut" 2>"$tmpErr"

  if diff -q "${f%in}out" "$tmpOut" && diff -q "${f%in}err" "$tmpErr"; then
    echo "succeded"
    passed=$((passed + 1))
  else
    echo "hasn't succeded"
  fi

  all=$((all + 1))
  rm "$tmpOut"
  rm "$tmpErr"
done

echo "Passed $passed / $all"
# make clean
