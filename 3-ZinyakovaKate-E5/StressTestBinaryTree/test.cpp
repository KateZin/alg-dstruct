#include "pch.h"
#include "Header.h"

TEST(FunctionalTest, OnlyRoot) {
	Tree* tree = CreateTree();
	if (tree == NULL) {
		ASSERT_TRUE(tree);
	}
	tree->value = 12;
	FillWidth(tree);
	EXPECT_EQ(tree->width, 2);
	DestroyTree(tree);
}

TEST(FunctionalTest, TreeWithZero) {
	Tree* tree = CreateTree();
	if (tree == NULL) {
		ASSERT_TRUE(tree);
	}
	tree->value = 0;
	FillWidth(tree);
	EXPECT_EQ(tree->width, 1);
	DestroyTree(tree);
}

TEST(FunctionalTest, OneSideTree) {
	Tree* tree1 = CreateTree();
	if (tree1 == NULL) {
		ASSERT_TRUE(tree1);
	}
	Tree* tree2 = CreateTree();
	if (tree2 == NULL) {
		free(tree1);
		ASSERT_TRUE(tree2);
	}
	Tree* tree3 = CreateTree();
	if (tree3 == NULL) {
		free(tree1);
		free(tree2);
		ASSERT_TRUE(tree3);
	}
	tree1->value = 3;
	tree2->value = 5;
	tree3->value = 8;
	tree1->right = tree2;
	tree2->right = tree3;
	FillWidth(tree1);
	EXPECT_EQ(tree1->width, 3);
	EXPECT_EQ(tree2->width, 2);
	EXPECT_EQ(tree3->width, 1);
	DestroyTree(tree1);
}

TEST(FunctionalTest, CheckResult) {
	Tree* tree1 = CreateTree();
	if (tree1 == NULL) {
		ASSERT_TRUE(tree1);
	}
	Tree* tree2 = CreateTree();
	if (tree2 == NULL) {
		free(tree1);
		ASSERT_TRUE(tree2);
	}
	Tree* tree3 = CreateTree();
	if (tree3 == NULL) {
		free(tree1);
		free(tree2);
		ASSERT_TRUE(tree3);
	}
	Tree* tree4 = CreateTree();
	if (tree4 == NULL) {
		free(tree1);
		free(tree2);
		free(tree4);
		ASSERT_TRUE(tree4);
	}
	tree1->value = 12;
	tree2->value = 5;
	tree3->value = 20;
	tree4->value = 16;
	tree1->left = tree2;
	tree1->right = tree3;
	tree3->left = tree4;
	FillWidth(tree1);
	EXPECT_EQ(tree1->width, 7);
	EXPECT_EQ(tree2->width, 1);
	EXPECT_EQ(tree3->width, 4);
	EXPECT_EQ(tree4->width, 2);
	DestroyTree(tree1);
}

TEST(FunctionalTest, NegativeElements) {
	Tree* tree1 = CreateTree();
	if (tree1 == NULL) {
		ASSERT_TRUE(tree1);
	}
	Tree* tree2 = CreateTree();
	if (tree2 == NULL) {
		free(tree1);
		ASSERT_TRUE(tree2);
	}
	Tree* tree3 = CreateTree();
	if (tree3 == NULL) {
		free(tree1);
		free(tree2);
		ASSERT_TRUE(tree3);
	}
	tree1->value = -12;
	tree2->value = -5;
	tree3->value = -20;
	tree1->left = tree3;
	tree1->right = tree2;
	FillWidth(tree1);
	EXPECT_EQ(tree1->width, 8);
	EXPECT_EQ(tree2->width, 2);
	EXPECT_EQ(tree3->width, 3);
	DestroyTree(tree1);
}

TEST(FunctionalTest, NegativeAndPositiveElements) {
	Tree* tree1 = CreateTree();
	if (tree1 == NULL) {
		ASSERT_TRUE(tree1);
	}
	Tree* tree2 = CreateTree();
	if (tree2 == NULL) {
		free(tree1);
		ASSERT_TRUE(tree2);
	}
	Tree* tree3 = CreateTree();
	if (tree3 == NULL) {
		free(tree1);
		free(tree2);
		ASSERT_TRUE(tree3);
	}
	Tree* tree4 = CreateTree();
	if (tree4 == NULL) {
		free(tree1);
		free(tree2);
		free(tree4);
		ASSERT_TRUE(tree4);
	}
	tree1->value = -5;
	tree2->value = -6;
	tree3->value = 2;
	tree4->value = 6;
	tree1->left = tree2;
	tree1->right = tree3;
	tree3->right = tree4;
	FillWidth(tree1);
	EXPECT_EQ(tree1->width, 6);
	EXPECT_EQ(tree2->width, 2);
	EXPECT_EQ(tree3->width, 2);
	EXPECT_EQ(tree4->width, 1);
	DestroyTree(tree1);
}

TEST(FunctionalTest, CheckPrint) {
	Tree* tree1 = CreateTree();
	if (tree1 == NULL) {
		ASSERT_TRUE(tree1);
	}
	Tree* tree2 = CreateTree();
	if (tree2 == NULL) {
		free(tree1);
		ASSERT_TRUE(tree2);
	}
	Tree* tree3 = CreateTree();
	if (tree3 == NULL) {
		free(tree1);
		free(tree2);
		ASSERT_TRUE(tree3);
	}
	Tree* tree4 = CreateTree();
	if (tree4 == NULL) {
		free(tree1);
		free(tree2);
		free(tree4);
		ASSERT_TRUE(tree4);
	}
	tree1->value = 12;
	tree2->value = 5;
	tree3->value = 20;
	tree1->left = tree2;
	tree1->right = tree3;
	FillWidth(tree1);
	EXPECT_EQ(ComparePrintResults(tree1, "correct.txt", "myResult.txt"), 1);
	DestroyTree(tree1);
}