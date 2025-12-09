#include <string.h>
#include <stdio.h>
#include <stdlib.h>
/*
Stack is a FILO (First In Last Out) type structure, that is, the first element 
inserted will be the last to be removed. Each element of the structure
can store one or more data and a pointer to the next element, which allows
chaining and maintains a linear structure.
*/
//Node struct for Stack list.
typedef struct Node{
	int valor;
	struct Node *prox;
}node;

//Struct Stack contend x nodes.
typedef struct Stack{
	struct Node *top_node;
	int nodesize;
}stack;

//auxiliary pointer for print and remove functions.
node *aux_pointer = NULL;
node *node_element = NULL;
//Function Prototype.
struct Stack* create_stack();
void insert_node(stack *Stack, node *node_element);
void printNode(stack *Stack);
void removedOneNode(stack *Stack);
void removedAllNodes(stack *Stack);


int main(int argc, char *argv[])
{
	//Create stack.	
	stack *Stack = create_stack();
	insert_node(Stack, node_element);
	insert_node(Stack, node_element);
	insert_node(Stack, node_element);

	printNode(Stack);

	removedOneNode(Stack);

	printNode(Stack);

	removedAllNodes(Stack);

	printNode(Stack);


	return 0;
}
// TODO: Create a Function capable of adding elements to a stack.
void insert_node(stack *Stack, node *node_element){
	
	//allocation and validation.

	if (node_element == NULL){
		printf("Error, memory allocation error");
		exit(1);
	}

	printf("Digite o valor do elemento na pilha: ");
	scanf("%d", &node_element->valor);
	
	//Push a new element in the list.
		node_element->prox = Stack->top_node;
		Stack->top_node = node_element;
		Stack->nodesize++;

}

// TODO: Alocation memory for stack node.
struct Stack* create_stack(){
	stack *Pilha = malloc(sizeof(stack));

	if (Pilha == NULL){
		printf("Error, memory allocation error \n");
		return Pilha;
	}
	Pilha -> top_node = NULL;
	Pilha -> nodesize = 0;

	return Pilha;
}

// TODO: Printing all values in the stack.
void printNode(stack *Stack){
	node *aux_pointer = Stack -> top_node;

	if(aux_pointer->prox == NULL){
		printf("Empty List \n");
	}
	else{
		do {
			printf("Valor: %d ↑\n", aux_pointer->valor);
			aux_pointer = aux_pointer -> prox;
		} while (aux_pointer != NULL);
	}
}

// TODO: Removing the top element from the stack.
void removedOneNode(stack *Stack){
	node *aux_pointer = Stack -> top_node;

	if(aux_pointer->prox == NULL){
		printf("Empty List \n");
	}
	else{
		printf("remove node: %d \n", aux_pointer->valor);
		Stack->top_node = Stack->top_node->prox;
		free(aux_pointer);
	}
}

// TODO: Removing all elements from the stack.
void removedAllNodes(stack *Stack){

	if(Stack->top_node == NULL){
		printf("Empty List \n");
	}
	else{
		do {
			node *aux_pointer = Stack ->top_node;

			printf("remove node: %d \n", aux_pointer->valor);
			Stack->top_node = aux_pointer-> prox;
			free(aux_pointer);
		} while (Stack->top_node->prox != NULL);
	}
}
