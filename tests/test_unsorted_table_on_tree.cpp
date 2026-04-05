// Copyright 2026 Viktoria Buzlaeva

#include <gtest/gtest.h>
#include "../lib_unsorted_table_on_tree/unsorted_table_on_tree.h"

#define EPSILON 0.000001

TEST(TestUnsortedTableOnTreeLib, can_create) {
    UnsortedTableOnTree<int, std::string> table;
    EXPECT_TRUE(table.is_empty());
}

TEST(TestUnsortedTableOnTreeLib, can_insert) {
    UnsortedTableOnTree<int, std::string> table;
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

TEST(TestUnsortedTableOnTreeLib, throw_when_try_insert_same_key) {
    UnsortedTableOnTree<int, std::string> table;
    table.insert(1, "one");
    table.insert(2, "two");
    table.insert(5, "five");
    table.insert(3, "three");
    table.insert(4, "four");
    table.insert(6, "six");
    ASSERT_ANY_THROW(table.insert(5, ""));
}

TEST(TestUnsortedTableOnTreeLib, can_find) {
    UnsortedTableOnTree<int, std::string> table;
    table.insert(1, "one");
    table.insert(2, "two");
    table.insert(5, "five");
    table.insert(3, "three");
    table.insert(4, "four");
    table.insert(6, "six");
    EXPECT_EQ(table.found(1), "one");
    EXPECT_EQ(table.found(2), "two");
}

TEST(TestUnsortedTableOnTreeLib, throw_when_try_find_non_exist_key) {
    UnsortedTableOnTree<int, std::string> table;
    ASSERT_ANY_THROW(table.found(1));
    table.insert(1, "one");
    table.insert(2, "two");
    table.insert(5, "five");
    table.insert(3, "three");
    table.insert(4, "four");
    table.insert(6, "six");
    ASSERT_ANY_THROW(table.found(7));
}

TEST(TestUnsortedTableOnTreeLib, can_erase) {
    UnsortedTableOnTree<int, std::string> table;
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

TEST(TestUnsortedTableOnTreeLib, throw_when_try_erase_non_exist_key) {
    UnsortedTableOnTree<int, std::string> table;
    ASSERT_ANY_THROW(table.erase(1));
    table.insert(1, "one");
    table.insert(2, "two");
    table.insert(5, "five");
    table.insert(4, "four");
    table.insert(6, "six");
    // table.print();
    ASSERT_ANY_THROW(table.erase(3));
}
