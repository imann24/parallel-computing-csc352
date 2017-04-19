/*
 Game of life
 D. Thiebaut,
 Modified by Isaiah Mann to read starting dish from a text file ("dish.txt")
 Heavily adapted from code found in java section at this
 URL:  https://rosettacode.org/wiki/Conway%27s_Game_of_Life#Java
 and ported to C.

 This code works in console mode, displaying successive generations
 of the game of life on the screen, and clearing the screen between
 each one.

 The initial pattern is defined in the array dish (as in petri dish).

 To compile and run:

 gcc -o GameOfLife GameOfLife.c
 ./GameOfLife


*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

// ------------------------------------- MACROS ----------------------------------------
#define NUMBERROWS 10000
#define esc 27
#define cls() printf("%c[2J",esc)
#define pos(row,col) printf("%c[%d;%dH",esc,row,col)
#define DISH_FILE "dish.txt"

// ------------------------------------- GLOBALS ----------------------------------------

int ROWSIZE = strlen("                                                                                  ") + 1;
char  *DISH0[ NUMBERROWS];
char  *DISH1[ NUMBERROWS];
char  *PATTERN[NUMBERROWS];

// --------------------------------- prototypes -----------------------------
void life( char**, char** );
void initDishes( );
void clearScreen();
void print( char ** );
void readDish();

// --------------------------------------------------------------------------
// initDishes
// inits the dishes (current and future)
void initDishes( ) {
  int i;

  //--- initialize other dish with spaces.  Make it same dimension as DISH0. ---
  for (i = 0; i< NUMBERROWS; i++ )  {
    DISH0[i] = (char *) malloc( (strlen( PATTERN[i] ) + 1 ) * sizeof( char ) );
    strcpy( DISH0[i], PATTERN[i] );

    DISH1[i] = (char *) malloc( (strlen( DISH0[i] )+1) * sizeof( char )  );
    strcpy( DISH1[i], DISH0[i] );
  }

}


// --------------------------------------------------------------------------
// clearscreen:
void clearScreen() {
  /*
   * brings the cursor home (top-left), so that the next generation will
   * be printed over the current one.
   */

  char ANSI_CLS[] = "\x1b[2J";
  char ANSI_HOME[] = "\x1b[H";
  printf( "%s%s", ANSI_HOME, ANSI_CLS );

}

// --------------------------------------------------------------------------
// print
void print( char* dish[] ) {
  /*
   * just display all the lines of the array of strings.
   */
  int i;

  for (i=0; i<NUMBERROWS; i++ ) {
    pos( i, 0 );
    printf( "%s\n", dish[i] );
  }

}


// --------------------------------------------------------------------------
void  life( char** dish, char** newGen ) {
  /*
   * Given an array of string representing the current population of cells
   * in a petri dish, computes the new generation of cells according to
   * the rules of the game. A new array of strings is returned.
   */
  int i, j, row;
  int rowLength = ROWSIZE;
  int dishLength = NUMBERROWS;

  for (row = 0; row < NUMBERROWS; row++) {// each row

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

        for ( j = i - 1; j <= i + 1; j++) {

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

void readDish()
{
     printf("STARTING ON THE FILE");
    FILE* filePointer;
    filePointer = fopen(DISH_FILE, "r");
    int dishIndex = 0;
    while(!feof(filePointer))
    {
        PATTERN[dishIndex] = (char *) malloc(ROWSIZE * sizeof(char));
        fgets(PATTERN[dishIndex], ROWSIZE, filePointer);
        PATTERN[dishIndex][ROWSIZE - 1] = '\0';
        dishIndex++;
        if(feof(filePointer))
        {
            break;
        }
    }
    fclose(filePointer);
    printf("READ THE FILE");
}

// --------------------------------------------------------------------------
int main( int argc, char* argv[] ) {
  int gens = 3000;      // # of generations
  int i;
  char **dish, **future, **temp;
  readDish();
  //--- clear screen ---
  cls();

  //--- init the global arrays ---
  initDishes();

  //--- set pointers to them ---
  dish   = DISH0;
  future = DISH1;

  //--- iterate over all generations ---
  for ( i = 0; i < gens; i++) {

    //printf( "Generation %d\n", i );

    // apply the rules of life to the current population and
    // generate the next generation.
    life( dish, future );

    // copy future to dish
    temp = dish;
    dish = future;
    future = temp;
  }

  // display the last generation
  print(dish);
}
