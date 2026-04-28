// Copyright 2026 Viktoria Buzlaeva

#include <gtest/gtest.h>
#include "../lib_avltree/avltree.h"

#define EPSILON 0.000001

TEST(TestAVLTreeLib, can_create) {
    ASSERT_NO_THROW((AVLTree<int, std::string>()));
}

TEST(TestAVLTreeLib, can_find) {
    AVLTree<int, std::string> t;
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

TEST(TestAVLTreeLib, can_insert_RR) {
    AVLTree<int, std::string> t;
    ASSERT_NO_THROW(t.insert(1, "one"));
    ASSERT_NO_THROW(t.insert(2, "two"));
    ASSERT_NO_THROW(t.insert(5, "five"));
    ASSERT_NO_THROW(t.insert(6, "six"));
    ASSERT_NO_THROW(t.insert(7, "seven"));
    ASSERT_NO_THROW(t.insert(8, "eight"));
    /*     6
          / \
         2   7
        / \   \
       1   5   8
    */
    EXPECT_EQ(t.root()->data.value, *(t.find(6)));
    EXPECT_EQ(t.root()->right->data.value, *(t.find(7)));
    EXPECT_EQ(t.root()->right->right->data.value, *(t.find(8)));
    EXPECT_EQ(t.root()->left->data.value, *(t.find(2)));
    EXPECT_EQ(t.root()->left->right->data.value, *(t.find(5)));
    EXPECT_EQ(t.root()->left->left->data.value, *(t.find(1)));
}

TEST(TestAVLTreeLib, can_insert_LL) {
    AVLTree<int, std::string> t;
    ASSERT_NO_THROW(t.insert(7, "seven"));
    ASSERT_NO_THROW(t.insert(6, "six"));
    ASSERT_NO_THROW(t.insert(5, "five"));
    ASSERT_NO_THROW(t.insert(3, "three"));
    ASSERT_NO_THROW(t.insert(2, "two"));
    ASSERT_NO_THROW(t.insert(1, "one"));
    /*     3
          / \
         2   6
        /   / \
       1   5   7
    */
    EXPECT_EQ(t.root()->data.value, *(t.find(3)));
    EXPECT_EQ(t.root()->right->data.value, *(t.find(6)));
    EXPECT_EQ(t.root()->right->right->data.value, *(t.find(7)));
    EXPECT_EQ(t.root()->right->left->data.value, *(t.find(5)));
    EXPECT_EQ(t.root()->left->data.value, *(t.find(2)));
    EXPECT_EQ(t.root()->left->left->data.value, *(t.find(1)));
}

TEST(TestAVLTreeLib, can_insert_RL) {
    AVLTree<int, std::string> t;
    ASSERT_NO_THROW(t.insert(2, "two"));
    ASSERT_NO_THROW(t.insert(5, "five"));
    ASSERT_NO_THROW(t.insert(3, "three"));
    ASSERT_NO_THROW(t.insert(9, "nine"));
    ASSERT_NO_THROW(t.insert(6, "six"));
    ASSERT_NO_THROW(t.insert(4, "four"));
    /*     5
          / \
         3   6
        / \   \
       2   4   9
    */
    EXPECT_EQ(t.root()->data.value, *(t.find(5)));
    EXPECT_EQ(t.root()->right->data.value, *(t.find(6)));
    EXPECT_EQ(t.root()->right->right->data.value, *(t.find(9)));
    EXPECT_EQ(t.root()->left->data.value, *(t.find(3)));
    EXPECT_EQ(t.root()->left->right->data.value, *(t.find(4)));
    EXPECT_EQ(t.root()->left->left->data.value, *(t.find(2)));
}

TEST(TestAVLTreeLib, can_insert_LR) {
    AVLTree<int, std::string> t;
    ASSERT_NO_THROW(t.insert(9, "nine"));
    ASSERT_NO_THROW(t.insert(5, "five"));
    ASSERT_NO_THROW(t.insert(7, "seven"));
    ASSERT_NO_THROW(t.insert(1, "one"));
    ASSERT_NO_THROW(t.insert(3, "three"));
    ASSERT_NO_THROW(t.insert(4, "four"));
    /*     5
          / \
         3   7
        / \   \
       1   4   9
    */
    EXPECT_EQ(t.root()->data.value, *(t.find(5)));
    EXPECT_EQ(t.root()->right->data.value, *(t.find(7)));
    EXPECT_EQ(t.root()->right->right->data.value, *(t.find(9)));
    EXPECT_EQ(t.root()->left->data.value, *(t.find(3)));
    EXPECT_EQ(t.root()->left->right->data.value, *(t.find(4)));
    EXPECT_EQ(t.root()->left->left->data.value, *(t.find(1)));
}

TEST(TestAVLTreeLib, can_insert_1) {
    AVLTree<int, std::string> t;
    ASSERT_NO_THROW(t.insert(1, "one"));
    ASSERT_NO_THROW(t.insert(2, "two"));
    ASSERT_NO_THROW(t.insert(5, "five"));
    ASSERT_NO_THROW(t.insert(3, "three"));
    ASSERT_NO_THROW(t.insert(4, "four"));
    ASSERT_NO_THROW(t.insert(6, "six"));
    ASSERT_NO_THROW(t.insert(8, "eight"));
    ASSERT_NO_THROW(t.insert(9, "nine"));
    ASSERT_NO_THROW(t.insert(77, "seven"));
    ASSERT_NO_THROW(t.insert(178, "one"));
    ASSERT_NO_THROW(t.insert(4654, "four"));
    ASSERT_NO_THROW(t.insert(935, "nine"));
    // t.print();
}

TEST(TestAVLTreeLib, can_insert_2) {
    AVLTree<int, int> t;
    for (int i = 1; i <= 100; i++) {
        t.insert(i, i);
    }
    ASSERT_NO_THROW(t.insert(0, 0));
    // t.print();
}

TEST(TestAVLTreeLib, can_insert_3) {
    AVLTree<int, int> t;
    for (int i = 99; i >= 0; i--) {
        t.insert(i, i);
    }
    ASSERT_NO_THROW(t.insert(100, 100));
    // t.print();
}

TEST(TestAVLTreeLib, can_insert_4) {
    AVLTree<int, int> t;
    for (int i = 50; i <= 99; i++) {
        t.insert(i, i);
    }
    for (int i = 49; i >= 0; i--) {
        t.insert(i, i);
    }
    ASSERT_NO_THROW(t.insert(100, 100));
    // t.print();
}

TEST(TestAVLTreeLib, can_insert_5) {
    AVLTree<int, int> t;
    for (int i = 50; i >= 1; i--) {
        t.insert(i, i);
    }
    for (int i = 51; i <= 100; i++) {
        t.insert(i, i);
    }
    ASSERT_NO_THROW(t.insert(0, 0));
    // t.print();
}

TEST(TestAVLTreeLib, throw_when_try_insert_same_key) {
    AVLTree<int, std::string> t;
    t.insert(1, "one");
    t.insert(2, "two");
    t.insert(5, "five");
    t.insert(3, "three");
    ASSERT_ANY_THROW(t.insert(1, "four"));
}

TEST(TestAVLTreeLib, can_check_empty) {
    AVLTree<int, std::string> t;
    EXPECT_TRUE(t.is_empty());

    t.insert(1, "one");
    EXPECT_FALSE(t.is_empty());
}

TEST(TestAVLTreeLib, can_clear) {
    AVLTree<int, std::string> t;
    t.insert(1, "one");
    t.insert(2, "two");
    t.insert(5, "five");
    t.insert(3, "three");
    t.insert(4, "four");

    t.clear();
    EXPECT_TRUE(t.is_empty());
}

TEST(TestAVLTreeLib, can_erase_with_LL_turn) {
    AVLTree<int, std::string> t;
    t.insert(1, "one");
    t.insert(2, "two");
    t.insert(5, "five");
    t.insert(6, "six");
    t.insert(7, "seven");
    t.insert(8, "eight");
    ASSERT_NO_THROW(t.erase(8));
    ASSERT_NO_THROW(t.erase(7));
    /*     6             6         2
          / \           /         / \
         2   7   -->   2   -->   1   6
        / \   \       / \           /
       1   5   8     1   5         5
    */
    EXPECT_EQ(t.root()->data.value, *(t.find(2)));
    EXPECT_EQ(t.root()->right->data.value, *(t.find(6)));
    EXPECT_EQ(t.root()->right->left->data.value, *(t.find(5)));
    EXPECT_EQ(t.root()->left->data.value, *(t.find(1)));
}

TEST(TestAVLTreeLib, can_insert_with_RR_turn) {
    AVLTree<int, std::string> t;
    t.insert(7, "seven");
    t.insert(6, "six");
    t.insert(5, "five");
    t.insert(3, "three");
    t.insert(2, "two");
    t.insert(1, "one");
    ASSERT_NO_THROW(t.erase(1));
    ASSERT_NO_THROW(t.erase(2));
    /*      3         3             6
           / \         \           / \
          2   6   -->   6   -->   3   7
         /   / \       / \         \
        1   5   7     5   7         5
    */
    EXPECT_EQ(t.root()->data.value, *(t.find(6)));
    EXPECT_EQ(t.root()->right->data.value, *(t.find(7)));
    EXPECT_EQ(t.root()->left->data.value, *(t.find(3)));
    EXPECT_EQ(t.root()->left->right->data.value, *(t.find(5)));
}

TEST(TestAVLTreeLib, can_erase_with_LR_turn) {
    AVLTree<int, std::string> t;
    t.insert(2, "two");
    t.insert(6, "six");
    t.insert(3, "three");
    t.insert(9, "nine");
    t.insert(7, "seven");
    t.insert(4, "four");
    t.insert(5, "five");
    ASSERT_NO_THROW(t.erase(9));
    /*     6             6             4
          / \           / \           / \
         3   7   -->   3   7   -->   3   6
        / \   \       / \           /   / \
       2   4   9     2   4         2   5   7
            \             \
             5             5
    */
    EXPECT_EQ(t.root()->data.value, *(t.find(4)));
    EXPECT_EQ(t.root()->right->data.value, *(t.find(6)));
    EXPECT_EQ(t.root()->right->right->data.value, *(t.find(7)));
    EXPECT_EQ(t.root()->right->left->data.value, *(t.find(5)));
    EXPECT_EQ(t.root()->left->data.value, *(t.find(3)));
    EXPECT_EQ(t.root()->left->left->data.value, *(t.find(2)));
}

TEST(TestAVLTreeLib, can_erase_with_RL_turn) {
    AVLTree<int, std::string> t;
    t.insert(9, "nine");
    t.insert(5, "five");
    t.insert(8, "eight");
    t.insert(1, "one");
    t.insert(3, "three");
    t.insert(7, "seven");
    t.insert(6, "six");
    ASSERT_NO_THROW(t.erase(1));
    /*     5             5             7
          / \           / \           / \
         3   8   -->   3   8   -->   5   8
        /   / \           / \       / \   \
       1   7   9         7   9     3   6   9
          /             /
         6             6
    */
    EXPECT_EQ(t.root()->data.value, *(t.find(7)));
    EXPECT_EQ(t.root()->right->data.value, *(t.find(8)));
    EXPECT_EQ(t.root()->right->right->data.value, *(t.find(9)));
    EXPECT_EQ(t.root()->left->data.value, *(t.find(5)));
    EXPECT_EQ(t.root()->left->right->data.value, *(t.find(6)));
    EXPECT_EQ(t.root()->left->left->data.value, *(t.find(3)));
}

TEST(TestAVLTreeLib, can_erase_1) {
    AVLTree<int, int> t;
    t.insert(2, 2);
    t.insert(15, 15);
    t.insert(3, 3);
    t.insert(35, 35);
    t.insert(30, 30);
    t.insert(7, 7);
    t.insert(9, 9);
    t.insert(16, 16);
    t.insert(5, 5);
    t.insert(1, 1);
    t.insert(40, 40);
    t.insert(4, 4);
    t.insert(6, 6);
    // t.print();
    ASSERT_NO_THROW(t.erase(3));  // Удаление узла с двумя детьми
    // t.print();
}

TEST(TestAVLTreeLib, can_erase_2) {
    AVLTree<int, int> t;
    t.insert(5, 5);
    t.insert(3, 3);
    t.insert(9, 9);
    t.insert(2, 2);
    t.insert(7, 7);
    t.insert(4, 4);
    t.insert(11, 11);
    t.insert(1, 1);
    t.insert(6, 6);
    t.insert(10, 10);
    t.insert(8, 8);
    t.insert(13, 13);
    t.insert(12, 12);
    // t.print();
    t.erase(4);  // Удаление листа
    // t.print();
    t.erase(7);
    t.erase(2);
    t.erase(9);
    t.erase(3);
    t.erase(5);
    t.erase(11);
    t.erase(6);
    t.erase(10);
    t.erase(8);
    t.erase(13);
    t.erase(12);
    t.erase(1);
    EXPECT_TRUE(t.is_empty());
}

TEST(TestAVLTreeLib, can_erase_3) {
    AVLTree<int, int> t;
    t.insert(10, 10);
    t.insert(5, 5);
    t.insert(15, 15);
    t.insert(3, 3);
    t.insert(7, 7);
    t.insert(13, 13);
    t.insert(18, 18);
    t.insert(1, 1);
    // t.print();
    ASSERT_NO_THROW(t.erase(10)); // Удаление корня
    // t.print();
}

TEST(TestAVLTreeLib, can_erase_4) {
    AVLTree<int, int> t;
    for (int i = 1; i <= 15; i++) t.insert(i, i);
    for (int i = 1; i <= 15; i++) {
        t.erase(i);
        // t.print();
        // std::cout << std::endl;
    }
    EXPECT_TRUE(t.is_empty());
}

TEST(TestAVLTreeLib, throw_when_try_erase_not_existing_key) {
    AVLTree<int, std::string> t;
    ASSERT_ANY_THROW(t.erase(6));
    t.insert(1, "one");
    t.insert(2, "two");
    t.insert(5, "five");
    t.insert(3, "three");
    t.insert(4, "four");
    ASSERT_ANY_THROW(t.erase(6));
}
