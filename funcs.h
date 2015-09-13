#ifndef FUNCS_H
#define FUNCS_H
#include "list.h"
typedef struct Life Life;
extern int BuildBoard(List*, const char*);
extern void NextStep(List*);
extern void PrintBoard(List*);
extern void PrintBoardN(List* gameBoard);
#endif
