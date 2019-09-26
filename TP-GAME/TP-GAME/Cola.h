#pragma once
#include <iostream>
template <typename T>
class Cola {
private:
	struct Node {
		T* element;
		Node* next;
		Node(T* element = nullptr, Node* next = nullptr) :element(element), next(next){}
	};
	Node* head;
	Node* tail;
	int lenght;
	int max_lenght;
public:
	Cola(Node* head = nullptr, Node* tail = nullptr, int lenght = 0,int max_lenght = 50) :head(head), tail(tail), lenght(0), max_lenght(50){}
	~Cola() {
		while (head != nullptr) {
			Node* aux = head;
			head = head->next;
			delete aux;
		}
	}
	bool IsEmpty() {return lenght == 0;}
	bool IsFull() {
		return lenght == max_lenght;
	}
	void Enqueue(T* element) {
		if (!IsFull()) {
			Node* aux = new Node(element, nullptr);
			if (IsEmpty()) {
				head = aux;
				tail = aux;
			}
			else {
				tail->next = aux;
				tail = aux;
			}
			lenght++;
		}
	}
	T* Dequeue() {
		if (!IsEmpty()){
			Node* aux = head;
			head = head->next;
			lenght--;
			return aux->element;
		}
	}
	T* GetElementPos(int pos) {
		Node* aux = head;
		for (int i = 0; i < pos; i++) {
			aux = aux->next;
		}
		return aux->element;
	}
	void Show() {
		Node* aux = head;
		for (int i = 0; i < lenght; i++) {
			std::cout << aux->element->GetFigure() << " ";
			aux = aux->next;
		}
	}
	int Size() { 
		return lenght; 
	}
	void SetMaxLength(int max_lenght) {
		this->max_lenght = max_lenght;
	}
	int GetMaxLength() { return max_lenght; };
};