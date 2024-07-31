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
};