#ifndef MSTD_ARENATREE_HPP
#define MSTD_ARENATREE_HPP

#include "Arena.hpp"

namespace mstd {

template <typename T, Size degree>
class ArenaTree {
public:
	ArenaTree(Arena& arena) {
		nodes = arena.reserve<Node>(1);
		nodeCount = 1;
		nodeCapacity = 1;
	}

	~ArenaTree() {
		if (nodes) {
			nodes = nullptr;
			nodeCount = 0;
			nodeCapacity = 0;
		}
	}

	ArenaTree(ArenaTree&& tree) {
		this->operator=(tree);
	}

	ArenaTree&& operator=(ArenaTree&& tree) {
		this->~Tree();

		this->nodes = tree.nodes;
		this->nodeCount = tree.nodeCount;
		this->nodeCapacity = tree.nodeCapacity;

		tree.nodes = nullptr;
		tree.nodeCount = 0;
		tree.nodeCapacity = 0;
	}

	ArenaTree(ArenaTree&) = delete;
	ArenaTree& operator=(ArenaTree& tree) = delete;

	struct Node {
		union {
			T leaves[degree];
			Node* nodes[degree];
		};
	};

	Node* root() const {
		return nodes;
	}

	void addChildren(Node* node, Arena& arena) {
		nodeCount += degree;

		for (Size i = 0; i < degree; ++i) {
			node->nodes[i] = nodes + nodeCapacity + i; 
		}

		if (nodeCount > nodeCapacity) {
			nodeCapacity += degree * degree;
			arena.reserve<Node>(degree * degree);
		}
	}

	Size size() const {
		return nodeCount;
	}

	void reserve(Size size, Arena& arena) {
		nodeCapacity += size;
		arena.reserve<Node>(size);
	}

	Size capacity() const {
		return nodeCapacity;
	}

private:
	Node* nodes;
	Size nodeCount;
	Size nodeCapacity;
};

template <typename T>
class ArenaBinaryTree : public ArenaTree<T, 2> {};

template <typename T>
class ArenaQuadtree : public ArenaTree<T, 4> {};

template <typename T>
class ArenaOctree : public ArenaTree<T, 8> {};

}

#endif
