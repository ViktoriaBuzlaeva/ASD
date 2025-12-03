// Copyright 2025 Viktoria Buzlaeva

// #define EASY_EXAMPLE
// #define TYPE_OF_CROSSING
#define CALCULATOR

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

#ifdef CALCULATOR

#include <iomanip>
#include <locale>
#include "../lib_expression/expression.h"
#include "../lib_tvector/tvector.h"

#define MAIN_OPTIONS 4
#define ID_COLUMN_WIDTH 4
#define EXPRESSION_COLUMN_WIDTH 45
#define VARIABLES_COLUMN_WIDTH 30

void print_line() {
    std::cout << "+";
    for (int i = 0; i < ID_COLUMN_WIDTH + EXPRESSION_COLUMN_WIDTH + VARIABLES_COLUMN_WIDTH + 8; i++) {
        std::cout << "-";
    }
    std::cout << "+" << std::endl;
}

void print_expr(int id, const std::string& expr, const std::string& vars) {
    std::cout << "| " << std::left << std::setw(ID_COLUMN_WIDTH) << id << " | " << std::setw(EXPRESSION_COLUMN_WIDTH)
        << expr << " | " << std::setw(VARIABLES_COLUMN_WIDTH) << vars << " |" << std::endl;
}

void print_tab(TVector<Expression>& exprs) {
    if (exprs.is_empty()) {
        return;
    }
    print_line();
    std::cout << "| " << std::left << std::setw(ID_COLUMN_WIDTH) << "ID" << " | " << std::setw(EXPRESSION_COLUMN_WIDTH)
        << "EXPRESSION" << " | " << std::setw(VARIABLES_COLUMN_WIDTH) << "VARIABLES VALUES" << " |" << std::endl;
    print_line();
    for (size_t i = 0; i < exprs.size(); i++) {
        print_expr(i + 1, exprs[i].get_expression(), exprs[i].get_variables());
    }
    print_line();
}

void print_main_menu(TVector<Expression>& exprs) {
    print_tab(exprs);
    std::cout << "============= МЕНЮ =============" << std::endl;
    std::cout << "1. Создать новое выражение" << std::endl;
    std::cout << "2. Удалить выражение" << std::endl;
    std::cout << "3. Задать переменные" << std::endl;
    std::cout << "4. Вычислить значение выражения" << std::endl;
    std::cout << "0. Выход" << std::endl;
    std::cout << "\nВаш выбор: ";
}

int get_user_num() {
    while (1) {
        int user_num = 0;
        if (std::cin >> user_num) {
            if (user_num >= 0 && user_num <= MAIN_OPTIONS) {
                return user_num;
            }
        }
        else {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        std::cout << "Некорректный ввод! Попробуйте снова" << std::endl;
    }
}

void print_creating_exprs_menu() {
    std::cout << "============= СОЗДАНИЕ НОВОГО ВЫРАЖЕНИЯ =============" << std::endl;
}

void start_creating_exprs_menu(TVector<Expression>& exprs) {
    system("cls");
    print_creating_exprs_menu();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    while (1) {
        std::cout << "Введите выражение: ";
        // std::string expr_str;
        // std::getline(std::cin, expr_str);
        try {
            //Expression expr(expr_str);
            Expression expr;
            std::cin >> expr;
            exprs.push_back(expr);
            break;
        }
        catch (std::logic_error e) {
            std::cerr << e.what() << std::endl;
        }
    }
}

void print_no_exprs() {
    std::cout << "Нет выражений!";
    getchar();
    getchar();
}

void print_deleting_exprs_menu(TVector<Expression>& exprs) {
    print_tab(exprs);
    std::cout << "============= УДАЛЕНИЕ ВЫРАЖЕНИЯ =============" << std::endl;
}

int get_expr_num(const TVector<Expression>& exprs) {
    while (1) {
        std::cout << "Введите номер выражения (введите '0', чтобы вернуться назад): ";
        int expr_num = 0;
        if (std::cin >> expr_num) {
            if (expr_num >= 0 && expr_num <= exprs.size()) {
                return expr_num;
            }
        }
        else {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        std::cout << "Некорректный ввод!" << std::endl;
    }
}

void start_deleting_exprs_menu(TVector<Expression>& exprs) {
    system("cls");
    if (exprs.is_empty()) {
        print_no_exprs();
        return;
    }
    print_deleting_exprs_menu(exprs);
    int expr_num = get_expr_num(exprs);
    if (expr_num == 0) return;
    exprs.erase(expr_num - 1);
}

void print_setting_vars_menu(TVector<Expression>& exprs) {
    print_tab(exprs);
    std::cout << "============= ЗАДАНИЕ ПЕРЕМЕННЫХ =============" << std::endl;
}

double get_user_input(const std::string& name) {
    while (1) {
        std::cout << "Введите значение для переменной " + name + " : ";
        double user_input = 0;
        if (std::cin >> user_input) {
            return user_input;
        }
        else {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        std::cout << "Некорректный ввод!" << std::endl;
    }
}

void start_setting_vars_menu(TVector<Expression>& exprs) {
    system("cls");
    if (exprs.is_empty()) {
        print_no_exprs();
        return;
    }
    print_setting_vars_menu(exprs);
    int expr_num = get_expr_num(exprs);
    if (expr_num == 0) return;
    List<Lexem> variables = exprs[expr_num - 1].get_list_vars();
    int user_input;

    for (auto it = variables.begin(); it != variables.end(); it++) {
        user_input = get_user_input((*it).name);
        exprs[expr_num - 1].set_variable((*it).name, user_input);
    }
}

void print_calculation_menu(TVector<Expression>& exprs) {
    print_tab(exprs);
    std::cout << "============= ВЫЧИСЛЕНИЕ ЗНАЧЕНИЯ ВЫРАЖЕНИЯ =============" << std::endl;
}

void start_calculation_menu(TVector<Expression>& exprs) {
    system("cls");
    if (exprs.is_empty()) {
        print_no_exprs();
        return;
    }
    print_calculation_menu(exprs);
    int expr_num = get_expr_num(exprs);
    if (expr_num == 0) return;
    try {
        double res = exprs[expr_num - 1].calculate();
        std::cout << "Результат вычисления: " << res;
    }
    catch (std::logic_error e) {
        std::cerr << e.what() << std::endl;

    }
    getchar();
    getchar();
}

int main() {
    setlocale(LC_ALL, "Russian");
    setlocale(LC_NUMERIC, "C");
    bool isExit = false;

    TVector<Expression> exprs;
    while (1) {
        system("cls");
        print_main_menu(exprs);
        int user_num = get_user_num();
        
        switch (user_num) {
        case 1:
            start_creating_exprs_menu(exprs);
            break;
        case 2:
            start_deleting_exprs_menu(exprs);
            break;
        case 3:
            start_setting_vars_menu(exprs);
            break;
        case 4:
            start_calculation_menu(exprs);
            break;
        case 0:
            isExit = true;
        }
        if (isExit) break;
    }
    return 0;
}

#endif  // CALCULATOR
