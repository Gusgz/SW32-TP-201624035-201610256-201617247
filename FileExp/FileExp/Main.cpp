#include <iostream>
#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#include <experimental/filesystem>
#include "Tree.h"

using namespace std;
namespace fs = std::experimental::filesystem;
typedef Tree<fs::path, string> TreeStr;

int main()
{
	fs::path p("Test");
	auto compName = [](fs::path a) { return a.stem().string(); };
	TreeStr* nameTree = new TreeStr(compName);
	cout << "Agregando archivos al arbol..." << endl;
	for (const auto& entry : fs::directory_iterator(p)) {
		nameTree->add(entry.path());
	}
	cout << "Archivos agregados!" << endl;
	auto showName = [](fs::path a) {
		cout << "Nombre:\t " << a.stem().string() << endl;
	};
	cout << "------------------------------" << endl;
	cout << "Mostrando arbol" << endl;
	cout << "Path:\t" << p.string() << endl;
	nameTree->inorder(showName);
	cout << "------------------------------" << endl;

	std::cin.get();
	return 0;
}