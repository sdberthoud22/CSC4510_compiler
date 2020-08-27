#!/bin/bash
# directory listing

dir=(`ls`)
size=${#dir[@]}
index=0
while [ $index -lt $size ]
do   # print 5 filesnames to a line
    echo -n "${dir[$index]}      "
    index=`expr $index + 1`
    tmp=`expr $index % 5`
    if [ $tmp -eq 0 ]
    then 
	echo "" # newline
    fi
done
echo ""


