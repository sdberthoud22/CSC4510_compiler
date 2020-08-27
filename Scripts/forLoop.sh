#!/bin/bash
# demonstrate for loop
# generate a multiplcation table for a given number
if [ $# -ne 1 ]
then
    echo "usage: $0 number"
    exit 1
fi

n=$1   # n assigned the valur of the argument provided to the script
for i in 1 2 3 4 5 6 7 8 9 10
do
    echo "$n * $i = `expr $i \* $n`"
done
