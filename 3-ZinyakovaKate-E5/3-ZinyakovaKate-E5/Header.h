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

	Tree* CreateTree(void);
	void DestroyTree(Tree* tree);
	void PrintTree(Tree* t, int n, FILE* file);
	void FillWidth(Tree* myTree);
	int CountWidth(int num);
	int Abs(int num);
	int ComparePrintResults(Tree* tree, char* resFile, char* myFile);

#ifdef __cplusplus
}
#endif

#endif