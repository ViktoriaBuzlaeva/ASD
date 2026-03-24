// Copyright 2026 Viktoria Buzlaeva

#ifndef LIB_HEAP_HEAP_H_
#define LIB_HEAP_HEAP_H_

#include "../lib_tvector/tvector.h"

template <class T>
class Heap {
    TVector<T> _data;

public:
    Heap();

    const T root() const {
        if (_data.is_empty()) throw std::logic_error
            ("Heap is empty!");
        return _data[0];
    }

    void insert(const T&) noexcept;
    void erase();
};

template <class T>
Heap<T>::Heap() : _data() {}

template <class T>
void Heap<T>::insert(const T& value) noexcept {
    _data.push_back(value);

    int i = _data.size() - 1;
    int parent = (i - 1) / 2;

    while (parent >= 0 && _data[i] < _data[parent]) {
        int temp = _data[i];
        _data[i] = _data[parent];
        _data[parent] = temp;

        i = parent;
        parent = (i - 1) / 2;
    }
}

template <class T>
void Heap<T>::erase() {
    if (_data.is_empty()) throw std::logic_error
        ("Heap is empty!");
    _data[0] = _data[_data.size() - 1];
    _data.pop_back();

    int i = 0;
    int min = 0;
    int left_child, right_child;
    while (1) {
        left_child = 2 * i + 1;
        right_child = 2 * i + 2;

        if (left_child < _data.size() && _data[left_child] < _data[min]) {
            min = left_child;
        }

        if (right_child < _data.size() && _data[right_child] < _data[min]) {
            min = right_child;
        }

        if (min == i) break;

        int temp = _data[i];
        _data[i] = _data[min];
        _data[min] = temp;

        i = min;
    }
}

#endif  // LIB_HEAP_HEAP_H_
