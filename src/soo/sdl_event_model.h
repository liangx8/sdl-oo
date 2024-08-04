#pragma once
#include <SDL2/SDL.h>
#include "soo_model.h"
class SooApp;
class SdlEventModel:public SooModel{
private:
    SDL_Renderer *m_renderer;
protected:
    virtual int onEvent(void *,SDL_Event *)=0;
    virtual int present(void *)=0;
public:
    virtual void attach()=0;
    virtual int run(void *);
    virtual void detach()=0;
    SdlEventModel(SooApp *,SDL_Renderer *);
};