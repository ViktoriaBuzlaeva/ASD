// Copyright 2025 Viktoria Buzlaeva

#ifndef LIB_ALGORITHMS_ALGORITHMS_H_
#define LIB_ALGORITHMS_ALGORITHMS_H_

#include <string>
#include "../lib_stack/stack.h"
#include "../lib_list/list.h"

bool check_brackets(std::string str);

void read_expression(std::string expression);

template <class T>
bool is_looped_1(List<T>& list) {
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

#endif  // LIB_ALGORITHMS_ALGORITHMS_H_
