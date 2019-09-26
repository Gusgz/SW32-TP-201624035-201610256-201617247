#include <iostream>
#include <thread>
#include <conio.h>
#include <time.h>
#include <ctime>
#include "Map.h"
#include "Player.h"
#include "Enemy.h"
#include "ListCircle.h"
#include "Cola.h"
#include "Lista.h" 
#include"PilaNumeroVidas.h"

#define UP 72
#define DOWN 80
#define RIGHT 77
#define LEFT 75
#define ESCAPE 27
#define ENTER 13
#define GUARDAR 'g'
#define CARGAR 'c'
using namespace std;
bool Colisionar(Player* p, Enemy* e) {
	if (p->GetX() == e->GetX() && p->GetY() == e->GetY())
		return true;
	else
		return false;
}
void Menu(Map* map, Design* d,pilaNumeroVidas<char>* vidas) {
	int cont_y = 5;
	d->SetColor(15);
	d->Gotoxy(map->GetColumns() + 5, cont_y++);
	cout << "[G] GUARDAR PARTIDA" << endl;
	d->Gotoxy(map->GetColumns() + 5, cont_y++);
	
	cout << "[C] CARGAR PARTIDA" << endl;
	d->Gotoxy(map->GetColumns() + 5, cont_y++);
	
	cout << "[ESCAPE] SALIR DEL JUEGO..." << endl;
	d->Gotoxy(map->GetColumns() + 5, cont_y++);
	d->Gotoxy(map->GetColumns() + 5, cont_y++);

	cout << "NUMERO DE VIDAS : " << endl;
	d->Gotoxy(map->GetColumns() + 5, cont_y++);
	vidas->Show();//Mostrando vidas

}
void KeyPressed(Map* map, Player* p, Design* d, int o,pilaNumeroVidas<char>* vidas) {
		switch (o)
		{
		case UP: case DOWN: case LEFT: case RIGHT:
			p->MovePlayer(o);
			break;
		case GUARDAR:
			// MAP
			map->SaveMap();
			//VIDAS
			vidas->guardarNumeroVidas();
			// PLAYER
			p->SavePosition();
			break;
		case CARGAR:
			system("cls");
			// MAP
			d->Gotoxy(0, 0);
			map->LoadMap();
			map->DrawMap(map->GetRows(), map->GetColumns());
			// PLAYER
			p->LoadPosition();
			p->DrawCharacter();
			//VIDAS
		/*	vidas->mostrarNumeroVidas();*/
			// MENU
			Menu(map, d,vidas);
			break;
		case ESCAPE:
			exit(0);
			break;
		default:
			break;
		}
}

int main() {
	// TIEMPO
	//time_t now;
	//struct tm* t;
	//now = time(NULL);

	bool comido = false;
	Map* map = new Map();
	map->LoadMap();
	map->DrawMap(map->GetRows(), map->GetColumns());
	Design* d = new Design(); // Gotoxy como apoyo en coord,diseño y cursor
	d->HideCursor();
	// JUGADOR
	Player* p = new Player(1, 1,char(184),15,map);
	p->DrawCharacter();
	 //LISTA DE ENEMIGOS RECIEN CREADOS
	Lista<Enemy>* listEnemy = new Lista<Enemy>();
	//int color_rand = 0;
	//for (int i = 0; i < 15; i++) {
	//	color_rand = rand()%(4,12);
	//	Enemy* aux = new Enemy(30, 12, char(223), color_rand, map);
	//	listEnemy->agregaInicial(aux);
	//}
	int rand_create = 0;
	for (int i = 0; i < map->GetRows();i++) {
		for (int j = 0; j < map->GetColumns();j++) {
			rand_create = rand() % 10;
			if(i > 3 && j > 3)
			if (map->GetMatrix(j, i) == 0 && rand_create == 5) {
				int color_rand = rand() % 3 + 1;
				Enemy* aux = new Enemy(j, i, char(223), color_rand, map);
				aux->DrawCharacter();
				listEnemy->agregaInicial(aux);
			}
		}
	}

	// COLA DE ENEMIGOS ELIMINADOS
	Cola<Enemy>* cEnemy = new Cola<Enemy>();
	cEnemy->SetMaxLength(10);
	//IMPLEMENTANDO VIDAS
	pilaNumeroVidas<char>* vidas = new pilaNumeroVidas<char>();
	for (int i = 0; i < 3; i++) { // EL JUGADOR SIEMPRE INICIA CON 3 VIDAS
		vidas->push(p->GetFigure());
	}
	
	Menu(map, d,vidas);
	while (1) {
		if (_kbhit()) {
			int o = _getch();
			KeyPressed(map, p, d, o,vidas);
		}
		for (int i = 0; i < listEnemy->longitud(); i++) {
			if (Colisionar(p, listEnemy->obtenerPos(i))) {//si colisionan
				comido = true;
				if (!cEnemy->IsFull()) {
					listEnemy->obtenerPos(i)->SetX(0);
					listEnemy->obtenerPos(i)->SetY(0);
					listEnemy->obtenerPos(i)->SetEstado(false);//cambia a muerto
					cEnemy->Enqueue(listEnemy->obtenerPos(i));//enviados a la cola de fantasmas eliminados
				}
				else {
					vidas->pop();// QUITANDO VIDAS CUANDO COLISIONAN
					system("cls");//LIMPIAR MAPA
					//// MAP
					d->Gotoxy(0, 0);//POSICION PARA DIBUJAR MAPA DE NUEVO
					map->DrawMap(map->GetRows(), map->GetColumns());//DIBUJAR MAPA
					//// PLAYER
					p->SetX(1);
					p->SetY(1);
					p->DrawCharacter();
				}
				//// MENU
				Menu(map, d, vidas);
			}
			else
				listEnemy->obtenerPos(i)->MoveEnemy();
		}
		if (comido == true) {
			for (int i = 0; i < cEnemy->Size(); i++) {
				d->Gotoxy(1+i,map->GetRows()-2);
				d->SetColor(cEnemy->GetElementPos(i)->GetColorFigure());
				cout << cEnemy->GetElementPos(i)->GetFigure() << "  ";
			}
			comido = false;
		}
	}
	return 0;
}

//BLACK                   0
//BLUE                    1
//GREEN                   2
//CYAN                    3
//RED                     4
//MAGENTA                 5
//BROWN                   6
//LIGHTGRAY               7
//DARKGRAY                8
//LIGHTBLUE               9
//LIGHTGREEN             10
//LIGHTCYAN              11 ENEMY
//LIGHTRED               12 ENEMY
//LIGHTMAGENTA           13 ENEMY
//YELLOW                 14 ENEMY
//WHITE                  15