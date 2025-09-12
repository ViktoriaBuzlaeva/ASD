// Copyright 2025 Viktoria Buzlaeva

#include <Windows.h>
#include <iostream>
#include <string>
#include <stdexcept>
#include "../lib_point/point.h"
#include "../lib_circle/circle.h"

Circle::Circle(float rad, float x, float y) : _cent(Point(x, y)) {
	if (rad < 0)
		throw std::invalid_argument("Input Error: radius can't be less than zero");
	_rad = rad;
}

Circle::Circle(float rad, Point cent) : _cent(cent) {
	if (rad < 0)
	throw std::invalid_argument("Input Error: radius can't be less than zero");
	_rad = rad;
}

Circle::Circle(const Circle& other) {
	_cent = other._cent;
	_rad = other._rad;
}

Point Circle::cent() {
	return _cent;
}

float Circle::rad() {
	return _rad;
}

const Point Circle::cent() const {
	return _cent;
}

const float Circle::rad() const {
	return _rad;
}

bool Circle::operator == (const Circle& other) const {
	if (_rad != other._rad || _cent != other._cent) return false;
	return true;
}

bool Circle::operator != (const Circle& other) const {
	return !(*this == other);
}
