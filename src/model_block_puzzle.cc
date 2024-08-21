#include "soo/sdl_model.h"
#include "soo/sdl_app.h"
#include "soo/sdl_texture.h"
#include "soo/sdl_view.h"
#include "game_data.h"
#include "game_block_puzzle.h"

class ModelBlockPuzzle:public SdlModel{
public:
    virtual void attach(SdlApplication *);
    virtual void onEvent(SDL_Event *ev,SdlApplication *);
    virtual void present(SdlApplication *);
    virtual void detach(SdlApplication *);
};
//extern SdlView *blockPuzzleBackground;
void ModelBlockPuzzle::attach(SdlApplication *app){
    //GameData *gd=GameData::getInstance();
    int w,h;
    app->getSize(&w,&h);
    int gamew = BLOCK_PUZZLE_SIZE*COL_NUM;
    int gamex = (w - gamew)/2;
    SDL_Rect rect={gamex,100,gamew,h-200};
    app->pushSdlView(fillRect(&rect,RGBA8888(0x34,0x56,0x78,0xff)));
    SDL_Log("block puzzle attach");
}

void ModelBlockPuzzle::present(SdlApplication *app){

}
void ModelBlockPuzzle::detach(SdlApplication *app){
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