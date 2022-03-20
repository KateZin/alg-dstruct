#pragma once
#include <stdio.h>

typedef struct Tree{
	struct Tree* parent;
	int keys[3];
	struct Tree* sons[3];
	int size;
} Tree;

Tree* Search(Tree* myTree, int x);
