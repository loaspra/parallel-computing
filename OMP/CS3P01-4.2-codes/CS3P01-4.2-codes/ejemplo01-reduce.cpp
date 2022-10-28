/*  MPI_Reduce  */

#include <mpi.h>
#include <iostream>
#include <stdlib.h>
using namespace std;

int main(int argc, char *argv[]) {
    	int   me, numprocs;
	int data,res;
	
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &me);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);

// inicializacion en proceso 0

// Broadcast		
        
// Reduce

// resultado en proceso 0
 
    MPI_Finalize();
}
    
