#pragma once
#ifndef __HEADER_H_
#define __HEADER_H_
#include <stdio.h>


#ifdef __cplusplus
extern "C" {
#endif

	typedef struct Tree {
		int value;
		int width;
		struct Tree* left;
		struct Tree* right;
	} Tree;

	void DestroyTree(Tree* tree);
	void PrintTree(Tree* t);
	void FillWidth(Tree** myTree);
	Tree* Insert(Tree* myTree, int val);
	int CountWidth(int num);
	int abs(int num);
	void PrintTreeValue(Tree* t);
	void PrintTreeWidth(Tree* t);
	void PrintTree(Tree* t);

#ifdef __cplusplus
}
#endif

#endif
