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
    GameData::init(&app);
    app.run();
}