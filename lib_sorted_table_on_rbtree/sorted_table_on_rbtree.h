// Copyright 2026 Viktoria Buzlaeva

#ifndef LIB_SORTED_TABLE_ON_RBTREE_SORTED_TABLE_ON_RBTREE_H_
#define LIB_SORTED_TABLE_ON_RBTREE_SORTED_TABLE_ON_RBTREE_H_

#define KEY_LENGTH 15
#define VALUE_LENGTH 40

#include <iomanip>
#include "../lib_table/table.h"
#include "../lib_rbtree/rbtree.h"

template <class TKey, class TValue>
class SortedTableOnRBTree : public Table<TKey, TValue> {
    RBTree<TKey, TValue> _rows;

public:
    SortedTableOnRBTree() = default;

    const RBTree<TKey, TValue>& rows() const noexcept { return _rows; }

    void insert(const TKey&, const TValue&) override;
    void erase(const TKey&) override {}
    TValue& found(const TKey&) override;
    bool is_empty() const noexcept override;
    void print() const noexcept override;

private:
    void print_rec(const RBTNode<TKey, TValue>*) const noexcept;
};

template <class TKey, class TValue>
void SortedTableOnRBTree<TKey, TValue>::insert(const TKey& key, const TValue& value) {
    if (_rows.find(key)) {
        throw std::logic_error("Key already exists");
    }
    _rows.insert(key, value);
}

template <class TKey, class TValue>
TValue& SortedTableOnRBTree<TKey, TValue>::found(const TKey& key) {
    if (is_empty()) throw std::logic_error("Table is empty");
    TValue* found = _rows.find(key);
    if (found == nullptr) {
        throw std::logic_error("Key doesn't exist");
    }
    return *found;
}

template <class TKey, class TValue>
bool SortedTableOnRBTree<TKey, TValue>::is_empty() const noexcept {
    return _rows.is_empty();
}

template <class TKey, class TValue>
void SortedTableOnRBTree<TKey, TValue>::print() const noexcept {
    if (is_empty()) {
        std::cout << "Table is empty" << std::endl;
        return;
    }

    std::cout << "+-" << std::string(KEY_LENGTH, '-') << "+-"
        << std::string(VALUE_LENGTH, '-') << "+" << std::endl;

    std::cout << "| " << std::left << std::setw(KEY_LENGTH) << "Key" << "| "
        << std::setw(VALUE_LENGTH) << "Value" << "|" << std::endl;

    std::cout << "+-" << std::string(KEY_LENGTH, '-') << "+-"
        << std::string(VALUE_LENGTH, '-') << "+" << std::endl;

    print_rec(_rows.root());

    std::cout << "+-" << std::string(KEY_LENGTH, '-') << "+-"
        << std::string(VALUE_LENGTH, '-') << "+" << std::endl;
}

template <class TKey, class TValue>
void SortedTableOnRBTree<TKey, TValue>::print_rec(const RBTNode<TKey, TValue>* node) const noexcept {
    if (node == nullptr) return;
    print_rec(node->left);

    std::cout << "| " << std::left << std::setw(KEY_LENGTH) << node->data.key << "| "
        << std::setw(VALUE_LENGTH) << node->data.value << "|" << std::endl;

    print_rec(node->right);
}

#endif  // LIB_SORTED_TABLE_ON_RBTREE_SORTED_TABLE_ON_RBTREE_H_
