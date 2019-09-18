#include <iostream>
#include <thread>
#include <conio.h>
#include <time.h>
#include "Map.h"
#include "Character.h"
#include "Gotoxy.h"
#include "Lista.h"

using namespace std;

#define UP 72
#define DOWN 80
#define RIGHT 77
#define LEFT 75
#define ESCAPE 27
#define ENTER 13
ListaCharacters* ls = new ListaCharacters();
int key, r, random;
int contador = 0;
double score;
bool game;
void MoveMain(Map* map, Character* cMain) {
	if (_kbhit()) {
		cMain->SetdX(0);
		cMain->SetdY(0);
		key = _getch();
		switch (key)
		{
		case LEFT:
			if (map->GetMatrix(cMain->GetX()-1, cMain->GetY()) == 1
				|| map->GetMatrix(cMain->GetX() - 1, cMain->GetY()) == 2)
				cMain->SetdX(-1);
			break;
		case RIGHT:
			if (map->GetMatrix(cMain->GetX()+1, cMain->GetY()) == 1
				|| map->GetMatrix(cMain->GetX() + 1, cMain->GetY()) == 2)
				cMain->SetdX(1);
			break;
		case UP:
			if (map->GetMatrix(cMain->GetX(), cMain->GetY() - 1) == 1
				|| map->GetMatrix(cMain->GetX(), cMain->GetY() - 1) == 2)
				cMain->SetdY(-1);
			break;
		case DOWN:
			if (map->GetMatrix(cMain->GetX(), cMain->GetY()+1) == 1
				|| map->GetMatrix(cMain->GetX(), cMain->GetY() + 1) == 2)
				cMain->SetdY(1);
			break;
		case 'g':
			//guardarMatriz();
			//guardarPosicion(x, y);
			break;
		case 'c':
			//system("cls");
			//cout << "Cargando partida.";
			//Sleep(1000); cout << "."; Sleep(1000); cout << "."; Sleep(1000); system("cls");
			//cargarMatriz();
			//dibujarMapa(FILAS, COLUMNAS);
			//mostrarPosicionGuardada();
			break;
		case ESCAPE:
			game = false;
			break;
		default:
			break;
		}
		cMain->EraseCharacter(map);
		cMain->SetX(cMain->GetX() + cMain->GetdX());
		cMain->SetY(cMain->GetY() + cMain->GetdY());
		if(map->GetMatrix(cMain->GetX(),cMain->GetY()) == 1)
			score = score + 0.25;
		if (cMain->GetdX() != 0 || cMain->GetdY() != 0)
			map->SetMatrix(cMain->GetX(), cMain->GetY(), 2);
		cMain->DrawCharacter();
	}
}
void MoveEnemy(Map* map, Character* cEnemy) {
	srand(time(NULL));
	random = rand() % 4;
	cEnemy->SetdX(0);
	cEnemy->SetdY(0);
	switch (random)
	{
	case 0:
		if (map->GetMatrix(cEnemy->GetX() - 1, cEnemy->GetY()) == 1
			|| map->GetMatrix(cEnemy->GetX() - 1, cEnemy->GetY()) == 2)
			cEnemy->SetdX(-1);
		break;
	case 1:
		if (map->GetMatrix(cEnemy->GetX() + 1, cEnemy->GetY()) == 1
			|| map->GetMatrix(cEnemy->GetX() + 1, cEnemy->GetY()) == 2)
			cEnemy->SetdX(1);
		break;
	case 2:
		if (map->GetMatrix(cEnemy->GetX(), cEnemy->GetY() - 1) == 1
			|| map->GetMatrix(cEnemy->GetX(), cEnemy->GetY() - 1) == 2)
			cEnemy->SetdY(-1);
		break;
	case 3:
		if (map->GetMatrix(cEnemy->GetX(), cEnemy->GetY() + 1) == 1
			|| map->GetMatrix(cEnemy->GetX(), cEnemy->GetY() + 1) == 2)
			cEnemy->SetdY(1);
		break;
	default:
		break;
	}
	Sleep(50);
	cEnemy->EraseCharacter(map);
	cEnemy->SetX(cEnemy->GetX() + cEnemy->GetdX());
	cEnemy->SetY(cEnemy->GetY() + cEnemy->GetdY());
	cEnemy->DrawCharacter();
}
void comer( Character* cMain, Character* cEnemy,int x,int y) {
		if (cMain->GetX() == cEnemy->GetX() && cMain->GetY() == cEnemy->GetY()) {
			ls->AddEnemy(cEnemy);
			cEnemy->SetdX(0);
			cEnemy->SetdY(0);
			cEnemy->SetX(x);
			cEnemy->SetY(y);
		}

}
void Menu() {
	gotoxy *g = new gotoxy();
	int auxY = 2;
	score = 0;
	g->got(62, auxY++);
	cout << "JUEGO"; g->got(62, auxY++);
	cout << "Score: " << score; g->got(62, auxY++);
	cout << "PRESIONE ESCAPE PARA SALIR DEL JUEGO "; g->got(62, auxY++);
	cout << "Presiona A para ver enemigos comidos";
	

}
int main() {
	char tecla;
	gotoxy* g = new gotoxy();
	game = true;
	Map* map = new Map();
	map->LoadMap();
	//map->DrawMap(map->GetRows(),map->GetColumns());
	map->prueba();
	Character* cMain = new Character(20,19,184,0);
	cMain->DrawCharacter();
	Character* cEnemy1 = new Character(34,20,220,1);
	Character* cEnemy2 = new Character(15, 12, 244, 3);
	cEnemy1->DrawCharacter();
	cEnemy2->DrawCharacter();

	Menu();
	
	while (game) {
		//g->got(62, 8);
		//cout<<cEnemy1->GetX();
		//g->got(62, 9);
		//cout<<cEnemy1->GetY();
		//g->got(66, 8);
		//cout << cMain->GetX();
		//g->got(66, 9);
		//cout << cMain->GetY();
		g->got(62, 3);
		cout << "Score: " << score;
		MoveMain(map,cMain); 
		MoveEnemy(map, cEnemy1);
		MoveEnemy(map, cEnemy2);
		comer( cMain, cEnemy1,31,16);
		comer( cMain, cEnemy2,13,16);
		if (_kbhit()) {
			tecla = _getch();
			if (tecla == 65 || tecla == 97) {
			
				if (!ls->IsEmpty()) {
					g->got(62, 7);
					cout << "Enemigos comidos: " << ls->Size();
					g->got(62, 9);
					ls->SeeList();
				}
				else {
					cout << "No has comido nada";
				}
				
			}
		}
		//std::thread t1(MoveMain, map, cMain);
		//std::thread t2(MoveEnemy, map, cEnemy1);
		//t2.join();
		//t1.join();
	}
	cMain->~Character();
	cEnemy1->~Character();
	map->~Map();
	return 0;
}