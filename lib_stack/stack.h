// Copyright 2025 Viktoria Buzlaeva

#ifndef LIB_STACK_STACK_H_
#define LIB_STACK_STACK_H_

template<class T>
class Stack {
	T* _data;
	int _size;
	int _top;

public:
	Stack(int size = 15);
	Stack(const Stack<T>&);

	~Stack();

	void push(T);
	void pop();

	T top() const;

	inline bool is_empty() noexcept const;
	inline bool is_full() noexcept const;

	void clear() noexcept;
};

#endif  // LIB_STACK_STACK_H_
