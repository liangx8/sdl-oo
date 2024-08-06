

#include <iostream>
#include <exception>
#include <memory>
#include "soo/sdl_app.h"
#include "game_data.h"

/*
        Uint32      flag,
        Uint32      imgFlag,
        const char *title,
        int w,
        int h,
        Uint32 winFlag);

*/
int main(int argc,char **argv)
{
    int res;
    try {
        SdlApplication app("ありがとうございます");
        app.run();
    }catch(std::exception &e){
        std::cout <<e.what();
        res=-1;
    }
    return res;
}
