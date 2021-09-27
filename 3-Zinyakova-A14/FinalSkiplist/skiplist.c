#include <stdio.h>
#include"skiplist.h"
#include<math.h>




node* _buildNode(float key, node* downNode, node* nextNode) {
	node* newnode = (node*)malloc(sizeof(node)); // todo: сделать проверку на malloс выvдление памяти
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

int searchEl(list** mylist, int key) {
	node* elem = (*mylist)->head->next;
	node* a = search(elem, key);
	if (a != NULL)
		return key;
	else
		return NULL;
}

char coin() {
	return rand() % 2;
}

node* insert(node* elem, int key) {
	while (elem->next != NULL && elem->next->value < key) {
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
		elem->next = buildNode(key, downNode, elem->next);
		if (coin() == 1) {
			return elem->next;
		}
		return NULL;
	}
	return NULL;
}

void listInsert(list** myList, int key, int* size) {
	if (search((*myList)->head, key)) return;
	node* newnode = insert((*myList)->head, key);
	if (newnode != NULL) {
		list* newList = createList();
		node* addnode = buildNode(key, newnode, newList->tail);
		newList->head->next = addnode;
		newList->head->down = (*myList)->head;
		(*myList) = newList;
	}
	(*size) = (*size) + 1;
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

//void printWholeList(list** myList) {
//	node* curNode = (*myList)->head;
//	while (curNode != NULL) {
//		printList(&curNode);
//		curNode = curNode->down;
//	}
//}

void deleteEl(node* elem , int key, int* size) {
	//node* elem = (*mylist)->head;
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
}

int listDeleteEl(list** myList, int key, int* size) {
	int currentSize = *size;
	deleteEl((*myList)->head, key, size);
	if (currentSize < *size) return 1;
	return 0;
}
