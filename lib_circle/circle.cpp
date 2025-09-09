// Copyright 2025 Viktoria Buzlaeva

#include <Windows.h>
#include <iostream>
#include <string>
#include "../lib_point/point.h"
#include "../lib_circle/circle.h"

Circle::Circle(Point cent, float rad) : _cent(cent), _rad(rad) {}

Circle::Circle(const Circle& other) {
	_cent = other._cent;
	_rad = other._rad;
}

Point Circle::get_cent() {
	return _cent;
}

float Circle::get_rad() {
	return _rad;
}
