#pragma once
#include <SDL2/SDL.h>
#include <vector>
#include "soo/soo_command.h"
typedef Uint16 MBLOCK;
/********************************************************
 * @brief 预览框
 * 
 ********************************************************/
class GameBase{
public:
    const int    ax,ay;
    int          bgcolor;
    /// @brief 落下块颜色索引
    int          fgcolor;
    MBLOCK       block;
    GameBase(int x,int y);
    virtual void getSize(int *,int *)const;
};
/********************************************************
 * @brief 游戏框
 * 
 ********************************************************/
class GameArea :public GameBase{
private:
    const int m_rows,m_cols;
public:
    /// @brief 落下块
    std::vector<Uint16> fall;
    std::vector<Uint16> oldFall;
    Uint8              *matrix;

    GameArea(int x,int y,int c,int r);
    virtual void getSize(int *,int *)const;
    virtual ~GameArea();
};
#define MOVE_ROTATE     1
#define MOVE_LEFT       2
#define MOVE_RIGHT      3
#define MOVE_DOWN       4
#define MOVE_LAND       5
#define MOVE_SWIPE_LINE 6


class BlockMove:public SooCommand{
private:
    int m_dir;
public:
    int execute(void *);
    BlockMove(int dir);
};

