// Copyright 2025 Viktoria Buzlaeva

#ifndef LIB_LIST_LIST_H_
#define LIB_LIST_LIST_H_

#include <iostream>

template <class T>
struct Node {
	T value;
	Node<T>* next;
	Node<T>* prev;
	
	Node(const T& value_, Node<T>* next_ = nullptr, Node<T>* prev_ = nullptr) : value(value_), next(next_), prev(prev_) {}

	bool operator == (const Node<T>& other) {
		return this->next == other.next && this->value == other.value;
	}
	bool operator != (const Node<T>& other) {
		return !(*this == other);
	}

	Node<T>& operator = (const Node<T>& other) {
		if (*this != other) {
			this->value = other.value;
			this->next = other.next;
			this->prev = other.prev;
		}
		return *this;
	}
};

template <class T>
class List {
protected:
	Node<T>* _head, * _tail;
	size_t _count;

public:
	List() : _head(nullptr), _tail(nullptr), _count(0) {}
	List(const List<T>&);

	~List();

	bool is_empty();

	Node<T>* head() const;
	Node<T>* tail() const;

	virtual void push_front(const T&) noexcept;
	virtual void push_back(const T&) noexcept;
	virtual void insert(size_t, const T&);
	virtual void insert(Node<T>*, const T&);

	virtual void pop_front();
	virtual void pop_back();
	virtual void erase(size_t);
	virtual void erase(Node<T>*);

	class Iterator {
	protected:
		Node<T>* _current;

	public:
		Iterator() : _current(nullptr) {}
		Iterator(Node<T>* node) { _current = node; }

		Iterator& operator = (const Iterator& other) {
			if (*this != other) {
				this->_current = other._current;
			}
			return *this;
		}
		Iterator& operator += (int num) {
			for (int i = 0; i < num; i++) {
				_current = _current->next;
			}
			return *this;
		}

		Iterator& operator ++ () {
			_current = _current->next;
			return *this;
		}
		Iterator operator ++ (int) {
			Iterator it = _current;
			_current = _current->next;
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

template <class T>
void List<T>::pop_front() {
	if (is_empty()) throw std::logic_error("List is empty");
	if (_head == _tail) { delete _head; _head = nullptr; _tail = nullptr; return; }
	Node<T>* temp = _head;
	_head = _head->next;
	delete temp;
	_count--;
}

template <class T>
void List<T>::pop_back() {
	if (is_empty()) throw std::logic_error("List is empty");
	if (_head == _tail) { delete _head; _head = nullptr; _tail = nullptr; return; }
	Node<T>* curr = _head;
	while (curr->next != _tail) {
		curr = curr->next;
	}
	delete _tail;
	_tail = curr;
	curr->next = nullptr;
	_count--;
}

template <class T>
void List<T>::erase(size_t pos) {
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
void List<T>::erase(Node<T>* node) {
	if (is_empty()) throw std::logic_error("List is empty");
	if (node == nullptr || node->next == nullptr) throw std::logic_error("Incorrect input");
	Node<T>* temp = node->next;
	node->next = temp->next;
	if (temp == _tail) _tail = node;
	delete temp;
	_count--;
}

#endif  // LIB_LIST_LIST_H_
