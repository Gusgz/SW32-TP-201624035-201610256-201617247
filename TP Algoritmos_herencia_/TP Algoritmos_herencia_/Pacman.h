#pragma once
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include "Map.h"
#include "Character.h"
#include "Map.h"

#define UP 72
#define DOWN 80
#define RIGHT 77
#define LEFT 75
#define ESCAPE 27
#define ENTER 13
class Pacman :public Character {
private:
	int vidas;
public:
	Pacman();
	Pacman(int posX, int posY, int value, char figure, int vidas);
	void DrawPacman(char figure, int value);
	void ErasePacman();
	void MoverPacman(Map* map);
	~Pacman();


};

Pacman::Pacman(int posX, int posY, int value, char figure, int vidas) :Character(posX, posY, value, figure) {
	this->vidas = vidas;
}

void Pacman::DrawPacman(char figure, int value) {
	DrawCharacter(figure, value);
}
void Pacman::ErasePacman() {
	EraseCharacter();
}

void Pacman::MoverPacman(Map* map) {//movimiento del pacman en el mapa
	int key;

	DrawPacman(getFigure(), getValue());
	if (_kbhit()) {
		SetdX(0);
		SetdY(0);
		key = _getch();
		switch (key)
		{
		case LEFT:
			if (map->GetMatrix(GetX() - 1, GetY()) == 0)
				SetdX(-1);
			ErasePacman();
			break;
		case RIGHT:
			if (map->GetMatrix(GetX() + 1, GetY()) == 0)
				SetdX(1);
			ErasePacman();
			break;
		case UP:
			if (map->GetMatrix(GetX(), GetY() - 1) == 0)
				SetdY(-1);
			ErasePacman();
			break;
		case DOWN:
			if (map->GetMatrix(GetX(), GetY() + 1) == 0)
				SetdY(1);
			ErasePacman();
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
		SetX(GetX() + GetdX());//movimiento del caracter(pacman) horizontal 
		SetY(GetY() + GetdY());//movimiento del caracter(pacman) vertical
	}
}

// GET AND SET
