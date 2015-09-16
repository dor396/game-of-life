#include "list.h"
#include <stdio.h>
#include <malloc.h>
//***free sum?
struct List {
	struct Node {
		struct Node* next;
		struct Node* prev;
		void* data;
	};
	struct Node* start;
	struct Node* end;
	void(*destroy)(void*);
	int length;
};
/************************************************
*create and initializing list					*
*Rerturn NULL if memory allocation failed		*
*else, return ptr to List (should be free)		*
************************************************/
extern List * createList(void (*destroy)(void* data)) {
	List* newList;
	newList = (List*)malloc(sizeof(List));
	if (newList == NULL) {
		return NULL;
	}
	newList->start = NULL;
	newList->end = NULL;
	newList->destroy = destroy;
	newList->length = 0;
	return newList;
}

//delete all list objects
extern void destroyList(List* list) {
	Node* temp;
	while (list->start != NULL) {
		temp = list->start;
		list->start = list->start->next;
		list->destroy(temp->data);
		free(temp);
	}
	free(list);
}

/************************************************
*add Node before the Node sent					*
*if Node* ptr is NULL - add Node to the end of	*
list											*
*Rerturn 0 if memory allocation failed			*
*else return 1									*
************************************************/
extern int addListNode(List* list, void* data,Node* beforeNode) {
	Node* temp = (Node*)malloc(sizeof(Node));
	if (temp == NULL) {
		return 0;
	}
	temp->next = beforeNode;
	temp->data = data;
	if (beforeNode == NULL) {
		temp->prev = list->end;
		if (list->end != NULL) {
			list->end->next = temp;
		}
		else {
			list->start = temp;
		}
		list->end = temp;
	}
	else if (beforeNode->prev==NULL){
		temp->prev = NULL;
		beforeNode->prev = temp;
		list->start = temp;
	}
	else {
		temp->prev = beforeNode->prev;
		beforeNode->prev->next = temp;
		beforeNode->prev = temp;
	}
	list->length++;
	return 1;
}

//delete Node from list
extern void deleteListNode(List* list, Node* node) {
	if (node->prev != NULL) {
		node->prev->next = node->next;
	}
	else {
		list->start = node->next;
	}
	if (node->next != NULL) {
		node->next->prev = node->prev;
	}
	else {
		list->end = node->prev;
	}
	list->length--;
	free(node->data);
	free(node);
}

//return list length
extern int getListLength(List* list) {
	return list->length;

}

//return ptr to list start
extern Node* getListFirst(List* list) {
	return list->start;
}

//return ptr to list end
extern Node* getListLast(List* list) {
	return list->end;
}

//return ptr to next object
extern Node* getListNext(Node* node) {
	return node->next;
}

//return ptr to prev object
extern Node* getListPrev(Node* node) {
	return node->prev;
}

extern Node* getNode(List* list, int index) {
	Node* temp = list->start;
	if (index < 0) {
		return NULL;
	}
	while (index > 0 && temp != NULL) {
		temp = temp->next;
		index--;
	}
	return temp;
}

//return Node data
extern void* getNodeData(Node* node) {
	return node->data;
}