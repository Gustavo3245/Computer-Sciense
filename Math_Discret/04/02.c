// An = 2An - 1 + 3. A1 = 4 
#include <math.h>
#include "funcoes.h"
#include <time.h>
#include <stdio.h>


void medir_tempo02(int (*funcao)(int), int (*funcao2)(int), int valor) {
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
	printf("Diferenca em  porcentagem: %g \n", diferenca_percentual);

}

int casebase02(int valor_inicial){
	
	if (valor_inicial == 1) {
		return 4;
	}
	
	return 2 * casebase02(valor_inicial - 1) + 3;
}

int conjetura02(int valor){

	if (valor == 1) {
		return 4;
	}

	return 7 * (pow(2, valor - 1)) - 3;
}


