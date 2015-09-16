#ifndef LIST_H
#define LIST_H	

//LIST OF DOUBLES MODULE

//List Object
typedef struct List List;
//Node of list
typedef struct Node Node;
/************************************************
*create and initializing list					*
*Rerturn NULL if memory allocation failed		*
*else, return ptr to List (should be free)		*
*add function: enter p1+p2 into p1				*
*sub function: enter p1-p2 into p1				*
*div function: return pointer to p1/p2			*
************************************************/
extern List* createList(void (*destroy)(void* data));

//delete all list objects
extern void destroyList(List*);

/************************************************
*add Node before the Node sent					*
*if Node* ptr is NULL - add Node to the end of	*
list											*
*Rerturn 0 if memory allocation failed			*
*else return 1									*
************************************************/
extern int addListNode(List*, void*, Node*);

//delete Node from list
extern void deleteListNode(List*, Node*);

//return list length
extern int getListLength(List*);

//return ptr to list start
extern Node* getListFirst(List*);

//return ptr to list end
extern Node* getListLast(List*);

//return ptr to next object
extern Node* getListNext(Node*);

//return ptr to prev object
extern Node* getListPrev(Node*);

//return Node by Index
extern Node* getNode(List* list, int index);

//return Node data
extern void* getNodeData(Node*);

#endif