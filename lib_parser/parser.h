// Copyright 2025 Viktoria Buzlaeva

#ifndef LIB_PARSER_PARSER_H_
#define LIB_PARSER_PARSER_H_

#include "../lib_functions/functions.h"
#include "../lib_lexem/lexem.h"
#include "../lib_list/list.h"
#include "../lib_stack/stack.h"

namespace Parser {
    List<Lexem> parse(const std::string&);

    bool is_correct_function(const std::string&, int);
    bool is_matching_brackets(const char&, const char&);

    std::string read_num(const std::string&, int&);
    std::string read_name(const std::string&, int&);

    double(*get_function(const std::string&))(double);
    int get_priority(const std::string&);

    std::string error_message(int, const std::string&);
}

#endif  // LIB_PARSER_PARSER_H_
