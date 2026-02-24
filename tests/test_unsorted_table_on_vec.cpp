// Copyright 2026 Viktoria Buzlaeva

#include <gtest/gtest.h>
#include "../lib_unsorted_table_on_vec/unsorted_table_on_vec.h"

#define EPSILON 0.000001

TEST(TestUnsortedTableOnVecLib, can_create) {
    UnsortedTableOnVec<int, std::string> table;
    EXPECT_TRUE(table.is_empty());
}

TEST(TestUnsortedTableOnVecLib, can_insert) {
    UnsortedTableOnVec<int, std::string> table;
    table.insert(1, "one");
    EXPECT_FALSE(table.is_empty());
}

TEST(TestUnsortedTableOnVecLib, throw_when_try_insert_same_key) {
    UnsortedTableOnVec<int, std::string> table;
    table.insert(1, "one");
    table.insert(2, "two");
    ASSERT_ANY_THROW(table.insert(1, ""));
}

TEST(TestUnsortedTableOnVecLib, can_find) {
    UnsortedTableOnVec<int, std::string> table;
    table.insert(1, "one");
    table.insert(2, "two");
    EXPECT_EQ(table.found(1), "one");
    EXPECT_EQ(table.found(2), "two");
}

TEST(TestUnsortedTableOnVecLib, throw_when_try_find_non_exist_key) {
    UnsortedTableOnVec<int, std::string> table;
    ASSERT_ANY_THROW(table.found(1));
    table.insert(1, "one");
    table.insert(2, "two");
    ASSERT_ANY_THROW(table.found(3));
}

TEST(TestUnsortedTableOnVecLib, can_erase) {
    UnsortedTableOnVec<int, std::string> table;
    table.insert(1, "one");
    table.erase(1);
    EXPECT_TRUE(table.is_empty());
}

TEST(TestUnsortedTableOnVecLib, throw_when_try_erase_non_exist_key) {
    UnsortedTableOnVec<int, std::string> table;
    ASSERT_ANY_THROW(table.erase(1));
    table.insert(1, "one");
    table.insert(2, "two");
    ASSERT_ANY_THROW(table.erase(3));
}
