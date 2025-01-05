#ifndef MSTD_TREE_HPP
#define MSTD_TREE_HPP

#include "Arena.hpp"

namespace mstd {

template <typename T, Size degree>
class Tree {
public:
	Tree() {}

	Tree(Tree&& tree) {
		this->operator=(tree);
	}

	Tree&& operator=(Tree&& tree) {
		this->~Tree();

		this->rootNode = tree.rootNode;

		tree.rootNode = nullptr;
	}

	Tree(Tree& tree, Arena& arena) {
		this->rootNode.value = tree.rootNode.value;
	}

	Tree& operator=(Tree& tree) = delete;

	struct Node {
		Node* nodes;
		T value;

		Node& operator[](Size i) {
			return nodes[i];
		}
	};

	Node& root() {
		return rootNode;
	}

	void addChildren(Node& node, Arena& arena) {
		node.nodes = arena.reserve<Node>(degree);

		for (Size i = 0; i < degree; ++i) {
			node[i] = { .nodes = {nullptr} };
		}
	}
private:
	Node rootNode;
};

}

#endif
