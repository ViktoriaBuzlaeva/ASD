// Copyright 2025 Viktoria Buzlaeva

#ifndef LIB_EXPRESSION_EXPRESSION_H_
#define LIB_EXPRESSION_EXPRESSION_H_

#include "../lib_parser/parser.h"

class Expression {
    List<Lexem> _lexems;
    List<Lexem> _polish_record;

public:
    Expression();
    Expression(const std::string&);
    Expression(const List<Lexem>&);

    List<Lexem> get_list_vars();

    std::string get_variables();
    std::string get_expression();

    void set_variable(const std::string& name, double value);
    double calculate();

    List<Lexem> to_polish_record();
    std::string to_string();

    friend std::ostream& operator << (std::ostream&, Expression&);
    friend std::istream& operator >> (std::istream&, Expression&);
};


#endif  // LIB_EXPRESSION_EXPRESSION_H_
