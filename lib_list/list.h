// Copyright 2025 Viktoria Buzlaeva

#ifndef LIB_LIST_LIST_H_
#define LIB_LIST_LIST_H_

#include <iostream>

template <class T>
struct Node {
	T value;
	Node<T>* next;
	
	Node(const T& value_, Node<T>* next_ = nullptr) : value(value_), next(next_) {}
};

template <class T>
class List {
	Node<T>* _head, * _tail;
	size_t _count;

public:
	List() : _head(nullptr), _tail(nullptr), _count(0) {}
	List(const List<T>&);

	~List();

	bool is_empty();

	Node<T>* head();
	Node<T>* tail();

	void push_front(const T&) noexcept;
	void push_back(const T&) noexcept;
	void insert(size_t, const T&) noexcept;
	void insert(Node<T>*, const T&) noexcept;

	void pop_front();
	void pop_back();
	void erase(size_t);
	void erase(Node<T>*);
};

template <class T>
List<T>::List(const List<T>& other) {
	if (&other == NULL) throw std::logic_error("Other list doesn't exist");
	_count = other._count;

	if (_count == 0) {
		_head = nullptr;
		_tail = nullptr;
		return;
	}

	_head = new Node<T>(other._head->value);
	Node<T>* current_this = _head;
	Node<T>* current_other = other._head->next;

	while (current_other != nullptr) {
		current_this->next = new Node<T>(current_other->value);
		current_this = current_this->next;
		current_other = current_other->next;
	}

	_tail = current_this;
	_count = other._count;
}

template <class T>
List<T>::~List() {
	while (_head != nullptr) {
		Node<T>* node = _head;
		_head = _head->next;
		delete node;
	}
}

#endif  // LIB_LIST_LIST_H_
