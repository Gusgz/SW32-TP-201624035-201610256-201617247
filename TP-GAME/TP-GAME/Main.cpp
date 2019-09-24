#include <iostream>
#include <thread>
#include <conio.h>
#include <time.h>
#include "Map.h"
#include "Player.h"
#include "Enemy.h"
#include "ListCircle.h"
#include "Cola.h"
using namespace std;
#define UP 72
#define DOWN 80
#define RIGHT 77
#define LEFT 75
#define ESCAPE 27
#define ENTER 13
#define GUARDAR 'g'
#define CARGAR 'c'
double score;
bool game;
// GZ guardar y cargar
void Menu(Map* map, Design* d) {
	int cont_y = 5;
	d->SetColor(15);
	d->Gotoxy(map->GetColumns() + 5, cont_y++);
	cout << "[" << GUARDAR << "] Guardar partida" << endl;
	d->Gotoxy(map->GetColumns() + 5, cont_y++);
	cout << "[" << CARGAR << "] Cargar partida" << endl;
	d->Gotoxy(map->GetColumns() + 5, cont_y++);
	cout << "LISTA DE ARMAS" << endl;
	d->Gotoxy(map->GetColumns() + 5, cont_y++);
	cout << "LISTA DE ENEMIGOS" << endl;
}

void Acciones(Map* map, Player* p, Design* d) {
	if (_kbhit()) {
		int o = _getch();
		switch (o)
		{
		case UP:
			p->MoveUp(map);
			break;
		case DOWN:
			p->MoveDown(map);
			break;
		case LEFT:
			p->MoveLeft(map);
			break;
		case RIGHT:
			p->MoveRight(map);
			break;
		case GUARDAR:
			map->SaveMap();
			p->SavePosition();
			break;
		case CARGAR:
			system("cls");
			//MAP
			map->LoadMap();
			d->Gotoxy(0, 0);
			map->DrawMap(map->GetRows(), map->GetColumns());
			//PLAYER
			p->LoadPosition();
			p->DrawPlayer('C',3);
			//MENU
			Menu(map, d);
			break;
		default:
			break;
		}
		if (p->PlayerMoved()) {
			p->ErasePlayer();
			p->SetX(p->GetX() + p->GetdX());
			p->SetY(p->GetY() + p->GetdY());
			p->DrawPlayer('C',3);
			p->SetdX(0);
			p->SetdY(0);
		}
	}
}

bool Crashed(Player* p, Enemy* e) {
	if (p->GetX() == e->GetX() && p->GetY() == e->GetY())
		return true;
	else
		return false;
}

int main() {
	Map* map = new Map();
	map->LoadMap();
	map->DrawMap(map->GetRows(), map->GetColumns());
	Design* d = new Design();
	Player* p = new Player(1, 1, 15, 'C', 3);
	p->DrawPlayer('C',3);
	Enemy* e = new Enemy(30, 12, 2, char(223));
	// CREACION DE COLA ENEMIGOS
	Cola<Enemy>* cEnemy = new Cola<Enemy>();
	Menu(map, d);
	while (1) {
		//p->MovePlayer(map);
		//e->MoveEnemy(map);
		//GZ
		Acciones(map, p, d);
		if (Crashed(p, e)) {
			cout << "Comido" << endl;
			e->SetX(2);
			e->SetY(map->GetRows() + 2);
			cEnemy->Enqueue(e);
			e->SetStatus();
			e->DrawEnemy(char(223),2);
		}
		else {
			e->MoveEnemy(map);
		}
	}
	return 0;
}