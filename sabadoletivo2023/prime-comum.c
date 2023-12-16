#include<stdio.h>
#include<time.h>

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
    int total_primos;

    printf("Digite um número: ");
    scanf("%d",&numero);
    total_primos = 0;

    printf("Início do processamento: ");
    timestamp();

    if (numero > 1) {
        for(int i = 2; i <= numero; i++) {
            int qtde_divisores = 0;
            for(int j=2; j <= i; j++) {
                if(i % j == 0) {
                    qtde_divisores++;
                }
            }
            if (qtde_divisores == 1) {
                total_primos++;
            }
        }
    }

    printf("Fim do processamento:    ");
    timestamp();

    printf("Existem %d números primos no intervalo de 0 até %d.\n",total_primos,numero);    
}