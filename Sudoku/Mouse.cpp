#include "Mouse.hpp"
using namespace std;

LButton::LButton() {
	button = { 0, 0, 0, 0 };
	mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
}

void LButton::setPosition(int x, int y, int w, int h) {
	button = { x,y,w,h };
}

void LButton::handleEvent(SDL_Event* e) {
	if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP) {
		int x, y;
		SDL_GetMouseState(&x, &y);

		bool inside = false;

		if (x - button.x >= 0 && x - button.x <= button.w && y - button.y >= 0 && y - button.y <= button.h) {
			inside = true;
		}

		if (!inside) {
			mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
		}
		else {
			switch (e->type) {
			case SDL_MOUSEMOTION:
				mCurrentSprite = BUTTON_SPRITE_MOUSE_OVER_MOTION;
				break;
			case SDL_MOUSEBUTTONDOWN:
				mCurrentSprite = BUTTON_SPRITE_MOUSE_DOWN;
				break;
			case SDL_MOUSEBUTTONUP:
				mCurrentSprite = BUTTON_SPRITE_MOUSE_UP;
				break;
			}
		}
	}
}

void LButton::render(SDL_Renderer* gRenderer) {
	Uint8 r, g, b, a;
	r = buttoncolor[mCurrentSprite].r;
	g = buttoncolor[mCurrentSprite].g;
	b = buttoncolor[mCurrentSprite].b;
	a = buttoncolor[mCurrentSprite].a;
	SDL_SetRenderDrawColor(gRenderer, r, g, b, a);
	SDL_RenderFillRect(gRenderer, &button);
}

bool insideRect(SDL_Rect a, int x, int y) {
		if (x - a.x >= 0 && y - a.y >= 0 && x - a.x <= a.w && y - a.y <= a.h) {
			return true;
		}
		return false;
}