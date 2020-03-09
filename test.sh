#!/bin/bash


for f in /dir/*.in
do
  echo -n "File ${f%/dir/} ";
  if diff "${f%in}"out <(./cmake-build-debug/smallProject) >/dev/null 2>&1
  then
    echo "passed tests"
  else
    echo "hasn't pass test";
  fi
done