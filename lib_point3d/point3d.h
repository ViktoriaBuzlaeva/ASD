// Copyright 2025 Viktoria Buzlaeva

#ifndef LIB_POINT_POINT3D_H_
#define LIB_POINT_POINT3D_H_

#include "../lib_point/point.h"

class Point3D : public Point {
	float _z;

public:
	Point3D(float x = 0, float y = 0, float z = 0);
	Point3D(const Point&, float);
	Point3D(const Point3D&);

	float z();

	const float z() const;

	bool operator == (const Point3D&) const;
	bool operator != (const Point3D&) const;

	float find_distance(const Point3D&) const;
};

#endif  // LIB_POINT_POINT3D_H_