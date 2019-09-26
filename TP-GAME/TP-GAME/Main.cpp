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
#include "Win.h"
#include "Lose.h"
#define UP 72
#define DOWN 80
#define RIGHT 77
#define LEFT 75
#define ESCAPE 27
#define ESPACE 32
#define ENTER 13
#define GUARDAR 'g'
#define CARGAR 'c'
using namespace std;


bool comido = false;
int option = 0;
int cont_cola = 0;
int o = 0;
int pos_x = 0;
int pos_y = 0;
int rx_2 = 27;
int ry_2 = 13;
int rx_3 = 42;
int ry_3 = 18;
Design* d = new Design();
Map* map = new Map();
Player* p = new Player(1, 1, char(184), 15, map);
Lista<Enemy>* lstEnemy = new Lista<Enemy>();
Cola<Enemy>* colaEnemy = new Cola<Enemy>();
pilaNumeroVidas<char>* vidas = new pilaNumeroVidas<char>();



void VerColaEnemigos() {
	for (int i = 0; i < colaEnemy->Size(); i++) {
		d->Gotoxy(1 + i, map->GetRows() - 2);
		d->SetColor(colaEnemy->GetElementPos(i)->GetColorFigure());
		cout << colaEnemy->GetElementPos(i)->GetFigure() << "  ";
	}
}
bool Colisionar(Player* p, Enemy* e) {
	if (p->GetX() == e->GetX() && p->GetY() == e->GetY())
		return true;
	else
		return false;
}
void Menu() {
	int cont_x = 2;
	int cont_y = 2;
	d->SetColor(14);
	// ------------------------------
	d->Gotoxy(map->GetColumns() + cont_x, cont_y++);
	cout << "[G] GUARDAR PARTIDA";
	// ------------------------------
	d->Gotoxy(map->GetColumns() + cont_x, cont_y++);
	cout << "[C] CARGAR PARTIDA";
	// ------------------------------
	d->Gotoxy(map->GetColumns() + cont_x, cont_y++);
	cout << "[ESPACIO] LIBERAR ENEMIGOS";
	// ------------------------------
	d->Gotoxy(map->GetColumns() + cont_x, cont_y++);
	cout << "[ESCAPE] SALIR DEL JUEGO";
	// ------------------------------
	d->Gotoxy(map->GetColumns() + cont_x, cont_y++);
	cout << "------------------------------";
	// ------------------------------
	d->Gotoxy(map->GetColumns() + cont_x, cont_y++);
	cout << "VIDAS: "; vidas->Show();
	// ------------------------------
	d->Gotoxy(map->GetColumns() + cont_x, cont_y++);
	cout << "ENEMIGOS MUERTOS: "; cout << colaEnemy->Size();

}
void KeyPressed(int o) {
		switch (o)
		{
		case UP: case DOWN: case LEFT: case RIGHT:
			p->MovePlayer(o);
			break;
		case ESPACE:
			if (colaEnemy->Size()>5) {
				lstEnemy->agregaInicial(colaEnemy->Dequeue());
				lstEnemy->obtenerInicial()->SetEstado(true);
				int rand_pos = rand() % 4;
				switch (rand_pos)
				{
				case 0:
					pos_x = 1;
					pos_y = map->GetRows() - 4;
					break;
				case 1:
					pos_x = rx_2;
					pos_y = ry_2;
					break;
				case 2:
					pos_x = rx_3;
					pos_y = ry_2;
					break;
				default:
					break;
				}
				lstEnemy->obtenerInicial()->SetX(pos_x);
				lstEnemy->obtenerInicial()->SetY(pos_y);
				lstEnemy->obtenerInicial()->DrawCharacter();
				VerColaEnemigos();
			}
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
			// PLAYER
			p->EraseCharacter();
			p->LoadPosition();
			p->DrawCharacter(); 

			VerColaEnemigos();
			break;
		case ESCAPE:
			exit(0);
			break;
		default:
			break;
		}
}

int main() {
	srand(time(0));
	// ------------------------------ MAPA
	map->LoadMap();
	map->DrawMap(map->GetRows(), map->GetColumns());
	// ------------------------------ DISEÑO
	d->HideCursor();
	// ------------------------------ JUGADOR
	p->DrawCharacter();
	// ------------------------------ LISTA DE ENEMIGOS
	int rand_create = 0;
	int rand_color = 0;
	for (int i = 0; i < map->GetRows(); i++) {
		for (int j = 0; j < map->GetColumns(); j++) {
			rand_create = rand() % 10;
			if (i != p->GetX() && j != p->GetY())
				if (map->GetMatrix(j, i) == 0 && rand_create == 7) {
					rand_color = 8 + rand() % 2;
					Enemy* aux = new Enemy(j, i, char(223), rand_color, map);
					aux->DrawCharacter();
					lstEnemy->agregaInicial(aux);//AGREGA ENEMIGOS
				}
		}
	}
	// ------------------------------ COLA DE ENEMIGOS
	colaEnemy->SetMaxLength(7);
	// ------------------------------ VIDAS
	for (int i = 0; i < 3; i++) {
		vidas->pushVidas(p->GetFigure());
	}
	// MENU
	Menu();
	// ------------------------------ JUEGO
	while ((!vidas->is_empty()) && !((p->GetX() == 47 && p->GetY() == 23) || (p->GetX() == 48 && p->GetY() == 22))) {
		// ------------------------------ SI PRESIONA TECLA
		if (_kbhit()) {
			o = _getch();
			KeyPressed(o);
		}
		// ------------------------------ ACCION DE CADA ENEMIGO
		for (int i = 0; i < lstEnemy->longitud(); i++) {
			// ------------------------------ SI COLISIONA
			if (Colisionar(p, lstEnemy->obtenerPos(i))) {
			/*	m = 1;*/
				if (!colaEnemy->IsFull()) {
					lstEnemy->obtenerPos(i)->SetX(0);
					lstEnemy->obtenerPos(i)->SetY(0);
					lstEnemy->obtenerPos(i)->SetEstado(false);

					colaEnemy->Enqueue(lstEnemy->obtenerPos(i));
					lstEnemy->eliminaPos(i);
					VerColaEnemigos();
				}
				else {
					system("cls");//LIMPIAR MAPA
					d->Gotoxy(0, 0);//POSICION PARA DIBUJAR MAPA DE NUEVO
					map->DrawMap(map->GetRows(), map->GetColumns());//DIBUJAR MAPA
					p->EraseCharacter();
					p->SetX(1);
					p->SetY(1);
					p->DrawCharacter();
					vidas->popVidas();

				}
				Menu();
			}
			// ------------------------------ SI NO COLISIONA
			else {
				lstEnemy->obtenerPos(i)->MoveEnemy();//MUEVE A LOS ENEMIGOS DE LA LISTA
			}
		}
	}
	// ------------------------------ FIN JUEGO




	if (vidas->is_empty()) {
		Lose* lose = new Lose();
		system("cls");
		lose->LoadLose();
		lose->DrawLose(lose->GetRows(), lose->GetColumns());
		cin.get();
		exit(0);
	}
	else if ((p->GetX() == 47 && p->GetY() == 23) || (p->GetX() == 48 && p->GetY() == 22)) {
		Win* w = new Win();
		system("cls");
		w->LoadWin();
		w->DrawWin(w->GetRows(), w->GetColumns());
		cin.get();
		exit(0);
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