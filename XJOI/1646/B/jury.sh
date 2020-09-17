#!/bin/bash
set -e

a=main
b=std
g='python3 ./gen.py'

if [[ "$1" != "" ]] ; then
    a=$1
fi

if [[ "$2" != "" ]] ; then
    b=$2
fi

if [[ "$3" != "" ]] ; then
    g=$3
fi

echo -e Jury started between \'$a\' and \'$b\', using generator command \'$g\'

for ((i=0;;i++)) ; do
    # python3 ./gen.py > data.in
    /usr/bin/time -o gen.time -f %e $g > data.in
    /usr/bin/time -o $a.time -f %e ./$a < data.in > $a.out
    /usr/bin/time -o $b.time -f %e ./$b < data.in > $b.out
    TIMEG=`cat gen.time`
    TIMEM=`cat $a.time`
    TIMES=`cat $b.time`
    if diff -Z ./$a.out ./$b.out ; then
        echo -e "Case $i: Accepted. \tTime: \tgen: $TIMEG\t$a: $TIMEM \t$b: $TIMES"
    else 
        echo "Case $i: Wrong Answer"
        exit
    fi
done
