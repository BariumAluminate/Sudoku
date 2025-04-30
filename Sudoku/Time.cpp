#pragma once

#include <iostream>
#include <sstream>
#include "Graphic.h"
using namespace std;

class Time {
public:
	void load();
	void render(int x, int y);
	void ResetTimer();
	void free();
	void transfer(int milisecond);
private:
	Graphic::LTexture TimeInScreen;
	int hour, minute, second;
};