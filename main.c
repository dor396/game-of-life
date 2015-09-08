#include <stdio.h>
#include "funcs.h"
#define FILES_ERROR 1;

int main(int argc,char* argv[]) {
	//IMPORTANT NULL INIT
	Life** gameBoard = NULL;
	char temp;
	if (argc != 2) {
		printf("Enter Board File ONLY!");
		return FILES_ERROR;
	}
	BuildBoard(&gameBoard, argv[1]);
	scanf("%c", &temp);
	while (temp != '0') {
		NextStep(gameBoard);
		PrintBoard(gameBoard);
		scanf(" %c", &temp);
	}
	return 0;
}