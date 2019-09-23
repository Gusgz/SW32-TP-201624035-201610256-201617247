#pragma once
using namespace std;
typedef unsigned int uint;

template<typename T>
class ListaDoblementeEnlazadaPtrIniPrtFin {
	struct Node {
		T elem;
		Node* siguiente;
		Node* anterior;
		Node(T elem, Node* siguiente = nullptr, Node* anterior = nullptr) :elem(elem), siguiente(siguiente), anterior(anterior) {}
	};
	Node* ini;
	Node* fin;
	uint tamaño;
public:
	ListaDoblementeEnlazadaPtrIniPrtFin() :ini(nullptr), fin(nullptr), tamaño(0) {}
	~ListaDoblementeEnlazadaPtrIniPrtFin() {
		Node* aux = ini;
		while (ini != nullptr) {
			aux = ini;
			ini = ini->siguiente;
			delete aux;
		}
	}

	class Iterador {
		unsigned int pos;
		Node* aux;
	public:
		Iterador() :pos(0), aux(nullptr) {}
		Iterador(unsigned int pos, Node* aux) :pos(pos), aux(aux) {}

	};

	Iterador begin() {
		return Iterador();
	}


	void insertar(T elem) {
		Node* nuevo;

		if (ini == nullptr) {
			nuevo = new Node(elem);
			nuevo->anterior = ini;
			nuevo->siguiente = fin;
			ini = nuevo;
			fin = nuevo;
			tamaño++;
		}
		else {
			nuevo = new Node(elem);
			nuevo->siguiente = nullptr;
			nuevo->anterior = fin;
			fin->siguiente = nuevo;
			fin = nuevo;
			tamaño++;

		}
	}

	void mostrar() {
		Node* actual = ini;
		int i;
		for (i = 0; i < this->tamaño; i++) {
			cout << actual->elem << " ";
			actual = actual->siguiente;
		}
	}

	void buscarhaciaDerecha(T elem) {
		Node* aux = ini;
		for (aux = ini; aux != nullptr; aux = aux->siguiente) {
			if (aux->elem == elem) {
				cout << aux->elem << endl;
			}
		}
		return;

	}
	void buscarhaciaIzquierda(T elem) {
		Node* aux = fin;
		for (aux = fin; aux != nullptr; aux = aux->anterior) {
			if (aux->elem == elem) {
				cout << aux->elem << endl;
			}
		}
		return;
	}



};
