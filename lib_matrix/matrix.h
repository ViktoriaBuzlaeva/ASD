// Copyright 2025 Viktoria Buzlaeva

#ifndef LIB_MATRIX_MATRIX_H_
#define LIB_MATRIX_MATRIX_H_

#include "../lib_math_vector/mathvector.h"

template <class T>
class Matrix : public MathVector<MathVector<T>> {
	size_t _rows;
	size_t _cols;

public:
	Matrix();
	Matrix(int, int);
	Matrix(const Matrix<T>&);
	Matrix(const MathVector<MathVector<T>>&);
	Matrix(std::initializer_list<std::initializer_list<T>>);

	inline const size_t rows() const noexcept;
	inline const size_t cols() const noexcept;

	inline size_t rows() noexcept;
	inline size_t cols() noexcept;

	Matrix<T> transpose() const;

	Matrix<T> operator + (const Matrix<T>&) const;
	Matrix<T> operator - (const Matrix<T>&) const;
	Matrix<T> operator * (const Matrix<T>&) const;
	MathVector<T> operator * (const MathVector<T>&) const;
	Matrix<T> operator * (const T) const;
	template <class T>
	friend Matrix<T> operator * (const T, const Matrix<T>&);

	Matrix<T>& operator += (const Matrix<T>&);
	Matrix<T>& operator -= (const Matrix<T>&);
	Matrix<T>& operator *= (const Matrix<T>&);
	Matrix<T>& operator *= (const T);

	Matrix<T>& operator = (const Matrix<T>&);

	bool operator == (const Matrix<T>&) const;
	bool operator != (const Matrix<T>&) const;

	template <class T>
	friend std::istream& operator >> (std::istream&, Matrix<T>&);
	template <class T>
	friend std::ostream& operator << (std::ostream&, const Matrix<T>&);
};

template <class T>
Matrix<T>::Matrix() : MathVector<MathVector<T>>(), _rows(0), _cols(0) {}

template <class T>
Matrix<T>::Matrix(int rows, int cols) {
	if (rows < 0 || cols < 0) throw std::logic_error ("Error in init constructor: incorrect input!");
	(*this) = MathVector<MathVector<T>>(rows);
	_rows = rows;
	_cols = cols;
	for (size_t i = 0; i < _rows; i++) {
		(*this)[i] = MathVector<T>(_cols);
	}
}

template <class T>
Matrix<T>::Matrix(const Matrix<T>& other) : MathVector<MathVector<T>>(other), _rows(other._rows), _cols(other._cols) {}

template <class T>
Matrix<T>::Matrix(const MathVector<MathVector<T>>& other) : MathVector<MathVector<T>>(other) {
	_rows = other.size();
	if (_rows > 0) {
		_cols = other[0].size();
	}
	else {
		_cols = 0;
	}
}

template <class T>
Matrix<T>::Matrix(std::initializer_list<std::initializer_list<T>> data) : MathVector<MathVector<T>>(data.size()) {
	_rows = data.size();
	if (_rows > 0) {
		_cols = data.begin()->size();
	}
	else {
		_cols = 0;
	}

	auto it = data.begin();
	for (size_t i = 0; it != data.end(); i++) {
		(*this)[i] = MathVector<T>(*it);
		it++;
	}
}

template <class T>
inline const size_t Matrix<T>::rows() const noexcept {
	return _rows;
}

template <class T>
inline const size_t Matrix<T>::cols() const noexcept {
	return _cols;
}

template <class T>
inline size_t Matrix<T>::rows() noexcept {
	return _rows;
}

template <class T>
inline size_t Matrix<T>::cols() noexcept {
	return _cols;
}

template <class T>
Matrix<T> Matrix<T>::transpose() const {
	Matrix<T> result(_cols, _rows);
	for (size_t i = 0; i < _rows; i++) {
		for (size_t j = 0; j < _cols; j++) {
			result[j][i] = (*this)[i][j];
		}
	}
	return result;
}

template <class T>
Matrix<T> Matrix<T>::operator + (const Matrix<T>& other) const {
	if (_rows != other._rows || _cols != other._cols) throw std::logic_error("Matrices must be the same size");
	Matrix<T> result(_rows, _cols);
	for (size_t i = 0; i < _rows; i++) {
		result[i] = (*this)[i] + other[i];
	}
	return result;
}

template <class T>
Matrix<T> Matrix<T>::operator - (const Matrix<T>& other) const {
	if (_rows != other._rows || _cols != other._cols) throw std::logic_error("Matrices must be the same size");
	Matrix<T> result(_rows, _cols);
	for (size_t i = 0; i < _rows; i++) {
		result[i] = (*this)[i] - other[i];
	}
	return result;
}

template <class T>
Matrix<T> Matrix<T>::operator * (const Matrix<T>& other) const {
	if (_cols != other._rows) throw std::logic_error("The size of matrices isn't suitable for multiplication");
	Matrix<T> result(_rows, other._cols);
	Matrix<T> other_t = other.transpose();
	for (size_t i = 0; i < _rows; i++) {
		for (size_t j = 0; j < other._cols; j++) {
			result[i][j] = (*this)[i] * other_t[j];
		}
	}
	return result;
}

template <class T>
MathVector<T> Matrix<T>::operator * (const MathVector<T>& vector) const {
	if (_cols != vector.size()) throw std::logic_error("The size of matrix and vector isn't suitable for multiplication");
	MathVector<T> result(_rows);
	for (size_t i = 0; i < _rows; i++) {
		result[i] = (*this)[i] * vector;
	}
	return result;
}

template <class T>
Matrix<T> Matrix<T>::operator * (const T scalar) const {
	Matrix<T> result(_rows, _cols);
	for (size_t i = 0; i < _rows; i++) {
		result[i] = (*this)[i] * scalar;
	}
	return result;
}

template <class T>
Matrix<T> operator * (const T scalar, const Matrix<T>& matr) {
	return matr * scalar;
}

template <class T>
Matrix<T>& Matrix<T>::operator += (const Matrix<T>& other) {
	if (_rows != other._rows || _cols != other._cols) throw std::logic_error("Matrices must be the same size");
	for (size_t i = 0; i < _rows; i++) {
		(*this)[i] += other[i];
	}
	return *this;
}

template <class T>
Matrix<T>& Matrix<T>::operator -= (const Matrix<T>& other) {
	if (_rows != other._rows || _cols != other._cols) throw std::logic_error("Matrices must be the same size");
	for (size_t i = 0; i < _rows; i++) {
		(*this)[i] -= other[i];
	}
	return *this;
}

template <class T>
Matrix<T>& Matrix<T>::operator *= (const Matrix<T>& other) {
	if (_cols != other._rows) throw std::logic_error("The size of matrices isn't suitable for multiplication");
	Matrix<T> result(_rows, other._cols);
	Matrix<T> other_t = other.transpose();
	for (size_t i = 0; i < _rows; i++) {
		for (size_t j = 0; j < other._cols; j++) {
			result[i][j] = (*this)[i] * other_t[j];
		}
	}
	*this = result;
	return *this;
}

template <class T>
Matrix<T>& Matrix<T>::operator *= (const T scalar) {
	for (size_t i = 0; i < _rows; i++) {
		(*this)[i] *= scalar;
	}
	return *this;
}

template <class T>
Matrix<T>& Matrix<T>::operator = (const Matrix<T>& other) {
	if (this != &other) {
		_rows = other._rows;
		_cols = other._cols;
		MathVector<MathVector<T>>::operator = (other);
	}
	return *this;
}

template <class T>
bool Matrix<T>::operator == (const Matrix<T>& other) const {
	if (_rows != other._rows || _cols != other._cols) return false;
	for (size_t i = 0; i < _rows; i++) {
		if ((*this)[i] != other[i]) return false;
	}
	return true;
}

template <class T>
bool Matrix<T>::operator != (const Matrix<T>& other) const {
	return !(*this == other);
}

template <class T>
std::ostream& operator << (std::ostream& out, const Matrix<T>& matrix) {
	out << "[";
	for (size_t i = 0; i < matrix._rows; i++) {
		out << " " << matrix[i];
		if (i < matrix._rows - 1) out << ", \n";
		out << " ";
	}
	out << "]";
	return out;
}

template <class T>
std::istream& operator >> (std::istream& in, const Matrix<T>& matrix) {
	return in;
}

#endif  // LIB_MATRIX_MATRIX_H_
