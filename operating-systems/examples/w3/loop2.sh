#!/bin/bash

charUnit="o"

while [ "$string" != "ooooo" ]
do
    string=$string$charUnit # concatenate charUnit to string
    echo "keep going ($string)"
done

echo "we got 5 os"
