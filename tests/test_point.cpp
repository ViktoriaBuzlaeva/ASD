// Copyright 2025 Viktoria Buzlaeva

#include <gtest/gtest.h>
#include "../lib_point/point.h"

TEST(TestPointLib, can_create) {
	// Arrange

	// Act & Assert
	ASSERT_NO_THROW(Point point());
}

TEST(TestPointLib, can_create_init) {
	// Arrange

	// Act & Assert
	ASSERT_NO_THROW(Point point(2, 3));
}

TEST(TestPointLib, can_create_copy) {
	// Arrange
	Point point_1(2, 3);

	// Act & Assert
	ASSERT_NO_THROW(Point point_2(point_1));
}
