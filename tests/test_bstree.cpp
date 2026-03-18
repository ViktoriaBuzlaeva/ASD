// Copyright 2026 Viktoria Buzlaeva

#include <gtest/gtest.h>
#include "../lib_bstree/bstree.h"

#define EPSILON 0.000001

TEST(TestBSTreeLib, can_create) {
    ASSERT_NO_THROW((BSTree<int, std::string>()));
}

TEST(TestBSTreeLib, can_insert) {
    BSTree<int, std::string> t;
    ASSERT_NO_THROW(t.insert(100, "one"));
    ASSERT_NO_THROW(t.insert(2, "two"));
    ASSERT_NO_THROW(t.insert(5, "five"));
    ASSERT_NO_THROW(t.insert(3, "three"));
    ASSERT_NO_THROW(t.insert(4, "four"));
    /*t.print_DLCR();
    std::cout << std::endl;*/
}

TEST(TestBSTreeLib, throw_when_try_insert_same_key) {
    BSTree<int, std::string> t;
    t.insert(1, "one");
    t.insert(2, "two");
    t.insert(5, "five");
    t.insert(3, "three");
    ASSERT_ANY_THROW(t.insert(1, "four"));
}

TEST(TestBSTreeLib, can_check_empty) {
    BSTree<int, std::string> t;
    EXPECT_TRUE(t.is_empty());

    t.insert(1, "one");
    EXPECT_FALSE(t.is_empty());
}

TEST(TestBSTreeLib, can_clear) {
    BSTree<int, std::string> t;
    t.insert(1, "one");
    t.insert(2, "two");
    t.insert(5, "five");
    t.insert(3, "three");
    t.insert(4, "four");

    t.clear();
    EXPECT_TRUE(t.is_empty());
}
