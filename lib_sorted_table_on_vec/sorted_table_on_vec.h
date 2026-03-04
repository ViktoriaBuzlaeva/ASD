// Copyright 2026 Viktoria Buzlaeva

#ifndef LIB_SORTED_TABLE_ON_VEC_SORTED_TABLE_ON_VEC_H_
#define LIB_SORTED_TABLE_ON_VEC_SORTED_TABLE_ON_VEC_H_

#include <iomanip>
#include "../lib_table/table.h"
#include "../lib_tvector/tvector.h"

template <class TKey, class TValue>
class SortedTableOnVec : public Table<TKey, TValue> {
    TVector<TPair<TKey, TValue>> _rows;

public:
    SortedTableOnVec() = default;

    const TVector<TPair<TKey, TValue>>& rows() const noexcept { return _rows; }

    void insert(const TKey&, const TValue&) override;
    void erase(const TKey&) override;
    TValue& found(const TKey&) override;
    bool is_empty() const noexcept override;
    void print() const noexcept override;

private:
    size_t find_index(const TKey&) const;
};

template <class TKey, class TValue>
void SortedTableOnVec<TKey, TValue>::insert(const TKey& key, const TValue& value) {
    size_t pos = find_index(key);
    if (_rows[pos].key == key) {
        throw std::logic_error("Key already exists");
    }
    TPair<TKey, TValue> new_pair(key, value);
    _rows.insert(pos, new_pair);
}

template <class TKey, class TValue>
void SortedTableOnVec<TKey, TValue>::erase(const TKey& key) {
    if (is_empty()) throw std::logic_error("Table is empty");
    size_t pos = find_index(key);
    if (_rows[pos].key != key) {
        throw std::out_of_range("Key doesn't exist");
    }
    _rows.erase(pos);
}

template <class TKey, class TValue>
TValue& SortedTableOnVec<TKey, TValue>::found(const TKey& key) {
    if (is_empty()) throw std::logic_error("Table is empty");
    size_t pos = find_index(key);
    if (_rows[pos].key != key) {
        throw std::out_of_range("Key doesn't exist");
    }
    return _rows[pos].value;
}

template <class TKey, class TValue>
bool SortedTableOnVec<TKey, TValue>::is_empty() const noexcept {
    return _rows.is_empty();
}

template <class TKey, class TValue>
void SortedTableOnVec<TKey, TValue>::print() const noexcept {
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

    for (size_t i = 0; i < _rows.size(); i++) {
        std::cout << "| " << std::left << std::setw(key_length) << _rows[i].key << "| "
            << std::setw(value_length) << _rows[i].value << "|" << std::endl;
    }

    std::cout << "+-" << std::string(key_length, '-') << "+-"
        << std::string(value_length, '-') << "+" << std::endl;
}

template <class TKey, class TValue>
size_t SortedTableOnVec<TKey, TValue>::find_index(const TKey& key) const {
    size_t left = 0, right = _rows.size();
    while (left < right) {
        size_t mid = left + (right - left) / 2;
        if (_rows[mid].key < key)
            left = mid + 1;
        else if (key < _rows[mid].key)
            right = mid;
        else
            return mid;
    }
    return left;
}

#endif  // LIB_SORTED_TABLE_ON_VEC_SORTED_TABLE_ON_VEC_H_
