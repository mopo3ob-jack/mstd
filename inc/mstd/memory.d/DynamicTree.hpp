#ifndef MSTD_DYNAMICTREE_HPP
#define MSTD_DYNAMICTREE_HPP

#include "Arena.hpp"

namespace mstd {

template <typename T>
class DynamicTree {
public:
	DynamicTree(const DynamicTree& tree) = delete;
	DynamicTree& operator=(const DynamicTree& tree) = delete;
	
	DynamicTree(const DynamicTree&& tree) = delete;
	DynamicTree& operator=(const DynamicTree&& tree) = delete;

	constexpr ~DynamicTree() {
		if (children) {
			for (Size i = 0; i < count; ++i) {
				children[i].~DynamicTree();
			}
		}
	}

	void addChildren(Arena& arena, Size count) {
		children = arena.reserve<DynamicTree>(count);

		for (Size i = 0; i < count; ++i) {
			children[i].children = nullptr;
			children[i].count = 0L;
		}

		this->count = count;
	}

	DynamicTree& operator[](Size i) {
		return children[i];
	}

	const DynamicTree& operator[](Size i) const {
		return children[i];
	}

	DynamicTree* data() {
		return children;
	}
	
	const DynamicTree* data() const {
		return children;
	}

	Size size() const {
		return count;
	}

	T value;

private:
	DynamicTree* children = nullptr;
	Size count = 0L;
};

}

#endif
