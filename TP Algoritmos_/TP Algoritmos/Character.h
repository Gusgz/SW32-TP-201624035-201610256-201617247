#pragma once
#include <iostream>
#include <Windows.h>
#include "Map.h"
#include "Gotoxy.h"
class Character {
private:
	int posX;
	int posY;
	int dX;
	int dY;
	char figure;
	bool tipo; // 0 es principal 1 es enemigo
	gotoxy* g;
public:
	Character(int posX, int posY, char figure, bool tipo);
	~Character(){}
	void SetColor(int value);
	void DrawCharacter();
	void EraseCharacter(Map* map);
	char getfigure();
	void setfigure(char figure);
	int GetX();
	int GetY();
	void SetX(int x);
	void SetY(int y);
	int GetdX();
	int GetdY();
	void SetdX(int dX);
	void SetdY(int dY);

};

Character::Character(int posX, int posY, char figure, bool tipo) {
	this->posX = posX;
	this->posY = posY;
	this->dX = 0;
	this->dY = 0;
	this->figure = figure;
	this->tipo = tipo;
	g = new gotoxy();
}

void Character:: SetColor(int value) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), value);
}
void Character::DrawCharacter() {
	g->got(this->posX, this->posY);
	SetColor(14);
	cout << this->figure;
}

void Character::EraseCharacter(Map* map) {
	switch (tipo) {
	case 0://pacman
		g->got(this->posX, this->posY);
		cout << " ";//para que no se repita cuando avance
		
		break;
	case 1://enemigo
		g->got(this->posX, this->posY);
		if (map->GetMatrix(this->posX, this->posY) == 1)
			cout << char(250);
	
		if (map->GetMatrix(this->posX, this->posY) == 2)
			cout << " ";
		break;
	default:
		break;
	}
}

// GET AND SET
char Character::getfigure() { return this->figure; }
void Character::setfigure(char figure) { this->figure = figure; }
int Character::GetX() { return this->posX; }
int Character::GetY() { return this->posY; }
void Character::SetX(int x) { this->posX = x; }
void Character::SetY(int y) { this->posY = y; }
int Character::GetdX() { return this->dX; }
int Character::GetdY() { return this->dY; }
void Character::SetdX(int dX) { this->dX = dX; }
void Character::SetdY(int dY) { this->dY = dY; }