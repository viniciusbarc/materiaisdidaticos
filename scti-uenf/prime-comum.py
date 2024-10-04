import datetime

def imprimir_data_hora():
    agora = datetime.datetime.now()
    data_hora_formatada = agora.strftime("%d/%m/%Y %H:%M:%S")
    return data_hora_formatada

numero = int(input("Digite um número: "))
total_primos = 0

print("Início do processamento: "+imprimir_data_hora())

if numero > 1:
    for i in range(2, numero + 1):
        qtde_divisores = 0
        for j in range(2, i + 1):
            if i % j == 0:
                qtde_divisores += 1
        if qtde_divisores == 1:
            total_primos += 1

print("Fim do processamento:    "+imprimir_data_hora())
print(f"Existem {total_primos} números primos no intervalo de 0 até {numero}.")


