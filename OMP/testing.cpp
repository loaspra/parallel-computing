#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

void wait()
{
    int x, y, z;
    x = 1;
    printf("Process %d arrive\n", omp_get_thread_num());
    while(x==1)
    {
        y = x + 1;
        z = x + 1;
    }
}

void arrive()
{
    printf("Process %d arrive\n", omp_get_thread_num());
    int x = 2;
}

int main(int argc, char **argv)
{
    #pragma omp parallel
    {
        #pragma omp task
            wait();
        #pragma omp task
            arrive();
    }
}