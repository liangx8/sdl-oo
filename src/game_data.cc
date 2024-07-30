#include <SDL2/SDL.h>
#include "soo/soo_exception.h"
#include "soo/sdl_texture.h"
#include "game_data.h"
#define SCREEN_MARGIN 100


#define RGBA8888(r,g,b,a) ((a) | ((b)<<8) | ((g)<<16) | ((r)<<24))

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
    const Uint32 bg     = SDL_MapRGBA(format,0x12,0x34,0x56,0);
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
SooModel *createMenuModel(SDL_Renderer *render,int win_w);
SooModel *createGameModel(SDL_Renderer *);
GameData::GameData()
{
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_JOYSTICK)){
        throw EX(SDL_GetError());
    }
    if(TTF_Init()){
        throw EX(TTF_GetError());
    }
    if(SDL_GetCurrentDisplayMode(0,&dm)){
        throw EX(SDL_GetError());
    }
    int num;
    if((num=SDL_NumJoysticks())<1){
        SDL_LogWarn(0,"没发现手柄");
    } else {
        SDL_Log("检测到%d个手柄",num);
    }
    win_w  = dm.w - (SCREEN_MARGIN * 4);
    win_h = dm.h - (SCREEN_MARGIN * 2);
    if(SDL_CreateWindowAndRenderer(win_w,win_h,0,&win,&renderer)){
        throw EX(SDL_GetError());
    }
    SDL_SetWindowTitle(win,"方块消除");
    // background
    background=new SdlTexture(renderer,SDL_PIXELFORMAT_RGBA8888,SDL_TEXTUREACCESS_STREAMING,win_w,win_h);
    SDL_Log("window size(%d,%d)",win_w,win_h);
    background->paintInPixel(paint_bg,nullptr,nullptr);
    menu=createMenuModel(renderer,win_w);
    game=createGameModel(renderer);
    
}

void deleteMenuModel(SooModel *);
void deleteGameModel(SooModel *);
GameData::~GameData()
{
    deleteMenuModel(menu);
    deleteGameModel(game);
    delete background;
    SDL_Quit();
}