#include <mpi.h>
#include <stdio.h>
#include <random>
#include <time.h>

#define leng 1
#define master_rank 2

/*Вторая задача про Китайский банк. Решить задачу о китайских

банках с дополнительным условием, что все пятничные расчеты банки про-
водят через Большой Банк, находящийся на улице Чжуань-Го.*/

int main(int argc, char **argv )
{
  int size, rank ;
  int mon;
  MPI_Status status;
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  srand(rank);
  srand(mon);
  int money = abs(mon); 
  int m = 1 + rand() % money ;

  if (rank == master_rank) {
    int bets[3];
    int bet[3];
    for (int i =0; i < 2; i++) {
      MPI_Recv(&money, leng, MPI_INTEGER, i, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
      bets[i] =money;
      printf("I'm main bank %d, and I got a money from bank %d = %d$\n", rank, i, money);
        for (int j =0; j < 2; j++) {
          bet[j] =m;
          printf("I'm main bank %d, and I sent %d$ to %d\n", rank, m, j);
          m = money - m;
        }
    }
    MPI_Send(&m, leng, MPI_INTEGER, rank, master_rank, MPI_COMM_WORLD);
  }

  else {
    printf("I'm %d, and I sent %d$\n", rank, money);
    MPI_Send(&money, leng, MPI_INTEGER, master_rank, rank, MPI_COMM_WORLD);
  }
  return 0;
}

