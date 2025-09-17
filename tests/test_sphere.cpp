// Copyright 2025 Viktoria Buzlaeva

#include <gtest/gtest.h>
#include "../lib_sphere/sphere.h"

#define EPSILON 0.000001

TEST(TestSphereLib, can_create) {
	// Arrange & Act
	Sphere sphere;

	// Assert
	EXPECT_EQ(0, sphere.cent().x());
	EXPECT_EQ(0, sphere.cent().y());
	EXPECT_EQ(0, sphere.cent().z());
	EXPECT_EQ(0, sphere.rad());
}

TEST(TestSphereLib, can_create_init) {
	// Arrange & Act
	Sphere sphere(2, 1, 2, 3);

	// Assert
	EXPECT_EQ(1, sphere.cent().x());
	EXPECT_EQ(2, sphere.cent().y());
	EXPECT_EQ(3, sphere.cent().z());
	EXPECT_EQ(2, sphere.rad());
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
	// Arrange & Act
	Point3D point3d(6, 2, 1);
	Sphere sphere(2, point3d);

	// Assert
	EXPECT_EQ(6, sphere.cent().x());
	EXPECT_EQ(2, sphere.cent().y());
	EXPECT_EQ(1, sphere.cent().z());
	EXPECT_EQ(2, sphere.rad());
}

TEST(TestSphereLib, throw_when_create_with_point3d_with_incorrect_rad) {
	// Arrange
	Point3D point3d(6, 2);
	int rad = -2;

	// Act & Assert
	ASSERT_ANY_THROW(Sphere sphere(rad, point3d));
}

TEST(TestSphereLib, can_create_copy) {
	// Arrange & Act
	Sphere sphere_1(3);
	Sphere sphere_2(sphere_1);

	// Assert
	EXPECT_EQ(sphere_2.cent().x(), sphere_1.cent().x());
	EXPECT_EQ(sphere_2.cent().y(), sphere_1.cent().y());
	EXPECT_EQ(sphere_2.cent().z(), sphere_1.cent().z());
	EXPECT_EQ(sphere_2.rad(), sphere_1.rad());
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
