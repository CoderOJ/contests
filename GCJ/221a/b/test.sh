#!/bin/bash
set -e

python3 ./local_testing_tool.py > p_in < p_out &
./main < p_in > p_out &
