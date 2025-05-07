#pragma once

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
using namespace std;

const SDL_Color buttoncolor[4] = {
    {0,0,0,0},
    {0,0,64,0},
    {0,64,0,0},
    {0,64,0,0},
};

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
    void setPosition(int x, int y, int w, int h);

    //Handles mouse event
    void handleEvent(SDL_Event* e);

    //Shows button sprite
    void render( SDL_Renderer* gRenderer);

private:
    SDL_Rect button;
    
    LButtonSprite mCurrentSprite;
};

bool insideRect(SDL_Rect a, int x, int y);