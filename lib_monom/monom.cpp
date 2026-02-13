// Copyright 2026 Viktoria Buzlaeva

#include "../lib_monom/monom.h"

Monom::Monom(double coeff) : _coeff(coeff) {
    for (int i = 0; i < VARSCOUNT; i++) {
        _powers[i] = 0;
    }
}

Monom::Monom(double coeff, const int powers[VARSCOUNT]) : _coeff(coeff) {
    for (int i = 0; i < VARSCOUNT; i++) {
        if (powers[i] < 0) 
            throw std::invalid_argument("Powers can't be negative");
        _powers[i] = powers[i];
    }
}

Monom::Monom(double coeff, const std::initializer_list<int> powers) {
    if (powers.size() != VARSCOUNT) throw std::logic_error
        ("Error in init constructor: incorrect input!");
    _coeff = coeff;
    auto it = powers.begin();
    for (int i = 0; i < VARSCOUNT; i++) {
        if (*it < 0)
            throw std::invalid_argument("Powers can't be negative");
        _powers[i] = *it;
        it++;
    }
}

Monom::Monom(const Monom& other) {
    if (&other == NULL) throw std::logic_error
        ("Error in copy constructor: other monom doesn't exist!");
    _coeff = other._coeff;
    for (int i = 0; i < VARSCOUNT; i++) {
        _powers[i] = other._powers[i];
    }
}

bool Monom::operator == (const Monom& other) const noexcept {
    for (int i = 0; i < VARSCOUNT; i++) {
        if (_powers[i] != other._powers[i]) return false;
    }
    return true;
}

bool Monom::operator != (const Monom& other) const noexcept {
    return !(*this == other);
}

bool Monom::operator > (const Monom & other) const noexcept {
    for (int i = 0; i < VARSCOUNT - 1; i++) {
        if (_powers[i] < other._powers[i]) return true;
        if (_powers[i] > other._powers[i]) return false;
    }
    if (_powers[VARSCOUNT - 1] >= other._powers[VARSCOUNT - 1]) return true;
    return false;
}

bool Monom::operator < (const Monom& other) const noexcept {
    if (*this == other) return false;
    return !(*this > other);
}

Monom& Monom::operator = (const Monom& other) noexcept {
    if (this != &other) {
        _coeff = other._coeff;
        for (int i = 0; i < VARSCOUNT; i++) {
            _powers[i] = other._powers[i];
        }
    }
    return *this;
}

Monom& Monom::operator += (const Monom& other) {
    if (*this != other) throw std::logic_error("Can't add not similar monoms");
    _coeff += other._coeff;
    return *this;
}

Monom& Monom::operator -= (const Monom& other) {
    if (*this != other) throw std::logic_error("Can't sub not similar monoms");
    _coeff -= other._coeff;
    return *this;
}

Monom& Monom::operator *= (const Monom& other) noexcept {
    _coeff *= other._coeff;
    for (int i = 0; i < VARSCOUNT; i++) {
        _powers[i] += other._powers[i];
    }
    return *this;
}

Monom& Monom::operator /= (const Monom& other) {
    for (int i = 0; i < VARSCOUNT; i++) {
        if (_powers[i] < other._powers[i])
            throw std::invalid_argument("Powers can't be negative");
    }
    if (other._coeff == 0) throw std::logic_error
        ("Incorrect division by zero");
    _coeff /= other._coeff;
    for (int i = 0; i < VARSCOUNT; i++) {
        _powers[i] -= other._powers[i];
    }
    return *this;
}

Monom& Monom::operator *= (const double num) noexcept {
    _coeff *= num;
    return *this;
}

Monom& Monom::operator /= (const double num) {
    if (num == 0) throw std::logic_error("Incorrect division by zero");
    _coeff /= num;
    return *this;
}

Monom Monom::operator + (const Monom& other) const {
    Monom res(*this);
    res += other;
    return res;
}

Monom Monom::operator - (const Monom& other) const {
    Monom res(*this);
    res -= other;
    return res;
}

Monom Monom::operator * (const Monom& other) const noexcept {
    Monom res(*this);
    res *= other;
    return res;
}

Monom Monom::operator / (const Monom& other) const {
    Monom res(*this);
    res /= other;
    return res;
}

Monom Monom::operator *= (const double num) const noexcept {
    Monom res(*this);
    res *= num;
    return res;
}

Monom Monom::operator /= (const double num) const {
    Monom res(*this);
    res /= num;
    return res;
}

Monom Monom::operator - () const noexcept {
    Monom res(*this);
    res._coeff = -_coeff;
    return res;
}

double Monom::calculate_point(double x, double y, double z) {
    return _coeff * pow(x, _powers[0])
        * pow(y, _powers[1]) * pow(z, _powers[2]);
}

std::ostream& operator << (std::ostream& out, const Monom& monom) {
    if (monom._coeff == 0) {
        out << "0";
        return out;
    }

    out << monom._coeff;

    char vars[] = { 'x', 'y', 'z' };

    for (int i = 0; i < VARSCOUNT; ++i) {
        if (monom._powers[i] != 0) {
            out << vars[i];
            if (monom._powers[i] != 1) {
                out << "^" << monom._powers[i];
            }
        }
    }

    return out;
}

std::istream& operator >> (std::istream& in, Monom& monom) {
    std::string m;
    in >> m;

    double coeff = 1.0;
    int powers[] = { 0, 0, 0 };
    int sign = 1;

    int i = 0;
    if (m[i] == '-') {
        sign = -1;
        i++;
    }

    if (i < m.size() && std::isdigit(m[i])) {
        coeff = std::stod(read_num(m, i));
        coeff *= sign;
    }
    else {
        coeff = sign;
    }

    while (i < m.size()) {
        int var;
        char c = m[i];
        switch (c) {
        case 'x':
            var = 0;
            break;
        case 'y':
            var = 1;
            break;
        case 'z':
            var = 2;
            break;
        default:
            throw std::logic_error("invalid variable");
        }
        i++;

        int power = 1;
        if (i < m.size() && m[i] == '^') {
            i++;
            power = std::stoi(read_num(m, i));
        }
        powers[var] += power;
    }

    try {
        monom = Monom(coeff, powers);
    }
    catch (std::logic_error e) {
        std::cerr << e.what() << std::endl;
    }

    return in;
}

std::string read_num(const std::string& str, int& pos) {
    std::string number = "";
    bool has_dot = false;

    while (pos < str.length() && (std::isdigit(str[pos]) || str[pos] == '.')) {
        if (!std::isdigit(str[pos])) {
            if (has_dot || str[pos] != '.') throw std::logic_error("invalid number input");
            has_dot = true;
        }
        number += str[pos];
        pos++;
    }

    return number;
}
