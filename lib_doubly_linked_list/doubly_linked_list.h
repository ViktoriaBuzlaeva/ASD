// Copyright 2025 Viktoria Buzlaeva

#ifndef LIB_DOUBLY_LINKED_LIST_DOUBLY_LINKED_LIST_H_
#define LIB_DOUBLY_LINKED_LIST_DOUBLY_LINKED_LIST_H_

#include <iostream>

template <class T>
struct DoublyNode {
	T value;
	DoublyNode<T>* next;
	DoublyNode<T>* prev;

	DoublyNode(const T& value_, DoublyNode<T>* next_ = nullptr, DoublyNode<T>* prev_ = nullptr) : value(value_), next(next_), prev(prev_) {}
};

template <class T>
class DoublyLinkedList {
	DoublyNode<T>* _head, * _tail;
	size_t _count;

public:
	DoublyLinkedList() : _head(nullptr), _tail(nullptr), _count(0) {}
	DoublyLinkedList(const DoublyLinkedList<T>&);

	~DoublyLinkedList() {}

	bool is_empty();

	DoublyNode<T>* head() const;
	DoublyNode<T>* tail() const;

	void push_front(const T&) noexcept;
	void push_back(const T&) noexcept;
	void insert(size_t, const T&);
	void insert(DoublyNode<T>*, const T&);

	void pop_front();
	void pop_back();
	void erase(size_t);
	void erase(DoublyNode<T>*);

	class Iterator {
		DoublyNode<T>* _current;

	public:
		Iterator() : _current(nullptr) {}
		Iterator(DoublyNode<T>* node) { _current = node; }

		Iterator& operator = (const Iterator& other) {
			if (*this != other) {
				this->_current = other._current;
			}
			return *this;
		}

		Iterator& operator += (int num) {
			for (int i = 0; i < num; i++) {
				++(*this);
			}
			return *this;
		}

		Iterator& operator ++ () {
			if (_current == nullptr) throw std::logic_error("Incrementing past end iterator");
			_current = _current->next;
			return *this;
		}

		Iterator operator ++ (int) {
			Iterator it = _current;
			++(*this);
			return it;
		}

		Iterator& operator -= (int num) {
			for (int i = 0; i < num; i++) {
				--(*this);
			}
			return *this;
		}

		Iterator& operator--() {
			if (_current == nullptr) throw std::logic_error("Decrementing before begin iterator");
			_current = _current->prev;
			return *this;
		}

		Iterator operator--(int) {
			Iterator it = _current;
			--(*this);
			return it;
		}

		T& operator * () {
			return _current->value;
		}

		bool operator == (const Iterator& other) const {
			return this->_current == other._current;
		}

		bool operator != (const Iterator& other) const {
			return !(*this == other);
		}
	};

	Iterator begin() {
		return Iterator(_head);
	}

	Iterator end() {
		return Iterator(nullptr);
	}

	Iterator rbegin() {
		return Iterator(_tail);
	}

	Iterator rend() {
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

	_head = new DoublyNode<T>(other._head->value);
	DoublyNode<T>* current_this = this->_head;
	DoublyNode<T>* current_other = other._head->next;
	DoublyNode<T>* prev_this = nullptr;

	while (current_other != nullptr) {
		current_this->next = new DoublyNode<T>(current_other->value);
		prev_this = current_this;
		current_this = current_this->next;
		current_this->prev = prev_this;
		current_other = current_other->next;
	}

	_tail = current_this;
}

template <class T>
bool DoublyLinkedList<T>::is_empty() { return _head == nullptr; }

template <class T>
DoublyNode<T>* DoublyLinkedList<T>::head() const { return _head; }

template <class T>
DoublyNode<T>* DoublyLinkedList<T>::tail() const { return _tail; }

template <class T>
void DoublyLinkedList<T>::push_front(const T& value) noexcept {
	DoublyNode<T>* node = new DoublyNode<T>(value, _head);
	if (is_empty()) { _tail = node; }
	else { _head->prev = node; }
	_head = node;
	_count++;
}

template <class T>
void DoublyLinkedList<T>::push_back(const T& value) noexcept {
	DoublyNode<T>* node = new DoublyNode<T>(value, nullptr, _tail);
	if (is_empty()) { _head = node; }
	else { _tail->next = node; }
	_tail = node;
	_count++;
}

template <class T>
void DoublyLinkedList<T>::insert(size_t pos, const T& value) {
	if (pos > _count) throw std::logic_error("Position out of range");
	if (pos == 0) { push_front(value); }
	else if (pos == _count) { push_back(value); }
	else {
		DoublyNode<T>* curr = _head;
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
void DoublyLinkedList<T>::insert(DoublyNode<T>* node, const T& value) {
	if (node == nullptr || is_empty()) throw std::logic_error("Incorrect input");
	DoublyNode<T>* new_node = new DoublyNode<T>(value);
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
	DoublyNode<T>* temp = _head;
	_head = _head->next;
	_head->prev = nullptr;
	delete temp;
	_count--;
}

template <class T>
void DoublyLinkedList<T>::pop_back() {
	if (is_empty()) throw std::logic_error("List is empty");
	if (_head == _tail) { delete _head; _head = nullptr; _tail = nullptr; return; }
	DoublyNode<T>* temp = _tail;
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
		DoublyNode<T>* curr = _head;
		size_t curr_pos = 0;
		while (curr != nullptr) {
			if (curr_pos == pos) break;
			curr_pos++;
			curr = curr->next;
		}
		erase(curr);
	}
}

template <class T>
void DoublyLinkedList<T>::erase(DoublyNode<T>* node) {
	if (is_empty()) throw std::logic_error("List is empty");
	if (node == nullptr) throw std::logic_error("Incorrect input");
	if (node->next != nullptr) { node->next->prev = node->prev; }
	else { _tail = node->prev; }
	if (node->prev != nullptr) { node->prev->next = node->next; }
	else { _head = node->next; }
	delete node;
	_count--;
}

#endif  // LIB_DOUBLY_LINKED_LIST_DOUBLY_LINKED_LIST_H_
