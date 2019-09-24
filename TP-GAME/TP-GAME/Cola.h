#pragma once
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
public:
	Cola(Node* head = nullptr, Node* tail = nullptr, int lenght = 0) :head(head), tail(tail), lenght(0) {}
	~Cola() {
		while (head != nullptr) {
			Node* aux = head;
			head = head->next;
			delete aux;
		}
	}
	bool IsEmpty() {return lenght == 0;}
	void Enqueue(T* element) {
		Node* aux = new Node(element,nullptr);
		if (IsEmpty()){
			head = aux;
			tail = aux;
		}
		else {
			tail->next = aux;
			tail = aux;
		}
		lenght++;
	}
	T* Dequeue() {
		if (IsEmpty())
			return NULL;
		else {
			Node* aux = head;
			head = head->next;
			lenght--;
			return aux->element;
		}
	}
	void Show() {
		Node* aux = head;
		for (int i = 0; i < lenght; i++) {
			std::cout << aux->element << "|";
			aux = aux->next;
		}
	}
	int Size() { return lenght; }
};