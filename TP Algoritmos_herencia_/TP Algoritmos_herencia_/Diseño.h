#pragma once
#include <windows.h>
#include <cstdlib>
#include <stdio.h>
class Diseño
{
public:
	void gotoxy(int x, int y);
	void SetColor(int value);
};

void Diseño::gotoxy(int x, int y)
{
	COORD coord = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void Diseño::SetColor(int value) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), value);
}