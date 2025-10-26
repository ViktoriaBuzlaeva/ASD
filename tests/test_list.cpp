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
