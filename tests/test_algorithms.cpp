// Copyright 2025 Viktoria Buzlaeva

#include <gtest/gtest.h>
#include "../lib_algorithms/algorithms.h"

#define EPSILON 0.000001

TEST(TestAlgorithmsLib, can_check_correct_breckets_1) {
	std::string str = "()";

	EXPECT_EQ(true, check_breckets(str));
}

TEST(TestAlgorithmsLib, can_check_uncorrect_breckets_1) {
	std::string str = "((";

	EXPECT_EQ(false, check_breckets(str));
}

TEST(TestAlgorithmsLib, can_check_correct_breckets_2) {
	std::string str = "({})[(){}]";

	EXPECT_EQ(true, check_breckets(str));
}

TEST(TestAlgorithmsLib, can_check_uncorrect_breckets_2) {
	std::string str = "({}})";

	EXPECT_EQ(false, check_breckets(str));
}

TEST(TestAlgorithmsLib, can_check_uncorrect_breckets_3) {
	std::string str = "((())))";

	EXPECT_EQ(false, check_breckets(str));
}
