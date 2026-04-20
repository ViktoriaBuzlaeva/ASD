// Copyright 2026 Viktoria Buzlaeva

#include <gtest/gtest.h>
#include "../lib_sorted_table_on_avltree/sorted_table_on_avltree.h"

#define EPSILON 0.000001

TEST(TestSortedTableOnAVLTreeLib, can_create) {
    SortedTableOnAVLTree<int, std::string> table;
    EXPECT_TRUE(table.is_empty());
}

TEST(TestSortedTableOnAVLTreeLib, can_insert) {
    SortedTableOnAVLTree<int, std::string> table;
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

TEST(TestSortedTableOnAVLTreeLib, throw_when_try_insert_same_key) {
    SortedTableOnAVLTree<int, std::string> table;
    table.insert(1, "one");
    table.insert(2, "two");
    table.insert(5, "five");
    table.insert(3, "three");
    table.insert(4, "four");
    table.insert(6, "six");
    ASSERT_ANY_THROW(table.insert(5, ""));
}

TEST(TestSortedTableOnAVLTreeLib, can_find) {
    SortedTableOnAVLTree<int, std::string> table;
    table.insert(1, "one");
    table.insert(2, "two");
    table.insert(5, "five");
    table.insert(3, "three");
    table.insert(4, "four");
    table.insert(6, "six");
    EXPECT_EQ(table.found(1), "one");
    EXPECT_EQ(table.found(2), "two");
}

TEST(TestSortedTableOnAVLTreeLib, throw_when_try_find_non_exist_key) {
    SortedTableOnAVLTree<int, std::string> table;
    ASSERT_ANY_THROW(table.found(1));
    table.insert(1, "one");
    table.insert(2, "two");
    table.insert(5, "five");
    table.insert(3, "three");
    table.insert(4, "four");
    table.insert(6, "six");
    ASSERT_ANY_THROW(table.found(7));
}

TEST(TestSortedTableOnAVLTreeLib, can_sort_correctly) {
    SortedTableOnAVLTree<int, std::string> table;
    table.insert(1, "one");
    table.insert(2, "two");
    table.insert(5, "five");
    table.insert(6, "six");
    table.insert(7, "seven");
    table.insert(8, "eight");
    EXPECT_EQ(table.rows().root()->data.value, table.found(6));
    EXPECT_EQ(table.rows().root()->right->data.value, table.found(7));
    EXPECT_EQ(table.rows().root()->right->right->data.value, table.found(8));
    EXPECT_EQ(table.rows().root()->left->data.value, table.found(2));
    EXPECT_EQ(table.rows().root()->left->right->data.value, table.found(5));
    EXPECT_EQ(table.rows().root()->left->left->data.value, table.found(1));
    // table.print();
}

TEST(TestSortedTableOnAVLTreeLib, can_erase) {
    SortedTableOnAVLTree<int, std::string> table;
    table.insert(1, "one");
    table.insert(2, "two");
    table.insert(5, "five");
    table.insert(3, "three");

    table.erase(1);
    table.erase(2);
    table.erase(5);
    table.erase(3);
    EXPECT_TRUE(table.is_empty());
}

TEST(TestSortedTableOnAVLTreeLib, throw_when_try_erase_non_exist_key) {
    SortedTableOnAVLTree<int, std::string> table;
    ASSERT_ANY_THROW(table.erase(1));
    table.insert(1, "one");
    table.insert(2, "two");
    table.insert(5, "five");
    table.insert(4, "four");
    table.insert(6, "six");
    ASSERT_ANY_THROW(table.erase(3));
}
