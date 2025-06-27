#ifndef MSTD_TREE_HPP
#define MSTD_TREE_HPP

#include "Arena.hpp"

namespace mstd {

template <typename T, Size degree>
class Tree {
public:
	Tree() {}

	constexpr ~Tree() {
		if (children) {
			for (Size i = 0; i < degree; ++i) {
				children[i].~Tree();
			}
		}
	}

	void addChildren(Arena& arena) {
		children = arena.reserve<Tree>(degree);

		for (Size i = 0; i < degree; ++i) {
			children[i].children = nullptr;
		}
	}

	Tree& operator[](Size i) {
		return children[i];
	}

	const Tree& operator[](Size i) const {
		return children[i];
	}

	Tree* data() {
		return children;
	}

	const Tree* data() const {
		return children;
	}

	T value;

private:
	Tree* children = nullptr;
};

}

#endif
