#pragma once
#include <Windows.h>
#include <cstdlib>
#include <stdio.h>
class Design
{
public:
	void Gotoxy(int x, int y);
	void SetColor(int value);
};

void Design::Gotoxy(int x, int y)
{
	COORD coord = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void Design::SetColor(int value) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), value);
}