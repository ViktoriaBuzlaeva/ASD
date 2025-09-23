// Copyright 2025 Viktoria Buzlaeva

#ifndef LIB_TRIANGLE_MATRIX_TRIANGLE_MATRIX_H_
#define LIB_TRIANGLE_MATRIX_TRIANGLE_MATRIX_H_

#include "../lib_matrix/matrix.h"

template <class T>
class TriangleMatrix : public Matrix<T> {

public:
	TriangleMatrix(int M = 0, int N = 0);

	bool operator == (const TriangleMatrix<T>&) const;
	bool operator != (const TriangleMatrix<T>&) const;

	TriangleMatrix<T>& operator = (const TriangleMatrix<T>&);
	TriangleMatrix<T>& operator + (const TriangleMatrix<T>&);
	TriangleMatrix<T>& operator - (const TriangleMatrix<T>&);
	TriangleMatrix<T>& operator * (const TriangleMatrix<T>&);

	template <class T>
	friend std::ostream& operator << (std::ostream&, const TriangleMatrix<T>&);
	template <class T>
	friend std::istream& operator >> (std::istream&, const TriangleMatrix<T>&);
};

template <class T>
TriangleMatrix<T>::TriangleMatrix(int M, int N) {}

template <class T>
TriangleMatrix<T>& TriangleMatrix<T>::operator = (const TriangleMatrix<T>& other) {
	return TriangleMatrix<T>();
}

template <class T>
TriangleMatrix<T>& TriangleMatrix<T>::operator + (const TriangleMatrix<T>& other) {
	return TriangleMatrix<T>();
}

template <class T>
TriangleMatrix<T>& TriangleMatrix<T>::operator - (const TriangleMatrix<T>& other) {
	return TriangleMatrix<T>();
}

template <class T>
TriangleMatrix<T>& TriangleMatrix<T>::operator * (const TriangleMatrix<T>& other) {
	return TriangleMatrix<T>();
}

template <class T>
bool TriangleMatrix<T>::operator == (const TriangleMatrix<T>& other) const {
	return bool();
}

template <class T>
bool TriangleMatrix<T>::operator != (const TriangleMatrix<T>& other) const {
	return !(*this == other);
}

template <class T>
std::ostream& operator << (std::ostream& out, const TriangleMatrix<T>& matrix) {
	return out;
}

template <class T>
std::istream& operator >> (std::istream& in, const TriangleMatrix<T>& matrix) {
	return in;
}

#endif  // LIB_TRIANGLE_MATRIX_TRIANGLE_MATRIX_H_
