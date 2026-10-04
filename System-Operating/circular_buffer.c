#include <stdio.h>
#include <unistd.h>

typedef int (*ptrfunc)(char param);

#define POOLSIZE 10

ptrfunc pool[POOLSIZE];

int start = 0, end = 0;


void AddFunc(ptrfunc novaFunc){
    if((end + 1) % POOLSIZE != start){
        pool[end] = novaFunc;
        end = (end+1) % POOLSIZE;
    }
}

int func(char param){
    printf("Ola executei a contagem %i", param);
    return param;
}


void exeCircular(void){
    int cont = 0;
    while(1){
        (*pool[start])(cont++);
        start = (start + 1) % end;
        sleep(1);
    }
}


int main(int argc, char *argv[]){
    
}
