#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "Header.h"
#pragma warning(disable : 4996)

Tree* CreateNode(int value) {
    Tree* nodeToAdd = (Tree*)malloc(sizeof(Tree));
    if (!nodeToAdd) {
        return NULL; 
    }
    nodeToAdd->first = NULL;
    nodeToAdd->second = NULL;
    nodeToAdd->third = NULL;
    nodeToAdd->fourth = NULL;
    nodeToAdd->parent = NULL;
    nodeToAdd->keys[0] = value;
    nodeToAdd->size = 1;
    return nodeToAdd;
}

Tree* CreateAndFillNode(int value, Tree* first, Tree* second, Tree* third, Tree* fourth, Tree* parent) {
    Tree* nodeToAdd = (Tree*)malloc(sizeof(Tree));
    if (!nodeToAdd) {
            return NULL;
    }
    nodeToAdd->first = first;
    nodeToAdd->second = second;
    nodeToAdd->third = third;
    nodeToAdd->fourth = fourth;
    nodeToAdd->parent = parent;
    nodeToAdd->keys[0] = value;
    nodeToAdd->size = 1;
    return nodeToAdd;
}

char Find(int value, int* keys, int size) {
    for (int i = 0; i < size; ++i) {
        if (keys[i] == value) {
            return 1;
        }
    }
    return 0;
}

void Swap(int* x, int* y) {
    int r = (*x);
    (*x) = (*y);
    (*y) = r;
}

void Sort2(int* x, int* y) {
    if (*x > *y) {
        Swap(x, y);
    }
}

void Sort3(int* x, int* y, int* z) {
    if (*x > *y) {
        Swap(x, y);
    }
    if (*x > *z) {
        Swap(x, z);
    }
    if (*y > *z) {
        Swap(y, z);
    }
}

void SortKeys(int size, int* keys) {
    if (size == 1) {
        return;
    }
    if (size == 2) {
        Sort2(&keys[0], &keys[1]);
    }
    if (size == 3) {
        Sort3(&keys[0], &keys[1], &keys[2]);
    }
}

void InsertToNode(int value, Tree* treeNode) {
    if (!treeNode) {
        return;
    }
    treeNode->keys[treeNode->size] = value;
    treeNode->size++;
    SortKeys(treeNode->size, treeNode->keys);
}

void DeleteKey(int value, Tree* treeNode) {
    if (!treeNode) {
        return;
    }
    if (treeNode->size >= 1 && treeNode->keys[0] == value) {
        treeNode->keys[0] = treeNode->keys[1];
        treeNode->keys[1] = treeNode->keys[2];
        treeNode->size--;
    }
    else if (treeNode->size == 2 && treeNode->keys[1] == value) {
        treeNode->keys[1] = treeNode->keys[2];
        treeNode->size--;
    }
}

void TransformNode(int value, int* keys, Tree* treeNode, Tree* first, Tree* second) {
    keys[0] = value;
    treeNode->first = first;
    treeNode->second = second;
    treeNode->third = NULL;
    treeNode->fourth = NULL;
    treeNode->parent = NULL;
    treeNode->size = 1;
}

char IsLeaf(Tree* tree) {
    if (!tree) {
        return 0;
    }
    if (!tree->first && !tree->second && !tree->third) {
        return 1;
    }
    return 0;
}

Tree* InsertNode(Tree* tree, int value) {
    if (!tree) {
        return CreateNode(value);
    }
    if (Search(tree, value)) {
        return Split(tree);
    }
    if (IsLeaf(tree)) {
        InsertToNode(value, tree);
    }
    else if (value <= tree->keys[0]) {
        InsertNode(tree->first, value);
    }
    else if ((tree->size == 1) || ((tree->size == 2) && value <= tree->keys[1])) {
        InsertNode(tree->second, value);
    }
    else {
        InsertNode(tree->third, value);
    }
    return Split(tree);
}

Tree* FindMin(Tree* tree) {
    if (!tree) {
        return tree;
    }
    if (!tree->first) {
        return tree;
    }
    else {
        return FindMin(tree->first);
    }
}

Tree* DeleteNode(Tree* tree, int value) {
    if (!tree) {
        return NULL;
    }
    Tree* item = Search(tree, value);
    if (!item) {
        return tree;
    }
    Tree* min = NULL;
    if (item->keys[0] == value) {
        min = FindMin(item->second);
    }
    else {
        min = FindMin(item->third);
    }
    if (min) {
        int* z = (value == item->keys[0] ? &(item->keys[0]) : &(item->keys[1]));
        Swap(z, &min->keys[0]);
        item = min;
    }
    DeleteKey(value, item);
    return Fix(item);
}

Tree* Split(Tree* item) {
    if (!item) {
        return NULL;
    }
    if (item->size < 3) {
        return item;
    }
    Tree* x = CreateAndFillNode(item->keys[0], item->first, item->second, NULL, NULL, item->parent);
    Tree* y = CreateAndFillNode(item->keys[2], item->third, item->fourth, NULL, NULL, item->parent);
    if (x->first) {
        x->first->parent = x;
    }
    if (x->second) {
        x->second->parent = x;
    }
    if (y->first) {
        y->first->parent = y;
    }
    if (y->second) {
        y->second->parent = y;
    }
    if (item->parent) {
        InsertToNode(item->keys[1], item->parent);
        if (item->parent->first == item) {
            item->parent->first = NULL;
        }
        else if (item->parent->second == item) {
            item->parent->second = NULL;
        }
        else if (item->parent->third == item) {
            item->parent->third = NULL;
        }
        if (!item->parent->first) {
            item->parent->fourth = item->parent->third;
            item->parent->third = item->parent->second;
            item->parent->second = y;
            item->parent->first = x;
        }
        else if (!item->parent->second) {
            item->parent->fourth = item->parent->third;
            item->parent->third = y;
            item->parent->second = x;
        }
        else {
            item->parent->fourth = y;
            item->parent->third = x;
        }
        Tree* tmp = item->parent;
        free(item);
        return tmp;
    }
    else {
        x->parent = item;
        y->parent = item;
        TransformNode(item->keys[1], item->keys, item, x, y);
        return item;
    }
}

Tree* Search(Tree* tree, int value) {
    if (!tree) {
        return NULL;
    }
    if (Find(value, tree->keys, tree->size)) {
        return tree;
    }
    else if (value < tree->keys[0]) {
        return Search(tree->first, value);
    }
    else if ((tree->size == 2) && (value < tree->keys[1]) || (tree->size == 1)) {
        return Search(tree->second, value);
    }
    else if (tree->size == 2) {
        return Search(tree->third, value);
    }
}

Tree* Fix(Tree* leaf) {
    if (!leaf) {
        return NULL;
    }
    if (leaf->size == 0 && !leaf->parent) {
        free(leaf);
        return NULL;
    }
    if (leaf->size) {
        if (leaf->parent) {
            return Fix(leaf->parent);
        }
        else {
            return leaf;
        }
    }

    Tree* parent = leaf->parent;
    if (parent->first->size == 2 || parent->second->size == 2 || parent->size == 2) {
        leaf = Redistribute(leaf);
    }
    else if (parent->size == 2 && parent->third->size == 2) {
        leaf = Redistribute(leaf);
    }
    else {
        leaf = Merge(leaf);
    }
    return Fix(leaf);
}

Tree* Merge(Tree* leaf) {
    if (!leaf) {
        return NULL;
    }
    Tree* parent = leaf->parent;
    if (parent->first == leaf) {
        InsertToNode(parent->keys[0], parent->second);
        parent->second->third = parent->second->second;
        parent->second->second = parent->second->first;
        if (leaf->first) {
            parent->second->first = leaf->first;
        }
        else if (leaf->second) {
            parent->second->first = leaf->second;
        }
        if (parent->second->first) {
            parent->second->first->parent = parent->second;
        }
        DeleteKey(parent->keys[0], parent);
        free(parent->first);
        parent->first = NULL;
    }
    else if (parent->second == leaf) {
        InsertToNode(parent->keys[0], parent->first);
        if (leaf->first) {
            parent->first->third = leaf->first;
        }
        else if (leaf->second) {
            parent->first->third = leaf->second;
        }
        if (parent->first->third) {
            parent->first->third->parent = parent->first;
        }
        DeleteKey(parent->keys[0], parent);
        free(parent->second);
        parent->second = NULL;
    }
    if (!parent->parent) {
        Tree* tmp = NULL;
        if (parent->first) {
            tmp = parent->first;
        }
        else {
            tmp = parent->second;
        }
        tmp->parent = NULL;
        free(parent);
        return tmp;
    }
    return parent;
}

Tree* Redistribute(Tree* leaf) {
    if (!leaf) {
        return NULL;
    }
    Tree* parent = leaf->parent;
    Tree* first = parent->first;
    Tree* second = parent->second;
    Tree* third = parent->third;

    if ((parent->size == 2) && (first->size < 2) && (second->size < 2) && (third->size < 2)) {
        if (first == leaf) {
            parent->first = parent->second;
            parent->second = parent->third;
            parent->third = NULL;
            InsertToNode(parent->keys[0], parent->first);
            parent->first->third = parent->first->second;
            parent->first->second = parent->first->first;

            if (leaf->first) {
                parent->first->first = leaf->first;
            }
            else if (leaf->second) {
                parent->first->first = leaf->second;
            }
            if (parent->first->first) {
                parent->first->first->parent = parent->first;
            }
            DeleteKey(parent->keys[0], parent);
        }
        else if (second == leaf) {
            InsertToNode(parent->keys[0], first);
            DeleteKey(parent->keys[0], parent);
            if (leaf->first) {
                first->third = leaf->first;
            }
            else if (leaf->second) {
                first->third = leaf->second;
            }
            if (first->third) {
                first->third->parent = first;
            }
            parent->second = parent->third;
            parent->third = NULL;
            free(second);
        }
        else if (third == leaf) {
            InsertToNode(parent->keys[1], second);
            parent->third = NULL;
            DeleteKey(parent->keys[1], parent);
            if (leaf->first) {
                second->third = leaf->first;
            }
            else if (leaf->second) {
                second->third = leaf->second;
            }

            if (second->third) {
                second->third->parent = second;
            }
            free(third);
        }
    }
    else if ((parent->size == 2) && ((first->size == 2) || (second->size == 2) || (third->size == 2))) {
        if (third == leaf) {
            if (leaf->first) {
                leaf->second = leaf->first;
                leaf->first = NULL;
            }
            InsertToNode(parent->keys[1], leaf);
            if (second->size == 2) {
                parent->keys[1] = second->keys[1];
                DeleteKey(second->keys[1], second);
                leaf->first = second->third;
                second->third = NULL;

                if (leaf->first) {
                    leaf->first->parent = leaf;
                }

            }
            else if (first->size == 2) {
                parent->keys[1] = second->keys[0];
                leaf->first = second->second;
                second->second = second->first;
                if (leaf->first) {
                    leaf->first->parent = leaf;
                }

                second->keys[0] = parent->keys[0];
                parent->keys[0] = first->keys[1];
                DeleteKey(first->keys[1], first);
                second->first = first->third;
                if (second->first) {
                    second->first->parent = second;
                }
                first->third = NULL;
            }
        }
        else if (second == leaf) {
            if (third->size == 2) {
                if (!leaf->first) {
                    leaf->first = leaf->second;
                    leaf->second = NULL;
                }
                InsertToNode(parent->keys[1], second);
                parent->keys[1] = third->keys[0];
                DeleteKey(third->keys[0], third);
                second->second = third->first;
                if (second->second) {
                    second->second->parent = second;
                }
                third->first = third->second;
                third->second = third->third;
                third->third = NULL;
            }
            else if (first->size == 2) {
                if (!leaf->second) {
                    leaf->second = leaf->first;
                    leaf->first = NULL;
                }
                InsertToNode(parent->keys[0], second);
                parent->keys[0] = first->keys[1];
                DeleteKey(first->keys[1], first);
                second->first = first->third;
                if (second->first) {
                    second->first->parent = second;
                }
                first->third = NULL;
            }
        }
        else if (first == leaf) {
            if (!leaf->first) {
                leaf->first = leaf->second;
                leaf->second = NULL;
            }
            InsertToNode(parent->keys[0], first);
            if (second->size == 2) {
                parent->keys[0] = second->keys[0];
                DeleteKey(second->keys[0], second);
                first->second = second->first;
                if (first->second) {
                    first->second->parent = first;
                }
                second->first = second->second;
                second->second = second->third;
                second->third = NULL;
            }
            else if (third->size == 2) {
                parent->keys[0] = second->keys[0];
                second->keys[0] = parent->keys[1];
                parent->keys[1] = third->keys[0];
                DeleteKey(third->keys[0], third);
                first->second = second->first;
                if (first->second) {
                    first->second->parent = first;
                }
                second->first = second->second;
                second->second = third->first;
                if (second->second) {
                    second->second->parent = second;
                }
                third->first = third->second;
                third->second = third->third;
                third->third = NULL;
            }
        }
    }
    else if (parent->size == 1) {
        InsertToNode(parent->keys[0], leaf);

        if (first == leaf && second->size == 2) {
            parent->keys[0] = second->keys[0];
            DeleteKey(second->keys[0], second);

            if (!leaf->first) {
                leaf->first = leaf->second;
            }
            leaf->second = second->first;
            second->first = second->second;
            second->second = second->third;
            second->third = NULL;
            if (leaf->second) {
                leaf->second->parent = leaf;
            }
        }
        else if (second == leaf && first->size == 2) {
            parent->keys[0] = first->keys[1];
            DeleteKey(first->keys[1], first);

            if (!leaf->second) {
                leaf->second = leaf->first;
            }
            leaf->first = first->third;
            first->third = NULL;

            if (leaf->first) {
                leaf->first->parent = leaf;
            }
        }
    }
    return parent;
}

void PrintTree(Tree* tree) {
    if (!tree) {
        return;
    }
    PrintTree(tree->first);
    for (int i = 0; i < tree->size; i++) {
        printf("%d ", tree->keys[i]);
    }
    PrintTree(tree->second);
    PrintTree(tree->third);
}

void DestroyTree(Tree* tree) {
    if (!tree) {
        return;
    }
    DestroyTree(tree->first);
    DestroyTree(tree->second);
    DestroyTree(tree->third);
    free(tree);
}

int Solution(FILE* fpIn, FILE* fpOut) {
    char buffer[BUFFER_SIZE] = { 0 };
    char x;
    int value;
    Tree* tree = NULL;
    while (fgets(buffer, BUFFER_SIZE, fpIn)) {
        sscanf(buffer, "%c %i", &x, &value);
        switch (x) {
        case 'a':
            tree = InsertNode(tree, value);
            break;
        case 'r':
            tree = DeleteNode(tree, value);
            break;
        case 'f':
            if (Search(tree, value))
                fprintf(fpOut, "yes\n");
            else
                fprintf(fpOut, "no\n");
            break;
        default:
            DestroyTree(tree);
            return 0;
        }
    }
    DestroyTree(tree);
    return 0;
}

int main(void) {
    Solution(stdin, stdout);
    return 0;
}