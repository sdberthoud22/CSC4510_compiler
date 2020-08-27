#!/bin/sh
# demonstrate multi-level if
# determine is argument is positive or negative
if [ $# -ne 1 ]
then
    echo "usage: $0 number"
    exit 1   # failure
fi
if [ $1 -lt 0 ]
then
    echo "$1 is negative"
elif [ $1 -gt 0 ]
then
    echo "$1 is positive"
elif [ $1 -eq 0 ]
then
    echo "$1 is zero"
else
    echo "$1 is not a number!"
fi
