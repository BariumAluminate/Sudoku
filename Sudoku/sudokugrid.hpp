#pragma once

#include <iostream>
#include "Graphic.h"
#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
using namespace std;

const int SCREEN_WIDTH = 1072;
const int SCREEN_HEIGHT = 603;
const int font_size = 30;

class cell {
private:
	bool show;
	Graphic::LTexture number;
public:
	cell();
	void render(int x, int y,SDL_Renderer* gRenderer);
	void change(bool a);
	void loadtext(string message, SDL_Renderer* gRenderer, TTF_Font* gFont);
	void free();
	int getWidth() const;
	int getHeight() const;
};

void GridLine(int n, SDL_Renderer* gRenderer, int x, int y, int Grid_Number = 9);

void rendernumber(vector <vector<cell>>& cells, int x, int y, int n, SDL_Renderer* gRenderer);

bool load(TTF_Font* gFont, vector<vector<cell>>& cells, vector<vector<int>> v, SDL_Renderer* gRenderer);

void RenderInControl();