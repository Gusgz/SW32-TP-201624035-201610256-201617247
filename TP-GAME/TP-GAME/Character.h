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
	//GZ
	void LoadPosition() {
		ifstream File("Character.txt");
		if (!File.is_open())
			cout << "Failed" << endl;
		else {
			string line;
			while (getline(File, line)) {
				istringstream iss(line);
				string temp_f;
				getline(iss, temp_f, ',');
				if (this->figure == temp_f[0]) {
					// X
					string temp_x;
					getline(iss, temp_x, ',');
					posX = stoi(temp_x);//cargar posicion x del caracater
					// Y
					string temp_y;
					getline(iss, temp_y, ',');
					posY = stoi(temp_y);//cargar posicion y del caracater
				}
			}
		}
		File.close();
	}
	void SavePosition() {
		ofstream File("Character.txt");
		if (!File.is_open())
			cout << "Failed" << endl;
		else {
			File << figure << ',' << posX << ',' << posY << endl;
		}
		File.close();
	}
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