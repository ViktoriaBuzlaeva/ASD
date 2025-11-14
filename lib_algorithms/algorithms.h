// Copyright 2025 Viktoria Buzlaeva

#ifndef LIB_ALGORITHMS_ALGORITHMS_H_
#define LIB_ALGORITHMS_ALGORITHMS_H_

#include "../lib_matrix/matrix.h"
#include "../lib_dsu/dsu.h"

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

int find_local_min_matrix(Matrix<int>, unsigned int seed = time(0));

int find_number_of_islands(Matrix<int>);

#endif  // LIB_ALGORITHMS_ALGORITHMS_H_
