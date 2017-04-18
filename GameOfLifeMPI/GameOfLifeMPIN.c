/**
 * Author: Isaiah Mann
 * Description: Runs Game of Life on MPI for N nodes
 * Adapted From: 2 Process Version by D. Thiebaut (CSC352, S17)
 * Note: Requires even number of processes to run properly
 */

 #include <stdio.h>
 #include <strings.h>
 #include <stdlib.h>
 #include <time.h>
 #include <unistd.h>
 #include "mpi.h"

 #define NUMBERROWS 28
 #define esc 27
 #define cls() printf("%c[2J",esc)
 #define pos(row,col) printf("%c[%d;%dH",esc,row,col)
 #define MANAGER 0

 char  *DISH0[ NUMBERROWS ];
 char  *DISH1[ NUMBERROWS ];
 char  *PATTERN[NUMBERROWS] = {
   "                                                                                  ",
   "   #                                                                              ",
   " # #                                            ###                               ",
   "  ##                                                                              ",
   "                                                                                  ",
   "                                                      #                           ",
   "                                                    # #                           ",
   "                                                     ##                           ",
   "                                                                                  ",
   "                                                                                  ",
   "                                                                                  ",
   "                                                                                  ",
   "             #                                                                    ",
   "           # #                                                                    ",
   "            ##                                                                    ",
   "                                                                                  ",
   "                                                                                  ",
   "                                                                                  ",
   "                                                                                  ",
   "                                                                                  ",
   "                                                                                  ",
   "                                                                                  ",
   "                                                                                  ",
   "                                                                                  ",
   "                                                                                  ",
   "                                                                                  ",
   "                                                                                  ",
   "                                                                                  "
 };
 int ROWSIZE = strlen( "                                                                                  ") + 1;

 //------------------------------- prototypes --------------------------------
 void life( char**, char**, int );
 void initDishes( int  );
 void print( char **, int );

 // --------------------------------------------------------------------------
 // initDishes
 // inits the dishes (current and future)
 void initDishes( int rank ) {
   int i;

   //--- initialize other dish with spaces.  Make it same dimension as DISH0. ---
   for (i = 0; i< NUMBERROWS; i++ )  {
     DISH0[i] = (char *) malloc( ( strlen( PATTERN[0] ) + 1 ) * sizeof( char ) );
     strcpy( DISH0[i], PATTERN[i] );

     DISH1[i] = (char *) malloc( (strlen( DISH0[0] )+1) * sizeof( char )  );
     strcpy( DISH1[i], PATTERN[i] );
   }
 }


 // --------------------------------------------------------------------------
 // initDishes2
 // inits the dishes (current and future)
 // (Buggy: attempts to declare only 1 half of the array, plus boundary
 //  rows, depending on rank.  Needs a bit more debugging...)
 void initDishes2( int rank ) {
   int i;

   // init to null all entries.  This way we'll be
   // able to tell if a row belongs to us or not.
   for ( i=0; i<NUMBERROWS; i++ ) {
     DISH0[i] = NULL;
     DISH1[i] = NULL;
   }

   //--- Init RANK 0 rows ---
   if ( rank == 0 ) {
     //--- initialize dishes with lower half of pattern ---
     for (i = 0; i< NUMBERROWS/2+1; i++ )  {

       DISH0[i] = (char *) malloc( (strlen( PATTERN[0] ) + 1 ) * sizeof( char ) );
       strcpy( DISH0[i], PATTERN[i] );

       DISH1[i] = (char *) malloc( (strlen( DISH0[0] )+1) * sizeof( char )  );
       strcpy( DISH1[i], DISH0[i] );
     }

     //--- initialize top row of dishes, as they are neighbors of Row 0 ---
     DISH0[NUMBERROWS-1] = (char *) malloc( (strlen( PATTERN[0] ) + 1 ) * sizeof( char ) );
     strcpy( DISH0[NUMBERROWS-1], PATTERN[NUMBERROWS-1] );
     DISH1[NUMBERROWS-1] = (char *) malloc( (strlen( PATTERN[0] ) + 1 ) * sizeof( char ) );
     strcpy( DISH1[NUMBERROWS-1], PATTERN[NUMBERROWS-1] );
   }

   //--- Init RANK 1 rows ---
   if ( rank == 1 ) {
     //--- initialize dishes with upper half of pattern ---
     for (i = NUMBERROWS/2-1; i< NUMBERROWS; i++ )  {

       DISH0[i] = (char *) malloc( (strlen( PATTERN[0] ) + 1 ) * sizeof( char ) );
       strcpy( DISH0[i], PATTERN[i] );

       DISH1[i] = (char *) malloc( (strlen( DISH0[0] )+1) * sizeof( char )  );
       strcpy( DISH1[i], DISH0[i] );
     }

     //--- initialize bottom row of dishes, as they are neighbors of top row  ---
     DISH0[0] = (char *) malloc( (strlen( PATTERN[0] ) + 1 ) * sizeof( char ) );
     strcpy( DISH0[0], PATTERN[0] );
     DISH1[0] = (char *) malloc( (strlen( PATTERN[0] ) + 1 ) * sizeof( char ) );
     strcpy( DISH1[0], PATTERN[01] );
   }
 }



 // --------------------------------------------------------------------------
 // print
 void print( char* dish[], int rank ) {
   int i;

   if ( rank == 0 ) {
     //--- display lower half only ---
     for (i=0; i<NUMBERROWS/2; i++ ) {
       if ( dish[i] == NULL ) continue;
       pos( i, 0 );
       printf( "%s\n", dish[i] );
     }
   }

   if ( rank == 1 ) {
     //--- display upper half only ---
     for (i=NUMBERROWS/2; i<NUMBERROWS; i++ ) {
       if ( dish[i] == NULL ) continue;
       pos( i, 0 );
       printf( "%s\n", dish[i] );
     }

   }
 }

 // --------------------------------------------------------------------------
 void check( char** dish, char** future ) {
   int i, j, k, l;
   l = sizeof( dish )/sizeof( dish[0] );
   printf( "length of dish = %d\n", l );

   for ( i=0; i<l; i++ ) {
     k = strlen( dish[i] );
     printf( "%d %s\n", k, dish[i] );
   }
   printf( "\n\n" );

   l = sizeof( future )/sizeof( future[0] );
   printf( "length of future = %d\n", l );

   for ( i=0; i<l; i++ ) {
     k = strlen( future[i] );
     printf( "%d %s\n", k, future[i] );
   }
   printf( "\n\n" );

 }

 // --------------------------------------------------------------------------
 void life(char** dish, char** newGen, int lowerRow, int upperRow)
 {
   /*
    * Given an array of string representing the current population of cells
    * in a petri dish, computes the new generation of cells according to
    * the rules of the game. A new array of strings is returned.
    */
   int i, j, row;
   int rowLength = strlen( dish[0] );
   int dishLength = NUMBERROWS;
   for (row = lowerRow; row < upperRow; row++) {// each row

     if ( dish[row] == NULL )
       continue;

     for ( i = 0; i < rowLength; i++) { // each char in the
                                        // row

       int r, j, neighbors = 0;
       char current = dish[row][i];

       // loop in a block that is 3x3 around the current cell
       // and count the number of '#' cells.
       for ( r = row - 1; r <= row + 1; r++) {

         // make sure we wrap around from bottom to top
         int realr = r;
         if (r == -1)
           realr = dishLength - 1;
         if (r == dishLength)
           realr = 0;

         for (int j = i - 1; j <= i + 1; j++) {

           // make sure we wrap around from left to right
           int realj = j;
           if (j == -1)
             realj = rowLength - 1;
           if (j == rowLength)
             realj = 0;

           if (r == row && j == i)
             continue; // current cell is not its
           // neighbor
           if (dish[realr][realj] == '#')
             neighbors++;
         }
       }

       if (current == '#') {
         if (neighbors < 2 || neighbors > 3)
           newGen[row][i] =  ' ';
         else
           newGen[row][i] = '#';
       }

       if (current == ' ') {
         if (neighbors == 3)
           newGen[row][i] = '#';
         else
           newGen[row][i] = ' ';
       }
     }
   }
 }


// --------------------------------------------------------------------------
int main( int argc, char* argv[] ) {
     int gens = 3000;      // # of generations
     int i;
     char **dish, **future, **temp;

     //--- MPI Variables ---
     int processCount = 0;
     int rank = 0;
     MPI_Status status;   // required variable for receive routines

     //--- initialize MPI ---
     MPI_Init( &argc, &argv );
     //--- get number of tasks, and make sure it's 2 ---
     MPI_Comm_size(MPI_COMM_WORLD, &processCount);
     //--- get rank ---
     MPI_Comm_rank( MPI_COMM_WORLD, &rank );

     //--- init the dishes as half of the original problem ---
     initDishes( rank );

     dish   = DISH0;
     future = DISH1;

     //check( dish, future );

     //--- clear screen ---
     cls();

     print( dish, rank );          // # first generation, in petri dish

     int rowsPerProcess = dishLength / NUMBERROWS;
     int lowerRow, upperRow, rowBelow, rowAbove, rankBelow, rankAbove;
     lowerRow = rowsPerProcess * rank;
     upperRow = rowsPerProcess * (rank + 1);
     rowBelow = lowerRow - 1;
     rowAbove = upperRow + 1;
     rankBelow = rank - 1;
     rankAbove = rank + 1;
     // Wrap around functionality:
     if(rowBelow < 0)
     {
          rowBelow = NUMBERROWS - 1;
     }
     if(rowAbove > NUMBERROWS - 1)
     {
          rowAbove = 0;
     }
     if(rankBelow < 0)
     {
          rankBelow = processCount - 1;
     }
     if(rankAbove > processCount - 1)
     {
          rankAbove = 0;
     }
     // iterate over all generations
     for ( i = 0; i < gens; i++) {
          pos( 33+rank, 0 );
          printf( "Rank %d: Generation %d\n", rank, i );

          // apply the rules of life to the current population and
          // generate the next generation.
          life(dish, future, lowerRow, upperRow);

          // display the new generation
          //print( dish, rank );

          // add a bit of a delay to better see the visualization
          // remove this part to get full timing.
          //if (rank == 0 ) sleep( 1 );

          if(rank % 2 == 0)
          {
               // Start at the second process (skip the manager)
               //          buffer                #items   item-size src/dest tag   world
               // Send lowerRow to previous process (rank - 1):
               MPI_Send(future[lowerRow], ROWSIZE, MPI_CHAR, rankBelow, rank, MPI_COMM_WORLD);
               // Send upperRow to next process (rank + 1):
               MPI_Send(future[upperRow], ROWSIZE, MPI_CHAR, rankAbove, rank, MPI_COMM_WORLD);
               // Receive row below bottom row from rank below:
               MPI_Recv(future[rowBelow], ROWSIZE, MPI_CHAR, rankBelow, rank, MPI_COMM_WORLD, &status);
               // Receive row above top row from rank above:
               MPI_Recv(future[rowAbove], ROWSIZE, MPI_CHAR, rankAbove, rank, MPI_COMM_WORLD, &status);
          }
          else
          {
               // Receive row above top row from rank above:
               MPI_Recv(future[rowAbove], ROWSIZE, MPI_CHAR, rankAbove, rank, MPI_COMM_WORLD, &status);
               // Receive row below bottom row from rank below:
               MPI_Recv(future[rowBelow], ROWSIZE, MPI_CHAR, rankBelow, rank, MPI_COMM_WORLD, &status);
               // Send upperRow to next process (rank + 1):
               MPI_Send(future[upperRow], ROWSIZE, MPI_CHAR, rankAbove, rank, MPI_COMM_WORLD);
               // Send lowerRow to previous process (rank - 1):
               MPI_Send(future[lowerRow], ROWSIZE, MPI_CHAR, rankBelow, rank, MPI_COMM_WORLD);
          }
          // copy future to dish
          temp = dish;
          dish = future;
          future = temp;
   }
   //--- display the last generation ---
   print(dish, rank);

   //--- close MPI ---
   pos( 30+rank, 0 );
   printf( "Process %d done.  Exiting\n\n", rank );
   MPI_Finalize();

   return 0;
}
