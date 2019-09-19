#pragma once
#include <iostream>
#include "Design.h"
template<typename T>
class ListCircle {
private:
	struct Node
	{
		T* element;
		Node* next;
		Node(T* element = NULL, Node * next = nullptr) :element(element), next(next) {}
	};
	Node* init;
	Node* fin;
	int length;
public:
	ListCircle() :init(nullptr), fin(nullptr), length(0) {}
	~ListCircle();

	bool IsEmpty() { return length == 0; }
	void AddFirst(T* element) {
		Node* aux = new Node(element, init);
		if (IsEmpty()) {
			fin = aux;
		}
		init = aux;
		fin->next = init;
		length++;
	}
	void AddEnd(int element) {
		Node* aux = new Node(element);
	}
	void SeeList(Design* d) {
		Node* aux = init;
		for (int i = 0; i < length; i++) {
			d->Gotoxy(0,25);
			std::cout << aux->element->GetFigure() << " | ";
			aux = aux->next;
		}
	}
	T GetInit() { return init->element; }
	T GetFin() { return fin->element; }
};