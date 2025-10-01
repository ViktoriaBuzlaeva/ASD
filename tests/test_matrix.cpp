// Copyright 2025 Viktoria Buzlaeva

#include <gtest/gtest.h>
#include "../lib_matrix/matrix.h"
	
#define EPSILON 0.000001

TEST(TestMatrixLib, can_create) {
	// Arrange & Act
	Matrix<int> matrix;

	// Assert
	EXPECT_EQ(0, matrix.rows());
	EXPECT_EQ(0, matrix.cols());
}

TEST(TestMatrixLib, can_create_with_rows_and_cols) {
	// Arrange & Act
	Matrix<int> matrix(2, 3);

	// Assert
	EXPECT_EQ(2, matrix.rows());
	EXPECT_EQ(3, matrix.cols());
}

TEST(TestMatrixLib, throw_when_try_create_with_incorrect_size) {
	// Arrange

	// Act & Assert
	ASSERT_ANY_THROW(Matrix<int> matrix(-2, 3));
}

TEST(TestMatrixLib, can_create_with_copy) {
	// Arrange & Act
	Matrix<int> matrix_1(2, 3);
	Matrix<int> matrix_2(matrix_1);

	// Assert
	EXPECT_EQ(2, matrix_2.rows());
	EXPECT_EQ(3, matrix_2.cols());
}

TEST(TestMatrixLib, throw_when_try_create_with_copy) {
	// Arrange
	Matrix<int>* matrix_1 = NULL;

	// Act & Assert
	ASSERT_ANY_THROW(Matrix<int> matrix_2(*matrix_1));
}

TEST(TestMatrixLib, can_create_with_matrix) {
	// Arrange & Act
	MathVector<MathVector<int>> matrix_1(2);
	for (size_t i = 0; i < matrix_1.size(); i++) {
		matrix_1[i] = MathVector<int>({1, 2, 3});
	}
	Matrix<int> matrix_2(matrix_1);

	// Assert
	EXPECT_EQ(2, matrix_2.rows());
	EXPECT_EQ(3, matrix_2.cols());
}

TEST(TestMatrixLib, can_create_with_init_list) {
	// Arrange & Act
	Matrix<int> matrix({ {1, 2, 3},
						{4, 5, 6} });
	MathVector<int> vector_1({ 1, 2, 3 });
	MathVector<int> vector_2({ 4, 5, 6 });

	// Assert
	EXPECT_EQ(2, matrix.rows());
	EXPECT_EQ(3, matrix.cols());
	EXPECT_EQ(vector_1, matrix[0]);
	EXPECT_EQ(vector_2, matrix[1]);
}

TEST(TestMatrixLib, can_assign_correctly) {
	// Arrange
	Matrix<int> matrix_1({ {1, 2, 3},
						{4, 5, 6} });
	MathVector<int> vector_1({ 1, 2, 3 });
	MathVector<int> vector_2({ 4, 5, 6 });
	Matrix<int> matrix_2;

	// Act
	matrix_2 = matrix_1;

	// Assert
	EXPECT_EQ(2, matrix_2.rows());
	EXPECT_EQ(3, matrix_2.cols());
	EXPECT_EQ(vector_1, matrix_2[0]);
	EXPECT_EQ(vector_2, matrix_2[1]);
}

TEST(TestMatrixLib, can_comp_correctly_with_eq_operator) {
	// Arrange
	Matrix<int> matrix_1({ {1, 2, 3}, 
						{4, 5, 6} });
	Matrix<int> matrix_2({ {1, 2, 3},
						{4, 5, 6} });
	Matrix<int> matrix_3({ {2, 2, 3},
						{4, 5, 6} });

	// Act & Assert
	EXPECT_TRUE(matrix_1 == matrix_2);
	EXPECT_FALSE(matrix_1 == matrix_3);
}

TEST(TestMatrixLib, can_comp_correctly_with_not_eq_operator) {
	// Arrange
	Matrix<int> matrix_1({ {1, 2, 3},
						{4, 5, 6} });
	Matrix<int> matrix_2({ {1, 2, 3},
						{4, 5, 6} });
	Matrix<int> matrix_3({ {2, 2, 3},
						{4, 5, 6} });

	// Act & Assert
	EXPECT_TRUE(matrix_1 != matrix_3);
	EXPECT_FALSE(matrix_1 != matrix_2);
}

TEST(TestMatrixLib, can_transpose_correctly) {
	// Arrange
	Matrix<int> matrix_1({ {1, 2, 3},
						{4, 5, 6} });
	Matrix<int> matrix_2({ {1, 4},
						{2, 5},
						{3, 6} });

	// Act & Assert
	EXPECT_EQ(matrix_2, matrix_1.transpose());
}

TEST(TestMatrixLib, can_add_correctly) {
	// Arrange
	Matrix<int> matrix_1({ {1, 2, 3},
						{4, 5, 6} });
	Matrix<int> matrix_2({ {1, 2, 3},
						{4, 5, 6} });
	Matrix<int> matrix_3({ {2, 4, 6},
						{8, 10, 12} });

	// Act & Assert
	EXPECT_EQ(matrix_3, matrix_1 + matrix_2);
}

TEST(TestMatrixLib, throw_when_try_add_with_incorrect_size) {
	// Arrange
	Matrix<int> matrix_1({ {1, 2, 3},
						{4, 5, 6} });
	Matrix<int> matrix_2({ {1, 2, 3},
						{4, 5, 6},
						{7, 8, 9} });

	// Act & Assert
	ASSERT_ANY_THROW(matrix_1 + matrix_2);
}

TEST(TestMatrixLib, can_sub_correctly) {
	// Arrange
	Matrix<int> matrix_1({ {1, 2, 3},
						{4, 5, 6} });
	Matrix<int> matrix_2({ {1, 1, 1},
						{1, 1, 1} });
	Matrix<int> matrix_3({ {0, 1, 2},
						{3, 4, 5} });

	// Act & Assert
	EXPECT_EQ(matrix_3, matrix_1 - matrix_2);
}

TEST(TestMatrixLib, throw_when_try_sub_with_incorrect_size) {
	// Arrange
	Matrix<int> matrix_1({ {1, 2, 3},
						{4, 5, 6} });
	Matrix<int> matrix_2({ {1, 2, 3},
						{4, 5, 6},
						{7, 8, 9} });

	// Act & Assert
	ASSERT_ANY_THROW(matrix_1 - matrix_2);
}

TEST(TestMatrixLib, can_mult_matrix_and_scalar_correctly) {
	// Arrange
	Matrix<int> matrix_1({ {1, 2, 3},
						{4, 5, 6} });
	int scalar = 3;
	Matrix<int> matrix_2({ {3, 6, 9},
						{12, 15, 18} });

	// Act & Assert
	EXPECT_EQ(matrix_2, matrix_1 * scalar);
}

TEST(TestMatrixLib, can_mult_scalar_and_matrix_correctly) {
	// Arrange
	Matrix<int> matrix_1({ {1, 2, 3},
						{4, 5, 6} });
	int scalar = 3;
	Matrix<int> matrix_2({ {3, 6, 9},
						{12, 15, 18} });

	// Act & Assert
	EXPECT_EQ(matrix_2, scalar * matrix_1);
}

TEST(TestMatrixLib, can_mult_vec_correctly) {
	// Arrange
	Matrix<int> matrix_1({ {1, 2, 3},
						{4, 5, 6} });
	MathVector<int> vector_1({ 2, 2, 2 });
	MathVector<int> vector_2({12, 30});

	// Act & Assert
	EXPECT_EQ(vector_2, matrix_1 * vector_1);
}

TEST(TestMatrixLib, throw_when_try_mult_vec_with_incorrect_size) {
	// Arrange
	Matrix<int> matrix({ {1, 2, 3},
						{4, 5, 6} });
	MathVector<int> vector({ 2, 2, 2, 2 });

	// Act & Assert
	ASSERT_ANY_THROW(matrix * vector);
}

TEST(TestMatrixLib, can_mult_matr_correctly) {
	// Arrange
	Matrix<int> matrix_1({ {1, 2, 3},
						{4, 5, 6} });
	Matrix<int> matrix_2({ {2, 2, 1, 1},
						{1, 1, 2, 2},
						{1, 1, 1, 1} });
	Matrix<int> matrix_3({ {7, 7, 8, 8},
						{19, 19, 20, 20} });

	// Act & Assert
	EXPECT_EQ(matrix_3, matrix_1 * matrix_2);
}

TEST(TestMatrixLib, throw_when_try_mult_matr_with_incorrect_size) {
	// Arrange
	Matrix<int> matrix_1({ {1, 2, 3},
						{4, 5, 6} });
	Matrix<int> matrix_2({ {2, 2, 1, 1},
						{1, 1, 2, 2} });

	// Act & Assert
	ASSERT_ANY_THROW(matrix_1 * matrix_2);
}

TEST(TestMatrixLib, can_add_with_assign_correctly) {
	// Arrange
	Matrix<int> matrix_1({ {1, 2, 3},
						{4, 5, 6} });
	Matrix<int> matrix_2({ {1, 2, 3},
						{4, 5, 6} });
	Matrix<int> matrix_3({ {2, 4, 6},
						{8, 10, 12} });

	// Act
	matrix_1 += matrix_2;

	// Assert
	EXPECT_EQ(matrix_3, matrix_1);
}

TEST(TestMatrixLib, throw_when_try_add_with_assign_with_incorrect_size) {
	// Arrange
	Matrix<int> matrix_1({ {1, 2, 3},
						{4, 5, 6} });
	Matrix<int> matrix_2({ {1, 2, 3},
						{4, 5, 6},
						{7, 8, 9} });

	// Act & Assert
	ASSERT_ANY_THROW(matrix_1 += matrix_2);
}

TEST(TestMatrixLib, can_sub_with_assign_correctly) {
	// Arrange
	Matrix<int> matrix_1({ {1, 2, 3},
						{4, 5, 6} });
	Matrix<int> matrix_2({ {1, 1, 1},
						{1, 1, 1} });
	Matrix<int> matrix_3({ {0, 1, 2},
						{3, 4, 5} });

	// Act
	matrix_1 -= matrix_2;

	// Assert
	EXPECT_EQ(matrix_3, matrix_1);
}

TEST(TestMatrixLib, throw_when_try_sub_with_assign_with_incorrect_size) {
	// Arrange
	Matrix<int> matrix_1({ {1, 2, 3},
						{4, 5, 6} });
	Matrix<int> matrix_2({ {1, 2, 3},
						{4, 5, 6},
						{7, 8, 9} });

	// Act & Assert
	ASSERT_ANY_THROW(matrix_1 -= matrix_2);
}

TEST(TestMatrixLib, can_mult_matr_with_assign_correctly) {
	// Arrange
	Matrix<int> matrix_1({ {1, 2, 3},
						{4, 5, 6} });
	Matrix<int> matrix_2({ {2, 2, 1, 1},
						{1, 1, 2, 2},
						{1, 1, 1, 1} });
	Matrix<int> matrix_3({ {7, 7, 8, 8},
						{19, 19, 20, 20} });

	// Act
	matrix_1 *= matrix_2;

	// Assert
	EXPECT_EQ(matrix_3, matrix_1);
}

TEST(TestMatrixLib, throw_when_try_mult_matr_with_assign_with_incorrect_size) {
	// Arrange
	Matrix<int> matrix_1({ {1, 2, 3},
						{4, 5, 6} });
	Matrix<int> matrix_2({ {1, 2, 3},
						{4, 5, 6} });

	// Act & Assert
	ASSERT_ANY_THROW(matrix_1 *= matrix_2);
}

TEST(TestMatrixLib, can_mult_scalar_with_assign_correctly) {
	// Arrange
	Matrix<int> matrix_1({ {1, 2, 3},
						{4, 5, 6} });
	int scalar = 3;
	Matrix<int> matrix_2({ {3, 6, 9},
						{12, 15, 18} });

	// Act
	std::cout << matrix_1;
	matrix_1 *= scalar;

	// Assert
	EXPECT_EQ(matrix_2, matrix_1);
}
