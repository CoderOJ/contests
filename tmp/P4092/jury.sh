#!/bin/bash
for ((i=0;;i++)) ; do
    python3 ./gen.py > data.in
    ./main < data.in > my.out
    ./std < data.in > std.out
    if diff ./my.out ./std.out ; then
        echo "Case $i: Accepted"
    else 
        echo "Case $i: Wrong Answer"
        exit
    fi
done
