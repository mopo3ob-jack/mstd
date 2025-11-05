#ifndef MSTD_STACK_HPP
#define MSTD_STACK_HPP

#include "Arena.hpp"

namespace mstd {

template <typename T>
class Stack {
public:
	Stack(const Stack& tree) = delete;
	Stack& operator=(const Stack& tree) = delete;

	Stack() {}

	Stack(Size count, Arena& arena) {
		first = arena.reserve<T>(count);
		current = first - 1;
	}

	~Stack() {
		while (first <= current) {
			first->~T();
			++first;
		}
	}

	T& operator[](Size i) {
		return first[i];
	}

	const T& operator[](Size i) const {
		return first[i];
	}

	void push(const T& t) {
		++current;
		*current = t;
	}

	void push(const T&& t) {
		++current;
		*current = t;
	}

	T& pop() {
		--current;
		return *current;
	}

	T& top() {
		return *current;
	}

	Size size() {
		return current - first + 1;
	}
	
private:
	T* first;
	T* current;
};

}

#endif
