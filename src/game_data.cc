#include <random>
#include <memory>
#include <SDL2/SDL.h>
#include "soo/soo_exception.h"
#include "soo/sdl_texture.h"
#include "soo/sdl_app.h"
#include "soo/sdl_view.h"
#include "game_data.h"


class _GameData:public GameData,public SdlView{
public:
    _GameData(SdlApplication *);
    virtual          ~_GameData();
    virtual int      paint(SDL_Renderer *);
};

#define SCREEN_MARGIN 100
std::mt19937 rand32;

#define GRID 88
int paint_bg(void* pixels,int pitch,int height,void *param){
    int width=pitch/4;
    Uint32 *p=(Uint32*)pixels;
#ifdef RGBA8888
    const Uint32 bg     = RGBA8888(0x4b,0x7d,0x91,0xff);
    const Uint32 line   = RGBA8888(0x80,0x80,0x80,0x80);
    const Uint32 border = RGBA8888(0x80,0xff,0x80,0xff);
#else
    SDL_PixelFormat *format= SDL_AllocFormat(SDL_PIXELFORMAT_RGBA8888);
    const Uint32 bg     = SDL_MapRGBA(format,0x4b,0x7d,0x91,0xff);
    const Uint32 line   = SDL_MapRGBA(format,0x80,0x80,0x80,0x80);
    const Uint32 border = SDL_MapRGBA(format,0x80,0xff,0x80,0xff);
    SDL_FreeFormat(format);
#endif
    int bottom=(height-1)*width;
    for(int ix=0;ix<width;ix++){
        *(p+ix)=border;
        *(p + bottom+ix)=border;
    }
    for(int iy=1;iy<height-1;iy++){
        *(p + iy * width) = border;
        *(p + iy * width+width-1) = border;
        for(int ix=1;ix<width-1;ix++){
            if(((ix % GRID)==0) || ((iy %GRID)==0)){
                *(p + iy * width + ix)=line;
                continue;
            }
            *(p + iy * width + ix)=bg;
        }
    }
    
    return 0;
}

#define AREA_R 0x8e
#define AREA_G 0xb6
#define AREA_B 0x8a


_GameData::~_GameData(){
    delete background;
}
void initMenu(SdlApplication *);
SdlModel *getMenu();
std::unique_ptr<_GameData> instancePtr;
SdlModel *getGame();
_GameData::_GameData(SdlApplication *ap){
    app=ap;
    initMenu(ap);
    menu=getMenu();
    game=getGame();
    for(int ix=1;ix<256;ix++){
        colors[ix]=rand32();
    }
}
int _GameData::paint(SDL_Renderer *ren){
    int win_w,win_h;
    app->getSize(&win_w,&win_h);
    SDL_Log("window size(%d,%d)",win_w,win_h);
    background=new SdlTexture(ren,SDL_PIXELFORMAT_RGBA8888,SDL_TEXTUREACCESS_STREAMING,win_w,win_h);
    background->paintInPixel(paint_bg,nullptr,nullptr);
    return 0;
}
GameData* GameData::getInstance(){
    return instancePtr.get();
}
void GameData::init(SdlApplication *app)
{
    _GameData *pgd=new _GameData(app);
    instancePtr=std::unique_ptr<_GameData>(pgd);
    app->initRenderView(pgd);
}