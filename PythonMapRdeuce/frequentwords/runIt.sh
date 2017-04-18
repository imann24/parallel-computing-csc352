#! /bin/bash

#! /bin/bash

cat ulysses.txt | ./mapper1.py | sort | ./reducer1.py | ./mapper2.py | sort -n | ./reducer2.py
