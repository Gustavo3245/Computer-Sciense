#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>

#define NUM_FILOSOFOS 5
#define NUM_GRAFOS 5

sem_t garfos[NUM_FILOSOFOS];
pthread_t filosofos[NUM_FILOSOFOS];

void *filosoAtiv(int *id){
    while (1) {
        printf("Filosofo %d está pensando", *id);
        
        printf("Filosofo %d está com Fome!", *id);
        
        sem_wait(&garfos[id]);
        sem_wait(&garfos[id + 1]);
        
        printf("Filosofo %d está comendo!", *id);

        sem_post(&garfos[id]);
        sem_post(&garfos[id + 1]);
    }
}

int main(int argc, char *argv[]){
    int id[NUM_FILOSOFOS];

    for (int value = 0; value < NUM_GRAFOS; value++) {
        sem_init(&garfos[value], 0, 1);
        id[value] = value;
    }

    for (int value = 0; value < NUM_GRAFOS; value++) {
        pthread_create(&filosofos[value], NULL, filosoAtiv, &id[value]);
    }
}
