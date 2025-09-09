// Copyright 2025 Viktoria Buzlaeva

#ifndef LIB_POINT_POINT_H_
#define LIB_POINT_POINT_H_

class Point {
	float _x;
	float _y;

public:
	Point(float x = 0, float y = 0);
	Point(const Point&);

	float get_x();
	float get_y();

	float find_distance(const Point&) const;
};

#endif  // LIB_POINT_POINT_H_
