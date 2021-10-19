#include<omp.h>
#include<stdio.h> 


int main()
{
  char C[100] = {'a','a','e','c','e','e','k','k','e','c','c','a','a','c','g','g','g','a',
'a','c','e','e','e','k','k','a','c','g','g','a','k','e','c','g','g','g','k','k','k','c','c',
'c','e','e','a','e','c','k','g','g','c','k','k','k','k','g','e','e','a','a','a','c','c','g',
'k','k','g','e','e','a','e','g','a','c','c','g','g','k','k','k','a','a','a','e','e','e','c',
'c','g','k','g','k','g','k','c','a','c','a','e','g'};

  int N=5;

  char para[10] = {'a','b','c','d','e','f','g','h','k','l'};
  
  #pragma omp parallel 
 
  #pragma omp parallel for
  for (int i=0; i<99;i++){ 
  int count=omp_get_thread_num();
    for (int j=0; j<2*N-1;j++){
      
      if ((C[i]==para[j])){
        C[i]=para[j+1];
        printf("%c of %d\n",C[i], count);
        }

    j=j+1;
    count=count+1;
    }
    
  }
  return 0;
}
