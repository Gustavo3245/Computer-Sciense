#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void strcopia(char *leitura, char *copia){
	int sizeleitura = strlen(leitura);

	for(int valor = 0;valor < sizeleitura + 1; valor++){
		copia[valor] = leitura[valor];
	}
	printf("%s", copia);
}

void strcopiafor(char leitura[], char copia[]){
	int valor;
	for (valor = 0; valor < strlen(copia) + 1; valor++) {
		copia[valor] = leitura[valor];
	}
	copia[valor] = '\0';
	printf("%s", copia);
}


int main(int argc, char *argv[])
{
	char *leitura;
	int sizeleitura = strlen(leitura);

	printf("Digite a string para ser copiada");
	scanf("%s", leitura);
	
	char *stringcopiada = malloc(sizeof(stringcopiada) + 1);
	
	strcopia(leitura, stringcopiada);
}




