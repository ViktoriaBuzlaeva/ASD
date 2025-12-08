// Copyright 2025 Viktoria Buzlaeva

#include <gtest/gtest.h>
#include "../lib_parser/parser.h"

#define EPSILON 0.000001

TEST(TestParserLib, can_parse_number_correctly) {
    List<Lexem> result = Parser::parse("123");

    auto it = result.begin();
    ASSERT_EQ("123", (*it).name);
    ASSERT_EQ(Constant, (*it).type);
    ASSERT_EQ(123, (*it).value);
}

TEST(TestParserLib, can_parse_decimal_number_correctly) {
    List<Lexem> result = Parser::parse("3.14");

    auto it = result.begin();
    ASSERT_EQ("3.14", (*it).name);
    ASSERT_EQ(Constant, (*it).type);
    ASSERT_EQ(3.14, (*it).value);
}

TEST(TestParserLib, can_parse_expression_correctly) {
    List<Lexem> result = Parser::parse("3 * 4");

    auto it = result.begin();
    ASSERT_EQ("3", (*it).name);
    ASSERT_EQ(Constant, (*it).type);
    ASSERT_EQ(3, (*it).value);
    it++;
    ASSERT_EQ("*", (*it).name);
    ASSERT_EQ(Operator, (*it).type);
    ASSERT_EQ(DBL_MAX, (*it).value);
    ASSERT_EQ(2, (*it).priority);
    it++;
    ASSERT_EQ("4", (*it).name);
    ASSERT_EQ(Constant, (*it).type);
    ASSERT_EQ(4, (*it).value);
}

TEST(TestParserLib, can_parse_unar_minus_correctly) {
    List<Lexem> result = Parser::parse("-5");

    auto it = result.begin();
    ASSERT_EQ("0", (*it).name);
    ASSERT_EQ(Constant, (*it).type);
    ASSERT_EQ(0, (*it).value);
    it++;
    ASSERT_EQ("-", (*it).name);
    ASSERT_EQ(Operator, (*it).type);
    ASSERT_EQ(1, (*it).priority);
    it++;
    ASSERT_EQ("5", (*it).name);
    ASSERT_EQ(Constant, (*it).type);
    ASSERT_EQ(5, (*it).value);
}

TEST(TestParserLib, can_parse_variable_correctly) {
    List<Lexem> result = Parser::parse("x");

    auto it = result.begin();
    ASSERT_EQ("x", (*it).name);
    ASSERT_EQ(Variable, (*it).type);
}

TEST(TestParserLib, can_parse_function_correctly) {
    List<Lexem> result = Parser::parse("sin(0)");

    auto it = result.begin();
    ASSERT_EQ("sin", (*it).name);
    ASSERT_EQ(Function, (*it).type);
    ASSERT_EQ(Functions::my_sin, (*it).function);
    it++;
    ASSERT_EQ("(", (*it).name);
    ASSERT_EQ(OpenBracket, (*it).type);
    it++;
    ASSERT_EQ("0", (*it).name);
    ASSERT_EQ(Constant, (*it).type);
    ASSERT_EQ(0, (*it).value);
    it++;
    ASSERT_EQ(")", (*it).name);
    ASSERT_EQ(ClosedBracket, (*it).type);
}

TEST(TestParserLib, can_parse_abs_correctly) {
    List<Lexem> result = Parser::parse("|-5|");

    auto it = result.begin();
    ASSERT_EQ("abs", (*it).name);
    ASSERT_EQ(Function, (*it).type);
    ASSERT_EQ(Functions::my_abs, (*it).function);
    it++;
    ASSERT_EQ("(", (*it).name);
    ASSERT_EQ(OpenBracket, (*it).type);
    it++;
    ASSERT_EQ("0", (*it).name);
    ASSERT_EQ(Constant, (*it).type);
    ASSERT_EQ(0, (*it).value);
    it++;
    ASSERT_EQ("-", (*it).name);
    ASSERT_EQ(Operator, (*it).type);
    ASSERT_EQ(1, (*it).priority);
    it++;
    ASSERT_EQ("5", (*it).name);
    ASSERT_EQ(Constant, (*it).type);
    ASSERT_EQ(5, (*it).value);
    it++;
    ASSERT_EQ(")", (*it).name);
    ASSERT_EQ(ClosedBracket, (*it).type);
}

TEST(TestParserLib, can_parse_correct_expressions) {
    std::string expr_1 = "3 * (15 + (x + y) * (2 * x - 7 * y^2))";
    std::string expr_2 = "-x * (-x + y) * (x - (-y))";

    ASSERT_NO_THROW(Parser::parse(expr_1));
    ASSERT_NO_THROW(Parser::parse(expr_2));
}

TEST(TestParserLib, can_throw_when_parse_uncorrect_expression_1) {
    std::string expr = "3 * (15 + (x y) * (2 * x - 7 * y^2))";

    ASSERT_ANY_THROW(Parser::parse(expr));
}

TEST(TestParserLib, can_throw_when_parse_uncorrect_expression_2) {
    std::string expr = "3 * (15 + (x + y) * (2 * x - 7 * y^))";

    ASSERT_ANY_THROW(Parser::parse(expr));
}

TEST(TestParserLib, can_throw_when_parse_uncorrect_expression_3) {
    std::string expr = "((x + y) * (x - y)";

    ASSERT_ANY_THROW(Parser::parse(expr));
}

TEST(TestParserLib, can_throw_when_parse_uncorrect_expression_4) {
    std::string expr = "3 * 15 + (x + y) *";

    ASSERT_ANY_THROW(Parser::parse(expr));
}

TEST(TestParserLib, can_throw_when_parse_uncorrect_expression_5) {
    std::string expr = "* (15 + (x + y) * (2 * x - 7 * y^2))";

    ASSERT_ANY_THROW(Parser::parse(expr));
}

TEST(TestParserLib, can_throw_when_parse_uncorrect_expression_6) {
    std::string expr = "(x + y) * (x - y))";

    ASSERT_ANY_THROW(Parser::parse(expr));
}

TEST(TestParserLib, can_throw_when_parse_uncorrect_expression_7) {
    std::string expr_1 = "(x + * y) * (x - y)";
    std::string expr_2 = "(x + -y) * (x - y)";

    ASSERT_ANY_THROW(Parser::parse(expr_1));
    ASSERT_ANY_THROW(Parser::parse(expr_2));
}

TEST(TestParserLib, can_throw_when_parse_uncorrect_expression_8) {
    std::string expr = "(x + y) & (x - y)";

    ASSERT_ANY_THROW(Parser::parse(expr));
}

TEST(TestParserLib, can_throw_when_parse_uncorrect_expression_9) {
    std::string expression = "";

    EXPECT_ANY_THROW(Parser::parse(expression));
}

TEST(TestParserLib, can_throw_when_parse_uncorrect_expression_10) {
    std::string expression = "(2+3]";

    EXPECT_ANY_THROW(Parser::parse(expression));
}

TEST(TestParserLib, can_throw_when_parse_uncorrect_expression_11) {
    std::string expression = "|2+3";

    EXPECT_ANY_THROW(Parser::parse(expression));
}
