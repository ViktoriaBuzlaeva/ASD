// Copyright 2026 Viktoria Buzlaeva

#ifndef LIB_AVLTREE_AVLTREE_H_
#define LIB_AVLTREE_AVLTREE_H_

#include "../lib_bstree/bstree.h"

template <class TKey, class TValue>
struct AVLTNode {
    TPair<TKey, TValue> data;
    AVLTNode<TKey, TValue>* left, * right, *parent;
    size_t height;

    AVLTNode(const TPair<TKey, TValue>& data_, AVLTNode<TKey, TValue>* left_ = nullptr,
        AVLTNode<TKey, TValue>* right_ = nullptr, AVLTNode<TKey, TValue>* parent_ = nullptr,
        size_t height_ = 1) :
        data(data_), left(left_), right(right_), parent(parent_), height(height_) {
    }
};

template <class TKey, class TValue>
class AVLTree : public BSTree<TKey, TValue, AVLTNode<TKey, TValue>> {

public:
    AVLTree();

    void insert(const TKey&, const TValue&);
    void erase(const TKey&);

private:
    void left_rotate(AVLTNode<TKey, TValue>*);
    void right_rotate(AVLTNode<TKey, TValue>*);
    void RR(AVLTNode<TKey, TValue>*);
    void LL(AVLTNode<TKey, TValue>*);
    void RL(AVLTNode<TKey, TValue>*);
    void LR(AVLTNode<TKey, TValue>*);
    void recover_balance(AVLTNode<TKey, TValue>*);
    void recalc_height(AVLTNode<TKey, TValue>*);
    int calc_balance(AVLTNode<TKey, TValue>*);
    size_t get_height(AVLTNode<TKey, TValue>*);
};

template <class TKey, class TValue>
AVLTree<TKey, TValue>::AVLTree() : BSTree<TKey, TValue, AVLTNode<TKey, TValue>>() {}

template <class TKey, class TValue>
void AVLTree<TKey, TValue>::insert(const TKey& key, const TValue& val) {
    AVLTNode<TKey, TValue>* P = BSTree<TKey, TValue, AVLTNode<TKey, TValue>>::insert(key, val);
    if (!P) return;

    AVLTNode<TKey, TValue>* node;
    if (P->left && P->left->data.key == key) node = P->left;
    else node = P->right;

    node->parent = P;
    recalc_height(P);

    AVLTNode<TKey, TValue>* G = P->parent;
    if (!G) return;
    int balance = calc_balance(G);
    if (abs(balance) > 1) {
        recover_balance(G);
        return;
    }

    AVLTNode<TKey, TValue>* curr = G;
    size_t prev_height;
    while (curr) {
        prev_height = curr->height;
        recalc_height(curr);
        if (prev_height == curr->height) break;

        int curr_balance = calc_balance(curr);
        if (abs(curr_balance) > 1) recover_balance(curr);

        curr = curr->parent;
    }
}

template <class TKey, class TValue>
void AVLTree<TKey, TValue>::erase(const TKey& key) {
    AVLTNode<TKey, TValue>* node = BSTree<TKey, TValue, AVLTNode<TKey, TValue>>::erase(key);
    if (!_root) return;
    if (_root && !node) {
        _root->parent = nullptr;
        node = _root;
    }

    if (node->right) node->right->parent = node;
    if (node->left) node->left->parent = node;

    size_t prev_height;
    while (node) {
        recalc_height(node);
        int balance = calc_balance(node);
        if (abs(balance) > 1) {
            recover_balance(node);
        }
        node = node->parent;
    }
}

template <class TKey, class TValue>
void AVLTree<TKey, TValue>::left_rotate(AVLTNode<TKey, TValue>* node) {
    /*
        G            P
         \          / \
          P   ->   G   C
         / \        \
        T   C        T
    */
    AVLTNode<TKey, TValue>* G = node;
    AVLTNode<TKey, TValue>* P = G->right;
    AVLTNode<TKey, TValue>* T = P->left;
    G->right = T;
    if (T) {
        T->parent = G;
    }
    P->left = G;

    P->parent = G->parent;
    G->parent = P;
    if (P->parent) {
        if (P->parent->left == G) P->parent->left = P;
        else P->parent->right = P;
    }
    else {
        _root = P;
    }
    recalc_height(G);
    recalc_height(P);
}

template <class TKey, class TValue>
void AVLTree<TKey, TValue>::right_rotate(AVLTNode<TKey, TValue>* node) {
    /*
            G        P
           /        / \
          P   ->   C   G
         / \          /
        C   T        T
    */
    AVLTNode<TKey, TValue>* G = node;
    AVLTNode<TKey, TValue>* P = G->left;
    AVLTNode<TKey, TValue>* T = P->right;
    G->left = T;
    if (T) {
        T->parent = G;
    }
    P->right = G;

    P->parent = G->parent;
    G->parent = P;
    if (P->parent) {
        if (P->parent->left == G) P->parent->left = P;
        else P->parent->right = P;
    }
    else {
        _root = P;
    }
    recalc_height(G);
    recalc_height(P);
}

template <class TKey, class TValue>
void AVLTree<TKey, TValue>::RR(AVLTNode<TKey, TValue>* node) {
    /*
        G            P
         \          / \
          P   ->   G   C
           \
            C
    */
    left_rotate(node);
}

template <class TKey, class TValue>
void AVLTree<TKey, TValue>::LL(AVLTNode<TKey, TValue>* node) {
    /*
            G        P
           /        / \
          P   ->   C   G
         /
        C
    */
    right_rotate(node);
}

template <class TKey, class TValue>
void AVLTree<TKey, TValue>::RL(AVLTNode<TKey, TValue>* node) {
    /*
        G        G            C
         \        \          / \
          P   ->   C   ->   G   P
         /          \
        C            P
    */
    AVLTNode<TKey, TValue>* G = node;
    AVLTNode<TKey, TValue>* P = G->right;
    right_rotate(P);
    left_rotate(G);
}

template <class TKey, class TValue>
void AVLTree<TKey, TValue>::LR(AVLTNode<TKey, TValue>* node) {
    /*
          G        G        C
         /        /        / \
        P   ->   C   ->   P   G
         \      /
          C    P
    */
    AVLTNode<TKey, TValue>* G = node;
    AVLTNode<TKey, TValue>* P = G->left;
    left_rotate(P);
    right_rotate(G);
}

template <class TKey, class TValue>
void AVLTree<TKey, TValue>::recover_balance(AVLTNode<TKey, TValue>* node) {
    int balance = calc_balance(node);
    if (balance > 1) {  // Ëוגמו ןמההונוגמ עÿזוכוו
        int left_balance = calc_balance(node->left);
        if (left_balance >= 0) LL(node);
        else LR(node);
    }
    else {
        int right_balance = calc_balance(node->right);
        if (right_balance <= 0) RR(node);
        else RL(node);
    }
}

template <class TKey, class TValue>
void AVLTree<TKey, TValue>::recalc_height(AVLTNode<TKey, TValue>* node) {
    if (!node) return;
    size_t left_height = get_height(node->left);
    size_t right_height = get_height(node->right);
    node->height = (left_height > right_height ? left_height : right_height) + 1;
}

template <class TKey, class TValue>
int AVLTree<TKey, TValue>::calc_balance(AVLTNode<TKey, TValue>* node) {
    if (!node) return 0;
    int left_height = get_height(node->left);
    int right_height = get_height(node->right);
    return left_height - right_height;
}

template <class TKey, class TValue>
size_t AVLTree<TKey, TValue>::get_height(AVLTNode<TKey, TValue>* node) {
    return node ? node->height : 0;
}

#endif  // LIB_AVLTREE_AVLTREE_H_
