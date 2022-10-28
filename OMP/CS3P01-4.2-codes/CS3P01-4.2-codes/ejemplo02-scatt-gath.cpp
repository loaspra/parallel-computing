#include <mpi.h>
#include <iostream>
#include <stdlib.h>
using namespace std;

int main(int argc, char **argv) {
   int size, rank;

   MPI_Init(&argc, &argv);
   MPI_Comm_size(MPI_COMM_WORLD, &size);
   MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  int globaldata[size];
  int localdata;
  int i;

// inicializacion en proceso 0
if(rank==0) {
	for(int i=0;i<size;i++)
		globaldata[i]=2*i+1;

}
// Comunicacion (scatter)

// Computo 

// Comunicacion (gather)

// resultado en proceso 0
   

MPI_Finalize();
    return 0;
}












