#define _CRT_SECURE_NO_WARNINGS // N
#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING

#include <iostream>
#include <experimental/filesystem>
#include "Tree.h"
#include <time.h> // N
#include <sstream> // N
#include "File.h"

using namespace std;
using namespace std::experimental::filesystem;

typedef unsigned long ulong;

typedef Tree<string, string> TreeStr;
typedef Tree<ulong, ulong> TreeLong;


int main()
{
	// Lambda que compara los atributos para ingresarlos en el arbol
	auto compName = [](string a) { return a; };
	auto compExtension = [](string e) {return e; };
	auto compSize = [](ulong s) {return s; };
	auto compDate = [](string d) {return d; };
	// Declaracion de los arboles y sus respectivas comparaciones
	TreeStr* nameTree = new TreeStr(compName);
	TreeStr* extensionTree = new TreeStr(compExtension);
	TreeLong* sizeTree = new TreeLong(compSize);
	TreeStr* dateTree = new TreeStr(compDate);
	// Busquedad de los archivos en una determinada ruta
	for (const auto& entry : recursive_directory_iterator("Test")) {
		File* file = new File(entry.path());
		nameTree->add(file->GetName());
		extensionTree->add(file->GetExtension());
		sizeTree->add(file->GetSize());
		dateTree->add(file->GetDate());
		delete file;
	}
	// Lambda que muestra el valor indicado
	auto showName = [](string a) { cout << a << endl; };
	auto showExtension = [](string e) { cout << e << endl; };
	auto showSize = [](ulong e) { cout << e << " bytes" << endl; };
	auto showDate = [](string d) { cout << d << endl; };
	// Se muestra en consola
	cout << "Name:" << endl;
	nameTree->inorder(showName);
	cout << "------------------------------" << endl;
	cout << "Extension:" << endl;
	extensionTree->inorder(showExtension);
	cout << "------------------------------" << endl;
	cout << "Size:" << endl;
	sizeTree->inorder(showSize);
	cout << "------------------------------" << endl;
	cout << "Date:" << endl;
	dateTree->inorder(showDate);
	cout << "------------------------------" << endl;
	std::cin.get();
	return 0;
}