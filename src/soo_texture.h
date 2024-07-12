#pragma once

#include <SDL.h>
class SooRenderer;
/**
 * @brief class Texture is a data of view in memory
 */
class SooTexture{
private:
    SDL_Texture *mTexture;
    SooTexture(SDL_Texture *);
public:
    virtual ~SooTexture();
    void GetSize(int *w,int *h);
    void SetColor(Uint8 r,Uint8 g, Uint8 b);
    void SetAlphaMod(Uint8 alpha);
    friend class SooRenderer;
};