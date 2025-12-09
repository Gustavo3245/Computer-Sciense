#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE];       // Buffer compartilhado
int proxima_insercao = 0;      // Índice para inserção (produtor)
int proxima_remocao = 0;       // Índice para remoção (consumidor)

sem_t espera_vaga;             // Contador de espaços vazios no buffer
sem_t espera_dado;             // Contador de itens disponíveis no buffer
sem_t exclusao_mutua;          // Semáforo para exclusão mútua

void produtor() {
    int item;
    for (int i = 0; i < 10; i++) {
        item = i;  // Produz um item (aqui, simplesmente o número `i`)
		
		// Insira o código aqui para completar
       
        sleep(1); // Simula o tempo de produção
    }
   
}

void  consumidor() {
    int item;
    for (int i = 0; i < 10; i++) {        
        
        // Insira o código aqui para completar

        sleep(2); // Simula o tempo de consumo
    }
   
}

int main() {
    pthread_t produtor_thread, consumidor_thread;

    // Inicializa os semáforos
    
    // Insira o código aqui para completar

    // Cria as threads
    pthread_create(&produtor_thread, NULL, (void *) produtor, NULL);
    pthread_create(&consumidor_thread, NULL, (void *) consumidor, NULL);

    // Aguarda as threads terminarem
    pthread_join(produtor_thread, NULL);
    pthread_join(consumidor_thread, NULL);

    // Destroi os semáforos
    sem_destroy(&espera_vaga);
    sem_destroy(&espera_dado);
    sem_destroy(&exclusao_mutua);

    printf("Execucao finalizada.\n");
    return 0;
}

