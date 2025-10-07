#include "funcoes.h"
#include <stdio.h>
#include <time.h>

int main(){
	clock_t casobase_time, conjetura_time;
	int Choose_valor;
	long long int porcentagem, diferenca;

	printf("Digite um valor a ser inserido: > 1: ");
	scanf("%d", &Choose_valor);
	
	printf("Questão: 1 CaseBase e conjetura: \n");
	medir_tempo01(casebase01, conjetura01, Choose_valor);
	puts("");
	printf("Questão: 2 CaseBase e conjetura: \n");
	medir_tempo02(casebase02, conjetura02,Choose_valor);
	puts("");
	printf("Questão: 3 CaseBase e conjetura: \n");
	medir_tempo03(casebase03, conjetura03, Choose_valor);
	puts("");
	printf("Questão: 4 CaseBase e conjetura: \n");
	medir_tempo04(casebase04, conjetura04, Choose_valor);
	puts("");
	printf("Questão: 5 CaseBase e conjetura: \n");
	medir_tempo05(casebase05, conjetura05, Choose_valor);


}
