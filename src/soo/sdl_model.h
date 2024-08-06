#pragma once
#include <SDL2/SDL.h>
class SdlApplication;
class SdlModel{
public:
    virtual void attach(SDL_Renderer *)=0;
    virtual void onEvent(SDL_Event *ev)=0;
    virtual void present()=0;
    virtual void detach(SDL_Renderer *)=0;
};