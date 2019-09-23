#pragma once
#include<iostream>
#include<functional>
using namespace std;
typedef unsigned int uint;

template<typename T>
class ListaSimplementeEnlazadaCircularPrtIniPrtFin {
	struct Node {
		T elem;
		Node* siguiente;
		Node(T elem) :elem(elem), siguiente(nullptr) {}

	};
	Node* ini;
	Node* fin;
	uint tama�o;

public:
	ListaSimplementeEnlazadaCircularPrtIniPrtFin() :ini(nullptr), fin(nullptr), tama�o(0) {}
	~ListaSimplementeEnlazadaCircularPrtIniPrtFin() {
		Node* aux = ini;
		while (ini != nullptr) {
			aux = ini;
			ini = ini->siguiente;
			delete aux;
		}
	}

	class Iterator {
		unsigned int    pos;
		Node* aux;
	public:
		Iterator() :pos(0), aux(nullptr) {}
		Iterator(unsigned int pos, Node* aux = nullptr) : pos(pos), aux(aux) {}
		void operator ++() { pos++; aux = aux->siguiente; }
		bool operator !=(Iterator x) { return pos != x.pos; }
		T    operator  *() { return aux->elem; }
	};

	Iterator begin() {
		return Iterator(0, ini);
	}
	Iterator end() {
		return Iterator(tama�o, nullptr);
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

	void mostrarLista(ListaSimplementeEnlazadaCircularPrtIniPrtFin<int>* elementos) {
		ListaSimplementeEnlazadaCircularPrtIniPrtFin<int>::Iterator it;
		for (it = elementos->begin(); it != elementos->end(); ++it) {
			cout << *it << " ";
		}


		/*

		Node* actual = ini;
		int i;
		for (i = 0; i < this->tama�o; i++) {
			cout << actual->elem << " ";
			actual = actual->siguiente;

		}*/

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
