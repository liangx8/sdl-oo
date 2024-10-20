#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
class SdlApplication;
/// @brief 创建texture时，选参数ACCESSTREAM,用pixels构建内容使用的回调函数
typedef int (*PaintPixels)(void *pixels,int pitch,int height,void *param);
class SdlTexture{
    SDL_Texture *m_texture;
    int          m_width;
    int          m_height;
    //SDL_Renderer *m_renderer;
public:
    SdlTexture(SDL_Renderer *ren,Uint32 format,int type,int w,int h);
    SdlTexture(SDL_Renderer *ren,const char *image);
    SdlTexture(SDL_Renderer *ren,TTF_Font *font,const char *text,SDL_Color *color);
    virtual ~SdlTexture();
    void asTarget(SDL_Renderer *renderer);
    void paintInPixel(PaintPixels,SDL_Rect *,void *param);
    void renderCopy(SDL_Renderer *ren,SDL_Rect *,SDL_Rect *) const;
    void getSize(int *w,int *h) const;
};