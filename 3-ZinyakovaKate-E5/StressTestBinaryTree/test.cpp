#include "pch.h"
#include "Header.h"

TEST(FunctionalTest, OnlyRoot) {
	Tree* tree = nullptr;
	tree = Insert(tree, 12);
	if (tree == NULL) {
		printf("problem with adding an element");
		ASSERT_TRUE(tree);
	}
	FillWidth(tree);
	EXPECT_EQ(tree->width, 2);
	PrintTree(tree, 1);
	DestroyTree(tree);
}

TEST(FunctionalTest, TreeWithZero) {
	Tree* tree = nullptr;
	tree = Insert(tree, 0);
	if (tree == NULL) {
		printf("problem with adding an element");
		ASSERT_TRUE(tree);
	}
	FillWidth(tree);
	EXPECT_EQ(tree->width, 1);
	PrintTree(tree, 1);
	DestroyTree(tree);
}

TEST(FunctionalTest, OneSideTree) {
	Tree* tree = nullptr;
	tree = Insert(tree, 3);
	if (tree == NULL) {
		printf("problem with adding an element");
		ASSERT_TRUE(tree);
	}
	tree = Insert(tree, 5);
	if (tree == NULL) {
		printf("problem with adding an element");
		ASSERT_TRUE(tree);
	}
	tree = Insert(tree, 8);
	if (tree == NULL) {
		printf("problem with adding an element");
		ASSERT_TRUE(tree);
	}
	FillWidth(tree);
	EXPECT_EQ(tree->width, 3);
	EXPECT_EQ(tree->right->width, 2);
	EXPECT_EQ(tree->right->right->width, 1);
	PrintTree(tree, 1);
	DestroyTree(tree);
}

TEST(FunctionalTest, CheckResult) {
	Tree* tree = nullptr;
	tree = Insert(tree, 12);
	if (tree == NULL) {
		printf("problem with adding an element");
		ASSERT_TRUE(tree);
	}
	tree = Insert(tree, 5);
	if (tree == NULL) {
		printf("problem with adding an element");
		ASSERT_TRUE(tree);
	}
	tree = Insert(tree, 20);
	if (tree == NULL) {
		printf("problem with adding an element");
		ASSERT_TRUE(tree);
	}
	tree = Insert(tree, 3);
	if (tree == NULL) {
		printf("problem with adding an element");
		ASSERT_TRUE(tree);
	}
	tree = Insert(tree, 6);
	if (tree == NULL) {
		printf("problem with adding an element");
		ASSERT_TRUE(tree);
	}
	tree = Insert(tree, 16);
	if (tree == NULL) {
		printf("problem with adding an element");
		ASSERT_TRUE(tree);
	}
	tree = Insert(tree, 22);
	if (tree == NULL) {
		printf("problem with adding an element");
		ASSERT_TRUE(tree);
	}
	tree = Insert(tree, 31);
	if (tree == NULL) {
		printf("problem with adding an element");
		ASSERT_TRUE(tree);
	}
	tree = Insert(tree, 30);
	if (tree == NULL) {
		printf("problem with adding an element");
		ASSERT_TRUE(tree);
	}
	FillWidth(tree);
	EXPECT_EQ(tree->left->left->width, 1);
	EXPECT_EQ(tree->left->right->width, 1);
	EXPECT_EQ(tree->left->width, 3);
	EXPECT_EQ(tree->right->width, 10);
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
	if (tree == NULL) {
		printf("problem with adding an element");
		ASSERT_TRUE(tree);
	}
	tree = Insert(tree, -10);
	if (tree == NULL) {
		printf("problem with adding an element");
		ASSERT_TRUE(tree);
	}
	tree = Insert(tree, -1);
	if (tree == NULL) {
		printf("problem with adding an element");
		ASSERT_TRUE(tree);
	}
	tree = Insert(tree, -11);
	if (tree == NULL) {
		printf("problem with adding an element");
		ASSERT_TRUE(tree);
	}
	tree = Insert(tree, -14);
	if (tree == NULL) {
		printf("problem with adding an element");
		ASSERT_TRUE(tree);
	}
	FillWidth(tree);
	EXPECT_EQ(tree->left->width, 3);
	EXPECT_EQ(tree->right->right->width, 2);
	EXPECT_EQ(tree->right->left->width, 3);
	EXPECT_EQ(tree->right->width, 8);
	EXPECT_EQ(tree->width, 14);
	PrintTree(tree, 1);
	DestroyTree(tree);
}

TEST(FunctionalTest, NegativeAndPositiveElements) {
	Tree* tree = nullptr;
	tree = Insert(tree, 12);
	if (tree == NULL) {
		printf("problem with adding an element");
		ASSERT_TRUE(tree);
	}
	tree = Insert(tree, 5);
	if (tree == NULL) {
		printf("problem with adding an element");
		ASSERT_TRUE(tree);
	}
	tree = Insert(tree, -10);
	if (tree == NULL) {
		printf("problem with adding an element");
		ASSERT_TRUE(tree);
	}
	tree = Insert(tree, 8);
	if (tree == NULL) {
		printf("problem with adding an element");
		ASSERT_TRUE(tree);
	}
	tree = Insert(tree, 14);
	if (tree == NULL) {
		printf("problem with adding an element");
		ASSERT_TRUE(tree);
	}
	FillWidth(tree);
	EXPECT_EQ(tree->left->width, 5);
	EXPECT_EQ(tree->right->width, 2);
	EXPECT_EQ(tree->left->right->width, 1);
	EXPECT_EQ(tree->left->left->width, 3);
	EXPECT_EQ(tree->width, 9);
	PrintTree(tree, 1);
	DestroyTree(tree);
}