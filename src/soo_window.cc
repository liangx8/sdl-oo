#include <exception>
#include <iostream>

#include "soo_window.h"
#include "soo_exception.h"
#include "soo_surface.h"
#include "soo_renderer.h"

SooWindow::SooWindow(const char *title,int x,int y,int w,int h,uint32_t flag) 
{
    mWin=SDL_CreateWindow(title,x,y,w,h,flag);
    if(mWin == nullptr){
        throw EX(SDL_GetError());
    }
    int width,heigh;
    SDL_GetWindowSize(mWin,&width,&heigh);
}
SooSurface* SooWindow::GetSurface(){
    return new SooSurface(SDL_GetWindowSurface(mWin));
}
SooRenderer* SooWindow::CreateRenderer(int index,Uint32 flags){
    auto ren=SDL_CreateRenderer(mWin,index,flags);
    if(ren == NULL){
        throw EX(SDL_GetError());
    }
    SooRenderer *sooRen=new SooRenderer();
    sooRen->mRenderer=ren;
    return sooRen;
}
void SooWindow::UpdateWindowSurface(){
    if(SDL_UpdateWindowSurface(mWin)){
        throw EX(SDL_GetError());
    }
}
void SooWindow::BlitSurface(SooSurface *src)
{
    auto surf=GetSurface();
    auto newSurf=SDL_ConvertSurface(src->mSurf,surf->mSurf->format,0);
    SDL_BlitSurface(newSurf,NULL,surf->mSurf,NULL);
    SDL_FreeSurface(newSurf);
    delete surf;
}
SooWindow::~SooWindow()
{
    const char *title = SDL_GetWindowTitle(mWin);
    std::cout << "SooWindow destruction <<" << title << ">>" << std::endl;
    SDL_DestroyWindow(mWin);
}

