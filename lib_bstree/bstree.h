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

template <class TKey, class TValue, class TypeNode = BSTNode<TKey, TValue>>
class BSTree {
protected:
    TypeNode* _root;

public:
    BSTree();
    ~BSTree();

    const TypeNode* root() const noexcept { return _root; }

    TypeNode* insert(const TKey&, const TValue&);
    TValue* find(const TKey&) const noexcept;
    TypeNode* erase(const TKey&);

    void clear() noexcept;

    bool is_empty() const noexcept;

    void print() const noexcept;
    void print_DLCR() const noexcept;

private:
    TypeNode* erase_node(TypeNode*, TypeNode*) noexcept;
    TypeNode* find_max_left(TypeNode*) const noexcept;
    void clear_rec(TypeNode*) noexcept;

    TVector<std::string> get_tree_lines(const TypeNode*) const;

    void print_DLCR_rec(TypeNode*) const noexcept;

protected:
    TypeNode* find_parent(const TKey&) const noexcept;

};

template <class TKey, class TValue, class TypeNode>
BSTree<TKey, TValue, TypeNode>::BSTree() {
    _root = nullptr;
}

template <class TKey, class TValue, class TypeNode>
BSTree<TKey, TValue, TypeNode>::~BSTree() {
    clear();
}

template <class TKey, class TValue, class TypeNode>
TypeNode* BSTree<TKey, TValue, TypeNode>::insert(const TKey& key, const TValue& value) {
    TypeNode* parent = find_parent(key);
    if (!parent) {
        _root = new TypeNode(TPair<TKey, TValue>(key, value));
        return nullptr;
    }
    if (parent->data.key < key && !parent->right) {
        parent->right = new TypeNode(TPair<TKey, TValue>(key, value));
        return parent;
    }
    if (parent->data.key > key && !parent->left) {
        parent->left = new TypeNode(TPair<TKey, TValue>(key, value));
        return parent;
    }
    throw std::logic_error("Key already exists");
}

template <class TKey, class TValue, class TypeNode>
TValue* BSTree<TKey, TValue, TypeNode>::find(const TKey& key) const noexcept {
    TypeNode* parent = find_parent(key);
    if (!parent) return nullptr;
    if (parent->left && parent->left->data.key == key)
        return &parent->left->data.value;
    else if (parent->right && parent->right->data.key == key)
        return &parent->right->data.value;
    else if (parent == _root && _root->data.key == key)
        return &_root->data.value;
    return nullptr;
}

template <class TKey, class TValue, class TypeNode>
TypeNode* BSTree<TKey, TValue, TypeNode>::erase(const TKey& key) {
    if (is_empty()) throw std::logic_error("Tree is empty");
    TypeNode* parent = find_parent(key);
    TypeNode* deleted_node = nullptr;

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

    return erase_node(deleted_node, parent);
}

template <class TKey, class TValue, class TypeNode>
void BSTree<TKey, TValue, TypeNode>::clear() noexcept {
    clear_rec(_root);
    _root = nullptr;
}

template <class TKey, class TValue, class TypeNode>
bool BSTree<TKey, TValue, TypeNode>::is_empty() const noexcept {
    return _root == nullptr;
}

template <class TKey, class TValue, class TypeNode>
void BSTree<TKey, TValue, TypeNode>::print() const noexcept {
    if (is_empty()) return;
    TVector<std::string> lines = get_tree_lines(_root);
    for (int i = 0; i < lines.size(); i++) {
        std::cout << lines[i] << std::endl;
    }
}

template <class TKey, class TValue, class TypeNode>
void BSTree<TKey, TValue, TypeNode>::print_DLCR() const noexcept {
    print_DLCR_rec(_root);
}

template <class TKey, class TValue, class TypeNode>
TypeNode* BSTree<TKey, TValue, TypeNode>::find_parent(const TKey& key) const noexcept {
    if (is_empty()) return nullptr;
    if (_root->data.key == key) return _root;
    TypeNode* curr = _root;
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

template <class TKey, class TValue, class TypeNode>
TypeNode* BSTree<TKey, TValue, TypeNode>::erase_node(TypeNode* deleted, TypeNode* parent) noexcept {
    if (!deleted->left && !deleted->right) {
        if (deleted == _root) {
            _root = nullptr;
            return nullptr;
        }
        else {
            if (parent->data.key < deleted->data.key) {
                parent->right = nullptr;
            }
            else {
                parent->left = nullptr;
            }
        }
        delete deleted;
        return parent;
    }
    else if (!deleted->left) {
        if (deleted == _root) {
            _root = deleted->right;
            return nullptr;
        }
        else {
            if (parent->data.key < deleted->data.key) {
                parent->right = deleted->right;
            }
            else {
                parent->left = deleted->right;
            }
        }
        delete deleted;
        return parent;
    }
    else if (!deleted->right) {
        if (deleted == _root) {
            _root = deleted->left;
            return nullptr;
        }
        else {
            if (parent->data.key < deleted->data.key) {
                parent->right = deleted->left;
            }
            else {
                parent->left = deleted->left;
            }
        }
        delete deleted;
        return parent;
    }
    else {
        TypeNode* replacer = find_max_left(deleted);
        TypeNode* replacer_parent = find_parent(replacer->data.key);
        deleted->data = replacer->data;
        return erase_node(replacer, replacer_parent);
    }
}

template <class TKey, class TValue, class TypeNode>
TypeNode* BSTree<TKey, TValue, TypeNode>::find_max_left(TypeNode* curr) const noexcept {
    curr = curr->left;
    while (curr->right) {
        curr = curr->right;
    }
    return curr;
}

template <class TKey, class TValue, class TypeNode>
void BSTree<TKey, TValue, TypeNode>::clear_rec(TypeNode* node) noexcept {
    if (node == nullptr) return;
    clear_rec(node->left);
    clear_rec(node->right);
    delete node;
}

template <class TKey, class TValue, class TypeNode>
TVector<std::string> BSTree<TKey, TValue, TypeNode>::get_tree_lines(const TypeNode* node) const {
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

template <class TKey, class TValue, class TypeNode>
void BSTree<TKey, TValue, TypeNode>::print_DLCR_rec(TypeNode* node) const noexcept {
    if (node == nullptr) return;
    print_DLCR_rec(node->left);
    std::cout << node->data.key << " ";
    print_DLCR_rec(node->right);
}

#endif  // LIB_BSTREE_BSTREE_H_
