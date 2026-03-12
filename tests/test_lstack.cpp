// Copyright 2025 Viktoria Buzlaeva

#include <gtest/gtest.h>
#include "../lib_lstack/lstack.h"

#define EPSILON 0.000001

TEST(TestLStackLib, can_create) {
	ASSERT_NO_THROW(LStack<int> stack);
	ASSERT_NO_THROW(LStack<int> stack(20));
}

TEST(TestLStackLib, throw_when_try_create_init_with_wrong_size) {
	ASSERT_ANY_THROW(LStack<int> stack(0));
	ASSERT_ANY_THROW(LStack<int> stack(-10));
}

TEST(TestLStackLib, can_create_copy) {
	LStack<int> stack_1(10);
	ASSERT_NO_THROW(LStack<int> stack_2(stack_1));
}

TEST(TestLStackLib, throw_when_try_create_copy) {
	LStack<int>* stack_1 = NULL;
	ASSERT_ANY_THROW(LStack<int> stack_2(*stack_1));
}

TEST(TestLStackLib, can_check_is_empty_correctly) {
	LStack<int> stack;
	EXPECT_TRUE(stack.is_empty());
	stack.push(111);
	EXPECT_FALSE(stack.is_empty());
}

TEST(TestLStackLib, can_push_elem_correctly) {
	LStack<int> stack(10);
	stack.push(111);
	EXPECT_EQ(111, stack.top());
	stack.push(222);
	EXPECT_EQ(222, stack.top());
}

TEST(TestLStackLib, can_pop_elem_correctly) {
	LStack<int> stack;

	stack.push(111);
	stack.push(111);
	stack.push(111);
	stack.pop();
	stack.pop();
	stack.pop();

	EXPECT_TRUE(stack.is_empty());
}

TEST(TestLStackLib, can_check_is_full_correctly) {
	LStack<int> stack(3);
	stack.push(111);
	EXPECT_FALSE(stack.is_full());
	stack.push(111);
	stack.push(111);
	EXPECT_TRUE(stack.is_full());
}

TEST(TestLStackLib, throw_when_try_push_elem_in_full_stack) {
	LStack<int> stack(3);

	stack.push(111);
	stack.push(222);
	stack.push(333);

	ASSERT_ANY_THROW(stack.push(444));
}

TEST(TestLStackLib, throw_when_try_pop_elem_in_empty_stack) {
	LStack<int> stack;
	ASSERT_ANY_THROW(stack.pop());
}

TEST(TestLStackLib, throw_when_try_assign_top_elem_in_empty_stack) {
	LStack<int> stack(3);
	ASSERT_ANY_THROW(stack.top());
}

TEST(TestLStackLib, can_clear_stack_correctly) {
	LStack<int> stack(10);

	stack.push(111);
	stack.push(222);
	stack.clear();
	stack.push(333);

	EXPECT_EQ(333, stack.top());
}
