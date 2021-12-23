#pragma once
#pragma once
#ifndef __HEADER_H_
#define __HEADER_H_

#include <stdio.h>
#include <stdlib.h>

#define MAX_LENGTH 999

#ifdef __cplusplus
extern "C" {
#endif

	int FindSet(unsigned long int** subset, int* mass, int** res, int n, int sum);
	int SubsetSum(int* set, int n, unsigned long int sum, int** res );
	int MassInFile(char* stream, int* mass, int size);
	void PrintRectMatrix(int** subset, int n, unsigned long int sum);
	void FillZeroRectMatrix(int** matrix, int str, unsigned long int col);
	int** CreateRectMatrix(int str, unsigned long int col);
	void PrintMassConvert(int* mass, int size);
	void PrintMass(int* mass, int size);
	int ReadData(char* filename, unsigned long int* sum, int* amount, int** mass);
	void DestroyMatrix(unsigned long int** matrix, int str, unsigned long int col);
	int LabSolution(char* input, char* output);

#ifdef __cplusplus
}
#endif

#endif