#!/usr/bin/env python
# reducer.py
# a reducer for the inverted index problem.
# It gets a sorted collection of tuples (word, file-name)
# and generates a list of tuples of the form
# (word, [list of file-names]).

from __future__ import print_function
from operator import itemgetter

import sys

currentWord = None
fileList = []
word = None

# input comes from STDIN
for line in sys.stdin:
      # parse the input we got from mapper.py
      word, fileName = line.strip().split('\t', 1)

      #print( "--------" )
      #print( "--- line = ", line )
      #print( "--- word = %s, fileName = %s, fileList = %s" % ( word, fileName, str( fileList )  ) )

      # this IF-switch only works because Hadoop sorts map output
      # by key (here: word) before it is passed to the reducer
      if currentWord == None:
            currentWord = word
            fileList = [ fileName ]
            #print( "-1- word = %s, fileName = %s, fileList = %s" % ( word, fileName, str( fileList )  ) )
            continue
      if currentWord == word:
            if fileName not in fileList:
                  fileList.append( fileName )
            #print( "-2- word = %s, fileName = %s, fileList = %s" % ( word, fileName, str( fileList )  ) )
            continue
      if currentWord != word:
            print( "%s\t%s" % ( currentWord, ",".join( fileList ) ) )
            fileList = [ fileName ]
            currentWord = word
            #print( "-3- word = %s, fileName = %s, fileList = %s" % ( word, fileName, str( fileList )  ) )
            continue

# do not forget to output the last word if needed!
if currentWord == word:
    print( '%s\t%s' % (currentWord, ",".join( fileList ) ) )
