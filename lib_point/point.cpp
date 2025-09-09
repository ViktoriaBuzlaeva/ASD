// Copyright 2025 Viktoria Buzlaeva

#include <math.h>
#include "../lib_point/point.h"

Point::Point(float x, float y) : _x(x), _y(y) {}

Point::Point(const Point& other) {
	_x = other._x;
	_y = other._y;
}

float Point::get_x() {
	return _x;
}

float Point::get_y() {
	return _y;
}

float Point::find_distance(const Point& other) const {
	float dis;
	if (_x == other._x) {
		dis = _y - other._y;
	}
	else if (_y == other._y) {
		dis = _x - other._x;
	}
	else {
		float a = _y - other._y;
		float b = _x - other._x;
		float c = a * a + b * b;
		dis = sqrt(c);
	}
	return dis;
}
