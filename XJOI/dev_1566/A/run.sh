#!/bin/bash
set -e

case="1 4 5 10 14 18"

for i in $case ; do
    echo $i
    ./main < ./ex_chess/ex_chess$i.in 
    cat ./ex_chess/ex_chess$i.out
done
