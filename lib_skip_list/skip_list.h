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

    SNode(const TPair<TKey, TValue>& data_, size_t level_)
        : data(data_), level(level_) {
        next = new SNode<TKey, TValue>*[level];
        for (int i = 0; i < level; i++) {
            next[i] = nullptr;
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
    ~SkipList();

    void insert(const TKey&, const TValue&);
    void print() const noexcept;

protected:
    size_t flip_coin() const noexcept;
    List<SNode<TKey, TValue>*> find_nearest(const TKey&) const;
};

template<class TKey, class TValue>
SkipList<TKey, TValue>::SkipList(size_t MAX_LVL) : _MAX_LVL(MAX_LVL), _heads() {
    _heads.push_back(nullptr);
    _LVL = 1;
    srand(time(0));
}

template<class TKey, class TValue>
SkipList<TKey, TValue>::~SkipList() {
    if (!_heads.is_empty()) {
        SNode<TKey, TValue>* current = _heads.head()->value;
        while (current != nullptr) {
            SNode<TKey, TValue>* next = current->next[0];
            delete current;
            current = next;
        }
    }
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

    List<SNode<TKey, TValue>*> prev_nodes = find_nearest(key); // Список ближайших узлов c 0 до LVL-1

    TPair<TKey, TValue> new_pair(key, value);
    SNode<TKey, TValue>* new_node = new SNode<TKey, TValue>(new_pair, new_level);

    auto it = prev_nodes.begin();
    auto head_it = _heads.begin();

    for (size_t i = 0; i < new_level; i++, it++, head_it++) {
        SNode<TKey, TValue>* prev = *it;
        if (prev == nullptr) { // Предыдущего узла нет
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
    SNode<TKey, TValue>* zero_level = _heads.head()->value;

    for (size_t level = _LVL; level-- > 0; ) {
        std::cout << level << ": ";

        auto head_it = _heads.begin();
        for (size_t i = 0; i < level; i++) head_it++;
        SNode<TKey, TValue>* curr_level_node = *head_it;

        SNode<TKey, TValue>* zero_node = zero_level;
        while (zero_node != nullptr) {
            std::ostringstream out;
            out << "[" << zero_node->data.key << ":" << zero_node->data.value << "]";
            std::string node_str = out.str();

            if (curr_level_node != nullptr && curr_level_node->data.key == zero_node->data.key) {
                std::cout << "->" << node_str;
                curr_level_node = curr_level_node->next[level];
            }
            else {
                std::cout << std::string(node_str.size() + 2, '-');
            }

            zero_node = zero_node->next[0];
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
List<SNode<TKey, TValue>*> SkipList<TKey, TValue>::find_nearest(const TKey& key) const {
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

        if (curr != nullptr && curr->data.key == key) {
            throw std::logic_error("Key already exists");
        }
    }

    return nodes;
}

#endif // LIB_SKIP_LIST_SKIP_LIST_H_
