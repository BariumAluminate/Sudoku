#include "sudokugrid.hpp"
#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <string>
#include "Graphic.h"
using namespace std;

int cell::getWidth() const {
	return number.getWidth();
}

int cell::getHeight() const {
	return number.getHeight();
}

void cell::change(bool a) {
	show = a;
}

cell::cell() {
	show = true;
}

void cell::free() {
	number.free();
}

void cell::render(int x, int y, SDL_Renderer* gRenderer) {
	number.render(x, y, gRenderer);
}

void GridLine(int n, SDL_Renderer* gRenderer, int x,int y, int GridNumber) {
	SDL_Rect outlineRect = { x, y, n, n };
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderDrawRect(gRenderer, &outlineRect);
	for (int i = 0; i < GridNumber; i++) {
		for (int j = 0; j < GridNumber; j++) {
			SDL_Rect grid = { x + i * n / GridNumber, y + j * n / GridNumber , n / GridNumber,n / GridNumber };
			SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
			SDL_RenderDrawRect(gRenderer, &grid);
		}
	}
}

void cell::loadtext(string message, SDL_Renderer* gRenderer,TTF_Font* gFont) {
	SDL_Color textColor = { 255, 255, 255 };
	number.loadFromRenderedText(message, textColor, gFont, gRenderer);
}

bool load(TTF_Font* gFont, vector<vector<cell>>& cells, vector<vector<int>> v,SDL_Renderer* gRenderer) {
	bool success = true;
	gFont = TTF_OpenFont("Arial.ttf", font_size);
	if (gFont == NULL) {
		throw std::runtime_error("Unable to load font" + string(TTF_GetError()));
	}
	else {
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {
				cells[i][j].loadtext(to_string(v[i][j]), gRenderer, gFont);
			}
		}
	}
	return success;
}

void rendernumber(vector <vector<cell>>& cells, int x, int y, int n, SDL_Renderer* gRenderer) {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			cells[i][j].render(x + i * n / 9 + (n / 9 - cells[i][j].getWidth() ) / 2, y + j * n / 9 + (n / 9 - cells[i][j].getHeight() ) / 2, gRenderer);
		}
	}
}

void cell::free() {
	number.free();
}