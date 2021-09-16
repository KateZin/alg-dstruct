#include <stdio.h>


#define MININF -100000
#define MAXINF 200000

//int sum(int a, int b);

// ÂÎÏÐÎÑÛ ÊÎÒÎÐÛÅ ÂÎÇÍÈÊÀÞÒ Â ÏÐÎÖÅÑÑÅ ÐÀÁÎÒÛ
// ÊÀÊ ÏÎÄÊËÞ×ÈÒÜ ÃÈÒÕÀÁ È ÐÀÁÎÒÀÒÜ ÒÀÌ
// ÌÍÅ ÂÑÅÃÄÀ ÍÀÄÎ ÏÈÑÀÒÜ STRUCT ÏÐÈ ÈÑÏÎËÜÇÎÂÀÍÈÈ 

/*
typedef struct node {
	int value;
	struct node* next;
	struct node* down;
} node;

typedef struct list {
	struct node* head;
	struct node* tail;
}list;
*/

int sum(int a, int b) {
	return a + b;
}

node* buildnode(int key, node* down_node, node* next_node) {
	node* newnode = (node*)malloc(sizeof(node));
	newnode->value = key;
	newnode->next = next_node;
	newnode->down = down_node;
	return newnode;
}


struct list* createlist() {
	struct list* newlist = (list*)malloc(sizeof(list));
	node* head = buildnode(MININF, NULL, NULL);
	node* tail = buildnode(MAXINF, NULL, NULL);
	newlist->head = head;
	newlist->tail = tail;
	head->next = tail;
	return newlist;
}


node* search(node* elem, int key) {
	while (elem->value < key)
		elem = elem->next;
	if (elem->down == NULL)
		return elem;
	search(elem->down, key);

}
char coin() {
	return rand() % 2;
}


node* insert(node* elem, int key) {
	node* down_node;
	while (elem->next != NULL && elem->next->value < key) {
		elem = elem->next;
	}
	if (elem->down == NULL) {
		down_node = NULL;
	}
	else {
		down_node = insert(elem->down, key);
	}
	if (down_node != NULL || elem->down == NULL) {
		elem->next = buildnode(key, down_node, elem->next);
		if (coin() == 1) {
			return elem->next;
		}
		return NULL;
	}
	return NULL;
}

void listinsert(list* mylist, int key, int* size) {
	node* newnode = insert(mylist->head, key);
	if (newnode != NULL) {
		list* newlist = createlist();
		newlist->head->next = newnode;
		mylist = newlist;
	}
	(*size) = (*size) + 1;
}

void printlist(node* elem, int size) {
	int i = 0;
	for (i = 0; i < size; i++) {
		if (elem->value != MININF && elem->value != MAXINF)
			printf("%d ", elem->value);
		elem = elem->next;
	}
	printf("\n");
}

//void delete (node* elem, int key, int* size) {
//	while (elem->next != NULL && elem->next->value < key)
//		elem = elem->next;
//	if (elem->down != NULL)
//		delete(elem->down, key, &size);
//	if (elem->next != NULL && elem->next->value == key)
//		elem->next = elem->next->next;
//	(*size)--;
//}
