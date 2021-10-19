#include <stdio.h>

#ifdef _OPENMP
#include <omp.h>
#endif

#define N 11

double a[N];
double b[N];


int main(void){
double a[N],b[N];
int i;
a[0] = 0;
#pragma omp parallel

# pragma omp parallel for//nowait
  for (i=1; i<N; i++)
    {
      a[i] = a[i-1]+2.0;
      b[i] = a[i] + a[i-1];
    }
  #pragma omp critical
  b[0]=a[N-1];

for(i=0;i<N; i++){
  printf("%g\n",b[i]);
  }
  return 0;
}
