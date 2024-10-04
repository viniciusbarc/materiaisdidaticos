from mpi4py import MPI
import datetime

def imprimir_data_hora():
    agora = datetime.datetime.now()
    data_hora_formatada = agora.strftime("%d/%m/%Y %H:%M:%S")
    return data_hora_formatada

comm = MPI.COMM_WORLD
pid = comm.Get_rank()
total_processos = comm.Get_size()

total_primos_de_cada_processo = 0
numero = None
total_primos = None

if pid == 0:
  numero = int(input("Digite um número: "))
  print("Início do processamento: "+imprimir_data_hora())

numero = comm.bcast(numero, root=0)

if numero > 1:
  for i in range(2 + pid, numero + 1, total_processos):
    qtde_divisores = 0
    for j in range(2, i + 1):
        if i % j == 0:
            qtde_divisores += 1
    if qtde_divisores == 1:
        total_primos_de_cada_processo += 1

total_primos = comm.reduce(total_primos_de_cada_processo, op=MPI.SUM, root=0)

if pid == 0:
  print("Fim do processamento:    "+imprimir_data_hora())
  print(f"Existem {total_primos} números primos no intervalo de 0 até {numero}.")


