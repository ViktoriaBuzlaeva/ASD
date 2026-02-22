// Copyright 2026 Viktoria Buzlaeva

#ifndef LIB_POLYNOM_PARSER_POLYNOM_PARSER_H_
#define LIB_POLYNOM_PARSER_POLYNOM_PARSER_H_

#include "../lib_list/list.h"
#include "../lib_monom/monom.h"

namespace PolynomParser {
    List<Monom> parse(const std::string&);
    std::string read_monom(const std::string&, int&);
}

#endif  // LIB_POLYNOM_PARSER_POLYNOM_PARSER_H_