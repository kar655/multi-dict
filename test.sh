#!/bin/bash
# ./test.sh ./forests dir
passed=0
all=0

for f in $(find $2 -name "*.in")
do
  echo -n "Test ${f%.in}: ";
  tmpOut=$(mktemp "XXXXXX.out")
  tmpErr=$(mktemp "XXXXXX.err")

  $1 <"$f" >"$tmpOut" 2>"$tmpErr"

  if diff -q "${f%in}out" "$tmpOut" && diff -q "${f%in}err" "$tmpErr"
  then
    echo "succeded"
    passed=$((passed + 1))
  else
    echo "hasn't succeded";
  fi

  all=$((all + 1))
  rm "$tmpOut"
  rm "$tmpErr"
done

echo "Passed $passed / $all"