#include "pch.h"
#include "Header.h"

TEST(FunctionalTest, OnlyRoot) {
	Tree* tree = nullptr;
	tree = Insert(tree, 111111111);
	FillWidth(&tree);
	EXPECT_EQ(tree->width, 11);
	PrintTree(tree, 1);
	DestroyTree(tree);
}

TEST(FunctionalTest, TreeWithZero) {
	Tree* tree = nullptr;
	tree = Insert(tree, 0);
	FillWidth(&tree);
	EXPECT_EQ(tree->width, 2);
	DestroyTree(tree);
}

TEST(FunctionalTest, CheckResult) {
	Tree* tree = nullptr;
	tree = Insert(tree, 51);
	tree = Insert(tree, 20);
	tree = Insert(tree, 1);
	tree = Insert(tree, 43);
	tree = Insert(tree, 66);
	tree = Insert(tree, 60);
	FillWidth(&tree);
	EXPECT_EQ(tree->left->left->width, 2);
	EXPECT_EQ(tree->left->right->width, 3);
	EXPECT_EQ(tree->left->width, 8);
	EXPECT_EQ(tree->right->left->width, 3);
	EXPECT_EQ(tree->right->width, 6);
	EXPECT_EQ(tree->width, 18);
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
		EXPECT_EQ(tree->left->width, 4);
		EXPECT_EQ((tree->right)->right->width, 3);
		EXPECT_EQ(tree->right->left->width, 4);
		EXPECT_EQ(tree->right->width, 12);
		EXPECT_EQ(tree->width, 21);
		PrintTree(tree, 1);
		DestroyTree(tree);
}

TEST(FunctionalTest, ElementsWithOverDigitInTheRoot) {
	Tree* tree = nullptr;
	tree = Insert(tree, 99);
	tree = Insert(tree, 11);
	tree = Insert(tree, 413);
	FillWidth(&tree);
	EXPECT_EQ(tree->right->width, 4);
	EXPECT_EQ(tree->left->width, 3);
	EXPECT_EQ(tree->width, 11);
	PrintTree(tree, 1);
	DestroyTree(tree);
}