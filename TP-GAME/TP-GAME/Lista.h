#pragma once
#include <functional>
using namespace std;
typedef unsigned int uint;
template <typename T>
class Lista {
	struct Nodo;
	typedef function<int(T*, T*)> Comp;
	Nodo* ini;
	uint lon;
	Comp comparar;
public:
	Lista() : ini(nullptr), lon(0), comparar([](T* a, T* b) {return a - b; }) {}
	Lista(Comp comparar) : ini(nullptr), lon(0), comparar(comparar) {}
	~Lista() {
		Nodo* aux = ini;
		while (aux != nullptr) {
			aux = ini;
			ini = ini->sig;
			delete aux;
		}
	}
	uint longitud() { return lon; }
	bool esVacia() { return lon == 0; }
	void agregaInicial(T* elem) {
		Nodo* nuevo = new Nodo(elem, ini);
		if (nuevo != nullptr) {
			ini = nuevo;
			lon++;
		}
	}
	void agregaPos(T elem, uint pos);
	void agregaFinal(T elem);
	void modificarInicial(T elem);
	void modificarPos(T elem, uint pos);
	void modificarFinal(T elem);
	void eliminaInicial() {
		Nodo* aux = ini;
		ini = aux->sig;
		delete aux;
	}
	void eliminaPos(uint pos);
	void eliminaFinal() {
		Nodo* iterador = ini;
		Nodo* fin;
		for (int i = 0; i < lon - 1; i++) {
			iterador = iterador->sig;
		}
		fin = iterador->sig;
		delete fin;
	}
	T obtenerInicial();
	T* obtenerPos(uint pos) {
		if (pos >= 0 && pos < lon) {
			Nodo* aux = ini;
			for (int i = 0; i < pos; i++) {
				aux = aux->sig;
			}
			return aux->elem;
		}
		else {
			return nullptr;
		}
	}
	T obtenerFinal();
	T buscar(T elem);
};
// Nodo
template <typename T>
struct Lista<T>::Nodo {
	T* elem;
	Nodo* sig;
	Nodo(T* elem = nullptr, Nodo* sig = nullptr) : elem(elem), sig(sig) {}
};