// Copyright 2025 Viktoria Buzlaeva

#ifndef LIB_CIRCLE_CIRCLE_H_
#define LIB_CIRCLE_CIRCLE_H_

#include "../lib_point/point.h"

class Circle {
	Point _cent;
	float _rad;

public:
	Circle(float rad = 0, Point point = 0);
	Circle(const Circle&);

	Point cent();
	float rad();

	const Point cent() const;
	const float rad() const;

	bool operator == (const Circle&) const;
	bool operator != (const Circle&) const;
};

#endif  // LIB_CIRCLE_CIRCLE_H_