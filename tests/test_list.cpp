// Copyright 2025 Viktoria Buzlaeva

#include <gtest/gtest.h>
#include "../lib_list/list.h"

#define EPSILON 0.000001

TEST(TestListLib, can_create) {
	ASSERT_NO_THROW(List<int> list);
}

TEST(TestListLib, can_create_copy) {
	List<int> list_1;

	ASSERT_NO_THROW(List<int> list_2(list_1));
}

TEST(TestListLib, throw_when_try_create_copy) {
	List<int>* list_1 = NULL;

	ASSERT_ANY_THROW(List<int> list_2(*list_1));
}

TEST(TestListLib, can_check_empty_correctly) {
	List<int> list;

	EXPECT_EQ(true, list.is_empty());
}

TEST(TestListLib, can_push_front_correctly) {
	List<int> list;

	list.push_front(1);
	list.push_front(2);
	list.push_front(3);

	EXPECT_EQ(1, list.tail()->value);
	EXPECT_EQ(3, list.head()->value);
}

TEST(TestListLib, can_push_back_correctly) {
	List<int> list;

	list.push_back(1);
	list.push_back(2);
	list.push_back(3);

	EXPECT_EQ(3, list.tail()->value);
	EXPECT_EQ(1, list.head()->value);
}

TEST(TestListLib, can_insert_by_pointer_correctly) {
	List<int> list;
	list.push_back(1);
	list.push_back(2);
	list.push_back(3);

	list.insert(list.head()->next, 444);
	list.insert(list.head(), 555);
	list.insert(list.tail(), 666);

	EXPECT_EQ(444, list.head()->next->next->next->value);
	EXPECT_EQ(555, list.head()->next->value);
	EXPECT_EQ(666, list.tail()->value);
}

TEST(TestListLib, throw_when_try_insert_by_pointer_empty) {
	List<int> list;

	ASSERT_ANY_THROW(list.insert(list.tail(), 555));
}

TEST(TestListLib, throw_when_try_insert_by_pointer_nullptr) {
	List<int> list;
	list.push_back(1);
	list.push_back(2);
	list.push_back(3);
	Node<int>* ptr = nullptr;

	ASSERT_ANY_THROW(list.insert(ptr, 555));
}

TEST(TestListLib, can_insert_by_pos_correctly) {
	List<int> list;
	list.push_back(1);
	list.push_back(2);
	list.push_back(3);

	list.insert(1, 444);
	list.insert((size_t)0, 555);
	list.insert(5, 666);

	EXPECT_EQ(444, list.head()->next->next->value);
	EXPECT_EQ(555, list.head()->value);
	EXPECT_EQ(666, list.tail()->value);
}

TEST(TestListLib, throw_when_try_insert_by_pos_out_of_range) {
	List<int> list;
	list.push_back(1);
	list.push_back(2);
	list.push_back(3);

	ASSERT_ANY_THROW(list.insert(4, 555));
}
