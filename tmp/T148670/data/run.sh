#!/bin/bash
set -e

CS="01 02 03 04 05 06 07 08 09 10 11 12 13 14 15 16 17 18 19 20"

for i in $CS; do
    echo -e "../main < a$i.in > a$i.out "
    time ../main < a$i.in > a$i.out
done
