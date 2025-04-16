#include <iostream>
#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Generate.hpp"
#include "Graphic.h"
using namespace std;

int main(int argc, char* args[]) {
	srand(time(0));
	vector<vector<int>> v;
	generate(v);
	SDL_Window* gWindow = NULL;
	SDL_Renderer* gRenderer = NULL;
	if (init(gWindow,gRenderer,640,480) == false) {
		cout << "Could not initialized SDL" << endl;
	}
	else {
		bool quit = false;
		SDL_Event e;
		while (quit == false) {
			while (SDL_PollEvent(&e) == 0) {
				if (e.type == SDL_QUIT) {
					quit = true;
				}
			}
			SDL_RenderClear(gRenderer);
		}
	}
}