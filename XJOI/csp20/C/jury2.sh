#!/bin/bash

for ((i=0;;i++)) ; do
    python3 ./gen.py > data.in
    ./main2 < data.in > main2.out
    if ./valid data.in main2.out ; then
        echo -e Case $i: Accepted
    else
        exit
    fi
done
