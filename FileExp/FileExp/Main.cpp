#define _CRT_SECURE_NO_WARNINGS // N
#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING

#include <iostream>
#include <experimental/filesystem>
#include "AvLFileTree.h"
#include <time.h> // N
#include <sstream> // N
#include "File.h"

using namespace std;
using namespace std::experimental::filesystem;

typedef unsigned long ulong;

//typedef AVLFILETREE<string, string> TreeStr;
//typedef AVLFILETREE<ulong, ulong> TreeLong;






int main()
{
	typedef AVLFILETREE<File*, string, nullptr> TreeStr;
	typedef AVLFILETREE<File*, ulong, nullptr> TreeLong;



	// Lambda que compara los atributos para ingresarlos en el arbol
	auto compName = [](File* a) { return a->GetName(); };
	//auto compExtension = [](string e) {return e; };
	auto compSize = [](File* s) {return s->GetSize(); };
	//auto compDate = [](string d) {return d; };
	// Declaracion de los arboles y sus respectivas comparaciones
	TreeStr* nameTree = new TreeStr(compName);
	//TreeStr* extensionTree = new TreeStr(compExtension);
	TreeLong* sizeTree = new TreeLong(compSize);
	//TreeStr* dateTree = new TreeStr(compDate);
	// Busquedad de los archivos en una determinada ruta
	for (const auto& entry : recursive_directory_iterator("Test/folder")) {
		if (is_regular_file(entry.path()) || is_directory(entry.path())) {
			File* file = new File(entry.path());
			nameTree->add(file);
			sizeTree->add(file);
			//extensionTree->add(file->GetExtension());
			//dateTree->add(file->GetDate());
		}
	}
	// Lambda que muestra el valor indicado
	auto showName = [](File* a) { 
		if (a != nullptr) {
			cout << a->GetName() << endl;
		}
		else {
			cout << "not found " << endl;
		}
	
	};
	auto showSize = [](File* s) {//Lambda que muestra los tamaños de archivos
		if (s != nullptr) {
			cout <<s->GetSize()  << endl;
		}
		else {
			cout << "not found " << endl;
		}

	};
	// ---------- contiene palabra
	string textoContiene = "a";
	auto Contiene = [&](File* a) {
		if (a != nullptr) {
			size_t found = a->GetName().find(textoContiene);
			if (found != string::npos) {
				cout << a->GetName() << endl;
			}

		}
		else {
			cout << "Not found\n";
		}
	};
	// ---------- empieza palabra
	char textoEmpieza = 'V';
	auto EmpiezanCon = [&](File* a) {
		if (a != nullptr) {
			if (a->GetName().front() == textoEmpieza && a->GetName().front() != NULL) {
				cout << a->GetName() << endl;
			}
		}
		else {
			cout << "Not found\n";
		}
	};
	// ---------- finaliza palabra
	char Textofinaliza = 'a';
	auto FinalizaCon = [&](File* a) {
		if (a != nullptr) {
			if (a->GetName().back() == Textofinaliza)
				cout << a->GetName() << endl;
		}
		else
			cout << "Not found\n";
	};
	// ---------- busca tamaño
	long NumeroBuscar = 81;
	auto BuscarElem = [&](File* b) {
		if (b != nullptr) {
			if (b->GetSize() == NumeroBuscar) {
				cout << b->GetSize() << endl;
			}
		}
		else {
			cout << "Not found\n";
		}
	};



	//auto showExtension = [](string e) { cout << e << endl; };
	//auto showSize = [](ulong e) { cout << e << " bytes" << endl; };
	//auto showDate = [](string d) { cout << d << endl; };
	// Se muestra en consola
	cout << "------------------------------" << endl;
	cout << "Archivos:" << endl;
	nameTree->inorder(showName);
	cout << "------------------------------" << endl;
	cout << "Contiene la palabra [" << textoContiene <<"]"<< endl;
	nameTree->inorder(Contiene);
	cout << "------------------------------" << endl;
	cout << "Empieza con la letra [" << textoEmpieza << "]"<< endl;
	nameTree->inorder(EmpiezanCon);
	cout << "------------------------------" << endl;
	cout << "Finaliza con la letra [" << Textofinaliza << "]"<< endl;
	nameTree->inorder(FinalizaCon);
	cout << "------------------------------" << endl;


	/*cout << "Extension:" << endl;
	extensionTree->inorder(showExtension);
	cout << "------------------------------" << endl;
	*/


	// FUNCIONA---
	//cout << "Size:" << endl;
	//sizeTree->inorder(showSize);
	//
	//cout << "Elemento Mayor :" << sizeTree->ElemMayor()->GetSize(); cout << endl;
	//cout << "Elemento Menor :" << sizeTree->ElemMenor()->GetSize(); cout << endl;
	//cout << "Elementos a buscar :"<< endl;
	//sizeTree->BuscarElem(BuscarElem);
	// FUNCIONA---


	/*

	cout << "------------------------------" << endl;
	cout << "Date:" << endl;
	dateTree->inorder(showDate);
	cout << "------------------------------" << endl;*/
	cout << "Presione enter para finalizar el programa..." << endl;
	std::cin.get();
	return 0;
}