#pragma once
#include <SDL2/SDL.h>
class SdlTexture;
class SooModel;
class SooCommand;
class SooApp;
class GameData{
public:
    SooApp         *app;
    SDL_Window     *win;
    SDL_Renderer   *renderer;
    SDL_DisplayMode dm;
    int             win_w,win_h;
    SooModel        *menu,*game;

    GameData(SooApp *);
    virtual ~GameData();
    SdlTexture *background;
    Uint32 colors[256];
};
#define RGBA8888(r,g,b,a) ((a) | ((b)<<8) | ((g)<<16) | ((r)<<24))


#define RED(u32)   (((u32) >> 24) & 0xff)
#define GREEN(u32) (((u32) >> 16) & 0xff)
#define BLUE(u32)  (((u32) >> 8)  & 0xff)
#define ALPHA(u32) ((u32) & 0xff)