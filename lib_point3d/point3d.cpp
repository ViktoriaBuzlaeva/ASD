// Copyright 2025 Viktoria Buzlaeva

#include <math.h>
#include "../lib_point3d/point3d.h"

Point3D::Point3D(float x, float y, float z) : Point(x, y), _z(z) {}

Point3D::Point3D(const Point& other, float z) : Point(other), _z(z) {}

Point3D::Point3D(const Point3D& other) {
    _x = other._x;
    _y = other._y;
    _z = other._z;
}

float Point3D::z() {
    return _z;
}

const float Point3D::z() const {
    return _z;
}

bool Point3D::operator == (const Point3D& other) const {
    if (_x != other._x || _y != other._y || _z != other._z) return false;
    return true;
}

bool Point3D::operator != (const Point3D& other) const {
    return !(*this == other);
}

float Point3D::find_distance(const Point3D& other) const {
    float dis;
    if (_x == other._x) {
        Point point_1(_y, _z);
        Point point_2(other._y, other._z);
        dis = point_1.find_distance(point_2);
    }
    else if (_y == other._y) {
        Point point_1(_x, _z);
        Point point_2(other._x, other._z);
        dis = point_1.find_distance(point_2);
    }
    else if(_z == other._z) {
        Point point_1(_x, _y);
        Point point_2(other._x, other._y);
        dis = point_1.find_distance(point_2);
    }
    else {
        float a = _y - other._y;
        float b = _x - other._x;
        float c = _z - other._z;
        dis = sqrt(a * a + b * b + c * c);
    }
    return dis;
}
