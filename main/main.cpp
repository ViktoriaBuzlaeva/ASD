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

enum TypeOfCrossing { Intersect, NotIntersect, Touch, Coincide };

template <class T>
TypeOfCrossing find_type_of_crossing(const T& first, const T& second) {
    if (first == second) {
        return Coincide;
    }
    else if (first.cent().find_distance(second.cent()) > (first.rad() + second.rad())) {
        return NotIntersect;
    }
    else if (first.cent().find_distance(second.cent()) < (first.rad() + second.rad())) {
        return Intersect;
    }
    else {
        return Touch;
    }
}

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

#define START_MENU_OPTIONS 3

void print_start_menu() {
    std::cout << "Matrix calculator\n";
    std::cout << "Choose operation (choose any key for exit):\n";
    std::cout << "1) Addition\n";
    std::cout << "2) Subtraction\n";
    std::cout << "3) Multiplication\n";
}

int get_user_num(int options) {
    int user_num = 0;
    std::cout << "Your choice: ";
    std::cin >> user_num;
    return user_num;
}

void print_addition_menu() {
    std::cout << "Matrix calculator\n";
    std::cout << "Choose matrix's size\n";
    std::cout << "For example, 2 3:\n";
    std::cout << "1 2 3\n";
    std::cout << "4 5 6\n";
}

int get_size() {
    int size = 0;
    std::cin >> size;
    return size;
}

void start_addition_menu() {
    print_addition_menu();

    int M1 = get_size();
    int N1 = get_size();
    Matrix matrix1(M1, N1);

    std::cout << "\n";

    int M2 = get_size();
    int N2 = get_size();
    Matrix matrix2(M2, N2);


}

void start_subtraction_menu() {

}
    
void start_multiplication_menu() {

}

void start_menu() {
    print_start_menu();
    
    int user_num = get_user_num(START_MENU_OPTIONS);

    system("cls");

    switch (user_num) {
    case 1:
        start_addition_menu();
    case 2:
        start_subtraction_menu();
    case 3:
        start_multiplication_menu();
    default:
        return;
    }


}

int main() {
    start_menu();
    return 0;
}

#endif  // MATRIX_INTERFACE