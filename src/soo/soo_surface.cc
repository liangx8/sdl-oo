#include <SDL_image.h>
#include <iostream>
#include "soo_surface.h"
#include "soo_texture.h"
#include "soo_exception.h"
SDL_Color TTR_BG={0xea,0,0xff};
SDL_Color TTR_FG={0xea,0xff,0xff};
SooSurface::SooSurface(TTF_Font *font,const char *text)
{
    mSurf=TTF_RenderUTF8(font,text,TTR_FG,TTR_BG);
    if(mSurf==NULL){
        throw EX(TTF_GetError());
    }
    std::cout << "SooSurface construction with string:\"" << text << '"' << std::endl;
}
SooSurface::SooSurface(const char *image)
{
    mSurf = IMG_Load(image);
    if(mSurf==NULL){
        throw EX(SDL_GetError());
    }
}
SooSurface::SooSurface(SDL_Surface *surf):mSurf(surf){}
SooSurface::~SooSurface()
{
    SDL_FreeSurface(mSurf);
}

int SooSurface::GetHeight(){return mSurf->h;}
int SooSurface::GetWidth(){return mSurf->w;}
void SooSurface::SetColorKey(int flags,Uint32 rgb)
{

    Uint32 key=SDL_MapRGB(mSurf->format,(rgb & 0xff),(rgb >> 8) & 0xff,(rgb >> 16)& 0xff);
    if(SDL_SetColorKey(mSurf,flags,key)){
        throw EX(SDL_GetError());
    }
}
// const char* SooSurface::className()
// {
//     return "Class[SooSurface]";
// }
