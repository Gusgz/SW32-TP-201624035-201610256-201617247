#pragma once
#include<iostream>
#include<functional>
using namespace std;
typedef unsigned int uint;



class Enemigo {
	int x;
	int y;
public:
	Enemigo() :x(0), y(0) {}
	int gey_x() {
		return this->x;
	}
};



template<typename T>
class ListaDoblementeEnlazadaPiniPfin {
	struct Node {
		T elem;
		Node* siguiente;
		Node(T elem) :elem(elem), siguiente(nullptr) {}

	};
	Node* ini;
	Node* fin;
	uint tamaño;

	typedef function<int(T, T)> Comp;
	Comp comparar;
public:
	ListaDoblementeEnlazadaPiniPfin() :ini(nullptr), fin(nullptr), tamaño(0), comparar([](T a, T b) {return a - b; }) {}

	~ListaDoblementeEnlazadaPiniPfin() {
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
		return Iterator(tamaño, nullptr);
	}



	void insercionLista(T elem) {
		Node* nuevo = new Node(elem);
		if (ini == nullptr) {
			nuevo->siguiente = nuevo;
			ini = nuevo;
			fin = nuevo;
			tamaño++;
		}
		else {
			fin->siguiente = nuevo;
			nuevo->siguiente = ini;
			fin = nuevo;
			tamaño++;
		}
	}

	int tamañoLista() {
		return this->tamaño;
	}



	void eliminacionListaInicio() {
		Node* actual = ini;
		if (tamaño > 1) {
			actual = ini;
			ini = ini->siguiente;
			fin->siguiente = ini;
			tamaño--;
		}
		else {
			actual = ini;
			ini = nullptr;
			fin = nullptr;
			delete actual;
			tamaño--;
		}

	}

	void mostrarLista(ListaDoblementeEnlazadaPiniPfin<int>* elementos) {
		ListaDoblementeEnlazadaPiniPfin<int>::Iterator it;
		for (it = elementos->begin(); it != elementos->end(); ++it) {
			cout << *it << " ";
		}


		/*

		Node* actual = ini;
		int i;
		for (i = 0; i < this->tamaño; i++) {
			cout << actual->elem << " ";
			actual = actual->siguiente;

		}*/

	}

	T buscarElemento(T elem) {
		Node* aux = ini;
		for (int i = 0; i < this->tamaño; i++) {
			aux = aux->siguiente;
			if (comparar(aux->elem, elem) == 0)
				return aux->elem; cout << endl;
		}
	}

	T buscarElemIterador(T elem) {
		ListaDoblementeEnlazadaPiniPfin<int>::Iterator it;
		for (it = begin(); it != end(); ++it) {
			if (comparar(*it, elem) == 0) {
				return *it;
			}
		}
	}

};






