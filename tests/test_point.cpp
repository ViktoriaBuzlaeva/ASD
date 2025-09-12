// Copyright 2025 Viktoria Buzlaeva

#include <gtest/gtest.h>
#include "../lib_point/point.h"

#define EPSILON 0.000001

TEST(TestPointLib, can_create) {
	// Arrange

	// Act & Assert
	ASSERT_NO_THROW(Point point_1);
}

TEST(TestPointLib, can_create_init) {
	// Arrange
	int x = 6;
	int y = 2;

	// Act & Assert
	ASSERT_NO_THROW(Point point(x, y));
}

TEST(TestPointLib, can_create_copy) {
	// Arrange
	Point point_1(2, 3);

	// Act & Assert
	ASSERT_NO_THROW(Point point_2(point_1));
}

TEST(TestPointLib, can_comp_correctly_eq_points) {
	// Arrange
	Point point_1(0, 3);
	Point point_2(0, 3);

	// Act & Assert
	EXPECT_TRUE(point_1 == point_2);
}

TEST(TestPointLib, can_comp_correctly_not_eq_points) {
	// Arrange
	Point point_1(0, 3);
	Point point_2(0, 4);

	// Act & Assert
	EXPECT_FALSE(point_1 == point_2);
}

TEST(TestPointLib, can_comp_correctly_eq_points_other) {
	// Arrange
	Point point_1(0, 3);
	Point point_2(0, 3);

	// Act & Assert
	EXPECT_FALSE(point_1 != point_2);
}

TEST(TestPointLib, can_comp_correctly_not_eq_points_other) {
	// Arrange
	Point point_1(0, 3);
	Point point_2(0, 4);

	// Act & Assert
	EXPECT_TRUE(point_1 != point_2);
}

TEST(TestPointLib, can_find_correctly_dis_y) {
	// Arrange
	Point point_1(0, 0);
	Point point_2(0, 3);

	// Act
	float actual_result = point_1.find_distance(point_2);

	// Assert
	float expected_result = 3;
	EXPECT_EQ(expected_result, actual_result);
}

TEST(TestPointLib, can_find_correctly_dis_x) {
	// Arrange
	Point point_1(0, 0);
	Point point_2(4.6 , 0);

	// Act
	float actual_result = point_1.find_distance(point_2);

	// Assert
	float expected_result = 4.6;
	EXPECT_EQ(expected_result, actual_result);
}

TEST(TestPointLib, can_find_correctly_dis) {
	// Arrange
	Point point_1(0, 3);
	Point point_2(4, 0);

	// Act
	float actual_result = point_1.find_distance(point_2);

	// Assert
	float expected_result = 5;
	EXPECT_EQ(expected_result, actual_result);
}

TEST(TestPointLib, can_find_correctly_dis_eq_points) {
	// Arrange
	Point point_1(0, 4);
	Point point_2(0, 4);

	// Act
	float actual_result = point_1.find_distance(point_2);

	// Assert
	float expected_result = 0;
	EXPECT_EQ(expected_result, actual_result);
}
