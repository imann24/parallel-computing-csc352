#!/usr/bin/env python
import sys

first = True

# input comes from STDIN (standard input)
for  line in sys.stdin:
    if first:
        first = False
        grepWord = line.strip().lower()
        continue

    if line.lower().find( grepWord ) != -1:
        print '%s\t%s' % ( grepWord, line.strip() )

        
