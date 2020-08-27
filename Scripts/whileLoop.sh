#!/bin/bash
# demonstrate while loop

if [ $# -ne 1 ]
then
    echo "usage: $0 number"
    exit 1
fi

n=$1
i=1
while [ $i -le 10 ]
do
    echo "$n * $i = `expr $i \* $n`"
    i=`expr $i + 1`
    # note lack of space around = sign above!
done
