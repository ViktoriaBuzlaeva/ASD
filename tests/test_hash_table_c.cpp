// Copyright 2026 Viktoria Buzlaeva

#include <gtest/gtest.h>
#include "../lib_hash_table_c/hash_table_c.h"

#define EPSILON 0.000001

TEST(TestHashTableCLib, can_create) {
    ASSERT_NO_THROW(HashTableC<int> table);
    ASSERT_NO_THROW(HashTableC<int> table(50));
}

TEST(TestHashTableCLib, can_insert) {
    HashTableC<int> table(6);
    table.insert("one", 1);
    table.insert("two", 2);
    table.insert("five", 5);
    table.insert("four", 4);
    table.insert("six", 6);
    table.insert("three", 3);
    EXPECT_FALSE(table.is_empty());
    // table.print();
}

TEST(TestHashTableCLib, throw_when_try_insert_same_key) {
    HashTableC<int> table;
    table.insert("one", 1);
    table.insert("two", 2);
    table.insert("five", 5);
    table.insert("four", 4);
    table.insert("six", 6);
    table.insert("three", 3);
    ASSERT_ANY_THROW(table.insert("six", 7));
}

TEST(TestHashTableCLib, can_find) {
    HashTableC<int> table;
    table.insert("one", 1);
    table.insert("two", 2);
    table.insert("five", 5);
    table.insert("four", 4);
    table.insert("six", 6);
    table.insert("three", 3);
    EXPECT_EQ(table.found("one"), 1);
    EXPECT_EQ(table.found("six"), 6);
}

TEST(TestHashTableCLib, throw_when_try_find_non_exist_key) {
    HashTableC<int> table(6);
    ASSERT_ANY_THROW(table.found("one"));
    table.insert("one", 1);
    table.insert("two", 2);
    table.insert("five", 5);
    table.insert("four", 4);
    table.insert("six", 6);
    table.insert("three", 3);
    ASSERT_ANY_THROW(table.found("seven"));
}

TEST(TestHashTableCLib, can_erase) {
    HashTableC<int> table;
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

TEST(TestHashTableCLib, throw_when_try_erase_non_exist_key) {
    HashTableC<int> table;
    ASSERT_ANY_THROW(table.erase("one"));
    table.insert("one", 1);
    table.insert("two", 2);
    table.insert("five", 5);
    table.insert("four", 4);
    table.insert("six", 6);
    ASSERT_ANY_THROW(table.erase("three"));
}

TEST(TestHashTableCLib, can_insert_with_collision) {
    HashTableC<int> table(20);
    table.insert("one", 1);
    table.insert("two", 2);
    table.insert("five", 5);
    table.insert("four", 4);
    table.insert("six", 6);
    table.insert("three", 3);
    table.insert("there", 10);
    EXPECT_EQ(10, table.found("there"));
}
