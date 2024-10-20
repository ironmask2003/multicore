/*
In questo programma viene mostrato l'esempio di come funzionano le chiamate MPI_Send e MPI_Recv.
Consiste nel far inviare ai processi diversi da 0 un messaggio (salvato nella variabile bueffer) al processo 0, il quale
stampa a schermo tale messaggio.
*/

#include <stdio.h>
#include <string.h>
#include <mpi.h>

int main(){
  char buffer[256];         // Messaggio da inviare ai processi 
  int comm_sz;              // Numero di processi
  int rank;                 // Processo che sta eseguendo il programma 
  // Inizio della porzione di codice che usa MPI
  MPI_Init(NULL, NULL);
  MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);    // Salva nella variabile comm_sz il numero di processi in esecuzione
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);       // Salva in rank il processo che sta eseguendo il codice
  // Controlla se il processo che sta eseguendo il codice non è il processo 0
  if(rank != 0) {
    // Salva nella variabile buffer il messaggio da invaire
    sprintf(buffer, "Sono il processo %d di %d", rank, comm_sz);
    // Invia al processo 0 il messaggio da invaire
    MPI_Send(buffer, strlen(buffer) + 1, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
  } 
  // Se il processso è il processo 0, stampa a schermo un messaggio e riceve dagli altri processi con MPI_Recv il messaggio inviato con MPI_Send 
  else {
    printf("Esecuzione delle chiamate MPI_Recv\n");
    // Itera sul numero di processi che sono in esecuzione e chiama il comando MPI_Recv per ogni processo e stampa a schermo il mmessaggio da loro inviato
    for (int i = 1; i < comm_sz; i++) {
      MPI_Recv(buffer, 256, MPI_CHAR, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      printf("%s\n", buffer);
    }
  }
  // Pulisce la memoria
  MPI_Finalize();
  return 0;
}
