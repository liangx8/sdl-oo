#include "soo/soo_exception.h"
#include "soo/sdl_texture.h"
#include "soo/soo_model.h"
#include "mygame.h"
#include "game_data.h"

MyGame::MyGame(const char *n):SooApp(),name(n){
}
int MyGame::init(void *param){
    GameData *gd=static_cast<GameData *>(param);
    setModel(gd->menu);
    gd->background->renderCopy(gd->renderer,nullptr,nullptr);
    return 0;
}

int MyGame::release(void *)
{
    return 0;
}
MyGame::~MyGame(){}