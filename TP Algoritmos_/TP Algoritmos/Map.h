#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <Windows.h>

using namespace std;
#define ROWS 31
#define COLUMNS 60
class Map {
private:
	int matrix[ROWS][COLUMNS];
	int rows;
	int columns;

public:	Map();
		~Map();
		void SetColor(int value);
		void LoadMap();
		void SaveMap();
		void DrawMap2(int rows, int columns);//2
		void DrawMap(int rows, int columns);//1
		void prueba();

		int GetRows();
		int GetColumns();
		int GetMatrix(int x, int y);
		void SetMatrix(int x, int y, int value);
};

Map::Map() { this->rows = ROWS; this->columns = COLUMNS; }
Map::~Map() { delete this->matrix; }
void Map::SetColor(int value) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), value);
}
void Map::LoadMap() {
	ifstream File("Map.txt");
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
void Map::SaveMap() {
	ofstream File("Map.txt");
	if (!File.is_open())
		cout << "Failed" << endl;
	else {
		for (int i = 0; i < this->rows; i++) {
			for (int j = 0; j < this->columns; j++) {
				File << matrix[i][j] << ',';
			}
			File << endl;
		}
	}
	File.close();
}
void Map::DrawMap2(int rows, int columns) {
	if (columns >= 0) {
		DrawMap2(rows, columns - 1);
		switch (matrix[rows][columns])
		{
		case 0: SetColor(1); cout << char(205); break;
		case 1: SetColor(15); cout << char(250); break;
		case 2: cout << " "; break;
		case 3: SetColor(1); cout << char(188); break;
		case 4: SetColor(1); cout << char(200); break;
		case 5: SetColor(1); cout << char(201); break;
		case 6: SetColor(1); cout << char(187); break;
		case 7: SetColor(1); cout << char(202); break;
		case 8: SetColor(0); cout << char(184); break;
		case 9: SetColor(1); cout << char(186); break;
		default:
			break;
		}
	}
}
void Map::DrawMap(int rows, int columns) {
	if (rows >= 0) {
		DrawMap(rows - 1, columns);
		DrawMap2(rows, columns - 1);
		cout << endl;
	}
}
void Map::prueba() {
	for (int i = 0; i < this->rows; i++) {
		for (int j = 0; j < this->columns; j++) {
			switch (matrix[i][j])
			{
			case 0: SetColor(1); cout << char(205); break;
			case 1: SetColor(15); cout << char(250); break;
			case 2: cout << " "; break;
			case 3: SetColor(1); cout << char(188); break;
			case 4: SetColor(1); cout << char(200); break;
			case 5: SetColor(1); cout << char(201); break;
			case 6: SetColor(1); cout << char(187); break;
			case 7: SetColor(1); cout << char(202); break;
			case 8: SetColor(0); cout << char(184); break;
			case 9: SetColor(1); cout << char(186); break;
			default:
				break;
			}
		}
		cout << endl;
	}
}
// GET AND SET
int Map::GetRows() { return this->rows; }
int Map::GetColumns() { return this->columns; }
int Map::GetMatrix(int x, int y) {
	return matrix[y][x];
}
void Map::SetMatrix(int x, int y, int value) {
	matrix[y][x] = value;
}
