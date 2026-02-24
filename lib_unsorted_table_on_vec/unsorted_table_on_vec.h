// Copyright 2026 Viktoria Buzlaeva

#ifndef LIB_UNSORTED_TABLE_M_H_
#define LIB_UNSORTED_TABLE_M_H_

#include <iomanip>
#include "../lib_table/table.h"
#include "../lib_tvector/tvector.h"

template <class TKey, class TValue>
class UnsortedTableOnVec : public Table<TKey, TValue> {
    TVector<TPair<TKey, TValue>> _rows;

public:
    UnsortedTableOnVec() = default;

    void insert(const TKey&, const TValue&) override;
    void erase(const TKey&) override;
    TValue& found(const TKey&) override;
    bool is_empty() const noexcept override;
    void print() const noexcept override;
};

template <class TKey, class TValue>
void UnsortedTableOnVec<TKey, TValue>::insert(const TKey& key, const TValue& value) {
    TPair<TKey, TValue> new_pair(key, value);
    if (find_first(_rows, new_pair) != -1) {
        throw std::logic_error("Key already exists");
    }
    _rows.push_back(new_pair);
}

template <class TKey, class TValue>
void UnsortedTableOnVec<TKey, TValue>::erase(const TKey& key) {
    if (is_empty()) throw std::logic_error("Table is empty");
    TPair<TKey, TValue> new_pair(key, TValue());
    int found = find_first(_rows, new_pair);
    if (found == -1) {
        throw std::logic_error("Key doesn't exist");
    }
    _rows.erase(found);
}

template <class TKey, class TValue>
TValue& UnsortedTableOnVec<TKey, TValue>::found(const TKey& key) {
    if (is_empty()) throw std::logic_error("Table is empty");
    TPair<TKey, TValue> new_pair(key, TValue());
    int found = find_first(_rows, new_pair);
    if (found == -1) {
        throw std::logic_error("Key doesn't exist");
    }
    return _rows.at(found).value;
}

template <class TKey, class TValue>
bool UnsortedTableOnVec<TKey, TValue>::is_empty() const noexcept {
    return _rows.is_empty();
}

template <class TKey, class TValue>
void UnsortedTableOnVec<TKey, TValue>::print() const noexcept {
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

#endif  // LIB_UNSORTED_TABLE_M_H_
