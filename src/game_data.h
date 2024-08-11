#pragma once
#include <memory>
#include <SDL2/SDL.h>
#include "soo/sdl_view.h"
class SdlTexture;
class SdlModel;
class SdlApplication;
class GameData :public SdlView{
private:
    static std::unique_ptr<GameData> instancePtr;
    GameData(SdlApplication  *app);
public:
    SdlApplication  *app;
    SdlModel        *menu,*game;
    SdlTexture      *background;
    Uint32           colors[256];
    GameData(const GameData&)=delete;
    virtual          ~GameData();
    static GameData* getInstance();
    static void      init(SdlApplication *app);
    virtual int      paint(SDL_Renderer *);
};
#define RGBA8888(r,g,b,a) ((a) | ((b)<<8) | ((g)<<16) | ((r)<<24))


#define RED(u32)   (((u32) >> 24) & 0xff)
#define GREEN(u32) (((u32) >> 16) & 0xff)
#define BLUE(u32)  (((u32) >> 8)  & 0xff)
#define ALPHA(u32) ((u32) & 0xff)