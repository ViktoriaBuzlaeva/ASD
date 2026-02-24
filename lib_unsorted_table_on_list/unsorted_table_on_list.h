// Copyright 2026 Viktoria Buzlaeva

#ifndef LIB_UNSORTED_TABLE_ON_LIST_UNSORTED_TABLE_ON_LIST_H_
#define LIB_UNSORTED_TABLE_ON_LIST_UNSORTED_TABLE_ON_LIST_H_

#include <iomanip>
#include "../lib_table/table.h"
#include "../lib_list/list.h"

template <class TKey, class TValue>
class UnsortedTableOnList : public Table<TKey, TValue> {
    List<TPair<TKey, TValue>> _rows;

public:
    UnsortedTableOnList() = default;

    void insert(const TKey&, const TValue&) override;
    void erase(const TKey&) override;
    TValue& found(const TKey&) override;
    bool is_empty() const noexcept override;
    void print() const noexcept override;

    Node<TPair<TKey, TValue>>* find(const TKey& key);
};

template <class TKey, class TValue>
void UnsortedTableOnList<TKey, TValue>::insert(const TKey& key, const TValue& value) {
    Node<TPair<TKey, TValue>>* curr = find(key);
    if (curr != nullptr) {
        throw std::logic_error("Key already exists");
    }
    TPair<TKey, TValue> new_pair(key, value);
    _rows.push_back(new_pair);
}

template <class TKey, class TValue>
void UnsortedTableOnList<TKey, TValue>::erase(const TKey& key) {
    if (is_empty()) throw std::logic_error("Table is empty");
    Node<TPair<TKey, TValue>>* curr = find(key);
    if (curr != nullptr) {
        if (curr == _rows.head()) {
            _rows.pop_front();
        }
        else {
            _rows.erase(curr);
        }
        return;
    }
    throw std::out_of_range("Key doesn't exist");
}

template <class TKey, class TValue>
TValue& UnsortedTableOnList<TKey, TValue>::found(const TKey& key) {
    if (is_empty()) throw std::logic_error("Table is empty");
    Node<TPair<TKey, TValue>>* curr = find(key);
    if (curr != nullptr) {
        return curr->value.value;
    }
    throw std::out_of_range("Key doesn't exist");
}

template <class TKey, class TValue>
bool UnsortedTableOnList<TKey, TValue>::is_empty() const noexcept {
    return _rows.is_empty();
}

template <class TKey, class TValue>
void UnsortedTableOnList<TKey, TValue>::print() const noexcept {
    if (_rows.is_empty()) {
        std::cout << "Table is empty" << std::endl;
        return;
    }

    int key_length = 15;
    int value_length = 40;

    std::cout << "+-" << std::string(key_length, '-') << "+-"
        << std::string(value_length, '-') << "+" << std::endl;

    std::cout << "| " << std::left << std::setw(key_length) << "Key" << "| "
        << std::setw(value_length) << "Value" << "|" << std::endl;

    std::cout << "+-" << std::string(key_length, '-') << "+-"
        << std::string(value_length, '-') << "+" << std::endl;

    for (auto it = _rows.begin(); it != _rows.end(); it++) {
        std::cout << "| " << std::left << std::setw(key_length) << (*it).key << "| "
            << std::setw(value_length) << (*it).value << "|" << std::endl;
    }

    std::cout << "+-" << std::string(key_length, '-') << "+-"
        << std::string(value_length, '-') << "+" << std::endl;
}

template <class TKey, class TValue>
Node<TPair<TKey, TValue>>* UnsortedTableOnList<TKey, TValue>::find(const TKey& key) {
    Node<TPair<TKey, TValue>>* curr = _rows.head();
    while (curr != nullptr) {
        if (curr->value.key == key) {
            return curr;
        }
        curr = curr->next;
    }
    return nullptr;
}

#endif  // LIB_UNSORTED_TABLE_ON_LIST_UNSORTED_TABLE_ON_LIST_H_
