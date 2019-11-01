#pragma once
#include <functional>
template <typename T, typename Comparable = T>
class Tree {
private:
	struct Node {
		T element;
		Node* left;
		Node* right;
		Node(T element = 0) :element(element), left(nullptr), right(nullptr) {}
	};
	Node* root;
	std::function<Comparable(T)> key;
	// -------------------- ELIMINAR ARBOL
	void destroy(Node* node) {
		if (node != nullptr) {
			destroy(node->left);
			destroy(node->right);
			delete node;
		}
	}
	// -------------------- add private
	Node* add(Node* node, T element) {
		if (node == nullptr)
			node = new Node(element);
		else {
			if (key(element) < key(node->element))
				node->left = add(node->left, element);
			else
				node->right = add(node->right, element);
		}
		return node;
	}
	// -------------------- inorder private
	void inorder(Node* node, std::function<void(T)> proc) {
		if (node != nullptr) {
			inorder(node->left, proc);
			proc(node->element);
			inorder(node->right, proc);
		}
	}
public:
	Tree(std::function<Comparable(T)> key = [](T a) {return a; }) : root(nullptr), key(key) {}
	~Tree() { destroy(root); }
	// -------------------- add public
	void add(T element) {
		root = add(root, element);
	}
	// -------------------- inorder public
	void inorder(std::function<void(T)> proc) {
		inorder(root, proc);
	}

};
