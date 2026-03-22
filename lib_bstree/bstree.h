// Copyright 2026 Viktoria Buzlaeva

#ifndef LIB_BSTREE_BSTREE_H_
#define LIB_BSTREE_BSTREE_H_

#include <iostream>
#include "../lib_pair/pair.h"
#include "../lib_tvector/tvector.h"

template <class TKey, class TValue>
struct BSTNode {
    TPair<TKey, TValue> data;
    BSTNode<TKey, TValue>* left, * right;

    BSTNode(const TPair<TKey, TValue>& data_, BSTNode<TKey, TValue>* left_ = nullptr,
        BSTNode<TKey, TValue>* right_ = nullptr) : data(data_), left(left_), right(right_) {
    }
};

template <class TKey, class TValue>
class BSTree {
    BSTNode<TKey, TValue>* _root;

public:
    BSTree();
    ~BSTree();

    const BSTNode<TKey, TValue>* root() const noexcept { return _root; }

    void insert(const TKey&, const TValue&);
    TValue* find(const TKey&) const noexcept;
    void erase(const TKey&);

    void clear() noexcept;

    bool is_empty() const noexcept;

    void print() const noexcept;
    void print_DLCR() const noexcept;

private:
    BSTNode<TKey, TValue>* find_parent(const TKey&) const noexcept;
    void erase_node(BSTNode<TKey, TValue>*, BSTNode<TKey, TValue>*) noexcept;
    BSTNode<TKey, TValue>* find_max_left(BSTNode<TKey, TValue>*) const noexcept;
    void clear_rec(BSTNode<TKey, TValue>*) noexcept;

    TVector<std::string> get_tree_lines(const BSTNode<TKey, TValue>*) const;

    void print_DLCR_rec(BSTNode<TKey, TValue>*) const noexcept;
};

template <class TKey, class TValue>
BSTree<TKey, TValue>::BSTree() {
    _root = nullptr;
}

template <class TKey, class TValue>
BSTree<TKey, TValue>::~BSTree() {
    clear();
}

template <class TKey, class TValue>
void BSTree<TKey, TValue>::insert(const TKey& key, const TValue& value) {
    BSTNode<TKey, TValue>* parent = find_parent(key);
    if (!parent) {
        _root = new BSTNode<TKey, TValue>(TPair<TKey, TValue>(key, value));
        return;
    }
    if (parent->data.key < key && !parent->right) {
        parent->right = new BSTNode<TKey, TValue>(TPair<TKey, TValue>(key, value));
        return;
    }
    if (parent->data.key > key && !parent->left) {
        parent->left = new BSTNode<TKey, TValue>(TPair<TKey, TValue>(key, value));
        return;
    }
    throw std::logic_error("Key already exists");
}

template <class TKey, class TValue>
TValue* BSTree<TKey, TValue>::find(const TKey& key) const noexcept {
    BSTNode<TKey, TValue>* parent = find_parent(key);
    if (!parent) return nullptr;
    if (parent->left && parent->left->data.key == key)
        return &parent->left->data.value;
    else if (parent->right && parent->right->data.key == key)
        return &parent->right->data.value;
    else if (parent == _root && _root->data.key == key)
        return &_root->data.value;
    return nullptr;
}

template <class TKey, class TValue>
void BSTree<TKey, TValue>::erase(const TKey& key) {
    BSTNode<TKey, TValue>* parent = find_parent(key);
    BSTNode<TKey, TValue>* deleted_node = nullptr;

    if (parent->data.key < key && parent->right) {
        deleted_node = parent->right;
    }
    else if (parent->data.key > key && parent->left) {
        deleted_node = parent->left;
    }
    else if (parent->data.key == key) {
        deleted_node = parent;
    }
    else {
        throw std::logic_error("Key doesn't exist");
    }

    erase_node(deleted_node, parent);
}

template <class TKey, class TValue>
void BSTree<TKey, TValue>::clear() noexcept {
    clear_rec(_root);
    _root = nullptr;
}

template <class TKey, class TValue>
bool BSTree<TKey, TValue>::is_empty() const noexcept {
    return _root == nullptr;
}

template <class TKey, class TValue>
void BSTree<TKey, TValue>::print() const noexcept {
    if (is_empty()) return;
    TVector<std::string> lines = get_tree_lines(_root);
    for (int i = 0; i < lines.size(); i++) {
        std::cout << lines[i] << std::endl;
    }
}

template <class TKey, class TValue>
void BSTree<TKey, TValue>::print_DLCR() const noexcept {
    print_DLCR_rec(_root);
}

template <class TKey, class TValue>
BSTNode<TKey, TValue>* BSTree<TKey, TValue>::find_parent(const TKey& key) const noexcept {
    if (is_empty()) return nullptr;
    if (_root->data.key == key) return _root;
    BSTNode<TKey, TValue>* curr = _root;
    while (1) {
        if (curr->data.key > key) {
            if (!curr->left) return curr; // для вставки
            if (curr->left->data.key == key) return curr;
            else curr = curr->left;
        }
        else {
            if (!curr->right) return curr; // для вставки
            if (curr->right->data.key == key) return curr;
            else curr = curr->right;
        }
    }
}

template <class TKey, class TValue>
void BSTree<TKey, TValue>::erase_node(BSTNode<TKey, TValue>* deleted, BSTNode<TKey, TValue>* parent) noexcept {
    if (!deleted->left && !deleted->right) {
        if (deleted == _root) _root = nullptr;
        else {
            if (parent->data.key < deleted->data.key) {
                parent->right = nullptr;
            }
            else {
                parent->left = nullptr;
            }
        }
        delete deleted;
    }
    else if (!deleted->left) {
        if (deleted == _root) _root = deleted->right;
        else {
            if (parent->data.key < deleted->data.key) {
                parent->right = deleted->right;
            }
            else {
                parent->left = deleted->right;
            }
        }
        delete deleted;
    }
    else if (!deleted->right) {
        if (deleted == _root) _root = deleted->left;
        else {
            if (parent->data.key < deleted->data.key) {
                parent->right = deleted->left;
            }
            else {
                parent->left = deleted->left;
            }
        }
        delete deleted;
    }
    else {
        BSTNode<TKey, TValue>* replacer = find_max_left(deleted);
        BSTNode<TKey, TValue>* replacer_parent = find_parent(replacer->data.key);
        if (deleted == _root) _root->data = replacer->data;
        else {
            deleted->data = replacer->data;
            if (parent->data.key < deleted->data.key) {
                parent->right = deleted;
            }
            else {
                parent->left = deleted;
            }
        }
        erase_node(replacer, replacer_parent);
    }
}

template <class TKey, class TValue>
BSTNode<TKey, TValue>* BSTree<TKey, TValue>::find_max_left(BSTNode<TKey, TValue>* curr) const noexcept {
    curr = curr->left;
    while (curr->right) {
        curr = curr->right;
    }
    return curr;
}

template <class TKey, class TValue>
void BSTree<TKey, TValue>::clear_rec(BSTNode<TKey, TValue>* node) noexcept {
    if (node == nullptr) return;
    clear_rec(node->left);
    clear_rec(node->right);
    delete node;
}

template <class TKey, class TValue>
TVector<std::string> BSTree<TKey, TValue>::get_tree_lines(const BSTNode<TKey, TValue>* node) const {
    TVector<std::string> result;
    if (!node) return result;

    TVector<std::string> left_lines = get_tree_lines(node->left);
    TVector<std::string> right_lines = get_tree_lines(node->right);

    size_t left_width = left_lines.is_empty() ? 0 : left_lines[0].size();
    size_t right_width = right_lines.is_empty() ? 0 : right_lines[0].size();

    std::ostringstream key_out;
    key_out << node->data.key;
    std::string key_str = key_out.str();

    std::string root_line = std::string(left_width, ' ') + key_str + std::string(right_width, ' ');
    result.push_back(root_line);

    // Строка для линий между корнем и предками
    std::string line_between_levels;
    if (!left_lines.is_empty() || !right_lines.is_empty()) {
        std::string left_part = left_lines.is_empty() ? std::string(left_width, ' ') : std::string(left_width - 1, ' ') + "/";
        std::string right_part = right_lines.is_empty() ? std::string(right_width, ' ') : "\\" + std::string(right_width - 1, ' ');
        line_between_levels = left_part + std::string(key_str.size(), ' ') + right_part;
    }
    if (!line_between_levels.empty()) result.push_back(line_between_levels);

    // Объединение строк левого и правого поддеревьев корня
    int max_lines = std::max(left_lines.size(), right_lines.size());
    for (int i = 0; i < max_lines; i++) {
        std::string left_part = i < left_lines.size() ? left_lines[i] : std::string(left_width, ' ');
        std::string right_part = i < right_lines.size() ? right_lines[i] : std::string(right_width, ' ');
        result.push_back(left_part + std::string(key_str.size(), ' ') + right_part);
    }

    return result;
}

template <class TKey, class TValue>
void BSTree<TKey, TValue>::print_DLCR_rec(BSTNode<TKey, TValue>* node) const noexcept {
    if (node == nullptr) return;
    print_DLCR_rec(node->left);
    std::cout << node->data.key << " ";
    print_DLCR_rec(node->right);
}

#endif  // LIB_BSTREE_BSTREE_H_
