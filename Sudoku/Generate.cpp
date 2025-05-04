#include "Generate.hpp"
#include <iostream>
#include <vector>
using namespace std;

bool checkBox(int value, int x, int y, vector<vector<int>>& v) {
	int FirstX = x - x % 3;
	int FirstY = y - y % 3;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (v[i + FirstX][j + FirstY] == value) return false;
		}
	}
	return true;
}

bool checkRow(int value, int x, int y, vector<vector<int>>& v) {
	for (int i = 0; i < 9; i++) {
		if (v[i][y] == value) return false;
	}
	return true;
}

bool checkColumn(int value, int x, int y, vector<vector<int>>& v) {
	for (int i = 0; i < 9; i++) {
		if (v[x][i] == value) return false;
	}
	return true;
}

bool fullcheck(int value, int x, int y, vector<vector<int>>& v) {
	return (checkBox(value, x, y, v) && checkColumn(value, x, y, v) && checkRow(value, x, y, v));
}

void fillBox(int x, int y, vector<vector<int>>& v) {
	int value;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			do {
				value = rand() % 9 + 1;
			} while (fullcheck(value, i + x, j + y, v) == false);
			v[i + x][j + y] = value;
		}
	}
}

void fillDiagonal(vector<vector<int>>& v) {
	for (int i = 0; i < 9; i += 3) {
		fillBox(i, i, v);
	}
}

bool fillRemaining(vector<vector<int>>& v, int x, int y) {
	if (x == 9) {
		return true;
	}

	if (y == 9) {
		return fillRemaining(v, x + 1, 0);
	}

	if (v[x][y] != 0) {
		return fillRemaining(v, x, y + 1);
	}

	for (int i = 0; i < 9; i++) {
		if (fullcheck(i + 1, x, y, v)) {
			v[x][y] = i + 1;
			if (fillRemaining(v, x, y + 1)) {
				return true;
			}
			v[x][y] = 0;
		}
	}
	return false;
}

void generate(vector<vector<int>>& v) {
	fillDiagonal(v);

	fillRemaining(v, 0, 0);
}

void CreateSudoku(vector<vector<int>>& ans, vector<vector<int>>& sudoku, int k) {
	sudoku = ans;
	while (k > 0) {
		int i = rand() % 9;
		int j = rand() % 9;
		if (sudoku[i][j] != 0) {
			sudoku[i][j] = 0;
			k--;
		}
	}
}