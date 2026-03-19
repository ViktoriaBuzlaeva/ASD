// Copyright 2026 Viktoria Buzlaeva

#ifndef LIB_UNSORTED_TABLE_ON_TREE_UNSORTED_TABLE_ON_TREE_H_
#define LIB_UNSORTED_TABLE_ON_TREE_UNSORTED_TABLE_ON_TREE_H_

#include <iomanip>
#include "../lib_table/table.h"
#include "../lib_tree/tree.h"

template <class TKey, class TValue>
class UnsortedTableOnTree : public Table<TKey, TValue> {
    Tree<TKey, TValue> _rows;

public:
    UnsortedTableOnTree() = default;

    void insert(const TKey&, const TValue&) override;
    void erase(const TKey&) override;
    TValue& found(const TKey&) override;
    bool is_empty() const noexcept override;
    void print() const noexcept override;
};

template <class TKey, class TValue>
void UnsortedTableOnTree<TKey, TValue>::insert(const TKey& key, const TValue& value) {
    if (_rows.find(key)) {
        throw std::logic_error("Key already exists");
    }
    _rows.insert(key, value);
}

template <class TKey, class TValue>
void UnsortedTableOnTree<TKey, TValue>::erase(const TKey& key) {
    if (!_rows.find(key)) {
        throw std::logic_error("Key doesn't exist");
    }
    _rows.erase(key);
}

template <class TKey, class TValue>
TValue& UnsortedTableOnTree<TKey, TValue>::found(const TKey& key) {
    if (is_empty()) throw std::logic_error("Table is empty");
    TValue* found = _rows.find(key);
    if (found == nullptr) {
        throw std::logic_error("Key doesn't exist");
    }
    return *found;
}

template <class TKey, class TValue>
bool UnsortedTableOnTree<TKey, TValue>::is_empty() const noexcept {
    return _rows.is_empty();
}

template <class TKey, class TValue>
void UnsortedTableOnTree<TKey, TValue>::print() const noexcept {
    if (is_empty()) {
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

    LQueue<const TNode<TKey, TValue>*> q;
    const TNode<TKey, TValue>* curr = nullptr;
    q.push(_rows.root());
    while (!q.is_empty()) {
        curr = q.head();

        std::cout << "| " << std::left << std::setw(key_length) << curr->data.key << "| "
            << std::setw(value_length) << curr->data.value << "|" << std::endl;

        q.pop();
        if (curr->left) q.push(curr->left);
        if (curr->right) q.push(curr->right);
    }

    std::cout << "+-" << std::string(key_length, '-') << "+-"
        << std::string(value_length, '-') << "+" << std::endl;
}

#endif  // LIB_UNSORTED_TABLE_ON_TREE_UNSORTED_TABLE_ON_TREE_H_
