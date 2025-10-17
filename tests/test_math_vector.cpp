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

TEST(TestMathVectorLib, can_create_with_size_and_start_index) {
	// Arrange & Act
	MathVector<int> mvector(20, 10);

	// Assert
	EXPECT_EQ(30, mvector.size());
}

TEST(TestMathVectorLib, can_create_with_array_and_size) {
	// Arrange
	int mass[4] = { 1, 2, 3, 4 };
	MathVector<int> mvector(4, mass);

	// Act
	bool actual_result = true;
	for (int i = 0; i < mvector.size(); i++) {
		actual_result &= (*(mvector.data() + i) == mass[i]);
	}

	// Assert
	bool expected_result = true;
	EXPECT_EQ(4, mvector.size());
	EXPECT_EQ(expected_result, actual_result);
}

TEST(TestMathVectorLib, can_create_with_array_and_size_other) {
	// Arrange
	int mass[4] = { 1, 2, 3, 4 };
	MathVector<int> mvector(4, { 1, 2, 3, 4 });

	// Act
	bool actual_result = true;
	for (int i = 0; i < mvector.size(); i++) {
		actual_result &= (*(mvector.data() + i) == mass[i]);
	}

	// Assert
	bool expected_result = true;
	EXPECT_EQ(4, mvector.size());
	EXPECT_EQ(expected_result, actual_result);
}

TEST(TestMathVectorLib, can_create_with_array) {
	// Arrange
	int mass[4] = { 1, 2, 3, 4 };
	MathVector<int> mvector({ 1, 2, 3, 4 });

	// Act
	bool actual_result = true;
	for (int i = 0; i < mvector.size(); i++) {
		actual_result &= (*(mvector.data() + i) == mass[i]);
	}

	// Assert
	bool expected_result = true;
	EXPECT_EQ(4, mvector.size());
	EXPECT_EQ(expected_result, actual_result);
}

TEST(TestMathVectorLib, can_create_with_array_and_start_index) {
	// Arrange
	int mass[5] = { 0, 1, 2, 3, 4 };
	MathVector<int> mvector({ 1, 2, 3, 4 }, 1);

	// Act
	bool actual_result = true;
	for (int i = 1; i < mvector.size(); i++) {
		actual_result &= (*(mvector.data() + i - 1) == mass[i]);
	}

	// Assert
	bool expected_result = true;
	EXPECT_EQ(5, mvector.size());
	EXPECT_EQ(expected_result, actual_result);
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

TEST(TestMathVectorLib, can_comp_correctly_with_operator_eq) {
	// Arrange
	MathVector<int> mvector1({ 1, 2, 3, 4 });
	MathVector<int> mvector2({ 1, 2, 3, 4 });
	MathVector<int> mvector3({ 1, 2, 3, 5 });

	// Act & Assert
	EXPECT_TRUE(mvector1 == mvector2);
	EXPECT_FALSE(mvector1 == mvector3);
}

TEST(TestMathVectorLib, can_comp_correctly_with_operator_not_eq) {
	// Arrange
	MathVector<int> mvector1({ 1, 2, 3, 4 });
	MathVector<int> mvector2({ 1, 2, 3, 4, 6 });
	MathVector<int> mvector3({ 1, 2, 3, 4 });

	// Act & Assert
	EXPECT_TRUE(mvector1 != mvector2);
	EXPECT_FALSE(mvector1 != mvector3);
}

TEST(TestMathVectorLib, can_assign_correctly_with_operator) {
	// Arrange
	MathVector<int> mvector1({ 1, 2, 3, 4 });
	MathVector<int> mvector2({ 1, 2 });

	// Act
	mvector1 = mvector2;

	// Assert
	EXPECT_TRUE(mvector1 == mvector2);
}

TEST(TestMathVectorLib, can_add_mvectors) {
	// Arrange
	MathVector<int> mvector_1({ 1, 2, 3 });
	MathVector<int> mvector_2({ 4, 5, 6 });
	MathVector<int> result({ 5, 7, 9 });

	// Act & Assert
	EXPECT_EQ(result, mvector_1 + mvector_2);
}

TEST(TestMathVectorLib, can_add_mvectors_with_start_index) {
	// Arrange
	MathVector<int> mvector_1({ 1, 2, 3 }, 1);
	MathVector<int> mvector_2({ 5, 6 }, 2);
	MathVector<int> result({ 1, 7, 9 }, 1);

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

TEST(TestMathVectorLib, can_sub_mvectors_with_start_index) {
	// Arrange
	MathVector<int> mvector_1({ 2, 3 }, 2);
	MathVector<int> mvector_2({ 4, 5, 6 }, 1);
	MathVector<int> result({ -4, -3, -3 }, 1);

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

TEST(TestMathVectorLib, can_mult_mvectors_with_start_index) {
	// Arrange
	MathVector<int> mvector_1({ 1, 2, 3 }, 3);
	MathVector<int> mvector_2({ 4, 5, 6, 1, 2, 3 });
	int result = 14;

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

TEST(TestMathVectorLib, can_mult_mvector_with_start_index_and_scalar) {
	// Arrange
	MathVector<int> mvector({ 1, 2, 3 }, 1);
	int scalar = 3;
	MathVector<int> result({ 3, 6, 9 }, 1);

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

TEST(TestMathVectorLib, can_mult_scalar_and_mvector_with_start_index) {
	// Arrange
	MathVector<int> mvector({ 1, 2, 3 }, 2);
	int scalar = 3;
	MathVector<int> result({ 3, 6, 9 }, 2);

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

TEST(TestMathVectorLib, can_add_mvectors_with_assign_with_start_index) {
	// Arrange
	MathVector<int> mvector_1({ 1, 2, 3 }, 1);
	MathVector<int> mvector_2({ 4, 5, 6 }, 1);
	MathVector<int> result({ 5, 7, 9 }, 1);

	// Act
	mvector_1 += mvector_2;

	// Assert
	EXPECT_EQ(result, mvector_1);
}

TEST(TestMathVectorLib, can_add_mvectors_with_assign_with_different_start_index) {
	// Arrange
	MathVector<int> mvector_1({ 4, 5 }, 2);
	MathVector<int> mvector_2({ 1, 2, 3, 4 });
	MathVector<int> result({ 1, 2, 7, 9 });

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

TEST(TestMathVectorLib, can_sub_mvectors_with_assign_with_start_index) {
	// Arrange
	MathVector<int> mvector_1({ 1, 2, 3 }, 1);
	MathVector<int> mvector_2({ 4, 5, 6 }, 1);
	MathVector<int> result({ -3, -3, -3 }, 1);

	// Act
	mvector_1 -= mvector_2;

	// Assert
	EXPECT_EQ(result, mvector_1);
}

TEST(TestMathVectorLib, can_sub_mvectors_with_assign_with_different_start_index) {
	// Arrange
	MathVector<int> mvector_1({ 4, 5 }, 2);
	MathVector<int> mvector_2({ 1, 2, 3, 4 });
	MathVector<int> result({ -1, -2, 1, 1 });

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

TEST(TestMathVectorLib, can_mult_scalar_with_assign_with_start_index) {
	// Arrange
	MathVector<int> mvector({ 1, 2, 3 }, 1);
	int scalar = 3;
	MathVector<int> result({ 3, 6, 9 }, 1);

	// Act
	mvector *= scalar;

	// Assert
	EXPECT_EQ(result, mvector);
}

TEST(TestMathVectorLib, can_access_with_operator_brackets) {
	// Arrange
	MathVector<int> mvector({ 1, 2, 3, 4 });

	//  Act & Assert
	EXPECT_EQ(1, mvector[0]);
}

TEST(TestMathVectorLib, can_access_with_operator_brackets_with_start_index) {
	// Arrange
	MathVector<int> mvector({ 1, 2, 3 }, 1);
	int zero_elem = mvector[0];

	//  Act & Assert
	EXPECT_EQ(0, zero_elem);
	EXPECT_EQ(1, mvector[1]);
}

TEST(TestMathVectorLib, can_access_with_method_at) {
	// Arrange
	MathVector<int> mvector({ 1, 2, 3 });

	//  Act & Assert
	EXPECT_EQ(1, mvector.at(0));
}

TEST(TestMathVectorLib, throw_when_try_access_with_method_at_out_of_range) {
	// Arrange
	MathVector<int> mvector({ 1, 2, 3 });

	// Act & Assert
	ASSERT_ANY_THROW(mvector.at(3));
}

TEST(TestMathVectorLib, can_access_with_method_at_with_start_index) {
	// Arrange
	MathVector<int> mvector({ 1, 2, 3, 4 }, 1);

	//  Act & Assert
	EXPECT_EQ(4, mvector.at(4));
}

TEST(TestMathVectorLib, throw_when_try_access_with_method_at_out_of_range_with_start_index) {
	// Arrange
	MathVector<int> mvector({ 1, 2, 3, 4 }, 1);

	// Act & Assert
	ASSERT_ANY_THROW(mvector.at(5));
}
