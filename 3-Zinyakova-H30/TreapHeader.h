#pragma once
#include <stdio.h>
#define BUFFER_SIZE 16

typedef struct Treap {
	int key;
	int value;
	struct Treap* left;
	struct Treap* right;
} Treap;

typedef struct TreapPair {
	struct Treap* right;
	struct Treap* left;
} TreapPair;

Treap* Find(Treap* tree, int key);
TreapPair Split(Treap* tree, int key);
Treap* Merge(Treap* tree1, Treap* tree2);
Treap* Insert(Treap* tree, int key, int value);
Treap* Delete(Treap* tree, int key);
void Destroy(Treap* tree);
int Solution(FILE* fpin, FILE* fpout);