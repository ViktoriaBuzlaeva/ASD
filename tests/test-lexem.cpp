// Copyright 2025 Viktoria Buzlaeva

#include <gtest/gtest.h>
#include "../lib_lexem/lexem.h"
#include "../lib_functions/functions.h"

#define EPSILON 0.000001

TEST(TestLexemLib, can_create_default) {
    Lexem lexem;

    EXPECT_EQ("", lexem.name);
    EXPECT_EQ(Constant, lexem.type);
    EXPECT_EQ(DBL_MAX, lexem.value);
    EXPECT_EQ(-1, lexem.priority);
    EXPECT_EQ(nullptr, lexem.function);
}

TEST(TestLexemLib, can_create_init) {
    Lexem lexem("abs", Function, 0, 3, Functions::my_abs);

    EXPECT_EQ("abs", lexem.name);
    EXPECT_EQ(Function, lexem.type);
    EXPECT_EQ(0, lexem.value);
    EXPECT_EQ(3, lexem.priority);
    EXPECT_EQ(10, lexem.function(-10));
}

TEST(TestLexemLib, can_create_copy) {
    Lexem lexem_1("abs", Function, 0, 3, Functions::my_abs);
    Lexem lexem_2(lexem_1);

    EXPECT_EQ(lexem_1.name, lexem_2.name);
    EXPECT_EQ(lexem_1.type, lexem_2.type);
    EXPECT_EQ(lexem_1.value, lexem_2.value);
    EXPECT_EQ(lexem_1.priority, lexem_2.priority);
    EXPECT_EQ(lexem_1.function, lexem_2.function);
}

TEST(TestLexemLib, can_assign) {
    Lexem lexem_1("abs", Function, 0, 3, Functions::my_abs);
    Lexem lexem_2;

    lexem_2 = lexem_1;

    EXPECT_EQ(lexem_1.name, lexem_2.name);
    EXPECT_EQ(lexem_1.type, lexem_2.type);
    EXPECT_EQ(lexem_1.value, lexem_2.value);
    EXPECT_EQ(lexem_1.priority, lexem_2.priority);
    EXPECT_EQ(lexem_1.function, lexem_2.function);
}
