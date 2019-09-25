#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Map.h"
#include "Design.h"
class Character {
protected:
	int x;
	int y;
	int dx;
	int dy;
	char figure;
	int color;
	Map* map; // NUEVO
	Design* d;
public:
	// CONSTRUCTORES
	Character();
	Character(int x, int y, char figure, int color, Map* map);
	~Character();
	// METODOS
	void DrawCharacter();
	void EraseCharacter();
	void LoadPosition();
	void SavePosition();
	// GET
	int GetX();
	int GetY();
	int Getdx();
	int Getdy();
	char GetFigure();
	int GetColorFigure();
	// SET
	void SetX(int x);
	void SetY(int y);
	void Setdx(int dx);
	void Setdy(int dy);
	void SetFigure(char figure);
	void SetColorFigure(int color);
};
// CONSTRUCTORES
Character::Character() {
	this->x = 0;
	this->y = 0;
	this->dx = 0;
	this->dy = 0;
	this->figure = 'f';
	this->color = 15;
	this->map = new Map();
	this->d = new Design();
}
Character::Character(int x, int y, char figure, int color, Map* map) {
	this->x = x;
	this->y = y;
	this->dx = 0;
	this->dy = 0;
	this->figure = figure;
	this->color = color;
	this->map = map;
	this->d = new Design();
}
Character::~Character() { 
	delete map;
	delete d;
}
// METODOS
void Character::DrawCharacter() {
	d->Gotoxy(x, y);
	d->SetColor(color);
	std::cout << figure;
}
void Character::EraseCharacter() {
	d->Gotoxy(x,y);
	cout << " ";
}
void Character::LoadPosition() {
	ifstream File("Character.txt");
	if (!File.is_open())
		cout << "Error al cargar posicion" << endl;
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
				x = stoi(temp_x);//cargar posicion x del caracater
				// Y
				string temp_y;
				getline(iss, temp_y, ',');
				y = stoi(temp_y);//cargar posicion y del caracater
			}
		}
	}
	File.close();
}
void Character::SavePosition() {
	ofstream File("Character.txt");
	if (!File.is_open())
		cout << "Error al guardar posicion" << endl;
	else {
		File << figure << ',' << x << ',' << y << endl;
	}
	File.close();
}
// GET
int Character::GetX() { return x; }
int Character::GetY() { return y; }
int Character::Getdx() { return dx; }
int Character::Getdy() { return dy; }
char Character::GetFigure() { return figure; }
int Character::GetColorFigure() { return color; }
// SET
void Character::SetX(int x) { this->x = x; }
void Character::SetY(int y) { this->y = y; }
void Character::Setdx(int dx) { this->dx = dx; }
void Character::Setdy(int dy) { this->dy = dy; }
void Character::SetFigure(char figure) { this->figure = figure; }
void Character::SetColorFigure(int color) { this->color = color; }