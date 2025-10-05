// Copyright 2025 Viktoria Buzlaeva

#include <gtest/gtest.h>
#include "../lib_triangle_matrix/trianglematrix.h"

#define EPSILON 0.000001

TEST(TestTriangleMatrixLib, can_create) {
	// Arrange & Act
	TriangleMatrix<int> tmatrix;

	// Assert
	EXPECT_EQ(0, tmatrix.size());
}

TEST(TestTriangleMatrixLib, can_create_with_size) {
	// Arrange & Act
	TriangleMatrix<int> tmatrix(2);

	// Assert
	EXPECT_EQ(2, tmatrix.size());
}

TEST(TestTriangleMatrixLib, can_create_with_copy) {
	// Arrange & Act
	TriangleMatrix<int> tmatrix_1(2);
	TriangleMatrix<int> tmatrix_2(tmatrix_1);

	// Assert
	EXPECT_EQ(2, tmatrix_2.size());
}

TEST(TestTriangleMatrixLib, throw_when_try_create_with_copy) {
	// Arrange
	TriangleMatrix<int>* tmatrix_1 = NULL;

	// Act & Assert
	ASSERT_ANY_THROW(TriangleMatrix<int> tmatrix_2(*tmatrix_1));
}

TEST(TestTriangleMatrixLib, can_create_with_init_list) {
	// Arrange & Act
	TriangleMatrix<int> tmatrix({ {1, 2, 3}, {5, 6}, {9} });
	MathVector<int> vector_1({ 1, 2, 3 });
	MathVector<int> vector_2({ 5, 6 });
	MathVector<int> vector_3({ 9 });

	// Assert
	EXPECT_EQ(3, tmatrix.size());
	EXPECT_EQ(vector_1, tmatrix[0]);
	EXPECT_EQ(vector_2, tmatrix[1]);
	EXPECT_EQ(vector_3, tmatrix[2]);
}

TEST(TestTriangleMatrixLib, can_assign_correctly) {
	// Arrange
	TriangleMatrix<int> tmatrix_1({ {1, 2, 3}, {5, 6}, {9} });
	MathVector<int> vector_1({ 1, 2, 3 });
	MathVector<int> vector_2({ 5, 6 });
	MathVector<int> vector_3({ 9 });
	TriangleMatrix<int> tmatrix_2;

	// Act
	tmatrix_2 = tmatrix_1;

	// Assert
	EXPECT_EQ(3, tmatrix_2.size());
	EXPECT_EQ(vector_1, tmatrix_2[0]);
	EXPECT_EQ(vector_2, tmatrix_2[1]);
	EXPECT_EQ(vector_3, tmatrix_2[2]);
}

TEST(TestTriangleMatrixLib, can_comp_correctly_with_eq_operator) {
	// Arrange
	TriangleMatrix<int> tmatrix_1({ {1, 2}, {5} });
	TriangleMatrix<int> tmatrix_2({ {1, 2}, {5} });
	TriangleMatrix<int> tmatrix_3({ {1, 2}, {9} });

	// Act & Assert
	EXPECT_TRUE(tmatrix_1 == tmatrix_2);
	EXPECT_FALSE(tmatrix_1 == tmatrix_3);
}

TEST(TestTriangleMatrixLib, can_comp_correctly_with_not_eq_operator) {
	// Arrange
	TriangleMatrix<int> tmatrix_1({ {1, 2}, {5} });
	TriangleMatrix<int> tmatrix_2({ {1, 2}, {5} });
	TriangleMatrix<int> tmatrix_3({ {1, 2}, {9} });

	// Act & Assert
	EXPECT_TRUE(tmatrix_1 != tmatrix_3);
	EXPECT_FALSE(tmatrix_1 != tmatrix_2);
}

TEST(TestTriangleMatrixLib, can_add_correctly) {
	// Arrange
	TriangleMatrix<int> tmatrix_1({ {1, 2}, {5} });
	TriangleMatrix<int> tmatrix_2({ {1, 2}, {5} });
	TriangleMatrix<int> tmatrix_3({ {2, 4}, {10} });

	// Act & Assert
	EXPECT_EQ(tmatrix_3, tmatrix_1 + tmatrix_2);
}

TEST(TestTriangleMatrixLib, throw_when_try_add_with_incorrect_size) {
	// Arrange
	TriangleMatrix<int> tmatrix_1({ {3, 4, 6}, {1, 2}, {5} });
	TriangleMatrix<int> tmatrix_2({ {1, 2}, {5} });

	// Act & Assert
	ASSERT_ANY_THROW(tmatrix_1 + tmatrix_2);
}

TEST(TestTriangleMatrixLib, can_sub_correctly) {
	// Arrange
	TriangleMatrix<int> tmatrix_1({ {1, 1, 1}, { 2, 4 }, {10} });
	TriangleMatrix<int> tmatrix_2({ {2, 3, 5}, {1, 2}, {5} });
	TriangleMatrix<int> tmatrix_3({ {-1, -2, -4}, {1, 2}, {5} });

	// Act & Assert
	EXPECT_EQ(tmatrix_3, tmatrix_1 - tmatrix_2);
}

TEST(TestTriangleMatrixLib, throw_when_try_sub_with_incorrect_size) {
	// Arrange
	TriangleMatrix<int> tmatrix_1({ {3, 4, 6}, {1, 2}, {5} });
	TriangleMatrix<int> tmatrix_2({ {1, 2}, {5} });

	// Act & Assert
	ASSERT_ANY_THROW(tmatrix_1 - tmatrix_2);
}

TEST(TestTriangleMatrixLib, can_mult_correctly) {
	// Arrange
	TriangleMatrix<int> tmatrix_1({ {1, 1, 1}, {1, 2}, {5} });
	TriangleMatrix<int> tmatrix_2({ {1, 1, 1}, {1, 2}, {5} });
	TriangleMatrix<int> tmatrix_3({ {1, 2, 8}, {1, 12}, {25} });

	// Act & Assert
	EXPECT_EQ(tmatrix_3, tmatrix_1 * tmatrix_2);
}

TEST(TestTriangleMatrixLib, can_mult_scalar_correctly) {
	// Arrange
	TriangleMatrix<int> tmatrix_1({ {1, 1, 1}, {1, 2}, {5} });
	int scalar = 3;
	TriangleMatrix<int> tmatrix_2({ {3, 3, 3}, {3, 6}, {15} });

	// Act & Assert
	EXPECT_EQ(tmatrix_2, tmatrix_1 * scalar);
}

TEST(TestTriangleMatrixLib, can_mult_left_scalar_correctly) {
	// Arrange
	TriangleMatrix<int> tmatrix_1({ {1, 1, 1}, {1, 2}, {5} });
	int scalar = 3;
	TriangleMatrix<int> tmatrix_2({ {3, 3, 3}, {3, 6}, {15} });

	// Act & Assert
	EXPECT_EQ(tmatrix_2, scalar * tmatrix_1);
}

TEST(TestTriangleMatrixLib, can_mult_vector_correctly) {
	// Arrange
	TriangleMatrix<int> tmatrix({ {1, 1, 1}, {1, 2}, {5} });
	MathVector<int> vector_1({ 3, 3, 5 });
	MathVector<int> vector_2({ 11, 13, 25 });

	// Act & Assert
	EXPECT_EQ(vector_2, tmatrix * vector_1);
}

TEST(TestTriangleMatrixLib, throw_when_try_mult_with_incorrect_size) {
	// Arrange
	TriangleMatrix<int> tmatrix_1({ {3, 4, 6}, {1, 2}, {5} });
	TriangleMatrix<int> tmatrix_2({ {1, 2}, {5} });

	// Act & Assert
	ASSERT_ANY_THROW(tmatrix_1 * tmatrix_2);
}

TEST(TestTriangleMatrixLib, can_add_with_assign_correctly) {
	// Arrange
	TriangleMatrix<int> tmatrix_1({ {1, 2}, {5} });
	TriangleMatrix<int> tmatrix_2({ {1, 2}, {6} });
	TriangleMatrix<int> tmatrix_3({ {2, 4}, {11} });

	// Act
	tmatrix_1 += tmatrix_2;

	// Assert
	EXPECT_EQ(tmatrix_3, tmatrix_1);
}

TEST(TestTriangleMatrixLib, throw_when_try_add_with_assign_with_incorrect_size) {
	// Arrange
	TriangleMatrix<int> matrix_1({ {1, 2}, {5} });
	TriangleMatrix<int> matrix_2({ {1, 2, 3}, {5, 6}, {9} });

	// Act & Assert
	ASSERT_ANY_THROW(matrix_1 += matrix_2);
}

TEST(TestTriangleMatrixLib, can_sub_with_assign_correctly) {
	// Arrange
	TriangleMatrix<int> matrix_1({ {1, 2}, {4} });
	TriangleMatrix<int> matrix_2({ {1, 1}, {1} });
	TriangleMatrix<int> matrix_3({ {0, 1}, {3} });

	// Act
	matrix_1 -= matrix_2;

	// Assert
	EXPECT_EQ(matrix_3, matrix_1);
}

TEST(TestTriangleMatrixLib, throw_when_try_sub_with_assign_with_incorrect_size) {
	// Arrange
	TriangleMatrix<int> matrix_1({ {1, 2}, {6} });
	TriangleMatrix<int> matrix_2({ {1, 2, 3}, {4, 6}, {7} });

	// Act & Assert
	ASSERT_ANY_THROW(matrix_1 -= matrix_2);
}

TEST(TestTriangleMatrixLib, can_mult_matr_with_assign_correctly) {
	// Arrange
	TriangleMatrix<int> matrix_1({ {1, 2}, {4} });
	TriangleMatrix<int> matrix_2({ {2, 2}, {1} });
	TriangleMatrix<int> matrix_3({ {2, 4}, {4} });

	// Act
	matrix_1 *= matrix_2;

	// Assert
	EXPECT_EQ(matrix_3, matrix_1);
}

TEST(TestTriangleMatrixLib, throw_when_try_mult_matr_with_assign_with_incorrect_size) {
	// Arrange
	TriangleMatrix<int> matrix_1({ {1, 2, 3}, {4, 5}, {6} });
	TriangleMatrix<int> matrix_2({ {1, 2}, {4} });

	// Act & Assert
	ASSERT_ANY_THROW(matrix_1 *= matrix_2);
}

TEST(TestTriangleMatrixLib, can_mult_scalar_with_assign_correctly) {
	// Arrange
	TriangleMatrix<int> matrix_1({ {1, 2}, {4} });
	int scalar = 3;
	TriangleMatrix<int> matrix_2({ {3, 6}, {12} });

	// Act
	matrix_1 *= scalar;

	// Assert
	EXPECT_EQ(matrix_2, matrix_1);
}
