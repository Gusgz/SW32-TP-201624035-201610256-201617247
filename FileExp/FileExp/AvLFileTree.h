#pragma once
#include <functional>

#define max(a, b) ( a > b? a : b )
typedef unsigned int uint;
typedef unsigned long ulong;

using namespace std;



template <typename T, typename Comparable = T, T NONE = 0>
class AVLFILETREE {
	struct Node {
		T elem;
		int   h;
		int   n;
		Node* left;
		Node* right;

		Node(T elem)
			: elem(elem), left(nullptr), right(nullptr), h(0), n(1) {}
	};

	Node* root;
	int len;
	function<Comparable(T)> key;



	void DestruccionNod(Node* node) {
		if (node != nullptr) {
			DestruccionNod(node->left);
			DestruccionNod(node->right);
			delete node;
		}
	}
	Node* add(Node* node, T elem) {
		if (node == nullptr) {
			node = new Node(elem);

		}
		else {
			if (key(elem) < key(node->elem)) {
				node->left = add(node->left, elem);


			}
			else {
				node->right = add(node->right, elem);

			}
			node = balance(node);
		}
		return node;
	}
	//Buscando Elemento menor del arbol
	T ElemMen(Node* auxmenor) {
		T menor;
		while (auxmenor->left != nullptr) {
			auxmenor = auxmenor->left;
			menor = auxmenor->elem;
			return menor;
		}

	}

	//Buscando Elemento mayor del arbol
	T ElemMay(Node* auxmayor) {
		T mayor;
		while (auxmayor->right != nullptr) {
			auxmayor = auxmayor->right;
			mayor = auxmayor->elem;
			return mayor;
		}
		
	}


	//Buscando Elemento igual a
	T find(Node* node, Comparable val) {
		if (node == nullptr) {
			return NONE;
		}
		else if (val == key(node->elem)) {
			return node->elem;
		}
		else if (val < key(node->elem)) {
			return find(node->left, val);
		}
		else {
			return find(node->right, val);
		}
	}



	//buscador de palabra 
	T buscar(Node* node, Comparable val) {
		size_t found = key(node->elem).find(val);
		if (node == nullptr) {
			return NONE;
		}

		else if (found != string::npos) {
			return node->elem;
		}
		else if (val < key(node->elem)) {
			return buscar(node->left, val);
		}
		else {
			return buscar(node->right, val);
		}


	}





	void inorder(Node* node, function<void(T)> proc) {
		if (node != nullptr) {
			inorder(node->left, proc);
			proc(node->elem);
			inorder(node->right, proc);
		}
	}




	// BALANCEO!
	int height(Node* node) { return node == nullptr ? -1 : node->h; }
	int length(Node* node) { return node == nullptr ? 0 : node->n; }
	void update(Node* node) {
		node->h = 1 + max(height(node->left), height(node->right));
		node->n = 1 + length(node->left) + length(node->right);
	}
	Node* rotLeft(Node* node) {
		Node* aux = node->right;
		node->right = aux->left;
		aux->left = node;
		update(aux->left);
		update(aux);
		return aux;
	}
	Node* rotRight(Node* node) {
		Node* aux = node->left;
		node->left = aux->right;
		aux->right = node;
		update(aux->right);
		update(aux);
		return aux;
	}
	Node* balance(Node* node) {
		int hl = height(node->left);
		int hr = height(node->right);
		if (hl - hr > 1) {
			if (height(node->left->right) > height(node->left->left)) {
				node->left = rotLeft(node->left);
			}
			node = rotRight(node);
		}
		else if (hl - hr < -1) {
			if (height(node->right->left) > height(node->right->right)) {
				node->right = rotRight(node->right);
			}
			node = rotLeft(node);
		}
		else {
			update(node);
		}
		return node;
	}

public:
	AVLFILETREE(function<Comparable(T)> key = [](T a) {return a; })
		: root(nullptr), len(0), key(key) {}
	~AVLFILETREE() {
		DestruccionNod(root);
	}
	int height() {
		return height(root);
	}
	int size() {
		return length(root);
	}
	void add(T elem) {
		root = add(root, elem);
	}



	//Buscando Palabra igual a
	T find(Comparable val) {
		return find(root, val);
	}


	//Menor Valor
	T ElemMenor() {
		return ElemMen(root);
	}

	//Mayor Valor
	T ElemMayor() {
		 return ElemMay(root);
	}

	// Mostrando
	void inorder(function<void(T)> proc) {
		inorder(root, proc);
	}





};


