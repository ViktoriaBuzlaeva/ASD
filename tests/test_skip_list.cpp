// Copyright 2026 Viktoria Buzlaeva

#include <gtest/gtest.h>
#include "../lib_skip_list/skip_list.h"

#define EPSILON 0.000001

TEST(TestSkipListLib, can_create) {
    ASSERT_NO_THROW((SkipList<int, std::string>()));
    ASSERT_NO_THROW((SkipList<int, std::string>(10)));
}

TEST(TestSkipListLib, can_insert) {
    SkipList<int, std::string> sl;
    // sl.print();
    ASSERT_NO_THROW(sl.insert(1, "one"));
    ASSERT_NO_THROW(sl.insert(2, "two"));
    ASSERT_NO_THROW(sl.insert(5, "five"));
    ASSERT_NO_THROW(sl.insert(3, "three"));
    ASSERT_NO_THROW(sl.insert(4, "four"));
    // sl.print();
}

TEST(TestSkipListLib, throw_when_try_insert_same_key) {
    SkipList<int, std::string> sl;
    ASSERT_NO_THROW(sl.insert(1, "one"));
    ASSERT_NO_THROW(sl.insert(2, "two"));
    ASSERT_NO_THROW(sl.insert(5, "five"));
    ASSERT_NO_THROW(sl.insert(3, "three"));
    ASSERT_ANY_THROW(sl.insert(5, "four"));
}
