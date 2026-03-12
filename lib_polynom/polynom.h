// Copyright 2026 Viktoria Buzlaeva

#ifndef LIB_POLYNOM_POLYNOM_H_
#define LIB_POLYNOM_POLYNOM_H_

#include <sstream>
#include "../lib_polynom_parser/polynom_parser.h"
#include "../lib_tvector/tvector.h"

class Polynom {
	List<Monom> _polynom;

public:
	Polynom();
	Polynom(const Monom&);
	Polynom(std::string);
	Polynom(const Polynom&);

	bool operator == (const Polynom&) const noexcept;
	bool operator != (const Polynom&) const noexcept;

	Polynom& operator = (const Polynom&) noexcept;

	Polynom& operator += (const Polynom&) noexcept;
	Polynom& operator -= (const Polynom&) noexcept;
	Polynom& operator *= (const Polynom&) noexcept;

	Polynom& operator += (const Monom&) noexcept;
	Polynom& operator -= (const Monom&) noexcept;
	Polynom& operator *= (const Monom&) noexcept;
	Polynom& operator /= (const Monom&);

	Polynom& operator += (const double) noexcept;
	Polynom& operator -= (const double) noexcept;
	Polynom& operator *= (const double) noexcept;
	Polynom& operator /= (const double);

	Polynom operator + (const Polynom&) const noexcept;
	Polynom operator - (const Polynom&) const noexcept;
	Polynom operator * (const Polynom&) const noexcept;

	Polynom operator + (const Monom&) const noexcept;
	Polynom operator - (const Monom&) const noexcept;
	Polynom operator * (const Monom&) const noexcept;
	Polynom operator / (const Monom&) const;

	Polynom operator + (const double) const noexcept;
	Polynom operator - (const double) const noexcept;
	Polynom operator * (const double) const noexcept;
	Polynom operator / (const double) const;

	friend Polynom operator + (const Monom&, const Polynom&) noexcept;
	friend Polynom operator - (const Monom&, const Polynom&) noexcept;
	friend Polynom operator * (const Monom&, const Polynom&) noexcept;

	friend Polynom operator + (const double, const Polynom&) noexcept;
	friend Polynom operator - (const double, const Polynom&) noexcept;
	friend Polynom operator * (const double, const Polynom&) noexcept;

	Polynom operator - () const noexcept;

	double calculate_point(double x = 0, double y = 0, double z = 0) const;

	std::string to_string() const;

	friend std::ostream& operator << (std::ostream&, const Polynom&);
	friend std::istream& operator >> (std::istream&, Polynom&);

private:
	void sort();
	bool is_sorted();
	void remove_zero_monoms();
	void insert_monom(const Monom&);
};

#endif  // LIB_POLYNOM_POLYNOM_H_
