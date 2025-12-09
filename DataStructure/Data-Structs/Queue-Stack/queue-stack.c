#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

//Define function.
int alocation_Memory();

typedef struct node{
  int number;
  struct node *next;

} node;

int main(int argc, char *argv[])
{
	alocation_Memory();
	//implementando uma Linked-list

	//criando uma variavel temporaria que armazena-rá o tamanho de um nodo. 
	node *list = NULL;
	
	//adicionando valores
	for (int value = 0; value < argc; value++){
		
		int number = atoi(argv[value]);
		node *tempory_value = malloc(sizeof(node));
		
		if (tempory_value == NULL){	
			//free memory this far.
			free(tempory_value);
			return 1;

		}

		tempory_value -> number = number;
		tempory_value -> next = NULL;


		//print the hole list.    
		node *ptr = list;

		while( ptr != NULL){
		
		printf("%i\n", ptr->number);
		ptr = ptr -> next;
		}
		
		// Caso a lista estiver vazia, aponte o primeiro valor a lista.
		if (list == NULL){
			list = tempory_value;
		}
		

		// Se o proximo valor for menor que o primeiro elemento da lista, ocupará o seu lugar.
		else if(tempory_value-> number < list-> number){
			
			tempory_value-> next = list;
			list = tempory_value;
		}
		
    //Caso Nenhum.
		else{
			//Percorrendo a lista de nodes.
			for(node *ptr = NULL; ptr != NULL; ptr = ptr->next){
				//Se o proximo elemento for NULL, indica que está no final da lista, Implementará o valor.
				if (ptr->next == NULL) {
					ptr->next = tempory_value;
					break;
				}
				//Se o numero temporario for menor do que o proximo numero, receberá seu indice.
				if (tempory_value->number < ptr->next -> number){
					
					tempory_value-> next = ptr->next;
					ptr->next = tempory_value;
					break;
				}
			}
		}
		

  }
}


int alocation_Memory(){
  
  //criando um array com o tamanho de 4 inteiros
  int *array  = malloc(4 * sizeof(int));
  
  //Verificando a alocação de memoria.
  if (array == NULL){

    printf("Out of Memmory");
    return 1;
  }
  //adicionando valores ao array.
  for (int value = 0; value < 4; value++){
    array[value] = value;
  }

  // é se eu quisesse aumentar a lista?
  
  // criando uma variavel de tamanho 5.
  int *duplicated_array = malloc(5);
  
  //Verificando a alocação de memoria.
  if (duplicated_array == NULL){
    
    printf("Out of Memory");
    free(array);
    return 2;
  }

  for (int value = 0; value < 4; value++){
    duplicated_array[value] = array[value];
  }
  //liberando a memoria do array duplicado.
  //fazendo o array ser do tamanho do duplicado.
  //
  duplicated_array[4] = 4;
  free(array);
  array = duplicated_array;

  //printando valores no terminar
  for (int value = 0; value < 5; value++){
    printf("%i \n", array[value]); 

  }
  free(array);
  return 0;
}
