#pragma once
#include <SDL2/SDL.h>
class SdlView{
public:
    virtual int paint(SDL_Renderer *)=0;
};

SdlView *drawRect(SDL_Rect *,Uint32 color);
SdlView *fillRect(SDL_Rect *,Uint32 color);
void viewRelease();