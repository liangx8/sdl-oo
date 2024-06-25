#ifndef SOO_SURFACE_H_NBJWER3K3
#define SOO_SURFACE_H_NBJWER3K3
#include <SDL.h>

class SooWindow;
class SooSurface{
public:
    SooSurface(const char *image);
    virtual ~SooSurface();

private:
    SooSurface(SDL_Surface *);
    SDL_Surface *mSurf;
    friend class SooWindow;
};
#endif