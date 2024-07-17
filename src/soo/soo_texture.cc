#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include "soo_renderer.h"
#include "soo_texture.h"
#include "soo_exception.h"

SooTexture::SooTexture(SooRenderer *render,const char *image){
    SDL_Texture *texture=IMG_LoadTexture(render->mRenderer,image);
    if(texture==NULL){
        throw EX(IMG_GetError());
    }
    mTexture=texture;
}
SooTexture::SooTexture(SooRenderer *render,TTF_Font *font,const char *text,SDL_Color color){
    SDL_Surface *surf=TTF_RenderUTF8_Solid(font,text,color);
    if(surf == NULL){
        throw EX(TTF_GetError());
    }
    SDL_Texture *texture=SDL_CreateTextureFromSurface(render->mRenderer,surf);
    SDL_FreeSurface(surf);
    if(texture==NULL){
        throw EX(SDL_GetError());
    }
    mTexture=texture;
}
SooTexture::SooTexture(SooRenderer *render,Uint32 format,int access,int w,int h)
{
    SDL_Texture *texture=SDL_CreateTexture(render->mRenderer,format,access,w,h);
    if(texture==NULL){
        throw EX(SDL_GetError());
    }
    mTexture=texture;
}

SooTexture::~SooTexture()
{
    SDL_DestroyTexture(mTexture);
}

void SooTexture::GetSize(int *w,int *h)
{
    if(SDL_QueryTexture(mTexture,NULL,NULL,w,h)){
        throw EX(SDL_GetError());
    }
}
void SooTexture::SetColor(Uint8 r,Uint8 g, Uint8 b)
{
    if(SDL_SetTextureColorMod(mTexture,r,g,b)){
        throw EX(SDL_GetError());
    }
}
void SooTexture::SetAlphaMod(Uint8 alpha)
{
    if(SDL_SetTextureAlphaMod(mTexture,alpha)){
        throw EX(SDL_GetError());
    }    
}
void SooTexture::render(SooRenderer *target,SDL_Rect *src,SDL_Rect *dst)
{
    if(SDL_RenderCopy(target->mRenderer,mTexture,src,dst)){
        throw EX(SDL_GetError());
    }
}
void SooTexture::setRenderTarget(SooRenderer *render)
{
    if(SDL_SetRenderTarget(render->mRenderer,mTexture)){
        throw EX(SDL_GetError());
    }

}
void SooTexture::modify(const SDL_Rect* r,pixelMofify fn)
{
    void *pixels;
    int pitch;
    if(SDL_LockTexture(mTexture,r,&pixels,&pitch)){
        throw EX(SDL_GetError());
    }
    int height=0;
    // fixme:
    if(r){
        std::cout <<"rw:"<< r->w << "rh:" << r->h << std::endl;
    }
    fn(pixels,pitch,height);
    SDL_UnlockTexture(mTexture);
}
// const char* SooTexture::className()
// {
//     return "Class[SooTexture]";
// }
