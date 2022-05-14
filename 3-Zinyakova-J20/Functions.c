#define _CRT_SECURE_NO_WARNINGS
#include"Header.h"

unsigned int Hash(const char* s) {
    unsigned int h = 0, g;
    while (*s) {
        h = (h << 4) + *s++;
        g = h & 0xf0000000L;
        if (g){
            h ^= g >> 24;
        }
        h &= ~g;
    }
    return h % TABLE_SIZE;
}

int FindNode(Node** table, const char* key) {
    unsigned index = Hash(key);
    const Node* it = table[index];
    while (it != NULL && strcmp(it->data, key) != 0){
        it = it->next;
    }
    if (it != NULL) {
        return 1;
    }
    else {
        return 0;
    }
}

int AddNode(Node** table, char* key) {
    if (!FindNode(table, key)){
        unsigned int index = Hash(key);
        Node* newNode = (Node*)malloc(sizeof * newNode);
        if (newNode == NULL){
            return 0;
        }
        newNode->data = (char*)malloc((strlen(key) + 1) * sizeof(char));
        if (newNode->data == NULL){
            return 0;
        }
        strcpy(newNode->data, key);
        newNode->next = table[index];
        table[index] = newNode;
        return 1;
    }
    return 0;
}

int DeleteNode(Node** table, char* key) {
    if (FindNode(table, key)) {
        unsigned int index = Hash(key);
        Node* it = table[index];
        Node* prev = NULL;
        while (strcmp(it->data, key) != 0){
            prev = it;
            it = it->next;
        }
        if (prev){
            prev->next = it->next;
        }
        else{
            table[index] = it->next;
        }
    }
    return 0;
}

void DeleteChain(Node** first) {
    if (!(*first)){
        return;
    }
    Node* prev = NULL;
    while ((*first)->next){
        prev = (*first);
        (*first) = (*first)->next;
        free(prev->data);
        free(prev);
    }
    free((*first)->data);
    free(*first);
}

int DeleteTable(Node** table) {
    Node* it = NULL;
    for (int i = 0; i < TABLE_SIZE; i++){
        DeleteChain(&table[i]);
    }
    free(*table);
    table = NULL;
    return 0;
}

int Solution() {
    char command;
    Node* table[TABLE_SIZE] = { NULL };
    char buf[BUF_SIZE] = { 0 };
    char value[10000] = { 0 };
    while (fgets(buf, BUF_SIZE, stdin)){
        sscanf(buf, "%c %s", &command, &value);
        switch (command){
        case 'a':
            AddNode(table, value);
            break;
        case 'r':
            DeleteNode(table, value);
            break;
        case 'f':
            if (FindNode(table, value))
            {
                printf("%s", "yes\n");
            }
            else
            {
                printf("%s", "no\n");
            }
            break;
        default:
            DeleteTable(table);
            return 1;
        }
    }
    DeleteTable(table);
    return 0;
}