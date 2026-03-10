// Copyright 2026 Viktoria Buzlaeva

#include "../lib_polynom/polynom.h"

Polynom::Polynom() {
    Monom zero;
    _polynom.push_back(zero);
}

Polynom::Polynom(const Monom& monom) {
    _polynom.push_back(monom);
}

Polynom::Polynom(std::string str) {
    _polynom = PolynomParser::parse(str);
    sort();
    remove_zero_monoms();
}

Polynom::Polynom(const Polynom& other) {
    if (&other == NULL) throw std::logic_error
        ("Error in copy constructor: other monom doesn't exist!");
    _polynom = other._polynom;
}

bool Polynom::operator == (const Polynom& other) const noexcept {
    auto it_1 = _polynom.begin();
    auto it_2 = other._polynom.begin();
    for (; it_1 != _polynom.end() && it_2 != other._polynom.end(); it_1++, it_2++) {
        if ((*it_1).coeff() != (*it_2).coeff() || *it_1 != *it_2) {
            return false;
        }
    }
    if (it_1 != _polynom.end() || it_2 != _polynom.end()) {
        return false;
    }
    return true;
}

bool Polynom::operator != (const Polynom& other) const noexcept {
    return !(*this == other);
}

Polynom& Polynom::operator = (const Polynom& other) noexcept {
    this->_polynom = other._polynom;
    return *this;
}

Polynom& Polynom::operator += (const Polynom& other) noexcept {
    auto it = other._polynom.begin();
    while (it != other._polynom.end()) {
        insert_monom(*it);
        it++;
    }
    remove_zero_monoms();
    return *this;
}

Polynom& Polynom::operator -= (const Polynom& other) noexcept {
    *this += -other;
    return *this;
}

Polynom& Polynom::operator *= (const Polynom& other) noexcept {
    *this = *this * other;
    return *this;
}

Polynom& Polynom::operator += (const Monom& monom) noexcept {
    insert_monom(monom);
    remove_zero_monoms();
    return *this;
}

Polynom& Polynom::operator -= (const Monom& monom) noexcept {
    *this += -monom;
    return *this;
}

Polynom& Polynom::operator *= (const Monom& monom) noexcept {
    for (auto it = _polynom.begin(); it != _polynom.end(); it++) {
        (*it) *= monom;
    }
    remove_zero_monoms();
    return *this;
}

Polynom& Polynom::operator /= (const Monom& monom) {
    *this = *this / monom;
    return *this;
}

Polynom& Polynom::operator += (const double num) noexcept {
    insert_monom(Monom(num));
    remove_zero_monoms();
    return *this;
}

Polynom& Polynom::operator -= (const double num) noexcept {
    *this += -num;
    return *this;
}

Polynom& Polynom::operator *= (const double num) noexcept {
    for (auto it = _polynom.begin(); it != _polynom.end(); it++) {
        (*it) *= num;
    }
    remove_zero_monoms();
    return *this;
}

Polynom& Polynom::operator /= (const double num) {
    for (auto it = _polynom.begin(); it != _polynom.end(); it++) {
        (*it) /= num;
    }
    return *this;
}

Polynom Polynom::operator + (const Polynom& other) const noexcept {
    Polynom res(*this);
    res += other;
    return res;
}

Polynom Polynom::operator - (const Polynom& other) const noexcept {
    Polynom res(*this);
    res -= other;
    return res;
}

Polynom Polynom::operator * (const Polynom& other) const noexcept {
    Polynom res;
    res._polynom.pop_front();

    for (auto it_2 = other._polynom.begin(); it_2 != other._polynom.end(); it_2++) {
        res += *this * (*it_2);
        // res.insert_monom((*it_1) * (*it_2));
    }

    if (res._polynom.is_empty()) {
        Monom zero;
        res._polynom.push_back(zero);
    }
    else {
        res.remove_zero_monoms();
    }
    return res;
}

Polynom Polynom::operator + (const Monom& monom) const noexcept {
    Polynom res(*this);
    res += monom;
    return res;
}

Polynom Polynom::operator - (const Monom& monom) const noexcept {
    Polynom res(*this);
    res -= monom;
    return res;
}

Polynom Polynom::operator * (const Monom& monom) const noexcept {
    Polynom res(*this);
    res *= monom;
    return res;
}

Polynom Polynom::operator / (const Monom& monom) const {
    Polynom res(*this);
    for (auto it = res._polynom.begin(); it != res._polynom.end(); it++) {
        *it /= monom;
    }
    return res;
}

Polynom Polynom::operator + (const double num) const noexcept {
    Polynom res(*this);
    res += num;
    return res;
}

Polynom Polynom::operator - (const double num) const noexcept {
    Polynom res(*this);
    res -= num;
    return res;
}

Polynom Polynom::operator * (const double num) const noexcept {
    Polynom res(*this);
    res *= num;
    return res;
}

Polynom Polynom::operator / (const double num) const {
    Polynom res(*this);
    res /= num;
    return res;
}

Polynom operator + (const Monom& monom, const Polynom& p) noexcept {
    Polynom res(p);
    res += monom;
    return res;
}

Polynom operator - (const Monom& monom, const Polynom& p) noexcept {
    Polynom res(-p);
    res += monom;
    return res;
}

Polynom operator * (const Monom& monom, const Polynom& p) noexcept {
    Polynom res(p);
    res *= monom;
    return res;
}

Polynom operator + (const double num, const Polynom& p) noexcept {
    Polynom res(p);
    res += num;
    return res;
}

Polynom operator - (const double num, const Polynom& p) noexcept {
    Polynom res(-p);
    res += num;
    return res;
}

Polynom operator * (const double num, const Polynom& p) noexcept {
    Polynom res(p);
    res *= num;
    return res;
}

Polynom Polynom::operator - () const noexcept {
    Polynom res(*this);
    for (auto it = res._polynom.begin(); it != res._polynom.end(); it++)
        *it = -(*it);
    return res;
}

double Polynom::calculate_point(double x, double y, double z) const {
    double res = 0;
    for (auto it = _polynom.begin(); it != _polynom.end(); it++) {
        res += (*it).calculate_point(x, y, z);
    }
    return res;
}

std::string Polynom::to_string() const {
    std::string res;

    bool first = true;
    for (auto it = _polynom.begin(); it != _polynom.end(); it++) {
        Monom m = *it;
        std::string monom_str = m.to_string();

        if (first) {
            res += monom_str;
            first = false;
        }
        else {
            if (!monom_str.empty() && monom_str[0] == '-') {
                res += " - " + monom_str.substr(1);
            }
            else {
                res += " + " + monom_str;
            }
        }
    }

    return res;
}

std::ostream& operator << (std::ostream& out, const Polynom& polynom) {
    out << polynom.to_string();
    return out;
}

std::istream& operator >> (std::istream& in, Polynom& polynom) {
    std::string p;
    std::getline(in, p);
    polynom._polynom = PolynomParser::parse(p);
    return in;
}

void Polynom::sort() {
    if (!is_sorted()) {
        TVector<Monom> monoms;
        for (auto it = _polynom.begin(); it != _polynom.end(); it++) {
            monoms.push_back(*it);
        }
        sort_hoare(monoms);

        while (!_polynom.is_empty()) {
            _polynom.pop_front();
        }

        for (auto it = monoms.begin(); it != monoms.end(); it++) {
            if (!_polynom.is_empty()) {
                Monom& last = _polynom.tail()->value;
                if (last != *it) {
                    _polynom.push_back(*it);
                }
                else {
                    last += *it;
                    if (last.coeff() == 0) {
                        _polynom.pop_back();
                    }
                }
            }
            else {
                _polynom.push_back(*it);
            }
        }
        if (_polynom.is_empty()) {
            Monom zero;
            _polynom.push_back(zero);
        }
    }
}

bool Polynom::is_sorted() {
    auto curr = _polynom.begin();
    auto prev = curr;
    curr++;
    for (; curr != _polynom.end(); curr++, prev++) {
        if (*prev > *curr || *prev == *curr) {
            return false;
        }
    }
    return true;
}

void Polynom::remove_zero_monoms() {
    bool has_zero = false;
    for (auto it = _polynom.begin(); it != _polynom.end(); it++) {
        if ((*it).coeff() == 0) {
            has_zero = true;
            break;
        }
    }
    if (has_zero) {
        List<Monom> new_polynom;
        for (auto it = _polynom.begin(); it != _polynom.end(); it++) {
            if ((*it).coeff() != 0) {
                new_polynom.push_back(*it);
            }
        }
        if (new_polynom.is_empty()) {
            Monom zero;
            new_polynom.push_back(zero);
        }
        _polynom = new_polynom;
    }
}

void Polynom::insert_monom(const Monom& monom) {
    if (monom.coeff() == 0) return;

    auto pos = _polynom.begin();
    for (; pos != _polynom.end(); pos++) {
        if (*pos == monom) {
            Monom& similar_monom = *pos;
            similar_monom += monom;
            break;
        }
        else if (*pos > monom) {
            if (pos == _polynom.begin()) {
                _polynom.push_front(monom);
            }
            else {
                Node<Monom>* prev = nullptr;
                Node<Monom>* curr = _polynom.head();
                while (curr != nullptr && curr->value != *pos) {
                    prev = curr;
                    curr = curr->next;
                }
                _polynom.insert(prev, monom);
            }
            break;
        }
    }
    if (pos == _polynom.end()) {
        _polynom.push_back(monom);
    }
}
