#include <mpi.h>
#include <stdio.h>
#include <math.h>
#include <ctime>
#include <cstdlib>  
#include <iostream>

int main(int argc, char **argv) {
  int mpi_rank, mpi_size;
  MPI_Status stat;
  MPI_Init(&argc, &argv);                  
  MPI_Comm_rank(MPI_COMM_WORLD, &mpi_rank); 
  MPI_Comm_size(MPI_COMM_WORLD, &mpi_size); 
  double t0 = 0.0, t1 = 0.0, t2 = 0.0, t3 = 0.0, t4=0.0, tf = 0.0;   

  //const int array_size = (int)pow(10,6);;
  const int array_size = (int)pow(2,20);;
  const int subpr_size = array_size/mpi_size;
  int send_arr[array_size], recv_arr[subpr_size];
  double result = 0.0, local_sum = 0.0, global_sum[mpi_size];

  // inicializar en el maestro, array con elementos entre 0-100
  if (mpi_rank == 0) {


}

// Comunicacion (scatter)

  
// Computo (promedios locales)

// Comunicacion (gather)

// promedio global y tiempos en el maestro
  if (mpi_rank == 0) {

  }

  MPI_Finalize();
}
