#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
using namespace std;

bool init(SDL_Window*& gWindow, SDL_Renderer*& gRenderer, int w, int h);

void close(SDL_Window*& gWindow, SDL_Renderer*& gRenderer);

namespace Graphic {
	class LTexture {
	public:
		LTexture();
		~LTexture();
		void free();
		int getHeight() const;
		int getWidth() const;
		bool LoadFromFile(string path,SDL_Renderer*& gRenderer);
		void render(int x, int y, SDL_Renderer*& gRenderer, SDL_Rect* Clips = NULL, double angle = 0, SDL_Point* center = NULL, SDL_RendererFlip = SDL_FLIP_NONE);
		void SetColor(Uint8 r, Uint8 g, Uint8 b);
		bool loadFromRenderedText(string textureText, SDL_Color textColor,TTF_Font* gFont, SDL_Renderer* gRenderer);
	private:
		SDL_Texture* mTexture;
		int w, h;
	};
}
