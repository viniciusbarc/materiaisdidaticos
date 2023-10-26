#include<stdio.h>
#include<time.h>
#include<mpi.h>

void timestamp () {
# define TIME_SIZE 40

  static char time_buffer[TIME_SIZE];
  const struct tm *tm;
  size_t len;
  time_t now;

  now = time ( NULL );
  tm = localtime ( &now );

  len = strftime ( time_buffer, TIME_SIZE, "%d %B %Y %I:%M:%S %p", tm );

  printf ( "%s\n", time_buffer );

  return;
# undef TIME_SIZE
}

int main() {
    int numero;
    int total_primos_de_cada_processo;
    int total_primos;
    int pid;
    int total_processos;

    MPI_Init (NULL, NULL);
    MPI_Comm_size ( MPI_COMM_WORLD, &total_processos );
    MPI_Comm_rank ( MPI_COMM_WORLD, &pid );

    total_primos_de_cada_processo = 0;

    if(pid == 0) {
        fflush(stdout);
        printf("Digite um número: ");
        fflush(stdout);
        scanf("%d", &numero);
        printf("Início do processamento: ");
        timestamp();
    }

    MPI_Bcast(&numero, 1, MPI_INT, 0, MPI_COMM_WORLD);

    if (numero > 1) {
        for(int i = 2 + pid; i <= numero; i = i + total_processos) {
            int qtde_divisores = 0;
            for(int j=2; j <= i; j++) {
                if(i % j == 0) {
                    qtde_divisores++;
                }
            }
            if (qtde_divisores == 1) {
                total_primos_de_cada_processo++;
            }
        }
    }

    MPI_Reduce ( &total_primos_de_cada_processo, &total_primos, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD );
    MPI_Finalize();
    if(pid == 0) {
        printf("Fim do processamento:    ");
        timestamp();

        printf("Existem %d números primos no intervalo de 0 até %d.\n",total_primos,numero); 
    }
   
}