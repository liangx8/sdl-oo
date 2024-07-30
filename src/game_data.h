#pragma once
#include <SDL2/SDL.h>
class SdlTexture;
class SooModel;
class SooCommand;
class GameData{
public:
    SDL_Window     *win;
    SDL_Renderer   *renderer;
    SDL_DisplayMode dm;
    int             win_w,win_h;
    SooModel        *menu,*game;
    // change model
    SooCommand      *setModel;

    GameData();
    virtual ~GameData();
    SdlTexture *background;
};