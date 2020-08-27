#!/bin/bash
# print chess board on the screen
# demonstrates nested for loops
# no arguments to the script

for (( i = 1; i <= 9; i++ )) ### outer loop
do
    for (( j = 1; j <= 9; j++ )) ### inner loop
    do
	tot=`expr $i + $j`
	tmp=`expr $tot % 2`
	if [ $tmp -eq 0 ]
	then
	    echo -e -n "\033[47m "
        else 
	    echo -e -n "\033[40m "
        fi
    done
    echo -n -e "\033[47m" ### set background color back to white
    echo ""  ### print a new line
done
