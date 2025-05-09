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
		Graphic::LTexture gameover;
		gameover.LoadFromFile("metal-gear-solid-game-over-screen.png", gRenderer);
		Graphic::LTexture victoryScreen;
		victoryScreen.LoadFromFile("Act_End_Victory.png", gRenderer);
		Graphic::LTexture frame;
		frame.LoadFromFile("Act_StartEnd_Frame.png", gRenderer);

		bool quit = false;
		SDL_Event e;
		a.ResetTimer();

		LButton controlbutton[3][3];
		Graphic::LTexture attemptleft;
		attemptleft.loadFromRenderedText("You have 3 attempt left", { 255,255,255 }, gFont, gRenderer);

		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				controlbutton[i][j].setPosition(SCREEN_WIDTH * 3 / 20 + j * 330 / 3, SCREEN_HEIGHT / 5 + attemptleft.getHeight() + i * 330 / 3, 55 * 2, 55 * 2);
			}
		}

		Graphic::LTexture chosen;
		chosen.loadFromRenderedText("You have not choose any number", { 255,255,255,255 }, gFont, gRenderer);

		SDL_Rect MainGrid = { SCREEN_WIDTH * 10 / 20, SCREEN_HEIGHT / 8, 495, 495 };
		SDL_Rect ControlGrid = { SCREEN_WIDTH * 3 / 20, SCREEN_HEIGHT / 5, 330, 330 };
		int x = 0, y = 0;
		int temp = 0;
		int attemp = 3;

		string current;
		bool victory = false;

		while (quit == false) {
			if (attemp == 0) {
				SDL_Rect ContinueButton = { SCREEN_WIDTH / 2 - gameover.getWidth() / 2 + 142,269,128,16 };
				SDL_Rect QuitButton = { SCREEN_WIDTH / 2 - gameover.getWidth() / 2 + 401,269,81,18 };
				while (attemp == 0 && !quit) {
					while (SDL_PollEvent(&e) != 0) {
						int x, y;
						SDL_GetMouseState(&x, &y);
						if (e.type == SDL_QUIT || (e.type == SDL_MOUSEBUTTONDOWN && insideRect(QuitButton, x, y) == true)) {
							quit = true;
							break;
						}
						
						if ( insideRect(ContinueButton,x,y)==true && e.type == SDL_MOUSEBUTTONDOWN) {
							attemp = 3;
							for (int i = 0; i < 9; i++) {
								for (int j = 0; j < 9; j++) {
									ans[i][j] = 0;
								}
							}
							generate(ans);
							CreateSudoku(ans, sudoku, k);
							for (int i = 0; i < 9; i++) {
								for (int j = 0; j < 9; j++) {
									cells[i][j].free();
									if (sudoku[i][j] == 0) {
										cells[i][j].loadtext(" ", gRenderer, gFont);
										continue;
									}
									cells[i][j].loadtext(to_string(sudoku[i][j]), gRenderer, gFont);
								}
							}
							a.ResetTimer();
							a.free();
							break;
						}
					}
					if (quit) break;

					SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0x00);
					SDL_RenderClear(gRenderer);

					gameover.render(SCREEN_WIDTH / 2 - gameover.getWidth() / 2, 0, gRenderer);
					a.render(SCREEN_WIDTH * 10 / 20, SCREEN_HEIGHT / 20, gRenderer);

					SDL_RenderPresent(gRenderer);

					SDL_Delay(10);
				}
			}
			else if (victory==true) {
				SDL_Rect ContinueButton = { 120 - 10,460 ,348,79 };
				SDL_Rect QuitButton = { 688 - 8,460 ,348,79 };
				Graphic::LTexture conti;
				Graphic::LTexture qui;
				conti.loadFromRenderedText("CONTINUE", { 255,255,255 }, gFont, gRenderer);
				qui.loadFromRenderedText("QUIT", { 255,255,255 }, gFont, gRenderer);
				while (victory && !quit) {
					while (SDL_PollEvent(&e) != 0) {
						int x, y;
						SDL_GetMouseState(&x, &y);
						if (e.type == SDL_QUIT || (e.type == SDL_MOUSEBUTTONDOWN && insideRect(QuitButton, x, y) == true)) {
							quit = true;
							break;
						}

						if (insideRect(ContinueButton, x, y) == true && e.type == SDL_MOUSEBUTTONDOWN) {
							attemp = 3;
							for (int i = 0; i < 9; i++) {
								for (int j = 0; j < 9; j++) {
									ans[i][j] = 0;
								}
							}
							generate(ans);
							CreateSudoku(ans, sudoku, k);
							for (int i = 0; i < 9; i++) {
								for (int j = 0; j < 9; j++) {
									cells[i][j].free();
									if (sudoku[i][j] == 0) {
										cells[i][j].loadtext(" ", gRenderer, gFont);
										continue;
									}
									cells[i][j].loadtext(to_string(sudoku[i][j]), gRenderer, gFont);
								}
							}
							victory = false;
							a.ResetTimer();
							a.free();
							conti.free();
							qui.free();
							break;
						}
					}
					if (quit) break;

					SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0x00);
					SDL_RenderClear(gRenderer);
					SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
					SDL_RenderDrawRect(gRenderer, &QuitButton);
					SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
					SDL_RenderDrawRect(gRenderer, &ContinueButton);
					
					frame.render(SCREEN_WIDTH / 2 - frame.getWidth() / 2, SCREEN_HEIGHT / 2 - frame.getHeight() / 2, gRenderer);
					victoryScreen.render(SCREEN_WIDTH / 2 - victoryScreen.getWidth() / 2, SCREEN_HEIGHT / 2 - victoryScreen.getHeight() / 2, gRenderer);
					
					a.render(SCREEN_WIDTH / 2 + frame.getWidth() / 2 + 32, SCREEN_HEIGHT / 2 + frame.getHeight() / 2 + 32, gRenderer);
					
					conti.render(110 - conti.getWidth() / 2 + 348 / 2, 460 - conti.getHeight() / 2 + 79 / 2, gRenderer);
					qui.render(680 - qui.getWidth() / 2 + 348 / 2, 460 - qui.getHeight() / 2 + 79 / 2, gRenderer);

					SDL_RenderPresent(gRenderer);

					SDL_Delay(10);
				}
			}
			else {
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
						temp = controlnum[y1][x1];
						chosen.loadFromRenderedText("You have chosen the number " + to_string(temp), { 255,255,255,255 }, gFont, gRenderer);
						current = "You have chosen the number " + to_string(temp);
					}
					if (insideRect(MainGrid, x, y) == true && temp != 0 && e.type == SDL_MOUSEBUTTONDOWN) {
						int x1 = (x - MainGrid.x) / (MainGrid.w / 9);
						int y1 = (y - MainGrid.y) / (MainGrid.h / 9);
						if (ans[y1][x1] == temp && sudoku[y1][x1] == 0) {
							sudoku[y1][x1] = temp;
							cells[y1][x1].free();
							cells[y1][x1].loadtext(to_string(temp), gRenderer, gFont);
							chosen.loadFromRenderedText("Correct", { 255,255,255,255 }, gFont, gRenderer);
							current = "Correct";
						}
						else if (sudoku[y1][x1] != 0) {
							chosen.loadFromRenderedText("This cell has been chosen", { 255,255,255,255 }, gFont, gRenderer);
							current = "This cell has been chosen";
						}
						else {
							attemp--;
							chosen.loadFromRenderedText("Wrong answer", { 255,255,255,255 }, gFont, gRenderer);
							current = "Wrong answer";
						}
					}
				}
				SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0x00);
				SDL_RenderClear(gRenderer);

				a.free();
				a.transfer();
				a.loadtime(gRenderer, gFont);
				attemptleft.loadFromRenderedText("You have " + to_string(attemp) + " attempt left", {255,255,255}, gFont, gRenderer);

				for (int i = 0; i < 3; i++) {
					for (int j = 0; j < 3; j++) {
						controlbutton[i][j].render(gRenderer);
					}
				}

				GridLine(495, gRenderer, SCREEN_WIDTH * 10 / 20, SCREEN_HEIGHT / 8);
				GridLine(330, gRenderer, SCREEN_WIDTH * 3 / 20, SCREEN_HEIGHT / 5 + attemptleft.getHeight(), 3);

				rendernumber(cells, SCREEN_WIDTH * 10 / 20, SCREEN_HEIGHT / 8, 495, gRenderer);
				rendernumber(control, SCREEN_WIDTH * 3 / 20, SCREEN_HEIGHT / 5 + attemptleft.getHeight(), 330, gRenderer, 3);

				chosen.render(0, SCREEN_HEIGHT * 2 / 20, gRenderer);
				attemptleft.render(0, SCREEN_HEIGHT * 2 / 20 + chosen.getHeight(), gRenderer);

				a.render(SCREEN_WIDTH * 10 / 20, SCREEN_HEIGHT / 20, gRenderer);

				SDL_RenderPresent(gRenderer);

				if (current == "Correct") {
					SDL_Delay(500);
				}

				if (current == "Wrong answer" || current == "This cell has been chosen") {
					SDL_Delay(500);
				}
				if (ans == sudoku) {
					victory = true;
				}
			}
		}
		gameover.free();
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