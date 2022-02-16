#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "TreapHeader.h"

Treap* Find(Treap* tree, int key) {
	if (tree == NULL) {
		return NULL;
	}
	if (tree->key == key) {
		return tree;
	}
	if (tree->key > key) {
		Treap* newTree = Find(tree->left, key);
		return newTree;
	}
	else {
		Treap* newTree = Find(tree->right, key);
		return newTree;
	}
}

TreapPair Split(Treap* tree, int key) {
	if (tree == NULL) {
		TreapPair nullTreap = { NULL, NULL };
		return nullTreap;
	}
	else if (key > tree->key) {
		TreapPair tmpPair = Split(tree->right, key);
		tree->right = tmpPair.right;
		TreapPair newTreap = { tree, tmpPair.left };
		return newTreap;
	}
	else {
		TreapPair tmpPair = Split(tree->left, key);
		tree->left = tmpPair.left;
		TreapPair newTreap = { tmpPair.right, tree };
		return newTreap;
	}
}

Treap* Merge(Treap* tree1, Treap* tree2) {
	if (tree1 == NULL) {
		return tree2;
	}
	if (tree2 == NULL) {
		return tree1;
	}
	if (tree1->value > tree2->value) {
		tree1->right = Merge(tree1->right, tree2);
		return tree1;
	}
	else {
		tree2->left = Merge(tree1, tree2->left);
		return tree2;
	}
}

Treap* Insert(Treap* tree, int key, int value) {
	if (Find(tree, key) != NULL) {
		return tree;
	}
	Treap* newTree = (Treap*)malloc(sizeof(Treap));
	if (newTree == NULL) {
		return tree;
	}
	newTree->key = key;
	newTree->value = value;
	newTree->right = NULL;
	newTree->left = NULL;
	TreapPair newPair = Split(tree, key);
	newPair.right = Merge(newPair.right, newTree);
	return Merge(newPair.right, newPair.left);
}

Treap* Delete(Treap* tree, int key) {
	if (Find(tree, key) == NULL)
		return tree;
	TreapPair newPair = Split(tree, key);
	TreapPair newTree = Split(newPair.left, key + 1);
	free(newTree.right);
	return Merge(newPair.right, newTree.left);
}

void Destroy(Treap* tree) {
	if (tree != NULL) {
		Destroy(tree->left);
		Destroy(tree->right);
		free(tree);
	}
}

int Solution(FILE* fpIn, FILE* fpOut) {
	char buffer[BUFFER_SIZE] = { 0 };
	char x;
	int value;
	Treap* tree = NULL;
	while (fgets(buffer, BUFFER_SIZE, fpIn)) {
		sscanf(buffer, "%c %i", &x, &value);
		switch (x) {
		case 'a':
			tree = Insert(tree, value, rand());
			break;
		case 'r':
			tree = Delete(tree, value);
			break;
		case 'f':
			if (Find(tree, value))
				fprintf(fpOut, "yes\n");
			else
				fprintf(fpOut, "no\n");
			break;
		default:
			Destroy(tree);
			return 0;
		}
	}
	Destroy(tree);
	return 0;
}

int main(void) {
	Solution(stdin, stdout);
	return 0;
}