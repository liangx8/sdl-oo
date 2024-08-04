#include <random>
#include "soo/soo_exception.h"
#include "game_data.h"
#include "game_func_data.h"
#include "game_thread_data.h"
#define CELL_SIZE   20

std::mt19937 rand32;
const MBLOCK sqr1=0b1;
const MBLOCK bar2=0b11;
const MBLOCK bar3=0b111;
const MBLOCK bar4=0b1111;

/**
 * -----
 */
const MBLOCK bar5=0b11111;
const MBLOCK bar8=0b11111111;
/**
 * -+
 *  +--
 */
const MBLOCK z1=0b11+(0b00001110<<8);
/**
 * -+
 *  +--
 */
const MBLOCK z2    = 0b111+(0b11100<<8);
const MBLOCK longL = 0b111111111;
const MBLOCK c3    = 0b111+(0b0101<<8);
const MBLOCK c4    = 0b1111+(0b1001<<8);
const MBLOCK square= 0b11+(0b11 << 8);
const MBLOCK barray[]={sqr1,bar2,bar3,bar4,bar5,bar8,z1,z2,longL,c3,c4,square};
/// @brief 把MBLOCK类型导入到fall数组中
void intrudce(std::vector<Uint16>& vec,MBLOCK blk)
{
    vec.clear();
    MBLOCK bb = blk;
    for(int ix=0;ix<(int)(sizeof(MBLOCK)*8);ix++){
        if(bb & 1){
            vec.push_back(static_cast<Uint16>(ix));
        }
        bb = bb >> 1;
        if(bb == 0)break;
    }
}


GameBase::GameBase(int x,int y):ax(x),ay(y),bgcolor(0),fgcolor(1),block(barray[rand32()%12]){}
void GameBase::getSize(int *cols,int *rows) const{
    *cols=8;
    *rows=2;
}
void GameArea::getSize(int *cols,int *rows) const{
    *cols=m_cols;
    *rows=m_rows;
}
GameArea::GameArea(int x,int y,int c,int r)try:
    GameBase(x,y),
    m_rows(r),
    m_cols(c),
    matrix(new Uint8[c*r]){
        intrudce(fall,block);
    }catch(...){throw;}

GameArea::~GameArea()
{
    delete [] matrix;
}

GameArea gameMain(110,-1,46,42);
GameBase gamePreview(1200,150);
static BlockMove _left(MOVE_LEFT);
static BlockMove _right(MOVE_RIGHT);
static BlockMove _down(MOVE_DOWN);


SooCommand *left   = &_left;
SooCommand *right  = &_right;
SooCommand *down   = &_down;

void _draw_block(GameData *gd,GameBase *ga,const std::vector<Uint16> &data)
{
    Uint32 color=gd->colors[ga->fgcolor % 12];
    SDL_Log("block:0x%x,color: 0x%x",ga->block,color);
    THROW_SDL_NOT_ZERO(SDL_SetRenderDrawColor(gd->renderer,RED(color),GREEN(color),BLUE(color),ALPHA(color)))
    SDL_Rect box{0,0,CELL_SIZE,CELL_SIZE};
    const auto stx=ga->ax;
    const auto sty=ga->ay;
    int cols;
    int rows;
    ga->getSize(&cols,&rows);
    for(auto itr=data.begin();itr != data.end();itr++){
        const auto idx= *itr;
        const auto x=idx % cols;
        const auto y=idx / cols;
        box.x=stx + 1 + x * (CELL_SIZE + 1);
        box.y=sty + 1 + y * (CELL_SIZE + 1);
        THROW_SDL_NOT_ZERO(SDL_RenderFillRect(gd->renderer,&box))
    }
}

void _draw_area(GameData *gd,GameBase *ga)
{
    int cols,rows;
    ga->getSize(&cols,&rows);
    const int width = cols * (CELL_SIZE + 1) + 1;
    const int height= rows * (CELL_SIZE + 1) + 1;
    int y=ga->ay;
    if(y<0){
        y= (gd->win_h-height)/2;
    }
    const auto x=ga->ax;
    SDL_Rect rect{x,y,width,height};
    // background color
    Uint32 color=gd->colors[ga->bgcolor & 0xff];
    if(ga->bgcolor){
        SDL_Log("color idx: %2d, color: 0x%08x",ga->bgcolor & 0xff,color);
    }
    const Uint8 ca=color & 0xff;
    const Uint8 cr=(color >> 24) & 0xff;
    const Uint8 cg=(color >> 16) & 0xff;
    const Uint8 cb=(color >> 8 ) & 0xff;
    THROW_SDL_NOT_ZERO(SDL_SetRenderDrawColor(gd->renderer,cr,cg,cb,ca))
    THROW_SDL_NOT_ZERO(SDL_RenderFillRect(gd->renderer,&rect))
    // outer border color
    THROW_SDL_NOT_ZERO(SDL_SetRenderDrawColor(gd->renderer,0,0xd3,0xb0,0xff))
    THROW_SDL_NOT_ZERO(SDL_RenderDrawRect(gd->renderer,&rect))
    THROW_SDL_NOT_ZERO(SDL_SetRenderDrawColor(gd->renderer,cr-10,cg-10,cb-10,ca))
    for(int ix=0;ix<rows-1;ix ++){
        int ya=y + (ix + 1) * (CELL_SIZE + 1);
        THROW_SDL_NOT_ZERO(SDL_RenderDrawLine(gd->renderer,x+1,ya,x+width-2,ya))
    }
    for(int ix=0;ix<cols-1;ix ++){
        int xa=x + (ix + 1) * (CELL_SIZE + 1);
        THROW_SDL_NOT_ZERO(SDL_RenderDrawLine(gd->renderer,xa,y+1,xa,y+height-2))
    }
}
void game_background(int idx)
{
    gameMain.bgcolor=idx;
}

void game_draw(GameData *gd)
{
    std::vector<Uint16> vec;
    _draw_area(gd,&gameMain);
    _draw_area(gd,&gamePreview);
    intrudce(vec,gamePreview.block);
    _draw_block(gd,&gamePreview,vec);
}

class NextBlock:public SooCommand{
public:
    int execute(void *pl){
        gameMain.block=gamePreview.block;
        gameMain.fgcolor=gamePreview.fgcolor;
        int color=gamePreview.fgcolor+1;
        if(color == gameMain.bgcolor || color == gamePreview.bgcolor){
            color ++;
        }
        gamePreview.block=barray[rand32()%12];
        gamePreview.fgcolor=color;
        // 触发填充内容到游戏窗口的程序
        return 0;
    }
};
static NextBlock _nextblock;
SooCommand *nextBlock=&_nextblock;

//THROW_SDL_NOT_ZERO