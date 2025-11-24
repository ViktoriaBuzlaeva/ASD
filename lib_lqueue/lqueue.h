// Copyright 2025 Viktoria Buzlaeva

#ifndef LIB_LQUEUE_LQUEUE_H_
#define LIB_LQUEUE_LQUEUE_H_

#include "../lib_list/list.h"

template<class T>
class LQueue {
    List<T> _data;
    int _size;

public:
    LQueue();
    LQueue(int);
    LQueue(const LQueue<T>&);

    void push(T);  // O(n)
    void pop();  // O(1)

    T head() const;
    T tail() const;

    inline bool is_empty() const noexcept;
    inline bool is_full() const noexcept;

    void clear() noexcept;  // 0(n)
};

template<class T>
LQueue<T>::LQueue() {
    _size = -1;
    _data = List<T>();
}

template<class T>
LQueue<T>::LQueue(int size) {
    if (size <= 0) throw std::logic_error("Size must be greater than zero!");
    _size = size;
    _data = List<T>();
}

template<class T>
LQueue<T>::LQueue(const LQueue<T>& other) {
    if (&other == NULL) throw std::logic_error("Other queue doesn't exist!");
    _size = other._size;
    _data = other._data;
}

template<class T>
void LQueue<T>::push(T value) {
    if (is_full()) throw std::logic_error("Queue is full!");
    _data.push_back(value);
}

template<class T>
void LQueue<T>::pop() {
    if (is_empty()) throw std::logic_error("Queue is empty!");
    _data.pop_front();
}

template<class T>
T LQueue<T>::head() const {
    if (is_empty()) throw std::logic_error("Queue is empty!");
    return _data.head()->value;
}

template<class T>
T LQueue<T>::tail() const {
    if (is_empty()) throw std::logic_error("Queue is empty!");
    return _data.tail()->value;
}

template<class T>
inline bool LQueue<T>::is_empty() const noexcept {
    return _data.is_empty();
}

template<class T>
inline bool LQueue<T>::is_full() const noexcept {
    if (_size == -1) return false;
    return _size == _data.get_count();
}

template<class T>
void LQueue<T>::clear() noexcept {
    while (!_data.is_empty()) {
        _data.pop_front();
    }
}

#endif  // LIB_LQUEUE_LQUEUE_H_
