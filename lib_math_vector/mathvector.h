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
	inline const T* data() const noexcept;

	inline T* data() noexcept;

	inline const T& at(size_t) const;
	inline T& at(size_t);

	MathVector<T> operator + (const MathVector<T>&) const;
	MathVector<T> operator - (const MathVector<T>&) const;
	T operator * (const MathVector<T>&) const;
	MathVector<T> operator * (const T) const;
	template <class T>
	friend MathVector<T> operator * (const T, const MathVector<T>&);

	MathVector<T>& operator += (const MathVector<T>&);
	MathVector<T>& operator -= (const MathVector<T>&);
	MathVector<T>& operator *= (const T scalar);

	MathVector<T>& operator = (const MathVector<T>&) noexcept;

	bool operator == (const MathVector<T>&) const noexcept;
	bool operator != (const MathVector<T>&) const noexcept;

	const T& operator [] (size_t) const noexcept;
	T& operator [] (size_t) noexcept;

	template <class T>
	friend std::istream& operator >> (std::istream&, MathVector<T>&);
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
inline const T* MathVector<T>::data() const noexcept {
	return TVector::data();
}

template <class T>
inline T* MathVector<T>::data() noexcept {
	return TVector::data();
}

template <class T>
inline const T& MathVector<T>::at(size_t pos) const {
	if (pos >= _start_index + size()) throw std::logic_error ("Error in at method: position out of range!");
	if (pos < _start_index) {
		T default = T();
		return default;
	}
	return TVector::operator [] (pos - _start_index);
}

template <class T>
inline T& MathVector<T>::at(size_t pos) {
	if (pos >= _start_index + size()) throw std::logic_error("Error in at method: position out of range!");
	if (pos < _start_index) {
		T default = T();
		return default;
	}
	return TVector::operator [] (pos - _start_index);
}

template <class T>
MathVector<T> MathVector<T>::operator + (const MathVector<T>& other) const {
	if (size() + _start_index != other.size() + other._start_index) throw std::logic_error("Vectors must be the same size");
	MathVector result(*this);
	result += other;
	return result;
}

template <class T>
MathVector<T> MathVector<T>::operator - (const MathVector<T>& other) const {
	if (size() + _start_index != other.size() + other._start_index) throw std::logic_error("Vectors must be the same size");
	MathVector result(*this);
	result -= other;
	return result;
}

template <class T>
T MathVector<T>::operator * (const MathVector<T>& other) const {
	if (size() + _start_index != other.size() + other._start_index) throw std::logic_error("Vectors must be the same size");
	T result = 0;
	size_t max_index = std::max(_start_index, other._start_index);
	for (size_t i = max_index; i < size() + _start_index; i++)
		result += (*this)[i] * other[i];
	return result;
}

template <class T>
MathVector<T> MathVector<T>::operator * (const T scalar) const {
	MathVector result(*this);
	result *= scalar;
	return result;
}

template <class T>
MathVector<T> operator * (const T scalar, const MathVector<T>& vec) {
	return vec * scalar;
}

template <class T>
MathVector<T>& MathVector<T>::operator += (const MathVector<T>& other) {
	if (size() + _start_index != other.size() + other._start_index) throw std::logic_error("Vectors must be the same size");
	size_t min_index = std::min(_start_index, other._start_index);
	size_t max_size = std::max(size(), other.size());
	MathVector<T> result(max_size, min_index);
	for (size_t i = min_index; i < size() + _start_index; i++) {
		result[i] = (*this)[i] + other[i];
	}
	*this = result;
	return *this;
}

template <class T>
MathVector<T>& MathVector<T>::operator -= (const MathVector<T>& other) {
	if (size() + _start_index != other.size() + other._start_index) throw std::logic_error("Vectors must be the same size");
	size_t min_index = std::min(_start_index, other._start_index);
	size_t max_size = std::max(size(), other.size());
	MathVector<T> result(max_size, min_index);
	for (size_t i = min_index; i < size() + _start_index; i++) {
		result[i] = (*this)[i] - other[i];
	}
	*this = result;
	return *this;
}

template <class T>
MathVector<T>& MathVector<T>::operator *= (const T scalar) {
	for (size_t i = _start_index; i < size() + _start_index; i++)
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
	T default = T();
	if (pos < _start_index || pos >= _start_index + size()) {
		return default;
	}
	return TVector::operator [] (pos - _start_index);
}

template <class T>
T& MathVector<T>::operator[] (size_t pos) noexcept {
	T default = T();
	if (pos < _start_index || pos >= _start_index + size()) {
		return default;
	}
	return TVector::operator [] (pos - _start_index);
}

template <class T>
std::istream& operator >> (std::istream& in, MathVector<T>& vector) {
	for (size_t i = 0; i < vector.size(); i++) {
		in >> vector[i];
	}
	return in;
}

template <class T>
std::ostream& operator << (std::ostream& out, const MathVector<T>& vector) {
	if (vector.data() == nullptr) {
		return out;
	}
	out << "{ ";
	for (size_t i = 0; i < vector.size() + vector._start_index - 1; i++) {
		out << vector[i] << ", ";
	}
	out << vector[vector.size() + vector._start_index - 1] << " }";
	return out;
}

#endif  // GAMESTORE_MATH_VECTOR_MATH_VECTOR_H_
