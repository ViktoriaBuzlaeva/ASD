// Copyright 2025 Viktoria Buzlaeva

#ifndef LIB_TRIANGLE_MATRIX_TRIANGLE_MATRIX_H_
#define LIB_TRIANGLE_MATRIX_TRIANGLE_MATRIX_H_

#include "../lib_matrix/matrix.h"

template <class T>
class TriangleMatrix : public Matrix<T> {

public:
	TriangleMatrix(size_t size = 0);
	TriangleMatrix(const TriangleMatrix<T>&);
	TriangleMatrix(std::initializer_list<std::initializer_list<T>>);

	TriangleMatrix<T> operator + (const TriangleMatrix<T>&) const;
	TriangleMatrix<T> operator - (const TriangleMatrix<T>&) const;
	TriangleMatrix<T> operator * (const TriangleMatrix<T>&) const;
	MathVector<T> operator * (const MathVector<T>&) const;
	TriangleMatrix<T> operator * (const T) const;
	template <class T>
	friend TriangleMatrix<T> operator * (const T, const TriangleMatrix<T>&);

	TriangleMatrix<T>& operator += (const TriangleMatrix<T>&);
	TriangleMatrix<T>& operator -= (const TriangleMatrix<T>&);
	TriangleMatrix<T>& operator *= (const TriangleMatrix<T>&);
	TriangleMatrix<T>& operator *= (const T);

	TriangleMatrix<T>& operator = (const TriangleMatrix<T>&);

	bool operator == (const TriangleMatrix<T>&) const;
	bool operator != (const TriangleMatrix<T>&) const;

	template <class T>
	friend std::ostream& operator << (std::ostream&, const TriangleMatrix<T>&);
	template <class T>
	friend std::istream& operator >> (std::istream&, TriangleMatrix<T>&);
};

template <class T>
TriangleMatrix<T>::TriangleMatrix(size_t size) : Matrix<T>(size) {
	cols() = size;
	for (size_t i = 0; i < size; i++) {
		(*this)[i] = MathVector<T>(size - i, i);
	}
}

template <class T>
TriangleMatrix<T>::TriangleMatrix(const TriangleMatrix<T>& other) : Matrix<T>(other) {}

template <class T>
TriangleMatrix<T>::TriangleMatrix(std::initializer_list<std::initializer_list<T>> data) : Matrix<T>(data.size()) {
	cols() = data.size();
	auto it = data.begin();
	for (size_t i = 0; it != data.end(); i++) {
		(*this)[i] = MathVector<T>(*it, i);
		it++;
	}
}

template <class T>
TriangleMatrix<T> TriangleMatrix<T>::operator + (const TriangleMatrix<T>& other) const {
	if (size() != other.size()) throw std::logic_error("Matrices must be the same size");
	TriangleMatrix<T> result(size());
	for (size_t i = 0; i < size(); i++) {
		result[i] = (*this)[i] + other[i];
	}
	return result;
}

template <class T>
TriangleMatrix<T> TriangleMatrix<T>::operator - (const TriangleMatrix<T>& other) const {
	if (size() != other.size()) throw std::logic_error("Matrices must be the same size");
	TriangleMatrix<T> result(size());
	for (size_t i = 0; i < size(); i++) {
		result[i] = (*this)[i] - other[i];
	}
	return result;
}

template <class T>
TriangleMatrix<T> TriangleMatrix<T>::operator * (const TriangleMatrix<T>& other) const {
	if (size() != other.size()) throw std::logic_error("Matrices must be the same size");
	TriangleMatrix<T> result(size());
	for (size_t i = 0; i < size(); i++) {
		for (size_t j = i; j < size(); j++) {
			T sum = 0;
			for (size_t k = i; k <= j; k++) {
				sum += (*this)[i][k] * other[k][j];
			}
			result[i][j] = sum;
		}
	}
	return result;
}

template <class T>
MathVector<T> TriangleMatrix<T>::operator * (const MathVector<T>& vector) const {
	if (size() != vector.size()) throw std::logic_error("The size of matrix and vector isn't suitable for multiplication");
	MathVector<T> result(size());
	for (size_t i = 0; i < size(); i++) {
		T sum = 0;
		for (size_t j = i; j < size(); j++) {
			sum += (*this)[i][j] * vector[j];
		}
		result[i] = sum;
	}
	return result;
}

template <class T>
TriangleMatrix<T> TriangleMatrix<T>::operator * (const T scalar) const {
	TriangleMatrix<T> result(size());
	for (size_t i = 0; i < size(); i++) {
		result[i] = (*this)[i] * scalar;
	}
	return result;
}

template <class T>
TriangleMatrix<T> operator * (const T scalar, const TriangleMatrix<T>& matr) {
	return matr * scalar;
}

template <class T>
TriangleMatrix<T>& TriangleMatrix<T>::operator += (const TriangleMatrix<T>& other) {
	if (size() != other.size()) throw std::logic_error("Matrices must be the same size");
	for (size_t i = 0; i < size(); i++) {
		(*this)[i] += other[i];
	}
	return *this;
}

template <class T>
TriangleMatrix<T>& TriangleMatrix<T>::operator -= (const TriangleMatrix<T>& other) {
	if (size() != other.size()) throw std::logic_error("Matrices must be the same size");
	for (size_t i = 0; i < size(); i++) {
		(*this)[i] -= other[i];
	}
	return *this;
}

template <class T>
TriangleMatrix<T>& TriangleMatrix<T>::operator *= (const TriangleMatrix<T>& other) {
	*this = (*this) * other;
	return *this;
}

template <class T>
TriangleMatrix<T>& TriangleMatrix<T>::operator *= (const T scalar) {
	for (size_t i = 0; i < size(); i++) {
		(*this)[i] *= scalar;
	}
	return *this;
}

template <class T>
TriangleMatrix<T>& TriangleMatrix<T>::operator = (const TriangleMatrix<T>& other) {
	if (this != &other) {
		Matrix<T>::operator = (other);
	}
	return *this;
}

template <class T>
bool TriangleMatrix<T>::operator == (const TriangleMatrix<T>& other) const {
	return Matrix<T>::operator == (other);
}

template <class T>
bool TriangleMatrix<T>::operator != (const TriangleMatrix<T>& other) const {
	return !(*this == other);
}

template <class T>
std::ostream& operator << (std::ostream& out, const TriangleMatrix<T>& matrix) {
	out << static_cast<const Matrix<T>&>(matrix);
	return out;
}

template <class T>
std::istream& operator >> (std::istream& in, TriangleMatrix<T>& matrix) {
	for (size_t i = 0; i < matrix.size(); i++) {
		for (size_t j = i; j < matrix.size(); j++) {
			in >> matrix[i][j];
		}
	}
	return in;
}

#endif  // LIB_TRIANGLE_MATRIX_TRIANGLE_MATRIX_H_
