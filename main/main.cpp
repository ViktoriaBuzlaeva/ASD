// Copyright 2024 Marina Usova

#define EASY_EXAMPLE
#ifdef EASY_EXAMPLE

#include <iostream>
#include <iomanip>
#include "../lib_easy_example/easy_example.h"
#include "../lib_point/point.h"
#include "../lib_circle/circle.h"

int find_type_of_crossing(const Circle& first, const Circle& second) {
	if ((first._cent).find_distance(second._cent) > first._rad) {  // не пересекаются
		return 1;
	}
	else if ((first._cent).find_distance(second._cent) < first._rad) { // пересекаются
		return 2;
	}
	else {  // касаются
		return 3;
	}
}

int main() {
  int a, b;
  float result;

  a = 1; b = 4;

  try {
      result = division(a, b);
      std::cout << a << " / " << b << " = "
          << std::setprecision(2) << result << std::endl;
  } catch (std::exception err) {
      std::cerr << err.what() << std::endl;
  }

  a = 1; b = 0;

  try {
      result = division(a, b);
      std::cout << a << " / " << b << " = "
          << std::setprecision(2) << result << std::endl;
  } catch (std::exception err) {
      std::cerr << err.what() << std::endl;
  }

  Point point1;
  Point point2(3, 4);
  Circle circle1;
  Circle circle2(point1, 5);

  float dis1 = point1.find_distance(point2);
  std::cout << dis1 << '\n';

  Circle circle3(point2, 1);

  std::cout << circle2.get_cent().get_x() << circle2.get_cent().get_y() << circle2.get_rad() << '\n';
  std::cout << circle3.get_cent().get_x() << circle3.get_cent().get_y() << circle3.get_rad() << '\n';
  int res = find_type_of_crossing(circle3, circle3);
  std::cout << res << '\n';

  return 0;
}

#endif  // EASY_EXAMPLE
