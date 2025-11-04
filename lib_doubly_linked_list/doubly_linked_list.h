// Copyright 2025 Viktoria Buzlaeva

#ifndef LIB_DOUBLY_LINKED_LIST_DOUBLY_LINKED_LIST_H_
#define LIB_DOUBLY_LINKED_LIST_DOUBLY_LINKED_LIST_H_

#include "../lib_list/list.h"

template <class T>
class DoublyLinkedList: public List<T> {
public:
	DoublyLinkedList() : List<T>() {}
	DoublyLinkedList(const DoublyLinkedList<T>&);

	~DoublyLinkedList() {}

	void push_front(const T&) noexcept override;
	void push_back(const T&) noexcept override;
	void insert(size_t, const T&) override;
	void insert(Node<T>*, const T&) override;

	void pop_front() override;
	void pop_back() override;
	void erase(size_t) override;
	void erase(Node<T>*) override;

	class Iterator : public List<T>::Iterator {
	public:
		Iterator() : List<T>::Iterator() {}
		Iterator(Node<T>* node) : List<T>::Iterator(node) {}

		Iterator& operator -= (int num) {
			for (int i = 0; i < num; i++) {
				_current = _current->prev;
			}
			return *this;
		}

		Iterator& operator--() {
			_current = _current->prev;
			return *this;
		}

		Iterator operator--(int) {
			Iterator it = _current;
			_current = _current->prev;
			return it;
		}
	};

	Iterator begin() {
		return Iterator(_head);
	}
	Iterator end() {
		return Iterator(nullptr);
	}
};

template <class T>
DoublyLinkedList<T>::DoublyLinkedList(const DoublyLinkedList<T>& other) {
	if (&other == NULL) throw std::logic_error("Other list doesn't exist");
	_count = other._count;

	if (_count == 0) {
		_head = nullptr;
		_tail = nullptr;
		return;
	}

	_head = new Node<T>(other._head->value);
	Node<T>* current_this = this->_head;
	Node<T>* current_other = other._head->next;
	Node<T>* prev_this = nullptr;

	while (current_other != nullptr) {
		current_this->next = new Node<T>(current_other->value);
		prev_this = current_this;
		current_this = current_this->next;
		current_this->prev = prev_this;
		current_other = current_other->next;
	}

	_tail = current_this;
}

template <class T>
void DoublyLinkedList<T>::push_front(const T& value) noexcept {
	Node<T>* node = new Node<T>(value, _head);
	if (is_empty()) { _tail = node; }
	else { _head->prev = node; }
	_head = node;
	_count++;
}

template <class T>
void DoublyLinkedList<T>::push_back(const T& value) noexcept {
	Node<T>* node = new Node<T>(value, nullptr, _tail);
	if (is_empty()) { _tail = node; _head = node; _count++; return; }
	_tail->next = node;
	_tail = node;
	_count++;
}

template <class T>
void DoublyLinkedList<T>::insert(size_t pos, const T& value) {
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
		DoublyLinkedList<T>::insert(curr, value);
	}
}

template <class T>
void DoublyLinkedList<T>::insert(Node<T>* node, const T& value) {
	if (node == nullptr || is_empty()) throw std::logic_error("Incorrect input");
	Node<T>* new_node = new Node<T>(value);
	new_node->next = node->next;
	new_node->prev = node;
	node->next = new_node;
	if (node == _tail) { _tail = new_node; }
	_count++;
}

template <class T>
void DoublyLinkedList<T>::pop_front() {
	if (is_empty()) throw std::logic_error("List is empty");
	if (_head == _tail) { delete _head; _head = nullptr; _tail = nullptr; return; }
	Node<T>* temp = _head;
	_head = _head->next;
	_head->prev = nullptr;
	delete temp;
	_count--;
}

template <class T>
void DoublyLinkedList<T>::pop_back() {
	if (is_empty()) throw std::logic_error("List is empty");
	if (_head == _tail) { delete _head; _head = nullptr; _tail = nullptr; return; }
	Node<T>* temp = _tail;
	_tail = _tail->prev;
	_tail->next = nullptr;
	delete temp;
	_count--;
}

template <class T>
void DoublyLinkedList<T>::erase(size_t pos) {
	if (is_empty()) throw std::logic_error("List is empty");
	if (pos > _count - 1) throw std::logic_error("Position out of range");
	if (pos == 0) { pop_front(); }
	else if (pos == _count - 1) { pop_back(); }
	else {
		Node<T>* curr = _head;
		size_t curr_pos = 0;
		while (curr != nullptr) {
			if (curr_pos == pos - 1) break;
			curr_pos++;
			curr = curr->next;
		}
		erase(curr);
	}
}

template <class T>
void DoublyLinkedList<T>::erase(Node<T>* node) {
	if (is_empty()) throw std::logic_error("List is empty");
	if (node == nullptr || node->next == nullptr) throw std::logic_error("Incorrect input");
	Node<T>* temp = node->next;
	node->next = temp->next;
	if (node->next != nullptr) node->next->prev = node;
	if (temp == _tail) _tail = node;
	delete temp;
	_count--;
}

#endif  // LIB_DOUBLY_LINKED_LIST_DOUBLY_LINKED_LIST_H_
