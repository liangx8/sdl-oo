#pragma once
class SDL_Renderer;
class SdlView{
public:
    virtual int paint(SDL_Renderer *)=0;
};