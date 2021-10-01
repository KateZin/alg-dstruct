#include <stdio.h>
#include"skiplist.h"
#include<math.h>

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

struct list* createList() {
	struct list* newList = (list*)malloc(sizeof(list));    
	if (newList == NULL) {
		printf("error in memory");
		return NULL;
	}
	node* head = _buildNode((-1) * INFINITY, NULL, NULL);
	node* tail = _buildNode(INFINITY, NULL, NULL);
	newList->head = head;
	newList->tail = tail;
	head->next = tail;
	newList->size = 0;
	return newList;
}

node* search(node* elem, int key) {
	key = (float)key;
	while (elem->next->value < key)
		elem = elem->next;
	if (elem->next->value == key)
		return elem->next;
	else if (elem->next->value > key)
		elem = elem->down;
	if (elem == NULL)
		return NULL;
	else
		search(elem, key);
}

char coin() {
	return rand() % 2;
}

node* insert(node* elem, int key, int* size) {
	if (search(elem, key)) {
		printf("element is already existed");
		return NULL;
	}
	else
		*size = *size + 1;
	while (elem->next != NULL && elem->next->value < key) {
		elem = elem->next;
	}

	node* downNode;
	if (elem->down == NULL) {
		downNode = NULL;
	}
	else {
		downNode = insert(elem->down, key, size);
	}
	if (downNode != NULL || elem->down == NULL) {
		elem->next = buildNode(key, downNode, elem->next);
		if (coin() == 1) {
			return elem->next;
		}
		return NULL;
	}
	return NULL;
}

void printList(node* elem) {
	int i = 0;
	node* curNode = elem;
	while (curNode->next->value == INFINITY) {
		if ((curNode->value != -1*INFINITY) && (curNode->value != INFINITY))
			printf("%d ", (int)curNode->value);
		curNode = curNode->next;
	}
	printf("\n");
}

int deleteEl(node* elem , int key, int* size) {
	if (size == 0) {
		printf("empty list");
		return -1;
	}
	if (search(elem, key) == NULL) {
		printf("Such element doesn't exist");
		return -1;
	}
	while (elem->next != NULL && elem->next->value < key)
		elem = elem->next;
	if (elem->down != NULL)
		deleteEl(elem->down, key, size);
	if (elem->next != NULL && elem->next->value == key) {
		elem->next = elem->next->next;
		if (elem->down == NULL) {
			(*size) = (*size) - 1;
		}
	}
	return 0;
}


