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

	Node<T>* head() const;
	Node<T>* tail() const;

	void push_front(const T&) noexcept;
	void push_back(const T&) noexcept;
	void insert(size_t, const T&);
	void insert(Node<T>*, const T&);

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

template <class T>
bool List<T>::is_empty() { return _head == nullptr; }

template <class T>
Node<T>* List<T>::head() const { return _head; }

template <class T>
Node<T>* List<T>::tail() const { return _tail; }

template <class T>
void List<T>::push_front(const T& value) noexcept {
	Node<T>* node = new Node<T>(value, _head);
	if (is_empty()) { _tail = node; }
	_head = node;
	_count++;
}

template <class T>
void List<T>::push_back(const T& value) noexcept {
	Node<T>* node = new Node<T>(value);
	if (is_empty()) { _tail = node; _head = node; _count++; return; }
	_tail->next = node;
	_tail = node;
	_count++;
}

template <class T>
void List<T>::insert(size_t pos, const T& value) {
	if (pos > _count) throw std::logic_error("Position out of range");
	if (pos == 0) { push_front(value); }
	else if (pos == _count) { push_back(value); }
	else {
		Node<T>* curr = _head;
		size_t curr_pos = 0;
		while (curr != nullptr) {
			if (curr_pos == pos - 1) break;
			curr_pos++;
			curr = curr->next;
		}
		insert(curr, value);
		_count++;
	}
}

template <class T>
void List<T>::insert(Node<T>* node, const T& value) {
	if (node == nullptr || is_empty()) throw std::logic_error("Incorrect input");
	Node<T>* new_node = new Node<T>(value);
	new_node->next = node->next;
	node->next = new_node;
	if (node == _tail) { _tail = new_node; }
	_count++;
}

#endif  // LIB_LIST_LIST_H_
