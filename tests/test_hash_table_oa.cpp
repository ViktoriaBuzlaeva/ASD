// Copyright 2026 Viktoria Buzlaeva

#include <gtest/gtest.h>
#include "../lib_hash_table_oa/hash_table_oa.h"

#define EPSILON 0.000001

TEST(TestHashTableOALib, can_create) {
    ASSERT_NO_THROW(HashTableOA<int> table);
    ASSERT_NO_THROW(HashTableOA<int> table(100));
    ASSERT_NO_THROW(HashTableOA<int> table(101));
}

TEST(TestHashTableOALib, can_insert) {
    HashTableOA<int> table;
    table.insert("one", 1);
    table.insert("two", 2);
    table.insert("five", 5);
    table.insert("four", 4);
    table.insert("six", 6);
    table.insert("three", 3);
    EXPECT_FALSE(table.is_empty());
    // table.print();
}

TEST(TestHashTableOALib, throw_when_try_insert_same_key) {
    HashTableOA<int> table;
    table.insert("one", 1);
    table.insert("two", 2);
    table.insert("five", 5);
    table.insert("four", 4);
    table.insert("six", 6);
    table.insert("three", 3);
    ASSERT_ANY_THROW(table.insert("six", 7));
}

TEST(TestHashTableOALib, throw_when_try_insert_full_table) {
    HashTableOA<int> table(6);
    table.insert("one", 1);
    table.insert("two", 2);
    table.insert("five", 5);
    table.insert("four", 4);
    table.insert("six", 6);
    table.insert("three", 3);
    ASSERT_ANY_THROW(table.insert("seven", 7));
}

TEST(TestHashTableOALib, can_find) {
    HashTableOA<int> table;
    table.insert("one", 1);
    table.insert("two", 2);
    table.insert("five", 5);
    table.insert("four", 4);
    table.insert("six", 6);
    table.insert("three", 3);
    EXPECT_EQ(table.found("one"), 1);
    EXPECT_EQ(table.found("six"), 6);
}

TEST(TestHashTableOALib, throw_when_try_find_non_exist_key) {
    HashTableOA<int> table(6);
    ASSERT_ANY_THROW(table.found("one"));
    table.insert("one", 1);
    table.insert("two", 2);
    table.insert("five", 5);
    table.insert("four", 4);
    table.insert("six", 6);
    table.insert("three", 3);
    ASSERT_ANY_THROW(table.found("seven"));
}

TEST(TestHashTableOALib, can_erase) {
    HashTableOA<int> table;
    table.insert("one", 1);
    table.insert("two", 2);
    table.insert("five", 5);
    table.insert("four", 4);

    table.erase("one");
    table.erase("two");
    table.erase("five");
    table.erase("four");
    EXPECT_TRUE(table.is_empty());
}

TEST(TestHashTableOALib, throw_when_try_erase_non_exist_key) {
    HashTableOA<int> table;
    ASSERT_ANY_THROW(table.erase("one"));
    table.insert("one", 1);
    table.insert("two", 2);
    table.insert("five", 5);
    table.insert("four", 4);
    table.insert("six", 6);
    ASSERT_ANY_THROW(table.erase("three"));
}
