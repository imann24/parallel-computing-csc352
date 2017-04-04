// pi3.c
// Author: Isaiah Mann,
// Adapted from code by D. Thiebaut
// Computes Pi using 3 processes under MPI
//
// To compile and run:
// mpicc -o pi3 pi3.c
// mpirun -np 3 pi3 100000000
//

#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#define MANAGER 0
#define WORKER_1 1
#define WORKER_2 2
#define NN      100000

//  P R O T O T Y P E S
void doManager( int );
void doWorker( );

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
  if (myId == MANAGER)
    doManager(N);
  else
    doWorker(2);

  //--- close up MPI ---
  MPI_Finalize();

  return 0;
}


// The function to be evaluated
double getFraction( double x ) {
  return 4.0 / ( 1.0 + x*x );
}

void doWorker(int numWorkers)
{
     MPI_Status status;
     int steps;
     double start, end;
     MPI_Recv(&steps, 1, MPI_INT, MANAGER, 0, MPI_COMM_WORLD, &status);
     MPI_Recv(&start, 1, MPI_DOUBLE, MANAGER, 0, MPI_COMM_WORLD, &status);
     MPI_Recv(&end, 1, MPI_DOUBLE, MANAGER, 0, MPI_COMM_WORLD, &status);
     double delta = (end - start) / (double) (steps * numWorkers);
     int i;
     double current = start;
     double sum = 0;
     for(i = 0; i < steps; i++)
     {
          sum += getFraction(current);
          current += delta;
     }
     MPI_Send(&sum, 1, MPI_DOUBLE, MANAGER, 0, MPI_COMM_WORLD);
}

void doManager(int steps)
{
     MPI_Status status;
     int stepsPerWorker = steps / 2;
     MPI_Send(&stepsPerWorker, 1, MPI_INT, WORKER_1, 0, MPI_COMM_WORLD);
     MPI_Send(&stepsPerWorker, 1, MPI_INT, WORKER_2, 0, MPI_COMM_WORLD);

     double start1 = 0;
     double end1 = 0.5;
     double start2 = 0.5;
     double end2 = 1.0;
     MPI_Send(&start1, 1, MPI_DOUBLE, WORKER_1, 0, MPI_COMM_WORLD);
     MPI_Send(&end1, 1, MPI_DOUBLE, WORKER_1, 0, MPI_COMM_WORLD);
     MPI_Send(&start2, 1, MPI_DOUBLE, WORKER_2, 0, MPI_COMM_WORLD);
     MPI_Send(&end2, 1, MPI_DOUBLE, WORKER_2, 0, MPI_COMM_WORLD);

     double sum1;
     double sum2;
     MPI_Recv(&sum1, 1, MPI_DOUBLE, WORKER_1, 0, MPI_COMM_WORLD, &status);
     MPI_Recv(&sum2, 1, MPI_DOUBLE, WORKER_2, 0, MPI_COMM_WORLD, &status);

     double delta = 1.0 / steps;
     printf("%d iterations: Pi = %1.6f\n", steps, ( sum1 + sum2)*delta);
}
