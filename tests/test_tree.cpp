// Copyright 2026 Viktoria Buzlaeva

#include <gtest/gtest.h>
#include "../lib_tree/tree.h"

#define EPSILON 0.000001

TEST(TestTreeLib, can_create) {
    ASSERT_NO_THROW((Tree<int, std::string>()));
}

TEST(TestTreeLib, can_insert) {
    Tree<int, std::string> t;
    ASSERT_NO_THROW(t.insert(1, "one"));
    ASSERT_NO_THROW(t.insert(2, "two"));
    ASSERT_NO_THROW(t.insert(5, "five"));
    ASSERT_NO_THROW(t.insert(3, "three"));
    ASSERT_NO_THROW(t.insert(4, "four"));
    /*t.print_w();
    std::cout << std::endl;
    t.print_DCLR();
    std::cout << std::endl;
    t.print_DLCR();
    std::cout << std::endl;
    t.print_DLRC();
    std::cout << std::endl;*/
}

TEST(TestTreeLib, can_check_empty) {
    Tree<int, std::string> t;
    EXPECT_TRUE(t.is_empty());

    t.insert(1, "one");
    EXPECT_FALSE(t.is_empty());
}

TEST(TestTreeLib, can_clear) {
    Tree<int, std::string> t;
    t.insert(1, "one");
    t.insert(2, "two");
    t.insert(5, "five");
    t.insert(3, "three");
    t.insert(4, "four");

    t.clear();
    EXPECT_TRUE(t.is_empty());
}
