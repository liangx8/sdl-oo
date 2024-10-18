/**
 * @file blpu.h block puzzle
 * @brief 数据结构
 */
#pragma once
#include <stdint.h>
class SdlView;
class blockPuzzleData;
class BlockPuzzle
{
private:
    blockPuzzleData *m_data;
public:
    BlockPuzzle(int,int,int ,int ,uint32_t *);
    SdlView *background();
    SdlView *update();
    void     next();
    virtual ~BlockPuzzle();
};