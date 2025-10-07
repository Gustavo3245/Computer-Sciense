#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

pthread_t t1, t2, t3;
int MAX_VALUE = 0;
int MIN_VALUE = 0;
int MEDIA = 0;

 struct  Inteiros{
    int *array;
    int tamanho;
} inteiros;

void *codigo_thread1(struct Inteiros *inteiro){
    int soma = 0;
    for (int value = 0; value < inteiro->tamanho; value++) {
        soma += inteiro->array[value];
    }
    soma = soma / inteiro->tamanho; 
    pthread_exit((void *) soma);
}


void codigo_thread2(struct Inteiros *inteiro){
    MIN_VALUE = inteiro->array[0];

    for (int i = 0; i < inteiro->tamanho; i++) {
        if (inteiro->array[i] < MIN_VALUE) {
            MIN_VALUE = inteiro->array[i];
        }
    }
}


void codigo_thread3(struct Inteiros *inteiro){
    MAX_VALUE = inteiro->array[0];

    for (int i = 0; i < inteiro->tamanho; i++) {
        if (inteiro->array[i] > MAX_VALUE) {
            MAX_VALUE = inteiro->array[i];
        }
    }
}

int main(int argc, char *argv[]){

    int array[] = {12,32,43,54,65};
    
    struct Inteiros inteiro;
    inteiro.array = array;
    inteiro.tamanho = 5;
    
    // Função para criação de threads, 
    // recebe o endereço da thread, atributos, a função da thread, e argumento restritos.


    pthread_create(&t1, NULL, (void *) codigo_thread1, (void *) &inteiro);
    pthread_create(&t2, NULL, (void *) codigo_thread2,  (void *) &inteiro);
    pthread_create(&t2, NULL, (void *) codigo_thread3,  (void *) &inteiro);


    
    pthread_join(t1, (void **) &MEDIA);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);
    // A função pthread espera as suas thread filhas terminarem antes de voltar a
    // a sua sequência normal.
    //
    printf("media %d\n", MEDIA);
        printf("maior %d\n", MAX_VALUE);
    printf("menor %d", MIN_VALUE);

}
