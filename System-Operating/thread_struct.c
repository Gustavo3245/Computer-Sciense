#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

pthread_t t1, t2;

struct param_t {
    int nst; // Count parameter.
    char *name; // thread name.
};

void codigo_thread(struct param_t *thread_struct){


    for (int value = 0; value < thread_struct -> nst; ++value) {
        sleep(1);
        printf("Thread One - Second %d\n", value + 1);
    }
}

void codigo_thread2(int *integer_Pointer){
    for (int value = 0; value < *integer_Pointer; value++) {
        sleep(1);
        printf("Thread Two - Second %d\n", value + 1);
    }
}

int main(int argc, char *argv[]){

    struct param_t thread_struct;
    thread_struct.nst = 5;
    thread_struct.name = "Tarefa 1";

    int param2 = 12;
    // Função para criação de threads, 
    // recebe o endereço da thread, atributos, a função da thread, e argumento restritos.

    pthread_create(&t1, NULL, (void *) codigo_thread, (void *) &thread_struct);
    pthread_create(&t2, NULL, (void *) codigo_thread2, (void *) &param2);
    
    // A função pthread espera as suas thread filhas terminarem antes de voltar a
    // a sua sequência normal.
     
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    return 0;
}
