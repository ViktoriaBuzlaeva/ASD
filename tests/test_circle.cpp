// Copyright 2025 Viktoria Buzlaeva

#include <gtest/gtest.h>
#include "../lib_circle/circle.h"

#define EPSILON 0.000001

TEST(TestCircleLib, can_create) {
	// Arrange

	// Act & Assert
	ASSERT_NO_THROW(Circle circle);
}

TEST(TestCircleLib, can_create_init) {
	// Arrange
	Point point(6, 2);
	int rad = 2;

	// Act & Assert
	ASSERT_NO_THROW(Circle circle(rad, point));
}

TEST(TestCircleLib, throw_when_create_with_incorrect_rad) {
	// Arrange
	Point point(6, 2);
	int rad = -2;

	// Act & Assert
	ASSERT_ANY_THROW(Circle circle(rad, point));
}

TEST(TestCircleLib, can_create_copy) {
	// Arrange
	Circle circle_1(3);

	// Act & Assert
	ASSERT_NO_THROW(Circle circle_2(circle_1));
}

TEST(TestCircleLib, can_comp_correctly_eq_circles) {
	// Arrange
	Circle circle_1(3);
	Circle circle_2(3);

	// Act & Assert
	EXPECT_TRUE(circle_1 == circle_2);
}

TEST(TestCircleLib, can_comp_correctly_not_eq_circles) {
	// Arrange
	Circle circle_1(3);
	Circle circle_2(4);

	// Act & Assert
	EXPECT_FALSE(circle_1 == circle_2);
}

TEST(TestCircleLib, can_comp_correctly_eq_circles_other) {
	// Arrange
	Circle circle_1(0, 3);
	Circle circle_2(0, 3);

	// Act & Assert
	EXPECT_FALSE(circle_1 != circle_2);
}

TEST(TestCircleLib, can_comp_correctly_not_eq_circles_other) {
	// Arrange
	Point point_1(0, 3);
	Point point_2(0, 4);
	Circle circle_1(3, point_1);
	Circle circle_2(3, point_2);

	// Act & Assert
	EXPECT_TRUE(circle_1 != circle_2);
}
