#include "pch.h"
#include "graph.h"
#include <crtdbg.h>
#include <Windows.h>

/*
IDE: Visual Studio 2019 Community Edition
OS: Windows 10 Pro Ver. 20H2 Build 19042.1288
PC configuration:
	CPU:            Intel(R) Core(TM) i3-2310M CPU @ 2.10GHz   2.10 GHz
	Motherboard:    Hewlett-Packard 1670
	RAM:            8.00 GB
	HDD:            256 GB

	Time: 2.263430 ms
	Used memory: about 860 MB*/

#define MAX_LENGTH 100
const int count = 15000;

TEST(GraphStressTest, GraphMain) {
	FILE* fstdin = fopen("C:/Users/z.kate/Desktop/tryToHelp.txt", "w");
	if (fstdin == NULL) {
		printf("Error in file");
		ASSERT_TRUE(fstdin);
	}
	int* countBuf = (int*)malloc(MAX_LENGTH * sizeof(int));
	if (countBuf == NULL) {
		printf("Error in malloc");
		fclose(fstdin);
		ASSERT_TRUE(countBuf);
	}
	int a = 0, b;
	// fill file 
	fprintf(fstdin, "%d\n", count);
	for (int i = 0; i < 3 * count; i++) {
		do {
			b = rand() % count;
		} while (b == a);
		fprintf(fstdin, "%d %d\n", a, b);
		a = rand() % count;
	}
	fclose(fstdin);
	// read file and do DFS
	fstdin = fopen("C:/Users/z.kate/Desktop/tryToHelp.txt", "r");
	FILE* fstdout = fopen("C:/Users/z.kate/Desktop/write.txt", "w");
	if (fstdout == NULL) {
		printf("Error in file");
		free(countBuf);
		fclose(fstdin);
		ASSERT_TRUE(fstdout);
	}
	char* check = fgets((char*)countBuf, MAX_LENGTH, fstdin);
	if (check == NULL) {
		fclose(fstdin);
		fclose(fstdout);
		free(countBuf);
	}
	int n = atoi((char*)countBuf);
	free(countBuf);
	int** matrix = CreateMatrix(n);
	if (matrix == NULL) {
		printf("Error in malloc 66\n\n");
		fclose(fstdin);
		fclose(fstdout);
		ASSERT_TRUE(matrix);
	}
	FillZero(matrix, n);
	ReadGraph(fstdin, matrix);
	DFS(fstdout, matrix, n);
	DestroyMatrix(matrix, n);
	fclose(fstdin);
	fclose(fstdout);
}