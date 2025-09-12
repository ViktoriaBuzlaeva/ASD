// Copyright 2025 Viktoria Buzlaeva

#ifndef LIB_POINT_POINT_H_
#define LIB_POINT_POINT_H_

class Point {
protected:
	float _x;
	float _y;

public:
	Point(float x = 0, float y = 0);
	Point(const Point&);

	float x();
	float y();

	const float x() const;
	const float y() const;

	bool operator == (const Point&) const;
	bool operator != (const Point&) const;

	float find_distance(const Point&) const;
};

#endif  // LIB_POINT_POINT_H_
