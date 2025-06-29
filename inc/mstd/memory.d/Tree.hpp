#ifndef MSTD_TREE_HPP
#define MSTD_TREE_HPP

#include "Arena.hpp"

namespace mstd {

template <typename T, Size degree>
class Tree {
public:
	Tree() {}

	constexpr ~Tree() {
		for (Size i = 0; i < degree; ++i) {
			if (children[i]) {
				children[i]->~Tree();
			}
		}
	}

	Tree*& operator[](Size i) {
		return children[i];
	}

	const Tree*& operator[](Size i) const {
		return children[i];
	}

	Tree** data() {
		return children;
	}

	const Tree** data() const {
		return children;
	}

	T value;

private:
	Tree* children[degree] = { nullptr };
};

}

#endif
