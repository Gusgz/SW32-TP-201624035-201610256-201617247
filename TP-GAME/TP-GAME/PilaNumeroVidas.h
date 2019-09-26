#pragma once
#include<iostream>
using namespace std;
template<typename T>
class pilaNumeroVidas{
	struct Node {
		T elem;
		Node* next;
		Node(T elem, Node* next = nullptr) :elem(elem), next(next) {}
	};

	Node* _top;
	int len;
public:
	pilaNumeroVidas() :_top(nullptr), len(0) {}
	~pilaNumeroVidas() {
		while (_top != nullptr) {
			Node* aux = _top;
			_top = _top->next;
			delete aux;

		}
	}

	bool is_empty() {
		return _top == nullptr;
	}

	void pushVidas(T elem) {
		_top = new Node(elem, _top);
		len++;
	}
	void Show() {
		Node* aux = _top;
		for (int i = 0; i < len; i++) {
			cout << aux->elem << " ";
			aux = aux->next;
		}
		delete aux;
	}

	void popVidas() {
		if (!is_empty()) {
			Node* aux = _top;
			_top = _top->next;
			delete aux;
			len--;
		}
	}

	T topVidas() {
		if (!is_empty()) {
			return _top->elem;
		}
		return 0;
	}

	int tamaño() {
		return len;
	}

	void guardarNumeroVidas() {
		ofstream archivo("vidas.text");
		if (!archivo.is_open()) {
			cout << "no se pudo guardar en el archivo" << endl;
		}
		string linea;
		archivo << "Numero de vidas :";
		for (int i = 0; i < this->tamaño(); i++)
		{
			archivo << topVidas() << ",";
		}
		archivo.close();
	}

	void mostrarNumeroVidas() {
		ifstream archivo("vidas.text");
		if (!archivo.is_open()) {
			cout << "no se pudo abrir el archivo" << endl;
		}
		string linea;
		while (getline(archivo, linea,',')) {
			cout << linea ;
		}
	}



};
