#define _CRT_SECURE_NO_WARNINGS // N
#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING

#include <iostream>
#include "Menu.h"


typedef unsigned long ulong;

int main()
{
	Menu* menu=new Menu();
	menu->SeeMenu();	
	std::cin.get();
	return 0;
}