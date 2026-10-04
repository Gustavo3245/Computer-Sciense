#include <stdio.h>
#include <unistd.h>
#include "kernel.h"

char tst1(void){
	printf("Process 1\n");
	sleep(1);
	return REPEAT;
}
char tst2(void){
	printf("Process 2\n");
	sleep(1);
	return SUCCESS;
}
char tst3(void){
	printf("Process 3\n");
	sleep(1);
	return REPEAT;
}


int main (){
	printf("...........Sistema Iniciado\n");
	//declara os processos
	process p1 = {tst1};
	process p2 = {tst2};
	process p3 = {tst3};
	kernelInit();
	if (kernelAddProc(&p1) == SUCCESS){
		printf("1st process added\n");}
	if (kernelAddProc(&p2) == SUCCESS){
		printf("2st process added\n");}
	if (kernelAddProc(&p3) == SUCCESS){
		printf("3st process added\n");}
	
	kernelLoop();
	
	return 0;	
}
