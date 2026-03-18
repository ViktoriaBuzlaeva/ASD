// Copyright 2026 Viktoria Buzlaeva

#ifndef LIB_SORTED_TABLE_ON_BSTREE_SORTED_TABLE_ON_BSTREE_H_
#define LIB_SORTED_TABLE_ON_BSTREE_SORTED_TABLE_ON_BSTREE_H_

#include <iomanip>
#include "../lib_table/table.h"
#include "../lib_bstree/bstree.h"

template <class TKey, class TValue>
class SortedTableOnBSTree : public Table<TKey, TValue> {
    BSTree<TKey, TValue> _rows;

public:
    SortedTableOnBSTree() = default;

    void insert(const TKey&, const TValue&) override;
    void erase(const TKey&) override;
    TValue& found(const TKey&) override;
    bool is_empty() const noexcept override;
    void print() const noexcept override;
};

template <class TKey, class TValue>
void SortedTableOnBSTree<TKey, TValue>::insert(const TKey& key, const TValue& value) {
    if (_rows.find(key)) {
        throw std::logic_error("Key already exists");
    }
    _rows.insert(key, value);
}

template <class TKey, class TValue>
void SortedTableOnBSTree<TKey, TValue>::erase(const TKey& key) {
    if (!_rows.find(key)) {
        throw std::logic_error("Key doesn't exist");
    }
    _rows.erase(key);
}

template <class TKey, class TValue>
TValue& SortedTableOnBSTree<TKey, TValue>::found(const TKey& key) {
    if (is_empty()) throw std::logic_error("Table is empty");
    TValue* found = _rows.find(key);
    if (found == nullptr) {
        throw std::logic_error("Key doesn't exist");
    }
    return *found;
}

template <class TKey, class TValue>
bool SortedTableOnBSTree<TKey, TValue>::is_empty() const noexcept {
    return _rows.is_empty();
}

template <class TKey, class TValue>
void SortedTableOnBSTree<TKey, TValue>::print() const noexcept {
    if (is_empty()) {
        std::cout << "Table is empty" << std::endl;
        return;
    }
}

#endif  // LIB_SORTED_TABLE_ON_BSTREE_SORTED_TABLE_ON_BSTREE_H_
