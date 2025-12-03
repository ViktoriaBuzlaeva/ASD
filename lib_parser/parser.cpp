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
            else if (c == '-' && (i == 0 || expression[i - 1] == '(')) {
                lexems.push_back(Lexem("0", Constant, 0));
                lexems.push_back(Lexem("-", Operator, DBL_MAX, 1));

                prev_is_operand = false;
                prev_is_operation = false;
            }
            else if (std::isdigit(c) || std::isalpha(c)) {
                if (std::isalpha(c)) {
                    std::string name = read_name(expression, i);

                    if (name == "sin") {
                        Lexem lex("sin", Function, DBL_MAX, -1, Functions::sin);
                        lexems.push_back(lex);
                    }
                    else if (name == "cos") {
                        Lexem lex("cos", Function, DBL_MAX, -1, Functions::cos);
                        lexems.push_back(lex);
                    }
                    else if (name == "tg") {
                        Lexem lex("tg", Function, DBL_MAX, -1, Functions::tg);
                        lexems.push_back(lex);
                    }
                    else {
                        lexems.push_back(Lexem(name, Variable));
                        expect_operand = false;
                    }
                }
                else {
                    std::string number = read_num(expression, i);
                    double value = std::stod(number);
                    std::string str = std::to_string(value);
                    str.erase(str.find_last_not_of('0') + 1, std::string::npos);
                    if (str[str.length() - 1] == '.') str.erase(str.length() - 1);
                    lexems.push_back(Lexem(str, Constant, value));
                    expect_operand = false;
                }

                prev_is_operand = true;
                prev_is_operation = false;
            }
            else {
                if (prev_is_operation) {
                    throw std::logic_error(error_message(i, "missing second operand in operation '" + std::string(1, expression[i - 1]) + "'"));
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
                if (c == '}' && brackets.top() == '{') {
                    brackets.pop();
                }
                else if (c == ']' && brackets.top() == '[') {
                    brackets.pop();
                }
                else if (c == ')' && brackets.top() == '(') {
                    brackets.pop();
                }
                else {
                    throw std::logic_error(error_message(i, "wrong closing bracket"));
                }
                lexems.push_back(Lexem(std::string(1, c), ClosedBracket));

                prev_is_operand = true;
                prev_is_operation = false;
            }
            else if (c == '|') {
                if (brackets.top() == '|') {
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
                switch (c) {
                case '+':
                    lexems.push_back(Lexem("+", Operator, DBL_MAX, 1));
                    break;
                case '-':
                    lexems.push_back(Lexem("-", Operator, DBL_MAX, 1));
                    break;
                case '*':
                    lexems.push_back(Lexem("*", Operator, DBL_MAX, 2));
                    break;
                case '/':
                    lexems.push_back(Lexem("/", Operator, DBL_MAX, 2));
                    break;
                case '^':
                    lexems.push_back(Lexem("^", Operator, DBL_MAX, 3));
                    break;
                }

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

    return lexems;
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

std::string Parser::error_message(int pos, const std::string& msg) {
    std::string error_msg = std::string(19 + pos, ' ') + "^\n";
    error_msg += "Error in function 'Parser::parse()' at " +
        std::to_string(pos + 1) + " symbol: " + msg;
    return error_msg;
}
