// Copyright 2025 Viktoria Buzlaeva

#ifndef LIB_STACK_STACK_H_
#define LIB_STACK_STACK_H_

#include <stdexcept>

template<class T>
class Stack {
	T* _data;
	int _size;
	int _top;

public:
	Stack(int size = 15);
	Stack(const Stack<T>&);

	~Stack();

	int get_size() const;
	int get_top() const;

	void push(T);
	void pop();

	T top() const;

	inline bool is_empty() const noexcept;
	inline bool is_full() const noexcept;

	void clear() noexcept;
};

template<class T>
Stack<T>::Stack(int size) {
	if (size <= 0) throw std::logic_error("Size must be greater than zero!");
	_size = size;
	_top = -1;
	_data = new T[_size];
}

template<class T>
Stack<T>::Stack(const Stack<T>& other) {
	if (&other == NULL) throw std::logic_error ("Other stack doesn't exist!");
	_size = other._size;
	_top = other._top;
	_data = new T[_size];
	for (int i = 0; i <= _top; i++) {
		_data[i] = other._data[i];
	}
}

template<class T>
Stack<T>::~Stack() {
	delete[] _data;
}

template<class T>
int Stack<T>::get_size() const {
	return _size;
}

template<class T>
int Stack<T>::get_top() const {
	return _top;
}

template<class T>
void Stack<T>::push(T value) {
	if (is_full()) throw std::logic_error("Stack is full!");
	_data[++_top] = value;
}

template<class T>
void Stack<T>::pop() {
	if (is_empty()) throw std::logic_error("Stack is empty!");
	--_top;
}

template<class T>
T Stack<T>::top() const {
	if (is_empty()) throw std::logic_error("Stack is empty!");
	return _data[_top];
}

template<class T>
inline bool Stack<T>::is_empty() const noexcept {
	return _top == -1;
}

template<class T>
inline bool Stack<T>::is_full() const noexcept {
	return _top == _size - 1;
}

template<class T>
void Stack<T>::clear() noexcept {
	_top = -1;
}

#endif  // LIB_STACK_STACK_H_
