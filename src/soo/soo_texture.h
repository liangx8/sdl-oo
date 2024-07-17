#pragma once

#include <SDL.h>
#include <SDL_ttf.h>

typedef void (*pixelMofify)(void *pixels,int pitch,int height);
class SooRenderer;
/**
 * @brief class Texture is a data of view in memory
 */
class SooTexture{
private:
    SDL_Texture *mTexture;
public:
    /**
     * @brief Create a texture from image
     */
    SooTexture(SooRenderer *render,const char *image);
    SooTexture(SooRenderer *render,TTF_Font *font,const char *text,SDL_Color color);
    SooTexture(SooRenderer *render,Uint32 format,int access,int w,int h);
    SooTexture(const SooTexture &)=delete;
    virtual ~SooTexture();
    void GetSize(int *w,int *h);
    void SetColor(Uint8 r,Uint8 g, Uint8 b);
    void SetAlphaMod(Uint8 alpha);
    void render(SooRenderer *target,SDL_Rect *src,SDL_Rect *dst);
    void setRenderTarget(SooRenderer *render);
    void modify(const SDL_Rect*,pixelMofify);
};