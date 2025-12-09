#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void adicionar(char *recheio, char tamanho, char *name, float valor);
void imprimir();
void remover();

typedef struct Pizza{
	char *recheio;
	char tamanho;
	float valor;
	char *name;
	struct Pizza *proximo;
}pizza;

pizza *start_node = NULL;
pizza *topo = NULL;
int size = 0;

int main(int argc, char *argv[]){
	adicionar("4 queijos", 'P', "Gustavo", 29.99);
	adicionar("Mussarela ", 'G', "Tiago", 30.99);
	adicionar("morango", 'M', "Lucas", 19.99);
	
	remover();

	imprimir();
}

void adicionar(char *recheio, char tamanho, char *name, float valor){

	pizza *pedido = malloc(sizeof(pizza));
	pedido->recheio = recheio;
	pedido->tamanho = tamanho;
	pedido->valor = valor;
	pedido->name = name;
	pedido->proximo = NULL;

	if(start_node == NULL){
		start_node = pedido;
		topo = pedido;
	}
	else{
		topo->proximo = pedido;
		topo = pedido;
	}
	size++;
	
}

void imprimir(){
	pizza *aux = start_node;
	for (int i = 0; i< size;i++ ) {
	
		printf("Recheio: %s\n", aux->recheio);
		printf("Tamanho: %c\n", aux->tamanho);
		printf("valor: %f\n", aux->valor);
		printf("nome: %s\n\n", aux->name);
		aux = aux->proximo;
	}
}

void remover(){
	if(size == 0){
		printf("Nao existe pizza na fila");
	}
	else{
		pizza *trash = start_node;
		start_node = start_node->proximo;
		if(size == 1){
			topo = NULL;
		}
		free(trash);
		size--;
	}
}
