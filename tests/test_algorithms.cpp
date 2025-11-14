// Copyright 2025 Viktoria Buzlaeva

#include <gtest/gtest.h>
#include "../lib_algorithms/algorithms.h"
#include "../lib_circle/circle.h"
#include "../lib_sphere/sphere.h"

#define EPSILON 0.000001

TEST(TestAlgorithmsLib, can_determine_coincide_circles) {
	// Arrange
	Circle circle(2, 3, 3);

	// Act
	TypeOfCrossing res = find_type_of_crossing(circle, circle);

	// Assert
	EXPECT_EQ(Coincide, res);
}

TEST(TestAlgorithmsLib, can_determine_not_intersect_circles) {
	// Arrange
	Circle circle1(2, 0, 3);
	Circle circle2(2, 8, 3);

	// Act
	TypeOfCrossing res = find_type_of_crossing(circle1, circle2);

	// Assert
	EXPECT_EQ(NotIntersect, res);
}

TEST(TestAlgorithmsLib, can_determine_intersect_circles) {
	// Arrange
	Circle circle1(3, 1, 2);
	Circle circle2(3, 3, 3);

	// Act
	TypeOfCrossing res = find_type_of_crossing(circle1, circle2);

	// Assert
	EXPECT_EQ(Intersect, res);
}

TEST(TestAlgorithmsLib, can_determine_touch_circles) {
	// Arrange
	Circle circle1(1, 3, 0);
	Circle circle2(1, 3, 2);

	// Act
	TypeOfCrossing res = find_type_of_crossing(circle1, circle2);

	// Assert
	EXPECT_EQ(Touch, res);
}

TEST(TestAlgorithmsLib, can_determine_coincide_spheres) {
	// Arrange
	Sphere sphere(2, 3, 3, 3);

	// Act
	TypeOfCrossing res = find_type_of_crossing(sphere, sphere);

	// Assert
	EXPECT_EQ(Coincide, res);
}

TEST(TestAlgorithmsLib, can_determine_not_intersect_spheres) {
	// Arrange
	Sphere sphere1(2, 0, 3, 8);
	Sphere sphere2(2, 8, 3, 9);

	// Act
	TypeOfCrossing res = find_type_of_crossing(sphere1, sphere2);

	// Assert
	EXPECT_EQ(NotIntersect, res);
}

TEST(TestAlgorithmsLib, can_determine_intersect_spheres) {
	// Arrange
	Sphere sphere1(3, 1, 2, 8);
	Sphere sphere2(3, 3, 3, 7);

	// Act
	TypeOfCrossing res = find_type_of_crossing(sphere1, sphere2);

	// Assert
	EXPECT_EQ(Intersect, res);
}

TEST(TestAlgorithmsLib, can_determine_touch_spheres) {
	// Arrange
	Sphere sphere1(1, 3, 0, 4);
	Sphere sphere2(1, 3, 2, 4);

	// Act
	TypeOfCrossing res = find_type_of_crossing(sphere1, sphere2);

	// Assert
	EXPECT_EQ(Touch, res);
}

TEST(TestAlgorithmsLib, can_find_one_local_min) {
	// Arrange
	Matrix<int> matrix({ {1, 2, 3},
		{ 4, 5, 6 },
		{ 7, 8, 9 } });

	// Act
	int value = find_local_min_matrix(matrix);

	// Assert
	EXPECT_EQ(1, value);
}

TEST(TestAlgorithmsLib, can_find_any_local_min) {
	// Arrange
	Matrix<int> matrix({ {3, 1, 2},
		{ 5, 8, 4 },
		{ 7, 6, 9 } });

	// Act
	int local_min_1 = 1;
	int local_min_2 = 6;
	int value = find_local_min_matrix(matrix);
	bool actual_result = (local_min_1 == value) || (local_min_2 == value);

	// Assert
	bool expected_result = true;
	EXPECT_EQ(expected_result, actual_result);
}

TEST(TestDSULib, can_count_islands) {
	Matrix<int> matrix_1({ { 1, 0, 0, 0, 0, 1 },
						{ 0, 0, 0, 0, 1, 1, },
						{ 1, 1, 0, 0, 0, 1 },
						{ 1, 0, 0, 0, 0, 1 },
						{ 1, 0, 0, 1, 0, 1 },
						{ 0, 0, 0, 1, 1, 1 } });

	Matrix<int> matrix_2({ { 1, 0, 0, 0, 0, 1 },
						{ 0, 0, 0, 0, 1, 1, },
						{ 1, 1, 0, 0, 0, 1 },
						{ 1, 0, 0, 0, 0, 1 },
						{ 1, 0, 0, 1, 0, 1 } });

	Matrix<int> matrix_3({ { 1, 0, 0, 0, 0, 1 },
						{ 0, 0, 0, 0, 1, 1, },
						{ 1, 1, 0, 0, 0, 1 },
						{ 0, 0, 0, 0, 0, 1 },
						{ 1, 1, 0, 1, 0, 1 },
						{ 0, 1, 0, 1, 0, 1 } });

	EXPECT_EQ(3, find_number_of_islands(matrix_1));
	EXPECT_EQ(4, find_number_of_islands(matrix_2));
	EXPECT_EQ(5, find_number_of_islands(matrix_3));
}
