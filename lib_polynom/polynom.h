// Copyright 2026 Viktoria Buzlaeva

#ifndef LIB_POLYNOM_POLYNOM_H_
#define LIB_POLYNOM_POLYNOM_H_

#include "../lib_list/list.h"
#include "../lib_monom/monom.h"

class Polynom {
	List<Monom> _polynom;
	std::string _name;

public:
	Polynom();
	Polynom(const Monom&);
	Polynom(std::string);
	Polynom(const Polynom&);

	Polynom& operator = (const Polynom&) noexcept;

	Polynom& operator += (const Polynom&) noexcept;
	Polynom& operator -= (const Polynom&) noexcept;
	Polynom& operator *= (const Polynom&) noexcept;
	Polynom& operator /= (const Polynom&) noexcept;

	Polynom& operator += (const Monom&) noexcept;
	Polynom& operator -= (const Monom&) noexcept;
	Polynom& operator *= (const Monom&) noexcept;
	Polynom& operator /= (const Monom&) noexcept;

	Polynom operator + (const Polynom&) const noexcept;
	Polynom operator - (const Polynom&) const noexcept;
	Polynom operator * (const Polynom&) const noexcept;
	Polynom operator / (const Polynom&) const noexcept;

	Polynom operator + (const Monom&) const noexcept;
	Polynom operator - (const Monom&) const noexcept;
	Polynom operator * (const Monom&) const noexcept;
	Polynom operator / (const Monom&) const noexcept;

	friend Polynom operator + (const Monom&, const Polynom&) noexcept;
	friend Polynom operator - (const Monom&, const Polynom&) noexcept;
	friend Polynom operator * (const Monom&, const Polynom&) noexcept;
	friend Polynom operator / (const Monom&, const Polynom&) noexcept;

	friend std::ostream& operator << (std::ostream&, const Polynom&);
	friend std::istream& operator >> (std::istream&, Polynom&);
};

#endif  // LIB_POLYNOM_POLYNOM_H_
