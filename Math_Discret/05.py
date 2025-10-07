#crivo de erastostenes
MARCADO = 1
DESMARCADO = 0

def criar_lista(n):
    lista = []
    for idx in range(n-1):
        lista.append(DESMARCADO)
    return lista

def marcar(primo,n,lista):
    for numero in range(primo+1,n+1):
        if numero % primo == 0:
            lista[numero-2] = MARCADO
            
def proximo(primo,n,lista):
    for proximo in range(primo+1,n+1):
        if lista[proximo - 2] == DESMARCADO:
            return proximo

    return n

def imprime(n,lista):
    print(f"Os primos menores que {n}: ")
    for numero in range(n-1):
        if lista[numero] == DESMARCADO:
            print(numero+2,end=" -> ")
    print("FIM")
    

def main():
    n = int(input("Digite um N: "))
    lista = criar_lista(n)
    primo = 2
    while(primo <= n):
        marcar(primo, n, lista)
        if primo == n:
            break
        primo = proximo(primo, n, lista)   
    imprime(n, lista)

if __name__ == '__main__':
    main()

























#include <stdio.h>
#include <stdlib.h>
#include "../headers/Crivo_de_Eratostenes.h"

#define MARCADO 123
#define DESMARCADO 456

# unsigned int* cria_lista(unsigned int final){
#   unsigned int* lista_numeros = (unsigned int*)malloc(sizeof(unsigned int)*(final-1)); //lista de 2 a N
#   for (unsigned int indice = 0; indice < final-1; indice++) {
#     lista_numeros[indice] = DESMARCADO;
#   }
#   return lista_numeros;
# }

# void marca_multiplos(unsigned int numero, unsigned int final, unsigned int* lista){
#   for (unsigned int numero_da_lista = numero+1; numero_da_lista <= final+1; numero_da_lista++) {
#     if (numero_da_lista % numero == 0 ) {
#       lista[numero_da_lista-2] = MARCADO;
#     }
#   }
# }

# unsigned int proximo_primo_na_lista(unsigned int primo_atual, unsigned int final, unsigned int* lista){
#   for (unsigned int prox_primo = primo_atual+1; prox_primo <= final; prox_primo++) {
#     if (lista[prox_primo-2] == DESMARCADO) {
#       return prox_primo;
#     }
#   }
#   return final;
# }

# void imprime_primos_na_lista(unsigned int final, unsigned int* lista){
#   printf("Primos menores ou iguais a %u:\n", final);
#   for (unsigned int i = 0; i < final-1; i++) {
#     if (lista[i] == DESMARCADO) {
#       printf("%d ",i+2);
#     }
#   }
#   printf("\n");
# }
# #include <stdlib.h>
# #include <stdio.h>
# #include "../headers/Crivo_de_Eratostenes.h"

# int main(int argc, char const *argv[]) {
#   unsigned int N = 1;
#   printf("Digite o número N para o qual se quer encontrar todos os primos menores ou iguais a N:\n");
#   scanf("%d",&N);
#   unsigned int* lista_numeros = cria_lista(N);
#   unsigned int i = 2;
#   while (i <= N) {
#     marca_multiplos(i, N, lista_numeros);
#     if (i == N) {
#       break;
#     }
#     i = proximo_primo_na_lista(i, N, lista_numeros);
#   }
#   imprime_primos_na_lista(N, lista_numeros);
#   free(lista_numeros);
#   return 0;
# }