// Copyright 2025 Viktoria Buzlaeva

#ifndef LIB_ALGORITHMS_ALGORITHMS_H_
#define LIB_ALGORITHMS_ALGORITHMS_H_

#include <iomanip>
#include <string>
#include "../lib_stack/stack.h"
#include "../lib_list/list.h"
#include "../lib_matrix/matrix.h"
#include "../lib_dsu/dsu.h"
#include "../lib_graph_adjacency_l/graph_adjacency_l.h"

enum TypeOfCrossing { Intersect, NotIntersect, Touch, Coincide };

template <class T>
TypeOfCrossing find_type_of_crossing(const T& first, const T& second) {
    if (first == second) {
        return Coincide;
    }
    else if (first.cent().find_distance(second.cent()) > (first.rad() + second.rad())) {
        return NotIntersect;
    }
    else if (first.cent().find_distance(second.cent()) < (first.rad() + second.rad())) {
        return Intersect;
    }
    else {
        return Touch;
    }
}

int find_local_min_matrix(Matrix<int>, unsigned int seed = time(0));

int find_number_of_islands(Matrix<int>);

Matrix<bool> generate_labyrinth(int, int, int, int);

Matrix<bool> create_wall_matrix(int, int, int, int);

void create_passage(Matrix<bool>&, int, int, int, int);

void print_lab(Matrix<bool> labyrinth, int N, int M);

bool check_brackets(std::string str);

void read_expression(std::string expression);

template <class T>
bool is_looped_1(List<T>& list) {  // O(n)
    if (list.is_empty() || list.begin() == list.end()) return false;

    List<T>::Iterator it_1 = list.begin();
    List<T>::Iterator it_2 = list.begin();

    do {
        it_1++;
        it_2++;
        if (it_2 == nullptr) return false;
        it_2++;
        if (it_2 == nullptr) return false;
    } while (it_1 != it_2);

    return true;
}

template <class T>
bool is_looped_2(List<T>& list) {
    if (list.is_empty() || list.head() == list.tail()) return false;

    bool loop_found = false;

    Node<T>* curr = list.head();
    Node<T>* prev = nullptr;

    while (curr != nullptr) {
        if (curr->next == list.head()) {
            loop_found = true;
        }

        Node<T>* tmp = curr->next;
        curr->next = prev;
        prev = curr;
        curr = tmp;
    }

    curr = prev;
    prev = nullptr;
    while (curr != nullptr) {
        Node<T>* tmp = curr->next;
        curr->next = prev;
        prev = curr;
        curr = tmp;
    }

    return loop_found;
}

template <class T>
Node<T>* find_loop(List<T>& list) {
    if (list.is_empty() || list.head() == list.tail()) return nullptr;
    
    Node<T>* first = list.head();
    Node<T>* second = list.head();

    do {
        if (second == nullptr || second->next == nullptr) return nullptr;
        first = first->next;
        second = second->next->next;
    } while (first != second);

    first = list.head();
    while (first != second) {
        first = first->next;
        second = second->next;
    }

    return first;
}

std::vector<int> find_path_in_labyrinth(Matrix<bool> labyrinth, int N, int M, int S, int F);

void print_lab_with_path(Matrix<bool> labyrinth, int N, int M, std::vector<int>);

#endif  // LIB_ALGORITHMS_ALGORITHMS_H_
