#include <stdio.h>
#include <stdlib.h>

typedef struct Person{
	char *name;
	char *sex;
	int age;
}person;

char nome[][50] = {"gustavo", "tiago", "ian"};
char sexualidade[][50] = {"Feminino", "Masculino", "outros"};

int main(int argc, char *argv[])
{
	int n;
	int *numeros;
	printf("Digite um valor inteiro:");
	scanf("%d", &n);
	
	numeros = (int*) malloc(n * sizeof(int));
	for (int i = 0; i < n; i++) {
		numeros[i] = rand() % 100;	
	}

	for (int i = 0; i < n; i++) {
		printf("%d -> ", numeros[i]);
	}
	puts("");

	person *pessoas = malloc(n*sizeof(person));
	
	
	for (int i = 0; i < n; i++) {

		int randomnumber = rand() % 3;
		
		pessoas[i].age = rand() % 100;
		pessoas[i].sex = sexualidade[randomnumber];
		pessoas[i].name = nome[randomnumber];
	}
	

	for (int i = 0; i < n; i++) {
		printf("%s \n", pessoas[i].name);
		printf("%d \n", pessoas[i].age);
		printf("%s \n", pessoas[i].sex);
		printf("--- \n");
	}
}
