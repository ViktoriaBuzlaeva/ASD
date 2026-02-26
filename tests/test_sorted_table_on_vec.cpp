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
    table.insert(2, "two");
    table.insert(5, "five");
    table.insert(4, "four");
    table.insert(6, "six");
    table.insert(3, "three");
    EXPECT_FALSE(table.is_empty());
    table.print();
}

TEST(TestSortedTableOnVecLib, throw_when_try_insert_same_key) {
    SortedTableOnVec<int, std::string> table;
    table.insert(1, "one");
    table.insert(2, "two");
    table.insert(5, "five");
    table.insert(4, "four");
    table.insert(6, "six");
    table.insert(3, "three");
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

TEST(TestSortedTableOnVecLib, can_sort_correctly) {
    SortedTableOnVec<int, std::string> table;
    table.insert(1, "one");
    table.insert(2, "two");
    table.insert(5, "five");
    table.insert(4, "four");
    table.insert(6, "six");
    table.insert(3, "three");
    EXPECT_EQ(table.rows()[0].value, table.found(1));
    EXPECT_EQ(table.rows()[1].value, table.found(2));
    EXPECT_EQ(table.rows()[2].value, table.found(3));
    EXPECT_EQ(table.rows()[3].value, table.found(4));
    EXPECT_EQ(table.rows()[4].value, table.found(5));
    EXPECT_EQ(table.rows()[5].value, table.found(6));
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
