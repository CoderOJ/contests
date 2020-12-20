#!/bin/bash
set -e

for i in `seq 1 20` ; do
  time ../main < ./inter$i.in > ./inter$i.out
done
