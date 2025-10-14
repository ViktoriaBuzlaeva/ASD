// Copyright 2025 Viktoria Buzlaeva

#include <gtest/gtest.h>
#include "../lib_stack/stack.h"

#define EPSILON 0.000001

TEST(TestStackLib, can_create_default) {
	// Arrange
	Stack<int> stack;

	// Act & Assert
	EXPECT_EQ(15, stack.get_size());
	EXPECT_EQ(-1, stack.get_top());
}

TEST(TestStackLib, can_create_init) {
	// Arrange
	Stack<int> stack(10);

	// Act & Assert
	EXPECT_EQ(10, stack.get_size());
	EXPECT_EQ(-1, stack.get_top());
}

TEST(TestStackLib, throw_when_try_create_init_with_wrong_size) {
	// Arrange
	// Act & Assert
	ASSERT_ANY_THROW(Stack<int> stack(0));
	ASSERT_ANY_THROW(Stack<int> stack(-10));
}

TEST(TestStackLib, can_create_copy) {
	// Arrange
	Stack<int> stack_1(10);
	Stack<int> stack_2(stack_1);

	// Act & Assert
	EXPECT_EQ(10, stack_2.get_size());
	EXPECT_EQ(-1, stack_2.get_top());
}

TEST(TestStackLib, throw_when_try_create_copy) {
	// Arrange
	Stack<int>* stack_1 = NULL;

	// Act & Assert
	ASSERT_ANY_THROW(Stack<int> stack_2(*stack_1));
}

TEST(TestStackLib, can_push_elem_correctly) {
	// Arrange
	Stack<int> stack(10);

	// Act
	stack.push(111);

	// Assert
	EXPECT_EQ(10, stack.get_size());
	EXPECT_EQ(0, stack.get_top());
}

TEST(TestStackLib, can_pop_elem_correctly) {
	// Arrange
	Stack<int> stack(10);

	// Act
	stack.push(111);
	stack.pop();

	// Assert
	EXPECT_EQ(10, stack.get_size());
	EXPECT_EQ(-1, stack.get_top());
}

TEST(TestStackLib, can_check_is_full_for_not_full_stack_correctly) {
	// Arrange
	Stack<int> stack(3);

	// Act
	stack.push(111);

	// Assert
	EXPECT_EQ(false, stack.is_full());
}

TEST(TestStackLib, can_check_is_full_for_full_stack_correctly) {
	// Arrange
	Stack<int> stack(3);

	// Act
	stack.push(111);
	stack.push(222);
	stack.push(333);

	// Assert
	EXPECT_EQ(true, stack.is_full());
}

TEST(TestStackLib, can_check_is_empty_for_not_empty_stack_correctly) {
	// Arrange
	Stack<int> stack(3);

	// Act
	stack.push(111);

	// Assert
	EXPECT_EQ(false, stack.is_empty());
}

TEST(TestStackLib, can_check_is_empty_for_empty_stack_correctly) {
	// Arrange
	Stack<int> stack(3);

	// Act
	stack.push(111);
	stack.pop();

	// Assert
	EXPECT_EQ(true, stack.is_empty());
}

TEST(TestStackLib, throw_when_try_push_elem_in_full_stack) {
	// Arrange
	Stack<int> stack(3);

	// Act
	stack.push(111);
	stack.push(222);
	stack.push(333);

	// Assert
	ASSERT_ANY_THROW(stack.push(444));
}

TEST(TestStackLib, throw_when_try_pop_elem_in_empty_stack) {
	// Arrange
	Stack<int> stack(3);

	// Act & Assert
	ASSERT_ANY_THROW(stack.pop());
}

TEST(TestStackLib, can_assign_top_elem_correctly) {
	// Arrange
	Stack<int> stack(10);

	// Act
	stack.push(111);

	// Assert
	EXPECT_EQ(111, stack.top());
}

TEST(TestStackLib, throw_when_try_assign_top_elem_in_empty_stack) {
	// Arrange
	Stack<int> stack(3);

	// Act & Assert
	ASSERT_ANY_THROW(stack.top());
}

TEST(TestStackLib, can_clear_stack_correctly) {
	// Arrange
	Stack<int> stack(10);

	// Act
	stack.push(111);
	stack.push(222);
	stack.clear();
	stack.push(333);

	// Assert
	EXPECT_EQ(10, stack.get_size());
	EXPECT_EQ(0, stack.get_top());
	EXPECT_EQ(333, stack.top());
}
