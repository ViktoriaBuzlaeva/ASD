// Copyright 2025 Viktoria Buzlaeva

#include <gtest/gtest.h>
#include "../lib_sphere/sphere.h"

#define EPSILON 0.000001

TEST(TestSphereLib, can_create) {
	// Arrange
	Sphere sphere;

	// Act
	Point3D cent(0, 0, 0);
	int rad = 0;
	bool actual_result = (sphere.cent() == cent) && (sphere.rad() == rad);

	// Assert
	bool expected_result = true;
	EXPECT_EQ(expected_result, actual_result);
}

TEST(TestSphereLib, can_create_init) {
	// Arrange
	Sphere sphere(2, 1, 2, 3);

	// Act
	Point3D cent(1, 2, 3);
	int rad = 2;
	bool actual_result = (sphere.cent() == cent) && (sphere.rad() == rad);

	// Assert
	bool expected_result = true;
	EXPECT_EQ(expected_result, actual_result);
}

TEST(TestSphereLib, throw_when_create_init_with_incorrect_rad) {
	// Arrange
	int x = 1;
	int y = 2;
	int z = 3;
	int rad = -2;

	// Act & Assert
	ASSERT_ANY_THROW(Sphere sphere(rad, x, y, z));
}

TEST(TestSphereLib, can_create_init_with_point3d) {
	// Arrange
	Point3D point3d(6, 2, 1);
	Sphere sphere(2, point3d);

	// Act
	int x = 6;
	int y = 2;
	int z = 1;
	int rad = 2;
	bool actual_result = (sphere.cent().x() == x) && (sphere.cent().y() == y)
		&& (sphere.cent().z() == z) && (sphere.rad() == rad);

	// Assert
	bool expected_result = true;
	EXPECT_EQ(expected_result, actual_result);
}

TEST(TestSphereLib, throw_when_create_with_point3d_with_incorrect_rad) {
	// Arrange
	Point3D point3d(6, 2);
	int rad = -2;

	// Act & Assert
	ASSERT_ANY_THROW(Sphere sphere(rad, point3d));
}

TEST(TestSphereLib, can_create_copy) {
	// Arrange
	Sphere sphere_1(3);
	Sphere sphere_2(sphere_1);

	// Act
	int x = 0;
	int y = 0;
	int z = 0;
	int rad = 3;
	bool actual_result = (sphere_2.cent().x() == x) && (sphere_2.cent().y() == y)
		&& (sphere_2.cent().z() == z) && (sphere_2.rad() == rad);

	// Assert
	bool expected_result = true;
	EXPECT_EQ(expected_result, actual_result);
}

TEST(TestSphereLib, can_comp_correctly_eq_spheres) {
	// Arrange
	Sphere sphere_1(3);
	Sphere sphere_2(3);

	// Act & Assert
	EXPECT_TRUE(sphere_1 == sphere_2);
}

TEST(TestSphereLib, can_comp_correctly_not_eq_circles) {
	// Arrange
	Sphere sphere_1(3);
	Sphere sphere_2(4);

	// Act & Assert
	EXPECT_FALSE(sphere_1 == sphere_2);
}

TEST(TestSphereLib, can_comp_correctly_eq_circles_other) {
	// Arrange
	Sphere sphere_1(3);
	Sphere sphere_2(3);

	// Act & Assert
	EXPECT_FALSE(sphere_1 != sphere_2);
}

TEST(TestSphereLib, can_comp_correctly_not_eq_circles_other) {
	// Arrange
	Point3D point3d_1(1, 2, 3);
	Point3D point3d_2(2, 2, 3);
	Sphere sphere_1(3, point3d_1);
	Sphere sphere_2(3, point3d_2);

	// Act & Assert
	EXPECT_TRUE(sphere_1 != sphere_2);
}
