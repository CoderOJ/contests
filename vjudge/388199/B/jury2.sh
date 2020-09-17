#!/bin/bash
set -e

for ((i=0;;i++)) ; do
    python3 ./gen.py > data.in
    ./main < data.in > my.out
    ./std < data.in > std.out
done
