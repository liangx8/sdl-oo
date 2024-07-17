#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
class SooWindow;
class SooTexture;
class SooSurface{
public:
    SooSurface(TTF_Font *,const char *);
    SooSurface(const char *image);
    SooSurface(const SooSurface&)=delete;
    virtual ~SooSurface();
    void SetColorKey(int,Uint32);
    int GetHeight();
    int GetWidth();
private:
    SooSurface(SDL_Surface *);
    SDL_Surface *mSurf;
    friend class SooWindow;
};