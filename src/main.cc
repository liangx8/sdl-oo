#include <iostream>
#include <string>
#include <exception>
#include "mygame.h"

using namespace std;

int main(int argc,char **argv)
{
    try {
        MyGame game("消除游戏");
        game.Poll();
    }catch(exception &e){
        cout <<e.what();
    }
    return 0;
}