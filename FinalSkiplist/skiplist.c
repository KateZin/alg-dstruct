#include <stdio.h>
#include"skiplist.h"


// ÂÎĎĐÎŃŰ ĘÎŇÎĐŰĹ ÂÎÇÍČĘŔŢŇ Â ĎĐÎÖĹŃŃĹ ĐŔÁÎŇŰ
// ĘŔĘ ĎÎÄĘËŢ×ČŇÜ ĂČŇŐŔÁ Č ĐŔÁÎŇŔŇÜ ŇŔĚ
// ĚÍĹ ÂŃĹĂÄŔ ÍŔÄÎ ĎČŃŔŇÜ STRUCT ĎĐČ ČŃĎÎËÜÇÎÂŔÍČČ 


#define MININF -100000
#define MAXINF 200000

//
//typedef struct node {
//	int value;
//	struct node* next;
//	struct node* down;
//} node;
//
//typedef struct list {
//	struct node* head;
//	struct node* tail;
//}list;


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


/*
node* search( list* mylist, int key) {
	node* n = mylist->head;
	while (n->down != NULL) {
		n = n->down;
		while (n->value < n->next->value) {
			n = n->next;
		 }
	}
	return n;
}
*/

//node* search(node* elem, int key) {
//	if (elem->value < key){
//		elem = elem->next;
//	if (elem->value == key)
//			return elem;
//	} 
//	// ĺńëč đŕâĺí ňî âîçâđŕůŕĺě ýë-ň, ĺńëč áîëüřĺ, ňî áĺđĺě íčćíčé ýëĺěĺíň
//	// ĺńëč íčćíčé đŕâĺí íóëë ňî âîçâđŕůŕĺě íóëë, číŕ÷ĺ ďîâňîđ˙ĺě ďîčńę
//	
//	 if (elem->next->value > key)
//		elem = elem->down;
//	if (elem == NULL)
//		return NULL;
//	else
//		return search(elem, key);
//}


node* search(node* elem, int key) {
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
	if (elem->value == key)
		return NULL;
	node* down_node;
	if (elem->down == NULL) {
		down_node = NULL;
		// äîëćíű ÷ňî ňî âńňŕâčňü?
	}
	else {
		down_node = insert(elem->down, key);
	}
	if (down_node != NULL || elem->down == NULL) {
		elem->next = buildnode(key, down_node, elem->next);
		if (coin() == 1) {
			//	printf("coin is 1, so we go up\n");
			return elem->next;
		}
		return NULL;
	}
	return NULL;

	// ńđŕâíčâŕĺě čäĺě âďĺđĺä âíčç äî ňĺő îđ îęŕ íĺ íŕřëč ěĺńňî
	// ĺńëč 1 óđîâĺíü âńňŕâë˙ĺě ýëĺěĺíň č íčćíčé = íóë
	// ĺńëč íĺ ďĺđâűé ňî ěîíĺňęŕ, ĺńëč ěîíĺňęŕ đŕâíŕ 1 č íĺ ďĺđâűé óđîâĺíü ňî âńňŕâë˙ĺě ýëĺěĺíň âîçâđŕůŕ
}

void listinsert(list** mylist, int key, int* size) {

	node* newnode = insert((*mylist)->head, key);
	if (newnode != NULL) {
		list* newlist = createlist();
		node* addnode = buildnode(key, newnode, newlist->tail);
		newlist->head->next = addnode;
		newlist->head->down = (*mylist)->head;
		(*mylist) = newlist;
	}
	(*size) = (*size) + 1;
}

void printlist(node* elem) {
	int i = 0;
	node* curNode = elem;
	while (curNode) {
		if (curNode->value != MININF && curNode->value != MAXINF)
			printf("%d ", curNode->value);
		curNode = curNode->next;
	}
	printf("\n");
}


void printWholeList(node* elem) {
	node* curNode = elem;
	while (curNode) {
		printlist(curNode);
		curNode = curNode->down;
	}
}


void deleteEl(node* elem, int key, int* size) {
	while (elem->next != NULL && elem->next->value < key)
		elem = elem->next;
	if (elem->down != NULL)
		deleteEl(elem->down, key, size);
	if (elem->next != NULL && elem->next->value == key)
		elem->next = elem->next->next;
	(*size) = (*size) - 1;
}