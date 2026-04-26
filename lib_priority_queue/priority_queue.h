// Copyright 2025 Viktoria Buzlaeva

#ifndef LIB_PRIORITY_QUEUE_PRIORITY_QUEUE_H_
#define LIB_PRIORITY_QUEUE_PRIORITY_QUEUE_H_

#include "../lib_heap/heap.h"

template <class TVal>
struct PriorityPair {
    int key;
    TVal value;
    int order;

    PriorityPair() = default;
    PriorityPair(const int& k, const TVal& v, const int& or) : key(k), value(v), order(or) {}

    bool operator == (const PriorityPair<TVal>& other) const {
        return key == other.key;
    }

    bool operator > (const PriorityPair<TVal>& other) const {
        if (key == other.key) {
            return order > other.order;
        }
        return key > other.key;
    }

    bool operator < (const PriorityPair<TVal>& other) const {
        if (key == other.key) {
            return order < other.order;
        }
        return key < other.key;
    }

    friend std::ostream& operator << (std::ostream& out, const PriorityPair<TVal>& pair) {
        out << pair.key << ":" << pair.value;
        return out;
    }
};

template<class T>
class PriorityQueue {
    Heap<T> _data;

public:
    PriorityQueue();

    void push(const T&);
    void pop();

    const T& head() const {
        return _data.root();
    }

    bool is_empty() const noexcept {
        return _data.is_empty();
    }
};

template<class T>
PriorityQueue<T>::PriorityQueue() : _data() {}

template<class T>
void PriorityQueue<T>::push(const T& value) {
    _data.insert(value);
}

template<class T>
void PriorityQueue<T>::pop() {
    _data.erase();
}

#endif  // LIB_PRIORITY_QUEUE_PRIORITY_QUEUE_H_
