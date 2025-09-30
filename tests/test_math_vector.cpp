// Copyright 2025 Viktoria Buzlaeva

#include <gtest/gtest.h>
#include "../lib_math_vector/mathvector.h"

#define EPSILON 0.000001

TEST(TestMathVectorLib, can_create) {
	// Arrange & Act
	MathVector<int> mvector;

	// Assert
	EXPECT_EQ(0, mvector.size());
}

TEST(TestMathVectorLib, can_create_with_size) {
	// Arrange & Act
	MathVector<int> mvector(30);

	// Assert
	EXPECT_EQ(30, mvector.size());
}

TEST(TestMathVectorLib, can_add_mvectors) {
	// Arrange
	MathVector<int> mvector_1({ 1, 2, 3 });
	MathVector<int> mvector_2({ 4, 5, 6 });
	MathVector<int> result({ 5, 7, 9 });

	// Act & Assert
	EXPECT_EQ(result, mvector_1 + mvector_2);
}

TEST(TestMathVectorLib, throw_when_try_add_mvectors_with_different_size) {
	// Arrange
	MathVector<int> mvector_1({ 1, 2 });
	MathVector<int> mvector_2({ 4, 5, 6 });

	// Act & Assert
	ASSERT_ANY_THROW(mvector_1 + mvector_2);
}

TEST(TestMathVectorLib, can_sub_mvectors) {
	// Arrange
	MathVector<int> mvector_1({ 1, 2, 3 });
	MathVector<int> mvector_2({ 4, 5, 6 });
	MathVector<int> result({ -3, -3, -3 });

	// Act & Assert
	EXPECT_EQ(result, mvector_1 - mvector_2);
}

TEST(TestMathVectorLib, throw_when_try_sub_mvectors_with_different_size) {
	// Arrange
	MathVector<int> mvector_1({ 1, 2 });
	MathVector<int> mvector_2({ 4, 5, 6 });

	// Act & Assert
	ASSERT_ANY_THROW(mvector_1 - mvector_2);
}

TEST(TestMathVectorLib, can_mult_mvectors) {
	// Arrange
	MathVector<int> mvector_1({ 1, 2, 3 });
	MathVector<int> mvector_2({ 4, 5, 6 });
	int result = 32;

	// Act & Assert
	EXPECT_EQ(result, mvector_1 * mvector_2);
}

TEST(TestMathVectorLib, throw_when_try_mult_mvectors_with_different_size) {
	// Arrange
	MathVector<int> mvector_1({ 1, 2 });
	MathVector<int> mvector_2({ 4, 5, 6 });

	// Act & Assert
	ASSERT_ANY_THROW(mvector_1 * mvector_2);
}

TEST(TestMathVectorLib, can_mult_mvector_and_scalar) {
	// Arrange
	MathVector<int> mvector({ 1, 2, 3 });
	int scalar = 3;
	MathVector<int> result({ 3, 6, 9 });

	// Act & Assert
	EXPECT_EQ(result, mvector * scalar);
}

TEST(TestMathVectorLib, can_mult_scalar_and_mvector) {
	// Arrange
	MathVector<int> mvector({ 1, 2, 3 });
	int scalar = 3;
	MathVector<int> result({ 3, 6, 9 });

	// Act & Assert
	EXPECT_EQ(result, scalar * mvector);
}

TEST(TestMathVectorLib, can_add_mvectors_with_assign) {
	// Arrange
	MathVector<int> mvector_1({ 1, 2, 3 });
	MathVector<int> mvector_2({ 4, 5, 6 });
	MathVector<int> result({ 5, 7, 9 });

	// Act
	mvector_1 += mvector_2;

	// Assert
	EXPECT_EQ(result, mvector_1);
}

TEST(TestMathVectorLib, throw_when_try_add_mvectors_with_assign_with_different_size) {
	// Arrange
	MathVector<int> mvector_1({ 1, 2 });
	MathVector<int> mvector_2({ 4, 5, 6 });

	// Act & Assert
	ASSERT_ANY_THROW(mvector_1 += mvector_2);
}

TEST(TestMathVectorLib, can_sub_mvectors_with_assign) {
	// Arrange
	MathVector<int> mvector_1({ 1, 2, 3 });
	MathVector<int> mvector_2({ 4, 5, 6 });
	MathVector<int> result({ -3, -3, -3 });

	// Act
	mvector_1 -= mvector_2;

	// Assert
	EXPECT_EQ(result, mvector_1);
}

TEST(TestMathVectorLib, throw_when_try_sub_mvectors_with_assign_with_different_size) {
	// Arrange
	MathVector<int> mvector_1({ 1, 2 });
	MathVector<int> mvector_2({ 4, 5, 6 });

	// Act & Assert
	ASSERT_ANY_THROW(mvector_1 -= mvector_2);
}

TEST(TestMathVectorLib, can_mult_scalar_with_assign) {
	// Arrange
	MathVector<int> mvector({ 1, 2, 3 });
	int scalar = 3;
	MathVector<int> result({ 3, 6, 9 });

	// Act
	mvector *= scalar;

	// Assert
	EXPECT_EQ(result, mvector);
}
