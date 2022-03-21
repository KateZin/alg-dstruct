#pragma once
#include <stdio.h>
#define BUFFER_SIZE 16

typedef struct Tree{
	struct Tree* parent;
	int keys[3];
	struct Tree* first;
	struct Tree* second;
	struct Tree* third;
	struct Tree* fourth;
	int size;
} Tree;

//Tree* CreateTree(int value);
//Tree* CreateAndFillTree(int value, Tree* first, Tree* second, Tree* third, Tree* fourth, Tree* parent);
//char FindKey(Tree* tree, int value);
//void swap(int* x, int* y);
//void sort2(int* x, int* y);
//void sort3(int* x, int* y, int* z);
//void SortKeys(Tree* tree);
//void InsertNode(int value, Tree* tree);
//void DeleteKeyFromNode(int value, Tree* treeNode);
//void TransformToNode(int value, Tree* treeNode, Tree* first, Tree* second);
//char IsLeaf(Tree* tree);
//Tree* Insert(Tree* tree, int value);
//Tree* DeleteNode(Tree* tree, int value);
//Tree* FindMin(Tree* tree);
//Tree* Split(Tree* tree);
//Tree* Search(Tree* tree, int value);
//Tree* Fix(Tree* leaf);
//Tree* Merge(Tree* leaf);
//Tree* Redistribute(Tree* leaf);
//void PrintTree(Tree* tree);
//void DestroyTree(Tree* tree);
//int Solution(FILE* fpIn, FILE* fpOut);
