#include <mpi.h>
#include <iostream>
#include <math.h>
#define K 1024
int main(int argc, char **argv) {
  int mpi_rank, mpi_size;
  MPI_Status stat;
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &mpi_rank);
  MPI_Comm_size(MPI_COMM_WORLD, &mpi_size);
  double t0 = 0.0, tf = 0.0;
  int n, iter = 12;
  double local_sum, global_sum, result, error;
  const int max_iter = 20;
  const double pi = 3.141592653589793;

// se itera max_iter veces
  while (iter <= max_iter) {

// datos en el maestro
    	if (mpi_rank == 0) {
    	
	}

// Broadcast
    
// suma local
    
// Reduce (suma global)

// resultados en el maestro
    if (mpi_rank == 0) {

  	}
    iter++;
  } // while

  MPI_Finalize(); // Exit MPI
}






