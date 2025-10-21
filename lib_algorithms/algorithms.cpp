// Copyright 2025 Viktoria Buzlaeva

#include "../lib_algorithms/algorithms.h"

bool check_breckets(std::string str) {
	Stack<char> stack;

	for (int i = 0; str[i] != '\0'; i++) {
		if (str[i] == '}' || str[i] == ']' || str[i] == ')') {
			if (stack.is_empty()) return false;
			switch (str[i]) {
			case '}':
				if (stack.top() == '{') {
					stack.pop();
					break;
				}
			case ']':
				if (stack.top() == '[') {
					stack.pop();
					break;
				}
			case ')':
				if (stack.top() == '(') {
					stack.pop();
					break;
				}
			}
		}
		else {
			stack.push(str[i]);
		}
	}

	return stack.is_empty();
}
