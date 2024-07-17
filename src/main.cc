
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
        std::cout << "正常结束" << std::endl;
    }catch(std::exception &e){
        std::cout <<e.what();
    }
    return 0;
}

#else
#include <memory>
#include "test_yes.h"

using namespace std;


void run_test();
int main(int argc,char **argv)
{
    run_test();
    
}
#endif
