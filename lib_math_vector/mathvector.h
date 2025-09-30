// Copyright 2025 Viktoria Buzlaeva

#ifndef GAMESTORE_MATH_VECTOR_MATH_VECTOR_H_
#define GAMESTORE_MATH_VECTOR_MATH_VECTOR_H_

#include "../lib_tvector/tvector.h"

template <class T>
class MathVector : private TVector<T> {
	size_t _start_index;

public:
	MathVector(size_t size = 0, size_t start_index = 0);
	MathVector(size_t, const T*, size_t start_index = 0);
	MathVector(size_t, std::initializer_list<T>, size_t start_index = 0);
	MathVector(std::initializer_list<T>, size_t start_index = 0);
	MathVector(const MathVector<T>&);

	inline const size_t size() const noexcept;

	MathVector<T> operator + (const MathVector<T>&) const;
	MathVector<T> operator - (const MathVector<T>&) const;
	T operator * (const MathVector<T>&) const;
	MathVector<T> operator * (const T&) const;

	MathVector<T>& operator += (const MathVector<T>&);
	MathVector<T>& operator -= (const MathVector<T>&);
	MathVector<T>& operator *= (const T& scalar);
	template <class T>
	friend MathVector<T> operator * (const T&, const MathVector<T>&);

	MathVector<T>& operator = (const MathVector<T>&) noexcept;

	bool operator == (const MathVector<T>&) const noexcept;
	bool operator != (const MathVector<T>&) const noexcept;

	const T& operator [] (size_t) const noexcept;
	T& operator [] (size_t) noexcept;

	template <class T>
	friend std::istream& operator >> (std::istream&, const MathVector<T>&);
	template <class T>
	friend std::ostream& operator << (std::ostream&, const MathVector<T>&);
};

template <class T>
MathVector<T>::MathVector(size_t size, size_t start_index) : TVector(size), _start_index(start_index) {}

template <class T>
MathVector<T>::MathVector(size_t size, const T* data, size_t start_index) : TVector(size, data), _start_index(start_index) {}

template <class T>
MathVector<T>::MathVector(size_t size, std::initializer_list<T> data, size_t start_index) : TVector(size, data), _start_index(start_index) {}

template <class T>
MathVector<T>::MathVector(std::initializer_list<T> data, size_t start_index) : TVector(data), _start_index(start_index) {}

template <class T>
MathVector<T>::MathVector(const MathVector<T>& other) : TVector(other) {
	_start_index = other._start_index;
}

template <class T>
inline const size_t MathVector<T>::size() const noexcept {
	return TVector::size();
}

template <class T>
MathVector<T> MathVector<T>::operator + (const MathVector<T>& other) const {
	if (size() != other.size()) throw std::logic_error("Vectors must be the same size");
	MathVector result(size());
	for (size_t i = 0; i < size(); i++)
		result[i] = (*this)[i] + other[i];
	return result;
}

template <class T>
MathVector<T> MathVector<T>::operator - (const MathVector<T>& other) const {
	if (size() != other.size()) throw std::logic_error("Vectors must be the same size");
	MathVector result(size());
	for (size_t i = 0; i < size(); i++)
		result[i] = (*this)[i] - other[i];
	return result;
}

template <class T>
T MathVector<T>::operator * (const MathVector<T>& other) const {
	if (size() != other.size()) throw std::logic_error("Vectors must be the same size");
	T result = 0;
	for (size_t i = 0; i < size(); i++)
		result += (*this)[i] * other[i];
	return result;
}

template <class T>
MathVector<T> MathVector<T>::operator * (const T& scalar) const {
	MathVector result(size());
	for (size_t i = 0; i < size(); i++)
		result[i] = (*this)[i] * scalar;
	return result;
}

template <class T>
MathVector<T> operator * (const T& scalar, const MathVector<T>& vec) {
	return vec * scalar;
}

template <class T>
MathVector<T>& MathVector<T>::operator += (const MathVector<T>& other) {
	if (size() != other.size()) throw std::logic_error("Vectors must be the same size");
	for (size_t i = 0; i < size(); i++)
		(*this)[i] += other[i];
	return *this;
}

template <class T>
MathVector<T>& MathVector<T>::operator -= (const MathVector<T>& other) {
	if (size() != other.size()) throw std::logic_error("Vectors must be the same size");
	for (size_t i = 0; i < size(); i++)
		(*this)[i] -= other[i];
	return *this;
}

template <class T>
MathVector<T>& MathVector<T>::operator *= (const T& scalar) {
	for (size_t i = 0; i < size(); i++)
		(*this)[i] *= scalar;
	return *this;
}

template <class T>
MathVector<T>& MathVector<T>::operator = (const MathVector<T>& other) noexcept {
	if (this != &other) {
		_start_index = other._start_index;
		TVector::operator = (other);
	}
	return *this;
}

template <class T>
bool MathVector<T>::operator == (const MathVector<T>& other) const noexcept {
	return TVector::operator == (other);
}

template <class T>
bool MathVector<T>::operator != (const MathVector<T>& other) const noexcept {
	return !(*this == other);
}

template <class T>
const T& MathVector<T>::operator[] (size_t pos) const noexcept {
	return TVector::operator [] (pos);
}

template <class T>
T& MathVector<T>::operator[] (size_t pos) noexcept {
	return TVector::operator [] (pos);
}

template <class T>
std::istream& operator >> (std::istream& in, const MathVector<T>& vector) {
	for (size_t i = 0; i < vector.size(); i++) {
		in >> vector[i];
	}
	return in;
}

template <class T>
std::ostream& operator << (std::ostream& out, const MathVector<T>& vector) {
	out << static_cast<const TVector<T>&>(vector);
	return out;
}

#endif  // GAMESTORE_MATH_VECTOR_MATH_VECTOR_H_
