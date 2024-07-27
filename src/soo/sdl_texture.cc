#include "sdl_texture.h"
#include <SDL2/SDL_image.h>
#include "soo_exception.h"

SdlTexture::SdlTexture(SDL_Renderer *renderer,Uint32 format,int access,int w,int h):
    m_width(w),m_height(h)
{
    m_texture=SDL_CreateTexture(renderer,format,access,w,h);
    if(m_texture==nullptr){
        throw EX(SDL_GetError());
    }
}
SdlTexture::SdlTexture(SDL_Renderer *renderer,const char *image)
{
    m_texture=IMG_LoadTexture(renderer,image);
    if(m_texture==nullptr){
        throw EX(IMG_GetError());
    }
    SDL_QueryTexture(m_texture,nullptr,nullptr,&m_width,&m_height);

}
SdlTexture::SdlTexture(SDL_Renderer *renderer,TTF_Font *font,const char *text,SDL_Color *color)
{
    SDL_Surface *surf=TTF_RenderUTF8_Solid(font,text,*color);
    if(surf == nullptr){
        throw EX(TTF_GetError());
    }
    m_texture=SDL_CreateTextureFromSurface(renderer,surf);
    SDL_FreeSurface(surf);
    if(m_texture==nullptr){
        throw EX(SDL_GetError());
    }
    SDL_QueryTexture(m_texture,nullptr,nullptr,&m_width,&m_height);
}

SdlTexture::~SdlTexture()
{
    SDL_DestroyTexture(m_texture);
}
const char* SdlTexture::className()const
{
    return "SdlTexture";
}
void SdlTexture::asTarget(SDL_Renderer *renderer)
{
    SDL_SetRenderTarget(renderer,m_texture);
}
void SdlTexture::paintInPixel(PaintPixels pp,SDL_Rect *re,void *param)
{
    void *pixels;
    int pitch;
    // SDL_Rect 参数暂时不用，因为还搞不懂当有这个参数后，pixels的高度是怎么设定
    if(SDL_LockTexture(m_texture,NULL,&pixels,&pitch)){
        throw EX(SDL_GetError());
    }
    SDL_Log("TEXTURE(%d,%d),pitch:%d",m_width,m_height,pitch);
    pp(pixels,pitch,m_height,param);
    SDL_UnlockTexture(m_texture);
}
void SdlTexture::renderCopy(SDL_Renderer *renderer,SDL_Rect *src,SDL_Rect *dst) const
{
    if(SDL_RenderCopy(renderer,m_texture,src,dst)){
        throw EX(SDL_GetError());
    }
}
void SdlTexture::getSize(int *w,int *h) const
{
    *w=m_width;
    *h=m_height;
}