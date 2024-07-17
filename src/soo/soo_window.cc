#include <exception>
#include <iostream>

#include "soo_window.h"
#include "soo_exception.h"
#include "soo_surface.h"
#include "soo_renderer.h"

SooWindow::SooWindow(const char *title,int x,int y,int w,int h,uint32_t flag) 
{
#if 0
    SDL_Renderer *render;
    if(SDL_CreateWindowAndRenderer(w,h,flag,&mWin,&render)){
        throw EX(SDL_GetError());
    }
    SDL_SetWindowTitle(mWin,title);
    m_render=std::unique_ptr<SooRenderer>(new SooRenderer(render));
#else
    mWin=SDL_CreateWindow(title,x,y,w,h,flag);
    if(mWin==nullptr){
        throw EX(SDL_GetError());
    }
    m_render=nullptr;
#endif
}
void SooWindow::GetSize(int *w,int *h){
    SDL_GetWindowSize(mWin,w,h);
}
void SooWindow::GetPos(int *rx,int *ry)
{
    SDL_GetWindowPosition(mWin,rx,ry);
}
SooSurface* SooWindow::GetSurface(){
    SDL_Surface *surf=SDL_GetWindowSurface(mWin);
    if(surf==NULL){
        throw EX(SDL_GetError());
    }
    return new SooSurface(surf);
}
SooRenderer* SooWindow::CreateRenderer(int index,Uint32 flags){
    if(m_render==nullptr){
        SDL_Renderer *rdr=SDL_CreateRenderer(mWin,index,flags);
        if(rdr==nullptr){
            throw EX(SDL_GetError());
        }
        m_render=new SooRenderer(rdr);
        std::cout << std::hex << rdr << m_render <<std::endl;
    }
    return m_render;
}
void SooWindow::UpdateWindowSurface(){
    if(SDL_UpdateWindowSurface(mWin)){
        throw EX(SDL_GetError());
    }
}
void SooWindow::BlitSurface(SooSurface *src,SDL_Rect *srcr,SDL_Rect *dstr)
{
    auto surf=GetSurface();
    auto newSurf=SDL_ConvertSurface(src->mSurf,surf->mSurf->format,0);
    SDL_BlitSurface(newSurf,srcr,surf->mSurf,dstr);
    SDL_FreeSurface(newSurf);
    delete surf;
}
SooWindow::~SooWindow()
{
    const char *title = SDL_GetWindowTitle(mWin);
    std::cout << "SooWindow destruction <<" << title << ">>" << std::endl;
    if(m_render){
        delete m_render;
    }
    SDL_DestroyWindow(mWin);

    
}

