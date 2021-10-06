#pragma once

typedef struct node {
	float value;
	struct node* next;
	struct node* down;
} node;

typedef struct list {
	struct node* head;
	struct node* tail;
	struct list* down;
}list;

list* createList();
void deleteList(list* myList);
void listInsert(list* myList, int key);
int searchElement(list* mylist, int key);
void deleteElement(list* myList, int key);






