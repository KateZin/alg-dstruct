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

//   Time: 5.515 ms
//   Time with reading from file: 26.811 ms

const int count = 999;

TEST(StressTest, SubsetSum) {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);

	char* input = "C:/Users/z.kate/Desktop/3 сем/структуры и алгосы/for git/alg-dstruct/3-Zinyakova-D20/Subset-Test-D20/test_data/StressTest/Data.txt";
	char* name = "C:/Users/z.kate/Desktop/3 сем/структуры и алгосы/for git/alg-dstruct/3-Zinyakova-D20/Subset-Test-D20/test_data/StressTest/checkData.txt";
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
	int* set = NULL;
	int B, N, checkSum = 0;
	int check = ReadData(input, &B, &N, &set);
	if (check == -1) {
		printf("error in reading data");
		ASSERT_TRUE(check);
	}
	int* res = NULL;
	int size = SubsetSum(set, N, B, &res);
	if (size == -1) {
		ASSERT_TRUE(size);
	}
	check = MassInFile(name, res, size);
	if (check == -1) {
		ASSERT_TRUE(check);
	}
	free(res);
	free(set);
	fclose(fstdin);
}

TEST(FunctionalTest, CheckSizeOfSubSet) {
	int subset[5] = { 2, 3, 4, 5, 9 };
	int n = 5;
	int sum = 10;
	int* res = NULL;
	int size = SubsetSum(subset, n, sum, &res);
	EXPECT_EQ(size, 3);
	free(res);
}

TEST(FunctionalTest, noElements) {
	char* filename = "C:/Users/z.kate/Desktop/3 сем/структуры и алгосы/for git/alg-dstruct/3-Zinyakova-D20/Subset-Test-D20/test_data/noElements/noElementsInput.txt";
	char* name = "C:/Users/z.kate/Desktop/3 сем/структуры и алгосы/for git/alg-dstruct/3-Zinyakova-D20/Subset-Test-D20/test_data/noElements/noElementsOutput.txt";
	int* set = NULL;
	int B, N;
	int check = ReadData(filename, &B, &N, &set);
	if (check == -1) {
		printf("error in reading data");
		ASSERT_TRUE(check);
	}
	EXPECT_EQ(N, 0);
	EXPECT_EQ(B, 10);
	int* res = NULL;
	int size = SubsetSum(set, N, B, &res);
	if (size == -1) {
		ASSERT_TRUE(size);
	}
	check = MassInFile(name, res, size);
	if (check == -1) {
		ASSERT_TRUE(check);
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
	free(res);
	free(set);
}

TEST(FunctionalTest, TooManyElements) {
	// there are no real set A in file as input is wrong (N>1000). Expect error
	char* filename = "C:/Users/z.kate/Desktop/3 сем/структуры и алгосы/for git/alg-dstruct/3-Zinyakova-D20/Subset-Test-D20/test_data/TooManyElements/TooManyElements.txt";
	char* name = "C:/Users/z.kate/Desktop/3 сем/структуры и алгосы/for git/alg-dstruct/3-Zinyakova-D20/Subset-Test-D20/test_data/TooManyElements/TooManyElements.txt";
	int* set = NULL;
	int B, N;
	int toCheck = ReadData(filename, &B, &N, &set);
	if (toCheck == -1) {
		printf("error in reading data");
		ASSERT_TRUE(toCheck);
	}
	EXPECT_EQ(N, 1001);
	EXPECT_EQ(B, 10);
	int* res = NULL;
	int size = SubsetSum(set, N, B, &res);
	EXPECT_EQ(size, -1);
	free(res);
	free(set);
}

TEST(FunctionalTest, NegativeElement) {
	// input is wrong as there is a negative number. Expect error
	char* filename = "C:/Users/z.kate/Desktop/3 сем/структуры и алгосы/for git/alg-dstruct/3-Zinyakova-D20/Subset-Test-D20/test_data/NegativeElement/NegativeElement.txt";
	int* set = NULL;
	int B, N;
	int toCheck = ReadData(filename, &B, &N, &set);
	if (toCheck == -1) {
		printf("error in reading data");
		ASSERT_TRUE(toCheck);
	}
	EXPECT_EQ(N, 5);
	EXPECT_EQ(B, 10);
	int* res = NULL;
	int size = SubsetSum(set, N, B, &res);
	EXPECT_EQ(size, -1);
	free(res);
	free(set);
}

TEST(FunctionalTest,ResultExistCheck) {
	char* filename = "C:/Users/z.kate/Desktop/3 сем/структуры и алгосы/for git/alg-dstruct/3-Zinyakova-D20/Subset-Test-D20/test_data/ResultExistCheck/Input.txt";
	char* output = "C:/Users/z.kate/Desktop/3 сем/структуры и алгосы/for git/alg-dstruct/3-Zinyakova-D20/Subset-Test-D20/test_data/ResultExistCheck/Output.txt";
	int* set = NULL;
	int B, N, checkSum = 0;
	int toCheck = ReadData(filename, &B, &N, &set);
	if (toCheck == -1) {
		printf("error in reading data");
		ASSERT_TRUE(toCheck);
	}
	EXPECT_EQ(N, 10);
	EXPECT_EQ(B, 20);
	int* res = NULL;
	int size = SubsetSum(set, N, B, &res);
	for (int i = 0; i < size; i++) {
		checkSum += res[i];
	}
	EXPECT_EQ(checkSum, B);
	free(res);
	free(set);
}


TEST(FunctionalTest, ResultNotExistCheck) {
	char* filename = "C:/Users/z.kate/Desktop/3 сем/структуры и алгосы/for git/alg-dstruct/3-Zinyakova-D20/Subset-Test-D20/test_data/ResultNotExistCheck/Input.txt";
	char* output = "C:/Users/z.kate/Desktop/3 сем/структуры и алгосы/for git/alg-dstruct/3-Zinyakova-D20/Subset-Test-D20/test_data/ResultNotExistCheck/Output.txt";
	int* set = NULL;
	int B, N, checkSum = 0;
	int check = ReadData(filename, &B, &N, &set);
	if (check == -1) {
		printf("error in reading data");
		ASSERT_TRUE(check);
	}
	EXPECT_EQ(N, 10);
	EXPECT_EQ(B, 65);
	int* res = NULL;
	int size = SubsetSum(set, N, B, &res);
	EXPECT_EQ(size, 1);
	check = MassInFile(output, res, size);
	if (check == -1) {
		ASSERT_TRUE(check);
	}
	FILE* fp = fopen(output, "r");
	if (fp == NULL) {
		printf("error in file");
		ASSERT_TRUE(fp);
	}
	char str[100];
	fgets(str, 100, fp);
	EXPECT_EQ(strcmp(str, "0 "), 0);
	free(res);
	free(set);
}