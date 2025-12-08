// Copyright 2025 Viktoria Buzlaeva

#include <gtest/gtest.h>
#include "../lib_expression/expression.h"

#define EPSILON 0.000001

TEST(TestExpressionLib, can_create_default) {
    Expression expr;

    EXPECT_EQ("", expr.get_expression());
}

TEST(TestExpressionLib, can_create_with_string) {
    Expression expr("2 + 3");

    EXPECT_EQ("2 + 3 ", expr.get_expression());
}

TEST(TestExpressionLib, can_create_with_lexems) {
    List<Lexem> lexems;
    lexems.push_back(Lexem("2", Constant, 2.0));
    lexems.push_back(Lexem("+", Operator, DBL_MAX, 1));
    lexems.push_back(Lexem("3", Constant, 3.0));

    Expression expr(lexems);

    EXPECT_EQ("2 + 3 ", expr.get_expression());
}

TEST(TestExpressionLib, can_calculate_correctly) {
    Expression expr_1("2 + 3");
    Expression expr_2("2 + 3 * 4");
    Expression expr_3("(2 + 3) * 4");
    Expression expr_4("2 ^ 3");
    Expression expr_5("|-5|");

    EXPECT_EQ(5, expr_1.calculate());
    EXPECT_EQ(14, expr_2.calculate());
    EXPECT_EQ(20, expr_3.calculate());
    EXPECT_EQ(8, expr_4.calculate());
    EXPECT_EQ(5, expr_5.calculate());
}

TEST(TestExpressionLib, can_get_empty_list_vars_correctly) {
    Expression expr("2 + 3");
    List<Lexem> vars = expr.get_list_vars();

    EXPECT_TRUE(vars.is_empty());
}

TEST(TestExpressionLib, can_get_not_empty_list_vars_correctly) {
    Expression expr("x + y * x");
    List<Lexem> vars = expr.get_list_vars();

    EXPECT_FALSE(vars.is_empty());
}

TEST(TestExpressionLib, can_set_variable_correctly) {
    Expression expr("x + 2 * x");

    expr.set_variable("x", 3);

    EXPECT_EQ(9, expr.calculate());
}

TEST(TestExpressionLib, can_throw_when_try_calculate_with_undefined_variables) {
    Expression expr("x + 2");

    EXPECT_ANY_THROW(expr.calculate());
}

TEST(TestExpressionLib, can_throw_when_try_calculate_with_division_by_zero) {
    Expression expr("5 / 0");

    EXPECT_ANY_THROW(expr.calculate());
}
