#ifndef SDLOO_H_ADKK323R
#define SDLOO_H_ADKK323R
#include <SDL.h>
#include <exception>
class SooSurface;
class SooRenderer;
class SooWindow{
private:
    SDL_Window *mWin;
    SooSurface *mSurf;
public:
    SooWindow(const char *title,int x,int y,int w,int h,uint32_t flag) ;
    SooSurface* GetSurface();
    SooRenderer* CreateRenderer(int,Uint32);
    void BlitSurface(SooSurface *);
    void UpdateWindowSurface();
    virtual ~SooWindow();
};


#endif