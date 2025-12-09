#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

void print_queue();

//Criando uam struct para representar a lista linkada
typedef struct Node{

	int number;
	struct Node *next;

}node;

node *list = NULL; //criando struct vazia para representar um ponteiro ao primeiro elemento.

int main(int argc, char **argv)
{
	//Loop pelo contador de elementos do terminal
	for(int value = 1; value < argc; value++){
		
		//Criando novo node e checando por errors de alocação de memoria.
		node *temporary_node = malloc(sizeof(node));
		if (temporary_node == NULL){

			printf("Error: Alocation Memory");
			return 1;
		}
		//Implementando valores ao novo node.
		temporary_node ->number = atoi(argv[value]);
		temporary_node ->next = NULL;
	
		node *temporary_aux = list; //Criando variavel auxiliar que apontar para o atual ultimo numero.


		//Se a lista estiver nulla, significa que é o primeiro elemento.
		if (list == NULL){
			list = temporary_node;

		}

		// Se o proximo valor for menor que o primeiro elemento da lista, ocupará o seu lugar.
		if(temporary_node-> number < list-> number){
			//aux recebe o antigo valor.
			temporary_aux = list; 

			temporary_node-> next = list;
			list = temporary_node;
		}

		//Nenhum caso.
		else{
			//precorrendo toda a lista de nodes.
			for(node *ptr = list; ptr != NULL; ptr = ptr->next){
				
				if(ptr->next == NULL){
					ptr->next = temporary_node;
				}
				
				//Se o numero temporario for menor do que o proximo numero, receberá seu indice.
				else if (temporary_node->number < ptr->next -> number){

					temporary_node-> next = ptr->next;
					ptr->next = temporary_node;
				}
			}
		}

	}
	print_queue();
}

void print_queue(){
	//precorrendo toda a lista de nodes.
	node *temporary_aux = list;

	while(temporary_aux != NULL){
		printf("Linked List value: %d\n", temporary_aux->number);
		temporary_aux = temporary_aux->next;
	}
}
