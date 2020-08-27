#!/bin/sh 
# simple script to sum numbers

if [ $# -ne 2 ]
then
	echo "Usage - $0 x y"
	echo "         where x and y are the 2 numbers to be summed"
	exit 1    # indicate failure of the script
fi
echo "Sum of $1 and $2 is `expr $1 + $2`"

