// Copyright 2026 Viktoria Buzlaeva

#include <gtest/gtest.h>
#include "../lib_polynom/polynom.h"

#define EPSILON 0.000001

TEST(TestPolynomLib, can_create_default) {
    Polynom polynom;
    EXPECT_EQ(polynom.to_string(), "0");
}

TEST(TestPolynomLib, can_create_with_monom) {
    Monom monom(5, { 2, 1, 0 });
    Polynom polynom(monom);

    EXPECT_EQ(polynom.to_string(), "5x^2y");
}

TEST(TestPolynomLib, can_create_with_string) {
    Polynom polynom_1("x + 0");
    EXPECT_EQ(polynom_1.to_string(), "x");

    Polynom polynom_2("-2x");
    EXPECT_EQ(polynom_2.to_string(), "-2x");

    Polynom polynom_3("1");
    EXPECT_EQ(polynom_3.to_string(), "1");

    Polynom polynom_4("x^2-3y+4");
    EXPECT_EQ(polynom_4.to_string(), "x^2 - 3y + 4");

    Polynom polynom_5("-3y+4 + x^2");
    EXPECT_EQ(polynom_5.to_string(), "x^2 - 3y + 4");

    Polynom polynom_6("x^2 -3y+4 + x^2");
    EXPECT_EQ(polynom_6.to_string(), "2x^2 - 3y + 4");
}

TEST(TestPolynomLib, throw_when_try_create_with_string) {
    ASSERT_ANY_THROW(Polynom(""));  // Пустая строка
    ASSERT_ANY_THROW(Polynom(" "));

    ASSERT_ANY_THROW(Polynom("x*y"));  // Недопустимые символы
    ASSERT_ANY_THROW(Polynom("x+a"));
    ASSERT_ANY_THROW(Polynom("1..2x"));

    ASSERT_ANY_THROW(Polynom("x^-1"));  // Некорректная степень
    ASSERT_ANY_THROW(Polynom("x^2.5"));

    ASSERT_ANY_THROW(Polynom("xx"));  // Одинаковые переменные в одном мономе
    ASSERT_ANY_THROW(Polynom("x^2x"));

    ASSERT_ANY_THROW(Polynom("+"));  // Некорректные знаки
    ASSERT_ANY_THROW(Polynom("-"));
    ASSERT_ANY_THROW(Polynom("--x"));
}

TEST(TestPolynomLib, can_create_with_copy) {
    Polynom polynom_1("x + y - z");
    Polynom polynom_2(polynom_1);

    EXPECT_EQ(polynom_1.to_string(), polynom_2.to_string());
}

TEST(TestPolynomLib, throw_when_try_create_copy) {
    Polynom* polynom_1 = NULL;

    ASSERT_ANY_THROW(Polynom polynom_2(*polynom_1));
}

TEST(TestPolynomLib, can_comp_correctly_with_eq_operator) {
    Polynom polynom_1("x + y - z");
    Polynom polynom_2("x + y - z");
    Polynom polynom_3("x^2-3y-z");

    EXPECT_TRUE(polynom_1 == polynom_2);
    EXPECT_FALSE(polynom_1 == polynom_3);
}

TEST(TestPolynomLib, can_comp_correctly_with_not_eq_operator) {
    Polynom polynom_1("x + y - z");
    Polynom polynom_2("x + y - z");
    Polynom polynom_3("x^2-3y");

    EXPECT_FALSE(polynom_1 != polynom_2);
    EXPECT_TRUE(polynom_1 != polynom_3);
}

TEST(TestPolynomLib, can_assign_correctly) {
    Polynom polynom_1("x^3 + 5.6y^4z^2 - z");

    Polynom polynom_2 = polynom_1;
    EXPECT_EQ(polynom_1.to_string(), polynom_2.to_string());
    EXPECT_EQ(polynom_1, polynom_2);
}

TEST(TestPolynomLib, can_add_polynom_correctly) {
    Polynom p_1("x^2 + 2x + y");
    Polynom p_2("x^2z^2 - y + 3");
    p_1 += p_2;

    Polynom p_3("x^2 + x^2z^2 + 2x + 3");
    EXPECT_EQ(p_1, p_3);

    Polynom p_4("x + y - 3x^2");
    Polynom p_5;
    Polynom p_6 = p_4 + p_5;

    Polynom p_7("-3x^2 + x + y");
    EXPECT_EQ(p_6, p_7);
}

TEST(TestPolynomLib, can_sub_polynom_correctly) {
    Polynom p_1("x + y");
    Polynom p_2("x - y");
    p_1 -= p_2;

    Polynom p_3("2y");
    EXPECT_EQ(p_1, p_3);

    Polynom p_4;
    Polynom p_5("x + y - 3x^2");
    Polynom p_6 = p_4 - p_5;

    Polynom p_7("3x^2 - x - y");
    EXPECT_EQ(p_6, p_7);
}

TEST(TestPolynomLib, can_mult_polynom_correctly) {
    Polynom p_1("4x^3 + y");
    Polynom p_2("2x^2 + xy + z");
    p_1 *= p_2;

    Polynom p_3("8x^5 + 4x^4y + 4x^3z + 2x^2y + xy^2 + yz");
    EXPECT_EQ(p_1, p_3);

    Polynom p_4("x + 1");
    Polynom p_5("x^2 + x + 1");
    Polynom p_6 = p_4 * p_5;

    Polynom p_7("x^3 + 2x^2 + 2x + 1");
    EXPECT_EQ(p_6, p_7);

    Polynom p_8("x^2 + x + 1");
    Polynom p_9;
    p_8 *= p_9;

    EXPECT_EQ(p_8, p_9);
}

TEST(TestPolynomLib, can_add_monom_correctly) {
    Polynom p_1("x + y");
    Monom m_1(2, { 1,0,0 });
    p_1 += m_1;

    Polynom p_2("3x + y");
    EXPECT_EQ(p_1, p_2);

    Polynom p_3("x - x");
    Monom m_2(1, { 1,0,0 });
    Polynom p_4 = p_3 + m_2;

    Polynom p_5("x");
    EXPECT_EQ(p_4, p_5);

    Polynom p_6("x + y");
    Monom m_3(3, { 2,0,0 });
    Polynom p_7 = m_3 + p_6;

    Polynom p_8("3x^2 + x + y");
    EXPECT_EQ(p_7, p_8);
}

TEST(TestPolynomLib, can_sub_monom_correctly) {
    Polynom p_1("x + y");
    Monom m_1(1, { 1,0,0 });
    p_1 -= m_1;

    Polynom p_2("y");
    EXPECT_EQ(p_1, p_2);

    Polynom p_3("x - x");
    Monom m_2(1, { 1,0,0 });
    Polynom p_4 = p_3 - m_2;

    Polynom p_5("-x");
    EXPECT_EQ(p_4, p_5);

    Polynom p_6("x + y");
    Monom m_3(3, { 2,0,0 });
    Polynom p_7 = m_3 - p_6;

    Polynom p_8("3x^2 - x - y");
    EXPECT_EQ(p_7, p_8);
}

TEST(TestPolynomLib, can_mult_monom_correctly) {
    Polynom p_1("x + y");
    Monom m_1(2, { 1,0,0 });
    p_1 *= m_1;

    Polynom p_2("2x^2 + 2xy");
    EXPECT_EQ(p_1, p_2);

    Polynom p_3("2xy - 2x^2z^3");
    Monom m_2(3, { 1,0,0 });
    Polynom p_4 = p_3 *m_2;

    Polynom p_5("-6x^3z^3 + 6x^2y");
    EXPECT_EQ(p_4, p_5);

    Polynom p_6("x + y");
    Monom m_3;
    Polynom p_7 = m_3 * p_6;

    Polynom p_8;
    EXPECT_EQ(p_7, p_8);
}

TEST(TestPolynomLib, can_div_monom_correctly) {
    Polynom p_1("4x^2 + 2x");
    Monom m_1(2, { 1,0,0 });
    p_1 /= m_1;

    Polynom p_2("2x + 1");
    EXPECT_EQ(p_1, p_2);

    Polynom p_3("2xy - 2x^2yz^3");
    Monom m_2(-4, { 0,1,0 });
    Polynom p_4 = p_3 / m_2;

    Polynom p_5("0.5x^2z^3 - 0.5x");
    EXPECT_EQ(p_4, p_5);
}

TEST(TestPolynomLib, throw_when_try_div_monom_by_zero) {
    Polynom p_1("4.2x^2 - 27.3y - 8.4z");
    Monom zero;

    ASSERT_ANY_THROW(p_1 /= zero);
    ASSERT_ANY_THROW(p_1 / zero);
}

TEST(TestPolynomLib, throw_when_try_div_monom_with_negative_power) {
    Polynom p_1("4.2x^2 - 26y");
    Monom monom(2, { 1,0,0 });

    ASSERT_ANY_THROW(p_1 /= monom);
    ASSERT_ANY_THROW(p_1 / monom);
}

TEST(TestPolynomLib, can_add_num_correctly) {
    Polynom p_1("x + y");
    double num_1 = 2;
    p_1 += num_1;

    Polynom p_2("x + y + 2");
    EXPECT_EQ(p_1, p_2);

    Polynom p_3("x + y");
    double num_2 = 0;
    Polynom p_4 = p_3 + num_2;

    Polynom p_5("x + y");
    EXPECT_EQ(p_4, p_5);

    Polynom p_6("x + y + 3");
    Monom num_3 = -3;
    Polynom p_7 = num_3 + p_6;

    Polynom p_8("x + y");
    EXPECT_EQ(p_7, p_8);
}

TEST(TestPolynomLib, can_sub_num_correctly) {
    Polynom p_1("x + y + 5");
    double num_1 = 2;
    p_1 -= num_1;

    Polynom p_2("x + y + 3");
    EXPECT_EQ(p_1, p_2);

    Polynom p_3("x + y");
    double num_2 = 0;
    Polynom p_4 = p_3 - num_2;

    Polynom p_5("x + y");
    EXPECT_EQ(p_4, p_5);

    Polynom p_6("x + y + 3");
    Monom num_3 = 3;
    Polynom p_7 = num_3 - p_6;

    Polynom p_8("-x - y");
    EXPECT_EQ(p_7, p_8);
}

TEST(TestPolynomLib, can_mult_num_correctly) {
    Polynom p_1("x^2 - 6.5y - 2z");
    double num_1 = 4.2;
    Polynom p_2("4.2x^2 - 27.3y - 8.4z");

    Polynom p_3 = p_1 * num_1;
    EXPECT_EQ(p_3, p_2);

    p_1 *= num_1;
    EXPECT_EQ(p_1, p_2);

    double num_2 = 0;
    Polynom p_4;
    p_1 = num_2 * p_2;
    EXPECT_EQ(p_1, p_4);
}

TEST(TestPolynomLib, can_div_num_correctly) {
    Polynom p_1("4.2x^2 - 27.3y - 8.4z");
    double num = 4.2;
    Polynom p_2("x^2 - 6.5y - 2z");

    Polynom p_3 = p_1 / num;
    p_1 /= num;
    EXPECT_EQ(p_1, p_2);
    EXPECT_EQ(p_3, p_2);
}

TEST(TestPolynomLib, throw_when_try_div_num_by_zero) {
    Polynom p_1("4.2x^2 - 27.3y - 8.4z");
    double num = 0;

    ASSERT_ANY_THROW(p_1 /= num);
    ASSERT_ANY_THROW(p_1 / num);
}

TEST(TestPolynomLib, check_operator_unar_minus) {
    Polynom polynom_1("-x - y + z");
    Polynom polynom_2("x + y - z");

    Polynom polynom_3(-polynom_2);
    EXPECT_EQ(polynom_1, polynom_3);
}

TEST(TestPolynomLib, can_calculate_value_in_point_correctly) {
    Polynom p("-6x^2z + 6x^2y");

    EXPECT_TRUE(48 == p.calculate_point(2, 2));
    EXPECT_TRUE(24 == p.calculate_point(2, 2, 1));
    EXPECT_TRUE(1.5 == p.calculate_point(0.5, 2, 1));
}
