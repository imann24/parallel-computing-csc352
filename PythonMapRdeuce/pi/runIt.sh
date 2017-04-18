#! /bin/bash

if [ $# -ne 1 ] ; then
   echo "Syntax $0 N   (where N equals number of samples)"
   exit
fi

echo $1 | ./mapper.py | sort | ./reducer.py

