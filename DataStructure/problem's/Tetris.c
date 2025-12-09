#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Piece{
	char  *PieceName;
	char  *PieceColor;
	int   PieceWeight;
	bool  PartEdge;

	struct Piece *prox;
	struct Piece *ant;
}piece;

typedef struct List{
	int			  ListSize;
	struct Piece *start_list;
	struct Piece *end_list;
}list;

piece *registerPart();
void  Enqueue(list *Source, piece *Piece);
void  printParts(list *Source);


char *PiecesOptions[] = {"T", "S1", "S2", "I", "L1", "L2", "Q"};
char *PiecesColors[] = {"Blue", "Red", "Yellow", "Brown", "Orange", "Green"};


void Insert_Elements(list *Source, piece *new_piece){

	if (Source->start_list == NULL) {
		Source->start_list = new_piece;
		Source->end_list = new_piece;
	}
	else{
		new_piece->prox = Source->start_list;
		Source->start_list->ant = new_piece;
		Source->start_list = new_piece;
	}
	Source->ListSize++;
}

list *created_list_pieces(){
	list *TetrisPieces = malloc(sizeof(list));

	if (TetrisPieces == NULL){
		printf("Memory Alocation fault.\n");
		 return NULL;
	}

	TetrisPieces->start_list = NULL;
	TetrisPieces->end_list = NULL;
	TetrisPieces->ListSize = 0;
	
	return TetrisPieces;
}

piece *created_new_piece(){
	
	piece *new_piece = malloc(sizeof(piece));
	
	if(new_piece == NULL){
		printf("Error, Alocation memory fault");
		return NULL;
	}
	
	new_piece->PieceName = malloc(4 * sizeof(char));
	new_piece->prox = NULL;
	new_piece->ant = NULL;

	return new_piece;
}

char *pieceColor(piece *new_piece){
	
	int ColorChoose;
	new_piece->PieceColor = malloc(10 * sizeof(char));

	for (int counter = 0; counter < 6; counter++ ) {
		printf("[%d] - Cor Da Peça %s \n", counter + 1, PiecesColors[counter]);
	}

	printf("Digite o numero da cor da peça:");
	scanf("%d", &ColorChoose);

	if (ColorChoose < 1 || ColorChoose > 6){
		printf("Digite um valor valido da proxima vez \n");
		return NULL;
	}

	return strcpy(new_piece->PieceColor, PiecesColors[ColorChoose - 1]);

}

char *pieceChoose(piece *new_piece){
	int Choose;

	for (int counter = 0; counter < 7; counter++ ) {
		printf("[%d] - Peça %s \n", counter + 1, PiecesOptions[counter]);
	}

	printf("\n\nDigite o número da peça que deseja Cadastrar:");
	scanf("%d", &Choose);
	
	if (Choose < 1 || Choose > 7){
		printf("Digite um valor valido da proxima vez \n");
		free(new_piece);
		return NULL;
	}

	new_piece->PieceWeight = Choose;
	return strcpy(new_piece->PieceName, PiecesOptions[Choose - 1]);
}

bool pieceEdge(piece *new_piece){

	char EdgeChoose;

	printf("A peça possui alguma borda? \n");
	scanf(" %c", &EdgeChoose);
	
	if(EdgeChoose != 's' && EdgeChoose != 'n'){
		printf("Digite ou s ou n como resposta \n");
	}
	else if(EdgeChoose == 's'){
		new_piece->PartEdge = true;
	}
	else new_piece->PartEdge = false;

	return new_piece->PartEdge;
}

void printParts(list *Source){

	if (Source->start_list == NULL){
		printf("Lista Vazia");
		return;
	}

	piece *temporary = Source->start_list;

	while (temporary->prox != NULL){
	
		printf("Peça %s - Cor %s -", temporary->PieceName, temporary->PieceColor);
		printf("%s", temporary->PartEdge == true ? "Com Borda \n": "Sem Borda \n");
		temporary = temporary->prox;
	}
}

piece *registerPart(){
	
	piece *new_piece = created_new_piece();
	
	new_piece->PieceName = pieceChoose(new_piece);
	printf("\n\nPiece Choose: %s\n\n", new_piece->PieceName);

	new_piece->PieceColor = pieceColor(new_piece);
	printf("\n\nColor: %s\n\n", new_piece->PieceColor);

	new_piece->PartEdge = pieceEdge(new_piece);
	
	return new_piece;
}


void insertionSort(list *Source){

	if (Source->start_list == NULL || Source->start_list->prox == NULL){
		return;
	}

    piece *sorted = NULL;  
    piece *current = Source->start_list;

    while (current != NULL) {
        piece *next = current->prox;  

        if (sorted == NULL || current->PieceWeight < sorted->PieceWeight) {
            
			current->prox = sorted;
            current->ant = NULL;
            if (sorted != NULL) {
                sorted->ant = current;
            }
            sorted = current;
        } else {

            piece *temporary = sorted;
            while (temporary->prox != NULL && current->PieceWeight >= temporary->prox->PieceWeight) {
                temporary = temporary->prox;
            }
            current->prox = temporary->prox;
            current->ant = temporary;
            
			if (temporary->prox != NULL) {
                temporary->prox->ant = current;
			}

            temporary->prox = current;
        }

        current = next;
    }

    Source->start_list = sorted;
    Source->end_list = sorted;

    while (Source->end_list != NULL && Source->end_list->prox != NULL) {
        Source->end_list = Source->end_list->prox;
    }
}

int main(){
	int ChooseOption;
	list *TetrisPieces = created_list_pieces();
	do {
		printf("Menu:\n1 - Cadastrar peça\n2 - Listar peças\n3 - Reorganizar peças\n0 - Sair\n");
		scanf("%d", &ChooseOption);

		if(ChooseOption > 4 || ChooseOption < 0){
		printf("Digite um valor permitido possível\n");
		}

		if(ChooseOption == 1){
			piece *pieceMade = registerPart();
			Insert_Elements(TetrisPieces, pieceMade);

		}

		else if(ChooseOption == 2){
			
			if(TetrisPieces->ListSize == 0){
				printf("nenhum elemento na lista! \n");
				
			} else printParts(TetrisPieces);
		}

		else if(ChooseOption == 3){
			insertionSort(TetrisPieces);
			printf("Peças Reorganizadas \n");
		}

	} while(ChooseOption != 0); 
	
}

