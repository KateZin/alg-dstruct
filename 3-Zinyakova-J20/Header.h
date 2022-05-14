#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF_SIZE 16
#define TABLE_SIZE 99999

typedef struct Node {
    char* data;
    struct Node* next;
} Node;

int AddNode(Node** table, char* key);
int FindNode(Node** table, const char* key);
unsigned int Hash(const char* s);
int DeleteNode(Node** table, char* key);
void DeleteChain(Node** first);
int DeleteTable(Node** table);
int Solution();