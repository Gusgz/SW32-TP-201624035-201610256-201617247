#pragma once
#include <windows.h>
#include <cstdlib> // system("color xy")
#include <stdio.h>
class gotoxy
{
public:
	void got(int x, int y);

};

void gotoxy::got(int x, int y)
{
	COORD coord = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

