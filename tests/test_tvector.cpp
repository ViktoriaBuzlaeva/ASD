// Copyright 2025 Viktoria Buzlaeva

#include <gtest/gtest.h>
#include "../lib_tvector/tvector.h"

#define EPSILON 0.000001

TEST(TestTVectorLib, can_create) {
	// Arrange & Act
	TVector<int> v;

	// Assert
	EXPECT_EQ(0, v.size());
	EXPECT_EQ(15, v.capacity());
}

TEST(TestTVectorLib, can_create_with_size) {
	// Arrange & Act
	TVector<int> v(30);

	// Assert
	EXPECT_EQ(30, v.size());
	EXPECT_EQ(45, v.capacity());
}

TEST(TestTVectorLib, can_create_with_array_and_size) {
	// Arrange
	int mass[4] = { 1, 2, 3, 4 };
	TVector<int> v(4, mass);

	// Act
	bool actual_result = true;
	for (int i = 0; i < v.size(); i++) {
		actual_result &= (*(v.data() + i) == mass[i]);
	}

	// Assert
	bool expected_result = true;
	EXPECT_EQ(4, v.size());
	EXPECT_EQ(15, v.capacity());
	EXPECT_EQ(expected_result, actual_result);
}

TEST(TestTVectorLib, can_create_with_array_and_size_other) {
	// Arrange
	int mass[4] = { 1, 2, 3, 4 };
	TVector<int> v(4, { 1, 2, 3, 4 });

	// Act
	bool actual_result = true;
	for (int i = 0; i < v.size(); i++) {
		actual_result &= (*(v.data() + i) == mass[i]);
	}

	// Assert
	bool expected_result = true;
	EXPECT_EQ(4, v.size());
	EXPECT_EQ(15, v.capacity());
	EXPECT_EQ(expected_result, actual_result);
}

TEST(TestTVectorLib, can_create_with_array) {
	// Arrange
	int mass[4] = { 1, 2, 3, 4 };
	TVector<int> v({ 1, 2, 3, 4 });

	// Act
	bool actual_result = true;
	for (int i = 0; i < v.size(); i++) {
		actual_result &= (*(v.data() + i) == mass[i]);
	}

	// Assert
	bool expected_result = true;
	EXPECT_EQ(4, v.size());
	EXPECT_EQ(15, v.capacity());
	EXPECT_EQ(expected_result, actual_result);
}

TEST(TestTVectorLib, can_create_copy) {
	// Arrange
	int mass[4] = { 1, 2, 3, 4 };
	TVector<int> v1({ 1, 2, 3, 4 });
	TVector<int> v2(v1);

	// Act
	bool actual_result = true;
	for (int i = 0; i < v2.size(); i++) {
		actual_result &= (*(v2.data() + i) == mass[i]);
	}

	// Assert
	bool expected_result = true;
	EXPECT_EQ(4, v2.size());
	EXPECT_EQ(15, v2.capacity());
	EXPECT_EQ(expected_result, actual_result);
}

TEST(TestTVectorLib, throw_when_create_copy) {
	// Arrange
	TVector<int>* v1 = NULL;

	// Act & Assert
	ASSERT_ANY_THROW(TVector<int> v2(*v1));
}

TEST(TestTVectorLib, can_create_with_size_and_value) {
	// Arrange
	int mass[4] = { 4, 4, 4, 4 };
	TVector<int> v(4, 4);

	// Act
	bool actual_result = true;
	for (int i = 0; i < v.size(); i++) {
		actual_result &= (*(v.data() + i) == mass[i]);
	}

	// Assert
	bool expected_result = true;
	EXPECT_EQ(4, v.size());
	EXPECT_EQ(15, v.capacity());
	EXPECT_EQ(expected_result, actual_result);
}

TEST(TestTVectorLib, can_access_front_elem) {
	// Arrange
	int first_elem = 1;
	int value = 4;
	TVector<int> v{ 1, 2, 3, 4 };

	// Act
	bool actual_result = (v.front() == first_elem);  // get
	v.front() = 4;  // set
	actual_result &= (v.front() == value);

	// Assert
	bool expected_result = true;
	EXPECT_TRUE(expected_result, actual_result);
}

TEST(TestTVectorLib, can_access_back_elem) {
	// Arrange
	int last_elem = 4;
	int value = 1;
	TVector<int> v{ 1, 2, 3, 4 };

	// Act
	
	bool actual_result = (v.back() == last_elem);  // get
	v.back() = 1;  // set
	actual_result &= (v.back() == value);

	// Assert
	bool expected_result = true;
	EXPECT_EQ(expected_result, actual_result);
}

TEST(TestTVectorLib, throw_when_access_front_elem_in_empty) {
	// Arrange
	TVector<int> v;

	// Act & Assert
	ASSERT_ANY_THROW(v.front());
}

TEST(TestTVectorLib, throw_when_access_back_elem_in_empty) {
	// Arrange
	TVector<int> v;

	// Act & Assert
	ASSERT_ANY_THROW(v.back());
}

TEST(TestTVectorLib, can_comp_correctly_with_eq) {
	// Arrange
	TVector<int> v1({ 1, 2, 3, 4 });
	TVector<int> v2({ 1, 2, 3, 4 });

	// Act & Assert
	EXPECT_TRUE(v1 == v2);
}

TEST(TestTVectorLib, can_comp_correctly_with_not_eq) {
	// Arrange
	TVector<int> v1({ 1, 2, 3, 4 });
	TVector<int> v2({ 1, 2, 3 });

	// Act & Assert
	EXPECT_FALSE(v1 == v2);
}

TEST(TestTVectorLib, can_comp_correctly_with_eq_other) {
	// Arrange
	TVector<int> v1({ 1, 2, 3, 4 });
	TVector<int> v2({ 1, 2, 3, 4 });

	// Act & Assert
	EXPECT_FALSE(v1 != v2);
}

TEST(TestTVectorLib, can_comp_correctly_with_not_eq_other) {
	// Arrange
	TVector<int> v1({ 1, 2, 3, 4 });
	TVector<int> v2({ 1, 2, 3 });

	// Act & Assert
	EXPECT_TRUE(v1 != v2);
}

TEST(TestTVectorLib, can_assign_with_size_and_value) {
	// Arrange
	TVector<int> v1(16, 2);
	TVector<int> v2({ 1, 1, 1, 1, 1 });

	// Act
	v1.assign(5, 1);

	// Assert
	EXPECT_TRUE(v1 == v2);
}

TEST(TestTVectorLib, can_assign_with_array) {
	// Arrange
	TVector<int> v1;
	TVector<int> v2({ 1, 1, 1, 1, 1 });

	// Act
	v1.assign({ 1, 1, 1, 1, 1 });

	// Assert
	EXPECT_TRUE(v1 == v2);
}

TEST(TestTVectorLib, can_assign_tvector_with_reset_memory) {
	// Arrange
	TVector<int> v1;
	TVector<int> v2(31, 2);
	TVector<int> v3(16, 1);

	// Act
	v1.assign(16, 1);
	v2.assign(16, 1);

	// Assert
	EXPECT_EQ(v1, v3);
	EXPECT_EQ(v1.size(), v3.size());
	EXPECT_EQ(v1.capacity(), v3.capacity());
	EXPECT_EQ(v2, v3);
	EXPECT_EQ(v2.size(), v3.size());
	EXPECT_NE(v2.capacity(), v3.capacity());
}

TEST(TestTVectorLib, can_assign_with_operator) {
	// Arrange
	TVector<int> v1({ 1, 2, 3, 4 });
	TVector<int> v2({ 1, 2 });

	// Act
	v1 = v2;

	// Assert
	EXPECT_TRUE(v1 == v2);
}

TEST(TestTVectorLib, can_access_elem_at_pos) {
	// Arrange
	TVector<int> v{ 1, 2, 3, 4 };
	int elem = 3;
	int value = 1;

	// Act
	
	bool actual_result = (v.at(2) == elem);  // get
	v.at(2) = 1;  // set
	actual_result &= (v.at(2) == value);

	// Assert
	bool expected_result = true;
	EXPECT_EQ(expected_result, actual_result);
}

TEST(TestTVectorLib, throw_when_access_elem_at_out_of_range_pos) {
	// Arrange
	TVector<int> v(6);

	// Act & Assert
	ASSERT_ANY_THROW(v.at(6));
}

TEST(TestTVectorLib, can_access_with_operator_brackets) {
	// Arrange
	TVector<int> v{ 1, 2, 3, 4 };
	int elem = 3;
	int value = 1;

	// Act
	
	bool actual_result = (v[2] == elem);  // get
	v[2] = 1;  // set
	actual_result &= (v[2] == value);

	// Assert
	bool expected_result = true;
	EXPECT_EQ(expected_result, actual_result);
}

TEST(TestTVectorLib, can_reserve_correctly_with_less_cap) {
	// Arrange
	TVector<int> v(16, 2);

	// Act
	v.reserve(17);

	// Assert
	EXPECT_EQ(16, v.size());
	EXPECT_EQ(30, v.capacity());
}

TEST(TestTVectorLib, can_reserve_correctly_with_greater_cap) {
	// Arrange
	TVector<int> v(14, 2);

	// Act
	v.reserve(17);

	// Assert
	EXPECT_EQ(14, v.size());
	EXPECT_EQ(17, v.capacity());
}

TEST(TestTVectorLib, can_resize_correctly_with_less_size) {
	// Arrange
	TVector<int> v(14, 2);

	// Act
	v.resize(10);

	// Assert
	EXPECT_EQ(10, v.size());
	EXPECT_EQ(15, v.capacity());
}

TEST(TestTVectorLib, can_resize_correctly_with_less_size_and_cap) {
	// Arrange
	TVector<int> v(16, 2);

	// Act
	v.resize(10);

	// Assert
	EXPECT_EQ(10, v.size());
	EXPECT_EQ(15, v.capacity());
}

TEST(TestTVectorLib, can_resize_correctly_with_greater_size) {
	// Arrange
	TVector<int> v(10, 2);

	// Act
	v.resize(13);

	// Assert
	EXPECT_EQ(13, v.size());
	EXPECT_EQ(15, v.capacity());
}

TEST(TestTVectorLib, can_resize_correctly_with_greater_size_and_cap) {
	// Arrange
	TVector<int> v(10, 2);

	// Act
	v.resize(16);

	// Assert
	EXPECT_EQ(16, v.size());
	EXPECT_EQ(30, v.capacity());
}

TEST(TestTVectorLib, can_resize_correctly_with_new_value) {
	// Arrange
	TVector<int> v1(10, 2);
	TVector<int> v2({ 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 4, 4, 4, 4, 4, 4 });

	// Act
	v1.resize(16, 4);

	// Assert
	EXPECT_EQ(v1, v2);
	EXPECT_EQ(v1.capacity(), v2.capacity());
}

TEST(TestTVectorLib, can_correctly_push_front) {
	// Arrange
	TVector<int> v1{ 2, 3, 4, 5 };
	TVector<int> v2{ 1, 2, 3, 4, 5 };

	// Act
	v1.push_front(1);

	// Assert
	EXPECT_EQ(v1, v2);
	EXPECT_EQ(v1.capacity(), v2.capacity());
}

TEST(TestTVectorLib, can_correctly_push_front_with_reset_memory) {
	// Arrange
	TVector<int> v1(14, 2);
	TVector<int> v2{ 3, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 };

	// Act
	v1.push_front(1);
	v1.push_front(3);

	// Assert
	EXPECT_EQ(v1, v2);
	EXPECT_EQ(v1.capacity(), v2.capacity());
}

TEST(TestTVectorLib, can_correctly_push_front_empty_tvector) {
	// Arrange
	TVector<int> v1;
	TVector<int> v2({ 1 });

	// Act
	v1.push_front(1);

	// Assert
	EXPECT_EQ(v2, v1);
}

TEST(TestTVectorLib, can_correctly_push_back) {
	// Arrange
	TVector<int> v1{ 1, 2, 3, 4 };
	TVector<int> v2{ 1, 2, 3, 4, 5 };

	// Act
	v1.push_back(5);

	// Assert
	EXPECT_EQ(v1, v2);
	EXPECT_EQ(v1.capacity(), v2.capacity());
}

TEST(TestTVectorLib, can_correctly_push_back_with_reset_memory) {
	// Arrange
	TVector<int> v1(14, 2);
	TVector<int> v2{ 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 3 };

	// Act
	v1.push_back(1);
	v1.push_back(3);

	// Assert
	EXPECT_EQ(v1, v2);
	EXPECT_EQ(v1.capacity(), v2.capacity());
}

TEST(TestTVectorLib, can_correctly_push_back_empty_tvector) {
	// Arrange
	TVector<int> v1;
	TVector<int> v2({ 10 });

	// Act
	v1.push_back(10);

	// Assert
	EXPECT_EQ(v2, v1);
}

TEST(TestTVectorLib, can_correctly_insert_first) {
	// Arrange
	TVector<int> v1{ 1, 2, 4, 5 };
	TVector<int> v2{ 1, 2, 3, 4, 5 };

	// Act
	v1.insert(2, 3);

	// Assert
	EXPECT_EQ(v1, v2);
	EXPECT_EQ(v1.capacity(), v2.capacity());
}

TEST(TestTVectorLib, can_correctly_insert_second) {
	// Arrange
	TVector<int> v1{ 1, 2, 3, 4, 5 };
	TVector<int> v2{ 1, 2, 3, 4, 5, 6, 6, 6 };

	// Act
	v1.insert(5, 3, 6);

	// Assert
	EXPECT_EQ(v1, v2);
	EXPECT_EQ(v1.capacity(), v2.capacity());
}

TEST(TestTVectorLib, can_correctly_insert_third) {
	// Arrange
	TVector<int> v1{ 1, 2, 3, 4, 5, 6, 6, 6 };
	TVector<int> v2{ 1, 2, 3, 4, 5, 6, 6, 8, 9, 10, 6 };

	// Act
	v1.insert(7, { 8, 9, 10 });

	// Assert
	EXPECT_EQ(v1, v2);
	EXPECT_EQ(v1.capacity(), v2.capacity());
}

TEST(TestTVectorLib, can_correctly_insert_with_reset_memory) {
	// Arrange
	TVector<int> v1(14, 2);
	TVector<int> v2{ 2, 2, 111, 2, 2, 2, 2, 2, 2, 333, 2, 2, 2, 2, 2, 2 };

	// Act
	v1.insert(2, 111);
	v1.insert(9, 333);

	// Assert
	EXPECT_EQ(v1, v2);
	EXPECT_EQ(v1.capacity(), v2.capacity());
}

TEST(TestTVectorLib, can_correctly_insert_empty_tvector) {
	// Arrange
	TVector<int> v1;
	TVector<int> v2({ 88 });

	// Act
	v1.insert(0, 88);

	// Assert
	EXPECT_EQ(v2, v1);
}

TEST(TestTVectorLib, can_correctly_insert_after_delete) {
	// Arrange
	int* mass = new int[100];
	for (int i = 0; i < 100; i++) {
		mass[i] = i + 1;
	}
	TVector<int> v1(100, mass);
	TVector<int> v2({ 2, 3, 5, 12, 55, 13, 33, 44, 55, 14, 15,
		16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31,
		32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47,
		48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63,
		64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79,
		80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95,
		96, 97, 98, 99 });

	// Act
	v1.erase(3);
	v1.pop_front();
	v1.pop_back();
	v1.erase(3, 6);
	v1.insert(4, 55);
	v1.insert(6, { 33, 44, 55 });

	// Assert
	EXPECT_EQ(v2, v1);
}

TEST(TestTVectorLib, throw_when_insert_out_of_range) {
	// Arrange
	TVector<int> v{ 1, 2, 3, 4, 5 };

	// Act & Assert
	ASSERT_ANY_THROW(v.insert(7, 6));
}

TEST(TestTVectorLib, can_clear_tvector) {
	// Arrange
	TVector<int> v{ 1, 2, 3, 4, 5 };

	// Act
	v.clear();

	// Assert
	EXPECT_EQ(0, v.size());
	EXPECT_EQ(15, v.capacity());
}

TEST(TestTVectorLib, can_correctly_pop_front) {
	// Arrange
	TVector<int> v1{ 1, 2, 3, 4, 5 };
	TVector<int> v2{ 3, 4, 5 };

	// Act
	v1.pop_front();
	v1.pop_front();

	// Assert
	EXPECT_EQ(v1, v2);
	EXPECT_EQ(v1.capacity(), v2.capacity());
}

TEST(TestTVectorLib, can_correctly_pop_front_without_reset_memory_for_delete) {
	// Arrange
	TVector<int> v1(14, 2);
	TVector<int> v2{ 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 14 };

	// Act
	v1.push_back(14);
	v1.pop_front();

	// Assert
	EXPECT_EQ(v1, v2);
	EXPECT_NE(v1.capacity(), v2.capacity());
	EXPECT_NE(*(v1.data() + 13), *(v2.data() + 13));
}

TEST(TestTVectorLib, throw_when_pop_front_empty_tvector) {
	// Arrange
	TVector<int> v;

	// Act & Assert
	ASSERT_ANY_THROW(v.pop_front());
}

TEST(TestTVectorLib, can_correctly_pop_back) {
	// Arrange
	TVector<int> v1{ 1, 2, 3, 4, 5 };
	TVector<int> v2{ 1, 2, 3, 4 };

	// Act
	v1.pop_back();

	// Assert
	EXPECT_EQ(v1, v2);
	EXPECT_EQ(v1.capacity(), v2.capacity());
}

TEST(TestTVectorLib, throw_when_pop_back_empty_tvector) {
	// Arrange
	TVector<int> v;

	// Act & Assert
	ASSERT_ANY_THROW(v.pop_back());
}

TEST(TestTVectorLib, can_correctly_erase) {
	// Arrange
	TVector<int> v1{ 1, 2, 3, 4, 5 };
	TVector<int> v2{ 1, 5 };

	// Act
	v1.erase(3);
	v1.erase(1, 2);

	// Assert
	EXPECT_EQ(v1, v2);
	EXPECT_EQ(v1.capacity(), v2.capacity());
}

TEST(TestTVectorLib, can_correctly_erase_without_reset_memory_for_delete) {
	// Arrange
	TVector<int> v1(14, 2);
	TVector<int> v2{ 2, 2, 2, 5, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 };

	// Act
	v1.insert(3, 4);
	v1.erase(3);
	v1.insert(3, 5);

	// Assert
	EXPECT_EQ(v1, v2);
	EXPECT_EQ(v1.capacity(), v2.capacity());
}

TEST(TestTVectorLib, can_correctly_erase_after_delete) {
	// Arrange
	int* mass = new int[100];
	for (int i = 0; i < 100; i++) {
		mass[i] = i + 1;
	}
	TVector<int> v1(100, mass);
	TVector<int> v2({ 2, 3, 5, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23,
		24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
		41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57,
		58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74,
		75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91,
		92, 93 });

	// Act
	v1.erase(3);
	v1.pop_front();
	v1.erase(3, 6);
	v1.erase(89);
	v1.erase(85, 6);

	// Assert
	EXPECT_EQ(v2, v1);
}

TEST(TestTVectorLib, throw_when_erase_empty_tvector) {
	// Arrange
	TVector<int> v;

	// Act & Assert
	ASSERT_ANY_THROW(v.erase(0));
}

TEST(TestTVectorLib, can_correctly_shrink_to_fit) {
	// Arrange
	TVector<int> v1(14, 2);
	TVector<int> v2({ 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 });

	// Act
	v1.insert(2, 333);
	v1.erase(2);
	bool actual_result = (*(v1.data() + 2) != *(v2.data() + 2));
	v1.shrink_to_fit();
	actual_result &= (*(v1.data() + 2) == *(v2.data() + 2));

	// Assert
	bool expected_result = true;
	EXPECT_EQ(expected_result, actual_result);
	EXPECT_EQ(v1, v2);
	EXPECT_NE(v1.capacity(), v2.capacity());
}

TEST(TestTVectorLib, can_correctly_replace_first) {
	// Arrange
	TVector<int> v1{ 1, 2, 3, 4, 5 };
	TVector<int> v2{ 1, 2, 333, 4, 5 };

	// Act
	v1.replace(2, 333);

	// Assert
	EXPECT_EQ(v1, v2);
	EXPECT_EQ(v1.capacity(), v2.capacity());
}

TEST(TestTVectorLib, can_correctly_replace_second) {
	// Arrange
	TVector<int> v1{ 1, 2, 333, 4, 5 };
	TVector<int> v2{ 1, 2, 3, 4, 5 };

	// Act
	v1.replace(v1.data() + 2, 3);

	// Assert
	EXPECT_EQ(v1, v2);
	EXPECT_EQ(v1.capacity(), v2.capacity());
}

TEST(TestTVectorLib, can_correctly_replace_after_delete_first) {
	// Arrange
	TVector<int> v1(14, 2);
	TVector<int> v2{ 2, 2, 333, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 };

	// Act
	v1.erase(2);
	v1.replace(2, 333);

	// Assert
	EXPECT_EQ(v1, v2);
	EXPECT_EQ(v1.capacity(), v2.capacity());
	EXPECT_NE(*(v1.data() + 2), *(v2.data() + 2));
}

TEST(TestTVectorLib, can_correctly_replace_after_delete_second) {
	// Arrange
	int* mass = new int[100];
	for (int i = 0; i < 100; i++) {
		mass[i] = i + 1;
	}
	TVector<int> v1(100, mass);
	TVector<int> v2({ 2, 3, 5, 7, 55, 9, 10, 11, 12, 13, 14, 15, 16,
		17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32,
		33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48,
		49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64,
		65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80,
		81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96,
		97, 98, 99 });

	// Act
	v1.erase(3);
	v1.pop_front();
	v1.pop_back();
	v1.erase(3);
	v1.replace(4, 55);

	// Assert=
	EXPECT_EQ(v2, v1);
}

TEST(TestTVectorLib, throw_when_replace_out_of_range_first) {
	// Arrange
	TVector<int> v{ 1, 2, 3, 4, 5 };

	// Act & Assert
	ASSERT_ANY_THROW(v.replace(5, 555));
}

TEST(TestTVectorLib, throw_when_replace_out_of_range_second) {
	// Arrange
	TVector<int> v{ 1, 2, 3, 4, 5 };

	// Act & Assert
	ASSERT_ANY_THROW(v.replace(v.data() + 5, 555));
}

TEST(TestTVectorLib, throw_when_replace_deleted_element) {
	// Arrange
	TVector<int> v(14, 2);

	// Act
	v.erase(2);

	// Assert
	ASSERT_ANY_THROW(v.replace(v.data() + 2, 555));
}

TEST(TestTVectorLib, can_correctly_find_first_element) {
	// Arrange
	TVector<int> v{ 1, 2, 3, 2, 5 };

	// Act
	int actual_result = find_first(v, 3);

	// Assert
	int expected_result = 2;
	EXPECT_EQ(expected_result, actual_result);
}

TEST(TestTVectorLib, throw_when_cannot_find_first_element) {
	// Arrange
	TVector<int> v{ 1, 2, 3, 4, 5 };

	// Act & Assert
	ASSERT_ANY_THROW(find_first(v, 6));
}

TEST(TestTVectorLib, can_correctly_find_last_element) {
	// Arrange
	TVector<int> v{ 1, 4, 3, 4, 5 };

	// Act
	int actual_result = find_last(v, 4);

	// Assert
	int expected_result = 3;
	EXPECT_EQ(expected_result, actual_result);
}

TEST(TestTVectorLib, throw_when_cannot_find_last_element) {
	// Arrange
	TVector<int> v{ 1, 2, 3, 4, 5 };

	// Act & Assert
	ASSERT_ANY_THROW(find_last(v, 6));
}

TEST(TestTVectorLib, can_correctly_find_all_elements) {
	// Arrange
	TVector<int> v{ 1, 2, 3, 4, 3 };

	// Act
	TVector<int> elems1(find_all(v, 3));

	// Assert
	TVector<int> elems2{ 2, 4 };
	EXPECT_EQ(elems2, elems1);
}

TEST(TestTVectorLib, throw_when_cannot_find_all_elements) {
	// Arrange
	TVector<int> v{ 1, 2, 3, 4, 5 };

	// Act & Assert
	ASSERT_ANY_THROW(find_all(v, 6));
}

TEST(TestTVectorLib, can_correctly_find_first_element_pointer) {
	// Arrange
	TVector<int> v{ 1, 2, 3, 4, 3 };

	// Act
	int* actual_result = find_first_pointer(v, 3);

	// Assert
	int* expected_result = v.data() + 2;
	EXPECT_EQ(expected_result, actual_result);
}

TEST(TestTVectorLib, throw_when_cannot_find_first_element_pointer) {
	// Arrange
	TVector<int> v{ 1, 2, 3, 4, 3 };

	// Act & Assert
	ASSERT_ANY_THROW(find_first_pointer(v, 6));
}

TEST(TestTVectorLib, can_correctly_find_last_element_pointer) {
	// Arrange
	TVector<int> v{ 1, 2, 3, 4, 3 };

	// Act
	int* actual_result = find_last_pointer(v, 3);

	// Assert
	int* expected_result = v.data() + 4;
	EXPECT_EQ(expected_result, actual_result);
}

TEST(TestTVectorLib, throw_when_cannot_find_last_element_pointer) {
	// Arrange
	TVector<int> v{ 1, 2, 3, 4, 3 };

	// Act & Assert
	ASSERT_ANY_THROW(find_last_pointer(v, 6));
}

TEST(TestTVectorLib, can_correctly_find_all_elements_pointers) {
	// Arrange
	TVector<int> v{ 1, 2, 3, 4, 3 };

	// Act
	TVector<int*> elems1(find_all_pointers(v, 3));

	// Assert
	TVector<int*> elems2{ v.data() + 2, v.data() + 4 };
	EXPECT_EQ(elems2, elems1);
}

TEST(TestTVectorLib, throw_when_cannot_find_all_elements_pointers) {
	// Arrange
	TVector<int> v{ 1, 2, 3, 4, 3 };

	// Act & Assert
	ASSERT_ANY_THROW(find_all(v, 6));
}

TEST(TestTVectorLib, can_correctly_replace_by_finding_pointer) {
	// Arrange
	TVector<int> v1({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16,
		17, 18, 19, 20, 7, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33,
		34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51,
		52, 53, 54, 7, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68,
		69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86,
		7, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100 });
	TVector<int> v2({ 1, 2, 3, 4, 5, 6, 7, 8, 99, 10, 11, 12, 13, 14, 15, 16,
		17, 18, 19, 20, 7, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33,
		34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51,
		52, 53, 54, 7, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68,
		69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86,
		7, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100 });

	// Act
	v1.replace(find_first_pointer(v1, 9), 99);

	// Assert
	EXPECT_EQ(v2, v1);
}

TEST(TestTVectorLib, can_shuffle) {
	// Arrange
	TVector<int> v1{ 1, 2, 3, 4, 5 };
	TVector<int> v2{ 1, 2, 3, 4, 5 };

	// Act
	shuffle(v1);

	// Assert
	EXPECT_EQ(v1.size(), v2.size());
	EXPECT_EQ(v1.capacity(), v2.capacity());
	EXPECT_NE(v1, v2);
}

TEST(TestTVectorLib, can_sort) {
	// Arrange
	TVector<int> v1{ 5, 2, 3, 1, 4 };
	TVector<int> v2{ 1, 2, 3, 4, 5 };

	// Act
	sort_hoare(v1);

	// Assert
	EXPECT_EQ(v1.size(), v2.size());
	EXPECT_EQ(v1.capacity(), v2.capacity());
	EXPECT_EQ(v1, v2);
}
