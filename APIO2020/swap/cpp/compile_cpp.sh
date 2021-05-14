#!/bin/bash

problem=swap

clang++ -std=c++17 -o "${problem}" "grader.cpp" "${problem}.cpp" -g -fsanitize=address,undefined  -Wall -Wextra 
