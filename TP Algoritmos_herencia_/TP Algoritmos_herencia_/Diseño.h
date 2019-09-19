#pragma once
#include <windows.h>
#include <cstdlib>
#include <stdio.h>
class Dise�o
{
public:
	void gotoxy(int x, int y);
	void SetColor(int value);
};

void Dise�o::gotoxy(int x, int y)
{
	COORD coord = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void Dise�o::SetColor(int value) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), value);
}