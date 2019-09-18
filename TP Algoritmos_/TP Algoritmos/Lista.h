#pragma once

#include "Character.h"
#include <iostream>
using namespace std;

class ListaCharacters {
	struct Node {
		Character* f;
		Node* next;
		Node(Character* f, Node* next = nullptr) :f(f), next(next) {}
	};

	Node* head;
	int len;
public:	ListaCharacters() : head(nullptr), len(0) {}
		~ListaCharacters() {
			while (head != nullptr) {
				Node* aux = head;
				head = head->next;
				delete aux;
			}
		}
		bool IsEmpty() {
			return len == 0;
		}
		int Size() {
			return len;
		}
		void setSize(int size) {
			len = size;
		}
		void AddEnemy(Character* f) {
			head = new Node(f, head);
			len++;
		}
		void SeeList() {

			Node* aux = head;
			for (int i = 0; i < len; ++i) {
				cout << aux->f->getfigure() << " ";
				aux = aux->next;
			}
		}

};


