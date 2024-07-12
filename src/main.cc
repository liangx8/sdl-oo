
#if 1

#include <iostream>
#include <exception>
#include <memory>
#include "mygame.h"


int main(int argc,char **argv)
{
    try {
        auto game=std::make_unique<MyGame>("消除游戏");
        game->Run();
    }catch(std::exception &e){
        std::cout <<e.what();
    }
    return 0;
}

#else
#include <memory>
#include "test_yes.h"

using namespace std;
int main(int argc,char **argv)
{
    unique_ptr<Yes> ok(new Yes("a","b",10));
    ok->show();
}
#endif
