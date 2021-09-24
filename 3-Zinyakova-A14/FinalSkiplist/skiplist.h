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


//node* buildNode(int key, node* down_node, node* next_node);
struct list* createList(); //
node* search(node* elem, int key); //
//char coin();
//node* insert(node* elem, int key);
void listInsert(list** mylist, int key, int* size); //
void printWholeList(node* elem);
//void printList(node* elem);
void deleteEl(node* element, int key, int* size); //
int listDeleteEl(list** mylist, int key, int* size); //


