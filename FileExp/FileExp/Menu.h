#pragma once
#define _CRT_SECURE_NO_WARNINGS // N
#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#include <iostream>
#include "File.h"
#include "AvLFileTree.h"
#include <experimental/filesystem>
#include <functional>
#include <conio.h>

using namespace std;
using namespace std::experimental::filesystem;

typedef unsigned long ulong;
class Menu {
private: 
	path ruta;
public:
	typedef AVLFILETREE<File*, string, nullptr> TreeStr;
	typedef AVLFILETREE<File*, ulong, nullptr> TreeLong;
	void alo() {
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
		for (const auto& entry : recursive_directory_iterator(ruta)) {
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
				cout << s->GetSize() << endl;
			}
			else {
				cout << "not found " << endl;
			}

		};
		//// ---------- contiene palabra
		//string textoContiene = "a";
		//auto Contiene = [&](File* a) {
		//	if (a != nullptr) {
		//		size_t found = a->GetName().find(textoContiene);
		//		if (found != string::npos) {
		//			cout << a->GetName() << endl;
		//		}

		//	}
		//	else {
		//		cout << "Not found\n";
		//	}
		//};
		//// ---------- empieza palabra
		//char textoEmpieza = 'a';
		//auto EmpiezanCon = [&](File* a) {
		//	if (a != nullptr) {
		//		if (a->GetName().front() == textoEmpieza && a->GetName().front() != NULL) {
		//			cout << a->GetName() << endl;
		//		}
		//	}
		//	else {
		//		cout << "Not found\n";
		//	}
		//};
		//// ---------- finaliza palabra
		//char Textofinaliza = 'a';
		//auto FinalizaCon = [&](File* a) {
		//	if (a != nullptr) {
		//		if (a->GetName().back() == Textofinaliza && a->GetName().back() != NULL)
		//			cout << a->GetName() << endl;
		//	}
		//	else
		//		cout << "Not found\n";
		//};
		//// ---------- busca tamaño
		//long NumeroBuscar = 81;
		//auto BuscarElem = [&](File* b) {
		//	if (b != nullptr) {
		//		if (b->GetSize() == NumeroBuscar) {
		//			cout << b->GetSize() << endl;
		//		}
		//	}
		//	else {
		//		cout << "Not found\n";
		//	}
		//};



		//auto showExtension = [](string e) { cout << e << endl; };
		//auto showSize = [](ulong e) { cout << e << " bytes" << endl; };
		//auto showDate = [](string d) { cout << d << endl; };
		// Se muestra en consola
		cout << "------------------------------" << endl;
		cout << "Archivos:" << endl;
		nameTree->inorder(showName);
		cout << "------------------------------" << endl;
	/*	cout << "Contiene la palabra [" << textoContiene << "]" << endl;
		nameTree->inorder(Contiene);
		cout << "------------------------------" << endl;
		cout << "Empieza con la letra [" << textoEmpieza << "]" << endl;
		nameTree->inorder(EmpiezanCon);
		cout << "------------------------------" << endl;
		cout << "Finaliza con la letra [" << Textofinaliza << "]" << endl;
		nameTree->inorder(FinalizaCon);
		cout << "------------------------------" << endl;*/


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
	}

	
	void SeeMenu() {
		int numero;
		do {
			cout << "==============================="; cout << endl;
			cout << "------------MENU---------------"; cout << endl;
			cout << "==============================="; cout << endl;
			cout << endl;
			cout << "----------------------------------: "; cout << endl;
			cout << "Ingrese la ruta que desea analizar: "; cin >> ruta;
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
			if (exists(ruta)) {
				for (const auto& entry : recursive_directory_iterator(ruta)) {
					if (is_regular_file(entry.path()) || is_directory(entry.path())) {
						File* file = new File(entry.path());
						nameTree->add(file);
						sizeTree->add(file);
						//extensionTree->add(file->GetExtension());
						//dateTree->add(file->GetDate());
					}
				}
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
						cout << s->GetSize() << endl;
					}
					else {
						cout << "not found " << endl;
					}

				};

				do {
					cout << "----------------------------------------------------------------------------" << endl;
					cout << "Ingrese el tipo de arbol [1:Nombres|2:Tamanios|3:Extensiones|4:Extensiones]: "; cin >> numero;
					switch (numero) {
					case 1: {
						cout << "++++++++++++++" << endl;
						cout << "Archivos:" << endl;
						nameTree->inorder(showName);
						cout << "\n*******************" << endl;
						int num;
						do{
						cout << "[1:Empieza Con|2:Contiene|3:Finaliza Con ]: "; cin >> num;

						switch (num) {
						case 1: {
							char textoEmpieza;	
							cout << "\n----------------------------------------"; cout << endl;
							cout << "Ingrese la letra inicial del archivo: "; cin >> textoEmpieza;
							
							
							auto EmpiezanCon = [&](File* a) {
								if (a != nullptr) {
									if (a->GetName().front() == toupper(textoEmpieza) || a->GetName().front() == tolower(textoEmpieza) && a->GetName().front() != NULL) {
										cout << a->GetName() << endl;
									}
								}
								else {
									cout << "Not found\n";
								}
							};
							cout << "\nArchivos que empiezan con la letra [" << textoEmpieza << "]" << endl;
							nameTree->inorder(EmpiezanCon);
						}break;
						case 2: {
							string textoContiene;
							cout << "\n----------------------------------------"; cout << endl;
							cout << "Ingrese una palabra cualquiera: "; cin >> textoContiene;

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
							cout << "Contiene la palabra [" << textoContiene << "]" << endl;
							nameTree->inorder(Contiene);
						}break;
						case 3: {
							char Textofinaliza;
							cout << "\n----------------------------------------"; cout << endl;
							cout << "Ingrese la letra final del archivo: "; cin >> Textofinaliza;

							auto FinalizaCon = [&](File* a) {
								if (a != nullptr) {
									if (a->GetName().back() == toupper(Textofinaliza) || a->GetName().back() == tolower(Textofinaliza) && a->GetName().back() != NULL)
										cout << a->GetName() << endl;
								}
								else
									cout << "Not found\n";
							};
							cout << "Finaliza con la letra [" << Textofinaliza << "]" << endl;
							nameTree->inorder(FinalizaCon);

						}break;
					
						}
					} while (num != 1 || num != 2 || numero != 3);

					} break;
					case 2: {
				 		cout << "++++++++++++" << endl;
						cout << "Size:" << endl;
						sizeTree->inorder(showSize);
						cout << "\n------------------------" << endl;
						cout << "El mayor tamanio es :" << sizeTree->ElemMayor()->GetSize(); cout << endl;
						cout << "El menor tamanio es :" << sizeTree->ElemMenor()->GetSize(); cout << endl;
						long NumeroBuscar;
						cout << "\n------------------------" << endl;
						cout << "Tamanio a buscar en bytes :"; cin >> NumeroBuscar;
						auto BuscarElem = [&](File* b) {
							if (b != nullptr) {
								if (b->GetSize() == NumeroBuscar) {
									cout << b->GetName() << endl;
								}
							}
							else {
								cout << "Not found\n";
							}
						};
						sizeTree->BuscarElem(BuscarElem);
					} break;

					case 3: {

					}break;

					case 4: {

					}break;
					}
				} while (numero != 1 || numero != 2 || numero != 3);
			}
			else {
				cout << "No existe la ruta especificada";
				cout << endl;
				_getch();
				system("cls");
				SeeMenu();
			}
			
			
			
		} while (ruta!="/");

	}

};
