// Copyright 2025 Viktoria Buzlaeva

#include <gtest/gtest.h>
#include "../lib_point/point.h"
#include "../lib_point3d/point3d.h"

#define EPSILON 0.000001

TEST(TestPoint3DLib, can_create) {
    // Arrange & Act
    Point3D point3d;

    // Assert
    EXPECT_EQ(0, point3d.x());
    EXPECT_EQ(0, point3d.y());
    EXPECT_EQ(0, point3d.z());
}

TEST(TestPoint3DLib, can_create_init) {
    // Arrange & Act
    Point3D point3d(3, 4, 2);

    // Assert
    EXPECT_EQ(3, point3d.x());
    EXPECT_EQ(4, point3d.y());
    EXPECT_EQ(2, point3d.z());
}

TEST(TestPoint3DLib, can_create_init_with_point2d) {
    // Arrange & Act
    Point point(6, 2);
    Point3D point3d(point, 4);

    // Assert
    EXPECT_EQ(6, point3d.x());
    EXPECT_EQ(2, point3d.y());
    EXPECT_EQ(4, point3d.z());
}

TEST(TestPoint3DLib, can_create_copy) {
    // Arrange & Act
    Point3D point3d_1(2, 3);
    Point3D point3d_2(point3d_1);

    // Assert
    EXPECT_EQ(point3d_2.x(), point3d_1.x());
    EXPECT_EQ(point3d_2.y(), point3d_1.y());
    EXPECT_EQ(point3d_2.z(), point3d_1.z());
}

TEST(TestPoint3DLib, can_comp_correctly_eq_points) {
    // Arrange
    Point3D point3d_1(0, 3, 1);
    Point3D point3d_2(0, 3, 1);

    // Act & Assert
    EXPECT_TRUE(point3d_1 == point3d_2);
}

TEST(TestPoint3DLib, can_comp_correctly_not_eq_points) {
    // Arrange
    Point3D point3d_1(0, 3, 1);
    Point3D point3d_2(0, 4, 1);

    // Act & Assert
    EXPECT_FALSE(point3d_1 == point3d_2);
}

TEST(TestPoint3DLib, can_comp_correctly_eq_points_other) {
    // Arrange
    Point3D point3d_1(0, 3, 1);
    Point3D point3d_2(0, 3, 1);

    // Act & Assert
    EXPECT_FALSE(point3d_1 != point3d_2);
}

TEST(TestPoint3DLib, can_comp_correctly_not_eq_points_other) {
    // Arrange
    Point3D point3d_1(0, 4, 2);
    Point3D point3d_2(0, 4, 1);

    // Act & Assert
    EXPECT_TRUE(point3d_1 != point3d_2);
}

TEST(TestPoint3DLib, can_find_correctly_dis_y) {
    // Arrange
    Point3D point3d_1(0, 0, 2);
    Point3D point3d_2(0, 3, 2);

    // Act
    float actual_result = point3d_1.find_distance(point3d_2);

    // Assert
    float expected_result = 3;
    EXPECT_EQ(expected_result, actual_result);
}

TEST(TestPoint3DLib, can_find_correctly_dis_x) {
    // Arrange
    Point3D point_1(0, 0, 0);
    Point3D point_2(4.6, 0, 0);

    // Act
    float actual_result = point_1.find_distance(point_2);

    // Assert
    float expected_result = 4.6;
    EXPECT_EQ(expected_result, actual_result);
}

TEST(TestPoint3DLib, can_find_correctly_dis_z) {
    // Arrange
    Point3D point_1(0, 0, 5);
    Point3D point_2(0, 0, 0);

    // Act
    float actual_result = point_1.find_distance(point_2);

    // Assert
    float expected_result = 5;
    EXPECT_EQ(expected_result, actual_result);
}

TEST(TestPoint3DLib, can_find_correctly_dis) {
    // Arrange
    Point3D point3d_1(0, 4, 7);
    Point3D point3d_2(4, 0, 0);

    // Act
    float actual_result = point3d_1.find_distance(point3d_2);

    // Assert
    float expected_result = 9;
    EXPECT_EQ(expected_result, actual_result);
}

TEST(TestPoint3DLib, can_find_correctly_dis_eq_points) {
    // Arrange
    Point3D point3d_1(0, 4, 2);
    Point3D point3d_2(0, 4, 2);

    // Act
    float actual_result = point3d_1.find_distance(point3d_2);

    // Assert
    float expected_result = 0;
    EXPECT_EQ(expected_result, actual_result);
}
