#!/bin/bash

problem=fun

javac "grader.java" "${problem}.java"
jar cfe "${problem}.jar" "grader" *.class
