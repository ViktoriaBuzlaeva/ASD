// Copyright 2026 Viktoria Buzlaeva

#include "../lib_polynom/polynom.h"

Polynom::Polynom() : _name("") {
    Monom zero;
    _polynom.push_back(zero);
}

Polynom::Polynom(const Monom& monom) {
    _polynom.push_back(monom);
}

Polynom::Polynom(std::string str) {

}

Polynom::Polynom(const Polynom& other) {
    if (&other == NULL) throw std::logic_error
        ("Error in copy constructor: other moonom doesn't exist!");
    _polynom = other._polynom;
    _name = other._name;
}
