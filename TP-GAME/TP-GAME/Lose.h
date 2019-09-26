#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <Windows.h>
using namespace std;
#define ROWS 20
#define COLUMNS 40
class Lose {
private:
	int matrix[ROWS][COLUMNS];
	int rows;
	int columns;

public:	Lose();
		~Lose();
		void SetColor(int value);
		void LoadLose();
private:
	void DrawLose2(int rows, int columns);
public:
	void DrawLose(int rows, int columns);

	int GetRows();
	int GetColumns();
	int GetMatrix(int x, int y);
	void SetMatrix(int x, int y, int value);
};

Lose::Lose() { this->rows = ROWS; this->columns = COLUMNS; }
Lose::~Lose() { delete this->matrix; }
void Lose::SetColor(int value) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), value);
}
void Lose::LoadLose() {
	ifstream File("lose.txt");
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
void Lose::DrawLose2(int rows, int columns) {
	if (columns >= 0) {
		DrawLose2(rows, columns - 1);
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
void Lose::DrawLose(int rows, int columns) {

	if (rows >= 0) {
		DrawLose(rows - 1, columns);
		if (rows < 20) {
			DrawLose2(rows, columns - 1);
			cout << endl;
		}
	}

}

// --------------------> Get and Set
int Lose::GetRows() { return this->rows; }
int Lose::GetColumns() { return this->columns; }
int Lose::GetMatrix(int x, int y) {
	return matrix[y][x];
}
void Lose::SetMatrix(int x, int y, int value) {
	matrix[y][x] = value;
}
#pragma once
