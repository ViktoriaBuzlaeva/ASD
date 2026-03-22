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
    ASSERT_NO_THROW(t.insert(6, "six"));
    ASSERT_NO_THROW(t.insert(8, "eight"));
    ASSERT_NO_THROW(t.insert(9, "nine"));
    ASSERT_NO_THROW(t.insert(7, "seven"));
    /*t.print();
    t.print_w();
    std::cout << std::endl << "clr:";
    t.print_DCLR();
    std::cout << std::endl << "lcr:";
    t.print_DLCR();
    std::cout << std::endl << "lrc:";
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

TEST(TestTreeLib, can_find) {
    Tree<int, std::string> t;
    t.insert(1, "one");
    t.insert(2, "two");
    t.insert(5, "five");
    t.insert(3, "three");
    t.insert(4, "four");

    EXPECT_EQ("one", *(t.find(1)));
    EXPECT_EQ("five", *(t.find(5)));
    EXPECT_EQ(nullptr, t.find(6));
}

TEST(TestTreeLib, can_erase) {
    Tree<int, std::string> t;
    t.insert(1, "one");
    t.insert(2, "two");
    t.insert(5, "five");
    t.insert(3, "three");
    t.insert(4, "four");

    t.erase(4);
    EXPECT_EQ(nullptr, t.find(4));
    t.erase(1);
    EXPECT_EQ(nullptr, t.find(1));
    t.erase(2);
    t.erase(3);
    t.erase(5);
    EXPECT_TRUE(t.is_empty());
}

TEST(TestTreeLib, throw_when_try_erase_empty_tree) {
    Tree<int, std::string> t;
    ASSERT_ANY_THROW(t.erase(4));
}

TEST(TestTreeLib, throw_when_try_erase_not_existing_key) {
    Tree<int, std::string> t;
    t.insert(1, "one");
    t.insert(2, "two");
    t.insert(5, "five");
    t.insert(3, "three");
    t.insert(4, "four");

    ASSERT_ANY_THROW(t.erase(6));
}
