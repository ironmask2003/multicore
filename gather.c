void printAndGatherVector(
  double local_vec[],
  int local_n,
  int n,
  char vec_name[],
  int rank,
  MPI_Comm comm
){
  double* vec = NULL;
  // Controlla se il procesos che esegue la funzione e' il processo 0
  if(rank == 0){
    vec = malloc(n * sizeof(double));   // Crea il vettore di n elmenti 
    // attraverso tale funzione aspetta che gli altri processi gli mandino un local_vec di local_n elmenti da salvare in vec
    MPI_Gather(local_vec, local_n, MPI_DOUBLE, vec, local_n, MPI_DOUBLE, 0, comm);
    // Stamp a schermo il contenuto finale di vec
    printf("Vector %s\n", vec_name);
    for (int i = 0; i < n; i++) printf("%lf\n", vec[i]);
    free(vec);  // Libera la memorioa
  } else {
    // Se il processo non e' il processo 0, allora manda al processo 0 il contenuto di local_vec aggiungendolo a vec 
    MPI_Gather(local_vec, local_n, MPI_DOUBLE, vec, local_n,  MPI_DOUBLE, 0, comm);
  }
}
