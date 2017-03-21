#include <stdio.h>

void main() {
  FILE *fp;
  char line[80];

  fp = fopen( "helloFile.c", "r" );  // open file for reading

  while ( !feof( fp ) ) {         // while not eof
    fgets( line, 80, fp );      // get at most 80 chars
    if ( feof( fp ) )           // if eof reached stop
      break;
    line[79] = '\0';            // truncate line to be safe
    printf( "%s", line );       // print it
  }

  close( fp );                    // close file
}
