#pragma once
#ifndef __HEADER_H_
#define __HEADER_H_

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>

#define EMPTY_STACK -1
#define EMPTY_LIST -1
#define MAX_LENGTH 20
#define TRUE 1
#define FALSE 0

#ifdef __cplusplus
extern "C" {
#endif

	typedef struct Node {
		int val;
		struct Node* next;
	}Node;

	typedef struct Stack {
		Node* top;
	}Stack;

	Stack* Create();
	Stack* Push(Stack* stack, int vertex);
	int Pop(Stack* stack);
	char IsEmpty(Stack* stack);
	void Destroy(Stack* stack);
	int Peek(Stack* stack);
	void PrintStack(Stack* myStack);
	int** CreateMatrix(int n);
	void FillZero(int** matrix, int n);
	void FillOne(int** matrix, int n);
	void PrintMatrix(int** mass, int size);
	void DFS(FILE* stream, int** matrix, int n);
	int** ReadGraph(FILE* stream, int** matrix);
	void DestroyMatrix(int** matrix, int n);

#ifdef __cplusplus
}
#endif

#endif