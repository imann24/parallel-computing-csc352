#!/usr/bin/env python
#! /usr/bin/env python
# pi.py
from __future__ import print_function
import sys

def f( x ):
    return 4.0 / ( 1.0 + x*x )

def main():
    if len( sys.argv ) <= 1:
        print( "Syntax: %s N (where N = number of samples)\n" % sys.argv[0])
        sys.exit(0)
    
    N = int( sys.argv[1] )
    deltaX = 1.0 / N
    sum    = 0

    for i in range( 0, N ):
        sum +=  f( i * deltaX )*deltaX 


    print( "%1.10f" % sum )

main()
