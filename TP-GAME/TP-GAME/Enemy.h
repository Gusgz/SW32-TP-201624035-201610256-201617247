#pragma once
#pragma once
#include <iostream>
#include <Windows.h>
#include "Map.h"
#include "Design.h"
#include "Character.h"
class Enemy :public Character {
private:
	int daño;
	Design* d;
public:
	Enemy(int posX, int posY, int value, char figure);
	~Enemy() {}
	void DrawEnemy(char figure, int value);
	void EraseEnemy();
	void MoveEnemy(Map* map);
	int GetX();
	int GetY();
	void SetX(int x);
	void SetY(int y);
	int GetdX();
	int GetdY();
	void SetdX(int dX);
	void SetdY(int dY);

};

Enemy::Enemy(int posX, int posY, int value, char figure) :Character(posX, posY, value, figure) {
	this->posX = posX;
	this->posY = posY;
	this->dX = 0;
	this->dY = 0;
	this->daño = 100;
	d = new Design();
}

void Enemy::DrawEnemy(char figure, int value) {
	DrawCharacter(figure, value);
}
void Enemy::EraseEnemy() {
	EraseCharacter();
}
void Enemy::MoveEnemy(Map* map) {//movimiento de enemigo en el mapa
	if (daño % 1994 == 0) {
		int random;
		random = rand() % 4;
		SetdX(0);
		SetdY(0);

		DrawEnemy(GetFigure(), getValue());
		switch (random)
		{
		case 0:
			if (map->GetMatrix(GetX() - 1, GetY()) == 0)
				SetdX(-1);
			break;
		case 1:
			if (map->GetMatrix(GetX() + 1, GetY()) == 0)
				SetdX(1);
			break;
		case 2:
			if (map->GetMatrix(GetX(), GetY() - 1) == 0)
				SetdY(-1);
			break;
		case 3:
			if (map->GetMatrix(GetX(), GetY() + 1) == 0)
				SetdY(1);
			break;
		default:
			break;
		}
		EraseEnemy();

		SetX(GetX() + GetdX());
		SetY(GetY() + GetdY());
		DrawEnemy(GetFigure(), getValue());
	}
	daño++;
}
// GET AND SET
int Enemy::GetX() { return this->posX; }
int Enemy::GetY() { return this->posY; }
void Enemy::SetX(int x) { this->posX = x; }
void Enemy::SetY(int y) { this->posY = y; }
int Enemy::GetdX() { return this->dX; }
int Enemy::GetdY() { return this->dY; }
void Enemy::SetdX(int dX) { this->dX = dX; }
void Enemy::SetdY(int dY) { this->dY = dY; }