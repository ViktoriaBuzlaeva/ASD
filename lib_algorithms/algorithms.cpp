// Copyright 2025 Viktoria Buzlaeva

#include "../lib_algorithms/algorithms.h"

bool check_brackets(std::string str) {
    Stack<char> stack;

    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '}' || str[i] == ']' || str[i] == ')') {
            if (stack.is_empty()) return false;
            switch (str[i]) {
            case '}':
                if (stack.top() == '{') {
                    stack.pop();
                    break;
                }
            case ']':
                if (stack.top() == '[') {
                    stack.pop();
                    break;
                }
            case ')':
                if (stack.top() == '(') {
                    stack.pop();
                    break;
                }
            }
        }
        else {
            stack.push(str[i]);
        }
    }

    return stack.is_empty();
}

void read_expression(std::string expression) {
    Stack<char> brackets;
    bool expect_operand = true;
    bool prev_is_operand = false;
    bool prev_is_operation = false;

    for (int i = 0; i < expression.length(); i++) {
        char c = expression[i];

        if (std::isspace(c)) { continue; }

        if (expect_operand) { // ������� ����������� ������, ������� �����, ����� ��� ����������
            if (c == '(') {
                brackets.push(c);

                prev_is_operand = false;
                prev_is_operation = false;
            }
            else if (c == '-' && (i == 0 || expression[i - 1] == '(' || prev_is_operation)) {
                prev_is_operand = false;
                prev_is_operation = false;
            }
            else if (std::isdigit(c) || std::isalpha(c)) {
                if (std::isalpha(c)) {
                    while (i < expression.length() && std::isalpha(expression[i])) {
                        i++;
                    }
                }
                else if (std::isdigit(c)) {
                    while (i < expression.length() && std::isdigit(expression[i])) {
                        i++;
                    }
                }
                i--;

                prev_is_operand = true;
                prev_is_operation = false;
                expect_operand = false;
            }
            else {
                if (prev_is_operation) {
                    throw std::logic_error("Missing second operand in operation " + std::string(1, expression[i - 1]));
                }
                else {
                    throw std::logic_error("Missing operand");
                }
            }
        }
        else { // ������� ����������� ������ ��� ��������
            if (c == ')') {
                if (brackets.is_empty()) {
                    throw std::logic_error("Extra closing bracket");
                }
                brackets.pop();

                prev_is_operand = true;
                prev_is_operation = false;
            }
            else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^') {
                if (i == expression.length() - 1) {  // ���������, ��� �������� �� � �����
                    throw std::logic_error("Missing second operand in operation " + std::string(1, c));
                }

                prev_is_operand = false;
                prev_is_operation = true;
                expect_operand = true;
            }
            else {
                throw std::logic_error("Missing operation");
            }
        }
    }

    if (!brackets.is_empty()) {
        throw std::logic_error("Missing closing bracket");
    }

    if (expect_operand && prev_is_operation) {
        throw std::logic_error("Missing operand");
    }
}
