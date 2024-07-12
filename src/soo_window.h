#pragma once

#include <SDL.h>
class SooSurface;
class SooRenderer;
class SooWindow{
private:
    SDL_Window *mWin;
    //std::unique_ptr<SooSurface> mSurf;
public:
    SooWindow(const char *title,int x,int y,int w,int h,uint32_t flag) ;
    SooSurface* GetSurface();
    SooRenderer* CreateRenderer(int,Uint32);
    void BlitSurface(SooSurface *,SDL_Rect *,SDL_Rect *);
    void UpdateWindowSurface();
    void GetSize(int *,int *);
    void GetPos(int *,int *);
    virtual ~SooWindow();
};