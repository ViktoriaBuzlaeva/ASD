// Copyright 2025 Viktoria Buzlaeva

// #define EASY_EXAMPLE
// #define TYPE_OF_CROSSING
// #define MATRIX_INTERFACE
// #define LABYRINTH_GENERATION
// #define SORT_DATA_WITH_BSTREE
#define SORT_DATA_WITH_HEAP

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

#ifdef MATRIX_INTERFACE

#include <iostream>
#include "../lib_matrix/matrix.h"
#include "../lib_triangle_matrix/trianglematrix.h"

#define START_MENU_OPTIONS 2
#define MATRIX_MENU_OPTIONS 7
#define TRIANGLE_MATRIX_MENU_OPTIONS 7

void show_start_menu() {
    std::cout << "Matrix calculator\n";
    std::cout << "Choose option:\n";
    std::cout << "1) Matrix;\n";
    std::cout << "2) Triangle matrix.\n";
    std::cout << "0) Exit.\n";
}

int get_user_num(int options) {
    while (1) {
        int user_num = 0;
        if (std::cin >> user_num) {
            if (user_num >= 0 && user_num <= options) {
                return user_num;
            }
        }
        else {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        std::cout << "Incorrect input! Try again" << std::endl;
    }
}

void show_matrix_input_menu() {
    std::cout << "Matrix calculator\n";
    std::cout << "Choose matrix's size\n";
}

size_t get_user_input(std::string name) {
    while (1) {
        std::cout << name;
        int user_input = 0;
        if (std::cin >> user_input) {
            if (user_input >= 0) {
                return user_input;
            }
        }
        else {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        std::cout << "Incorrect input! Try again" << std::endl;
    }
}

Matrix<double> input_matrix(std::string name) {
    std::cout << "Matrix " << name << "\n";
    
    size_t rows = get_user_input("Rows: ");
    size_t cols = get_user_input("Columns: ");

    Matrix<double> matrix(rows, cols);

    std::cout << "Input elements separated by a space:\n";
    std::cin >> matrix;

    return matrix;
}

void show_matrix_menu(Matrix<double>& A, Matrix<double>& B, Matrix<double>& C) {
    std::cout << "Matrix calculator\n";
    std::cout << "A = ";
    std::cout << A << std::endl;
    std::cout << "B = ";
    std::cout << B << std::endl;
    if (C != NULL) {
        std::cout << "C = ";
        std::cout << C << std::endl;
    }
    std::cout << "Choose option:\n";
    std::cout << "1) Input matrices (A, B);\n";
    std::cout << "2) Addition;\n";
    std::cout << "3) Subtraction;\n";
    std::cout << "4) Multiplication (matrices);\n";
    std::cout << "5) Multiplication (matrix and vector);\n";
    std::cout << "6) Multiplication (matrix and scalar);\n";
    std::cout << "7) Back.\n";
    std::cout << "0) Exit.\n";
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

Matrix<double> start_addition_menu(Matrix<double>& A, Matrix<double>& B, Matrix<double>& C) {
    Matrix<double> fmatrix = choose_matrix(A, B, C);
    Matrix<double> smatrix = choose_matrix(A, B, C);

    Matrix<double> result;

    try {
        result = fmatrix + smatrix;
    }
    catch (std::logic_error e) {
        std::cerr << e.what() << std::endl;
        getchar();
        getchar();
    }
    
    return result;
}

Matrix<double> start_subtraction_menu(Matrix<double>& A, Matrix<double>& B, Matrix<double>& C) {
    Matrix<double> fmatrix = choose_matrix(A, B, C);
    Matrix<double> smatrix = choose_matrix(A, B, C);

    Matrix<double> result;

    try {
        result = fmatrix - smatrix;
    }
    catch (std::logic_error e) {
        std::cerr << e.what() << std::endl;
        getchar();
        getchar();
    }
    
    return result;
}

Matrix<double> start_multiplication_menu(Matrix<double>& A, Matrix<double>& B, Matrix<double>& C) {
    Matrix<double> fmatrix = choose_matrix(A, B, C);
    Matrix<double> smatrix = choose_matrix(A, B, C);

    Matrix<double> result;

    try {
        result = fmatrix * smatrix;
    }
    catch (std::logic_error e) {
        std::cerr << e.what() << std::endl;
        getchar();
        getchar();
    }

    return result;
}

Matrix<double> start_multiplication_vector_menu(Matrix<double>& A, Matrix<double>& B, Matrix<double>& C) {
    Matrix<double> matrix = choose_matrix(A, B, C);
    MathVector<double> vector(matrix.cols());
    std::cout << "Input vector elements separated by a space (size " << vector.size() << "):\n";
    std::cin >> vector;

    Matrix<double> result;

    try {
        MathVector<double> vec_res = matrix * vector;
        MathVector<MathVector<double>> res(1);
        res[0] = vec_res;
        Matrix<double> r(res);
        result = r;
    }
    catch (std::logic_error e) {
        std::cerr << e.what() << std::endl;
        getchar();
        getchar();
    }

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
        int user_num = get_user_num(MATRIX_MENU_OPTIONS);
        bool isBack = false;

        system("cls");
        switch (user_num) {
        case 1:
            show_matrix_input_menu();
            A = input_matrix("A");
            B = input_matrix("B");
            break;
        case 2:
            C = start_addition_menu(A, B, C);
            break;
        case 3:
            C = start_subtraction_menu(A, B, C);
            break;
        case 4:
            C = start_multiplication_menu(A, B, C);
            break;
        case 5:
            C = start_multiplication_vector_menu(A, B, C);
            break;
        case 6:
            C = start_multiplication_scalar_menu(A, B, C);
            break;
        case 7:
            isBack = true;
            break;
        default:
            return true;
        }

        if (isBack) break;
    }

    return false;
}

TriangleMatrix<double> input_triangle_matrix(std::string name) {
    std::cout << "Matrix " << name << "\n";

    size_t size = get_user_input("Size: ");

    TriangleMatrix<double> matrix(size);

    std::cout << "Input non-zero elements separated by a space:\n";
    std::cin >> matrix;

    return matrix;
}

void show_triangle_matrix_menu(Matrix<double>& A, Matrix<double>& B, Matrix<double>& C) {
    std::cout << "Matrix calculator\n";
    std::cout << "A = ";
    std::cout << A << std::endl;
    std::cout << "B = ";
    std::cout << B << std::endl;
    if (C != NULL) {
        std::cout << "C = ";
        std::cout << C << std::endl;
    }
    std::cout << "Choose option:\n";
    std::cout << "1) Input matrices (A, B);\n";
    std::cout << "2) Addition;\n";
    std::cout << "3) Subtraction;\n";
    std::cout << "4) Multiplication (matrices);\n";
    std::cout << "5) Multiplication (matrix and vector);\n";
    std::cout << "6) Multiplication (matrix and scalar);\n";
    std::cout << "7) Back.\n";
    std::cout << "0) Exit.\n";
}

TriangleMatrix<double> start_addition_menu(TriangleMatrix<double>& A, TriangleMatrix<double>& B, TriangleMatrix<double>& C) {
    TriangleMatrix<double> fmatrix = choose_matrix(A, B, C);
    TriangleMatrix<double> smatrix = choose_matrix(A, B, C);

    TriangleMatrix<double> result;

    try {
        result = fmatrix + smatrix;
    }
    catch (std::logic_error e) {
        std::cerr << e.what() << std::endl;
        getchar();
        getchar();
    }

    return result;
}

TriangleMatrix<double> start_subtraction_menu(TriangleMatrix<double>& A, TriangleMatrix<double>& B, TriangleMatrix<double>& C) {
    TriangleMatrix<double> fmatrix = choose_matrix(A, B, C);
    TriangleMatrix<double> smatrix = choose_matrix(A, B, C);

    TriangleMatrix<double> result;

    try {
        result = fmatrix - smatrix;
    }
    catch (std::logic_error e) {
        std::cerr << e.what() << std::endl;
        getchar();
        getchar();
    }

    return result;
}

TriangleMatrix<double> start_multiplication_menu(TriangleMatrix<double>& A, TriangleMatrix<double>& B, TriangleMatrix<double>& C) {
    TriangleMatrix<double> fmatrix = choose_matrix(A, B, C);
    TriangleMatrix<double> smatrix = choose_matrix(A, B, C);

    TriangleMatrix<double> result;

    try {
        result = fmatrix * smatrix;
    }
    catch (std::logic_error e) {
        std::cerr << e.what() << std::endl;
        getchar();
        getchar();
    }

    return result;
}

void start_multiplication_vector_menu(TriangleMatrix<double>& A, TriangleMatrix<double>& B, TriangleMatrix<double>& C) {
    TriangleMatrix<double> matrix = choose_matrix(A, B, C);
    MathVector<double> vector(matrix.cols());
    std::cout << "Input vector elements separated by a space (size " << vector.size() << "):\n";
    std::cin >> vector;

    try {
        MathVector<double> result = matrix * vector;
        std::cout << "Result: " << result << std::endl;
        std::cout << "Press any key to continue";
        std::getchar();
        std::getchar();
    }
    catch (std::logic_error e) {
        std::cerr << e.what() << std::endl;
        getchar();
        getchar();
    }
}

TriangleMatrix<double> start_multiplication_scalar_menu(TriangleMatrix<double>& A, TriangleMatrix<double>& B, TriangleMatrix<double>& C) {
    TriangleMatrix<double> fmatrix = choose_matrix(A, B, C);
    double scalar = 0;
    std::cout << "Input scalar:\n";
    std::cin >> scalar;

    TriangleMatrix<double> result;
    result = fmatrix * scalar;
    return result;
}

bool start_triangle_matrix_menu() {
    show_matrix_input_menu();
    TriangleMatrix<double> A = input_triangle_matrix("A");
    TriangleMatrix<double> B = input_triangle_matrix("B");
    TriangleMatrix<double> C = NULL;
    MathVector<double> res(A.size());

    while (1) {
        system("cls");
        show_triangle_matrix_menu(A, B, C);
        int user_num = get_user_num(TRIANGLE_MATRIX_MENU_OPTIONS);
        bool isBack = false;

        system("cls");
        switch (user_num) {
        case 1:
            show_matrix_input_menu();
            A = input_triangle_matrix("A");
            B = input_triangle_matrix("B");
            break;
        case 2:
            C = start_addition_menu(A, B, C);
            break;
        case 3:
            C = start_subtraction_menu(A, B, C);
            break;
        case 4:
            C = start_multiplication_menu(A, B, C);
            break;
        case 5:
            start_multiplication_vector_menu(A, B, C);
            break;
        case 6:
            C = start_multiplication_scalar_menu(A, B, C);
            break;
        case 7:
            isBack = true;
            break;
        default:
            return true;
        }

        if (isBack) break;
    }

    return false;
}

int main() {
    bool isExit = false;
    while (1) {
        show_start_menu();
        int user_num = get_user_num(START_MENU_OPTIONS);

        system("cls");
        switch (user_num) {
        case 1:
            isExit = start_matrix_menu();
            break;
        case 2:
            isExit = start_triangle_matrix_menu();
            break;
        case 0:
            isExit = true;
        }
        if (isExit) break;
    }
    return 0;
}

#endif  // MATRIX_INTERFACE

#ifdef LABYRINTH_GENERATION

#include <iomanip>
#include <locale>
#include "../lib_algorithms/algorithms.h"

int main() {
    setlocale(LC_ALL, "Russian");
    while (1) {
        int S, F, N, M;
        std::cout << "¬ведите вход, выход и размеры лабиринта (через пробел): ";
        std::cin >> S;
        std::cin >> F;
        std::cin >> N;
        std::cin >> M;
        Matrix<bool> labyrinth;
        try {
            labyrinth = generate_labyrinth(S, F, N, M);
            print_lab(labyrinth, N, M);
            std::getchar();
            std::getchar();
        }
        catch (std::logic_error e) {
            std::cerr << e.what() << std::endl;
            getchar();
            getchar();
        }
        system("cls");
    }
    return 0;
}

#endif  // LABYRINTH_GENERATION

#ifdef SORT_DATA_WITH_BSTREE

#include "../lib_bstree/bstree.h"
#include "../lib_tvector/tvector.h"

int main() {
    srand(time(0));
    int size = 25;

    TVector<TPair<int, int>> pairs;
    for (int i = 0; i < size; i++) {
        TPair<int, int> pair(rand() % 101, i);
        pairs.push_back(pair);
    }

    BSTree<int, int> bst;
    for (int i = 0; i < size; i++) {
        try {
            bst.insert(pairs[i].key, pairs[i].value);
        }
        catch (std::exception ex) {
        }
    }

    bst.print_DLCR();
    return 0;
}

#endif  // SORT_DATA_WITH_BSTREE

#ifdef SORT_DATA_WITH_HEAP

#include "../lib_heap/heap.h"

int main() {
    srand(time(0));
    int size = 25;

    Heap<int> h;
    for (int i = 0; i < size; i++) {
        h.insert(rand() % 101);
    }

    for (int i = 0; i < size; i++) {
        std::cout << h.root() << " ";
        h.erase();
    }

    return 0;
}

#endif  // SORT_DATA_WITH_HEAP
