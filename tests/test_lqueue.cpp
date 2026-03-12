// Copyright 2025 Viktoria Buzlaeva

#include <gtest/gtest.h>
#include "../lib_lqueue/lqueue.h"

#define EPSILON 0.000001

TEST(TestLQueueLib, can_create) {
	ASSERT_NO_THROW(LQueue<int> queue);
	ASSERT_NO_THROW(LQueue<int> queue(10));
}

TEST(TestLQueueLib, throw_when_try_create_init_with_wrong_size) {
	ASSERT_ANY_THROW(LQueue<int> queue(0));
	ASSERT_ANY_THROW(LQueue<int> queue(-10));
}

TEST(TestLQueueLib, can_create_copy) {
	LQueue<int> queue_1(10);
	ASSERT_NO_THROW(LQueue<int> queue_2(queue_1));
}

TEST(TestLQueueLib, throw_when_try_create_copy) {
	LQueue<int>* queue_1 = NULL;\
	ASSERT_ANY_THROW(LQueue<int> queue_2(*queue_1));
}

TEST(TestLQueueLib, can_check_is_empty_correctly) {
	LQueue<int> queue;
	EXPECT_TRUE(queue.is_empty());
}

TEST(TestLQueueLib, can_push_elem_correctly) {
	LQueue<int> queue(10);
	queue.push(111);
	EXPECT_EQ(111, queue.head());
	queue.push(222);
	EXPECT_EQ(111, queue.head());
	EXPECT_EQ(222, queue.tail());
}

TEST(TestLQueueLib, can_pop_elem_correctly) {
	LQueue<int> queue(10);
	queue.push(111);
	queue.pop();
	EXPECT_TRUE(queue.is_empty());
}

TEST(TestLQueueLib, can_check_is_full_correctly) {
	LQueue<int> queue(3);
	queue.push(111);
	EXPECT_FALSE(queue.is_full());
	queue.push(111);
	queue.push(111);
	EXPECT_TRUE(queue.is_full());
}

TEST(TestLQueueLib, throw_when_try_push_elem_in_full_queue) {
	LQueue<int> queue(3);
	queue.push(111);
	queue.push(222);
	queue.push(333);
	ASSERT_ANY_THROW(queue.push(444));
}

TEST(TestLQueueLib, throw_when_try_pop_elem_in_empty_queue) {
	LQueue<int> queue(3);
	ASSERT_ANY_THROW(queue.pop());
}

TEST(TestLQueueLib, throw_when_try_assign_elems_in_empty_queue) {
	LQueue<int> queue(3);
	ASSERT_ANY_THROW(queue.head());
	ASSERT_ANY_THROW(queue.tail());
}

TEST(TestLQueueLib, can_clear_queue_correctly) {
	LQueue<int> queue(10);
	queue.push(111);
	queue.push(222);
	queue.clear();
	queue.push(333);
	EXPECT_EQ(333, queue.head());
	EXPECT_EQ(333, queue.tail());
}
