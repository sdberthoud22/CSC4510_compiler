#!/bin/bash
# demonstrated nested if statements
if [ $# -ne 1 ]
then
    echo "usage: $0 number"
    exit 1
fi
if [ $1 -lt 0 ]
then 
    echo "$1 is negative"
else
    if [ $1 -gt 0 ]
    then
	echo "$1 is positive"
    else
	if [ $1 -eq 0 ]
	then
	    echo "$1 is zero"
	else
	    echo "Argument must be a number"
	fi
    fi
fi
