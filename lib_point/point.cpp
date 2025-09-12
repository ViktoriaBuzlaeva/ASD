// Copyright 2025 Viktoria Buzlaeva

#include <math.h>
#include "../lib_point/point.h"

Point::Point(float x, float y) : _x(x), _y(y) {}

Point::Point(const Point& other) {
	_x = other._x;
	_y = other._y;
}

float Point::x() {
	return _x;
}

float Point::y() {
	return _y;
}

const float Point::x() const {
	return _x;
}

const float Point::y() const {
	return _y;
}

bool Point::operator == (const Point& other) const {
	if (_x != other._x || _y != other._y) return false;
	return true;
}

bool Point::operator != (const Point& other) const {
	return !(*this == other);
}

float Point::find_distance(const Point& other) const {
	float dis;
	if (_x == other._x) {
		dis = fabs(_y - other._y);
	}
	else if (_y == other._y) {
		dis = fabs(_x - other._x);
	}
	else {
		float a = _y - other._y;
		float b = _x - other._x;
		dis = sqrt(a * a + b * b);
	}
	return dis;
}
