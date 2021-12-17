#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <crtdbg.h>
#include <Header.h>

int abs(int num) {
	if (num >= 0) {
		return num;
	}
	else {
		return -1 * num;
	}
}

int CountWidth(int num) {
	int count = 0;
	if (num == 0) {
		return 1;
	}
	else {
		if (num < 0) {
			count++;
		}
		do {
			count++;
			num = abs(num) / 10;
		} while (abs(num) > 0);
		return count;
	}
}

Tree* Insert(Tree* myTree, int val) {
	int flag = 0;
	if (myTree == NULL) {
		myTree = (Tree*)malloc(sizeof(Tree));
		if (myTree == NULL) {
			printf("error in memory");
			return NULL;
		}
		myTree->value = val;
		myTree->width = 0;
		myTree->left = NULL;
		myTree->right = NULL;
		return myTree;
	}
	else {
		if (val <= myTree->value) {
			myTree->left = Insert(myTree->left, val);
			if (myTree->left == NULL) {
				return NULL;
			}
		}
		else if (val > myTree->value) {
			myTree->right = Insert(myTree->right, val);
			if (myTree->right == NULL) {
				return NULL;
			}
		}
	}
	return myTree;
}

void FillWidth(Tree** myTree) {
	int countLeft = 0;
	int countRight = 0;
	int numLeft = 0, numRight = 0;
	if (myTree == NULL) {
		return;
	}
	if ((*myTree)->left == NULL && (*myTree)->right == NULL) {
		(*myTree)->width = CountWidth((*myTree)->value);
		return;
	}
	if ((*myTree)->left != NULL) {
		FillWidth(&((*myTree)->left));
		Tree* tmpTree = *myTree;
		tmpTree = tmpTree->left;
		countLeft = tmpTree->width;
		(*myTree)->width = countLeft;
		if ((*myTree)->right == NULL) {
			(*myTree)->width = countLeft + CountWidth((*myTree)->value);
		}
	}
	if ((*myTree)->right != NULL) {
		FillWidth(&((*myTree)->right));
		Tree* tmpTree = *myTree;
		tmpTree = tmpTree->right;
		numRight = CountWidth(tmpTree->value);
		countRight = tmpTree->width + CountWidth((*myTree)->value);
		(*myTree)->width += countRight;
	}
}

void PrintTreeValue(Tree* t) {
	if (t != NULL) {
		printf("%d ", t->value);
		PrintTreeValue(t->left);
		PrintTreeValue(t->right);
	}
}

void PrintTreeWidth(Tree* t) {
	if (t != NULL) {
		printf("%d ", t->width);
		PrintTreeWidth(t->left);
		PrintTreeWidth(t->right);
	}
}

void PrintTree(Tree* t) {
	if (t != NULL) {
		PrintTreeValue(t, t->value);
		printf("\n");
		PrintTreeWidth(t, t->width);
	}
	printf("\n");
}

void DestroyTree(Tree* tree) {
	if (tree != NULL) {
		DestroyTree(tree->left);
		DestroyTree(tree->right);
		free(tree);
	}
}