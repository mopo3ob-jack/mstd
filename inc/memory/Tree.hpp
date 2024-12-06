#include "allocator.hpp"

namespace mstd {

template <typename T, Size degree>
class Tree {
public:
	Tree() {
		alloc(nodes, 1);
		nodeCount = 1;
		nodeCapacity = 1;
	}

	~Tree() {
		if (nodes) {
			free(nodes);
			nodes = nullptr;
			nodeCount = 0;
			nodeCapacity = 0;
		}
	}

	Tree(Tree&& tree) {
		this->operator=(tree);
	}

	Tree&& operator=(Tree&& tree) {
		this->~Tree();

		this->nodes = tree.nodes;
		this->nodeCount = tree.nodeCount;
		this->nodeCapacity = tree.nodeCapacity;

		tree.nodes = nullptr;
		tree.nodeCount = 0;
		tree.nodeCapacity = 0;
	}

	Tree(Tree&) = delete;
	Tree& operator=(Tree& tree) = delete;

	struct Node {
		union {
			T leaves[degree];
			Node* nodes[degree];
		};
	};

	Node* root() const {
		return nodes;
	}

	void addChildren(Node* node) {
		nodeCount += degree;

		for (Size i = 0; i < degree; ++i) {
			node->nodes[i] = nodes + nodeCapacity + i; 
		}

		if (nodeCount > nodeCapacity) {
			nodeCapacity += degree * degree;
			realloc(nodes, nodeCapacity);
		}
	}

	Size size() const {
		return nodeCount;
	}

	void reserve(Size size) {
		nodeCapacity += size;
		realloc(nodes, nodeCapacity);
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
class BinaryTree : public Tree<T, 2> {};

template <typename T>
class Quadtree : public Tree<T, 4> {};

template <typename T>
class Octree : public Tree<T, 8> {};

}
