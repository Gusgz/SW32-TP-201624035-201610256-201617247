#include <iostream>
#include <thread>
#include <conio.h>
#include <time.h>
#include "Map.h"
#include "Player.h"
#include "Enemy.h"
#include "ListCircle.h"

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
	Design* d = new Design();
	Player* p = new Player(1, 1, 15, 'C', 3);
	Enemy* e = new Enemy(30, 12, 2, char(223));
	map->LoadMap();
	map->DrawMap(map->GetRows(), map->GetColumns());
	//GZ
	ListCircle<Enemy>* lc = new ListCircle<Enemy>();
	lc->AddFirst(e);
	lc->SeeList(d);
	while (1) {
		p->MovePlayer(map);
		e->MoveEnemy(map);
	}
	return 0;
}