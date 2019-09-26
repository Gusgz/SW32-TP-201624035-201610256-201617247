
#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <Windows.h>
using namespace std;
#define ROWS 20
#define COLUMNS 40
class Win {
private:
	int matrix[ROWS][COLUMNS];
	int rows;
	int columns;

public:	Win();
		~Win();
		void SetColor(int value);
		void LoadWin();
private:
	void DrawWin2(int rows, int columns);
public:
	void DrawWin(int rows, int columns);

	int GetRows();
	int GetColumns();
	int GetMatrix(int x, int y);
	void SetMatrix(int x, int y, int value);
};

Win::Win() { this->rows = ROWS; this->columns = COLUMNS; }
Win::~Win() { delete this->matrix; }
void Win::SetColor(int value) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), value);
}
void Win::LoadWin() {
	ifstream File("win.txt");
	if (!File.is_open())
		cout << "Failed" << endl;
	else {
		int r = 0;
		string line;
		while (getline(File, line)) {
			istringstream iss(line);
			for (int c = 0; c < this->columns; c++) {
				string temp;
				getline(iss, temp, ',');
				matrix[r][c] = stoi(temp);
			}
			r++;
		}
	}
	File.close();
}
void Win::DrawWin2(int rows, int columns) {
	if (columns >= 0) {
		DrawWin2(rows, columns - 1);
		switch (matrix[rows][columns])
		{
		case 0: cout << " "; break;
		case 1: SetColor(4); cout << char(219); break;
		case 3:SetColor(2); cout << char(219); break;
		default:
			break;
		}
	}
}
void Win::DrawWin(int rows, int columns) {

	if (rows >= 0) {
		DrawWin(rows - 1, columns);
		if (rows < 20) {
			DrawWin2(rows, columns - 1);
			cout << endl;
		}
	}

}

// --------------------> Get and Set
int Win::GetRows() { return this->rows; }
int Win::GetColumns() { return this->columns; }
int Win::GetMatrix(int x, int y) {
	return matrix[y][x];
}
void Win::SetMatrix(int x, int y, int value) {
	matrix[y][x] = value;
}
#pragma once
