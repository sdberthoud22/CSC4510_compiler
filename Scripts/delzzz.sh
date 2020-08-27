#!/bin/bash
#script to demonstrate use of variables and curly brackets
if [ $# -ne 1 ]
then
    echo "Usage: $0 filename"
    exit 1
fi
theFile=$1
touch $theFile     # creates a file called zzz with no contents
if [ -e $theFile ]
then
    echo "File $theFile exists."
    ls $theFile
else
    echo "File $theFile should have been created!"
    exit 1
fi
# Now create a file with the extension ".XYZ"
touch "${theFile}.XYZ"
if [ -e "${theFile}.XYZ" ]
then
    echo "File ${theFile}.XYZ exists."
    ls "${theFile}.XYZ"
else
    echo "File ${theFile}.XYZ should have been created!"
    exit 1
fi
#clean up
rm $theFile
rm "${theFile}.XYZ"


