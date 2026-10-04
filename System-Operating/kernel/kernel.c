#include "kernel.h"

#define POOLSIZE 10

static process *pool[POOLSIZE];
static int start;
static int end;

char kernelAddProc(process* newProc){
    if(((end+1) % POOLSIZE) != start){
        pool[end] = newProc;
        end = (end + 1) % POOLSIZE;
        return SUCCESS;
    }
    return FAIL;
}

char kernelInit(void){
	start = 0;
    end = 0;
}

void kernelLoop(void){
    while (1) {
        if(start != end){
            if(pool[start]->func() == REPEAT){
                kernelAddProc(pool[start]);
                start = (start + 1) % end;
            }
        }
    }
}
