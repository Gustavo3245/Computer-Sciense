#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

// A queue is a linear data structure that follows the First In First Out (FIFO) 
// order of insertion and deletion. It means that the element that is inserted 
// first will be the first one to be removed and the element that is 
// inserted last will be removed at last.


typedef struct Node{
	int value;
	struct Node *prox_node;
}node;

typedef struct Queue{
	int queue_size;
	struct Node *head;
	struct Node *rear;
	struct Node *aux_temporary;
}queue;

// TODO: create a function that returns error when the head pointer is null.
int SourceHead_validation(queue *Source){
	
	if (Source->head == NULL){
		return -1;
	}
	return 1;
}

// TODO: create return function for create alocation queue.
queue* create_queue(){
	
	queue *Queue = malloc(sizeof(queue));
	if (Queue == NULL){
		printf("Error, Alocation Memory Error");
	}
	
	else {
		Queue->head = NULL;
		Queue->rear = NULL;
		Queue->aux_temporary = NULL;
		Queue->queue_size = 0;
	}
	return Queue;
	
}
// TODO: Enqueue or Insertion function.
void enqueue(int input_value, queue *Source){
	
	node *temporary_node = malloc(sizeof(node));
	if (temporary_node == NULL){
		printf("Error, Alocation Memory Error");
	}
	else {
		temporary_node->value = input_value;
		temporary_node->prox_node = NULL;
	}
	
	if(Source->head == NULL){
		Source->rear = temporary_node;
		Source->head = temporary_node;
	}
	else {
		Source->rear->prox_node = temporary_node;
		Source->rear = temporary_node;
	}
	Source->queue_size++;
}
// TODO: Dequeue or deletion function. (return the delete element).
int dequeue(queue *Source){

	if (SourceHead_validation(Source) == -1){
		printf("The Queue is already empty");
		return -1;
	}
	
	else {
		Source->aux_temporary = Source->head;
		Source->head = Source->head->prox_node;

		return Source->aux_temporary->value;
		free(Source->aux_temporary);
	}
	
}
// TODO: Peek: returns the front element of the queue.
int peek(queue *Source){
	
	if(SourceHead_validation(Source) == -1){
		printf("There nothing in the head of queue \n");
		return 0;
	}

	printf("\nValue in the queue head: %d \n", Source->head->value);
	return Source->head->value;

}
// TODO: Empty function for remove all elements in the data struct.
void remove_all_elements(queue *Source){

	if(SourceHead_validation(Source) == -1){
		printf("List already empty");
		return;
	}

	do {
		Source->aux_temporary = Source->head;
		
		printf("remove element: %d <-- ", Source->aux_temporary->value);
		Source->head = Source-> head-> prox_node;
		free(Source->aux_temporary);
	} while (Source->head != NULL);
	puts("");
}

//  TODO: print all elements in the queue list.
void print_queue(queue *Source){
	
	if (SourceHead_validation(Source) == -1){
		printf("List empty");
		return;
	}
	else {
		Source->aux_temporary = Source->head;
		do {
			printf("%d <-- ", Source-> aux_temporary-> value);
			Source->aux_temporary = Source-> aux_temporary-> prox_node;
		} while (Source->aux_temporary != NULL);
	}
	puts("");
	printf("The Queue Size: %d \n", Source->queue_size);
}


int main(int argc, char *argv[])
{
	queue *Fila = create_queue();
	enqueue(10, Fila);
	enqueue(11, Fila);
	enqueue(12, Fila);
	enqueue(12, Fila);
	print_queue(Fila);
	remove_all_elements(Fila);


	peek(Fila);
}
