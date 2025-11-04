// Copyright 2025 Viktoria Buzlaeva

#include <gtest/gtest.h>
#include "../lib_doubly_linked_list/doubly_linked_list.h"

#define EPSILON 0.000001

TEST(TestDoublyLinkedListLib, can_create) {
	ASSERT_NO_THROW(DoublyLinkedList<int> doubly_linked_list);
}

TEST(TestDoublyLinkedListLib, can_create_copy) {
	DoublyLinkedList<int> list_1;
	list_1.push_back(1);
	list_1.push_back(2);
	list_1.push_back(3);

	ASSERT_NO_THROW(DoublyLinkedList<int> list_2(list_1));
}

TEST(TestDoublyLinkedListLib, can_create_copy_correctly) {
	DoublyLinkedList<int> list_1;
	list_1.push_back(1);
	list_1.push_back(2);
	list_1.push_back(3);

	DoublyLinkedList<int> list_2(list_1);

	EXPECT_EQ(3, list_2.tail()->value);
	EXPECT_EQ(1, list_2.head()->value);
}

TEST(TestDoublyLinkedListLib, throw_when_try_create_copy) {
	DoublyLinkedList<int>* list_1 = NULL;

	ASSERT_ANY_THROW(DoublyLinkedList<int> list_2(*list_1));
}

TEST(TestDoublyLinkedListLib, can_check_empty_correctly) {
	DoublyLinkedList<int> list;

	EXPECT_TRUE(list.is_empty());
}

TEST(TestDoublyLinkedListLib, can_push_front_correctly) {
	DoublyLinkedList<int> list;

	list.push_front(1);
	list.push_front(2);
	list.push_front(3);

	EXPECT_EQ(1, list.tail()->value);
	EXPECT_EQ(3, list.head()->value);
}

TEST(TestDoublyLinkedListLib, can_push_back_correctly) {
	DoublyLinkedList<int> list;

	list.push_back(1);
	list.push_back(2);
	list.push_back(3);

	EXPECT_EQ(3, list.tail()->value);
	EXPECT_EQ(1, list.head()->value);
}

TEST(TestDoublyLinkedListLib, can_insert_by_pointer_correctly) {
	DoublyLinkedList<int> list;
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

TEST(TestDoublyLinkedListLib, throw_when_try_insert_by_pointer_empty) {
	DoublyLinkedList<int> list;

	ASSERT_ANY_THROW(list.insert(list.tail(), 555));
}

TEST(TestDoublyLinkedListLib, throw_when_try_insert_by_pointer_nullptr) {
	DoublyLinkedList<int> list;
	list.push_back(1);
	list.push_back(2);
	list.push_back(3);
	Node<int>* ptr = nullptr;

	ASSERT_ANY_THROW(list.insert(ptr, 555));
}

TEST(TestDoublyLinkedListLib, can_insert_by_pos_correctly) {
	DoublyLinkedList<int> list;
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

TEST(TestDoublyLinkedListLib, throw_when_try_insert_by_pos_out_of_range) {
	DoublyLinkedList<int> list;
	list.push_back(1);
	list.push_back(2);
	list.push_back(3);

	ASSERT_ANY_THROW(list.insert(4, 555));
}

TEST(TestDoublyLinkedListLib, can_pop_front_correctly) {
	DoublyLinkedList<int> list;
	list.push_back(1);
	list.push_back(2);
	list.push_back(3);

	list.pop_front();
	list.pop_front();
	EXPECT_EQ(3, list.tail()->value);
	EXPECT_EQ(3, list.head()->value);

	list.pop_front();
	EXPECT_TRUE(list.is_empty());
}

TEST(TestDoublyLinkedListLib, throw_when_try_pop_front_empty) {
	DoublyLinkedList<int> list;

	ASSERT_ANY_THROW(list.pop_front());
}

TEST(TestDoublyLinkedListLib, can_pop_back_correctly) {
	DoublyLinkedList<int> list;
	list.push_back(1);
	list.push_back(2);
	list.push_back(3);

	list.pop_back();
	list.pop_back();
	EXPECT_EQ(1, list.tail()->value);
	EXPECT_EQ(1, list.head()->value);

	list.pop_back();
	EXPECT_TRUE(list.is_empty());
}

TEST(TestDoublyLinkedListLib, throw_when_try_pop_back_empty) {
	DoublyLinkedList<int> list;

	ASSERT_ANY_THROW(list.pop_back());
}

TEST(TestDoublyLinkedListLib, can_erase_by_pointer_correctly) {
	DoublyLinkedList<int> list;
	list.push_back(1);
	list.push_back(2);
	list.push_back(3);

	list.erase(list.head()->next);
	list.erase(list.head());
	EXPECT_EQ(1, list.tail()->value);
	EXPECT_EQ(1, list.head()->value);
}

TEST(TestDoublyLinkedListLib, throw_when_try_erase_empty_or_incorrect_pos) {
	DoublyLinkedList<int> list;
	ASSERT_ANY_THROW(list.erase(list.head()));

	list.push_back(1);
	list.push_back(2);
	ASSERT_ANY_THROW(list.erase(list.tail()->next));
}

TEST(TestDoublyLinkedListLib, throw_when_try_erase_nullptr) {
	DoublyLinkedList<int> list;
	list.push_back(1);
	list.push_back(2);
	list.push_back(3);
	Node<int>* ptr = nullptr;

	ASSERT_ANY_THROW(list.erase(ptr));
}

TEST(TestDoublyLinkedListLib, can_erase_by_pos_correctly) {
	DoublyLinkedList<int> list;
	list.push_back(1);
	list.push_back(2);
	list.push_back(3);
	list.push_back(4);
	list.push_back(5);

	list.erase((size_t)0);
	list.erase(3);
	list.erase(1);

	EXPECT_EQ(2, list.head()->value);
	EXPECT_EQ(4, list.tail()->value);
}

TEST(TestDoublyLinkedListLib, throw_when_try_erase_by_pos_empty) {
	DoublyLinkedList<int> list;

	ASSERT_ANY_THROW(list.erase((size_t)0));
}

TEST(TestDoublyLinkedListLib, throw_when_try_erase_by_pos_out_of_range) {
	DoublyLinkedList<int> list;
	list.push_back(1);
	list.push_back(2);
	list.push_back(3);

	ASSERT_ANY_THROW(list.erase(4));
}

TEST(TestDoublyLinkedListLib, check_iterator_empty_list) {
	DoublyLinkedList<int> list;

	int i = 1;
	DoublyLinkedList<int>::Iterator it;
	for (it = list.begin(); it != list.end(); it++) {
		*it = i;
	}

	EXPECT_EQ(it, list.begin());
}

TEST(TestDoublyLinkedListLib, check_iterator_reading) {
	DoublyLinkedList<int> list;

	for (int i = 0; i < 3; i++) {
		list.push_back(i * 3 + 1);
	}

	DoublyLinkedList<int>::Iterator it;
	it = list.begin();

	EXPECT_EQ(1, *it);
	EXPECT_EQ(4, *(++it));
	EXPECT_EQ(7, *(it += 1));
	EXPECT_EQ(4, *(it -= 1));
	EXPECT_EQ(1, *(--it));
}

TEST(TestDoublyLinkedListLib, check_iterator_writing) {
	DoublyLinkedList<int> list;

	for (int i = 0; i < 3; i++) {
		list.push_back(0);
	}

	int i = 1;
	DoublyLinkedList<int>::Iterator it;
	for (it = list.begin(); it != list.end(); it++) {
		*it = i;
		i *= 2;
	}

	it = list.begin();
	EXPECT_EQ(1, *it);
	EXPECT_EQ(2, *(++it));
	EXPECT_EQ(4, *(++it));
}
