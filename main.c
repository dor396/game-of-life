#include <stdio.h>
#include "funcs.h"
#define FILES_ERROR 1;
//working game of life but still not done because time limit.
int main(int argc,char* argv[]) {
	//List of "list of 'Life'"
	List* gameBoard = createList(&destroyList);
	char temp;
	int error;
	if (argc != 2) {
		printf("Enter Board File ONLY!");
		return FILES_ERROR;
	}
	error = BuildBoard(gameBoard, argv[1]);
	if (error) {
		//can print error types..
		return 1;
	}
	PrintBoard(gameBoard);
	printf("\n");
	scanf("%c", &temp);
	while (temp != '0') {
		NextStep(gameBoard);
		PrintBoard(gameBoard);
		scanf(" %c", &temp);
	}
	destroyList(gameBoard);
	return 0;
}