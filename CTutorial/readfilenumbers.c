#include <stdio.h>

void main() {
    FILE *fp;
    char line[80];
    int N, n1, n2, n3;

    fp = fopen( "fileOfInts.txt", "r" ); // 1st number is # of lines
                                         // then 3 ints per line

    if ( feof( fp ) ) {
        printf( "Empty file!\n\n" );
        return;
    }

    // get the number of lines
    fscanf( fp, "%d", &N );

    while ( !feof( fp ) ) {
        fscanf( fp, "%d %d %d", &n1, &n2, &n3 );
        if ( feof( fp ) )
            break;
        printf( "%d, %d, %d\n", n1, n2, n3 );
    }

    close( fp );
}
