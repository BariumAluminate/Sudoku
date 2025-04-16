#include "Generate.hpp"
#include <iostream>
#include <vector>
using namespace std;

void fill(vector<vector<int>>& v) {
	vector<int> temp(9);
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			temp[j] = (i + j ) % 9 + 1;
		}
		v.push_back(temp);
	}
	temp.clear();
}

void ColumnSwap(int i, int j, vector<vector<int>>& v) {
	//swap 2 cot i va j voi nhau
	for (int k = 0; k < 9; k++) {
		swap(v[k][i], v[k][j]);
	}
}

void RowSwap(int i, int j, vector<vector<int>>& v) {
	for (int k = 0; k < 9; k++) {
		swap(v[i][k], v[j][k]);
	}
}

void generate(vector<vector<int>>& v) {
	fill(v);
	int t = 217,i,j;
	while (t>0) {
		i = rand() % 9;
		j = rand() % 9;
		if (i != j) {
			ColumnSwap(i, j, v);
			t--;
		}
	}
	t = 217;
	while (t > 0) {
		i = rand() % 9;
		j = rand() % 9;
		if (i != j) {
			RowSwap(i, j, v);
			t--;
		}
	}
}