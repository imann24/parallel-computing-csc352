# D. Thiebaut
#!/usr/bin/env python
from __future__ import print_function
import sys

sortNumeric = False
if len( sys.argv ) > 1 and sys.argv[1] == "-n":
   sortNumeric = True

L = []

# input comes from STDIN
for line in sys.stdin:
      # remove leading and trailing whitespace
      line = line.strip()

      word, count = line.split('\t', 1)
      if sortNumeric:
          word = int( word )

      L.append( (word, count) )


L.sort()

for word, count in L:
    print( '%s\t%s' % (word, count) )
