#!/usr/bin/env python
# A mapper program for the reverse index problem.
# Receives the file name of the first line, and 
# all the lines should come from the given file.
# 1 mapper per text file.
# If several text files need to be processed,
# the combined output of all the mappers should
# be fed to the reducer.
import sys

first = True
fileName = None

# input comes from STDIN (standard input)
for line in sys.stdin:
    if first:
        first = False
        fileName = line.strip()
        continue

    # create tuples of all words in line
    L = [ (word.strip().lower(), fileName ) for word in line.strip().split() ]

    # increase counters
    for word, f in L:
        # write the results to STDOUT (standard output);
        # what we output here will be the input for the
        # Reduce step, i.e. the input for reducer.py
        #
        # tab-delimited; the trivial word count is 1
        print( '%s\t%s' % (word, f) )
