#include "kernel.h"

#define POOL_SIZE 10
#define MIN_INT -30000

//armazena as referï¿½ncias dos processos
volatile static process* pool[POOL_SIZE];

//primeiro elemento do buffer
volatile static int start;

//ï¿½ltimo elemento do buffer
volatile static int end;

//adiciona os processos no pool
char kernelAddProc(process* newProc){
//adiciona os processos somente se houver espaï¿½o livre
//o fim nunca pode coincidir com o inï¿½cio
	if(((end+1)%POOL_SIZE) != start){//sempre proteje o espaï¿½o depois do ï¿½ltimo
		//protege acesso a pool
				
		//adiciona o novo processo e agenda para executar imediatamente
		
		
		pool[end] = newProc;
		end = (end+1)%POOL_SIZE;
		//libera pool de processos
				
		return SUCCESS;			
	}
	return FAIL;
}

//inicializa o kernel
char kernelInit(void){
	start=0;
	end=0;
	return SUCCESS;
}

//executa os processos do 'pool'
void kernelLoop(void){
	unsigned int count;
	unsigned int next;
	process * tempProc;
	for(;;){    
		
		if(start != end){						
			//procura a próxima função com base no tempo
			
			//Algoritmo de escalonamento
			
			
								
			while((pool[start]->deadline) > 0){
				//coloca a CPU em modo de economia de energia
				
			}						
			switch(pool[start]->func()){
				case REPEAT:
					kernelAddProc(pool[start]);
					break;
				case FAIL:
					break;
				default:
					break;						
			}
			start = (start+1)%POOL_SIZE;			
		}
					
	}	
}

void kernelTick(void){
	//Aqui deve decrementar o deadline de todos os processos a cada passagem do tempo por interrupção de hardware 
}
