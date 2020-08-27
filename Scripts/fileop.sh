#!/bin/bash

# check 3 arguments are provided
if [ $# -lt 3 ]
then
    echo "usage: $0 option pattern filename"
    exit 1
fi

# check that the given file actually exists
if [ ! -f $3 ]
then
    echo "Filename given \"$3\" does not exist"
    exit 1
fi

case "$1" in
    #count number of lines matched
    -i) echo "Number of lines with the pattern $2: "
	grep -c -i $2 $3
	;;
    #count number of words matched
    -c) echo "Number of words matched with the pattern $2: "
	grep -o -i $2 $3 | wc -l
	;;
    #print all the matched lines
    -p) echo "Lines matched with the pattern $2: "
	grep -i $2 $3
	;;
    #delete all the lines matched with the pattern
    -d) echo "After deleting the lines matched with the pattern $2: "
	sed -n "/$2/!p" $3
	;;
    *)  echo "invalid option"
	;;
esac
