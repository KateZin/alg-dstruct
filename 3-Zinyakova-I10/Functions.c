#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "Header.h"

// check if

Tree* Search(Tree* myTree, int x) {
	Tree* tmpTree = myTree;
	if (!myTree) {
		return NULL;
	}
	if (x == myTree->keys[0] || x == myTree->keys[1] || x == myTree->keys[2]) {
		return myTree;
	}
	if (x < myTree->keys[0]) {
		tmpTree = myTree->sons[0];
		tmpTree = Search(tmpTree, x);
	}
	else if ((myTree->size == 2 && x < myTree->keys[1] ) || (myTree->size == 1) ){
		tmpTree = myTree->sons[1];
		tmpTree = Search(tmpTree, x);
	}
	else {
		tmpTree = myTree->sons[2];
		tmpTree = Search(tmpTree, x);
	}
	return tmpTree;
}

Tree* FindMinTree(Tree* myTree) {
	if (!myTree) {
		return myTree;
	}
	if (!myTree->sons[0]) {
		return myTree;
	}
	else {
		return FindMinTree(myTree->sons[0]);
	}
}

void ChangeNodes(int* a, int* b) {
	int tmp = a;
	a = b;
	b = tmp;
}

void DeleteKey(Tree* myTree, int x) {
	if (myTree->size >= 1 && myTree->keys[0] == x) {
		myTree->keys[0] = myTree->keys[1];
		myTree->keys[1] = myTree->keys[2];
		myTree->size--;
	}
	else if (myTree->size == 2 && myTree->keys[1] == x) {
		myTree->keys[1] = myTree->keys[2];
		myTree->size--;
	}
}

//
//Tree* Delete(Tree* myTree, int x) {
//	if (!myTree) {
//		return NULL;
//	}
//	Tree* minTree;
//	Tree* nodeToDel = Search(myTree, x);
//	if (!nodeToDel) {
//		return myTree;
//	}
//	if (nodeToDel->keys[0] == x) {
//		minTree = FindMinTree(nodeToDel->sons[1]);
//	}
//	else {
//		minTree = FindMinTree(nodeToDel->sons[2]);
//	}
//	if (minTree) {
//		int tmp;
//		if (x == nodeToDel->keys[0]) {
//			tmp = (nodeToDel->keys[0]);
//		}
//		else {
//			tmp = nodeToDel->keys[1];
//		}
//		ChangeNodes(tmp, minTree->keys[0]);
//		nodeToDel = minTree;
//	}
//	DeleteKey(nodeToDel, x);
//	nodeToDel = RebuildTree(nodeToDel);
//}

Tree* MoveMiddleToParent(Tree* tree) {
	Tree* parent = tree->parent;
	if (parent->size == 1) {
		parent->keys[1] = tree->keys[1];
		parent->size++;
	}
	else {
		parent->keys[2] = tree->keys[1];
		parent->size++;
	}
	tree->keys[1] = tree->keys[2];
	tree->keys[2] = NULL;
	return tree;
}


Tree* Split(Tree* tree){
	int tmp = tree->keys[0];
	tree->keys[0] = tree->keys[1];
}

Tree* RebuildTree(Tree* myTree) {
	myTree = MoveMiddleToParent(myTree);  // return previous tree !don't forget to change size!
	myTree = Split(myTree);  
	if (myTree->size == 3) {
		myTree = RebuildTree(myTree);
	}
	return myTree;
}


Tree* CreateTree(int x) {
	Tree* myTree= (Tree*)malloc(sizeof(Tree));
	myTree->parent = NULL;
	myTree->sons[0] = NULL;
	myTree->sons[1] = NULL;
	myTree->sons[2] = NULL;
	myTree->keys[0] = x;
	myTree->keys[1] = NULL;
	myTree->keys[2] = NULL;
	myTree->size = 1;
	return myTree;
}

char IsLeaf(Tree* tree) {
	if (tree->sons[0] == NULL && tree->sons[1] == NULL && tree->sons[2] == NULL) {
		return 1;
	}
	else {
		return 0;
	}
}

Tree* FindPlaceToInsert(Tree* myTree, int x) {
	if (IsLeaf(myTree)) {
		return myTree;
	}
	if (x < myTree->keys[0]) {
		myTree = FindPlaceToInsert(myTree->sons[0], x);
	}
	else if ((myTree->size == 1) || (myTree->size == 2 && x < myTree->keys[1])) {
		myTree = FindPlaceToInsert(myTree->sons[1], x);
	}
	else {
		myTree = FindPlaceToInsert(myTree->sons[2], x);
	}
	return myTree;
}

 


void PrintTree(Tree* t, int n) {
	int i;
	if (t != NULL) {
		PrintTree(t->sons[0], n + 2);
		for (i = 0; i < n; i++) {
			printf(" ");
		}
		printf("%d", t->keys[0]);
		printf( "\n");
		PrintTree(t->sons[1], n + 2); //
		for (int i = 0; i < n; i++) {
			printf(" ");
		}
		if (t->size == 2) {
			printf("%d", t->keys[1]);
		}
		printf("\n");
		PrintTree(t->sons[2], n + 2); //
	}
}

int main() {
	Tree* t = (Tree*)malloc(sizeof(Tree));
	Tree* leftT = (Tree*)malloc(sizeof(Tree));
	Tree* middleT = (Tree*)malloc(sizeof(Tree));
	Tree* rightT = (Tree*)malloc(sizeof(Tree));
	t->size = 2;
	t->keys[0] = 20;
	t->keys[1] = 27;
	t->parent = NULL;
	t->sons[0] = leftT;
	t->sons[1] = middleT;
	t->sons[2] = rightT;
	leftT->parent = t;
	middleT->parent = t;
	rightT->parent = t;
	leftT->sons[0] = NULL;
	leftT->sons[1] = NULL;
	leftT->sons[2] = NULL;
	middleT->sons[0] = NULL;
	middleT->sons[1] = NULL;
	middleT->sons[2] = NULL;
	rightT->sons[0] = NULL;
	rightT->sons[1] = NULL;
	rightT->sons[2] = NULL;
	leftT->size = 2;
	middleT->size = 1;
	rightT->size = 1;
	leftT->keys[0] = 5;
	leftT->keys[1] = 10;
	middleT->keys[0] = 25;
	rightT->keys[0] = 30;

	PrintTree(t, 1);
	int x = 30;
	Tree* findTree = Search(t, x);
	//printf("%d, %d", findTree->keys[0], findTree->keys[1]);
}