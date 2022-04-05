#!/bin/bash
set -e

test -p fin || mkfifo fin
test -p fout || mkfifo fout
cp $1 alice.in
cp $2 bob.in
./bob > fin < fout &
./alice < fin > fout &
