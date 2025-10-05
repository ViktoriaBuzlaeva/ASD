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

TEST(TestMathVectorLib, can_create_copy) {
	// Arrange
	int mass[4] = { 1, 2, 3, 4 };
	MathVector<int> mvector_1({ 1, 2, 3, 4 });
	MathVector<int> mvector_2(mvector_1);

	// Act
	bool actual_result = true;
	for (int i = 0; i < mvector_2.size(); i++) {
		actual_result &= (*(mvector_2.data() + i) == mass[i]);
	}

	// Assert
	bool expected_result = true;
	EXPECT_EQ(expected_result, actual_result);
}

TEST(TestMathVectorLib, throw_when_create_copy) {
	// Arrange
	MathVector<int>* mvector_1 = NULL;

	// Act & Assert
	ASSERT_ANY_THROW(MathVector<int> mvector_2(*mvector_1));
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

TEST(TestMathVectorLib, can_access_with_operator_brackets_with_start_index) {
	// Arrange
	MathVector<int> mvector({ 1, 2, 3 }, 1);
	int zero_elem = mvector[0];

	//  Act & Assert
	EXPECT_EQ(0, zero_elem);
	EXPECT_EQ(1, mvector[1]);
}
