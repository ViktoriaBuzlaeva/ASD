// Copyright 2026 Viktoria Buzlaeva

#include <gtest/gtest.h>
#include "../lib_sorted_table_on_bstree/sorted_table_on_bstree.h"

#define EPSILON 0.000001

TEST(TestSortedTableOnBSTreeLib, can_create) {
    SortedTableOnBSTree<int, std::string> table;
    EXPECT_TRUE(table.is_empty());
}

TEST(TestSortedTableOnBSTreeLib, can_insert) {
    SortedTableOnBSTree<int, std::string> table;
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

TEST(TestSortedTableOnBSTreeLib, throw_when_try_insert_same_key) {
    SortedTableOnBSTree<int, std::string> table;
    table.insert(1, "one");
    table.insert(2, "two");
    table.insert(5, "five");
    table.insert(3, "three");
    table.insert(4, "four");
    table.insert(6, "six");
    ASSERT_ANY_THROW(table.insert(5, ""));
}

TEST(TestSortedTableOnBSTreeLib, can_find) {
    SortedTableOnBSTree<int, std::string> table;
    table.insert(1, "one");
    table.insert(2, "two");
    table.insert(5, "five");
    table.insert(3, "three");
    table.insert(4, "four");
    table.insert(6, "six");
    EXPECT_EQ(table.found(1), "one");
    EXPECT_EQ(table.found(2), "two");
}

TEST(TestSortedTableOnBSTreeLib, throw_when_try_find_non_exist_key) {
    SortedTableOnBSTree<int, std::string> table;
    ASSERT_ANY_THROW(table.found(1));
    table.insert(1, "one");
    table.insert(2, "two");
    table.insert(5, "five");
    table.insert(3, "three");
    table.insert(4, "four");
    table.insert(6, "six");
    ASSERT_ANY_THROW(table.found(7));
}

TEST(TestSortedTableOnBSTreeLib, can_sort_correctly) {
    SortedTableOnBSTree<int, std::string> table;
    table.insert(1, "one");
    table.insert(2, "two");
    table.insert(5, "five");
    table.insert(4, "four");
    table.insert(6, "six");
    table.insert(3, "three");
    EXPECT_EQ(table.rows().root()->data.value, table.found(1));
    EXPECT_EQ(table.rows().root()->right->data.value, table.found(2));
    EXPECT_EQ(table.rows().root()->right->right->data.value, table.found(5));
    EXPECT_EQ(table.rows().root()->right->right->right->data.value,
        table.found(6));
    EXPECT_EQ(table.rows().root()->right->right->left->data.value,
        table.found(4));
    EXPECT_EQ(table.rows().root()->right->right->left->left->data.value,
        table.found(3));
    // table.print();
}

TEST(TestSortedTableOnBSTreeLib, can_erase) {
    SortedTableOnBSTree<int, std::string> table;
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

TEST(TestSortedTableOnBSTreeLib, throw_when_try_erase_non_exist_key) {
    SortedTableOnBSTree<int, std::string> table;
    ASSERT_ANY_THROW(table.erase(1));
    table.insert(1, "one");
    table.insert(2, "two");
    table.insert(5, "five");
    table.insert(4, "four");
    table.insert(6, "six");
    ASSERT_ANY_THROW(table.erase(3));
}
