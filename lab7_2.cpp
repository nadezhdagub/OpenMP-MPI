#include <omp.h>
#include <cmath>
#include <iostream>
#define N 6

int main(int argc, char** argv)
{
#ifdef _OPENMP
    std::cout << "Conpleted by an OpenMp - compliant implementation.\n";
    std::cout << "Num of threads: " << omp_get_max_threads()<< std::endl;
#endif

    int num_of_threads {omp_get_max_threads()};
    if (argc >1)
      num_of_threads = std::stoi(argv[1]);


    int A[N][N]=
    {
        {1, 4, 3, 1, 6,  9 },
        {2, 1, 4, 3, 5,  12},        
        {3, 2, 1, 7, 11, 4 },
        {5, 7, 1, 1, 6,  9 }, 
        {4, 3, 2, 4, 11, 4 },
        {2, 1, 5, 5, 5,  9 }
    };
    double Det ;    
    int p=0;
#pragma omp parallel

#pragma omp parallel for num_threads(num_of_threads)

    for(int step = 0; step < N - 1; step++)
    {

        int t=1;
        while(A[step][step]==0)
        {
            for(int col = 0; col < N; col++)
            {
              A[step][col]=Det;
              A[step][col]=A[step+t][col];
              A[step+t][col]=Det;
            }
            p++;
            t++;
        }
        for(int row = step + 1; row < N; row++)
        {
             Det = A[row][step] / A[step][step]; 

            for(int col = 0; col < N; col++)
            {

                A[row][col] -= A[step][col] * Det;
            } 
        }
    }

 
    Det =pow(-1,p);
    for(int i = 0; i < N; i++)
    {
        Det *= A[i][i];
    }

  
    std::cout << Det << std::endl;
    std::cout << " ";
 /*   for (int i = 0; i<N; i++)
    {
        for (int j = 0; j<N; j++)
        {
           std::cout << A[i][j] ;
           std::cout <<" ";
        }
        
    std::cout << std::endl;
   }*/
    return 0;
}
