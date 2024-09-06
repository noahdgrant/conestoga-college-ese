#!/bin/bash

# clear current console screen
clear

echo "=== start of script ==="

echo Listing of Positional Parameter Variables
echo

# $0 is the first parameter when launching shell script
echo name of the script is: $0

# $# number of arguments excluding the program name
echo Number of unique arguments is: $#

# $@ refers to all the arguments excluding the program name
echo All arguments: $@

echo argument 1: $1
echo argument 2: $2
echo argument 3: $3

echo sum of arg1 to arg3 is: $(( $1+$2+$3 ))

echo "=== end of script ==="
