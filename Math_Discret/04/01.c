// An = 2 An - 1
#include <math.h>
#include <time.h>
#include <stdio.h>
#include "funcoes.h"

void medir_tempo01(int (*funcao)(int), int (*funcao2)(int), int valor) {
    struct timespec start, end;
	
    clock_gettime(CLOCK_MONOTONIC, &start);
    funcao(valor);
    clock_gettime(CLOCK_MONOTONIC, &end); 

    double tempo_decorrido1 = (end.tv_sec - start.tv_sec) + 
                             (end.tv_nsec - start.tv_nsec) / 1e9;
	

    clock_gettime(CLOCK_MONOTONIC, &start);
    funcao2(valor);
    clock_gettime(CLOCK_MONOTONIC, &end); 

    double tempo_decorrido2 = (end.tv_sec - start.tv_sec) + 
                             (end.tv_nsec - start.tv_nsec) / 1e9;
	
	double diferenca_percentual = ((tempo_decorrido2 - tempo_decorrido1) / tempo_decorrido1) * 100;

	printf("Tempo de execucao com o valor %d inserido: %lf \n", valor, tempo_decorrido1 * 1000);
	printf("Tempo de execucao com o valor %d inserido: %lf \n", valor, tempo_decorrido2 * 1000);
	printf("Diferenca em  porcentagem: %g\n", diferenca_percentual);

}

int casebase01(int valor_inicial){
	
	if (valor_inicial == 1) {
		return 2;
	}
	
	return 2 * casebase01(valor_inicial - 1);
	
}

int conjetura01(int valor){

	if (valor == 1) {
		return 2;
	}
	
	return pow(2, valor);
}

