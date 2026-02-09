// Copyright 2026 Viktoria Buzlaeva

#include "../lib_monom/monom.h"

Monom::Monom(double coeff) : _coeff(coeff) {
    for (int i = 0; i < VARSCOUNT; i++) {
        _powers[i] = 0;
    }
}

Monom::Monom(double coeff, const int powers[VARSCOUNT]) : _coeff(coeff) {
    for (int i = 0; i < VARSCOUNT; i++) {
        _powers[i] = powers[i];
    }
}

Monom::Monom(double coeff, const std::initializer_list<int> powers) {
    if (powers.size() != VARSCOUNT) throw std::logic_error
        ("Error in init constructor: incorrect input!");
    _coeff = coeff;
    auto it = powers.begin();
    for (int i = 0; i < VARSCOUNT; i++) {
        _powers[i] = *it;
        it++;
    }
}

Monom::Monom(const Monom& other) {
    if (&other == NULL) throw std::logic_error
        ("Error in copy constructor: other moonom doesn't exist!");
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
    if (other._coeff == 0) throw std::logic_error
        ("Incorrect division by zero");
    _coeff /= other._coeff;
    for (int i = 0; i < VARSCOUNT; i++) {
        _powers[i] -= other._powers[i];
    }
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
