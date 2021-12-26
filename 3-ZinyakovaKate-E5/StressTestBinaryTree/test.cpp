#include "pch.h"
#include "Header.h"

int ComparePrintResults(Tree* tree, char* resFile, char* myFile) {
	int expect, res;
	FILE* p1 = fopen(myFile, "w");
	if (p1 == NULL) {
		printf("error in openning file");
		return -1;
	}
	PrintTree(tree, 1, p1);
	fclose(p1);
	FILE* p2 = fopen(resFile, "r");
	if (p2 == NULL) {
		printf("error in openning file");
		return -1;
	}
	p1 = fopen(myFile, "r");
	if (p1 == NULL) {
		printf("error in openning file");
		fclose(p2);
		return -1;
	}
	while (fscanf(p2, "%d", &expect) != EOF && fscanf(p1, "%d", &res) != EOF) {
		if (expect != res) {
			fclose(p1);
			fclose(p2);
			return 0;
		}
	}
	fclose(p1);
	fclose(p2);
	return 1;
}

TEST(FunctionalTest, OnlyRoot) {
	Tree* tree = CreateTree();
	if (tree == NULL) {
		ASSERT_TRUE(tree);
	}
	tree->value = 12;
	FillWidth(tree);
	EXPECT_EQ(tree->width, 2);
	EXPECT_EQ(ComparePrintResults(tree, "TestData/OnlyRoot.txt", "TestData/ResultOnlyRoot.txt"), 1);
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
	EXPECT_EQ(ComparePrintResults(tree, "TestData/TreeWithZero.txt", "TestData/ResultTreeWithZero.txt"), 1);
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
	EXPECT_EQ(ComparePrintResults(tree1, "TestData/OneSideTree.txt", "TestData/ResultOneSideTree.txt"), 1);
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
	EXPECT_EQ(ComparePrintResults(tree1, "TestData/CheckResult.txt", "TestData/ResultCheckResult.txt"), 1);
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
	EXPECT_EQ(ComparePrintResults(tree1, "TestData/NegativeElements.txt", "TestData/ResultNegativeElements.txt"), 1);
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
	EXPECT_EQ(ComparePrintResults(tree1, "TestData/NegativeAndPositiveElements.txt", "TestData/ResultNegativeAndPositiveElements.txt"), 1);
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
	EXPECT_EQ(ComparePrintResults(tree1, "TestData/Correct.txt", "TestData/MyResult.txt"), 1);
	DestroyTree(tree1);
}