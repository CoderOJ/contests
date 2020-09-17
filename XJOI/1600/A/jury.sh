#!/bin/bash
for ((i=0;;i++)) ; do
    python3 ./gen.py > data.in
    /usr/bin/time -o $1.time -f %e ./$1 < data.in > $1.out
    /usr/bin/time -o $2.time -f %e ./$2 < data.in > $2.out
    TIMEM=`cat $1.time`
    TIMES=`cat $2.time`
    if diff -Z ./$1.out ./$2.out ; then
        echo -e "Case $i: Accepted. \tTime: \t$1: $TIMEM \t$2: $TIMES"
    else 
        echo "Case $i: Wrong Answer"
        exit
    fi
done
