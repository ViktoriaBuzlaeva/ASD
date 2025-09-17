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
