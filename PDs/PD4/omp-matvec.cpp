#include<omp.h>
#include <iostream>
#include <math.h>

#define T 5

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
    int N = T;

    int A[T][T]; 
    int v[T];

    make_mat(A, N);
    make_vec(v, N);

    int X[N];
    int suma = 0;
    omp_set_num_threads(8);
    #pragma omp parallel
    {
        #pragma omp for firstprivate(suma)
        for (int i = 0; i < N; i++)
        {
            for (int g = 0; g < N; g++)
            {
                suma += A[i][g] * v[g];
            }
            X[i] = suma;
            suma = 0;
        }
    }
}