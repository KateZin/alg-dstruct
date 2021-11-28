#include "pch.h"
#include "SubsetHeader.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

/*
IDE: Visual Studio 2019 Community Edition
OS: Windows 10 Pro Ver. 20H2 Build 19042.1288
PC configuration:
	CPU:            Intel(R) Core(TM) i3-2310M CPU @ 2.10GHz   2.10 GHz
	Motherboard:    Hewlett-Packard 1670
	RAM:            8.00 GB
	HDD:            256 GB */

//   Time: 4.292922 ms
//   Time with reading from file: 11.554175 ms

const int count = 1000000;
#define MAX_LENGTH 1000000

TEST(StressTest, SubsetSum) {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);

	FILE* fstdin = fopen("C:/Users/z.kate/Desktop/Data.txt", "w");
	char* name = "C:/Users/z.kate/Desktop/checkData.txt";
	srand(time(NULL));
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
	int sum = rand() % MAX_LENGTH;
	// fill file 
	fprintf(fstdin, "%d\n", sum);
	fprintf(fstdin, "%d\n", count);
	for (int i = 0; i < count; i++) {
		fprintf(fstdin, "%d ", rand() % MAX_LENGTH);
	}
	fclose(fstdin);
	free(countBuf);
	// read file and run functions
	fstdin = fopen("C:/Users/z.kate/Desktop/Data.txt", "r");
	if (fstdin == NULL) {
		printf("Error in file");
		ASSERT_TRUE(fstdin);
	}
	countBuf = (int*)malloc(MAX_LENGTH * sizeof(int));
	if (countBuf == NULL) {
		printf("Error in malloc");
		fclose(fstdin);
		ASSERT_TRUE(countBuf);
	}
	char* check = fgets((char*)countBuf, MAX_LENGTH, fstdin);
	if (check == NULL) {
		fclose(fstdin);
		free(countBuf);
		ASSERT_TRUE(check);
	}
	int num = atoi((char*)countBuf);
	check = fgets((char*)countBuf, MAX_LENGTH, fstdin);
	if (check == NULL) {
		fclose(fstdin);
		free(countBuf);
		ASSERT_TRUE(check);
	}
	int n = atoi((char*)countBuf);
	free(countBuf);
	int* mass = ReadMass(fstdin, n);
	if (mass == NULL) {
		ASSERT_TRUE(mass);
	}
	int* res = NULL;
	int size = SubsetSum(mass, n, num, &res);
	if (size == -1) {
		ASSERT_TRUE(size);
	}
	int toCheck = MassInFile(name, res, size);
	if (toCheck = -1) {
		ASSERT_TRUE(toCheck);
	}
	free(res);
	fclose(fstdin);
	free(mass);
}

TEST(SubSetSum, CheckResInFile) {
	char* name = "output.txt";
	FILE* fp = fopen("output.txt", "r");
	int subset[5] = { 2, 3, 4, 5, 9 };
	int n = 5;
	int sum = 10;
	int* res = NULL;
	int size = SubsetSum(subset, n, sum, &res);
	MassInFile(name, res, size);
	char str[100];
	fgets(str, 100, fp);
	EXPECT_EQ(strcmp(str, "2 3 5 "),  0);
	fclose(fp);
	free(res);
}

TEST(SubSetSum, NoSubset) {
	char* name = "output.txt";
	FILE* fp = fopen("output.txt", "r");
	int subset[5] = { 2, 3, 4, 5, 9 };
	int n = 5;
	int sum = 1;
	int* res = NULL;
	int size = SubsetSum(subset, n, sum, &res);
	MassInFile(name, res, size);
	char str[100];
	fgets(str, 100, fp);
	EXPECT_EQ(strcmp(str, "0 "), 0);
	fclose(fp);
	free(res);
}

TEST(SubSetSum, CheckSizeOfSubSet) {
	int subset[5] = { 2, 3, 4, 5, 9 };
	int n = 5;
	int sum = 10;
	int* res = NULL;
	int size = SubsetSum(subset, n, sum, &res);
	EXPECT_EQ(size, 3);
	free(res);
}