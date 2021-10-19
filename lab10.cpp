#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
  int rank1 = 0, size1 = 0;
  int value = 1;
  MPI_Comm comm1;
  MPI_Status status;
  MPI_Init(&argc, &argv);
  int compete_threads = 0;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank1);
  MPI_Comm_size(MPI_COMM_WORLD, &size1);
  printf("Process #%d from %d process\n", rank1, size1);
  MPI_Bcast(&value, 1, MPI_INT, rank1, MPI_COMM_WORLD);
  printf("Process %d. Broadcast complete message\n", rank1);
  for (int i = 0; i < size1; i++) {
    if (i == rank1) {
      continue;
    }
    int complete = 0;
    MPI_Bcast(&complete, 1, MPI_INT, i, MPI_COMM_WORLD);
    compete_threads += complete;
    printf("Process %d. Receive %d threads\n", rank1, compete_threads);
  }

  printf("Process %d synchronized\n", rank1);

  MPI_Finalize();
}
