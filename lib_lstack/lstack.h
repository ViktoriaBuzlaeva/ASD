// Copyright 2025 Viktoria Buzlaeva

#ifndef LIB_LSTACK_LSTACK_H_
#define LIB_LSTACK_LSTACK_H_

#include "../lib_list/list.h"

template<class T>
class LStack {
    List<T> _data;
    int _size;

public:
    LStack();
    LStack(int);
    LStack(const LStack<T>&);

    void push(T);  // O(1)
    void pop();  // O(1)

    T top() const;

    inline bool is_empty() const noexcept;
    inline bool is_full() const noexcept;

    void clear() noexcept;  // O(n)
};

template<class T>
LStack<T>::LStack() {
    _size = -1;
    _data = List<T>();
}

template<class T>
LStack<T>::LStack(int size) {
    if (size <= 0) throw std::logic_error("Size must be greater than zero!");
    _size = size;
    _data = List<T>();
}

template<class T>
LStack<T>::LStack(const LStack<T>& other) {
    if (&other == NULL) throw std::logic_error("Other stack doesn't exist!");
    _size = other._size;
    _data = other._data;
}

template<class T>
void LStack<T>::push(T value) {
    if (is_full()) throw std::logic_error("Stack is full!");
    _data.push_front(value);
}

template<class T>
void LStack<T>::pop() {
    if (is_empty()) throw std::logic_error("Stack is empty!");
    _data.pop_front();
}

template<class T>
T LStack<T>::top() const {
    if (is_empty()) throw std::logic_error("Stack is empty!");
    return _data.head()->value;
}

template<class T>
inline bool LStack<T>::is_empty() const noexcept {
    return _data.is_empty();
}

template<class T>
inline bool LStack<T>::is_full() const noexcept {
    if (_size == -1) return false;
    return _size == _data.size();
}

template<class T>
void LStack<T>::clear() noexcept {
    while (!_data.is_empty()) {
        _data.pop_front();
    }
}

#endif  // LIB_LSTACK_LSTACK_H_
