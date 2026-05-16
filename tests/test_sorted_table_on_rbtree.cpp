// Copyright 2026 Viktoria Buzlaeva

#include <gtest/gtest.h>
#include "../lib_sorted_table_on_rbtree/sorted_table_on_rbtree.h"

#define EPSILON 0.000001

TEST(TestSortedTableOnRBTreeLib, can_create) {
    SortedTableOnRBTree<int, std::string> table;
    EXPECT_TRUE(table.is_empty());
}

TEST(TestSortedTableOnRBTreeLib, can_insert) {
    SortedTableOnRBTree<int, std::string> table;
    table.insert(1, "one");
    table.insert(2, "two");
    table.insert(5, "five");
    table.insert(3, "three");
    table.insert(4, "four");
    table.insert(6, "six");
    table.insert(8, "eight");
    table.insert(9, "nine");
    table.insert(7, "seven");
    EXPECT_FALSE(table.is_empty());
    // table.print();
}

TEST(TestSortedTableOnRBTreeLib, throw_when_try_insert_same_key) {
    SortedTableOnRBTree<int, std::string> table;
    table.insert(1, "one");
    table.insert(2, "two");
    table.insert(5, "five");
    table.insert(3, "three");
    table.insert(4, "four");
    table.insert(6, "six");
    ASSERT_ANY_THROW(table.insert(5, ""));
}

TEST(TestSortedTableOnRBTreeLib, can_find) {
    SortedTableOnRBTree<int, std::string> table;
    table.insert(1, "one");
    table.insert(2, "two");
    table.insert(5, "five");
    table.insert(3, "three");
    table.insert(4, "four");
    table.insert(6, "six");
    EXPECT_EQ(table.found(1), "one");
    EXPECT_EQ(table.found(2), "two");
}

TEST(TestSortedTableOnRBTreeLib, throw_when_try_find_non_exist_key) {
    SortedTableOnRBTree<int, std::string> table;
    ASSERT_ANY_THROW(table.found(1));
    table.insert(1, "one");
    table.insert(2, "two");
    table.insert(5, "five");
    table.insert(3, "three");
    table.insert(4, "four");
    table.insert(6, "six");
    ASSERT_ANY_THROW(table.found(7));
}

TEST(TestSortedTableOnRBTreeLib, can_sort_correctly) {
    SortedTableOnRBTree<int, std::string> table;
    table.insert(1, "one");
    table.insert(2, "two");
    table.insert(5, "five");
    table.insert(6, "six");
    table.insert(7, "seven");
    table.insert(8, "eight");
    EXPECT_EQ(table.rows().root()->data.value, table.found(2));
    EXPECT_EQ(table.rows().root()->right->data.value, table.found(6));
    EXPECT_EQ(table.rows().root()->right->right->data.value, table.found(7));
    EXPECT_EQ(table.rows().root()->right->left->data.value, table.found(5));
    EXPECT_EQ(table.rows().root()->right->right->right->data.value, table.found(8));
    EXPECT_EQ(table.rows().root()->left->data.value, table.found(1));
    // table.print();
}
