// Copyright 2026 Viktoria Buzlaeva

#ifndef LIB_RBTREE_RBTREE_H_
#define LIB_RBTREE_RBTREE_H_

#include "../lib_bstree/bstree.h"

enum Color { Red, Black };

template <class TKey, class TValue>
struct RBTNode {
    TPair<TKey, TValue> data;
    RBTNode<TKey, TValue>* left, * right, * parent;
    Color color;

    RBTNode(const TPair<TKey, TValue>& data_, RBTNode<TKey, TValue>* left_ = nullptr,
        RBTNode<TKey, TValue>* right_ = nullptr, RBTNode<TKey, TValue>* parent_ = nullptr,
        Color color_ = Red) :
        data(data_), left(left_), right(right_), parent(parent_), color(color_) {
    }

    void recolor() {
        color = color == Red ? Black : Red;
    }

    friend std::ostream& operator << (std::ostream& out, const RBTNode<TKey, TValue>* node) {
        if (node->color == Red) {
            out << "(" << node->data.key << ")";
        }
        else if (node->color == Black) {
            out << "[" << node->data.key << "]";
        }
        return out;
    }
};

template <class TKey, class TValue>
class RBTree : public BSTree<TKey, TValue, RBTNode<TKey, TValue>> {

public:
    RBTree();

    void insert(const TKey&, const TValue&);

    void print_with_colors() const noexcept;

private:
    void left_rotate(RBTNode<TKey, TValue>*);
    void right_rotate(RBTNode<TKey, TValue>*);
    void RR(RBTNode<TKey, TValue>*);
    void LL(RBTNode<TKey, TValue>*);
    void RL(RBTNode<TKey, TValue>*);
    void LR(RBTNode<TKey, TValue>*);
    void recover_balance(RBTNode<TKey, TValue>*);
    void swap_colors(RBTNode<TKey, TValue>*, RBTNode<TKey, TValue>*);

    TVector<std::string> get_tree_lines(const RBTNode<TKey, TValue>*) const;
};

template <class TKey, class TValue>
RBTree<TKey, TValue>::RBTree() : BSTree<TKey, TValue, RBTNode<TKey, TValue>>() {}

template <class TKey, class TValue>
void RBTree<TKey, TValue>::insert(const TKey& key, const TValue& val) {
    RBTNode<TKey, TValue>* parent = BSTree<TKey, TValue, RBTNode<TKey, TValue>>::insert(key, val);
    if (!parent) { _root->recolor(); return; }

    RBTNode<TKey, TValue>* node;
    if (parent->left && parent->left->data.key == key) {
        node = parent->left;
        node->parent = parent;
    }
    else {
        node = parent->right;
        node->parent = parent;
    }

    if (parent == _root) return;

    if (parent->color == Red) recover_balance(node);
}

template <class TKey, class TValue>
void RBTree<TKey, TValue>::left_rotate(RBTNode<TKey, TValue>* node) {
    /*
        G            P
         \          / \
          P   ->   G   C
         / \        \
        T   C        T
    */
    RBTNode<TKey, TValue>* G = node;
    RBTNode<TKey, TValue>* P = G->right;
    RBTNode<TKey, TValue>* T = P->left;
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
}

template <class TKey, class TValue>
void RBTree<TKey, TValue>::right_rotate(RBTNode<TKey, TValue>* node) {
    /*
            G        P
           /        / \
          P   ->   C   G
         / \          /
        C   T        T
    */
    RBTNode<TKey, TValue>* G = node;
    RBTNode<TKey, TValue>* P = G->left;
    RBTNode<TKey, TValue>* T = P->right;
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
}

template <class TKey, class TValue>
void RBTree<TKey, TValue>::RR(RBTNode<TKey, TValue>* node) {
    /*
        G            P
         \          / \
          P   ->   G   C
           \
            C
    */
    RBTNode<TKey, TValue>* G = node;
    RBTNode<TKey, TValue>* P = G->right;
    left_rotate(G);
    swap_colors(G, P);
}

template <class TKey, class TValue>
void RBTree<TKey, TValue>::LL(RBTNode<TKey, TValue>* node) {
    /*
            G        P
           /        / \
          P   ->   C   G
         /
        C
    */
    RBTNode<TKey, TValue>* G = node;
    RBTNode<TKey, TValue>* P = G->left;
    right_rotate(node);
    swap_colors(G, P);
}

template <class TKey, class TValue>
void RBTree<TKey, TValue>::RL(RBTNode<TKey, TValue>* node) {
    /*
        G        G            C
         \        \          / \
          P   ->   C   ->   G   P
         /          \
        C            P
    */
    RBTNode<TKey, TValue>* G = node;
    RBTNode<TKey, TValue>* P = G->right;
    RBTNode<TKey, TValue>* C = P->left;
    right_rotate(P);
    left_rotate(G);
    swap_colors(G, C);
}

template <class TKey, class TValue>
void RBTree<TKey, TValue>::LR(RBTNode<TKey, TValue>* node) {
    /*
          G        G        C
         /        /        / \
        P   ->   C   ->   P   G
         \      /
          C    P
    */
    RBTNode<TKey, TValue>* G = node;
    RBTNode<TKey, TValue>* P = G->left;
    RBTNode<TKey, TValue>* C = P->right;
    left_rotate(P);
    right_rotate(G);
    swap_colors(G, C);
}

template <class TKey, class TValue>
void RBTree<TKey, TValue>::recover_balance(RBTNode<TKey, TValue>* node) {
    if (!node) return;
    RBTNode<TKey, TValue>* C = node;
    RBTNode<TKey, TValue>* P = C->parent;
    if (!P) return;
    RBTNode<TKey, TValue>* G = P->parent;
    if (!G) return;
    RBTNode<TKey, TValue>* U;
    if (G->left && G->left == P) {
        U = G->right;
    }
    else {
        U = G->left;
    }

    if (U && U->color == Red) {
        while (P->color == Red && U->color == Red) {
            U->recolor();
            P->recolor();

            if (_root == G) break;
            G->recolor();

            C = G;
            P = C->parent;
            if (!P) break;
            G = P->parent;
            if (!G) break;
            if (G->left && G->left == P) {
                U = G->right;
            }
            else {
                U = G->left;
            }
        }
    }

    if (P && P->color == Black) return;

    if (!P || !G) return;
    if (G->right == P && P->right == C) RR(G);
    else if (G->right == P && P->left == C) RL(G);
    else if (G->left == P && P->right == C) LR(G);
    else LL(G);
}

template <class TKey, class TValue>
void RBTree<TKey, TValue>::swap_colors(RBTNode<TKey, TValue>* f, RBTNode<TKey, TValue>* s) {
    Color temp = f->color;
    f->color = s->color;
    s->color = temp;
}

template <class TKey, class TValue>
void RBTree<TKey, TValue>::print_with_colors() const noexcept {
    if (is_empty()) return;
    TVector<std::string> lines = get_tree_lines(_root);
    for (int i = 0; i < lines.size(); i++) {
        std::cout << lines[i] << std::endl;
    }
}

template <class TKey, class TValue>
TVector<std::string> RBTree<TKey, TValue>::get_tree_lines(const RBTNode<TKey, TValue>* node) const {
    TVector<std::string> result;
    if (!node) return result;

    TVector<std::string> left_lines = get_tree_lines(node->left);
    TVector<std::string> right_lines = get_tree_lines(node->right);

    size_t left_width = left_lines.is_empty() ? 0 : left_lines[0].size();
    size_t right_width = right_lines.is_empty() ? 0 : right_lines[0].size();

    std::ostringstream key_out;
    key_out << node;
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

#endif  // LIB_RBTREE_RBTREE_H_
