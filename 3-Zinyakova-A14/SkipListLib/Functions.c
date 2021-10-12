#include <stdio.h>
#include "Header.h"
#include <math.h>
#include <stdlib.h>
#pragma warning (disable:4996)

node* _buildNode(float key, node* downNode, node* nextNode) {
	node* newnode = (node*)malloc(sizeof(node));
	if (newnode == NULL) {
		printf("error in memory");
		return NULL;
	}
	newnode->value = key;
	newnode->next = nextNode;
	newnode->down = downNode;
	return newnode;
}

node* buildNode(int key, node* downNode, node* nextNode) {
	return _buildNode((float)key, downNode, nextNode);
}

list* createList() {
	list* newList = (list*)malloc(sizeof(list));
	if (newList == NULL) {
		printf("error in memory");
		return NULL;
	}
	node* head = _buildNode((-1) * INFINITY, NULL, NULL);
	node* tail = _buildNode(INFINITY, NULL, NULL);
	if (head == NULL || tail == NULL) {
		printf("\n The list cannot be created\n");
		free(newList);
		free(head);
		free(tail);
		return NULL;
	}
	newList->head = head;
	newList->tail = tail;
	newList->down = NULL;
	head->next = tail;
	return newList;
}

node* search(node* elem, int key) {
	while (elem->next->value < (float)key) {
		elem = elem->next;
	}
	if (elem->next->value == (float)key) {
		return elem->next;
	}
	else if (elem->next->value > (float) key) {
		elem = elem->down;
	}
	if (elem == NULL) {
		return NULL;
	}
	else {
		search(elem, key);
	}
}

// если возвращает 1 - элемент найден, 0 - не найден
int searchElement(list* mylist, int key) {
	node* elem = mylist->head;
	if (search(elem, key) == NULL) {
		return 0;
	}
	else {
		return 1;
	}
}

char coin() {
	return rand() % 2;
}

node* insert(node* elem, int key) {
	if (search(elem, key)) {
		printf("element is already existed");
		return NULL;
	}
	while (elem->next != NULL && elem->next->value < (float)key) {
		elem = elem->next;
	}
	node* downNode;
	if (elem->down == NULL) {
		downNode = NULL;
	}
	else {
		downNode = insert(elem->down, key);
	}
	if (downNode != NULL || elem->down == NULL) {
		node* newNext = buildNode(key, downNode, elem->next);
		if (newNext == NULL) {
			printf("\nThe node hasn't been created");
			return NULL;
		}
		else {
			elem->next = newNext;
		}
		if (coin() == 1) {
			return elem->next;
		}
		return NULL;
	}
	return NULL;
}

void listInsert(list** ptrList, int key) {
	list* myList = *ptrList;
	if (search(myList->head, key)) {
		return;
	}
	node* newnode = insert(myList->head, key);
	if (newnode != NULL) {
		list* newList = createList();
		if (newList == NULL) {
			printf("\nNew level hasn't been created\n");
			return;
		}
		node* addnode = buildNode(key, newnode, newList->tail);
		if (addnode == NULL) {
			printf("\nNew node hasn't been created\n");
			free(newList->head);
			free(newList->tail);
			free(newList);
			return;
		}
		newList->head->next = addnode;
		newList->head->down = myList->head;
		newList->down = myList;
		*ptrList = newList;
	}
}

void deleteEl(node* elem, int key) {
	while (elem->next->value < (float)key) {
		elem = elem->next;
	}
	if (elem->next->value == (float)key) {
		node* toDel = elem->next;
		elem->next = elem->next->next;
		elem = elem->down;
		free(toDel);
	}
	else if (elem->next->value > (float)key) {
		elem = elem->down;
	}
	if (elem == NULL) {
		return;
	}
	else {
		deleteEl(elem, key);
	}
}

void deleteElement(list** ptrList, int key) {
	list* myList = *ptrList;
	if (search(myList->head, key) == NULL) {
		return;
	}
	else {
		deleteEl(myList->head, key);
		while (myList->head->next == myList->tail && myList->down != NULL) {
			list* toDel = myList;
			list* downList = myList->down;
			node* temp1 = toDel->head;
			node* temp2 = toDel->tail;
			free(temp2);
			free(temp1);
			free(toDel);
			myList = downList;
			*ptrList = downList;
		}
	}
}

void deleteList(list* myList) {
	while (myList->head->next != myList->tail) {
		deleteElement(&myList, (int)myList->head->next->value);
	}
	free(myList->head);
	free(myList->tail);
	free(myList);
}

