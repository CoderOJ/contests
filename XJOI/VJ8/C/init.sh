#!/bin/bash

RED='\033[31m'
GREEN='\033[32m'
YELLOW='\033[33m'
BLUE='\033[36m'
DEFCOL='\033[0m'

read -p "class name: " class_name
sed -i "s/CLASS_NAME/${class_name}/g" "./main.h" "./test.cpp"

read -p "method name: " method_name
sed -i "s/METHOD_NAME/${method_name}/g" "./main.h" "./test.cpp"

read -p "parameters: " parameters
sed -i "s/PARAMETERS/${parameters}/g" "./main.h"

read -p "return value: " return_value
sed -i "s/RETURN_VALUE/${return_value}/g" "./main.h"


read -p "input(s) number: " n
expr $n + 0 &> /dev/null
if [ $? -ne 0 ] ; then
  echo -e "${RED}error: input is not an number, exit ${DEFCOL}"
  exit 1
fi

for ((i=0;i<${n};i++)) ; do
  vim "in$i.csh"
done
