#include <random>
#include "soo/soo_exception.h"
#include "game_data.h"
#define CELL_SIZE 20


class GameArea{
    //SDL_Rect area;
public:
    const int ax,ay;
    const int cols;
    const int rows;
    GameArea(int x,int y,int c,int r):ax(x),ay(y),cols(c),rows(r){}

};

GameArea gameMain(110,-1,46,42);
GameArea gamePreview(1200,150,8,2);
#define AREA_R 0x8e
#define AREA_G 0xb6
#define AREA_B 0x8a
int _draw_area(GameData *gd,GameArea *ga)
{
    const int width = ga->cols * (CELL_SIZE + 1) + 1;
    const int height= ga->rows * (CELL_SIZE + 1) + 1;
    int y=ga->ay;
    if(y<0){
        y= (gd->win_h-height)/2;
    }
    const auto x=ga->ax;
    SDL_Rect rect{x,y,width,height};
    // background color
    THROW_SDL_NOT_ZERO(SDL_SetRenderDrawColor(gd->renderer,AREA_R,AREA_G,AREA_B,0xff))
    THROW_SDL_NOT_ZERO(SDL_RenderFillRect(gd->renderer,&rect))
    // outer border color
    THROW_SDL_NOT_ZERO(SDL_SetRenderDrawColor(gd->renderer,0,0xd3,0xb0,0xff))
    THROW_SDL_NOT_ZERO(SDL_RenderDrawRect(gd->renderer,&rect))
    THROW_SDL_NOT_ZERO(SDL_SetRenderDrawColor(gd->renderer,AREA_R-10,AREA_G-10,AREA_B-10,0xff))
    for(int ix=0;ix<ga->rows-1;ix ++){
        int ya=y + (ix + 1) * (CELL_SIZE + 1);
        THROW_SDL_NOT_ZERO(SDL_RenderDrawLine(gd->renderer,x+1,ya,x+width-2,ya))
    }
    for(int ix=0;ix<ga->cols-1;ix ++){
        int xa=x + (ix + 1) * (CELL_SIZE + 1);
        THROW_SDL_NOT_ZERO(SDL_RenderDrawLine(gd->renderer,xa,y+1,xa,y+height-2))
    }
    return 0;
}
int game_draw(GameData *gd)
{
    if(_draw_area(gd,&gameMain)){
        return -1;
    }
    if(_draw_area(gd,&gamePreview)){
        return -1;
    }
    return 0;
}
//THROW_SDL_NOT_ZERO