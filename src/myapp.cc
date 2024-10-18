#include "soo/sdl_app.h"
#include "game_data.h"


class myapp:public SdlApplication{
public:
    virtual void init(){
        setModel(GameData::getInstance()->menu);
    }
    myapp(const char *t):SdlApplication(t){}
};


void gamestart(){
    myapp app("ありがとうございます");
    int sw,sh;// screen size
    app.getScreenSize(&sw,&sh);
    if(sw >1300){
        sw=1300;
    }
    int win_w=sh * 4 / 3;
    int win_h=sw * 3 / 4;
    if(win_h > sh){
        win_h=sh;
    }
    if(win_w > sw){
        win_w=sw;
    }
    app.setWindowSize(win_w,win_h);
    SDL_Log("myapp.cpp: window size:%d,%d",win_w,win_h);
    GameData::init(&app);

    app.run();
}