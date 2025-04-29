#pragma once
#include <vector>
using namespace std;

void generate(vector <vector<int>>& v);

bool checkBox(int value, int x, int y, vector <vector<int>>& v);

bool checkRow(int value, int x, int y, vector<vector<int>>& v);

bool checkColumn(int value, int x, int y, vector<vector<int>>& v);

void fillBox(int x, int y, vector<vector<int>>& v);

void fillDiagonal(vector<vector<int>>& v);

bool fullcheck(int value, int x, int y, vector<vector<int>>& v);

bool fillRemaining(vector<vector<int>>& v, int x,int y);