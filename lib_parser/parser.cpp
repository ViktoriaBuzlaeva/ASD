// Copyright 2025 Viktoria Buzlaeva

#include "../lib_parser/parser.h"

List<Lexem> Parser::parse(const std::string& expression) {
    List<Lexem> lexems;
    Stack<char> brackets;

    bool expect_operand = true;
    bool prev_is_operand = false;
    bool prev_is_operation = false;

    for (int i = 0; i < expression.length(); i++) {
        if (std::isspace(expression[i])) { continue; }
        char c = expression[i];

        if (expect_operand) {
            if (c == '(' || c == '{' || c == '[' || c == '|') {
                brackets.push(c);
                if (c == '|') {
                    lexems.push_back(Lexem("abs", Function, DBL_MAX, -1, Functions::my_abs));
                    lexems.push_back(Lexem("(", OpenBracket));
                }
                else {
                    lexems.push_back(Lexem(std::string(1, c), OpenBracket));
                }

                prev_is_operand = false;
                prev_is_operation = false;
            }
            else if (c == '-' && (i == 0 || lexems.tail()->value.type == OpenBracket)) {
                lexems.push_back(Lexem("0", Constant, 0));
                lexems.push_back(Lexem("-", Operator, DBL_MAX, 1));

                prev_is_operand = false;
                prev_is_operation = false;
            }
            else if (std::isdigit(c) || std::isalpha(c)) {
                if (std::isalpha(c)) {
                    std::string name = read_name(expression, i);

                    if (name == "sin" || name == "cos" || name == "tg") {
                        if (!is_correct_function(expression, i + 1)) throw std::logic_error(error_message(i, "missing argument in function '" + name + "'"));
                        lexems.push_back(Lexem(name, Function, DBL_MAX, -1, get_function(name)));
                    }
                    else {
                        lexems.push_back(Lexem(name, Variable));
                        expect_operand = false;
                    }
                }
                else {
                    std::string number = read_num(expression, i);
                    double value = std::stod(number);
                    lexems.push_back(Lexem(number, Constant, value));
                    expect_operand = false;
                }

                prev_is_operand = true;
                prev_is_operation = false;
            }
            else {
                if (prev_is_operation) {
                    do i--; while (expression[i] == ' ');
                    throw std::logic_error(error_message(i, "missing second operand in operation '" + std::string(1, expression[i]) + "'"));
                }
                else {
                    throw std::logic_error(error_message(i, "missing operand"));
                }
            }
        }
        else {
            if (c == ')' || c == '}' || c == ']') {
                if (brackets.is_empty()) {
                    throw std::logic_error(error_message(i, "extra closing bracket"));
                }
                if (!is_matching_brackets(c, brackets.top())) {
                    throw std::logic_error(error_message(i, "wrong closing bracket"));
                }
                brackets.pop();
                lexems.push_back(Lexem(std::string(1, c), ClosedBracket));

                prev_is_operand = true;
                prev_is_operation = false;
            }
            else if (c == '|') {
                if (!brackets.is_empty() && brackets.top() == '|') {
                    brackets.pop();
                    lexems.push_back(Lexem(")", ClosedBracket));

                    prev_is_operand = true;
                    prev_is_operation = false;
                }
                else { throw std::logic_error(error_message(i, "invalid character '|'")); }
            }
            else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^') {
                if (i == expression.length() - 1) {
                    throw std::logic_error(error_message(i, "missing second operand in operation '" + std::string(1, c) + "'"));
                }
                lexems.push_back(Lexem(std::string(1, c), Operator, DBL_MAX, get_priority(std::string(1, c))));

                prev_is_operand = false;
                prev_is_operation = true;
                expect_operand = true;
            }
            else {
                throw std::logic_error(error_message(i, "missing operation"));
            }
        }
    }

    if (!brackets.is_empty()) {
        throw std::logic_error(error_message(expression.length() - 1, "missing closing bracket"));
    }

    if (expect_operand && prev_is_operation) {
        throw std::logic_error(error_message(expression.length() - 1, "missing operand"));
    }

    if (lexems.is_empty()) throw std::logic_error(error_message(expression.length() - 1, "empty input"));

    return lexems;
}

double(*Parser::get_function(const std::string& name))(double) {
    if (name == "sin") return Functions::my_sin;
    else if (name == "cos") return Functions::my_cos;
    else if (name == "tg") return Functions::my_tg;
    return nullptr;
}

bool Parser::is_correct_function(const std::string& expr, int pos) {
    while (expr[pos] == ' ') pos++;
    if (expr[pos] != '(' && expr[pos] != '{' && expr[pos] != '[') return false;
}

std::string Parser::read_num(const std::string& expr, int& pos) {
    std::string number = "";
    bool has_dot = false;

    while (pos < expr.length() && (std::isdigit(expr[pos]) || expr[pos] == '.')) {
        if (!std::isdigit(expr[pos])) {
            if (has_dot || expr[pos] != '.') throw std::logic_error(error_message(pos, "invalid number input"));
            has_dot = true;
        }
        number += expr[pos];
        pos++;
    }
    pos--;

    return number;
}

std::string Parser::read_name(const std::string& expr, int& pos) {
    std::string name = "";

    while (pos < expr.length() && (std::isalpha(expr[pos]) || std::isdigit(expr[pos]) || expr[pos] == '_')) {
        name += expr[pos];
        pos++;
    }
    pos--;

    return name;
}

bool Parser::is_matching_brackets(const char& opened, const char& closed) {
    if (opened == '}' && closed == '{') {
        return true;
    }
    else if (opened == ']' && closed == '[') {
        return true;
    }
    else if (opened == ')' && closed == '(') {
        return true;
    }
    return false;
}

int Parser::get_priority(const std::string& name) {
    if (name == "+" || name == "-") return 1;
    else if (name == "*" || name == "/") return 2;
    else if (name == "^") return 3;
    return -1;
}

std::string Parser::error_message(int pos, const std::string& msg) {
    std::string error_msg = std::string(19 + pos, ' ') + "^\n";
    error_msg += "Error in function 'Parser::parse()' at " +
        std::to_string(pos + 1) + " symbol: " + msg;
    return error_msg;
}
