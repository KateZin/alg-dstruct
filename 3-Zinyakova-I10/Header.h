#pragma once
#include <stdio.h>
#define BUFFER_SIZE 16

typedef struct Tree {
    struct Tree* parent;
    int keys[3];
    struct Tree* first;
    struct Tree* second;
    struct Tree* third;
    struct Tree* fourth;
    int size;
} Tree;

Tree* CreateNode(int value);
Tree* CreateAndFillNode(int value, Tree* first, Tree* second, Tree* third, Tree* fourth, Tree* parent);
char Find(int value, int* keys, int size);
void Swap(int* x, int* y);
void Sort2(int* x, int* y);
void Sort3(int* x, int* y, int* z);
void SortKeys(int size, int* keys);
void InsertToNode(int value, Tree* treeNode);
void DeleteKey(int value, Tree* treeNode);
void TransformNode(int value, int* keys, Tree* treeNode, Tree* first, Tree* second);
char IsLeaf(Tree* tree);
Tree* InsertNode(Tree* tree, int value);
Tree* FindMin(Tree* tree);
Tree* DeleteNode(Tree* tree, int value);
Tree* Split(Tree* item);
Tree* Search(Tree* tree, int value);
Tree* Fix(Tree* leaf);
Tree* Merge(Tree* leaf);
Tree* Redistribute(Tree* leaf);
void PrintTree(Tree* tree);
void DestroyTree(Tree* tree);
int Solution(FILE* fpIn, FILE* fpOut);