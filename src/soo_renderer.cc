#include <SDL_image.h>
#include <iostream>
#include "soo_renderer.h"
#include "soo_texture.h"
#include "soo_exception.h"

SooRenderer::SooRenderer(SDL_Renderer *ren):mRenderer(ren){}
SooRenderer::~SooRenderer(){
    SDL_DestroyRenderer(mRenderer);
    std::cout << "SooRenderer destruction" << std::endl;
}
void SooRenderer::SetDrawColor(Uint8 r,Uint8 g,Uint8 b,Uint8 a){
    if(SDL_SetRenderDrawColor(mRenderer,r,g,b,a)){
        throw EX(SDL_GetError());
    }
}
void SooRenderer::Clear(){
    if(SDL_RenderClear(mRenderer)){
        throw EX(SDL_GetError());
    }
}

void SooRenderer::SetViewport(const SDL_Rect *rect){
    if(SDL_RenderSetViewport(mRenderer,rect)){
        throw EX(SDL_GetError());
    }
}
void SooRenderer::DrawRect(const SDL_Rect *rect)
{
    if(SDL_RenderDrawRect(mRenderer,rect)){
        throw EX(SDL_GetError());
    }
}
void SooRenderer::FillRect(const SDL_Rect *rect){

    if(SDL_RenderFillRect(mRenderer,rect)){
        throw EX(SDL_GetError());
    }
}
void SooRenderer::Present() {
    SDL_RenderPresent(mRenderer);
}
void SooRenderer::DrawLine(int x1,int y1,int x2,int y2){
    if(SDL_RenderDrawLine(mRenderer,x1,y1,x2,y2)){
        throw EX(SDL_GetError());
    }
}
SooTexture *SooRenderer::CreateTexture(TTF_Font *font,const char *text,SDL_Color color)
{
    SDL_Surface *surf=TTF_RenderUTF8_Solid(font,text,color);
    if(surf == NULL){
        throw EX(TTF_GetError());
        
    }
    SDL_Texture *texture=SDL_CreateTextureFromSurface(mRenderer,surf);
    SDL_FreeSurface(surf);
    if(texture==NULL){
        throw EX(SDL_GetError());
    }
    return new SooTexture(texture);
}
SooTexture *SooRenderer::CreateTexture(const char *image)
{
    SDL_Texture *texture=IMG_LoadTexture(mRenderer,image);
    if(texture==NULL){
        throw EX(IMG_GetError());
    }
    return new SooTexture(texture);
}
SooTexture *SooRenderer::CreateTexture(Uint32 format,int access,int w,int h)
{
    SDL_Texture *texture=SDL_CreateTexture(mRenderer,format,access,w,h);
    if(texture==NULL){
        throw EX(SDL_GetError());
    }
    return new SooTexture(texture);
}
void SooRenderer::RenderCopy(SooTexture *texture,const SDL_Rect *srcrect,const SDL_Rect *dstrect){
    if(SDL_RenderCopy(mRenderer,texture->mTexture,srcrect,dstrect)){
        throw EX(SDL_GetError());
    }
}
void SooRenderer::SetRenderTarget(SooTexture *texture)
{
    auto raw = (texture==nullptr)?nullptr:texture->mTexture;
    if(SDL_SetRenderTarget(mRenderer,raw)){
        throw EX(SDL_GetError());
    }
}