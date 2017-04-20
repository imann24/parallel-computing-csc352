#!/usr/bin/env python
# reducer.py
# D. Thiebaut
# Reducer stage for the game of life.
# The input typically looks like this:
# 
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
# where the first word is a string of 6 0-padded digits, the first 3 
# representing the row of a cell, and the last 3 its column.  The
# second word indicates whether the cell is actually a live cell in 
# the current generation, or whether its status is unknown, but there
# is a cell in the previous generation that is alive and is its 
# neighbor.
#
# Since all the lines fed to the reducer are sorted, then lines 
# with the same keys, representing the same cell, are together.
# 
# 000004   OneMoreNeighbor
# 000005   OneMoreNeighbor
# 000006   OneMoreNeighbor
# 001004   OneMoreNeighbor
# 001004   OneMoreNeighbor
# 001005   alive
# 001005   OneMoreNeighbor
# 001006   OneMoreNeighbor
# 001006   OneMoreNeighbor
# 002004   OneMoreNeighbor
# 002004   OneMoreNeighbor
# 002004   OneMoreNeighbor
# 002005   alive
# 002005   OneMoreNeighbor
# 002005   OneMoreNeighbor
# 002006   OneMoreNeighbor
# 002006   OneMoreNeighbor
# 002006   OneMoreNeighbor
# 003004   OneMoreNeighbor
# 003004   OneMoreNeighbor
# 003005   alive
# 003005   OneMoreNeighbor
# 003006   OneMoreNeighbor
# 003006   OneMoreNeighbor
# 004004   OneMoreNeighbor
# 004005   OneMoreNeighbor
# 004006   OneMoreNeighbor
#
# It is then easy to divide the input lines into blocks with the same key,
# and count the number of neighbors, and know if the cell is alive or dead.
# If the cell should be alive in the next generation, then the reducer
# outputs its coordinates (row, column) as two numbers separated by a tab.
# For example:
#
# 2  4
# 2  5
# 2  6
# 
#

from __future__ import print_function
from operator import itemgetter
import sys

lastCell = None
isAlive = False
cell = None
noNeighbors = 0

# input comes from STDIN
for line in sys.stdin:
      # remove leading and trailing whitespace
      line = line.strip()
      
      # parse the input we got from mapper.py
      # 001002 alive
      # 001002 oneMoreNeighbor

      cell, status = line.split('\t', 1)
      
      if cell != lastCell:
         # we are now looking at a new cell.  Figure out the fate
         # of the previous cell
         if isAlive and 2 <= noNeighbors <= 3:
            # continue living
            print( "%d\t%d" % ( int( lastCell )/1000, int( lastCell )%1000 ) )
         if not isAlive and noNeighbors == 3:
            # be born 
            print( "%d\t%d" % ( int( lastCell )/1000, int( lastCell )%1000 ) )

         noNeighbors = 0
         isAlive = False
 
      # parse status of new cell
      if status.find( "alive" ) != -1:
          isAlive = True
      else:
          noNeighbors += 1

      lastCell = cell


# do not forget to output the last cell if needed!
if isAlive and 2 <= noNeighbors <= 3:
   # continue living
   print( "%d\t%d" % ( int( lastCell )/1000, int( lastCell )%1000 ) )
if not isAlive and noNeighbors == 3:
   # be born
   print( "%d\t%d" % ( int( lastCell )/1000, int( lastCell )%1000 ) )
