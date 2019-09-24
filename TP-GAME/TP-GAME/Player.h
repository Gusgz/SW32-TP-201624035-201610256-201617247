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
class Player : public Character {
private:
	int vidas;
public:
	Player();
	Player(int posX, int posY, int value, char figure, int vidas);
	void DrawPlayer(char figure, int value);
	~Player();
	void ErasePlayer();
	void MovePlayer(Map* map);
	//GZ
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

void Player::DrawPlayer(char figure, int value) {
	DrawCharacter(figure, value);
}
void Player::ErasePlayer() {
	EraseCharacter();
}

void Player::MovePlayer(Map* map) {//movimiento del pacman en el mapa
	int key;

	DrawPlayer(GetFigure(), getValue());
	if (_kbhit()) {
		SetdX(0);
		SetdY(0);
		key = _getch();
		switch (key)
		{
		case LEFT:
			if (map->GetMatrix(GetX() - 1, GetY()) == 0)
				SetdX(-1);
			break;
		case RIGHT:
			if (map->GetMatrix(GetX() + 1, GetY()) == 0)
				SetdX(1);
			break;
		case UP:
			if (map->GetMatrix(GetX(), GetY() - 1) == 0)
				SetdY(-1);
			break;
		case DOWN:
			if (map->GetMatrix(GetX(), GetY() + 1) == 0)
				SetdY(1);
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
		default:
			break;
		}
		ErasePlayer();
		SetX(GetX() + GetdX());//movimiento del caracter(pacman) horizontal 
		SetY(GetY() + GetdY());//movimiento del caracter(pacman) vertical
	}
}

//GZ
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
// --------------------> Get and Set
