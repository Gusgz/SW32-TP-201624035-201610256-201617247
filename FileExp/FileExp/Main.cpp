#include <iostream>
#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#include <experimental/filesystem>
#include "Tree.h"

using namespace std;
using namespace std::experimental::filesystem;

typedef unsigned long ulong;

typedef Tree<path, string> TreeStr;
typedef Tree<path, ulong> TreeInt;

int main()
{
	path p = current_path();//devuelve ruta actual
	auto compName = [](path a) { return a.stem().string(); };//Devuelve el nombre
	auto compExtension = [](path e) {return e.extension().string(); };//Devuelve la extension
	auto compSize = [](path s) {return file_size(s); };//Devuelve el tamaño
	TreeStr* nameTree = new TreeStr(compName);//Arbol de nombre
	TreeStr* extensionTree = new TreeStr(compExtension);//Arbol de extension
	TreeInt* sizeTree = new TreeInt(compSize);//Arbol de tamaño
	cout << "Agregando archivos al arbol..." << endl;
	for (const auto& entry : directory_iterator("Test")) {
		nameTree->add(entry.path());//archivos de Test agregandolos al arbol(nombres)
	}
	for (const auto& entry : directory_iterator("Test")) {
		extensionTree->add(entry.path());//archivos de Test agregandolos al arbol(extensiones)
	}
	for (const auto& entry : directory_iterator("Test")) {
		sizeTree->add(entry.path());//archivos de Test agregandolos al arbol(extensiones)
	}
	cout << "Archivos agregados!" << endl;
	auto showName = [](path a) {
		cout << "Nombre\t " << a.stem().string() << endl;
	};
	auto showExtension = [](path e) {
		cout << "Extension\t " << e.extension().string() << endl;
	};
	auto showSize = [](path e) {
		cout << "Tamanio\t " << file_size(e) << endl;
	};
	cout << "Mostrando arbol(Nombres):" << endl;
	nameTree->inorder(showName);
	cout << "------------------------------" << endl;

	cout << endl;
	cout << "Mostrando arbol(Extensiones):" << endl;
	nameTree->inorder(showExtension);
	cout << "------------------------------" << endl;

	cout << endl;
	cout << "Mostrando arbol(Tamanios):" << endl;
	nameTree->inorder(showSize);
	cout << "------------------------------" << endl;
	std::cin.get();
	return 0;
}