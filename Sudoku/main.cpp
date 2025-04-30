#include <iostream>
#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <sstream>
#include "Generate.hpp"
#include "Graphic.h"
#include "sudokugrid.hpp"
using namespace std;

int main(int argc, char* args[]) {

	srand(time(0));

	vector<vector<int>> v(9, vector<int>(9, 0));
	generate(v);

	SDL_Window* gWindow = NULL;
	SDL_Renderer* gRenderer = NULL;
	TTF_Font* gFont = NULL;

	vector <vector<cell>> cells(9, vector <cell>(9));


	if (init(gWindow,gRenderer,SCREEN_WIDTH,SCREEN_HEIGHT) == false) {
		cout << "Could not initialized SDL" << endl;
	}
	else if (!load(gFont,cells,v,gRenderer)) {
		cout << "Could not load texture" << endl;
	}
	else {

		bool quit = false;
		SDL_Event e;
		stringstream time;

		while (quit == false) {

			while (SDL_PollEvent(&e) != 0) {
				if (e.type == SDL_QUIT) {
					quit = true;
				}
			}

			SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0x00);
			SDL_RenderClear(gRenderer);

			GridLine(495, gRenderer, SCREEN_WIDTH*10/20, SCREEN_HEIGHT/8);
			GridLine(225, gRenderer, SCREEN_WIDTH * 4 / 20, SCREEN_HEIGHT * 2 / 5, 3);
			rendernumber(cells, SCREEN_WIDTH * 10 / 20, SCREEN_HEIGHT / 8, 495, gRenderer);

			SDL_RenderPresent(gRenderer);
		}
	}
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			cells[i][j].free();
		}
	}
	close(gWindow,gRenderer);
	return 0;
}