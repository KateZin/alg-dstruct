#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <crtdbg.h>
#include <Header.h>

Tree* CreateTree(void) {
	Tree* myTree = (Tree*)malloc(sizeof(Tree));
	if (myTree == NULL) {
		printf("error in memory");
		return NULL;
	}
	myTree->width = 0;
	myTree->left = NULL;
	myTree->right = NULL;
	return myTree;
}

int Abs(int num) {
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

void FillWidth(Tree* myTree) {
	int countLeft = 0;
	int countRight = 0;
	if (myTree == NULL) {
		return;
	}
	if (myTree->left == NULL && myTree->right == NULL) {
		myTree->width = CountWidth(myTree->value);
		return;
	}
	if (myTree->left != NULL) {
		FillWidth(myTree->left);
		countLeft = myTree->left->width;
		myTree->width = countLeft;
		if (myTree->right == NULL) {
			myTree->width = countLeft + CountWidth(myTree->value);
		}
	}
	if (myTree->right != NULL) {
		FillWidth(myTree->right);
		countRight = myTree->right->width + CountWidth(myTree->value);
		myTree->width += countRight;
	}
}

void PrintTree(Tree* t, int n, FILE* file) {
	int i;
	if (t != NULL) {
		PrintTree(t->right, n + 2, file);
		for (i = 0; i < n; i++) {
			fprintf(file, " ");
		}
		fprintf(file, "%d", t->value);
		fprintf(file, "\n");
		for (int i = 0; i < n; i++) {
			fprintf(file, " ");
		}
		fprintf(file, "%d\n", t->width);
		PrintTree(t->left, n + 2, file);
	}
}

void DestroyTree(Tree* tree) {
	if (tree != NULL) {
		DestroyTree(tree->left);
		DestroyTree(tree->right);
		free(tree);
	}
}