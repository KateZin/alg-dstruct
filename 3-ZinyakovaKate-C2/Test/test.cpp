#include "pch.h"
#include "graph.h"

/*
IDE: Visual Studio 2019 Community Edition
OS: Windows 10 Pro Ver. 20H2 Build 19042.1288
PC configuration:
    CPU:            AMD Ryzen 7 3700X 8-Core Processor 3.59 GHz
    Motherboard:    GIGABYTE B450 AORUS ELITE
    RAM:            Kingston HyperX Fury 2x8 Gb (16 Gb) dual-channel (Intel XPM profile 3200 MHz on)
    HDD:            WD Blue 1TB - this is the hard drive on which test files are being read/written
*/

/*
LabSolution_StressTest results (run on Release VS configuration):
    Time:   4.718 sec to generate graph
            20.281 sec to output answer
    RAM:    about 1.3 GB at peak
*/


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
        ASSERT_TRUE(fstdout);
    }
    char* check = fgets((char*)countBuf, MAX_LENGTH, fstdin);
    if (check == NULL) {
        free(countBuf);
    }
    int n = atoi((char*)countBuf);
    free(countBuf);
    int** matrix = CreateMatrix(n);
    if (matrix == NULL) {
        printf("Error in malloc");
        ASSERT_TRUE(matrix);
    }
    FillZero(matrix, n);
    ReadGraph(fstdin, matrix);
    DFS(fstdout, matrix, n);
    DestroyMatrix(matrix, n);
    fclose(fstdin);
    fclose(fstdout);
}