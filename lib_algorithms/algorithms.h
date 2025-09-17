// Copyright 2025 Viktoria Buzlaeva

#ifndef LIB_ALGORITHMS_ALGORITHMS_H_
#define LIB_ALGORITHMS_ALGORITHMS_H_

enum TypeOfCrossing { Intersect, NotIntersect, Touch, Coincide };

template <class T>
TypeOfCrossing find_type_of_crossing(const T& first, const T& second) {
    if (first == second) {
        return Coincide;
    }
    else if (first.cent().find_distance(second.cent()) > (first.rad() + second.rad())) {
        return NotIntersect;
    }
    else if (first.cent().find_distance(second.cent()) < (first.rad() + second.rad())) {
        return Intersect;
    }
    else {
        return Touch;
    }
}

#endif  // LIB_ALGORITHMS_ALGORITHMS_H_
