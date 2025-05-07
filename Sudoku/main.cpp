#include <iostream>
#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <sstream>
#include <chrono>
#include <thread>
#include "Generate.hpp"
#include "Graphic.h"
#include "sudokugrid.hpp"
#include "Time.hpp"
#include "Mouse.hpp"
using namespace std;

int main(int argc, char* args[]) {

	srand(time(0));

	vector<vector<int>> ans(9, vector<int>(9, 0));
	vector<vector<int>> sudoku(9, vector<int>(9));
	vector<vector<int>> controlnum(3, vector<int>(3));
	
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
				controlnum[i][j] = index; 
				cout << controlnum[i][j]<<" ";
				index++;
			}
			cout << endl;
		}
		
		bool quit = false;
		SDL_Event e;
		a.ResetTimer();

		LButton controlbutton[3][3];

		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				controlbutton[i][j].setPosition(SCREEN_WIDTH * 3 / 20 + j * 330 / 3, SCREEN_HEIGHT / 5 + i * 330 / 3, 55 * 2, 55 * 2);
			}
		}

		SDL_Rect MainGrid = { SCREEN_WIDTH * 10 / 20, SCREEN_HEIGHT / 8, 495, 495 };
		SDL_Rect ControlGrid = { SCREEN_WIDTH * 3 / 20, SCREEN_HEIGHT / 5, 330, 330 };
		int x = 0, y = 0;
		int temp = 0;
		Graphic::LTexture chosen;
		chosen.loadFromRenderedText("You have not choose any number", { 255,255,255,255 }, gFont, gRenderer);
		string current;
		while (quit == false) {
			if (temp == 0) {
				chosen.loadFromRenderedText("You have not choose any number", { 255,255,255,255 }, gFont, gRenderer);
				current = "You have not choose any number";
			}
			while (SDL_PollEvent(&e) != 0) {
				if (e.type == SDL_QUIT) {
					quit = true;
				}
				SDL_GetMouseState(&x, &y);
				for (int i = 0; i < 3; i++) {
					for (int j = 0; j < 3; j++) {
						controlbutton[i][j].handleEvent(&e);
					}
				}
				if (insideRect(ControlGrid, x, y) == true && e.type == SDL_MOUSEBUTTONDOWN) {
					int x1 = (x - ControlGrid.x) / (ControlGrid.w / 3);
					int y1 = (y - (ControlGrid.y)) / (ControlGrid.h / 3);
					cout << x1 << " " << y1 << endl;
					temp = controlnum[y1][x1];
					chosen.loadFromRenderedText("You have chosen the number " + to_string(temp), { 255,255,255,255 }, gFont, gRenderer);
					cout << temp << endl;
					current = "You have chosen the number " + to_string(temp);
				}
				if (insideRect(MainGrid, x, y) == true && temp != 0 && e.type == SDL_MOUSEBUTTONDOWN) {
					int x1 = (x - MainGrid.x) / (MainGrid.w / 9);
					int y1 = (y - MainGrid.y) / (MainGrid.h / 9);
					cout << x1 << " " << y1 << endl;
					if (ans[y1][x1] == temp) {
						sudoku[y1][x1] = temp;
						cells[y1][x1].free();
						cells[y1][x1].loadtext(to_string(temp), gRenderer, gFont);
						chosen.loadFromRenderedText("Correct", { 255,255,255,255 }, gFont, gRenderer);
						current = "Correct";
					}
					cout << sudoku[y1][x1] << endl;
					temp = 0;
				}
			}
			SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0x00);
			SDL_RenderClear(gRenderer);
			
			a.free();
			a.transfer();
			a.loadtime(gRenderer, gFont);

			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					controlbutton[i][j].render(gRenderer);
				}
			}
			GridLine(495, gRenderer, SCREEN_WIDTH*10/20, SCREEN_HEIGHT/8);
			GridLine(330, gRenderer, SCREEN_WIDTH * 3 / 20, SCREEN_HEIGHT / 5, 3);
			rendernumber(cells, SCREEN_WIDTH * 10 / 20, SCREEN_HEIGHT / 8, 495, gRenderer);
			rendernumber(control, SCREEN_WIDTH * 3 / 20, SCREEN_HEIGHT / 5, 330, gRenderer, 3);
			chosen.render(0, SCREEN_HEIGHT * 2 / 20, gRenderer);
			a.render(SCREEN_WIDTH * 10 / 20, SCREEN_HEIGHT / 20, gRenderer);
			SDL_RenderPresent(gRenderer);
			if (current == "Correct") {
				this_thread::sleep_for(chrono::seconds(1));
			}
		}
	}

	a.free();

	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			cells[i][j].free();
		}
	}

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			control[i][j].free();
		}
	}

	close(gWindow,gRenderer,gFont);

	if (gFont != NULL) {
		TTF_CloseFont(afont);
		gFont = NULL;
	}
	return 0;
}