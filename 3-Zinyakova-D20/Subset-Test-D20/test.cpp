#include "pch.h"
#include "SubsetHeader.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <Windows.h>

/*
IDE: Visual Studio 2019 Community Edition
OS: Windows 10 Pro Ver. 20H2 Build 19042.1288
PC configuration:
	CPU:            Intel(R) Core(TM) i3-2310M CPU @ 2.10GHz   2.10 GHz
	Motherboard:    Hewlett-Packard 1670
	RAM:            8.00 GB
	HDD:            256 GB */

//   Time: 3.9825 ms
//   Used memory: about 839 MB

const int count = 200000;

TEST(StressTest, SubsetSum) {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);

	char* input = "test_data/StressTest/Data.txt";
	char* output = "test_data/StressTest/checkData.txt";
	FILE* fstdin = fopen(input, "w");
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
	LARGE_INTEGER freq, start, end;
	QueryPerformanceFrequency(&freq);
	QueryPerformanceCounter(&start);
	int toCheck = LabSolution(input, output);
	QueryPerformanceCounter(&end);
	double time = (end.QuadPart - start.QuadPart) / (double)freq.QuadPart;
	if (toCheck == -1) {
		ASSERT_TRUE(toCheck);
	}
}

TEST(FunctionalTest, CheckWritingInFile) {
	char* filename = "test_data/CheckWriting/Input.txt";
	int* set = NULL;
	unsigned long int num;
	int amount;
	int check = ReadData(filename, &num, &amount, &set);
	if (check == -1) {
		printf("error in reading data");
		ASSERT_TRUE(check);
	}
	EXPECT_EQ(amount, 10);
	EXPECT_EQ(num, 20);
	free(set);
}

TEST(FunctionalTest, CheckSizeOfSubSet) {
	char* filename = "test_data/CheckSizeOfSubSet/input.txt";
	char* name = "test_data/CheckSizeOfSubSet/output.txt";
	int* set = NULL;
	unsigned long int num;
	int amount;
	int check = ReadData(filename, &num, &amount, &set);
	if (check == -1) {
		printf("error in reading data");
		ASSERT_TRUE(check);
	}
	EXPECT_EQ(amount, 5);
	EXPECT_EQ(num, 10);
	int* res = NULL;
	int size = SubsetSum(set, amount, num, &res);
	if (size == -1) {
		ASSERT_TRUE(size);
	}
	EXPECT_EQ(size, 3);
	free(set);
	free(res);
}

TEST(FunctionalTest, noElements) {
	char* filename = "test_data/noElements/noElementsInput.txt";
	char* name = "test_data/noElements/noElementsOutput.txt";
	int toCheck = LabSolution(filename, name);
	if (toCheck == -1) {
		ASSERT_TRUE(toCheck);
	}
	FILE* output = fopen(name, "r");
	if (output == NULL) {
		printf("error in file");
		ASSERT_TRUE(output);
	}
	char str[100];
	fgets(str, 100, output);
	EXPECT_EQ(strcmp(str, "0 "), 0);
	fclose(output);
}

TEST(FunctionalTest, NegativeElement) {
	// input is wrong as there is a negative number. Expect error
	char* filename = "test_data/NegativeElement/NegativeElement.txt";
	int* set = NULL;
	unsigned long int num;
	int amount;
	int toCheck = ReadData(filename, &num, &amount, &set);
	if (toCheck == -1) {
		printf("error in reading data");
		ASSERT_TRUE(toCheck);
	}
	EXPECT_EQ(amount, 5);
	EXPECT_EQ(num, 10);
	int* res = NULL;
	int size = SubsetSum(set, amount, num, &res);
	EXPECT_EQ(size, -1);
	free(res);
	free(set);
}

TEST(FunctionalTest,ResultExistCheck) {
	char* filename = "test_data/ResultExistCheck/Input.txt";
	char* output = "test_data/ResultExistCheck/Output.txt";
	int toCheck = LabSolution(filename, output);
	FILE* fp = fopen(output, "r");
	if (fp == NULL) {
		printf("error in file");
		ASSERT_TRUE(fp);
	}
	char str[100];
	fgets(str, 100, fp);
	EXPECT_EQ(strcmp(str, "5 1 8 2 4 "), 0);
	fclose(fp);
}

TEST(FunctionalTest, ResultIsCorrectCheck) {
	char* filename = "test_data/ResultExistCheck/Input.txt";
	char* output = "test_data/ResultExistCheck/Output.txt";
	int toCheck = LabSolution(filename, output);
	FILE* fp = fopen(output, "r");
	if (fp == NULL) {
		printf("error in file");
		ASSERT_TRUE(fp);
	}
	int res[5];
	int size = 5;
	int sumCheck = 0;
	for (int i = 0; i < size; i++) {
		int check = fscanf(fp, "%d", &res[i]);
		if (check == 0) {
			printf("error in reading from file");
			ASSERT_TRUE(check);
		}
		sumCheck += res[i];
	}
	EXPECT_EQ(sumCheck, 20);
	fclose(fp);
}

TEST(FunctionalTest, ResultNotExistCheck) {
	char* input = "test_data/ResultNotExistCheck/Input.txt";
	char* output = "test_data/ResultNotExistCheck/Output.txt";
	int toCheck = LabSolution(input, output);
	FILE* fp = fopen(output, "r");
	if (fp == NULL) {
		printf("error in file");
		ASSERT_TRUE(fp);
	}
	char str[100];
	fgets(str, 100, fp);
	EXPECT_EQ(strcmp(str, "0 "), 0);
}

TEST(FunctionalTest, SumEquelsToOneOfTheElements) {
	char* filename = "test_data/SumEquelsToOneOfTheElements/input.txt";
	char* name = "test_data/SumEquelsToOneOfTheElements/output.txt";
	int* set = NULL;
	unsigned long int num;
	int amount;
	int check = ReadData(filename, &num, &amount, &set);
	if (check == -1) {
		printf("error in reading data");
		ASSERT_TRUE(check);
	}
	EXPECT_EQ(amount, 5);
	EXPECT_EQ(num, 10);
	int* res = NULL;
	int size = SubsetSum(set, amount, num, &res);
	if (size == -1) {
		ASSERT_TRUE(size);
	}
	EXPECT_EQ(size, 1);
	check = MassInFile(name, res, size);
	if (check == -1) {
		ASSERT_TRUE(check);
	}
	FILE* fp = fopen(name, "r");
	if (fp == NULL) {
		printf("error in file");
		ASSERT_TRUE(fp);
	}
	char str[100];
	fgets(str, 100, fp);
	EXPECT_EQ(strcmp(str, "10 "), 0);
	free(res);
	free(set);
}