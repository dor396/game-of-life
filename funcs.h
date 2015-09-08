#ifndef FUNCS_H
#define FUNCS_H
typedef struct Life Life;
extern void BuildBoard(Life***, char*);
extern void NextStep(Life**);
extern void PrintBoard(Life**);
#endif
