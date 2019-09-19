#pragma once
#include <iostream>
#include <Windows.h>
#include "Map.h"
#include "Diseño.h"
class Character {
protected:
	int posX;
	int posY;
	int dX;
	int dY;
	char figure;
	int value;
	Diseño* d;
	//bool tipo; // 0 es principal 1 es enemigo

public:
	Character(int posX, int posY, int value, char figure);
	~Character() {}
	void DrawCharacter(char figure, int value);
	void EraseCharacter();
	int GetX();
	int GetY();
	void SetX(int x);
	void SetY(int y);
	char getFigure();
	int getValue();
	void SetValue(int value);
	int GetdX();
	int GetdY();
	void SetdX(int dX);
	void SetdY(int dY);

};

Character::Character(int posX, int posY, int value, char figure) {
	this->posX = posX;
	this->posY = posY;
	this->dX = 0;
	this->dY = 0;
	this->figure = figure;
	this->value = value;
	d = new Diseño();
}
void Character::DrawCharacter(char figure, int value) {
	d->gotoxy(this->posX, this->posY);
	d->SetColor(value);
	cout << char(figure);
}

void Character::EraseCharacter() {
	d->gotoxy(this->posX, this->posY);
	cout << " ";
}

// GET AND SET
int  Character::getValue() { return this->value; }
void Character::SetValue(int value) { this->value = value; }
char Character::getFigure() { return this->figure; }
int Character::GetX() { return this->posX; }
int Character::GetY() { return this->posY; }
void Character::SetX(int x) { this->posX = x; }
void Character::SetY(int y) { this->posY = y; }
int Character::GetdX() { return this->dX; }
int Character::GetdY() { return this->dY; }
void Character::SetdX(int dX) { this->dX = dX; }
void Character::SetdY(int dY) { this->dY = dY; }