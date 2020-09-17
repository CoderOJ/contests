#!/bin/bash
for ((i=0;;i++)) ; do
    python3 ./gen.py > data.in
    /usr/bin/time -o my.time -f %e ./main < data.in > my.out
    /usr/bin/time -o std.time -f %e ./std < data.in > std.out
    TIMEM=`cat my.time`
    TIMES=`cat std.time`
    if diff -Z ./my.out ./std.out ; then
        echo -e "Case $i: Accepted. \tTime: \tmain: $TIMEM \tstd: $TIMES"
    else 
        echo "Case $i: Wrong Answer"
        exit
    fi
done
