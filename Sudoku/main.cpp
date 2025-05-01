#include <iostream>
#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <sstream>
#include "Generate.hpp"
#include "Graphic.h"
#include "sudokugrid.hpp"
#include "Time.hpp"
using namespace std;

int main(int argc, char* args[]) {

	srand(time(0));

	vector<vector<int>> v(9, vector<int>(9, 0));
	generate(v);

	SDL_Window* gWindow = NULL;
	SDL_Renderer* gRenderer = NULL;

	vector <vector<cell>> cells(9, vector <cell>(9));

	Time a;

	Graphic::LTexture numberInControl[9];


	if (init(gWindow,gRenderer,SCREEN_WIDTH,SCREEN_HEIGHT) == false) {
		cout << "Could not initialized SDL" << endl;
	}
	else {

		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {
				cells[i][j].loadtext(to_string(v[i][j]), gRenderer);
			}
		}

		for (int i = 0; i < 9; i++) {
			SDL_Color color = { 255,255,255 };
			TTF_Font* gFont = TTF_OpenFont("Arial.ttf", 30);
			numberInControl[i].loadFromRenderedText(to_string(i + 1), color, gFont, gRenderer);
		}

		bool quit = false;
		SDL_Event e;
		a.ResetTimer();

		while (quit == false) {

			while (SDL_PollEvent(&e) != 0) {
				if (e.type == SDL_QUIT) {
					quit = true;
				}
			}
			
			a.transfer();
			a.loadtime(gRenderer);

			SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0x00);
			SDL_RenderClear(gRenderer);

			GridLine(495, gRenderer, SCREEN_WIDTH*10/20, SCREEN_HEIGHT/8);
			GridLine(330, gRenderer, SCREEN_WIDTH * 3 / 20, SCREEN_HEIGHT / 5, 3);
			rendernumber(cells, SCREEN_WIDTH * 10 / 20, SCREEN_HEIGHT / 8, 495, gRenderer);

			a.render(SCREEN_WIDTH * 10 / 20, SCREEN_HEIGHT / 20, gRenderer);

			SDL_RenderPresent(gRenderer);
		}
	}

	a.free();

	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			cells[i][j].freespace();
		}
	}
	close(gWindow,gRenderer);
	return 0;
}