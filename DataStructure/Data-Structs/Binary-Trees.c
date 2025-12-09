#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct node{
	int number;
	struct node *point_left;
	struct node *point_right;
} node;

void Insection_node(node *Initial_list, node *tempory_node);
bool search_binaryTree(node *Initial_list);


int main(int argc, char *argv[])
{
	//Check for invalide digit values.
	if (argc != 2){
		printf("Default: ./Binary-Trees: Values.. \n");
		return 1;
	}
	//Create the Pointer Node.
	node *Initial_list = NULL;
	
	//Iterating for argc, counter numbers.
	for (int value = 0; value < argc; value++){

		int value_number = atoi(argv[value]);
		node *tempory_node = malloc(sizeof(node));

		//Check for Memory Errors, free Memory.
		if (tempory_node == NULL){
			printf("Default: Segment Fault \n");
			free(tempory_node);
			return 1;
		}
		
		//Implementing values in tempory node.
		tempory_node -> number = value_number;
		tempory_node -> point_left = NULL;
		tempory_node -> point_right = NULL;

	//Implementing First Value in the list.
	if(Initial_list == NULL){
		Initial_list = tempory_node;
	}
		
	//If is not the case.
	else{

		//Create a boolean value to discover new space and marking current location.
		bool find_newspace = false;
		node *axillary_node = Initial_list;

		while(find_newspace == false){
			//If the element is not the first in list, and less than the current number.
			if(tempory_node-> number < axillary_node-> number){
				
				//If the element on the left does not exist, it will occupy that place.
				if (axillary_node-> point_left == NULL){
					axillary_node-> point_left = tempory_node;
					find_newspace = true;
				}
				//If the element is not null, we will use it as the current point.
				else{
					axillary_node = axillary_node -> point_left;
				}
			}

			//If the element is not the first in list, and greater than the current number.
			else if(tempory_node-> number >= axillary_node-> number){
				
				//If the element on the right does not exist, it will occupy that place.
				if (axillary_node-> point_right == NULL){
					axillary_node-> point_right = tempory_node;
					find_newspace = true;
				}
				//If the element is not null, we will use it as the current point.
				else{
					axillary_node = axillary_node -> point_right;
				}
			}
    

		}
	}

	}
}

/*
//Insection a new node.
void Insection_node(node *Initial_list, node *tempory_node){

	//Implementing First Value in the list.
	if(Initial_list == NULL){
		Initial_list = tempory_node;
	}
		
	//If is not the case.
	else{

		//Create a boolean value to discover new space and marking current location.
		bool find_newspace = false;
		node *axillary_node = Initial_list;

		while(find_newspace == false){
			//If the element is not the first in list, and less than the current number.
			if(tempory_node-> number < axillary_node-> number){
				
				//If the element on the left does not exist, it will occupy that place.
				if (axillary_node-> point_left == NULL){
					axillary_node-> point_left = tempory_node;
					find_newspace = true;
				}
				//If the element is not null, we will use it as the current point.
				else{
					axillary_node = axillary_node -> point_left;
				}
			}

			//If the element is not the first in list, and greater than the current number.
			else if(tempory_node-> number >= axillary_node-> number){
				
				//If the element on the right does not exist, it will occupy that place.
				if (axillary_node-> point_right == NULL){
					axillary_node-> point_right = tempory_node;
					find_newspace = true;
				}
				//If the element is not null, we will use it as the current point.
				else{
					axillary_node = axillary_node -> point_right;
				}
			}
    

		}
	}
	
}
*/

//Search for a number in Binary tree
bool search_binaryTree(node *Initial_list){

	//Check if the tree exists.
	if (Initial_list == NULL){
		printf("the tree do not exists \n");
		return false;
	}
	//If the tree exists.
	else{
		
		int search_number;
		printf("Digite o numero a ser consultado: ");
		scanf("%i \n", &search_number);

		// Create bool for validation, and a copy node.
		bool number_notfound = false;
		node *axillary_node = Initial_list;
	
		while(number_notfound == false){
			
			if (axillary_node-> number == search_number){
				printf("The number is the source \n");
				return true;
			}
			// Check if the number its less than the current number, if not the axillary pointer changes direct.
			else if (search_number < axillary_node-> number){
				if (axillary_node-> point_left-> number == search_number){
					printf("The number is the source \n");
					return true;
				}
				else
					axillary_node = axillary_node-> point_left; 
			}
			// Check if the number its greater than the current number, if not the axillary pointer changes direct.
			else if (search_number > axillary_node-> number){
				if (axillary_node-> point_right-> number == search_number){
					printf("The number is the source \n");
					return true;
				}
				else
					axillary_node = axillary_node-> point_right;
			}
		}

	}
	return false;
}
	/*
	// Check if the number its less than the current number. -RECURSIVE.
	else if(number < tree-> number){
		return search_binaryTree(tree->point_left, number);
	}

	// Check if the number its greater than the current number. -RECURSIVE.
	else if (number > tree-> number) {
		return search_binaryTree(tree->point_right, number);
	}
	
	//Check for the current number.
	if(number == tree-> number){
		printf("The number exists");
		return true;
	}
	//if none of the conditions are established, the number does not exist.
	return false;
	*/

