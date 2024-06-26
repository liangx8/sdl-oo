#include "soo_renderer.h"
#include "soo_exception.h"
SooRenderer::SooRenderer(SDL_Renderer *ren):mRenderer(ren){}
SooRenderer::~SooRenderer(){
    SDL_DestroyRenderer(mRenderer);
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
void SooRenderer::FillRect(const SDL_Rect *rect){
    if(SDL_RenderFillRect(mRenderer,rect)){
        throw EX(SDL_GetError());
    }
}
void SooRenderer::Present() throw(){
    SDL_RenderPresent(mRenderer);
}
void SooRenderer::DrawLine(int x1,int y1,int x2,int y2){
    if(SDL_RenderDrawLine(mRenderer,x1,y1,x2,y2)){
        throw EX(SDL_GetError());
    }
}