#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

pthread_t t1, t2;
int ERRO_TH = 111;
int SUCESSO_TH = 222;

// Print um valor esperando 1 segundo.
void* codigo_thread(){
    for (int value = 0; value < 10; ++value) {
        sleep(1);
        printf("Thread One - Second %d\n", value + 1);
    }

    return (void*) &SUCESSO_TH;
}

void codigo_thread2(){
    for (int value = 0; value < 15; value++) {
        sleep(1);
        printf("Thread Two - Second %d\n", value + 1);
    }
    pthread_exit(&ERRO_TH);
}

int main(int argc, char *argv[]){
    
    int *cod1, *cod2;
    // Função para criação de threads, 
    // recebe o endereço da thread, atributos, a função da thread, e argumento restritos.

    pthread_create(&t1, NULL, (void *) codigo_thread, NULL);
    pthread_create(&t2, NULL, (void *) codigo_thread2, NULL);
    
    // A função pthread espera as suas thread filhas terminarem antes de voltar a
    // a sua sequência normal.
     
    pthread_join(t1, (void**) &cod1);
    pthread_join(t2, (void**) &cod2);

    printf("Retorno da tarefa 1 %d\n Retorno da tarefa 2 %d\n", *cod1, *cod2);
    return 0;
}
