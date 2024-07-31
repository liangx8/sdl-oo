

#include <iostream>
#include <exception>
#include <memory>
#include "mygame.h"
#include "game_data.h"


int main(int argc,char **argv)
{
    int res;
    try {
        auto game=std::make_unique<MyGame>("消除游戏");
        GameData data(game.get());
        res=game->run(&data);
        std::cout << "正常结束" << std::endl;
    }catch(std::exception &e){
        std::cout <<e.what();
        res=-1;
    }
    return res;
}
