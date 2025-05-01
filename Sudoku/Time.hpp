#pragma once

#include <iostream>
#include <sstream>
#include "Graphic.h"
using namespace std;

class Time {
public:
	bool loadtime(SDL_Renderer* gRenderer);
	void render(int x, int y, SDL_Renderer* gRenderer);
	void ResetTimer();
	void free();
	void transfer();
	Time();
private:
	Graphic::LTexture TimeInScreen;
	int Startime;
	int hour, minute, second;
};