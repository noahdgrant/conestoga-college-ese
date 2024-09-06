#!/bin/bash

echo "== start of script =="

# setup a variable
# can't have space before or after =
var="test"

# variable will be a string
echo $var

# to make something an int use $((var))
var2=24

# don't need space between $(( and var
echo $((var2 + var2))

# need space between [ and $var2
if [ $var2 = 24 ]
then
    echo "TWENTY-FOUR"
elif [ $var = 48 ]
then
    echo "FOUTRY-EIGHT"
else
    echo "NOTHING"
fi

# user input
read myvar

echo "you entered: $myvar"

# if with flags
path="/home/noah"

if [ -d $path ]
then
    echo "directory found!"
else
    echo "directory not found!"
fi

# print working directory
echo $PWD

# print username
echo $USER

# random int
echo $RANDOM

# print time since script started
echo $SECONDS

echo "== end of script =="
