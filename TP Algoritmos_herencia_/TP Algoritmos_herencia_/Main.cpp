#include <iostream>
#include <thread>
#include <conio.h>
#include <time.h>
#include "Map.h"
#include "Pacman.h"
#include "Fantasma.h"

using namespace std;
#define UP 72
#define DOWN 80
#define RIGHT 77
#define LEFT 75
#define ESCAPE 27
#define ENTER 13
double score;
bool game;

int main() {
	Map* map = new Map();
	Pacman* p = new Pacman(1, 1, 15, char(169), 3);
	Ghost* f = new Ghost(30, 12, 2, char(223));
	Diseño* d = new Diseño();

	map->LoadMap();
	map->DrawMap(map->GetRows(), map->GetColumns());
	/*map->prueba();*/
	while (1) {
		/*MoveMain(map,cMain); */
		p->MoverPacman(map);
		f->MoveGhost(map);
		//MoveEnemy(map, cEnemy1);
		//std::thread t1(MoveMain, map, cMain);
		//std::thread t2(MoveEnemy, map, cEnemy1);
		//t2.join();
		//t1.join();*/
	}
	return 0;
}