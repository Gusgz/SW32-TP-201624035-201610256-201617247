#pragma once
#pragma once
#include <iostream>
#include <Windows.h>
#include "Character.h"
class Enemy :public Character {
private:
	double move;
	bool estado;
public:
	// CONSTRUCTORES
	Enemy();
	Enemy(int x, int y, char figure, int color, Map* map);
	~Enemy();
	// METODOS
	void MoveEnemy();
	void Dead();
	// GET
	bool GetEstado();
	// SET
	void SetEstado(bool estado);
};
// CONSTRUCTORES
Enemy::Enemy() {
	Character::Character();
	move = 0;
	estado = true;
}
Enemy::Enemy(int x, int y, char figure, int color, Map* map) : Character(x, y, figure, color, map) {
	move = 0;
	estado = true;
}
Enemy::~Enemy() {
	Character::~Character();
}
void Enemy::MoveEnemy() {//movimiento de enemigo en el mapa
	if (move > 1000 && estado == true) {
		EraseCharacter();
		move = 0;
		int random;
		random = rand() % 4;
		Setdx(0);
		Setdy(0);
		switch (random)
		{
		case 0:
			if (map->GetMatrix(GetX() - 1, GetY()) == 0)
				Setdx(-1);
			break;
		case 1:
			if (map->GetMatrix(GetX() + 1, GetY()) == 0)
				Setdx(1);
			break;
		case 2:
			if (map->GetMatrix(GetX(), GetY() - 1) == 0)
				Setdy(-1);
			break;
		case 3:
			if (map->GetMatrix(GetX(), GetY() + 1) == 0)
				Setdy(1);
			break;
		default:
			break;
		}
		SetX(GetX() + Getdx());
		SetY(GetY() + Getdy());
		DrawCharacter();
	}
	else
		move = move + 0.1;
}
void Enemy::Dead() {
	x = 0;
	y = 0;
	figure = 'D';
}
// GET
bool Enemy::GetEstado() {
	return estado;
}
// SET
void Enemy::SetEstado(bool estado) {
	this->estado = estado;
}