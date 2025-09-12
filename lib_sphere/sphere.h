// Copyright 2025 Viktoria Buzlaeva

#ifndef LIB_SPHERE_SPHERE_H_
#define LIB_SPHERE_SPHERE_H_

#include "../lib_point3d/point3d.h"
#include "../lib_circle/circle.h"

class Sphere : public Circle {
	Point3D _cent;

public:
	Sphere(float rad = 0, Point3D cent = 0);
	Sphere(const Sphere&);

	Point3D cent();

	const Point3D cent() const;

	bool operator == (const Sphere&) const;
	bool operator != (const Sphere&) const;
};

#endif  // LIB_SPHERE_SPHERE_H_
