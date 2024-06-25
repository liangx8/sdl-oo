#include <SDL_image.h>
#include "soo_surface.h"
#include "soo_exception.h"
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