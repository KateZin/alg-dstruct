#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "SubsetHeader.h"

int* ReadMass(FILE* stream, int size) {
	int* mass = (int*)malloc(sizeof(int) * size);
	if (mass == NULL) {
		printf("error in malloc");
		return NULL;
	}
	for (int i = 0; i < size; i++) {
		int check = fscanf(stream, "%d", &mass[i]);
		if (check == 0) {
			printf("error in reading from file");
			free(mass);
			return NULL;
		}
	}
	return mass;
}

int ReadData(char* filename, int* B, int* N, int** mass) {
	FILE* fstdin = fopen(filename, "r");
	if (fstdin == NULL) {
		printf("Error in file");
		return -1;
	}
	int* countBuf = (int*)malloc(MAX_LENGTH * sizeof(int));
	if (countBuf == NULL) {
		printf("Error in malloc");
		fclose(fstdin);
		return -1;
	}
	char* check = fgets((char*)countBuf, MAX_LENGTH, fstdin);
	if (check == NULL) {
		fclose(fstdin);
		free(countBuf);
		return -1;
	}
	*B = atoi((char*)countBuf);
	check = fgets((char*)countBuf, MAX_LENGTH, fstdin);
	if (check == NULL) {
		fclose(fstdin);
		free(countBuf);
		return -1;
	}
	*N = atoi((char*)countBuf);
	free(countBuf);
	*mass = ReadMass(fstdin, *N);
	if (mass == NULL) {
		return -1;
	}
	fclose(fstdin);
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

int findSet(int** subset, int* mass, int** res, int n, int sum) {
	int i = n;
	int j = sum;
	int count = 0;
	int check = 0;
	while (check != sum) {
		if (mass[i - 1] == sum) {
			*res = mass[i - 1];
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

int SubsetSum(int set[], int n, int sum, int** res) {
	if (n > MAX_LENGTH) {
		printf("input is not correct. too many elements\n");
		return - 1;
	}
	int size = 0;
	int** subset = CreateRectMatrix(n + 1, sum + 1);
	if (subset == NULL) {
		return -1;
	}
	for (int i = 0; i <= n; i++) {
		if (set[i] < 0 && i!= n) {
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
		size = findSet(subset, set, &tmp, n, sum);
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