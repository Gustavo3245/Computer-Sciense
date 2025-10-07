#include <math.h>
#include <stdio.h>

void casobase(){
	int valor_inicial = 1;
	int resultado_base= pow(valor_inicial, 3) + (2 * valor_inicial);
	printf("Resultado Do Caso Base: \n");
	printf("n³ + 2 * n == %d é divisivel por 3 \n", resultado_base);
	puts("");
}

int main(int argc, char *argv[]){

	int numero_escolhido;
	printf("Digite um N pertencente ao inteiros positivos: ");
	scanf("%d", &numero_escolhido);

	if(numero_escolhido < 1){
		printf("EScolha um numero valido, > 1");
		return -1;
	}

	printf("Provando Caso Base: \n");
	casobase();

	printf("Provando: (n + 1)³ + 2(n + 1) é divisivel por 3 \n");
	printf("Provando para N = %d, n + 1 \n", numero_escolhido);
	long long int resultado = pow((numero_escolhido + 1), 3) + (2 * (numero_escolhido + 1));

	printf("Resultado Final: %llu \n",resultado);


	if (resultado % 3 == 0) {
		printf("Resultado: %llu é divisivel por 3 \n",resultado);
	}
	else{
		printf("Resultado: %llu não é divisivel por 3 \n",resultado);
		printf("A equação está complementamente errada:");
	}

}
