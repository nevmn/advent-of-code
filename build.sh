#!/usr/bin/env bash

for file in *.c; do
  gcc -Wall -Wpedantic -Wextra \
    -I. \
    -c \
    -g \
    ./"$file"
done

gcc -Wall -Wpedantic -Wextra \
  -I. \
  -g \
  -o aoc2015 \
  ./*.o
