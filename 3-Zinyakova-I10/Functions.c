#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
//#include "Header.h"

typedef struct Tree {
	struct Tree* parent;
	int keys[3];
	struct Tree* first;
	struct Tree* second;
	struct Tree* third;
	struct Tree* fourth;
	int size;
} Tree;

Tree* CreateTree(int value);
Tree* CreateAndFillTree(int value, Tree* first, Tree* second, Tree* third, Tree* fourth, Tree* parent);
char FindKey(Tree* tree, int value);
void swap(int* x, int* y);
void sort2(int* x, int* y);
void sort3(int* x, int* y, int* z);
void SortKeys(Tree* tree);
void InsertNode(int value, Tree* tree);
void DeleteKeyFromNode(int value, Tree* treeNode);
void TransformToNode(int value, Tree* treeNode, Tree* first, Tree* second);
char IsLeaf(Tree* tree);
Tree* Insert(Tree* tree, int value);
Tree* DeleteNode(Tree* tree, int value);
Tree* FindMin(Tree* tree);
Tree* Split(Tree* tree);
Tree* Search(Tree* tree, int value);
Tree* Fix(Tree* leaf);
Tree* Merge(Tree* leaf);
Tree* Redistribute(Tree* leaf);
void PrintTree(Tree* tree);
void DestroyTree(Tree* tree);
int Solution(FILE* fpIn, FILE* fpOut);


int main(void) {
	Solution(stdin, stdout);
	return 0;
}

Tree* CreateTree(int value) {
	Tree* newTree = (Tree*)malloc(sizeof(Tree));
	if (!newTree) {
		return NULL;
	}
	newTree->first = NULL;
	newTree->second = NULL;
	newTree->third = NULL;
	newTree->fourth = NULL;
	newTree->parent = NULL;
	newTree->keys[0] = value;
	newTree->size = 1;
	return newTree;
}

Tree* CreateAndFillTree(int value, Tree* first, Tree* second, Tree* third, Tree* fourth, Tree* parent) {
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

char FindKey(Tree* tree, int value) {
	for (int i = 0; i < tree->size; ++i) {
		if (tree->keys[i] == value) {
			return 1;
		}
	}
	return 0;
}

void swap(int* x, int* y) {
	int r = (*x);
	(*x) = (*y);
	(*y) = r;
}

void sort2(int* x, int* y) {
	if (*x > *y) {
		swap(x, y);
	}
}

void sort3(int* x, int* y, int* z) {
	if (*x > *y) {
		swap(x, y);
	}

	if (*x > *z) {
		swap(x, z);
	}

	if (*y > *z) {
		swap(y, z);
	}
}

void SortKeys(Tree* tree) {
	if (tree->size == 1) {
		return;
	}
	if (tree->size == 2) {
		sort2(&(tree->keys[0]), &(tree->keys[1]));
	}
	if (tree->size == 3) {
		sort3(&(tree->keys[0]), &(tree->keys[1]), &(tree->keys[2]));
	}
}

void InsertNode(int value, Tree* tree) {
	if (!tree) {
		return;
	}
	tree->keys[tree->size] = value;
	tree->size++;
	SortKeys(tree);
}

void DeleteKeyFromNode(int value, Tree* treeNode) {
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

void TransformToNode(int value, Tree* treeNode, Tree* first, Tree* second) {
	treeNode->keys[0] = value;
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
	if ((tree->first == NULL) && (tree->second == NULL) && (tree->third == NULL)) {
		return 1;
	}
	else {
		return 0;
	}
}


Tree* Merge(Tree* leaf) {
	if (leaf) {
		return NULL;
	}

	Tree* parent = leaf->parent;

	if (parent->first == leaf) {
		InsertNode(parent->keys[0], parent->second);
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

		DeleteKeyFromNode(parent->keys[0], parent);
		free(parent->first);
		parent->first = NULL;
	}
	else if (parent->second == leaf) {
		InsertNode(parent->keys[0], parent->first);

		if (leaf->first) {
			parent->first->third = leaf->first;
		}
		else if (leaf->second) {
			parent->first->third = leaf->second;
		}

		if (parent->first->third) {
			parent->first->third->parent = parent->first;
		}

		DeleteKeyFromNode(parent->keys[0], parent);
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
			InsertNode(parent->keys[0], parent->first);
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

			DeleteKeyFromNode(parent->keys[0], parent);
		}
		else if (second == leaf) {
			InsertNode(parent->keys[0], first);
			DeleteKeyFromNode(parent->keys[0], parent);
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
			InsertNode(parent->keys[1], second);
			parent->third = NULL;
			DeleteKeyFromNode(parent->keys[1], parent);
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

			InsertNode(parent->keys[1], leaf);
			if (second->size == 2) {
				parent->keys[1] = second->keys[1];
				DeleteKeyFromNode(second->keys[1], second);
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
				DeleteKeyFromNode(first->keys[1], first);
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

				InsertNode(parent->keys[1], second);
				parent->keys[1] = third->keys[0];
				DeleteKeyFromNode(third->keys[0], third);
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
				InsertNode(parent->keys[0], second);
				parent->keys[0] = first->keys[1];
				DeleteKeyFromNode(first->keys[1], first);
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
			InsertNode(parent->keys[0], first);
			if (second->size == 2) {
				parent->keys[0] = second->keys[0];
				DeleteKeyFromNode(second->keys[0], second);
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
				DeleteKeyFromNode(third->keys[0], third);
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
		InsertNode(parent->keys[0], leaf);

		if (first == leaf && second->size == 2) {
			parent->keys[0] = second->keys[0];
			DeleteKeyFromNode(second->keys[0], second);

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
			DeleteKeyFromNode(first->keys[1], first);

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

Tree* Insert(Tree* tree, int value) {
	if (!tree) {
		return CreateTree(value);
	}
	if (Search(tree, value)) {
		tree = Split(tree);
		return tree;
	}
	if (IsLeaf(tree)) {
		InsertNode(value, tree);
	}
	else if (value <= tree->keys[0]) {
		Insert(tree->first, value);
	}
	else if ((tree->size == 1) || ((tree->size == 2) && value <= tree->keys[1])) {
		Insert(tree->second, value);
	}
	else {
		Insert(tree->third, value);
	}
	tree = Split(tree);
	return tree;
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

Tree* Fix(Tree* leaf) {
	if (leaf) {
		return NULL;
	}

	if (leaf->size == 0 && leaf->parent == NULL) {
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



Tree* Split(Tree* tree) {
	if (!tree) {
		return NULL;
	}
	if (tree->size < 3) {
		return tree;
	}
	Tree* x = CreateAndFillTree(tree->keys[0], tree->first, tree->second, NULL, NULL, tree->parent);
	Tree* y = CreateAndFillTree(tree->keys[2], tree->third, tree->fourth, NULL, NULL, tree->parent);
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
	if (tree->parent) {
		InsertNode(tree->keys[1], tree->parent);
		if (tree->parent->first == tree) {
			tree->parent->first = NULL;
		}
		else if (tree->parent->second == tree) {
			tree->parent->second = NULL;
		}
		else if (tree->parent->third == tree) {
			tree->parent->third = NULL;
		}

		if (!tree->parent->first) {
			tree->parent->fourth = tree->parent->third;
			tree->parent->third = tree->parent->second;
			tree->parent->second = y;
			tree->parent->first = x;
		}
		else if (!tree->parent->second) {
			tree->parent->fourth = tree->parent->third;
			tree->parent->third = y;
			tree->parent->second = x;
		}
		else {
			tree->parent->fourth = y;
			tree->parent->third = x;
		}

		Tree* tmp = tree->parent;
		free(tree);
		return tmp;
	}
	else {
		x->parent = tree;
		y->parent = tree;
		TransformToNode(tree->keys[1], tree, x, y);
		return tree;
	}
}

Tree* Search(Tree* tree, int value) {;
	if (!tree) {
		return NULL;
	}
	if (FindKey(tree, value)) {
		return tree;
	}
	else if (value < tree->keys[0]) {
		tree = tree->first;
		tree = Search(tree, value);
	}
	else if ((tree->size == 2) && (value < tree->keys[1]) || (tree->size == 1)) {
		tree = tree->second;
		tree = Search(tree, value);
	}
	else if (tree->size == 2) {
		tree = tree->third;
		tree = Search(tree, value);
	}
	return tree;
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
		swap(z, &min->keys[0]);
		item = min;
	}

	DeleteKeyFromNode(value, item);
	return Fix(item);
}

//
//void PrintTree(Tree* t, int n) {
//	int i;
//	if (t != NULL) {
//		PrintTree(t->third, n + 2);
//		for (i = 0; i < n; i++) {
//			printf(" ");
//		}
//		if (t->size == 2) {
//			printf("%d", t->keys[1]);
//		}
//		printf( "\n");
//		PrintTree(t->second, n + 2); 
//		for (int i = 0; i < n; i++) {
//			printf(" ");
//		}
//			printf("%d", t->keys[0]);
//		
//		printf("\n");
//		PrintTree(t->first, n + 2); //
//	}
//}

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
	if (tree == NULL) {
		return;
	}

	DestroyTree(tree->first);
	DestroyTree(tree->second);
	DestroyTree(tree->second);
	free(tree);
}

int Solution(FILE* fpIn, FILE* fpOut) {
	char command;
	Tree* t = NULL;
	int key = 0;
	while (scanf("%c", &command) >= 1) {
		if (command != 'p' && command != 'q') {
			scanf("%i", &key);
		}

		switch (command) {
		case 'a':
			t = Insert(t, key);
			break;
		case 'r':
			t = DeleteNode(t, key);
			break;
		case 'f':
			if (Search(t, key)) {
				puts("yes");
			}
			else {
				puts("no");
			}

			break;
		default:
			DestroyTree(t);
			return 0;
		}
	}
	DestroyTree(t);
	return 0;

}