#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t semaforo; // Declaração do semáforo

void* thread_func(void* arg) {
    int id = *(int*)arg;

    printf("Thread %d: Aguardando para entrar na secao critica.\n", id);
    sem_wait(&semaforo); // Bloqueia o semáforo (entra na seção crítica)

    // Seção crítica
    printf("Thread %d: Entrou na secao critica.\n", id);
    sleep(2); // Simula uma operação demorada
    printf("Thread %d: Saindo da secao critica.\n", id);

    sem_post(&semaforo); // Libera o semáforo (sai da seção crítica)
    return NULL;
}

int main() {
    pthread_t threads[2];
    int thread_ids[2] = {1, 2};

    // Inicializa o semáforo com valor 1 (apenas uma thread por vez)
    sem_init(&semaforo, 0, 1);

    // Cria as threads
    pthread_create(&threads[0], NULL, thread_func, &thread_ids[0]);
    pthread_create(&threads[1], NULL, thread_func, &thread_ids[1]);

    // Aguarda a finalização das threads
    pthread_join(threads[0], NULL);
    pthread_join(threads[1], NULL);

    // Destroi o semáforo
    sem_destroy(&semaforo);

    printf("Programa finalizado.\n");
    return 0;
}

