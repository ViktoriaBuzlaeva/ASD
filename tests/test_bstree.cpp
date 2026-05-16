// Copyright 2026 Viktoria Buzlaeva

#include <gtest/gtest.h>
#include "../lib_bstree/bstree.h"

#define EPSILON 0.000001

TEST(TestBSTreeLib, can_create) {
    ASSERT_NO_THROW((BSTree<int, std::string>()));
}

TEST(TestBSTreeLib, can_insert) {
    BSTree<int, std::string> t;
    ASSERT_NO_THROW(t.insert(6, "six"));
    ASSERT_NO_THROW(t.insert(8, "eight"));
    ASSERT_NO_THROW(t.insert(9, "nine"));
    ASSERT_NO_THROW(t.insert(4, "four"));
    ASSERT_NO_THROW(t.insert(7, "seven"));
    ASSERT_NO_THROW(t.insert(2, "two"));
    ASSERT_NO_THROW(t.insert(5, "five"));
    ASSERT_NO_THROW(t.insert(3, "three"));
    ASSERT_NO_THROW(t.insert(1, "one"));
    /*t.print();
    t.print_DLCR();
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

TEST(TestBSTreeLib, can_find) {
    BSTree<int, std::string> t;
    t.insert(1, "one");
    EXPECT_EQ("one", *(t.find(1)));
    EXPECT_EQ(nullptr, t.find(6));

    t.insert(2, "two");
    t.insert(5, "five");
    t.insert(3, "three");
    t.insert(4, "four");
    EXPECT_EQ("one", *(t.find(1)));
    EXPECT_EQ("five", *(t.find(5)));
    EXPECT_EQ(nullptr, t.find(6));
}

TEST(TestBSTreeLib, can_erase) {
    BSTree<int, std::string> t;
    t.insert(1, "one");
    t.insert(2, "two");
    t.insert(5, "five");
    t.insert(3, "three");
    t.insert(4, "four");

    t.erase(4); // нет предков
    EXPECT_EQ(nullptr, t.find(4));

    t.erase(5); // есть левый предок
    EXPECT_EQ(nullptr, t.find(5));
    EXPECT_EQ("three", *(t.find(3)));

    t.erase(2); // есть правый предок
    EXPECT_EQ(nullptr, t.find(2));
    EXPECT_EQ("three", *(t.find(3)));

    t.insert(8, "eight");
    t.insert(9, "nine");
    t.insert(4, "four");
    t.insert(6, "six");
    t.insert(5, "five");
    t.erase(8); // есть оба предка
    EXPECT_EQ(nullptr, t.find(8));
    EXPECT_EQ("five", *(t.find(5)));
    EXPECT_EQ("nine", *(t.find(9)));
}

TEST(TestBSTreeLib, can_erase_root) {
    BSTree<int, std::string> t;
    t.insert(1, "one");
    t.erase(1); // нет предков
    EXPECT_TRUE(t.is_empty());

    t.insert(1, "one");
    t.insert(2, "two");
    t.erase(1); // есть правый предок
    EXPECT_EQ(nullptr, t.find(1));
    EXPECT_EQ("two", *(t.find(2)));

    t.insert(1, "one");
    t.erase(2); // есть левый предок
    EXPECT_EQ(nullptr, t.find(2));
    EXPECT_EQ("one", *(t.find(1)));

    t.insert(2, "two");
    t.insert(3, "three");
    t.erase(1); // есть оба предка
    EXPECT_EQ(nullptr, t.find(1));
    EXPECT_EQ("two", *(t.find(2)));
    EXPECT_EQ("three", *(t.find(3)));
}

TEST(TestBSTreeLib, throw_when_try_erase_not_existing_key) {
    BSTree<int, std::string> t;
    ASSERT_ANY_THROW(t.erase(6));
    t.insert(1, "one");
    t.insert(2, "two");
    t.insert(5, "five");
    t.insert(3, "three");
    t.insert(4, "four");
    ASSERT_ANY_THROW(t.erase(6));
}
