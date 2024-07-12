#include "soo_texture.h"
#include "soo_exception.h"

SooTexture::SooTexture(SDL_Texture *ttr):mTexture(ttr){}
// SooTexture::SooTexture(TTF_Font *font,const char *text,SDL_Color color)
// {
//     SDL_Surface *surf=TTF_RenderUTF8_Solid(font,text,color);
//     if(surf == NULL){
//         EX(TTF_GetError());
//     }
// }

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