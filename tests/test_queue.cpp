// Copyright 2025 Viktoria Buzlaeva

#include <gtest/gtest.h>
#include "../lib_queue/queue.h"

#define EPSILON 0.000001

TEST(TestQueueLib, can_create_default) {
	Queue<int> queue;

	EXPECT_EQ(15, queue.get_size());
	EXPECT_EQ(0, queue.get_count());
	EXPECT_EQ(0, queue.get_head());
}

TEST(TestQueueLib, can_create_init) {
	Queue<int> queue(10);

	EXPECT_EQ(10, queue.get_size());
	EXPECT_EQ(0, queue.get_count());
	EXPECT_EQ(0, queue.get_head());
}

TEST(TestQueueLib, throw_when_try_create_init_with_wrong_size) {
	ASSERT_ANY_THROW(Queue<int> queue(0));
	ASSERT_ANY_THROW(Queue<int> queue(-10));
}

TEST(TestQueueLib, can_create_copy) {
	Queue<int> queue_1(10);
	Queue<int> queue_2(queue_1);

	EXPECT_EQ(10, queue_2.get_size());
	EXPECT_EQ(0, queue_2.get_count());
	EXPECT_EQ(0, queue_2.get_head());
}

TEST(TestQueueLib, throw_when_try_create_copy) {
	Queue<int>* queue_1 = NULL;

	ASSERT_ANY_THROW(Queue<int> queue_2(*queue_1));
}

TEST(TestQueueLib, can_push_elem_correctly) {
	Queue<int> queue(10);

	queue.push(111);

	EXPECT_EQ(10, queue.get_size());
	EXPECT_EQ(1, queue.get_count());
	EXPECT_EQ(0, queue.get_head());
}

TEST(TestQueueLib, can_pop_elem_correctly) {
	Queue<int> queue(10);

	queue.push(111);
	queue.pop();

	EXPECT_EQ(10, queue.get_size());
	EXPECT_EQ(0, queue.get_count());
	EXPECT_EQ(1, queue.get_head());
}

TEST(TestQueueLib, can_check_is_full_for_not_full_queue_correctly) {
	Queue<int> queue(3);

	queue.push(111);

	EXPECT_EQ(false, queue.is_full());
}

TEST(TestQueueLib, can_check_is_full_for_full_queue_correctly) {
	Queue<int> queue(3);

	queue.push(111);
	queue.push(222);
	queue.push(333);

	EXPECT_EQ(true, queue.is_full());
}

TEST(TestQueueLib, can_check_is_empty_for_not_empty_queue_correctly) {
	Queue<int> queue(3);

	queue.push(111);

	EXPECT_EQ(false, queue.is_empty());
}

TEST(TestQueueLib, can_check_is_empty_for_empty_queue_correctly) {
	Queue<int> queue(3);

	queue.push(111);
	queue.pop();

	EXPECT_EQ(true, queue.is_empty());
}

TEST(TestQueueLib, throw_when_try_push_elem_in_full_queue) {
	Queue<int> queue(3);

	queue.push(111);
	queue.push(222);
	queue.push(333);

	ASSERT_ANY_THROW(queue.push(444));
}

TEST(TestQueueLib, throw_when_try_pop_elem_in_empty_queue) {
	Queue<int> queue(3);

	ASSERT_ANY_THROW(queue.pop());
}

TEST(TestQueueLib, can_assign_head_elem_correctly) {
	Queue<int> queue(10);

	queue.push(111);
	queue.push(222);
	queue.push(333);

	EXPECT_EQ(111, queue.head());
}

TEST(TestQueueLib, can_assign_tail_elem_correctly) {
	Queue<int> queue(10);

	queue.push(111);
	queue.push(222);
	queue.push(333);

	EXPECT_EQ(333, queue.tail());
}

TEST(TestQueueLib, can_assign_equal_head_and_tail_elem_correctly) {
	Queue<int> queue(10);

	queue.push(111);

	EXPECT_EQ(111, queue.head());
	EXPECT_EQ(111, queue.tail());
}

TEST(TestQueueLib, can_assign_elems_correctly) {
	Queue<int> queue(5);

	queue.push(111);
	queue.push(222);
	queue.push(333);
	queue.push(444);
	queue.push(555);
	queue.pop();
	queue.pop();
	queue.push(666);
	queue.push(777);

	EXPECT_EQ(333, queue.head());
	EXPECT_EQ(777, queue.tail());
}

TEST(TestQueueLib, throw_when_try_assign_head_elem_in_empty_queue) {
	Queue<int> queue(3);

	ASSERT_ANY_THROW(queue.head());
}

TEST(TestQueueLib, throw_when_try_assign_tail_elem_in_empty_queue) {
	Queue<int> queue(3);

	ASSERT_ANY_THROW(queue.tail());
}

TEST(TestQueueLib, can_clear_queue_correctly) {
	Queue<int> queue(10);

	queue.push(111);
	queue.push(222);
	queue.clear();

	EXPECT_EQ(10, queue.get_size());
	EXPECT_EQ(0, queue.get_count());
	EXPECT_EQ(0, queue.get_head());
}
