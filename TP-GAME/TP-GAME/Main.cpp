#include <iostream>
#include <thread>
#include <conio.h>
#include <time.h>
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

	cout << "NUMEROS DE VIDAS : " << endl;
	d->Gotoxy(map->GetColumns() + 5, cont_y++);
	for(int i=0;i<vidas->tamaño();i++)
	cout << vidas->top()<<" " ;// MOSTRANDO VIDAS 



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
			//vidas->mostrarNumeroVidas();
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
	bool menu = true; bool comido = false;
	Map* map = new Map();
	map->LoadMap();
	map->DrawMap(map->GetRows(), map->GetColumns());
	Design* d = new Design(); // Gotoxy SetColor
	Player* p = new Player(1, 1,'P',15,map,5);
	p->DrawCharacter();
	 //LISTA DE ENEMIGOS RECIEN CREADOS
	Lista<Enemy>* listEnemy = new Lista<Enemy>();
	int color_rand = 0;
	for (int i = 0; i < 5; i++) {
		color_rand = rand()%4+11;
		Enemy* aux = new Enemy(30, 12, char(223), color_rand, map);
		listEnemy->agregaInicial(aux);
	}
	// COLA DE ENEMIGOS ELIMINADOS
	Cola<Enemy>* cEnemy = new Cola<Enemy>();


	//IMPLEMENTANDO VIDAS
	pilaNumeroVidas<char>* vidas = new pilaNumeroVidas<char>();
	for (int i = 0; i < 3; i++) { // EL JUGADOR SIEMPRE INICIA CON 3 VIDAS
		vidas->push('C');
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
				listEnemy->obtenerPos(i)->SetX(0);
				listEnemy->obtenerPos(i)->SetY(0);
				listEnemy->obtenerPos(i)->SetEstado(false);//cambia a muerto

				cEnemy->Enqueue(listEnemy->obtenerPos(i));//enviados a la cola de fantasmas eliminados
				vidas->pop();// QUITANDO VIDAS CUANDO COLISIONAN
				d->Gotoxy(2, map->GetRows() + 2);
			}
			else
				listEnemy->obtenerPos(i)->MoveEnemy();
		}
		if (comido == true) {
			for (int i = 0; i < cEnemy->Size(); i++) {
				d->Gotoxy(i+2,map->GetRows()+3);
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