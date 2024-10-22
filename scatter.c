#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>

/* Funzione che prende in input:
 * un vettori in cui vengono salvati sono gli elementi divisi da MPI_Scatter;
 * il numero di elmeneti in cui dividere il vettore;
 * il numero di elmenti presenti nel vettore principale
 * il vettore principale
 * il processo che sta eseguendo la funzione 
 * il comunicatore usato
 * La funzione prende in input attraverso il processo 0 gli elementi che compongono il vettore e li distribuisce a tutti
 * i procossi coinvolti nel comunicatore specificato in input
 * */
void readAndScatterVettor(double local_vec[], int local_n, int n, char vec_name[], int rank, MPI_Comm comm){
  double* vec = NULL;   // Inizializza il vettore a NULL 
  // Controlla se il processo che sta eseguendo la funzione e' il processo 0
  if(rank == 0){
    // Alloca memoria per creare un vettori di n elmenti 
    vec = malloc(n * sizeof(double)); 
    // Prende in input gli elementi che compongono il vettore
    printf("Enter the vector %s\n", vec_name);
    for (int i = 0; i < n; i ++) scanf("%lf", &vec[i]);
    // Distribuisce a tutti i processi coinvolti in comm gli elmenti di vec, dividendoli in local_n elementi e salvandoli in local_vec
    MPI_Scatter(vec, local_n, MPI_DOUBLE, local_vec, local_n, MPI_DOUBLE, 0, comm);
    // Libera la memoria  di mec 
    free(vec);
  } // Se il processo non e' il processo 0, riceve gli elementi mandati dal processo 0
  else MPI_Scatter(vec, local_n, MPI_DOUBLE, local_vec, local_n, MPI_DOUBLE, 0, comm);
  // Stampa a schermo gli elementi del vettore divisi con il processo che ha ricevuto gli elementi divisi da MPI_Scatter
  for (int i = 0; i < local_n; i ++) {
    printf("%lf: Processo %d\n", local_vec[i],rank);
  }
}
