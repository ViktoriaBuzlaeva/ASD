// Copyright 2025 Viktoria Buzlaeva

#ifndef LIB_QUEUE_QUEUE_H_
#define LIB_QUEUE_QUEUE_H_

template<class T>
class Queue {
	T* _data;
	int _size;
	int _count;
	int _head;

public:
	Queue(int size = 15);
	Queue(const Queue<T>&);

	~Queue();

	int get_size() const;
	int get_count() const;
	int get_head() const;

	void push(T);
	void pop();

	T head() const;
	T tail() const;

	inline bool is_empty() const noexcept;
	inline bool is_full() const noexcept;

	void clear() noexcept;
};

template<class T>
Queue<T>::Queue(int size) {
	if (size <= 0) throw std::logic_error("Size must be greater than zero!");
	_size = size;
	_head = 0;
	_count = 0;
	_data = new T[_size];
}

template<class T>
Queue<T>::Queue(const Queue<T>& other) {
	if (&other == NULL) throw std::logic_error("Other queue doesn't exist!");
	_size = other._size;
	_count = other._count;
	_head = other._head;
	_data = new T[_size];
	for (int i = 0; i <= _head; i++) {
		_data[i] = other._data[i];
	}
}

template<class T>
Queue<T>::~Queue() {
	delete[] _data;
}

template<class T>
int Queue<T>::get_size() const {
	return _size;
}

template<class T>
int Queue<T>::get_count() const {
	return _count;
}

template<class T>
int Queue<T>::get_head() const {
	return _head;
}

template<class T>
void Queue<T>::push(T value) {
	if (is_full()) throw std::logic_error("Queue is full!");
	_data[(_head + _count) % _size] = value;
	_count++;
}

template<class T>
void Queue<T>::pop() {
	if (is_empty()) throw std::logic_error("Queue is empty!");
	_head = (_head + 1) % _size;
	_count--;
}

template<class T>
T Queue<T>::head() const {
	if (is_empty()) throw std::logic_error("Queue is empty!");
	return _data[_head];
}

template<class T>
T Queue<T>::tail() const {
	if (is_empty()) throw std::logic_error("Queue is empty!");
	return _data[(_head + _count) % _size - 1];
}

template<class T>
inline bool Queue<T>::is_empty() const noexcept {
	return _count == 0;
}

template<class T>
inline bool Queue<T>::is_full() const noexcept {
	return _count == _size;
}

template<class T>
void Queue<T>::clear() noexcept {
	_head = 0;
	_count = 0;
}

#endif  // LIB_QUEUE_QUEUE_H_
