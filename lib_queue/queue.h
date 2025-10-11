// Copyright 2025 Viktoria Buzlaeva

#ifndef LIB_QUEUE_QUEUE_H_
#define LIB_QUEUE_QUEUE_H_

template<class T>
class Queue {
	T* _data;
	int _size;

public:

	~Queue();

	void push(T);
	void pop();

	T tail() const;
	T head() const;

	inline bool is_empty() const noexcept;
	inline bool is_full() const noexcept;

	void clear() noexcept;
};

template<class T>
Queue<T>::~Queue() {
	delete[] _data;
}

template<class T>
void Queue<T>::push(T value) {
	if (is_full()) throw std::logic_error("Queue is full!");
}

template<class T>
void Queue<T>::pop() {
	if (is_empty()) throw std::logic_error("Queue is empty!");
}

template<class T>
T Queue<T>::tail() const {
	if (is_empty()) throw std::logic_error("Queue is empty!");
}

template<class T>
T Queue<T>::head() const {
	if (is_empty()) throw std::logic_error("Queue is empty!");
}

template<class T>
inline bool Queue<T>::is_empty() const noexcept {
}

template<class T>
inline bool Queue<T>::is_full() const noexcept {
}

template<class T>
void Queue<T>::clear() noexcept {
}

#endif  // LIB_QUEUE_QUEUE_H_
