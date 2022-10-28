#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

void swap(int *x, int *y)
{
  int temp = *x;
  *x = *y;
  *y = temp;
}

int separate(int *x, int low, int high)
{
  int pivot, last;
  pivot = x[low]; 
  swap(x+low, x+high);
  last = low;
  #pragma omp parallel for
  for(int i = low; i<high; i++){
    if(x[i] <= pivot){
      swap(x+last, x+i);
      last += 1;
    }
  }
  swap(x+last, x+high);
  for (int i = low; i < high; i++)
  {
    printf("%d |", x[i]);
  }
  printf("\n");
  return last;
}

void qs(int *z, int zstart, int zend, int firstcall){
  int pivot;
  
  if(firstcall == 1) 
  {
    qs(z,0,zend,0);
  } else 
  {
    if(zstart<zend) 
    {
      pivot = separate(z, zstart,zend);
      #pragma omp task firstprivate(pivot)
      {
        printf("Task 1 from %d\n", omp_get_thread_num());
        qs(z, zstart, pivot-1,0);
      }
      #pragma omp task firstprivate(pivot)
      {
        printf("Task 2 from %d\n", omp_get_thread_num());
        qs(z,pivot+1,zend,0);
      }
    }
  }
}

void test_(int n, int* w, int veces)
{

  for(int i = 0; i<n; i++) 
  {
    w[i] = rand()%100;
    printf("%d | ", w[i]);
  }
  printf("\n");
  // inicio

  for (size_t i = 0; i < veces; i++)
  {
    #pragma omp parallel
    {
      #pragma omp single
        qs(w,0,n-1,1);
    }
    // final

    if(n<25)
      for(int i=0;i<n;i++) printf("%d - ",w[i]);
    printf("\n");
  }
}

int main(int argc, char **argv){
  int i,n,*w;
  n = atoi(argv[1]);
  w = malloc(n*sizeof(int));
  omp_set_num_threads(4);
  test_(n, w, 1);
  printf("\n");
}