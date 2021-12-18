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
	int fillRes = 0, curWidth = 0, tmp = 0, curVal = 0, tmpRight = 0, tmpLeft = 0;
	if (myTree == NULL) {
		return;
	}
	if ((*myTree)->left == NULL && (*myTree)->right == NULL) {
		curVal = CountWidth((*myTree)->value);
		curWidth = CountWidth(curVal + tmp);
		fillRes = curVal + curWidth;
		if (CountWidth(fillRes) > CountWidth(curWidth)) {
			fillRes++;
		}
		(*myTree)->width = fillRes;
		return;
	}
	if ((*myTree)->left != NULL) {
		FillWidth(&((*myTree)->left));
		Tree* tmpTree = *myTree;
		tmpTree = tmpTree->left;
		tmp = tmpTree->width;
		curVal = CountWidth((*myTree)->value);
		curWidth = CountWidth(curVal + tmp);
		fillRes = tmp;
		if ((*myTree)->right == NULL) {
			fillRes = tmp + curVal + curWidth;
		}
	}
	if ((*myTree)->right != NULL) {
		FillWidth(&((*myTree)->right));
		Tree* tmpTree = *myTree;
		tmpTree = tmpTree->right;
		tmp = tmpTree->width;
		curVal = CountWidth((*myTree)->value);
		curWidth = CountWidth(curVal + tmp + fillRes);
		fillRes += tmp + curVal + curWidth;
	}
	if ((*myTree)->right != NULL) {
		tmpRight = (*myTree)->right->width;
	}
	if ((*myTree)->left != NULL) {
		tmpLeft = (*myTree)->left->width;
	}
	if (CountWidth(fillRes) > CountWidth(tmpRight + tmpLeft + curVal)) {
		fillRes++;
	}
	(*myTree)->width = fillRes;
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