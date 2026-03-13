// Copyright 2026 Viktoria Buzlaeva

#ifndef LIB_TREE_TREE_H_
#define LIB_TREE_TREE_H_

#include "../lib_pair/pair.h"
#include "../lib_queue/queue.h"

template <class TKey, class TValue>
struct TNode {
    TPair<TKey, TValue> data;
    TNode<TKey, TValue>* left, * right;

    TNode(const TPair<TKey, TValue>& data_, TNode<TKey, TValue>* left_ = nullptr,
        TNode<TKey, TValue>* right_ = nullptr) : data(data_), left(left_), right(right_) {}
};

template <class TKey, class TValue>
class Tree {
    TNode<TKey, TValue>* _root;

public:
    Tree();
    ~Tree();

    void insert(const TKey&, const TValue&);
    TValue* find(const TKey&) const noexcept;
    void erase(const TKey&);

    void clear() noexcept;

    bool is_empty() const noexcept;

    void print_w() const noexcept;
    void print_DLCR() const noexcept;
    void print_DLRC() const noexcept;
    void print_DCLR() const noexcept;

private:
    void clear_rec(TNode<TKey, TValue>*) noexcept;

    void print_DLCR_rec(TNode<TKey, TValue>*) const noexcept;
    void print_DLRC_rec(TNode<TKey, TValue>*) const noexcept;
    void print_DCLR_rec(TNode<TKey, TValue>*) const noexcept;
};

template <class TKey, class TValue>
Tree<TKey, TValue>::Tree() {
    _root = nullptr;
}

template <class TKey, class TValue>
Tree<TKey, TValue>::~Tree() {
    if (is_empty()) { delete _root; return; }

    Queue<TNode<TKey, TValue>*> q;
    TNode<TKey, TValue>* current = nullptr;
    q.push(_root);
    while (!q.is_empty()) {
        current = q.head();
        q.pop();
        if (current->left) q.push(current->left);
        if (current->right) q.push(current->right);
        delete current;
    }
}

template <class TKey, class TValue>
void Tree<TKey, TValue>::insert(const TKey& key, const TValue& value) {
    TNode<TKey, TValue>* new_node =
        new TNode<TKey, TValue>(TPair<TKey, TValue>(key, value));

    if (is_empty()) { _root = new_node; return; }

    TNode<TKey, TValue>* curr = nullptr;
    Queue<TNode<TKey, TValue>*> q;
    q.push(_root);
    while (1) {
        curr = q.head();
        q.pop();
        if (!curr->left) { curr->left = new_node; return; }
        if (!curr->right) { curr->right = new_node; return; }
        q.push(curr->left);
        q.push(curr->right);
    }
}

template <class TKey, class TValue>
TValue* Tree<TKey, TValue>::find(const TKey& key) const noexcept {

}

template <class TKey, class TValue>
void Tree<TKey, TValue>::erase(const TKey& key) {

}

template <class TKey, class TValue>
void Tree<TKey, TValue>::clear() noexcept {
    clear_rec(_root);
    _root = nullptr;
}

template <class TKey, class TValue>
bool Tree<TKey, TValue>::is_empty() const noexcept {
    return _root == nullptr;
}

template <class TKey, class TValue>
void Tree<TKey, TValue>::print_w() const noexcept {
    if (is_empty()) return;

    Queue<TNode<TKey, TValue>*> q;
    TNode<TKey, TValue>* curr = nullptr;
    q.push(_root);
    while (!q.is_empty()) {
        curr = q.head();
        std::cout << curr->data.key << " ";
        q.pop();
        if (curr->left) q.push(curr->left);
        if (curr->right) q.push(curr->right);
    }
}

template <class TKey, class TValue>
void Tree<TKey, TValue>::print_DLCR() const noexcept {
    print_DLCR_rec(_root);
}

template <class TKey, class TValue>
void Tree<TKey, TValue>::print_DLRC() const noexcept {
    print_DLRC_rec(_root);
}

template <class TKey, class TValue>
void Tree<TKey, TValue>::print_DCLR() const noexcept {
    print_DCLR_rec(_root);
}

template <class TKey, class TValue>
void Tree<TKey, TValue>::print_DLCR_rec(TNode<TKey, TValue>* node) const noexcept {
    if (node == nullptr) return;
    print_DLCR_rec(node->left);
    std::cout << node->data.key << " ";
    print_DLCR_rec(node->right);
}

template <class TKey, class TValue>
void Tree<TKey, TValue>::print_DLRC_rec(TNode<TKey, TValue>* node) const noexcept {
    if (node == nullptr) return;
    print_DLRC_rec(node->left);
    print_DLRC_rec(node->right);
    std::cout << node->data.key << " ";
}

template <class TKey, class TValue>
void Tree<TKey, TValue>::print_DCLR_rec(TNode<TKey, TValue>* node) const noexcept {
    if (node == nullptr) return;
    std::cout << node->data.key << " ";
    print_DCLR_rec(node->left);
    print_DCLR_rec(node->right);
}

template <class TKey, class TValue>
void Tree<TKey, TValue>::clear_rec(TNode<TKey, TValue>* node) noexcept {
    if (node == nullptr) return;
    clear_rec(node->left);
    clear_rec(node->right);
    delete node;
}

#endif  // LIB_TREE_TREE_H_
