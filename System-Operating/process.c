#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]){
    int pid = fork();
    for (int i = 0; i < 3; i++) {
    printf("Father Process PID=%d\n, process_id= %d", getpid(), i);
    }
}
