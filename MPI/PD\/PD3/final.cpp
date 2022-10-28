/*
    All done, code works for all N and p
*/

#include <mpi.h>
#include <iostream>
#include <math.h>

#define T 500

void make_mat(int A[][T], int N)
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            A[i][j] = (i + 1) * (j + 1);
        }
    }
}


void make_vec(int v[], int N)
{
    for (int i = 0; i < N; i++)
    {
        v[i] = (N - i) * i + 1;
    }
}


int main(int argc, char** argv) 
{
    // Initialize the MPI environment
    MPI_Init(&argc, &argv);
    int N = T;
    int world_rank, world_size;
    
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    int A[T][T]; 
    int v[T];
    double start, end;

    if(world_rank == 0)
    {
        start = MPI_Wtime();
        make_mat(A, N);
        make_vec(v, N);
    }
    int X[N];
    // cantidad de filas a enviar 
    int p = int(ceil(float(N)/float(world_size)));
    int n_filas = N * p;
    int a[n_filas];

    MPI_Bcast(&v, N, MPI_INT, 0, MPI_COMM_WORLD);
    // if(world_rank == 0)
        // printf("Numero de cosas a enviar %d | Numero de procesadores %d \n", n_filas, world_size); 

    MPI_Scatter(A, n_filas, MPI_INT, a, n_filas, MPI_INT, 0, MPI_COMM_WORLD);
    
    int x[n_filas / N];
    int suma = 0;
    for (int i = 0; i < n_filas; i++)
    {
        suma += a[i] * v[i % N];
        // printf("|i: %d| Process %d multiplicando %d x %d \n", i, world_rank, a[i], v[i % N]);
        if((i + 1) % N == 0 && i != 0)
        {
            x[i / (N - 1) - 1] = suma;
            // printf("Process %d guardo suma %d en %d \n", world_rank, suma, i / (N - 1) - 1);
            suma = 0;
        }
    }
    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Gather(x, n_filas / N, MPI_INT, X, n_filas / N, MPI_INT, 0, MPI_COMM_WORLD);
    
    if(world_rank == 0)
    {
        end = MPI_Wtime();
        printf("Tiempo |%lf| \n", end - start);
        // for (int i = 0; i < N; i++)
        // {
        //     printf("|");
        //     for (int j = 0; j < N; j++)
        //     {
        //         if(j != N - 1)
        //             printf("%d\t", A[i][j]);
        //         else
        //             printf("%d|", A[i][j]);
        //     }
        //     printf(" |%d| = %d\n", v[i], X[i]);
        // }
    }
    MPI_Finalize();
}