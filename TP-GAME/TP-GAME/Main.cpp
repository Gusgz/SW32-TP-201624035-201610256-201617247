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
using namespace std;

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
	p->DrawPlayer();
	 //LISTA DE ENEMIGOS RECIEN CREADOS
	Lista<Enemy>* listEnemy = new Lista<Enemy>();
	for (int i = 0; i < 5; i++) {
		Enemy* aux = new Enemy(30, 12, 2, char(223));
		listEnemy->agregaInicial(aux);
	}
	// COLA DE ENEMIGOS ELIMINADOS
	Cola<Enemy>* cEnemy = new Cola<Enemy>();
	p->Menu(map, d);
	while (1) {
		p->Acciones(map);
		for(int i = 0; i < listEnemy->longitud();i++)
		if (Crashed(p, listEnemy->obtenerPos(i))) {//si colisionan
			cEnemy->Enqueue(listEnemy->obtenerPos(i));//enviados a la cola de fantasmas eliminados
			listEnemy->obtenerPos(i)->SetX(i+8);//cuando los captura lo cambia de posicion en x
			listEnemy->obtenerPos(i)->SetY(map->GetRows() + 2);//cambia de posicion en y
			listEnemy->obtenerPos(i)->SetStatus();//cambia a muerto
			listEnemy->obtenerPos(i)->DrawEnemy();//lo dibuja
		}
		else {
			for (int i = 0; i < listEnemy->longitud(); i++)
				listEnemy->obtenerPos(i)->MoveEnemy(map);
		}
	}
	return 0;
}