// Copyright 2025 Viktoria Buzlaeva

#include <gtest/gtest.h>
#include "../lib_algorithms/algorithms.h"

#define EPSILON 0.000001

TEST(TestAlgorithmsLib, can_check_correct_brackets_1) {
	std::string str = "()";

	EXPECT_EQ(true, check_brackets(str));
}

TEST(TestAlgorithmsLib, can_check_uncorrect_brackets_1) {
	std::string str = "((";

	EXPECT_EQ(false, check_brackets(str));
}

TEST(TestAlgorithmsLib, can_check_correct_brackets_2) {
	std::string str = "({})[(){}]";

	EXPECT_EQ(true, check_brackets(str));
}

TEST(TestAlgorithmsLib, can_check_uncorrect_brackets_2) {
	std::string str = "({}})";

	EXPECT_EQ(false, check_brackets(str));
}

TEST(TestAlgorithmsLib, can_check_uncorrect_brackets_3) {
	std::string str = "((())))";

	EXPECT_EQ(false, check_brackets(str));
}

TEST(TestAlgorithmsLib, can_check_correct_expression) {
	std::string expr = "3 * (15 + (x + y) * (2 * x - 7 * y^2))";

	ASSERT_NO_THROW(read_expression(expr));
}

TEST(TestAlgorithmsLib, can_check_uncorrect_expression_1) {
	std::string expr = "3 * (15 + (x y) * (2 * x - 7 * y^2))";

	ASSERT_ANY_THROW(read_expression(expr));
}

TEST(TestAlgorithmsLib, can_check_uncorrect_expression_2) {
	std::string expr = "3 * (15 + (x + y) * (2 * x - 7 * y^))";

	ASSERT_ANY_THROW(read_expression(expr));
}

TEST(TestAlgorithmsLib, can_check_uncorrect_expression_3) {
	std::string expr = "((x + y) * (x - y)";

	ASSERT_ANY_THROW(read_expression(expr));
}
