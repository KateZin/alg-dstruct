#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include "graph.h"

#define EMPTY_STACK -1
#define EMPTY_LIST -1
#define MAX_LENGTH 20
#define TRUE 1
#define FALSE 0

Stack* Create() {
	Stack* stack = (Stack*)malloc(sizeof(Stack));
	if (stack == NULL) {
		return NULL;
	}
	stack->top = NULL;
	return stack;
}

Stack* Push(Stack* stack, int vertex) {
	Node* myNode = (Node*)malloc(sizeof(Node));
	if (myNode == NULL) {
		return NULL;
	}
	myNode->val = vertex;
	myNode->next = stack->top;
	stack->top = myNode;
	return stack;
}

char IsEmpty(Stack* stack) {
	if (stack->top == NULL) {
		return TRUE;
	}
	return FALSE;
}

int Pop(Stack* stack) {
	if (IsEmpty(stack) != TRUE) {
		Node* freeNode = stack->top;
		int vertex = freeNode->val;
		stack->top = stack->top->next;
		free(freeNode);
		return vertex;
	}
	return EMPTY_STACK;
}

void Destroy(Stack* stack) {
	Node* tmp = stack->top;
	while (tmp != NULL) {
		Node* ToFree = tmp;
		tmp = tmp->next;
		free(tmp);
	}
	free(stack);
}

int Peek(Stack* stack) {
	return stack->top->val;
}

void PrintStack(Stack* myStack) {
	Node* a = myStack->top;
	while (IsEmpty(myStack) == FALSE) {
		a = myStack->top;
		printf("%d\n", a->val);
		Pop(myStack);
	}
}

int** CreateMatrix(int n) {
	int** matrix = (int**)malloc(sizeof(int*) * n);
	if (matrix == NULL) {
		return NULL;
	}
	for (int i = 0; i < n; i++) {
		matrix[i] = (int*)malloc(sizeof(int) * n);
		if (matrix[i] == NULL) {
			for (int j = 0; j < i; j++) {
				free(matrix[j]);
			}
			free(matrix);
			return NULL;
		}
	}
	return matrix;
}

void FillZero(int** matrix, int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			matrix[i][j] = 0;
		}
	}
}

void FillOne(int** matrix, int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			matrix[i][j] = 1;
		}
	}
}

void PrintMatrix(int** mass, int size) {
	printf("\n");
	for (int str = 0; str < size; str++) {
		for (int col = 0; col < size; col++) {
			printf("%d ", mass[str][col]);
			printf("%d ", mass[str][col]);
		}
		printf("\n");
	}
}

void DFS(FILE* stream, int** matrix, int n) {
	int* visited = (int*)malloc(sizeof(int) * n);
	if (visited == NULL) {
		return;
	}
	Stack* myStack = Create();
	if (myStack == NULL) {
		free(visited);
		return;
	}
	int start = 0;
	Push(myStack, start);
	for (int i = 0; i < n; i++) {
		visited[i] = 0;
	}
	visited[0] = 1;
	fprintf(stream, "%d ", Peek(myStack));
	while (IsEmpty(myStack) == FALSE) {
		int v = -1;
		int a = Peek(myStack);
		for (int i = 0; i < n; i++) {
			if (matrix[a][i] == 1 && visited[i] == 0) {
				v = i;
				break;
			}
		}
		if (v == -1) {
			Pop(myStack);
		}
		else {
			visited[v] = 1;
			fprintf(stream, "%d ", v);
			Push(myStack, v);
		}
	}
	Destroy(myStack);
	free(visited);
}

int** ReadGraph(FILE* stream, int** matrix) {
	const int maxSize = 10;
	char lineBuf[10];
	int v1, v2;
	char* check = NULL;
	while (1) {
		check = fgets(lineBuf, maxSize, stream);
		if (check == NULL) {
			break;
		}
		sscanf(lineBuf, "%d%*c%d", &v1, &v2);
		matrix[v1][v2] = 1;
		matrix[v2][v1] = 1;
	}
	return matrix;
}

void DestroyMatrix(int** matrix, int n) {
	for (int i = 0; i < n; i++) {
		free(matrix[i]);
	}
	free(matrix);
}