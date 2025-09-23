// Copyright 2025 Viktoria Buzlaeva

// #define EASY_EXAMPLE
#ifdef EASY_EXAMPLE

#include <iostream>
#include <iomanip>
#include "../lib_easy_example/easy_example.h"

int main() {
  int a, b;
  float result;

  a = 1; b = 4;

  try {
      result = division(a, b);
      std::cout << a << " / " << b << " = "
          << std::setprecision(2) << result << std::endl;
  } catch (std::exception err) {
      std::cerr << err.what() << std::endl;
  }

  a = 1; b = 0;

  try {
      result = division(a, b);
      std::cout << a << " / " << b << " = "
          << std::setprecision(2) << result << std::endl;
  } catch (std::exception err) {
      std::cerr << err.what() << std::endl;
  }

  return 0;
}

#endif  // EASY_EXAMPLE

// #define TYPE_OF_CROSSING
#ifdef TYPE_OF_CROSSING

#include <iostream>
#include "../lib_circle/circle.h"
#include "../lib_sphere/sphere.h"
#include "../lib_algorithms/algorithms.h"

void print_result(TypeOfCrossing res) {
    switch (res) {
    case Intersect:
        std::cout << "Intersect" << '\n';
        break;
    case NotIntersect:
        std::cout << "Not Intersect" << '\n';
        break;
    case Touch:
        std::cout << "Touch" << '\n';
        break;
    case Coincide:
        std::cout << "Coincide" << '\n';
        break;
    }
}

int main() {
    Point point_1(3, 2);
    Point point_2(3, 4);

    Circle circle_1(1, point_1);
    Circle circle_2(1, point_2);

    std::cout << "(" << circle_1.cent().x() << ", " << circle_1.cent().y() <<
        "); r = " << circle_1.rad() << '\n';
    std::cout << "(" << circle_2.cent().x() << ", " << circle_2.cent().y() <<
        "); r = " << circle_2.rad() << '\n';

    TypeOfCrossing res_2d = find_type_of_crossing(circle_1, circle_2);
    print_result(res_2d);

    Point3D point3d_1(3, 2, 0);
    Point3D point3d_2(3, 4, 0);

    Sphere sphere_1(5, point3d_1);
    Sphere sphere_2(5, point3d_2);

    std::cout << "(" << sphere_1.cent().x() << ", " << sphere_1.cent().y() <<
        ", " << sphere_1.cent().z() << "); r = " << sphere_1.rad() << '\n';
    std::cout << "(" << sphere_2.cent().x() << ", " << sphere_2.cent().y() <<
        ", " << sphere_2.cent().z() << "); r = " << sphere_2.rad() << '\n';

    TypeOfCrossing res_3d = find_type_of_crossing(sphere_1, sphere_2);
    print_result(res_3d);

    return 0;
}

#endif  // TYPE_OF_CROSSING

#define MATRIX_INTERFACE
#ifdef MATRIX_INTERFACE

#include <iostream>
#include "../lib_matrix/matrix.h"
#include "../lib_triangle_matrix/trianglematrix.h"

#define START_MENU_OPTIONS 2
#define MATRIX_MENU_OPTIONS 7
#define TRIANGLE_MATRIX_MENU_OPTIONS 5

void show_start_menu() {
    std::cout << "Matrix calculator\n";
    std::cout << "Choose option (input any key to exit):\n";
    std::cout << "1) Matrix;\n";
    std::cout << "2) Triangle matrix.\n";
}

void show_matrix_menu(Matrix<double>& A, Matrix<double>& B, Matrix<double>& C) {
    std::cout << "Matrix calculator\n";
    std::cout << "A = ";
    std::cout << A << std::endl;
    std::cout << "B = ";
    std::cout << B << std::endl;
    if (C != NULL) {
        std::cout << "C = " << std::endl;
    }
    std::cout << C << std::endl;
    std::cout << "Choose option (input any key to return start menu):\n";
    std::cout << "1) Input matrices (A, B);\n";
    std::cout << "2) Addition;\n";
    std::cout << "3) Subtraction;\n";
    std::cout << "4) Multiplication (matrices);\n";
    std::cout << "5) Multiplication (matrix and vector);\n";
    std::cout << "6) Multiplication (matrix and scalar);\n";
    std::cout << "7) Exit.\n";
}

void show_triangle_matrix_menu(Matrix<double>& A, Matrix<double>& B, Matrix<double>& C) {
    std::cout << "Matrix calculator\n";
    std::cout << "A = ";
    std::cout << A << std::endl;
    std::cout << "B = ";
    std::cout << B << std::endl;
    if (C != NULL) {
        std::cout << "C = ";
    }
    std::cout << C << std::endl;
    std::cout << "Choose option (input any key to return start menu):\n";
    std::cout << "1) Input matrices (A, B);\n";
    std::cout << "2) Addition;\n";
    std::cout << "3) Subtraction;\n";
    std::cout << "4) Multiplication;\n";
    std::cout << "5) Exit.\n";
}

char get_user_num(int options) {
    char user_num = '0';
    std::cout << "Your choice: ";
    std::cin >> user_num;
    return user_num;
}

template <class T>
T choose_matrix(T A, T B, T C) {
    while (1) {
        char name;
        std::cout << "Choose first matrix A, B or C:\n";
        std::cin >> name;
        switch (name) {
        case 'A':
            return A;
        case 'B':
            return B;
        case 'C':
            return C;
        default:
            std::cout << "Wrong input. Try again\n";
            break;
        }
    }
}

void show_matrix_input_menu() {
    std::cout << "Matrix calculator\n";
    std::cout << "Choose matrix's size\n";
    std::cout << "For example, 2 rows 3 columns:\n";
    std::cout << "1 2 3\n";
    std::cout << "4 5 6\n";
}

Matrix<double> input_matrix(std::string name) {
    std::cout << "Matrix " << name << "\n";
    int rows, cols;

    std::cout << "Rows: ";
    std::cin >> rows;

    std::cout << "Columns: ";
    std::cin >> cols;

    Matrix<double> matrix(rows, cols);

    std::cout << "Input elements separated by a space:\n";
    std::cin >> matrix;

    return matrix;
}

TriangleMatrix<double> input_triangle_matrix(std::string name) {
    std::cout << "Matrix " << name << "\n";
    int rows, cols;

    std::cout << "Rows: ";
    std::cin >> rows;

    std::cout << "Columns: ";
    std::cin >> cols;

    TriangleMatrix<double> matrix(rows, cols);

    std::cout << "Input non-zero elements separated by a space:\n";
    std::cin >> matrix;

    return matrix;
}

Matrix<double> start_addition_menu(Matrix<double>& A, Matrix<double>& B, Matrix<double>& C) {
    Matrix<double> fmatrix = choose_matrix(A, B, C);
    Matrix<double> smatrix = choose_matrix(A, B, C);

    Matrix<double> result;
    result = fmatrix + smatrix;
    return result;
}

Matrix<double> start_subtraction_menu(Matrix<double>& A, Matrix<double>& B, Matrix<double>& C) {
    Matrix<double> fmatrix = choose_matrix(A, B, C);
    Matrix<double> smatrix = choose_matrix(A, B, C);

    Matrix<double> result;
    result = fmatrix - smatrix;
    return result;
}

Matrix<double> start_multiplication_menu(Matrix<double>& A, Matrix<double>& B, Matrix<double>& C) {
    Matrix<double> fmatrix = choose_matrix(A, B, C);
    Matrix<double> smatrix = choose_matrix(A, B, C);

    Matrix<double> result;
    result = fmatrix * smatrix;
    return result;
}

Matrix<double> start_multiplication_vector_menu(Matrix<double>& A, Matrix<double>& B, Matrix<double>& C) {
    Matrix<double> matrix = choose_matrix(A, B, C);
    MathVector<double> vector;
    std::cout << "Input vector:\n";
    std::cin >> vector;

    Matrix<double> result;
    result = matrix * vector;
    return result;
}

Matrix<double> start_multiplication_scalar_menu(Matrix<double>& A, Matrix<double>& B, Matrix<double>& C) {
    Matrix<double> fmatrix = choose_matrix(A, B, C);
    double scalar = 0;
    std::cout << "Input scalar:\n";
    std::cin >> scalar;

    Matrix<double> result;
    result = fmatrix * scalar;
    return result;
}

bool start_matrix_menu() {
    show_matrix_input_menu();
    Matrix<double> A = input_matrix("A");
    Matrix<double> B = input_matrix("B");
    Matrix<double> C = NULL;

    while (1) {
        system("cls");
        show_matrix_menu(A, B, C);
        char user_num = get_user_num(MATRIX_MENU_OPTIONS);
        bool isBack = false;

        system("cls");
        switch (user_num) {
        case '1':
            show_matrix_input_menu();
            A = input_matrix("A");
            B = input_matrix("B");
            break;
        case '2':
            C = start_addition_menu(A, B, C);
            break;
        case '3':
            C = start_subtraction_menu(A, B, C);
            break;
        case '4':
            C = start_multiplication_menu(A, B, C);
            break;
        case '5':
            C = start_multiplication_vector_menu(A, B, C);
            break;
        case '6':
            C = start_multiplication_scalar_menu(A, B, C);
            break;
        case '7':
            return true;
        default:
            isBack = true;
            break;
        }

        if (isBack) break;
    }

    return false;
}

TriangleMatrix<double> start_addition_menu(TriangleMatrix<double>& A, TriangleMatrix<double>& B, TriangleMatrix<double>& C) {
    TriangleMatrix<double> fmatrix = choose_matrix(A, B, C);
    TriangleMatrix<double> smatrix = choose_matrix(A, B, C);

    TriangleMatrix<double> result;
    result = fmatrix + smatrix;
    return result;
}

TriangleMatrix<double> start_subtraction_menu(TriangleMatrix<double>& A, TriangleMatrix<double>& B, TriangleMatrix<double>& C) {
    TriangleMatrix<double> fmatrix = choose_matrix(A, B, C);
    TriangleMatrix<double> smatrix = choose_matrix(A, B, C);

    TriangleMatrix<double> result;
    result = fmatrix - smatrix;
    return result;
}

TriangleMatrix<double> start_multiplication_menu(TriangleMatrix<double>& A, TriangleMatrix<double>& B, TriangleMatrix<double>& C) {
    TriangleMatrix<double> fmatrix = choose_matrix(A, B, C);
    TriangleMatrix<double> smatrix = choose_matrix(A, B, C);

    TriangleMatrix<double> result;
    result = fmatrix * smatrix;
    return result;
}

bool start_triangle_matrix_menu() {
    show_matrix_input_menu();
    TriangleMatrix<double> A = input_triangle_matrix("A");
    TriangleMatrix<double> B = input_triangle_matrix("B");
    TriangleMatrix<double> C = NULL;

    while (1) {
        system("cls");
        show_triangle_matrix_menu(A, B, C);
        char user_num = get_user_num(TRIANGLE_MATRIX_MENU_OPTIONS);
        bool isBack = false;

        system("cls");
        switch (user_num) {
        case '1':
            show_matrix_input_menu();
            A = input_triangle_matrix("A");
            B = input_triangle_matrix("B");
            break;
        case '2':
            C = start_addition_menu(A, B, C);
            break;
        case '3':
            C = start_subtraction_menu(A, B, C);
            break;
        case '4':
            C = start_multiplication_menu(A, B, C);
            break;
        case '5':
            return true;
        default:
            isBack = true;
            break;
        }

        if (isBack) break;
    }

    return false;
}

int main() {
    bool isExit = false;
    while (1) {
        show_start_menu();
        char user_num = get_user_num(START_MENU_OPTIONS);

        system("cls");
        switch (user_num) {
        case '1':
            isExit = start_matrix_menu();
            break;
        case '2':
            isExit = start_triangle_matrix_menu();
            break;
        default:
            isExit = true;
        }
        if (isExit) break;
    }
    return 0;
}

#endif  // MATRIX_INTERFACE