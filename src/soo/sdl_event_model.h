#pragma once
#include <SDL2/SDL.h>
#include "soo_model.h"
class SdlEventModel:public SooModel{
protected:
    virtual int onEvent(SDL_Event *)=0;
    virtual int present()=0;
public:
    virtual void attach(void *)=0;
    virtual int execute(void *);
    virtual void detach(void *)=0;
};