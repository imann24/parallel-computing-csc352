#! /bin/bash

{ cat 4300-8.txt ; cat pg10.txt; } | ./mapper1.py | sort | ./reducer1.py | ./mapper2.py | sort -n | ./reducer2.py
