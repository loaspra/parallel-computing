#include <iostream>
#include<omp.h>
#define N     20
using namespace std;

int main(int argc, char *argv[])
{
int i, chunk=10;
float a[N], b[N], c[N];
omp_set_num_threads(4);

for (i=0; i < N; i++){
  	a[i] = 2.0*i;
	b[i] = i * 1.0;
}

#pragma omp parallel 
  {
  #pragma omp for  
  for (i=0; i < N; i++){
    	c[i] = a[i] + b[i];
 	printf("hilo activo: %i %i\n",omp_get_thread_num(),i);
  } 
  }  /* end of parallel section */

for (i=0; i < N; i++)
	cout<<a[i]<<"\t"<<b[i]<<"\t"<<c[i]<<endl;

}
