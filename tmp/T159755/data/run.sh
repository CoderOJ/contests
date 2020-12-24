#!/bin/bash
set -e

for i in `seq 1 20` ; do
  echo -e "running $i:"
  /usr/bin/time -v ../main < ./inter$i.in > ./inter$i.out
  echo
  echo
done
