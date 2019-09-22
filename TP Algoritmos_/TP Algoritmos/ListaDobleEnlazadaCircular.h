#pragma once
#include<iostream>
#include<functional>
using namespace std;
typedef unsigned int uint;



template<typename T>
class ListaDoblementeEnlazadaPrtIni {
	struct Node {
		T elem;
		Node* siguiente;
		Node(T elem) :elem(elem), siguiente(nullptr) {}

	};
	Node* ini;
	Node* fin;
	uint tama�o;

public:
	class iterator {
		unsigned int    pos;
		Node* aux;
	public:
		iterator(unsigned int pos, Node* aux) : pos(pos), aux(aux) {}
		int begin() {
			return this->ini;
		}
		int end() {
			return this->fin;
		}
		void operator ++() { pos++; aux = aux->sig; }
		bool operator !=(iterator x) { return pos != x.pos; }
		int    operator  *() { return aux->elem; }
	};

	ListaDoblementeEnlazadaPrtIni() :ini(nullptr), fin(nullptr), tama�o(0) {}
	~ListaDoblementeEnlazadaPrtIni() {
		Node* aux = ini;
		while (ini != nullptr) {
			aux = ini;
			ini = ini->siguiente;
			delete aux;
		}
	}

	void insercionLista(T elem) {
		Node* nuevo = new Node(elem);
		if (ini == nullptr) {
			nuevo->siguiente = nuevo;
			ini = nuevo;
			fin = nuevo;
			tama�o++;
		}
		else {
			fin->siguiente = nuevo;
			nuevo->siguiente = ini;
			fin = nuevo;
			tama�o++;
		}
	}

	int tama�oLista() {
		return this->tama�o;
	}



	void eliminacionListaInicio() {
		Node* actual = ini;
		if (tama�o > 1) {
			actual = ini;
			ini = ini->siguiente;
			fin->siguiente = ini;
			tama�o--;
		}
		else {
			actual = ini;
			ini = nullptr;
			fin = nullptr;
			delete actual;
			tama�o--;
		}

	}

	void mostrarLista() {

		Node* actual = ini;
		int i;
		for (i = 0; i < this->tama�o; i++) {
			cout << actual->elem << " ";
			actual = actual->siguiente;

		}

	}

	void buscarElemento(T elem) {
		Node* aux = ini;
		for (int i = 0; i < this->tama�o; i++) {
			aux = aux->siguiente;
			if (aux->elem == elem)
				cout << aux->elem << endl;
		}
	}
};


