#pragma once



typedef struct node {
	int value;
	struct node* next;
	struct node* down;
} node;

typedef struct list {
	struct node* head;
	struct node* tail;
	int size;
}list;


node* buildnode(int key, node* down_node, node* next_node);
struct list* createlist();
node* search(node* elem, int key);
char coin();
node* insert(node* elem, int key);
void listinsert(list** mylist, int key, int* size);
void printWholeList(node* elem);
void printlist(node* elem);
void deleteEl(node* elem, int key, int* size);
