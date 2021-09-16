#include "pch.h"
#include "main.c"

TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}

TEST(TestCaseName, Add1To2) {
	EXPECT_EQ(sum(1,2), 3);
}