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

TEST(TestAlgorithmsLib, can_find_one_local_min) {
    // Arrange
    Matrix<int> matrix({ {1, 2, 3},
                        { 4, 5, 6 },
                        { 7, 8, 9 } });

    // Act
    int value = find_local_min_matrix(matrix);

    // Assert
    EXPECT_EQ(1, value);
}

TEST(TestAlgorithmsLib, can_find_any_local_min) {
    // Arrange
    Matrix<int> matrix({ {3, 1, 2},
                        { 5, 8, 4 },
                        { 7, 6, 9 } });

    // Act
    int local_min_1 = 1;
    int local_min_2 = 6;
    int value = find_local_min_matrix(matrix);
    bool actual_result = (local_min_1 == value) || (local_min_2 == value);

    // Assert
    bool expected_result = true;
    EXPECT_EQ(expected_result, actual_result);
}

TEST(TestAlgorithmsLib, can_count_islands) {
    Matrix<int> matrix_1({
                        { 0, 0, 0, 0, 0, 0 },
                        { 0, 0, 0, 0, 0, 0 },
                        { 0, 0, 0, 0, 0, 0 },
                        { 0, 0, 0, 0, 0, 0 },
                        { 0, 0, 0, 0, 0, 0 },
                        { 0, 0, 0, 0, 0, 0 } });

    Matrix<int> matrix_2({
                        { 1, 0, 0, 0, 0, 1 },
                        { 0, 0, 0, 0, 1, 1 },
                        { 1, 1, 0, 0, 0, 1 },
                        { 1, 0, 0, 0, 0, 1 },
                        { 1, 0, 0, 1, 0, 1 } });

    Matrix<int> matrix_3({
                        { 1, 0, 0, 0, 0, 1 },
                        { 0, 0, 0, 0, 1, 1 },
                        { 1, 1, 0, 0, 0, 1 },
                        { 0, 0, 0, 0, 0, 1 },
                        { 1, 1, 0, 1, 0, 1 },
                        { 0, 1, 0, 1, 0, 1 } });

    Matrix<int> matrix_4({
                        { 1, 1, 1, 1, 1, 1 },
                        { 1, 1, 1, 1, 1, 1 },
                        { 1, 1, 1, 1, 1, 1 },
                        { 1, 1, 1, 1, 1, 1 },
                        { 1, 1, 1, 1, 1, 1 },
                        { 1, 1, 1, 1, 1, 1 } });

    Matrix<int> matrix_5({ { 1 } });

    Matrix<int> matrix_6({ { 0 } });

    Matrix<int> matrix_7({
                        { 0, 0, 0, 0, 0, 1 },
                        { 0, 0, 0, 1, 1, 1 },
                        { 1, 1, 1, 1, 0, 1 },
                        { 0, 1, 0, 1, 0, 1 },
                        { 1, 1, 0, 1, 0, 1 },
                        { 0, 1, 0, 1, 0, 1 } });

    EXPECT_EQ(0, find_number_of_islands(matrix_1));
    EXPECT_EQ(4, find_number_of_islands(matrix_2));
    EXPECT_EQ(5, find_number_of_islands(matrix_3));
    EXPECT_EQ(1, find_number_of_islands(matrix_4));
    EXPECT_EQ(1, find_number_of_islands(matrix_5));
    EXPECT_EQ(0, find_number_of_islands(matrix_6));
    EXPECT_EQ(1, find_number_of_islands(matrix_7));
}

TEST(TestAlgorithmsLib, can_generate_labyrinth) {
    ASSERT_ANY_THROW(generate_labyrinth(1, 16, 4, 4));
    ASSERT_ANY_THROW(generate_labyrinth(1, 26, 5, 5));
    ASSERT_ANY_THROW(generate_labyrinth(1, 17, 5, 5));
    ASSERT_NO_THROW(generate_labyrinth(1, 25, 5, 5));
}

TEST(TestAlgorithmsLib, can_check_correct_brackets) {
    std::string str = "[(()){}]";

    EXPECT_EQ(true, check_brackets(str));
}

TEST(TestAlgorithmsLib, can_check_uncorrect_brackets_1) {
    std::string str = "(()";

    EXPECT_EQ(false, check_brackets(str));
}

TEST(TestAlgorithmsLib, can_check_uncorrect_brackets_2) {
    std::string str = "({})[(){]]";

    EXPECT_EQ(false, check_brackets(str));
}

TEST(TestAlgorithmsLib, can_check_uncorrect_brackets_3) {
    std::string str = "({}))";

    EXPECT_EQ(false, check_brackets(str));
}

TEST(TestAlgorithmsLib, can_check_correct_expressions) {
    std::string expr_1 = "3 * (15 + (x + y) * (2 * x - 7 * y^2))";
    std::string expr_2 = "-x * (-x + y) * (x - (-y))";

    ASSERT_NO_THROW(read_expression(expr_1));
    ASSERT_NO_THROW(read_expression(expr_2));
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
    std::string expr = "3 * 15 + (x + y) *";

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

TEST(TestAlgorithmsLib, can_check_uncorrect_expression_7) {
    std::string expr_1 = "(x + * y) * (x - y)";
    std::string expr_2 = "(x + -y) * (x - y)";

    ASSERT_ANY_THROW(read_expression(expr_1));
    ASSERT_ANY_THROW(read_expression(expr_2));
}

TEST(TestAlgorithmsLib, can_check_uncorrect_expression_8) {
    std::string expr = "(x + y) & (x - y)";

    ASSERT_ANY_THROW(read_expression(expr));
}

TEST(TestAlgoritmsLib, can_check_empty_list) {
    List<int> list;

    EXPECT_FALSE(is_looped_1(list));
    EXPECT_FALSE(is_looped_2(list));
    EXPECT_EQ(nullptr, find_loop(list));
}

TEST(TestAlgoritmsLib, can_check_one_elem_list) {
    List<int> list;
    
    list.push_back(1);

    EXPECT_FALSE(is_looped_1(list));
    EXPECT_FALSE(is_looped_2(list));
    EXPECT_EQ(nullptr, find_loop(list));
}

TEST(TestAlgoritmsLib, can_check_not_looped_list) {
    List<int> list;

    for (int i = 0; i < 5; i++) {
        list.push_back(i * 3 + 1);
    }

    EXPECT_FALSE(is_looped_1(list));
    EXPECT_FALSE(is_looped_2(list));
    EXPECT_EQ(nullptr, find_loop(list));
}

TEST(TestAlgoritmsLib, can_check_looped_list) {
    List<int> list;
    
    for (int i = 0; i < 5; i++) {
        list.push_back(i * 3 + 1);
    }

    list.tail()->next = list.head()->next->next;

    EXPECT_TRUE(is_looped_1(list));
    EXPECT_TRUE(is_looped_2(list));
    EXPECT_EQ(list.head()->next->next, find_loop(list));

    list.tail()->next = nullptr;
}

TEST(TestAlgoritmsLib, can_check_looped_list_with_loop_in_head) {
    List<int> list;

    for (int i = 0; i < 5; i++) {
        list.push_back(i * 3 + 1);
    }

    list.tail()->next = list.head();

    EXPECT_TRUE(is_looped_1(list));
    EXPECT_TRUE(is_looped_2(list));
    EXPECT_EQ(list.head(), find_loop(list));

    list.tail()->next = nullptr;
}
