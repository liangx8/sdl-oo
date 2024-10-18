#include <string.h>
#include <memory>
#include <random>
#include <vector>
#include "soo/soo_exception.h"
#include "soo/sdl_view.h"
#include "blpu.h"
#include "game_data.h"

extern std::mt19937 rand32;
extern const Uint16 *blpu_block;
#define RED(u32)   (((u32) >> 24) & 0xff)
#define GREEN(u32) (((u32) >> 16) & 0xff)
#define BLUE(u32)  (((u32) >> 8)  & 0xff)
#define ALPHA(u32) ((u32) & 0xff)

#define BG_R 0x74
#define BG_G 0xa0
#define BG_B 0x30
#define BG_GAP 10

#define BOARD_X_RATE   0.02f
#define BOARD_Y_RATE   0.05f



//#define UNIT_SIZE 20
/* 定义２个SdlView派生类，并实例化
一个是空白背景，另一个是游戏画面
*/
class backgroundView:public SdlView{
public:
    blockPuzzleData *m_data;
    virtual int paint(SDL_Renderer *);
};
class nextBlockView:public SdlView{
public:
    blockPuzzleData *m_data;
    virtual int paint(SDL_Renderer *);
};

class blockPuzzleData{
public:
    int                        x,y,cols,rows;
    int                        nx,ny;         // 下一块的窗口位置
    std::vector<Uint16>        curr;
    std::unique_ptr<uint8_t[]> matrix;        // 整个方块的描述:0是空位置,其他值则是颜色索引
    backgroundView             background;
    nextBlockView              viewNextBlock;
    Uint16                     nextBlock;
    uint8_t                    color_idx1;
    uint8_t                    color_idx2;
    int                        unitSize;
    int                        updataNext;
};
void backgroundClean(SDL_Renderer *ren,int outx,int outy,int cols,int rows,int unitSize){
    // outer rectangle
    SDL_Rect rect={
        outx,
        outy,
        cols * (unitSize+1)+1,
        rows * (unitSize+1)+1
    };
    THROW_SDL_NOT_ZERO(SDL_SetRenderDrawColor(ren,0,0,0xff,0xff))
    THROW_SDL_NOT_ZERO(SDL_RenderDrawRect(ren,&rect))
    rect.x=outx+1;
    rect.y=outy+1;
    rect.w=rect.w-2;
    rect.h=rect.h-2;
    THROW_SDL_NOT_ZERO(SDL_SetRenderDrawColor(ren,BG_R,BG_G,BG_B,0xf0))
    THROW_SDL_NOT_ZERO(SDL_RenderFillRect(ren,&rect))
    THROW_SDL_NOT_ZERO(SDL_SetRenderDrawColor(ren,BG_R-BG_GAP,BG_G-BG_GAP,BG_B-BG_GAP,0xf0))
    for(int xx=1;xx<cols;xx++){
        THROW_SDL_NOT_ZERO(SDL_RenderDrawLine(ren,outx+xx * (unitSize+1),outy+1,outx+xx * (unitSize+1),outy+rect.h))
    }
    for(int yy=1;yy<rows;yy++){
        THROW_SDL_NOT_ZERO(SDL_RenderDrawLine(ren,outx+1,outy+yy * (unitSize+1),outx+rect.w,outy+yy*(unitSize +1)))
    }
}

int nextBlockView::paint(SDL_Renderer *ren)
{
    GameData *gd=GameData::getInstance();
    Uint16 block=m_data->nextBlock;
    SDL_Rect rect;
    Uint32 color=*(gd->colors+m_data->color_idx1);
    int outx=m_data->nx;
    int outy=m_data->ny;
    rect.x=outx+1;
    rect.y=outy+1;
    rect.w=m_data->unitSize;
    rect.h=m_data->unitSize;
    THROW_SDL_NOT_ZERO(SDL_SetRenderDrawColor(ren,RED(color),GREEN(color),BLUE(color),0xff))
    for(int ix=0;ix<8;ix++){
        if(block){
            if(block & 1){
                // 画一格
                THROW_SDL_NOT_ZERO(SDL_RenderFillRect(ren,&rect))
            }
        } else {
            break;
        }
        block = block >> 1;
        rect.x+=m_data->unitSize+1;
    }
    rect.x=outx+1;
    rect.y=m_data->unitSize+1;
    for(int ix=8;ix<16;ix++){
        if(block){
            if(block & 1){
                // 画一格
                THROW_SDL_NOT_ZERO(SDL_RenderFillRect(ren,&rect))
            }
        } else {
            break;
        }
        block = block >> 1;
        rect.x+=m_data->unitSize+1;
    }
    return 0;
}
int backgroundView::paint(SDL_Renderer *ren)
{
    backgroundClean(ren,m_data->x,m_data->y,m_data->cols,m_data->rows,m_data->unitSize);
    // next block window
    backgroundClean(ren,m_data->nx,m_data->ny,8,2,m_data->unitSize);
    return 0;
}


void BlockPuzzle::next()
{
    auto u32=rand32();
    auto idx=u32 % 11;
    m_data->nextBlock=blpu_block[idx];
    m_data->color_idx1=(u32 >> 8) & 0xff;
}

BlockPuzzle::BlockPuzzle(int win_w,int win_h,int cols,int rows,uint32_t *colors)
{
    blockPuzzleData *data=new blockPuzzleData();
    
    int board_y=win_h * BOARD_Y_RATE;
    data->unitSize=(win_h - board_y * 2)/rows;
    int board_x=win_w-data->unitSize * (cols+1)-9* data->unitSize - 8 * (data->unitSize +1);
    board_x = board_x/2;
    SDL_Log("blpu_func.cc(114)unit size:%d",data->unitSize);
    data->x    = board_x;
    data->y    = board_y;
    data->nx   = board_x + cols * (data->unitSize+1)+1 + (data->unitSize+1)*9;
    data->ny   = board_y + 20;
    data->cols = cols;
    data->rows = rows;
    data->matrix=std::make_unique<uint8_t[]>(cols*rows);
    bzero(data->matrix.get(),cols*rows);
    m_data=data;
    data->background.m_data=data;
    data->viewNextBlock.m_data=data;
    data->updataNext=1;
    next();

}
SdlView* BlockPuzzle::background()
{
    return &(m_data->background);
}
SdlView* BlockPuzzle::update()
{
    if(m_data->updataNext){
        m_data->updataNext=0;
        return &(m_data->viewNextBlock);
    }
    return nullptr;
}
BlockPuzzle::~BlockPuzzle(){
    delete m_data;
}

