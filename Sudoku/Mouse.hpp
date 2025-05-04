#pragma once

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
using namespace std;

enum LButtonSprite
{
    BUTTON_SPRITE_MOUSE_OUT = 0,
    BUTTON_SPRITE_MOUSE_OVER_MOTION = 1,
    BUTTON_SPRITE_MOUSE_DOWN = 2,
    BUTTON_SPRITE_MOUSE_UP = 3,
    BUTTON_SPRITE_TOTAL = 4
};

class LButton
{
public:
    //Initializes internal variables
    LButton();

    //Sets top left position
    void setPosition(int x, int y);

    //Handles mouse event
    void handleEvent(SDL_Event* e, SDL_Rect button);

    //Shows button sprite
    void render(SDL_Rect button, SDL_Renderer* gRenderer);

private:
    //Top left position
    SDL_Point mPosition;

    //Currently used global sprite
    LButtonSprite mCurrentSprite;
};