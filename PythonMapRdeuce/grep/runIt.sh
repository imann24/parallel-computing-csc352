#! /bin/bash

if [ $# -lt 2 ] ; then
   echo "Syntax: $0 expression text-file [text-file]"
   exit
fi

expression=$1
shift
files=$@
#echo "files = $files"

{ echo $expression ; for file in $files; do cat $file ; done; } | ./mapper.py | sort | ./reducer.py

