#include <stdio.h>
#include"skiplist.h"
#include<math.h>

node* _buildNode(float key, node* down_node, node* next_node) {
	node* newnode = (node*)malloc(sizeof(node)); // todo: сделать проверку на malloс выvдление памяти
	newnode->value = key;
	newnode->next = next_node;
	newnode->down = down_node;
	return newnode;
}

node* buildNode(int key, node* down_node, node* next_node) {
	return _buildNode((float)key, down_node, next_node);
}

struct list* createList() {
	struct list* newlist = (list*)malloc(sizeof(list));    // todo: сделать проверку на malloс выvдление памяти
	node* head = _buildNode((-1) * INFINITY, NULL, NULL);
	node* tail = _buildNode(INFINITY, NULL, NULL);
	newlist->head = head;
	newlist->tail = tail;
	head->next = tail;
	return newlist;
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

node* insert(node* elem, int key) {
	while (elem->next != NULL && elem->next->value < key) {
		elem = elem->next;
	}

	node* down_node;
	if (elem->down == NULL) {
		down_node = NULL;
	}
	else {
		down_node = insert(elem->down, key);
	}
	if (down_node != NULL || elem->down == NULL) {
		elem->next = buildNode(key, down_node, elem->next);
		if (coin() == 1) {
			return elem->next;
		}
		return NULL;
	}
	return NULL;
}

void listInsert(list** mylist, int key, int* size) {
	if (search((*mylist)->head, key)) return;
	node* newnode = insert((*mylist)->head, key);
	if (newnode != NULL) {
		list* newlist = createList();
		node* addnode = buildNode(key, newnode, newlist->tail);
		newlist->head->next = addnode;
		newlist->head->down = (*mylist)->head;
		(*mylist) = newlist;
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

void printWholeList(list** mylist) {
	node* curNode = (*mylist)->head;
	while (curNode != NULL) {
		printList(&curNode);
		curNode = curNode->down;
	}
}

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

int listDeleteEl(list** mylist, int key, int* size) {
	int currentSize = *size;
	deleteEl((*mylist)->head, key, size);
	if (currentSize < *size) return 1;
	return 0;
}
