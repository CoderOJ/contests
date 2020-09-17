#!/bin/bash
set -e

a=main
b=std

if [[ "$1" != "" ]] ; then
    a=$1
fi

if [[ "$2" != "" ]] ; then
    b=$2
fi

for ((i=0;;i++)) ; do
    python3 ./gen.py > data.in
    /usr/bin/time -o $a.time -f %e ./$a < data.in > $a.out
    /usr/bin/time -o $b.time -f %e ./$b < data.in > $b.out
    TIMEM=`cat $a.time`
    TIMES=`cat $b.time`
    if diff -Z ./$a.out ./$b.out ; then
        echo -e "Case $i: Accepted. \tTime: \t$a: $TIMEM \t$b: $TIMES"
    else 
        echo "Case $i: Wrong Answer"
        exit
    fi
done
