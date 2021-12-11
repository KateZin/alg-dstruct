#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "SubsetHeader.h"

int ReadData(char* filename, unsigned long int* sum, int* amount, int** mass) {
	FILE* fstdin = fopen(filename, "r");
	if (fstdin == NULL) {
		printf("Error in file");
		return -1;
	}
	fscanf(fstdin, "%lu\n", sum);
	fscanf(fstdin, "%d\n", amount);
	*mass = (int*)malloc(sizeof(int) * *amount);
	if (mass == NULL) {
		printf("error in malloc");
		fclose(fstdin);
		return -1;
	}
	for (int i = 0; i < *amount; i++) {
		int check = fscanf(fstdin, "%d", (*mass)+i);
		if (check == 0) {
			printf("error in reading from file");
			fclose(fstdin);
			free(mass);
			return NULL;
		}
	}
	fclose(fstdin);
	return 0;
}

void PrintMass(int* mass, int size) {
	printf("\n");
	for (int i = 0; i < size; i++) {
		printf("%d ", mass[i]);
	}
}

void PrintMassConvert(int* mass, int size) {
	printf("\n");
	for (int i = size - 1; i >= 0; i--) {
		printf("%d ", mass[i]);
	}
}

int** CreateRectMatrix(int str, int col) {
	int** matrix = (int**)malloc(sizeof(int*) * str);
	if (matrix == NULL) {
		return NULL;
	}
	for (int i = 0; i < str; i++) {
		matrix[i] = (int*)malloc(sizeof(int) * col);
		if (matrix[i] == NULL) {
			for (int j = 0; j <= i; j++) {
				free(matrix[j]);
			}
			free(matrix);
			return NULL;
		}
	}
	return matrix;
}

void FillZeroRectMatrix(int** matrix, int str, int col) {
	for (int i = 0; i < str; i++) {
		for (int j = 0; j < col; j++) {
			matrix[i][j] = 0;
		}
	}
}

void PrintRectMatrix(int** subset, int n, int sum) {
	printf("\n");
	for (int i = 0; i <= n; i++) {
		for (int j = 0; j <= sum; j++) {
			printf("%4d", subset[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

int FindSet(int** subset, int* mass, int** res, int n, int sum) {
	int i = n;
	int j = sum;
	int count = 0;
	int check = 0;
	while (check != sum) {
		if (mass[i - 1] == sum) {
			**res = mass[i - 1];
			return 1;
		}
		while (subset[i][j] != 0) {
			i--;
		}
		count++;
		int* tmp = realloc(*res, sizeof(int) * count);
		if (tmp == NULL) {
			printf("\nerror in memory");
			return -1;
		}
		*res = tmp;
		(*res)[count - 1] = mass[i];
		check += (*res)[count - 1];
		j = j - (*res)[count - 1];
	}
	return count;
}

int MassInFile(char* stream, int* mass, int size) {
	FILE* fp = fopen(stream, "w");
	if (fp == NULL) {
		printf("error in openning file");
		return -1;
	}
	for (int i = size - 1; i >= 0; i--) {
		fprintf(fp, "%d ", mass[i]);
	}
	fclose(fp);
	return 0;
}

int SubsetSum(int* set, int n, int sum, int** res) {
	int size = 0;
	int** subset = CreateRectMatrix(n + 1, sum + 1);
	if (subset == NULL) {
		return -1;
	}
	for (int i = 0; i <= n; i++) {
		if (i != n && set[i] < 0) {
			printf("inpit is wrong. negative number\n");
			DestroyMatrix(subset, n + 1, sum + 1);
			return -1;
		}
		subset[i][0] = 1;
	}
	for (int i = 1; i <= sum; i++) {
		subset[0][i] = 0;
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= sum; j++) {
			if (j < set[i - 1]) {
				subset[i][j] = subset[i - 1][j];
			}
			if (j >= set[i - 1]) {
				subset[i][j] = subset[i - 1][j] || subset[i - 1][j - set[i - 1]];
			}
		}
	}
	*res = (int*)malloc(sizeof(int));
	if (*res == NULL) {
		DestroyMatrix(subset, n+1, sum+1);
		return -1;
	}
	int* tmp = *res;
	if (subset[n][sum] == 1) {
		size = FindSet(subset, set, &tmp, n, sum);
		if (size == -1) {
			free(res);
			DestroyMatrix(subset, n + 1, sum + 1);
			return -1;
		}
		*res = tmp;
	}
	else {
		size = 1;
		(*res)[0] = 0;
	}
	DestroyMatrix(subset, n + 1, sum + 1);
	return size;
}

void DestroyMatrix(int** matrix, int str, int col) {
	for (int i = 0; i < str; i++) {
		free(matrix[i]);
	}
	free(matrix);
}

int LabSolution(char* input, char* output) {
	int* set = NULL;
	unsigned long int num;
	int amount;
	int check = ReadData(input, &num, &amount, &set);
	if (check == -1) {
		printf("error in reading data");
		return -1;
	}
	int* res = NULL;
	int size = SubsetSum(set, amount, num, &res);
	if (size == -1) {
		free(set);
		printf("error in SubsetSum function");
		return -1;
	}
	check = MassInFile(output, res, size);
	if (check == -1) {
		free(set);
		free(res);
		printf("error in filling data");
		return -1;
	}
	free(res);
	free(set);
	return 0;
}