#include "pch.h"
#include "Header.h"

TEST(FunctionalTest, OnlyRoot) {
	Tree* tree = nullptr;
	tree = Insert(tree, 12);
	FillWidth(&tree);
	EXPECT_EQ(tree->width, 2);
	PrintTree(tree, 1);
	DestroyTree(tree);
}

TEST(FunctionalTest, TreeWithZero) {
	Tree* tree = nullptr;
	tree = Insert(tree, 0);
	FillWidth(&tree);
	EXPECT_EQ(tree->width, 1);
	PrintTree(tree, 1);
	DestroyTree(tree);
}

TEST(FunctionalTest, OneSideTree) {
	Tree* tree = nullptr;
	tree = Insert(tree, 3);
	tree = Insert(tree, 5);
	tree = Insert(tree, 8);
	FillWidth(&tree);
	EXPECT_EQ(tree->width, 3);
	EXPECT_EQ(tree->right->width, 2);
	EXPECT_EQ(tree->right->right->width, 1);
	PrintTree(tree, 1);
	DestroyTree(tree);
}

TEST(FunctionalTest, CheckResult) {
	Tree* tree = nullptr;
	tree = Insert(tree, 12);
	tree = Insert(tree, 5);
	tree = Insert(tree, 20);
	tree = Insert(tree, 3);
	tree = Insert(tree, 6);
	tree = Insert(tree, 16);
	tree = Insert(tree, 22);
	tree = Insert(tree, 31);
	tree = Insert(tree, 30);
	FillWidth(&tree);
	EXPECT_EQ(tree->left->left->width, 1);
	EXPECT_EQ(tree->left->right->width, 1);
	EXPECT_EQ(tree->left->width, 3);
	EXPECT_EQ(tree->right->left->width, 2);
	EXPECT_EQ(tree->right->right->width, 6);
	EXPECT_EQ(tree->right->right->right->width, 4);
	EXPECT_EQ(tree->right->right->right->left->width, 2);
	EXPECT_EQ(tree->width, 15);
	PrintTree(tree, 1);
	DestroyTree(tree);
}

TEST(FunctionalTest, NegativeElements) {
	Tree* tree = nullptr;
	tree = Insert(tree, -12);
	tree = Insert(tree, -10);
	tree = Insert(tree, -1);
	tree = Insert(tree, -11);
	tree = Insert(tree, -14);
	FillWidth(&tree);
	EXPECT_EQ(tree->left->width, 3);
	EXPECT_EQ((tree->right)->right->width, 2);
	EXPECT_EQ(tree->right->left->width, 3);
	EXPECT_EQ(tree->right->width, 8);
	EXPECT_EQ(tree->width, 14);
	PrintTree(tree, 1);
	DestroyTree(tree);
}