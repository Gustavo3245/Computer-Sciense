#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

pthread_t t1, t2;

// Print um valor esperando 1 segundo.
void codigo_thread(){
    for (int value = 0; value < 10; ++value) {
        sleep(1);
        printf("Thread One - Second %d\n", value + 1);
    }
}

void codigo_thread2(){
    for (int value = 0; value < 15; value++) {
        sleep(1);
        printf("Thread Two - Second %d\n", value + 1);
    }
}

int main(int argc, char *argv[]){
    
    // Função para criação de threads, 
    // recebe o endereço da thread, atributos, a função da thread, e argumento restritos.

    pthread_create(&t1, NULL, (void *) codigo_thread, NULL);
    pthread_create(&t2, NULL, (void *) codigo_thread2, NULL);
    
    // A função pthread espera as suas thread filhas terminarem antes de voltar a
    // a sua sequência normal.
     
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    return 0;
}
