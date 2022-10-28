#include<iostream>
#include<omp.h>
using namespace std;

int main(){
srand(time(nullptr));
int m=16;
int i=0,j=0,a[m],b[m],low,high;
float c[m];

for (i=0; i<m;i++){
a[i]=rand()%16;
b[i]=rand()%16;
c[i]=16;//rand()%16;
printf(" %d %d %3.1f\n",a[i],b[i],c[i]);
}
int TID=0;
omp_set_num_threads(8);

#pragma omp parallel private (i,j,TID,low,high)
for (i=0; i<m;i++){
TID=omp_get_thread_num();
low=a[i];
high=b[i];
printf("Hilo %d, i: %d, low: %d, high: %d\n",omp_get_thread_num(),i,low,high);
if (low>high){
#pragma omp single
printf("Salida en la iteracion %d, hilo %d, low: %d, high: %d\n",i,omp_get_thread_num(),low,high);
break;
}

#pragma omp for nowait
for (j=low; j<high;j++){
c[j]=(c[j]-a[i])/b[i];
printf("for: %d, hilo %d, j: %d, i: %d\n",TID,omp_get_thread_num(),j,i);
}
}
for(int i=0;i<m;i++)
printf(" %d %d %3.1f\n",a[i],b[i],c[i]);

}
