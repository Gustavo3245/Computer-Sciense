#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

/* A linked list is a data structure that represents a 
 set of data organized in linear and dynamic order. 
 It is made up of cells also called nodes*/

void insert_elements_list();
void print_list();


typedef struct Node{
	int valor;
	struct Node *prox;
	struct Node *ant;
}node;

node *start_node = NULL;
node *end_node = NULL;

node *node_aux;

int main(int argc, char *argv[])
{
	insert_elements_list();
	insert_elements_list();

	print_list();
}

// insert_elements_list() -Inserindo valores na lista de nodes.
void insert_elements_list(){

	node *temporary_node = malloc(sizeof(node));
	if (temporary_node == NULL){
		printf("Error, Alocation Memory");
		return;
	}

	printf("Insert value in temporary_node valor: ");
	scanf("%i", &temporary_node -> valor);

	temporary_node->prox = NULL;
	temporary_node->ant = NULL;

	if(start_node == NULL){
		start_node = temporary_node;	
		end_node = temporary_node;
	
	}else if(temporary_node->valor <= start_node->valor){
		temporary_node->prox = start_node;
		start_node->ant = temporary_node;
		start_node = temporary_node;
		
	}else if(temporary_node->valor > end_node->valor){
		end_node->prox = temporary_node;
		temporary_node->ant = end_node;
		end_node = temporary_node; 	
		
	}else{
		node_aux = start_node;

		while (node_aux->prox != NULL) {
			if(temporary_node->valor < node_aux-> prox-> valor){
				temporary_node->prox = node_aux->prox;
				temporary_node->ant = node_aux;
				node_aux->prox = temporary_node;
				temporary_node->prox->ant = temporary_node;
				return;
			}
			else
				node_aux = node_aux->prox;
		}
	}

}

//Imprimindo a lista de valores.
void print_list(){

	node *temporary = start_node;	

	if(start_node == NULL){	
		printf("Empty List!!");
	}

	do{  //Percorrendo a lista utilizando o node.
		printf("%d -> ", temporary->valor);
		temporary = temporary->prox; //recebe o proximo valor.

	} while (temporary != NULL); //enquanto o ponteiro for diferente de nulo.
	printf(" Null\n");
	printf("\n start_node: %p", start_node);
	printf("\n end_node: %p \n", end_node);

}

void remove_node(){

	int number; //numero que será procurado.
	
	//Caso a lista estiver vazia.
	if(start_node == NULL){
		printf("Empty List!!");
	}

	else{
		//pedindo o numero.
		printf("Digite o numero a ser encontrado:");
		scanf("%d", &number);

		node_aux = start_node; //Inicializando o node auxiliar.
		
		if(start_node->valor == number){

			if(start_node->prox == NULL){
				start_node = NULL;
				end_node = NULL;
			}
			else{
			node *trash = start_node;
			start_node = start_node -> prox;
			end_node = NULL;
			}
		}

		else if(number == end_node->valor){
			node *trash = end_node;
		}
	}

}

int remover_maior_elemente(){

	node_aux = start_node->prox;
	node *maior = start_node;

	while(node_aux != NULL){
		if(node_aux->valor > maior->valor){
			maior = node_aux;
		}
		else
			node_aux = node_aux->prox;
	}
	return 0;
}
