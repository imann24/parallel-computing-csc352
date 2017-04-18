#! /bin/bash

cat ulysses.txt | ./mapper.py | ./shuffleSort.py | ./reducer.py 
