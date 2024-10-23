#include <stdio.h>
#include <mpi.h>

void build_MPI_type(double* a_p, double* b_p, int* n_p, MPI_Datatype* input_mpi_t_p){
  MPI_Aint a_addr, b_addr, n_addr;

  int AoB[3] = {1, 1, 1};
  MPI_Datatype AoT[3] = {MPI_DOUBLE, MPI_DOUBLE, MPI_INT};
  MPI_Aint AoD[3]= {0};

  MPI_Get_address(a_p, &a_addr);
  MPI_Get_address(b_p, &b_addr);
  MPI_Get_address(n_p, &n_addr);

  AoD[1] = b_addr - a_addr;
  AoD[2] = n_addr - a_addr;
  MPI_Type_create_struct(3, AoB, AoD, AoT, input_mpi_t_p);
  MPI_Type_commit(input_mpi_t_p);
}

void getInput(int rank, int comm_sz, double* a_p, double* b_p, int* n_p){
  MPI_Datatype MPI_Input_t;
  build_MPI_type(a_p, b_p, n_p, &MPI_Input_t);

  if(rank == 0){
    printf("Enter a, b and n:\n");
    scanf("%lf %lf %d", a_p, b_p, n_p);
  }

  MPI_Bcast(a_p, 1, MPI_Input_t, 0, MPI_COMM_WORLD);
  MPI_Type_free(&MPI_Input_t);
}
