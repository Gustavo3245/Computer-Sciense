#include <math.h>
#include <stdio.h>


/* Prove por indução que
 * Se N,K e Z+ n >= 1, então:
 * 7^n - 2^n = 5k
 * 
 * */



void casebase(){
	int valor_inicial = 1;
	int resultado_final = (pow(7, valor_inicial) - pow(2, valor_inicial));
	printf("Resultado Do Caso Base: \n");
	printf("7^1 - 2^1 == %d \n", resultado_final);
	puts("");
}


int main(int argc, char *argv[])
{
	int numero_escolhido;
	printf("Digite um N pertencente ao inteiros positivos: ");
	scanf("%d", &numero_escolhido);

	if(numero_escolhido < 1){
		printf("EScolha um numero valido, > 1");
		return -1;
	}
	printf("Provando Caso Base: \n");
	casebase();
	
	printf("Provando 7^(n + 1) = 2^(n + 1) == 5k para qualquer N \n");
	printf("Provando para N = %d, n + 1 \n", numero_escolhido);
	long long int resultado = (pow(7, numero_escolhido + 1) - pow(2, numero_escolhido + 1));

	if(resultado % 5 == 0){
		long long int dividir_esquerda = resultado / 5;
		printf("esquerda: %llu, direita %llu \n", (5 * dividir_esquerda), resultado);
		printf("Os valores são iguais e divisiveis por 5");
	}
	else {
		printf("A equação está errada");
	}

}
