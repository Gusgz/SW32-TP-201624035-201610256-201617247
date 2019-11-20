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
	typedef AVLFILETREE<File*, char, nullptr> TreeChr;
	typedef AVLFILETREE<File*, ulong, nullptr> TreeLong;
	
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
			auto compExtension = [](File* e) {return e->GetExtension(); };
			auto compSize = [](File* s) {return s->GetSize(); };
			auto compDate = [](File* d) {return d->GetDate(); };

			auto compNameFin = [](File* a) { return a->GetName().back(); };
			// Declaracion de los arboles y sus respectivas comparaciones
			TreeStr* nameTree = new TreeStr(compName);
			TreeStr* extensionTree = new TreeStr(compExtension);
			TreeLong* sizeTree = new TreeLong(compSize);
			TreeStr* dateTree = new TreeStr(compDate);

			TreeChr* nameTreeFin = new TreeChr(compNameFin);
			// Busquedad de los archivos en una determinada ruta
			if (exists(ruta)) {
				for (const auto& entry : recursive_directory_iterator(ruta)) {
					if (is_regular_file(entry.path()) || is_directory(entry.path())) {
						File* file = new File(entry.path());
						nameTree->add(file);
						sizeTree->add(file);
						extensionTree->add(file);
						dateTree->add(file);
					}
				}
				auto showName = [](File* a) {
					if (a != nullptr) {
						cout << a->GetName() << endl;
					}

				};
				auto showSize = [](File* s) {//Lambda que muestra los tamaños de archivos
					if (s != nullptr) {
						cout << s->GetSize() << endl;
					}

				};

				auto ShowDate = [](File* d) {
					if (d != nullptr) {
						cout << d->GetDate() << endl;
					}

				};
				auto ShowExtension = [](File* e) {
					if (e != nullptr) {
						cout << e->GetExtension() << endl;
					}
				};

				do {
					cout << "----------------------------------------------------------------------------" << endl;
					cout << "Ingrese el tipo de arbol [1:Nombres|2:Tamanios|3:Extensiones|4:Fechas]: "; cin >> numero;
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
							};
							cout << "\nArchivos que empiezan con la letra [" << textoEmpieza << "]" << endl;
							nameTree->inorder(EmpiezanCon);
							_getch();
							system("cls");
							SeeMenu();
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
							};
							cout << "Contiene la palabra [" << textoContiene << "]" << endl;
							nameTree->inorder(Contiene);
							_getch();
							system("cls");
							SeeMenu();
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
							};
							cout << "Finaliza con la letra [" << Textofinaliza << "]" << endl;
							nameTree->inorder(FinalizaCon);
							_getch();
							system("cls");
							SeeMenu();

						}break;
					
						}
					} while (num != 1 || num != 2 || num != 3);

					} break;
					case 2: {
				 		cout << "++++++++++++" << endl;
						cout << "Size:" << endl;
						
						//sizeTree->inorder(showSize);
						sizeTree->Descendente(showSize);//mostrando descendente
						cout << "\n------------------------" << endl;
						cout << "El mayor tamanio es :" << sizeTree->ElemMayor()->GetSize(); cout << endl;
						cout << "El menor tamanio es :" << sizeTree->ElemMenor()->GetSize(); cout << endl;
						ulong NumeroBuscar;
						cout << "\n------------------------" << endl;
						cout << "Tamanio a buscar :"; cin >> NumeroBuscar;
						auto buscar = [&](File* d) {
							if (d != nullptr) {
								if (d->GetSize() == NumeroBuscar) {
									cout << d->GetName() << endl;
								}
							}

						};
						sizeTree->inorder(buscar);
						//cout << sizeTree->find(NumeroBuscar)->GetName() << endl;
						_getch();
						system("cls");
						SeeMenu();
					} break;

					case 3: {
						cout << "------------------------------" << endl;
						cout << "Extension:" << endl;
						extensionTree->inorder(ShowExtension);
						_getch();
						system("cls");
						SeeMenu();
					}break;

					case 4: {
						cout << "------------------------------" << endl;
						cout << "Fecha:" << endl;
						dateTree->inorder(ShowDate);
						_getch();
						system("cls");
						SeeMenu();
					}break;
					}
				} while (numero != 1 || numero != 2 || numero != 3 || numero != 4);
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
