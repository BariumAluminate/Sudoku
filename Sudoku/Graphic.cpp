#include "Graphic.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <fstream>
#include <stdexcept>
using namespace std;

bool init(SDL_Window*& gWindow, SDL_Renderer*& gRenderer, int w, int h) {
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		throw std::runtime_error("Fail to initialized SDL! SDL Error: " + std::string(SDL_GetError()));
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}

		//Create window
		gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			throw std::runtime_error("Fail to create window! SDL Error: " + std::string(SDL_GetError()));
			success = false;
		}
		else
		{
			//Create renderer for window
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
			if (gRenderer == NULL)
			{
				throw std::runtime_error("Fail to create renderer! SDL Error: " + std::string(SDL_GetError()));
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00,0x00);

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					throw std::runtime_error("Fail to initialized SDL image! SDL image Error: " + std::string(IMG_GetError()));
					success = false;
				}
				if (TTF_Init() == -1)
				{
					throw std::runtime_error("SDL_ttf could not initialize! SDL_ttf Error: " + std::string(TTF_GetError()));
					success = false;
				}
			}
		}
	}

	return success;
}

int Graphic::LTexture::getHeight() const {
	return h;
}

int Graphic::LTexture::getWidth() const {
	return w;
}

bool Graphic::LTexture::LoadFromFile(string path,SDL_Renderer*& gRenderer) {
	free();
	SDL_Texture* newTexture = NULL;
	SDL_Surface* surface = IMG_Load(path.c_str());
	if (surface == NULL) {
		throw std::runtime_error("Failed to load image. SDL error: " + std::string(IMG_GetError()));
	}
	else {
		newTexture = SDL_CreateTextureFromSurface(gRenderer, surface);
		if (newTexture == NULL) {
			throw std::runtime_error("Unable to convert surface into texture. SDL error: " + std::string(SDL_GetError()));
		}
		else {
			mTexture = newTexture;
			w = surface->w;
			h = surface->h;
		}
	}
	SDL_FreeSurface(surface);
	return mTexture != NULL;
}

Graphic::LTexture::LTexture() {
	mTexture = NULL;
	w = 0;
	h = 0;
}

Graphic::LTexture::~LTexture() {
	free();
}

void Graphic::LTexture::free() {
	if (mTexture != NULL) {
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
	}
	w = 0;
	h = 0;
}


void Graphic::LTexture::render(int x, int y, SDL_Renderer*& gRenderer, SDL_Rect* Clips,double angle,SDL_Point* center, SDL_RendererFlip flip) {
	SDL_Rect renderQuad = { x,y,w,h };
	if (Clips != NULL) {
		renderQuad.w = Clips->w;
		renderQuad.h = Clips->h;
	}
	SDL_RenderCopy(gRenderer, mTexture, Clips, &renderQuad);
}

void Graphic::LTexture::SetColor(Uint8 r, Uint8 g, Uint8 b) {
	SDL_SetTextureColorMod(mTexture, r, g, b);
}

void close(SDL_Window*& gWindow, SDL_Renderer*& gRenderer, TTF_Font*& gFont) {
	if (gFont != NULL) {
		TTF_CloseFont(gFont);
		gFont = NULL;
	}
	if (gRenderer != NULL) {
		SDL_DestroyRenderer(gRenderer);
		gRenderer = NULL;
	}
	if (gWindow != NULL) {
		SDL_DestroyWindow(gWindow);
		gWindow = NULL;
	}
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}


bool Graphic::LTexture::loadFromRenderedText(std::string textureText, SDL_Color textColor,TTF_Font* gFont, SDL_Renderer* gRenderer)
{
	//Get rid of preexisting texture
	free();

	//Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, textureText.c_str(), textColor);
	if (textSurface == NULL)
	{
		throw std::runtime_error("Unable to render text surface! SDL_ttf Error:" + string(TTF_GetError()));
	}
	else
	{
		//Create texture from surface pixels
		mTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
		if (mTexture == NULL)
		{
			printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
		}
		else
		{
			//Get image dimensions
			w = textSurface->w;
			h = textSurface->h;
		}

		//Get rid of old surface
		SDL_FreeSurface(textSurface);
	}

	//Return success
	return mTexture != NULL;
}
