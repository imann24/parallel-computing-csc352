#! /bin/bash

if [ $# -lt 1 ] ; then
    echo "Syntax: $0 file1 [file2...]"
    exit
fi
    
for i in $@ ; do 
   { echo $i; cat $i; } | ./mapper.py
done |  sort | ./reducer.py


