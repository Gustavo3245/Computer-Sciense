#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct node{
	int			 number;
	struct node *point_left;
	struct node *point_right;
}	Node;

typedef struct Binary_tree{
	int			 size;
	struct node *raiz;
}	Binary_tree;

int main(int argc, char *argv[]){
	
}

Node *buscar(int valor, Node *aux){

	if(valor == aux->number){

	}

	else if(valor < aux->number){

		if(aux->point_left != NULL){
			return buscar(valor, aux->point_left);
		}
		else {
			return aux;
		}
	}

	else {

		if(aux->point_right != NULL){
			return buscar(valor, aux->point_right);
		}
		else {
			return aux;
		}
	}
	
}

// Complexity é igual a de uma lista/pilha.
void imprimir(Node *aux){

	if(aux == NULL){
		printf("Binary Struct is empyt");
		return;
	}

	if(aux != NULL){
		printf("Node: %d ", aux->number);
		imprimir(aux->point_left);
		imprimir(aux->point_right);
	}
}

void add(int valor){
	Node *temporary_node = malloc(sizeof(Node));
	if(temporary_node == NULL){
		printf("Error, Memory Fault Error");
		return;
	}
	temporary_node->number = valor;
	temporary_node->point_left = NULL;
	temporary_node->point_right = NULL;

	if(Binary_tree->raiz == NULL){
		raiz = temporary_node;
	}

	else{

		Binary_tree->aux = buscar(valor, raiz);

		if(temporary_node->number == valor){
			printf("Esse valor ja existe na arvore");
		}
		else{
			if(temporary_node->number < valor){
				Binary_tree->aux->point_left = novo;
			}
			else if(temporary_node->number > valor){
				Binary_tree->aux->point_right = novo;
			}
		}
	}
}
