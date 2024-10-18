#include "soo/sdl_model.h"
#include "soo/sdl_app.h"
#include "soo/sdl_texture.h"
#include "soo/sdl_view.h"
#include "game_data.h"
#include "blpu.h"

#define COL_NUM           35

class ModelBlockPuzzle:public SdlModel{
private:
    BlockPuzzle *m_blockPuzzle;
public:
    virtual void attach(SdlApplication *);
    virtual void onEvent(SDL_Event *ev,SdlApplication *);
    virtual void present(SdlApplication *);
    virtual void detach(SdlApplication *);
};
//extern SdlView *blockPuzzleBackground;
void ModelBlockPuzzle::attach(SdlApplication *app){
    GameData *gd=GameData::getInstance();
    int w,h;
    app->getSize(&w,&h);
    m_blockPuzzle = new BlockPuzzle(w,h,COL_NUM,40,&gd->colors[0]);
    app->renderView(m_blockPuzzle->background());
    SDL_Log("block puzzle attach");
}

void ModelBlockPuzzle::present(SdlApplication *app){
    auto view=m_blockPuzzle->update();
    if(view != nullptr){
        SDL_Log("model_block_puzzle.cc(32):check point");
        app->renderView(view);
    }
}
void ModelBlockPuzzle::detach(SdlApplication *app){
    delete m_blockPuzzle;
    SDL_Log("block puzzle detach");
}
void ModelBlockPuzzle::onEvent(SDL_Event *ev,SdlApplication *app){
    GameData *gd=GameData::getInstance();
    if (ev->type == SDL_KEYUP){
        if(ev->key.keysym.sym==SDLK_ESCAPE){
            app->setModel(gd->menu);
        }
    }
}
ModelBlockPuzzle blockPuzzle;
SdlModel *getGame(){
    // 初始化block puzzle的准备数据
    return &blockPuzzle;
}