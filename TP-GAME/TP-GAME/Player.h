#pragma once
#include <Windows.h>
#include <conio.h>
#include "Character.h"
#define UP 72
#define DOWN 80
#define RIGHT 77
#define LEFT 75
class Player : public Character {
private:
	int vida;
public:
	// CONSTRUCTORES
	Player();
	Player(int x, int y, char figure, int color, Map* map);
	~Player();
	// METODOS
	void MovePlayer(int o);
	void LoadPosition() {
		Character::LoadPosition();
	}
	void SavePosition() {
		Character::SavePosition();
	}
	// GET
	int GetVida();
};
// CONSTRUCTORES
Player::Player() {
	Character::Character();
	vida = 0;
}
Player::Player(int x, int y, char figure, int color, Map* map) : Character(x, y, figure, color,map) {
	this->vida = vida;
}
Player::~Player() {
	Character::~Character();
}
// METODOS
void Player::MovePlayer(int o) {
	dx = 0;
	dy = 0;
	switch (o)
	{
	case UP:
		if (map->GetMatrix(GetX(), GetY() - 1) == 0)
			Setdy(-1);
		break;
	case DOWN:
		if (map->GetMatrix(GetX(), GetY() + 1) == 0)
			Setdy(1);
		break;
	case LEFT:
		if (map->GetMatrix(GetX() - 1, GetY()) == 0)
			Setdx(-1);
		break;
	case RIGHT:
		if (map->GetMatrix(GetX() + 1, GetY()) == 0)
			Setdx(1);
		break;
	default:
		break;
	}
	EraseCharacter();
	x = x + dx;
	y = y + dy;
	DrawCharacter();
}
// GET
int Player::GetVida() {
	return vida;
}
