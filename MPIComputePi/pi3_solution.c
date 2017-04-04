// pi2.c
// D. Thiebaut
// Computes Pi using 2 processes under MPI
// 
// To compile and run:
// mpicc -o pi2 pi2.cpp
// mpirun -np 2 pi2 100000000
//
// Output
// Process 1 of 2 started on beowulf2.  N= 50000000
// Process 0 of 2 started on beowulf2.  N= 50000000
//  50000000 iterations: Pi = 3.14159

#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#define MANAGER 0
#define WORKER  1
#define NN      100000
#define TAG     123

//  P R O T O T Y P E S
void doManager( int, int );
void doWorker( int );

//      M  A  I  N
int main(int argc, char *argv[]) {
  int N, myId, noProcs, nameLen, i;
  char procName[MPI_MAX_PROCESSOR_NAME];

  if ( argc<2 ) {
    printf( "Syntax: mpirun -np 2 pi2 N\n" );
    return 1;
  }

  N = atoi( argv[1] );
  
  //--- start MPI ---
  MPI_Init( &argc, &argv );
  MPI_Comm_rank( MPI_COMM_WORLD, &myId );
  MPI_Comm_size( MPI_COMM_WORLD, &noProcs );
  MPI_Get_processor_name( procName, &nameLen );

  printf( "Process %d of %d started on %s. N = %d\n",
          myId, noProcs, procName, N );
  
  //--- farm out the work: 1 manager, several workers ---
  if ( myId == MANAGER ) 
    doManager( N, noProcs );
  else
    doWorker( myId );
  
  //--- close up MPI ---
  MPI_Finalize();
  
  return 0;
}


// The function to be evaluated
double f( double x ) {
  return 4.0 / ( 1.0 + x*x );
}


//===  M A N A G E R  ===
void doManager( int n, int noProcs ) {
  double sum0 = 0, sum1;
  double deltaX = 1.0/n;
  int i;
  MPI_Status status;

  //--- first send n to worker ---
  MPI_Send( &n, 1, MPI_INT, 1, TAG, MPI_COMM_WORLD );
  MPI_Send( &n, 1, MPI_INT, 2, TAG, MPI_COMM_WORLD );

  //--- perform 1st half of the work ---
  //for ( i=0; i< n/2; i++ )
  //  sum0 += f( i * deltaX );

  //--- wait for other half from worker ---
  MPI_Recv( &sum0, 1, MPI_DOUBLE, 1, TAG, MPI_COMM_WORLD, &status );
  MPI_Recv( &sum1, 1, MPI_DOUBLE, 2, TAG, MPI_COMM_WORLD, &status );

  //--- output result ---
  printf( "%d iterations: Pi = %1.6f\n", n, ( sum0 + sum1 )*deltaX );
}

//===  W O R K E R  ===
void doWorker( int myId ) {
  int i, n;
  MPI_Status status;
  double sum = 0, deltaX;

  //--- get n from manager ---
  MPI_Recv( &n, 1, MPI_INT, MANAGER, TAG, MPI_COMM_WORLD, &status );

  //--- do (second) half of the work ---
  deltaX = 1.0/n;

  if ( myId == 1 )
    for ( i=n/2; i< n; i++ )
      sum += f( i * deltaX );
  else
    for ( i=0; i< n/2; i++ )
      sum += f( i * deltaX );

  //-- send result to manager ---
  MPI_Send( &sum, 1, MPI_DOUBLE, MANAGER, TAG, MPI_COMM_WORLD );
}

