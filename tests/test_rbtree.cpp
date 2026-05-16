// Copyright 2026 Viktoria Buzlaeva

#include <gtest/gtest.h>
#include "../lib_rbtree/rbtree.h"

#define EPSILON 0.000001

TEST(TestRBTreeLib, can_create) {
    ASSERT_NO_THROW((RBTree<int, std::string>()));
}

TEST(TestRBTreeLib, can_find) {
    RBTree<int, std::string> t;
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

TEST(TestRBTreeLib, can_insert_correctly) {
    RBTree<int, std::string> t;
    ASSERT_NO_THROW(t.insert(50, "50"));
    ASSERT_NO_THROW(t.insert(25, "25"));
    ASSERT_NO_THROW(t.insert(75, "75"));
    ASSERT_NO_THROW(t.insert(10, "10"));
    /*
             [50]            [50]
             /  \            /  \
          (25)  (75)  ->  [25]  [75]
          /               /
       (10)            (10)
    */
    EXPECT_EQ(t.root()->color, Black);
    EXPECT_EQ(t.root()->right->color, Black);
    EXPECT_EQ(t.root()->left->color, Black);
    EXPECT_EQ(t.root()->left->left->color, Red);
    EXPECT_EQ(t.root()->data.key, 50);
    EXPECT_EQ(t.root()->right->data.key, 75);
    EXPECT_EQ(t.root()->left->data.key, 25);
    EXPECT_EQ(t.root()->left->left->data.key, 10);
}

TEST(TestRBTreeLib, can_insert_with_multiple_recolors) {
    RBTree<int, std::string> t;
    t.insert(50, "50");
    t.insert(25, "25");
    t.insert(75, "75");
    t.insert(6, "6");
    t.insert(37, "37");
    t.insert(3, "3");
    t.insert(13, "13");
    t.insert(66, "66");
    t.insert(88, "88");
    t.insert(70, "70");
    /*
                   [50]                          [50]
                 /       \                     /       \
              (25)        (75)              [25]        [75]
              /  \        /  \              /  \        /  \
            [6]  [37]  [66]   [88] ->     (6)  [37]  [66]   [88]
           /   \          \              /   \          \
         (3)   (13)       (70)         [3]   [13]       (70)
        /                              /
      (2)                            (2)
    */
    t.insert(2, "2");
    EXPECT_EQ(t.root()->right->color, Black);
    EXPECT_EQ(t.root()->left->color, Black);

    EXPECT_EQ(t.root()->left->left->color, Red);
    EXPECT_EQ(t.root()->left->left->left->color, Black);
    EXPECT_EQ(t.root()->left->left->right->color, Black);
}

TEST(TestRBTreeLib, can_insert_with_rotations) {
    RBTree<int, std::string> t;
    t.insert(15, "13");
    t.insert(25, "25");
    t.insert(63, "63");
    /*
       [15]          [25]
         \           /  \
         (25)  -> (15)  (63)
           \
           (63)
    */
    EXPECT_EQ(t.root()->color, Black);
    EXPECT_EQ(t.root()->right->color, Red);
    EXPECT_EQ(t.root()->left->color, Red);

    EXPECT_EQ(t.root()->data.key, 25);
    EXPECT_EQ(t.root()->right->data.key, 63);
    EXPECT_EQ(t.root()->left->data.key, 15);

    t.insert(9, "9");
    t.insert(70, "70");
    t.insert(60, "60");
    /*
            [25]                   [25]
           /    \                /      \
        [15]    [63]    ->   [13]        [63]
        /       /  \         /  \        /  \
      (9)    (60)  (70)    (9)  (15)  (60)  (70)
        \
        (13)
    */
    t.insert(13, "13");
    EXPECT_EQ(t.root()->left->color, Black);
    EXPECT_EQ(t.root()->left->right->color, Red);

    EXPECT_EQ(t.root()->left->data.key, 13);
    EXPECT_EQ(t.root()->left->left->data.key, 9);
    EXPECT_EQ(t.root()->left->right->data.key, 15);
}

TEST(TestRBTreeLib, can_insert_with_rotation_after_recolor) {
    RBTree<int, std::string> t;
    t.insert(50, "50");
    t.insert(25, "25");
    t.insert(75, "75");
    t.insert(6, "6");
    t.insert(37, "37");
    t.insert(3, "3");
    t.insert(13, "13");
    /*
                 [50]                    [25]
                /    \                 /      \
             (25)    [75]           (6)        (50)
             /  \                  /   \       /   \
           [6]  [37]       ->    [3]   [13] [37]   [75]
          /   \                 /
        (3)   (13)            (2)
        /
      (2)
    */
    t.insert(2, "2");

    EXPECT_EQ(t.root()->data.key, 25);
    EXPECT_EQ(t.root()->right->data.key, 50);
    EXPECT_EQ(t.root()->right->left->data.key, 37);
    EXPECT_EQ(t.root()->left->data.key, 6);

    EXPECT_EQ(t.root()->color, Black);
    EXPECT_EQ(t.root()->right->color, Red);
    EXPECT_EQ(t.root()->left->color, Red);
    EXPECT_EQ(t.root()->left->left->color, Black);
    EXPECT_EQ(t.root()->left->right->color, Black);
}

TEST(TestRBTreeLib, throw_when_try_insert_same_key) {
    RBTree<int, std::string> t;
    t.insert(1, "one");
    t.insert(2, "two");
    t.insert(5, "five");
    t.insert(3, "three");
    ASSERT_ANY_THROW(t.insert(1, "four"));
}

TEST(TestRBTreeLib, can_check_empty) {
    RBTree<int, std::string> t;
    EXPECT_TRUE(t.is_empty());

    t.insert(1, "one");
    EXPECT_FALSE(t.is_empty());
}

TEST(TestRBTreeLib, can_clear) {
    RBTree<int, std::string> t;
    t.insert(1, "one");
    t.insert(2, "two");
    t.insert(5, "five");
    t.insert(3, "three");
    t.insert(4, "four");

    t.clear();
    EXPECT_TRUE(t.is_empty());
}
