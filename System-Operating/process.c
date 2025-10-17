#include <stdio.h>
#include <unistd.h>

/* Todo programa cria um processo, tudo feito dentro dos limites do sistema operacional precisa de um processo.
 * um processo é a ação do sistema operacional, é a forma de pegar arquivos, códigos, e executa-los.
 */

int main(int argc, char *argv[]){
    int pid = fork();
    for (int i = 0; i < 3; i++) {
    printf("Father Process PID=%d\n, process_id= %d", getpid(), i);
    }
}
