// Copyright 2025 Viktoria Buzlaeva

#include <Windows.h>
#include <iostream>
#include <string>
#include <stdexcept>
#include "../lib_sphere/sphere.h"

Sphere::Sphere(float rad, float x, float y, float z) :
    _cent(Point3D(x, y, z)) {
    if (rad < 0)
        throw std::invalid_argument("Input Error: radius can't be less than zero");
    _rad = rad;
}

Sphere::Sphere(float rad, Point3D cent) : _cent(cent) {
    if (rad < 0)
        throw std::invalid_argument("Input Error: radius can't be less than zero");
    _rad = rad;
}

Sphere::Sphere(const Sphere& other) {
    _cent = other._cent;
    _rad = other._rad;
}

Point3D Sphere::cent() {
    return _cent;
}

const Point3D Sphere::cent() const {
    return _cent;
}

bool Sphere::operator == (const Sphere& other) const {
    if (_rad != other._rad || _cent != other._cent) return false;
    return true;
}

bool Sphere::operator != (const Sphere& other) const {
    return !(*this == other);
}
