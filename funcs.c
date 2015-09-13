#include "funcs.h"
#include <malloc.h>
#include <stdio.h>
#define MEMORY_FLAG -1
#define SUCCESS_FLAG 0
#define FILE_FLAG -2
#define FIRST_ALLOC_FLAG 1
#define USAGE_FLAG -3
#define BOARD_COL_START_LEN 10
#define BOARD_ROW_START_LEN 10
#define NEIGHBORS_PLUS 2
#define NEIGHBORS_MINUS 3
#define AT_START 0
#define AT_END 1
struct Life {
	/****************************************************
	*it possible to use char to decrease memory usage   *
	*(in both variables)								*
	*****************************************************/
	int neighbors;
	int isLife;
};
static void DestroyLife(Life* data) {
	free(data);
}
/********************************************************
*Return R^2 array with 1 where there is life and 0 else	*
*(Like the file)										*
*********************************************************/
static int CopyBoardFromFile(List* boardPTR, const char* fileName);
//add 1 to each neighbor of the cordination
static void UpdateNeighbors(List*, int* row_Cord, int* col_Cord, int x);
static int AddEmptyRow(List* gameBoard, int at);
static int AddEmptyCol(List* gameBoard, int at);
/**************************************************************
return the board where each place have number of his neighbors*
***************************************************************/
int BuildBoard(List* gameBoard, const char* fileName) {
	int i, j;
	Node* temp_Col;
	Node* temp_RowN;
	List* temp_Row;
	Life* temp_Life;
	if (CopyBoardFromFile(gameBoard, fileName)) {
		return MEMORY_FLAG;
	}
	//counting neighbors
	for (temp_RowN = getListFirst(gameBoard), i = 0; i < getListLength(gameBoard); i++, temp_RowN = getListNext(temp_RowN)) {
		temp_Row = (List*)getNodeData(temp_RowN);
		for (temp_Col = getListFirst(temp_Row), j = 0; j < getListLength(temp_Row); j++, temp_Col = getListNext(temp_Col)) {
			temp_Life = (Life*)getNodeData(temp_Col);
			if (temp_Life->isLife) {
				UpdateNeighbors(gameBoard, &i, &j, 1);
			}
		}
	}
	return SUCCESS_FLAG;
}
static int CopyBoardFromFile(List* gameBoard, const char* fileName) {
	FILE* board = NULL;
	char runner;
	Node* temp_Col;
	board = fopen(fileName, "r");
	if (board == NULL) {
		return FILE_FLAG;
	}
	runner = fgetc(board);
	addListNode(gameBoard, createList(&DestroyLife), NULL);
	temp_Col = getListFirst(gameBoard);
	while (runner != EOF) {
		if (runner == '1' || runner == '0') {
			Life* temp = (Life*)malloc(sizeof(Life));
			if (temp == NULL) {
				return MEMORY_FLAG;
			}
			temp->isLife = runner - '0';
			temp->neighbors = 0;
			addListNode(getNodeData(temp_Col), temp, NULL);
		}
		else if (runner == '\n') {
			addListNode(gameBoard, createList(&DestroyLife), NULL);
			temp_Col = getListNext(temp_Col);
		}
		else {
			return FILE_FLAG;
		}
		runner = fgetc(board);
	} //end of while loop
	return SUCCESS_FLAG;
}
static void UpdateNeighbors(List* gameBoard, int* row_Cord, int* col_Cord, int x) {
	Node* temp_Row;
	Node* temp_Col;
	Node* temp;
	if (*row_Cord == 0) {
		AddEmptyRow(gameBoard, AT_START);
		(*row_Cord)++;
	}
	if (*row_Cord == getListLength(gameBoard) - 1) {
		AddEmptyRow(gameBoard, AT_END);
	}
	if (*col_Cord == 0) {
		AddEmptyCol(gameBoard, AT_START);
		(*col_Cord)++;
	}
	if (*col_Cord == getListLength((List*)getNodeData(getListFirst(gameBoard))) - 1) {
		AddEmptyCol(gameBoard, AT_END);
	}
	temp_Row = getNode(gameBoard, *row_Cord);
	temp_Col = getNode((List*)getNodeData(temp_Row), *col_Cord);
	/************************
	update these neighbors:	*
	*	000					*
	*	*1*				*
	*	000					*
	*************************/
	((Life*)getNodeData(getListPrev(temp_Col)))->neighbors += x;
	((Life*)getNodeData(getListNext(temp_Col)))->neighbors += x;
	/************************
	update these neighbors:	*
	*	***					*
	*	010					*
	*	000					*
	*************************/
	temp = getListPrev(temp_Row);
	temp_Col = getNode((List*)getNodeData(temp), *col_Cord);
	((Life*)getNodeData(temp_Col))->neighbors += x;
	((Life*)getNodeData(getListPrev(temp_Col)))->neighbors += x;
	((Life*)getNodeData(getListNext(temp_Col)))->neighbors += x;
	/************************
	update these neighbors:	*
	*	000					*
	*	010					*
	*	***					*
	*************************/
	temp = getListNext(temp_Row);
	temp_Col = getNode((List*)getNodeData(temp), *col_Cord);
	((Life*)getNodeData(temp_Col))->neighbors += x;
	((Life*)getNodeData(getListPrev(temp_Col)))->neighbors += x;
	((Life*)getNodeData(getListNext(temp_Col)))->neighbors += x;
}
extern void NextStep(List* gameBoard) {
	Node* temp_Col;
	Node* temp_RowN;
	List* temp_Row;
	Life* temp_Life;
	int i, j;
	//update dead\live
	for (temp_RowN = getListFirst(gameBoard), i = 0; i < getListLength(gameBoard); i++, temp_RowN = getListNext(temp_RowN)) {
		temp_Row = (List*)getNodeData(temp_RowN);
		for (temp_Col = getListFirst(temp_Row), j = 0; j < getListLength(temp_Row); j++, temp_Col = getListNext(temp_Col)) {
			temp_Life = (Life*)getNodeData(temp_Col);
			if (temp_Life->neighbors > 3 || temp_Life->neighbors < 2) {
				if (temp_Life->isLife) {
					temp_Life->isLife = NEIGHBORS_MINUS;
				}
			}
			else if (!(temp_Life->isLife) && temp_Life->neighbors == 3) {
				temp_Life->isLife = NEIGHBORS_PLUS;
			}
		}
	}
	//update neighbors
	for (temp_RowN = getListFirst(gameBoard), i = 0; i < getListLength(gameBoard); i++, temp_RowN = getListNext(temp_RowN)) {
		temp_Row = (List*)getNodeData(temp_RowN);
		for (temp_Col = getListFirst(temp_Row), j = 0; j < getListLength(temp_Row); j++, temp_Col = getListNext(temp_Col)) {
			temp_Life = (Life*)getNodeData(temp_Col);
			if (temp_Life->isLife == NEIGHBORS_PLUS) {
				UpdateNeighbors(gameBoard, &i, &j, 1);
				temp_Life->isLife = 1;
			}
			else if (temp_Life->isLife == NEIGHBORS_MINUS) {
				UpdateNeighbors(gameBoard, &i, &j, -1);
				temp_Life->isLife = 0;
			}
		}
	}
}
extern void PrintBoard(List* gameBoard) {
	Node* temp_Col = getListFirst(gameBoard);
	Node* temp_Life;
	int i, j;
	for (i = 0; i < getListLength(gameBoard); i++) {
		List* temp_List = (List*)getNodeData(temp_Col);
		temp_Life = getListFirst(temp_List);
		for (j = 0; j < getListLength(temp_List); j++) {
			printf("%d", ((Life*)getNodeData(temp_Life))->isLife);
			temp_Life = getListNext(temp_Life);
		}
		temp_Col = getListNext(temp_Col);
		printf("\n");
	}
}
extern void PrintBoardN(List* gameBoard) {
	Node* temp_Col = getListFirst(gameBoard);
	Node* temp_Life;
	int i, j;
	for (i = 0; i < getListLength(gameBoard); i++) {
		List* temp_List = (List*)getNodeData(temp_Col);
		temp_Life = getListFirst(temp_List);
		for (j = 0; j < getListLength(temp_List); j++) {
			printf("%d", ((Life*)getNodeData(temp_Life))->neighbors);
			temp_Life = getListNext(temp_Life);
		}
		temp_Col = getListNext(temp_Col);
		printf("\n");
	}
}
static int AddEmptyRow(List* gameBoard, int at) {
	List* temp_List;
	int row_Len = getListLength((List*)getNodeData(getListFirst(gameBoard)));
	int i;
	if (at == AT_START) {
		addListNode(gameBoard, createList(&DestroyLife), getListFirst(gameBoard));
		temp_List = (List*)getNodeData(getListFirst(gameBoard));
	}
	else if (at == AT_END) {
		addListNode(gameBoard, createList(&DestroyLife), NULL);
		temp_List = (List*)getNodeData(getListLast(gameBoard));
	}
	else {
		return USAGE_FLAG;
	}
	for (i = 0; i < row_Len; i++) {
		Life* temp_Life = (Life*)malloc(sizeof(Life));
		if (temp_Life == NULL){
			return MEMORY_FLAG;
		}
		temp_Life->isLife = 0;
		temp_Life->neighbors = 0;
		addListNode(temp_List, temp_Life, NULL);
	}
	return SUCCESS_FLAG;
}
static int AddEmptyCol(List* gameBoard, int at) {
	int i;
	Node* temp = getListFirst(gameBoard);
	List* temp_List;
	for (i = 0; i < getListLength(gameBoard); i++) {
		temp_List = (List*)getNodeData(temp);
		Life* temp_Life = (Life*)malloc(sizeof(Life));
		if (temp_Life == NULL) {
			return MEMORY_FLAG;
		}
		temp_Life->isLife = 0;
		temp_Life->neighbors = 0;
		if (at == AT_START) {
			addListNode(temp_List, temp_Life, getListFirst(temp_List));
		}
		else if (at == AT_END) {
			addListNode(temp_List, temp_Life, NULL);
		}
		else {
			return MEMORY_FLAG;
		}
		temp = getListNext(temp);
	}
	return SUCCESS_FLAG;
}