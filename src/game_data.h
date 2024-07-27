#pragma once
#include <SDL2/SDL.h>
class SdlTexture;
class SooModel;
class GameData{
public:
    SDL_Window     *win;
    SDL_Renderer   *renderer;
    SDL_DisplayMode dm;
    int             win_w,win_h;
    SooModel *menu,*game;

    GameData();
    virtual ~GameData();
    SdlTexture *background;
};