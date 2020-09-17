#!/bin/bash

problem=fun

java -Xmx512M -Xss64M -jar "${problem}.jar" "grader"
