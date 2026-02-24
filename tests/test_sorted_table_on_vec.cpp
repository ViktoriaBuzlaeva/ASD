// Copyright 2026 Viktoria Buzlaeva

#include <gtest/gtest.h>
#include "../lib_sorted_table_on_vec/sorted_table_on_vec.h"

#define EPSILON 0.000001

TEST(TestSortedTableOnVecLib, can_create) {
    SortedTableOnVec<int, std::string> table;
    EXPECT_TRUE(table.is_empty());
}

TEST(TestSortedTableOnVecLib, can_insert) {
    SortedTableOnVec<int, std::string> table;
    table.insert(1, "one");
    EXPECT_FALSE(table.is_empty());
}

TEST(TestSortedTableOnVecLib, throw_when_try_insert_same_key) {
    SortedTableOnVec<int, std::string> table;
    table.insert(1, "one");
    table.insert(2, "two");
    ASSERT_ANY_THROW(table.insert(1, ""));
}

TEST(TestSortedTableOnVecLib, can_find) {
    SortedTableOnVec<int, std::string> table;
    table.insert(1, "one");
    table.insert(2, "two");
    EXPECT_EQ(table.found(1), "one");
    EXPECT_EQ(table.found(2), "two");
}

TEST(TestSortedTableOnVecLib, throw_when_try_find_non_exist_key) {
    SortedTableOnVec<int, std::string> table;
    ASSERT_ANY_THROW(table.found(1));
    table.insert(1, "one");
    table.insert(2, "two");
    ASSERT_ANY_THROW(table.found(3));
}

TEST(TestSortedTableOnVecLib, can_erase) {
    SortedTableOnVec<int, std::string> table;
    table.insert(1, "one");
    table.erase(1);
    EXPECT_TRUE(table.is_empty());
}

TEST(TestSortedTableOnVecLib, throw_when_try_erase_non_exist_key) {
    SortedTableOnVec<int, std::string> table;
    ASSERT_ANY_THROW(table.erase(1));
    table.insert(1, "one");
    table.insert(2, "two");
    ASSERT_ANY_THROW(table.erase(3));
}
