// Copyright 2026 Viktoria Buzlaeva

#ifndef LIB_MONOM_MONOM_H_
#define LIB_MONOM_MONOM_H_

#include <iostream>
#include <string>
#include <cmath>

#define VARSCOUNT 3

class Monom {
    double _coeff;
    int _powers[VARSCOUNT];

public:
    Monom(double coeff = 0.0);
    Monom(double coeff, const int powers[VARSCOUNT]);
    Monom(double coeff, const std::initializer_list<int> powers);
    Monom(const Monom&);

    const double& coeff() const { return _coeff; }
    double& coeff() { return _coeff; }

    bool operator == (const Monom&) const noexcept;
    bool operator != (const Monom&) const noexcept;
    bool operator > (const Monom&) const noexcept;
    bool operator < (const Monom&) const noexcept;

    Monom& operator = (const Monom&) noexcept;

    Monom& operator += (const Monom&);
    Monom& operator -= (const Monom&);
    Monom& operator *= (const Monom&) noexcept;
    Monom& operator /= (const Monom&);

    Monom& operator *= (const double) noexcept;
    Monom& operator /= (const double);

    Monom operator + (const Monom&) const;
    Monom operator - (const Monom&) const;
    Monom operator * (const Monom&) const noexcept;
    Monom operator / (const Monom&) const;

    Monom operator * (const double) const noexcept;
    Monom operator / (const double) const;
    friend Monom operator * (const double, const Monom&) noexcept;

    Monom operator - () const noexcept;

    double calculate_point(double x = 0, double y = 0, double z = 0) const;

    static Monom parse(const std::string&);
    std::string to_string() const;

    friend std::ostream& operator << (std::ostream&, const Monom&);
    friend std::istream& operator >> (std::istream&, Monom&);

private:
    friend std::string read_num(const std::string&, int&);
    bool is_const() const;
};

#endif  // LIB_MONOM_MONOM_H_
