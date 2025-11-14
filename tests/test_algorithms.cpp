// Copyright 2025 Viktoria Buzlaeva

#include <gtest/gtest.h>
#include "../lib_algorithms/algorithms.h"
#include "../lib_circle/circle.h"
#include "../lib_sphere/sphere.h"

#define EPSILON 0.000001

TEST(TestAlgorithmsLib, can_determine_coincide_circles) {
	// Arrange
	Circle circle(2, 3, 3);

	// Act
	TypeOfCrossing res = find_type_of_crossing(circle, circle);

	// Assert
	EXPECT_EQ(Coincide, res);
}

TEST(TestAlgorithmsLib, can_determine_not_intersect_circles) {
	// Arrange
	Circle circle1(2, 0, 3);
	Circle circle2(2, 8, 3);

	// Act
	TypeOfCrossing res = find_type_of_crossing(circle1, circle2);

	// Assert
	EXPECT_EQ(NotIntersect, res);
}

TEST(TestAlgorithmsLib, can_determine_intersect_circles) {
	// Arrange
	Circle circle1(3, 1, 2);
	Circle circle2(3, 3, 3);

	// Act
	TypeOfCrossing res = find_type_of_crossing(circle1, circle2);

	// Assert
	EXPECT_EQ(Intersect, res);
}

TEST(TestAlgorithmsLib, can_determine_touch_circles) {
	// Arrange
	Circle circle1(1, 3, 0);
	Circle circle2(1, 3, 2);

	// Act
	TypeOfCrossing res = find_type_of_crossing(circle1, circle2);

	// Assert
	EXPECT_EQ(Touch, res);
}

TEST(TestAlgorithmsLib, can_determine_coincide_spheres) {
	// Arrange
	Sphere sphere(2, 3, 3, 3);

	// Act
	TypeOfCrossing res = find_type_of_crossing(sphere, sphere);

	// Assert
	EXPECT_EQ(Coincide, res);
}

TEST(TestAlgorithmsLib, can_determine_not_intersect_spheres) {
	// Arrange
	Sphere sphere1(2, 0, 3, 8);
	Sphere sphere2(2, 8, 3, 9);

	// Act
	TypeOfCrossing res = find_type_of_crossing(sphere1, sphere2);

	// Assert
	EXPECT_EQ(NotIntersect, res);
}

TEST(TestAlgorithmsLib, can_determine_intersect_spheres) {
	// Arrange
	Sphere sphere1(3, 1, 2, 8);
	Sphere sphere2(3, 3, 3, 7);

	// Act
	TypeOfCrossing res = find_type_of_crossing(sphere1, sphere2);

	// Assert
	EXPECT_EQ(Intersect, res);
}

TEST(TestAlgorithmsLib, can_determine_touch_spheres) {
	// Arrange
	Sphere sphere1(1, 3, 0, 4);
	Sphere sphere2(1, 3, 2, 4);

	// Act
	TypeOfCrossing res = find_type_of_crossing(sphere1, sphere2);

	// Assert
	EXPECT_EQ(Touch, res);
}

TEST(TestAlgorithmsLib, can_check_correct_brackets_1) {
	std::string str = "()";

	EXPECT_EQ(true, check_brackets(str));
}

TEST(TestAlgorithmsLib, can_check_uncorrect_brackets_1) {
	std::string str = "((";

	EXPECT_EQ(false, check_brackets(str));
}

TEST(TestAlgorithmsLib, can_check_correct_brackets_2) {
	std::string str = "({})[(){}]";

	EXPECT_EQ(true, check_brackets(str));
}

TEST(TestAlgorithmsLib, can_check_uncorrect_brackets_2) {
	std::string str = "({}})";

	EXPECT_EQ(false, check_brackets(str));
}

TEST(TestAlgorithmsLib, can_check_uncorrect_brackets_3) {
	std::string str = "((())))";

	EXPECT_EQ(false, check_brackets(str));
}

TEST(TestAlgorithmsLib, can_check_correct_expression) {
	std::string expr = "3 * (15 + (x + y) * (2 * x - 7 * y^2))";

	ASSERT_NO_THROW(read_expression(expr));
}

TEST(TestAlgorithmsLib, can_check_uncorrect_expression_1) {
	std::string expr = "3 * (15 + (x y) * (2 * x - 7 * y^2))";

	ASSERT_ANY_THROW(read_expression(expr));
}

TEST(TestAlgorithmsLib, can_check_uncorrect_expression_2) {
	std::string expr = "3 * (15 + (x + y) * (2 * x - 7 * y^))";

	ASSERT_ANY_THROW(read_expression(expr));
}

TEST(TestAlgorithmsLib, can_check_uncorrect_expression_3) {
	std::string expr = "((x + y) * (x - y)";

	ASSERT_ANY_THROW(read_expression(expr));
}

TEST(TestAlgorithmsLib, can_check_uncorrect_expression_4) {
	std::string expr = "3 * (15 + (x + y) *";

	ASSERT_ANY_THROW(read_expression(expr));
}

TEST(TestAlgorithmsLib, can_check_uncorrect_expression_5) {
	std::string expr = "* (15 + (x + y) * (2 * x - 7 * y^2))";

	ASSERT_ANY_THROW(read_expression(expr));
}

TEST(TestAlgorithmsLib, can_check_uncorrect_expression_6) {
	std::string expr = "(x + y) * (x - y))";

	ASSERT_ANY_THROW(read_expression(expr));
}

TEST(TestAlgoritmsLib, can_check_empty_list_1_alg) {
	List<int> list;

	EXPECT_FALSE(is_looped_1(list));
}

TEST(TestAlgoritmsLib, can_check_one_elem_list_1_alg) {
	List<int> list;
	
	list.push_back(1);

	EXPECT_FALSE(is_looped_1(list));
}

TEST(TestAlgoritmsLib, can_check_not_looped_list_1_alg) {
	List<int> list;

	for (int i = 0; i < 5; i++) {
		list.push_back(i * 3 + 1);
	}

	EXPECT_FALSE(is_looped_1(list));
}

TEST(TestAlgoritmsLib, can_check_looped_list_1_alg) {
	List<int> list;
	
	for (int i = 0; i < 5; i++) {
		list.push_back(i * 3 + 1);
	}

	list.tail()->next = list.head()->next->next;

	EXPECT_TRUE(is_looped_1(list));

	list.tail()->next = nullptr;
}

TEST(TestAlgoritmsLib, can_check_empty_list_2_alg) {
	List<int> list;

	EXPECT_FALSE(is_looped_2(list));
}

TEST(TestAlgoritmsLib, can_check_one_elem_list_2_alg) {
	List<int> list;

	list.push_back(1);

	EXPECT_FALSE(is_looped_2(list));
}

TEST(TestAlgoritmsLib, can_check_not_looped_list_2_alg) {
	List<int> list;

	for (int i = 0; i < 5; i++) {
		list.push_back(i * 3 + 1);
	}

	EXPECT_FALSE(is_looped_2(list));
}

TEST(TestAlgoritmsLib, can_check_looped_list_2_alg) {
	List<int> list;

	for (int i = 0; i < 5; i++) {
		list.push_back(i * 3 + 1);
	}

	list.tail()->next = list.head()->next->next;

	EXPECT_TRUE(is_looped_2(list));

	list.tail()->next = nullptr;
}

TEST(TestAlgoritmsLib, can_return_nullptr_not_looped_list_3_alg) {
	List<int> list;

	for (int i = 0; i < 5; i++) {
		list.push_back(i * 3 + 1);
	}

	EXPECT_EQ(nullptr, find_loop(list));
}

TEST(TestAlgoritmsLib, can_find_loop_3_alg) {
	List<int> list;

	for (int i = 0; i < 5; i++) {
		list.push_back(i * 3 + 1);
	}

	list.tail()->next = list.head()->next->next;

	EXPECT_EQ(list.head()->next->next, find_loop(list));

	list.tail()->next = nullptr;
}
