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
	typedef AVLFILETREE<File*, ulong,nullptr> TreeLong;
	


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
	for (const auto& entry : recursive_directory_iterator("Test")) {
		File* file = new File(entry.path());
		nameTree->add(file);
		//extensionTree->add(file->GetExtension());
		sizeTree->add(file);
		//dateTree->add(file->GetDate());
		
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




	string textoContiene = "texto";// hallando el elemnto contiene
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

	char textoEmpieza = 's';//Hllando el elemnto empieza con
	auto EmpiezanCon = [&](File* a) {
		if (a != nullptr) {

			if (a->GetName().front() == textoEmpieza) {
				cout << a->GetName() << endl;
			}

		}
		else {
			cout << "Not found\n";
		}
	};

	char Textofinaliza = 's';//Hallando elemnto finaliza con 
	auto FinalizaCon = [&](File* a) {
		if (a != nullptr) {

			if (a->GetName().back() == Textofinaliza) {
				cout << a->GetName() << endl;
			}

		}
		else {
			cout << "Not found\n";
		}
	};

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
	cout << "Name:" << endl;
	nameTree->inorder(showName);
	cout << "------------------------------" << endl;
	nameTree->inorder(Contiene);
	cout << "------------------------------" << endl;
	nameTree->inorder(EmpiezanCon);
	cout << "------------------------------" << endl;
	nameTree->inorder(FinalizaCon);
	cout << "------------------------------" << endl;
	/*cout << "Extension:" << endl;
	extensionTree->inorder(showExtension);
	cout << "------------------------------" << endl;
	*/
	cout << "Size:" << endl;
	sizeTree->inorder(showSize);
	
	cout << "Elemento Mayor :" << sizeTree->ElemMayor()->GetSize(); cout << endl;
	cout << "Elemento Menor :" << sizeTree->ElemMenor()->GetSize(); cout << endl;
	cout << "Elementos a buscar :"<< endl;
	sizeTree->BuscarElem(BuscarElem);
	/*
	cout << "------------------------------" << endl;
	cout << "Date:" << endl;
	dateTree->inorder(showDate);
	cout << "------------------------------" << endl;*/
	std::cin.get();
	return 0;
}