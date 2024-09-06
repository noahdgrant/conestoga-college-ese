#!/bin/bash

case $1 in
1)
    echo "you entered case 1"
    ;; # break
2)
    echo "case 2"
    ;;
3)
    echo "case 3"
    ;;
9|10|11|12) # waterfall cases
    echo "other jackpot numbers"
    ;;
*) # default
    echo "useless numbers"
    ;;
esac
