// Copyright 2026 Viktoria Buzlaeva

#ifndef LIB_SKIP_LIST_SKIP_LIST_H_
#define LIB_SKIP_LIST_SKIP_LIST_H_

#include <vector>
#include <sstream>
#include <string>
#include <iostream>
#include <limits>
#include"../lib_pair/pair.h"
#include"../lib_list/list.h"

template<class TKey, class TValue>
struct SNode {
    TPair<TKey, TValue> data;
    SNode<TKey, TValue>** next;
    size_t level;

    SNode(size_t level_) : data(), level(level_) {
        next = new SNode<TKey, TValue>*[level];
        for (size_t i = 0; i < level; i++)
            next[i] = nullptr;
    }

    SNode(const TPair<TKey, TValue>& data_, size_t level_)
        : data(data_), level(level_) {
        next = new SNode<TKey, TValue>*[level];
        for (int i = 0; i < level; i++) {
            next[i] = new SNode<TKey, TValue>(level);
        }
    }

    ~SNode() {
        delete[] next;
    }
};

template<class TKey, class TValue>
class SkipList {
    size_t _MAX_LVL;
    size_t _LVL;
    List<SNode<TKey, TValue>*> _heads;

public:
    SkipList(size_t MAX_LVL = SIZE_MAX);

    void insert(const TKey&, const TValue&);
    void print() const noexcept;

protected:
    size_t flip_coin() const noexcept;
    List<SNode<TKey, TValue>*> find_nearest(const TKey&) const noexcept;
};

template<class TKey, class TValue>
SkipList<TKey, TValue>::SkipList(size_t MAX_LVL) : _MAX_LVL(MAX_LVL), _heads() {
    _heads.push_back(nullptr);
    _LVL = 1;
    srand(time(0));
}

template<class TKey, class TValue>
void SkipList<TKey, TValue>::insert(const TKey& key, const TValue& value) {
    size_t new_level = flip_coin();
    if (new_level > _LVL) {
        for (size_t i = _LVL; i < new_level; i++) {
            _heads.push_back(nullptr);
        }
        _LVL = new_level;
    }

    List<SNode<TKey, TValue>*> prev_nodes = find_nearest(key);

    SNode<TKey, TValue>* prev_key = nullptr;
    if (!prev_nodes.is_empty()) {
        prev_key = prev_nodes.head()->value;
    }

    SNode<TKey, TValue>* next_key;
    if (prev_key == nullptr) {
        next_key = _heads.head()->value;
    }
    else {
        next_key = prev_key->next[0];
    }

    if (next_key != nullptr && next_key->data.key == key) {
        throw std::logic_error("Key already exists");
    }

    TPair<TKey, TValue> new_pair(key, value);
    SNode<TKey, TValue>* new_node = new SNode<TKey, TValue>(new_pair, new_level);

    auto it = prev_nodes.begin();
    auto head_it = _heads.begin();

    for (size_t i = 0; i < new_level; i++, it++, head_it++) {
        SNode<TKey, TValue>* prev = *it;
        if (prev == nullptr) {
            new_node->next[i] = *head_it;
            *head_it = new_node;
        }
        else {
            new_node->next[i] = prev->next[i];
            prev->next[i] = new_node;
        }
    }
}

template<class TKey, class TValue>
void SkipList<TKey, TValue>::print() const noexcept {
    for (size_t level = _LVL; level-- > 0; ) {
        std::cout << level + 1 << ": ";
        auto it = _heads.begin();
        for (size_t i = 0; i < level; i++) it++;
        SNode<TKey, TValue>* curr = *it;
        while (curr != nullptr) {
            std::cout << "[" << curr->data.key << ":" << curr->data.value << "]";
            if (curr->next[level] != nullptr) std::cout << "->";
            curr = curr->next[level];
        }
        std::cout << "->NULL" << std::endl;
    }
}

template<class TKey, class TValue>
size_t SkipList<TKey, TValue>::flip_coin() const noexcept {
    size_t lvl = 1;
    while (rand() % 100 < 50 && lvl < _MAX_LVL) {
        lvl++;
    }
    return lvl;
}

template<class TKey, class TValue>
List<SNode<TKey, TValue>*> SkipList<TKey, TValue>::find_nearest(const TKey& key) const noexcept {
    List<SNode<TKey, TValue>*> nodes;
    SNode<TKey, TValue>* nearest = nullptr;

    for (size_t l = _LVL; l-- > 0; ) {
        SNode<TKey, TValue>* curr;
        if (nearest == nullptr) {
            auto it = _heads.begin();
            for (size_t i = 0; i < l; i++) it++;
            curr = *it;
        }
        else {
            curr = nearest->next[l];
        }

        while (curr != nullptr && curr->data.key < key) {
            nearest = curr;
            curr = curr->next[l];
        }

        nodes.push_front(nearest);
    }

    return nodes;
}

#endif // LIB_SKIP_LIST_SKIP_LIST_H_
