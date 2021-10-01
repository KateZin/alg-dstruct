#pragma once

typedef struct node {
	float value;
	struct node* next;
	struct node* down;
} node;

typedef struct list {
	struct node* head;
	struct node* tail;
	int size;
}list;

node* buildNode(int key, node* down_node, node* next_node);
struct list* createList();
node* search(node* elem, int key);
node* insert(node* elem, int key, int* size);
void printList(node* elem);
int deleteEl(node* element, int key, int* size);



