// Copyright 2026 Viktoria Buzlaeva

#include "../lib_polynom_parser/polynom_parser.h"

List<Monom> PolynomParser::parse(const std::string& str) {
    std::string polynom;
    for (int i = 0; i < str.length(); i++) {
        if (!std::isspace(str[i]))
            polynom += str[i];
    }

    List<Monom> result;
    std::string monom_str = "";

    for (int i = 0; i < polynom.length(); i++) {
        char c = polynom[i];

        if (c == '-') {
            monom_str += c;
            continue;
        }
        else if (c == '+') {
            continue;
        }

        monom_str += read_monom(polynom, i);
        Monom m = Monom::parse(monom_str);
        result.push_back(m);
        monom_str.clear();
    }

    if (result.is_empty()) throw std::logic_error("Empty input");

    return result;
}

std::string PolynomParser::read_monom(const std::string& str, int& pos) {
    std::string monom = "";

    while (pos < str.length() && (std::isdigit(str[pos]) || str[pos] == '.'
        || str[pos] == 'x' || str[pos] == 'y' || str[pos] == 'z'
        || str[pos] == '^')) {
        monom += str[pos];
        pos++;
    }
    if (pos < str.length() && str[pos] != '+' && str[pos] != '-'
        || monom == "") {
        throw std::logic_error("Invalid input");
    }
    pos--;

    return monom;
}
