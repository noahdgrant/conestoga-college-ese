#!/bin/bash

echo "Factorial Calculator"
echo "===================="
echo "Give me an input..."

read input
result=$input

while [ $input -gt 1 ]
do
    input=$((input - 1))
    result=$((result * input))
done
echo "Result = "$result""
