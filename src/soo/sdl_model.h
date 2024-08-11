#pragma once
#include <SDL2/SDL.h>
class SdlApplication;
class SdlModel{
public:
    virtual void attach(SdlApplication *)=0;
    virtual void onEvent(SDL_Event *ev)=0;
    virtual void present(SdlApplication *)=0;
    virtual void detach(SdlApplication *)=0;
};