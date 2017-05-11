#!/usr/bin/env python
# mapper.py
# mapper for Conway's 2D Game of Life.
# The input data has two possible formats:
# 1) The first first generation defined by
# a python-type collection of quoted strings.
# We refer to it  as "raw-life"
#
#0       "           "
#1       "     *     "
#2       "     *     "
#3       "     *     "
#4       "           "
#
# 2) the output comes from a previous map-reduce stage,
# in which case the reducer outputs the coordinates of
# live cells only:
#
# 2  4
# 2  5
# 2  6
#
# Above, 3 cells are live, at coordinates (2,4), (2,5), and (2,6)
#
# For every live cell that it finds, the mapper sends 9 tupples:
# 001005 alive
# 000004 OneMoreNeighbor
# 000005 OneMoreNeighbor
# 000006 OneMoreNeighbor
# 001004 OneMoreNeighbor
# 001006 OneMoreNeighbor
# 002004 OneMoreNeighbor
# 002005 OneMoreNeighbor
# 002006 OneMoreNeighbor
#
# The first string contains the 0-padded coordinates of live cells and
# neighbor cells that have this live cell as a neighbor.
#

from __future__ import print_function
import sys

# input comes from STDIN (standard input)
for line in sys.stdin:

    # remove leading and trailing whitespace
    line = line.strip()
    #print( "line =", line )

    # split the line into words
    words = line.split( None, 1 )

    #print( "words = ", words )
    isRawLife = line.find( "\"" ) != -1

    # are we reading the original array of cells from a file?
    if isRawLife:
       lineNo = int( words[0] )
       lineWidth = len( words[1] )-2 # for the double quotes
       lifeLine = words[1].replace( "\"", "" )
       #print( "(%d, >%s<)" % ( lineNo, lifeLine ) )
       for j in range( len( lifeLine ) ):
           if lifeLine[j] != ' ':
              print( "%03d%03d\t%s" % ( lineNo, j, "alive" ) )
              for row in range( lineNo-1, lineNo+1+1 ):
                  for col in range( j-1, j+1+1 ):
                      if row < 0: continue
                      if col < 0: continue
                      if col > lineWidth: col = 0
                      if row == lineNo and col == j: continue
                      print( "%03d%03d\t%s" % ( row, col, "OneMoreNeighbor" ) )

    # or are we reading tuples output by the reducer?
    else:
       lineNo = int( words[0] )
       j      = int( words[1] )
       print( "%03d%03d\t%s" % ( lineNo, j, "alive" ) )
       for row in range( lineNo-1, lineNo+1+1 ):
           for col in range( j-1, j+1+1 ):
               if row < 0: continue
               if col < 0: continue
               if row == lineNo and col == j: continue
               print( "%03d%03d\t%s" % ( row, col, "OneMoreNeighbor" ) )
