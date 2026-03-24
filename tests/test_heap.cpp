// Copyright 2026 Viktoria Buzlaeva

#include <gtest/gtest.h>
#include "../lib_heap/heap.h"

#define EPSILON 0.000001

TEST(TestHeapLib, can_create) {
    ASSERT_NO_THROW(Heap<int>());
}

TEST(TestHeapLib, can_insert) {
    Heap<int> h;
    ASSERT_NO_THROW(h.insert(5));
    EXPECT_EQ(5, h.root());
    ASSERT_NO_THROW(h.insert(3));
    EXPECT_EQ(3, h.root());
    ASSERT_NO_THROW(h.insert(4));
    EXPECT_EQ(3, h.root());
    ASSERT_NO_THROW(h.insert(6));
    EXPECT_EQ(3, h.root());
    ASSERT_NO_THROW(h.insert(2));
    EXPECT_EQ(2, h.root());
    ASSERT_NO_THROW(h.insert(1));
    EXPECT_EQ(1, h.root());
    ASSERT_NO_THROW(h.insert(7));
    EXPECT_EQ(1, h.root());
}

TEST(TestHeapLib, can_erase) {
    Heap<int> h;
    h.insert(3);
    h.insert(8);
    h.insert(6);
    h.insert(2);
    h.insert(4);
    h.insert(5);
    h.insert(1);
    h.insert(7);
    h.erase();
    EXPECT_EQ(2, h.root());
    h.erase();
    EXPECT_EQ(3, h.root());
}
