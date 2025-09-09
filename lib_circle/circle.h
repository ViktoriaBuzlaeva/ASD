// Copyright 2025 Viktoria Buzlaeva

#ifndef LIB_CIRCLE_CIRCLE_H_
#define LIB_CIRCLE_CIRCLE_H_

class Circle {
	Point _cent;
	float _rad;

public:
	Circle(Point point = Point(), float rad = 0);
	Circle(const Circle&);

	Point get_cent();
	float get_rad();

	friend int find_type_of_crossing(const Circle&, const Circle&);
};

#endif  // LIB_CIRCLE_CIRCLE_H_