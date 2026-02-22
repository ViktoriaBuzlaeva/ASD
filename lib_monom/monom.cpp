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
    for (int i = 0; i < VARSCOUNT; i++) {
        if (_powers[i] != other._powers[i]) {
            return _powers[i] < other._powers[i];
        }
    }
    return false;
}

bool Monom::operator < (const Monom& other) const noexcept {
    if (*this == other) return false;
    return other > *this;
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

Monom Monom::operator * (const double num) const noexcept {
    Monom res(*this);
    res *= num;
    return res;
}

Monom Monom::operator / (const double num) const {
    Monom res(*this);
    res /= num;
    return res;
}

Monom operator * (const double num, const Monom& monom) noexcept {
    Monom res(monom);
    res *= num;
    return res;
}

Monom Monom::operator - () const noexcept {
    Monom res(*this);
    res._coeff = -_coeff;
    return res;
}

double Monom::calculate_point(double x, double y, double z) const {
    return _coeff * pow(x, _powers[0])
        * pow(y, _powers[1]) * pow(z, _powers[2]);
}

Monom Monom::parse(const std::string& str) {
    if (str.empty()) throw std::logic_error("Empty monom");

    double coeff = 1.0;
    int powers[] = { 0, 0, 0 };
    bool found[] = { false, false, false };
    int sign = 1;
    int pos = 0;

    if (str[pos] == '-') {
        sign = -1;
        pos++;
    }

    if (pos < str.size() && std::isdigit(str[pos])) {
        coeff = std::stod(read_num(str, pos));
        coeff *= sign;
    }
    else {
        coeff = sign;
    }

    while (pos < str.size()) {
        int var;
        switch (str[pos]) {
        case 'x': var = 0; break;
        case 'y': var = 1; break;
        case 'z': var = 2; break;
        default: throw std::logic_error("Invalid character");
        }
        if (found[var]) throw std::logic_error
            ("Variable has been already met");
        found[var] = true;
        
        pos++;

        int power = 1;
        if (pos < str.size() && str[pos] == '^') {
            pos++;
            if (str[pos] == '-')
                throw std::logic_error("Power can't be negative");
            std::string num_str = read_num(str, pos);
            if (num_str == "")
                throw std::logic_error("Invalid number input");
            if (num_str.find('.') != std::string::npos) 
                throw std::logic_error("Power must be integer");
            power = std::stoi(num_str);
        }
        powers[var] += power;
    }

    return Monom(coeff, powers);
}

std::string Monom::to_string() const {
    if (_coeff == 0) return "0";
    if (_coeff == 1 && is_const()) return "1";
    if (_coeff == -1 && is_const()) return "-1";

    std::string res = "";

    if (_coeff == -1) {
        res += "-";
    }
    else if (_coeff != 1) {
        std::string str_coeff = std::to_string(_coeff);
        str_coeff.erase(str_coeff.find_last_not_of('0') + 1, std::string::npos);
        if (str_coeff[str_coeff.length() - 1] == '.')
            str_coeff.erase(str_coeff.length() - 1);
        res += str_coeff;
    }

    char vars[] = { 'x', 'y', 'z' };

    for (int i = 0; i < VARSCOUNT; ++i) {
        if (_powers[i] != 0) {
            res += vars[i];
            if (_powers[i] != 1) {
                res += "^" + std::to_string(_powers[i]);
            }
        }
    }

    return res;
}

std::ostream& operator << (std::ostream& out, const Monom& monom) {
    out << monom.to_string();
    return out;
}

std::istream& operator >> (std::istream& in, Monom& monom) {
    std::string m;
    in >> m;
    monom = Monom::parse(m);
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

bool Monom::is_const() const {
    for (int i = 0; i < VARSCOUNT; i++) {
        if (_powers[i] != 0) return false;
    }
    return true;
}
