#!/bin/bash
# another example of a for loop
if [ $# -ne 1 ]
then
    echo "usage: $0 number"
    echo "          number must be positive"
    exit 1
else
    # right number of parameters, check it is positive
    if [ $1 -lt 0 ]
    then
	echo "Error: number must be positive"
	exit 1
    fi
fi

n=$1
for ((i = 0 ; i <= $n; i++ ))  # note use of double brackets
do
    echo "Welcome $i times"
done

