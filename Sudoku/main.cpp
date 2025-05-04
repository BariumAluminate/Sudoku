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

	vector<vector<int>> ans(9, vector<int>(9, 0));
	vector<vector<int>> sudoku(9, vector<int>(9));
	
	generate(ans);

	int k = 30;
	CreateSudoku(ans, sudoku, k);

	SDL_Window* gWindow = NULL;
	SDL_Renderer* gRenderer = NULL;
	TTF_Font* gFont = NULL;
	TTF_Font* afont = NULL;

	vector <vector<cell>> cells(9, vector <cell>(9));

	vector <vector<cell>> control(3, vector<cell>(3));

	Time a;

	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			cout << ans[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;

	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			cout << sudoku[i][j] << " ";
		}
		cout << endl;
	}

	if (init(gWindow,gRenderer,SCREEN_WIDTH,SCREEN_HEIGHT) == false) {
		cout << "Could not initialized SDL" << endl;
	}
	else {
		gFont = TTF_OpenFont("Arial.ttf", 30);
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {
				if (sudoku[i][j] == 0) {
					cells[i][j].loadtext(" ", gRenderer, gFont);
					continue;
				}
				cells[i][j].loadtext(to_string(sudoku[i][j]), gRenderer, gFont);
			}
		}

		int index = 1;

		afont = TTF_OpenFont("Arial.ttf", 50);

		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				control[i][j].loadtext(to_string(index), gRenderer, afont);
				index++;
			}
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
			

			SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0x00);
			SDL_RenderClear(gRenderer);
			
			a.free();
			a.transfer();
			a.loadtime(gRenderer, gFont);

			GridLine(495, gRenderer, SCREEN_WIDTH*10/20, SCREEN_HEIGHT/8);
			GridLine(330, gRenderer, SCREEN_WIDTH * 3 / 20, SCREEN_HEIGHT / 5, 3);
			rendernumber(cells, SCREEN_WIDTH * 10 / 20, SCREEN_HEIGHT / 8, 495, gRenderer);
			rendernumber(control, SCREEN_WIDTH * 3 / 20, SCREEN_HEIGHT / 5, 330, gRenderer, 3);
			SDL_Rect MainGrid = { SCREEN_WIDTH * 10 / 20, SCREEN_HEIGHT / 8, 495, 495 };
			SDL_Rect ControlGrid = { SCREEN_WIDTH * 3 / 20, SCREEN_HEIGHT / 5, 330, 330 };
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

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			control[i][j].freespace();
		}
	}

	close(gWindow,gRenderer,gFont);

	if (gFont != NULL) {
		TTF_CloseFont(afont);
		gFont = NULL;
	}
	return 0;
}