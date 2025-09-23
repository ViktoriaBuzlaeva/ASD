// Copyright 2025 Viktoria Buzlaeva

#ifndef GAMESTORE_MATH_VECTOR_MATH_VECTOR_H_
#define GAMESTORE_MATH_VECTOR_MATH_VECTOR_H_

#include "../lib_tvector/tvector.h"

template <class T>
class MathVector : public TVector<T> {

public:
	template <class T>
	friend std::istream& operator >> (std::istream&, const MathVector<T>&);
};

template <class T>
std::istream& operator >> (std::istream& in, const MathVector<T>& vector) {
	return in;
}

#endif  // GAMESTORE_MATH_VECTOR_MATH_VECTOR_H_
