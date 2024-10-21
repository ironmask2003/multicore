#include <stdio.h>
#include <mpi.h>

int main(){
  int rank, comm_sz;
  double* a = NULL;
  double* b = NULL;
  int* n = NULL;

  MPI_Init(NULL, NULL);
  MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  // Controlla se il processi in esecuzione è il processo 0, se lo è prende in input i 3 numeri
  if(my_rank == 0){
    printf("Enter the values of a, b and n: ");
    scanf("%lf %lf %d", a_p, b_p, n_p);
  }
  // Invia a tutti i processi coinvolti nella comunicazione attraverso il comunicatore MPI_COMM_WORLD i 3 numeri presi in input
  MPI_Bcast(a, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
  MPI_Bcast(b, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
  MPI_Bcast(n, 1, MPI_INT, 0, MPI_COMM_WORLD);

  MPI_Finalize();

  return 0;
}
