// Copyright 2026 Viktoria Buzlaeva

#ifndef LIB_MONOM_MONOM_H_
#define LIB_MONOM_MONOM_H_

#include <iostream>

#define VARSCOUNT 3

class Monom {
	double _coeff;
	int _powers[VARSCOUNT];

public:
	Monom(double coeff = 0.0);
	Monom(double coeff, const int powers[VARSCOUNT]);
	Monom(double coeff, const std::initializer_list<int> powers);
	Monom(const Monom&);

	bool operator == (const Monom&) const noexcept;
	bool operator != (const Monom&) const noexcept;
	bool operator > (const Monom&) const noexcept;
	bool operator < (const Monom&) const noexcept;

	Monom& operator = (const Monom&) noexcept;

	Monom& operator += (const Monom&);
	Monom& operator -= (const Monom&);
	Monom& operator *= (const Monom&) noexcept;
	Monom& operator /= (const Monom&);

	Monom operator + (const Monom&) const;
	Monom operator - (const Monom&) const;
	Monom operator * (const Monom&) const noexcept;
	Monom operator / (const Monom&) const;
};

#endif  // LIB_MONOM_MONOM_H_
