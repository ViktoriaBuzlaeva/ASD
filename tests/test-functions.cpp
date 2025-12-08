// Copyright 2025 Viktoria Buzlaeva

#include <gtest/gtest.h>
#include "../lib_functions/functions.h"

#define EPSILON 0.1
#define PI 3.14

TEST(TestFunctionsLib, check_my_abs) {
    EXPECT_EQ(5, Functions::my_abs(5));
    EXPECT_EQ(5, Functions::my_abs(-5));
    EXPECT_EQ(0, Functions::my_abs(0));
    EXPECT_NEAR(3.14, Functions::my_abs(-3.14), EPSILON);
}

TEST(TestFunctionsLib, check_my_sin) {
    EXPECT_NEAR(1.0, Functions::my_sin(PI / 2), EPSILON);
    EXPECT_NEAR(1.0, Functions::my_sin(5 * PI / 2), EPSILON);
    EXPECT_NEAR(0.0, Functions::my_sin(PI), EPSILON);

    EXPECT_NEAR(-1.0, Functions::my_sin(-PI / 2), EPSILON);
    EXPECT_NEAR(-0.5, Functions::my_sin(-PI / 6), EPSILON);

    EXPECT_NEAR(Functions::my_sin(50 * PI), Functions::my_sin(0.0), EPSILON);
}

TEST(TestFunctionsLib, check_my_cos) {
    EXPECT_NEAR(0.0, Functions::my_cos(PI / 2), EPSILON);
    EXPECT_NEAR(0.0, Functions::my_cos(5 * PI / 2), EPSILON);
    EXPECT_NEAR(1.0, Functions::my_cos(0.0), EPSILON);

    EXPECT_NEAR(0.0, Functions::my_cos(-PI / 2), EPSILON);
    EXPECT_NEAR(-1.0, Functions::my_cos(-PI), EPSILON);

    EXPECT_NEAR(Functions::my_cos(49 * PI), Functions::my_cos(PI), EPSILON);
}

TEST(TestFunctionsLib, check_my_tg) {
    EXPECT_NEAR(0.0, Functions::my_tg(0.0), EPSILON);
    EXPECT_NEAR(0.0, Functions::my_tg(PI), EPSILON);
    EXPECT_NEAR(1.0, Functions::my_tg(PI / 4), EPSILON);

    EXPECT_NEAR(0.0, Functions::my_tg(-PI), EPSILON);
    EXPECT_NEAR(-1.0, Functions::my_tg(-PI / 4), EPSILON);

    EXPECT_NEAR(Functions::my_tg(50 * PI), Functions::my_tg(PI), EPSILON);
}

TEST(TestFunctionsLib, check_throw_when_tg_undefined) {
    EXPECT_ANY_THROW(Functions::my_tg(PI / 2), std::logic_error);
}
