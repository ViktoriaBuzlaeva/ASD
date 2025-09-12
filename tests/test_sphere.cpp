// Copyright 2025 Viktoria Buzlaeva

#include <gtest/gtest.h>
#include "../lib_sphere/sphere.h"

#define EPSILON 0.000001

TEST(TestSphereLib, can_create) {
	// Arrange

	// Act & Assert
	ASSERT_NO_THROW(Sphere sphere);
}

TEST(TestSphereLib, can_create_init) {
	// Arrange
	Point3D point3d(6, 2);
	int rad = 2;

	// Act & Assert
	ASSERT_NO_THROW(Sphere sphere(rad, point3d));
}

TEST(TestSphereLib, can_create_init_with_point3d) {
	// Arrange
	Point3D point3d(6, 2, 1);
	int rad = 2;

	// Act & Assert
	ASSERT_NO_THROW(Sphere sphere(rad, point3d));
}

TEST(TestSphereLib, throw_when_create_with_incorrect_rad) {
	// Arrange
	Point3D point3d(6, 2);
	int rad = -2;

	// Act & Assert
	ASSERT_ANY_THROW(Sphere sphere(rad, point3d));
}

TEST(TestSphereLib, can_create_copy) {
	// Arrange
	Sphere sphere_1(3);

	// Act & Assert
	ASSERT_NO_THROW(Sphere sphere_2(sphere_1));
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
