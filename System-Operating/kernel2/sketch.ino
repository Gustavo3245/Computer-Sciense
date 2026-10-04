#include "kernel.h"
#include <TimerOne.h>

void setup() {
  // put your setup code here, to run once:

  //declara os processos
	process p1 = {tst1,8,0};
	process p2 = {tst2,4,0};
	process p3 = {tst3,2,0};

  //inicialização dos periféricos
  Serial.begin(9600);

	kernelInit();

  if (kernelAddProc(&p1) == SUCCESS){
		Serial.println("1st process added");}
	if (kernelAddProc(&p2) == SUCCESS){
		Serial.println("2st process added");}
	if (kernelAddProc(&p3) == SUCCESS){
		Serial.println("3st process added");}

// Iniciar a Interrupção de Timer 
Timer1.initialize(10e6);//microsegundos 10x10e-6 = 1s
Timer1.attachInterrupt(tick);

//execução do Kernel
kernelLoop();

}


void tick(){
  kernelTick();
}



char tst1(void){
	Serial.println("Processo 1");
	return REPEAT;
}


char tst2(void){
  Serial.println("Processo 2");
  return SUCCESS;
}

char tst3(void){
	Serial.println("Processo 3");
	return REPEAT;
}


void loop() {
  // put your main code here, to run repeatedly:
}
