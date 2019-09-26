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

	void push(T elem) {
		_top = new Node(elem, _top);
		++len;
	}
	void Show() {
		Node* aux = _top;
		for (int i = 0; i < tamaño(); i++) {
			cout << aux->elem << " ";
			aux= aux->next;
		}
	}

	void pop() {
		if (!is_empty()) {
			Node* aux = _top;
			_top = _top->next;
			delete aux;
			--len;
		}
	}

	T top() {
		if (!is_empty()) {
			return _top->elem;
		}
		return 0;
	}

	int tamaño() {
		return this->len;
	}

	void guardarNumeroVidas() {
		ofstream archivo("vidas.text");
		if (!archivo.is_open()) {
			cout << "no se pudo guardar en el archivo" << endl;
		}
		string linea;
		for(int i=0;i<this->tamaño();i++)
		archivo << "Numero de vidas : "<<top()<<",";
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
