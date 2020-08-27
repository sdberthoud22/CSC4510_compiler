#!/bin/sh
# Demonstrate if statement
# indicate if argument is positive or negative
if [ $# -ne 1 ]
then
    echo "usage $0 number"
    exit 1 # failure
fi
if [ $1 -eq 0 ]
then
    echo "$1 is zero"
    exit # success
fi
if [ $1 -lt 0 ]
then
    echo "$1 is negative"
    exit # success
fi
if [ $1 -gt 0 ]
then
    echo "$1 is positive"
    exit # success
fi
echo "Failure"
exit 1
