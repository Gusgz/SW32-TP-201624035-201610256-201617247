#pragma once
#pragma once
#include <iostream>
#include <Windows.h>
#include "Map.h"
#include "Diseño.h"
#include "Character.h"
class Ghost :public Character {
private:
	int daño;
	Diseño* d;
public:
	Ghost(int posX, int posY, int value, char figure);
	~Ghost() {}
	void DrawGhost(char figure, int value);
	void EraseGhost();
	void MoveGhost(Map* map);
	int GetX();
	int GetY();
	void SetX(int x);
	void SetY(int y);
	int GetdX();
	int GetdY();
	void SetdX(int dX);
	void SetdY(int dY);

};

Ghost::Ghost(int posX, int posY, int value, char figure) :Character(posX, posY, value, figure) {
	this->posX = posX;
	this->posY = posY;
	this->dX = 0;
	this->dY = 0;
	this->daño = 100;
	d = new Diseño();
}

void Ghost::DrawGhost(char figure, int value) {
	DrawCharacter(figure, value);
}
void Ghost::EraseGhost() {
	EraseCharacter();
}


void Ghost::MoveGhost(Map* map) {//movimiento de enemigo en el mapa
	if (daño % 1994 == 0) {
		int random;
		random = rand() % 4;
		SetdX(0);
		SetdY(0);

		DrawGhost(getFigure(), getValue());
		switch (random)
		{
		case 0:
			if (map->GetMatrix(GetX() - 1, GetY()) == 0)
				SetdX(-1);
			EraseGhost();
			break;
		case 1:
			if (map->GetMatrix(GetX() + 1, GetY()) == 0)
				SetdX(1);
			EraseGhost();
			break;
		case 2:
			if (map->GetMatrix(GetX(), GetY() - 1) == 0)
				SetdY(-1);
			EraseGhost();
			break;
		case 3:
			if (map->GetMatrix(GetX(), GetY() + 1) == 0)
				SetdY(1);
			EraseGhost();
			break;
		default:
			break;
		}

		SetX(GetX() + GetdX());
		SetY(GetY() + GetdY());
		DrawGhost(getFigure(), getValue());
	}
	daño++;
}

// GET AND SET
int Ghost::GetX() { return this->posX; }
int Ghost::GetY() { return this->posY; }
void Ghost::SetX(int x) { this->posX = x; }
void Ghost::SetY(int y) { this->posY = y; }
int Ghost::GetdX() { return this->dX; }
int Ghost::GetdY() { return this->dY; }
void Ghost::SetdX(int dX) { this->dX = dX; }
void Ghost::SetdY(int dY) { this->dY = dY; }