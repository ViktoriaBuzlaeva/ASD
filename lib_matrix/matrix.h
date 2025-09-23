// Copyright 2025 Viktoria Buzlaeva

#ifndef LIB_MATRIX_MATRIX_H_
#define LIB_MATRIX_MATRIX_H_

#include "../lib_math_vector/mathvector.h"

template <class T>
class Matrix : public MathVector<MathVector<T>> {

public:
	Matrix(int M = 0, int N = 0);

	Matrix<T>& operator = (const Matrix<T>&);
	Matrix<T>& operator + (const Matrix<T>&);
	Matrix<T>& operator - (const Matrix<T>&);
	Matrix<T>& operator * (const Matrix<T>&);
	Matrix<T>& operator * (const MathVector<T>&);
	Matrix<T>& operator * (const T&);

	bool operator == (const Matrix<T>&) const;
	bool operator != (const Matrix<T>&) const;

	template <class T>
	friend std::ostream& operator << (std::ostream&, const Matrix<T>&);
	template <class T>
	friend std::istream& operator >> (std::istream&, const Matrix<T>&);
};

template <class T>
Matrix<T>::Matrix(int M, int N) {}

template <class T>
Matrix<T>& Matrix<T>::operator = (const Matrix<T>& other) {
	return Matrix<T>();
}

template <class T>
Matrix<T>& Matrix<T>::operator + (const Matrix<T>& other) {
	return Matrix<T>();
}

template <class T>
Matrix<T>& Matrix<T>::operator - (const Matrix<T>& other) {
	return Matrix<T>();
}

template <class T>
Matrix<T>& Matrix<T>::operator * (const Matrix<T>& other) {
	return Matrix<T>();
}

template <class T>
Matrix<T>& Matrix<T>::operator * (const MathVector<T>& vector) {
	return Matrix<T>();
}

template <class T>
Matrix<T>& Matrix<T>::operator * (const T& scalar) {
	return Matrix<T>();
}

template <class T>
bool Matrix<T>::operator == (const Matrix<T>& other) const {
	return bool();
}

template <class T>
bool Matrix<T>::operator != (const Matrix<T>& other) const {
	return !(*this == other);
}

template <class T>
std::ostream& operator << (std::ostream& out, const Matrix<T>& matrix) {
	return out;
}

template <class T>
std::istream& operator >> (std::istream& in, const Matrix<T>& matrix) {
	return in;
}

#endif  // LIB_MATRIX_MATRIX_H_
