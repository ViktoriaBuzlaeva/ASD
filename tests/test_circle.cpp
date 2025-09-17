// Copyright 2025 Viktoria Buzlaeva

#include <gtest/gtest.h>
#include "../lib_circle/circle.h"

#define EPSILON 0.000001

TEST(TestCircleLib, can_create) {
	// Arrange & Act
	Circle circle;

	// Assert
	EXPECT_EQ(0, circle.cent().x());
	EXPECT_EQ(0, circle.cent().y());
	EXPECT_EQ(0, circle.rad());
}

TEST(TestCircleLib, can_create_init) {
	// Arrange & Act
	Circle circle(2, 6, 2);

	// Assert
	EXPECT_EQ(6, circle.cent().x());
	EXPECT_EQ(2, circle.cent().y());
	EXPECT_EQ(2, circle.rad());
}

TEST(TestCircleLib, throw_when_create_init_with_incorrect_rad) {
	// Arrange
	int x = 6;
	int y = 2;
	int rad = -2;

	// Act & Assert
	ASSERT_ANY_THROW(Circle circle(rad, x, y));
}

TEST(TestCircleLib, can_create_init_with_point) {
	// Arrange & Act
	Point cent(6, 2);
	Circle circle(2, cent);

	// Assert
	EXPECT_EQ(6, circle.cent().x());
	EXPECT_EQ(2, circle.cent().y());
	EXPECT_EQ(2, circle.rad());
}

TEST(TestCircleLib, throw_when_create_with_point_with_incorrect_rad) {
	// Arrange
	Point point(6, 2);
	int rad = -2;

	// Act & Assert
	ASSERT_ANY_THROW(Circle circle(rad, point));
}

TEST(TestCircleLib, can_create_copy) {
	// Arrange & Act
	Circle circle_1(3);
	Circle circle_2(circle_1);

	// Assert
	EXPECT_EQ(circle_2.cent(), circle_1.cent());
	EXPECT_EQ(circle_2.rad(), circle_1.rad());
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
	Circle circle_1(3);
	Circle circle_2(3);

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
