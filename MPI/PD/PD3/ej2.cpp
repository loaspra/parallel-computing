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
    // para medir el tiempo
    double start, end;

    // Initialize the MPI environment
    MPI_Init(&argc, &argv);
    int N = T;
    int world_rank, world_size;
    
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    int A[N][T]; 

    int v[N];
    if(world_rank == 0)
    {
        start = MPI_Wtime();
        make_mat(A, N);
        make_vec(v, N);
    }
    // for recv
    int tag, val, buff;

    // resultado
    int x[N];
    
    // enviar vector v a todos los procesos
    MPI_Bcast(&v, N, MPI_INT, 0, MPI_COMM_WORLD);
    int idx = 0;

    int pes = 1;
        if(world_size <= N)
            pes = world_size;
        else
            pes = N;

    if(world_rank == 0)
    {
        // enviar trozos de la matriz a los procesadores 
        if(world_size > 1)
        for (int i = 1; i < pes; i++)
        {
            // enviar las filas a los procesos
            for (int k = 0; k < int(ceil(float(N)/float(world_size))); k++)
            {
                for (int j = 0; j < N; j++)
                {
                    val = A[idx][j];
                    MPI_Send(&val, 1, MPI_INT, i, (k + j), MPI_COMM_WORLD);
                }
            }
            idx += 1;
        }
        
        while (idx < N)
        {
            val = 0;
            for (int i = 0; i < N; i++)
            {
                val += A[idx][i] * v[i];
            }
            x[idx] = val;
            idx++;
        }
    } 
    else 
    {
        if(world_rank < pes)
        for (int i = 0; i < int(ceil(float(N)/float(world_size))); i++)
        {
            val = 0;
            for (int j = 0; j < N; j++)
            {   
                MPI_Recv(&buff, 1, MPI_INT, 0, (j + i), MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                val += buff * v[j];
            }
            MPI_Send(&val, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
        }
    }
    MPI_Barrier(MPI_COMM_WORLD);

    if(world_rank == 0)
    {
        for (int i = 1; i < pes; i++)
        {
            for (int j = 0; j < int(ceil(float(N)/float(world_size))); j++)
            {
                MPI_Recv(&buff, 1, MPI_INT, i, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                x[i - 1] = buff;
            }
        }
        end = MPI_Wtime();
        printf("Tiempo %lf\n", end - start);
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
        //     printf(" |%d| = %d\n", v[i], x[i]);
        // }
    }
    MPI_Finalize();
}