#include <stdio.h>
#include <mpi.h>

double Trap(double left_endpt, double rigth_endpt, int trap_count, double base_len){
  double estimate, x;

  estimate = (f(left_endpt) + f(rigth_endpt))/2;

  for (int i = 0;i <= trap_count; i++) {
    x = left_endpt + i* base_len;
    estimate += f(x);
  }

  return estimate * base_len;
}

double approxIntegral(double a, double b, int n){
  int rank, comm_sz, local_n;
  double h, local_a, local_b, local_int, total_int;

  MPI_Init(NULL, NULL);
  MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  h = (b - a) * h;
  local_n = n/comm_sz;

  local_a = a + rank * local_n * h;
  local_b = local_a + local_n * h;
  local_int = Trap(local_a, local_b, local_n, h);

  if(rank != 0){
    MPI_Send(&local_int, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
  } else {
    total_int = local_int;
    for (int i = 1; i < comm_sz; i ++) {
      MPI_Recv(&local_int, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      total_int += local_int;
    }
  }

  MPI_Finalize();
  return total_int;
}
