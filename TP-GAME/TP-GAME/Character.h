#pragma once
#include <iostream>
#include <Windows.h>
#include "Map.h"
#include "Design.h"
class Character {
protected:
	int posX;
	int posY;
	int dX;
	int dY;
	char figure;
	int value;
	Design* d;

public:
	Character(int posX, int posY, int value, char figure);
	~Character() {}
	void DrawCharacter(char figure, int value);
	void EraseCharacter();
	int GetX();
	int GetY();
	void SetX(int x);
	void SetY(int y);
	char GetFigure();
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
	this->d = new Design();
}
void Character::DrawCharacter(char figure, int value) {
	d->Gotoxy(this->posX, this->posY);
	d->SetColor(value);
	cout << char(figure);
}
void Character::EraseCharacter() {
	d->Gotoxy(this->posX, this->posY);
	cout << " ";
}

// --------------------> Get and Set
int  Character::getValue() { return this->value; }
void Character::SetValue(int value) { this->value = value; }
char Character::GetFigure() { return this->figure; }
int Character::GetX() { return this->posX; }
int Character::GetY() { return this->posY; }
void Character::SetX(int x) { this->posX = x; }
void Character::SetY(int y) { this->posY = y; }
int Character::GetdX() { return this->dX; }
int Character::GetdY() { return this->dY; }
void Character::SetdX(int dX) { this->dX = dX; }
void Character::SetdY(int dY) { this->dY = dY; }