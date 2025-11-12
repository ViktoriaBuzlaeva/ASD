// Copyright 2025 Viktoria Buzlaeva

#include <gtest/gtest.h>
#include "../lib_algorithms/algorithms.h"

#define EPSILON 0.000001

TEST(TestAlgoritmsLib, can_check_empty_list_1_alg) {
	List<int> list;

	EXPECT_FALSE(is_looped_1(list));
}

TEST(TestAlgoritmsLib, can_check_one_elem_list_1_alg) {
	List<int> list;
	
	list.push_back(1);

	EXPECT_FALSE(is_looped_1(list));
}

TEST(TestAlgoritmsLib, can_check_not_looped_list_1_alg) {
	List<int> list;

	for (int i = 0; i < 5; i++) {
		list.push_back(i * 3 + 1);
	}

	EXPECT_FALSE(is_looped_1(list));
}

TEST(TestAlgoritmsLib, can_check_looped_list_1_alg) {
	List<int> list;
	
	for (int i = 0; i < 5; i++) {
		list.push_back(i * 3 + 1);
	}

	list.tail()->next = list.head()->next->next;

	EXPECT_TRUE(is_looped_1(list));

	list.tail()->next = nullptr;
}

TEST(TestAlgoritmsLib, can_check_empty_list_2_alg) {
	List<int> list;

	EXPECT_FALSE(is_looped_2(list));
}

TEST(TestAlgoritmsLib, can_check_one_elem_list_2_alg) {
	List<int> list;

	list.push_back(1);

	EXPECT_FALSE(is_looped_2(list));
}

TEST(TestAlgoritmsLib, can_check_not_looped_list_2_alg) {
	List<int> list;

	for (int i = 0; i < 5; i++) {
		list.push_back(i * 3 + 1);
	}

	EXPECT_FALSE(is_looped_2(list));
}

TEST(TestAlgoritmsLib, can_check_looped_list_2_alg) {
	List<int> list;

	for (int i = 0; i < 5; i++) {
		list.push_back(i * 3 + 1);
	}

	list.tail()->next = list.head()->next->next;

	EXPECT_TRUE(is_looped_2(list));

	list.tail()->next = nullptr;
}

TEST(TestAlgoritmsLib, can_return_nullptr_not_looped_list_3_alg) {
	List<int> list;

	for (int i = 0; i < 5; i++) {
		list.push_back(i * 3 + 1);
	}

	EXPECT_EQ(nullptr, find_loop(list));
}

TEST(TestAlgoritmsLib, can_find_loop_3_alg) {
	List<int> list;

	for (int i = 0; i < 5; i++) {
		list.push_back(i * 3 + 1);
	}

	list.tail()->next = list.head()->next->next;

	EXPECT_EQ(list.head()->next->next, find_loop(list));

	list.tail()->next = nullptr;
}
