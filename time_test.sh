#!/bin/bash

for f in tests/*.in
do
  time /home/karol/Desktop/MIMUW/IPP/smallProject/cmake-build-debug/smallProject <"$f" >"${f%in}"out
done