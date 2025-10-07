
// Calcular o mmc de dois numeros 
// utilizando q fatoração de numeros primos.

#include <math.h>
#include <stdio.h>

void calcularMMC(int primeiro_valor, int segundo_valor){
	
	int divisor = 2;
	int contador_primeiro, contador_segundo;
	int valor_mmc = 1;
	
	printf("MMC(%d, %d) = ", primeiro_valor, segundo_valor);

	while (primeiro_valor > 1 || segundo_valor > 1) {
		
		contador_primeiro = 0;
		contador_segundo = 0;

		while (primeiro_valor % divisor == 0){
			primeiro_valor /= divisor;
			contador_primeiro++;
		} 

		while(segundo_valor % divisor == 0) {
			segundo_valor /= divisor;
			contador_segundo++;
		}

		if(contador_primeiro > contador_segundo){

			valor_mmc *= pow(divisor, contador_primeiro);
			printf(" %d ^ %d *", divisor, contador_primeiro);
		}

		else if(contador_segundo > contador_primeiro){

			valor_mmc *= pow(divisor, contador_segundo);
			printf(" %d ^ %d *", divisor, contador_segundo);
		}

		else {
			valor_mmc *= pow(divisor, contador_primeiro);
			printf(" %d ^ %d *", divisor, contador_primeiro);
		}

		divisor++;
	}
	puts("");
	printf("Valor Final: %d \n", valor_mmc);
	
}

int main(int argc, char *argv[]){
	calcularMMC(2420, 70);
	puts("");
	calcularMMC(8370, 465);
	puts("");
	calcularMMC(1018215, 2695);
}
