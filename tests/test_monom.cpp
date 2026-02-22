// Copyright 2026 Viktoria Buzlaeva

#include <gtest/gtest.h>
#include "../lib_monom/monom.h"

#define EPSILON 0.000001

TEST(TestMonomLib, can_create_with_coeff) {
    ASSERT_NO_THROW(Monom monom_1);
    ASSERT_NO_THROW(Monom monom_2(-2));
    ASSERT_NO_THROW(Monom monom_3(5.67));
}

TEST(TestMonomLib, can_create_with_powers) {
    int powers_1[] = { 1, 2, 3 };
    ASSERT_NO_THROW(Monom monom_1(-2, powers_1));
    int powers_2[] = { 1, -2, 3 };
    ASSERT_ANY_THROW(Monom monom_2(-2, powers_2));

    ASSERT_NO_THROW(Monom monom_3(5.67, {0, 0, 3}));
    ASSERT_ANY_THROW(Monom monom_4(-5.67, {2, 4, 5, 6}));
    ASSERT_ANY_THROW(Monom monom_4(-5.67, { 2, 4, -5}));
}

TEST(TestMonomLib, can_create_copy) {
    Monom monom_1(5.67, { 0, 0, 3 });
    ASSERT_NO_THROW(Monom monom_2(monom_1));

    Monom* monom_3 = NULL;
    ASSERT_ANY_THROW(Monom monom_4(*monom_3));
}

TEST(TestMonomLib, can_comp_correctly_with_eq_operator) {
    Monom monom_1(5.67, { 0, 0, 3 });
    Monom monom_2(5, { 0, 0, 3 });
    Monom monom_3(5.67, { 1, 2, 3 });

    EXPECT_TRUE(monom_1 == monom_2);
    EXPECT_FALSE(monom_1 == monom_3);
}

TEST(TestMonomLib, can_comp_correctly_with_not_eq_operator) {
    Monom monom_1(5.67, { 0, 0, 3 });
    Monom monom_2(5, { 0, 0, 3 });
    Monom monom_3(5.67, { 1, 2, 3 });

    EXPECT_FALSE(monom_1 != monom_2);
    EXPECT_TRUE(monom_1 != monom_3);
}

TEST(TestMonomLib, can_comp_correctly_with_greater_operator) {
    Monom monom_x(1, { 1, 0, 0 });
    Monom monom_y(1, { 0, 1, 0 });
    Monom monom_z(1, { 0, 0, 1 });

    Monom monom_1(5, { 0, 2, 2 });
    Monom monom_2(5, { 0, 2, 1 });

    EXPECT_TRUE(monom_y > monom_x);
    EXPECT_TRUE(monom_z > monom_y);
    EXPECT_TRUE(monom_z > monom_x);

    EXPECT_TRUE(monom_1 > monom_x);
    EXPECT_TRUE(monom_2 > monom_1);
    EXPECT_TRUE(monom_2 > monom_x);
    EXPECT_TRUE(monom_z > monom_2);
    EXPECT_TRUE(monom_z > monom_1);
}

TEST(TestMonomLib, can_comp_correctly_with_less_operator) {
    Monom monom_x(1, { 1, 0, 0 });
    Monom monom_y(1, { 0, 1, 0 });
    Monom monom_z(1, { 0, 0, 1 });

    Monom monom_1(5, { 0, 2, 2 });
    Monom monom_2(5, { 0, 2, 1 });

    EXPECT_TRUE(monom_x < monom_1);
    EXPECT_TRUE(monom_1 < monom_2);
    EXPECT_TRUE(monom_x < monom_2);
    EXPECT_TRUE(monom_2 < monom_z);
    EXPECT_TRUE(monom_1 < monom_z);
}

TEST(TestMonomLib, can_assign_correctly) {
    Monom monom_1(5.67, { 0, 0, 3 });
    Monom monom_2(5, { 1, 2, 3 });

    monom_2 = monom_1;
    EXPECT_TRUE(monom_1 == monom_2);
}

TEST(TestMonomLib, can_add_with_assign_correctly) {
    Monom monom_1(5.67, { 1, 2, 3 });
    Monom monom_2(4.33, { 1, 2, 3 });
    Monom monom_3(10, { 1, 2, 3 });

    monom_1 += monom_2;
    EXPECT_TRUE(monom_1 == monom_3);
}

TEST(TestMonomLib, throw_when_try_add_with_assign_not_similar_monoms) {
    Monom monom_1(5, { 1, 2, 3 });
    Monom monom_2(0, { 0, 0, 3 });

    ASSERT_ANY_THROW(monom_1 += monom_2);
}

TEST(TestMonomLib, can_sub_with_assign_correctly) {
    Monom monom_1(5.67, { 1, 2, 3 });
    Monom monom_2(4.33, { 1, 2, 3 });
    Monom monom_3(10, { 1, 2, 3 });

    monom_3 -= monom_2;
    EXPECT_TRUE(monom_1 == monom_3);
}

TEST(TestMonomLib, throw_when_try_sub_with_assign_not_similar_monoms) {
    Monom monom_1(5, { 1, 2, 3 });
    Monom monom_2(0, { 0, 0, 3 });

    ASSERT_ANY_THROW(monom_1 -= monom_2);
}

TEST(TestMonomLib, can_mult_with_assign_correctly) {
    Monom monom_1(5, { 1, 2, 3 });
    Monom monom_2(4, { 0, 0, 3 });
    Monom monom_3(20, { 1, 2, 6 });

    monom_1 *= monom_2;
    EXPECT_TRUE(monom_1 == monom_3);
}

TEST(TestMonomLib, can_div_with_assign_correctly) {
    Monom monom_1(5, { 1, 2, 3 });
    Monom monom_2(4, { 0, 0, 3 });
    Monom monom_3(20, { 1, 2, 6 });

    monom_3 /= monom_2;
    EXPECT_TRUE(monom_1 == monom_3);
}

TEST(TestMonomLib, throw_when_try_div_with_greater_powers) {
    Monom monom_1(5, { 1, 2, 3 });
    Monom monom_2(4, { 2, 0, 3 });

    ASSERT_ANY_THROW(monom_1 /= monom_2);
}

TEST(TestMonomLib, throw_when_try_div_with_assign_by_zero) {
    Monom monom_1(5, { 1, 2, 3 });
    Monom monom_2(0, { 0, 0, 3 });

    ASSERT_ANY_THROW(monom_1 /= monom_2);
}

TEST(TestMonomLib, can_mult_num_with_assign_correctly) {
    Monom monom_1(5, { 1, 2, 3 });
    double num = 4.2;
    Monom monom_2(21, { 1, 2, 3 });

    monom_1 *= num;
    EXPECT_TRUE(monom_1 == monom_2);
}

TEST(TestMonomLib, can_div_num_with_assign_correctly) {
    Monom monom_1(5, { 1, 2, 3 });
    double num = 4.2;
    Monom monom_2(21, { 1, 2, 3 });

    monom_2 /= num;
    EXPECT_TRUE(monom_1 == monom_2);
}

TEST(TestMonomLib, throw_when_try_div_num_with_assign_by_zero) {
    Monom monom_1(5, { 1, 2, 3 });
    double num = 0;

    ASSERT_ANY_THROW(monom_1 /= num);
}

TEST(TestMonomLib, can_add_correctly) {
    Monom monom_1(5.67, { 1, 2, 3 });
    Monom monom_2(4.33, { 1, 2, 3 });
    Monom monom_3(10, { 1, 2, 3 });

    Monom monom_4 = monom_1 + monom_2;
    EXPECT_TRUE(monom_3 == monom_4);
}

TEST(TestMonomLib, throw_when_try_add_not_similar_monoms) {
    Monom monom_1(5, { 1, 2, 3 });
    Monom monom_2(0, { 0, 0, 3 });

    ASSERT_ANY_THROW(monom_1 + monom_2);
}

TEST(TestMonomLib, can_sub_correctly) {
    Monom monom_1(5.67, { 1, 2, 3 });
    Monom monom_2(4.33, { 1, 2, 3 });
    Monom monom_3(10, { 1, 2, 3 });

    Monom monom_4 = monom_3 - monom_2;
    EXPECT_TRUE(monom_1 == monom_4);
}

TEST(TestMonomLib, throw_when_try_sub_not_similar_monoms) {
    Monom monom_1(5, { 1, 2, 3 });
    Monom monom_2(0, { 0, 0, 3 });

    ASSERT_ANY_THROW(monom_1 - monom_2);
}

TEST(TestMonomLib, can_mult_correctly) {
    Monom monom_1(5, { 1, 2, 3 });
    Monom monom_2(4, { 0, 0, 3 });
    Monom monom_3(20, { 1, 2, 6 });

    Monom monom_4 = monom_1 * monom_2;
    EXPECT_TRUE(monom_3 == monom_4);
}

TEST(TestMonomLib, can_div_correctly) {
    Monom monom_1(5, { 0, 0, 3 });
    Monom monom_2(4, { 2, 2, 3 });
    Monom monom_3(20, { 2, 2, 6 });

    Monom monom_4 = monom_3 / monom_2;
    EXPECT_TRUE(monom_1 == monom_4);
}

TEST(TestMonomLib, throw_when_try_div_by_zero) {
    Monom monom_1(5, { 1, 2, 3 });
    Monom monom_2(0, { 0, 0, 3 });

    ASSERT_ANY_THROW(monom_1 / monom_2);
}

TEST(TestMonomLib, can_mult_num_correctly) {
    Monom monom_1(5, { 1, 2, 3 });
    double num = 4.2;
    Monom monom_2(21, { 1, 2, 3 });

    Monom monom_3 = monom_1 * num;
    Monom monom_4 = num * monom_1;
    EXPECT_TRUE(monom_2 == monom_3);
    EXPECT_TRUE(monom_2 == monom_4);
}

TEST(TestMonomLib, can_div_num_correctly) {
    Monom monom_1(5, { 1, 0, 3 });
    double num = 4.2;
    Monom monom_2(21, { 1, 0, 3 });

    Monom monom_3 = monom_2 / num;
    EXPECT_TRUE(monom_1 == monom_3);
}

TEST(TestMonomLib, throw_when_try_div_num_by_zero) {
    Monom monom_1(5, { 1, 2, 3 });
    double num = 0;

    ASSERT_ANY_THROW(monom_1 / num);
}

TEST(TestMonomLib, check_operator_unar_minus) {
    Monom monom_1(5, { 1, 0, 3 });
    Monom monom_2(0, { 1, 0, 3 });
    Monom monom_3(-5, { 1, 0, 3 });

    Monom monom_4 = -monom_1;
    Monom monom_5 = -monom_2;
    EXPECT_TRUE(monom_3 == monom_4);
    EXPECT_TRUE(monom_2 == monom_5);
}

TEST(TestMonomLib, can_calculate_value_in_point_correctly) {
    Monom monom(5, { 1, 2, 3 });

    EXPECT_TRUE(0 == monom.calculate_point(2, 2));
    EXPECT_TRUE(40 == monom.calculate_point(2, 2, 1));
    EXPECT_TRUE(70 == monom.calculate_point(3.5, 2, 1));
}
