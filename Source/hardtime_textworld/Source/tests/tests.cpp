#include "gtest/gtest.h"


namespace {
	TEST(SimpleTest, GreaterThan1) {
		EXPECT_GT(2, 1);
	}

	// Tests factorial of 0.
	TEST(SimpleTest, EqualTo1) {
		EXPECT_EQ(1, 0);
	}

}  // namespace
