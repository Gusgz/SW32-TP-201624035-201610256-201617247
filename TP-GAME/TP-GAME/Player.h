#pragma once
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include "Map.h"
#include "Character.h"
#define UP 72
#define DOWN 80
#define RIGHT 77
#define LEFT 75
#define ESCAPE 27
#define ENTER 13
#define GUARDAR 'g'
#define CARGAR 'c'
class Player : public Character {
private:
	int vidas;
public:
	Player();
	Player(int posX, int posY, int value, char figure, int vidas);
	void DrawPlayer();
	~Player();
	void ErasePlayer();
	void Menu(Map* map, Design* d);
	void Acciones(Map* map);

	void MoveUp(Map* map);
	void MoveDown(Map* map);
	void MoveLeft(Map* map);
	void MoveRight(Map* map);
	bool PlayerMoved() {
		if (this->dX != 0 || this->dY != 0)
			return true;
	}
	void LoadPosition() {
		Character::LoadPosition();
	}
	void SavePosition() {
		Character::SavePosition();
	}

};

Player::Player(int posX, int posY, int value, char figure, int vidas) :Character(posX, posY, value, figure) {
	this->vidas = vidas;
}

void Player::DrawPlayer() {
	d->Gotoxy(this->posX, this->posY);
	d->SetColor(value);
	cout << char(GetFigure());
}
void Player::ErasePlayer() {
	EraseCharacter();
}

void Player::MoveUp(Map* map) {
	if (map->GetMatrix(GetX(), GetY() - 1) == 0)
		SetdY(-1);
}
void Player::MoveDown(Map* map) {
	if (map->GetMatrix(GetX(), GetY() + 1) == 0)
		SetdY(1);
}
void Player::MoveLeft(Map* map) {
	if (map->GetMatrix(GetX() - 1, GetY()) == 0)
		SetdX(-1);
}
void Player::MoveRight(Map* map) {
	if (map->GetMatrix(GetX() + 1, GetY()) == 0)
		SetdX(1);
}

void Player::Menu(Map* map, Design* d) {
	int cont_y = 5;
	d->SetColor(15);
	d->Gotoxy(map->GetColumns() + 5, cont_y++);
	cout << "[" << GUARDAR << "] Guardar partida" << endl;
	d->Gotoxy(map->GetColumns() + 5, cont_y++);
	cout << "[" << CARGAR << "] Cargar partida" << endl;
	d->Gotoxy(map->GetColumns() + 5, cont_y++);
	cout << "LISTA DE ENEMIGOS" << endl;
}



void Player::Acciones(Map* map) {//movimiento del pacman en el mapa
	if (_kbhit()) {
		int o = _getch();
		switch (o)
		{
		case UP:
			MoveUp(map);
			break;
		case DOWN:
			MoveDown(map);
			break;
		case LEFT:
			MoveLeft(map);
			break;
		case RIGHT:
			MoveRight(map);
			break;
		case GUARDAR:
			map->SaveMap();
			SavePosition();
			break;
		case CARGAR:
			system("cls");
			//MAP
			map->LoadMap();
			d->Gotoxy(0, 0);
			map->DrawMap(map->GetRows(), map->GetColumns());
			//PLAYER
			LoadPosition();
			DrawPlayer();
			//MENU
			Menu(map, d);
			break;
		default:
			break;
		}
		if (PlayerMoved()) {
			ErasePlayer();
			SetX(GetX() + GetdX());
			SetY(GetY() + GetdY());
			DrawPlayer();
			SetdX(0);
			SetdY(0);
		}
	}
}



// --------------------> Get and Set
