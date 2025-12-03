// Copyright 2025 Viktoria Buzlaeva

#include "../lib_expression/expression.h"

Expression::Expression(const std::string& expr) {
    _lexems = Parser::parse(expr);
    _polish_record = to_polish_record();
}

Expression::Expression(const List<Lexem>& lexems) {
    _lexems = lexems;
    _polish_record = to_polish_record();
}

List<Lexem> Expression::get_list_vars() {
    List<Lexem> variables;

    for (auto it_1 = _polish_record.begin(); it_1 != _polish_record.end(); it_1++) {
        if ((*it_1).type == Variable) {
            bool is_unique = true;
            for (auto it_2 = variables.begin(); it_2 != variables.end(); it_2++) {
                if ((*it_1).name == (*it_2).name) {
                    is_unique = false;
                    break;
                }
            }
            if (is_unique) variables.push_back(*(it_1));
        }
    }

    return variables;
}

std::string Expression::get_variables() {
    List<Lexem> variables = get_list_vars();

    if (variables.is_empty()) { return ""; }

    std::string vars;
    for (auto it = variables.begin(); it != variables.end(); it++) {
        if (it != variables.begin()) {
            vars += ", ";
        }
        std::string str_val = std::to_string((*it).value);
        str_val.erase(str_val.find_last_not_of('0') + 1, std::string::npos);
        if (str_val[str_val.length() - 1] == '.') str_val.erase(str_val.length() - 1);
        vars += (*it).name + " = " + ((*it).value == DBL_MAX? "?" : str_val);
    }

    return vars;
}

std::string Expression::get_expression() { 
    return to_string(); 
}

double Expression::calculate() {
    Stack<double> stack;

    for (auto it = _polish_record.begin(); it != _polish_record.end(); it++) {
        Lexem lexem = *it;

        switch (lexem.type) {
        case Constant:
            stack.push(lexem.value);
            break;
        case Variable:
            if (lexem.value == DBL_MAX) {
                throw std::logic_error("Переменная '" + lexem.name + "' не определена");
            }
            stack.push(lexem.value);
            break;
        case Function: {
            double val = stack.top();
            stack.pop();
            stack.push(lexem.function(val));
            break;
        }
        case Operator: {
            double b = stack.top();
            stack.pop();
            double a = stack.top();
            stack.pop();
            if (lexem.name == "+") stack.push(a + b);
            else if (lexem.name == "-") stack.push(a - b);
            else if (lexem.name == "*") stack.push(a * b);
            else if (lexem.name == "/") {
                if (b == 0) throw std::logic_error("Некорректное деление на ноль");
                stack.push(a / b);
            }
            else if (lexem.name == "^") stack.push(pow(a, b));
            break;
        }
        }
    }
    return stack.top();
}

void Expression::set_variable(const std::string& name, double value) {
    for (auto it = _polish_record.begin(); it != _polish_record.end(); it++) {
        if ((*it).type == Variable && (*it).name == name) {
            (*it).value = value;
        }
    }
}

List<Lexem> Expression::to_polish_record() {
    List<Lexem> record;
    Stack<Lexem> stack;

    for (auto it = _lexems.begin(); it != _lexems.end(); ++it) {
        switch ((*it).type) {
        case Constant:
            record.push_back(*it);
            break;
        case Variable:
            record.push_back(*it);
            break;
        case Function:
            stack.push(*it);
            break;
        case Operator:
            while (!stack.is_empty() && (stack.top().type == Function ||
                (stack.top().type == Operator && stack.top().priority >= (*it).priority))) {
                record.push_back(stack.top());
                stack.pop();
            }
            stack.push(*it);
            break;
        case OpenBracket:
            stack.push(*it);
            break;
        case ClosedBracket:
            while (stack.top().type != OpenBracket) {
                record.push_back(stack.top());
                stack.pop();
            }
            stack.pop();
            if (!stack.is_empty() && stack.top().type == Function) {
                record.push_back(stack.top());
                stack.pop();
            }
            break;
        }
    }

    while (!stack.is_empty()) {
        record.push_back(stack.top());
        stack.pop();
    }

    return record;
}

std::string Expression::to_string() {
    std::string res;
    bool is_abs = false;
    
    for (auto it = _lexems.begin(); it != _lexems.end(); it++) {
        if ((*it).name == "abs") {
            res += "|";
            it++;
            is_abs = true;
            continue;
        }

        bool need_space = true;

        if ((*it).type == OpenBracket || (*it).type == Function || (*it).name == "^") {
            need_space = false;
        }

        auto next_it = it;
        if (next_it != _lexems.end()) {
            next_it++;
            if (next_it != _lexems.end()){
                if ((*next_it).type == ClosedBracket || (*next_it).name == "^") {
                    need_space = false;
                }
            }
        }

        if ((*it).type == ClosedBracket && is_abs) {
            is_abs = false;
            res += "|";
            if (need_space) res += " ";
            continue;
        }

        res += (*it).name;
        if (need_space) res += " ";
    }

    return res;
}

std::ostream& operator << (std::ostream& out, Expression& expr) {
    out << expr.to_string();
    return out;
}

std::istream& operator >> (std::istream& in, Expression& expr) {
    std::string line;
    std::getline(in, line);
    expr._lexems = Parser::parse(line);
    expr._polish_record = expr.to_polish_record();
    return in;
}
