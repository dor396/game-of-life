#include "funcs.h"
#include <stdio.h>
#define MEMORY_FLAG -1
#define SUCCESS_FLAG 0
#define FILE_FLAG -2
#define FIRST_ALLOC_FLAG 1
#define BOARD_COL_START_LEN 10
#define BOARD_ROW_START_LEN 10
#define DEFAULT_JUMP 2
struct Life {
	/****************************************************
	*it possible to use char to decrease memory usage   *
	*(in both variables)								*
	*****************************************************/
	int neighbors;
	int isLife;
};
//Allocated memory to Board (RESIZE OR FIRST ALLOCATE)
static int BoardAlloc(Life*** board, int* col_Len, int* row_Len);
/********************************************************
*Return R^2 array with 1 where there is life and 0 else	*
*(Like the file)										*
*********************************************************/
static int CopyBoardFromFile(Life*** boardPTR, char* fileName, int* col_Len, int* row_Len);
//add 1 to each neighbor of the cordination
static void UpdateNeighbors(Life**, int col_Cord, int row_Cord);
/**************************************************************
return the board where each place have number of his neighbors*
***************************************************************/
void BuildBoard(Life*** boardPTR, const char* fileName) {
	int col_Len = 0, row_Len = 0;
	int i, j;
	if (CopyBoardFromFile(boardPTR, fileName, &col_Len, &row_Len)) {
		return MEMORY_FLAG;
	}
	for (i = 0; i < col_Len; i++) {
		for (j = 0; j < row_Len; j++) {
			if (((*boardPTR)[i][j]).isLife) {
				UpdateNeighbors(*boardPTR, i, j);
			}
		}
	}
	return SUCCESS_FLAG;
}
static int CopyBoardFromFile(Life*** boardPTR, char* fileName, int* col_Len, int* row_Len) {
	//allocate memory
	//copy
	//reallocate if need
	//copy
	//...
	FILE* board = NULL;
	char runner;
	int col_Cord = 1, row_Cord = 1;
	board = fopen(fileName, "r");
	if (board == NULL) {
		return FILE_FLAG;
	}
	//Allocate board memory
	if (BoardAlloc(boardPTR, col_Len, row_Len)) {
		return MEMORY_FLAG;
	}
	runner = fgetc(board);
	while (runner != EOF) {
		/*should do in broad alloc
		if (col_Cord == 0 || row_Cord == 0 || runner == '\n') {
			(*boardPTR)[col_Cord][row_Cord].isLife = 0;
			(*boardPTR)[col_Cord][row_Cord].neighbors = 0;
		}*/
		//NEED TO CHECK IF > OR >=***************************************
		if (col_Cord >= *col_Len || row_Cord >= *row_Len) {
			if (BoardAlloc(boardPTR, col_Len, row_Len)) {
				return MEMORY_FLAG;
			}
		}
		if (runner == '1') {
			(*boardPTR)[col_Cord][row_Cord].isLife = 1;
			UpdateNeighbors(*boardPTR, col_Cord, row_Cord);
		}
		else if (runner == '\n') {
			col_Cord++;
			row_Cord = 0;
			continue;
		}
		else if (runner != '0') {
			return FILE_FLAG;
		}
		row_Cord++;
		runner = fgetc(board);
	} //end of while loop
}
static int BoardAlloc(Life*** boardPTR, int* col_Len, int* row_Len) {
//	static int jumper = DEFAULT_JUMP;
	Life** temp;
	int i, j;
	int flag = !FIRST_ALLOC_FLAG;
	if (*col_Len == 0 || row_Len == 0) {
		*col_Len = BOARD_COL_START_LEN;
		*row_Len = BOARD_ROW_START_LEN;
		flag = FIRST_ALLOC_FLAG;
	}
	else {
		*col_Len *= (DEFAULT_JUMP);
		*row_Len *= (DEFAULT_JUMP);
	}
	temp = (Life**)realloc(*boardPTR, (*col_Len)*sizeof(Life*));
	if (*temp == NULL) {
		//FREE MEMORY!! (MAIN?)
		return MEMORY_FLAG;
	}
	*boardPTR = temp;
	for (i = 0;i<colLen)


	for (i = 0; i < colLen; i++) {
		(*boardPTR)[i] = (int*)malloc(rowLen*sizeof(int));
		if ((*boardPTR)[i] == NULL) {
			return MEMORY_FLAG;
		}
		for (j = 0; j < rowLen; j++) {

		}
	}
}